/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: DataReadThread.cpp
** 摘要: GPIO数据接收线程类
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.11.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2018.11.01   V1.0      创建
** 聂晓波      2019.07.13   V1.1      修改、完善
** 张旺        20220223     V1.2      基于gpiodatarecvthread新建，AD760601读取数据和处理数据线程
****************************************************************************/
#include "datareadthread.h"
#include <qapplication.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <QMutex>
#include "commmacro.h"
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

//add by zw 20220223
extern int fd_err;
extern STRU_BASICPARA g_struBasicPara;
extern STRU_NEWFAULTSTATUS g_newfaultstatus;
extern STRU_ADDATANEW g_newaddata;
extern STRU_NEWADJCOEF g_newAdjcoef;
extern QStringList  g_strlistGeneralProc;
extern QVector<STR_STATUSDATA>g_vec_StatusRecord;
extern STRU_NEWCHASETDATA g_newchasetdata;
//end add by zw 20220223

DataReadThread::DataReadThread(QWidget * ptr,int nfd)
{
    m_pReceiver = ptr;
    m_bStopped= false;
    fd_ad01=nfd;
    m_iGfstartflag=false;
    pwm1Freq = 10000;
    displyCnt = pwm1Freq/4;
    m_bMuxOut = TPH_B;
    printf("DataReadThread::DataReadThread\n");
}
DataReadThread::~DataReadThread()
{
}
void DataReadThread::restart()
{
    m_bStopped = false;
    wait();
    start();
}
void DataReadThread::stop()
{
    m_bStopped = true;
    wait();
}

// add by zw 20220223
void DataReadThread::run()
{
    int tcnt = 0;
#ifdef UBUNTU_DEV //Compiler Switch
    choseMuxOut(m_bMuxOut);
    while (!m_bStopped)
    {
        tcnt++;
//        usleep(2000000);
//        readAllData();
        readErrStatus();
        if(tcnt%3 == 0)
        {
            m_bMuxOut++;
            if(m_bMuxOut > 2)
                m_bMuxOut = 0;
            choseMuxOut(m_bMuxOut);
        }
        if(m_iGfstartflag)
        {
//            readAd760601();
            handleData();
//            qDebug()<<"#### ain02 ="<<i_pGPIOdataThread->ain02[0]<<"####";
//            qDebug()<<"#### ain01 ="<<ain01[0]<<"####";
        }
        //AD7606-01采集速率控制

        usleep(99900);  //10Hz 99900/100 50000/50000
        ioctl(fd_out,1,AD01_CA);  //开始AD转换，同时读取上次转换结果
        usleep(100);
        readAd760601();
        ioctl(fd_out,0,AD01_CA);
        //qDebug()<<"#### DataReadThread::run() ####";
        //AD7606-01采集速率控制
//        usleep(2000000);//测试控制周期
    }
#endif //Compiler Switch
}
//end add by zw 20220223

void DataReadThread::handleData()
{
#ifdef UBUNTU_DEV //Compiler Switch
       //检测是否存在外部保护
      g_strlistGeneralProc.clear();
      g_vec_StatusRecord.clear();
      STR_STATUSDATA statusrec;
      int iGeneralProcCnt=0;
      int cnt_proc=0;
      bool bCheckOk=false;
     bCheckOk=m_JudgeProc.newCheckExterProcExist(g_newchasetdata,cnt_proc,g_strlistGeneralProc);
     if(bCheckOk)
     {
        printf("bIsExterProcExist\n");
        iGeneralProcCnt++;
     }
     bCheckOk=m_JudgeProc.newCheckSubDoorProcExist(g_newfaultstatus,g_newchasetdata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//从柜门保护
        g_strlistGeneralProc.append(m_JudgeProc.m_strSubmbh);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strSubmbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     bCheckOk=m_JudgeProc.newCheckSubRectBridgeOverheat(g_newchasetdata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//从柜整流桥过温
        g_strlistGeneralProc.append(m_JudgeProc.m_strSubzlqgw);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strSubzlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     m_JudgeProc.newCheckExcitVolExist();//检测励磁电压控制励磁指示灯

     /*
     bCheckOk=m_JudgeProc.newCheckVoltImbalance(g_newaddata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//三相电压不平衡
        g_strlistGeneralProc.append(m_JudgeProc.m_strVoltUnbalance);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltUnbalance,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     bCheckOk=m_JudgeProc.newCheckOverVolt(g_newaddata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//三相电压过高
        g_strlistGeneralProc.append(m_JudgeProc.m_strVoltUp);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     bCheckOk=m_JudgeProc.newCheckLowVolt(g_newaddata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//三相电压过低
        g_strlistGeneralProc.append(m_JudgeProc.m_strVoltDown);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltDown,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     if((g_newaddata.fTotalVolAC-g_struBasicPara.fTotalvoltUp)>DELT_FVALUE)
     {
         iGeneralProcCnt++;//功放总输出电压过高
         g_strlistGeneralProc.append(m_JudgeProc.m_strOutVoltUp);
         statusrec=organizationStatusRecord(m_JudgeProc.m_strOutVoltUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
         g_vec_StatusRecord.push_back(statusrec);
     }
     int iCurrOverCnt=0;
     bCheckOk=m_JudgeProc.newCheckOutputCurrentOver(g_newaddata,iCurrOverCnt);
     if(bCheckOk)
     {
         iGeneralProcCnt++;//分柜输出电流过高
         g_strlistGeneralProc.append(m_JudgeProc.m_strSubCurrentUp);
         statusrec=organizationStatusRecord(m_JudgeProc.m_strSubCurrentUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
         g_vec_StatusRecord.push_back(statusrec);
     }
     if((g_newaddata.fTotalSlaveCurAC-g_struBasicPara.fTotalcurrentUp)>DELT_FVALUE)
     {
         iGeneralProcCnt++;//功放总输出电流过高
         g_strlistGeneralProc.append(m_JudgeProc.m_strOutCurrentUp);
         statusrec=organizationStatusRecord(m_JudgeProc.m_strOutCurrentUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
         g_vec_StatusRecord.push_back(statusrec);
     }
     int BusVoltUpCnt=0;
     bCheckOk=m_JudgeProc.newCheckBusVoltUpExist(g_newaddata,BusVoltUpCnt);
     if(bCheckOk)
     {
         iGeneralProcCnt++;//母线电压过高
         g_strlistGeneralProc.append(m_JudgeProc.m_strBusVoltUp);
         statusrec=organizationStatusRecord(m_JudgeProc.m_strBusVoltUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
         g_vec_StatusRecord.push_back(statusrec);
     }
//     createStatusRecordFileByVector(g_vec_StatusRecord);
*/
     if(iGeneralProcCnt>0)
     {
         printf("iGeneralProcCnt=%d\n",iGeneralProcCnt);
         //-内外部保护检测结束，通知主界面,add by 2019.05.18
         QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 2000),0);
     }
     else
     {
         //-不存在内外部通用保护，通知主界面,add by 2019.05.24
          QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 3000),0);
     }
#endif

}

STR_STATUSDATA  DataReadThread::organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal)
{
    STR_STATUSDATA tmpStatusData;//由于成员变量有QString类型的，所以不能用memset函数初始化该结构体
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    QString filedate =current_date_time.toString("yyyyMMddhhmm");
    tmpStatusData.strAlarmTime=current_date;

    //保护类型
    tmpStatusData.strErrorType=strProctype;
    //输出电压有效值
    tmpStatusData.fVoltRms=fVoltVal;
    //输出电压最大值
    tmpStatusData.fVoltMax=fVoltVal*qSqrt(2.0);
    //输出电流有效值
    tmpStatusData.fCurrentRms=fCurrVal;
    //	printf("fCurrentRms=%f--i=%d\n",tmpStatusData.fCurrentRms,i);
    //输出电流最大值
    tmpStatusData.fCurrentMax=fCurrVal*qSqrt(2.0);
    return tmpStatusData;

}

void DataReadThread::readAd760601()
{
#ifdef UBUNTU_DEV //Compiler Switch
    int i,j;
        j=0;
        read(fd_ad01,ad_bf,16);
        for(i=0;i<15;i++)
        {
            ret = ((ad_bf[i])<<8)+ad_bf[i+1];
            //add by zw 2022.07.06
            if(ret >= 32767)
                ret = 0;
            if(ret&0x8000)

                ain01[j] = (10.0-((ret&0x7fff)*10.0/32767))*(-1);

            else
                ain01[j] = (ret&0x7fff)*10.0/32767;
            j++;
            i++;
        }
//        qDebug()<<ain01[0]<<"###"<<ain01[1]<<"###"<<ain01[2]<<"###"<<ain01[3]<<"###"<<ain01[4]<<"###"<<ain01[5]<<"###"<<ain01[6]<<"###"<<ain01[7];

//        ret = ((ad_bf[0])<<8)+ad_bf[1];
//        qDebug()<<ad_bf[0]<<"###"<<ad_bf[1]<<"###"<<ad_bf[2]<<"#### ret0 ="<<ret<<"####"<<"ret1 ="<<ret1<<"####";

//        if(ret&0x8000)
//        {
//            ain02_01 = (10.0-((ret&0x7fff)*10.0/32767))*(-1);
//        }
//        else
//            ain02_01 = (ret&0x7fff)*10.0/32767;
//        qDebug()<<"#### posi ="<<posi<<"####";


        if(Q0.size()>999)
            Q0.pop_front();
        if(Q1.size()>999)
            Q1.pop_front();
        if(Q2.size()>999)
            Q2.pop_front();
        if(Q3.size()>999)
            Q3.pop_front();
        if(Q4.size()>999)
            Q4.pop_front();
        if(Q5.size()>999)
            Q5.pop_front();
        if(Q6.size()>999)
            Q6.pop_front();
        if(Q7.size()>999)
            Q7.pop_front();
//        ain01[0] = g_newAdjcoef.fSlave1VolDCK*ain01[0]+g_newAdjcoef.fSlave1VolDCB;
//        ain01[1] = g_newAdjcoef.fSlave2VolDCK*ain01[1]+g_newAdjcoef.fSlave2VolDCB;
//        ain01[2] = g_newAdjcoef.fSlave3VolDCK*ain01[2]+g_newAdjcoef.fSlave3VolDCB;
//        ain01[3] = g_newAdjcoef.fSlave4VolDCK*ain01[3]+g_newAdjcoef.fSlave4VolDCB;
//        ain01[4] = g_newAdjcoef.fExcitVoltK*ain01[4]+g_newAdjcoef.fExcitVoltB;
//        ain01[5] = g_newAdjcoef.fCustom11K*ain01[5]+g_newAdjcoef.fCustom11B;
//        ain01[6] = g_newAdjcoef.fCustom12K*ain01[6]+g_newAdjcoef.fCustom12B;
        switch (m_bMuxOut)
        {
        case TPH_A:     //三相电A项直流
            ain01[7] = g_newAdjcoef.fTriPhaseAVolDCK*ain01[7]+g_newAdjcoef.fTriPhaseAVolDCB;
            break;
        case TPH_B:     //三相电B项直流
            ain01[7] = g_newAdjcoef.fTriPhaseBVolDCK*ain01[7]+g_newAdjcoef.fTriPhaseBVolDCB;
            break;
        case TPH_C:     //三相电C项直流
            ain01[7] = g_newAdjcoef.fTriPhaseCVolDCK*ain01[7]+g_newAdjcoef.fTriPhaseCVolDCB;
            break;
        default:
            break;
        }
        Q0.push_back(ain01[0]);
        Q1.push_back(ain01[1]);
        Q2.push_back(ain01[2]);
        Q3.push_back(ain01[3]);
        Q4.push_back(ain01[4]);
        Q5.push_back(ain01[5]);
        Q6.push_back(ain01[6]);
        Q7.push_back(ain01[7]);
//        qDebug()<<"#### Q.size() ="<<Q0.size()<<"####";
//        for(i=0;i<Q.size();i++)
//        {
//            qDebug()<<"#### Q["<<i<<"] ="<<Q[i]<<"####";
//        }
        readAllData();
#endif
}

void DataReadThread::readErrStatus()
{
#ifdef UBUNTU_DEV //Compiler Switch
    //振动台过位移
    g_newfaultstatus.iFaultValue[0]=ioctl(fd_err,0,VIBOD);
    if(g_newfaultstatus.iFaultValue[0] == g_newchasetdata.isw_Zdtgwy)
        g_newfaultstatus.iVIBODFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iVIBODFlag = LED_RED;
//        qDebug()<<"#### readErrStatus VIBOD err ####";
    }
    usleep(1);
    //振动台冷却故障
    g_newfaultstatus.iFaultValue[1]=ioctl(fd_err,0,VIBCU);
    if(g_newfaultstatus.iFaultValue[1] == g_newchasetdata.isw_Xtlq)
        g_newfaultstatus.iVIBCUFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iVIBCUFlag = LED_RED;
//        qDebug()<<"#### readErrStatus VIBCU err ####";
    }
    usleep(1);
    //振动过温
    g_newfaultstatus.iFaultValue[2]=ioctl(fd_err,0,VIBOT);
    if(g_newfaultstatus.iFaultValue[2] == g_newchasetdata.isw_Zdtgw)
        g_newfaultstatus.iVIBOTFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iVIBOTFlag = LED_RED;
//        qDebug()<<"#### readErrStatus VIBOT err ####";
    }
    usleep(1);
    //滑台过位移保护
    g_newfaultstatus.iFaultValue[3]=ioctl(fd_err,0,STOD);
    if(g_newfaultstatus.iFaultValue[3] == g_newchasetdata.isw_Htgwy)
        g_newfaultstatus.iSTODFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSTODFlag = LED_RED;
//        qDebug()<<"#### readErrStatus STOD err ####";
    }
    usleep(1);
    //滑台欠压
    g_newfaultstatus.iFaultValue[4]=ioctl(fd_err,0,STUP);
    if(g_newfaultstatus.iFaultValue[4] == g_newchasetdata.isw_Htqy)
        g_newfaultstatus.iSTUPFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSTUPFlag = LED_RED;
//        qDebug()<<"#### readErrStatus STUP err ####";
    }
    usleep(1);

    //滑台过温
    g_newfaultstatus.iFaultValue[5]=ioctl(fd_err,0,STOT);
    if(g_newfaultstatus.iFaultValue[5] == g_newchasetdata.isw_Htgw)
        g_newfaultstatus.iSTOTFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSTOTFlag = LED_RED;
//        qDebug()<<"#### readErrStatus STOT err ####";
    }
    usleep(1);
    //滑台欠液位
    g_newfaultstatus.iFaultValue[6]=ioctl(fd_err,0,STOL);
    if(g_newfaultstatus.iFaultValue[6] == g_newchasetdata.isw_Htqyw)
        g_newfaultstatus.iSTOLFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSTOLFlag = LED_RED;
//        qDebug()<<"#### readErrStatus STOL err ####";
    }
    usleep(1);

    //功放热继保护
    g_newfaultstatus.iFaultValue[7]=ioctl(fd_err,0,RELAY);
    if(g_newfaultstatus.iFaultValue[7] == g_newchasetdata.isw_Gfrjbh)
        g_newfaultstatus.iRELAYFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iRELAYFlag = LED_RED;
//        qDebug()<<"#### readErrStatus RELAY err ####";
    }
    usleep(1);
    //门保护
    g_newfaultstatus.iFaultValue[8]=ioctl(fd_err,0,DOOR);
    if(g_newfaultstatus.iFaultValue[8] == g_newchasetdata.isw_Zgmbh)
        g_newfaultstatus.iDOORFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iDOORFlag = LED_RED;
//        qDebug()<<"#### readErrStatus DOOR err ####";
    }
    usleep(1);
    //静压轴承欠压
    g_newfaultstatus.iFaultValue[9]=ioctl(fd_err,0,HBUP);
    if(g_newfaultstatus.iFaultValue[9] == g_newchasetdata.isw_Jyzcdy)
        g_newfaultstatus.iHBUPFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iHBUPFlag = LED_RED;
//        qDebug()<<"#### readErrStatus HBUP err ####";
    }
    usleep(1);
    //自定义1
    g_newfaultstatus.iFaultValue[10]=ioctl(fd_err,0,EXT1);
    if(g_newfaultstatus.iFaultValue[10] == g_newchasetdata.isw_Selfdef1)
        g_newfaultstatus.iEXT1Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iEXT1Flag = LED_RED;
//        qDebug()<<"#### readErrStatus EXT1 err ####";
    }
    usleep(1);

    //自定义2
    g_newfaultstatus.iFaultValue[11]=ioctl(fd_err,0,EXT2);
    if(g_newfaultstatus.iFaultValue[11] == g_newchasetdata.isw_Selfdef2)
        g_newfaultstatus.iEXT2Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iEXT2Flag = LED_RED;
//        qDebug()<<"#### readErrStatus EXT2 err ####";
    }
    usleep(1);
    //自定义3
    g_newfaultstatus.iFaultValue[12]=ioctl(fd_err,0,EXT3);
    if(g_newfaultstatus.iFaultValue[12] == g_newchasetdata.isw_Selfdef3)
        g_newfaultstatus.iEXT3Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iEXT3Flag = LED_RED;
//        qDebug()<<"#### readErrStatus EXT3 err ####";
    }
    usleep(1);
    //自定义4
    g_newfaultstatus.iFaultValue[13]=ioctl(fd_err,0,EXT4);
    if(g_newfaultstatus.iFaultValue[13] == g_newchasetdata.isw_Selfdef4)
        g_newfaultstatus.iEXT4Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iEXT4Flag = LED_RED;
//        qDebug()<<"#### readErrStatus EXT4 err ####";
    }
    usleep(1);
    //紧急停机
    g_newfaultstatus.iFaultValue[14]=ioctl(fd_err,0,ESTOP);
    if(g_newfaultstatus.iFaultValue[14] == g_newchasetdata.isw_Jjtj)
        g_newfaultstatus.iESTOPFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iESTOPFlag = LED_RED;
//        qDebug()<<"#### readErrStatus ESTOP err ####";
    }
    usleep(1);

    //从柜1整流桥过温1
    g_newfaultstatus.iFaultValue[15]=ioctl(fd_err,0,OT1);
    if(g_newfaultstatus.iFaultValue[15] == g_newchasetdata.isw_C1zlqgw)
        g_newfaultstatus.iOT1Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iOT1Flag = LED_RED;
//        qDebug()<<"#### readErrStatus OT1 err ####";
    }
    usleep(1);
    //从柜1整流桥过温2
    g_newfaultstatus.iFaultValue[16]=ioctl(fd_err,0,OT2);
    if(g_newfaultstatus.iFaultValue[16] == g_newchasetdata.isw_C2zlqgw)
        g_newfaultstatus.iOT2Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iOT2Flag = LED_RED;
//        qDebug()<<"#### readErrStatus OT2 err ####";
    }
    usleep(1);
    //从柜1整流桥过温3
    g_newfaultstatus.iFaultValue[17]=ioctl(fd_err,0,OT3);
    if(g_newfaultstatus.iFaultValue[17] == g_newchasetdata.isw_C3zlqgw)
        g_newfaultstatus.iOT3Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iOT3Flag = LED_RED;
//        qDebug()<<"#### readErrStatus OT3 err ####";
    }
    usleep(1);
    //从柜1整流桥过温4
    g_newfaultstatus.iFaultValue[18]=ioctl(fd_err,0,OT4);
    if(g_newfaultstatus.iFaultValue[18] == g_newchasetdata.isw_C4zlqgw)
        g_newfaultstatus.iOT4Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iOT4Flag = LED_RED;
//        qDebug()<<"#### readErrStatus OT4 err ####";
    }
    usleep(1);
    //S紧急停机
    g_newfaultstatus.iFaultValue[19]=ioctl(fd_err,0,SESTOP);
    if(g_newfaultstatus.iFaultValue[19] == g_newchasetdata.isw_SJiti)
        g_newfaultstatus.iSESTOPFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSESTOPFlag = LED_RED;
//        qDebug()<<"#### readErrStatus SESTOP err ####";
    }
    usleep(1);

    //从柜1错误信号
    g_newfaultstatus.iFaultValue[20]=ioctl(fd_err,0,FAULT1);
    if(g_newfaultstatus.iFaultValue[20] == g_newchasetdata.isw_C1cwbh)
        g_newfaultstatus.iFAULT1Flag = LED_RED;
    else
    {
        g_newfaultstatus.iFAULT1Flag = LED_GREEN;
//        qDebug()<<"#### readErrStatus FAULT1 err ####";
    }
    usleep(1);
    //从柜2错误信号
    g_newfaultstatus.iFaultValue[21]=ioctl(fd_err,0,FAULT2);
    if(g_newfaultstatus.iFaultValue[21] == g_newchasetdata.isw_C2cwbh)
        g_newfaultstatus.iFAULT2Flag = LED_RED;
    else
    {
        g_newfaultstatus.iFAULT2Flag = LED_GREEN;
//        qDebug()<<"#### readErrStatus FAULT2 err ####";
    }
    usleep(1);
    //从柜3错误信号
    g_newfaultstatus.iFaultValue[22]=ioctl(fd_err,0,FAULT3);
    if(g_newfaultstatus.iFaultValue[22] == g_newchasetdata.isw_C3cwbh)
        g_newfaultstatus.iFAULT3Flag = LED_RED;
    else
    {
        g_newfaultstatus.iFAULT3Flag = LED_GREEN;
//        qDebug()<<"#### readErrStatus FAULT3 err ####";
    }
    usleep(1);
    //从柜4错误信号
    g_newfaultstatus.iFaultValue[23]=ioctl(fd_err,0,FAULT4);
    if(g_newfaultstatus.iFaultValue[23] == g_newchasetdata.isw_C4cwbh)
        g_newfaultstatus.iFAULT4Flag = LED_RED;
    else
    {
        g_newfaultstatus.iFAULT4Flag = LED_GREEN;
//        qDebug()<<"#### readErrStatus FAULT4 err ####";
    }
    usleep(1);
    //VOL- for test
    g_newfaultstatus.iFaultValue[24]=ioctl(fd_err,0,KEYCOL6);

#endif
}

void DataReadThread::readAllData()
{   //从柜1母线电压直流
    g_newaddata.fSlave1VolDC = ain01[0]*ADK100;
    //从柜2母线电压直流
    g_newaddata.fSlave2VolDC = ain01[1]*ADK101;
    //从柜3母线电压直流
    g_newaddata.fSlave3VolDC = ain01[2]*ADK102;
    //从柜4母线电压直流
    g_newaddata.fSlave4VolDC = ain01[3]*ADK103;
    //励磁电压直流
    g_newaddata.fExcitVolt = ain01[4]*ADK104;
    //外部预留11
    g_newaddata.fCustom11 = ain01[5]*ADK105;
    //外部预留12
    g_newaddata.fCustom12 = ain01[6]*ADK106;
    //三相电直流
    switch (m_bMuxOut)
    {
    case TPH_A:     //三相电A项直流
        g_newaddata.fTriPhaseAVolDC = ain01[7]*ADK107A;
        break;
    case TPH_B:     //三相电B项直流
        g_newaddata.fTriPhaseBVolDC = ain01[7]*ADK107B;
        break;
    case TPH_C:     //三相电C项直流
        g_newaddata.fTriPhaseCVolDC = ain01[7]*ADK107C;
        break;
    default:
        break;
    }
    //总电压交流
    g_newaddata.fTotalVolAC = i_pGPIOdataThread->ain02[0]*ADK200;
    //总电压直流
    g_newaddata.fTotalVolDC = i_pGPIOdataThread->ain02[1]*ADK201;
    //从柜1电流直流
    g_newaddata.fSlave1CurDC = i_pGPIOdataThread->ain02[2]*ADK202;
    //从柜2电流直流
    g_newaddata.fSlave2CurDC = i_pGPIOdataThread->ain02[3]*ADK203;
    //从柜3电流直流
    g_newaddata.fSlave3CurDC = i_pGPIOdataThread->ain02[4]*ADK204;
    //从柜4电流直流
    g_newaddata.fSlave4CurDC = i_pGPIOdataThread->ain02[5]*ADK205;
    //从柜总电流直流
    g_newaddata.fTotalSlaveCurAC = i_pGPIOdataThread->ain02[6]*ADK206;
    //励磁电流直流
    g_newaddata.fExcitCur = i_pGPIOdataThread->ain02[7]*ADK207;
}

void DataReadThread::choseMuxOut(int trip)
{
#ifdef UBUNTU_DEV
//    printf("DataReadThread::choseMuxOut\n");
    //MUX_OUT 选择------三相电直流
    switch (trip)
    {
    case TPH_A:     //三相电A项直流
        ioctl(fd_out,0,MUX_A0);
        usleep(10);
        ioctl(fd_out,0,MUX_A1);
        usleep(10);
        break;
    case TPH_B:     //三相电B项直流
        ioctl(fd_out,1,MUX_A0);
        usleep(10);
        ioctl(fd_out,0,MUX_A1);
        usleep(10);
        break;
    case TPH_C:     //三相电C项直流
        ioctl(fd_out,0,MUX_A0);
        usleep(10);
        ioctl(fd_out,1,MUX_A1);
        usleep(10);
        break;
    default:
        break;
    }
#endif
}

//创建状态记录文件(单个文件考虑)--vector,add by 2020.09.05******
void DataReadThread::createStatusRecordFileByVector(QVector<STR_STATUSDATA>vec_strusdata)
{
    STR_STATUSDATA tmpStatusData;
    printf("strusdata.size=%d\n",vec_strusdata.size());
    if(vec_strusdata.size()==0)//防误20190716
    {
        return;
    }
#ifdef WIN_DEV
    QString m_strStafilepath= "./debug/statusdata/statusdata.csv";
#else
    QString m_strStafilepath=QApplication::applicationDirPath() + "/statusdata/statusdata.csv";
#endif

     printf("createStatusRecordFileByList:%s\n",m_strStafilepath.toStdString().data());
    if(!m_strStafilepath.contains(tr("/statusdata/statusdata.csv")))
     {
             printf("no /statusdata/statusdata.csv path exist\n");
             return;
    }
    QFile file(m_strStafilepath);
    if (!file.open(QFile::WriteOnly | QFile::Append))//文件追加写入
        {
             printf("##createStatusRecordFileByList:file.open error\n");
             return;
         }
         QTextStream out(&file);
         out.setCodec("GB2312");
         QStringList datafilelist;
         QString strTemp;

         for(int j=0;j<vec_strusdata.size();j++)
         {
             tmpStatusData=vec_strusdata.at(j);
             datafilelist.clear();
             //报警时间
             datafilelist.append(tmpStatusData.strAlarmTime);
             datafilelist.append(tr(","));
             printf("j=%d--strAlarmTime=%s\n",j,tmpStatusData.strAlarmTime.toStdString().data());
             //错误(保护)类型
             datafilelist.append(tmpStatusData.strErrorType);
             datafilelist.append(tr(","));
             printf("j=%d--strErrorType=%s\n",j,tmpStatusData.strErrorType.toStdString().data());
             //输出电压有效值
             strTemp= QString::number(tmpStatusData.fVoltRms,'f',2);
             datafilelist.append(strTemp);
             datafilelist.append(tr(","));
             printf("j=%d--fVoltRms=%s\n",j,strTemp.toStdString().data());
             //输出电压最大值
             strTemp= QString::number(tmpStatusData.fVoltMax,'f',2);
             datafilelist.append(strTemp);
             datafilelist.append(tr(","));
             printf("j=%d--fVoltMax=%s\n",j,strTemp.toStdString().data());
             //输出电流有效值
             strTemp= QString::number(tmpStatusData.fCurrentRms,'f',2);
             datafilelist.append(strTemp);
             datafilelist.append(tr(","));
             printf("j=%d--fCurrentRms=%s\n",j,strTemp.toStdString().data());
             //输出电流最大值
             strTemp= QString::number(tmpStatusData.fCurrentMax,'f',2);
             datafilelist.append(strTemp);
             printf("j=%d--fCurrentMax=%s\n",j,strTemp.toStdString().data());
             out << datafilelist.at(0) << datafilelist.at(1)<< datafilelist.at(2)<< datafilelist.at(3)<< datafilelist.at(4)<< datafilelist.at(5)<< datafilelist.at(6)<< datafilelist.at(7)<< datafilelist.at(8)<<datafilelist.at(9)<< datafilelist.at(10)<<"\n";
         }// for(int j=0;j<tmpVecStaData.size();j++)
         file.close();
         //通知主界面线程最新文件已写完，可以读取
         QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 5000),0);
     //}
}










