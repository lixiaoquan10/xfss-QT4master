#include "ccommunicationmanager.h"
#include "packageanalyzer.h"
#include "cserialport.h"
#include "cprocesscontroller.h"
#include "cprocessdistribution.h"
#include "cglobal.h"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QMessageBox>
#define CANDATALEN 15


CCommunicationManager::CCommunicationManager(QObject *parent) :
    QObject(parent),m_isDebug(false)
{
    connect(&m_ledTimer, SIGNAL(timeout()), this, SLOT(handleSendLedData()));
    connect(&m_linkageTimer, SIGNAL(timeout()), this, SLOT(handleSendLinkageData()));

    connect(&m_Can1Timer, SIGNAL(timeout()), this, SLOT(handleSendCan1Data()));
    connect(&m_Can2Timer, SIGNAL(timeout()), this, SLOT(handleSendCan2Data()));

    connect(&m_ledReciveTimer, SIGNAL(timeout()), this, SLOT(handleLedReciveData()));
    connect(&m_linkageReciveTimer, SIGNAL(timeout()), this, SLOT(handleLinkageReciveData()));

    connect(&m_testReciveTimer, SIGNAL(timeout()), this, SLOT(handleTestReciveData()));

    connect(&m_Can1ReciveTimer, SIGNAL(timeout()), this, SLOT(handleCan1ReciveData()));
    connect(&m_Can2ReciveTimer, SIGNAL(timeout()), this, SLOT(handleCan2ReciveData()));

    m_ledReciveTimer.start(30);
    m_linkageReciveTimer.start(30);

    m_testReciveTimer.start(30);

    m_Can1ReciveTimer.start(15);
    m_Can2ReciveTimer.start(15);

    m_ledTimer.start(10);
    m_linkageTimer.start(10);

    m_Can1Timer.start(5);
    m_Can2Timer.start(5);

    led_reciveData = 0;
    CAN1_reciveData = 0;
    CAN2_reciveData = 0;

    isSerialportNameSeted = false;
}

CCommunicationManager::~CCommunicationManager()
{
    foreach(QString lineName,m_hashCommunicationLine.keys()){
        m_hashCommunicationLine[lineName]->destroy();
        m_hashCommunicationLine.remove(lineName);
    }
}

void CCommunicationManager::setLedSendTimer(int msec)
{
    m_ledTimer.start(msec);
}

void CCommunicationManager::setTestLinkageCom(bool enable)
{
    qDebug() << "CCommunicationManager::setTestLinkageCom" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(enable)
        m_testReciveTimer.start(30);
    else
    {
        m_testReciveTimer.stop();
        CGlobal::instance()->m_linkageTestStatus = 0;
    }
}

void CCommunicationManager::setLinkageBaudRate(QString baudrateString)
{
    qDebug() << "CCommunicationManager::setLinkageBaudRate" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QString linename = "linkagecard";
    long baudrate = baudrateString.toLong(); // 将QString转换为整数
    if(!m_hashCommunicationLine.contains(linename)) return;
    CSerialPort* pSerialPort = m_hashCommunicationLine[linename]->pSerialPort;

    if(pSerialPort)
    {
        pSerialPort->serialPort()->close();
        QString portName = pSerialPort->serialPort()->portName();
        pSerialPort->serialPort()->setPortName(portName);
        pSerialPort->serialPort()->setBaudRate((BaudRateType)baudrate);
        QObject::connect(pSerialPort->serialPort(), SIGNAL(readyRead()), pSerialPort->serialPort(), SLOT(doReciveData()));
        if(!pSerialPort->serialPort()->open(QIODevice::ReadWrite))
        {

        }
    }
}

int CCommunicationManager::getPortFromCommunicationType(int type)
{
    qDebug() << "CCommunicationManager::getPortFromCommunicationType" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    switch(type)
    {
        case CT_CanCard1:
            return 1;
        case CT_CanCard2:
            return 0;
        case CT_LedCard:
            return 2;
        case CT_LinkageCard:
            return 3;
        case CT_TestCard:
            return 4;
        case CT_NoCard:
            return 5;
        case CT_FASCard:
            return 6;
        default:
            return 10;
    }
}

bool CCommunicationManager::createCommunicationLine(const QString &lineName, int type)
{
    qDebug() << "CCommunicationManager::createCommunicationLine" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(m_hashCommunicationLine.contains(lineName)){
        return false;
    }
    CSerialPort *pSerialPort ;
    if (lineName == "cancard1" || lineName == "cancard2")
            pSerialPort = new CSerialPort(0, 115200);
    else if (lineName == "ledcard")
        pSerialPort = new CSerialPort(0, 19200);
    else if (lineName == "linkagecard")
        pSerialPort = new CSerialPort(0, 19200);
    else if (lineName == "testcard")
        pSerialPort = new CSerialPort(0, 19200);
    else
        pSerialPort = new CSerialPort();
    pSerialPort->setName(lineName);
    connect(pSerialPort, SIGNAL(sig_ReciveData(const QString&,const QByteArray&)),
            this, SLOT(doReciveData(const QString&,const QByteArray&)));

    connect(this, SIGNAL(sig_ReceivedPacket(int)), pSerialPort, SLOT(handleConfirmationPacket(int)));

    pSerialPort->setDebugOut(m_isDebug);
    CCommunicationLine *communicationLine = new CCommunicationLine();
    communicationLine->pSerialPort = pSerialPort;
    communicationLine->nPort = getPortFromCommunicationType(type);
    m_hashCommunicationLine.insert(lineName,communicationLine);
    return true;
}

void CCommunicationManager::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool CCommunicationManager::removeCommunicationLine(const QString& lineName)
{
    if(m_hashCommunicationLine.contains(lineName)){
        m_hashCommunicationLine[lineName]->destroy();
        m_hashCommunicationLine.remove(lineName);
        return true;
    }else{
        return false;
    }
}

bool CCommunicationManager::open(const QString &lineName)
{
    qDebug() << "CCommunicationManager::open" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(m_hashCommunicationLine.contains(lineName)){
        CCommunicationLine* line = m_hashCommunicationLine[lineName];
        int result = line->pSerialPort->open(line->nPort);
        qDebug() << "CCommunicationManager::open, lineName is " << lineName << ",open result is " << result << ",port is " << line->nPort ;

        if(result == 1){
            return true;
        }else{
            return false;
        }

    }else{
        return false;
    }
}

bool CCommunicationManager::isActive(const QString &lineName) const
{
    if(m_hashCommunicationLine.contains(lineName)){
        return m_hashCommunicationLine[lineName]->pSerialPort->isActive();
    }else{
        return false;
    }
}

bool CCommunicationManager::close(const QString &lineName)
{
    qDebug() << "CCommunicationManager::close" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(m_hashCommunicationLine.contains(lineName)){
        int result = m_hashCommunicationLine[lineName]->pSerialPort->close();
        if(result == 1){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void CCommunicationManager::doReciveData(const QString &lineName,const QByteArray& data)
{
    if(m_hashCommunicationLine.contains(lineName)){
        m_hashCommunicationLine[lineName]->reciveData.append(data);
    }
}

bool CCommunicationManager::setTimeOut(const QString& lineName, int timeOut)
{
    if(m_hashCommunicationLine.contains(lineName)){
        m_hashCommunicationLine[lineName]->pSerialPort->setTimeOut(timeOut);
        return false;
    }else{
        return false;
    }
}

int CCommunicationManager::getTimeOut(const QString& lineName) const
{
    if(m_hashCommunicationLine.contains(lineName)){
        return m_hashCommunicationLine[lineName]->pSerialPort->getTimeOut();
    }else{
        return -1;
    }
}

void CCommunicationManager::setDebugOut(bool isDebug)
{
    m_isDebug=isDebug;
    foreach(CCommunicationLine* lineObj, m_hashCommunicationLine){
        CSerialPort* pSerialPort = lineObj->pSerialPort;
        if(pSerialPort){
            pSerialPort->setDebugOut(m_isDebug);
        }
    }
}

bool CCommunicationManager::sendData(QString lineName, int infoType, const QByteArray &data)
{
    qDebug() << "sendData";
    if(m_hashCommunicationLine.contains(lineName)){
        CSerialPort* pSerialPort = m_hashCommunicationLine[lineName]->pSerialPort;
        if(pSerialPort){
            if(m_hashCommunicationLine[lineName]->sendDataTableAsType.contains(infoType)){
                m_hashCommunicationLine[lineName]->sendDataTableAsType[infoType].append(data);
            }else{
                m_hashCommunicationLine[lineName]->sendDataTableAsType[infoType].clear();
                m_hashCommunicationLine[lineName]->sendDataTableAsType[infoType].append(data);
            }
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

/*
================
slot CCommunicationManager::updataRecentSerialNumber
================
*/
void CCommunicationManager::updataRecentSerialNumber(const QString &name, int nSerialNumber)
{
    if(m_hashCommunicationLine.contains(name)){
        m_hashCommunicationLine[name]->recentRespondSerialNumber = nSerialNumber;
    }
}

bool CCommunicationManager::sendCommandData(const QString &lineName, const int &infotype, const QHash<QString, QVariant> &controlDomain, const QByteArray &data)
{
//    qDebug() << "CCommunicationManager::sendCommandData" << lineName << infotype << data.toHex();
    int canportAdd = controlDomain["canportAdd"].toInt();
//    QString  data1 = "sendCommandData:  " + lineName + "   " + QString::number(canportAdd)  + " " + data.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//    QFile file("/home/xfss/root/sendCommandData.txt");

//    if (file.open(QIODevice::Append | QIODevice::Text))
//    {
//        QTextStream stream(&file);
//        stream << data1 << '\n' << '\n';
//        file.close();
//    }
    if(infotype == SendCanData){
        if(
            controlDomain.contains("recvAddr") && controlDomain.contains("sendAddr")
                && controlDomain.contains("commandType") && controlDomain.contains("dataLen")
                && (controlDomain["dataLen"].toInt()&0x000000ff) == data.size())
        {
            int frameCount=0;
            int multiple=0;
            int remainder=0;
            int len = controlDomain["dataLen"].toInt()&0x000000ff;
            QByteArray tmpByteArray;
            QByteArray headByteArray;
            QList<QByteArray> listsend;
            headByteArray.resize(6);

            headByteArray[0] = (char)(controlDomain["recvAddr"].toInt()&0x000000ff);
            headByteArray[1] = (char)(controlDomain["sendAddr"].toInt()&0x000000ff);
            if (controlDomain.contains("loopAddr"))
                headByteArray[2] = (char)(controlDomain["loopAddr"].toInt()&0x000000ff);      // loop addr
            else
                headByteArray[2] = 0;
            if (controlDomain.contains("deviceAddr"))
                headByteArray[3] = (char)(controlDomain["deviceAddr"].toInt()&0x000000ff);       // terminate addr
            else
                headByteArray[3] = 0;

            if(len>8){
                multiple = len/8;
                remainder = len%8;

                if(remainder == 0){
                    frameCount = multiple;
                }else{
                    frameCount = multiple+1;
                }
                if(frameCount>31){
                    return false;
                }

                for(int i=0, maxCount=frameCount-1; i<maxCount; ++i){
                    tmpByteArray.clear();
                    headByteArray[5]=(char)((i+1)&0x000000ff);
                    headByteArray[6]=(char)(8&0x000000ff);
                    tmpByteArray.append(headByteArray);
                    tmpByteArray.append(data.mid(i*8,8));
                    listsend.append(tmpByteArray);
                }

                if(remainder>0){
                    tmpByteArray.clear();
                    headByteArray[5] = (char)(31&0x000000ff);
                    headByteArray[6] = (char)(remainder&0x000000ff);
                    tmpByteArray.append(headByteArray);
                    tmpByteArray.append(data.mid((frameCount-1)*8,remainder));
                    listsend.append(tmpByteArray);
                }else{
                    tmpByteArray.clear();
                    headByteArray[5]=(char)(31&0x000000ff);
                    headByteArray[6]=(char)(8&0x000000ff);
                    tmpByteArray.append(headByteArray);
                    tmpByteArray.append(data.mid((frameCount-1)*8, 8));
                    listsend.append(tmpByteArray);
                }
            }else{
                frameCount=1;
                tmpByteArray.clear();
                headByteArray[4]=(char)(0&0x000000ff);
                headByteArray[5]=(char)(len&0x000000ff);
                tmpByteArray.append(headByteArray);
                tmpByteArray.append(data.mid(0,len));
                listsend.append(tmpByteArray);
            }
            bool result = true;
            for(int i=0; i<listsend.count(); ++i){
                //canportAdd作为infotype发送
                result = sendData(lineName, canportAdd, listsend.at(i));
                if(!result) return false;
            }
        } else {
            return false;
        }
    } else {
        return sendData(lineName, infotype, data);
    }
    return true;
}

bool CCommunicationManager::sendLedData(const QString &lineName, const int &infotype, const QByteArray &data)
{
    return sendData(lineName, infotype, data);
}

bool CCommunicationManager::sendLinkageData(const QString &lineName, const int &infotype, const QByteArray &data)
{
    return sendData(lineName, infotype, data);
}


void CCommunicationManager::handleSendLedData()
{
    qDebug() << "handleSendLedData";
    QString linename = "ledcard";
    if(!m_hashCommunicationLine.contains(linename))
        return;
    CSerialPort* pSerialPort = m_hashCommunicationLine[linename]->pSerialPort;

    if(pSerialPort){
        foreach (int infoType, m_hashCommunicationLine[linename]->sendDataTableAsType.keys()){

            if (infoType != SetLedStatus)
                continue;

            QList<QByteArray>& sendDataList = m_hashCommunicationLine[linename]->sendDataTableAsType[infoType];
            if(sendDataList.count() > 0){

                QByteArray tmpArray(sendDataList[0]);
                sendDataList.removeAt(0);

                if (tmpArray.size() < 2) /* LED status1, LED status2 */
                    continue;
                char sum = 0;
                QByteArray byteArray;
                byteArray.append(char(0x55));
                byteArray.append(char(0x13));
                byteArray.append(tmpArray.at(0));
                byteArray.append(char(0));
                byteArray.append(char(0));
                byteArray.append(char(0));
                byteArray.append(tmpArray.at(1));
                byteArray.append(tmpArray.at(2));
                byteArray.append(char(0));
                byteArray.append(char(0));
                byteArray.append(char(0));
                for (int ix = 0; ix < byteArray.size(); ix++)
                    sum += byteArray.at(ix);
                byteArray.append(sum);

//                if(CGlobal::isDebug()) qDebug() << "CCommunicationManager::handleSendLEDData():port is " << linename << ",info type is "
//                                                << infoType << byteArray.toHex() << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
                pSerialPort->sendData(byteArray);
//                QString  data = "ledSendData:  " + byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//                QFile file("/home/xfss/root/ledSendData.txt");

//                if (file.open(QIODevice::Append | QIODevice::Text))
//                {
//                    QTextStream stream(&file);
//                    stream << data << '\n' << '\n';
//                    file.close();
//                }
            }
            quint64 tick = ::getTickCount();
            while(::getTickCount() - tick < 1){}

        }
    }
}


void CCommunicationManager::handleSendLinkageData()
{
    qDebug() << "handleSendLinkageData";
    QString linename = "linkagecard";
    if(!m_hashCommunicationLine.contains(linename)) return;
    CSerialPort* pSerialPort = m_hashCommunicationLine[linename]->pSerialPort;

    if(pSerialPort){
        foreach (int infoType, m_hashCommunicationLine[linename]->sendDataTableAsType.keys())
        {
            if(infoType == TestCom)
            {
                //关闭后再打开火报通讯测试串口，若未打开，则修改串口名称再重新打开，范围为ttyUSB2——ttyUSB4
                CSerialPort* pSerialPort_test = m_hashCommunicationLine["testcard"]->pSerialPort;
                if(!pSerialPort_test)
                    return;
                if(!pSerialPort_test->serialPort()->open(QIODevice::ReadWrite))
                {
                    for(int i=2;i<5;i++)
                    {
                        pSerialPort_test->serialPort()->close();
                        pSerialPort_test->serialPort()->setPortName("/dev/ttyUSB"+ QString::number(i));
                        //linkagecard的波特率
                        BaudRateType baudRate = pSerialPort->serialPort()->baudRate();
                        pSerialPort_test->serialPort()->setBaudRate(baudRate);
                        QObject::connect(pSerialPort_test->serialPort(), SIGNAL(readyRead()), pSerialPort_test->serialPort(), SLOT(doReciveData()));
                        if(pSerialPort_test->serialPort()->open(QIODevice::ReadWrite))
                            break;
                    }
                }

                QList<QByteArray>& sendDataList = m_hashCommunicationLine[linename]->sendDataTableAsType[infoType];
                if(sendDataList.count() > 0){

                    QByteArray tmpArray(sendDataList[0]);
                    sendDataList.removeAt(0);

                    if (tmpArray.size() < 2)
                        continue;
                    char sum = 0;
                    QByteArray byteArray;
                    byteArray.append(char(0x55));
                    byteArray.append(char(0x13));
                    byteArray.append(tmpArray.at(0));
                    byteArray.append(tmpArray.at(1));
                    byteArray.append(tmpArray.at(2));
                    for (int ix = 0; ix < byteArray.size(); ix++)
                        sum += byteArray.at(ix);
                    byteArray.append(sum);
                    pSerialPort->sendData(byteArray);

                    QString  data = "linkageSendData:  " + byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
                    QFile file("/home/xfss/root/linkageSendData.txt");

                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream stream(&file);
                        stream << data << '\n' << '\n';
                        file.close();
                    }
                }
                quint64 tick = ::getTickCount();
                while(::getTickCount() - tick < 1){}
            }

            else if(!isSerialportNameSeted && infoType == SetLedStatus)
            {
                QList<QByteArray>& sendDataList = m_hashCommunicationLine[linename]->sendDataTableAsType[infoType];
                if(sendDataList.count() > 0){

                    QByteArray tmpArray(sendDataList[0]);
                    sendDataList.removeAt(0);

                    if (tmpArray.size() < 2)
                        continue;
                    char sum = 0;
                    QByteArray byteArray;
                    byteArray.append(char(0x55));
                    byteArray.append(char(0x13));
                    byteArray.append(tmpArray.at(0));
                    byteArray.append(char(0));
                    byteArray.append(char(0));
                    byteArray.append(char(0));
                    byteArray.append(tmpArray.at(1));
                    byteArray.append(tmpArray.at(2));
                    byteArray.append(char(0));
                    byteArray.append(char(0));
                    byteArray.append(char(0));
                    for (int ix = 0; ix < byteArray.size(); ix++)
                        sum += byteArray.at(ix);
                    byteArray.append(sum);
                    pSerialPort->sendData(byteArray);

                    QString  data = "linkageSendData:  " + byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
                    QFile file("/home/xfss/root/linkageSendData.txt");

                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream stream(&file);
                        stream << data << '\n' << '\n';
                        file.close();
                    }
                }
                quint64 tick = ::getTickCount();
                while(::getTickCount() - tick < 1){}
            }

            else if(infoType == SendFasFire)
            {
                QList<QByteArray>& sendDataList = m_hashCommunicationLine[linename]->sendDataTableAsType[infoType];
                if(sendDataList.count() > 0){

                    QByteArray tmpArray(sendDataList[0]);
                    sendDataList.removeAt(0);

                    if (tmpArray.size() < 6)
                        continue;
                    QByteArray byteArray;
                    byteArray.append(tmpArray);
                    // 计算 CRC 值
                    // 获取指向数据的指针和长度
                    const unsigned char *dataPtr = reinterpret_cast<const unsigned char *>(tmpArray.constData());
                    unsigned short length = static_cast<unsigned short>(tmpArray.size());
                    // 调用 CRC 函数
                    unsigned short crc = usMBCRC16(dataPtr, length);
                    byteArray.append(static_cast<char>(crc & 0xFF));        // 低字节
                    byteArray.append(static_cast<char>((crc >> 8) & 0xFF));// 高字节
                    pSerialPort->sendData(byteArray);

                    QString  data = "linkageSendData:  " + byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
                    QFile file("/home/xfss/root/linkageSendData.txt");

                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream stream(&file);
                        stream << data << '\n' << '\n';
                        file.close();
                    }
                    QString filePath = "/home/xfss/root/linkageSendData.txt";
                    manageLogFile(filePath,4 * 1024 * 1024);
                }
                quint64 tick = ::getTickCount();
                while(::getTickCount() - tick < 1){}
            }

        }
    }
}

void CCommunicationManager::manageLogFile(const QString &filePath, qint64 maxSize)
{
    QFile file(filePath);

    if (file.size() > maxSize)
    {
        QFile tempFile(filePath + ".tmp");
        if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open temporary file for writing.";
            return;
        }

        QTextStream tempStream(&tempFile);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QStringList lines;

            // Read all lines into a list
            while (!stream.atEnd()) {
                lines.append(stream.readLine());
            }
            file.close();

            // Write all lines except the first one to the temp file
            for (int i = 1; i < lines.size(); ++i) {
                tempStream << lines[i] << '\n';
            }

            tempFile.close();

            // Replace the original file with the temp file
            if (!file.remove()) {
                qDebug() << "Failed to remove original file.";
                return;
            }

            if (!tempFile.rename(filePath)) {
                qDebug() << "Failed to rename temporary file.";
            }
        } else {
            qDebug() << "Failed to open file for reading.";
        }
    }
}

unsigned short CCommunicationManager::usMBCRC16(const unsigned char *pucFrame, unsigned short usLen)
{
    uchar ucCRCHi = 0xFF;
    uchar ucCRCLo = 0xFF;
    int iIndex;
    while(usLen--)
    {
        iIndex = ucCRCLo ^ *(pucFrame++);
        ucCRCLo = (uchar)(ucCRCHi ^ aucCRCHi[iIndex]);
        ucCRCHi = aucCRCLo[iIndex];
    }
    return (ushort)(ucCRCHi << 8 | ucCRCLo);
}

void CCommunicationManager::handleSendCan1Data()
{
    qDebug() << "handleSendCan1Data";
    QString linename = "cancard1";
    if(!m_hashCommunicationLine.contains(linename)) return;
    CSerialPort* pSerialPort = m_hashCommunicationLine[linename]->pSerialPort;
    PackageTemplate &packetTemplate = m_hashCommunicationLine[linename]->sendPacketTemplate;
    int nSerialNumber=0;
    if(pSerialPort){
        //infoType代表CAN编号 3/4/7/8
        foreach (int infoType, m_hashCommunicationLine[linename]->sendDataTableAsType.keys()){
            QList<QByteArray>& sendDataList = m_hashCommunicationLine[linename]->sendDataTableAsType[infoType];
            packetTemplate.initializationPackage();
            if(sendDataList.count() > 0){
//                packetTemplate.setInfoType(infoType);
                packetTemplate.setCanId(infoType);

                if(sendDataList[0].size()>0){
                    packetTemplate.appendInfo(sendDataList[0]);
                    sendDataList.removeAt(0);
                }
                if(!infoType)
                {
                    for(int i=0; i<4; i++)
                    {
                        if(i<2)
                            packetTemplate.setCanId(i+3);//CAN1/2地址3 4
                        else
                            packetTemplate.setCanId(i+5);//CAN5/6地址7 8
                        const QByteArray& byteArray = packetTemplate.buildBytes(&nSerialNumber);
//                        qDebug() << "CCommunicationManager::handleSendCan1Data():port is " << nSerialNumber << ",info type is " << infoType << byteArray.toHex();
                        pSerialPort->sendData(byteArray);
                        Sleep(5);
                        QString  data = "cancard1SendData:  " + QString::number(packetTemplate.getCanId()) + " "+
                                byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
                        QFile file("/home/xfss/root/cancard1SendData.txt");

                        if (file.open(QIODevice::Append | QIODevice::Text))
                        {
                            QTextStream stream(&file);
                            stream << data << '\n' << '\n';
                            file.close();
                        }
                    }
                }
                else
                {
                    const QByteArray& byteArray = packetTemplate.buildBytes(&nSerialNumber);
//                    qDebug() << "CCommunicationManager::handleSendCan1Data():port is " << nSerialNumber << ",info type is " << infoType << byteArray.toHex();
                    pSerialPort->sendData(byteArray);

                    QString  data = "cancard1SendData:  " + QString::number(packetTemplate.getCanId()) + " " +
                            byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
                    QFile file("/home/xfss/root/cancard1SendData.txt");

                    if (file.open(QIODevice::Append | QIODevice::Text))
                    {
                        QTextStream stream(&file);
                        stream << data << '\n' << '\n';
                        file.close();
                    }
                }
            }
            quint64 tick = ::getTickCount();
            while(::getTickCount() - tick < 1){}
        }

    }
}
void CCommunicationManager::handleSendCan2Data()
{
    qDebug() << "handleSendCan2Data";
    QString linename = "cancard2";
    if(!m_hashCommunicationLine.contains(linename)) return;
    CSerialPort* pSerialPort = m_hashCommunicationLine[linename]->pSerialPort;
    PackageTemplate &packetTemplate = m_hashCommunicationLine[linename]->sendPacketTemplate;
    int nSerialNumber=0;
    if(pSerialPort){
        //infoType代表CAN编号 5/6/9/10
        foreach (int infoType, m_hashCommunicationLine[linename]->sendDataTableAsType.keys()){
            QList<QByteArray>& sendDataList = m_hashCommunicationLine[linename]->sendDataTableAsType[infoType];
            packetTemplate.initializationPackage();
            if(sendDataList.count() > 0){
//                packetTemplate.setInfoType(infoType);
                packetTemplate.setCanId(infoType);

                if(sendDataList[0].size()>0){
                    packetTemplate.appendInfo(sendDataList[0]);
                    sendDataList.removeAt(0);
                }
                if(!infoType)
                {
                    for(int i=0; i<4; i++)
                    {
                        if(i<2)
                            packetTemplate.setCanId(i+5);//CAN3/4地址5 6
                        else
                            packetTemplate.setCanId(i+7);//CAN7/8地址9 10
                        const QByteArray& byteArray = packetTemplate.buildBytes(&nSerialNumber);
//                        qDebug() << "CCommunicationManager::handleSendCan2Data():port is " << nSerialNumber << ",info type is " << infoType << byteArray.toHex();
                        pSerialPort->sendData(byteArray);
                        Sleep(5);
//                        QString  data = "cancard2SendData:  " + QString::number(packetTemplate.getCanId()) + " " +
//                                byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//                        QFile file("/home/xfss/root/cancard2SendData.txt");

//                        if (file.open(QIODevice::Append | QIODevice::Text))
//                        {
//                            QTextStream stream(&file);
//                            stream << data << '\n' << '\n';
//                            file.close();
//                        }
                    }
                }
                else
                {
                    const QByteArray& byteArray = packetTemplate.buildBytes(&nSerialNumber);
//                    qDebug() << "CCommunicationManager::handleSendCan2Data():port is " << nSerialNumber << ",info type is " << infoType << byteArray.toHex();
                    pSerialPort->sendData(byteArray);
//                    QString  data = "cancard2SendData:  " + QString::number(packetTemplate.getCanId()) + " " +
//                            byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//                    QFile file("/home/xfss/root/cancard2SendData.txt");

//                    if (file.open(QIODevice::Append | QIODevice::Text))
//                    {
//                        QTextStream stream(&file);
//                        stream << data << '\n' << '\n';
//                        file.close();
//                    }
                }
            }
            quint64 tick = ::getTickCount();
            while(::getTickCount() - tick < 1){}
        }
    }
}



/*
================
timer slot CCommunicationManager::handleReciveData
================
*/
void CCommunicationManager::handleLedReciveData()
{
    qDebug() << "handleLedReciveData";
    CSerialPort* pSerialPort = m_hashCommunicationLine["ledcard"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["ledcard"]->reciveData;
    if (reciveData.isEmpty())
        return;
    if(pSerialPort){
        if (reciveData.size() < 47 || reciveData.at(0) != 0x55 || reciveData.at(1) != 0x13) {
            reciveData.clear();
            return;
        }
//        if (led_reciveData.size() < 47) {
//            led_reciveData.append(reciveData);
//            reciveData.clear();
//            return;
//        }
//        led_reciveData.append(reciveData);
//        reciveData.clear();
//        for(int i=0; i<led_reciveData.size(); i++)
//        {
//            if(led_reciveData.at(0) != 0x55 || led_reciveData.at(1) != 0x13)
//              led_reciveData.remove(0,1);
//            else
//              continue;
//        }
//        if(led_reciveData.size() < 47)
//            return;
//        char sum = 0;
//        for (int ix = 0; ix < 46; ix++)
//            sum += led_reciveData.at(ix);
//        if (led_reciveData.at(46) != sum) {
//            led_reciveData.remove(0,47);
//            return;
//        }
        char sum = 0;
        for (int ix = 0; ix < 46; ix++)
            sum += reciveData.at(ix);
        if (reciveData.at(46) != sum) {
            reciveData.clear();
            return;
        }
//        QString data = "handleLedReciveData:  " + led_reciveData.left(47).toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
//        QFile file("/home/xfss/root/LedReciveData.txt");

//        if (file.open(QIODevice::Append | QIODevice::Text))
//        {
//            QTextStream stream(&file);
//            stream << data << '\n';
//            file.close();
//        }
        isSerialportNameSeted = true;
//        if(CGlobal::isDebug()) qDebug() << "led Recive:" << led_reciveData.left(47).toHex() << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
        QByteArray tmpByteArray;
        //        tmpByteArray.append(led_reciveData.at(2));
        //        tmpByteArray.append(led_reciveData.at(6));
        //        tmpByteArray.append(led_reciveData.at(7));
        //        tmpByteArray.append(led_reciveData.at(9));
        //        tmpByteArray.append(led_reciveData.at(10));
        //        tmpByteArray.append(led_reciveData.at(14));
        //        tmpByteArray.append(led_reciveData.at(15));
        //        tmpByteArray.append(led_reciveData.at(16));
        //        tmpByteArray.append(led_reciveData.at(17));
        //        tmpByteArray.append(led_reciveData.at(18));
        //        tmpByteArray.append(led_reciveData.at(19));
        //        tmpByteArray.append(led_reciveData.at(20));
        //        led_reciveData.remove(0,47);
        tmpByteArray.append(reciveData.at(2));
        tmpByteArray.append(reciveData.at(6));
        tmpByteArray.append(reciveData.at(7));
        tmpByteArray.append(reciveData.at(9));
        tmpByteArray.append(reciveData.at(10));
        tmpByteArray.append(reciveData.at(14));
        tmpByteArray.append(reciveData.at(15));
        tmpByteArray.append(reciveData.at(16));
        tmpByteArray.append(reciveData.at(17));
        tmpByteArray.append(reciveData.at(18));
        tmpByteArray.append(reciveData.at(19));
        tmpByteArray.append(reciveData.at(20));
        reciveData.clear();
        QHash<QString, QVariant> controlDomain;
        controlDomain.insert("communicationType",CT_LedCard);
//        if(CGlobal::isDebug()) qDebug() << "ledcardReciveData" << tmpByteArray.toHex() << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
        CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
    }
}

void CCommunicationManager::handleLinkageReciveData()
{
    qDebug() << "handleLinkageReciveData";
    CSerialPort* pSerialPort = m_hashCommunicationLine["linkagecard"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["linkagecard"]->reciveData;
    if (reciveData.isEmpty())
        return;
    if(pSerialPort){
        QString data = "handleLinkageReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
        QFile file("/home/xfss/root/LinkageReciveData.txt");

        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << data << '\n';
            file.close();
        }
        //检测到灯键板通讯
        if(reciveData.count() >= 47 && reciveData.at(0) == 0x55  && reciveData.at(1) == 0x13)
        {
            char sum = 0;
            for (int ix = 0; ix < (47-1); ix++)
            {
               sum += reciveData.at(ix);
            }
            //校验和正确
            if (reciveData.at(46) == sum)
            {
                CSerialPort* pSerialPortLed = m_hashCommunicationLine["ledcard"]->pSerialPort;
                QString  data1 = "oldledPortName:  " + pSerialPortLed->serialPort()->portName() + "\n" +
                                "oldlinkagePortName:  " + pSerialPort->serialPort()->portName() + "\n" +
                                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                //关闭串口
                pSerialPort->serialPort()->close();
                pSerialPortLed->serialPort()->close();
                //交换串口名称
                QString ledPortName = pSerialPortLed->serialPort()->portName();
                BaudRateType ledbaudRate = pSerialPortLed->serialPort()->baudRate();
                QString linkagePortName = pSerialPort->serialPort()->portName();
                BaudRateType linkagebaudRate = pSerialPort->serialPort()->baudRate();
                pSerialPort->serialPort()->setPortName(ledPortName);
                pSerialPort->serialPort()->setBaudRate(linkagebaudRate);
                pSerialPortLed->serialPort()->setPortName(linkagePortName);
                pSerialPortLed->serialPort()->setBaudRate(ledbaudRate);
                QObject::connect(pSerialPort->serialPort(), SIGNAL(readyRead()), pSerialPort->serialPort(), SLOT(doReciveData()));
                QObject::connect(pSerialPortLed->serialPort(), SIGNAL(readyRead()), pSerialPortLed->serialPort(), SLOT(doReciveData()));
                // 重新打开串口
                if (pSerialPort->serialPort()->open(QIODevice::ReadWrite)) {
                    data1 =data1 + "串口重新打开成功" + "\n";
                    // 连接信号与槽等相关操作
                }  else {
                    data1 =data1 + "串口重新打开失败：" + pSerialPort->serialPort()->errorString() + "\n";
                }
                // 重新打开串口
                if (pSerialPortLed->serialPort()->open(QIODevice::ReadWrite)) {
                    data1 =data1 + "串口重新打开成功" + "\n";
                    // 连接信号与槽等相关操作
                }  else {
                    data1 =data1 + "串口重新打开失败：" + pSerialPort->serialPort()->errorString() + "\n";
                }

                data1 =data1 + "newledPortName:  " + pSerialPortLed->serialPort()->portName() + "\n" +
                                "newlinkagePortName:  " + pSerialPort->serialPort()->portName() + "\n" +
                                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                QFile file1("/home/xfss/root/portName.txt");

                if (file1.open(QIODevice::Append | QIODevice::Text))
                {
                    QTextStream stream(&file1);
                    stream << data1 << '\n' << '\n';
                    file1.close();
                }

                isSerialportNameSeted = true;
                QByteArray tmpByteArray;
                tmpByteArray.append(reciveData.at(2));
                tmpByteArray.append(reciveData.at(6));
                tmpByteArray.append(reciveData.at(7));
                tmpByteArray.append(reciveData.at(9));
                tmpByteArray.append(reciveData.at(10));
                tmpByteArray.append(reciveData.at(14));
                tmpByteArray.append(reciveData.at(15));
                tmpByteArray.append(reciveData.at(16));
                tmpByteArray.append(reciveData.at(17));
                reciveData.clear();
                QHash<QString, QVariant> controlDomain;
                controlDomain.insert("communicationType",CT_LedCard);
                CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
            }
            else
            {
                reciveData.clear();
            }
        }
        //火报通讯USB接口测试
        else if(reciveData.count() == 6 && reciveData.at(0) == 0x55  && reciveData.at(1) == 0x13)
        {
            if(static_cast<unsigned char>(reciveData.at(2)) == 0xFF &&
               static_cast<unsigned char>(reciveData.at(3)) == 0xFF &&
               static_cast<unsigned char>(reciveData.at(4)) == 0xFF)
            {
                reciveData.clear();
                //火报通讯USB接口接收测试成功
                QHash<QString, QVariant> controlDomain;
                controlDomain.insert("communicationType",CT_TestCard);
                QByteArray tmpByteArray;
                tmpByteArray.append(char(0x02));
                CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
            }
        }
        //火报通讯
        else
        {
            if(reciveData.count() < 11)
            {
                reciveData.clear();
                return;
            }
            CGlobal::instance()->m_isReceiveLinkageData = true;
            QString filePath = "/home/xfss/root/LinkageReciveData.txt";
            manageLogFile(filePath,4 * 1024 * 1024);

            if(reciveData.at(0) != 0x01 || reciveData.at(1) != 0x03 || reciveData.at(2) != 0x06)
            {
                reciveData.clear();
                return;
            }
            // 提取前 9 个字节
            QByteArray dataToCheck = reciveData.left(9);
            // 提取存储的 CRC 值（最后 2 个字节）
            unsigned short storedCRC = (static_cast<unsigned char>(reciveData.at(10)) << 8) | static_cast<unsigned char>(reciveData.at(9));
            // 计算 CRC
            unsigned short calculatedCRC = usMBCRC16(reinterpret_cast<const unsigned char *>(dataToCheck.constData()), dataToCheck.size());
            if(storedCRC != calculatedCRC)
            {
                reciveData.clear();
                return;
            }
            QHash<QString, QVariant> controlDomain;
            controlDomain.insert("communicationType",CT_LinkageCard);

            QByteArray tmpByteArray;
            tmpByteArray.append(reciveData.at(3));   //设备
            tmpByteArray.append(reciveData.at(4));   //设备
            tmpByteArray.append(reciveData.at(5));   //回路
            tmpByteArray.append(reciveData.at(6));   //回路
            tmpByteArray.append(reciveData.at(7));   //点位
            tmpByteArray.append(reciveData.at(8));   //点位

            CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
            reciveData.clear();
        }
    }
}


void CCommunicationManager::handleTestReciveData()
{
    qDebug() << "handleTestReciveData";
    CSerialPort* pSerialPort = m_hashCommunicationLine["testcard"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["testcard"]->reciveData;
    if (reciveData.isEmpty())
        return;
    if(reciveData.count() < 6)
    {
        reciveData.clear();
        return;
    }
    if(pSerialPort)
    {
        if(static_cast<unsigned char>(reciveData.at(2)) == 0xFF &&
           static_cast<unsigned char>(reciveData.at(3)) == 0xFF &&
           static_cast<unsigned char>(reciveData.at(4)) == 0xFF)
        {
            //火报通讯USB接口发送测试成功
            QHash<QString, QVariant> controlDomain;
            controlDomain.insert("communicationType",CT_TestCard);
            //测试USB火报通讯口接收（中间层火报接口发送）
            QByteArray byteArray;
            int sum = 0;
            byteArray.append(char(0x55));
            byteArray.append(char(0x13));
            byteArray.append(char(0xFF));
            byteArray.append(char(0xFF));
            byteArray.append(char(0xFF));
            for (int ix = 0; ix < byteArray.size(); ix++)
                sum += byteArray.at(ix);
            byteArray.append(sum);
            pSerialPort->sendData(byteArray);
            QString data = "handleTestSendData:  " + byteArray.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
            QFile file("/home/xfss/root/TestSendData.txt");

            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&file);
                stream << data << '\n';
                file.close();
            }
            QByteArray tmpByteArray;
            tmpByteArray.append(char(0x01));
            CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
        }

        QString data = "handleTestReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
        QFile file("/home/xfss/root/TestReciveData.txt");

        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << data << '\n';
            file.close();
        }
        reciveData.clear();
    }
}
/*

*/
void CCommunicationManager::handleCan1ReciveData()
{
    qDebug() << "handleCan1ReciveData";
    CSerialPort* pSerialPort = m_hashCommunicationLine["cancard1"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["cancard1"]->reciveData;

    if (reciveData.isEmpty())
        return;
    if(pSerialPort)
    {
        while (reciveData.size() >= 14)  // 14 最短长度（心跳）
        {
            // 检查是否匹配帧头
            if (reciveData.startsWith(QByteArray::fromHex("55aacc33"))) {
                // 如果匹配帧头，获取数据包长度（假设长度信息在帧头之后）
                int packetLength = 13 + reciveData.at(10);

                // 检查接收到的数据是否包含整个数据包
                if (reciveData.size() >= packetLength) {
                    // 获取整个数据包
                    QByteArray packet = reciveData.left(packetLength);
//                    QString  data = "cancard1ReciveData:  " + packet.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//                    QFile file("/home/xfss/root/receiveCan1data.txt");

//                    if (file.open(QIODevice::Append | QIODevice::Text))
//                    {
//                        QTextStream stream(&file);
//                        stream << data << '\n' << '\n';
//                        file.close();
//                    }

                    // 处理数据包
                    static PackageAnalyzer packAnalyzer;
                    PackageTemplate* pack = packAnalyzer.doAnalysis(packet);

                    // 清除已处理的数据
                    reciveData.remove(0, packetLength);

                    // 继续处理数据包
                    if (pack) {
                        int nInfoType = pack->getInfoType();
                        QByteArray tmpByteArray = pack->getInfo().toByteArray();
                        QHash<QString, QVariant> controlDomain;
                        controlDomain.insert("_portNumber_", pack->getCanId() - 2);
                        controlDomain.insert("recvAddr", pack->getRxAddr());
                        controlDomain.insert("sendAddr", pack->getTxAddr());
                        controlDomain.insert("commandType", pack->getCode());
                        controlDomain.insert("loopAddr", pack->getLoopAddr());
                        controlDomain.insert("deviceAddr", pack->getDeviceAddr());
                        if (nInfoType == 0x61) {
                            QByteArray uid = pack->getSimpleVar();
                            controlDomain.insert("uid", CGlobal::instance()->getUidString(uid, 6));
                        }
                        CGlobal::instance()->processDistribution()->procRecvEvent(nInfoType, controlDomain, tmpByteArray);
                    }
                } else {
                    // 如果接收到的数据不足以构成一个完整的数据包，则退出循环，等待更多数据
                    break;
                }
            } else {
                // 如果没有匹配到帧头，则移除第一个字节，继续查找帧头
                reciveData.remove(0, 1);
            }
        }
    }
}


void CCommunicationManager::handleCan2ReciveData()
{
    qDebug() << "handleCan2ReciveData";
    CSerialPort* pSerialPort = m_hashCommunicationLine["cancard2"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["cancard2"]->reciveData;

    if (reciveData.isEmpty())
        return;

    if(pSerialPort)
    {
        while (reciveData.size() >= 14)  // 14 最短长度（心跳）
        {
            // 检查是否匹配帧头
            if (reciveData.startsWith(QByteArray::fromHex("55aacc33"))) {
                // 如果匹配帧头，获取数据包长度（假设长度信息在帧头之后）
                int packetLength = 13 + reciveData.at(10);

                // 检查接收到的数据是否包含整个数据包
                if (reciveData.size() >= packetLength) {
                    // 获取整个数据包
                    QByteArray packet = reciveData.left(packetLength);
//                    QString  data = "cancard2ReciveData:  " + packet.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//                    QFile file("/home/xfss/root/receiveCan2data.txt");

//                    if (file.open(QIODevice::Append | QIODevice::Text))
//                    {
//                        QTextStream stream(&file);
//                        stream << data << '\n' << '\n';
//                        file.close();
//                    }

                    // 处理数据包
                    static PackageAnalyzer packAnalyzer;
                    PackageTemplate* pack = packAnalyzer.doAnalysis(packet);

                    // 清除已处理的数据
                    reciveData.remove(0, packetLength);

                    // 继续处理数据包
                    if (pack) {
                        int nInfoType = pack->getInfoType();
                        QByteArray tmpByteArray = pack->getInfo().toByteArray();
                        QHash<QString, QVariant> controlDomain;
                        controlDomain.insert("_portNumber_", pack->getCanId() - 2);
                        controlDomain.insert("recvAddr", pack->getRxAddr());
                        controlDomain.insert("sendAddr", pack->getTxAddr());
                        controlDomain.insert("commandType", pack->getCode());
                        controlDomain.insert("loopAddr", pack->getLoopAddr());
                        controlDomain.insert("deviceAddr", pack->getDeviceAddr());
                        if (nInfoType == 0x61) {
                            QByteArray uid = pack->getSimpleVar();
                            controlDomain.insert("uid", CGlobal::instance()->getUidString(uid, 6));
                        }
                        CGlobal::instance()->processDistribution()->procRecvEvent(nInfoType, controlDomain, tmpByteArray);
                    }
                } else {
                    // 如果接收到的数据不足以构成一个完整的数据包，则退出循环，等待更多数据
                    break;
                }
            } else {
                // 如果没有匹配到帧头，则移除第一个字节，继续查找帧头
                reciveData.remove(0, 1);
            }
        }
    }
}

void CCommunicationManager::canSendDataClear()
{
    QString linename = "cancard1";
    if (!m_hashCommunicationLine.contains(linename)) return;

    // 清空 sendDataTableAsType
    m_hashCommunicationLine[linename]->sendDataTableAsType.clear();

    linename = "cancard2";
    if (!m_hashCommunicationLine.contains(linename)) return;

    // 清空 sendDataTableAsType
    m_hashCommunicationLine[linename]->sendDataTableAsType.clear();
}

void CCommunicationManager::canReceiveDataClear()
{
    QString linename = "cancard1";
    if (!m_hashCommunicationLine.contains(linename)) return;

    // 清空 reciveData
    m_hashCommunicationLine[linename]->reciveData.clear();

    linename = "cancard2";
    if (!m_hashCommunicationLine.contains(linename)) return;

    // 清空 reciveData
    m_hashCommunicationLine[linename]->reciveData.clear();
}
