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
 //��CAN�˿�
 int openCANSerialPort();
 //��������ģ��
 void startPowerModule(int nCANfd);
 //�رչ���ģ��
 void stopPowerModule(int nCANfd);
 //����CAN���ݺ�����CAN��ַ01��
 void sendCANData(int nCANfd,int nData4,int nData5,int nData6,int nData7);
 //���������ѹ����ֵ(���޺�����,CAN��ַ02)
 void sendOutPutVoltData(int nCANfd,int nData2,int nData3,int nData4,int nData5);
 //����ֱ����ѹ��ѹ����(����,CAN��ַ02)
 void sendDCVoltLowData(int nCANfd,int nData6,int nData7);
 //����ֱ����ѹ��ѹ����(����,CAN��ַ03)
 void sendDCVoltUpData(int nCANfd,int nData2,int nData3);
 //���������������ֵ�ͱ���ֵ����(���޺�����,CAN��ַ03)
 void sendProcAndWarnData(int nCANfd,int nData4,int nData5,int nData6,int nData7);
 //����IGBT���¶���ֵ����(���޺�����,CAN��ַ04)
 void sendIGBTTemperData(int nCANfd,int nData2,int nData3,int nData4,int nData5);
 //���͵���¶�1���¶���ֵ����(����,CAN��ַ04)
 void sendIDUCTTemper1Data(int nCANfd,int nData6,int nData7);
 //���͵���¶�2���¶���ֵ����(����,CAN��ַ05)
 void sendSubTotalcurrData(int nCANfd,int nData2,int nData3);
#ifdef UBUNTU_DEV //Compiler Switch
 //void parsem_iDCINPUTVoltageCtlData(struct can_frame frame,STRU_INPUTDCVOLTAGEMONI &stru_DCINPUTDATA);
  //����IGBT�¶ȼ������
 void parseIGBTTemperCtlData(struct can_frame frame,STRU_IGBTTEMPERATUREMONI &stru_TemperDATA);
 //��������¶ȼ������
 void parseIDUCTTemperCtlData(struct can_frame frame,STRU_IDUCTTEMPERATUREMONI &stru_TemperDATA);
 //��������״̬����
 void parseRunningStatData(struct can_frame frame,STRU_RUNNINGSTATUS &stru_RunningDATA);
 //��������״̬����
 void parseFaultStatData(struct can_frame frame,STRU_FAULTSTATUS &stru_FaultDATA,STRU_INPUTDCVOLTAGEMONI &stru_DCINPUTDATA);
#endif //Compiler Switch

};
#endif //CAN_DATA_RW_H
