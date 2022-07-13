/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: DataReadThread.cpp
** ժҪ: GPIO���ݽ����߳���
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2018.11.01
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2018.11.01   V1.0      ����
** ������      2019.07.13   V1.1      �޸ġ�����
** ����        20220223     V1.2      ����gpiodatarecvthread�½���AD760601��ȡ���ݺʹ��������߳�
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
        //AD7606-01�ɼ����ʿ���

        usleep(99900);  //10Hz 99900/100 50000/50000
        ioctl(fd_out,1,AD01_CA);  //��ʼADת����ͬʱ��ȡ�ϴ�ת�����
        usleep(100);
        readAd760601();
        ioctl(fd_out,0,AD01_CA);
        //qDebug()<<"#### DataReadThread::run() ####";
        //AD7606-01�ɼ����ʿ���
//        usleep(2000000);//���Կ�������
    }
#endif //Compiler Switch
}
//end add by zw 20220223

void DataReadThread::handleData()
{
#ifdef UBUNTU_DEV //Compiler Switch
       //����Ƿ�����ⲿ����
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
        iGeneralProcCnt++;//�ӹ��ű���
        g_strlistGeneralProc.append(m_JudgeProc.m_strSubmbh);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strSubmbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     bCheckOk=m_JudgeProc.newCheckSubRectBridgeOverheat(g_newchasetdata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//�ӹ������Ź���
        g_strlistGeneralProc.append(m_JudgeProc.m_strSubzlqgw);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strSubzlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     m_JudgeProc.newCheckExcitVolExist();//������ŵ�ѹ��������ָʾ��

     /*
     bCheckOk=m_JudgeProc.newCheckVoltImbalance(g_newaddata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//�����ѹ��ƽ��
        g_strlistGeneralProc.append(m_JudgeProc.m_strVoltUnbalance);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltUnbalance,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     bCheckOk=m_JudgeProc.newCheckOverVolt(g_newaddata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//�����ѹ����
        g_strlistGeneralProc.append(m_JudgeProc.m_strVoltUp);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     bCheckOk=m_JudgeProc.newCheckLowVolt(g_newaddata);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//�����ѹ����
        g_strlistGeneralProc.append(m_JudgeProc.m_strVoltDown);
        statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltDown,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
     }
     if((g_newaddata.fTotalVolAC-g_struBasicPara.fTotalvoltUp)>DELT_FVALUE)
     {
         iGeneralProcCnt++;//�����������ѹ����
         g_strlistGeneralProc.append(m_JudgeProc.m_strOutVoltUp);
         statusrec=organizationStatusRecord(m_JudgeProc.m_strOutVoltUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
         g_vec_StatusRecord.push_back(statusrec);
     }
     int iCurrOverCnt=0;
     bCheckOk=m_JudgeProc.newCheckOutputCurrentOver(g_newaddata,iCurrOverCnt);
     if(bCheckOk)
     {
         iGeneralProcCnt++;//�ֹ������������
         g_strlistGeneralProc.append(m_JudgeProc.m_strSubCurrentUp);
         statusrec=organizationStatusRecord(m_JudgeProc.m_strSubCurrentUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
         g_vec_StatusRecord.push_back(statusrec);
     }
     if((g_newaddata.fTotalSlaveCurAC-g_struBasicPara.fTotalcurrentUp)>DELT_FVALUE)
     {
         iGeneralProcCnt++;//�����������������
         g_strlistGeneralProc.append(m_JudgeProc.m_strOutCurrentUp);
         statusrec=organizationStatusRecord(m_JudgeProc.m_strOutCurrentUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
         g_vec_StatusRecord.push_back(statusrec);
     }
     int BusVoltUpCnt=0;
     bCheckOk=m_JudgeProc.newCheckBusVoltUpExist(g_newaddata,BusVoltUpCnt);
     if(bCheckOk)
     {
         iGeneralProcCnt++;//ĸ�ߵ�ѹ����
         g_strlistGeneralProc.append(m_JudgeProc.m_strBusVoltUp);
         statusrec=organizationStatusRecord(m_JudgeProc.m_strBusVoltUp,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
         g_vec_StatusRecord.push_back(statusrec);
     }
//     createStatusRecordFileByVector(g_vec_StatusRecord);
*/
     if(iGeneralProcCnt>0)
     {
         printf("iGeneralProcCnt=%d\n",iGeneralProcCnt);
         //-���ⲿ������������֪ͨ������,add by 2019.05.18
         QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 2000),0);
     }
     else
     {
         //-���������ⲿͨ�ñ�����֪ͨ������,add by 2019.05.24
          QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 3000),0);
     }
#endif

}

STR_STATUSDATA  DataReadThread::organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal)
{
    STR_STATUSDATA tmpStatusData;//���ڳ�Ա������QString���͵ģ����Բ�����memset������ʼ���ýṹ��
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    QString filedate =current_date_time.toString("yyyyMMddhhmm");
    tmpStatusData.strAlarmTime=current_date;

    //��������
    tmpStatusData.strErrorType=strProctype;
    //�����ѹ��Чֵ
    tmpStatusData.fVoltRms=fVoltVal;
    //�����ѹ���ֵ
    tmpStatusData.fVoltMax=fVoltVal*qSqrt(2.0);
    //���������Чֵ
    tmpStatusData.fCurrentRms=fCurrVal;
    //	printf("fCurrentRms=%f--i=%d\n",tmpStatusData.fCurrentRms,i);
    //����������ֵ
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
        case TPH_A:     //�����A��ֱ��
            ain01[7] = g_newAdjcoef.fTriPhaseAVolDCK*ain01[7]+g_newAdjcoef.fTriPhaseAVolDCB;
            break;
        case TPH_B:     //�����B��ֱ��
            ain01[7] = g_newAdjcoef.fTriPhaseBVolDCK*ain01[7]+g_newAdjcoef.fTriPhaseBVolDCB;
            break;
        case TPH_C:     //�����C��ֱ��
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
    //��̨��λ��
    g_newfaultstatus.iFaultValue[0]=ioctl(fd_err,0,VIBOD);
    if(g_newfaultstatus.iFaultValue[0] == g_newchasetdata.isw_Zdtgwy)
        g_newfaultstatus.iVIBODFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iVIBODFlag = LED_RED;
//        qDebug()<<"#### readErrStatus VIBOD err ####";
    }
    usleep(1);
    //��̨��ȴ����
    g_newfaultstatus.iFaultValue[1]=ioctl(fd_err,0,VIBCU);
    if(g_newfaultstatus.iFaultValue[1] == g_newchasetdata.isw_Xtlq)
        g_newfaultstatus.iVIBCUFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iVIBCUFlag = LED_RED;
//        qDebug()<<"#### readErrStatus VIBCU err ####";
    }
    usleep(1);
    //�񶯹���
    g_newfaultstatus.iFaultValue[2]=ioctl(fd_err,0,VIBOT);
    if(g_newfaultstatus.iFaultValue[2] == g_newchasetdata.isw_Zdtgw)
        g_newfaultstatus.iVIBOTFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iVIBOTFlag = LED_RED;
//        qDebug()<<"#### readErrStatus VIBOT err ####";
    }
    usleep(1);
    //��̨��λ�Ʊ���
    g_newfaultstatus.iFaultValue[3]=ioctl(fd_err,0,STOD);
    if(g_newfaultstatus.iFaultValue[3] == g_newchasetdata.isw_Htgwy)
        g_newfaultstatus.iSTODFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSTODFlag = LED_RED;
//        qDebug()<<"#### readErrStatus STOD err ####";
    }
    usleep(1);
    //��̨Ƿѹ
    g_newfaultstatus.iFaultValue[4]=ioctl(fd_err,0,STUP);
    if(g_newfaultstatus.iFaultValue[4] == g_newchasetdata.isw_Htqy)
        g_newfaultstatus.iSTUPFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSTUPFlag = LED_RED;
//        qDebug()<<"#### readErrStatus STUP err ####";
    }
    usleep(1);

    //��̨����
    g_newfaultstatus.iFaultValue[5]=ioctl(fd_err,0,STOT);
    if(g_newfaultstatus.iFaultValue[5] == g_newchasetdata.isw_Htgw)
        g_newfaultstatus.iSTOTFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSTOTFlag = LED_RED;
//        qDebug()<<"#### readErrStatus STOT err ####";
    }
    usleep(1);
    //��̨ǷҺλ
    g_newfaultstatus.iFaultValue[6]=ioctl(fd_err,0,STOL);
    if(g_newfaultstatus.iFaultValue[6] == g_newchasetdata.isw_Htqyw)
        g_newfaultstatus.iSTOLFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSTOLFlag = LED_RED;
//        qDebug()<<"#### readErrStatus STOL err ####";
    }
    usleep(1);

    //�����ȼ̱���
    g_newfaultstatus.iFaultValue[7]=ioctl(fd_err,0,RELAY);
    if(g_newfaultstatus.iFaultValue[7] == g_newchasetdata.isw_Gfrjbh)
        g_newfaultstatus.iRELAYFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iRELAYFlag = LED_RED;
//        qDebug()<<"#### readErrStatus RELAY err ####";
    }
    usleep(1);
    //�ű���
    g_newfaultstatus.iFaultValue[8]=ioctl(fd_err,0,DOOR);
    if(g_newfaultstatus.iFaultValue[8] == g_newchasetdata.isw_Zgmbh)
        g_newfaultstatus.iDOORFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iDOORFlag = LED_RED;
//        qDebug()<<"#### readErrStatus DOOR err ####";
    }
    usleep(1);
    //��ѹ���Ƿѹ
    g_newfaultstatus.iFaultValue[9]=ioctl(fd_err,0,HBUP);
    if(g_newfaultstatus.iFaultValue[9] == g_newchasetdata.isw_Jyzcdy)
        g_newfaultstatus.iHBUPFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iHBUPFlag = LED_RED;
//        qDebug()<<"#### readErrStatus HBUP err ####";
    }
    usleep(1);
    //�Զ���1
    g_newfaultstatus.iFaultValue[10]=ioctl(fd_err,0,EXT1);
    if(g_newfaultstatus.iFaultValue[10] == g_newchasetdata.isw_Selfdef1)
        g_newfaultstatus.iEXT1Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iEXT1Flag = LED_RED;
//        qDebug()<<"#### readErrStatus EXT1 err ####";
    }
    usleep(1);

    //�Զ���2
    g_newfaultstatus.iFaultValue[11]=ioctl(fd_err,0,EXT2);
    if(g_newfaultstatus.iFaultValue[11] == g_newchasetdata.isw_Selfdef2)
        g_newfaultstatus.iEXT2Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iEXT2Flag = LED_RED;
//        qDebug()<<"#### readErrStatus EXT2 err ####";
    }
    usleep(1);
    //�Զ���3
    g_newfaultstatus.iFaultValue[12]=ioctl(fd_err,0,EXT3);
    if(g_newfaultstatus.iFaultValue[12] == g_newchasetdata.isw_Selfdef3)
        g_newfaultstatus.iEXT3Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iEXT3Flag = LED_RED;
//        qDebug()<<"#### readErrStatus EXT3 err ####";
    }
    usleep(1);
    //�Զ���4
    g_newfaultstatus.iFaultValue[13]=ioctl(fd_err,0,EXT4);
    if(g_newfaultstatus.iFaultValue[13] == g_newchasetdata.isw_Selfdef4)
        g_newfaultstatus.iEXT4Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iEXT4Flag = LED_RED;
//        qDebug()<<"#### readErrStatus EXT4 err ####";
    }
    usleep(1);
    //����ͣ��
    g_newfaultstatus.iFaultValue[14]=ioctl(fd_err,0,ESTOP);
    if(g_newfaultstatus.iFaultValue[14] == g_newchasetdata.isw_Jjtj)
        g_newfaultstatus.iESTOPFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iESTOPFlag = LED_RED;
//        qDebug()<<"#### readErrStatus ESTOP err ####";
    }
    usleep(1);

    //�ӹ�1�����Ź���1
    g_newfaultstatus.iFaultValue[15]=ioctl(fd_err,0,OT1);
    if(g_newfaultstatus.iFaultValue[15] == g_newchasetdata.isw_C1zlqgw)
        g_newfaultstatus.iOT1Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iOT1Flag = LED_RED;
//        qDebug()<<"#### readErrStatus OT1 err ####";
    }
    usleep(1);
    //�ӹ�1�����Ź���2
    g_newfaultstatus.iFaultValue[16]=ioctl(fd_err,0,OT2);
    if(g_newfaultstatus.iFaultValue[16] == g_newchasetdata.isw_C2zlqgw)
        g_newfaultstatus.iOT2Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iOT2Flag = LED_RED;
//        qDebug()<<"#### readErrStatus OT2 err ####";
    }
    usleep(1);
    //�ӹ�1�����Ź���3
    g_newfaultstatus.iFaultValue[17]=ioctl(fd_err,0,OT3);
    if(g_newfaultstatus.iFaultValue[17] == g_newchasetdata.isw_C3zlqgw)
        g_newfaultstatus.iOT3Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iOT3Flag = LED_RED;
//        qDebug()<<"#### readErrStatus OT3 err ####";
    }
    usleep(1);
    //�ӹ�1�����Ź���4
    g_newfaultstatus.iFaultValue[18]=ioctl(fd_err,0,OT4);
    if(g_newfaultstatus.iFaultValue[18] == g_newchasetdata.isw_C4zlqgw)
        g_newfaultstatus.iOT4Flag = LED_GREEN;
    else
    {
        g_newfaultstatus.iOT4Flag = LED_RED;
//        qDebug()<<"#### readErrStatus OT4 err ####";
    }
    usleep(1);
    //S����ͣ��
    g_newfaultstatus.iFaultValue[19]=ioctl(fd_err,0,SESTOP);
    if(g_newfaultstatus.iFaultValue[19] == g_newchasetdata.isw_SJiti)
        g_newfaultstatus.iSESTOPFlag = LED_GREEN;
    else
    {
        g_newfaultstatus.iSESTOPFlag = LED_RED;
//        qDebug()<<"#### readErrStatus SESTOP err ####";
    }
    usleep(1);

    //�ӹ�1�����ź�
    g_newfaultstatus.iFaultValue[20]=ioctl(fd_err,0,FAULT1);
    if(g_newfaultstatus.iFaultValue[20] == g_newchasetdata.isw_C1cwbh)
        g_newfaultstatus.iFAULT1Flag = LED_RED;
    else
    {
        g_newfaultstatus.iFAULT1Flag = LED_GREEN;
//        qDebug()<<"#### readErrStatus FAULT1 err ####";
    }
    usleep(1);
    //�ӹ�2�����ź�
    g_newfaultstatus.iFaultValue[21]=ioctl(fd_err,0,FAULT2);
    if(g_newfaultstatus.iFaultValue[21] == g_newchasetdata.isw_C2cwbh)
        g_newfaultstatus.iFAULT2Flag = LED_RED;
    else
    {
        g_newfaultstatus.iFAULT2Flag = LED_GREEN;
//        qDebug()<<"#### readErrStatus FAULT2 err ####";
    }
    usleep(1);
    //�ӹ�3�����ź�
    g_newfaultstatus.iFaultValue[22]=ioctl(fd_err,0,FAULT3);
    if(g_newfaultstatus.iFaultValue[22] == g_newchasetdata.isw_C3cwbh)
        g_newfaultstatus.iFAULT3Flag = LED_RED;
    else
    {
        g_newfaultstatus.iFAULT3Flag = LED_GREEN;
//        qDebug()<<"#### readErrStatus FAULT3 err ####";
    }
    usleep(1);
    //�ӹ�4�����ź�
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
{   //�ӹ�1ĸ�ߵ�ѹֱ��
    g_newaddata.fSlave1VolDC = ain01[0]*ADK100;
    //�ӹ�2ĸ�ߵ�ѹֱ��
    g_newaddata.fSlave2VolDC = ain01[1]*ADK101;
    //�ӹ�3ĸ�ߵ�ѹֱ��
    g_newaddata.fSlave3VolDC = ain01[2]*ADK102;
    //�ӹ�4ĸ�ߵ�ѹֱ��
    g_newaddata.fSlave4VolDC = ain01[3]*ADK103;
    //���ŵ�ѹֱ��
    g_newaddata.fExcitVolt = ain01[4]*ADK104;
    //�ⲿԤ��11
    g_newaddata.fCustom11 = ain01[5]*ADK105;
    //�ⲿԤ��12
    g_newaddata.fCustom12 = ain01[6]*ADK106;
    //�����ֱ��
    switch (m_bMuxOut)
    {
    case TPH_A:     //�����A��ֱ��
        g_newaddata.fTriPhaseAVolDC = ain01[7]*ADK107A;
        break;
    case TPH_B:     //�����B��ֱ��
        g_newaddata.fTriPhaseBVolDC = ain01[7]*ADK107B;
        break;
    case TPH_C:     //�����C��ֱ��
        g_newaddata.fTriPhaseCVolDC = ain01[7]*ADK107C;
        break;
    default:
        break;
    }
    //�ܵ�ѹ����
    g_newaddata.fTotalVolAC = i_pGPIOdataThread->ain02[0]*ADK200;
    //�ܵ�ѹֱ��
    g_newaddata.fTotalVolDC = i_pGPIOdataThread->ain02[1]*ADK201;
    //�ӹ�1����ֱ��
    g_newaddata.fSlave1CurDC = i_pGPIOdataThread->ain02[2]*ADK202;
    //�ӹ�2����ֱ��
    g_newaddata.fSlave2CurDC = i_pGPIOdataThread->ain02[3]*ADK203;
    //�ӹ�3����ֱ��
    g_newaddata.fSlave3CurDC = i_pGPIOdataThread->ain02[4]*ADK204;
    //�ӹ�4����ֱ��
    g_newaddata.fSlave4CurDC = i_pGPIOdataThread->ain02[5]*ADK205;
    //�ӹ��ܵ���ֱ��
    g_newaddata.fTotalSlaveCurAC = i_pGPIOdataThread->ain02[6]*ADK206;
    //���ŵ���ֱ��
    g_newaddata.fExcitCur = i_pGPIOdataThread->ain02[7]*ADK207;
}

void DataReadThread::choseMuxOut(int trip)
{
#ifdef UBUNTU_DEV
//    printf("DataReadThread::choseMuxOut\n");
    //MUX_OUT ѡ��------�����ֱ��
    switch (trip)
    {
    case TPH_A:     //�����A��ֱ��
        ioctl(fd_out,0,MUX_A0);
        usleep(10);
        ioctl(fd_out,0,MUX_A1);
        usleep(10);
        break;
    case TPH_B:     //�����B��ֱ��
        ioctl(fd_out,1,MUX_A0);
        usleep(10);
        ioctl(fd_out,0,MUX_A1);
        usleep(10);
        break;
    case TPH_C:     //�����C��ֱ��
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

//����״̬��¼�ļ�(�����ļ�����)--vector,add by 2020.09.05******
void DataReadThread::createStatusRecordFileByVector(QVector<STR_STATUSDATA>vec_strusdata)
{
    STR_STATUSDATA tmpStatusData;
    printf("strusdata.size=%d\n",vec_strusdata.size());
    if(vec_strusdata.size()==0)//����20190716
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
    if (!file.open(QFile::WriteOnly | QFile::Append))//�ļ�׷��д��
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
             //����ʱ��
             datafilelist.append(tmpStatusData.strAlarmTime);
             datafilelist.append(tr(","));
             printf("j=%d--strAlarmTime=%s\n",j,tmpStatusData.strAlarmTime.toStdString().data());
             //����(����)����
             datafilelist.append(tmpStatusData.strErrorType);
             datafilelist.append(tr(","));
             printf("j=%d--strErrorType=%s\n",j,tmpStatusData.strErrorType.toStdString().data());
             //�����ѹ��Чֵ
             strTemp= QString::number(tmpStatusData.fVoltRms,'f',2);
             datafilelist.append(strTemp);
             datafilelist.append(tr(","));
             printf("j=%d--fVoltRms=%s\n",j,strTemp.toStdString().data());
             //�����ѹ���ֵ
             strTemp= QString::number(tmpStatusData.fVoltMax,'f',2);
             datafilelist.append(strTemp);
             datafilelist.append(tr(","));
             printf("j=%d--fVoltMax=%s\n",j,strTemp.toStdString().data());
             //���������Чֵ
             strTemp= QString::number(tmpStatusData.fCurrentRms,'f',2);
             datafilelist.append(strTemp);
             datafilelist.append(tr(","));
             printf("j=%d--fCurrentRms=%s\n",j,strTemp.toStdString().data());
             //����������ֵ
             strTemp= QString::number(tmpStatusData.fCurrentMax,'f',2);
             datafilelist.append(strTemp);
             printf("j=%d--fCurrentMax=%s\n",j,strTemp.toStdString().data());
             out << datafilelist.at(0) << datafilelist.at(1)<< datafilelist.at(2)<< datafilelist.at(3)<< datafilelist.at(4)<< datafilelist.at(5)<< datafilelist.at(6)<< datafilelist.at(7)<< datafilelist.at(8)<<datafilelist.at(9)<< datafilelist.at(10)<<"\n";
         }// for(int j=0;j<tmpVecStaData.size();j++)
         file.close();
         //֪ͨ�������߳������ļ���д�꣬���Զ�ȡ
         QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 5000),0);
     //}
}










