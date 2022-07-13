#ifndef GPIODATARECVTHREAD_H
#define GPIODATARECVTHREAD_H
#include <qthread.h>
#include <QWidget>
#include "gpiorw.h"
#include "judgeprotection.h" //add by 2019.05.17
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QQueue>


class GPIODataRecvThread : public QThread
{
public:
     GPIODataRecvThread(QWidget * ptr,int nSocketID);
    ~GPIODataRecvThread();
public:
    void restart();
    void stop();
    void run();
    bool GetThreadCurrentStatus();
    //创建状态记录文件(单个文件考虑),add by 2019.07.14
    void createStatusRecordFileByList(QStringList srtlist);
    void createStatusRecordFile(QString  strProc);
    //创建状态记录文件(单个文件考虑)--vector,add by 2020.09.05
    void createStatusRecordFileByVector(QVector<STR_STATUSDATA>vec_strusdata);

public:
     CGPIORW m_Gpiorw;
     bool m_iGfstartflag;
private:
    void initGPIOData();             //初始化GPIO数据变量,add by 2019.07.14
    void readVersionData();          //读取版本数据,add by by zqc 2019.07.13
    void readDC5VData();             //读取直流5V数据,add by zqc 2019.07.13
    void readMasterDIData();         //读取主柜DI状态数据,add by zqc 2019.07.13
    void readSlaveDIData();          //读取从柜DI状态数据,add by zqc 2019.07.13
    void readExcitVoltData();        //读取功放励磁电压数据,add by zqc 2019.07.13
    void readExcitCurrentData();     //读取功放励磁电流数据,add by zqc 2019.07.13
    void readThreePhaseVoltData();   //读取三相电压数据,add by zqc 2019.07.13
    void readSlaveVoltData();        //读取4个从柜电压数据,add by zqc 2019.07.13
    void readSlaveCurrentData();     //读取4个从柜电流数据,add by zqc 2019.07.13
    void readSlaveBusVoltData();     //读取4个从柜母线电压数据,add by zqc 2019.07.13
    void readSlaveActBusVoltData();  //读取4个从柜正母线电压数据,add by zqc 2019.07.13
    void readSlaveRegBusVoltData();  //读取4个从柜负母线电压数据,add by zqc 2019.07.13
    void readData();                 //读取数据,add by zqc 2019.07.13
    void handleData();               //处理数据并发通知给主界面线程,add by zqc 2019.07.13
    STR_STATUSDATA  organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal);//add by 2020.09.05

private:
     volatile bool m_bStopped;
     QWidget *m_pReceiver;
     int m_ifd;
     CJudgeProc m_JudgeProc;        //判断保护类,add by 2019.05.17
     bool m_bCreateStafileflag;     //创建状态记录文件标志,add by 2019.07.14
     QString m_strStafilepath;      //状态记录文件绝对路径，add by 2019.07.14

     //add by zw 20220223
 public:
     int fd_ad02;
     unsigned char ad_bf[16];
     int ret,ret1;
     double ain02[8];//ain02[0]-- vol_total_AC
                     //ain02[1]-- vol_total_DC
                     //ain02[2]-- slave1_cur_DC
                     //ain02[3]-- slave2_cur_DC
                     //ain02[4]-- slave3_cur_DC
                     //ain02[5]-- slave4_cur_DC
                     //ain02[6]-- slave_cur_total_AC
                     //ain02[7]-- excitation_cur
     int pwm2Freq;
     int displyCnt;  //4Hz显示时displyCnt=pwm2Freq/4;
     QQueue<double> Q0;
     QQueue<double> Q1;
     QQueue<double> Q2;
     QQueue<double> Q3;
     QQueue<double> Q4;
     QQueue<double> Q5;
     QQueue<double> Q6;
     QQueue<double> Q7;

     void readAd760602();

     //end add by zw 20220223

};
#endif // GPIODATARECVTHREAD_H
