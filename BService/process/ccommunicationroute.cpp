#include <QDebug>
#include <QVector>
#include <QTextCodec>
#include <QThread>
#include <QByteArray>
#include "struct/cmsgnull.h"
#include "cprocessbase.h"
#include "cprocesscontroller.h"
#include "ccommunicationroute.h"
#include "ccommunicationmanager.h"
#include "cglobal.h"
#include "cserialport.h"
#include "ccommunicationled.h"
#include "ccommunicationlinkage.h"
#include "qextserialport.h"

CCommunicationRoute::CCommunicationRoute(QObject *parent) :
    QObject(parent), m_communicationManager(NULL)
{
    initCommunicationManager();
//    createCommunication(CT_LedCard);
//    createCommunication(CT_LinkageCard);
//    createCommunication(CT_TestCard);

    // 创建led串口
    m_ledSerialPort = makeSerialPort("/dev/ttyUSB0", (BaudRateType)19200);

    // 创建led发送线程
    m_ledSendThread = new QThread;
    m_ledSerialSender = new ledSerialSender(m_ledSerialPort);
    m_ledSerialSender->moveToThread(m_ledSendThread);
    // 启动led发送线程
    m_ledSendThread->start();
    connect(this, SIGNAL(ledSendDataRequested(int,int,int)), m_ledSerialSender, SLOT(sendData(int,int,int)));

    // 创建led接收线程
    m_ledReceiveThread = new QThread;
    m_ledSerialReceiver = new ledSerialReceiver(m_ledSerialPort);
    m_ledSerialReceiver->moveToThread(m_ledReceiveThread);
    // 启动led接收线程
    m_ledReceiveThread->start();
    connect(m_ledSerialReceiver, SIGNAL(dataReceived(int,QByteArray)), this, SLOT(slot_dataProcessed(int,QByteArray)));

    // 创建linkage串口
    m_linkageSerialPort = makeSerialPort("/dev/ttyUSB1", (BaudRateType)19200);

    // 创建linkage线程
    m_linkageThread = new QThread;
    m_linkageSerial = new linkageSerialWorker(m_linkageSerialPort);
    m_linkageSerial->moveToThread(m_linkageThread);
    // 启动linkage线程
    m_linkageThread->start();
    // 连接linkage数据发送信号
    connect(this, SIGNAL(linkageSendDataRequested(QByteArray)), m_linkageSerial, SLOT(sendData(QByteArray)));
    // 连接linkage数据接收信号
    connect(m_linkageSerial, SIGNAL(linkageDataReceived(int,QByteArray)), this, SLOT(slot_dataProcessed(int,QByteArray)));
    // 连接交换灯键和火报串口信号
    connect(m_linkageSerial, SIGNAL(switchLedAndLinkageSerial(QByteArray)), this, SLOT(slot_switchLedAndLinkageSerial(QByteArray)));
    // 连接linkage状态信号
    connect(m_linkageSerial, SIGNAL(linkageStatus()), this, SLOT(slot_linkageStatus()));

    // 创建linkageTest串口
    m_linkageTestSerialPort = makeSerialPort("/dev/ttyUSB2", (BaudRateType)19200);

    // 创建linkageTest线程
    m_linkageTestThread = new QThread;
    m_linkageTestSerial = new linkageTestSerialWorker(m_linkageTestSerialPort);
    m_linkageTestSerial->moveToThread(m_linkageTestThread);
    // 启动linkageTest线程
    m_linkageTestThread->start();
    // 连接linkageTest数据发送信号
    connect(this, SIGNAL(linkageTestSendDataRequested()), m_linkageTestSerial, SLOT(sendData()));
    // 连接linkageTest数据接收信号
    connect(m_linkageTestSerial, SIGNAL(linkageTestDataReceived(int,QByteArray)), this, SLOT(slot_dataProcessed(int,QByteArray)));
    // 连接linkageTest返回发送数据信号
    connect(m_linkageTestSerial, SIGNAL(returnSendData()), this, SLOT(slot_linkageTestReturnSendData()));
}

CCommunicationRoute::~CCommunicationRoute()
{
    delete m_communicationManager;
    delete m_ledSerialPort;
    delete m_ledSerialSender;
    delete m_ledSerialReceiver;
    delete m_linkageSerialPort;
    delete m_linkageSerial;
    delete m_linkageTestSerialPort;
    delete m_linkageTestSerial;
    // 停止 LED 发送线程
    if (m_ledSendThread) {
        m_ledSendThread->quit();          // 请求线程退出
        m_ledSendThread->wait();          // 等待线程结束
        delete m_ledSendThread;           // 删除线程对象
    }

    // 停止 LED 接收线程
    if (m_ledReceiveThread) {
        m_ledReceiveThread->quit();       // 请求线程退出
        m_ledReceiveThread->wait();       // 等待线程结束
        delete m_ledReceiveThread;        // 删除线程对象
    }

    // 停止 Linkage 线程
    if (m_linkageThread) {
        m_linkageThread->quit();          // 请求线程退出
        m_linkageThread->wait();          // 等待线程结束
        delete m_linkageThread;           // 删除线程对象
    }

    // 停止 LinkageTest 线程
    if (m_linkageTestThread) {
        m_linkageTestThread->quit();          // 请求线程退出
        m_linkageTestThread->wait();          // 等待线程结束
        delete m_linkageTestThread;           // 删除线程对象
    }
}

QextSerialPort* CCommunicationRoute::makeSerialPort(QString serialName, long baudrate)
{
    QextSerialPort *SerialPort = new QextSerialPort(QextSerialPort::EventDriven);
    SerialPort->setPortName(serialName);
    SerialPort->setBaudRate((BaudRateType)baudrate);
    SerialPort->setDataBits((DataBitsType)DATA_8);
    SerialPort->setParity((ParityType)PAR_NONE);
    SerialPort->setStopBits((StopBitsType)STOP_1);
    return SerialPort;
}

void CCommunicationRoute::slot_dataProcessed(const int &type, const QByteArray &data)
{
    QHash<QString, QVariant> controlDomain;
    controlDomain.insert("communicationType",type);
    CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, data);
}

void CCommunicationRoute::slot_linkageStatus()
{
    CMsgNull msgNull;
    QByteArray byte = msgNull.data(NCT_LinkageComStatus);
    CGlobal::instance()->DealEvent(NCT_LinkageComStatus, byte);
}

void CCommunicationRoute::initCommunicationManager()
{
    if(!m_communicationManager)
        m_communicationManager = new CCommunicationManager();
    connect(m_communicationManager, SIGNAL(sig_ReciveData(QString,int,QHash<QString,QVariant>,QByteArray)), this, SLOT(procCommunicationRecvEvent(QString,int,QHash<QString,QVariant>,QByteArray)));}

bool CCommunicationRoute::createRoute(CProcessBase *process, const int type, const QHash<QString, QVariant> &control)
{
    QString processName = process->name();
    QString communication = createCommunication(type);
    if(communication.isEmpty())
        return false;
    if(isCommunicationLine(type))
    {
        int port = control.value(INTERFACEBOARD_PORT_NUMBER_STR, QVariant(0)).toInt();
        if(!process->addCardPort(port))
            return false;
        m_communicationManager->setTimeOut(communication, INTERFACEBOARD_TIMEOUT);
        int speed = control.value(INTERFACEBOARD_PORT_SPEED_STR, QVariant(0)).toInt();
        m_interfaceBoardPortSpeed.insert(port, speed);
        if(type == CT_FASCard){
            m_interfaceInfo.insert(INTERFACEBOARD_COMMPNYCODE, control.value(INTERFACEBOARD_COMMPNYCODE, QVariant(0)).toInt());
            m_interfaceInfo.insert(INTERFACEBOARD_PANEL, control.value(INTERFACEBOARD_PANEL, QVariant(0)).toInt());
        }
    }
    if(!m_process.contains(processName)){
        m_process.insert(processName, process);
        m_processCommunication.insert(processName, communication);
        connect(this, SIGNAL(processRecvEvent(QString,int,QHash<QString,QVariant>,QByteArray)), process, SLOT(recvEvent(QString,int,QHash<QString,QVariant>,QByteArray)));
    } else{
        if(!m_processCommunication.values(processName).contains(communication))
            m_processCommunication.insertMulti(processName, communication);
    }
    return true;
}

////create communication line
QString CCommunicationRoute::createCommunication(const int type)
{
    QString communicationName;
    communicationName = getCommunicationName(type);
    if(!communicationName.isEmpty() && m_communicationManager)
    {
        if(!m_communication.contains(communicationName))
        {
            if(!m_communicationManager->createCommunicationLine(communicationName, type))
                return QString();
            m_communication.append(communicationName);
        }
    }
    return communicationName;
}

void CCommunicationRoute::openCommunication()
{
    if(CGlobal::isDebug()) qDebug() << "CCommunicationRoute::openCommunication()" << m_communication.size();
    for(int i = 0; i < m_communication.size(); ++i) /*灯 电源 can1 can2*/
    {
        m_communicationManager->open(m_communication.at(i));
    }
}

void CCommunicationRoute::closeCommunication()
{
    for(int i = 0; i < m_communication.size(); ++i)
    {
        m_communicationManager->close(m_communication.at(i));
    }
}

void CCommunicationRoute::setDebug(const bool enable)
{
    m_communicationManager->setDebugOut(enable);
}

void CCommunicationRoute::canSendDataClear()
{
    m_communicationManager->canSendDataClear();
}

void CCommunicationRoute::canReceiveDataClear()
{
    m_communicationManager->canReceiveDataClear();
}

void CCommunicationRoute::setLedStatus(const int ledStatus1, const int ledStatus2, const int ledStatus3)
{
    emit ledSendDataRequested(ledStatus1, ledStatus2, ledStatus3);
    if(!CGlobal::instance()->m_isSerialportNameSeted)
    {
        char sum = 0;
        QByteArray byteArray;
        byteArray.append(char(0x55));
        byteArray.append(char(0x13));
        byteArray.append(char(ledStatus1));
        byteArray.append(char(0));
        byteArray.append(char(0));
        byteArray.append(char(0));
        byteArray.append(char(ledStatus2));
        byteArray.append(char(ledStatus3));
        byteArray.append(char(0));
        byteArray.append(char(0));
        byteArray.append(char(0));
        for (int ix = 0; ix < byteArray.size(); ix++)
            sum += byteArray.at(ix);
        byteArray.append(sum);
        emit linkageSendDataRequested(byteArray);
    }
}

void CCommunicationRoute::testLinkageCom()
{
    //测试USB火报通讯口发送（中间层火报接口接收）
    QTimer::singleShot(5000, this, SLOT(slot_stopTestLinkageCom()));

    if(!m_linkageTestSerialPort->isOpen())
    {
        for(int i=3;i<5;i++)
        {
            disconnect(m_linkageTestSerialPort, SIGNAL(readyRead()), m_linkageTestSerial, SLOT(readData()));
            // 如果串口已打开，则先关闭
            if (m_linkageTestSerialPort->isOpen()) {
                m_linkageTestSerialPort->close();
            }
            m_linkageTestSerialPort->setBaudRate(m_linkageTestSerialPort->baudRate());
            m_linkageTestSerialPort->setPortName("/dev/ttyUSB"+ QString::number(i));
            if(m_linkageTestSerialPort->open(QIODevice::ReadWrite))
            {
                connect(m_linkageTestSerialPort, SIGNAL(readyRead()), m_linkageTestSerial, SLOT(readData()));
            }
        }
    }
    char sum = 0;
    QByteArray byteArray;
    byteArray.append(char(0x55));
    byteArray.append(char(0x13));
    byteArray.append(char(0xFF));
    byteArray.append(char(0xFF));
    byteArray.append(char(0xFF));
    for (int ix = 0; ix < byteArray.size(); ix++)
        sum += byteArray.at(ix);
    byteArray.append(sum);
    emit linkageSendDataRequested(byteArray);
}

void CCommunicationRoute::slot_linkageTestReturnSendData()
{
    emit linkageTestSendDataRequested();
}

void CCommunicationRoute::slot_stopTestLinkageCom()
{
    CGlobal::instance()->m_linkageTestStatus = 0;
}

void CCommunicationRoute::linkageSendData(QByteArray data)
{
    QByteArray byteArray;
    byteArray.append(data);
    // 计算 CRC 值
    // 获取指向数据的指针和长度
    const unsigned char *dataPtr = reinterpret_cast<const unsigned char *>(data.constData());
    unsigned short length = static_cast<unsigned short>(data.size());
    // 调用 CRC 函数
    unsigned short crc = CGlobal::instance()->usMBCRC16(dataPtr, length);
    byteArray.append(static_cast<char>(crc & 0xFF));        // 低字节
    byteArray.append(static_cast<char>((crc >> 8) & 0xFF)); // 高字节
    emit linkageSendDataRequested(byteArray);

    QString  str = "FasSendData:  " + byteArray.toHex() + "   " + QString::number(m_linkageSerialPort->baudRate()) + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    QFile file("/home/xfss/root/logfile/FasSendData.txt");

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << str << '\n' << '\n';
        file.close();
    }
    QString filePath = "/home/xfss/root/logfile/FasSendData.txt";
    CGlobal::instance()->manageLogFile(filePath, 1024 * 1024);
}

//设置火报通讯波特率
void CCommunicationRoute::setLinkageBaudRate(QString baudrateString)
{
    //停止发送数据
    CGlobal::instance()->processController()->stopLinkageCom();
    m_linkageBaudrate = baudrateString.toLong(); // 将QString转换为整数
    //延时修改火报通讯波特率
    QTimer::singleShot(1000, this, SLOT(slot_ChangeLinkageSerialPort()));
}
//开始修改火报通讯波特率
void CCommunicationRoute::slot_ChangeLinkageSerialPort()
{
    disconnect(m_linkageSerialPort, SIGNAL(readyRead()), m_linkageSerial, SLOT(readData()));

    // 如果串口已打开，则先关闭
    if (m_linkageSerialPort->isOpen()) {
        m_linkageSerialPort->close();
    }
    m_linkageSerialPort->setBaudRate((BaudRateType)m_linkageBaudrate);
    m_linkageSerialPort->setPortName(m_linkageSerialPort->portName());
    if(m_linkageSerialPort->open(QIODevice::ReadWrite))
    {
        connect(m_linkageSerialPort, SIGNAL(readyRead()), m_linkageSerial, SLOT(readData()));
    }
    //同步修改测试端口波特率
    disconnect(m_linkageTestSerialPort, SIGNAL(readyRead()), m_linkageTestSerial, SLOT(readData()));

    // 如果串口已打开，则先关闭
    if (m_linkageTestSerialPort->isOpen()) {
        m_linkageTestSerialPort->close();
    }
    m_linkageTestSerialPort->setBaudRate((BaudRateType)m_linkageBaudrate);
    m_linkageTestSerialPort->setPortName(m_linkageTestSerialPort->portName());
    if(m_linkageTestSerialPort->open(QIODevice::ReadWrite))
    {
        connect(m_linkageTestSerialPort, SIGNAL(readyRead()), m_linkageTestSerial, SLOT(readData()));
    }
    CGlobal::instance()->processController()->startLinkageCom();
}

//交换灯键和火报串口
void CCommunicationRoute::slot_switchLedAndLinkageSerial(const QByteArray &data)
{
    disconnect(m_linkageSerialPort, SIGNAL(readyRead()), m_linkageSerial, SLOT(readData()));
    disconnect(m_ledSerialPort, SIGNAL(readyRead()), m_ledSerialReceiver, SLOT(readData()));
    long ledBaudRate = m_ledSerialPort->baudRate();
    long linkageBaudRate = m_linkageSerialPort->baudRate();
    QString ledPortName = m_ledSerialPort->portName();
    QString linkagePortName = m_linkageSerialPort->portName();
    QString  log = "oldledPortName:  " + ledPortName + " "
                    + QString::number(ledBaudRate) + "\n" +
                    "oldlinkagePortName:  " + linkagePortName + " "
                    + QString::number(linkageBaudRate) + "\n" +
                    QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
    // 如果串口已打开，则先关闭
    if (m_linkageSerialPort->isOpen()) {
        m_linkageSerialPort->close();
    }
    // 如果串口已打开，则先关闭
    if (m_ledSerialPort->isOpen()) {
        m_ledSerialPort->close();
    }
    m_linkageSerialPort->setBaudRate((BaudRateType)ledBaudRate);
    m_linkageSerialPort->setPortName(ledPortName);
    m_ledSerialPort->setBaudRate((BaudRateType)linkageBaudRate);
    m_ledSerialPort->setPortName(linkagePortName);
    if(m_linkageSerialPort->open(QIODevice::ReadWrite))
    {
        log = log + "linkage串口重新打开成功" + "\n";
        connect(m_linkageSerialPort, SIGNAL(readyRead()), m_linkageSerial, SLOT(readData()));
    }
    else
    {
        log = log + "linkage串口重新打开失败：" + m_linkageSerialPort->errorString() + "\n";
    }
    if(m_ledSerialPort->open(QIODevice::ReadWrite))
    {
        log = log + "led串口重新打开成功" + "\n";
        connect(m_ledSerialPort, SIGNAL(readyRead()), m_ledSerialReceiver, SLOT(readData()));
    }
    else
    {
        log = log + "led串口重新打开失败：" + m_ledSerialPort->errorString() + "\n";
    }
    log = log + "newledPortName:  " + m_ledSerialPort->portName() + " "
            + QString::number(m_ledSerialPort->baudRate()) + "\n" +
            "newlinkagePortName:  " + m_linkageSerialPort->portName() + " "
            + QString::number(m_linkageSerialPort->baudRate()) + "\n"
            + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
    QFile file("/home/xfss/root/logfile/portName.txt");

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << log << '\n' << '\n';
        file.close();
    }
    CGlobal::instance()->m_isSerialportNameSeted = true;
    //灯键接收数据处理
    slot_dataProcessed(CT_LedCard, data);
}


////get line name from line type
QString CCommunicationRoute::getCommunicationName(const int type)
{
    QString name;
    switch(type)
    {
    case CT_LinkageCard:
        name = "linkagecard";
        break;
    case CT_LedCard:
        name = "ledcard";
        break;
    case CT_CanCard1:
        name = "cancard1";
        break;
    case CT_CanCard2:
        name = "cancard2";
        break;
    case CT_FASCard:
        name = "fascard";
        break;
    case CT_TestCard:
        name = "testcard";
        break;
    default:
        name = "Client";
        break;
    }
    return name;
}

int CCommunicationRoute::getCommunicationType(const QString lineName)
{
    if(lineName.toLower() == "linkagecard") return CT_LinkageCard;
    else if(lineName.toLower() == "ledcard") return CT_LedCard;
    else if(lineName.toLower() == "cancard1") return CT_CanCard1;
    else if(lineName.toLower() == "cancard2") return CT_CanCard2;
    else if(lineName.toLower() == "testcard") return CT_TestCard;
    else if(lineName.toLower() == "fascard") return CT_FASCard;
    else return CT_NoCard;
}

////line type is true line
bool CCommunicationRoute::isCommunicationLine(const int type) const
{
    if(type == CT_CanCard1 || type == CT_CanCard2 || type == CT_LedCard || type == CT_LinkageCard
           || type == CT_TestCard || type == CT_FASCard)
        return true;
    else
        return false;
}

bool CCommunicationRoute::communicationIsActive(const QString &name) const
{
    return m_communicationManager->isActive(name);
}


QString CCommunicationRoute::canNameByAdd(int canportAdd)
{
    if(canportAdd == 3 || canportAdd == 4 || canportAdd == 7 || canportAdd == 8)
        return "cancard1";
    else if(canportAdd == 5 || canportAdd == 6 || canportAdd == 9 || canportAdd == 10)
        return "cancard2";
    return "";
}

int CCommunicationRoute::getIntFromByte(QByteArray data, int start, int len)
{
    if(data.size() < start+len) return 0;
    return (*(unsigned int*)data.mid(start,len).data())&0x0000ffff;;
}

////send data to process
void CCommunicationRoute::procCommunicationRecvEvent(const QString &linename, const int &infoType, const QHash<QString, QVariant> &controlDomain, const QByteArray &data)
{
//    if(CGlobal::isDebug()) qDebug() << "CCommunicationRoute::procCommunicationRecvEvent=====" << linename << infoType << data.toHex();
    if(m_communication.contains(linename))
    {
        QList<QString> processList = m_processCommunication.keys(linename);
        for(int i = 0; i < processList.size(); ++i)
            emit processRecvEvent(processList.at(i), infoType, controlDomain, data);
    }
}
