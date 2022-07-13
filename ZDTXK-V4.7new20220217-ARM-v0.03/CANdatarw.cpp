/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: CANdatarw.cpp
** ժҪ: CAN���ݶ�д��
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2019.02.15
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2019.02.15   V1.0      ����

****************************************************************************/
#include "CANdatarw.h"
#include <stdio.h>
#include <QMutex>
extern QMutex g_Mutex;
CCANDataRW::CCANDataRW()
{


}
CCANDataRW::~CCANDataRW()
{
}
//��CAN�˿�
int CCANDataRW::openCANSerialPort()
{
 int s=-1;
 #ifdef UBUNTU_DEV //Compiler Switch
   struct sockaddr_can addr;
   struct ifreq ifr;
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        printf("Create socket failed");
        exit(-1);
    }
    //set up can interface
    strcpy(ifr.ifr_name, "can0");
    //assign can device
   ioctl(s, SIOCGIFINDEX, &ifr);
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
   //bind can device
    if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Bind can device failed\n");
        exit(-2);
    }
#endif  //Compiler Switch
    return s;
}
//��������ģ��
void CCANDataRW::startPowerModule(int nCANfd)
{
    sendCANData(nCANfd,0xa5,0xa5,0x5a,0x5a);
}
//�رչ���ģ��
void CCANDataRW::stopPowerModule(int nCANfd)
{
  sendCANData(nCANfd,0x5a,0x5a,0xa5,0xa5);
}
 void  CCANDataRW::sendCANData(int nCANfd,int nData4,int nData5,int nData6,int nData7)
 {
     if(nCANfd<0)
     {
         //��������
         return;
     }
#ifdef UBUNTU_DEV //Compiler Switch
    //configure can_id and can data length
    time_t nowtime = time(NULL);
    struct tm timeTemp;
    localtime_r(&nowtime,&timeTemp);
    struct can_frame frame;
    memset(frame.data,0,sizeof(frame.data));
    frame.can_id = CAN_EFF_FLAG | CAN_ADDRESS_00;
    frame.can_dlc = 8;
    printf("####CCANDataRW::ControlPowerModule####\n");
    frame.data[0]=0x11;
    frame.data[1]=timeTemp.tm_min;
    frame.data[2]=timeTemp.tm_hour;
    frame.data[3]=timeTemp.tm_sec;
    frame.data[4]=nData4;
    frame.data[5]=nData5;
    frame.data[6]=nData6;
    frame.data[7]=nData7;
    printf ("####nCANfd=%d####\n",nCANfd);
    write(nCANfd,&frame,sizeof(frame));
    printf ("####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x####\n",
        frame.data[0],
        frame.data[1],
        frame.data[2],
        frame.data[3],
        frame.data[4],
        frame.data[5],
        frame.data[6],
        frame.data[7]);
 #endif //Compiler Switch
 }
 //����ֱ����ѹ����ֵ����(ֻ������ֵ,CAN��ַ02)
// void  CCANDataRW::sendDCVoltLowData(int nCANfd,int nData6,int nData7)
// {
//	 if(nCANfd<0)
//	 {
//		 //��������
//		 return;
//	 }
//#ifdef UBUNTU_DEV //Compiler Switch
//    //configure can_id and can data length
//    time_t nowtime = time(NULL);
//    struct tm timeTemp;
//    localtime_r(&nowtime,&timeTemp);
//	struct can_frame frame;
//    memset(frame.data,0,sizeof(frame.data));
//    frame.can_id = CAN_EFF_FLAG | CAN_ADDRESS_02;
//    frame.can_dlc = 8;
//	printf("####CCANDataRW::sendDCVoltOverData####\n");
//    frame.data[0]=0x11;
//    frame.data[1]=timeTemp.tm_min;
//    frame.data[6]=nData6;
//    frame.data[7]=nData7;
//	printf ("####nCANfd=%d####\n",nCANfd);
//    write(nCANfd,&frame,sizeof(frame));
//	printf ("####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x####\n",
//		frame.data[0],
//		frame.data[1],
//		frame.data[2],
//		frame.data[3],
//		frame.data[4],
//		frame.data[5],
//		frame.data[6],
//		frame.data[7]);
// #endif //Compiler Switch
// }
 //���������ѹ����ֵ����(����ֵ������ֵ,CAN��ַ02)
// void  CCANDataRW::sendOutPutVoltData(int nCANfd,int nData2,int nData3,int nData4,int nData5)
// {
//	 if(nCANfd<0)
//	 {
//		 //��������
//		 return;
//	 }
//#ifdef UBUNTU_DEV //Compiler Switch
//    //configure can_id and can data length
//    time_t nowtime = time(NULL);
//    struct tm timeTemp;
//    localtime_r(&nowtime,&timeTemp);
//	struct can_frame frame;
//    memset(frame.data,0,sizeof(frame.data));
//    frame.can_id = CAN_EFF_FLAG | CAN_ADDRESS_02;
//    frame.can_dlc = 8;
//	printf("####CCANDataRW::sendOutputVoltProc####\n");
//    frame.data[0]=0x11;
//    frame.data[1]=timeTemp.tm_min;
//    frame.data[2]=nData2;
//    frame.data[3]=nData3;
//    frame.data[4]=nData4;
//    frame.data[5]=nData5;
//	printf ("####nCANfd=%d####\n",nCANfd);
//    write(nCANfd,&frame,sizeof(frame));
//	printf ("####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x####\n",
//		frame.data[0],
//		frame.data[1],
//		frame.data[2],
//		frame.data[3],
//		frame.data[4],
//		frame.data[5],
//		frame.data[6],
//		frame.data[7]);
// #endif //Compiler Switch
// }
  //����ֱ����ѹ����ֵ����(ֻ������ֵ,CAN��ַ03)
// void  CCANDataRW::sendDCVoltUpData(int nCANfd,int nData2,int nData3)
// {
//	 if(nCANfd<0)
//	 {
//		 //��������
//		 return;
//	 }
//#ifdef UBUNTU_DEV //Compiler Switch
//    //configure can_id and can data length
//    time_t nowtime = time(NULL);
//    struct tm timeTemp;
//    localtime_r(&nowtime,&timeTemp);
//	struct can_frame frame;
//    memset(frame.data,0,sizeof(frame.data));
//    frame.can_id = CAN_EFF_FLAG | CAN_ADDRESS_03;
//    frame.can_dlc = 8;
//	printf("####CCANDataRW::sendDCVoltUpData####\n");
//    frame.data[0]=0x11;
//    frame.data[1]=timeTemp.tm_min;
//    frame.data[2]=nData2;
//    frame.data[3]=nData3;
//	printf ("####nCANfd=%d####\n",nCANfd);
//    write(nCANfd,&frame,sizeof(frame));
//	printf ("####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x####\n",
//		frame.data[0],
//		frame.data[1],
//		frame.data[2],
//		frame.data[3],
//		frame.data[4],
//		frame.data[5],
//		frame.data[6],
//		frame.data[7]);
// #endif //Compiler Switch
// }
 //���������������ֵ�ͱ���ֵ����(���޺�����,CAN��ַ03)
// void CCANDataRW::sendProcAndWarnData(int nCANfd,int nData4,int nData5,int nData6,int nData7)
// {
//	 if(nCANfd<0)
//	 {
//		 //��������
//		 return;
//	 }
//#ifdef UBUNTU_DEV //Compiler Switch
//    //configure can_id and can data length
//    time_t nowtime = time(NULL);
//    struct tm timeTemp;
//    localtime_r(&nowtime,&timeTemp);
//	struct can_frame frame;
//    memset(frame.data,0,sizeof(frame.data));
//    frame.can_id = CAN_EFF_FLAG | CAN_ADDRESS_03;
//    frame.can_dlc = 8;
//	printf("####CCANDataRW::sendProcAndWarnData####\n");
//    frame.data[0]=0x11;
//    frame.data[1]=timeTemp.tm_min;
//    frame.data[4]=nData4;
//    frame.data[5]=nData5;
//	frame.data[6]=nData6;
//    frame.data[7]=nData7;
//	printf ("####nCANfd=%d####\n",nCANfd);
//    write(nCANfd,&frame,sizeof(frame));
//	printf ("####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x####\n",
//		frame.data[0],
//		frame.data[1],
//		frame.data[2],
//		frame.data[3],
//		frame.data[4],
//		frame.data[5],
//		frame.data[6],
//		frame.data[7]);
// #endif //Compiler Switch
// }
 //����IGBT���¶���ֵ����(���޺�����,CAN��ַ04)
// void CCANDataRW::sendIGBTTemperData(int nCANfd,int nData2,int nData3,int nData4,int nData5)
// {
//	if(nCANfd<0)
//	 {
//		 //��������
//		 return;
//	 }
//#ifdef UBUNTU_DEV //Compiler Switch
//    //configure can_id and can data length
//    time_t nowtime = time(NULL);
//    struct tm timeTemp;
//    localtime_r(&nowtime,&timeTemp);
//	struct can_frame frame;
//    memset(frame.data,0,sizeof(frame.data));
//    frame.can_id = CAN_EFF_FLAG | CAN_ADDRESS_04;
//    frame.can_dlc = 8;
//	printf("####CCANDataRW::sendIGBTTemperData####\n");
//    frame.data[0]=0x11;
//    frame.data[1]=timeTemp.tm_min;
//    frame.data[2]=nData2;
//    frame.data[3]=nData3;
//	frame.data[4]=nData4;
//    frame.data[5]=nData5;
//	printf ("####nCANfd=%d####\n",nCANfd);
//    write(nCANfd,&frame,sizeof(frame));
//	printf ("####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x####\n",
//		frame.data[0],
//		frame.data[1],
//		frame.data[2],
//		frame.data[3],
//		frame.data[4],
//		frame.data[5],
//		frame.data[6],
//		frame.data[7]);
// #endif //Compiler Switch
// }
 //���͵���¶�1���¶���ֵ����(����,CAN��ַ04)
// void CCANDataRW::sendIDUCTTemper1Data(int nCANfd,int nData6,int nData7)
// {
//	 if(nCANfd<0)
//	 {
//		 //��������
//		 return;
//	 }
//#ifdef UBUNTU_DEV //Compiler Switch
//    //configure can_id and can data length
//    time_t nowtime = time(NULL);
//    struct tm timeTemp;
//    localtime_r(&nowtime,&timeTemp);
//	struct can_frame frame;
//    memset(frame.data,0,sizeof(frame.data));
//    frame.can_id = CAN_EFF_FLAG | CAN_ADDRESS_04;
//    frame.can_dlc = 8;
//	printf("####CCANDataRW::sendIDUCTTemper1Data####\n");
//    frame.data[0]=0x11;
//    frame.data[1]=timeTemp.tm_min;
//	frame.data[6]=nData6;
//    frame.data[7]=nData7;
//	printf ("####nCANfd=%d####\n",nCANfd);
//    write(nCANfd,&frame,sizeof(frame));
//	printf ("####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x####\n",
//		frame.data[0],
//		frame.data[1],
//		frame.data[2],
//		frame.data[3],
//		frame.data[4],
//		frame.data[5],
//		frame.data[6],
//		frame.data[7]);
// #endif //Compiler Switch
// }
 //���͵���¶�2���¶���ֵ����(����,CAN��ַ05)
 void CCANDataRW::sendSubTotalcurrData(int nCANfd,int nData2,int nData3)
 {
    if(nCANfd<0)
     {
         //��������
         return;
     }
#ifdef UBUNTU_DEV //Compiler Switch
    //configure can_id and can data length
    time_t nowtime = time(NULL);
    struct tm timeTemp;
    localtime_r(&nowtime,&timeTemp);
    struct can_frame frame;
    memset(frame.data,0,sizeof(frame.data));
    frame.can_id = CAN_EFF_FLAG | CAN_ADDRESS_05;
    frame.can_dlc = 8;
    //printf("####CCANDataRW::sendSubTotalcurrData####\n");
    frame.data[0]=0x11;
    frame.data[1]=timeTemp.tm_min;
    frame.data[2]=nData2;
    frame.data[3]=nData3;
    //printf ("####nCANfd=%d####\n",nCANfd);
    write(nCANfd,&frame,sizeof(frame));
    /*printf ("####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x####\n",
        frame.data[0],
        frame.data[1],
        frame.data[2],
        frame.data[3],
        frame.data[4],
        frame.data[5],
        frame.data[6],
        frame.data[7]);*/
 #endif //Compiler Switch
 }
  #ifdef UBUNTU_DEV //Compiler Switch
 //��������ģ������ֱ����ѹ����
 //void CCANDataRW::parsem_iDCINPUTVoltageCtlData(struct can_frame frame,STRU_INPUTDCVOLTAGEMONI &stru_TemperDATA)
 //{
    //	stru_TemperDATA.fINPUTDCVoltage = (frame.data[6]*256+frame.data[7])/10.0;//����ģ������ֱ����ѹ
    //	//printf("##%2.1f##",stru_TemperDATA.fINPUTDCVoltage);
 //}
 //����IGBT�¶ȼ�����ݺ͹���ģ�����������������
 void CCANDataRW::parseIGBTTemperCtlData(struct can_frame frame,STRU_IGBTTEMPERATUREMONI &stru_TemperDATA)
 {
        stru_TemperDATA.fOUTPUTACCurrent = (frame.data[2]*256+frame.data[3])/10.0;//����ģ�������������
        stru_TemperDATA.fIGBT1Temper = (frame.data[4]*256+frame.data[5])/64.0-256.0;//IGBT�¶�1
        stru_TemperDATA.fIGBT2Temper = (frame.data[6]*256+frame.data[7])/64.0-256.0;//IGBT�¶�2
        /*printf("####fIGBT1Temper=%2.1f--fIGBT2Temper=%2.1f--fOUTPUTACCurrent=%2.1f####\n",
          stru_TemperDATA.fIGBT1Temper,
          stru_TemperDATA.fIGBT2Temper,
          stru_TemperDATA.fOUTPUTACCurrent);*/
 }

 //����IDUCT�¶ȼ������
 void CCANDataRW::parseIDUCTTemperCtlData(struct can_frame frame,STRU_IDUCTTEMPERATUREMONI &stru_TemperDATA)
 {
      stru_TemperDATA.fIDUCT1Temper = (frame.data[2]*256+frame.data[3])/64.0-256.0;   //����¶�1
      stru_TemperDATA.fIDUCT2Temper = (frame.data[4]*256+frame.data[5])/64.0-256.0;   //����¶�2
      stru_TemperDATA.fOUTPUTACVoltage = (frame.data[6]*256+frame.data[7])/10;//����ģ�����������ѹ
      /*printf("####fIDUCT1Temper=%2.1f--fIDUCT2Temper=%2.1f--fOUTPUTACVoltage=%2.1f####\n",
      stru_TemperDATA.fIDUCT1Temper,
      stru_TemperDATA.fIDUCT2Temper,
      stru_TemperDATA.fOUTPUTACVoltage);*/
 }

  //��������״̬����
 void CCANDataRW::parseRunningStatData(struct can_frame frame,STRU_RUNNINGSTATUS &stru_RunningDATA)
 {
       //���ݸ�ֵ-Data2
      stru_RunningDATA.iRestartprocFlag =(frame.data[2]&0x80)>>7;     //����������
      stru_RunningDATA.iNormaloperFlag  =(frame.data[2]&0x40)>>6;     //��������
      stru_RunningDATA.iFaultProtFlag   =(frame.data[2]&0x20)>>5;     //���ϱ�����
      stru_RunningDATA.iFaultlockFlag   =(frame.data[2]&0x10)>>4;     //���ϱ���
      stru_RunningDATA.iProtectedTimes  =frame.data[2]&0x0F;//�ѱ�������(����4λ)
       //���ݸ�ֵ-Data3(���ݸ�3λ)
      stru_RunningDATA.iBlockpulseFlag  =(frame.data[3]&0x80)>>7;     //��������
      stru_RunningDATA.iRecstartsigFlag =(frame.data[3]&0x40)>>6;     //�յ������ź�
      stru_RunningDATA.iRecshutsigFlag  =(frame.data[3]&0x20)>>5;     //�յ��ػ��ź�
      /*printf("iRestartprocFlag=%d,iNormaloperFlag=%d,iFaultProtFlag=%d,iFaultlockFlag=%d,iProtectedTimes=%d,iBlockpulseFlag=%d,iRecstartsigFlag=%d,iRecshutsigFlag=%d\n",
          stru_RunningDATA.iRestartprocFlag,
          stru_RunningDATA.iNormaloperFlag,
          stru_RunningDATA.iFaultProtFlag,
          stru_RunningDATA.iFaultlockFlag,
          stru_RunningDATA.iProtectedTimes,
          stru_RunningDATA.iBlockpulseFlag,
          stru_RunningDATA.iRecstartsigFlag,
          stru_RunningDATA.iRecshutsigFlag
          );*/
      QString strTempMsg;
      strTempMsg.sprintf("%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",frame.data[0],frame.data[1],frame.data[2],frame.data[3],frame.data[4],frame.data[5],frame.data[6],frame.data[7]);
      stru_RunningDATA.strOrigMsg=strTempMsg;
 }
   //��������״̬����
 void CCANDataRW::parseFaultStatData(struct can_frame frame,STRU_FAULTSTATUS &stru_FaultDATA,STRU_INPUTDCVOLTAGEMONI &stru_DCINPUTDATA)
 {
      //���ݸ�ֵ-Data2
      stru_FaultDATA.iOutovervoltFlag  =(frame.data[2]&0x80)>>7;  //�����ѹ
      stru_FaultDATA.iDCovervoltFlag   =(frame.data[2]&0x40)>>6;  //����ֱ����ѹ
      stru_FaultDATA.iDCundervoltFlag  =(frame.data[2]&0x20)>>5;  //����ֱ��Ƿѹ
      stru_FaultDATA.iACcurrentwarnFlag=(frame.data[2]&0x10)>>4;  //���������������
      stru_FaultDATA.iACcurrentprocFlag=(frame.data[2]&0x08)>>3;  //���������������
      stru_FaultDATA.iIGBT1overtempFlag=(frame.data[2]&0x04)>>2;  //IGBT1���±���
      stru_FaultDATA.iIGBT2overtempFlag=(frame.data[2]&0x02)>>1;  //IGBT2���±���
      stru_FaultDATA.iIndu1overtempFlag=frame.data[2]&0x01;  //���1���±���
      /*printf("iOutovervoltFlag=%d-iDCovervoltFlag=%d-iDCundervoltFlag=%d-iACcurrentwarnFlag=%d-iACcurrentwarnFlag=%d-iIGBT1overtempFlag=%d-iIGBT2overtempFlag=%d-iIndu1overtempFlag=%d\n",
          stru_FaultDATA.iOutovervoltFlag,
          stru_FaultDATA.iDCovervoltFlag,
          stru_FaultDATA.iDCundervoltFlag,
          stru_FaultDATA.iACcurrentwarnFlag,
          stru_FaultDATA.iACcurrentprocFlag,
          stru_FaultDATA.iIGBT1overtempFlag,
          stru_FaultDATA.iIGBT2overtempFlag,
          stru_FaultDATA.iIndu1overtempFlag);*/
      //���ݸ�ֵ-Data3
      stru_FaultDATA.iIndu2overtempFlag=(frame.data[3]&0x80)>>7;  //���2���±���
      stru_FaultDATA.iDripulseblockFlag=(frame.data[3]&0x40)>>6;  //�����������
      stru_FaultDATA.iDigspecinterFlag=(frame.data[3]&0x20)>>5;   //���������ź��ж�
      stru_FaultDATA.iAnaspecampoverFlag=(frame.data[3]&0x10)>>4; //ģ�������źŷ�ֵ����Χ
      stru_FaultDATA.iAnaspecfreqoverFlag=(frame.data[3]&0x08)>>3;//ģ�������ź�Ƶ�ʳ���Χ
      stru_FaultDATA.iDigspecampoverFlag=(frame.data[3]&0x04)>>2; //���������źŷ�ֵ����Χ
      stru_FaultDATA.iDigspecfreqoverFlag=(frame.data[3]&0x02)>>1;//���������ź�Ƶ�ʳ���Χ
      stru_FaultDATA.iIGBT1driprocFlag=frame.data[3]&0x01;   //IGBT1��������
      /*printf("iIndu2overtempFlag=%d,iDripulseblockFlag=%d,iDigspecinterFlag=%d,iAnaspecampoverFlag=%d,iAnaspecfreqoverFlag=%d,iDigspecampoverFlag=%d,iDigspecfreqoverFlag=%d,iIGBT1driprocFlag=%d",
          stru_FaultDATA.iIndu2overtempFlag,
          stru_FaultDATA.iDripulseblockFlag,
          stru_FaultDATA.iDigspecinterFlag,
          stru_FaultDATA.iAnaspecampoverFlag,
          stru_FaultDATA.iAnaspecfreqoverFlag,
          stru_FaultDATA.iDigspecampoverFlag,
          stru_FaultDATA.iDigspecfreqoverFlag,
          stru_FaultDATA.iIGBT1driprocFlag);*/
      //���ݸ�ֵ-Data4(���ݸ�5λ)
      stru_FaultDATA.iIGBT2driprocFlag=(frame.data[4]&0x80)>>7;    //IGBT2��������
      stru_FaultDATA.iIGBT3driprocFlag=(frame.data[4]&0x40)>>6;    //IGBT3��������
      stru_FaultDATA.iIGBT4driprocFlag=(frame.data[4]&0x20)>>5;    //IGBT4��������
      stru_FaultDATA.iIGBT5driprocFlag=(frame.data[4]&0x10)>>4;    //IGBT5��������
      stru_FaultDATA.iIGBT6driprocFlag=(frame.data[4]&0x08)>>3;    //IGBT6��������
      stru_FaultDATA.iOutputvoltwarnFlag=(frame.data[4]&0x04)>>2;    //�����ѹ����
      /*printf("iIGBT2driprocFlag=%d,iIGBT3driprocFlag=%d,iIGBT4driprocFlag=%d,iIGBT5driprocFlag=%d,iIGBT6driprocFlag=%d,iOutputvoltwarnFlag=%d\n",
          stru_FaultDATA.iIGBT2driprocFlag,
          stru_FaultDATA.iIGBT3driprocFlag,
          stru_FaultDATA.iIGBT4driprocFlag,
          stru_FaultDATA.iIGBT5driprocFlag,
          stru_FaultDATA.iIGBT6driprocFlag,
          stru_FaultDATA.iOutputvoltwarnFlag);*/
      stru_DCINPUTDATA.fINPUTDCVoltage = (frame.data[6]*256+frame.data[7])/10.0;//����ģ������ֱ����ѹ
      //printf("fINPUTDCVoltage=%2.1f\n",stru_DCINPUTDATA.fINPUTDCVoltage);
 }
#endif
