#include "ccommunicationlinkage.h"
#include "cglobal.h"
#include "cprocesscontroller.h"
#include "struct.h"
#include "struct/cmsgnull.h"

linkageSerialWorker::linkageSerialWorker(QextSerialPort *port) : m_linkageSerialPort(port)
{
    if(!m_linkageSerialPort)
        return;
    if(m_linkageSerialPort->open(QIODevice::ReadWrite))
    {
        connect(m_linkageSerialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    }

    //复位火报通讯发送标志位
    m_timerResetLinkageFlag = new QTimer(this);
    connect(m_timerResetLinkageFlag, SIGNAL(timeout()), this, SLOT(slot_LinkageFlagReset()));
    m_timerResetLinkageFlag->start(3000);
    //ARTU模块数据间隔发送
    m_timerARTUDIsend = new QTimer(this);
    connect(m_timerARTUDIsend, SIGNAL(timeout()), this, SLOT(slot_ARTUDIsend()));
}

linkageSerialWorker::~linkageSerialWorker()
{
    delete m_linkageSerialPort;
    m_linkageSendDataList.clear();
    ARTUDIlists.clear();
}

void linkageSerialWorker::sendData(const QByteArray &data)
{
    QMutexLocker locker(&m_mutex); // 加锁
    m_linkageSendDataList.append(data);  // 将新数据加入队列
    if (m_linkageSendDataList.isEmpty())
    {
//            qDebug() << "No data to send.";
        return;
    }
    if (m_linkageSerialPort->isOpen())
    {
        m_sendingInProgress = true;
        QByteArray sendData = m_linkageSendDataList.takeFirst();  // 取出并移除第一条数据
        qint64 bytesWritten = m_linkageSerialPort->write(sendData);
        m_sendingInProgress = false;
        if (bytesWritten == -1)
        {
//                qDebug() << "Failed to write data:" << m_serialPort->errorString();
        } else {
//                qDebug() << "Data sent, bytes written:" << bytesWritten;
            if(bytesWritten == 6)
            {
                QString  data = "FasTestUSBSendData:  " + sendData.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
                QFile file("/home/xfss/root/logfile/FasTestData.txt");

                if (file.open(QIODevice::Append | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    stream << data << '\n' << '\n';
                    file.close();
                }
            }
        }
    } else {
//            qDebug() << "Serial port is not open.";
    }
}

void linkageSerialWorker::readData()
{
    QMutexLocker locker(&m_mutex); // 加锁
    QByteArray bytes;
    int nSize;
    while(m_linkageSerialPort->bytesAvailable() > 0)
    {
        nSize = m_linkageSerialPort->bytesAvailable();
        bytes.resize(nSize);
        m_linkageSerialPort->read(bytes.data(), bytes.size());
    }
//    QString data = "linkageSerialWorkerReadData:  " + bytes.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
//    QFile file("/home/xfss/root/logfile/linkageSerialWorkerReadData.txt");

//    if (file.open(QIODevice::Append | QIODevice::Text))
//    {
//        QTextStream stream(&file);
//        stream << data << '\n';
//        file.close();
//    }
    m_linkageReceiveData.append(bytes);
    if(m_linkageReceiveData.isEmpty())
        return;

    if(CGlobal::instance()->m_isSerialportNameSeted)
    {
        //火报通讯USB接口测试
        if(m_linkageReceiveData.count() == 6 && m_linkageReceiveData.at(0) == 0x55  && m_linkageReceiveData.at(1) == 0x13)
        {
            QByteArray reciveData = m_linkageReceiveData.mid(0, 6);
            m_linkageReceiveData.remove(0, 6); // 从索引 0 开始删除 6 个字节
            if(static_cast<unsigned char>(reciveData.at(2)) == 0xFF &&
               static_cast<unsigned char>(reciveData.at(3)) == 0xFF &&
               static_cast<unsigned char>(reciveData.at(4)) == 0xFF)
            {
                QString data = "FasTestUSBReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                QFile file("/home/xfss/root/logfile/FasTestData.txt");

                if (file.open(QIODevice::Append | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    stream << data << '\n';
                    file.close();
                }
                //火报通讯USB接口接收测试成功
                QByteArray tmpByteArray;
                tmpByteArray.append(char(0x02));
                emit linkageDataReceived(CT_TestCard, tmpByteArray);
            }
        }
       //ARTU通讯
       else if(CGlobal::instance()->processController()->ARTUType())
       {
           QString filePath = "/home/xfss/root/logfile/ARTUReciveData.txt";
           CGlobal::instance()->manageLogFile(filePath, 1024 * 1024);
           int deviceAddress = CGlobal::instance()->processController()->ARTUAddress();
           //079-KJ
           if(CGlobal::instance()->processController()->ARTUType() == 2)
           {
               while (m_linkageReceiveData.count() >= 6)
               {
                   emit linkageStatus();
                   CGlobal::instance()->m_isReceiveLinkageData = true;
                   m_timerResetLinkageFlag->start(3000);
                   if(m_linkageReceiveData.at(0) == deviceAddress && m_linkageReceiveData.at(1) == 0x02)
                   {
                       QByteArray reciveData = m_linkageReceiveData.mid(0, 6);
                       m_linkageReceiveData.remove(0, 6); // 从索引 0 开始删除 6 个字节
                       QString data = "ARTUReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                       QFile file("/home/xfss/root/logfile/ARTUReciveData.txt");

                       if (file.open(QIODevice::Append | QIODevice::Text))
                       {
                           QTextStream stream(&file);
                           stream << data << '\n';
                           file.close();
                       }
                       // 获取数据部分
                       unsigned char value = static_cast<unsigned char>(reciveData.at(3));

                       for (int i = 1; i <= 8; ++i)
                       {
                           if (value & (1 << (i-1)))
                           {
                               QHash<QString, QVariant> controlDomain;
                               controlDomain.insert("communicationType",CT_LinkageCard);
                               QByteArray tmpByteArray;
                               tmpByteArray.append(static_cast<char>((deviceAddress>>8)&0xFF));   //设备
                               tmpByteArray.append(static_cast<char>(deviceAddress&0xFF));   //设备
                               tmpByteArray.append(static_cast<char>(0x00));   //回路
                               tmpByteArray.append(static_cast<char>(0x00));   //回路
                               tmpByteArray.append(static_cast<char>(((i)>>8)&0xFF));   //点位
                               tmpByteArray.append(static_cast<char>(i&0xFF));        //点位
                               ARTUDIlists.append(tmpByteArray);
                               m_timerARTUDIsend->start(100);
                           }
                       }
                   } else {
                       // 删除开头无效数据
                       m_linkageReceiveData.remove(0, 1); // 删除第一个字节
                   }
               }
           }
           //426和079-K
           else if(CGlobal::instance()->processController()->ARTUType() == 1 ||
                   CGlobal::instance()->processController()->ARTUType() == 3)
           {
               while (m_linkageReceiveData.count() >= 9)
               {
                   emit linkageStatus();
                   CGlobal::instance()->m_isReceiveLinkageData = true;
                   m_timerResetLinkageFlag->start(3000);
                   if(m_linkageReceiveData.at(0) == deviceAddress && m_linkageReceiveData.at(1) == 0x02)
                   {
                       QByteArray reciveData = m_linkageReceiveData.mid(0, 9);
                       m_linkageReceiveData.remove(0, 9); // 从索引 0 开始删除 9 个字节
                       QString data = "ARTUReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                       QFile file("/home/xfss/root/logfile/ARTUReciveData.txt");

                       if (file.open(QIODevice::Append | QIODevice::Text))
                       {
                           QTextStream stream(&file);
                           stream << data << '\n';
                           file.close();
                       }
                       // 获取数据部分
                       unsigned int value = static_cast<unsigned int>((static_cast<unsigned char>(reciveData.at(6)) << 24) |
                                                                       (static_cast<unsigned char>(reciveData.at(5)) << 16) |
                                                                       (static_cast<unsigned char>(reciveData.at(4)) << 8) |
                                                                       (static_cast<unsigned char>(reciveData.at(3))));

                       for (int i = 1; i <= 32; ++i)
                       {
                           if (value & (1 << (i-1)))
                           {
                               QHash<QString, QVariant> controlDomain;
                               controlDomain.insert("communicationType",CT_LinkageCard);
                               QByteArray tmpByteArray;
                               tmpByteArray.append(static_cast<char>((deviceAddress>>8)&0xFF));   //设备
                               tmpByteArray.append(static_cast<char>(deviceAddress&0xFF));   //设备
                               tmpByteArray.append(static_cast<char>(0x00));   //回路
                               tmpByteArray.append(static_cast<char>(0x00));   //回路
                               tmpByteArray.append(static_cast<char>(((i)>>8)&0xFF));   //点位
                               tmpByteArray.append(static_cast<char>(i&0xFF));        //点位
                               ARTUDIlists.append(tmpByteArray);
                               m_timerARTUDIsend->start(100);
                           }
                       }
                   } else {
                       // 删除开头无效数据
                       m_linkageReceiveData.remove(0, 1); // 删除第一个字节
                   }
               }
           }
       }
       //火报通讯
       else
       {
           QString filePath = "/home/xfss/root/logfile/FasReciveData.txt";
           CGlobal::instance()->manageLogFile(filePath, 1024 * 1024);
           while (m_linkageReceiveData.count() >= 11)
           {
               emit linkageStatus();
               CGlobal::instance()->m_isReceiveLinkageData = true;
               m_timerResetLinkageFlag->start(3000);
               if(m_linkageReceiveData.at(0) == 0x01 && m_linkageReceiveData.at(1) == 0x03 && m_linkageReceiveData.at(2) == 0x06)
               {
                   QByteArray reciveData = m_linkageReceiveData.mid(0, 11);
                   m_linkageReceiveData.remove(0, 11); // 从索引 0 开始删除 11 个字节
                   QString data = "FasReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                   QFile file("/home/xfss/root/logfile/FasReciveData.txt");

                   if (file.open(QIODevice::Append | QIODevice::Text))
                   {
                       QTextStream stream(&file);
                       stream << data << '\n';
                       file.close();
                   }
                   QByteArray tmpByteArray;
                   tmpByteArray.append(reciveData.at(3));   //设备
                   tmpByteArray.append(reciveData.at(4));   //设备
                   tmpByteArray.append(reciveData.at(5));   //回路
                   tmpByteArray.append(reciveData.at(6));   //回路
                   tmpByteArray.append(reciveData.at(7));   //点位
                   tmpByteArray.append(reciveData.at(8));   //点位

                   emit linkageDataReceived(CT_LinkageCard, tmpByteArray);
               } else {
                   // 删除开头无效数据
                   m_linkageReceiveData.remove(0, 1); // 删除第一个字节
               }
           }
       }
    }

    while (!CGlobal::instance()->m_isSerialportNameSeted && m_linkageReceiveData.size() >= 47)
    {
        //检测到灯键板通讯
        if(m_linkageReceiveData.at(0) == 0x55 && m_linkageReceiveData.at(1) == 0x13)
        {
            char sum = 0;
            for (int ix = 0; ix < (47-1); ix++)
            {
               sum += m_linkageReceiveData.at(ix);
            }
            //校验和正确
            if (m_linkageReceiveData.at(46) == sum)
            {
                QByteArray tmpByteArray;
                tmpByteArray.append(m_linkageReceiveData.at(2));
                tmpByteArray.append(m_linkageReceiveData.at(6));
                tmpByteArray.append(m_linkageReceiveData.at(7));
                tmpByteArray.append(m_linkageReceiveData.at(9));
                tmpByteArray.append(m_linkageReceiveData.at(10));
                tmpByteArray.append(m_linkageReceiveData.at(14));
                tmpByteArray.append(m_linkageReceiveData.at(15));
                tmpByteArray.append(m_linkageReceiveData.at(16));
                tmpByteArray.append(m_linkageReceiveData.at(17));
                emit switchLedAndLinkageSerial(tmpByteArray);
                m_linkageReceiveData.clear();
            } else {
                // 删除开头无效数据
                m_linkageReceiveData.remove(0, 1); // 删除第一个字节
            }
        } else {
            // 删除开头无效数据
            m_linkageReceiveData.remove(0, 1); // 删除第一个字节
        }
    }
}


void linkageSerialWorker::slot_LinkageFlagReset()
{
    if(!CGlobal::instance()->m_isReceiveLinkageData)
        CGlobal::instance()->m_isReceiveLinkageData = true;
}

void linkageSerialWorker::slot_ARTUDIsend()
{
    if(!CGlobal::instance()->m_isReceiveLinkageData)
        return;
    if(ARTUDIlists.isEmpty())
    {
        m_timerARTUDIsend->stop();
        return;
    }
    emit linkageDataReceived(CT_LinkageCard, ARTUDIlists.at(0));
    ARTUDIlists.removeAt(0);
}
