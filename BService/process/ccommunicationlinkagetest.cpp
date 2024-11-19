#include "ccommunicationlinkagetest.h"
#include "cglobal.h"
#include "cprocesscontroller.h"
#include "struct.h"
#include "struct/cmsgnull.h"

linkageTestSerialWorker::linkageTestSerialWorker(QextSerialPort *port) : m_linkageTestSerialPort(port)
{
    if(!m_linkageTestSerialPort)
        return;
    if(m_linkageTestSerialPort->open(QIODevice::ReadWrite))
    {
        connect(m_linkageTestSerialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    }
}

linkageTestSerialWorker::~linkageTestSerialWorker()
{
    delete m_linkageTestSerialPort;
    m_linkageTestSendDataList.clear();
}

void linkageTestSerialWorker::sendData()
{
    QMutexLocker locker(&m_mutex); // 加锁
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
    m_linkageTestSendDataList.append(byteArray);  // 将新数据加入队列
    if (m_linkageTestSendDataList.isEmpty())
    {
        return;
    }
    if (m_linkageTestSerialPort->isOpen())
    {
        m_sendingInProgress = true;
        QByteArray sendData = m_linkageTestSendDataList.takeFirst();  // 取出并移除第一条数据
        qint64 bytesWritten = m_linkageTestSerialPort->write(sendData);
        m_sendingInProgress = false;
        if (bytesWritten == -1)
        {

        } else {
            QString  data = "FasTestComSendData:  " + byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
            QFile file("/home/xfss/root/logfile/FasTestData.txt");

            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&file);
                stream << data << '\n' << '\n';
                file.close();
            }
        }
    } else {
//            qDebug() << "Serial port is not open.";
    }
}

void linkageTestSerialWorker::readData()
{
    QMutexLocker locker(&m_mutex); // 加锁
    QByteArray bytes;
    int nSize;
    while(m_linkageTestSerialPort->bytesAvailable() > 0)
    {
        nSize = m_linkageTestSerialPort->bytesAvailable();
        bytes.resize(nSize);
        m_linkageTestSerialPort->read(bytes.data(), bytes.size());
    }
    m_linkageTestReceiveData.append(bytes);
    if(m_linkageTestReceiveData.isEmpty())
        return;

    while (m_linkageTestReceiveData.count() >= 6)
    {
        QByteArray reciveData = m_linkageTestReceiveData.mid(0, 6);
        m_linkageTestReceiveData.remove(0, 6); // 从索引 0 开始删除 6 个字节
        if(static_cast<unsigned char>(reciveData.at(2)) == 0xFF &&
           static_cast<unsigned char>(reciveData.at(3)) == 0xFF &&
           static_cast<unsigned char>(reciveData.at(4)) == 0xFF)
        {
            QString dataReceive = "FasTestComReceiveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
            QFile fileReceive("/home/xfss/root/logfile/FasTestData.txt");

            if (fileReceive.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&fileReceive);
                stream << dataReceive << '\n';
                fileReceive.close();
            }
            //火报通讯USB接口发送测试成功
            QByteArray tmpByteArray;
            tmpByteArray.append(char(0x01));
            emit linkageTestDataReceived(CT_TestCard, tmpByteArray);
            //测试USB火报通讯口接收（中间层火报接口发送）
            emit returnSendData();
        }
    }
}


