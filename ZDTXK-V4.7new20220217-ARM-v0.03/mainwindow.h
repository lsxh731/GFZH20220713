#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_mainwindow.h"
#include "logindlg.h"
#include "adjcoefdlg.h"
#include "chainsetdlg.h"
#include "thresholdsetdlg.h"
#include <QDialog>
#include <qsocketnotifier.h>
#include "gpiodatarecvthread.h"   //add by zqc 2018.12.11
#include "tempermonitorWidget.h"  //add by zqc 2018.12.23
#include "countdownWidget.h"      //add by 2019.05.26
#include "faultcondWidget.h"     //add by zqc 2018.12.23
#include "runningstatusWidget.h" //add by zqc 2018.12.23
#include "hiscurveWidget.h"
#include "passwordsetdlg.h"
#include "gainsetdlg.h"         // add by zqc 2019.05.13
#include "invalidsetdlg.h"
#include "dcsetdlg.h"
#include "commmacro.h"
#include "gpiorw.h"
#include <QStringList>
#include "CANdatarw.h"
#include "judgeprotection.h"
#include "inifileparse.h"
#include "basicparasetdlg.h"  //add by zqc 2019.06.01
#include "keyboarddlg.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "syssetdlg.h" //add by 2020.08.10
#include "datareadthread.h"
#include "newadjdlg.h"

namespace Ui
{
    class mainWindow;
}
class  CMymainWindow:public QMainWindow
{
    Q_OBJECT
public:
    CMymainWindow();
    ~CMymainWindow();
public Q_SLOTS:
    void homeBtn_clicked();     //切换主界面槽函数,add by 2020.04.04
    void slaveBtn_clicked();    //切换分柜信息槽函数,add by 2020.04.04
    void staRecordBtn_clicked();//切换状态记录槽函数,add by 2020.04.04
    void setBtn_clicked();      //切换设置选择槽函数,add by 2020.04.04
    void masterBtn_clicked();   //切换主柜开关量状态槽函数,add by 2020.04.04
    void debugBtn_clicked();    //切换调试信息槽函数,add by 2020.04.04
    void adjBtn_clicked();       //"� �准系数"槽函数
    void chainBtn_clicked();     //"连锁设置"槽函数
    //void thrBtn_clicked();       //"保护阈值"槽函数
    void tempCtlBtn_clicked();   //"温度监控"槽函数
    void faultStaBtn_clicked();  //"故障状态"槽函数
    void runningStaBtn_clicked();//"运行状态"槽函数
    void lineEdit_clicked();      //"页数选择"槽函数
    void hisCurveBtn_clicked();  //"历史曲线"槽函数
    void updateTime();           //"更新1秒时间"槽函数
    void update100msTime();      //"更新100ms时间"槽函数,add by 2019.05.26
    void syssetBtn_clicked();     //"系统设置"槽函数 add by 2020.08.10
//	void OutLogBtn_clicked();     //"输出日志"槽函数 add by 2020.11.12

    void gfstartBtn_clicked();   //"功放启动"槽函数
    void gfstopBtn_clicked();    //"功放停止"槽函数
    void gfresetBtn_clicked();   //"功放复位"槽函数

    void zystartBtn_clicked();   //"增益启动"槽函数
    void zystopBtn_clicked();    //"增益停止"槽函数

    void pwdsetBtn_clicked();    //"密� �设置"槽函数
    void invalidBtn_clicked();   //"� 效设置"槽函数
    //void dcBtn_clicked();        //"直流设置"槽函数
    void basicparaBtn_clicked(); //"基本参数"槽函数

    void startupBtn_clicked();   //"功率模块启动"槽函数
    void shutdownBtn_clicked();  //"功率模块关机"槽函数
    void jjtjBtn_clicked();      //"紧急停机"槽函数

    void waiting1second();        //等待1秒钟
    void waiting5second();        //等待5秒钟
    void waiting3second();        //等待3秒钟
    void waiting60second();       //等待60秒钟
    void waiting5minute();        //等待5分钟

    //void comboBox_fgnum_clicked(int index); //"分柜号选择"槽函数
    void on_recvCANTempCtlCANRPT(); //接收所有CAN报文
    //void on_recvRunningCANRPT(int socket);     //接收运行状态CAN报文
    //void on_recvFaultCANRPT(int socket);       //接收故障状态CAN报文
    //void on_recvIGBTTempCtlCANRPT(int socket); //接收IGBT温度监控CAN报文
    //void on_recvIDUCTTempCtlCANRPT(int socket);//接收电感温度监控CAN报文

    void clearlogBtn_clicked();//清除日志-槽函数,add by 2019.05.18
    void savelogBtn_clicked(); //保存日志-槽函数,add by 2019.05.18
    void updateSliderValue(int nValue);//更新滑条值到label_slider并下发-槽函数，add by 2019.05.23
    void setSliderPosbyGear(int nGear);//� �据挡位设置滑条位置-槽函数，add by 2019.05.23
    void updatesetBtn_clicked(); //更新模拟设置-槽函数，add by 2019.05.23
    void upBtn_clicked();        //翻到上一页-槽函数,add by 2019.07.14
    void nextBtn_clicked();      //翻到下一页-槽函数,add by 2019.07.14
    void firstBtn_clicked();     //翻到首页-槽函数,add by 2019.07.14
    void tailBtn_clicked();      //翻到尾页-槽函数,add by 2019.07.14

    void lrctlBtn_clicked();          //远程控制槽函数，，add by 2019.08.21
    void slotStartServer();       //开启服务器槽函数，add by 2019.08.21
    void slotSendMesg();          //发送信息槽函数，add by 2019.08.21
    void slotNewConnect();        //建立连接槽函数，add by 2019.08.21
    void slotReadMesg();          //读取信息槽函数，add by 2019.08.21
    void slotCANTEMPConnect();      //建立CAN温度信息连接槽函数，add by 2019.09.06
    void slotReadCANTEMPMesg();      //读取端口13000槽函数，add by 2019.09.06
    void slotCANRUNConnect();      //建立CAN运行状态信息连接槽函数，add by 2019.09.07
    void slotReadCANRUNMesg();      //读取端口13001槽函数，add by 2019.09.07
    void slotCANFAULTConnect();     //建立CAN故障状态信息连接槽函数，add by 2019.09.07
    void slotReadCANFAULTMesg();    //读取端口13002槽函数，add by 2019.09.07
    void slotPROTECTConnect();     //建立CAN故障状态信息连接槽函数，add by 2019.09.07
    void slotReadPROTECTMesg();     //读取端口14000槽函数
    void slotAdjConnect();     //建立� �准系数置信息连接槽函数，add by 2019.12.13
    void slotReadadjMesg();       //读取端口14001槽函数
    void slotBasicConnect();     //建立基本参数信息连接槽函数，add by 2019.12.13
    void slotReadbasicMesg();       //读取端口14002槽函数
    void slotChainConnect();     //建立连锁设置信息连接槽函数，add by 2019.12.13
    void slotReadchainMesg();       //读取端口14003槽函数
    void slotStartCheck();          //检查是否时间不足槽函数
    void languageEN();                 //语言切换英文函数
    void languageCN();                 //语言切换中文函数

    void sub1Btn_clicked();            //分柜信息页面-分柜1切换槽函数,add by 2020.04.18
    void sub2Btn_clicked();            //分柜信息页面-分柜2切换槽函数,add by 2020.04.18
    void sub3Btn_clicked();            //分柜信息页面-分柜3切换槽函数,add by 2020.04.18
    void sub4Btn_clicked();            //分柜信息页面-分柜4切换槽函数,add by 2020.04.18
private:
        int openSerialPort();                     //打开端口
        void initHomePage();                      //初始化主界面信息
        void initStatusPage();                    //初始化状态界面信息
        void initSetPage();                       //初始化控制设置界面
        void initMasterDIPage(QIcon icon);        //初始化DI页面信息
        void initSlaveControlPage(QIcon icon);    //初始化分柜页面信息
        void updateDI(int nDIValue,
            QToolButton *ToolButton);             //更新开关量数据

        void newupdateDI(int nDIValue,
                         QLabel *qlabel);  //add by zw 20220722
        void showSlaveRTdata();	  //显示分柜实时数据
        void showPowerAmpRTdata(void);            //显示功放实时数据
        void initProctype();                      //初始化保护类型数据
        void updateSlaveStatusData(int nStaValue,int nSubopen,
            QToolButton *ToolButton);             //更新从柜运行状态
        void updateStatusData(int nStaValue,
            QToolButton *ToolButton);             //更新状态量数据
        void createHisDataFile(QString strfiledate,QString strCurrdate,
            int nTotaltime);                      //生成历史数据文件
        void CloseSubCabinetRelay();              //分柜高压继电器吸合
        void ReCloseSubCabinetRelay();            //重新对分柜高压继电器吸合,add by zqc 2019.06.02
        void DisAllRelays();                      //断开所有继电器
        void DisAllRelaysExCoolSystem();          //断开所有继电器(除了冷却系统)
        void ReDisAllRelays();                    //重新断开所有继电器,add by zqc 2019.06.02
        void ReDisAllRelaysExCoolSystem();        //重新断开所有继电器(除了冷却系统),add by zqc 2019.06.02

        void OperationSection1();//S1段执行操作,add by 2019.05.18
        void OperationSection2();//S2段执行操作,add by 2019.05.18
        void OperationSection34();//S3和S4段执行操作,add by 2019.05.18
        bool CheckXtlqProcExist();//检测是否存在系统冷却单元保护
        void initGfStartSet();    //功放启动初始化设置,add by 2019.05.21
        void GetSimuProcSet(STRU_SIMUPROCSET &stru_simuprocset);   //获取模拟保护设置参数（正常测试时禁用）,add by 2019.05.23
        void CheckProcOfSection1();//检测S1段的保护，add by2019.07.20
        void CheckProcOfSection2();//检测S2段的保护，add by2019.07.20
        void CheckProcOfSection3();//检测S3段的保护,add by 2019.05.24
        void CheckProcOfSection4();//检测S4段的保护,add by 2019.05.24
        void ShowChainSetStatus(); //显示连锁屏蔽设置状态,add by 2019.05.25
        void updateChainStatusButton(int nValue,QToolButton *toolButton);//更新连锁设置状态按钮,add by 2019.05.25
        void initGainSet();       //增益设置初始化(置0),add by 2019.06.02
        bool readStatusRecordFile();//读取状态记录文件,add by 2019.07.14
        void showStatusRecordInfo(QVector<STR_STATUSDATA> vec_statusData,int nCurrPage); //显示状态记录信息,add by 2019.07.14
        void updateStatusRecordTable(int nCurrPage,int nRows);//按页更新状态记录表� �数据,add by 2019.07.14
        void showRecordStatistics(int nRecsize,int nTotalPage);//显示状态统计信息到label中,add by 2019.07.14
        void delay();//间隔延时函数，add by 2019.07.21
        void openDigKeyBoardDlg(QLineEdit *lineEdit);
        void GPIOsendMesg();
        void ADData_show();
        void PCCtlMesg(QString strMesg);  //PC端控制信号解析
        void PCAdjMesg(QString strMesg);  //PC端� �准系数解析
        void PCBasicMesg(QString strMesg);  //PC端基本参数解析
        void PCChainMesg(QString strMesg);  //PC端连锁设置解析
        void CANTEMPsendMesg();   //发送CAN温度信息
        void CANRUNsendMesg();    //发送CAN运行状态报文
        void CANFAULTsendMesg();    //发送CAN故障状态报文
        void PROTECTsendMesg(QString strPROTECTMesg);      //发送保护类型报文
        void SentSubAvgCurr();
        void mainLangchange();              //主界面提示语中英文切换
        QString TimeFormatTransfer(qint64 nSeconds);//时间� �式转换 add by 2020.08.15
private:
        int m_CANfd,fd2;
        int m_nGPIOfd;
        QSocketNotifier  *m_notifier;

         QTimer *m_pTimer1s;        //1秒定时器,add by 2019.05.18
         QTimer *m_pTimer3s;        //3秒定时器
         QTimer *m_pTimer5s;        //5秒定时器
         QTimer *m_pTimer60s;       //60秒定时器
         QTimer *m_pTimer5m;        //5分钟定时器
         bool m_Timer60StartFlag;   //60秒定时器启动� �志
         bool m_GfTestPauseFlag;    //功放启动测试中断� �志,false-继续测试；true-测试中断,add by 20190518
         bool m_GfStartFlag;        //功放启动� �志，true-启动;false-未启动,add by 20190512
         bool m_GfResetFlag;        //功放复位� �志，true-复位;false-未复位,add by 20190512
         bool m_GfStopFlag;         //功放停止� �志，true-停止;false-未停止,add by 20190512
         bool m_GainStartFlag;      //增益启动� �志，true-启动;false-停止,add by 20190523
         bool m_EmergencyFlag;      //紧机停机� �志，true-按下；false-抬起，add by 20190709
         int  m_nTestFlag;          //测试� �记,add by 2019.05.14
         int  m_nSectionPos;        //程序执行片段位置,add by 2019.05.18
         bool m_isGenModuleProcExist;   //模块通用保护是否存在� �志,add by 2019.05.25
         bool m_ExcitExistFlag;        //励磁开路判别� �识符
         int m_iSubopenFlag[4];
         bool m_StartCheckFlag;      //开机检查是否失效� �志
         bool iLongrCtl;                //远程控制� �志
         QTcpServer *m_pTcpServer;      //TCP通信GPIO服务器，add by 2019.08.21
         QTcpSocket *pTcpSocketServer;  //TCP通信GPIO套接字
         QTcpServer *m_pTcpServerCANTEMP; //TCP通信CAN温度信息服务器，add by 2019.09.6
         QTcpSocket *pTcpSocketServerCANTEMP;//TCP通信CAN温度信息套接字
         QTcpServer *m_pTcpServerCANRUN; //TCP通信CAN运行状态信息服务器，add by 2019.09.6
         QTcpSocket *pTcpSocketServerCANRUN;//TCP通信CAN运行状态信息套接字
         QTcpServer *m_pTcpServerCANFAULT; //TCP通信CAN故障状态信息服务器，add by 2019.09.6
         QTcpSocket *pTcpSocketServerCANFAULT;//TCP通信CAN故障状态信息套接字
         QTcpServer *m_pTcpServerPROTECT; //TCP通信控制和保护信息服务器，add by 2019.09.11
         QTcpSocket *pTcpSocketServerPROTECT;//TCP通信控制和保护信息套接字
         QTcpServer *m_pTcpServerBasic; //TCP通信基本参数设置服务器，add by 2019.12.13
         QTcpSocket *pTcpSocketServerBasic;//TCP通信基本参数设置套接字
         QTcpServer *m_pTcpServerChain; //TCP通信连锁设置服务器，add by 2019.12.13
         QTcpSocket *pTcpSocketServerChain;//TCP通信连锁设置套接字
         QTcpServer *m_pTcpServerAdj; //TCP通信� �准系数服务器，add by 2019.12.13
         QTcpSocket *pTcpSocketServerAdj;//TCP通信� �准系数套接字
private:
              int                 m_iRoletype;               //角色类型变量 add by 2020.08.15
        CLogindlg             m_logindlg;                //"输入密� �"对话框对象
        CPasswordSetdlg     m_Pwdsetdlg;           //"密� �设置"对话框对象

        CAdjcoefdlg          *m_pAdjcoefdlg;       //"� �� �系数"对话框对象
        CChainsetdlg         *m_pChainsetdlg;      //"连锁屏蔽设置"对话框对象指针
        CThresholdsetdlg      m_Thresholdsetdlg;   //"保护阈值设置"对话框对象
        CTempMonitorWidget    *m_pTempmonitorWdgt;   //"温度监控"对话框对象
        CFaultConditionWidget m_FaultCondWdgt;     //"故障状态"对话框对象
        CRunningStatusWidget  *m_pRunStaWdget;       //"运行状态"对话框对象
        CHiscurveWidget       m_HiscurveWdget;     //"历史曲线"对话框对象
        CInvalidSetdlg        m_Invalidsetdlg;     //"� 效设置"对话框对象
        CDCSetdlg             m_DCSetdlg;          //"直流调节"对话框对象
        CGainSetdlg           m_GainSetdlg;        //"增益设置"对话框对象,add by 2019.05.13
        CBasicParaSetdlg      m_BasicParaSetdlg;   //"基本参数"对话框对象，add by 2019.06.01
        CJudgeProc   m_JudgeProc;         // 检测保护类对象，add by 2019.05.18
        QStringList  m_strlistGenModuProc;//通用模块(除了序号29)list,add by 2019.05.21
        QStringList  m_strlistAddProc;    //� 判的保护(数据源为GPIO)，add by 2019.07.15
        CCountDownWidget m_CountDownWdgt;   //"倒计时提示"对话框,add by 2019.05.26
        CKeyBoardDlg m_KeyBoardDlg;   //数字键盘类对象
        CSyssetdlg m_Syssetdlg;//add by 2020.08.10
private:
        GPIODataRecvThread *m_pGPIORecvThread;     //GPIO报文接收数据线程类指针;2018-12-11
private:
     int m_iDCINPUTVoltageCtlCnt;//功率模块输入直流电压计数器
     int m_iIGBTTempCtlCnt;  //IGBT温度监控报文计数
     int m_iIDUCTTempCtlCnt; //电感温度监控报文计数
     int m_iFaultCnt;         //故障运行状态报文计数
     quint64 m_itotaltime;        //seconds
      quint64 m_ithistime;        //本次时间 add by 2020.08.15
     int m_iSumlast;  //最后一次运行时间
     int m_isecondcnt;        //0-59秒
     CGPIORW m_Gpiorw;//GPIO读写类对象
     int m_iMode;     //1-正常模式；0-异常模式
     QString m_strHisfilepath;//历史文件路径
     int m_iCountDownTime;
     qint64 linvalidsetValue;
     qint64 lRuningtime;
     qint64 lremaintime;
private:
     QIcon m_greenicon; //绿色图� �
     QIcon m_redicon;   //红色图� �
     QIcon m_yellowicon;//黄色图� �

     QIcon m_ybonicon;  //压板-合图� �
     QIcon m_ybofficon; //压板-开图� �

     QColor m_defaultBgColor;
     QColor m_mouseclickColor;
     QColor m_jjtjBgColor;
     QColor m_jjtjclickedColor;
     QIcon m_adjcoeficon;
     QIcon m_chainseticon;
     QIcon m_procvalueicon;
     QIcon m_dcseticon;
     QIcon m_invalidseticon;
     QIcon m_procfuncicon;
     QIcon m_longrangectlicon;
     QIcon m_tempericon;
     QIcon m_faultstatusicon;
     QIcon m_runningicon;
     QIcon m_hiscurveicon;
private:
     QString m_strProcType;       //待显示的保护类型信息
        bool m_isFlash;//是否闪烁
     QString m_strjjtj;//紧急停机
     QString m_strhtgwy;//滑台过位移
     QString m_strzdtgwy;//振动台过位移
     QString m_strhtdyw;//滑台低液位
     QString m_strzdtlq;//振动台冷却
     QString m_strhtqy;//滑台轴承低压
     QString m_strzdtgw;//振动台过温
     QString m_strezgwy;//耳轴过位移
     QString m_strgfrjbh;//功放热继保护
     QString m_strjyzcdy;//静压轴承低压
     QString m_strmbh;   //门保护
     QString m_strhtqyw;//主柜整流桥过温
     QString m_strxtlqdy;//系统冷却单元
     QString m_strInfo;  //提示
     QString m_strgainTips;  //增益设置提示
     QString m_strYes;//"是"提示
     QString m_strNo; //"否"提示
     QString m_strWait60s;//等待60s提示
     QString m_strLacktime;
     QString m_strOverime;
     STRU_CHAINSETDATA m_ChainSetData;//连锁设置结构体对象,add by 2019.04.13
     CInifileparse m_Inifile;
     STRU_BASICPARA m_struBasicpara;
     STRU_ADJCOEF m_struAdjcoef;
     STRU_TOTALRUNNING m_struTotaltime;
     STRU_STATUSRECORD m_struStatus;
     QVector<STR_STATUSDATA> m_vec_statusData;
     int m_iCurrPage; //当前页数,add by 2019.07.14
     int m_iTotalPage;//总页数,add by 2019.07.14
     int m_iRemindNum;//余数,add by 2019.07.14

private:
    Ui::mainWindow  *m_pUi;
    QString m_strFriendlytips;//友情提示语
    QString m_strResetTips;//“可以进行功放复位操作”的提示语
    CCANDataRW m_CANDatarw;
    STRU_RUNNINGSTATUS m_struRunningDATA[MAX_SIZE];
    STRU_FAULTSTATUS m_struLeftFaultDATA[MAX_SIZE/2]; //放在左边的故障状态数据
    STRU_FAULTSTATUS m_struRightFaultDATA[MAX_SIZE/2];//放在右边的故障状态数据
    STRU_INPUTDCVOLTAGEMONI m_struDCINPUTVoltagectlDATA[MAX_SIZE];
    STRU_IGBTTEMPERATUREMONI m_struIGBTTempctlDATA[MAX_SIZE];
    STRU_IDUCTTEMPERATUREMONI m_struIDUCTTempctlDATA[MAX_SIZE];
    int m_iAnalogCnt;//主画面模拟数据计数器,add by 2019.05.26
    int m_iCANDataCnt;//CAN数据显示计数器，add by 2019.09.05
    QString m_strInvalidinfo;             //不合法提示
    QString m_strErrinfo;          //错误提示语
private:
    QString m_strMainWindow;       //主界面
    QString m_strSubcabinetctl;     //从柜控制信息
    QString m_strStatusrecord;      //状态记录
    QString m_strSettings;          //设置选择
    QString m_strSwitchstatus;      //主柜开关状态
    QString m_strLanguage;          //语言
    QString m_strPoweramplstate;     //功放状态
    QString m_strtotaloutputVolt;   //功放总输出电压
    QString m_strtotaloutputCurr;   //功放总输出电流
    QString m_strExcitationvolt;     //励磁电压
    QString m_strExcitationcurr;     //励磁电流
    QString m_strPhaseAVoltage;      //A相电压
    QString m_strPhaseBVoltage;      //B相电压
    QString m_strPhaseCVoltage;      //C相电压
    QString m_strStationindicator;    //状态指示灯
    QString m_strRunning;            //运行
    QString m_strCooling;             //冷却
    QString m_strExcitation;          //励磁
    QString m_strReady;               //准备
    QString m_strGain;                //增益
    QString m_strFault;               //故障
    QString m_strPoweramplctl;        //功放控制
    QString m_strStart;               //启动
    QString m_strStop;                //停止
    QString m_strReset;               //复位
    QString m_strGainctl;             //增益控制
    QString m_strSwitch;              //开关
    QString m_strGear;                //挡位
    QString m_strMessagefeedback;     //消息反馈
    QString m_strConnection;          //连接状态
    QString m_strEstop;         //急停状态，add by 2020.11.25
    QString m_strProtecttype;         //保护类型
    QString m_strSubcabinetNum;       //分柜号
    QString m_strSubcabinetInfo;      //分柜开关量状态
    QString n_fileheaddate;

private:
    CInifileparse  m_IniOutLogParse; //输出日志ini文件读写类对象  add by 2020.11.12
    CInifileparse  m_OutputRecord;//输出日志记录读写类对象 add by 2020.11.12
    QString m_strOutputSaveSuccess;      //输出日志文件保存成功提示语 add by 2020.11.12
    QString m_strOutputSaveFail;      //输出日志文件保存失败提示语 add by 2020.11.12
protected:
      virtual void customEvent(QEvent *event);  //自定义事件处理函数,add by zqc 2018.11.30
      virtual void closeEvent(QCloseEvent *event);	//自定义关闭事件处理函数，add by 2019.07.21


    //add by zw 20220223
public:
    int oflags;
    int fd_beep; //beep fd
    int fd_Err;  //err_input fd
    int fd_pwm;  //pwm fd
    int fd_ad5292; //ad5292 fd
    int fd_ad760601; //ad760601 fd
    int fd_ad760602; //ad760602 fd
    int fd_ioout;  //io_out ctl fd
    unsigned char *p_map;
    static void ErrInput(int signum);
    static void readErrStatus();
    DataReadThread *m_pdataReadThread;
    volatile int i_zyLoadPerc; //???????
    newadjdlg *m_pNewAdjdlg;

public Q_SLOTS:
    void OpenOnePWM(int p,int freq);
    void CloseOnePWM(int p);
    void CloseAllPWM();
    void OpenOneOutIO(int p);
    void CloseOneOutIO(int p);

    void zyNstart_ad5292(int perc);
    void zyStop_ad5292();

    //end add by zw 20220223
};
#endif  //MAIN_WINDOW_H
