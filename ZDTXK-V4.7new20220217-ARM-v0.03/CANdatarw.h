#ifndef CAN_DATA_RW_H
#define CAN_DATA_RW_H
#include "commmacro.h"

#ifdef UBUNTU_DEV //Compiler Switch
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <math.h>
#endif           //Compiler Switch

class CCANDataRW
{
public:
    CCANDataRW();
    ~CCANDataRW();
public:
 //打开CAN端口
 int openCANSerialPort();
 //启动功率模块
 void startPowerModule(int nCANfd);
 //关闭功率模块
 void stopPowerModule(int nCANfd);
 //发送CAN数据函数（CAN地址01）
 void sendCANData(int nCANfd,int nData4,int nData5,int nData6,int nData7);
 //发送输出电压保护值(下限和上限,CAN地址02)
 void sendOutPutVoltData(int nCANfd,int nData2,int nData3,int nData4,int nData5);
 //发送直流电压过压数据(下限,CAN地址02)
 void sendDCVoltLowData(int nCANfd,int nData6,int nData7);
 //发送直流电压过压数据(上限,CAN地址03)
 void sendDCVoltUpData(int nCANfd,int nData2,int nData3);
 //发送输出电流保护值和报警值数据(下限和上限,CAN地址03)
 void sendProcAndWarnData(int nCANfd,int nData4,int nData5,int nData6,int nData7);
 //发送IGBT过温动作值数据(下限和上限,CAN地址04)
 void sendIGBTTemperData(int nCANfd,int nData2,int nData3,int nData4,int nData5);
 //发送电感温度1过温动作值数据(下限,CAN地址04)
 void sendIDUCTTemper1Data(int nCANfd,int nData6,int nData7);
 //发送电感温度2过温动作值数据(上限,CAN地址05)
 void sendSubTotalcurrData(int nCANfd,int nData2,int nData3);
#ifdef UBUNTU_DEV //Compiler Switch
 //void parsem_iDCINPUTVoltageCtlData(struct can_frame frame,STRU_INPUTDCVOLTAGEMONI &stru_DCINPUTDATA);
  //解析IGBT温度监控数据
 void parseIGBTTemperCtlData(struct can_frame frame,STRU_IGBTTEMPERATUREMONI &stru_TemperDATA);
 //解析电感温度监控数据
 void parseIDUCTTemperCtlData(struct can_frame frame,STRU_IDUCTTEMPERATUREMONI &stru_TemperDATA);
 //解析运行状态数据
 void parseRunningStatData(struct can_frame frame,STRU_RUNNINGSTATUS &stru_RunningDATA);
 //解析故障状态数据
 void parseFaultStatData(struct can_frame frame,STRU_FAULTSTATUS &stru_FaultDATA,STRU_INPUTDCVOLTAGEMONI &stru_DCINPUTDATA);
#endif //Compiler Switch

};
#endif //CAN_DATA_RW_H
