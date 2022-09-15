/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: gpiodatarecvThread.cpp
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
****************************************************************************/
#include "gpiodatarecvthread.h"
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

STR_GPIODATA g_GPIOData;
STRU_CHAINSETDATA g_ChainSetData;       //add by 2019.05.14
QStringList  g_strlistGeneralProc;      //add by 2019.05.14

QVector<STR_STATUSDATA>g_vec_StatusRecord;//2020.09.05


STRU_SIMUPROCSET g_SimuProcSet;         //add by 2019.05.23
extern STRU_BASICPARA g_struBasicPara;  //add by 2019.05.28
extern STRU_ADJCOEF g_struAdjcoef;//add by 2019.07.09

QMutex g_Mutex;//add by 2019.05.27
//add by zw 20220223
extern STRU_NEWADJCOEF g_newAdjcoef;
extern STRU_NEWCHASETDATA g_newchasetdata;
//end add by zw 20220223

GPIODataRecvThread::GPIODataRecvThread(QWidget * ptr,int nfd)
{
    m_pReceiver = ptr;
    m_bStopped= false;
    m_ifd=nfd;
    m_bCreateStafileflag=false;
    m_iGfstartflag=false;
    pwm2Freq = 10000;
    displyCnt = pwm2Freq/5;
    printf("GPIODataRecvThread::GPIODataRecvThread\n");
}
GPIODataRecvThread::~GPIODataRecvThread()
{
}
void GPIODataRecvThread::restart()
{
    m_bStopped = false;
    wait();
    start();
}
void GPIODataRecvThread::stop()
{
    m_bStopped = true;
    wait();
}
//��ʼ��GPIO���ݱ���,add by 2019.07.14
void GPIODataRecvThread::initGPIOData()
{
      //��ʼ��
      memset(&g_GPIOData,0,sizeof(g_GPIOData));
      for(int i=0;i<4;i++)
      {
         //�ӹ�����״̬����ʼ��
        g_GPIOData.iSlaveStaValue[i]=-1;
      }
      //����״̬����ʼ��
       g_GPIOData.iRunningState=-1;
       g_GPIOData.iCoolingState=-1;
       g_GPIOData.iExcitationState=-1;
       g_GPIOData.iReadyState=-1;
       g_GPIOData.iGainState=-1;
       g_GPIOData.iFaultState=-1;
     for(int j=0;j<MAX_SIZE;j++)
     {
         //���ӹ񿪹�����ʼ��
         g_GPIOData.iMasterDI[j]=-1;
         g_GPIOData.iSlaveDI[j]=-1;
     }
     g_strlistGeneralProc.clear();
     g_vec_StatusRecord.clear();//add by 2020.09.05
}
//void GPIODataRecvThread::run()
//{
//#ifdef UBUNTU_DEV //Compiler Switch
//    initGPIOData();
//    while (!m_bStopped)
//    {
//        readData();
//        usleep(100);
//        if(m_iGfstartflag)
//        {
//            handleData();
//        }
//        usleep(DELAY_TIME*1000);//����Ϊ100ms��ʱ,add by 2019.05.26
//        //add by zw 20220223
//        readAd760602();
//        //end add
//    }//while (!m_bStopped)
//#endif //Compiler Switch
//}

// add by zw 20220223
void GPIODataRecvThread::run()
{
    int tcnt = 0;
#ifdef UBUNTU_DEV //Compiler Switch
    initGPIOData();
    while (!m_bStopped)
    {
        if(tcnt > displyCnt)
        {
            QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 1000),0);
            tcnt = 0;
        }
        readAd760602();
        tcnt++;
    }//while (!m_bStopped)
#endif //Compiler Switch
}
//end add by zw 20220223



//��ȡ����,add by zqc 2019.07.13
void GPIODataRecvThread::readData()
{
    /*
    //��ȡ�汾����
    readVersionData();
    usleep(100);
    //��ȡ����DI״̬����
    readMasterDIData();
    usleep(100);
    //��ȡ�ӹ�DI״̬����
    readSlaveDIData();
    usleep(100);
    //��ȡ����-���ŵ�ѹ
    readExcitVoltData();
    usleep(100);
    //��ȡ����-���ŵ���
    readExcitCurrentData();
    usleep(100);
    //��ȡ�����ѹ����
    readThreePhaseVoltData();
    usleep(100);
    //��ȡ4���ӹ��ѹ����
    readSlaveVoltData();
    usleep(100);
    //��ȡ4���ӹ��������
    readSlaveCurrentData();
    usleep(100);
     //��ȡ4���ӹ�ĸ�ߵ�ѹ����
    readSlaveBusVoltData();
    usleep(100);
     //��ȡ4���ӹ���ĸ�ߵ�ѹ����
    readSlaveActBusVoltData();
    usleep(100);
    //��ȡ4���ӹ�ĸ�ߵ�ѹ����
    readSlaveRegBusVoltData();
    usleep(100);
    //��ȡֱ��5V����
    readDC5VData();
    usleep(100);
    QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 1000),0);
    //SendGPIOMesg();
    */
    usleep(2000);
    QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 1000),0);
}
//�������ݲ�֪ͨ�������߳�,add by zqc 2019.07.13
void GPIODataRecvThread::handleData()
{
#ifdef UBUNTU_DEV //Compiler Switch
       //����Ƿ�����ⲿ����,add by 2019.05.17
      g_strlistGeneralProc.clear();
      g_vec_StatusRecord.clear();//add by 2020.09.
      STR_STATUSDATA statusrec;
      int iGeneralProcCnt=0;
      bool bCheckOk=false;
      bool bIsExterProcExist=false;
      //buffer_read is modified by g_GPIOData.iMasterDI 2019.07.13 ???
     bIsExterProcExist=m_JudgeProc.CheckExterProcExist(g_GPIOData.iMasterDI,g_ChainSetData,g_strlistGeneralProc);
     if(bIsExterProcExist)
     {
        printf("bIsExterProcExist\n");
        iGeneralProcCnt++;
     }
     bCheckOk=m_JudgeProc.CheckSubDoorProcExist(g_GPIOData,g_ChainSetData);
     if(bCheckOk)
     {
        iGeneralProcCnt++;//�ӹ��ű���(�ڲ�����,���21)
        g_strlistGeneralProc.append(m_JudgeProc.m_strSubmbh);
        //add by 2020.09.05
        statusrec=organizationStatusRecord(m_JudgeProc.m_strSubmbh,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
        g_vec_StatusRecord.push_back(statusrec);

     }
    bCheckOk=m_JudgeProc.CheckSubRectBridgeOverheat(g_GPIOData,g_ChainSetData);
    if(bCheckOk)
      {
        iGeneralProcCnt++;//�ӹ������Ź���(�ڲ�����,���22)
        g_strlistGeneralProc.append(m_JudgeProc.m_strSubzlqgw);
        //add by 2020.09.05
        statusrec=organizationStatusRecord(m_JudgeProc.m_strSubzlqgw,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
        g_vec_StatusRecord.push_back(statusrec);
       }
        //�ж��Ƿ�������ŵ�ѹ����������ָʾ�ƣ�add by 2019.06.29
      if((g_GPIOData.fExcitVolt-EXCIT_VOLTAGE_LIMIT)>DELT_FVALUE)
       {
            g_GPIOData.iExcitationState=1;
       }
       else
        {
            g_GPIOData.iExcitationState=-1;
        }

        //�ж������ѹ��ƽ��,add by 2019.05.17
         bCheckOk=m_JudgeProc.CheckVoltImbalance(g_GPIOData.fPhaseAVolt,g_GPIOData.fPhaseBVolt,g_GPIOData.fPhaseCVolt);
         if(bCheckOk)
            {
                iGeneralProcCnt++;//�����ѹ��ƽ��(�ڲ�����,���15)
                g_strlistGeneralProc.append(m_JudgeProc.m_strVoltUnbalance);
                //add by 2020.09.05
               statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltUnbalance,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
               g_vec_StatusRecord.push_back(statusrec);
            }
            /*printf("chech three phase unbalance finish\n");*/
            //�ж������ѹ���ߣ�add by 2019.05.17
            bCheckOk=m_JudgeProc.CheckOverVolt(g_GPIOData.fPhaseAVolt,g_GPIOData.fPhaseBVolt,g_GPIOData.fPhaseCVolt);
            if(bCheckOk)
            {
                iGeneralProcCnt++;//�����ѹ����(�ڲ����������16)
                g_strlistGeneralProc.append(m_JudgeProc.m_strVoltUp);
                //add by 2020.09.05
               statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltUp,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
               g_vec_StatusRecord.push_back(statusrec);
            }
            /*printf("chech three phase overvoltage finish\n");*/
            //�ж������ѹ����, add by 2019.05.17
            bCheckOk=m_JudgeProc.CheckLowVolt(g_GPIOData.fPhaseAVolt,g_GPIOData.fPhaseBVolt,g_GPIOData.fPhaseCVolt);
            if(bCheckOk)
            {
                iGeneralProcCnt++;//�����ѹ����(�ڲ����������17)
                g_strlistGeneralProc.append(m_JudgeProc.m_strVoltDown);
                //add by 2020.09.05
               statusrec=organizationStatusRecord(m_JudgeProc.m_strVoltDown,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
               g_vec_StatusRecord.push_back(statusrec);
            }
            /*printf("chech three phase lowvoltage finish\n");*/

            //�жϹ����������ѹ���ߣ�add by 2019.05.17
          if((g_GPIOData.fTotalVolt-g_struBasicPara.fTotalvoltUp)>DELT_FVALUE)
          {
              iGeneralProcCnt++;//�����������ѹ���ߣ��ڲ����棬���18��
              g_strlistGeneralProc.append(m_JudgeProc.m_strOutVoltUp);
              //add by 2020.09.05
               statusrec=organizationStatusRecord(m_JudgeProc.m_strOutVoltUp,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
               g_vec_StatusRecord.push_back(statusrec);
          }
          /*printf("g_GPIOData.fTotalVolt-TOTAL_VOLT_UP_LIMIT finish\n");*/

           //�жϷֹ�����������ߣ�add by 2019.05.18
           int iCurrOverCnt=0;
           bCheckOk=m_JudgeProc.CheckOutputCurrentOver(g_GPIOData,iCurrOverCnt);
           if(bCheckOk)
           {
               iGeneralProcCnt++;//�ֹ�����������ߣ��ڲ����ϣ����27��
               g_strlistGeneralProc.append(m_JudgeProc.m_strSubCurrentUp);
               //add by 2020.09.05
               statusrec=organizationStatusRecord(m_JudgeProc.m_strSubCurrentUp,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
               g_vec_StatusRecord.push_back(statusrec);
           }
           //�жϹ�������������Ƿ���ߣ�add by 2019.05.17
           if((g_GPIOData.fTotalCurrent-g_struBasicPara.fTotalcurrentUp)>DELT_FVALUE)
           {
               iGeneralProcCnt++;//�����������������(�ڲ����������19)
               g_strlistGeneralProc.append(m_JudgeProc.m_strOutCurrentUp);
               //add by 2020.09.05
               statusrec=organizationStatusRecord(m_JudgeProc.m_strOutCurrentUp,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
               g_vec_StatusRecord.push_back(statusrec);
           }
            //�ж�ĸ�߲����⣬add by 2019.05.17
         //  int iUnbalanceCnt=0;
         //  bCheckOk=m_JudgeProc.CheckBusVoltUnbalance(g_GPIOData,iUnbalanceCnt);
         //  if(bCheckOk)
            //{
            //	 iGeneralProcCnt++;//�ж�ĸ�߲�����(�ڲ����������26)
            //	 g_strlistGeneralProc.append(m_JudgeProc.m_strBusVoltUnbalance);
         //   }
           /*printf("CheckBusVoltUnbalance finish\n");*/

            //�ж�ĸ�ߵ�ѹ���ߣ�add by 2019.05.17
           int BusVoltUpCnt=0;
           bCheckOk=m_JudgeProc.CheckBusVoltUpExist(g_GPIOData,BusVoltUpCnt);
           if(bCheckOk)
           {
               iGeneralProcCnt++;//ĸ�ߵ�ѹ����(�ڲ����������24)
               g_strlistGeneralProc.append(m_JudgeProc.m_strBusVoltUp);
                //add by 2020.09.05
               statusrec=organizationStatusRecord(m_JudgeProc.m_strBusVoltUp,g_GPIOData.fTotalVolt,g_GPIOData.fTotalCurrent);
               g_vec_StatusRecord.push_back(statusrec);
           }
           /*printf("CheckBusVoltUpExist finish\n");*/
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

#endif //Compiler Switch
}
STR_STATUSDATA  GPIODataRecvThread::organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal)
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
//����״̬��¼�ļ�(�����ļ�����)--vector,add by 2020.09.05******
void GPIODataRecvThread::createStatusRecordFileByVector(QVector<STR_STATUSDATA>vec_strusdata)
{
    STR_STATUSDATA tmpStatusData;
    printf("strusdata.size=%d\n",vec_strusdata.size());
    if(vec_strusdata.size()==0)//����20190716
    {
        return;
    }
#ifdef WIN_DEV
    m_strStafilepath= "./debug/statusdata/statusdata.csv";
#else
    m_strStafilepath=QApplication::applicationDirPath() + "/statusdata/statusdata.csv";
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
//����״̬��¼�ļ�(�����ļ�����),add by 2019.07.14
void GPIODataRecvThread::createStatusRecordFileByList(QStringList srtlist)
{
    STR_STATUSDATA tmpStatusData;//���ڳ�Ա������QString���͵ģ����Բ�����memset������ʼ���ýṹ��
    tmpStatusData.fVoltRms=0.00;
    tmpStatusData.fVoltMax=0.00;
    tmpStatusData.fCurrentRms=0.00;
    tmpStatusData.fCurrentMax=0.00;
    QVector<STR_STATUSDATA>tmpVecStaData;
    tmpVecStaData.clear();
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    QString filedate =current_date_time.toString("yyyyMMddhhmm");
    tmpStatusData.strAlarmTime=current_date;
    printf("srtlist.size=%d\n",srtlist.size());
    if(srtlist.size()==0)//����20190716
    {
        return;
    }
    for(int i=0;i<srtlist.size();i++)
    {
        tmpStatusData.strErrorType=srtlist.at(i);
        //�����ѹ��Чֵ
        tmpStatusData.fVoltRms=g_GPIOData.fTotalVolt;
        //�����ѹ���ֵ
        tmpStatusData.fVoltMax=g_GPIOData.fTotalVolt*qSqrt(2.0);
        //���������Чֵ
        tmpStatusData.fCurrentRms=g_GPIOData.fTotalCurrent;
        printf("fCurrentRms=%f--i=%d\n",tmpStatusData.fCurrentRms,i);
        //����������ֵ
        tmpStatusData.fCurrentMax=g_GPIOData.fTotalCurrent*qSqrt(2.0);
        tmpVecStaData.push_back(tmpStatusData);
    }
#ifdef WIN_DEV
    m_strStafilepath="./debug/statusdata/statusdata.csv";
#else
    m_strStafilepath=QApplication::applicationDirPath() + "/statusdata/statusdata.csv";
#endif

     printf("createStatusRecordFileByList:%s\n",m_strStafilepath.toStdString().data());

     //else
     //{
         //�Ѵ���״̬��¼�ļ�����ֱ��д��������
         printf("##createStatusRecordFileByList:%s\n",m_strStafilepath.toStdString().data());
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
         if(tmpVecStaData.size()==0)//����20190716
         {
             printf("createStatusRecordFileByList()--m_bCreateStafileflag=%d-Vecsize=%d",m_bCreateStafileflag,tmpVecStaData.size());
             return;
         }
         for(int j=0;j<tmpVecStaData.size();j++)
         {
             tmpStatusData=tmpVecStaData.at(j);
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
//����״̬��¼�ļ�(�����ļ�����),add by 2019.07.14
void GPIODataRecvThread::createStatusRecordFile(QString  strProc)
{
    STR_STATUSDATA tmpStatusData;//���ڳ�Ա������QString���͵ģ����Բ�����memset������ʼ���ýṹ��
    tmpStatusData.fVoltRms=0.00;
    tmpStatusData.fVoltMax=0.00;
    tmpStatusData.fCurrentRms=0.00;
    tmpStatusData.fCurrentMax=0.00;
    QVector<STR_STATUSDATA>tmpVecStaData;
    tmpVecStaData.clear();
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    QString filedate =current_date_time.toString("yyyyMMddhhmm");
    tmpStatusData.strAlarmTime=current_date;
    tmpStatusData.strErrorType=strProc;
    g_Mutex.lock();
    //�����ѹ��Чֵ
    tmpStatusData.fVoltRms=g_GPIOData.fTotalVolt;
    //�����ѹ���ֵ
    tmpStatusData.fVoltMax=g_GPIOData.fTotalVolt*qSqrt(2.0);
    //���������Чֵ
    tmpStatusData.fCurrentRms=g_GPIOData.fTotalCurrent;
    //����������ֵ
    tmpStatusData.fCurrentMax=g_GPIOData.fTotalCurrent*qSqrt(2.0);
    g_Mutex.unlock();
#ifdef WIN_DEV
    m_strStafilepath="./debug/statusdata/statusdata.csv";
#else
    m_strStafilepath=QApplication::applicationDirPath() + "/statusdata/statusdata.csv";
#endif
     m_strStafilepath=QApplication::applicationDirPath() + "/statusdata/statusdata.csv";
     //if(!m_bCreateStafileflag)
     //{
        // //û�д���״̬��¼�ļ�,��Ҫ�½�,add by 2019.07.14
        // if(!m_strStafilepath.contains(tr("/statusdata/statusdata.csv")))
        // {
        //	 printf("no /statusdata/statusdata.csv path exist\n");
        //	 return;
        // }
        // QFile file(m_strStafilepath);
     //   if (!file.open(QIODevice::WriteOnly | QIODevice::Append))//�ļ�׷��д��
  //                 return;
  //       QTextStream out(&file);
        // //����ļ�ͷ����Ϣ
        // QStringList headfilelist;
        // headfilelist.append(tr("time"));
        // headfilelist.append(tr(","));
        // headfilelist.append(tr("errrortype"));
        // headfilelist.append(tr(","));
        // headfilelist.append(tr("volt_rms(V)"));
        // headfilelist.append(tr(","));
        // headfilelist.append(tr("volt_max(V)"));
        // headfilelist.append(tr(","));
        // headfilelist.append(tr("current_rms(A)"));
        // headfilelist.append(tr(","));
        // headfilelist.append(tr("current_max(A)"));

        // out << headfilelist.at(0) << headfilelist.at(1)<< headfilelist.at(2)<< headfilelist.at(3)<< headfilelist.at(4)<< headfilelist.at(5)<< headfilelist.at(6)<< headfilelist.at(7)<< headfilelist.at(8)<<headfilelist.at(9)<< headfilelist.at(10)<<"\n";
     //    m_bCreateStafileflag=true;
     //}
     //else
     //{
         //�Ѵ���״̬��¼�ļ�����ֱ��д��������
         if(!m_strStafilepath.contains(tr("/statusdata/statusdata.csv")))
         {
             printf("no /statusdata/statusdata.csv path exist\n");
             return;
         }
         QFile file(m_strStafilepath);
         if (!file.open(QFile::WriteOnly | QFile::Append))//�ļ�׷��д��
              return;
         QTextStream out(&file);
         out.setCodec("GB2312");
         QStringList datafilelist;
         QString strTemp;
          //����ʱ��
         datafilelist.append(tmpStatusData.strAlarmTime);
         datafilelist.append(tr(","));
          //����(����)����
         datafilelist.append(tmpStatusData.strErrorType);
         datafilelist.append(tr(","));
          //�����ѹ��Чֵ
         strTemp= QString::number(tmpStatusData.fVoltRms,'f',2);
         datafilelist.append(strTemp);
         datafilelist.append(tr(","));
           //�����ѹ���ֵ
         strTemp= QString::number(tmpStatusData.fVoltMax,'f',2);
         datafilelist.append(strTemp);
         datafilelist.append(tr(","));
           //���������Чֵ
         strTemp= QString::number(tmpStatusData.fCurrentRms,'f',2);
         datafilelist.append(strTemp);
         datafilelist.append(tr(","));
           //����������ֵ
         strTemp= QString::number(tmpStatusData.fCurrentMax,'f',2);
         datafilelist.append(strTemp);
         out << datafilelist.at(0) << datafilelist.at(1)<< datafilelist.at(2)<< datafilelist.at(3)<< datafilelist.at(4)<< datafilelist.at(5)<< datafilelist.at(6)<< datafilelist.at(7)<< datafilelist.at(8)<<datafilelist.at(9)<< datafilelist.at(10)<<"\n";
         file.close();
         //֪ͨ�������߳������ļ���д�꣬���Զ�ȡ
         QCoreApplication::postEvent(m_pReceiver,new QCustomEvent(QEvent::User + 5000),0);
    // }
}
//��ȡ�汾����,add by by zqc 2019.07.13
void GPIODataRecvThread::readVersionData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    long int ret_di_data=0;
    //��ȡ�汾����Ϣ
     m_Gpiorw.read_adi(read_address_version_00,buffer_read,m_ifd);
     ret_di_data = m_Gpiorw.ai_data_compute(buffer_read);
}
//��ȡֱ��5V����,add by zqc 2019.07.13
void GPIODataRecvThread::readDC5VData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    long int ret_ai_data=0;
    float ai_value=0.00;
    //��ȡ+5V����
    m_Gpiorw.read_adi(read_address_ai_60,buffer_read,m_ifd);
    ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
    ai_value = ret_ai_data*20.00/65536.00;
}
//��ȡ����DI״̬����
void GPIODataRecvThread::readMasterDIData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_di_data=0;
    g_Mutex.lock();
    bReadOk=m_Gpiorw.read_adi(read_address_di_08,buffer_read,m_ifd);
    ret_di_data = m_Gpiorw.ai_data_compute(buffer_read);
    for(int k=0;k<MAX_SIZE;k++)
    {
      g_GPIOData.iMasterDI[k]=buffer_read[k];
    }
    g_Mutex.unlock();
}
//��ȡ�ӹ�DI״̬����
void GPIODataRecvThread::readSlaveDIData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_di_data=0;
    g_Mutex.lock();
    bReadOk=m_Gpiorw.read_adi(read_address_di_0A,buffer_read,m_ifd);
    ret_di_data = m_Gpiorw.ai_data_compute(buffer_read);
    for(int k=0;k<MAX_SIZE;k++)
    {
        g_GPIOData.iSlaveDI[k]=buffer_read[k];
    }
    g_Mutex.unlock();
}
//��ȡ�������ŵ�ѹ����
void GPIODataRecvThread::readExcitVoltData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_ai_data=0;
    float ai_value=0.00;
    float Adj_K=1.0;
    float Adj_B=0.0;
    Adj_K=g_struAdjcoef.fMEvoltK;
    Adj_B=g_struAdjcoef.fMEvoltB;
    bReadOk=m_Gpiorw.read_adi(read_address_ai_26,buffer_read,m_ifd);
    ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
    ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
    g_Mutex.lock();
    g_GPIOData.fExcitVolt=ai_value*EXCIT_VOLT_RATIO*Adj_K+Adj_B;
    g_Mutex.unlock();
}
//��ȡ�������ŵ�������
void GPIODataRecvThread::readExcitCurrentData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_ai_data=0;
    float ai_value=0.00;
    float Adj_K=1.0;
    float Adj_B=0.0;
     if(g_SimuProcSet.isSimuFlag)
       {
            //--ģ�����̬ʱ��add by 2019.05.25
           g_GPIOData.fExcitCurrent=g_SimuProcSet.fSimuExcitCurrent;
        }
     else
     {
           Adj_K=g_struAdjcoef.fMEcurrK;
           Adj_B=g_struAdjcoef.fMEcurrB;
           bReadOk=m_Gpiorw.read_adi(read_address_ai_28,buffer_read,m_ifd);
           ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
           ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
           g_GPIOData.fExcitCurrent=ai_value*EXCIT_CURRENT_RATIO*Adj_K+Adj_B;
     }
}
//��ȡ�����ѹ����,add by zqc 2019.07.13
void  GPIODataRecvThread::readThreePhaseVoltData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_ai_data=0;
    float ai_value=0.00;
    float Adj_K=1.0;
    float Adj_B=0.0;
    //--��ȡ����-A���ѹ
    Adj_K=g_struAdjcoef.fMAvoltK;
    Adj_B=g_struAdjcoef.fMAvoltB;
    bReadOk=m_Gpiorw.read_adi(read_address_ai_2A,buffer_read,m_ifd);
    ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
    ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
    g_GPIOData.fPhaseAVolt=ai_value*THREE_VOLT_RATIO*Adj_K+Adj_B;
    usleep(100);
    //��ȡ����-B���ѹ
    Adj_K=g_struAdjcoef.fMBvoltK;
    Adj_B=g_struAdjcoef.fMBvoltB;
    bReadOk=m_Gpiorw.read_adi(read_address_ai_2C,buffer_read,m_ifd);
    ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
    ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
    g_GPIOData.fPhaseBVolt=ai_value*THREE_VOLT_RATIO*Adj_K+Adj_B;
    usleep(100);
    //��ȡ����-C���ѹ
    Adj_K=g_struAdjcoef.fMCvoltK;
    Adj_B=g_struAdjcoef.fMCvoltB;
    bReadOk=m_Gpiorw.read_adi(read_address_ai_2E,buffer_read,m_ifd);
    ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
    ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
    g_GPIOData.fPhaseCVolt=ai_value*THREE_VOLT_RATIO*Adj_K+Adj_B;
    if(bReadOk)
    {
        g_GPIOData.iRunningState=1;
    }
    else
    {
        g_GPIOData.iRunningState=-1;
    }
}
//��ȡ4���ӹ��ѹ����,add by zqc 2019.07.13
void  GPIODataRecvThread::readSlaveVoltData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_ai_data=0;
    float ai_value=0.00;
    float Adj_K=1.0;
    float Adj_B=0.0;
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
     {
           //��ȡ�ӹ�0��ѹ
        Adj_K=g_struAdjcoef.fSub1outvoltK;
        Adj_B=g_struAdjcoef.fSub1outvoltB;
        bReadOk= m_Gpiorw.read_adi(read_address_ai_32,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_GPIOData.fSlaveVolt[0]=ai_value*OUTPUT_VOLT_RATIO*Adj_K+Adj_B;
        usleep(100);
      }
    if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
      {
            //��ȡ�ӹ�1��ѹ
        Adj_K=g_struAdjcoef.fSub2outvoltK;
        Adj_B=g_struAdjcoef.fSub2outvoltB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_34,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_GPIOData.fSlaveVolt[1]=ai_value*OUTPUT_VOLT_RATIO*Adj_K+Adj_B;
        usleep(100);
     }
     if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
     {
            //��ȡ�ӹ�2��ѹ
        Adj_K=g_struAdjcoef.fSub3outvoltK;
        Adj_B=g_struAdjcoef.fSub3outvoltB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_36,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_GPIOData.fSlaveVolt[2]=ai_value*OUTPUT_VOLT_RATIO*Adj_K+Adj_B;
        usleep(100);
     }
     if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
     {
            //��ȡ�ӹ�3��ѹ
        Adj_K=g_struAdjcoef.fSub4outvoltK;
        Adj_B=g_struAdjcoef.fSub4outvoltB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_38,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_GPIOData.fSlaveVolt[3]=ai_value*OUTPUT_VOLT_RATIO*Adj_K+Adj_B;
        usleep(100);
     }
    if(bReadOk)
    {
        float fVoltSum=0.00;
        int cnt=0;
        if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
        {
            fVoltSum+= g_GPIOData.fSlaveVolt[0];
            cnt++;
        }
        if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
        {
            fVoltSum+= g_GPIOData.fSlaveVolt[1];
            cnt++;
        }
        if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
        {
            fVoltSum+= g_GPIOData.fSlaveVolt[2];
            cnt++;
        }
        if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
        {
            fVoltSum+= g_GPIOData.fSlaveVolt[3];
            cnt++;
        }
        if(cnt>0)
        {
            g_GPIOData.fTotalVolt=fVoltSum/cnt;//����ֹ��ѹ��ֵ
        }
    }//if(bReadOk)
}
//��ȡ4���ӹ��������,add by zqc 2019.07.13
void  GPIODataRecvThread::readSlaveCurrentData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_ai_data=0;
    float ai_value=0.00;
    float Adj_K=1.0;
    float Adj_B=0.0;
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
      {
            //��ȡ�ӹ�0����
        Adj_K=g_struAdjcoef.fSub1outcurrK;
        Adj_B=g_struAdjcoef.fSub1outcurrB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_3A,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveCurrent[0]=ai_value*OUTPUT_CURRENT_RATIO*Adj_K+Adj_B;
        g_Mutex.unlock();
        usleep(100);
     }
    if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
     {
          //��ȡ�ӹ�1����
        Adj_K=g_struAdjcoef.fSub2outcurrK;
        Adj_B=g_struAdjcoef.fSub2outcurrB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_3C,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveCurrent[1]=ai_value*OUTPUT_CURRENT_RATIO*Adj_K+Adj_B;
        g_Mutex.unlock();
        usleep(100);
    }
   if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
      {
          //��ȡ�ӹ�2����
        Adj_K=g_struAdjcoef.fSub3outcurrK;
        Adj_B=g_struAdjcoef.fSub3outcurrB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_3E,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveCurrent[2]=ai_value*OUTPUT_CURRENT_RATIO*Adj_K+Adj_B;
        g_Mutex.unlock();
        usleep(100);
     }
     if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
      {
          //��ȡ�ӹ�3����
        Adj_K=g_struAdjcoef.fSub4outcurrK;
        Adj_B=g_struAdjcoef.fSub4outcurrB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_40,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveCurrent[3]=ai_value*OUTPUT_CURRENT_RATIO*Adj_K+Adj_B;
        g_Mutex.unlock();
        usleep(100);
      }
          if(bReadOk)
          {
               g_Mutex.lock();
               float fCurrentSum=0.00;
               if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
               {
                    fCurrentSum+= g_GPIOData.fSlaveCurrent[0];
               }
               if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
               {
                    fCurrentSum+= g_GPIOData.fSlaveCurrent[1];
               }
              if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
               {
                    fCurrentSum+= g_GPIOData.fSlaveCurrent[2];
               }
              if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
               {
                    fCurrentSum+= g_GPIOData.fSlaveCurrent[3];
               }
              g_GPIOData.fTotalCurrent=fCurrentSum;//4���ֹ�������
              g_Mutex.unlock();
          }//if(bReadOk)
}
//��ȡ4���ӹ�ĸ�ߵ�ѹ����,add by zqc 2019.07.13
void  GPIODataRecvThread::readSlaveBusVoltData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_ai_data=0;
    float ai_value=0.00;
    float Adj_K=1.0;
    float Adj_B=0.0;
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {
        //��ȡ�ӹ�0ĸ�ߵ�ѹ
        Adj_K=g_struAdjcoef.fSub1voltK;
        Adj_B=g_struAdjcoef.fSub1voltB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_42,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveBusVolt[0]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
        g_Mutex.unlock();
    }
    if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
    {
        //��ȡ�ӹ�1ĸ�ߵ�ѹ-add by zqc 2019.01.26
        Adj_K=g_struAdjcoef.fSub2voltK;
        Adj_B=g_struAdjcoef.fSub2voltB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_44,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveBusVolt[1]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
        g_Mutex.unlock();
    }
    if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
    {
    //��ȡ�ӹ�2ĸ�ߵ�ѹ-add by zqc 2019.01.26
        Adj_K=g_struAdjcoef.fSub3voltK;
        Adj_B=g_struAdjcoef.fSub3voltB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_46,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveBusVolt[2]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
        g_Mutex.unlock();
    }
    if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
    {
    //��ȡ�ӹ�3ĸ�ߵ�ѹ-add by zqc 2019.01.26
        Adj_K=g_struAdjcoef.fSub4voltK;
        Adj_B=g_struAdjcoef.fSub4voltB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_48,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveBusVolt[3]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
        g_Mutex.unlock();
    }
}
 //��ȡ4���ӹ���ĸ�ߵ�ѹ����,add by zqc 2019.07.13
void  GPIODataRecvThread::readSlaveActBusVoltData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_ai_data=0;
    float ai_value=0.00;
    float Adj_K=1.0;
    float Adj_B=0.0;
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
        {
        //��ȡ�ӹ�0��ĸ�ߵ�ѹ
        Adj_K=g_struAdjcoef.fSub1ActvoltK;
        Adj_B=g_struAdjcoef.fSub1ActvoltB;
        bReadOk=m_Gpiorw.read_adi(read_address_ai_4A,buffer_read,m_ifd);
        ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
        ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
        g_Mutex.lock();
        g_GPIOData.fSlaveActBusVolt[0]=ai_value*Adj_K*BUS_VOLT_RATIO+Adj_B;
        g_Mutex.unlock();
        if(bReadOk)
            {//����״ֵ̬
                g_GPIOData.iSlaveStaValue[0]=1;
            }
            else
            {
                g_GPIOData.iSlaveStaValue[0]=0;

            }
        usleep(100);
        }
        if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
        {
        //��ȡ�ӹ�1��ĸ�ߵ�ѹ
            Adj_K=g_struAdjcoef.fSub2ActvoltK;
            Adj_B=g_struAdjcoef.fSub2ActvoltB;
            bReadOk=m_Gpiorw.read_adi(read_address_ai_4C,buffer_read,m_ifd);
            ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
            ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
            g_Mutex.lock();
            g_GPIOData.fSlaveActBusVolt[1]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
            g_Mutex.unlock();
        if(bReadOk)
            {//����״ֵ̬
                g_GPIOData.iSlaveStaValue[1]=1;
            }
            else
            {
                g_GPIOData.iSlaveStaValue[1]=0;

            }
            usleep(100);
        }
        if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
        {
        //��ȡ�ӹ�2��ĸ�ߵ�ѹ
            Adj_K=g_struAdjcoef.fSub3ActvoltK;
            Adj_B=g_struAdjcoef.fSub3ActvoltB;
            bReadOk=m_Gpiorw.read_adi(read_address_ai_4E,buffer_read,m_ifd);
            ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
            ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
            g_Mutex.lock();
            g_GPIOData.fSlaveActBusVolt[2]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
            g_Mutex.unlock();
            if(bReadOk)
                {//����״ֵ̬
                g_GPIOData.iSlaveStaValue[2]=1;
                }
                else
                {
                g_GPIOData.iSlaveStaValue[2]=0;
                }
            usleep(100);
        }
        if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
        {
        //��ȡ�ӹ�3��ĸ�ߵ�ѹ
            Adj_K=g_struAdjcoef.fSub4ActvoltK;
            Adj_B=g_struAdjcoef.fSub4ActvoltB;
            bReadOk=m_Gpiorw.read_adi(read_address_ai_50,buffer_read,m_ifd);
            ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
            ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
            g_Mutex.lock();
            g_GPIOData.fSlaveActBusVolt[3]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
            g_Mutex.unlock();
            if(bReadOk)
            {//����״ֵ̬
                g_GPIOData.iSlaveStaValue[3]=1;
                }
            else
                {
                g_GPIOData.iSlaveStaValue[3]=0;
                }
        }
}
//��ȡ4���ӹ�ĸ�ߵ�ѹ����,add by zqc 2019.07.13
void  GPIODataRecvThread::readSlaveRegBusVoltData()
{
    int buffer_read[MAX_SIZE];
    memset(buffer_read,0,sizeof(buffer_read));
    bool bReadOk=false;
    long int ret_ai_data=0;
    float ai_value=0.00;
    float Adj_K=1.0;
    float Adj_B=0.0;
        if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
        {
        //��ȡ�ӹ�0��ĸ�ߵ�ѹ
            Adj_K=g_struAdjcoef.fSub1negvoltK;
            Adj_B=g_struAdjcoef.fSub1negvoltB;
            bReadOk=m_Gpiorw.read_adi(read_address_ai_52,buffer_read,m_ifd);
            ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
            ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
            g_Mutex.lock();
            g_GPIOData.fSlaveNegBusVolt[0]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
            g_Mutex.unlock();
            usleep(100);
        }
        if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
        {
        //��ȡ�ӹ�1��ĸ�ߵ�ѹ
            Adj_K=g_struAdjcoef.fSub2negvoltK;
            Adj_B=g_struAdjcoef.fSub2negvoltB;
            bReadOk=m_Gpiorw.read_adi(read_address_ai_54,buffer_read,m_ifd);
            ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
            ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
            g_Mutex.lock();
            g_GPIOData.fSlaveNegBusVolt[1]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
            g_Mutex.unlock();
            usleep(100);
        }
        if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
        {
        //��ȡ�ӹ�2��ĸ�ߵ�ѹ
            Adj_K=g_struAdjcoef.fSub3negvoltK;
            Adj_B=g_struAdjcoef.fSub3negvoltB;
            bReadOk=m_Gpiorw.read_adi(read_address_ai_56,buffer_read,m_ifd);
            ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
            ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
            g_Mutex.lock();
            g_GPIOData.fSlaveNegBusVolt[2]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
            g_Mutex.unlock();
            usleep(100);
        }
        if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
        {
        //��ȡ�ӹ�3��ĸ�ߵ�ѹ
            Adj_K=g_struAdjcoef.fSub4negvoltK;
            Adj_B=g_struAdjcoef.fSub4negvoltB;
            bReadOk=m_Gpiorw.read_adi(read_address_ai_58,buffer_read,m_ifd);
            ret_ai_data = m_Gpiorw.ai_data_compute(buffer_read);
            ai_value = ((ret_ai_data+0x8000)&0xFFFF)*20.00/65536.00-10.0;
            g_Mutex.lock();
            g_GPIOData.fSlaveNegBusVolt[3]=ai_value*BUS_VOLT_RATIO*Adj_K+Adj_B;
            g_Mutex.unlock();
        }
}


void GPIODataRecvThread::readAd760602()
{
#ifdef UBUNTU_DEV //Compiler Switch
    int i,j;
        j=0;
        read(fd_ad02,ad_bf,16);
        for(i=0;i<15;i++)
        {
            ret = ((ad_bf[i])<<8)+ad_bf[i+1];
            //add by zw 2022.07.06
            if(ret >= 32767)
                ret = 0;
            if(ret&0x8000)
            {
                ain02[j] = (10.0-((ret&0x7fff)*10.0/32767))*(-1);
            }
            else
            {
                ain02[j] = (ret&0x7fff)*10.0/32767;
            }
            j++;
            i++;
        }
//        qDebug()<<ain02[0]<<"###"<<ain02[1]<<"###"<<ain02[2]<<"###"<<ain02[3]<<"###"<<ain02[4]<<"###"<<ain02[5]<<"###"<<ain02[6]<<"###"<<ain02[7];

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


        ain02[0] = g_newAdjcoef.fTotalVolACK*ain02[0]+g_newAdjcoef.fTotalVolACB;
        ain02[1] = g_newAdjcoef.fTotalVolDCK*ain02[1]+g_newAdjcoef.fTotalVolDCB;
        ain02[2] = g_newAdjcoef.fSlave1CurDCK*ain02[2]+g_newAdjcoef.fSlave1CurDCB;
        ain02[3] = g_newAdjcoef.fSlave2CurDCK*ain02[3]+g_newAdjcoef.fSlave2CurDCB;
        ain02[4] = g_newAdjcoef.fSlave3CurDCK*ain02[4]+g_newAdjcoef.fSlave3CurDCB;
        ain02[5] = g_newAdjcoef.fSlave4CurDCK*ain02[5]+g_newAdjcoef.fSlave4CurDCB;
        ain02[6] = g_newAdjcoef.fTotalSlaveCurACK*ain02[6]+g_newAdjcoef.fTotalSlaveCurACB;
        ain02[7] = g_newAdjcoef.fExcitCurK*ain02[7]+g_newAdjcoef.fExcitCurB;
//        qDebug()<<"####  ain02[0] ="<< ain02[0]<<"####";

        Q0.push_back(ain02[0]);
        Q1.push_back(ain02[1]);
        Q2.push_back(ain02[2]);
        Q3.push_back(ain02[3]);
        Q4.push_back(ain02[4]);
        Q5.push_back(ain02[5]);
        Q6.push_back(ain02[6]);
        Q7.push_back(ain02[7]);
//        qDebug()<<"#### Q.size() ="<<Q.size()<<"####";
//        for(i=0;i<Q.size();i++)
//        {
//            qDebug()<<"#### Q["<<i<<"] ="<<Q[i]<<"####";
//        }
#endif
}
