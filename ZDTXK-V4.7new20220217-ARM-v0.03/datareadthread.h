#ifndef DATAREADTHREAD_H
#define DATAREADTHREAD_H
#include <qthread.h>
#include <QWidget>
#include "gpiorw.h"
#include "judgeprotection.h" //add by 2019.05.17
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QQueue>
#include "gpiodatarecvthread.h"


class DataReadThread : public QThread
{
public:
     DataReadThread(QWidget * ptr,int nSocketID);
    ~DataReadThread();
public:
    void restart();
    void stop();
    void run();

public:

     bool m_iGfstartflag;

private:
     volatile bool m_bStopped;
     QWidget *m_pReceiver;
     CJudgeProc m_JudgeProc;        //判断保护类,add by 2019.05.17

     //add by zw 20220223
 public:
     int fd_ad01;
     unsigned char ad_bf[17];
     int ret,ret1;
     double ain01[8];//ain01[0]-- slave1_vol_DC
                     //ain01[1]-- slave2_vol_DC
                     //ain01[2]-- slave3_vol_DC
                     //ain01[3]-- slave4_vol_DC
                     //ain01[4]-- excitation_vol
                     //ain01[5]-- Custom11
                     //ain01[6]-- Custom12
                     //ain01[7]-- MUX_OUT_OP(0:triphase_volA_DC,1:triphase_volB_DC,2:triphase_volC_DC)
     int pwm1Freq;
     int displyCnt;  //4Hz显示时displyCnt=pwm2Freq/4;
     QQueue<double> Q0;
     QQueue<double> Q1;
     QQueue<double> Q2;
     QQueue<double> Q3;
     QQueue<double> Q4;
     QQueue<double> Q5;
     QQueue<double> Q6;
     QQueue<double> Q7;

     GPIODataRecvThread *i_pGPIOdataThread;
     volatile int m_bMuxOut; //mux_out Flag; 0:triphase_volA_DC,1:triphase_volB_DC,2:triphase_volC_DC
     int fd_out; //IO 控制fd


     void readAd760601();
     void handleData();
     void readErrStatus();
     void readAllData();
     void choseMuxOut(int trip);
     void dataTransfer(); //将采集数据通过K、B系数进行计算校准
     STR_STATUSDATA  organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal);
     //创建状态记录文件(单个文件考虑)--vector,add by 2020.09.05
     void createStatusRecordFileByVector(QVector<STR_STATUSDATA>vec_strusdata);

     //end add by zw 20220223

};
#endif // GPIODATARECVTHREAD_H
