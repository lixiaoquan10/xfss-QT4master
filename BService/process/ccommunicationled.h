#ifndef CCOMMUNICATIONLED_H
#define CCOMMUNICATIONLED_H

#include "qextserialport.h"
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QMutex>

//class ledSerialWorker : public QObject {
//    Q_OBJECT

//public:
//    explicit ledSerialWorker(QSerialPort *port = 0);
//    ~ledSerialWorker();

//public slots:
//    void sendData(const QByteArray &data);
//    void readData();


//    void onErrorOccurred(QSerialPort::SerialPortError error);

//signals:
//    void ledDataReceived(const QByteArray &data);  // 数据接收信号
//    void debug(const QByteArray &data);  // 数据接收信号
//private:
//    QSerialPort *m_ledSerialPort;
//    QByteArray m_ledReceiveData;
//    QList<QByteArray> m_ledSendDataList;  // 数据队列
//    QMutex m_mutex; // 互斥锁
//};


class ledSerialSender : public QObject
{
    Q_OBJECT

public:
    explicit ledSerialSender(QextSerialPort *port = 0);
    ~ledSerialSender();
public slots:
    void sendData(const int &ledStatus1, const int &ledStatus2, const int &ledStatus3);
private:
    QextSerialPort *m_ledSerialSender;
    QList<QByteArray> m_ledSendDataList;  // 数据队列
};

class ledSerialReceiver : public QObject
{
    Q_OBJECT

public:
    explicit ledSerialReceiver(QextSerialPort *port = 0);
    ~ledSerialReceiver();
public slots:
    void readData();
signals:
    void dataReceived(const int &type, const QByteArray &data);  // 数据接收信号
private:
    QextSerialPort *m_ledSerialReceiver;
    QByteArray m_ledReceiveData;
};


#endif // CCOMMUNICATIONLED_H
