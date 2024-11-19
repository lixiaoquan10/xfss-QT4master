#ifndef CGLOBAL_H
#define CGLOBAL_H

#include "bservice.h"
#include "struct/cmsgrouteconfig.h"
#include <QHash>
#include <QFile>
#include <QVariant>
#include <QDateTime>
#include <QTextCodec>
#include <QTextStream>
#include <QDebug>

static unsigned aucCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};

static unsigned aucCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

enum DllStatus {DS_TXNone = 0, DS_TXType = 1, DS_TXInitial = 2, DS_TXStart = 3, DS_TXStop = 4};

enum {Confirm = 0x01, Refuse = 0x02, TestCom = 0x03, UploadTest = 0x04,
      SetCardSpeed = 0x05, ReadCardSpeed = 0x06, UploadCardSpeed = 0x07,
      Reset = 0x08, Emergency = 0x09,
      SendCanData = 0x11, ReadCanState = 0x12, UploadCanState = 0x13,
      SetFasConfig = 0x21, ReadFasConfig = 0x22, SendFasFire = 0x23, SetOutputPort = 0x24,
      ReadInputPort = 0x25, UploadInputPort = 0x26, FasStatus = 0x27,
      ReadPowerState = 0x31, UploadPowerState = 0x32, SetPowerStatus = 0x33,
      SetLedStatus = 0x41, UploadKeyInfo = 0x42,
      PrintData = 0x43,  ReadPrintState = 0x44, UploadPrintState = 0x45};
/*调整顺序*/
//enum {LedEmergency = 1, LedMainPower = 2, LedStandbyPower = 3, LedAuto = 4, LedManual = 5, LedFault = 6, LedSystemFault = 7, LedMute = 8, LedRun = 9, LedMonthCheck = 10, LedYearCheck = 11};
enum {LedMainPower = 1, LedStandbyPower = 2, LedSystemFault = 3, LedFault = 4, LedEmergency = 5, LedAuto = 6, LedManual = 7, LedMute = 8};


enum {LedOff = 0, LedOn = 1, LedFlash = 2};
enum PrintType {
    Start = 1,
    Fault = 2,
    Other = 3,
    Error = 4
};

enum {KeyEmergency = 1, KeyAuto = 2, KeyManual = 3, KeySelfCheck = 4, KeyMute = 5, KeyReset = 6 };
enum CommunicationType {CT_NoCard = 0, CT_LinkageCard = 1, CT_LedCard = 2, CT_CanCard1 = 3, CT_CanCard2 = 4, CT_FASCard = 5, CT_TestCard=6};
enum {MainPower = 1, StandbyPower = 2, Charger = 3, BatteryLine = 4, PowerOutput = 5, BatteryLowVoltage = 6, BatteryLowQuantity = 7, BatteryOverDischarge = 8,
      MainPowerR = 129, StandbyPowerR = 130, ChargerR = 131, BatteryLineR = 132, PowerOutputR = 133, BatteryLowVoltageR = 134, BatteryLowQuantityR = 135, BatteryOverDischargeR = 136};

enum ObjectStatus {
    OBJS_None = 0,
    OBJS_Start = 1,
    OBJS_Fault = 2,
    OBJS_Emergency = 3,
    OBJS_Fire = 4,
    OBJS_Online = 5,
    OBJS_LoginDeviceType = 6,
    OBJS_PowerChargerValue = 7,
    OBJS_PowerAutoValue = 8,
    OBJS_AutoEvacuation = 9,
    OBJS_InputPort = 10,
    OBJS_OutputPort = 11,
    OBJS_NewRegister = 12,
//Start:
    OBJS_PathStart = 13,
    OBJS_EvacuationGroupStart = 14,
    OBJS_UpStart = 15,
    OBJS_DownStart = 16,
    OBJS_LeftStart = 17,
    OBJS_RightStart = 18,
    OBJS_LightStart = 19,
//Fault:
    OBJS_SystemFault = 20,
    OBJS_PowerFault = 21,
    OBJS_MainPowerFault = 22,
    OBJS_StandbyPowerFault = 23,
    OBJS_ConcenterPowerFault = 24,
    OBJS_ChargerFault = 25,
    OBJS_PowerOutputFault = 26,
    OBJS_BatteryLineFault = 27,
    OBJS_BatteryLineFault_1 = 28,
    OBJS_BatteryLineFault_2 = 29,
    OBJS_BatteryLineFault_3 = 30,
    OBJS_BatteryLowVoltageFault = 31,
    OBJS_BatteryLowVoltageFault_1 = 32,
    OBJS_BatteryLowVoltageFault_2 = 33,
    OBJS_BatteryLowVoltageFault_3 = 34,
    OBJS_BatteryLowQuantityFault = 35,
    OBJS_BatteryOverDischargeFault = 36,
    OBJS_LoopOutShortFault = 37,
    OBJS_LoopOutOverloadFault = 38,
    OBJS_LoopCommunicationFault = 39,
    OBJS_NetCommunicationFault = 40,
    OBJS_LightCommunicationFault = 41,
    OBJS_LightFault = 42,
    OBJS_CheckFault = 43,
    OBJS_OutLoopFault = 44,
    OBJS_DistributionFault = 45,
    OBJS_DistributionCommunicationFault = 46,
    OBJS_PowerCommunicationFault = 47,
    OBJS_FASCommunicationFault = 48,
    OBJS_BatteryOffFault = 69,
    OBJS_BatteryShortFault = 70,
    OBJS_StandbyPowerOff = 74,
    OBJS_StandbyPowerShort = 75,
    OBJS_StandbyPowerUndervoltage = 76,
//Emergency:
    OBJS_RemoteEmergency = 49,
    OBJS_FireEmergency = 50,
    OBJS_ForceEmergency = 51,
    OBJS_InputEmergency = 52,
    OBJS_ManualEmergency = 60,
    OBJS_DIEmergency = 64,
    OBJS_TestEmergency = 65,
    OBJS_SystemEmergency = 66,
    OBJS_UndervoltageEmergency = 67,
    OBJS_AutoEmergency = 68,
    OBJS_MonthEmergency = 69,
    OBJS_YearEmergency = 70,
    OBJS_SimulateFireEmergency = 77,
    OBJS_UnknownFireEmergency = 78,
//Other:
    OBJS_Mute = 53,
    OBJS_FirstFire = 54,
    OBJS_MainPowerWork = 55,
    OBJS_StandbyPowerWork = 56,
    OBJS_DirectionFlash = 57,
    OBJS_PowerKaiLuFault = 58,
    OBJS_PowerOutShortFault = 59,
    OBJS_RunMode = 61,
    OBJS_BatteryOverheating = 62,
    OBJS_ChargeStatus = 63
};

qint64 getTickCount();

class CLog;
class CAdapterObject;
class CProcessClient;
class CProcessController;
class CProcessDistribution;
class CCommunicationRoute;
class dlgInformationWindow;
class CGlobal
{
private:
    CGlobal();
    ~CGlobal();
public:
    static bool isDebug(){return m_bDebug;}
    static CGlobal* instance();
    static void destroy();
    static bool setDateTime(const QDateTime& t);

    void initParams();
    void SetCallBack(OnDealEvent dlevent){m_dle = dlevent;}
    int DealEvent(int nType, const QByteArray &data);

    void setRouteConfig(const QList<RouteConfig>& routeConfig);
    void write(int nPort, bool bsend, QByteArray byte);
    void closefile();

    void setPanelAddress(const int n) { m_PanelAddress = n; }
    int  panelAddress() const { return m_PanelAddress; }
    QString projectName() const { return m_projectName; }
    void setProjectName(const QString& name) { m_projectName = name; }
    CLog* log() const { return m_log; }
    CAdapterObject* adapterObject() { return m_adapterObject; }
    CProcessClient* processClient() const { return m_processClient; }
    CProcessDistribution* processDistribution() const { return m_processDistribution; }
    CProcessController* processController() const { return m_processController; }
    CCommunicationRoute* communicationRoute() const { return m_communicationRoute; }
    dlgInformationWindow* DlgInformationWindow() const { return m_dlgInforWindow; }
    void setDlgInformationWindow(dlgInformationWindow* InforWindow){ m_dlgInforWindow = InforWindow; }

    QTextCodec* getCodec() { return QTextCodec::codecForName("UTF-8"); }

    QString getUidString(const QByteArray &buff, int n);

    void setRecordPage(const int page) { m_recordPage = page; }
    void setRecordNumber(const int number) { m_recordNumber = number; }

    unsigned short usMBCRC16(const unsigned char *pucFrame, unsigned short usLen)
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

    void manageLogFile(const QString &filePath, qint64 maxSize)
    {
        QFile file(filePath);

        // Check if the file exists and its size
        if (!file.exists() || file.size() <= maxSize) {
            return;  // Nothing to do
        }

        // Create a temporary file
        QFile tempFile(filePath + ".tmp");
        if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return;
        }

        QTextStream tempStream(&tempFile);

        // Open the original file for reading
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);

            // Skip the first line and write the rest to the temporary file
            for(int i=0; i<10; i++)
            {
                stream.readLine();  // Skip the first line
            }
            while (!stream.atEnd()) {
                tempStream << stream.readLine() << '\n';
            }
            file.close();  // Close the original file

            tempFile.close();  // Close the temporary file

            // Replace the original file with the temporary file
            if (!file.remove()) {
                return;
            }
            if (!tempFile.rename(filePath)) {
            }
        } else {
        }
    }

public:
    static QString m_workPath;
    static int m_dllStatus;
    static bool m_bDebug;
    int m_nPowerBeatCount;
    bool m_bPowerFault;
    int m_recordPage;
    int m_recordNumber;
    int m_canport1ID;
    int m_canport2ID;
    bool m_isReceiveLinkageData;

    int m_linkageTestStatus;

    bool m_isSerialportNameSeted;  //灯键和火报串口正确设置标志
private:
    static CGlobal* m_instance;
    QString m_projectName;
    OnDealEvent m_dle;

    int m_PanelAddress;    

    CLog* m_log;    
    QFile m_writefile[6];
    CProcessController* m_processController;
    CProcessDistribution* m_processDistribution;
    CProcessClient* m_processClient;
    CAdapterObject* m_adapterObject;
    CCommunicationRoute* m_communicationRoute;
    dlgInformationWindow* m_dlgInforWindow;
};

#endif // CGLOBAL_H
