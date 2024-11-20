#include "cprocessserver.h"
#include "cprocesssocket.h"
#include "cglobal.h"
#include "struct/cmsgnull.h"
#include "struct/cmsglog.h"
#include "struct/cmsgdeviceinfo.h"
#include "struct/cmsgobjectstatus.h"
#include "struct/cmsgfirepoint.h"
#include "struct/cmsgchecktime.h"
#include "struct/cmsgevacuationgroup.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QApplication>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QDomDocument>
#include <QXmlStreamReader>

CprocessServer::CprocessServer(QTcpServer *tcpServer) : m_tcpServer(tcpServer)
{
    m_timer = new QTimer();
    m_heartTimer = new QTimer();
    m_disconnectTimer = new QTimer();
    m_controlMasterTxtTimer = new QTimer();
    m_isMasterConnected = false;
    m_queryAllStateFlag = false;
    m_masterStateUploadFlag = false;
    m_lampSoftwareID = 0;
    m_distributionRealtimeDataID = 0;
    m_distributionSoftwareInfoID = 0;
    m_xmlheader = "version=\"1.0\" encoding=\"UTF-8\"";
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_serverlisten()));
    connect(m_heartTimer, SIGNAL(timeout()), this, SLOT(slot_heartBeat()));
    connect(m_disconnectTimer, SIGNAL(timeout()), this, SLOT(slot_handleDisconnected()));
    connect(m_controlMasterTxtTimer, SIGNAL(timeout()), this, SLOT(slot_controlMasterTxtFileSize()));
    m_timer->start(5000);
    m_controlMasterTxtTimer->start(5000);
}

CprocessServer::~CprocessServer()
{
    delete m_tcpServer;
    delete m_tcpSocket;
    delete m_timer;
    delete m_heartTimer;
    delete m_disconnectTimer;
}

void CprocessServer::slot_serverlisten()
{
    if (!m_tcpServer->listen(QHostAddress::Any, 8654))
    {
       return;
    }
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(slot_handleNewConnection()));
}

// 处理新的连接请求
void CprocessServer::slot_handleNewConnection()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();  // 接受新连接
    m_isMasterConnected = true;
    m_timer->stop();
    CGlobal::instance()->TimeInterval()->setComStatus();
    QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + QString("主从客户端连接成功: %1:%2").arg(m_tcpSocket->peerAddress().toString()).arg(m_tcpSocket->peerPort())
            + QLatin1Char('\n');
    //发送客户端数据保存到txt文件
    CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/masterData.txt", content);
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slot_readClientData()));  // 监听客户端数据
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(slot_handleDisconnected()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    m_heartTimer->start(4000);
}

void CprocessServer::onSocketError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    if (m_tcpSocket) {
        QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                + QLatin1Char('\n')
                + QString("Socket error occurred: ")
                + m_tcpSocket->errorString()
                + QLatin1Char('\n');
        CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/masterData.txt", content);
    }
}

//服务端xml格式模板初始化
void CprocessServer::serverXmlInit()
{
    m_xmldoc.clear();
    m_xmldoc.appendChild(m_xmldoc.createProcessingInstruction("xml",m_xmlheader));
    //根元素
    m_xmlroot = m_xmldoc.createElement("R");
    m_xmldoc.appendChild(m_xmlroot);
}

void CprocessServer::slot_heartBeat()
{
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("HeartbeatUpload");
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray());
}

// 读取客户端数据
void CprocessServer::slot_readClientData()
{
    if (m_tcpSocket) {
        QByteArray array = m_tcpSocket->readAll();  // 读取收到的数据
        // 处理收到的数据

        // 将已接收到的数据缓存
        m_receiveBuff.append(array);

        // 查找开始符和结束符的位置
        int start = m_receiveBuff.indexOf("<?");
        int end = m_receiveBuff.indexOf("</R>");

        while (start != -1 && end != -1) {
            // 提取完整的帧数据（包括开始符和结束符）
            QByteArray frameData = m_receiveBuff.mid(start, end - start + 4);

            // 处理帧数据
            processReceiveData(frameData);

            // 移除已处理的帧数据
            m_receiveBuff.remove(0, end + 4);

            // 继续查找下一个开始符和结束符的位置
            start = m_receiveBuff.indexOf("<?");
            end = m_receiveBuff.indexOf("</R>");
        }
    }
}


void CprocessServer::processReceiveData(QByteArray array)
{
    QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + QLatin1String("Receive:")
            + QLatin1Char('\n')
            + QString::fromUtf8(array)
            + QLatin1Char('\n');
    //收到客户端数据保存到txt文件
    saveDataToTxt("/home/xfss/root/logfile/masterData.txt", content);
    CMsgObjectStatus *xmlObjectStatus = new CMsgObjectStatus();
    QDomDocument doc;
    doc.setContent(array);
    QDomElement root = doc.documentElement();//根节点

    if(root.tagName() == "R")
    {
        QDomNode firstNode = root.firstChild();//第一个子节点
        while (!firstNode.isNull())
        {
            if (firstNode.isElement()) {
                QDomElement element = firstNode.toElement();
                //查询CAN设备
                if(element.tagName() == "QueryCanDevice")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("CanDeviceList");

                    CController* controller = CGlobal::instance()->controller();
                    if(!controller)
                        return;
                    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
                    {
                        CCanport* canport = controller->canportByAddress(i);
                        if(!canport)
                            continue;
                        QList <CDistribution*> distributions = canport->distributions();
                        for(int j=0; j<distributions.count(); j++)
                        {
                            CDistribution* distribution = distributions.at(j);
                            if(distribution)
                            {
                                int distributionkeyId = CGlobal::instance()->saveKeyId(OBJT_Distribution,distribution->keyId());
                                m_xmlitem_2 = m_xmldoc.createElement("D");
                                m_xmlitem_2.setAttribute("ID", distributionkeyId);
                                m_xmlitem_2.setAttribute("CanPort", i-2);
                                m_xmlitem_2.setAttribute("Address", distribution->distributionAddress());
                                m_xmlitem_2.setAttribute("DeviceType", "集中电源");
                                m_xmlitem_2.setAttribute("Area", distribution->distributionValue(DISTRIBUTION_VALUE_AREA).toString());
                                m_xmlitem_2.setAttribute("Location", distribution->distributionValue(DISTRIBUTION_VALUE_LOCATION).toString());
                                m_xmlitem_1.appendChild(m_xmlitem_2);
                            }
                        }
                        distributions.clear();
                    }
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询通道
                else if(element.tagName() == "QueryChannel")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("ChannelList");
                    CController* controller = CGlobal::instance()->controller();
                    if(!controller)
                        return;
                    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
                    {
                        CCanport* canport = controller->canportByAddress(i);
                        if(!canport)
                            continue;
                        QList <CDistribution*> distributions = canport->distributions();
                        for(int j=0; j<distributions.count(); j++)
                        {
                            CDistribution* distribution = distributions.at(j);
                            if(!distribution)
                                continue;
                            int distributionkeyId = CGlobal::instance()->saveKeyId(OBJT_Distribution,distribution->keyId());
                            for(int i=0; i<8; i++)
                            {
                                CLoop* loop = distribution->loopByAdd(i+1);
                                if(!loop)
                                    continue;
                                int loopkeyId = CGlobal::instance()->saveKeyId(OBJT_Loop,loop->keyId());
                                m_xmlitem_2 = m_xmldoc.createElement("C");
                                m_xmlitem_2.setAttribute("ID", loopkeyId);
                                m_xmlitem_2.setAttribute("CanDeviceID", distributionkeyId);
                                m_xmlitem_2.setAttribute("Number", loop->loopValue(LOOP_VALUE_NUMBER).toInt());
                                m_xmlitem_2.setAttribute("Loop", loop->loopAdd());
                                m_xmlitem_2.setAttribute("Remark", tr("通道%1").arg(loop->loopValue(LOOP_VALUE_NUMBER).toInt()));
                                m_xmlitem_1.appendChild(m_xmlitem_2);
                            }
                        }
                    }
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询灯具
                else if(element.tagName() == "QueryLamp")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("LampList");
                    CController* controller = CGlobal::instance()->controller();
                    if(!controller)
                        return;
                    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
                    {
                        CCanport* canport = controller->canportByAddress(i);
                        if(!canport)
                            continue;
                        QList <CDistribution*> distributions = canport->distributions();
                        for(int j=0; j<distributions.count(); j++)
                        {
                            CDistribution* distribution = distributions.at(j);
                            if(!distribution)
                                continue;
                            for(int l=0; l<8; l++)
                            {
                                CLoop* loop = distribution->loopByAdd(l+1);
                                if(!loop)
                                    continue;
                                int loopkeyId = CGlobal::instance()->saveKeyId(OBJT_Loop,loop->keyId());
                                QList <CDevice*> devices = loop->devices();
                                for(int m=0; m<devices.count(); m++)
                                {
                                    CDevice* device = devices.at(m);
                                    if(!device)
                                        return;
                                    int devicekeyId = CGlobal::instance()->saveKeyId(OBJT_Device,device->keyId());
                                    m_xmlitem_2 = m_xmldoc.createElement("L");
                                    m_xmlitem_2.setAttribute("ID", devicekeyId);
                                    m_xmlitem_2.setAttribute("CID", loopkeyId);
                                    m_xmlitem_2.setAttribute("A", device->deviceAdd());
                                    m_xmlitem_2.setAttribute("T", device->deviceTypeId());
                                    m_xmlitem_2.setAttribute("Ar", device->deviceValue(DEVICE_VALUE_AREA).toString());
                                    m_xmlitem_2.setAttribute("Lo", device->deviceValue(DEVICE_VALUE_LOCATION).toString());
                                    m_xmlitem_2.setAttribute("R", device->deviceValue(DEVICE_VALUE_DESCRIPTION).toString());
                                    m_xmlitem_1.appendChild(m_xmlitem_2);
                                }
                                devices.clear();
                            }
                        }
                        distributions.clear();
                    }
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询着火点
                else if(element.tagName() == "QueryFirePoint")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("FirePointList");

                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    CDBSqlite db(fileName);
                    if(!db.open())
                        return;
                    QSqlQuery query = db.query(QString("SELECT f.id,f.device,f.loop,f.address,f.area,f.location from FirePoint f"));
                    QSqlRecord record = query.record();
                    int fieldId = record.indexOf("id");
                    int fieldDevice = record.indexOf("device");
                    int fieldLoopAddress = record.indexOf("loop");
                    int fieldTerminalAddress = record.indexOf("address");
                    int fieldArea = record.indexOf("area");
                    int fieldLocation = record.indexOf("location");
                    while(query.next())
                    {
                        m_xmlitem_2 = m_xmldoc.createElement("FP");
                        m_xmlitem_2.setAttribute("ID", query.value(fieldId).toInt());
                        m_xmlitem_2.setAttribute("D", query.value(fieldDevice).toInt());
                        m_xmlitem_2.setAttribute("L", query.value(fieldLoopAddress).toInt());
                        m_xmlitem_2.setAttribute("A", query.value(fieldTerminalAddress).toInt());
                        m_xmlitem_2.setAttribute("Ar", query.value(fieldArea).toString());
                        m_xmlitem_2.setAttribute("Lo", query.value(fieldLocation).toString());
                        m_xmlitem_1.appendChild(m_xmlitem_2);
                    }
                    db.close();
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询灯具与着火点关联
                else if(element.tagName() == "QueryLampToFirePoint")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("LampToFirePointList");
                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    CDBSqlite db(fileName);
                    if(!db.open())
                        return;
                    QSqlQuery query = db.query(QString("SELECT f.ID,f.LampInfoId,f.FirePointID from LampToFirePoint f"));
                    QSqlRecord record = query.record();
                    int fieldId = record.indexOf("ID");
                    int fieldFirePointID = record.indexOf("FirePointID");
                    int fieldLampID = record.indexOf("LampInfoId");
                    while(query.next())
                    {
                        m_xmlitem_2 = m_xmldoc.createElement("LTFP");
                        m_xmlitem_2.setAttribute("ID", query.value(fieldId).toInt());
                        m_xmlitem_2.setAttribute("FPID", query.value(fieldFirePointID).toInt());
                        m_xmlitem_2.setAttribute("LID", query.value(fieldLampID).toInt());
                        m_xmlitem_1.appendChild(m_xmlitem_2);
                    }
                    db.close();
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询灯具连接信息
                else if(element.tagName() == "QueryLampConnection")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("LampConnection");

                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    CDBSqlite db(fileName);
                    if(!db.open())
                        return;
                    QSqlQuery query = db.query(QString("SELECT f.id,f.StartLampID,f.Joint,f.EndLampID from LampConnection f"));
                    QSqlRecord record = query.record();
                    int fieldId = record.indexOf("id");
                    int fieldStartLampID = record.indexOf("StartLampID");
                    int fieldEndLampID = record.indexOf("EndLampID");
                    int fieldJoint = record.indexOf("Joint");
                    while(query.next())
                    {
                        m_xmlitem_2 = m_xmldoc.createElement("LC");
                        m_xmlitem_2.setAttribute("ID", query.value(fieldId).toInt());
                        m_xmlitem_2.setAttribute("SID", query.value(fieldStartLampID).toInt());
                        m_xmlitem_2.setAttribute("EID", query.value(fieldEndLampID).toInt());
                        m_xmlitem_2.setAttribute("J", query.value(fieldJoint).toString());
                        m_xmlitem_1.appendChild(m_xmlitem_2);
                    }
                    db.close();
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询记录信息
                else if(element.tagName() == "QueryEvent")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("EventList");
                    QString eventType = element.attribute("Type");
                    QString fileName = CGlobal::instance()->workspaces() + "/" + "log.db";
                    CDBSqlite db(fileName);
                    if(!db.open())
                        return;
                    QString sql = QString("SELECT EventTypeID,Type,Time,CanPort,CanDeviceAddress,Loop,"
                                        "LampDeviceAddress,Area,Location,Remark from log WHERE Time > '%1' AND Time < '%2' ")
                                        .arg(element.attribute("StartTime"))
                                        .arg(element.attribute("EndTime"));
                    if(eventType != "")
                    {
                        sql.append(QString(" AND type = '%1'").arg(element.attribute("Type")));
                    }
                    QSqlQuery query = db.query(sql);
                    QSqlRecord record = query.record();
                    int fieldId = record.indexOf("EventTypeID");
                    int fieldType = record.indexOf("Type");
                    int fieldTime = record.indexOf("Time");
                    int fieldCanPort = record.indexOf("CanPort");
                    int fieldCanDeviceAddress = record.indexOf("CanDeviceAddress");
                    int fieldLoop = record.indexOf("Loop");
                    int fieldLampDeviceAddress = record.indexOf("LampDeviceAddress");
                    int fieldArea = record.indexOf("Area");
                    int fieldLocation = record.indexOf("Location");
                    int fieldRemark = record.indexOf("Remark");
                    while(query.next())
                    {
                        m_xmlitem_2 = m_xmldoc.createElement("E");
                        m_xmlitem_2.setAttribute("ID", query.value(fieldId).toInt());
                        m_xmlitem_2.setAttribute("EventType", query.value(fieldType).toString());
                        m_xmlitem_2.setAttribute("Time", query.value(fieldTime).toString());
                        m_xmlitem_2.setAttribute("CanPort", query.value(fieldCanPort).toInt());
                        m_xmlitem_2.setAttribute("CanDeviceAddress", query.value(fieldCanDeviceAddress).toInt());
                        m_xmlitem_2.setAttribute("Loop", query.value(fieldLoop).toInt());
                        m_xmlitem_2.setAttribute("LampDeviceAddress", query.value(fieldLampDeviceAddress).toInt());
                        m_xmlitem_2.setAttribute("Area", query.value(fieldArea).toString());
                        m_xmlitem_2.setAttribute("Location", query.value(fieldLocation).toString());
                        m_xmlitem_2.setAttribute("Remark", query.value(fieldRemark).toString());
                        m_xmlitem_1.appendChild(m_xmlitem_2);
                    }
                    db.close();
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询所有状态
                else if(element.tagName() == "QueryAllState")
                {
//                    CGlobal::instance()->ClientBusiness()->serverAllState();
                    m_queryAllStateFlag = true;
                    CController* controller = CGlobal::instance()->controller();
                    if(!controller)
                        return;
                    //服务端主机状态上传
                    slot_serverHostStateUpload(controller);
                    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
                    {
                        CCanport* canport = controller->canportByAddress(i);
                        if(!canport)
                            continue;
                        QList <CDistribution*> distributions = canport->distributions();
                        for(int j=0; j<distributions.count(); j++)
                        {
                            CDistribution* distribution = distributions.at(j);
                            if(!distribution)
                                continue;
                            //集中电源状态
                            slot_serverCentralizedPowerStateUpload(distribution);
                            for(int l=0; l<8; l++)
                            {
                                CLoop* loop = distribution->loopByAdd(l+1);
                                if(!loop)
                                    continue;
                                QList <CDevice*> devices = loop->devices();
                                for(int m=0; m<devices.count(); m++)
                                {
                                    CDevice* device = devices.at(m);
                                    if(device)
                                    {
                                        //灯具状态
                                        slot_serverLampStateUpload(device);
                                    }
                                }
                            }
                        }
                    }
                    m_queryAllStateFlag = false;
                }
                //查询布局页面
                else if(element.tagName() == "QueryPageInfo")
                {
//                    CGlobal::instance()->ClientBusiness()->serverPageInfo();
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("PageInfo");

                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    CDBSqlite db(fileName);
                    if(!db.open())
                        return;
                    QSqlQuery query = db.query(QString("SELECT ID,BackgroundColor,BackgroundPicture,PageWidth,PageHeight,Remark from LayoutPage"));
                    QSqlRecord record = query.record();
                    int fieldId = record.indexOf("ID");
                    int fieldBackgroundColor = record.indexOf("BackgroundColor");
                    int fieldBackgroundPicture = record.indexOf("BackgroundPicture");
                    int fieldPageWidth = record.indexOf("PageWidth");
                    int fieldPageHeight = record.indexOf("PageHeight");
                    int fieldRemark = record.indexOf("Remark");
                    while(query.next())
                    {
                        m_xmlitem_2 = m_xmldoc.createElement("PI");
                        m_xmlitem_2.setAttribute("ID", query.value(fieldId).toInt());
                        if(query.value(fieldBackgroundPicture).toString() == "")
                            m_xmlitem_2.setAttribute("C", query.value(fieldBackgroundColor).toInt());
                        else
                        {
                            m_xmlitem_2.setAttribute("P", query.value(fieldBackgroundPicture).toString());
                            QString filePath = CGlobal::instance()->workspaces() + "/" + "PageBackgroundFolder/" + query.value(fieldBackgroundPicture).toString();
                            QFile file(filePath);
                            if (!file.open(QIODevice::ReadOnly)) {

                            }
                            QByteArray imageData = file.readAll();
                            m_xmlitem_2.setAttribute("S", imageData.size());
                //            QImage image;
                //            if (image.loadFromData(imageData)) {
                //                int memorySize = image.byteCount();
                //                m_xmlitem_2.setAttribute("S", memorySize);
                //                qDebug() << "Image Memory Size:" << memorySize << "bytes";
                //            }
                //            else
                //                m_xmlitem_2.setAttribute("S", 0);
                            file.close();
                        }

                        m_xmlitem_2.setAttribute("W", query.value(fieldPageWidth).toInt());
                        m_xmlitem_2.setAttribute("H", query.value(fieldPageHeight).toInt());
                        m_xmlitem_2.setAttribute("R", query.value(fieldRemark).toString());
                        m_xmlitem_1.appendChild(m_xmlitem_2);

                    }
                    db.close();
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询背景图片
                else if(element.tagName() == "QueryPicture")
                {
                    QString filePath = CGlobal::instance()->workspaces() + "/" + "PageBackgroundFolder/" + element.attribute("PN");
                    QFile file(filePath);
                    if (!file.open(QIODevice::ReadOnly)) {

                    }
                    QByteArray imageData = file.readAll();
                    imageData.append("E");
                    imageData.append("O");
                    imageData.append("F");
                    replyXmlMsg(imageData);
                }
                //查询灯具坐标
                else if(element.tagName() == "QueryLampCoordinate")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("LampCoordinate");

                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    CDBSqlite db(fileName);
                    if(!db.open())
                        return;
                    QSqlQuery query = db.query(QString("SELECT c.id,c.lampinfoid,c.layoutpageid,c.cx,c.cy,c.width,c.height,c.angle from Coordinate c"));
                    QSqlRecord record = query.record();
                    int fieldKeyId = record.indexOf("id");
                    int fieldLampInfoID = record.indexOf("lampinfoid");
                    int fieldLayoutPageID = record.indexOf("layoutpageid");
                    int fieldCX = record.indexOf("cx");
                    int fieldCY = record.indexOf("cy");
                    int fieldWidth = record.indexOf("width");
                    int fieldHeight = record.indexOf("height");
                    int fieldAngle = record.indexOf("angle");
                    while(query.next())
                    {
                        m_xmlitem_2 = m_xmldoc.createElement("LC");
                        m_xmlitem_2.setAttribute("ID", query.value(fieldKeyId).toInt());
                        m_xmlitem_2.setAttribute("LID", query.value(fieldLampInfoID).toInt());
                        m_xmlitem_2.setAttribute("PID", query.value(fieldLayoutPageID).toInt());
                        m_xmlitem_2.setAttribute("X", query.value(fieldCX).toInt());
                        m_xmlitem_2.setAttribute("Y", query.value(fieldCY).toInt());
                        m_xmlitem_2.setAttribute("W", query.value(fieldWidth).toInt());
                        m_xmlitem_2.setAttribute("H", query.value(fieldHeight).toInt());
                        m_xmlitem_2.setAttribute("A", query.value(fieldAngle).toInt());
                        m_xmlitem_1.appendChild(m_xmlitem_2);

                    }
                    db.close();
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询着火点坐标
                else if(element.tagName() == "QueryFirePointCoordinate")
                {
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("FirePointCoordinate");

                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    CDBSqlite db(fileName);
                    if(!db.open())
                        return;
                    QSqlQuery query = db.query(QString("SELECT f.id,f.firepointid,f.layoutpageid,f.cx,f.cy,f.width,f.height from FirePointCoordinate f"));
                    QSqlRecord record = query.record();
                    int fieldId = record.indexOf("id");
                    int fieldFirePointID = record.indexOf("firepointid");
                    int fieldLayoutPageID = record.indexOf("layoutpageid");
                    int fieldCX = record.indexOf("cx");
                    int fieldCY = record.indexOf("cy");
                    int fieldWidth = record.indexOf("width");
                    int fieldHeight = record.indexOf("height");
                    while(query.next())
                    {
                        m_xmlitem_2 = m_xmldoc.createElement("FPC");
                        m_xmlitem_2.setAttribute("ID", query.value(fieldId).toInt());
                        m_xmlitem_2.setAttribute("FPID", query.value(fieldFirePointID).toInt());
                        m_xmlitem_2.setAttribute("PID", query.value(fieldLayoutPageID).toInt());
                        m_xmlitem_2.setAttribute("X", query.value(fieldCX).toDouble());
                        m_xmlitem_2.setAttribute("Y", query.value(fieldCY).toDouble());
                        m_xmlitem_2.setAttribute("W", query.value(fieldWidth).toDouble());
                        m_xmlitem_2.setAttribute("H", query.value(fieldHeight).toDouble());
                        m_xmlitem_1.appendChild(m_xmlitem_2);
                    }
                    db.close();
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //查询灯具软件信息
                else if(element.tagName() == "QueryLampSoftwareInfo")
                {
                    int ChannelInfoID = 0;
                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
                    db.setDatabaseName(fileName);
                    if(!db.open())
                        return;
                    QSqlQuery querydevice(db);
                    querydevice.prepare(QString("SELECT l.id,l.channelinfoid,l.address from LampInfo l "
                                                             "left join lamptype r on l.lamptypeid=r.id "
                                                             "where l.id=%1").arg(element.attribute("ID").toInt()));
                    if (!querydevice.exec())
                    {
                        return;
                    }
                    QSqlRecord recorddevice = querydevice.record();
                    int fieldChannelInfoID = recorddevice.indexOf("channelinfoid");
                    int fieldLampAddress = recorddevice.indexOf("address");
                    while(querydevice.next())
                    {
                        ChannelInfoID = querydevice.value(fieldChannelInfoID).toInt();
                        xmlObjectStatus->nDeviceID = querydevice.value(fieldLampAddress).toInt();
                    }
                    QSqlQuery query(db);
                    query.prepare(QString("SELECT m.id,m.candeviceinfoid,m.loop,c.canport,c.address from ChannelInfo m "
                                                       "left join CanDeviceInfo c on m.candeviceinfoid=c.id "
                                                       "where m.id=%1"
                                                       ).arg(ChannelInfoID));
                    if (!query.exec())
                    {
                        return;
                    }
                    QSqlRecord record = query.record();
                    int fieldLoopAddress = record.indexOf("loop");
                    int fieldCanportAddress = record.indexOf("canport");
                    int fieldDistributionAddress = record.indexOf("address");
                    while(query.next())
                    {
                        xmlObjectStatus->nLoopID = query.value(fieldLoopAddress).toInt();
                        xmlObjectStatus->nDisID = query.value(fieldDistributionAddress).toInt();
                        xmlObjectStatus->nCanportAdd = query.value(fieldCanportAddress).toInt()+2;
                    }
                    db.close();
                    //读灯具软件版本信息
                    emit exeCommand(NCT_ReadDeviceInfo, xmlObjectStatus);
                    //服务端回复见软件版本信息接收部分
                    m_lampSoftwareID = element.attribute("ID").toInt();
                }
                //查询集中电源软件信息
                else if(element.tagName() == "QueryDeviceSoftwareInfo")
                {
                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
                    db.setDatabaseName(fileName);
                    if(!db.open())
                        return;
                    QSqlQuery query(db);
                    query.prepare(QString("SELECT m.id,m.canport,m.address from CanDeviceInfo m "
                                        "where m.id=%1").arg(element.attribute("ID").toInt()));
                    if (!query.exec())
                    {
                        return;
                    }
                    QSqlRecord record = query.record();
                    int fieldDistributionAddress = record.indexOf("address");
                    int fieldCanportAddress = record.indexOf("canport");
                    while(query.next())
                    {
                        xmlObjectStatus->nDisID = query.value(fieldDistributionAddress).toInt();
                        xmlObjectStatus->nCanportAdd = query.value(fieldCanportAddress).toInt()+2;
                    }
                    db.close();
                    //读集中电源软件版本信息
                    emit exeCommand(NCT_ReadDeviceInfo, xmlObjectStatus);
                    //服务端回复见软件版本信息接收部分
                    m_distributionSoftwareInfoID = element.attribute("ID").toInt();
                }
                //查询集中电源运行参数
                else if(element.tagName() == "QueryDeviceRealtimeData")
                {
                    xmlObjectStatus->nValue = element.attribute("ID").toInt();
                    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                    CDBSqlite db(fileName);
                    if(!db.open())
                        return;
                    int id = element.attribute("ID").toInt();
                    QString str = QString("SELECT ID, CanPort, Address from CanDeviceInfo "
                                          "WHERE ID=%1").arg(id);
                    QSqlQuery query = db.query(str);
                    QSqlRecord record = query.record();
                    int fieldDistributionAddress = record.indexOf("address");
                    int fieldCanport = record.indexOf("canport");
                    while(query.next())
                    {
                        xmlObjectStatus->nDisID = query.value(fieldDistributionAddress).toInt();
                        xmlObjectStatus->nCanportAdd = query.value(fieldCanport).toInt() + 2;
                    }
                    db.close();
                    //读集中电源运行参数
                    emit exeCommand(NCT_PowerInfo, xmlObjectStatus);
                    //服务端回复见运行参数接收部分
                    m_distributionRealtimeDataID = element.attribute("ID").toInt();
                }
                //主机故障应答
                else if(element.tagName() == "HostFaultUploadConfirm")
                {
                    //
                }
                //CAN设备故障应答
                else if(element.tagName() == "CentralizedPowerStateUploadConfirm")
                {
                    //
                }
                //灯具状态应答
                else if(element.tagName() == "LampStateUploadConfirm")
                {
                    //
                }
                //开关量应急应答
                else if(element.tagName() == "EmergencyInputUploadConfirm")
                {
                    //
                }
                //手动应急应答
                else if(element.tagName() == "ManualLaunchUploadConfirm")
                {
                    //
                }
                //着火点报警应答
                else if(element.tagName() == "FirePointWarningUploadConfirm")
                {
                    //
                }
                //灯具指向应答
                else if(element.tagName() == "LampDirectionUploadConfirm")
                {
                    //
                }
                //主机控制命令
                else if(element.tagName() == "HostControl")
                {
                    if(element.attribute("ControlType") == "启动")
                        emit performLaunch(0);
                    else if(element.attribute("ControlType") == "复位")
                        emit performReset();
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("HostControlConfirm");
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //主机控制命令
                else if(element.tagName() == "PerformReset")
                {
                    emit performReset();
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("PerformResetConfirm");
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //主机控制命令
                else if(element.tagName() == "PerformLaunch")
                {
                    int firepointID = element.attribute("FirePointID").toInt();
                    emit performLaunch(firepointID);
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("PerformLaunchConfirm");
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //上传使能开关
                else if(element.tagName() == "SetAutoStateUpload")
                {
                    QString stateUploadFlag = element.attribute("AutoUpload");
                    if(stateUploadFlag == "True" || stateUploadFlag == "true")
                    {
                        m_masterStateUploadFlag = true;
                    }
                    else if(stateUploadFlag == "False" || stateUploadFlag == "false")
                    {
                        m_masterStateUploadFlag = false;
                    }
                    serverXmlInit();
                    m_xmlitem_1 = m_xmldoc.createElement("SetAutoStateUploadConfirm");
                    m_xmlroot.appendChild(m_xmlitem_1);
                    replyXmlMsg(m_xmldoc.toByteArray(4));
                }
                //心跳
                else if(element.tagName() == "HeartbeatUploadConfirm")
                {
                    m_disconnectTimer->stop();
                    m_disconnectTimer->start(30000);
                }
            }
            firstNode = firstNode.nextSibling();
        }
    }
}

void CprocessServer::slot_serverHostStateUpload(CController* controller)
{
    if(!m_isMasterConnected)
        return;
    if(!(m_queryAllStateFlag || m_masterStateUploadFlag))
        return;
    serverXmlInit();
    QString isBatteryOK = "False", isMainPowerOK = "True";
    if(controller->getStatus(OBJS_StandbyPowerOff))
        ;
    else if(controller->getStatus(OBJS_StandbyPowerShort))
        ;
    else if(controller->getStatus(OBJS_StandbyPowerUndervoltage))
        ;
    else
    {
        isBatteryOK = "True";
    }
    if(controller->getStatus(OBJS_MainPowerFault))
        isMainPowerOK = "False";
    m_xmlitem_1 = m_xmldoc.createElement("HostFaultUpload");
    m_xmlitem_1.setAttribute("IsMainPowerOK", isMainPowerOK);
    m_xmlitem_1.setAttribute("IsBackupBatteryOK", isBatteryOK);
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
}

void CprocessServer::slot_serverCentralizedPowerStateUpload(CDistribution* distribution)
{
    if(!m_isMasterConnected)
        return;
    if(!(m_queryAllStateFlag || m_masterStateUploadFlag))
        return;
    CLoop* loop;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("CanDeviceStateUpload");
    m_xmlitem_1.setAttribute("CanDeviceID", CGlobal::instance()->saveKeyId(OBJT_Distribution, distribution->keyId()));
    m_xmlitem_1.setAttribute("IsCommunicationOK", distribution->getStatus(OBJS_DistributionCommunicationFault) ? "False" : "True");
    m_xmlitem_1.setAttribute("IsOutputOverload", distribution->getoverOut() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsOutputCut", distribution->getoutOpen() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsBatteryVoltage1Low", distribution->getbat1Undervoltage() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsBatteryVoltage2Low", distribution->getbat2Undervoltage() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsBatteryVoltage3Low", distribution->getbat3Undervoltage() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsBackupBatteryFault", distribution->getbackupPowerFault() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsChargerFault", distribution->getchargeFault() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsOverDischarge", distribution->getoverDischargeFault() ? "True" : "False");
    m_xmlitem_1.setAttribute("Warning", distribution->getemergencyStatus() ? "True" : "False");
    m_xmlitem_1.setAttribute("Is36VInputFault", distribution->get36vOut() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsMainPowerFault", distribution->getmainPowerFault() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsSystemFault", distribution->getsystemFault() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsManualMode", distribution->getrunMode() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsCharging", distribution->getchargeStatus() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsBattery1OverHeating", distribution->getbatOverheating() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsBattery2OverHeating", distribution->getbatOverheating() ? "True" : "False");
    m_xmlitem_1.setAttribute("IsBattery3OverHeating", distribution->getbatOverheating() ? "True" : "False");

    for(int i=1; i<13; i++)
    {
        loop = distribution->loopByAdd(i);
        if(loop)
        {
            m_xmlitem_1.setAttribute(QString("Loop%1State").arg(i), loop->getLoopCommunicationFault() ? "故障":"正常");
            m_xmlitem_1.setAttribute(QString("Loop%1OutputCut").arg(i), (distribution->getloopOpen() & (0x01<<(i-1))) ? "True" : "False");
        }
        else
        {
            m_xmlitem_1.setAttribute(QString("Loop%1State").arg(i), "正常");
            m_xmlitem_1.setAttribute(QString("Loop%1OutputCut").arg(i), "False");
        }
    }
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
}

void CprocessServer::slot_serverLampStateUpload(CDevice* device)
{
    if(!m_isMasterConnected)
        return;
    if(!(m_queryAllStateFlag || m_masterStateUploadFlag))
        return;
    serverXmlInit();
    QString isCommunicationOK = "True",isLightFault = "False",isWarning = "False";
    if(!device->isDeviceOnline())
        isCommunicationOK = "False";
    if(device->deviceValue(DEVICE_VALUE_LIGHT) == "光源故障")
        isLightFault = "True";
    if(device->deviceValue(DEVICE_VALUE_EMERGENCY) == "应急" || CGlobal::instance()->m_isEmergency)
        isWarning = "True";
    m_xmlitem_1 = m_xmldoc.createElement("LampStateUpload");
    m_xmlitem_1.setAttribute("LampID", CGlobal::instance()->saveKeyId(OBJT_Device,device->keyId()));
    m_xmlitem_1.setAttribute("IsCommunicationOK", isCommunicationOK);
    m_xmlitem_1.setAttribute("IsLightSourceFault", isLightFault);
    m_xmlitem_1.setAttribute("IsWarning", isWarning);
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
}

//服务端上传复位声明
void CprocessServer::slot_serverResetDeclareUpload()
{
    if(!m_isMasterConnected)
        return;
    if(m_masterStateUploadFlag == false)
        return;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("ResetDeclareUpload");
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
}

//服务端上传开关量应急
void CprocessServer::slot_serverEmergencyInputUpload()
{
    if(!m_isMasterConnected)
        return;
    if(m_masterStateUploadFlag == false)
        return;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("EmergencyInputUpload");
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
}

//服务端上传手动应急
void CprocessServer::slot_serverManualLaunchUpload()
{
    if(!m_isMasterConnected)
        return;
    if(m_masterStateUploadFlag == false)
        return;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("ManualLaunchUpload");
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
}

//服务端上传着火点报警
void CprocessServer::slot_serverFirePointWarningUpload(int deviceAddress, int loopAddress, int terminalAddress)
{
    if(!m_isMasterConnected)
        return;
    if(m_masterStateUploadFlag == false)
        return;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("FirePointWarningUpload");
    m_xmlitem_1.setAttribute("DeviceAddress", deviceAddress);
    m_xmlitem_1.setAttribute("LoopAddress", loopAddress);
    m_xmlitem_1.setAttribute("TerminalAddress", terminalAddress);
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
}

//服务端回复集中电源软件信息
void CprocessServer::slot_serverDistributionSoftwareInfo(CDistribution* distribution)
{
    if(!m_isMasterConnected)
        return;
    if(m_distributionSoftwareInfoID == 0)
        return;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("DeviceSoftwareInfo");
    m_xmlitem_1.setAttribute("ID", CGlobal::instance()->saveKeyId(OBJT_Distribution,distribution->keyId()));
    m_xmlitem_1.setAttribute("CPUVersion", distribution->distributionValue(DISTRIBUTION_VALUE_CPUVERSION).toString());
    m_xmlitem_1.setAttribute("POWVersion", distribution->distributionValue(DISTRIBUTION_VALUE_POWVERSION).toString());
    m_xmlitem_1.setAttribute("ABUS1Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS1VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS2Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS2VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS3Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS3VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS4Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS4VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS5Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS5VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS6Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS6VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS7Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS7VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS8Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS8VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS9Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS9VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS10Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS10VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS11Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS11VERSION).toString());
    m_xmlitem_1.setAttribute("ABUS12Version", distribution->distributionValue(DISTRIBUTION_VALUE_ABUS12VERSION).toString());
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
    m_distributionSoftwareInfoID = 0;
}

//服务端回复集中电源运行参数
void CprocessServer::slot_serverDistributionRealtimeData(CDistribution* distribution)
{
    if(!m_isMasterConnected)
        return;
    if(m_distributionRealtimeDataID == 0)
        return;
    CLoop* loop;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("DeviceRealtimeData");
    m_xmlitem_1.setAttribute("ID", CGlobal::instance()->saveKeyId(OBJT_Distribution,distribution->keyId()));
    m_xmlitem_1.setAttribute("MainPowerVoltage", distribution->distributionValue(DISTRIBUTION_VALUE_MAINV).toString());
    m_xmlitem_1.setAttribute("OutputVoltage", distribution->distributionValue(DISTRIBUTION_VALUE_OUTV).toString());
    m_xmlitem_1.setAttribute("OutputCurrent", distribution->distributionValue(DISTRIBUTION_VALUE_OUTA).toString());
    m_xmlitem_1.setAttribute("OutsideVoltage", distribution->distributionValue(DISTRIBUTION_VALUE_EXTERNALV).toString());
    m_xmlitem_1.setAttribute("Battery1Voltage", distribution->distributionValue(DISTRIBUTION_VALUE_BAT1V).toString());
    m_xmlitem_1.setAttribute("Battery2Voltage", distribution->distributionValue(DISTRIBUTION_VALUE_BAT2V).toString());
    m_xmlitem_1.setAttribute("Battery3Voltage", distribution->distributionValue(DISTRIBUTION_VALUE_BAT3V).toString());
    m_xmlitem_1.setAttribute("Battery1Temperature", distribution->distributionValue(DISTRIBUTION_VALUE_BAT1T).toString());
    m_xmlitem_1.setAttribute("Battery2Temperature", distribution->distributionValue(DISTRIBUTION_VALUE_BAT2T).toString());
    m_xmlitem_1.setAttribute("Battery3Temperature", distribution->distributionValue(DISTRIBUTION_VALUE_BAT3T).toString());
    m_xmlitem_1.setAttribute("BatteryTotalVoltage", distribution->distributionValue(DISTRIBUTION_VALUE_BATV).toString());
    for(int i=1; i<13; i++)
    {
        loop = distribution->loopByAdd(i);
        if(loop)
        {
            m_xmlitem_1.setAttribute(QString("Loop%1Voltage").arg(i), loop->loopValue(LOOP_VALUE_V).toString());
            m_xmlitem_1.setAttribute(QString("Loop%1Current").arg(i), loop->loopValue(LOOP_VALUE_A).toString());
        }
        else
        {
            m_xmlitem_1.setAttribute(QString("Loop%1Voltage").arg(i), 0);
            m_xmlitem_1.setAttribute(QString("Loop%1Current").arg(i), 0);
        }
    }
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
    m_distributionRealtimeDataID = 0;
}

//服务端回复灯具软件信息
void CprocessServer::slot_serverLampSoftwareInfo(int ID, int SoftwareNumber, int SoftwareVersion)
{
    if(!m_isMasterConnected)
        return;
    if(m_lampSoftwareID == 0)
        return;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("LampSoftwareInfo");
    m_xmlitem_1.setAttribute("ID", ID);
    m_xmlitem_1.setAttribute("SoftwareNumber", SoftwareNumber);
    m_xmlitem_1.setAttribute("SoftwareVersion", SoftwareVersion);
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
    m_lampSoftwareID = 0;
}

//服务端上传灯具指向
void CprocessServer::slot_serverLampDirectionUpload(int lampID, QString direction)
{
    if(!m_isMasterConnected)
        return;
    if(m_masterStateUploadFlag == false)
        return;
    serverXmlInit();
    m_xmlitem_1 = m_xmldoc.createElement("LampDirectionUpload");
    m_xmlitem_1.setAttribute("LampID", lampID);
    m_xmlitem_1.setAttribute("Direction", direction);
    m_xmlroot.appendChild(m_xmlitem_1);
    replyXmlMsg(m_xmldoc.toByteArray(4));
}

void CprocessServer::replyXmlMsg(QByteArray data)
{
    char lastData = data.at(data.length() - 1);  // 获取最后一个数据
    if (!data.isEmpty() && lastData == '\n') // 判断最后一个数据是否是换行符
    {
        data.chop(1);  // 去掉最后一个数据（字节）
    }
    qint64 datalength = m_tcpSocket->write(data);
    qint64 bytesWaiting = m_tcpSocket->bytesToWrite();
    if (bytesWaiting > 0)
    {
        if(m_tcpSocket->waitForBytesWritten())
        {
            QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                    + QLatin1Char('\n')
                    + QString("SendLength: ")
                    + QString::number(datalength)
                    + QLatin1Char('\n')
                    + QString::fromUtf8(data)
                    + QLatin1Char('\n');
            //发送客户端数据保存到txt文件
            saveDataToTxt("/home/xfss/root/logfile/masterData.txt", content);
        }
        else
        {
            QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                    + QLatin1Char('\n')
                    + QString("Failed SendLength: ")
                    + QString::number(datalength)
                    + QLatin1Char('\n')
                    + QString::fromUtf8(data)
                    + QLatin1Char('\n');
            //发送客户端数据保存到txt文件
            saveDataToTxt("/home/xfss/root/logfile/masterData.txt", content);
        }
    }
}


// 处理客户端断开连接
void CprocessServer::slot_handleDisconnected()
{
    if (m_tcpSocket && m_isMasterConnected) {
        m_isMasterConnected = false;
        m_tcpSocket->deleteLater(); // 删除客户端socket对象
        QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                + QLatin1Char('\n')
                + QString("主从客户端断开连接: %1:%2").arg(m_tcpSocket->peerAddress().toString()).arg(m_tcpSocket->peerPort())
                + QLatin1Char('\n');
        //发送客户端数据保存到txt文件
        CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/masterData.txt", content);
        m_timer->start(1000);
        m_heartTimer->stop();
    }
}

//保存监听数据文本
void CprocessServer::saveDataToTxt(const QString& filePath, const QString& data)
{
    QFile file(filePath);

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << data << '\n' << '\n';
        file.close();
    }
}

void CprocessServer::slot_controlMasterTxtFileSize()
{
    //设置文档大小最大为1M
    qint64 maxSize = 1024*1024;
    QFile file("/home/xfss/root/logfile/masterData.txt");

    if (file.size() > maxSize) {
        // 读取文件内容
        QString content;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            content = stream.readAll();
            file.close();
        } else {
            return;
        }

        // 删除最早的数据
        QStringList lines = content.split("\n", QString::SkipEmptyParts);
        while (file.size() > maxSize && !lines.isEmpty()) {
            lines.removeFirst();
        }

        // 重新写入文件
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream stream(&file);
            QString newData = lines.join("\n\n");
            stream << newData;
            file.close();
        }
    }
}
