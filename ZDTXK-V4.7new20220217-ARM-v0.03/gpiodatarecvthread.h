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
    //����״̬��¼�ļ�(�����ļ�����),add by 2019.07.14
    void createStatusRecordFileByList(QStringList srtlist);
    void createStatusRecordFile(QString  strProc);
    //����״̬��¼�ļ�(�����ļ�����)--vector,add by 2020.09.05
    void createStatusRecordFileByVector(QVector<STR_STATUSDATA>vec_strusdata);

public:
     CGPIORW m_Gpiorw;
     bool m_iGfstartflag;
private:
    void initGPIOData();             //��ʼ��GPIO���ݱ���,add by 2019.07.14
    void readVersionData();          //��ȡ�汾����,add by by zqc 2019.07.13
    void readDC5VData();             //��ȡֱ��5V����,add by zqc 2019.07.13
    void readMasterDIData();         //��ȡ����DI״̬����,add by zqc 2019.07.13
    void readSlaveDIData();          //��ȡ�ӹ�DI״̬����,add by zqc 2019.07.13
    void readExcitVoltData();        //��ȡ�������ŵ�ѹ����,add by zqc 2019.07.13
    void readExcitCurrentData();     //��ȡ�������ŵ�������,add by zqc 2019.07.13
    void readThreePhaseVoltData();   //��ȡ�����ѹ����,add by zqc 2019.07.13
    void readSlaveVoltData();        //��ȡ4���ӹ��ѹ����,add by zqc 2019.07.13
    void readSlaveCurrentData();     //��ȡ4���ӹ��������,add by zqc 2019.07.13
    void readSlaveBusVoltData();     //��ȡ4���ӹ�ĸ�ߵ�ѹ����,add by zqc 2019.07.13
    void readSlaveActBusVoltData();  //��ȡ4���ӹ���ĸ�ߵ�ѹ����,add by zqc 2019.07.13
    void readSlaveRegBusVoltData();  //��ȡ4���ӹ�ĸ�ߵ�ѹ����,add by zqc 2019.07.13
    void readData();                 //��ȡ����,add by zqc 2019.07.13
    void handleData();               //�������ݲ���֪ͨ���������߳�,add by zqc 2019.07.13
    STR_STATUSDATA  organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal);//add by 2020.09.05

private:
     volatile bool m_bStopped;
     QWidget *m_pReceiver;
     int m_ifd;
     CJudgeProc m_JudgeProc;        //�жϱ�����,add by 2019.05.17
     bool m_bCreateStafileflag;     //����״̬��¼�ļ���־,add by 2019.07.14
     QString m_strStafilepath;      //״̬��¼�ļ�����·����add by 2019.07.14

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
     int displyCnt;  //4Hz��ʾʱdisplyCnt=pwm2Freq/4;
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
