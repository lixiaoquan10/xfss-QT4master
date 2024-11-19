#include "ccommunicationled.h"
#include "cglobal.h"
#include "ccommunicationroute.h"
#include <QFile>
#include <QDateTime>

//ledSerialWorker::ledSerialWorker(QSerialPort *port) : m_ledSerialPort(port)
//{
//    if(!m_ledSerialPort)
//        return;
//    if(m_ledSerialPort->open(QIODevice::ReadWrite))
//    {
//        connect(m_ledSerialPort, &QSerialPort::readyRead, this, &ledSerialWorker::readData);
//        connect(m_ledSerialPort, &QSerialPort::errorOccurred, this, &ledSerialWorker::onErrorOccurred);
//    }
//}

//ledSerialWorker::~ledSerialWorker()
//{
//    delete m_ledSerialPort;
//    m_ledSendDataList.clear();
//}

//void ledSerialWorker::sendData(const QByteArray &data)
//{
//    QMutexLocker locker(&m_mutex); // 加锁
//    m_ledSendDataList.append(data);  // 将新数据加入队列
//    if (m_ledSendDataList.isEmpty())
//    {
////            qDebug() << "No data to send.";
//        return;
//    }
//    if (m_ledSerialPort->isOpen())
//    {
//        QByteArray sendData = m_ledSendDataList.takeFirst();  // 取出并移除第一条数据
//        qint64 bytesWritten = m_ledSerialPort->write(sendData);
//        if (bytesWritten == -1)
//        {
////                qDebug() << "Failed to write data:" << m_serialPort->errorString();
//        } else
//        {
////                qDebug() << "Data sent, bytes written:" << bytesWritten;
//        }
//    } else {
////            qDebug() << "Serial port is not open.";
//    }
//}

//void ledSerialWorker::readData()
//{
//    QMutexLocker locker(&m_mutex); // 加锁
//    QByteArray data = m_ledSerialPort->readAll();
////        qDebug() << "Data received:" << data;
//    if(data.isEmpty())
//        return;
//    m_ledReceiveData.append(data);

//    while (m_ledReceiveData.size() >= 47)
//    {
//        // 检查开头是否为 0x55 0x13
//        if (m_ledReceiveData.at(0) == 0x55 && m_ledReceiveData.at(1) == 0x13)
//        {

//            QByteArray reciveData = m_ledReceiveData.mid(0, 47);
//            m_ledReceiveData.remove(0, 47); // 从索引 0 开始删除 47 个字节
//            char sum = 0;
//            for (int ix = 0; ix < 46; ix++)
//                sum += reciveData.at(ix);
//            if (reciveData.at(46) != sum) {
//                reciveData.clear();
//                return;
//            }
//            QByteArray tmpByteArray;
//            tmpByteArray.append(reciveData.at(2));
//            tmpByteArray.append(reciveData.at(6));
//            tmpByteArray.append(reciveData.at(7));
//            tmpByteArray.append(reciveData.at(9));
//            tmpByteArray.append(reciveData.at(10));
//            tmpByteArray.append(reciveData.at(14));
//            tmpByteArray.append(reciveData.at(15));
//            tmpByteArray.append(reciveData.at(16));
//            tmpByteArray.append(reciveData.at(17));
//            tmpByteArray.append(reciveData.at(18));
//            tmpByteArray.append(reciveData.at(19));
//            tmpByteArray.append(reciveData.at(20));
//            reciveData.clear();
//            emit ledDataReceived(tmpByteArray);  // 发送接收到的数据
//        } else {
//            // 删除开头无效数据
//            m_ledReceiveData.remove(0, 1); // 删除第一个字节
//        }
//    }
//}

//void ledSerialWorker::onErrorOccurred(QSerialPort::SerialPortError error) {
//    if (error != QSerialPort::NoError) {
////            qDebug() << "Serial port error occurred:" << m_serialPort->errorString();
//    }
//}


ledSerialSender::ledSerialSender(QextSerialPort *port) : m_ledSerialSender(port)
{
    if(!m_ledSerialSender->open(QIODevice::ReadWrite))
    {
        connect(CGlobal::instance()->communicationRoute(), SIGNAL(ledSendDataRequested(int,int,int)), this, SLOT(sendData(int,int,int)));
    }
}

ledSerialSender::~ledSerialSender()
{
    delete m_ledSerialSender;
    m_ledSendDataList.clear();
}

void ledSerialSender::sendData(const int &ledStatus1, const int &ledStatus2, const int &ledStatus3)
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
    m_ledSendDataList.append(byteArray);  // 将新数据加入队列
    if (m_ledSendDataList.isEmpty())
    {
//        qDebug() << "Led no data to send.";
        return;
    }
    if (m_ledSerialSender->isOpen())
    {
        QByteArray sendData = m_ledSendDataList.takeFirst();  // 取出并移除第一条数据
        qint64 bytesWritten = m_ledSerialSender->write(sendData);
        if (bytesWritten != -1)
        {

//            qDebug() << "Data sent, bytes written:" << bytesWritten;
//            QString data = "handleLedSendData:  " + sendData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
//            QFile file("/home/xfss/root/logfile/LedSendData.txt");

//            if (file.open(QIODevice::Append | QIODevice::Text))
//            {
//                QTextStream stream(&file);
//                stream << data << '\n';
//                file.close();
//            }
        } else {
//            qDebug() << "Failed to write data:" << m_ledSerialSender->errorString();
        }
    } else {
        // 重新打开串口
        QString data;
        data = "Led串口打开失败!  " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
        if(!m_ledSerialSender->open(QIODevice::ReadWrite))
        {
            data = data + "Led串口重新打开成功!  " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
            // 连接信号与槽等相关操作
        }  else {
            data = data + "Led串口重新打开失败!  " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
        }
        QFile file("/home/xfss/root/logfile/ledportlog.txt");

        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << data << '\n' << '\n';
            file.close();
        }
    }
}

ledSerialReceiver::ledSerialReceiver(QextSerialPort *port) : m_ledSerialReceiver(port)
{
    connect(m_ledSerialReceiver, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(this, SIGNAL(dataReceived(int,QByteArray)), CGlobal::instance()->communicationRoute(), SLOT(slot_dataProcessed(int,QByteArray)));
}

ledSerialReceiver::~ledSerialReceiver()
{
    delete m_ledSerialReceiver;
}

void ledSerialReceiver::readData()
{
    QByteArray data = m_ledSerialReceiver->readAll();
//    qDebug() << "Led data received:" << data;
    if(data.isEmpty())
        return;
    m_ledReceiveData.append(data);

    while (m_ledReceiveData.size() >= 47)
    {
        // 检查开头是否为 0x55 0x13
        if (m_ledReceiveData.at(0) == 0x55 && m_ledReceiveData.at(1) == 0x13)
        {

            QByteArray reciveData = m_ledReceiveData.mid(0, 47);
            m_ledReceiveData.remove(0, 47); // 从索引 0 开始删除 47 个字节
            char sum = 0;
            for (int ix = 0; ix < 46; ix++)
                sum += reciveData.at(ix);
            if (reciveData.at(46) != sum) {
                reciveData.clear();
                return;
            }
            CGlobal::instance()->m_isSerialportNameSeted = true;
//            QString data = "handleLedReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
//            QFile file("/home/xfss/root/logfile/LedReciveData.txt");

//            if (file.open(QIODevice::Append | QIODevice::Text))
//            {
//                QTextStream stream(&file);
//                stream << data << '\n';
//                file.close();
//            }
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
            tmpByteArray.append(reciveData.at(18));
            tmpByteArray.append(reciveData.at(19));
            tmpByteArray.append(reciveData.at(20));
            reciveData.clear();
            emit dataReceived(CT_LedCard, tmpByteArray);  // 发送接收到的数据
        } else {
            // 删除开头无效数据
            m_ledReceiveData.remove(0, 1); // 删除第一个字节
        }
    }
}
