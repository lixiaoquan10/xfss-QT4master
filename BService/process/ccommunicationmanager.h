#ifndef CCOMMUNICATIONMANAGER_H
#define CCOMMUNICATIONMANAGER_H

#include <QHash>
#include <QTimer>
#include <QObject>
#include "ccommunicationline.h"

class CCommunicationManager : public QObject
{
    Q_OBJECT
public:
    explicit CCommunicationManager(QObject *parent = 0);
    ~CCommunicationManager();
    int getPortFromCommunicationType(int type);
    
    bool createCommunicationLine(const QString &lineName, int type);
    bool removeCommunicationLine(const QString &lineName);

    bool open(const QString &lineName);
    bool isActive(const QString &lineName) const;
    bool close(const QString &lineName);

    bool setTimeOut(const QString &lineName,int timeOut);
    int  getTimeOut(const QString &lineName) const;
    void setDebugOut(bool isDebug);
    void Sleep(int msec);

    void canSendDataClear();
    void canReceiveDataClear();

public slots:
    void doReciveData(const QString &name,const QByteArray& data);

public:
    QHash<QString /*line name*/,CCommunicationLine*> m_hashCommunicationLine;
    bool m_isSerialportNameSeted;
private:
    bool m_isDebug;
    QHash<int,QString> m_commandNameTable;
    QHash<QString,int> m_commandTypeTable;
    QHash<int,int> m_commandWordTypeTable;


    QTimer m_ledReciveTimer;
    QTimer m_linkageReciveTimer;
    QTimer m_testReciveTimer;
    QTimer m_Can1ReciveTimer;
    QTimer m_Can2ReciveTimer;

    QTimer m_ledTimer;
    QTimer m_linkageTimer;
    QTimer m_Can1Timer;
    QTimer m_Can2Timer;

    QByteArray led_reciveData;
    QByteArray CAN1_reciveData;
    QByteArray CAN2_reciveData;

    QTimer* m_timerARTUDIsend;
public:
    QList<QByteArray> ARTUDIlists;
private slots:
//    void handleLedReciveData();
//    void handleLinkageReciveData();
//    void handleTestReciveData();
    void handleCan1ReciveData();
    void handleCan2ReciveData();
    void updataRecentSerialNumber(const QString &name,int nSerialNumber);

signals:
    void sig_ReceivedPacket(int nSerialNumber);
    void sig_ReciveData(const QString &lineName, const int &infoType,
                        const QHash<QString, QVariant> &controlDomain,
                        const QByteArray &data);
};

#endif // CCOMMUNICATIONMANAGER_H
