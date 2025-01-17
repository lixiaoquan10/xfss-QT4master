#ifndef STRUCT_H
#define STRUCT_H

#include <QDateTime>

enum NCommandType{
    NCT_None = 0,                       // ?????
    NCT_GetProcessTypeName = 1,         // ????????????
    NCT_SetInterfaceBoardInfo = 2,      // ???????,Dll??Server
    NCT_SetRouteConfig = 3,             // ??????,Server??Dll
    NCT_ObjectStatus = 4,               // ??????
    NCT_AddLog = 5,                     // ????
    NCT_GetLog = 6,                     // ????
    NCT_Reset = 7,                      // ??
    NCT_Mute = 8,                       // ??
    NCT_EmergencyStart = 9,             // ??????
    NCT_EmergencyStop = 10,              // ??????
    NCT_AutomaticEvacuation = 11,        // ??????
    NCT_ManualEvacuation = 12,           // ??????
    NCT_SystemSelfCheck = 13,            // ????
    NCT_SystemMonthCheck = 14,           // ????
    NCT_SystemYearCheck = 15,            // ????
    NCT_Relogin = 16,                    // ????

    NCT_SimulateFire = 18,               // 模拟火警点应急
    NCT_PrintSet = 19,                   // ????
    NCT_CheckSet = 20,                   // ????
    NCT_DirectionTest = 21,              // ????
    NCT_FactoryReset = 22,               // ??????
    NCT_AutoFire = 23,                  // ???????
    NCT_CheckTimeSync = 24,
    NCT_SelfCheckStart = 25,             // ??????
    NCT_SelfCheckStop = 26,              // ??????
    NCT_UndefinedObject = 27,            // ?????Object
    NCT_ClientReset = 28,
    NCT_ForceEmergency = 29,             // ????????
    NCT_Log = 30,                        // ????
    NCT_LedStatus = 31,           // ??????
    NCT_ControllerInfo = 32,             // ?????
    NCT_GetControllerInfo = 33,          // ???????
    NCT_StopCommunication = 34,                 // ?????
    NCT_StartCommunication = 35,                // ?????
//    NCT_GetCurrentValue = 36,            // ????????
//    NCT_GetVoltageValue = 37,            // ????????
    NCT_DuplicateCheck = 36,
    NCT_ChangeDeviceAddress = 37,
    NCT_ClearUndefinedObject = 38,       // ?????????
    NCT_AddUndefinedObject = 39,         // ?????????
    NCT_DelUndefinedObject = 40,         // ?????????
    NCT_MonthCheckBegin = 41,            // ????
    NCT_MonthCheckEnd = 42,              // ????
    NCT_YearCheckBegin = 43,             // ????
    NCT_YearCheckEnd = 44,               // ????
    NCT_ProjectInitComplete = 45,  // ??????????
    NCT_CancelMute = 46,                 // ????
    NCT_PowerInfo = 47,                  // ??????
    NCT_StartEvacuationGroup = 48,       // ??????
    NCT_StartFlowEvacuationGroup = 49,   // ???????????
    NCT_StopEvacuationGroup = 50,        // ??????
    NCT_DeviceEmergencyStart = 51,       // ??????
    NCT_DeviceEmergencyStop = 52,        // ??????
    NCT_GetLayerEvacuationFlow = 53,     // ??????
    NCT_LayerEvacuationFlow = 54,        // ????
    NCT_ClearEvacuationFlow = 55,        // ?????
    NCT_HasFASSystem = 56,               // ??????
    NCT_StartSpeedUp = 57,               // ??????
    NCT_StopSpeedUp = 58,                // ??????
    NCT_StartCharge = 59,               // ????
    NCT_StopCharge = 60,                // ????
    NCT_ExitProgram = 61,               // ????
    NCT_EnergyMode = 62,                // ????
    NCT_SystemSet = 63,                 // ????
    NCT_LoginInfo = 64,                 //????
    NCT_Unlogin = 65,                   //??????
    NCT_LoginInfoLoop = 17,             //????
    NCT_UnLoginLoop = 66,               //??????
    NCT_DeviceTestStart = 67,           //??????
    NCT_DeviceReset = 68,               //????
    NCT_DeviceAdd = 69,                 //??????
    NCT_DeviceType = 70,                //??????
    NCT_ReadProtectInfor = 71,          //??????
    NCT_WriteProtectInfor = 72,         //?????
    NCT_DeviceDefaultOn = 73,           //??????
    NCT_DeviceDirection = 74,           //???????
    NCT_InputEmergency = 75,            //???????????
    NCT_ReadDeviceInfo = 76,            //?????
    NCT_FlashControl = 77,              //????
    NCT_ChangeControl = 78,             //??????
    NCT_CloseBatteryOut = 79,           //????????????
    NCT_SetLoopOutStatus = 80,          //???????????
    NCT_ReadLoopOutStatus = 81,         //?????????????
    NCT_RecordPage = 82,                //??????
    NCT_DeviceDefaultOff = 83,          //??????
    NCT_DeviceDefaultDrection = 84,     //??????
    NCT_Emergency = 85,                 //??????
    NCT_FlashConfig = 86,               //????

    NCT_ActiveInputEmergency = 87,      //????????
    NCT_PassiveInputEmergency = 88,     //????????
    NCT_ControllerParam = 89,           //控制器电参量
    NCT_RemoveFaultLamp = 90,           //清除故障灯具注册状态
    NCT_TestLinkageCom = 91,            //测试火报通讯口
    NCT_LinkageComBaudRate = 92,        //火报通讯口波特率
    NCT_NologinSendToDistribution = 93, //未注册灯具下发到集中电源指定回路
    NCT_LinkageComStatus = 94,          //火报通讯状态
    NCT_ClearCanSendData = 95,          //清空CAN发送数据
    NCT_ClearCanReceiveData = 96        //清空CAN接收数据
};


#endif // STRUCT_H
