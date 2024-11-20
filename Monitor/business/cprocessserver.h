#ifndef CPROCESSSERVER
#define CPROCESSSERVER

#include "cglobal.h"
#include <QObject>
#include <QAbstractSocket>
#include <QProcess>
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>

class QTimer;
class QTcpSocket;
class QTcpServer;
class CprocessServer : public QObject
{
    Q_OBJECT
public:
    explicit CprocessServer(QTcpServer *tcpServer = 0);
    ~CprocessServer();
    void replyXmlMsg(QByteArray data);
    void processReceiveData(QByteArray array);
    void serverXmlInit();
    void saveDataToTxt(const QString& filePath, const QString& data);
public slots:
    void slot_readClientData();
    void slot_handleNewConnection();
    void slot_serverlisten();
    void slot_handleDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void slot_heartBeat();
    void slot_controlMasterTxtFileSize();

    void slot_serverHostStateUpload(CController* controller);
    void slot_serverCentralizedPowerStateUpload(CDistribution* distribution);
    void slot_serverLampStateUpload(CDevice* device);
    void slot_serverResetDeclareUpload();
    void slot_serverEmergencyInputUpload();
    void slot_serverManualLaunchUpload();
    void slot_serverFirePointWarningUpload(int deviceAddress, int loopAddress, int terminalAddress);
    void slot_serverDistributionSoftwareInfo(CDistribution* distribution);
    void slot_serverDistributionRealtimeData(CDistribution* distribution);
    void slot_serverLampSoftwareInfo(int ID, int SoftwareNumber, int SoftwareVersion);
    void slot_serverLampDirectionUpload(int lampID, QString direction);

signals:
    void exeCommand(int commandType, CMsgStructBase *msgData);
    void performLaunch(int firePointID);
    void performReset();

public:
    bool m_isMasterConnected;
    bool m_masterStateUploadFlag;
    bool m_queryAllStateFlag;
private:
    QTcpServer* m_tcpServer;       // TCP服务器对象
    QTcpSocket* m_tcpSocket;       // 客户端连接列表
    QTimer* m_timer;
    QTimer *m_heartTimer;
    QTimer *m_disconnectTimer;

    QByteArray m_receiveBuff;

    QTimer *m_controlMasterTxtTimer;

    QDomDocument m_xmldoc;
    QDomElement m_xmlroot;
    QDomElement m_xmlitem_1;
    QDomElement m_xmlitem_2;
    QDomText m_xmltext;
    QString m_xmlheader;

    int m_lampSoftwareID;
    int m_distributionRealtimeDataID;
    int m_distributionSoftwareInfoID;
};

#endif // CPROCESSSERVER

