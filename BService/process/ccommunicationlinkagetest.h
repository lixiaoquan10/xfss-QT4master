#ifndef CCOMMUNICATIONLINKAGETEST_H
#define CCOMMUNICATIONLINKAGETEST_H

#include "qextserialport.h"
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QTimer>

class linkageTestSerialWorker : public QObject {
    Q_OBJECT

public:
    explicit linkageTestSerialWorker(QextSerialPort *port = 0);
    ~linkageTestSerialWorker();

public slots:
    void sendData();
    void readData();

signals:
    void linkageTestDataReceived(const int &type, const QByteArray &data);        // 数据接收信号
    void returnSendData();
private:
    QextSerialPort *m_linkageTestSerialPort;
    QByteArray m_linkageTestReceiveData;
    QList<QByteArray> m_linkageTestSendDataList;  // 数据队列
    QMutex m_mutex; // 互斥锁
    bool m_sendingInProgress; //发送状态标志

};



#endif // CCOMMUNICATIONLINKAGETEST_H
