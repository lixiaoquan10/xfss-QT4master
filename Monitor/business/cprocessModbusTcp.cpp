#include "cprocessModbusTcp.h"
#include "cprocesssocket.h"
#include "cglobal.h"

#include "dm/ccontroller.h"
#include "dm/ccanport.h"
#include "dm/cdistribution.h"
#include "dm/cloop.h"
#include "dm/cdevice.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QApplication>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QDomDocument>
#include <QXmlStreamReader>

CprocessModbusTcp::CprocessModbusTcp()
{
    m_modbustcpServer = new QTcpServer(this);
    m_timer = new QTimer();
    m_disconnectTimer = new QTimer();
    m_controlTxtTimer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_serverlisten()));
    connect(m_disconnectTimer, SIGNAL(timeout()), this, SLOT(slot_handleDisconnected()));
    connect(m_controlTxtTimer, SIGNAL(timeout()), this, SLOT(slot_controlTxtFileSize()));
    m_timer->start(5000);
    m_controlTxtTimer->start(5000);
}

CprocessModbusTcp::~CprocessModbusTcp()
{
    delete m_modbustcpServer;
    delete m_modbustcpSocket;
    delete m_timer;
    delete m_disconnectTimer;
}

void CprocessModbusTcp::slot_serverlisten()
{
    qDebug() << "CprocessModbusTcp::slot_serverlisten"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(!m_modbustcpServer->listen(QHostAddress::Any, 502))
    {
        qDebug() << "Unable to start the server: " << m_modbustcpServer->errorString() << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
        return;
    }
    connect(m_modbustcpServer, SIGNAL(newConnection()), this, SLOT(slot_handleNewConnection()));
}

// 处理新的连接请求
void CprocessModbusTcp::slot_handleNewConnection()
{
    qDebug() << "CprocessModbusTcp::slot_handleNewConnection"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    m_modbustcpSocket = m_modbustcpServer->nextPendingConnection();  // 接受新连接
    m_timer->stop();
    QString str = QString("modbusTcp连接成功: %1:%2").arg(m_modbustcpSocket->peerAddress().toString()).arg(m_modbustcpSocket->peerPort());
    //发送客户端数据保存到txt文件
    CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", str);
    connect(m_modbustcpSocket, SIGNAL(readyRead()), this, SLOT(slot_readClientData()));  // 监听客户端数据
    connect(m_modbustcpSocket, SIGNAL(disconnected()), this, SLOT(slot_handleDisconnected()));
    connect(m_modbustcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

void CprocessModbusTcp::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << "CprocessModbusTcp::onSocketError"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if (m_modbustcpSocket)
    {
        qDebug() << "modbusTcp error occurred: " << m_modbustcpSocket->errorString();
        qDebug() << "Error code: " << error;
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
        QString dataWithTimestamp;
        dataWithTimestamp = "(modbusTcp error occurred:" + timestamp + ")" + '\n' + m_modbustcpSocket->errorString();
        CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", dataWithTimestamp);
    }
}


// 读取客户端数据
void CprocessModbusTcp::slot_readClientData()
{
    qDebug() << "CprocessModbusTcp::slot_readClientData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if (m_modbustcpSocket)
    {
        QByteArray array = m_modbustcpSocket->readAll();  // 读取收到的数据
        // 处理收到的数据
        qDebug() << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
        qDebug() << array;

        // 将已接收到的数据缓存
        m_receiveBuff.append(array);
        // 处理帧数据
        processReceiveData(m_receiveBuff);
    }
}


void CprocessModbusTcp::processReceiveData(QByteArray array)
{
    qDebug() << "CprocessModbusTcp::processReceiveData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString dataWithTimestamp;
    dataWithTimestamp = "(Receive:" + timestamp + ")" + '\n' + array.toHex();
    //收到客户端数据保存到txt文件
    CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", dataWithTimestamp);
    if(array.count() < 12)
        return;
    if(array.at(0) == char(0) && array.at(1) == char(0) &&
            array.at(2) == char(0) && array.at(3) == char(0) &&
            array.at(4) == char(0))
    {
        m_receiveBuff.remove(0,12);
//        int length = array.at(5);
        char typeNumber = array.at(7);
        char canportAddress = array.at(6)+2;
        if(typeNumber == 0x10)
        {
            if(array.at(8) == 0x00 && array.at(9) == 0x00)
            {
                if(array.at(11) == 0x01)
                {
                    CGlobal::instance()->TopToolBar()->resetSystem();
                }
                else if(array.at(11) == 0x02)
                {
                    CGlobal::instance()->m_isEmergency = true;
                    CMsgNull m_MsgNUll;
                    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_CancelMute, &m_MsgNUll);
                    CGlobal::instance()->DataProcessing()->setSoundIcon(true);
                    if(CGlobal::instance()->m_EmergencyOperation == CGlobal::Start)
                        return;
                    CGlobal::instance()->m_EmergencyOperation = CGlobal::Start;
                    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_EmergencyStart, &m_MsgNUll);
                }
            }
        }
        else if(typeNumber == 0x03)
        {
            int distributionAddress = array.at(8)/8+1;
            int loopAddress = array.at(8)%8;
            int deviceAddress = array.at(9);
            int number = array.at(10)<<8 | array.at(11);
            bool startflag = false;
            int count = 0;
            QByteArray deviceArray;
            for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
            {
                if(count >= number)
                    break;
                CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
                if(!canport)
                    continue;
                for(int j=1; j<=32; j++)
                {
                    if(count >= number)
                        break;
                    QApplication::processEvents();
                    CDistribution* distribution = canport->distributionByAddress(j);
                    if(!distribution)
                        continue;
                    for(int l=1; l<=8; l++)
                    {
                        if(count >= number)
                            break;
                        CLoop* loop = distribution->loopByAdd(l);
                        if(!loop)
                            continue;
                        for(int m=1; m<=255; m++)
                        {
                            QApplication::processEvents();
                            if((i == canportAddress) && (j == distributionAddress) &&
                                    (l == loopAddress) && (m == deviceAddress))
                                startflag = true;
                            if(startflag)
                            {
                                CDevice* device = loop->deviceByAdd(m);
                                if(!device)
                                    continue;
                                char status = 0;
                                char comFault = 0;
                                char lightFault = 0;
                                char batFault = 0;
                                char emergency = 0;
                                if(device->getDeviceCommunicationFault())
                                    comFault = 0x01;
                                if(device->deviceValue(DEVICE_VALUE_LIGHT) == "光源故障")
                                    lightFault = 0x01;
                                if(device->deviceValue(DEVICE_VALUE_BATTERYPOWER).toString() == "电池断线" ||
                                        device->deviceValue(DEVICE_VALUE_BATTERYPOWER).toString() == "电池短路" ||
                                        device->deviceValue(DEVICE_VALUE_BATTERYPOWER).toString() == "电池过放电")
                                    batFault = 0x01;
                                if((distribution->getemergencyStatus() || device->deviceValue(DEVICE_VALUE_EMERGENCY) == "应急"))
                                    emergency = 0x01;
                                status |= comFault;
                                status |= lightFault<<1;
                                status |= batFault<<2;
                                status |= emergency<<3;
                                deviceArray.append(char(0));
                                deviceArray.append(status);
                                count ++;
                                if(count >= number)
                                    break;
                            }

                        }
                    }
                }
            }
            QByteArray data;
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(count*2+3));
            data.append(canportAddress-2);
            data.append(0x03);
            data.append(char(count*2));
            data.append(deviceArray);
            replySendData(data);
        }
        else if(typeNumber == 0x04)
        {
            int distributionAddress = array.at(9);
            int number = array.at(10)<<8 | array.at(11);
            bool startflag = false;
            int count = 0;
            QByteArray distributionArray;
            for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
            {
                if(count >= number)
                    break;
                CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
                if(canport)
                {
                    for(int j=1; j<=32; j++)
                    {
                        QApplication::processEvents();
                        if((i == canportAddress) && (j == distributionAddress))
                            startflag = true;
                        if(startflag)
                        {
                            CDistribution* distribution = canport->distributionByAddress(j);
                            if(distribution)
                            {
                                char status = 0;
                                char comFault = 0;
                                char mainpowerFault = 0;
                                char batpowerFault = 0;
                                char emergency = 0;
                                if((distribution->getStatus(OBJS_DistributionCommunicationFault) == 1) || (!distribution->isDistributionOnline()))
                                    comFault = 0x01;
                                if(distribution->getmainPowerFault())
                                    mainpowerFault = 0x01;
                                if(distribution->getbackupPowerFault())
                                    batpowerFault = 0x01;
                                if(distribution->getemergencyStatus())
                                    emergency = 0x01;
                                status |= comFault;
                                status |= mainpowerFault<<1;
                                status |= batpowerFault<<2;
                                status |= emergency<<3;
                                distributionArray.append(char(0));
                                distributionArray.append(status);
                                count ++;
                                if(count >= number)
                                    break;
                            }
                        }
                    }
                }
            }
            QByteArray data;
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(count*2+3));
            data.append(canportAddress-2);
            data.append(0x04);
            data.append(char(count*2));
            data.append(distributionArray);
            replySendData(data);
        }
    }
}

void CprocessModbusTcp::replySendData(QByteArray data)
{
    qDebug() << "CprocessModbusTcp::replySendData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    qDebug() << data;

    qint64 datalength = m_modbustcpSocket->write(data);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString dataWithTimestamp;
    qint64 bytesWaiting = m_modbustcpSocket->bytesToWrite();
    if (bytesWaiting > 0)
    {
        if(m_modbustcpSocket->waitForBytesWritten())
        {
            dataWithTimestamp = "(Send:" + timestamp +" length:"+ QString::number(datalength) + ")" + '\n' + data.toHex();
            //发送客户端数据保存到txt文件
            CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", dataWithTimestamp);
        }
        else
        {
            dataWithTimestamp = "(Send Failed:" + timestamp +" length:"+ QString::number(datalength) + ")" + '\n' + data.toHex();
            //发送客户端数据保存到txt文件
            CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", dataWithTimestamp);
        }
    }
}


// 处理客户端断开连接
void CprocessModbusTcp::slot_handleDisconnected()
{
    qDebug() << "CprocessModbusTcp::slot_handleDisconnected"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if (m_modbustcpSocket)
    {
        m_modbustcpSocket->deleteLater(); // 删除客户端socket对象
        QString str = QString("modbusTcp断开连接: %1:%2").arg(m_modbustcpSocket->peerAddress().toString()).arg(m_modbustcpSocket->peerPort());
        //发送客户端数据保存到txt文件
        CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", str);
        m_timer->start(1000);
        CGlobal::instance()->TimeInterval()->setComStatus();
    }
}

void CprocessModbusTcp::slot_controlTxtFileSize()
{
    qDebug() << "CprocessModbusTcp::slot_controlTxtFileSize"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    //设置文档大小最大为1M
    CGlobal::instance()->processSocket()->controlTxtFileSize("/home/xfss/root/logfile/modbusTcpData.txt",1024*1024);
}
