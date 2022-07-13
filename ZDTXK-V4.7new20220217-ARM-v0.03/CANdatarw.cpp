/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: CANdatarw.cpp
** 摘要: CAN数据读写类
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.02.15
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.02.15   V1.0      创建

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
//打开CAN端口
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
//启动功率模块
void CCANDataRW::startPowerModule(int nCANfd)
{
    sendCANData(nCANfd,0xa5,0xa5,0x5a,0x5a);
}
//关闭功率模块
void CCANDataRW::stopPowerModule(int nCANfd)
{
  sendCANData(nCANfd,0x5a,0x5a,0xa5,0xa5);
}
 void  CCANDataRW::sendCANData(int nCANfd,int nData4,int nData5,int nData6,int nData7)
 {
     if(nCANfd<0)
     {
         //参数防误
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
 //发送直流过压保护值参数(只有下限值,CAN地址02)
// void  CCANDataRW::sendDCVoltLowData(int nCANfd,int nData6,int nData7)
// {
//	 if(nCANfd<0)
//	 {
//		 //参数防误
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
 //发送输出电压保护值参数(下限值和上限值,CAN地址02)
// void  CCANDataRW::sendOutPutVoltData(int nCANfd,int nData2,int nData3,int nData4,int nData5)
// {
//	 if(nCANfd<0)
//	 {
//		 //参数防误
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
  //发送直流过压保护值参数(只有上限值,CAN地址03)
// void  CCANDataRW::sendDCVoltUpData(int nCANfd,int nData2,int nData3)
// {
//	 if(nCANfd<0)
//	 {
//		 //参数防误
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
 //发送输出电流保护值和报警值数据(下限和上限,CAN地址03)
// void CCANDataRW::sendProcAndWarnData(int nCANfd,int nData4,int nData5,int nData6,int nData7)
// {
//	 if(nCANfd<0)
//	 {
//		 //参数防误
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
 //发送IGBT过温动作值数据(下限和上限,CAN地址04)
// void CCANDataRW::sendIGBTTemperData(int nCANfd,int nData2,int nData3,int nData4,int nData5)
// {
//	if(nCANfd<0)
//	 {
//		 //参数防误
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
 //发送电感温度1过温动作值数据(下限,CAN地址04)
// void CCANDataRW::sendIDUCTTemper1Data(int nCANfd,int nData6,int nData7)
// {
//	 if(nCANfd<0)
//	 {
//		 //参数防误
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
 //发送电感温度2过温动作值数据(上限,CAN地址05)
 void CCANDataRW::sendSubTotalcurrData(int nCANfd,int nData2,int nData3)
 {
    if(nCANfd<0)
     {
         //参数防误
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
 //解析功率模块输入直流电压数据
 //void CCANDataRW::parsem_iDCINPUTVoltageCtlData(struct can_frame frame,STRU_INPUTDCVOLTAGEMONI &stru_TemperDATA)
 //{
    //	stru_TemperDATA.fINPUTDCVoltage = (frame.data[6]*256+frame.data[7])/10.0;//功率模块输入直流电压
    //	//printf("##%2.1f##",stru_TemperDATA.fINPUTDCVoltage);
 //}
 //解析IGBT温度监控数据和功率模块输出交流电流数据
 void CCANDataRW::parseIGBTTemperCtlData(struct can_frame frame,STRU_IGBTTEMPERATUREMONI &stru_TemperDATA)
 {
        stru_TemperDATA.fOUTPUTACCurrent = (frame.data[2]*256+frame.data[3])/10.0;//功率模块输出交流电流
        stru_TemperDATA.fIGBT1Temper = (frame.data[4]*256+frame.data[5])/64.0-256.0;//IGBT温度1
        stru_TemperDATA.fIGBT2Temper = (frame.data[6]*256+frame.data[7])/64.0-256.0;//IGBT温度2
        /*printf("####fIGBT1Temper=%2.1f--fIGBT2Temper=%2.1f--fOUTPUTACCurrent=%2.1f####\n",
          stru_TemperDATA.fIGBT1Temper,
          stru_TemperDATA.fIGBT2Temper,
          stru_TemperDATA.fOUTPUTACCurrent);*/
 }

 //解析IDUCT温度监控数据
 void CCANDataRW::parseIDUCTTemperCtlData(struct can_frame frame,STRU_IDUCTTEMPERATUREMONI &stru_TemperDATA)
 {
      stru_TemperDATA.fIDUCT1Temper = (frame.data[2]*256+frame.data[3])/64.0-256.0;   //电感温度1
      stru_TemperDATA.fIDUCT2Temper = (frame.data[4]*256+frame.data[5])/64.0-256.0;   //电感温度2
      stru_TemperDATA.fOUTPUTACVoltage = (frame.data[6]*256+frame.data[7])/10;//功率模块输出交流电压
      /*printf("####fIDUCT1Temper=%2.1f--fIDUCT2Temper=%2.1f--fOUTPUTACVoltage=%2.1f####\n",
      stru_TemperDATA.fIDUCT1Temper,
      stru_TemperDATA.fIDUCT2Temper,
      stru_TemperDATA.fOUTPUTACVoltage);*/
 }

  //解析运行状态数据
 void CCANDataRW::parseRunningStatData(struct can_frame frame,STRU_RUNNINGSTATUS &stru_RunningDATA)
 {
       //数据赋值-Data2
      stru_RunningDATA.iRestartprocFlag =(frame.data[2]&0x80)>>7;     //重启过程中
      stru_RunningDATA.iNormaloperFlag  =(frame.data[2]&0x40)>>6;     //正常运行
      stru_RunningDATA.iFaultProtFlag   =(frame.data[2]&0x20)>>5;     //故障保护中
      stru_RunningDATA.iFaultlockFlag   =(frame.data[2]&0x10)>>4;     //故障闭锁
      stru_RunningDATA.iProtectedTimes  =frame.data[2]&0x0F;//已保护次数(右移4位)
       //数据赋值-Data3(数据高3位)
      stru_RunningDATA.iBlockpulseFlag  =(frame.data[3]&0x80)>>7;     //封锁脉冲
      stru_RunningDATA.iRecstartsigFlag =(frame.data[3]&0x40)>>6;     //收到启动信号
      stru_RunningDATA.iRecshutsigFlag  =(frame.data[3]&0x20)>>5;     //收到关机信号
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
   //解析故障状态数据
 void CCANDataRW::parseFaultStatData(struct can_frame frame,STRU_FAULTSTATUS &stru_FaultDATA,STRU_INPUTDCVOLTAGEMONI &stru_DCINPUTDATA)
 {
      //数据赋值-Data2
      stru_FaultDATA.iOutovervoltFlag  =(frame.data[2]&0x80)>>7;  //输出过压
      stru_FaultDATA.iDCovervoltFlag   =(frame.data[2]&0x40)>>6;  //输入直流过压
      stru_FaultDATA.iDCundervoltFlag  =(frame.data[2]&0x20)>>5;  //输入直流欠压
      stru_FaultDATA.iACcurrentwarnFlag=(frame.data[2]&0x10)>>4;  //输出交流电流报警
      stru_FaultDATA.iACcurrentprocFlag=(frame.data[2]&0x08)>>3;  //输出交流电流保护
      stru_FaultDATA.iIGBT1overtempFlag=(frame.data[2]&0x04)>>2;  //IGBT1过温保护
      stru_FaultDATA.iIGBT2overtempFlag=(frame.data[2]&0x02)>>1;  //IGBT2过温保护
      stru_FaultDATA.iIndu1overtempFlag=frame.data[2]&0x01;  //电感1过温保护
      /*printf("iOutovervoltFlag=%d-iDCovervoltFlag=%d-iDCundervoltFlag=%d-iACcurrentwarnFlag=%d-iACcurrentwarnFlag=%d-iIGBT1overtempFlag=%d-iIGBT2overtempFlag=%d-iIndu1overtempFlag=%d\n",
          stru_FaultDATA.iOutovervoltFlag,
          stru_FaultDATA.iDCovervoltFlag,
          stru_FaultDATA.iDCundervoltFlag,
          stru_FaultDATA.iACcurrentwarnFlag,
          stru_FaultDATA.iACcurrentprocFlag,
          stru_FaultDATA.iIGBT1overtempFlag,
          stru_FaultDATA.iIGBT2overtempFlag,
          stru_FaultDATA.iIndu1overtempFlag);*/
      //数据赋值-Data3
      stru_FaultDATA.iIndu2overtempFlag=(frame.data[3]&0x80)>>7;  //电感2过温保护
      stru_FaultDATA.iDripulseblockFlag=(frame.data[3]&0x40)>>6;  //驱动脉冲封锁
      stru_FaultDATA.iDigspecinterFlag=(frame.data[3]&0x20)>>5;   //数字谱型信号中断
      stru_FaultDATA.iAnaspecampoverFlag=(frame.data[3]&0x10)>>4; //模拟谱型信号幅值超范围
      stru_FaultDATA.iAnaspecfreqoverFlag=(frame.data[3]&0x08)>>3;//模拟谱型信号频率超范围
      stru_FaultDATA.iDigspecampoverFlag=(frame.data[3]&0x04)>>2; //数字谱型信号幅值超范围
      stru_FaultDATA.iDigspecfreqoverFlag=(frame.data[3]&0x02)>>1;//数字谱型信号频率超范围
      stru_FaultDATA.iIGBT1driprocFlag=frame.data[3]&0x01;   //IGBT1驱动保护
      /*printf("iIndu2overtempFlag=%d,iDripulseblockFlag=%d,iDigspecinterFlag=%d,iAnaspecampoverFlag=%d,iAnaspecfreqoverFlag=%d,iDigspecampoverFlag=%d,iDigspecfreqoverFlag=%d,iIGBT1driprocFlag=%d",
          stru_FaultDATA.iIndu2overtempFlag,
          stru_FaultDATA.iDripulseblockFlag,
          stru_FaultDATA.iDigspecinterFlag,
          stru_FaultDATA.iAnaspecampoverFlag,
          stru_FaultDATA.iAnaspecfreqoverFlag,
          stru_FaultDATA.iDigspecampoverFlag,
          stru_FaultDATA.iDigspecfreqoverFlag,
          stru_FaultDATA.iIGBT1driprocFlag);*/
      //数据赋值-Data4(数据高5位)
      stru_FaultDATA.iIGBT2driprocFlag=(frame.data[4]&0x80)>>7;    //IGBT2驱动保护
      stru_FaultDATA.iIGBT3driprocFlag=(frame.data[4]&0x40)>>6;    //IGBT3驱动保护
      stru_FaultDATA.iIGBT4driprocFlag=(frame.data[4]&0x20)>>5;    //IGBT4驱动保护
      stru_FaultDATA.iIGBT5driprocFlag=(frame.data[4]&0x10)>>4;    //IGBT5驱动保护
      stru_FaultDATA.iIGBT6driprocFlag=(frame.data[4]&0x08)>>3;    //IGBT6驱动保护
      stru_FaultDATA.iOutputvoltwarnFlag=(frame.data[4]&0x04)>>2;    //输出电压报警
      /*printf("iIGBT2driprocFlag=%d,iIGBT3driprocFlag=%d,iIGBT4driprocFlag=%d,iIGBT5driprocFlag=%d,iIGBT6driprocFlag=%d,iOutputvoltwarnFlag=%d\n",
          stru_FaultDATA.iIGBT2driprocFlag,
          stru_FaultDATA.iIGBT3driprocFlag,
          stru_FaultDATA.iIGBT4driprocFlag,
          stru_FaultDATA.iIGBT5driprocFlag,
          stru_FaultDATA.iIGBT6driprocFlag,
          stru_FaultDATA.iOutputvoltwarnFlag);*/
      stru_DCINPUTDATA.fINPUTDCVoltage = (frame.data[6]*256+frame.data[7])/10.0;//功率模块输入直流电压
      //printf("fINPUTDCVoltage=%2.1f\n",stru_DCINPUTDATA.fINPUTDCVoltage);
 }
#endif
