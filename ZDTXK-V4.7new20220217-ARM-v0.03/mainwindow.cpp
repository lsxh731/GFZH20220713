/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: mainwindow.cpp
** 摘要: 程序主界面框架类
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.11.27
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波     2018.11.27   V1.0      创建
**
****************************************************************************/
#include <iostream>
#include <qtextedit.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qstringlist.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <QMutex>
#include <QFile>
#include <QFileDialog>
#include <QTabWidget>
#include <QTextStream>
#include <QDateTime>
#include <QProgressBar>
#include <QSlider>

#include "mainwindow.h"
#include "gpiorw.h"
#include "inifileparse.h"
//#include "spi.h"


#ifdef UBUNTU_DEV //Compiler Switch
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/spi/spidev.h>
extern int g_iCounter;
extern struct can_frame g_frame;
extern struct can_frame g_IGBTframe;
extern struct STR_GPIODATA g_GPIOData;
extern QStringList  g_strlistGeneralProc;//add by 2019.05.14
#endif  //Compiler Switch

extern struct STRU_CHAINSETDATA g_ChainSetData;//连锁设置参数-全局变量,add by 2019.05.14
extern STRU_SIMUPROCSET g_SimuProcSet;//add by 2019.05.23
extern QMutex g_Mutex;//add by 2019.05.27
extern STRU_BASICPARA g_struBasicPara;//add by 2019.05.28
extern STRU_ADJCOEF g_struAdjcoef;//add by 2019.07.09
long int data_out;
int g_iLangChange;               //语言切换标识符,1-中文，0-英文

extern QVector<STR_STATUSDATA>g_vec_StatusRecord;//add by 2020.11.10


//add by zw 20220223
int irq;
int fd_err;
unsigned char bf_Err[2];
STRU_NEWFAULTSTATUS g_newfaultstatus;
STRU_ADDATANEW g_newaddata;
extern STRU_NEWADJCOEF m_newAdjcoef;
STRU_NEWADJCOEF g_newAdjcoef;
STRU_NEWCHASETDATA g_newchasetdata;

//end add by zw 20220223

CMymainWindow::CMymainWindow()
{
    m_pUi= new Ui::mainWindow;
    m_pUi->setupUi(this);
    qDebug()<<QApplication::applicationDirPath();
    connect(m_pUi->toolButton_Home,SIGNAL(clicked()),this,SLOT(homeBtn_clicked()));
    connect(m_pUi->toolButton_Slave,SIGNAL(clicked()),this,SLOT(slaveBtn_clicked()));
    connect(m_pUi->toolButton_StaRecord,SIGNAL(clicked()),this,SLOT(staRecordBtn_clicked()));
    connect(m_pUi->toolButton_Set,SIGNAL(clicked()),this,SLOT(setBtn_clicked()));
    connect(m_pUi->toolButton_Master,SIGNAL(clicked()),this,SLOT(masterBtn_clicked()));
    connect(m_pUi->toolButton_Debug,SIGNAL(clicked()),this,SLOT(debugBtn_clicked()));
     m_pUi->toolButton_Home->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     m_pUi->toolButton_Slave->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     m_pUi->toolButton_StaRecord->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     m_pUi->toolButton_Set->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     m_pUi->toolButton_Master->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     m_pUi->toolButton_Debug->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //信号与槽
    connect(m_pUi->toolButton_TempCtl,SIGNAL(clicked()),this,SLOT(tempCtlBtn_clicked()));
    connect(m_pUi->toolButton_FaultSta,SIGNAL(clicked()),this,SLOT(faultStaBtn_clicked()));
    connect(m_pUi->toolButton_RunningSta,SIGNAL(clicked()),this,SLOT(runningStaBtn_clicked()));
    connect(m_pUi->syssetBtn,SIGNAL(clicked()),this,SLOT (syssetBtn_clicked()));//"系统设置"槽函数 add by 2020.08.10
//	connect(m_pUi->OutLogBtn,SIGNAL(clicked()),this,SLOT (OutLogBtn_clicked()));//"输出日志"槽函数 add by 2020.11.12

    m_greenicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"gct_ied_green.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_redicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"gct_ied_red.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_yellowicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png"), QSize(), QIcon::Normal, QIcon::Off);

    initHomePage();
    initStatusPage();
    initSetPage();
    initSlaveControlPage(m_yellowicon);
    initMasterDIPage(m_yellowicon);
    initProctype();
    m_iDCINPUTVoltageCtlCnt = 0;
    m_iIGBTTempCtlCnt = 0;
    m_iIDUCTTempCtlCnt = 0;
    m_iFaultCnt=0;
    m_isecondcnt=0;
    m_CANfd = -1;
    m_nGPIOfd=-1;

#ifdef UBUNTU_DEV //Compiler Switch
    //add by zw 20220223

    /*****************BEEP Open*********************************/
      char *beep_node = "/dev/buzzer_ctl";
      fd_beep = -1;
      if((fd_beep = open(beep_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
      {
           printf("###Mygfzk_BEEP Open failed!###\n");
//           return;
      }
      else
      {
           printf("###Mygfzk_BEEP Open successed!###\n");
      }
      ioctl(fd_beep,0,0); //close beep
    /*****************BEEP Open*********************************/

    /*****************IO_OUT Open*********************************/
      char *ioout_node = "/dev/ioout";
      fd_ioout = -1;
      if((fd_ioout = open(ioout_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
      {
           printf("###Mygfzk_OIOUT Open failed!###\n");
//           return;
      }
      else
      {
           printf("###Mygfzk_IOOUT Open successed!###\n");
      }

    /*****************IO_OUT Open*********************************/

    /*****************ERR_INPUT Open*********************************/
      char *err_node = "/dev/errinput";
      fd_Err = -1;
      if((fd_Err = open(err_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
      {
           printf("###Mygfzk_ErrIuput Open failed!###\n");
//           return;
      }
      else
      {
           printf("###Mygfzk_ErrIuput Open successed!###\n");
      }
      signal(SIGIO, CMymainWindow::ErrInput);
      fcntl(fd_Err, F_SETOWN, getpid());
      oflags = fcntl(fd_Err, F_GETFL);
      fcntl(fd_Err, F_SETFL, oflags | FASYNC);
      irq = -1;
      fd_err = fd_Err;

      g_newfaultstatus.iVIBODFlag = -1;     //振动台过位移
      g_newfaultstatus.iVIBCUFlag = -1;     //振动台冷却故障
      g_newfaultstatus.iVIBOTFlag = -1;     //振动过温
      g_newfaultstatus.iSTODFlag = -1;      //滑台过位移保护
      g_newfaultstatus.iSTUPFlag = -1;      //滑台欠压
      g_newfaultstatus.iSTOTFlag = -1;      //滑台过温
      g_newfaultstatus.iSTOLFlag = -1;      //滑台欠液位
      g_newfaultstatus.iRELAYFlag = -1;     //功放热继保护
      g_newfaultstatus.iDOORFlag = -1;      //门保护
      g_newfaultstatus.iHBUPFlag = -1;      //静压轴承欠压
      g_newfaultstatus.iEXT1Flag = -1;      //自定义1
      g_newfaultstatus.iEXT2Flag = -1;      //自定义2
      g_newfaultstatus.iEXT3Flag = -1;      //自定义3
      g_newfaultstatus.iEXT4Flag = -1;      //自定义4
      g_newfaultstatus.iESTOPFlag = -1;     //紧急停机
      g_newfaultstatus.iOT1Flag = -1;       //从柜1整流桥过温1
      g_newfaultstatus.iOT2Flag = -1;       //从柜1整流桥过温2
      g_newfaultstatus.iOT3Flag = -1;       //从柜1整流桥过温3
      g_newfaultstatus.iOT4Flag = -1;       //从柜1整流桥过温4
      g_newfaultstatus.iSESTOPFlag = -1;    //S紧急停机
      g_newfaultstatus.iFAULT1Flag = -1;    //从柜1错误信号
      g_newfaultstatus.iFAULT2Flag = -1;    //从柜2错误信号
      g_newfaultstatus.iFAULT3Flag = -1;    //从柜3错误信号
      g_newfaultstatus.iFAULT4Flag = -1;    //从柜4错误信号
      g_newfaultstatus.iKEYCOL6Flag = -1;   //VOL- for test
      for(int i=0;i<25;i++)
      {
          g_newfaultstatus.iFaultValue[i] = -1;
      }

    /************ERR_INPUT Open*************************************/

    /*****************PWM Open*********************************/
      char *pwm_node = "/dev/gfpwm";
      fd_pwm = -1;
      if((fd_pwm = open(pwm_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
      {
           printf("###Mygfzk_PWM Open failed!###\n");
//           return;
      }
      else
      {
           printf("###Mygfzk_PWM Open successed!###\n");
      }

    /************PWM Open*************************************/

    /*****************AD760601 Open*********************************/
        char *ad760601_node = "/dev/ad760601";
        if((fd_ad760601 = open(ad760601_node, O_RDWR))<0)
        {
            printf("###Mygfzk_AD760601_SPI Open failed!###\n");
//            return;
        }
        else
        {
            printf("###Mygfzk_AD760601_SPI Open successed!###\n");
        }
        int ret;
        static uint8_t mode01 = SPI_MODE_0;
        ret = ioctl(fd_ad760601, SPI_IOC_WR_MODE, &mode01);
        if (ret == -1)
            printf("can't set spi0.0 mode");

        ret = ioctl(fd_ad760601, SPI_IOC_RD_MODE, &mode01);
        if (ret == -1)
            printf("can't get spi0.0 mode");

        static uint8_t bits01 = 8;
        ret = ioctl(fd_ad760601, SPI_IOC_WR_BITS_PER_WORD, &bits01);
        if (ret == -1)
            printf("can't set spi0.0 bits per word\n");

        ret = ioctl(fd_ad760601, SPI_IOC_RD_BITS_PER_WORD, &bits01);
        if (ret == -1)
            printf("can't get spi0.0 bits per word\n");

        static uint32_t speed01 = 10*1000*1000;//10M;
        ret = ioctl(fd_ad760601, SPI_IOC_WR_MAX_SPEED_HZ, &speed01);
        if (ret == -1)
            printf("can't set spi0.0 max speed hz\n");

        ret = ioctl(fd_ad760601, SPI_IOC_RD_MAX_SPEED_HZ, &speed01);
        if (ret == -1)
            printf("can't get spi0.0 max speed hz\n");

        printf("spi0.0 mode: %d\n", mode01);
        printf("spi0.0 bits per word: %d\n", bits01);
        printf("spi0.0 max speed: %d Hz (%d KHz)\n", speed01, speed01/1000);

    /************AD760601 Open*************************************/

    /*****************AD760602 Open*********************************/
      char *ad760602_node = "/dev/ad760602";
      if((fd_ad760602 = open(ad760602_node, O_RDWR))<0)
      {
          printf("###Mygfzk_AD760602_SPI Open failed!###\n");
  //        return;
      }
      else
      {
          printf("###Mygfzk_AD760602_SPI Open successed!###\n");
      }
      static uint8_t mode02 = SPI_MODE_0;
      ret = ioctl(fd_ad760602, SPI_IOC_WR_MODE, &mode02);
      if (ret == -1)
          printf("can't set spi1.0 mode");

      ret = ioctl(fd_ad760602, SPI_IOC_RD_MODE, &mode02);
      if (ret == -1)
          printf("can't get spi1.0 mode");

      static uint8_t bits02 = 8;
      ret = ioctl(fd_ad760602, SPI_IOC_WR_BITS_PER_WORD, &bits02);
      if (ret == -1)
          printf("can't set spi1.0 bits per word\n");

      ret = ioctl(fd_ad760602, SPI_IOC_RD_BITS_PER_WORD, &bits02);
      if (ret == -1)
          printf("can't get spi1.0 bits per word\n");

      static uint32_t speed02 = 10*1000*1000;//10M;
      ret = ioctl(fd_ad760602, SPI_IOC_WR_MAX_SPEED_HZ, &speed02);
      if (ret == -1)
          printf("can't set spi1.0 max speed hz\n");

      ret = ioctl(fd_ad760602, SPI_IOC_RD_MAX_SPEED_HZ, &speed02);
      if (ret == -1)
          printf("can't get spi1.0 max speed hz\n");

      printf("spi1.0 mode: %d\n", mode02);
      printf("spi1.0 bits per word: %d\n", bits02);
      printf("spi1.0 max speed: %d Hz (%d KHz)\n", speed02, speed02/1000);

      //初始化adc数据采集保存结构体
      memset(&g_newaddata,0,sizeof(g_newaddata));
      g_newaddata.iRunningState = -1;
      g_newaddata.iCoolingState = -1;
      g_newaddata.iExcitationState = -1;
      g_newaddata.iReadyState = -1;
      g_newaddata.iGainState = -1;
      g_newaddata.iFaultState = -1;
      for(int i=0;i<4;i++)
      {
         //从柜运行状态量初始化
        g_newaddata.iSlaveStaValue[i]=-1;
      }

      //内存映射
      /*
      p_map = (unsigned char *)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_ad760602, 0);
      if(p_map == (void *)-1)
      {
          printf("mmap fail\n");
      }
      for(i = 0;i < 10;i++)
      {
          printf("p_map[%d]=%d\n",i,p_map[i]);
      }
      */
    /************AD760602 Open*************************************/

    /*****************AD5292 Open*********************************/
          char *ad5292_node = "/dev/ad5292";
          if((fd_ad5292 = open(ad5292_node, O_RDWR))<0)
          {
              printf("###Mygfzk_AD5292_SPI Open failed!###\n");
  //            return;
          }
          else
          {
              printf("###Mygfzk_AD5292_SPI Open successed!###\n");
          }
          static uint8_t mode03 = SPI_MODE_0;
          ret = ioctl(fd_ad5292, SPI_IOC_WR_MODE, &mode03);
          if (ret == -1)
              printf("can't set spi2.0 mode");

          ret = ioctl(fd_ad5292, SPI_IOC_RD_MODE, &mode03);
          if (ret == -1)
              printf("can't get spi2.0 mode");

          static uint8_t bits03 = 8;
          ret = ioctl(fd_ad5292, SPI_IOC_WR_BITS_PER_WORD, &bits03);
          if (ret == -1)
              printf("can't set spi2.0 bits per word\n");

          ret = ioctl(fd_ad5292, SPI_IOC_RD_BITS_PER_WORD, &bits03);
          if (ret == -1)
              printf("can't get spi2.0 bits per word\n");

          static uint32_t speed03 = 5*1000*1000;//5M;
          ret = ioctl(fd_ad5292, SPI_IOC_WR_MAX_SPEED_HZ, &speed03);
          if (ret == -1)
              printf("can't set spi2.0 max speed hz\n");

          ret = ioctl(fd_ad5292, SPI_IOC_RD_MAX_SPEED_HZ, &speed03);
          if (ret == -1)
              printf("can't get spi2.0 max speed hz\n");

          printf("spi2.0 mode: %d\n", mode03);
          printf("spi2.0 bits per word: %d\n", bits03);
          printf("spi2.0 max speed: %d Hz (%d KHz)\n", speed03, speed03/1000);
          i_zyLoadPerc = 0; //初始化增益加载比例为0

    /************AD5292 Open*************************************/

    //硬件测试代码
//          unsigned char bf_cmd[1];
//          bf_cmd[0] = 0x20;
//          ret = write(fd_ad5292,bf_cmd,1);
          zyNstart_ad5292(50);
          usleep(3000000);
          zyStop_ad5292();
#ifdef UBUNTU_DEV //Compiler Switch
          ioctl(fd_ioout,1,EXT21);  //for test pull up err_input pin

//          ioctl(fd_ioout,1,COOLING);
//          ioctl(fd_ioout,1,FIELD);
//          ioctl(fd_ioout,1,FAN);
//          ioctl(fd_ioout,1,HB);
//          ioctl(fd_ioout,1,ST);
//          ioctl(fd_ioout,1,K1_0);
//          ioctl(fd_ioout,1,K1_1);

//          ioctl(fd_ioout,1,K2_0);
//          ioctl(fd_ioout,1,K2_1);
//          ioctl(fd_ioout,1,K3_0);
//          ioctl(fd_ioout,1,K3_1);
//          ioctl(fd_ioout,1,K4_0);
//          ioctl(fd_ioout,1,K4_1);
//          ioctl(fd_ioout,1,RUN);
//          ioctl(fd_ioout,1,CUS12EN);
#endif

    //end add by zw 20220223

    /*****************GPIO Open*********************************/
//    char *gpio_node = "/dev/gpiofpga_ctl";
//     if((m_nGPIOfd = open(gpio_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
//     {
//           printf("GPIO Open %s failed!\n", gpio_node);
//           return;
//      }
//      printf("GPIO Open success!\n");

    /************CAN Open*************************************/
    m_CANfd=openSerialPort();

    if (m_CANfd	 < 0)
    {
        //QMessageBox::warning(this, tr("Error"), tr("Fail to open serial port!"));
        printf("Fail to open serial port=%d\n",m_CANfd);
        return ;
    }
    for(int i=0;i<MAX_SIZE;i++)
    {
          //运行状态结构体初始化
            m_struRunningDATA[i].iRestartprocFlag=-1;
            m_struRunningDATA[i].iNormaloperFlag=-1;
            m_struRunningDATA[i].iFaultProtFlag=-1;
            m_struRunningDATA[i].iFaultlockFlag=-1;
            m_struRunningDATA[i].iProtectedTimes=-1;
            m_struRunningDATA[i].iBlockpulseFlag=-1;
            m_struRunningDATA[i].iRecstartsigFlag=-1;
            m_struRunningDATA[i].iRecshutsigFlag=-1;
            //温度监控结构体初始化
            m_struIGBTTempctlDATA[i].fIGBT1Temper=0.0;
            m_struIGBTTempctlDATA[i].fIGBT2Temper=0.0;

            m_struIDUCTTempctlDATA[i].fIDUCT1Temper=0.0;
            m_struIDUCTTempctlDATA[i].fIDUCT2Temper=0.0;

            m_struDCINPUTVoltagectlDATA[i].fINPUTDCVoltage=0.0;
            m_struIGBTTempctlDATA[i].fOUTPUTACCurrent=0.0;
            m_struIDUCTTempctlDATA[i].fOUTPUTACVoltage=0.0;
    }
     for(int j=0;j<(MAX_SIZE/2);j++)
     {
          //故障状态结构体初始化(左边)
            m_struLeftFaultDATA[j].iOutovervoltFlag=-1;
            m_struLeftFaultDATA[j].iDCovervoltFlag=-1;
            m_struLeftFaultDATA[j].iDCundervoltFlag=-1;
            m_struLeftFaultDATA[j].iACcurrentwarnFlag=-1;
            m_struLeftFaultDATA[j].iACcurrentprocFlag=-1;
            m_struLeftFaultDATA[j].iIGBT1overtempFlag=-1;
            m_struLeftFaultDATA[j].iIGBT2overtempFlag=-1;
            m_struLeftFaultDATA[j].iIndu1overtempFlag=-1;
            m_struLeftFaultDATA[j].iIndu2overtempFlag=-1;
            m_struLeftFaultDATA[j].iDripulseblockFlag=-1;
            m_struLeftFaultDATA[j].iDigspecinterFlag=-1;
            m_struLeftFaultDATA[j].iAnaspecampoverFlag=-1;
            m_struLeftFaultDATA[j].iAnaspecfreqoverFlag=-1;
            m_struLeftFaultDATA[j].iDigspecampoverFlag=-1;
            m_struLeftFaultDATA[j].iDigspecfreqoverFlag=-1;
            m_struLeftFaultDATA[j].iIGBT1driprocFlag=-1;
            m_struLeftFaultDATA[j].iIGBT2driprocFlag=-1;
            m_struLeftFaultDATA[j].iIGBT3driprocFlag=-1;
            m_struLeftFaultDATA[j].iIGBT4driprocFlag=-1;
            m_struLeftFaultDATA[j].iIGBT5driprocFlag=-1;
            m_struLeftFaultDATA[j].iIGBT6driprocFlag=-1;
            m_struLeftFaultDATA[j].iOutputvoltwarnFlag=-1;
            //故障状态结构体初始化(右边)
            m_struRightFaultDATA[j].iOutovervoltFlag=-1;
            m_struRightFaultDATA[j].iDCovervoltFlag=-1;
            m_struRightFaultDATA[j].iDCundervoltFlag=-1;
            m_struRightFaultDATA[j].iACcurrentwarnFlag=-1;
            m_struRightFaultDATA[j].iACcurrentprocFlag=-1;
            m_struRightFaultDATA[j].iIGBT1overtempFlag=-1;
            m_struRightFaultDATA[j].iIGBT2overtempFlag=-1;
            m_struRightFaultDATA[j].iIndu1overtempFlag=-1;
            m_struRightFaultDATA[j].iIndu2overtempFlag=-1;
            m_struRightFaultDATA[j].iDripulseblockFlag=-1;
            m_struRightFaultDATA[j].iDigspecinterFlag=-1;
            m_struRightFaultDATA[j].iAnaspecampoverFlag=-1;
            m_struRightFaultDATA[j].iAnaspecfreqoverFlag=-1;
            m_struRightFaultDATA[j].iDigspecampoverFlag=-1;
            m_struRightFaultDATA[j].iDigspecfreqoverFlag=-1;
            m_struRightFaultDATA[j].iIGBT1driprocFlag=-1;
            m_struRightFaultDATA[j].iIGBT2driprocFlag=-1;
            m_struRightFaultDATA[j].iIGBT3driprocFlag=-1;
            m_struRightFaultDATA[j].iIGBT4driprocFlag=-1;
            m_struRightFaultDATA[j].iIGBT5driprocFlag=-1;
            m_struRightFaultDATA[j].iIGBT6driprocFlag=-1;
            m_struRightFaultDATA[j].iOutputvoltwarnFlag=-1;
     }
    m_notifier = new QSocketNotifier(m_CANfd, QSocketNotifier::Read, this);
    connect(m_notifier, SIGNAL(activated(int)), this, SLOT(on_recvCANTempCtlCANRPT()));//add by 2019.05.21
    m_isGenModuleProcExist=false;//add by 2019.05.25
    m_pGPIORecvThread =NULL;
    m_pGPIORecvThread = new GPIODataRecvThread(this,m_nGPIOfd);
    //add by zw 20220223
    m_pGPIORecvThread->fd_ad02 = fd_ad760602;
    OpenOnePWM(IMX_PWM2,m_pGPIORecvThread->pwm2Freq);
    //end add by zw 20220223
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_5C,write_data_0+qPow(2,10),m_nGPIOfd);//初始化滑块到0，add by 2019.05.30
    delay();
    //初始化熄灭"报警灯",add by 2019.04.12
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_84,write_data_0,m_nGPIOfd);
    m_pGPIORecvThread->start();

    //add by zw 20220223
    m_pdataReadThread = NULL;
    m_pdataReadThread = new DataReadThread(this,fd_ad760601);
    m_pdataReadThread->i_pGPIOdataThread = m_pGPIORecvThread;
    m_pdataReadThread->fd_out = fd_ioout;
    m_pdataReadThread->start();
    //end add by zw 20220223

    printf("####m_pGPIORecvThread->start()####\n");
    m_pTimer1s=new QTimer(this);//add by 2019.05.18
    m_pTimer3s=new QTimer(this);
    m_pTimer5s=new QTimer(this);
    m_pTimer60s=new QTimer(this);

    connect(m_pTimer1s, SIGNAL(timeout()), this, SLOT(waiting1second()));//add by 2019.05.18
    connect(m_pTimer3s, SIGNAL(timeout()), this, SLOT(waiting3second()));
    connect(m_pTimer5s, SIGNAL(timeout()), this, SLOT(waiting5second()));
    connect(m_pTimer60s, SIGNAL(timeout()), this, SLOT(waiting60second()));
    printf("####CMymainWindow init() end ####\n");

#endif //Compiler Switch
    m_pTcpServer = new QTcpServer();
    pTcpSocketServer =new QTcpSocket();
    m_pTcpServerCANTEMP = new QTcpServer();
    pTcpSocketServerCANTEMP =new QTcpSocket();
    m_pTcpServerCANRUN = new QTcpServer();
    pTcpSocketServerCANRUN =new QTcpSocket();
    m_pTcpServerCANFAULT = new QTcpServer();
    pTcpSocketServerCANFAULT =new QTcpSocket();
    m_pTcpServerPROTECT = new QTcpServer();
    pTcpSocketServerPROTECT =new QTcpSocket();
    m_pTcpServerBasic = new QTcpServer();
    pTcpSocketServerBasic =new QTcpSocket();
    m_pTcpServerChain = new QTcpServer();
    pTcpSocketServerChain =new QTcpSocket();
    m_pTcpServerAdj = new QTcpServer();
    pTcpSocketServerAdj =new QTcpSocket();

    if(readStatusRecordFile())
    {
        printf("#######It is correct to readStatusRecordFile##########\n");
        firstBtn_clicked();     //默认首页显示
    }
    else
        printf("#########Fail to readStatusRecordFile#########\n");
    linvalidsetValue=0;
    lRuningtime=0;
    lremaintime=0;

    if(!m_Inifile.readInifile(m_struTotaltime))
    {
        m_struTotaltime.lSetValue=0.0;
    }
        linvalidsetValue = m_struTotaltime.lSetValue;
        lRuningtime=m_struStatus.lTotaltime;
        lremaintime= linvalidsetValue-lRuningtime;
//		QTimer::singleShot(1000, this, SLOT(slotStartCheck()));

        m_iMode=DEBUG_MODE;


}
CMymainWindow::~CMymainWindow()
{
    delete pTcpSocketServer;
    delete m_pTcpServer;
    delete pTcpSocketServerCANTEMP;
    delete m_pTcpServerCANTEMP;
    delete pTcpSocketServerCANRUN;
    delete m_pTcpServerCANRUN;
    delete pTcpSocketServerCANFAULT;
    delete m_pTcpServerCANFAULT;
    delete pTcpSocketServerPROTECT;
    delete m_pTcpServerPROTECT;
    delete pTcpSocketServerBasic;
    delete m_pTcpServerBasic;
    delete pTcpSocketServerChain;
    delete m_pTcpServerChain;
    delete pTcpSocketServerAdj;
    delete m_pTcpServerAdj;
#ifdef UBUNTU_DEV //Compiler Switch

        if (m_notifier)
        {
            delete m_notifier;
            m_notifier = NULL;
        }
        //printf("1\n");
        if (m_CANfd >= 0)
        {
            ::close(m_CANfd);
            m_CANfd = -1;
        }
        //printf("2\n");
        //线程资源析构
        if (m_pGPIORecvThread!=NULL)
        {
            if(m_pGPIORecvThread->isRunning())
            {
                m_pGPIORecvThread->stop();
            }
            delete m_pGPIORecvThread;
            m_pGPIORecvThread = NULL;
        }
        //线程资源析构
        if (m_pdataReadThread!=NULL)
        {
            if(m_pdataReadThread->isRunning())
            {
                m_pdataReadThread->stop();
            }
            delete m_pdataReadThread;
            m_pdataReadThread = NULL;
        }
        //printf("3\n");
        if (m_nGPIOfd >= 0)
        {
            ::close(m_nGPIOfd);
            m_nGPIOfd = -1;
        }
        //printf("4\n");
        //定时器资源析构，add by 2019.07.21
        if(NULL!=m_pTimer1s)
        {
            m_pTimer1s->stop();
            delete m_pTimer1s;
            m_pTimer1s=NULL;
        }
        if(NULL!=m_pTimer3s)
        {
            m_pTimer3s->stop();
            delete m_pTimer3s;
            m_pTimer3s=NULL;
        }
        if(NULL!=m_pTimer5s)
        {
            m_pTimer5s->stop();
            delete m_pTimer5s;
            m_pTimer5s=NULL;
        }
        if(NULL!=m_pTimer60s)
        {
            m_pTimer60s->stop();
            delete m_pTimer60s;
            m_pTimer60s=NULL;
        }
        //printf("5\n");
        //子窗口资源析构
        if(NULL!=m_pChainsetdlg)
        {
            delete m_pChainsetdlg;
            m_pChainsetdlg=NULL;
        }
        //printf("6\n");
        if(NULL!=m_pAdjcoefdlg)
        {
            delete m_pAdjcoefdlg;
            m_pAdjcoefdlg=NULL;
        }
        //printf("7\n");
        if(NULL!=m_pTempmonitorWdgt)
        {
            delete m_pTempmonitorWdgt;
            m_pTempmonitorWdgt=NULL;
        }
        //printf("8\n");
        if(NULL!=m_pRunStaWdget)
        {
            delete m_pRunStaWdget;
            m_pRunStaWdget=NULL;
        }
        //printf("9\n");
        //主窗口资源析构
        delete m_pUi;
        m_pUi=NULL;
        //printf("10\n");
#endif     //Compiler Switch
}
//校准系数设置-槽函数@@@
void CMymainWindow::adjBtn_clicked()
{
//    m_pAdjcoefdlg->init();//恢复出厂设置时重新初始化，add by 2020.11.23
    //add by zw 20220223
    m_pNewAdjdlg->show();
    //end add by zw 20220223
    m_pUi->adjBtn->setBackgroundColor(m_mouseclickColor);
//    m_pAdjcoefdlg->exec();
    //add by zw 20220223
    m_pNewAdjdlg->exec();
    //end add by zw 20220223
    m_pUi->adjBtn->setBackgroundColor(m_defaultBgColor);
}
//连锁设置-槽函数@@@
void CMymainWindow::chainBtn_clicked()
{
    m_pChainsetdlg->init();//恢复出厂设置时重新初始化，add by 2020.11.24
    m_pUi->chainBtn->setBackgroundColor(m_mouseclickColor);
    m_pChainsetdlg->exec();
    m_ChainSetData=m_pChainsetdlg->getChainSetData();//获取连锁参数数据，add by 2019.04.13
    m_iMode=m_pChainsetdlg->getMode();
    if(m_iMode==DEBUG_MODE)
    {
        m_pUi->toolButton_zystart->setEnabled(true);
    }
    else if(m_iMode==NORMAL_MODE)
    {
        m_pUi->toolButton_zystart->setEnabled(false);
    }

    memcpy(&g_ChainSetData,&m_ChainSetData,sizeof(m_ChainSetData));//更新连锁屏蔽设置参数给全局变量g_ChainSetData,add by 2019.05.25

    m_pUi->chainBtn->setBackgroundColor(m_defaultBgColor);
}
//保护阈值设置-槽函数
//void CMymainWindow::thrBtn_clicked()
//{
//	m_pUi->thrBtn->setBackgroundColor(m_mouseclickColor);
//	int ret =m_logindlg.exec();
//	if(m_logindlg.IsPWDCorrect())
//	{
//		m_logindlg.clearBtn_clicked();//清除密码
//		m_Thresholdsetdlg.exec();
//	}
//	m_pUi->thrBtn->setBackgroundColor(m_defaultBgColor);
//}
//无效设置-槽函数@@@
void CMymainWindow::invalidBtn_clicked()
{
    m_pUi->invalidBtn->setBackgroundColor(m_mouseclickColor);
    m_Invalidsetdlg.exec();
    m_pUi->invalidBtn->setBackgroundColor(m_defaultBgColor);
}
//直流设置-槽函数
//void CMymainWindow::dcBtn_clicked()
//{
//	m_pUi->dcBtn->setBackgroundColor(m_mouseclickColor);
//	m_DCSetdlg.exec();
//	m_pUi->dcBtn->setBackgroundColor(m_defaultBgColor);
//}
//"密码设置"-槽函数
void CMymainWindow::pwdsetBtn_clicked()
{
    m_pUi->pwdsetBtn->setBackgroundColor(m_mouseclickColor);
    m_Pwdsetdlg.clearBtn_clicked();//先清除历史输入痕迹
    m_Pwdsetdlg.getRoletype(m_iRoletype);
    m_Pwdsetdlg.exec();            //再打开密码设置对话框
    m_pUi->pwdsetBtn->setBackgroundColor(m_defaultBgColor);
}
//打开端口
int CMymainWindow::openSerialPort()
{
    int s=-1;
#ifdef UBUNTU_DEV //Compiler Switch
   struct sockaddr_can addr;
   struct ifreq ifr;
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("Create socket failed");
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
//@@@
void CMymainWindow::on_recvCANTempCtlCANRPT()
{
#ifdef UBUNTU_DEV //Compiler Switch
    struct can_frame frame;
    struct can_filter rfilter[64];
    QString strtmep;
    int iCANframetype=0;
    int iCANframeID=0;
    rfilter[0].can_id = CAN_EFF_FLAG | 0x08063001;//用于接收运行状态CAN报文
    rfilter[0].can_mask = CAN_EFF_MASK;
    rfilter[1].can_id = CAN_EFF_FLAG | 0x08073001;
    rfilter[1].can_mask = CAN_EFF_MASK;
    rfilter[2].can_id = CAN_EFF_FLAG | 0x08083001;
    rfilter[2].can_mask = CAN_EFF_MASK;
    rfilter[3].can_id = CAN_EFF_FLAG | 0x08093001;
    rfilter[3].can_mask = CAN_EFF_MASK;
    rfilter[4].can_id = CAN_EFF_FLAG | 0x08063002;
    rfilter[4].can_mask = CAN_EFF_MASK;
    rfilter[5].can_id = CAN_EFF_FLAG | 0x08073002;
    rfilter[5].can_mask = CAN_EFF_MASK;
    rfilter[6].can_id = CAN_EFF_FLAG | 0x08083002;
    rfilter[6].can_mask = CAN_EFF_MASK;
    rfilter[7].can_id = CAN_EFF_FLAG | 0x08093002;
    rfilter[7].can_mask = CAN_EFF_MASK;
    rfilter[8].can_id = CAN_EFF_FLAG | 0x08063003;
    rfilter[8].can_mask = CAN_EFF_MASK;
    rfilter[9].can_id = CAN_EFF_FLAG | 0x08073003;
    rfilter[9].can_mask = CAN_EFF_MASK;
    rfilter[10].can_id = CAN_EFF_FLAG | 0x08083003;
    rfilter[10].can_mask = CAN_EFF_MASK;
    rfilter[11].can_id = CAN_EFF_FLAG | 0x08093003;
    rfilter[11].can_mask = CAN_EFF_MASK;
    rfilter[12].can_id = CAN_EFF_FLAG | 0x08063004;
    rfilter[12].can_mask = CAN_EFF_MASK;
    rfilter[13].can_id = CAN_EFF_FLAG | 0x08073004;
    rfilter[13].can_mask = CAN_EFF_MASK;
    rfilter[14].can_id = CAN_EFF_FLAG | 0x08083004;
    rfilter[14].can_mask = CAN_EFF_MASK;
    rfilter[15].can_id = CAN_EFF_FLAG | 0x08093004;
    rfilter[15].can_mask = CAN_EFF_MASK;

    rfilter[16].can_id = CAN_EFF_FLAG | 0x08063005;
    rfilter[16].can_mask = CAN_EFF_MASK;
    rfilter[17].can_id = CAN_EFF_FLAG | 0x08073005;
    rfilter[17].can_mask = CAN_EFF_MASK;
    rfilter[18].can_id = CAN_EFF_FLAG | 0x08083005;
    rfilter[18].can_mask = CAN_EFF_MASK;
    rfilter[19].can_id = CAN_EFF_FLAG | 0x08093005;
    rfilter[19].can_mask = CAN_EFF_MASK;
    rfilter[20].can_id = CAN_EFF_FLAG | 0x08063006;
    rfilter[20].can_mask = CAN_EFF_MASK;
    rfilter[21].can_id = CAN_EFF_FLAG | 0x08073006;
    rfilter[21].can_mask = CAN_EFF_MASK;
    rfilter[22].can_id = CAN_EFF_FLAG | 0x08083006;
    rfilter[22].can_mask = CAN_EFF_MASK;
    rfilter[23].can_id = CAN_EFF_FLAG | 0x08093006;
    rfilter[23].can_mask = CAN_EFF_MASK;
    rfilter[24].can_id = CAN_EFF_FLAG | 0x08063007;
    rfilter[24].can_mask = CAN_EFF_MASK;
    rfilter[25].can_id = CAN_EFF_FLAG | 0x08073007;
    rfilter[25].can_mask = CAN_EFF_MASK;
    rfilter[26].can_id = CAN_EFF_FLAG | 0x08083007;
    rfilter[26].can_mask = CAN_EFF_MASK;
    rfilter[27].can_id = CAN_EFF_FLAG | 0x08093007;
    rfilter[27].can_mask = CAN_EFF_MASK;
    rfilter[28].can_id = CAN_EFF_FLAG | 0x08063008;
    rfilter[28].can_mask = CAN_EFF_MASK;
    rfilter[29].can_id = CAN_EFF_FLAG | 0x08073008;
    rfilter[29].can_mask = CAN_EFF_MASK;
    rfilter[30].can_id = CAN_EFF_FLAG | 0x08083008;
    rfilter[30].can_mask = CAN_EFF_MASK;
    rfilter[31].can_id = CAN_EFF_FLAG | 0x08093008;
    rfilter[31].can_mask = CAN_EFF_MASK;

    rfilter[32].can_id = CAN_EFF_FLAG | 0x08063009;
    rfilter[32].can_mask = CAN_EFF_MASK;
    rfilter[33].can_id = CAN_EFF_FLAG | 0x08073009;
    rfilter[33].can_mask = CAN_EFF_MASK;
    rfilter[34].can_id = CAN_EFF_FLAG | 0x08083009;
    rfilter[34].can_mask = CAN_EFF_MASK;
    rfilter[35].can_id = CAN_EFF_FLAG | 0x08093009;
    rfilter[35].can_mask = CAN_EFF_MASK;
    rfilter[36].can_id = CAN_EFF_FLAG | 0x0806300a;
    rfilter[36].can_mask = CAN_EFF_MASK;
    rfilter[37].can_id = CAN_EFF_FLAG | 0x0807300a;
    rfilter[37].can_mask = CAN_EFF_MASK;
    rfilter[38].can_id = CAN_EFF_FLAG | 0x0808300a;
    rfilter[38].can_mask = CAN_EFF_MASK;
    rfilter[39].can_id = CAN_EFF_FLAG | 0x0809300a;
    rfilter[39].can_mask = CAN_EFF_MASK;
    rfilter[40].can_id = CAN_EFF_FLAG | 0x0806300b;
    rfilter[40].can_mask = CAN_EFF_MASK;
    rfilter[41].can_id = CAN_EFF_FLAG | 0x0807300b;
    rfilter[41].can_mask = CAN_EFF_MASK;
    rfilter[42].can_id = CAN_EFF_FLAG | 0x0808300b;
    rfilter[42].can_mask = CAN_EFF_MASK;
    rfilter[43].can_id = CAN_EFF_FLAG | 0x0809300b;
    rfilter[43].can_mask = CAN_EFF_MASK;
    rfilter[44].can_id = CAN_EFF_FLAG | 0x0806300c;
    rfilter[44].can_mask = CAN_EFF_MASK;
    rfilter[45].can_id = CAN_EFF_FLAG | 0x0807300c;
    rfilter[45].can_mask = CAN_EFF_MASK;
    rfilter[46].can_id = CAN_EFF_FLAG | 0x0808300c;
    rfilter[46].can_mask = CAN_EFF_MASK;
    rfilter[47].can_id = CAN_EFF_FLAG | 0x0809300c;
    rfilter[47].can_mask = CAN_EFF_MASK;

    rfilter[48].can_id = CAN_EFF_FLAG | 0x0806300d;
    rfilter[48].can_mask = CAN_EFF_MASK;
    rfilter[49].can_id = CAN_EFF_FLAG | 0x0807300d;
    rfilter[49].can_mask = CAN_EFF_MASK;
    rfilter[50].can_id = CAN_EFF_FLAG | 0x0808300d;
    rfilter[50].can_mask = CAN_EFF_MASK;
    rfilter[51].can_id = CAN_EFF_FLAG | 0x0809300d;
    rfilter[51].can_mask = CAN_EFF_MASK;
    rfilter[52].can_id = CAN_EFF_FLAG | 0x0806300e;
    rfilter[52].can_mask = CAN_EFF_MASK;
    rfilter[53].can_id = CAN_EFF_FLAG | 0x0807300e;
    rfilter[53].can_mask = CAN_EFF_MASK;
    rfilter[54].can_id = CAN_EFF_FLAG | 0x0808300e;
    rfilter[54].can_mask = CAN_EFF_MASK;
    rfilter[55].can_id = CAN_EFF_FLAG | 0x0809300e;
    rfilter[55].can_mask = CAN_EFF_MASK;
    rfilter[56].can_id = CAN_EFF_FLAG | 0x0806300f;
    rfilter[56].can_mask = CAN_EFF_MASK;
    rfilter[57].can_id = CAN_EFF_FLAG | 0x0807300f;
    rfilter[57].can_mask = CAN_EFF_MASK;
    rfilter[58].can_id = CAN_EFF_FLAG | 0x0808300f;
    rfilter[58].can_mask = CAN_EFF_MASK;
    rfilter[59].can_id = CAN_EFF_FLAG | 0x0809300f;
    rfilter[59].can_mask = CAN_EFF_MASK;
    rfilter[60].can_id = CAN_EFF_FLAG | 0x08063011;
    rfilter[60].can_mask = CAN_EFF_MASK;
    rfilter[61].can_id = CAN_EFF_FLAG | 0x08073011;
    rfilter[61].can_mask = CAN_EFF_MASK;
    rfilter[62].can_id = CAN_EFF_FLAG | 0x08083011;
    rfilter[62].can_mask = CAN_EFF_MASK;
    rfilter[63].can_id = CAN_EFF_FLAG | 0x08093011;
    rfilter[63].can_mask = CAN_EFF_MASK;

    if(setsockopt(m_CANfd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)) < 0)
    {
        perror("on_recvRunningCANRPT：set receiving filter error\n");
        return;
    }
    //keep reading
    if(read(m_CANfd, &frame, sizeof(frame)) <= 0 )
    {
        perror("on_recvRunningCANRPT：read error\n");
        return;
    }
    iCANframetype=(frame.can_id&0x000F0000)>>16;
    iCANframeID=(frame.can_id&0x000000FF)-1;
    //test
    printf ("%08x####%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-iCANframeID=%d-iCANframetype=%d####\n",frame.can_id,
                frame.data[0],
                frame.data[1],
                frame.data[2],
                frame.data[3],
                frame.data[4],
                frame.data[5],
                frame.data[6],
                frame.data[7],
                iCANframeID,
                iCANframetype);
    //test
    switch(iCANframetype)
    {
        case 6:
            m_CANDatarw.parseRunningStatData(frame,m_struRunningDATA[iCANframeID]);
            break;
        case 7:
            //解析故障状态数据与输入直流电压数据
            if(iCANframeID%2==0)
            {
                m_CANDatarw.parseFaultStatData(frame,m_struLeftFaultDATA[iCANframeID/2],m_struDCINPUTVoltagectlDATA[iCANframeID]);//暂时只有一个模块，2019.04.07
                m_strlistGenModuProc.clear();
                m_isGenModuleProcExist=m_JudgeProc.CheckGenModuleProcExist(1,&m_struLeftFaultDATA[iCANframeID/2],m_strlistGenModuProc);//add by 2019.05.21
            }
            else
            {
                m_CANDatarw.parseFaultStatData(frame,m_struRightFaultDATA[iCANframeID/2],m_struDCINPUTVoltagectlDATA[iCANframeID]);//暂时只有一个模块，2019.04.07
                m_strlistGenModuProc.clear();
                m_isGenModuleProcExist=m_JudgeProc.CheckGenModuleProcExist(1,&m_struRightFaultDATA[iCANframeID/2],m_strlistGenModuProc);//add by 2019.05.21
            }
            //判断是否存在通用的模块保护信息(除了序号29-模块直流欠压)
            if(m_isGenModuleProcExist&&m_GfStartFlag)
            {
                for(int k=0;k<m_strlistGenModuProc.size();k++)
                {
                    if(m_strlistGenModuProc.size()<=0)
                    {
                        break;
                    }
                    else
                    {
                        g_strlistGeneralProc.append(m_strlistGenModuProc.at(k));//记录通用的模块保护信息，add by 2019.05.26
                    }
                }
                m_GfTestPauseFlag=true;//add by 2019.05.22
                //调试信息窗口显示驱动保护信息,add by 2019.05.21
                if(m_strlistGenModuProc.size()==0)
                {
                    return;
                }
                strtmep.append(m_strlistGenModuProc.at(0));
                for(int j=1;j<m_strlistGenModuProc.size();j++)
                {
                    strtmep.append(" ");
                    strtmep.append(m_strlistGenModuProc.at(j));
                    //printf("####m_strlistGenModuProc.at(%d)=%s####\n",j,m_strlistGenModuProc.at(j).toAscii().constData());
                }
                strtmep.append(tr("\n"));
                m_pUi->DebugTextEdit->append(strtmep);
                m_pUi->label_procinfo->setText(strtmep);//add by zqc 2019.07.15
                if(iLongrCtl)
                {
                    PROTECTsendMesg(strtmep);
                }
                m_pGPIORecvThread->createStatusRecordFileByList(m_strlistGenModuProc);//add by zqc 2019.07.15
                m_pUi->DebugTextEdit->setStyleSheet("color:red;border:2px solid gray;");//设置为红色字体
            }
            break;
        case 8:
            m_CANDatarw.parseIGBTTemperCtlData(frame,m_struIGBTTempctlDATA[iCANframeID]);
            break;
        case 9:
            m_CANDatarw.parseIDUCTTemperCtlData(frame,m_struIDUCTTempctlDATA[iCANframeID]);
            break;
        default:
            break;
    }
#endif //Compiler Switch
}

//自定义事件处理函数
void CMymainWindow::customEvent(QEvent *event)
{
 #ifdef UBUNTU_DEV //Compiler-- Switch
  QString strtmep;
  QString strComma="，";
  QDateTime current_date_time =QDateTime::currentDateTime();
  QString strCurrTime =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
   switch(event->type())
    {
    case (QEvent::User+1000):
        {
             m_iAnalogCnt++;
//             if(m_iAnalogCnt%(1000/DELAY_TIME)==0)
//             {
                 //降低主画面电压电流等模拟量数据显示频率,1000ms刷新1次即可,add by 2019.05.26
                showPowerAmpRTdata();
                showSlaveRTdata();
                //add by zw 20220412 for test ad7606
                ADData_show();
                //end add by zw 20220412 for test ad7606
                m_iAnalogCnt=0;
                if(iLongrCtl)
                {
                    GPIOsendMesg();
                    CANTEMPsendMesg();
                    CANRUNsendMesg();
                    CANFAULTsendMesg();

                }
//             }
#ifndef NEWCODE_SW
             //更新"紧急停机"状态灯
             updateDI(g_GPIOData.iMasterDI[0],m_pUi->toolButton_jjtj);
             //更新"滑台过位移"状态灯
             updateDI(g_GPIOData.iMasterDI[1],m_pUi->toolButton_htgwy);
             //更新"振动台过位移"状态灯
             updateDI(g_GPIOData.iMasterDI[2],m_pUi->toolButton_zdtgwy);
             //更新"滑台低液位"状态灯
             updateDI(g_GPIOData.iMasterDI[3],m_pUi->toolButton_htdyw);

             //更新"滑台轴承低压"状态灯
             updateDI(g_GPIOData.iMasterDI[5],m_pUi->toolButton_htzcdy);
              //更新"振动台过温"状态灯
             updateDI(g_GPIOData.iMasterDI[6],m_pUi->toolButton_zdtgw);
             //更新"耳轴过位移"状态灯
             updateDI(g_GPIOData.iMasterDI[7],m_pUi->toolButton_sjjtj);
             //更新"功放热继保护"状态灯
             updateDI(g_GPIOData.iMasterDI[8],m_pUi->toolButton_gfrjbh);
             //更新"静压轴承低压"状态灯
             updateDI(g_GPIOData.iMasterDI[9],m_pUi->toolButton_jyzcdy);
             //更新"门保护"状态灯
             updateDI(g_GPIOData.iMasterDI[10],m_pUi->toolButton_zgmbh);
             //更新"系统冷却单元"状态灯
             updateDI(g_GPIOData.iMasterDI[11],m_pUi->toolButton_xtlqdy);
              //更新"主柜整流器过温"状态灯,add by 2019.05.26
             updateDI(g_GPIOData.iMasterDI[12],m_pUi->toolButton_seldefine4);
#endif
             ShowChainSetStatus();//显示连锁屏蔽设置状态，add by 2019.05.26 +保护指示灯状态 add by zw 20220223
#ifndef NEWCODE_SW
             //更新"分柜1整流器过温"状态灯（分柜）
             updateDI(g_GPIOData.iSlaveDI[0],m_pUi->toolButton_fg1zlqgw);
             //更新"分柜1门保护"状态灯（分柜）
             updateDI(g_GPIOData.iSlaveDI[1],m_pUi->toolButton_fg1mbh);

             //更新"分柜2整流器过温"状态灯（分柜）
             updateDI(g_GPIOData.iSlaveDI[3],m_pUi->toolButton_fg2zlqgw);
             //更新"分柜2门保护"状态灯（分柜）
             updateDI(g_GPIOData.iSlaveDI[2],m_pUi->toolButton_fg2mbh);

             //更新"分柜3整流器过温"状态灯（分柜）
             updateDI(g_GPIOData.iSlaveDI[5],m_pUi->toolButton_fg3zlqgw);
             //更新"分柜3门保护"状态灯（分柜）
             updateDI(g_GPIOData.iSlaveDI[4],m_pUi->toolButton_fg3mbh);

             //更新"分柜4整流器过温"状态灯（分柜）
             updateDI(g_GPIOData.iSlaveDI[6],m_pUi->toolButton_fg4zlqgw);
             //更新"分柜4门保护"状态灯（分柜）
             updateDI(g_GPIOData.iSlaveDI[7],m_pUi->toolButton_fg4mbh);
#endif
#ifdef NEWCODE_SW
             //更新"分柜1整流器过温"状态灯（分柜）
             updateDI(g_newfaultstatus.iOT1Flag,m_pUi->toolButton_fg1zlqgw);
             //更新"分柜1门保护"状态灯（分柜）
             updateDI(g_newfaultstatus.iFAULT1Flag,m_pUi->toolButton_fg1mbh);

             //更新"分柜2整流器过温"状态灯（分柜）
             updateDI(g_newfaultstatus.iOT2Flag,m_pUi->toolButton_fg2zlqgw);
             //更新"分柜2门保护"状态灯（分柜）
             updateDI(g_newfaultstatus.iFAULT2Flag,m_pUi->toolButton_fg2mbh);

             //更新"分柜3整流器过温"状态灯（分柜）
             updateDI(g_newfaultstatus.iOT3Flag,m_pUi->toolButton_fg3zlqgw);
             //更新"分柜3门保护"状态灯（分柜）
             updateDI(g_newfaultstatus.iFAULT3Flag,m_pUi->toolButton_fg3mbh);

             //更新"分柜4整流器过温"状态灯（分柜）
             updateDI(g_newfaultstatus.iOT4Flag,m_pUi->toolButton_fg4zlqgw);
             //更新"分柜4门保护"状态灯（分柜）
             updateDI(g_newfaultstatus.iFAULT4Flag,m_pUi->toolButton_fg4mbh);
#endif

        }
        break;
    case (QEvent::User+2000)://存在内外部通用保护,add by 2019.05.17
        {
//            qDebug()<<"#### this is QEvent::User+2000####";
            m_GfTestPauseFlag=true;
            if(m_GfStartFlag)
            {
                //--未启动功放测试，只显示保护信息，不操作
              strtmep.append(tr("[GfStartFlag=")+QString::number(m_GfStartFlag)+tr("]"));
              strtmep.append(strCurrTime);
              strtmep.append(" ");
              strtmep.append(tr("Exist Protect:"));
              m_strProcType=tr(" ");//add by 2019.07.20
              int nGeneralProc=g_strlistGeneralProc.size();
              if(nGeneralProc>0)
              {
                strtmep.append(g_strlistGeneralProc.at(0));
                m_strProcType.append(g_strlistGeneralProc.at(0));//add by 2019.07.20
                for(int j=1;j<g_strlistGeneralProc.size();j++)
                {
                 strtmep.append(" ");
                 strtmep.append(g_strlistGeneralProc.at(j));
                 m_strProcType.append(" ");//add by 2019.07.20
                 m_strProcType.append(g_strlistGeneralProc.at(j));//add by 2019.07.20
                }
              }
             strtmep.append(tr("\n"));
             m_pUi->DebugTextEdit->append(strtmep);
             m_pUi->label_procinfo->setText(m_strProcType);//add by zqc 2019.07.15
             m_pUi->label_procinfo->setStyleSheet("color:red;border:2px solid gray;");//设置为红色字体
             if(iLongrCtl)
            {
                PROTECTsendMesg(m_strProcType);
             }
            }
        }
        break;
    case (QEvent::User+3000)://不存在内外部通用保护,add by 2019.05.24
          {
//          qDebug()<<"#### this is QEvent::User+3000####";
          if(!m_isGenModuleProcExist)
          {
              //不存在内外部通用保护+模块通用保护（指序号28和序号30）,add by 2019.05.25
               m_GfTestPauseFlag=false;
          }
          }
          break;
    case (QEvent::User+4000):
        {
            //disconnect(m_notifier,0,0,0);
            //printf("disconnect(m_notifier,0,0,0)\n");
        }
    case (QEvent::User+5000)://有最新状态文件生成，可以读取并显示,add by zqc 2019.07.14
        {
            printf("receive QEvent::User+5000\n");
            if(readStatusRecordFile())
            {
                printf("It is correct to readStatusRecordFile\n");
                firstBtn_clicked();     //默认首页显示
            }
        }
        break;
    default:
        break;
    }// switch(event->type())
#endif  //Compiler Switch
}
//@@@
void CMymainWindow::closeEvent(QCloseEvent *event)
{
    if((linvalidsetValue==0.0)||(lremaintime>DELT_FVALUE))
    {
        int ret=-1;
        QString strYes;
        QString strNo;
        QString strTemp;
        QMessageBox *msgBox=new QMessageBox(QMessageBox::Question,
        m_strInfo,
        m_strgainTips,
        QMessageBox::Yes | QMessageBox::No);
        if(g_iLangChange==1)
        {
            strTemp=QApplication::translate("Dialog", "\346\230\257\345\220\246\351\200\200\345\207\272\346\234\254\350\275\257\344\273\266\357\274\237", 0, QApplication::UnicodeUTF8);
        }
        else
        {
            strTemp="Whether to quit";
        }
        msgBox->setText(strTemp);
        msgBox->button(QMessageBox::Yes)->setText(m_strYes);
        // 将原本显示“No”的按钮改为显示“否”
        msgBox->button(QMessageBox::No)->setText(m_strNo);
        // 弹出对话框
        ret=msgBox->exec();
        if(ret==QMessageBox::Yes)
        {
            event->accept();//退出软件
        }
        else if(ret==QMessageBox::No)
        {
            event->ignore();//不退出
        }
    }
    else
    {
        event->accept();
    }
}
//读取状态记录文件,add by 2019.07.14
bool CMymainWindow::readStatusRecordFile()
{
#ifdef WIN_DEV
    QString strStatusfilepath="./debug/statusdata/statusdata.csv";
#else
    QString strStatusfilepath=QApplication::applicationDirPath() + "/statusdata/statusdata.csv";
#endif
     if(!strStatusfilepath.contains(tr("/statusdata/statusdata.csv")))
        {
             printf("no /statusdata/statusdata.csv path exist\n");
             return false;
        }
    QFile file(strStatusfilepath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        printf("####【CMymainWindow::readStatusRecordFile】Fail to open  statusdata file####\n");
        return false;
    }
    QStringList linelist;
    QTextStream in(&file);
    in.setCodec("GB2312");
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
    QString strTemp;
    STR_STATUSDATA tmpStatusData;//由于成员变量有QString类型的，所以不能用memset函数初始化该结构体
    tmpStatusData.fVoltRms=0.00;
    tmpStatusData.fVoltMax=0.00;
    tmpStatusData.fCurrentRms=0.00;
    tmpStatusData.fCurrentMax=0.00;
    m_vec_statusData.clear();
    int recordsize=linelist.size();
    if(recordsize<=1)//防误20190716
    {
        printf("recordsize=%d Error Exist\n",recordsize);
        return false;
    }
    //--倒序赋值,把最新的记录放到最前面
    for(int i=recordsize-1;i>0;i--)
    {
        //报警时间
        strTemp=linelist.at(i).section(',', 0, 0);
        tmpStatusData.strAlarmTime=strTemp;
        //错误(保护)类型
        strTemp=linelist.at(i).section(',', 1, 1);
        tmpStatusData.strErrorType=strTemp;
        //输出电压有效值
        strTemp=linelist.at(i).section(',', 2, 2);
        tmpStatusData.fVoltRms=strTemp.toFloat(&ok);
        //输出电压最大值
        strTemp=linelist.at(i).section(',', 3, 3);
        tmpStatusData.fVoltMax=strTemp.toFloat(&ok);
        //输出电流有效值
        strTemp=linelist.at(i).section(',', 4, 4);
        tmpStatusData.fCurrentRms=strTemp.toFloat(&ok);
        //输出电流最大值
        strTemp=linelist.at(i).section(',', 5, 5);
        tmpStatusData.fCurrentMax=strTemp.toFloat(&ok);
        m_vec_statusData.push_back(tmpStatusData);
    }//for(int i=linelist.size()-1;i>0;i--)
    m_iTotalPage=(recordsize-1)/ROWS_PER_PAGE;//去掉表头计算
    m_iRemindNum=(recordsize-1)%ROWS_PER_PAGE;
    if(m_iRemindNum>0)
    {
       m_iTotalPage=m_iTotalPage+1;
    }
    file.close();
   return true;
}
//显示状态记录信息,add by 2019.07.14
void CMymainWindow::showStatusRecordInfo(QVector<STR_STATUSDATA> vec_statusData,int nCurrPage)
{
    QCoreApplication::processEvents();//避免界面冻结
    int nStaRecSize=vec_statusData.size();
    if(nStaRecSize<=ROWS_PER_PAGE)
    {
        updateStatusRecordTable(1,nStaRecSize);
    }
    else
    {
        printf("begin updateStatusRecordTable(nCurrPage,ROWS_PER_PAGE)\n");
        if((nCurrPage==m_iTotalPage) && (m_iRemindNum!=0))
        {
            updateStatusRecordTable(nCurrPage,m_iRemindNum);
        }
        else
        {
            updateStatusRecordTable(nCurrPage,ROWS_PER_PAGE);
        }
    }
    QCoreApplication::processEvents();//避免界面冻结
}
//显示状态统计信息,add by 2019.07.14
void CMymainWindow::showRecordStatistics(int nRecsize,int nTotalPage)
{
    QCoreApplication::processEvents();//避免界面冻结
    m_pUi->label_totalrecord->setText(QString::number(nRecsize));
    m_pUi->label_totalpage->setText(QString::number(nTotalPage));
    QCoreApplication::processEvents();//避免界面冻结
}
//更新状态记录到表格,add by 2019.07.14
void CMymainWindow::updateStatusRecordTable(int nCurrPage,int nRows)
{
      QCoreApplication::processEvents();//避免界面冻结
      m_pUi->tableWidget->setRowCount(nRows);
      QString strTemp;
      QFont tempfont;
      tempfont.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
      tempfont.setPointSize(16);
      for(int i=0;i<nRows;i++)
      {
          //报警时间
          QTableWidgetItem *newItem0= new QTableWidgetItem(m_vec_statusData.at(i+(nCurrPage-1)*ROWS_PER_PAGE).strAlarmTime);
          newItem0->setFont(tempfont);
          newItem0->setForeground(QBrush(QColor(255, 255, 255)));
          m_pUi->tableWidget->setItem(i, 0, newItem0);
          //错误(保护)类型
          strTemp=m_vec_statusData.at(i+(nCurrPage-1)*ROWS_PER_PAGE).strErrorType;
          QTableWidgetItem *newItem1= new QTableWidgetItem(tr(strTemp.toLocal8Bit()));
          newItem1->setFont(tempfont);
          newItem1->setForeground(QBrush(QColor(255, 255, 255)));
          m_pUi->tableWidget->setItem(i, 1, newItem1);
          //输出电压有效值
          QTableWidgetItem *newItem2= new QTableWidgetItem(QString::number(m_vec_statusData.at(i+(nCurrPage-1)*ROWS_PER_PAGE).fVoltRms,'f',2));
          newItem2->setTextAlignment(Qt::AlignCenter);//居中显示
          newItem2->setFont(tempfont);
          newItem2->setForeground(QBrush(QColor(255, 255, 255)));
          m_pUi->tableWidget->setItem(i, 2, newItem2);
          //输出电压最大值
          QTableWidgetItem *newItem3= new QTableWidgetItem(QString::number(m_vec_statusData.at(i+(nCurrPage-1)*ROWS_PER_PAGE).fVoltMax,'f',2));
          m_pUi->tableWidget->setItem(i, 3, newItem3);
          newItem3->setTextAlignment(Qt::AlignCenter);//居中显示
          newItem3->setFont(tempfont);
          newItem3->setForeground(QBrush(QColor(255, 255, 255)));
          //输出电流有效值
          QTableWidgetItem *newItem4= new QTableWidgetItem(QString::number(m_vec_statusData.at(i+(nCurrPage-1)*ROWS_PER_PAGE).fCurrentRms,'f',2));
          m_pUi->tableWidget->setItem(i, 4, newItem4);
          newItem4->setTextAlignment(Qt::AlignCenter);//居中显示
          newItem4->setFont(tempfont);
          newItem4->setForeground(QBrush(QColor(255, 255, 255)));
          //输出电流最大值
          QTableWidgetItem *newItem5= new QTableWidgetItem(QString::number(m_vec_statusData.at(i+(nCurrPage-1)*ROWS_PER_PAGE).fCurrentMax,'f',2));
          m_pUi->tableWidget->setItem(i, 5, newItem5);
          newItem5->setTextAlignment(Qt::AlignCenter);//居中显示
          newItem5->setFont(tempfont);
          newItem5->setForeground(QBrush(QColor(255, 255, 255)));
      }//for(int i=0;i<nRows;i++)
      //隔行变色
      for (int i = 0;i <  m_pUi->tableWidget->rowCount();i++)
      {
         if (i % 2 == 0)
         {
            for (int j = 0;j <  m_pUi->tableWidget->columnCount();j++)
            {
                 QTableWidgetItem *item =  m_pUi->tableWidget->item(i,j);
                 if (item)
                 {
                     const QColor color = QColor(26,42,53);//单元格的背景色，可设置
                      item->setBackgroundColor(color);
                 }
            }
         }
      }
     m_pUi->tableWidget->resizeColumnsToContents();//根据内容自适应宽度
     QCoreApplication::processEvents();//避免界面冻结
}
//翻到上一页-槽函数,add by 2019.07.14
void CMymainWindow::upBtn_clicked()
{
#ifdef UBUNTU_DEV //Compiler Switch
#else
    readStatusRecordFile();
#endif
    m_iCurrPage--;
    if(m_iCurrPage<1)
    {
        m_iCurrPage=1;
        return;
    }
    m_pUi->lineEdit_page->setText(QString::number(m_iCurrPage));
    showStatusRecordInfo(m_vec_statusData,m_iCurrPage);
    showRecordStatistics(m_vec_statusData.size(),m_iTotalPage);
}
//翻到下一页-槽函数,add by 2019.07.14@@@
void CMymainWindow::nextBtn_clicked()
{
#ifdef UBUNTU_DEV //Compiler Switch
#else
    readStatusRecordFile();
#endif
    m_iCurrPage++;
    if(m_iCurrPage>m_iTotalPage)
    {
        m_iCurrPage=m_iTotalPage;
        return;
    }
    m_pUi->lineEdit_page->setText(QString::number(m_iCurrPage));
    showStatusRecordInfo(m_vec_statusData,m_iCurrPage);
    showRecordStatistics(m_vec_statusData.size(),m_iTotalPage);
}
//翻到首页-槽函数,add by 2019.07.14@@
void CMymainWindow::firstBtn_clicked()
{
#ifdef UBUNTU_DEV //Compiler Switch
#else
    readStatusRecordFile();
#endif
    m_iCurrPage=1;
    m_pUi->lineEdit_page->setText(QString::number(m_iCurrPage));
    showStatusRecordInfo(m_vec_statusData,m_iCurrPage);
    showRecordStatistics(m_vec_statusData.size(),m_iTotalPage);
}
//翻到尾页-槽函数,add by 2019.07.14
void CMymainWindow::tailBtn_clicked()
{
#ifdef UBUNTU_DEV //Compiler Switch ;
#else
    readStatusRecordFile();
#endif
    m_iCurrPage=m_iTotalPage;
    showStatusRecordInfo(m_vec_statusData,m_iCurrPage);
    printf("tailBtn_clicked()--showStatusRecordInfo(m_vec_statusData,m_iCurrPage)\n");
    m_pUi->lineEdit_page->setText(QString::number(m_iCurrPage));
    showRecordStatistics(m_vec_statusData.size(),m_iTotalPage);
}
//显示分柜实时数据
void CMymainWindow::showSlaveRTdata()
{
#ifdef UBUNTU_DEV //Compiler Switch
    m_iSubopenFlag[0]=g_struBasicPara.iSub1CabOpen;
    m_iSubopenFlag[1]=g_struBasicPara.iSub2CabOpen;
    m_iSubopenFlag[2]=g_struBasicPara.iSub3CabOpen;
    m_iSubopenFlag[3]=g_struBasicPara.iSub4CabOpen;
#ifndef NEWCODE_SW
    //因布局调整修改了toolButton的名称 2020.04.19
    updateSlaveStatusData(g_GPIOData.iSlaveStaValue[0],m_iSubopenFlag[0],m_pUi->toolButton_fgstatus_1);
    updateSlaveStatusData(g_GPIOData.iSlaveStaValue[1],m_iSubopenFlag[1],m_pUi->toolButton_fgstatus_2);
    updateSlaveStatusData(g_GPIOData.iSlaveStaValue[2],m_iSubopenFlag[2],m_pUi->toolButton_fgstatus_3);
    updateSlaveStatusData(g_GPIOData.iSlaveStaValue[3],m_iSubopenFlag[3],m_pUi->toolButton_fgstatus_4);
    QString strTempVer;
    strTempVer= QString::number(g_GPIOData.fSlaveVolt[0],'f',0);
    m_pUi->slavevolt_label_1->display(strTempVer);  //显示分柜1电压

    strTempVer= QString::number(g_GPIOData.fSlaveCurrent[0],'f',0);
    m_pUi->slavecurrent_label_1->display(strTempVer);//显示分柜1电流

    strTempVer= QString::number(g_GPIOData.fSlaveBusVolt[0],'f',0);
    m_pUi->busvolt_label_1->setText(strTempVer); //显示f分柜1正负母线电压

    strTempVer= QString::number(g_GPIOData.fSlaveVolt[1],'f',0);
    m_pUi->slavevolt_label_2->display(strTempVer);  //显示分柜2电压

    strTempVer= QString::number(g_GPIOData.fSlaveCurrent[1],'f',0);
    m_pUi->slavecurrent_label_2->display(strTempVer);//显示分柜2电流

    strTempVer= QString::number(g_GPIOData.fSlaveBusVolt[1],'f',0);
    m_pUi->busvolt_label_2->setText(strTempVer); //显示分柜2正负母线电压

    strTempVer= QString::number(g_GPIOData.fSlaveVolt[2],'f',0);
    m_pUi->slavevolt_label_3->display(strTempVer);  //显示分柜3电压

    strTempVer= QString::number(g_GPIOData.fSlaveCurrent[2],'f',0);
    m_pUi->slavecurrent_label_3->display(strTempVer);//显示分柜3电流

    strTempVer= QString::number(g_GPIOData.fSlaveBusVolt[2],'f',0);
    m_pUi->busvolt_label_3->setText(strTempVer); //显示分柜3正负母线电压

    strTempVer= QString::number(g_GPIOData.fSlaveVolt[3],'f',0);
    m_pUi->slavevolt_label_4->display(strTempVer);  //显示分柜4电压

    strTempVer= QString::number(g_GPIOData.fSlaveCurrent[3],'f',0);
    m_pUi->slavecurrent_label_4->display(strTempVer);//显示分柜4电流

    strTempVer= QString::number(g_GPIOData.fSlaveBusVolt[3],'f',0);
    m_pUi->busvolt_label_4->setText(strTempVer); //显示分柜4正负母线电压
#endif
#ifdef NEWCODE_SW
    updateSlaveStatusData(g_newaddata.iSlaveStaValue[0],m_iSubopenFlag[0],m_pUi->toolButton_fgstatus_1);
    updateSlaveStatusData(g_newaddata.iSlaveStaValue[1],m_iSubopenFlag[1],m_pUi->toolButton_fgstatus_2);
    updateSlaveStatusData(g_newaddata.iSlaveStaValue[2],m_iSubopenFlag[2],m_pUi->toolButton_fgstatus_3);
    updateSlaveStatusData(g_newaddata.iSlaveStaValue[3],m_iSubopenFlag[3],m_pUi->toolButton_fgstatus_4);
    QString strTempVer;
    strTempVer= QString::number(g_newaddata.fSlave1VolDC,'f',2);
    m_pUi->slavevolt_label_1->display(strTempVer);  //显示分柜1电压

    strTempVer= QString::number(g_newaddata.fSlave1CurDC,'f',2);
    m_pUi->slavecurrent_label_1->display(strTempVer);//显示分柜1电流

    strTempVer= QString::number(g_GPIOData.fSlaveBusVolt[0],'f',0);
    m_pUi->busvolt_label_1->setText(strTempVer); //显示f分柜1正负母线电压

    strTempVer= QString::number(g_newaddata.fSlave2VolDC,'f',2);
    m_pUi->slavevolt_label_2->display(strTempVer);  //显示分柜2电压

    strTempVer= QString::number(g_newaddata.fSlave2CurDC,'f',2);
    m_pUi->slavecurrent_label_2->display(strTempVer);//显示分柜2电流

    strTempVer= QString::number(g_GPIOData.fSlaveBusVolt[1],'f',0);
    m_pUi->busvolt_label_2->setText(strTempVer); //显示分柜2正负母线电压

    strTempVer= QString::number(g_newaddata.fSlave3VolDC,'f',2);
    m_pUi->slavevolt_label_3->display(strTempVer);  //显示分柜3电压

    strTempVer= QString::number(g_newaddata.fSlave3CurDC,'f',2);
    m_pUi->slavecurrent_label_3->display(strTempVer);//显示分柜3电流

    strTempVer= QString::number(g_GPIOData.fSlaveBusVolt[2],'f',0);
    m_pUi->busvolt_label_3->setText(strTempVer); //显示分柜3正负母线电压

    strTempVer= QString::number(g_newaddata.fSlave4VolDC,'f',2);
    m_pUi->slavevolt_label_4->display(strTempVer);  //显示分柜4电压

    strTempVer= QString::number(g_newaddata.fSlave4CurDC,'f',2);
    m_pUi->slavecurrent_label_4->display(strTempVer);//显示分柜4电流

    strTempVer= QString::number(g_GPIOData.fSlaveBusVolt[3],'f',0);
    m_pUi->busvolt_label_4->setText(strTempVer); //显示分柜4正负母线电压
#endif
#endif  //Compiler Switch
}
//显示功放实时数据
void CMymainWindow::showPowerAmpRTdata()
{
#ifdef UBUNTU_DEV //Compiler Switch
#ifndef NEWCODE_SW //new code running switch by zw 20220223
    //更新运行状态灯
    //updateStatusData(g_GPIOData.iRunningState,m_pUi->toolButton_yxstatus);
    //更新冷却状态灯
    updateStatusData(g_GPIOData.iCoolingState,m_pUi->toolButton_lqstatus);
    //更新励磁状态灯
    updateStatusData(g_GPIOData.iExcitationState,m_pUi->toolButton_licistatus);
    //更新准备状态灯
    updateStatusData(g_GPIOData.iReadyState,m_pUi->toolButton_readystatus);
    //更新增益状态灯
    updateStatusData(g_GPIOData.iGainState,m_pUi->toolButton_zengyistatus);
    //更新故障状态灯
    updateStatusData(g_GPIOData.iFaultState,m_pUi->toolButton_faultstatus);

    QString strTempVer;
    strTempVer= QString::number(g_GPIOData.fTotalVolt,'f',0);
    m_pUi->lineEdit_totalvolt->display(strTempVer);    //显示总输出电压

    strTempVer= QString::number(g_GPIOData.fTotalCurrent,'f',0);
    m_pUi->lineEdit_totalcurrent->display(strTempVer); //显示总输出电流

    strTempVer= QString::number(g_GPIOData.fExcitVolt,'f',0);
    m_pUi->lineEdit_exitvolt->setText(strTempVer);    //显示励磁电压

    strTempVer= QString::number(g_GPIOData.fExcitCurrent,'f',0);
    m_pUi->lineEdit_exitcurrent->setText(strTempVer); //显示励磁电流

    strTempVer= QString::number(g_GPIOData.fPhaseAVolt,'f',0);
    m_pUi->lineEdit_AVolt->setText(strTempVer);      //显示A相电压

    strTempVer= QString::number(g_GPIOData.fPhaseBVolt,'f',0);
    m_pUi->lineEdit_BVolt->setText(strTempVer);      //显示B相电压

    strTempVer= QString::number(g_GPIOData.fPhaseCVolt,'f',0);
    m_pUi->lineEdit_CVolt->setText(strTempVer);      //显示C相电压
#endif
#ifdef NEWCODE_SW //new code running switch by zw 20220223
    //更新运行状态灯
    //updateStatusData(g_GPIOData.iRunningState,m_pUi->toolButton_yxstatus);
    //更新冷却状态灯
    updateDI(g_newaddata.iCoolingState,m_pUi->toolButton_lqstatus);
    //更新励磁状态灯
    updateDI(g_newaddata.iExcitationState,m_pUi->toolButton_licistatus);
    //更新准备状态灯
    updateDI(g_newaddata.iReadyState,m_pUi->toolButton_readystatus);
    //更新增益状态灯
    updateDI(g_newaddata.iGainState,m_pUi->toolButton_zengyistatus);
    //更新故障状态灯
    updateDI(g_newaddata.iFaultState,m_pUi->toolButton_faultstatus);

    QString strTempVer;
    strTempVer= QString::number(g_newaddata.fTotalVolDC,'f',0);
    m_pUi->lineEdit_totalvolt->display(strTempVer);    //显示总输出电压

    strTempVer= QString::number(g_newaddata.fTotalSlaveCurAC,'f',0);
    m_pUi->lineEdit_totalcurrent->display(strTempVer); //显示总输出电流

    strTempVer= QString::number(g_newaddata.fExcitVolt,'f',0);
    m_pUi->lineEdit_exitvolt->setText(strTempVer);    //显示励磁电压

    strTempVer= QString::number(g_newaddata.fExcitCur,'f',0);
    m_pUi->lineEdit_exitcurrent->setText(strTempVer); //显示励磁电流

    strTempVer= QString::number(g_newaddata.fTriPhaseAVolDC,'f',0);
    m_pUi->lineEdit_AVolt->setText(strTempVer);      //显示A相电压

    strTempVer= QString::number(g_newaddata.fTriPhaseBVolDC,'f',0);
    m_pUi->lineEdit_BVolt->setText(strTempVer);      //显示B相电压

    strTempVer= QString::number(g_newaddata.fTriPhaseCVolDC,'f',0);
    m_pUi->lineEdit_CVolt->setText(strTempVer);      //显示C相电压
#endif
#endif  //Compiler Switch
}
//初始化主界面@@@
void CMymainWindow::initHomePage()
{
    m_pUi->stackedWidget->setCurrentIndex(0);//默认开机显示主界面 add by 2020.08.15
    QColor defaultBgColor("#154b6b");
    QIcon logoicon,starticon,stopicon,reseticon,emergicon,gainstarticon;

    logoicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"logo_right.png"), QSize(), QIcon::Normal, QIcon::Off);
    starticon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"start-default.png"), QSize(), QIcon::Normal, QIcon::Off);
    stopicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"stop-default.png"), QSize(), QIcon::Normal, QIcon::Off);
    reseticon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"reset-default.png"), QSize(), QIcon::Normal, QIcon::Off);
    emergicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"emergency.png"), QSize(), QIcon::Normal, QIcon::Off);
    gainstarticon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"Gain-off.png"), QSize(), QIcon::Normal, QIcon::Off);

    //设置logo图标
    m_pUi->toolButton_logo->setIcon(logoicon);
    m_pUi->toolButton_logo->setIconSize(QSize(107, 107));
    //设置功放控制组的"启动按钮"图标
    m_pUi->toolButton_gfstart->setIcon(starticon);
    m_pUi->toolButton_gfstart->setIconSize(QSize(64, 64));
    //设置功放控制组的"停止按钮"图标
    m_pUi->toolButton_gfstop->setIcon(stopicon);
    m_pUi->toolButton_gfstop->setIconSize(QSize(64, 64));
    //设置功放控制组的"复位按钮"图标
    m_pUi->toolButton_gfreset->setIcon(reseticon);
    m_pUi->toolButton_gfreset->setIconSize(QSize(64, 64));
    //设置增益控制组的"启动按钮"图标
    m_pUi->toolButton_zystart->setIcon(gainstarticon);
    m_pUi->toolButton_zystart->setIconSize(QSize(64, 64));
    //设置"紧急停机"图标
    m_pUi->jjtjBtn->setIcon(emergicon);
    m_pUi->jjtjBtn->setIconSize(QSize(64, 64));

    //设置"运行状态"图标
    //m_pUi->toolButton_yxstatus->setIcon(m_yellowicon);
    //设置冷却状态"图标
    m_pUi->toolButton_lqstatus->setIcon(m_yellowicon);
    //设置"励磁状态"图标
    m_pUi->toolButton_licistatus->setIcon(m_yellowicon);
    //设置"准备状态"图标
    m_pUi->toolButton_readystatus->setIcon(m_yellowicon);
    //设置"增益状态"图标
    m_pUi->toolButton_zengyistatus->setIcon(m_yellowicon);
    //设置"故障状态"图标
    m_pUi->toolButton_faultstatus->setIcon(m_yellowicon);
    m_pUi->horizontalScrollBar->setEnabled(false);//禁用滑块，add by 2019.05.29
    m_pUi->comboBox_gear->setEnabled(false);//禁用挡位选择，add by 2019.05.29

    connect(m_pUi->pushButton_CN,SIGNAL(clicked()),this,SLOT(languageCN()));
    connect(m_pUi->pushButton_EN,SIGNAL(clicked()),this,SLOT(languageEN()));
    //"功放控制"相关信号与槽函数
    connect(m_pUi->toolButton_gfstart,SIGNAL(clicked()),this,SLOT(gfstartBtn_clicked()));
    connect(m_pUi->toolButton_gfstop,SIGNAL(clicked()),this,SLOT(gfstopBtn_clicked()));
    connect(m_pUi->toolButton_gfreset,SIGNAL(clicked()),this,SLOT(gfresetBtn_clicked()));
    //"增益控制"相关信号与槽函数
    connect(m_pUi->toolButton_zystart,SIGNAL(clicked()),this,SLOT(zystartBtn_clicked()));
    connect (m_pUi->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(updateSliderValue(int)));
    connect (m_pUi->comboBox_gear, SIGNAL(activated(int)), this, SLOT(setSliderPosbyGear(int)));
    //"紧急停机"相关信号与槽函数
    connect(m_pUi->jjtjBtn,SIGNAL(clicked()),this,SLOT(jjtjBtn_clicked()));
    //清除日志-信号与槽函数,add by 2019.05.18
    connect(m_pUi->clearlogBtn,SIGNAL(clicked()),this,SLOT(clearlogBtn_clicked()));
    //更新模拟设置-信号与槽函数，add by 2019.05.23
    connect(m_pUi->updatesetBtn,SIGNAL(clicked()),this,SLOT(updatesetBtn_clicked()));
    //（临时）发送按钮
    connect(m_pUi->pushButton_Send,SIGNAL(clicked()),this,SLOT(slotSendMesg()));
    iLongrCtl=false;
    g_iLangChange=1;
    m_pUi->pushButton_CN->setEnabled(false);
    m_pUi->pushButton_CN->setDown(true);
    m_pUi->pushButton_EN->setEnabled(true);
    m_pUi->pushButton_EN->setDown(false);
    m_iMode=NORMAL_MODE;
    m_pUi->toolButton_zystart->setEnabled(false);
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
//    QString n_fileheaddate =current_date_time.toString("yyyy.MM.dd  hh:mm:ss");//csv文件的时间列 add by 2020.09.05
    QString n_fileheaddate =current_date_time.toString("yyyyMMddhhmm");
#ifdef WIN_DEV
    m_strHisfilepath = QString("./debug/hisdata/%1.csv").arg(n_fileheaddate);
#else
    m_strHisfilepath = QString(QApplication::applicationDirPath()+"/hisdata/%1.csv").arg(n_fileheaddate);
#endif

    m_pUi->curtime_label->setText(current_date);
    m_pUi->lineEdit_totalvolt->setEnabled(false);
    m_pUi->lineEdit_totalcurrent->setEnabled(false);
    m_pUi->lineEdit_exitvolt->setEnabled(false);
    m_pUi->lineEdit_exitcurrent->setEnabled(false);
    m_pUi->lineEdit_AVolt->setEnabled(false);
    m_pUi->lineEdit_BVolt->setEnabled(false);
    m_pUi->lineEdit_CVolt->setEnabled(false);
    //读取运行状态时间配置文件
    if(!m_Inifile.readStatusRecordInifile(m_struStatus))
    {
        m_struStatus.lTotaltime=Zerotime;
        m_struStatus.iSumtime=Zerotime;
    }
    m_iSumlast=m_struStatus.iSumtime;
    int nDaylast=0;
    int nHourlast=0;
    int nMinlast=0;
    int nSeclast=0;
    nDaylast=m_iSumlast/86400;
    nHourlast=m_iSumlast/3600-nDaylast*24;
    nMinlast=m_iSumlast/60-nDaylast*24*60-nHourlast*60;
    nSeclast=m_iSumlast-nHourlast*3600-nMinlast*60-nDaylast*24*60*60;
    QString strLasttime=QString::number(nDaylast,10)+tr("\345\244\251")+QString::number(nHourlast,10)+tr("\345\260\217\346\227\266")+QString::number(nMinlast,10)+tr("\345\210\206\351\222\237")+QString::number(nSeclast,10)+tr("\347\247\222");
    //m_pUi->lasttime_label->setText(strLasttime);

     m_isFlash=false;
     mainLangchange();
     m_iSumlast=0;
     m_StartCheckFlag=false;
     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
     timer->start(1000);

     QTimer *timer100ms = new QTimer(this);
     connect(timer100ms, SIGNAL(timeout()), this, SLOT(update100msTime()));
     timer100ms->start(100);//100ms定时器判驱动保护等,add by 2019.05.26

     m_pTimer5m=new QTimer(this);
     connect(m_pTimer5m, SIGNAL(timeout()), this, SLOT(waiting5minute()));
     m_pTimer5m->start(5*60*1000);//5分钟定时器写总运行时间，add by 2019.07.19

     m_iAnalogCnt=0;//主画面模拟数据计数器,add by 2019.05.26
     m_iCANDataCnt=0;//CAN数据显示计数器，add by 2019.09.05
     m_Timer60StartFlag=false;

     //连锁参数结构体变量初始化,add by 2019.04.13
     m_ChainSetData.iJjtjVal=SWITCH_OFF;  //紧急停机
     m_ChainSetData.iHtgwyVal=SWITCH_OFF; //滑台过位移
     m_ChainSetData.iZdtgwyVal=SWITCH_OFF;//振动台过位移
     m_ChainSetData.iHtdywVal=SWITCH_OFF; //滑台低液位
     m_ChainSetData.iHtqyVal=SWITCH_OFF;//滑台轴承低压
     m_ChainSetData.iZdtgwVal=SWITCH_OFF; //振动台过温
     m_ChainSetData.iEzgwyVal=SWITCH_OFF; //耳轴过位移
     m_ChainSetData.iGfrjbhVal=SWITCH_OFF;//功放热继保护
     m_ChainSetData.iJyzcdyVal=SWITCH_OFF;//静压轴承低压
     m_ChainSetData.iZgMenbVal=SWITCH_OFF;  //主柜门保护
     m_ChainSetData.iXtlqdyVal=SWITCH_OFF;//系统冷却单元
     m_ChainSetData.iHtqywVal=SWITCH_OFF;//主柜整流桥过温,add by 2019.05.25
     m_ChainSetData.iSubMenbVal=SWITCH_OFF;//从柜门保护
     m_ChainSetData.iSubzlqgwVal=SWITCH_OFF;//从柜整流桥过温,add by 2019.05.25
     m_ChainSetData.iSelfdefineVal1=SWITCH_OFF;//自定义1,add by 2019.05.25
     m_ChainSetData.iSelfdefineVal2=SWITCH_OFF;//自定义2,add by 2019.05.25
     m_ChainSetData.iSelfdefineVal3=SWITCH_OFF;//自定义3,add by 2019.05.25
     m_ChainSetData.iSubyuliuPorcVal=SWITCH_OFF;//从柜预留保护,add by 2019.05.25

     //触点切换初始化-常开 add by 2020.11.24
     m_ChainSetData.iSwitch_Jjtj=NORMAL_OPEN;//紧急停机
     m_ChainSetData.iSwitch_htgwy=NORMAL_OPEN;//滑台过位移
     m_ChainSetData.iSwitch_zdtgwy=NORMAL_OPEN;//振动台过位移
     m_ChainSetData.iSwitch_htdyw=NORMAL_OPEN;//滑台低液位
     m_ChainSetData.iSwitch_htqy=NORMAL_OPEN;//滑台轴承低压
     m_ChainSetData.iSwitch_zdtgw=NORMAL_OPEN;//振动台过温
     m_ChainSetData.iSwitch_ezgwy=NORMAL_OPEN;//耳轴过位移
     m_ChainSetData.iSwitch_gfrjbh=NORMAL_OPEN;//功放热继保护
     m_ChainSetData.iSwitch_jyzcdy=NORMAL_OPEN;//静压轴承低压
     m_ChainSetData.iSwitch_zgmenbh=NORMAL_OPEN;//主柜门
     m_ChainSetData.iSwitch_htgw=NORMAL_OPEN;//从柜门
     m_ChainSetData.iSwitch_xtlqdy=NORMAL_OPEN;//系统冷却单元
     m_ChainSetData.iSwitch_htqyw=NORMAL_OPEN;//主柜整流器过温
     m_ChainSetData.iSwitch_subzlqgw=NORMAL_OPEN;//从柜整流器过温
     m_ChainSetData.iSwitch_selfdefine1=NORMAL_OPEN;//自定义1
     m_ChainSetData.iSwitch_selfdefine2=NORMAL_OPEN;//自定义2
     m_ChainSetData.iSwitch_selfdefine3=NORMAL_OPEN;//自定义3
     m_ChainSetData.iSwitch_subyuliu=NORMAL_OPEN;//从柜预留

     m_nTestFlag=NOTEST_FLAG;//测试态，只考虑一个分柜电气加量情况，add by 2019.05.14

     /*功放启动、复位和停止三种操作标志初始化 20190512*/
     m_GfTestPauseFlag=false;//功放启动测试中断标志,false-继续测试，add by 20190518
     m_GfStartFlag=false;
     m_GfResetFlag=false;
     m_GfStopFlag=false;
     m_GainStartFlag=false;
     m_EmergencyFlag=false;
     m_ExcitExistFlag=false;
     m_nSectionPos=PROCESS_SECTION_NULL;

     //读取模拟保护参数，add by 2019.05.23
     GetSimuProcSet(g_SimuProcSet);
     m_iCountDownTime=60;
     if(!m_Inifile.readBasicParaInifile(m_struBasicpara))
     {
       //基本参数的初始化，add by 2019.05.28
        m_struBasicpara.fBusImbalance=BUS_VOLT_UNBALANCE;
        m_struBasicpara.fBusvoltLow=BUS_VOLT_DOWN_LIMIT;
        m_struBasicpara.fBusvoltUp=BUS_VOLT_UP_LIMIT;
        m_struBasicpara.fSub1CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
        m_struBasicpara.fSub2CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
        m_struBasicpara.fSub3CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
        m_struBasicpara.fSub4CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
        m_struBasicpara.fThreevoltLow=THREE_VOLT_DOWN;
        m_struBasicpara.fThreevoltUp=THREE_VOLT_UP;
        m_struBasicpara.fTotalcurrentUp=TOTAL_CURRENT_UP_LIMIT;
        m_struBasicpara.fTotalvoltUp=TOTAL_VOLT_UP_LIMIT;
        m_struBasicpara.fVoltimbalance=Threephase_VOLT_UNBALANCE;
        m_struBasicpara.iSub1CabOpen=SUBCABOPEN_FLAG;
        m_struBasicpara.iSub2CabOpen=SUBCABOPEN_FLAG;
        m_struBasicpara.iSub3CabOpen=SUBCABOPEN_FLAG;
        m_struBasicpara.iSub4CabOpen=SUBCABOPEN_FLAG;
     }
     memcpy(&g_struBasicPara,&m_struBasicpara,sizeof(m_struBasicpara));

     if(!m_Inifile.readAdjcoefInifile(m_struAdjcoef))
     {
         m_struAdjcoef.fSub1voltK=COMMON_K;
         m_struAdjcoef.fSub1voltB=COMMON_B;
         m_struAdjcoef.fSub1ActvoltK=COMMON_K;
         m_struAdjcoef.fSub1ActvoltB=COMMON_B;
         m_struAdjcoef.fSub1negvoltK=COMMON_K;
         m_struAdjcoef.fSub1negvoltB=COMMON_B;
         m_struAdjcoef.fSub1outvoltK=COMMON_K;
         m_struAdjcoef.fSub1outvoltB=COMMON_B;
         m_struAdjcoef.fSub1outcurrK=COMMON_K;
         m_struAdjcoef.fSub1outcurrB=COMMON_B;

         m_struAdjcoef.fSub2voltK=COMMON_K;
         m_struAdjcoef.fSub2voltB=COMMON_B;
         m_struAdjcoef.fSub2ActvoltK=COMMON_K;
         m_struAdjcoef.fSub2ActvoltB=COMMON_B;
         m_struAdjcoef.fSub2negvoltK=COMMON_K;
         m_struAdjcoef.fSub2negvoltB=COMMON_B;
         m_struAdjcoef.fSub2outvoltK=COMMON_K;
         m_struAdjcoef.fSub2outvoltB=COMMON_B;
         m_struAdjcoef.fSub2outcurrK=COMMON_K;
         m_struAdjcoef.fSub2outcurrB=COMMON_B;

         m_struAdjcoef.fSub3voltK=COMMON_K;
         m_struAdjcoef.fSub3voltB=COMMON_B;
         m_struAdjcoef.fSub3ActvoltK=COMMON_K;
         m_struAdjcoef.fSub3ActvoltB=COMMON_B;
         m_struAdjcoef.fSub3negvoltK=COMMON_K;
         m_struAdjcoef.fSub3negvoltB=COMMON_B;
         m_struAdjcoef.fSub3outvoltK=COMMON_K;
         m_struAdjcoef.fSub3outvoltB=COMMON_B;
         m_struAdjcoef.fSub3outcurrK=COMMON_K;
         m_struAdjcoef.fSub3outcurrB=COMMON_B;

         m_struAdjcoef.fSub4voltK=COMMON_K;
         m_struAdjcoef.fSub4voltB=COMMON_B;
         m_struAdjcoef.fSub4ActvoltK=COMMON_K;
         m_struAdjcoef.fSub4ActvoltB=COMMON_B;
         m_struAdjcoef.fSub4negvoltK=COMMON_K;
         m_struAdjcoef.fSub4negvoltB=COMMON_B;
         m_struAdjcoef.fSub4outvoltK=COMMON_K;
         m_struAdjcoef.fSub4outvoltB=COMMON_B;
         m_struAdjcoef.fSub4outcurrK=COMMON_K;
         m_struAdjcoef.fSub4outcurrB=COMMON_B;

         m_struAdjcoef.fMAvoltK=COMMON_K;
         m_struAdjcoef.fMAvoltB=COMMON_B;
         m_struAdjcoef.fMBvoltK=COMMON_K;
         m_struAdjcoef.fMBvoltB=COMMON_B;
         m_struAdjcoef.fMCvoltK=COMMON_K;
         m_struAdjcoef.fMCvoltB=COMMON_B;
         m_struAdjcoef.fMEvoltK=COMMON_K;
         m_struAdjcoef.fMEvoltB=COMMON_B;
         m_struAdjcoef.fMEcurrK=COMMON_K;
         m_struAdjcoef.fMEcurrB=COMMON_B;
     }
     memcpy(&g_struAdjcoef,&m_struAdjcoef,sizeof(m_struAdjcoef));

     if(!m_Inifile.readnewAdjcoefInifile(m_newAdjcoef))
     {
         m_newAdjcoef.fTriPhaseAVolDCK = COMMON_K;
         m_newAdjcoef.fTriPhaseAVolDCB = COMMON_B;
         m_newAdjcoef.fTriPhaseBVolDCK = COMMON_K;
         m_newAdjcoef.fTriPhaseBVolDCB = COMMON_B;
         m_newAdjcoef.fTriPhaseCVolDCK = COMMON_K;
         m_newAdjcoef.fTriPhaseCVolDCB = COMMON_B;
         m_newAdjcoef.fExcitVoltK = COMMON_K;
         m_newAdjcoef.fExcitVoltB = COMMON_B;
         m_newAdjcoef.fExcitCurK = COMMON_K;
         m_newAdjcoef.fExcitCurB = COMMON_B;
         m_newAdjcoef.fSlave1VolDCK = COMMON_K;
         m_newAdjcoef.fSlave1VolDCB = COMMON_B;
         m_newAdjcoef.fSlave1CurDCK = COMMON_K;
         m_newAdjcoef.fSlave1CurDCB = COMMON_B;
         m_newAdjcoef.fSlave2VolDCK = COMMON_K;
         m_newAdjcoef.fSlave2VolDCB = COMMON_B;
         m_newAdjcoef.fSlave2CurDCK = COMMON_K;
         m_newAdjcoef.fSlave2CurDCB = COMMON_B;
         m_newAdjcoef.fSlave3VolDCK = COMMON_K;
         m_newAdjcoef.fSlave3VolDCB = COMMON_B;
         m_newAdjcoef.fSlave3CurDCK = COMMON_K;
         m_newAdjcoef.fSlave3CurDCB = COMMON_B;
         m_newAdjcoef.fSlave4VolDCK = COMMON_K;
         m_newAdjcoef.fSlave4VolDCB = COMMON_B;
         m_newAdjcoef.fSlave4CurDCK = COMMON_K;
         m_newAdjcoef.fSlave4CurDCB = COMMON_B;
         m_newAdjcoef.fTotalVolACK = COMMON_K;
         m_newAdjcoef.fTotalVolACB = COMMON_B;
         m_newAdjcoef.fTotalVolDCK = COMMON_K;
         m_newAdjcoef.fTotalVolDCB = COMMON_B;
         m_newAdjcoef.fTotalSlaveCurACK = COMMON_K;
         m_newAdjcoef.fTotalSlaveCurACB = COMMON_B;
         m_newAdjcoef.fCustom11K = COMMON_K;
         m_newAdjcoef.fCustom11B = COMMON_B;
         m_newAdjcoef.fCustom12K = COMMON_K;
         m_newAdjcoef.fCustom12B = COMMON_B;
     }
     memcpy(&g_newAdjcoef,&m_newAdjcoef,sizeof(m_newAdjcoef));
}
//@@@
void  CMymainWindow::mainLangchange()
{
    if(g_iLangChange==1)
    {
        m_strInfo=QApplication::translate("mainWindow",
        "\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//提示

        m_strResetTips=QApplication::translate("mainWindow",
         "\345\217\257\344\273\245\350\277\233\350\241\214\345\212\237\346\224\276\345\244\215\344\275\215\346\223\215\344\275\234\344\272\206",
         0,
         QApplication::UnicodeUTF8);//“可以进行功放复位操作了”提示语
        m_strgainTips=QApplication::translate("mainWindow",
         "\345\242\236\347\233\212\350\256\276\347\275\256",
         0,
         QApplication::UnicodeUTF8);

        m_strYes=QApplication::translate("mainWindow",
          "\346\230\257",
          0, QApplication::UnicodeUTF8);

        m_strNo=QApplication::translate("mainWindow",
                "\345\220\246",
                0, QApplication::UnicodeUTF8);

        m_strWait60s=QApplication::translate("mainWindow",
         "\351\234\200\350\246\201\347\255\211\345\276\20560\347\247\222\351\222\237\357\274\214\350\257\267\347\250\215\345\200\231",
         0,
         QApplication::UnicodeUTF8);
        m_strLacktime=QApplication::translate("mainWindow",
          "\346\211\200\345\211\251\346\227\266\351\227\264\345\267\262\344\270\215\350\266\263\344\270\200\345\244\251",
          0,
          QApplication::UnicodeUTF8);
        m_strOverime=QApplication::translate("mainWindow",
          "\345\267\262\346\227\240\345\211\251\344\275\231\346\227\266\351\227\264\357\274\214\350\257\267\346\202\250\350\201\224\347\263\273\345\216\202\345\256\266\347\273\255\346\227\266",
          0,
          QApplication::UnicodeUTF8);
        m_strOutputSaveSuccess= QApplication::translate("mainWindow", "\350\276\223\345\207\272\346\227\245\345\277\227\346\226\207\344\273\266\344\277\235\345\255\230\346\210\220\345\212\237",
        0,
        QApplication::UnicodeUTF8);//add by 2020.11.12

    m_strOutputSaveFail= QApplication::translate("mainWindow", "\350\276\223\345\207\272\346\227\245\345\277\227\346\226\207\344\273\266\344\277\235\345\255\230\345\244\261\350\264\245,\350\257\267\346\243\200\346\237\245",
        0,
        QApplication::UnicodeUTF8);//add by 2020.11.12
    }
    else
    {
        m_strInfo="Tips";//提示
        m_strResetTips="The power amplifier reset operation is ready";//“可以进行功放复位操作了”提示语
        m_strgainTips="Gain set";//“增益设置”提示语
        m_strYes="Yes";
        m_strNo="No";
        m_strWait60s="Need to wait for 60s,please wait...";//“需要等待60s，请稍后”提示语
        m_strLacktime="Less than a day left";//“所剩时间已不足一天”提示语
        m_strOverime="There is no time left.Please contact the manufacturer for renewal.";//“已无剩余时间，请您联系厂家续时”提示语
        m_strOutputSaveSuccess= "Output log profile saved successfully";//add by 2020.11.12
        m_strOutputSaveFail= "Output log profile failed to save,please check";//add by 2020.11.12
    }
}
//更新滑条值到label_slider-槽函数，add by 2019.05.23@@@
void  CMymainWindow::updateSliderValue(int nValue)
{
     QCoreApplication::processEvents();//避免界面冻结
    //按照百分比设置增益
#ifndef NEWCODE_SW
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_5C,1023*(nValue)/100+qPow (2, 10),m_nGPIOfd);//qPow(2.10)是标识高4位为0001
#endif
     //add by zw 202220223
     i_zyLoadPerc = nValue;
     //end add by zw 20220223
     printf("updateSliderValue=%d\n",nValue);
     m_pUi->label_slider->setText(QString::number(nValue)+"%");
     QCoreApplication::processEvents();//避免界面冻结
}
//根据挡位设置滑条位置-槽函数，add by 2019.05.23
void CMymainWindow::setSliderPosbyGear(int nGear)
{
    int ret=-1;
    QString strYes;
    QString strNo;
    QString strTemp;
    int nValue=0;
    QMessageBox *msgBox=new QMessageBox(QMessageBox::Question,
    m_strInfo,
    m_strgainTips,
    QMessageBox::Yes | QMessageBox::No);
    switch (nGear)
    {
        case 0:
            nValue=10;
            break;
        case 1:
            nValue=30;
            break;
        case 2:
            nValue=50;
            break;
        case 3:
            nValue=80;
            break;
        case 4:
            nValue=100;
            break;
        default:
            nValue=10;
            break;
  }//switch (nGear)
     strTemp=m_strgainTips+QString::number(nValue)+tr("%");
     msgBox->setText(strTemp);
     msgBox->button(QMessageBox::Yes)->setText(m_strYes);
    // 将原本显示“No”的按钮改为显示“否”
     msgBox->button(QMessageBox::No)->setText(m_strNo);
    // 弹出对话框
     ret=msgBox->exec();
     if(ret==QMessageBox::Yes)
     {
         m_pUi->horizontalScrollBar->setValue(nValue);
        //按照百分比设置增益
        m_pGPIORecvThread->m_Gpiorw.write_do(write_address_5C,1023*(nValue)/100+qPow (2, 10),m_nGPIOfd);//qPow(2.10)是标识高4位为0001
     }
     else if(ret==QMessageBox::No)
     {
        return;
     }
}
void CMymainWindow::slotStartCheck()
{
    QDateTime current_date_time=QDateTime::currentDateTime();//add by 2020.11.18
    int currenttimeT=current_date_time.toTime_t();// add by 2020.11.18
    int activetimeT=m_Inifile.active_date_time.toTime_t();// add by 2020.11.18
    int ndayssec=24*60*60;// add by 2020.11.18
    int remainCalDay=(currenttimeT-activetimeT)/(ndayssec)+
        ((currenttimeT-activetimeT)%(ndayssec)+(ndayssec-1))/(ndayssec)-1; //add by 2020.11.18
    if(!m_StartCheckFlag)
    {
        m_StartCheckFlag=true;
        if(((linvalidsetValue!=0)&&(lremaintime<=DELT_FVALUE))||(remainCalDay>=m_Inifile.calendarDay))
        {
            QMessageBox::warning(this,
                           tr(m_strInfo),
                           tr(m_strOverime));
            int ret =m_logindlg.exec();
//			if(m_logindlg.IsPWDCorrect()==2)  //输入是管理员密码时，才可继续
            if(m_logindlg.IsPWDCorrect()==6)  //输入是管理员密码时，才可继续
            {
                m_logindlg.clearBtn_clicked();//清除密码
            }
            else
            {
             if(g_iLangChange==1)
              {
                QMessageBox::warning(this, tr("\350\255\246\345\221\212"),
                                    tr("\346\202\250\350\276\223\345\205\245\347\232\204\345\257\206\347\240\201\351\224\231\350\257\257,\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245"));
              }
              else
              {
                QMessageBox::warning(this, tr("Waring"),
                                    tr("Password input error "));
              }
//				this->close();
                QCoreApplication::exit();
            }
        }
        else if((lremaintime>=DELT_FVALUE)&&(lremaintime<=Limittime))
        {
            QMessageBox::warning(this,
                           tr(m_strInfo),
                           tr(m_strLacktime));
        }
    }
}
//时间格式转换实现 add by 2020.08.15
QString CMymainWindow::TimeFormatTransfer(qint64 nSeconds)
{
        qint64 nDay=0;
        qint64 nHour=0;
        qint64 nMin=0;
        qint64 nSec=0;
        nDay=nSeconds/86400;
        nHour=nSeconds/3600-nDay*24;
        nMin=nSeconds/60-nDay*24*60-nHour*60;
        nSec=nSeconds-nHour*3600-nMin*60-nDay*24*60*60;
        QString strTime=QString::number(nDay,10)+tr("\345\244\251")+QString::number(nHour,10)+tr("\345\260\217\346\227\266")+QString::number(nMin,10)+tr("\345\210\206\351\222\237")+QString::number(nSec,10)+tr("\347\247\222");
        return strTime;
}
//更新当前时间、历史文件存储及模控数据解析(每秒处理一次)
void CMymainWindow::updateTime()
{
    QCoreApplication::processEvents();//避免界面冻结
    m_itotaltime=m_struStatus.lTotaltime;
    m_struStatus.iSumtime=Zerotime;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd \n hh:mm:ss");
    QString fileheaddate =current_date_time.toString("yyyy.MM.dd  hh:mm:ss");//csv文件的时间列 add by 2020.09.05
    QString filedate =current_date_time.toString("yyyyMMddhhmm");

    QString strTotaltime=TimeFormatTransfer(m_itotaltime);
    //更新时间信息
    m_pUi->totaltime_label->setText(strTotaltime);
    m_pUi->curtime_label->setText(current_date);

    //历史数据存储
    createHisDataFile(filedate,fileheaddate,m_itotaltime);
    m_ithistime++;
    m_itotaltime++;
    QString strThistime=TimeFormatTransfer(m_ithistime);
    m_pUi->lasttime_label->setText(strThistime);//add by 2020.08.15
    m_iSumlast++;
    //m_pUi->DebugTextEdit->setStyleSheet("color:black;border:2px solid gray;");//设置为黑色字体
    m_struStatus.lTotaltime=m_itotaltime;
    m_struStatus.iSumtime=m_iSumlast;
    if(m_Timer60StartFlag)
    {
        //显示剩余时间信息,add by 2019.05.26
        m_iCountDownTime--;
        if(m_iCountDownTime>=0)
        {
            if(!m_CountDownWdgt.isVisible())
            {
                m_CountDownWdgt.exec();
            }
           m_CountDownWdgt.showRemainingTime(m_iCountDownTime);
        }
        else
        {
            //--恢复初始值,add by 2019.05.26
            m_CountDownWdgt.close();
            m_Timer60StartFlag=false;
        /*QMessageBox::information(this,
        tr(m_strInfo),
        tr(m_strResetTips));*/
        }
    }
}
//"更新总运行时间配置文件5分钟"槽函数add by 2019.07.19
void CMymainWindow::waiting5minute()
{
    m_struStatus.lTotaltime=m_itotaltime;
    m_struStatus.iSumtime=m_iSumlast;
    m_Inifile.writeStatusRecordInifile(m_struStatus);
}
//"更新100ms时间"槽函数,add by 2019.05.26
void CMymainWindow::update100msTime()
{
    QCoreApplication::processEvents();//避免界面冻结
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    QString strtmep;
    strtmep.sprintf("pos=%d-mode=%d-gfstartflag=%d-pauseflag=%d\n",m_nSectionPos,m_iMode,m_GfStartFlag,m_GfTestPauseFlag);
    m_pUi->label_key->setText(current_date+tr(" ")+strtmep);
#ifndef NEWCODE_SW
    SentSubAvgCurr();
#endif
    m_iCANDataCnt++;
#ifdef UBUNTU_DEV
    if(m_iCANDataCnt%10==0)
    {
        //更新故障状态数据
        bool  isActive=false;
        isActive=m_FaultCondWdgt.isActiveWindow();
        bool  isVis=false;
        isVis=m_FaultCondWdgt.isVisible();
        if((isActive)||(isVis))
        {
            m_FaultCondWdgt.updateFaultConditionData(m_FaultCondWdgt.ifaultindex,&m_struLeftFaultDATA[0],&m_struRightFaultDATA[0]);//有16个模块
        }
        //更新运行状态数据
        isActive=m_pRunStaWdget->isActiveWindow();
        isVis=m_pRunStaWdget->isVisible();
        if((isActive)||(isVis))
        {
            m_struRunningDATA[0].strTime=current_date;//更新当前时间
            m_pRunStaWdget->updateRunningStatusData(&m_struRunningDATA[0]);//有16个模块，2019.12.02
         }
        //更新温度监控数据
        isActive=m_pTempmonitorWdgt->isActiveWindow();
        isVis=m_pTempmonitorWdgt->isVisible();
        if((isActive)||(isVis))
        {
            m_pTempmonitorWdgt->updateTemperatureData(&m_struIGBTTempctlDATA[0],&m_struIDUCTTempctlDATA[0],&m_struDCINPUTVoltagectlDATA[0]);//有16个模块
        }
        m_iCANDataCnt=0;
    }
    switch(m_nSectionPos)
    {
     case PROCESS_SECTION_01:
        CheckProcOfSection1();
        break;
     case PROCESS_SECTION_02:
        CheckProcOfSection2();
        break;
     case PROCESS_SECTION_03:
        CheckProcOfSection3();
        break;
     case PROCESS_SECTION_04:
        CheckProcOfSection4();
        break;
     default:
         break;
    }//switch(m_nSectionPos)
#endif
}
//生成历史数据文件
void CMymainWindow::createHisDataFile(QString strfiledate,QString strCurrdate,int nTotaltime)
{
#ifdef WIN_DEV
    QString strHisfilepath="./debug/hisdata/";
#else
    QString strHisfilepath=QApplication::applicationDirPath() + "/hisdata/";
#endif

     if(nTotaltime%3600==0)
     {
         //满1个小时新建一个文件
          strHisfilepath+=strfiledate;
          strHisfilepath+=tr(".csv");
          m_strHisfilepath=strHisfilepath;
          QFile file(m_strHisfilepath);
       if (!file.open(QFile::WriteOnly | QFile::Append))//文件追加写入
              return;
         QTextStream out(&file);
         //输出文件头行信息
         QStringList headfilelist;
         headfilelist.append(tr("time"));
         headfilelist.append(tr(","));
         headfilelist.append(tr("second"));
         headfilelist.append(tr(","));
         headfilelist.append(tr("totalvolt(V)"));
         headfilelist.append(tr(","));
         headfilelist.append(tr("totalcurrent(A)"));
         headfilelist.append(tr(","));
         headfilelist.append(tr("excitvolt(V)"));
         headfilelist.append(tr(","));
         headfilelist.append(tr("excitcurrent(A)"));
         headfilelist.append(tr(","));
         headfilelist.append(tr("phaseAvolt(V)"));
         headfilelist.append(tr(","));
         headfilelist.append(tr("phaseBvolt(V)"));
         headfilelist.append(tr(","));
         headfilelist.append(tr("phaseCvolt(V)"));

         out << headfilelist.at(0) << headfilelist.at(1)<< headfilelist.at(2)<< headfilelist.at(3)<< headfilelist.at(4)<< headfilelist.at(5)<< headfilelist.at(6)<< headfilelist.at(7)<< headfilelist.at(8)<<headfilelist.at(9)<< headfilelist.at(10)<<headfilelist.at(11)<< headfilelist.at(12)<<headfilelist.at(13)<<headfilelist.at(14)<<headfilelist.at(15)<<headfilelist.at(16)<<"\n";
         file.close();
     }
     else
     {
         QFile file(m_strHisfilepath);
         if (!file.open(QFile::WriteOnly | QFile::Append))//文件追加写入
              return;
         QTextStream out(&file);
         QStringList datafilelist;
         QString strTempVer;
         datafilelist.append(strCurrdate);
         datafilelist.append(tr(","));
         datafilelist.append(QString::number(m_isecondcnt));
         datafilelist.append(tr(","));
#ifdef UBUNTU_DEV //Compiler Switch
         g_Mutex.lock();
         strTempVer= QString::number(g_GPIOData.fTotalVolt,'f',2);
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(g_GPIOData.fTotalCurrent,'f',2);
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(g_GPIOData.fExcitVolt,'f',2);
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(g_GPIOData.fExcitCurrent,'f',2);
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(g_GPIOData.fPhaseAVolt,'f',2);
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(g_GPIOData.fPhaseBVolt,'f',2);
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(g_GPIOData.fPhaseCVolt,'f',2);
         datafilelist.append(strTempVer);
          g_Mutex.unlock();
#else
         float ftmep=0.33;
         strTempVer= QString::number(ftmep,'f',2);//totalvolt(V)
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(ftmep,'f',2);//totalcurrent(A)
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(ftmep,'f',2);//excitvolt(V)
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(ftmep,'f',2);//excitcurrent(A)
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(ftmep,'f',2);//phaseAvolt(V)
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(ftmep,'f',2);//phaseBvolt(V)
         datafilelist.append(strTempVer);
         datafilelist.append(tr(","));
         strTempVer= QString::number(ftmep,'f',2);//phaseCvolt(V)
         datafilelist.append(strTempVer);
#endif    //Compiler Switch
         //输出文件数据信息
          out << datafilelist.at(0) << datafilelist.at(1)<< datafilelist.at(2)<< datafilelist.at(3)<< datafilelist.at(4)<< datafilelist.at(5)<< datafilelist.at(6)<< datafilelist.at(7)<< datafilelist.at(8)<<datafilelist.at(9)<< datafilelist.at(10)<<datafilelist.at(11)<< datafilelist.at(12)<<datafilelist.at(13)<<datafilelist.at(14)<<datafilelist.at(15)<<datafilelist.at(16)<<"\n";
          file.close();

     }
     if(m_isecondcnt==59)
     {
         m_isecondcnt =0;//满59清0
     }
     else
     {
         m_isecondcnt++;
     }
}
//状态记录页面初始化@@@
void CMymainWindow::initStatusPage()
{
    m_pUi->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: rgb(2, 59, 101);}");//background:skyblue
    m_pUi->tableWidget->horizontalHeader()->setStyleSheet("color:#39c9ff;");

    //信号与槽关系初始化,add by 2019.07.14
    connect(m_pUi->upBtn,SIGNAL(clicked()),this,SLOT(upBtn_clicked()));
    connect(m_pUi->nextBtn,SIGNAL(clicked()),this,SLOT(nextBtn_clicked()));
    connect(m_pUi->firstBtn,SIGNAL(clicked()),this,SLOT(firstBtn_clicked()));
    connect(m_pUi->tailBtn,SIGNAL(clicked()),this,SLOT(tailBtn_clicked()));
    connect(m_pUi->lineEdit_page,SIGNAL(clicked()),this,SLOT(lineEdit_clicked()));
    //按钮样式设置 add by 2020.04.04
    m_pUi->upBtn->setStyleSheet("border:2px groove gray;border-radius:14px;padding:2px 4px;background-color: rgb(35, 210, 92);");
    m_pUi->nextBtn->setStyleSheet("border:2px groove gray;border-radius:14px;padding:2px 4px;background-color: rgb(35, 210, 92);");
    m_pUi->firstBtn->setStyleSheet("border:2px groove gray;border-radius:14px;padding:2px 4px;background-color: rgb(35, 210, 92);");
    m_pUi->tailBtn->setStyleSheet("border:2px groove gray;border-radius:14px;padding:2px 4px;background-color: rgb(35, 210, 92);");
    m_vec_statusData.clear();
    m_iCurrPage=1;
    m_iTotalPage=1;
    m_iRemindNum=0;
    m_itotaltime=0;        //seconds
    m_ithistime=0;        //本次时间 add by 2020.08.15
    m_pUi->tableWidget->setRowCount(ROWS_PER_PAGE);//默认设置100行
    m_pUi->lineEdit_page->setText(QString::number(m_iCurrPage));
    // add by zw 20220223
    m_pUi->tableWidget->resizeColumnsToContents();//根据内容自适应宽度
    //end add by zw 20220223
}
//设置选择页面初始化@@@
void CMymainWindow::initSetPage()
{
    m_defaultBgColor=QColor("#154b6b");
    m_mouseclickColor=QColor("#1AAAFF");
    m_jjtjBgColor=QColor("#FFFFFF");
    m_jjtjclickedColor=QColor("#B3B3B3");

    m_adjcoeficon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"adjcoef.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_chainseticon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"chainset.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_procfuncicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"passwordset.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_procvalueicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"basicpara.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_dcseticon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"dcset.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_invalidseticon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"invalidset.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_tempericon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"temperature.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_faultstatusicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"faultstatus.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_runningicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"running.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_hiscurveicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"hiscurve.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_longrangectlicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"remotectl.png"), QSize(), QIcon::Normal, QIcon::Off);

    //校核系数按钮设置背景
    m_pUi->adjBtn->setIcon(m_adjcoeficon);
    m_pUi->adjBtn->setIconSize(QSize(54, 54));
    m_pUi->adjBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->adjBtn->setBackgroundColor(m_defaultBgColor);
    //连锁设置按钮设置背景
    m_pUi->chainBtn->setIcon(m_chainseticon);
    m_pUi->chainBtn->setIconSize(QSize(128, 128));
    m_pUi->chainBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->chainBtn->setBackgroundColor(m_defaultBgColor);
    //保护阈值按钮设置背景
    /*m_pUi->thrBtn->setIcon(m_procvalueicon);
    m_pUi->thrBtn->setIconSize(QSize(54, 54));
    m_pUi->thrBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->thrBtn->setBackgroundColor(m_defaultBgColor);*/
    //基本参数按钮设置背景(add by zqc 2019.06.01)
    m_pUi->basicparaBtn->setIcon(m_procvalueicon);
    m_pUi->basicparaBtn->setIconSize(QSize(128, 128));
    m_pUi->basicparaBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->basicparaBtn->setBackgroundColor(m_defaultBgColor);
    //xitong按钮设置背景(add by chenchen 2020.08.10)
    m_pUi->syssetBtn->setIcon(m_procvalueicon);
    m_pUi->syssetBtn->setIconSize(QSize(128, 128));
    m_pUi->syssetBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->syssetBtn->setBackgroundColor(m_defaultBgColor);
    //直流按钮设置背景
    /*m_pUi->dcBtn->setIcon(m_dcseticon);
    m_pUi->dcBtn->setIconSize(QSize(54, 54));
    m_pUi->dcBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->dcBtn->setBackgroundColor(m_defaultBgColor);*/
    //无效按钮设置背景
    m_pUi->invalidBtn->setIcon(m_invalidseticon);
    m_pUi->invalidBtn->setIconSize(QSize(54, 54));
    m_pUi->invalidBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->invalidBtn->setBackgroundColor(m_defaultBgColor);
    //密码设置按钮设置背景
    m_pUi->pwdsetBtn->setIcon(m_procfuncicon);
    m_pUi->pwdsetBtn->setIconSize(QSize(54, 54));
    m_pUi->pwdsetBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->pwdsetBtn->setBackgroundColor(m_defaultBgColor);
    //远程控制按钮设置背景
    m_pUi->lrctlBtn->setIcon(m_longrangectlicon);
    m_pUi->lrctlBtn->setIconSize(QSize(54, 54));
    m_pUi->lrctlBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pUi->lrctlBtn->setBackgroundColor(m_defaultBgColor);
    //紧机停机按钮设置背景颜色
     m_pUi->jjtjBtn->setBackgroundColor(m_jjtjBgColor);
    //信号与槽初始化
    connect(m_pUi->chainBtn,SIGNAL(clicked()),this,SLOT(chainBtn_clicked()));    //连锁设置
    connect(m_pUi->adjBtn,SIGNAL(clicked()),this,SLOT(adjBtn_clicked()));        //校核系数
    //connect(m_pUi->thrBtn,SIGNAL(clicked()),this,SLOT(thrBtn_clicked()));        //保护阈值
    connect(m_pUi->pwdsetBtn,SIGNAL(clicked()),this,SLOT(pwdsetBtn_clicked()));  //密码设置
    connect(m_pUi->invalidBtn,SIGNAL(clicked()),this,SLOT(invalidBtn_clicked()));//无效设置
    //connect(m_pUi->dcBtn,SIGNAL(clicked()),this,SLOT(dcBtn_clicked()));          //直流设置
    connect(m_pUi->basicparaBtn,SIGNAL(clicked()),this,SLOT(basicparaBtn_clicked()));//基本参数,add by 2019.06.01
    connect(m_pUi->lrctlBtn,SIGNAL(clicked()),SLOT(lrctlBtn_clicked()));//远程控制信号与槽函数，add by 2019.08.21
    m_pAdjcoefdlg = new CAdjcoefdlg(m_nGPIOfd);
    m_pChainsetdlg = new CChainsetdlg(m_nGPIOfd);
    //add by zw 20220223
    m_pNewAdjdlg = new newadjdlg();
    //end add by zw 20220223
}
//主柜开关量状态页面初始化
void CMymainWindow::initMasterDIPage(QIcon icon)
{
    //"滑台过位移"状态灯初始化
    m_pUi->toolButton_htgwy->setIcon(icon);
    m_pUi->toolButton_htgwy->setIconSize(QSize(32, 32));
    //"振动台过位移"状态灯初始化
    m_pUi->toolButton_zdtgwy->setIcon(icon);
    m_pUi->toolButton_zdtgwy->setIconSize(QSize(32, 32));
    //"滑台低液位"状态灯初始化
    m_pUi->toolButton_htdyw->setIcon(icon);
    m_pUi->toolButton_htdyw->setIconSize(QSize(32, 32));
    //"滑台轴承低压"状态灯初始化
    m_pUi->toolButton_htzcdy->setIcon(icon);
    m_pUi->toolButton_htzcdy->setIconSize(QSize(32, 32));
    //"振动台过温"状态灯初始化
    m_pUi->toolButton_zdtgw->setIcon(icon);
    m_pUi->toolButton_zdtgw->setIconSize(QSize(32, 32));
    //"功放热继保护"状态灯初始化
    m_pUi->toolButton_gfrjbh->setIcon(icon);
    m_pUi->toolButton_gfrjbh->setIconSize(QSize(32, 32));
    //"系统冷却单元"状态灯初始化
    m_pUi->toolButton_xtlqdy->setIcon(icon);
    m_pUi->toolButton_xtlqdy->setIconSize(QSize(32, 32));

    //"静压轴承低压"状态灯初始化
    m_pUi->toolButton_jyzcdy->setIcon(icon);
    m_pUi->toolButton_jyzcdy->setIconSize(QSize(32, 32));
    //"主柜门保护"状态灯初始化
    m_pUi->toolButton_zgmbh->setIcon(icon);
    m_pUi->toolButton_zgmbh->setIconSize(QSize(32, 32));
    //"紧急停机"状态灯初始化
    m_pUi->toolButton_jjtj->setIcon(icon);
    m_pUi->toolButton_jjtj->setIconSize(QSize(32, 32));
    //"S紧急停机"状态灯初始化
    m_pUi->toolButton_sjjtj->setIcon(icon);
    m_pUi->toolButton_sjjtj->setIconSize(QSize(32, 32));
    //"自定义1"状态灯初始化
    m_pUi->toolButton_seldefine1->setIcon(icon);
    m_pUi->toolButton_seldefine1->setIconSize(QSize(32, 32));
    //"主柜整流桥过温"状态灯初始化
    m_pUi->toolButton_seldefine4->setIcon(icon);
    m_pUi->toolButton_seldefine4->setIconSize(QSize(32, 32));
    //"自定义2"状态灯初始化
    m_pUi->toolButton_seldefine2->setIcon(icon);
    m_pUi->toolButton_seldefine2->setIconSize(QSize(32, 32));
    //"自定义3"状态灯初始化
    m_pUi->toolButton_seldefine3->setIcon(icon);
    m_pUi->toolButton_seldefine3->setIconSize(QSize(32, 32));
    //"自定义4"状态灯初始化
    m_pUi->toolButton_seldefine4->setIcon(icon);
    m_pUi->toolButton_seldefine4->setIconSize(QSize(32, 32));

    m_ybonicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"yb_on.png"), QSize(48,16), QIcon::Normal, QIcon::Off);
    m_ybofficon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"yb_off.png"), QSize(48,16), QIcon::Normal, QIcon::Off);

}
//分柜控制子页面初始化@@@
void CMymainWindow::initSlaveControlPage(QIcon icon)
{
    //分柜运行状态按钮灯状态
    //信号与槽初始化
   connect(m_pUi->toolButton_HisCurve,SIGNAL(clicked()),this,SLOT(hisCurveBtn_clicked()));
   connect(m_pUi->sub1Btn,SIGNAL(clicked()),this,SLOT(sub1Btn_clicked()));
   connect(m_pUi->sub2Btn,SIGNAL(clicked()),this,SLOT(sub2Btn_clicked()));
   connect(m_pUi->sub3Btn,SIGNAL(clicked()),this,SLOT(sub3Btn_clicked()));
   connect(m_pUi->sub4Btn,SIGNAL(clicked()),this,SLOT(sub4Btn_clicked()));

     m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));
     /******状态灯颜色初始化******/
    //"分柜1整流器过温"状态灯初始化
     m_pUi->toolButton_fg1zlqgw->setIcon(icon);
     m_pUi->toolButton_fg1zlqgw->setIconSize(QSize(32, 32));
    //"分柜1门保护"状态灯初始化
     m_pUi->toolButton_fg1mbh->setIcon(icon);
     m_pUi->toolButton_fg1mbh->setIconSize(QSize(32, 32));

    //"分柜2整流器过温"状态灯初始化
     m_pUi->toolButton_fg2zlqgw->setIcon(icon);
     m_pUi->toolButton_fg2zlqgw->setIconSize(QSize(32, 32));
      //"分柜2门保护"状态灯初始化
     m_pUi->toolButton_fg2mbh->setIcon(icon);
     m_pUi->toolButton_fg2mbh->setIconSize(QSize(32, 32));

    //"分柜3整流器过温"状态灯初始化
     m_pUi->toolButton_fg3zlqgw->setIcon(icon);
     m_pUi->toolButton_fg3zlqgw->setIconSize(QSize(32, 32));
     //"分柜3门保护"状态灯初始化
     m_pUi->toolButton_fg3mbh->setIcon(icon);
     m_pUi->toolButton_fg3mbh->setIconSize(QSize(32, 32));

     //"分柜4整流器过温"状态灯初始化
     m_pUi->toolButton_fg4zlqgw->setIcon(icon);
     m_pUi->toolButton_fg4zlqgw->setIconSize(QSize(32, 32));
     //"分柜4门保护"状态灯初始化
     m_pUi->toolButton_fg4mbh->setIcon(icon);
     m_pUi->toolButton_fg4mbh->setIconSize(QSize(32, 32));

    /******状态灯颜色初始化******/
     m_pTempmonitorWdgt=NULL;
     m_pTempmonitorWdgt=new CTempMonitorWidget(this);
     m_pRunStaWdget=NULL;
     m_pRunStaWdget=new CRunningStatusWidget(this);
}
//更新开入量数据
void CMymainWindow::updateDI(int nDIValue,QToolButton *ToolButton)
{
    switch(nDIValue)
    {
    case 0:
        ToolButton->setIcon(m_redicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;
    case 1:
        ToolButton->setIcon(m_greenicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;
    default:
        ToolButton->setIcon(m_yellowicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;

    }//switch(nDIValue)
     QCoreApplication::processEvents();//避免界面冻结
}
//更新从柜运行状态
void CMymainWindow::updateSlaveStatusData(int nStaValue,int nSubopen,QToolButton *ToolButton)
{
    int nTemp=-1;
    nTemp = nStaValue&&nSubopen;
    switch(nTemp)
    {
    case 0:
        ToolButton->setIcon(m_redicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;
    case 1:
        ToolButton->setIcon(m_greenicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;
    default:
        ToolButton->setIcon(m_yellowicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;

    }//switch(nStaValue)
     QCoreApplication::processEvents();//避免界面冻结
}

//更新状态数据
void CMymainWindow::updateStatusData(int nStaValue,QToolButton *ToolButton)
{
    switch(nStaValue)
    {
    case 0:
        ToolButton->setIcon(m_redicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;
    case 1:
        ToolButton->setIcon(m_greenicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;
    default:
        ToolButton->setIcon(m_yellowicon);
        ToolButton->setIconSize(QSize(32, 32));
        break;

    }//switch(nStaValue)
     QCoreApplication::processEvents();//避免界面冻结
}
//接收CAN总线"温度监控"、"故障状态"、"运行状态"数据
//void CMymainWindow::on_recvCANTempCtlCANRPT(int socket)
//{
//	on_recvIGBTTempCtlCANRPT(socket);
//	on_recvFaultCANRPT(socket);
//	on_recvRunningCANRPT(socket);
//}
//打开"温度监控"子界面(数据源为CAN总线)
void CMymainWindow::tempCtlBtn_clicked()
{
     QCoreApplication::processEvents();//避免界面冻结
#ifdef UBUNTU_DEV //Compiler Switch
    //断开运行状态信号连接
    //disconnect(m_notifier,0,0,0);
    //接收温度监控CAN报文（启动信号连接）
    //connect(m_notifier, SIGNAL(activated(int)), this, SLOT(on_recvIGBTTempCtlCANRPT(int)));
    //connect(m_notifier, SIGNAL(activated(int)), this, SLOT(on_recvIDUCTTempCtlCANRPT(int)));
#endif
    m_pUi->toolButton_TempCtl->setBackgroundColor(m_mouseclickColor);
    m_pTempmonitorWdgt->exec();
    m_pUi->toolButton_TempCtl->setBackgroundColor(m_defaultBgColor);
}
//打开"故障状态"子界面(数据源为CAN总线)@@@
void CMymainWindow::faultStaBtn_clicked()
{
     QCoreApplication::processEvents();//避免界面冻结
#ifdef UBUNTU_DEV //Compiler Switch
    //断开运行状态信号连接
    //disconnect(m_notifier,0,0,0);
    //接收故障状态CAN报文（启动信号连接）
    //connect(m_notifier, SIGNAL(activated(int)), this, SLOT(on_recvFaultCANRPT(int)));
#endif
    m_pUi->toolButton_FaultSta->setBackgroundColor(m_mouseclickColor);
    m_FaultCondWdgt.exec();
    m_pUi->toolButton_FaultSta->setBackgroundColor(m_defaultBgColor);

}
//打开"运行状态"子界面(数据源为CAN总线)
void  CMymainWindow::runningStaBtn_clicked()
{
    QCoreApplication::processEvents();//避免界面冻结
#ifdef UBUNTU_DEV //Compiler Switch
    //断开运行状态信号连接
    //disconnect(m_notifier,0,0,0);
    //接收运行状态CAN报文（启动信号连接）
    //connect(m_notifier, SIGNAL(activated(int)), this, SLOT(on_recvRunningCANRPT(int)));
#endif
    m_pUi->toolButton_RunningSta->setBackgroundColor(m_mouseclickColor);
    m_pRunStaWdget->exec();
    m_pUi->toolButton_RunningSta->setBackgroundColor(m_defaultBgColor);

}
//打开"历史曲线"子界面(槽函数)@@@
void CMymainWindow::hisCurveBtn_clicked()
{
    m_pUi->toolButton_HisCurve->setBackgroundColor(m_mouseclickColor);
    m_HiscurveWdget.exec();
    m_pUi->toolButton_HisCurve->setBackgroundColor(m_defaultBgColor);
}
//功放启动-槽函数
void CMymainWindow::gfstartBtn_clicked()
{
#ifdef UBUNTU_DEV //Compiler Switch
    QString strStartEnd=QApplication::translate("mainWindow",
        "\345\212\237\346\224\276\345\220\257\345\212\250\346\223\215\344\275\234\347\273\223\346\235\237",
        0,
        QApplication::UnicodeUTF8);//功放启动操作结束
    m_GfStartFlag=true;//功放启动操作标志置“true”,add by 2019.05.12
    m_pGPIORecvThread->m_iGfstartflag=m_GfStartFlag;
    //add by zw 20220223
    m_pdataReadThread->m_iGfstartflag = true;
    //end add by zw 20220223

    m_nSectionPos=PROCESS_SECTION_01;
    m_pUi->toolButton_gfstart->setEnabled(false);//禁用状态
    m_pUi->toolButton_Set->setEnabled(false);//功放启动后禁用设置功能，add by 2020.08.21
    if(!m_GfTestPauseFlag)
    {
        //--没有收到通用保护信息，正常执行S1段操作
        //台体、功放冷却系统启动（指令或者继电器）
#ifndef NEWCODE_SW
        m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0C,write_data_1,m_nGPIOfd);
        delay();
        g_GPIOData.iCoolingState=1;  //冷却系统绿灯亮
        //LED Panel-警报灯灭
        m_pGPIORecvThread->m_Gpiorw.write_do(write_address_84,write_data_0,m_nGPIOfd);
#endif
        //add by zw 20220223
        //开启冷却系统继电器
#ifdef NEWCODE_SW  //new code running switch by zw 20220223
        OpenOneOutIO(COOLING);
        printf("####Starting of Cooling Relay ####\n");
        //点亮主页面冷却指示灯
        g_newaddata.iCoolingState = LED_GREEN;
        //end add by zw 20220223
#endif
        //等待5秒钟
        m_pTimer5s->start(5000);//启动5s定时器，add by 2019.04.14
    }
    //else
    //{
    //	printf("protect\n");
    //	//--收到通用保护信息，立即中断
    //	OperationSection2();//新加操作同OperationSection2
    //	initGfStartSet();
    //}
#endif  //Compiler Switch

    m_OutputRecord.writeStartOutputfile();//将功放启动记录写入OutputRecord文件 add by 2020.11.12
}
//功放停止-槽函数
void CMymainWindow::gfstopBtn_clicked()
{
    //关闭蜂鸣器
    ioctl(fd_beep,0,0);
    m_pUi->toolButton_gfstop->setEnabled(false);//禁止状态
    m_pUi->toolButton_Set->setEnabled(true);//功放停止后启用设置功能，add by 2020.08.21
    m_GfStopFlag=true;
    m_OutputRecord.writeStopOutputfile();//将功放停止记录写入OutputRecord文件 add by 2020.11.12
#ifdef UBUNTU_DEV //Compiler Switch
    if(m_pTimer5s->isActive())
    {
        m_pTimer5s->stop();//5s定时器处于"开"的状态，应及时停止
    }
    if(m_pTimer3s->isActive())
    {
        m_pTimer3s->stop();//3s定时器处于"开"的状态，应及时停止
    }
    if(m_pTimer1s->isActive())
    {
        m_pTimer1s->stop();//1s定时器处于"开"的状态，应及时停止
    }
    //断开其他继电器，除了冷却系统
     DisAllRelaysExCoolSystem();
     //等待60秒
     //QMessageBox::warning(this, tr(m_strInfo), tr(m_strWait60s));//需要等待60秒钟，请稍候
     zystopBtn_clicked();//软件关闭使能
     initGfStartSet();
     printf("####DisAllRelays####\n");
     m_pTimer60s->start(60000);//启动60s定时器
     m_Timer60StartFlag=true;
     if(!m_CountDownWdgt.isVisible())
     {
        m_CountDownWdgt.exec();
     }
#endif  //Compiler Switch
}
//功放复位-槽函数
void CMymainWindow::gfresetBtn_clicked()
{
    /*
     if(g_iLangChange==1)
    {
        m_pUi->label_connect->setText(m_strConnection);  //add by 2020.11.25
    }
    else
    {
        m_pUi->label_connect->setText("Connection status is normal");//addby 2020.11.25
    }
    */

#ifdef UBUNTU_DEV //Compiler Switch
  QString strResetEnd=QApplication::translate("mainWindow",
        "\345\212\237\346\224\276\345\244\215\344\275\215\346\223\215\344\275\234\347\273\223\346\235\237",
        0,
        QApplication::UnicodeUTF8);//功放复位操作结束

    m_pUi->toolButton_gfreset->setEnabled(false);//禁止状态
    m_pUi->toolButton_Set->setEnabled(true);//功放停止后启用设置功能，add by 2020.08.21
    m_pdataReadThread->m_iGfstartflag = false;
    m_pGPIORecvThread->m_iGfstartflag = false;
    m_GfStartFlag = false;
#ifdef NEWCODE_SW
    g_newaddata.iFaultState=-1;//熄灭故障状态灯
    //关闭蜂鸣器
    ioctl(fd_beep,0,0);
    zyStop_ad5292();
#endif
    initGfStartSet();//add by 2019.05.24
    m_pUi->label_procinfo->clear();
#ifndef NEWCODE_SW
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_00,write_data_1,m_nGPIOfd);//1:复位FPGA
    printf("####gfresetBtn_clicked():Power Amplifier Reset FPGA ####\n");
    delay();
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_00,write_data_0,m_nGPIOfd);//0:释放FPGA
    printf("####gfresetBtn_clicked():Power Amplifier Free FPGA ####\n");
    g_GPIOData.iFaultState=-1;//熄灭故障状态灯,add by 2019.06.17
    //LED Panel-熄灭警报灯,蜂鸣器响
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_84,write_data_0,m_nGPIOfd);//add by 2019.04.16
    delay();
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_5C,write_data_0+qPow(2,10),m_nGPIOfd);//初始化滑块到0，add by 2019.05.30
#endif

#endif  //Compiler Switch
    if(!iLongrCtl)
    {
        m_pUi->toolButton_gfreset->setEnabled(true);//开启状态
        m_pUi->toolButton_gfstart->setEnabled(true);//功放启动按钮重新开放,add by 2019.05.21
    }
    m_GfTestPauseFlag=false;
    m_ExcitExistFlag=false;
#ifdef UBUNTU_DEV //Compiler Switch
    /*QMessageBox::information(this,
        tr(m_strInfo),
        tr(strResetEnd));*/
#endif  //Compiler Switch
}
 //"增益启动"槽函数
void CMymainWindow::zystartBtn_clicked()
{
    QIcon starticon,stopicon;
    starticon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"Gain-off.png"), QSize(), QIcon::Normal, QIcon::Off);
    stopicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"Gain-on.png"), QSize(), QIcon::Normal, QIcon::Off);
    if(!m_GainStartFlag)
    {
        //设置增益控制组的"停止按钮"图标
        m_pUi->toolButton_zystart->setIcon(stopicon);
        m_pUi->toolButton_zystart->setIconSize(QSize(64, 64));
         QString strZYstart=QApplication::translate("mainWindow",
          "\345\242\236\347\233\212\345\220\257\345\212\250\346\223\215\344\275\234\347\273\223\346\235\237",
          0,
          QApplication::UnicodeUTF8);//增益启动操作结束
#ifdef UBUNTU_DEV //Compiler Switch
#ifndef NEWCODE_SW
        m_pGPIORecvThread->m_Gpiorw.write_do(write_address_5C,write_data_0+qPow(2,10),m_nGPIOfd);
#endif
#ifdef NEWCODE_SW
        //加载增益函数
        zyNstart_ad5292(i_zyLoadPerc);
#endif
        if(!iLongrCtl)
        {
            m_pUi->horizontalScrollBar->setEnabled(true);//开放滑块，add by 2019.05.28
            m_pUi->comboBox_gear->setEnabled(true);//开放挡位选择，add by 2019.05.28
        }
        startupBtn_clicked();//启动功率模块，add by 2019.05.28
#ifndef NEWCODE_SW
        g_GPIOData.iGainState=1;//将增益状态灯置为绿色，add by 2019.05.28
#endif
#ifdef NEWCODE_SW
        g_newaddata.iGainState = LED_GREEN;//将增益状态灯置为绿色
#endif
        printf("####zystartBtn_clicked():Gain Start####\n");
#endif  //Compiler Switch
    //QMessageBox::information(this,
    //	tr(m_strInfo),
    //	tr(strZYstart));
      m_GainStartFlag=true;
    }
    else
    {
       zystopBtn_clicked();
       m_GainStartFlag=false;
    }
}
//"增益停止"槽函数
void CMymainWindow::zystopBtn_clicked()
{
     QIcon starticon;
        //设置增益控制组的"启动按钮"图标
     starticon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"Gain-off.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_pUi->toolButton_zystart->setIcon(starticon);
    m_pUi->toolButton_zystart->setIconSize(QSize(64, 64));
     QString strZYstop=QApplication::translate("mainWindow",
     "\345\242\236\347\233\212\345\201\234\346\255\242\346\223\215\344\275\234\347\273\223\346\235\237",
     0,
     QApplication::UnicodeUTF8);//增益停止操作结束
#ifdef UBUNTU_DEV //Compiler Switch
#ifdef NEWCODE_SW //new code running switch by zw 20220223
     //add by zw 20220223
     //关闭增益输出
     zyStop_ad5292();
     //end add by zw 20220223
#endif
    shutdownBtn_clicked();//功率模块关机，add by 2019.05.28
    //m_pGPIORecvThread->m_Gpiorw.write_do(write_address_5C,write_data_0+qPow(2,10),m_nGPIOfd);//qPow(2 ,10)是标识高4位为0001
    //delay();
    m_pUi->horizontalScrollBar->setValue(0);//进度条恢复为0位置，add by 2019.05.26
    m_pUi->horizontalScrollBar->setEnabled(false);//禁用滑块，add by 2019.05.28
    m_pUi->comboBox_gear->setEnabled(false);//禁用挡位选择，add by 2019.05.28
#ifndef NEWCODE_SW //new code running switch by zw 20220223
    g_GPIOData.iGainState=-1;//将增益状态灯置为黄色，add by 2019.05.28
#endif
#ifdef NEWCODE_SW
    g_newaddata.iGainState = LED_YELLOW;//将增益状态灯置为黄色
#endif
    m_pUi->label_slider->setText(tr("0%"));//进度值为0%位置，add by 2019.05.26
    printf("####:zystopBtn_clicked():Gain Stop####\n");
#endif  //Compiler Switch
    //QMessageBox::information(this,
    //	tr(m_strInfo),
    //	tr(strZYstop));
}
//判断冷却系统是否有保护@@@暂不使用
bool CMymainWindow::CheckXtlqProcExist()
{
#ifdef UBUNTU_DEV //Compiler Switch
    g_Mutex.lock();
    if((g_GPIOData.iMasterDI[11]==1)&&(m_ChainSetData.iXtlqdyVal==SWITCH_ON))
    {
        for(int i=0;i<MAX_SIZE;i++)
        {
            printf("CheckXtlqProcExist()--g_GPIOData.iMasterDI[%d]=%d\n",i,g_GPIOData.iMasterDI[i]);
        }
        g_Mutex.unlock();
        return true;
    }
    else
    {
        g_Mutex.unlock();
    }
#endif  //Compiler Switch
    return false;
}
//等待5秒-槽函数
void CMymainWindow::waiting5second()
{
#ifdef UBUNTU_DEV //Compiler Switch
    m_nSectionPos=PROCESS_SECTION_02;//执行到S2段
    printf("#####five seconds have passed #####\n");
    if(m_pTimer5s->isActive())
    {
        m_pTimer5s->stop();//5s定时器处于"开"的状态，应及时停止
    }
    bool isXtlqExist=false;
#ifndef NEWCODE_SW
    isXtlqExist=CheckXtlqProcExist();
#endif
#ifdef NEWCODE_SW  //new code running switch by zw 20220223
    isXtlqExist = m_JudgeProc.newCheckXtlqProcExist(g_newchasetdata);
#endif
    if(isXtlqExist)
    { /*冷却系统有保护-内部保护（序号1）*/
        m_pUi->label_procinfo->setText(m_strxtlqdy);//add by zqc 2019.07.15
        m_pGPIORecvThread->createStatusRecordFile(m_strxtlqdy);//add by zqc 2019.07.15
        if(iLongrCtl)
        {
            PROTECTsendMesg(m_strxtlqdy);
        }
        OperationSection2();
        initGfStartSet();
    }
    else
    {
        /*冷却系统没有保护*/
       if(m_iMode==NORMAL_MODE)
        {
              /*正常模式下*/
            if(!m_GfTestPauseFlag)
            {
#ifndef NEWCODE_SW
              m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0E,write_data_1,m_nGPIOfd);//励磁继电器启动
              printf("####Starting of Excitation Relay in Normal Mode####\n");
              m_pUi->DebugTextEdit->append("####Starting of Excitation Relay in Normal Mode####\n");
#endif
#ifdef NEWCODE_SW //new code running switch by zw 20220223
              OpenOneOutIO(FIELD);
              printf("####Starting of Excitation Relay in Normal Mode####\n");
              m_pUi->DebugTextEdit->append("####Starting of Excitation Relay in Normal Mode####\n");
#endif
              delay();
              m_ExcitExistFlag=true;
              printf("m_ExcitExistFlag=true\n");
              if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
              {
#ifndef NEWCODE_SW
                m_pGPIORecvThread->m_Gpiorw.write_do(write_address_16,write_data_1,m_nGPIOfd);//分柜0软启动
                printf("####Soft start of sub-cabinet 0 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 0 in Normal Mode####\n");
#endif
#ifdef NEWCODE_SW
                OpenOneOutIO(K1_0);
                printf("####Soft start of sub-cabinet 0 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 0 in Normal Mode####\n");
#endif
                delay();
              }
              if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
              {
#ifndef NEWCODE_SW
                m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1A,write_data_1,m_nGPIOfd);//分柜1软启动
                printf("####Soft start of sub-cabinet 1 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 1 in Normal Mode####\n");
#endif
#ifdef NEWCODE_SW
                OpenOneOutIO(K2_0);
                printf("####Soft start of sub-cabinet 1 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 1 in Normal Mode####\n");
#endif
                delay();
              }

              if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
              {
#ifndef NEWCODE_SW
                m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1E,write_data_1,m_nGPIOfd);//分柜2软启动
                printf("####Soft start of sub-cabinet 2 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 2 in Normal Mode####\n");
#endif
#ifdef NEWCODE_SW
                OpenOneOutIO(K3_0);
                printf("####Soft start of sub-cabinet 2 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 2 in Normal Mode####\n");
#endif
                delay();
              }

              if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
              {
#ifndef NEWCODE_SW
                m_pGPIORecvThread->m_Gpiorw.write_do(write_address_22,write_data_1,m_nGPIOfd);//分柜3软启动
                printf("####Soft start of sub-cabinet 3 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 3 in Normal Mode####\n");
#endif
#ifdef NEWCODE_SW
                OpenOneOutIO(K4_0);
                printf("####Soft start of sub-cabinet 3 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 3 in Normal Mode####\n");
#endif
                delay();
              }
              //等待3秒钟
              m_pTimer3s->start(3000);//启动3s定时器
            }
        }
        else if( m_iMode==DEBUG_MODE)
        {
              /*调试模式下*/
            if(!m_GfTestPauseFlag)
            {
                //没有保护存在，分柜软启动继电器吸合
              if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
              {
#ifndef NEWCODE_SW
                m_pGPIORecvThread->m_Gpiorw.write_do(write_address_16,write_data_1,m_nGPIOfd);//分柜0软启动
                printf("####Soft start of sub-cabinet 0 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 0 in Normal Mode####\n");
#endif
#ifdef NEWCODE_SW
                OpenOneOutIO(K1_0);
                printf("####Soft start of sub-cabinet 0 in Debug Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 0 in Debug Mode####\n");
#endif
                delay();
              }

              if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
              {
#ifndef NEWCODE_SW
                m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1A,write_data_1,m_nGPIOfd);//分柜1软启动
                printf("####Soft start of sub-cabinet 1 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 1 in Debug Mode####\n");
#endif
#ifdef NEWCODE_SW
                OpenOneOutIO(K2_0);
                printf("####Soft start of sub-cabinet 1 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 1 in Debug Mode####\n");
#endif
                delay();
              }

              if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
              {
#ifndef NEWCODE_SW
                m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1E,write_data_1,m_nGPIOfd);//分柜2软启动
                printf("####Soft start of sub-cabinet 2 in Debug Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 2 in Debug Mode####\n");
#endif
#ifdef NEWCODE_SW
                OpenOneOutIO(K3_0);
                printf("####Soft start of sub-cabinet 2 in Debug Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 2 in Debug Mode####\n");
#endif
                delay();
              }

              if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
              {
#ifndef NEWCODE_SW
                m_pGPIORecvThread->m_Gpiorw.write_do(write_address_22,write_data_1,m_nGPIOfd);//分柜3软启动
                printf("####Soft start of sub-cabinet 3 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 3 in Debug Mode####\n");
#endif
#ifdef NEWCODE_SW
                OpenOneOutIO(K4_0);
                printf("####Soft start of sub-cabinet 3 in Normal Mode####\n");
                m_pUi->DebugTextEdit->append("####Soft start of sub-cabinet 3 in Debug Mode####\n");
#endif
                delay();
              }
              //等待3秒钟
              m_pTimer3s->start(3000);//启动3s定时器
            }
        }
    }
#endif  //Compiler Switch
}
//功放启动初始化设置,add by 2019.05.21@@@
void CMymainWindow::initGfStartSet()
{
    m_nSectionPos=PROCESS_SECTION_NULL;//段位置恢复默认值,add by 2019.05.21
    m_GfStartFlag=false;
    m_ExcitExistFlag=false;
#ifdef UBUNTU_DEV //Compiler Switch
    m_pGPIORecvThread->m_iGfstartflag=false;
    m_pdataReadThread->m_iGfstartflag = false;
#ifndef NEWCODE_SW //new code running switch by zw 20220223
    g_GPIOData.iGainState=-1;//将增益状态灯置为黄色，add by 2019.05.28
    g_GPIOData.iReadyState=-1;//将准备状态灯置为黄色，add by 2019.05.28
#endif
#ifdef NEWCODE_SW //new code running switch by zw 20220223
    g_newaddata.iGainState = -1; //将增益状态灯置为黄色，add by zw 2022.02.23
    g_newaddata.iReadyState = -1; //将准备状态灯置为黄色，add by zw 2022.02.23
    g_newaddata.iExcitationState = -1;//将励磁状态灯置为黄色
#endif
    if(m_iMode==NORMAL_MODE)
    {
        m_pUi->toolButton_zystart->setEnabled(false);
    }
 #endif
}
//等待1秒-槽函数
void CMymainWindow::waiting1second()
{
#ifdef UBUNTU_DEV //Compiler Switch
 printf("#####one seconds have passed #####\n");
    if(m_pTimer1s->isActive())
    {
        m_pTimer1s->stop();//1s定时器处于"开"的状态，应及时停止
    }
    bool isXtlqExist=false;
    bool isExcitExist=false;
    bool isVoltDown=false;
    int  iBusVoltDownCnt=0;
    QString strtmep;
    //--检测是否存在系统冷却单元(序号1)
#ifndef NEWCODE_SW
    isXtlqExist=CheckXtlqProcExist();
#endif
#ifdef NEWCODE_SW
    isXtlqExist = m_JudgeProc.newCheckXtlqProcExist(g_newchasetdata);
#endif
    if(isXtlqExist)
    {
         m_pUi->label_procinfo->setText(m_strxtlqdy);//add by zqc 2019.07.15
         m_pGPIORecvThread->createStatusRecordFile(m_strxtlqdy);//add by zqc 2019.07.15
         m_pUi->DebugTextEdit->append(m_JudgeProc.m_strxtlqdy);//add by 2019.05.26
         if(iLongrCtl)
         {
            PROTECTsendMesg(m_JudgeProc.m_strxtlqdy);
         }
    }
    if(m_GfTestPauseFlag)
    {
//         g_Mutex.lock();
         //m_pGPIORecvThread->createStatusRecordFileByList(g_strlistGeneralProc);//del by 2020.09.05
         m_pGPIORecvThread->createStatusRecordFileByVector(g_vec_StatusRecord);//add by 2020.09.05
//         g_Mutex.unlock();
    }
    if(m_iMode==NORMAL_MODE)
    {
      //--正常模式
         m_nSectionPos=PROCESS_SECTION_04;//S4段
         g_Mutex.lock();
#ifndef NEWCODE_SW
        isExcitExist=m_JudgeProc.CheckExcitProcExist(g_GPIOData);
#endif
#ifdef NEWCODE_SW
        isExcitExist=m_JudgeProc.newCheckExcitProcExist(g_newaddata);
#endif
         g_Mutex.unlock();
         if(isExcitExist)
         {
              m_pUi->label_procinfo->setText(m_JudgeProc.m_strExcitopen);//add by zqc 2019.07.15
              m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strExcitopen);//add by zqc 2019.07.15
              m_pUi->DebugTextEdit->append(m_JudgeProc.m_strExcitopen);//add by 2019.05.26
              if(iLongrCtl)
              {
                PROTECTsendMesg(m_JudgeProc.m_strExcitopen);
              }
         }
          //--检测是否存在母线电压过低(序号25),addd by 2019.05.24
         g_Mutex.lock();
#ifndef NEWCODE_SW
         isVoltDown=m_JudgeProc.CheckBusVoltDownExist(g_GPIOData,iBusVoltDownCnt);
#endif
#ifdef NEWCODE_SW
         isVoltDown=m_JudgeProc.newCheckBusVoltDownExist(g_newaddata,iBusVoltDownCnt);
#endif
         g_Mutex.unlock();
         if(isVoltDown)
         {
            m_pUi->label_procinfo->setText(m_JudgeProc.m_strBusVoltDown);//add by zqc 2019.07.15
            m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strBusVoltDown);//add by zqc 2019.07.15
            m_pUi->DebugTextEdit->append(m_JudgeProc.m_strBusVoltDown);//add by 2019.05.26
            if(iLongrCtl)
            {
                PROTECTsendMesg(m_JudgeProc.m_strBusVoltDown);
            }
         }
         if(m_struLeftFaultDATA[0].iDCundervoltFlag==1)
         {
            m_pUi->label_procinfo->setText(m_JudgeProc.m_strModuleUnderVolt);//add by zqc 2019.07.15
            m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strModuleUnderVolt);//add by zqc 2019.07.15
            {
                PROTECTsendMesg(m_JudgeProc.m_strModuleUnderVolt);
            }
         }
         //--检查功放保护
         if((isXtlqExist)||(isExcitExist)||(isVoltDown)||(m_struLeftFaultDATA[0].iDCundervoltFlag==1)||(m_GfTestPauseFlag))
         {
            printf("####m_nSectionPos=%d####\n",m_nSectionPos);
            printf("isXtlqExist=%d-isExcitExist=%d-isVoltDown=%d-iDCundervoltFlag=%d\n",
              isXtlqExist,
              isExcitExist,
              isVoltDown,
              m_struLeftFaultDATA[0].iDCundervoltFlag);

            strtmep.sprintf("m_nSectionPos=%d-isXtlqExist=%d-isExcitExist=%d-isVoltDown=%d-iDCundervoltFlag=%d\n",
                        m_nSectionPos,
                        isXtlqExist,
                        isExcitExist,
                        isVoltDown,
                        m_struLeftFaultDATA[0].iDCundervoltFlag);
            m_pUi->DebugTextEdit->append(strtmep);
            m_pUi->DebugTextEdit->setStyleSheet("color:red;border:2px solid gray;");//设置为红色字体
            OperationSection34();//执行S34操作，立即中断
            initGfStartSet();
         }
         else
         {
            QCoreApplication::processEvents();//避免界面冻结,add by 2019.05.24
            //--没有收到任何保护信息
            //startupBtn_clicked();//功率模块启动,add by 2019.05.14
#ifndef NEWCODE_SW
            g_GPIOData.iReadyState=1;//设置准备状态灯为绿色，add by 2019.05.28
#endif
#ifdef NEWCODE_SW
            g_newaddata.iReadyState = LED_GREEN;
#endif
            m_pUi->toolButton_zystart->setEnabled(true);
         }
  }
  else if(m_iMode==DEBUG_MODE)
  {
    //--调试模式
    m_nSectionPos=PROCESS_SECTION_03;//S3段
    if(m_struLeftFaultDATA[0].iDCundervoltFlag==1)
    {
           m_pUi->label_procinfo->setText(m_JudgeProc.m_strModuleUnderVolt);//add by zqc 2019.07.15
           m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strModuleUnderVolt);//add by zqc 2019.07.15
           if(iLongrCtl)
           {
                PROTECTsendMesg(m_JudgeProc.m_strModuleUnderVolt);
           }
    }
    //--检查除20、25外的所有保护
    if((isXtlqExist)||(m_struLeftFaultDATA[0].iDCundervoltFlag==1)||(m_GfTestPauseFlag))
    {
        printf("####m_nSectionPos=%d####\n",m_nSectionPos);
        printf("isXtlqExist=%d-iDCundervoltFlag=%d\n",
                    isXtlqExist,
                    m_struLeftFaultDATA[0].iDCundervoltFlag);
        strtmep.sprintf("isXtlqExist=%d-iDCundervoltFlag=%d\n",
                    isXtlqExist,
                    m_struLeftFaultDATA[0].iDCundervoltFlag);
        m_pUi->DebugTextEdit->append(strtmep);
        m_pUi->DebugTextEdit->setStyleSheet("color:red;border:2px solid gray;");//设置为红色字体
        OperationSection34();
        initGfStartSet();
    }
    else
    {	//无除20、25外的所有保护
        //m_Gpiorw.write_do(write_address_5C,write_data_0+qPow(2,10),m_nGPIOfd);//增益大小为0%(和关闭增益的设置一样？)
        //--给出"使能"信号
#ifndef NEWCODE_SW
            g_GPIOData.iReadyState=1;//设置准备状态灯为绿色，add by 2019.05.28
#endif
#ifdef NEWCODE_SW
            g_newaddata.iReadyState = LED_GREEN;
#endif

    }
  }
#endif  //Compiler Switch
}
//监测S1断的保护，add by 2019.07.20
void CMymainWindow::CheckProcOfSection1()
{
#ifdef UBUNTU_DEV
    if((m_GfTestPauseFlag))
    {
        printf("####CheckProcOfSection1----m_GfTestPauseFlag=true\n");
//        g_Mutex.lock();
        //m_pGPIORecvThread->createStatusRecordFileByList(g_strlistGeneralProc);//del by 2020.09.05
        m_pGPIORecvThread->createStatusRecordFileByVector(g_vec_StatusRecord);//add by 2020.09.05
//        g_Mutex.unlock();
        if(m_pTimer5s->isActive())
        {
            m_pTimer5s->stop();//5s定时器处于"开"的状态，应及时停止
        }
        OperationSection2();
        initGfStartSet();
     }
#endif
}
//监测S2断的保护，add by 2019.07.20
void CMymainWindow::CheckProcOfSection2()
{
#ifdef UBUNTU_DEV
    bool isXtlqExist=false;
    QString strtemp;
    bool isExcitExist=false;
#ifndef NEWCODE_SW
    isXtlqExist=CheckXtlqProcExist();
#endif
#ifdef NEWCODE_SW
    isXtlqExist = m_JudgeProc.newCheckXtlqProcExist(g_newchasetdata);
#endif
    if(isXtlqExist)
    {
        printf("####CheckProcOfSection2----isXtlqExist=true\n");
        m_pUi->label_procinfo->setText(m_strxtlqdy);//add by zqc 2019.07.15
//        g_Mutex.lock();
        m_pGPIORecvThread->createStatusRecordFile(m_strxtlqdy);//add by zqc 2019.07.15
//        g_Mutex.unlock();
        m_pUi->DebugTextEdit->append(m_JudgeProc.m_strxtlqdy);//add by 2019.05.26
        if(iLongrCtl)
        {
            PROTECTsendMesg(m_JudgeProc.m_strxtlqdy);
        }
    }
    if(m_GfTestPauseFlag)
    {
        printf("####CheckProcOfSection2----m_GfTestPauseFlag=true\n");
//        g_Mutex.lock();
        //m_pGPIORecvThread->createStatusRecordFileByList(g_strlistGeneralProc);//del by 2020.09.05
        m_pGPIORecvThread->createStatusRecordFileByVector(g_vec_StatusRecord);//add by 2020.09.05
//        g_Mutex.unlock();
    }
    if(m_ExcitExistFlag)
    {
#ifndef NEWCODE_SW
        isExcitExist=m_JudgeProc.CheckExcitProcExist(g_GPIOData);
#endif
#ifdef NEWCODE_SW
        isExcitExist=m_JudgeProc.newCheckExcitProcExist(g_newaddata);
#endif
         if(isExcitExist)
         {
              printf("####CheckProcOfSection2----isExcitExist=true\n");
              m_pUi->label_procinfo->setText(m_JudgeProc.m_strExcitopen);//add by zqc 2019.07.15
//              g_Mutex.lock();
              m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strExcitopen);//add by zqc 2019.07.15
//              g_Mutex.unlock();
              m_pUi->DebugTextEdit->append(m_JudgeProc.m_strExcitopen);//add by 2019.05.26
              if(iLongrCtl)
              {
                 PROTECTsendMesg(m_JudgeProc.m_strExcitopen);
              }
         }
    }
    if((isXtlqExist)||(m_GfTestPauseFlag)||(isExcitExist))
    {
        if(m_pTimer3s->isActive())
        {
            m_pTimer3s->stop();//3s定时器处于"开"的状态，应及时停止
        }
        if(m_pTimer1s->isActive())
        {
            m_pTimer1s->stop();//1s定时器处于"开"的状态，应及时停止
        }
         strtemp.sprintf("m_nSectionPos=%d-isXtlqExist=%d\n",
                    m_nSectionPos,
                    isXtlqExist);
          m_pUi->DebugTextEdit->append(strtemp);
          m_pUi->DebugTextEdit->setStyleSheet("color:red;border:2px solid gray;");//设置为红色字体
          OperationSection2();
          initGfStartSet();
     }
#endif
}
//检测S3段的保护,add by 2019.05.24
void CMymainWindow::CheckProcOfSection3()
{
#ifdef UBUNTU_DEV //Compiler Switch
    bool isXtlqExist=false;
    QString strtemp;
#ifndef NEWCODE_SW
    isXtlqExist=CheckXtlqProcExist();
#endif
#ifdef NEWCODE_SW
    isXtlqExist = m_JudgeProc.newCheckXtlqProcExist(g_newchasetdata);
#endif
    if(isXtlqExist)
    {
        printf("####CheckProcOfSection3----isXtlqExist=true\n");
        m_pUi->label_procinfo->setText(m_strxtlqdy);//add by zqc 2019.07.15
        m_pGPIORecvThread->createStatusRecordFile(m_strxtlqdy);//add by zqc 2019.07.15
        m_pUi->DebugTextEdit->append(m_JudgeProc.m_strxtlqdy);//add by 2019.05.26
        if(iLongrCtl)
        {
            PROTECTsendMesg(m_JudgeProc.m_strxtlqdy);
        }
    }
    if(m_GfTestPauseFlag)
    {
        printf("####CheckProcOfSection3----m_GfTestPauseFlag=true\n");
//        g_Mutex.lock();
        //m_pGPIORecvThread->createStatusRecordFileByList(g_strlistGeneralProc);//del by 2020.09.05
        m_pGPIORecvThread->createStatusRecordFileByVector(g_vec_StatusRecord);//add by 2020.09.05
//        g_Mutex.unlock();
    }
#ifndef NEWCODE_SW
    if(m_struLeftFaultDATA[0].iDCundervoltFlag==1)
    {
           printf("####CheckProcOfSection3----m_struLeftFaultDATA[0].iDCundervoltFlag=1\n");
           m_pUi->label_procinfo->setText(m_JudgeProc.m_strModuleUnderVolt);//add by zqc 2019.07.15
           m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strModuleUnderVolt);//add by zqc 2019.07.15
           if(iLongrCtl)
           {
                PROTECTsendMesg(m_JudgeProc.m_strModuleUnderVolt);
           }
    }
#endif
    if((isXtlqExist)||(m_struLeftFaultDATA[0].iDCundervoltFlag==1)||(m_GfTestPauseFlag))
    {
         /*printf("####m_nSectionPos=%d####\n",m_nSectionPos);
         printf("isXtlqExist=%d-iDCundervoltFlag=%d\n",
                    isXtlqExist,
                    m_struLeftFaultDATA[0].iDCundervoltFlag);*/
         strtemp.sprintf("m_nSectionPos=%d-isXtlqExist=%d-iDCundervoltFlag=%d\n",
                    m_nSectionPos,
                    isXtlqExist,
                    m_struLeftFaultDATA[0].iDCundervoltFlag);
          m_pUi->DebugTextEdit->append(strtemp);
          m_pUi->DebugTextEdit->setStyleSheet("color:red;border:2px solid gray;");//设置为红色字体
          OperationSection34();
          initGfStartSet();
     }
#endif
}
//检测S4段的保护,add by 2019.05.24
void CMymainWindow::CheckProcOfSection4()
{
#ifdef UBUNTU_DEV //Compiler Switch
    bool isXtlqExist=false;
    bool isExcitExist=false;
    bool isVoltDown=false;
    int  iBusVoltDownCnt=0;
    QString strtemp;
     //--检测是否存在系统冷却单元(序号1)
#ifndef NEWCODE_SW
    isXtlqExist=CheckXtlqProcExist();
#endif
#ifdef NEWCODE_SW
    isXtlqExist = m_JudgeProc.newCheckXtlqProcExist(g_newchasetdata);
#endif
     if(isXtlqExist)
     {
         printf("####CheckProcOfSection4----isXtlqExist=true\n");
         m_pUi->label_procinfo->setText(m_strxtlqdy);//add by zqc 2019.07.15
         m_pGPIORecvThread->createStatusRecordFile(m_strxtlqdy);//add by zqc 2019.07.15
         m_pUi->DebugTextEdit->append(m_JudgeProc.m_strxtlqdy);//add by 2019.05.26
         if(iLongrCtl)
        {
            PROTECTsendMesg(m_JudgeProc.m_strxtlqdy);
         }
     }
     //--检测是否存在励磁开路(序号20)
#ifndef NEWCODE_SW
        isExcitExist=m_JudgeProc.CheckExcitProcExist(g_GPIOData);
#endif
#ifdef NEWCODE_SW
        isExcitExist=m_JudgeProc.newCheckExcitProcExist(g_newaddata);
#endif
     if(isExcitExist)
     {
          printf("####CheckProcOfSection4----isExcitExist=true\n");
          m_pUi->label_procinfo->setText(m_JudgeProc.m_strExcitopen);//add by zqc 2019.07.15
          m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strExcitopen);//add by zqc 2019.07.15
          m_pUi->DebugTextEdit->append(m_JudgeProc.m_strExcitopen);//add by 2019.05.26
          if(iLongrCtl)
         {
            PROTECTsendMesg(m_JudgeProc.m_strExcitopen);
          }
     }
      //--检测是否存在母线电压过低(序号25)
       g_Mutex.lock();
#ifndef NEWCODE_SW
      isVoltDown=m_JudgeProc.CheckBusVoltDownExist(g_GPIOData,iBusVoltDownCnt);
#endif
#ifdef NEWCODE_SW
      isVoltDown=m_JudgeProc.newCheckBusVoltDownExist(g_newaddata,iBusVoltDownCnt);
#endif
       g_Mutex.unlock();
      if(isVoltDown)
      {
           printf("####CheckProcOfSection4----isVoltDown=true\n");
           m_pUi->label_procinfo->setText(m_JudgeProc.m_strBusVoltDown);//add by zqc 2019.07.15
           m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strBusVoltDown);//add by zqc 2019.07.15
           m_pUi->DebugTextEdit->append(m_JudgeProc.m_strBusVoltDown);//add by 2019.05.26
           if(iLongrCtl)
           {
                PROTECTsendMesg(m_JudgeProc.m_strBusVoltDown);
           }
      }
      if(m_struLeftFaultDATA[0].iDCundervoltFlag==1)
      {
           printf("####CheckProcOfSection4----m_struLeftFaultDATA[0].iDCundervoltFlag=1\n");
           m_pUi->label_procinfo->setText(m_JudgeProc.m_strModuleUnderVolt);//add by zqc 2019.07.15
           m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strModuleUnderVolt);//add by zqc 2019.07.15
           if(iLongrCtl)
           {
                PROTECTsendMesg(m_JudgeProc.m_strModuleUnderVolt);
            }
      }//--检测是否存在模块直流欠压(序号29)
      if(m_GfTestPauseFlag)
      {
          printf("####CheckProcOfSection4----m_GfTestPauseFlag=true\n");
//          g_Mutex.lock();
          //m_pGPIORecvThread->createStatusRecordFileByList(g_strlistGeneralProc);//del by 2020.09.05
          m_pGPIORecvThread->createStatusRecordFileByVector(g_vec_StatusRecord);//add by 2020.09.05
//          g_Mutex.unlock();
      }
      if((isXtlqExist)||(isExcitExist)||(isVoltDown)||(m_struLeftFaultDATA[0].iDCundervoltFlag==1)||(m_GfTestPauseFlag))
        {
            printf("####m_nSectionPos=%d####\n",m_nSectionPos);
            printf("isXtlqExist=%d-isExcitExist=%d-isVoltDown=%d-iDCundervoltFlag=%d\n",
                    isXtlqExist,
                    isExcitExist,
                    isVoltDown,
                    m_struLeftFaultDATA[0].iDCundervoltFlag);
             strtemp.sprintf("m_nSectionPos=%d-isXtlqExist=%d-isExcitExist=%d-isVoltDown=%d-iDCundervoltFlag=%d\n",
                    m_nSectionPos,
                    isXtlqExist,
                    isExcitExist,
                    isVoltDown,
                    m_struLeftFaultDATA[0].iDCundervoltFlag);
              m_pUi->DebugTextEdit->append(strtemp);
              m_pUi->DebugTextEdit->setStyleSheet("color:red;border:2px solid gray;");//设置为红色字体
                OperationSection34();//执行S34操作，立即中断
                initGfStartSet();
       }
#endif       //Compiler Switch
}
//等待3秒-槽函数
void CMymainWindow::waiting3second()
{
#ifdef UBUNTU_DEV //Compiler Switch
    m_nSectionPos=PROCESS_SECTION_02;//S2段
    printf("####3 seconds have arrived####\n");
    if(m_pTimer3s->isActive())
    {
        m_pTimer3s->stop();//3s定时器处于"开"的状态，应及时停止
    }
    if(m_GfTestPauseFlag)
    {
//        g_Mutex.lock();
        //m_pGPIORecvThread->createStatusRecordFileByList(g_strlistGeneralProc);//del by 2020.09.05
        m_pGPIORecvThread->createStatusRecordFileByVector(g_vec_StatusRecord);//add by 2020.09.05
//        g_Mutex.unlock();
    }
    if(m_iMode==NORMAL_MODE)
    {
        //正常模式下
         QString strtemp;
         bool isExcitExist=false;
          g_Mutex.lock();
#ifndef NEWCODE_SW
         isExcitExist=m_JudgeProc.CheckExcitProcExist(g_GPIOData);
#endif
#ifdef NEWCODE_SW
         isExcitExist=m_JudgeProc.newCheckExcitProcExist(g_newaddata);
#endif
          g_Mutex.unlock();
         if(isExcitExist)
         {
           printf("####waiting3second isExcitExist = true####\n");
           //g_strlistGeneralProc.append(m_JudgeProc.m_strExcitopen);//add by 2019.05.26
           m_pUi->DebugTextEdit->append(m_JudgeProc.m_strExcitopen);
           m_pUi->label_procinfo->setText(m_JudgeProc.m_strExcitopen);//add by zqc 2019.07.15
           m_pGPIORecvThread->createStatusRecordFile(m_JudgeProc.m_strExcitopen);//add by zqc 2019.07.15
           if(iLongrCtl)
           {
                PROTECTsendMesg(m_JudgeProc.m_strExcitopen);
           }
         }
        if((m_GfTestPauseFlag)||(isExcitExist))
        {
            printf("####waiting3second m_GfTestPauseFlag or isExcitExist = true####\n");
            strtemp.sprintf("m_nSectionPos=%d-isExcitExist=%d\n",
                    m_nSectionPos,
                    isExcitExist);
               m_pUi->DebugTextEdit->append(strtemp);
               m_pUi->DebugTextEdit->setStyleSheet("color:red;border:2px solid gray;");//设置为红色字体
            OperationSection2();
            initGfStartSet();
        }
        else
        {//--不存在励磁开路保护
                CloseSubCabinetRelay();//分柜高压继电器吸合
                m_pTimer1s->start(1000);
        }
    }
    else if(m_iMode==DEBUG_MODE)
    {
        //调试模式下
        if(m_GfTestPauseFlag)
        {
            OperationSection2();
            initGfStartSet();
        }
        else
        {
             CloseSubCabinetRelay();//分柜高压继电器吸合
             m_pTimer1s->start(1000);
        }
    }
#endif  //Compiler Switch
}
//分柜高压继电器吸合,modified by zqc 2019.06.02@@@
void CMymainWindow::CloseSubCabinetRelay()
{
#ifndef NEWCODE_SW
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {
       m_pGPIORecvThread->m_Gpiorw.write_do(write_address_18,write_data_1,m_nGPIOfd); //打开分柜0主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 0 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 0 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
    {
       m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1C,write_data_1,m_nGPIOfd); //打开分柜1主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 1 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 1 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
    {
       m_pGPIORecvThread->m_Gpiorw.write_do(write_address_20,write_data_1,m_nGPIOfd); //打开分柜2主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 2 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 2 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
    {
       m_pGPIORecvThread->m_Gpiorw.write_do(write_address_24,write_data_1,m_nGPIOfd);//打开分柜3主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 3 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 3 main relay####\n");
       delay();
    }
#endif
#ifdef NEWCODE_SW
#ifdef UBUNTU_DEV
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {

       OpenOneOutIO(K1_1);//打开分柜0主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 0 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 0 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
    {
       OpenOneOutIO(K2_1); //打开分柜1主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 1 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 1 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
    {
       OpenOneOutIO(K3_1); //打开分柜2主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 2 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 2 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
    {
       OpenOneOutIO(K4_1);//打开分柜3主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 3 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 3 main relay####\n");
       delay();
    }
#endif
#endif
}
//重新对分柜高压继电器吸合,add by zqc 2019.06.02
void CMymainWindow::ReCloseSubCabinetRelay()
{
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {
       m_pGPIORecvThread->m_Gpiorw.write_do(write_address_18,write_data_1,m_nGPIOfd); //打开分柜0主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 0 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 0 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
    {
       m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1C,write_data_1,m_nGPIOfd); //打开分柜1主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 1 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 1 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
    {
       m_pGPIORecvThread->m_Gpiorw.write_do(write_address_20,write_data_1,m_nGPIOfd); //打开分柜2主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 2 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 2 main relay####\n");
       delay();
    }

    if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
    {
       m_pGPIORecvThread->m_Gpiorw.write_do(write_address_24,write_data_1,m_nGPIOfd);//打开分柜3主继电器
       printf("####CloseSubCabinetRelay()-Open sub-cabinet 3 main relay####\n");
       m_pUi->DebugTextEdit->append("####CloseSubCabinetRelay()-Open sub-cabinet 3 main relay####\n");
       delay();
    }
}
//等待60秒-槽函数
void CMymainWindow::waiting60second()
{
#ifdef UBUNTU_DEV //Compiler Switch
    printf("####60 seconds have arrived####\n");
    if(m_pTimer60s->isActive ())
    {
        m_pTimer60s->stop();//60s定时器处于"开"的状态，应及时停止
        printf("####m_pTimer60s->stop()####\n");
        m_Timer60StartFlag=false;
        m_iCountDownTime=60;
        m_CountDownWdgt.close();
     /*QMessageBox::information(this,
        tr(m_strInfo),
        tr(m_strResetTips));*/
    }
    //断开台体、功放冷却系统启动（指令或者继电器）
#ifndef NEWCODE_SW
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0C,write_data_0,m_nGPIOfd);
    g_GPIOData.iCoolingState=-1;//系统冷却单元灯灭，add by 2019.06.29
#endif
#ifdef NEWCODE_SW
    CloseOneOutIO(COOLING);//关闭冷却系统继电器
    g_newaddata.iCoolingState = LED_YELLOW;//系统冷却单元灯灭
#endif
    printf("####Disconnect the platform and start the power amplifier cooling system####\n");
#endif  //Compiler Switch
    if(m_GfStopFlag && !iLongrCtl)
    {
        m_pUi->toolButton_gfstop->setEnabled(true);//按钮使能状态
        m_pUi->toolButton_gfstart->setEnabled(true);//功放启动按钮重新开放,add by 2019.05.21
        m_GfStopFlag=false;
    }
}
//初始化保护类型(数据)@@@
void CMymainWindow::initProctype()
{
    //紧急停机
     m_strjjtj=QApplication::translate("mainWindow",
         "\347\264\247\346\200\245\345\201\234\346\234\272",
         0,
         QApplication::UnicodeUTF8);
    //滑台过位移
     m_strhtgwy=QApplication::translate("mainWindow",
         "\346\273\221\345\217\260\350\277\207\344\275\215\347\247\273",
         0,
         QApplication::UnicodeUTF8);
     //振动台过位移
     m_strzdtgwy= QApplication::translate("mainWindow",
         "\346\214\257\345\212\250\345\217\260\350\277\207\344\275\215\347\247\273",
         0,
         QApplication::UnicodeUTF8);
     //滑台低液位
     m_strhtdyw=QApplication::translate("mainWindow",
         "\346\273\221\345\217\260\344\275\216\346\266\262\344\275\215",
         0,
         QApplication::UnicodeUTF8);
     //振动台冷却
     m_strzdtlq= QApplication::translate("mainWindow",
         "\346\214\257\345\212\250\345\217\260\345\206\267\345\215\264",
         0,
         QApplication::UnicodeUTF8);
     //滑台轴承低压
     m_strhtqy=QApplication::translate("mainWindow",
         "\346\273\221\345\217\260\350\275\264\346\211\277\344\275\216\345\216\213",
         0,
         QApplication::UnicodeUTF8);
     //振动台过温
     m_strzdtgw=QApplication::translate("mainWindow",
         "\346\214\257\345\212\250\345\217\260\350\277\207\346\270\251",
         0,
         QApplication::UnicodeUTF8);
     //耳轴过位移
     m_strezgwy=QApplication::translate("mainWindow",
         "\350\200\263\350\275\264\350\277\207\344\275\215\347\247\273",
         0,
         QApplication::UnicodeUTF8);
     //功放热继保护
     m_strgfrjbh=QApplication::translate("mainWindow",
         "\345\212\237\346\224\276\347\203\255\347\273\247\344\277\235\346\212\244",
         0,
         QApplication::UnicodeUTF8);
     //静压轴承低压
     m_strjyzcdy=QApplication::translate("mainWindow",
         "\351\235\231\345\216\213\350\275\264\346\211\277\344\275\216\345\216\213",
         0,
         QApplication::UnicodeUTF8);
     //主柜门保护
     m_strmbh=QApplication::translate("mainWindow",
         "\344\270\273\346\237\234\351\227\250\344\277\235\346\212\244",
         0,
         QApplication::UnicodeUTF8);
     //系统冷却单元
     m_strxtlqdy=QApplication::translate("mainWindow",
         "\347\263\273\347\273\237\345\206\267\345\215\264\345\215\225\345\205\203",
         0,
         QApplication::UnicodeUTF8);
     //主柜整流桥过温
     m_strhtqyw=QApplication::translate("mainWindow",
         "\344\270\273\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251",
         0,
         QApplication::UnicodeUTF8);
}
//"功率模块启动"槽函数
void CMymainWindow::startupBtn_clicked()
{
#ifndef NEWCODE_SW
    m_CANDatarw.startPowerModule(m_CANfd);
#endif
#ifdef NEWCODE_SW
    OpenOneOutIO(RUN);//模块使能信号
#endif
    QString strStart =QApplication::translate("mainWindow",
        "\345\212\237\347\216\207\346\250\241\345\235\227\345\220\257\345\212\250\345\221\275\344\273\244\344\270\213\345\217\221\346\210\220\345\212\237",
        0,
        QApplication::UnicodeUTF8);//功率模块启动命令下发成功
    m_pUi->DebugTextEdit->append(strStart);
}
//"功率模块关机"槽函数
void CMymainWindow::shutdownBtn_clicked()
{
#ifndef NEWCODE_SW //new code running switch by zw 20220223
    m_CANDatarw.stopPowerModule(m_CANfd);
#endif
#ifdef NEWCODE_SW
    CloseOneOutIO(RUN);//模块使能信号
#endif
   QString strClose=QApplication::translate("mainWindow",
        "\345\212\237\347\216\207\346\250\241\345\235\227\345\205\263\346\234\272\345\221\275\344\273\244\344\270\213\345\217\221\346\210\220\345\212\237",
        0,
        QApplication::UnicodeUTF8);//功率模块关机命令下发成功
    m_pUi->DebugTextEdit->append(strClose);
}
//"紧急停机"槽函数@@@
void CMymainWindow::jjtjBtn_clicked()
{
    if(!m_EmergencyFlag)
    {
         m_pUi->jjtjBtn->setDown(true);
         m_pUi->jjtjBtn->setBackgroundColor(m_jjtjclickedColor);
         /*
         if(g_iLangChange==1)
        {
            m_pUi->label_connect->setText(m_strEstop);  //add by 2020.11.25
        }
        else
        {
            m_pUi->label_connect->setText("Emergency Stop");//addby 2020.11.25
        }
        */

         //T1:报警灯亮；蜂鸣器响；显示保护信息
#ifdef UBUNTU_DEV
#ifndef NEWCODE_SW
         g_GPIOData.iCoolingState=-1;//冷却系统灯灭
         m_pGPIORecvThread->m_Gpiorw.write_do(write_address_84,write_data_1,m_nGPIOfd);
#endif
#ifdef NEWCODE_SW
         g_newaddata.iCoolingState = LED_YELLOW;
#endif
         if(m_pTimer5s->isActive())
        {
            m_pTimer5s->stop();//5s定时器处于"开"的状态，应及时停止
        }
         if(m_pTimer3s->isActive())
        {
            m_pTimer3s->stop();//3s定时器处于"开"的状态，应及时停止
        }
         if(m_pTimer1s->isActive())
        {
            m_pTimer1s->stop();//1s定时器处于"开"的状态，应及时停止
        }
#endif
         DisAllRelays();//断开所有继电器
         zystopBtn_clicked();//软件关闭使能
         printf("####DisAllRelays####\n");
         initGfStartSet();
         m_EmergencyFlag=true;
    }
    else
    {
        m_pUi->jjtjBtn->setDown(false);
        m_pUi->jjtjBtn->setBackgroundColor(m_jjtjBgColor);
        gfresetBtn_clicked();
        m_EmergencyFlag=false;
        if(!iLongrCtl)
        {
            m_pUi->toolButton_gfstart->setEnabled(true);//功放启动按钮重新开放,add by 2019.05.21
        }
        m_GfTestPauseFlag=false;
        m_ExcitExistFlag=false;
    }
}
//断开所有继电器@@@
void CMymainWindow::DisAllRelays()
{
#ifndef NEWCODE_SW
      m_pUi->DebugTextEdit->append("####DisAllRelays####\n");
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0C,write_data_0,m_nGPIOfd); //断开冷却单元
      printf("####DisAllRelays()：Disconnect Cooling unit ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays()：Disconnect Cooling unit ####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0E,write_data_0,m_nGPIOfd);//断开励磁继电器
      printf("####DisAllRelays：Disconnect Excitation Relay####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays()：Disconnect Excitation Relay####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_16,write_data_0,m_nGPIOfd);//断开分柜0软启动
      printf("####DisAllRelays()：Disconnect sub-cabinet 0 soft start####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays：Disconnect sub-cabinet 0 soft start####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_18,write_data_0,m_nGPIOfd);//断开分柜0主继电器
      printf("####DisAllRelays()：Disconnect main relay of sub-cabinet 0 ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays()：Disconnect main relay of sub-cabinet 0 ####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1A,write_data_0,m_nGPIOfd);//断开分柜1软启动
      printf("####DisAllRelays()：Disconnect sub-cabinet 1 soft start####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays：Disconnect sub-cabinet 1 soft start####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1C,write_data_0,m_nGPIOfd);//断开分柜1主继电器
      printf("####DisAllRelays()：Disconnect main relay of sub-cabinet 1 ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays()：Disconnect main relay of sub-cabinet 1 ####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1E,write_data_0,m_nGPIOfd);//断开分柜2软启动
      printf("####DisAllRelays()：Disconnect sub-cabinet 2 soft start####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays()：Disconnect sub-cabinet 2 soft start####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_20,write_data_0,m_nGPIOfd);//断开分柜2主继电器
      printf("####DisAllRelays()：Disconnect main relay of sub-cabinet 2 ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays()：Disconnect main relay of sub-cabinet 2 ####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_22,write_data_0,m_nGPIOfd);//断开分柜3软启动
      printf("####DisAllRelays()：Disconnect sub-cabinet 3 soft start####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays()：Disconnect sub-cabinet 3 soft start####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_24,write_data_0,m_nGPIOfd);//断开分柜3主继电器
      printf("####DisAllRelays()：Disconnect main relay of sub-cabinet 3 ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelays()：Disconnect main relay of sub-cabinet 3 ####\n");
  #endif
#ifdef NEWCODE_SW
      CloseOneOutIO(COOLING);
      printf("####DisAllRelays()：Disconnect COOLING relay ####\n");
      delay();
      CloseOneOutIO(FIELD);
      printf("####DisAllRelays()：Disconnect FIELD relay ####\n");
      delay();
      CloseOneOutIO(FAN);
      printf("####DisAllRelays()：Disconnect FAN relay ####\n");
      delay();
      CloseOneOutIO(HB);
      printf("####DisAllRelays()：Disconnect HB relay ####\n");
      delay();
      CloseOneOutIO(K1_0);
      printf("####DisAllRelays()：Disconnect K1_0 relay ####\n");
      delay();
      CloseOneOutIO(K1_1);
      printf("####DisAllRelays()：Disconnect K1_1 relay ####\n");
      delay();
      CloseOneOutIO(K2_0);
      printf("####DisAllRelays()：Disconnect K2_0 relay ####\n");
      delay();
      CloseOneOutIO(K2_1);
      printf("####DisAllRelays()：Disconnect K2_1 relay ####\n");
      delay();
      CloseOneOutIO(K3_0);
      printf("####DisAllRelays()：Disconnect K3_0 relay ####\n");
      delay();
      CloseOneOutIO(K3_1);
      printf("####DisAllRelays()：Disconnect K3_1 relay ####\n");
      delay();
      CloseOneOutIO(K4_0);
      printf("####DisAllRelays()：Disconnect K4_0 relay ####\n");
      delay();
      CloseOneOutIO(K4_1);
      printf("####DisAllRelays()：Disconnect K4_1 relay ####\n");
      delay();
//      CloseOneOutIO(ST);
//      printf("####DisAllRelays()：Disconnect ST relay ####\n");
//      delay();
//      CloseOneOutIO(EXT21);
//      printf("####DisAllRelays()：Disconnect EXT21 relay ####\n");
//      delay();
      CloseOneOutIO(RUN);
      printf("####DisAllRelays()：Disconnect RUN relay ####\n");
#endif
}
//断开所有继电器(除了冷却系统)@@@
void CMymainWindow::DisAllRelaysExCoolSystem()
{
#ifndef NEWCODE_SW
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():DisAllRelaysExCoolSystem####\n");
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0E,write_data_0,m_nGPIOfd);//断开励磁继电器
      g_newaddata.iExcitationState = LED_YELLOW;
      printf("####DisAllRelaysExCoolSystem():Disconnect Excitation Relay####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect Excitation Relay####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_16,write_data_0,m_nGPIOfd);//断开分柜0软启动
      printf("####DisAllRelaysExCoolSystem():Disconnect sub-cabinet 0 soft start####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect sub-cabinet 0 soft start####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_18,write_data_0,m_nGPIOfd);//断开分柜0主继电器
      printf("####DisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 0 ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 0 ####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1A,write_data_0,m_nGPIOfd);//断开分柜1软启动
      printf("####DisAllRelaysExCoolSystem():Disconnect sub-cabinet 1 soft start####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect sub-cabinet 1 soft start####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1C,write_data_0,m_nGPIOfd);//断开分柜1主继电器
      printf("####DisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 1 ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 1 ####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1E,write_data_0,m_nGPIOfd);//断开分柜2软启动
      printf("####DisAllRelaysExCoolSystem():Disconnect sub-cabinet 2 soft start####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect sub-cabinet 2 soft start####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_20,write_data_0,m_nGPIOfd);//断开分柜2主继电器
      printf("####DisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 2 ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 2 ####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_22,write_data_0,m_nGPIOfd);//断开分柜3软启动
      printf("####DisAllRelaysExCoolSystem():Disconnect sub-cabinet 3 soft start####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect sub-cabinet 3 soft start####\n");
      delay();
      m_pGPIORecvThread->m_Gpiorw.write_do(write_address_24,write_data_0,m_nGPIOfd);//断开分柜3主继电器
      printf("####DisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 3 ####\n");
      m_pUi->DebugTextEdit->append("####DisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 3 ####\n");
      delay();
#endif
#ifdef NEWCODE_SW
      CloseOneOutIO(FIELD);
      printf("####DisAllRelays()：Disconnect FIELD relay ####\n");
      delay();
      CloseOneOutIO(FAN);
      printf("####DisAllRelays()：Disconnect FAN relay ####\n");
      delay();
      CloseOneOutIO(HB);
      printf("####DisAllRelays()：Disconnect HB relay ####\n");
      delay();
      CloseOneOutIO(K1_0);
      printf("####DisAllRelays()：Disconnect K1_0 relay ####\n");
      delay();
      CloseOneOutIO(K1_1);
      printf("####DisAllRelays()：Disconnect K1_1 relay ####\n");
      delay();
      CloseOneOutIO(K2_0);
      printf("####DisAllRelays()：Disconnect K2_0 relay ####\n");
      delay();
      CloseOneOutIO(K2_1);
      printf("####DisAllRelays()：Disconnect K2_1 relay ####\n");
      delay();
      CloseOneOutIO(K3_0);
      printf("####DisAllRelays()：Disconnect K3_0 relay ####\n");
      delay();
      CloseOneOutIO(K3_1);
      printf("####DisAllRelays()：Disconnect K3_1 relay ####\n");
      delay();
      CloseOneOutIO(K4_0);
      printf("####DisAllRelays()：Disconnect K4_0 relay ####\n");
      delay();
      CloseOneOutIO(K4_1);
      printf("####DisAllRelays()：Disconnect K4_1 relay ####\n");
      delay();
//      CloseOneOutIO(ST);
//      printf("####DisAllRelays()：Disconnect ST relay ####\n");
//      delay();
//      CloseOneOutIO(EXT21);
//      printf("####DisAllRelays()：Disconnect EXT21 relay ####\n");
//      delay();
      CloseOneOutIO(RUN);
      printf("####DisAllRelays()：Disconnect RUN relay ####\n");
#endif
}
//重新断开所有继电器，add by zqc 2019.06.02
void CMymainWindow::ReDisAllRelays()
{
     m_pUi->DebugTextEdit->append("####ReDisAllRelays####\n");
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0C,write_data_0,m_nGPIOfd); //断开冷却单元
     printf("####ReDisAllRelays():DisAllRelays()：Disconnect Cooling unit ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays()：Disconnect Cooling unit ####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0E,write_data_0,m_nGPIOfd);//断开励磁继电器
     printf("####ReDisAllRelays：Disconnect Excitation Relay####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays()：Disconnect Excitation Relay####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_16,write_data_0,m_nGPIOfd);//断开分柜0软启动
     printf("####ReDisAllRelays()：Disconnect sub-cabinet 0 soft start####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays：Disconnect sub-cabinet 0 soft start####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_18,write_data_0,m_nGPIOfd);//断开分柜0主继电器
     printf("####ReDisAllRelays()：Disconnect main relay of sub-cabinet 0 ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays()：Disconnect main relay of sub-cabinet 0 ####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1A,write_data_0,m_nGPIOfd);//断开分柜1软启动
     printf("####ReDisAllRelays()：Disconnect sub-cabinet 1 soft start####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays：Disconnect sub-cabinet 1 soft start####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1C,write_data_0,m_nGPIOfd);//断开分柜1主继电器
     printf("####ReDisAllRelays()：Disconnect main relay of sub-cabinet 1 ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays()：Disconnect main relay of sub-cabinet 1 ####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1E,write_data_0,m_nGPIOfd);//断开分柜2软启动
     printf("####ReDisAllRelays()：Disconnect sub-cabinet 2 soft start####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays()：Disconnect sub-cabinet 2 soft start####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_20,write_data_0,m_nGPIOfd);//断开分柜2主继电器
     printf("####ReDisAllRelays()：Disconnect main relay of sub-cabinet 2 ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays()：Disconnect main relay of sub-cabinet 2 ####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_22,write_data_0,m_nGPIOfd);//断开分柜3软启动
     printf("####ReDisAllRelays()：Disconnect sub-cabinet 3 soft start####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays()：Disconnect sub-cabinet 3 soft start####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_24,write_data_0,m_nGPIOfd);//断开分柜3主继电器
     printf("####ReDisAllRelays()：Disconnect main relay of sub-cabinet 3 ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelays()：Disconnect main relay of sub-cabinet 3 ####\n");
     delay();
}
//重新断开所有继电器(除了冷却系统),add by zqc 2019.06.02
void CMymainWindow::ReDisAllRelaysExCoolSystem()
{
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem####\n");
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_0E,write_data_0,m_nGPIOfd);//断开励磁继电器
     printf("####ReDisAllRelaysExCoolSystem():Disconnect Excitation Relay####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect Excitation Relay####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_16,write_data_0,m_nGPIOfd);//断开分柜0软启动
     printf("####ReDisAllRelaysExCoolSystem():Disconnect sub-cabinet 0 soft start####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect sub-cabinet 0 soft start####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_18,write_data_0,m_nGPIOfd);//断开分柜0主继电器
     printf("####ReDisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 0 ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 0 ####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1A,write_data_0,m_nGPIOfd);//断开分柜1软启动
     printf("####ReDisAllRelaysExCoolSystem():Disconnect sub-cabinet 1 soft start####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect sub-cabinet 1 soft start####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1C,write_data_0,m_nGPIOfd);//断开分柜1主继电器
     printf("####ReDisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 1 ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 1 ####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_1E,write_data_0,m_nGPIOfd);//断开分柜2软启动
     printf("####ReDisAllRelaysExCoolSystem():Disconnect sub-cabinet 2 soft start####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect sub-cabinet 2 soft start####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_20,write_data_0,m_nGPIOfd);//断开分柜2主继电器
     printf("####ReDisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 2 ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 2 ####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_22,write_data_0,m_nGPIOfd);//断开分柜3软启动
     printf("####ReDisAllRelaysExCoolSystem():Disconnect sub-cabinet 3 soft start####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect sub-cabinet 3 soft start####\n");
     delay();
     m_pGPIORecvThread->m_Gpiorw.write_do(write_address_24,write_data_0,m_nGPIOfd);//断开分柜3主继电器
     printf("####ReDisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 3 ####\n");
     m_pUi->DebugTextEdit->append("####ReDisAllRelaysExCoolSystem():Disconnect main relay of sub-cabinet 3 ####\n");
     delay();
}
//清除日志-槽函数,add by 2019.05.18@@@
void CMymainWindow::clearlogBtn_clicked()
{
     m_pUi->DebugTextEdit->clear();
}
//保存日志-槽函数,add by 2019.05.18
void CMymainWindow::savelogBtn_clicked()
{

}
//S1段执行操作(T1+T4)
void CMymainWindow::OperationSection1()
{
#ifdef UBUNTU_DEV
#ifndef NEWCODE_SW
    //T1:报警灯亮；蜂鸣器响；显示保护信息
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_84,write_data_1,m_nGPIOfd);
    g_GPIOData.iFaultState=0;//将故障状态灯设置为红色,add by 2019.06.17
#endif
#ifdef NEWCODE_SW
    g_newaddata.iFaultState = LED_RED;//点亮主界面故障灯
    //蜂鸣器响，待完善代码
    ioctl(fd_beep,1,0);
#endif
#endif
}
//S2段执行操作(T1+T2+T4)
void CMymainWindow::OperationSection2()
{
    //T1:报警灯亮；蜂鸣器响；显示保护信息
#ifndef NEWCODE_SW
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_84,write_data_1,m_nGPIOfd);
    #ifdef UBUNTU_DEV
    g_GPIOData.iFaultState=0;//将故障状态灯设置为红色,add by 2019.06.17
    g_GPIOData.iCoolingState=-1;//冷却系统灯灭，add by 2019.06.29
    #endif
#endif
#ifdef NEWCODE_SW//new code running switch by zw 20220223
    g_newaddata.iFaultState = LED_RED;//点亮主界面故障灯
    g_newaddata.iCoolingState = LED_YELLOW;//冷却系统灯灭
    //蜂鸣器响，待完善代码
    ioctl(fd_beep,1,0);

#endif
    //T2:断开所有继电器；软件关闭使能
    DisAllRelays();
    zystopBtn_clicked();
    //T4:等待按下“复位”;

}
//S3段执行操作(T1+T3+T4)
void CMymainWindow::OperationSection34()
{
#ifndef NEWCODE_SW
    //T1:报警灯亮；蜂鸣器响；显示保护信息
    m_pGPIORecvThread->m_Gpiorw.write_do(write_address_84,write_data_1,m_nGPIOfd);
    #ifdef UBUNTU_DEV
    g_GPIOData.iFaultState=0;//将故障状态灯设置为红色,add by 2019.06.17
    #endif
#endif
#ifdef NEWCODE_SW
    g_newaddata.iFaultState = LED_RED;//点亮主界面故障灯
    //蜂鸣器响，待完善代码
//    ioctl(fd_beep,1,0);
#endif
    //T3:断开其他继电器（除了冷却系统单元），等待60s,断开台体、功放冷却单元；软件关闭使能
    DisAllRelaysExCoolSystem();
    zystopBtn_clicked();
    //等待60秒
    //QMessageBox::warning(this, tr(m_strInfo), tr(m_strWait60s));//需要等待60秒钟，请稍候
    m_pTimer60s->start(60000);//启动60s定时器
    m_Timer60StartFlag=true;
    if(!m_CountDownWdgt.isVisible())
     {
        m_CountDownWdgt.exec();
     }
}
//获取模拟保护设置参数（正常测试时禁用）,add by 2019.05.23@@@
void CMymainWindow::GetSimuProcSet(STRU_SIMUPROCSET &stru_simuprocset)
{
    bool ok=false;
    stru_simuprocset.fSimuPhaseAVolt=m_pUi->lEdit_AVolt_Simu->text().toFloat(&ok);
    stru_simuprocset.fSimuPhaseBVolt=m_pUi->lEdit_BVolt_Simu->text().toFloat(&ok);
    stru_simuprocset.fSimuPhaseCVolt=m_pUi->lEdit_CVolt_Simu->text().toFloat(&ok);
    stru_simuprocset.fSimuBusVolt=m_pUi->lEdit_BusVolt_Simu->text().toFloat(&ok);
    stru_simuprocset.fSimuExcitCurrent=m_pUi->lEdit_ExcitCurrent_Simu->text().toFloat(&ok);
    stru_simuprocset.isSimuFlag=m_pUi->comboBox->currentIndex();
    printf("fSimuPhaseAVolt=%4.1f-fSimuPhaseBVolt=%4.1f-fSimuPhaseCVolt=%4.1f,fSimuBusVolt=%4.1f,fSimuExcitCurrent=%2.1f,isSimuFlag=%d\n",
        stru_simuprocset.fSimuPhaseAVolt,
        stru_simuprocset.fSimuPhaseBVolt,
        stru_simuprocset.fSimuPhaseCVolt,
        stru_simuprocset.fSimuBusVolt,
        stru_simuprocset.fSimuExcitCurrent,
        stru_simuprocset.isSimuFlag);
}
//更新模拟设置-槽函数，add by 2019.05.23
void CMymainWindow::updatesetBtn_clicked()
{
     GetSimuProcSet(g_SimuProcSet);
     QMessageBox::warning(this, tr(m_strInfo), tr("Simu Para has been Updated"));//提示模拟参数更新成功
}
//显示连锁设置状态,add by 2019.05.25
void CMymainWindow::ShowChainSetStatus()
{
    int nValue=-1;
#ifndef NEWCODE_SW
    //紧急停机屏蔽设置
    nValue=g_ChainSetData.iJjtjVal;//m_pChainsetdlg->m_iSwitchFlag[0];
    updateChainStatusButton(nValue,m_pUi->toolButton_jjtjchain);
    //滑台过位移屏蔽设置
    nValue=g_ChainSetData.iHtgwyVal;//m_pChainsetdlg->m_iSwitchFlag[1];
    updateChainStatusButton(nValue,m_pUi->toolButton_htgwychain);
    //振动台过位移屏蔽设置
    nValue=g_ChainSetData.iZdtgwyVal;//m_pChainsetdlg->m_iSwitchFlag[2];
    updateChainStatusButton(nValue,m_pUi->toolButton_zdtgwychain);
    //滑台低液位屏蔽设置
    nValue=g_ChainSetData.iHtdywVal;//m_pChainsetdlg->m_iSwitchFlag[3];
    updateChainStatusButton(nValue,m_pUi->toolButton_htdywchain);
    //自定义1屏蔽设置
    nValue=g_ChainSetData.iSelfdefineVal1;//m_pChainsetdlg->m_iSwitchFlag[4];
    updateChainStatusButton(nValue,m_pUi->toolButton_seldefine1chain);
    //滑台轴承低压屏蔽设置
    nValue=g_ChainSetData.iHtqyVal;//m_pChainsetdlg->m_iSwitchFlag[5];
    updateChainStatusButton(nValue,m_pUi->toolButton_htzcdychain);
    //振动台过温屏蔽设置
    nValue=g_ChainSetData.iZdtgwVal;//m_pChainsetdlg->m_iSwitchFlag[6];
    updateChainStatusButton(nValue,m_pUi->toolButton_zdtgwchain);
    //耳轴过位移屏蔽设置
    nValue=g_ChainSetData.iEzgwyVal;//m_pChainsetdlg->m_iSwitchFlag[7];
    updateChainStatusButton(nValue,m_pUi->toolButton_sjjtjchain);
    //功放热继保护屏蔽设置
    nValue=g_ChainSetData.iGfrjbhVal;//m_pChainsetdlg->m_iSwitchFlag[8];
    updateChainStatusButton(nValue,m_pUi->toolButton_gfrjbhchain);
    //静压轴承低压屏蔽设置
    nValue=g_ChainSetData.iJyzcdyVal;//m_pChainsetdlg->m_iSwitchFlag[9];
    updateChainStatusButton(nValue,m_pUi->toolButton_jyzcdychain);
    //主柜门保护屏蔽设置
    nValue=g_ChainSetData.iZgMenbVal;//m_pChainsetdlg->m_iSwitchFlag[10];
    updateChainStatusButton(nValue,m_pUi->toolButton_zgmbhchain);
    //系统冷却单元屏蔽设置
    nValue=g_ChainSetData.iXtlqdyVal;//m_pChainsetdlg->m_iSwitchFlag[11];
    updateChainStatusButton(nValue,m_pUi->toolButton_xtlqdychain);
    //主柜整流桥过温屏蔽设置
    nValue=g_ChainSetData.iHtqywVal;//m_pChainsetdlg->m_iSwitchFlag[12];
    updateChainStatusButton(nValue,m_pUi->toolButton_seldefine4chain);
    //自定义2屏蔽设置
    nValue=g_ChainSetData.iSelfdefineVal2;//m_pChainsetdlg->m_iSwitchFlag[13];
    updateChainStatusButton(nValue,m_pUi->toolButton_seldefine2chain);
    //自定义3屏蔽设置
    nValue=g_ChainSetData.iSelfdefineVal3;//m_pChainsetdlg->m_iSwitchFlag[14];
    updateChainStatusButton(nValue,m_pUi->toolButton_seldefine3chain);
#endif
#ifdef NEWCODE_SW  //new code running switch by zw 20220223
    //系统冷却单元
    nValue=g_newfaultstatus.iVIBCUFlag;
    updateDI(nValue,m_pUi->toolButton_xtlqdy);
    nValue=g_newchasetdata.iXtlqVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_xtlqdychain);
    //振动台过温
    nValue=g_newfaultstatus.iVIBOTFlag;
    updateDI(nValue,m_pUi->toolButton_zdtgw);
    nValue=g_newchasetdata.iZdtgwVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_zdtgwchain);
    //振动台过位移
    nValue=g_newfaultstatus.iVIBODFlag;
    updateDI(nValue,m_pUi->toolButton_zdtgwy);
    nValue=g_newchasetdata.iZdtgwyVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_zdtgwychain);
    //滑台低液位
    nValue=g_newfaultstatus.iSTOLFlag;
    updateDI(nValue,m_pUi->toolButton_htdyw);
    nValue=g_newchasetdata.iHtqywVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_htdywchain);
    //滑台欠压
    nValue=g_newfaultstatus.iSTUPFlag;
    updateDI(nValue,m_pUi->toolButton_htzcdy);
    nValue=g_newchasetdata.iHtqyVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_htzcdychain);
    //滑台过位移
    nValue=g_newfaultstatus.iSTODFlag;
    updateDI(nValue,m_pUi->toolButton_htgwy);
    nValue=g_newchasetdata.iHtgwyVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_htgwychain);
    //滑台过温
    nValue=g_newfaultstatus.iSTOTFlag;
    updateDI(nValue,m_pUi->toolButton_htgw);
    nValue=g_newchasetdata.iHtgwVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_htgwchain);
    //功放热继保护
    nValue=g_newfaultstatus.iRELAYFlag;
    updateDI(nValue,m_pUi->toolButton_gfrjbh);
    nValue=g_newchasetdata.iGfrjbhVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_gfrjbhchain);
    //静压轴承低压
    nValue=g_newfaultstatus.iHBUPFlag;
    updateDI(nValue,m_pUi->toolButton_jyzcdy);
    nValue=g_newchasetdata.iJyzcdyVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_jyzcdychain);
    //主柜门保护
    nValue=g_newfaultstatus.iDOORFlag;
    updateDI(nValue,m_pUi->toolButton_zgmbh);
    nValue=g_newchasetdata.iZgmbhVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_zgmbhchain);
    //紧急停机
    nValue=g_newfaultstatus.iESTOPFlag;
    updateDI(nValue,m_pUi->toolButton_jjtj);
    nValue=g_newchasetdata.iJjtjVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_jjtjchain);
    //S紧急停机
    nValue=g_newfaultstatus.iSESTOPFlag;
    updateDI(nValue,m_pUi->toolButton_sjjtj);
    nValue=g_newchasetdata.iSJitiVal;
    updateChainStatusButton(nValue,m_pUi->toolButton_sjjtjchain);
    //自定义1
    nValue=g_newfaultstatus.iEXT1Flag;
    updateDI(nValue,m_pUi->toolButton_seldefine1);
    nValue=g_newchasetdata.iSelfdefVal1;
    updateChainStatusButton(nValue,m_pUi->toolButton_seldefine1chain);
    //自定义2
    nValue=g_newfaultstatus.iEXT2Flag;
    updateDI(nValue,m_pUi->toolButton_seldefine2);
    nValue=g_newchasetdata.iSelfdefVal2;
    updateChainStatusButton(nValue,m_pUi->toolButton_seldefine2chain);
    //自定义3
    nValue=g_newfaultstatus.iEXT3Flag;
    updateDI(nValue,m_pUi->toolButton_seldefine3);
    nValue=g_newchasetdata.iSelfdefVal3;
    updateChainStatusButton(nValue,m_pUi->toolButton_seldefine3chain);
    //自定义4
    nValue=g_newfaultstatus.iEXT4Flag;
    updateDI(nValue,m_pUi->toolButton_seldefine4);
    nValue=g_newchasetdata.iSelfdefVal4;
    updateChainStatusButton(nValue,m_pUi->toolButton_seldefine4chain);
#endif
}
//刷新连锁设置状态,add by 2019.05.25
void  CMymainWindow::updateChainStatusButton(int nValue,QToolButton *toolButton)
{
    if(nValue==1)
    {
      toolButton->setIcon(m_ybonicon);
      toolButton->setIconSize(QSize(66, 48));
    }
    else
    {
      toolButton->setIcon(m_ybofficon);
      toolButton->setIconSize(QSize(66, 48));
    }
}
//打开基本参数对话框并设置参数,add by zqc 2019.06.01@@@
void CMymainWindow::basicparaBtn_clicked()
{
    m_BasicParaSetdlg.initPara();//恢复出厂设置时重新初始化，add by 2020.11.23
    m_pUi->basicparaBtn->setBackgroundColor(m_mouseclickColor);
    m_BasicParaSetdlg.exec();
    m_pUi->basicparaBtn->setBackgroundColor(m_defaultBgColor);
}
//初始化(置0)增益设置,add by zqc 2019.06.02@@@
void CMymainWindow::initGainSet()
{
    //延时时间到，再做1次操作
#ifndef NEWCODE_SW
   m_pGPIORecvThread->m_Gpiorw.write_do(write_address_5C,write_data_0+qPow(2,10),m_nGPIOfd);
#endif
#ifdef NEWCODE_SW
   zyStop_ad5292();
#endif
}
//间隔延时函数，10us，add by 2019.07.21
void CMymainWindow::delay()
{
   int i,j,k;
   for(i=1000;i>0;i--);
     //for(j=132;j>0;j--)
       //for(k=20;k>0;k--);
}
//状态记录界面页数设置槽函数@@@
void CMymainWindow::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    m_strErrinfo = QApplication::translate("basicparasetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示
    m_strInvalidinfo = QApplication::translate("basicparasetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入
    float iValue=0.0;
    bool ok=false;
    m_KeyBoardDlg.exec();//打开键盘对话框
    m_KeyBoardDlg.clearBtn_clicked();//清除旧的输入痕迹
    ok=m_KeyBoardDlg.getInputValue(iValue);
    if((ok)&&(iValue>=1 && iValue<=m_iTotalPage))
    {
        lineEdit->setText(QString::number(iValue));
        m_iCurrPage=iValue;
        showStatusRecordInfo(m_vec_statusData,m_iCurrPage);
    }
    else
    {
        QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//输入的数值不合法
    }
}
void CMymainWindow::lineEdit_clicked()                  //点击状态记录页码，弹出数字键盘
{
    m_KeyBoardDlg.disablePointAndNagBtn();
    openDigKeyBoardDlg(m_pUi->lineEdit_page);
}
//远程控制连接槽函数
void CMymainWindow::lrctlBtn_clicked()
{
    if(!iLongrCtl)
    {
        m_pUi->lrctlBtn->setDown(true);
        m_pUi->lrctlBtn->setBackgroundColor(m_mouseclickColor);
        slotStartServer();
        iLongrCtl=true;
        m_pUi->toolButton_gfreset->setEnabled(false);
        m_pUi->toolButton_gfstart->setEnabled(false);
        m_pUi->toolButton_gfstop->setEnabled(false);
        m_pUi->toolButton_zystart->setEnabled(false);
        m_pUi->adjBtn->setEnabled(false);
        m_pUi->chainBtn->setEnabled(false);
        m_pUi->basicparaBtn->setEnabled(false);
    }
    else
    {
        m_pUi->lrctlBtn->setDown(false);
        m_pUi->lrctlBtn->setBackgroundColor(m_defaultBgColor);
        disconnect(pTcpSocketServer,0,0,0);
        disconnect(m_pTcpServer,0,0,0);
        disconnect(pTcpSocketServerCANTEMP,0,0,0);
        disconnect(m_pTcpServerCANTEMP,0,0,0);
        disconnect(pTcpSocketServerCANRUN,0,0,0);
        disconnect(m_pTcpServerCANRUN,0,0,0);
        disconnect(pTcpSocketServerCANFAULT,0,0,0);
        disconnect(m_pTcpServerCANFAULT,0,0,0);
        disconnect(pTcpSocketServerPROTECT,0,0,0);
        disconnect(m_pTcpServerPROTECT,0,0,0);
        disconnect(pTcpSocketServerBasic,0,0,0);
        disconnect(m_pTcpServerBasic,0,0,0);
        disconnect(pTcpSocketServerChain,0,0,0);
        disconnect(m_pTcpServerChain,0,0,0);
        disconnect(pTcpSocketServerAdj,0,0,0);
        disconnect(m_pTcpServerAdj,0,0,0);

        iLongrCtl=false;
        m_pUi->toolButton_gfreset->setEnabled(true);//开启状态
        m_pUi->toolButton_gfstart->setEnabled(true);//功放启动按钮重新开放,add by 2019.05.21
        m_pUi->toolButton_gfstop->setEnabled(true);
        m_pUi->adjBtn->setEnabled(true);
        m_pUi->chainBtn->setEnabled(true);
        m_pUi->basicparaBtn->setEnabled(true);
        if(m_iMode==DEBUG_MODE)
        {
            m_pUi->toolButton_zystart->setEnabled(true);
        }
    }
}
//创建服务器
void CMymainWindow::slotStartServer()
{
    m_pTcpServer->listen(QHostAddress::Any,13003);
    connect(m_pTcpServer,SIGNAL(newConnection()),this,SLOT(slotNewConnect()));
    m_pTcpServerCANTEMP->listen(QHostAddress::Any,13000);
    connect(m_pTcpServerCANTEMP,SIGNAL(newConnection()),this,SLOT(slotCANTEMPConnect()));
    m_pTcpServerCANRUN->listen(QHostAddress::Any,13001);
    connect(m_pTcpServerCANRUN,SIGNAL(newConnection()),this,SLOT(slotCANRUNConnect()));
    m_pTcpServerCANFAULT->listen(QHostAddress::Any,13002);
    connect(m_pTcpServerCANFAULT,SIGNAL(newConnection()),this,SLOT(slotCANFAULTConnect()));
    m_pTcpServerPROTECT->listen(QHostAddress::Any,14000);
    connect(m_pTcpServerPROTECT,SIGNAL(newConnection()),this,SLOT(slotPROTECTConnect()));
    m_pTcpServerAdj->listen(QHostAddress::Any,14001);
    connect(m_pTcpServerAdj,SIGNAL(newConnection()),this,SLOT(slotAdjConnect()));
    m_pTcpServerBasic->listen(QHostAddress::Any,14002);
    connect(m_pTcpServerBasic,SIGNAL(newConnection()),this,SLOT(slotBasicConnect()));
    m_pTcpServerChain->listen(QHostAddress::Any,14003);
    connect(m_pTcpServerChain,SIGNAL(newConnection()),this,SLOT(slotChainConnect()));

}
//端口号为13003的服务器发送报文槽函数
void CMymainWindow::slotSendMesg()
{
    if(iLongrCtl)
    {
        QString strMesg=m_pUi->lineEdit_sendmsg->text();
        m_pUi->lineEdit_sendmsg->clear();
        QByteArray ba =strMesg.toLatin1();            //must
        char* ch = ba.data();
        int nlen=strlen(strMesg);
        pTcpSocketServerCANRUN->write(ch,nlen);
    }
}
//端口号为13003的服务器新连接
void CMymainWindow::slotNewConnect()
{
    pTcpSocketServer =  m_pTcpServer->nextPendingConnection();
    connect(pTcpSocketServer,SIGNAL(readyRead()),this,SLOT(slotReadMesg()));
}
void CMymainWindow::slotCANTEMPConnect()
{
    pTcpSocketServerCANTEMP =  m_pTcpServerCANTEMP->nextPendingConnection();
    connect(pTcpSocketServerCANTEMP,SIGNAL(readyRead()),this,SLOT(slotReadCANTEMPMesg()));
}
void CMymainWindow::slotCANRUNConnect()
{
    pTcpSocketServerCANRUN =  m_pTcpServerCANRUN->nextPendingConnection();
    connect(pTcpSocketServerCANRUN,SIGNAL(readyRead()),this,SLOT(slotReadCANRUNMesg()));
}
void CMymainWindow::slotCANFAULTConnect()
{
    pTcpSocketServerCANFAULT =  m_pTcpServerCANFAULT->nextPendingConnection();
    connect(pTcpSocketServerCANFAULT,SIGNAL(readyRead()),this,SLOT(slotReadCANFAULTMesg()));
}
void CMymainWindow::slotPROTECTConnect()
{
    pTcpSocketServerPROTECT =  m_pTcpServerPROTECT->nextPendingConnection();
    connect(pTcpSocketServerPROTECT,SIGNAL(readyRead()),this,SLOT(slotReadPROTECTMesg()));
}
void CMymainWindow::slotBasicConnect()
{
    pTcpSocketServerBasic =  m_pTcpServerBasic->nextPendingConnection();
    connect(pTcpSocketServerBasic,SIGNAL(readyRead()),this,SLOT(slotReadbasicMesg()));
}
void CMymainWindow::slotChainConnect()
{
    pTcpSocketServerChain =  m_pTcpServerChain->nextPendingConnection();
    connect(pTcpSocketServerChain,SIGNAL(readyRead()),this,SLOT(slotReadchainMesg()));
}
void CMymainWindow::slotAdjConnect()
{
    pTcpSocketServerAdj =  m_pTcpServerAdj->nextPendingConnection();
    connect(pTcpSocketServerAdj,SIGNAL(readyRead()),this,SLOT(slotReadadjMesg()));
}
//端口号13000的服务器收报文
void CMymainWindow::slotReadCANTEMPMesg()
{
    QByteArray qba= pTcpSocketServerCANTEMP->readAll(); //读取
    QString ss=QVariant(qba).toString();
    QHostAddress ip = pTcpSocketServerCANTEMP->peerAddress();
    QString qStrSendInfo = ip.toString()+" : "+ss;
    m_pUi->DebugTextEdit->append(qStrSendInfo);
}
//端口号13001的服务器收报文
void CMymainWindow::slotReadCANRUNMesg()
{
    QByteArray qba= pTcpSocketServerCANRUN->readAll(); //读取
    QString ss=QVariant(qba).toString();
    QHostAddress ip = pTcpSocketServerCANRUN->peerAddress();
    QString qStrSendInfo = ip.toString()+" : "+ss;
    m_pUi->DebugTextEdit->append(qStrSendInfo);
}
//端口号13002的服务器收报文
void CMymainWindow::slotReadCANFAULTMesg()
{
    QByteArray qba= pTcpSocketServerCANFAULT->readAll(); //读取
    QString ss=QVariant(qba).toString();
    QHostAddress ip = pTcpSocketServerCANFAULT->peerAddress();
    QString qStrSendInfo = ip.toString()+" : "+ss;
    m_pUi->DebugTextEdit->append(qStrSendInfo);
}
//端口号14000的服务器收报文
void CMymainWindow::slotReadPROTECTMesg()
{
    QByteArray qba= pTcpSocketServerPROTECT->readAll(); //读取
    QString ss=QVariant(qba).toString();
    PCCtlMesg(ss);
}
//端口号14001的服务器收报文
void CMymainWindow::slotReadadjMesg()
{
    QByteArray qba= pTcpSocketServerAdj->readAll(); //读取
    QString ss=QVariant(qba).toString();
    PCAdjMesg(ss);
    QHostAddress ip = pTcpSocketServerAdj->peerAddress();
    QString qStrSendInfo = ip.toString()+" : "+ss;
    m_pUi->DebugTextEdit->append(qStrSendInfo);
}
//端口号14002的服务器收报文
void CMymainWindow::slotReadbasicMesg()
{
    QByteArray qba= pTcpSocketServerBasic->readAll(); //读取
    QString ss=QVariant(qba).toString();
    PCBasicMesg(ss);
    QHostAddress ip = pTcpSocketServerBasic->peerAddress();
    QString qStrSendInfo = ip.toString()+" : "+ss;
    m_pUi->DebugTextEdit->append(qStrSendInfo);
}
//端口号14003的服务器收报文
void CMymainWindow::slotReadchainMesg()
{
    QByteArray qba= pTcpSocketServerChain->readAll(); //读取
    QString ss=QVariant(qba).toString();
    PCChainMesg(ss);
    QHostAddress ip = pTcpSocketServerChain->peerAddress();
    QString qStrSendInfo = ip.toString()+" : "+ss;
    m_pUi->DebugTextEdit->append(qStrSendInfo);
}

//端口号为13003的服务器收报文
void CMymainWindow::slotReadMesg()
{
    QByteArray qba= pTcpSocketServer->readAll(); //读取
    QString ss=QVariant(qba).toString();

    /*QHostAddress ip = pTcpSocketServer->peerAddress();
    QString qStrSendInfo = ip.toString()+" : "+ss;
    m_pUi->DebugTextEdit->append(qStrSendInfo);*/
}
//PC端连锁设置信息解析@@@
void CMymainWindow::PCChainMesg(QString strMesg)
{
    int nPos=4;
    bool ok=false;
    ulong ltemp=0;
    QString strTemp;
    if(strMesg.startsWith("bb11"))
    {
        //报文长度字符
        QString strLen=strMesg.mid(nPos,sizeof(int16)*2);
        int iLen=strLen.toInt(&ok,16);
        nPos+=sizeof(int16)*2;
        //模式选择
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_iMode=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        /*if(m_iMode==DEBUG_MODE)
        {
            m_pUi->toolButton_zystart->setEnabled(true);
        }
        else if(m_iMode==NORMAL_MODE)
        {
            m_pUi->toolButton_zystart->setEnabled(false);
        }*/
        //滑台过位移
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iHtgwyVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //振动台过位移
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iZdtgwyVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //滑台低液位
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iHtdywVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //滑台轴承低压
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iHtqyVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //振动台过温
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iZdtgwVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //耳轴过位移
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iEzgwyVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //功放热继保护
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iGfrjbhVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //静压轴承低压
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iJyzcdyVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //主柜门保护
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iZgMenbVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //从柜门保护
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iSubMenbVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //系统冷却单元
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iXtlqdyVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //主柜整流桥过温
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iHtqywVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //从柜整流桥过温
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iSubzlqgwVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //自定义1
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iSelfdefineVal1=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //自定义2
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iSelfdefineVal2=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //自定义3
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iSelfdefineVal3=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //从柜预留保护
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_ChainSetData.iSubyuliuPorcVal=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        memcpy(&g_ChainSetData,&m_ChainSetData,sizeof(m_ChainSetData));
    }
}
//PC端校准系数信息解析@@@
void CMymainWindow::PCAdjMesg(QString strMesg)
{
    int nPos=4;
    bool ok=false;
    int16 stemp=0;
    long ltemp=0;
    QString strTemp;
    if(strMesg.startsWith("bb09"))
    {
        //报文长度字符
        QString strLen=strMesg.mid(nPos,sizeof(int16)*2);
        int iLen=strLen.toInt(&ok,16);
        nPos+=sizeof(int16)*2;
        //从柜1母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1voltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
            /*m_pUi->DebugTextEdit->append(strTemp);
            QString strS1voltK;
            strS1voltK.sprintf("ltemp=%ld-----m_struAdjcoef.fSub1voltK=%3.2f",ltemp,m_struAdjcoef.fSub1voltK);
            m_pUi->DebugTextEdit->append(strS1voltK);*/

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1voltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
            /*m_pUi->DebugTextEdit->append(strTemp);
            QString strS1voltB;
            strS1voltB.sprintf("ltemp=%ld-----m_struAdjcoef.fSub1voltB=%3.2f",ltemp,m_struAdjcoef.fSub1voltB);
            m_pUi->DebugTextEdit->append(strS1voltB);*/
        }
        else
        {
            nPos+=18;
        }
        //从柜1正母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1ActvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1ActvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜1负母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1negvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1negvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜1输出电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1outvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1outvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜1输出电流
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1outcurrK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub1outcurrB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜2母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2voltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2voltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜2正母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2ActvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2ActvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜2负母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2negvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2negvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜2输出电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2outvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2outvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜2输出电流
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2outcurrK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub2outcurrB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜3母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3voltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3voltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜3正母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3ActvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3ActvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜3负母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3negvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3negvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜3输出电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3outvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3outvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜3输出电流
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3outcurrK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub3outcurrB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜4母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4voltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4voltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜4正母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4ActvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4ActvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜4负母线电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4negvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4negvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜4输出电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4outvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4outvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //从柜4输出电流
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4outcurrK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fSub4outcurrB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //A相电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMAvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
            /*m_pUi->DebugTextEdit->append(strTemp);
            QString strMAvoltK;
            strMAvoltK.sprintf("ltemp=%ld-----m_struAdjcoef.fMAvoltK=%3.2f",ltemp,m_struAdjcoef.fMAvoltK);
            m_pUi->DebugTextEdit->append(strMAvoltK);*/

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMAvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
            /*m_pUi->DebugTextEdit->append(strTemp);
            QString strMAvoltB;
            strMAvoltB.sprintf("ltemp=%ld-----m_struAdjcoef.fMAvoltB=%3.2f",ltemp,m_struAdjcoef.fMAvoltB);
            m_pUi->DebugTextEdit->append(strMAvoltB);*/
        }
        else
        {
            nPos+=18;
        }
        //B相电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMBvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMBvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //C相电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMCvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMCvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //励磁电压
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMEvoltK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMEvoltB,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        //励磁电流
        strTemp=strMesg.mid(nPos,sizeof(int8)*2);
        stemp=strTemp.toShort(&ok,16);
        if(stemp==1)
        {
            nPos+=sizeof(int8)*2;
            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMEcurrK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;

            strTemp=strMesg.mid(nPos,sizeof(float)*2);
            ltemp=strTemp.toULong(&ok,16);
            memcpy(&m_struAdjcoef.fMEcurrK,&ltemp,sizeof(float));
            nPos+=sizeof(float)*2;
        }
        else
        {
            nPos+=18;
        }
        m_Inifile.writeAdjcoefInifile(m_struAdjcoef);
        memcpy(&g_struAdjcoef,&m_struAdjcoef,sizeof(m_struAdjcoef));
        m_Inifile.writeneweAdjcoefInifile(m_newAdjcoef);
        memcpy(&g_newAdjcoef,&m_newAdjcoef,sizeof(m_newAdjcoef));
    }
}
//PC端基本参数信息解析@@@
void CMymainWindow::PCBasicMesg(QString strMesg)
{
    int nPos=4;
    bool ok=false;
    long ltemp=0;
    QString strTemp;
    if(strMesg.startsWith("bb10"))
    {
        //报文长度字符
        QString strLen=strMesg.mid(nPos,sizeof(int16)*2);
        int iLen=strLen.toInt(&ok,16);
        nPos+=sizeof(int16)*2;
        //母线电压上限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fBusvoltUp,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;

        /*m_pUi->DebugTextEdit->append(strTemp);
        QString strBusVoltage;
        strBusVoltage.sprintf("ltemp=%ld-----m_struBasicpara.fBusvoltUp=%3.1f",ltemp,m_struBasicpara.fBusvoltUp);
        m_pUi->DebugTextEdit->append(strBusVoltage);*/
        //母线电压下限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fBusvoltLow,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;

        /*m_pUi->DebugTextEdit->append(strTemp);
        QString strBusLowVoltage;
        strBusLowVoltage.sprintf("ltemp=%ld-----m_struBasicpara.fBusvoltLow=%3.1f",ltemp,m_struBasicpara.fBusvoltLow);
        m_pUi->DebugTextEdit->append(strBusLowVoltage);*/
        //三相电压上限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fThreevoltUp,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //三相电压下限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fThreevoltLow,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //母线电压不均衡度
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fBusImbalance,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //三相电压不均衡度
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fVoltimbalance,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //分柜1输出电流上限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fSub1CabinetcurrentUp,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //分柜2输出电流上限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fSub2CabinetcurrentUp,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //分柜3输出电流上限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fSub3CabinetcurrentUp,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //分柜4输出电流上限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fSub4CabinetcurrentUp,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //功放总输出电压上限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fTotalvoltUp,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //功放总输出电流上限
        strTemp=strMesg.mid(nPos,sizeof(float)*2);
        ltemp=strTemp.toULong(&ok,16);
        memcpy(&m_struBasicpara.fTotalcurrentUp,&ltemp,sizeof(float));
        nPos+=sizeof(float)*2;
        //分柜1接入标志
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_struBasicpara.iSub1CabOpen=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //分柜2接入标志
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_struBasicpara.iSub2CabOpen=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //分柜3接入标志
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_struBasicpara.iSub3CabOpen=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        //分柜4接入标志
        strTemp=strMesg.mid(nPos,sizeof(int32)*2);
        m_struBasicpara.iSub4CabOpen=strTemp.toULong (&ok,16);
        nPos+=sizeof(int32)*2;
        m_Inifile.writeBasicParaInifile(m_struBasicpara);
        memcpy(&g_struBasicPara,&m_struBasicpara,sizeof(m_struBasicpara));
    }
}
//PC端下发控制信号解析@@@
void CMymainWindow::PCCtlMesg(QString strMesg)
{
    int nPos=4;
    bool ok=false;
    int nvalue=0;
    int8 itemp=0;
    int clen=strlen(strMesg);
    QByteArray ba=strMesg.toLatin1();
    //报文长度字符
    QString strLen=strMesg.mid(nPos,sizeof(int16)*2);
    int iLen=strLen.toInt(&ok,16);
    nPos+=sizeof(int16)*2;
    if(strMesg.startsWith("bb05"))
    {//解析功放控制（功放启动，停止）报文
        QString strGFctl=strMesg.mid(nPos,sizeof(int8)*2);
        itemp=strGFctl.toInt(&ok,16);
        nPos+=sizeof(int8)*2;
        if(itemp==1)
        {
            gfstartBtn_clicked();
        }
        else if(itemp==0)
        {
            gfstopBtn_clicked();
        }
    }
    if(strMesg.startsWith("bb06"))
    {//解析紧急停机与复位报文
        QString strJtFwctl=strMesg.mid(nPos,sizeof(int8)*2);
        itemp=strJtFwctl.toInt(&ok,16);
        nPos+=sizeof(int8)*2;
        if(itemp==1)
        {
            jjtjBtn_clicked();
        }
        else if(itemp==0)
        {
            gfresetBtn_clicked();
        }
    }
    if(strMesg.startsWith("bb07"))
    {//解析增益控制报文
        QString strZyctl=strMesg.mid(nPos,sizeof(int8)*2);
        itemp=strZyctl.toInt(&ok,16);
        nPos+=sizeof(int8)*2;
        if(itemp==1||itemp==0)
        {
            zystartBtn_clicked();
        }
    }
    if(strMesg.startsWith("bb08"))
    {//解析谱型增益设置报文
        int ntimes=clen/16;
        //int remained=clen%16;
        for(int i=0;i<ntimes;i++)
        {//防止增益滑动过快产生重叠帧
            QString strZyset=strMesg.mid(nPos,sizeof(int32)*2);
            nvalue=strZyset.toInt(&ok,16);
            nPos+=sizeof(int32)*2+8;
            if(nvalue>=0 && nvalue<=100)
            {
                m_pUi->horizontalScrollBar->setValue(nvalue);
            }
        }
    }

}

//GPIO实时数据转发至PC端,add by 2019.08.24
void CMymainWindow::GPIOsendMesg()
{
#ifdef UBUNTU_DEV
    int8 itemp=0;
    int16 stemp=0;
    int32 ltemp=0;
    short int nlen=sizeof(g_GPIOData)+sizeof(short int)+sizeof(short int);
    //printf("nlen=%d\n",nlen);
    if(nlen<=300)
    {
        char buffer[280];
        memset(buffer,0,sizeof(buffer));
        char *pbuf=buffer;
        //报文标识符
        short int rptID=htons(0xaa05);
        memcpy(pbuf,&rptID,sizeof(rptID));
        pbuf+=sizeof(rptID);
        stemp=htons(nlen);
        memcpy(pbuf,&stemp,sizeof(stemp));
        pbuf+=sizeof(stemp);
        //数据块--主柜状态量
        for(int i=0;i<16;i++)
        {
            itemp=g_GPIOData.iMasterDI[i];
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
        }
        //数据块--从柜状态量
        for(int i=0;i<16;i++)
        {
            itemp=g_GPIOData.iSlaveDI[i];
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
        }
        //运行状态量
        itemp=g_GPIOData.iRunningState;
        memcpy(pbuf,&itemp,sizeof(itemp));
        pbuf+=sizeof(itemp);
        //冷却状态量
        itemp=g_GPIOData.iCoolingState;
        memcpy(pbuf,&itemp,sizeof(itemp));
        pbuf+=sizeof(itemp);
        //励磁状态量
        itemp=g_GPIOData.iExcitationState;
        memcpy(pbuf,&itemp,sizeof(itemp));
        pbuf+=sizeof(itemp);
        //准备状态量
        itemp=g_GPIOData.iReadyState;
        memcpy(pbuf,&itemp,sizeof(itemp));
        pbuf+=sizeof(itemp);
        //增益状态量
        itemp=g_GPIOData.iGainState;
        memcpy(pbuf,&itemp,sizeof(itemp));
        pbuf+=sizeof(itemp);
        //故障状态量
        itemp=g_GPIOData.iFaultState;
        memcpy(pbuf,&itemp,sizeof(itemp));
        pbuf+=sizeof(itemp);
        //总输出电压
        memcpy(&ltemp,&g_GPIOData.fTotalVolt,sizeof(float));
        ltemp=htonl(ltemp);
        memcpy(pbuf,&ltemp,sizeof(ltemp));
        pbuf+=sizeof(ltemp);
        //总输出电流
        memcpy(&ltemp,&g_GPIOData.fTotalCurrent,sizeof(float));
        ltemp=htonl(ltemp);
        memcpy(pbuf,&ltemp,sizeof(ltemp));
        pbuf+=sizeof(ltemp);
        //励磁电压
        memcpy(&ltemp,&g_GPIOData.fExcitVolt,sizeof(float));
        ltemp=htonl(ltemp);
        memcpy(pbuf,&ltemp,sizeof(ltemp));
        pbuf+=sizeof(ltemp);
        //励磁电流
        memcpy(&ltemp,&g_GPIOData.fExcitCurrent,sizeof(float));
        ltemp=htonl(ltemp);
        memcpy(pbuf,&ltemp,sizeof(ltemp));
        pbuf+=sizeof(ltemp);
        //A相电压
        memcpy(&ltemp,&g_GPIOData.fPhaseAVolt,sizeof(float));
        ltemp=htonl(ltemp);
        memcpy(pbuf,&ltemp,sizeof(ltemp));
        pbuf+=sizeof(ltemp);
        //B相电压
        memcpy(&ltemp,&g_GPIOData.fPhaseBVolt,sizeof(float));
        ltemp=htonl(ltemp);
        memcpy(pbuf,&ltemp,sizeof(ltemp));
        pbuf+=sizeof(ltemp);
        //C相电压
        memcpy(&ltemp,&g_GPIOData.fPhaseCVolt,sizeof(float));
        ltemp=htonl(ltemp);
        memcpy(pbuf,&ltemp,sizeof(ltemp));
        pbuf+=sizeof(ltemp);
        //从柜电压
        for(int i=0;i<4;i++)
        {
            memcpy(&ltemp,&g_GPIOData.fSlaveVolt[i],sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
        }
        //从柜电流
        for(int i=0;i<4;i++)
        {
            memcpy(&ltemp,&g_GPIOData.fSlaveCurrent[i],sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
        }
        //从柜母线电压
        for(int i=0;i<4;i++)
        {
            memcpy(&ltemp,&g_GPIOData.fSlaveBusVolt[i],sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
        }
        //从柜正母线电压
        for(int i=0;i<4;i++)
        {
            memcpy(&ltemp,&g_GPIOData.fSlaveActBusVolt[i],sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
        }
        //从柜负母线电压
        for(int i=0;i<4;i++)
        {
            memcpy(&ltemp,&g_GPIOData.fSlaveNegBusVolt[i],sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
        }
        //从柜运行状态值
        for(int i=0;i<4;i++)
        {
            itemp=g_GPIOData.iSlaveStaValue[i];
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
        }
        //printf("buffer[0]=%02x--buffer[1]=%02x\n",buffer[0],buffer[1]);
        QString strMesg;
        for(int i=0;i<nlen;i++)
        {
            strMesg.append(QString().sprintf("%02x",buffer[i]));
        }
        QByteArray ba =strMesg.toLatin1();
        char* ch = ba.data();
        nlen=strlen(strMesg);
        pTcpSocketServer->write(ch,nlen);
        //printf("strMesg=%s--nlen=%d\n",strMesg.toStdString().data(),nlen);
    }
#endif
}
//CAN温度报文发送@@@
void CMymainWindow::CANTEMPsendMesg()
{
#ifdef UBUNTU_DEV
    int8 itemp=0;
    int16 stemp=0;
    int32 ltemp=0;
    int16 nlen=sizeof(int16)+sizeof(int16)+sizeof(float)*7*16;
    if(nlen<=500)
    {
        unsigned char buffer[500];
        memset(buffer,0,sizeof(buffer));
        unsigned char *pbuf=buffer;
        //报文标识符
        int16 rptID=htons(0xaa06);
        //printf("rptID=%04x",rptID);
        memcpy(pbuf,&rptID,sizeof(rptID));
        pbuf+=sizeof(rptID);
        stemp=htons(nlen);
        memcpy(pbuf,&stemp,sizeof(stemp));
        pbuf+=sizeof(stemp);
        for(int i=0;i<16;i++)
        {
            memcpy(&ltemp,&m_struIGBTTempctlDATA[i].fIGBT1Temper,sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
            memcpy(&ltemp,&m_struIGBTTempctlDATA[i].fIGBT2Temper,sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
            memcpy(&ltemp,&m_struIGBTTempctlDATA[i].fOUTPUTACCurrent,sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
            memcpy(&ltemp,&m_struIDUCTTempctlDATA[i].fIDUCT1Temper,sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
            memcpy(&ltemp,&m_struIDUCTTempctlDATA[i].fIDUCT2Temper,sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
            memcpy(&ltemp,&m_struIDUCTTempctlDATA[i].fOUTPUTACVoltage,sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
            memcpy(&ltemp,&m_struDCINPUTVoltagectlDATA[i].fINPUTDCVoltage,sizeof(float));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
        }
        QString strMesg;
        for(int i=0;i<nlen;i++)
        {
            strMesg.append(QString().sprintf("%02x",buffer[i]));
        }
        QByteArray ba =strMesg.toLatin1();
        char* ch = ba.data();
        nlen=strlen(strMesg);
        pTcpSocketServerCANTEMP->write(ch,nlen);
        //printf("strMesg=%s--nlen=%d\n",strMesg.toStdString().data(),nlen);
    }
#endif
}
//发送CAN运行状态报文
void CMymainWindow::CANRUNsendMesg()
{
#ifdef UBUNTU_DEV
    int8 itemp=0;
    int16 stemp=0;
    int32 ltemp=0;
    int16 nlen=sizeof(int16)+sizeof(int16)+sizeof(int)*16+sizeof(int8)*7*16;
    if(nlen<=200)
    {
        unsigned char buffer[200];
        memset(buffer,0,sizeof(buffer));
        unsigned char *pbuf=buffer;
        //报文标识符
        int16 rptID=htons(0xaa07);
        //printf("rptID=%04x",rptID);
        memcpy(pbuf,&rptID,sizeof(rptID));
        pbuf+=sizeof(rptID);
        stemp=htons(nlen);
        memcpy(pbuf,&stemp,sizeof(stemp));
        pbuf+=sizeof(stemp);
        for(int i=0;i<16;i++)
        {
            itemp=m_struRunningDATA[i].iRestartprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRunningDATA[i].iNormaloperFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRunningDATA[i].iFaultProtFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRunningDATA[i].iFaultlockFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            memcpy(&ltemp,&m_struRunningDATA[i].iProtectedTimes,sizeof(int));
            ltemp=htonl(ltemp);
            memcpy(pbuf,&ltemp,sizeof(ltemp));
            pbuf+=sizeof(ltemp);
            itemp=m_struRunningDATA[i].iBlockpulseFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRunningDATA[i].iRecstartsigFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRunningDATA[i].iRecshutsigFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
        }
        QString strMesg;
        for(int i=0;i<nlen;i++)
        {
            strMesg.append(QString().sprintf("%02x",buffer[i]));
        }
        QByteArray ba =strMesg.toLatin1();
        char* ch = ba.data();
        nlen=strlen(strMesg);
        pTcpSocketServerCANRUN->write(ch,nlen);
        //printf("strMesg=%s--nlen=%d\n",strMesg.toStdString().data(),nlen);
    }
#endif
}
//@@@
void CMymainWindow::CANFAULTsendMesg()
{
#ifdef UBUNTU_DEV
    int8 itemp=0;
    int16 stemp=0;
    int32 ltemp=0;
    int16 nlen=sizeof(int16)+sizeof(int16)+sizeof(int8)*22*16;
    if(nlen<=400)
    {
        unsigned char buffer[400];
        memset(buffer,0,sizeof(buffer));
        unsigned char *pbuf=buffer;
        //报文标识符
        int16 rptID=htons(0xaa08);
        //printf("rptID=%04x",rptID);
        memcpy(pbuf,&rptID,sizeof(rptID));
        pbuf+=sizeof(rptID);
        stemp=htons(nlen);
        memcpy(pbuf,&stemp,sizeof(stemp));
        pbuf+=sizeof(stemp);
        for(int i=0;i<8;i++)
        {
            itemp=m_struLeftFaultDATA[i].iOutovervoltFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iDCovervoltFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iDCundervoltFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iACcurrentwarnFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iACcurrentprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIGBT1overtempFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIGBT2overtempFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIndu1overtempFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIndu2overtempFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iDripulseblockFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iDigspecinterFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iAnaspecampoverFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iAnaspecfreqoverFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iDigspecampoverFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iDigspecfreqoverFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIGBT1driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIGBT2driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIGBT3driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIGBT4driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIGBT5driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iIGBT6driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struLeftFaultDATA[i].iOutputvoltwarnFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iOutovervoltFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iDCovervoltFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iDCundervoltFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iACcurrentwarnFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iACcurrentprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIGBT1overtempFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIGBT2overtempFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIndu1overtempFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIndu2overtempFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iDripulseblockFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iDigspecinterFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iAnaspecampoverFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iAnaspecfreqoverFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iDigspecampoverFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iDigspecfreqoverFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIGBT1driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIGBT2driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIGBT3driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIGBT4driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIGBT5driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iIGBT6driprocFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
            itemp=m_struRightFaultDATA[i].iOutputvoltwarnFlag;
            memcpy(pbuf,&itemp,sizeof(itemp));
            pbuf+=sizeof(itemp);
        }
        QString strMesg;
        for(int i=0;i<nlen;i++)
        {
            strMesg.append(QString().sprintf("%02x",buffer[i]));
        }
        QByteArray ba =strMesg.toLatin1();
        char* ch = ba.data();
        nlen=strlen(strMesg);
        pTcpSocketServerCANFAULT->write(ch,nlen);
        //printf("strMesg=%s--nlen=%d\n",strMesg.toStdString().data(),nlen);
    }
#endif
}
//发送保护类型@@@
void CMymainWindow::PROTECTsendMesg(QString strPROTECTMesg)
{
#ifdef UBUNTU_DEV
    int8 itemp=0;
    int16 stemp=0;
    int32 ltemp=0;
    int16 nlen=sizeof(int16)+sizeof(int16)+sizeof(int8);
    if(nlen<=50)
    {
        unsigned char buffer[50];
        memset(buffer,0,sizeof(buffer));
        unsigned char *pbuf=buffer;
        //报文标识符
        int16 rptID=htons(0xaa09);
        //printf("rptID=%04x",rptID);
        memcpy(pbuf,&rptID,sizeof(rptID));
        pbuf+=sizeof(rptID);

        stemp=htons(nlen);
        memcpy(pbuf,&stemp,sizeof(stemp));
        pbuf+=sizeof(stemp);

        if((m_nSectionPos==PROCESS_SECTION_03)||(m_nSectionPos==PROCESS_SECTION_04))
        {
            itemp=1;
        }
        else
        {
            itemp=0;
        }
        memcpy(pbuf,&itemp,sizeof(itemp));
        pbuf+=sizeof(itemp);

        QString strMesg;
        for(int i=0;i<nlen;i++)
        {
            strMesg.append(QString().sprintf("%02x",buffer[i]));
        }
        strMesg.append(strPROTECTMesg);
        QByteArray ba =strMesg.toUtf8();
        char* ch = ba.data();
        nlen=strlen(strMesg);
        pTcpSocketServerPROTECT->write(ch,nlen);
        printf("strMesg=%s--nlen=%d\n",strMesg.toStdString().data(),nlen);
    }
#endif
}
//CAN发送从柜平均电流函数
void CMymainWindow::SentSubAvgCurr()
{
    int iAvgCurrent=0;
    int cnt=0;
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {
        cnt++;
    }
    if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
    {
        cnt++;
    }
    if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
    {
        cnt++;
    }
    if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
    {
        cnt++;
    }
#ifdef UBUNTU_DEV
    float fAvgCurrent=g_GPIOData.fTotalCurrent/cnt;
    fAvgCurrent=fAvgCurrent*RATIO;
    iAvgCurrent=(int) fAvgCurrent;
    m_CANDatarw.sendSubTotalcurrData(m_CANfd,iAvgCurrent>>8,iAvgCurrent);
#endif
}
//语言切换函数——中文@@@
void CMymainWindow::languageCN()
{
    g_iLangChange=1;
    m_pUi->pushButton_CN->setEnabled(false);
    m_pUi->pushButton_CN->setDown(true);
    m_pUi->pushButton_EN->setEnabled(true);
    m_pUi->pushButton_EN->setDown(false);
    m_pUi->pushButton_CN->setText(QApplication::translate("mainWindow", "\344\270\255\346\226\207", 0, QApplication::UnicodeUTF8));
    m_pUi->pushButton_EN->setText(QApplication::translate("mainWindow", "\350\213\261\346\226\207", 0, QApplication::UnicodeUTF8));
    m_strMainWindow=QApplication::translate("mainWindow",
        "\344\270\273\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8);
    m_strSubcabinetctl=QApplication::translate("mainWindow",
        "\345\210\206\346\237\234\346\216\247\345\210\266\344\277\241\346\201\257",
        0,
        QApplication::UnicodeUTF8);
    m_strStatusrecord=QApplication::translate("mainWindow",
        "\347\212\266\346\200\201\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8);
    m_strSettings=QApplication::translate("mainWindow",
        "\350\256\276\347\275\256\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8);
    m_strSwitchstatus=QApplication::translate("mainWindow",
        "\344\270\273\346\237\234\345\274\200\345\205\263\351\207\217\347\212\266\346\200\201",
        0,
        QApplication::UnicodeUTF8);
    m_strLanguage=QApplication::translate("mainWindow",
        "    \350\257\255\350\250\200",
        0,
        QApplication::UnicodeUTF8);
    m_strPoweramplstate=QApplication::translate("mainWindow",
        "\345\212\237\346\224\276\347\212\266\346\200\201",
        0,
        QApplication::UnicodeUTF8);
    m_strtotaloutputVolt=QApplication::translate("mainWindow",
        "     \347\224\265\345\216\213\357\274\210V\357\274\211",
        0,
        QApplication::UnicodeUTF8);
    m_strtotaloutputCurr=QApplication::translate("mainWindow",
        "     \347\224\265\346\265\201\357\274\210A\357\274\211",
        0,
        QApplication::UnicodeUTF8);
    m_strExcitationvolt=QApplication::translate("mainWindow",
        "   \345\212\261\347\243\201\347\224\265\345\216\213",
        0,
        QApplication::UnicodeUTF8);
    m_strExcitationcurr=QApplication::translate("mainWindow",
        "   \345\212\261\347\243\201\347\224\265\346\265\201",
        0,
        QApplication::UnicodeUTF8);
    m_strPhaseAVoltage=QApplication::translate("mainWindow",
        "   A\347\233\270\347\224\265\345\216\213",
        0,
        QApplication::UnicodeUTF8);
    m_strPhaseBVoltage=QApplication::translate("mainWindow",
        "   B\347\233\270\347\224\265\345\216\213",
        0,
        QApplication::UnicodeUTF8);
    m_strPhaseCVoltage=QApplication::translate("mainWindow",
        "   C\347\233\270\347\224\265\345\216\213",
        0,
        QApplication::UnicodeUTF8);
    m_strStationindicator=QApplication::translate("mainWindow",
        "\347\212\266\346\200\201\346\214\207\347\244\272\347\201\257",
        0,
        QApplication::UnicodeUTF8);
    m_strRunning=QApplication::translate("mainWindow",
        "\350\277\220\350\241\214",0, QApplication::UnicodeUTF8);
    m_strCooling=QApplication::translate("mainWindow",
        "\345\206\267\345\215\264", 0, QApplication::UnicodeUTF8);
    m_strExcitation=QApplication::translate("mainWindow",
        "\345\212\261\347\243\201", 0, QApplication::UnicodeUTF8);
    m_strReady=QApplication::translate("mainWindow",
        "\345\207\206\345\244\207", 0, QApplication::UnicodeUTF8);
    m_strGain=QApplication::translate("mainWindow",
        "\345\242\236\347\233\212", 0, QApplication::UnicodeUTF8);
    m_strFault=QApplication::translate("mainWindow",
        "\346\225\205\351\232\234", 0, QApplication::UnicodeUTF8);
    m_strPoweramplctl=QApplication::translate("mainWindow",
        "\345\212\237\346\224\276\346\216\247\345\210\266",
        0,
        QApplication::UnicodeUTF8);
    m_strStart=QApplication::translate("mainWindow",
        "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8);
    m_strStop=QApplication::translate("mainWindow",
        "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8);
    m_strReset=QApplication::translate("mainWindow",
        "\345\244\215\344\275\215", 0, QApplication::UnicodeUTF8);
    m_strGainctl=QApplication::translate("mainWindow",
        "\345\242\236\347\233\212\346\216\247\345\210\266",
        0,
        QApplication::UnicodeUTF8);
    m_strSwitch=QApplication::translate("mainWindow",
        "  \345\274\200\345\205\263", 0, QApplication::UnicodeUTF8);
    m_strGear=QApplication::translate("mainWindow",
        "\346\241\243\344\275\215", 0, QApplication::UnicodeUTF8);
    m_strMessagefeedback=QApplication::translate("mainWindow",
        "    \346\266\210\346\201\257\345\217\215\351\246\210:",
        0,
        QApplication::UnicodeUTF8);
    m_strConnection=QApplication::translate("mainWindow",
        "\350\256\276\345\244\207\350\277\236\346\216\245\347\212\266\346\200\201\346\255\243\345\270\270",
        0,
        QApplication::UnicodeUTF8);
    /*
    m_strEstop=QApplication::translate("mainWindow",
        "\347\264\247\346\200\245\345\201\234\346\234\272",
        0,
        QApplication::UnicodeUTF8);//add by 2020.11.25
        */
    m_strProtecttype=QApplication::translate("mainWindow",
        "    \344\277\235\346\212\244\347\261\273\345\236\213:",
        0,
        QApplication::UnicodeUTF8);
    m_strSubcabinetNum=QApplication::translate("mainWindow", "\345\210\206\346\237\234\345\217\267",
        0, QApplication::UnicodeUTF8);
    m_strSubcabinetInfo=QApplication::translate("mainWindow",
        "\345\210\206\346\237\234\345\274\200\345\205\263\351\207\217\347\212\266\346\200\201",
        0,
        QApplication::UnicodeUTF8);
    //MainWindow下tabWidget语言切换
    m_pUi->toolButton_Home->setText(QApplication::translate("mainWindow", "\344\270\273\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));       //主界面（简写 by 2020.04.19）
    m_pUi->toolButton_Slave->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\234\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));   //分柜信息（简写 by 2020.04.19）
    m_pUi->toolButton_StaRecord->setText(QApplication::translate("mainWindow", "\347\212\266\346\200\201\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));//状态记录（简写by 2020.04.19）
    m_pUi->toolButton_Set->setText(QApplication::translate("mainWindow", "\350\256\276\347\275\256\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));    //设置选择(简写 by 2020.04.19)
    m_pUi->toolButton_Master->setText(QApplication::translate("mainWindow", "\344\270\273\346\237\234\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8)); //主柜信息(简写 by 2020.04.19)
    m_pUi->toolButton_gfstate->setText(m_strPoweramplstate);//"功放状态"按钮中文字 by 2020.04.19
    m_pUi->label_3->setText(m_strtotaloutputVolt);
    m_pUi->label_14->setText(m_strtotaloutputCurr);
    m_pUi->label_16->setText(m_strExcitationvolt);
    m_pUi->label_18->setText(m_strExcitationcurr);
    m_pUi->label_20->setText(m_strPhaseAVoltage);
    m_pUi->label_22->setText(m_strPhaseBVoltage);
    m_pUi->label_24->setText(m_strPhaseCVoltage);
    m_pUi->toolButton_staIndicator->setText(m_strStationindicator);//"状态指示灯"按钮中文，add by 2020.04.19
//	m_pUi->label_8->setText(m_strRunning);
    m_pUi->label_9->setText(m_strCooling);
    m_pUi->label_10->setText(m_strExcitation);
    m_pUi->label_11->setText(m_strReady);
    m_pUi->label_12->setText(m_strGain);
    m_pUi->label_67->setText(m_strFault);
    m_pUi->toolButton_gfctl->setText(m_strPoweramplctl);//"功放控制"按钮中文，add by 2020.04.19
    m_pUi->label_start->setText(m_strStart);
    m_pUi->label_stop->setText(m_strStop);
    m_pUi->label_reset->setText(m_strReset);
    m_pUi->label_emergency->setText(QApplication::translate("mainWindow", "\346\200\245\345\201\234", 0, QApplication::UnicodeUTF8));
    m_pUi->toolButton_gainctl->setText(m_strGainctl);   //"增益控制"按钮中文，add by 2020.04.19
    m_pUi->label_4->setText(m_strSwitch);
    m_pUi->label_28->setText(m_strGear);
    m_pUi->label_feedback->setText(m_strMessagefeedback);
    m_pUi->label_connect->setText(m_strConnection);
    m_pUi->proctypelabel->setText(m_strProtecttype);
    m_pUi->label_2->setText(QApplication::translate("mainWindow", "\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
    m_pUi->label_13->setText(QApplication::translate("mainWindow", "\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
    m_pUi->label_15->setText(QApplication::translate("mainWindow", "\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
    m_pUi->label_26->setText(QApplication::translate("mainWindow", "\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));

    m_pUi->label_7->setText(QApplication::translate("mainWindow", "\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
    m_pUi->label_30->setText(QApplication::translate("mainWindow", "\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
    m_pUi->label_32->setText(QApplication::translate("mainWindow", "\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
    m_pUi->label_34->setText(QApplication::translate("mainWindow", "\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));

    m_pUi->sub1label_runstate->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));//运行状态简写     by 2020.04.19
    m_pUi->label_sub1volt->setText(QApplication::translate("mainWindow", "\347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));    //分柜电压简写     by 2020.04.19
    m_pUi->label_sub1current->setText(QApplication::translate("mainWindow", "\347\224\265\346\265\201\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8)); //分柜电流间写     by 2020.04.19
    m_pUi->busvolt_1->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));     //母线正负电压简写 by 2020.04.19

    m_pUi->sub2label_runstate->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->label_sub2volt->setText(QApplication::translate("mainWindow", "\347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
    m_pUi->label_sub2current->setText(QApplication::translate("mainWindow", "\347\224\265\346\265\201\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
    m_pUi->busvolt_2->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));

    m_pUi->sub3label_runstate->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->label_sub3volt->setText(QApplication::translate("mainWindow", "\347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
    m_pUi->label_sub3current->setText(QApplication::translate("mainWindow", "\347\224\265\346\265\201\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
    m_pUi->busvolt_3->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));

    m_pUi->sub4label_runstate->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->label_sub4volt->setText(QApplication::translate("mainWindow", "\347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
    m_pUi->label_sub4current->setText(QApplication::translate("mainWindow", "\347\224\265\346\265\201\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
    m_pUi->busvolt_4->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));

    m_pUi->toolButton_TempCtl->setText(QApplication::translate("mainWindow", "\346\270\251\345\272\246\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
    m_pUi->toolButton_FaultSta->setText(QApplication::translate("mainWindow", "\346\225\205\351\232\234\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->toolButton_RunningSta->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->toolButton_HisCurve->setText(QApplication::translate("mainWindow", "\345\216\206\345\217\262\346\233\262\347\272\277", 0, QApplication::UnicodeUTF8));
    m_pUi->fgDigBtn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\234\345\274\200\345\205\263\351\207\217\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));//分柜开关量状态简写英文 by 2020.04.19

    m_pUi->label_sub1->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));//分柜1英文 by 2020.08.21
    m_pUi->label_sub2->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));//分柜1英文 by 2020.08.21
    m_pUi->label_sub3->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));//分柜1英文 by 2020.08.21
    m_pUi->label_sub4->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));//分柜1英文 by 2020.08.21
    //删掉button类型，改为label，add by 2020.08.21
    /*
    m_pUi->fg1Btn->setText(QApplication::translate("mainWindow", "\345\210\206 \346\237\234 1", 0, QApplication::UnicodeUTF8));
    m_pUi->fg2Btn->setText(QApplication::translate("mainWindow", "\345\210\206 \346\237\234 2", 0, QApplication::UnicodeUTF8));
    m_pUi->fg3Btn->setText(QApplication::translate("mainWindow", "\345\210\206 \346\237\234 3", 0, QApplication::UnicodeUTF8));
    m_pUi->fg4Btn->setText(QApplication::translate("mainWindow", "\345\210\206 \346\237\234 4", 0, QApplication::UnicodeUTF8));
    */
    //温度界面语言切换
    m_pTempmonitorWdgt->temperLangChange();
    //故障状态界面语言切换
    m_FaultCondWdgt.faultLangChange();
    //运行状态界面语言切换
    m_pRunStaWdget->runningLangChange();
    //历史曲线界面语言切换
    m_HiscurveWdget.hiscurvelangchange();
    //状态记录界面
    m_pUi->upBtn->setText(QApplication::translate("mainWindow", "\344\270\212\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
    m_pUi->nextBtn->setText(QApplication::translate("mainWindow", "\344\270\213\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
    m_pUi->firstBtn->setText(QApplication::translate("mainWindow", "\351\246\226  \351\241\265", 0, QApplication::UnicodeUTF8));
    m_pUi->tailBtn->setText(QApplication::translate("mainWindow", " \345\260\276  \351\241\265", 0, QApplication::UnicodeUTF8));
    //设置选择语言切换
    m_pUi->adjBtn->setText(QApplication::translate("mainWindow", "\346\240\241\345\207\206\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
    m_pUi->chainBtn->setText(QApplication::translate("mainWindow", "\350\277\236\351\224\201\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    //m_pUi->thrBtn->setText(QApplication::translate("mainWindow", "\344\277\235\346\212\244\351\230\200\345\200\274", 0, QApplication::UnicodeUTF8));
    //m_pUi->dcBtn->setText(QApplication::translate("mainWindow", "\347\233\264\346\265\201\350\260\203\350\212\202", 0, QApplication::UnicodeUTF8));
    m_pUi->invalidBtn->setText(QApplication::translate("mainWindow", "\345\244\261\346\225\210\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    m_pUi->pwdsetBtn->setText(QApplication::translate("mainWindow", "\345\257\206\347\240\201\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    m_pUi->basicparaBtn->setText(QApplication::translate("mainWindow", "\345\237\272\346\234\254\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
    m_pUi->lrctlBtn->setText(QApplication::translate("mainWindow", "\350\277\234\347\250\213\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
    m_pUi->syssetBtn->setText(QApplication::translate("mainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));//add by 2020.11.20
    //校准界面语言切换
    m_pAdjcoefdlg->adjcoefLangChange();
    //连锁设置界面语言切换
    m_pChainsetdlg->chainLangChange();
    //密码设置界面语言切换
    m_Pwdsetdlg.passwordLangChange();
    //基本参数界面语言切换
    m_BasicParaSetdlg.basicparaLangChange();
    //系统设置界面语言切换 add by 2020.11.20
    m_Syssetdlg.syssetLangChange();
    //主柜开关量语言切换
    m_pUi->label_73->setText(QApplication::translate("mainWindow", "\345\261\217\350\224\275\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->label_57->setText(QApplication::translate("mainWindow", "\345\275\223\345\211\215\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->label_84->setText(QApplication::translate("mainWindow", "\345\275\223\345\211\215\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->label_59->setText(QApplication::translate("mainWindow", "\345\261\217\350\224\275\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
    m_pUi->label_46->setText(QApplication::translate("mainWindow", "\347\264\247\346\200\245\345\201\234\346\234\272", 0, QApplication::UnicodeUTF8));
    m_pUi->label_49->setText(QApplication::translate("mainWindow", "\346\273\221\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
    m_pUi->label_99->setText(QApplication::translate("mainWindow", "\346\214\257\345\212\250\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
    m_pUi->label_100->setText(QApplication::translate("mainWindow", "\346\273\221\345\217\260\344\275\216\346\266\262\344\275\215", 0, QApplication::UnicodeUTF8));
    m_pUi->label_102->setText(QApplication::translate("mainWindow", "\346\273\221\345\217\260\350\275\264\346\211\277\344\275\216\345\216\213", 0, QApplication::UnicodeUTF8));
    m_pUi->label_103->setText(QApplication::translate("mainWindow", "\346\214\257\345\212\250\345\217\260\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
    m_pUi->label_101->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
    m_pUi->label_104->setText(QApplication::translate("mainWindow", "\350\200\263\350\275\264\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
    m_pUi->label_105->setText(QApplication::translate("mainWindow", "\345\212\237\346\224\276\347\203\255\347\273\247\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
    m_pUi->label_106->setText(QApplication::translate("mainWindow", "\351\235\231\345\216\213\350\275\264\346\211\277\344\275\216\345\216\213", 0, QApplication::UnicodeUTF8));
    m_pUi->label_107->setText(QApplication::translate("mainWindow", "\344\270\273\346\237\234\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
    m_pUi->label_108->setText(QApplication::translate("mainWindow", "\347\263\273\347\273\237\345\206\267\345\215\264\345\215\225\345\205\203", 0, QApplication::UnicodeUTF8));
    m_pUi->label_109->setText(QApplication::translate("mainWindow", "\344\270\273\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
    m_pUi->label_110->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2112", 0, QApplication::UnicodeUTF8));
    m_pUi->label_111->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2113", 0, QApplication::UnicodeUTF8));
    m_pUi->sub1Btn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));
    m_pUi->sub2Btn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));
    m_pUi->sub3Btn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));
    m_pUi->sub4Btn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));
    m_pUi->label_77->setText(QApplication::translate("mainWindow","\344\270\273\346\237\234\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8)); //add by 2020.08.25
    m_pUi->label_79->setText(QApplication::translate("mainWindow", "\344\270\273\346\237\234\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8)); //add by 2020.08.25
    //数字键盘语言切换
    m_KeyBoardDlg.keyboardLangChange();
    //密码键盘语言切换
    m_logindlg.loginLangChange();
    //倒计时界面语言切换
    m_CountDownWdgt.countdownLangChange();
    //失效设置界面语言切换
    m_Invalidsetdlg.invalidsetLangChange();
    //保护类型语言切换
    //紧急停机
     m_strjjtj=QApplication::translate("mainWindow",
         "\347\264\247\346\200\245\345\201\234\346\234\272",
         0,
         QApplication::UnicodeUTF8);
    //滑台过位移
     m_strhtgwy=QApplication::translate("mainWindow",
         "\346\273\221\345\217\260\350\277\207\344\275\215\347\247\273",
         0,
         QApplication::UnicodeUTF8);
     //振动台过位移
     m_strzdtgwy= QApplication::translate("mainWindow",
         "\346\214\257\345\212\250\345\217\260\350\277\207\344\275\215\347\247\273",
         0,
         QApplication::UnicodeUTF8);
     //滑台低液位
     m_strhtdyw=QApplication::translate("mainWindow",
         "\346\273\221\345\217\260\344\275\216\346\266\262\344\275\215",
         0,
         QApplication::UnicodeUTF8);
     //振动台冷却
     m_strzdtlq= QApplication::translate("mainWindow",
         "\346\214\257\345\212\250\345\217\260\345\206\267\345\215\264",
         0,
         QApplication::UnicodeUTF8);
     //滑台轴承低压
     m_strhtqy=QApplication::translate("mainWindow",
         "\346\273\221\345\217\260\350\275\264\346\211\277\344\275\216\345\216\213",
         0,
         QApplication::UnicodeUTF8);
     //振动台过温
     m_strzdtgw=QApplication::translate("mainWindow",
         "\346\214\257\345\212\250\345\217\260\350\277\207\346\270\251",
         0,
         QApplication::UnicodeUTF8);
     //耳轴过位移
     m_strezgwy=QApplication::translate("mainWindow",
         "\350\200\263\350\275\264\350\277\207\344\275\215\347\247\273",
         0,
         QApplication::UnicodeUTF8);
     //功放热继保护
     m_strgfrjbh=QApplication::translate("mainWindow",
         "\345\212\237\346\224\276\347\203\255\347\273\247\344\277\235\346\212\244",
         0,
         QApplication::UnicodeUTF8);
     //静压轴承低压
     m_strjyzcdy=QApplication::translate("mainWindow",
         "\351\235\231\345\216\213\350\275\264\346\211\277\344\275\216\345\216\213",
         0,
         QApplication::UnicodeUTF8);
     //主柜门保护
     m_strmbh=QApplication::translate("mainWindow",
         "\344\270\273\346\237\234\351\227\250\344\277\235\346\212\244",
         0,
         QApplication::UnicodeUTF8);
     //系统冷却单元
     m_strxtlqdy=QApplication::translate("mainWindow",
         "\347\263\273\347\273\237\345\206\267\345\215\264\345\215\225\345\205\203",
         0,
         QApplication::UnicodeUTF8);
     //主柜整流桥过温
     m_strhtqyw=QApplication::translate("mainWindow",
         "\344\270\273\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251",
         0,
         QApplication::UnicodeUTF8);
     //保护判断语言切换
     m_JudgeProc.judgeLangChange();
     mainLangchange();
     //状态记录界面语言切换
    m_pUi->label_29->setText(QApplication::translate("mainWindow", "\347\263\273\347\273\237\346\200\273\350\277\220\350\241\214\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
    m_pUi->label_31->setText(QApplication::translate("mainWindow", "\346\234\200\345\220\216\344\270\200\346\254\241\350\277\220\350\241\214\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
    m_pUi->label_5->setText(QApplication::translate("mainWindow", "\347\254\254", 0, QApplication::UnicodeUTF8));
    m_pUi->label_6->setText(QApplication::translate("mainWindow", "\351\241\265", 0, QApplication::UnicodeUTF8));
    m_pUi->label->setText(QApplication::translate("mainWindow", "\345\205\261", 0, QApplication::UnicodeUTF8));
    m_pUi->label_69->setText(QApplication::translate("mainWindow", "\346\235\241\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
    m_pUi->label_70->setText(QApplication::translate("mainWindow", "\345\205\261", 0, QApplication::UnicodeUTF8));
    m_pUi->label_72->setText(QApplication::translate("mainWindow", "\351\241\265", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem = m_pUi->tableWidget->horizontalHeaderItem(0);
    ___qtablewidgetitem->setText(QApplication::translate("mainWindow", "\346\212\245\350\255\246\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem1 = m_pUi->tableWidget->horizontalHeaderItem(1);
    ___qtablewidgetitem1->setText(QApplication::translate("mainWindow", "\344\277\235\346\212\244\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem2 = m_pUi->tableWidget->horizontalHeaderItem(2);
    ___qtablewidgetitem2->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\347\224\265\345\216\213\346\234\211\346\225\210\345\200\274\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem3 = m_pUi->tableWidget->horizontalHeaderItem(3);
    ___qtablewidgetitem3->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\347\224\265\345\216\213\346\234\200\345\244\247\345\200\274\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem4 = m_pUi->tableWidget->horizontalHeaderItem(4);
    ___qtablewidgetitem4->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\347\224\265\346\265\201\346\234\211\346\225\210\345\200\274\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem5 = m_pUi->tableWidget->horizontalHeaderItem(5);
    ___qtablewidgetitem5->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\347\224\265\346\265\201\346\234\200\345\244\247\345\200\274\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
    //输出日志语言切换
    m_strOutputSaveSuccess= QApplication::translate("mainWindow", "\350\276\223\345\207\272\346\227\245\345\277\227\346\226\207\344\273\266\344\277\235\345\255\230\346\210\220\345\212\237",
        0,
        QApplication::UnicodeUTF8);//输出日志文件保存成功提示语 add by 2020.11.12

    m_strOutputSaveFail= QApplication::translate("mainWindow", "\350\276\223\345\207\272\346\227\245\345\277\227\346\226\207\344\273\266\344\277\235\345\255\230\345\244\261\350\264\245,\350\257\267\346\243\200\346\237\245",
        0,
        QApplication::UnicodeUTF8);//输出日志文件保存失败提示语 add by 2020.11.12
}
//语言切换函数——英文@@@
void CMymainWindow::languageEN()
{
    g_iLangChange=0;
    m_pUi->pushButton_CN->setEnabled(true);
    m_pUi->pushButton_CN->setDown(false);
    m_pUi->pushButton_EN->setEnabled(false);
    m_pUi->pushButton_EN->setDown(true);
    //MainWindow下tabWidget语言切换
    m_pUi->pushButton_CN->setText(tr("CN"));
    m_pUi->pushButton_EN->setText(tr("EN"));

    m_pUi->toolButton_Home->setText(tr("Home"));       //主界面（简写 by 2020.04.19）
    m_pUi->toolButton_Slave->setText(tr("Sub-cab"));   //分柜信息（简写 by 2020.04.19）
    m_pUi->toolButton_StaRecord->setText(tr("Record"));//状态记录（简写by 2020.04.19）
    m_pUi->toolButton_Set->setText(tr("Settings"));    //设置选择(简写 by 2020.04.19)
    m_pUi->toolButton_Master->setText(tr("Main-cab")); //主柜信息(简写 by 2020.04.19)
    m_pUi->toolButton_gfstate->setText(tr("PA Status"));//add by 2020.04.19
    m_pUi->label_3->setText("        V");//删除"output"
    m_pUi->label_14->setText("        A");//删除"output"
    m_pUi->label_16->setText("Field Voltage");
    m_pUi->label_18->setText("Field Current");
    m_pUi->label_20->setText("Phase A Voltage");
    m_pUi->label_22->setText("Phase B Voltage");
    m_pUi->label_24->setText("Phase C Voltage");
    m_pUi->toolButton_staIndicator->setText(tr("Indicator"));
//	m_pUi->label_8->setText("Running");
    m_pUi->label_9->setText("Cooling");
    m_pUi->label_10->setText("Field");
    m_pUi->label_11->setText("Ready");
    m_pUi->label_12->setText("Gain");
    m_pUi->label_67->setText("Fault");
    m_pUi->toolButton_gfctl->setText(tr("Control"));
    m_pUi->label_start->setText("Start");
    m_pUi->label_stop->setText("Stop");
    m_pUi->label_reset->setText("Reset");
    m_pUi->label_emergency->setText("E-stop");
    m_pUi->toolButton_gainctl->setText(tr("Gain"));
    m_pUi->label_4->setText("Switch");
    m_pUi->label_28->setText("Gear");
    m_pUi->label_feedback->setText("Message:");
    m_pUi->label_connect->setText("Connection status is normal");
    m_pUi->proctypelabel->setText("Protection:");
    m_pUi->label_2->setText("REC.TEMP");
    m_pUi->label_13->setText("REC.TEMP");
    m_pUi->label_15->setText("REC.TEMP");
    m_pUi->label_26->setText("REC.TEMP");

    m_pUi->label_7->setText("Doors");
    m_pUi->label_30->setText("Doors");
    m_pUi->label_32->setText("Doors");
    m_pUi->label_34->setText("Doors");
    m_pUi->sub1Btn->setText(tr("Cub1"));
    m_pUi->sub2Btn->setText(tr("Cub2"));
    m_pUi->sub3Btn->setText(tr("Cub3"));
    m_pUi->sub4Btn->setText(tr("Cub4"));

    //删掉button类型，改为label，add by 2020.08.21
    /*
    m_pUi->fg1Btn->setText(tr("Cub1"));
    m_pUi->fg2Btn->setText(tr("Cub2"));
    m_pUi->fg3Btn->setText(tr("Cub3"));
    m_pUi->fg4Btn->setText(tr("Cub4"));
    */
    m_pUi->label_sub1->setText("Sub1");//分柜1简写英文     by 2020.08.21
    m_pUi->label_sub2->setText("Sub2");//分柜2简写英文     by 2020.08.21
    m_pUi->label_sub3->setText("Sub3");//分柜3简写英文     by 2020.08.21
    m_pUi->label_sub4->setText("Sub4");//分柜4简写英文     by 2020.08.21
    m_pUi->sub1label_runstate->setText("Running");//运行状态简写英文     by 2020.04.19
    m_pUi->label_sub1volt->setText("    V");    //分柜电压简写英文     by 2020.04.19
    m_pUi->label_sub1current->setText("    A"); //分柜电流间写英文     by 2020.04.19
    m_pUi->busvolt_1->setText("DC Voltage");     //母线正负电压简写英文 by 2020.04.19

    m_pUi->sub2label_runstate->setText("Running");
    m_pUi->label_sub2volt->setText("    V");
    m_pUi->label_sub2current->setText("    A");
    m_pUi->busvolt_2->setText("DC Voltage");

    m_pUi->sub3label_runstate->setText("Running");
    m_pUi->label_sub3volt->setText("    V");
    m_pUi->label_sub3current->setText("    A");
    m_pUi->busvolt_3->setText("DC Voltage");

    m_pUi->sub4label_runstate->setText("Running");
    m_pUi->label_sub4volt->setText("    V");
    m_pUi->label_sub4current->setText("    A");
    m_pUi->busvolt_4->setText("DC Voltage");

    m_pUi->fgDigBtn->setText("Switch Status of Cab");//分柜开关量状态简写英文 by 2020.04.19
    m_pUi->toolButton_TempCtl->setText("Monitor");   //温度监控英文  by 2020.04.19
    m_pUi->toolButton_FaultSta->setText("Fault");    //故障状态英文  by 2020.04.19
    m_pUi->toolButton_RunningSta->setText("Running");//运行状态英文  by 2020.04.19
    m_pUi->toolButton_HisCurve->setText("HisCurve"); //历史曲线英文  by 2020.04.19
    //温度界面语言切换
    m_pTempmonitorWdgt->temperLangChange();
    //故障状态界面语言切换
    m_FaultCondWdgt.faultLangChange();
    //运行状态界面语言切换
    m_pRunStaWdget->runningLangChange();
    //历史曲线界面语言切换
    m_HiscurveWdget.hiscurvelangchange();
    //状态记录与界面
    m_pUi->upBtn->setText("Page Up");
    m_pUi->nextBtn->setText("Page Down");
    m_pUi->firstBtn->setText("  Home  ");
    m_pUi->tailBtn->setText("  End  ");
    //设置选择语言切换
    m_pUi->adjBtn->setText("Calibration");
    m_pUi->chainBtn->setText("Interlock");
    m_pUi->invalidBtn->setText("Expiration");
    m_pUi->pwdsetBtn->setText("Password");
    m_pUi->basicparaBtn->setText("Properties");
    m_pUi->lrctlBtn->setText("Remote");
    m_pUi->syssetBtn->setText("System");// add by 2020.11.20
    //校准界面语言切换
    m_pAdjcoefdlg->adjcoefLangChange();
    //连锁设置界面语言切换
    m_pChainsetdlg->chainLangChange();
    //密码设置界面语言切换
    m_Pwdsetdlg.passwordLangChange();
    //基本参数界面语言切换
    m_BasicParaSetdlg.basicparaLangChange();
    //主柜开关量语言切换
    m_pUi->label_73->setText("Shield Status");
    m_pUi->label_57->setText("   Status");
    m_pUi->label_84->setText("   Status");
    m_pUi->label_59->setText("Shield Status");
    m_pUi->label_46->setText("Emergency Stop");
    m_pUi->label_49->setText("S.T. Overtravel");
    m_pUi->label_99->setText("VIB. Overtravel");
    m_pUi->label_100->setText("S.T. U/L");
    m_pUi->label_102->setText("S.T. U/P");
    m_pUi->label_103->setText("VIB. OverTEMP");
    m_pUi->label_101->setText("External1");
    m_pUi->label_104->setText("TRUN. O/T");
    m_pUi->label_105->setText("Relay O/L");
    m_pUi->label_106->setText("VIB. U/P");
    m_pUi->label_107->setText("Main Doors");
    m_pUi->label_108->setText("S.C.U.");
    m_pUi->label_109->setText("M.R. OverTEMP");
    m_pUi->label_110->setText("External2");
    m_pUi->label_111->setText("External3");
    m_pUi->label_77->setText("Main Protection");// add by 2020.08.25
    m_pUi->label_79->setText("Main Protection");// add by 2020.08.25
    //数字键盘语言切换
    m_KeyBoardDlg.keyboardLangChange();
    //密码键盘语言切换
    m_logindlg.loginLangChange();
    //倒计时界面语言切换
    m_CountDownWdgt.countdownLangChange();
    //失效设置界面语言切换
    m_Invalidsetdlg.invalidsetLangChange();
    //保护类型语言切换
    //紧急停机
     m_strjjtj="Emergency shutdown";
    //滑台过位移
     m_strhtgwy="S.T. Overtravel";
     //振动台过位移
     m_strzdtgwy= "VIB. Overtravel";
     //滑台低液位
     m_strhtdyw="S.T. U/L";
     //振动台冷却
     m_strzdtlq="Shaker cooling";
     //滑台轴承低压
     m_strhtqy="S.T. U/P";
     //振动台过温
     m_strzdtgw="VIB. OverTEMP";
     //耳轴过位移
     m_strezgwy="TRUN. O/T";
     //功放热继保护
     m_strgfrjbh="Relay O/L";
     //静压轴承低压
     m_strjyzcdy="VIB. U/P";
     //主柜门保护
     m_strmbh="Main Doors";
     //系统冷却单元
     m_strxtlqdy="S.C.U.";
     //主柜整流桥过温
     m_strhtqyw="M.R. OverTEMP";
     //保护判断语言切换
     m_JudgeProc.judgeLangChange();
     mainLangchange();
     //状态记录语言切换
    m_pUi->label_29->setText("Total running time");
    m_pUi->label_31->setText("Last runing time");
    m_pUi->label_5->setText("Page");
    m_pUi->label_6->setText(" ");
    m_pUi->label->setText(" ");
    m_pUi->label_69->setText("records");
    m_pUi->label_70->setText(" ");
    m_pUi->label_72->setText("pages");
    QTableWidgetItem *___qtablewidgetitem = m_pUi->tableWidget->horizontalHeaderItem(0);
    ___qtablewidgetitem->setText("Time");
    QTableWidgetItem *___qtablewidgetitem1 = m_pUi->tableWidget->horizontalHeaderItem(1);
    ___qtablewidgetitem1->setText("Protection");
    QTableWidgetItem *___qtablewidgetitem2 = m_pUi->tableWidget->horizontalHeaderItem(2);
    ___qtablewidgetitem2->setText("Effective voltage");
    QTableWidgetItem *___qtablewidgetitem3 = m_pUi->tableWidget->horizontalHeaderItem(3);
    ___qtablewidgetitem3->setText("Maximum voltage");
    QTableWidgetItem *___qtablewidgetitem4 = m_pUi->tableWidget->horizontalHeaderItem(4);
    ___qtablewidgetitem4->setText("Effective current");
    QTableWidgetItem *___qtablewidgetitem5 = m_pUi->tableWidget->horizontalHeaderItem(5);
    ___qtablewidgetitem5->setText("Maximum current");
    //输出日志语言切换
    m_strOutputSaveSuccess= "Output log profile saved successfully";//输出日志文件保存成功提示语 add by 2020.11.12
    m_strOutputSaveFail= "Output log profile failed to save,please check";//输出日志文件保存失败提示语 add by 2020.11.12
}//切换主界面槽函数,add by 2020.04.04@@@
 void CMymainWindow::homeBtn_clicked()
 {
     m_pUi->stackedWidget->setCurrentIndex(0);
 }
 //切换分柜信息槽函数,add by 2020.04.04
void CMymainWindow::slaveBtn_clicked()
{
    m_pUi->stackedWidget->setCurrentIndex(1);
    sub1Btn_clicked();
}
//切换状态记录槽函数,add by 2020.04.04
void CMymainWindow::staRecordBtn_clicked()
{
    m_pUi->stackedWidget->setCurrentIndex(2);
    firstBtn_clicked();
}
//切换设置选择槽函数,add by 2020.04.04
void CMymainWindow::setBtn_clicked()
{
    int ret =m_logindlg.exec();
    if(m_logindlg.IsPWDCorrect()==USER_ROLE_TYPE)//用户密码
    {
        m_iRoletype=USER_ROLE_TYPE;//add by 2020.08.15
        m_logindlg.clearBtn_clicked();//清除密码
        //m_pUi->adjBtn->setEnabled(true);
        m_pUi->adjBtn->show();         //add by 2020.08.21
        m_pUi->pwdsetBtn->show();   //add by 2020.08.21
        m_pUi->lrctlBtn->show();       //add by 2020.08.21
        m_pUi->syssetBtn->show();     //add by 2020.08.21
        m_pUi->chainBtn->hide();
        m_pUi->basicparaBtn->hide();
        m_pUi->invalidBtn->hide();
        m_pUi->pwdsetBtn->setEnabled(true);
        m_pUi->lrctlBtn->setEnabled(true);
        /*
        QHBoxLayout *buttonLayout = new QHBoxLayout(this);
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(m_pUi->adjBtn);
        buttonLayout->addStretch(2);
        buttonLayout->addWidget(m_pUi->pwdsetBtn);
        buttonLayout->addStretch(3);
        buttonLayout->addWidget(m_pUi->lrctlBtn);
        buttonLayout->addStretch(4);
        buttonLayout->addWidget(m_pUi->syssetBtn);
        buttonLayout->addStretch(8);
        buttonLayout->setContentsMargins(0,0,0,0);
        */
    }
    else if(m_logindlg.IsPWDCorrect()==ADMIN_ROLE_TYPE)//管理员密码
    {
        m_iRoletype=ADMIN_ROLE_TYPE;//add by 2020.08.15
        m_logindlg.clearBtn_clicked();//清除密码
        m_pUi->adjBtn->show();
        m_pUi->chainBtn->show();
        m_pUi->basicparaBtn->show();
        m_pUi->invalidBtn->show();
        m_pUi->pwdsetBtn->show();
        m_pUi->lrctlBtn->show();
        m_pUi->syssetBtn->show();

    }
    else if(m_logindlg.IsPWDCorrect()==ENGINEER_ROLE_TYPE)//工程师密码
    {
        m_iRoletype=ENGINEER_ROLE_TYPE;//add by 2020.08.15
        m_logindlg.clearBtn_clicked();//清除密码
        m_pUi->adjBtn->show();
        m_pUi->chainBtn->show();
        m_pUi->basicparaBtn->show();
        m_pUi->invalidBtn->hide();
        m_pUi->pwdsetBtn->show();
        m_pUi->lrctlBtn->show();
        m_pUi->syssetBtn->show();
    }
    else
    {
        m_iRoletype=OTHER_ROLE_TYPE;//add by 2020.08.15
        m_logindlg.clearBtn_clicked();//清除密码

        m_pUi->adjBtn->hide();
        m_pUi->chainBtn->hide();
        m_pUi->basicparaBtn->hide();
        m_pUi->invalidBtn->hide();
        m_pUi->pwdsetBtn->hide();
        m_pUi->lrctlBtn->hide();
        m_pUi->syssetBtn->hide();
    }
    m_pUi->stackedWidget->setCurrentIndex(3);
}
//切换主柜开关量状态槽函数,add by 2020.04.04@@@
void CMymainWindow::masterBtn_clicked()
{
    m_pUi->stackedWidget->setCurrentIndex(4);
}
//切换调试信息槽函数,add by 2020.04.04
void CMymainWindow::debugBtn_clicked()
{
    m_pUi->stackedWidget->setCurrentIndex(5);
}
//分柜信息页面-分柜1切换槽函数,add by 2020.04.18
void CMymainWindow::sub1Btn_clicked()
{
    m_pUi->SubStackedWidget->setCurrentIndex(0);
    m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));//亮色
    m_pUi->sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
}
//分柜信息页面-分柜2切换槽函数,add by 2020.04.18
void CMymainWindow::sub2Btn_clicked()
{
    m_pUi->SubStackedWidget->setCurrentIndex(1);
    m_pUi->sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));//亮色
    m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
}
//分柜信息页面-分柜3切换槽函数,add by 2020.04.18
void CMymainWindow::sub3Btn_clicked()
{
    m_pUi->SubStackedWidget->setCurrentIndex(2);
    m_pUi->sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));//亮色
    m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
}
//分柜信息页面-分柜4切换槽函数,add by 2020.04.18
void CMymainWindow::sub4Btn_clicked()
{
    m_pUi->SubStackedWidget->setCurrentIndex(3);
    m_pUi->sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));//亮色
    m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
}
/*系统设置槽函数实现 add by 2020.08.10*/
void CMymainWindow::syssetBtn_clicked()
{
    m_Syssetdlg.exec();
}

//add by zw 20220223
//错误信号异步通知处理函数
void CMymainWindow::ErrInput(int signum)
{
#ifdef UBUNTU_DEV //Compiler Switch
    irq = -1;
    read(fd_err,bf_Err,1);
    irq =(int)bf_Err[0];
    qDebug()<<"###ErrInput signum = "<<signum<<"Err input id = "<<irq<<"###";
    readErrStatus();
#endif
}

//读取错误保护状态信息
void CMymainWindow::readErrStatus()
{
#ifdef UBUNTU_DEV //Compiler Switch
    int tmpt1;
    switch (irq) {
    case VIBOD:
        tmpt1=ioctl(fd_err,0,VIBOD);
        printf("###VIBOD = %d\n",tmpt1);
        g_newfaultstatus.iVIBODFlag = 1;
        break;
    case VIBCU:
        tmpt1=ioctl(fd_err,0,VIBCU);
        printf("###VIBCU = %d\n",tmpt1);
        g_newfaultstatus.iVIBCUFlag = 1;
        break;
    case VIBOT:
        tmpt1=ioctl(fd_err,0,VIBOT);
        printf("###VIBOT = %d\n",tmpt1);
        g_newfaultstatus.iVIBOTFlag = 1;
        break;
    case STOD:
        tmpt1=ioctl(fd_err,0,STOD);
        printf("###STOD = %d\n",tmpt1);
        g_newfaultstatus.iSTODFlag = 1;
        break;
    case STUP:
        tmpt1=ioctl(fd_err,0,STUP);
        printf("###STUP = %d\n",tmpt1);
        g_newfaultstatus.iSTUPFlag = 1;
        break;
    case STOT:
        tmpt1=ioctl(fd_err,0,STOT);
        printf("###STOT = %d\n",tmpt1);
        g_newfaultstatus.iSTOTFlag = 1;
        break;
    case STOL:
        tmpt1=ioctl(fd_err,0,STOL);
        printf("###STOL = %d\n",tmpt1);
        g_newfaultstatus.iSTOLFlag = 1;
        break;
    case RELAY:
        tmpt1=ioctl(fd_err,0,RELAY);
        printf("###RELAY = %d\n",tmpt1);
        g_newfaultstatus.iRELAYFlag = 1;
        break;
    case DOOR:
        tmpt1=ioctl(fd_err,0,DOOR);
        printf("###DOOR = %d\n",tmpt1);
        g_newfaultstatus.iDOORFlag = 1;
        break;
    case HBUP:
        tmpt1=ioctl(fd_err,0,HBUP);
        printf("###HBUP = %d\n",tmpt1);
        g_newfaultstatus.iHBUPFlag = 1;
        break;
    case EXT1:
        tmpt1=ioctl(fd_err,0,EXT1);
        printf("###EXT1 = %d\n",tmpt1);
        g_newfaultstatus.iEXT1Flag = 1;
        break;
    case EXT2:
        tmpt1=ioctl(fd_err,0,EXT2);
        printf("###EXT2 = %d\n",tmpt1);
        g_newfaultstatus.iEXT2Flag = 1;
        break;
    case EXT3:
        tmpt1=ioctl(fd_err,0,EXT3);
        printf("###EXT3 = %d\n",tmpt1);
        g_newfaultstatus.iEXT3Flag = 1;
        break;
    case EXT4:
        tmpt1=ioctl(fd_err,0,EXT4);
        printf("###EXT4 = %d\n",tmpt1);
        g_newfaultstatus.iEXT4Flag = 1;
        break;
    case ESTOP:
        tmpt1=ioctl(fd_err,0,ESTOP);
        printf("###ESTOP = %d\n",tmpt1);
        g_newfaultstatus.iESTOPFlag = 1;
        break;
    case OT1:
        tmpt1=ioctl(fd_err,0,OT1);
        printf("###OT1 = %d\n",tmpt1);
        g_newfaultstatus.iOT1Flag = 1;
        break;
    case OT2:
        tmpt1=ioctl(fd_err,0,OT2);
        printf("###OT2 = %d\n",tmpt1);
        g_newfaultstatus.iOT2Flag = 1;
        break;
    case OT3:
        tmpt1=ioctl(fd_err,0,OT3);
        printf("###OT3 = %d\n",tmpt1);
        g_newfaultstatus.iOT3Flag = 1;
        break;
    case OT4:
        tmpt1=ioctl(fd_err,0,OT4);
        printf("###OT4 = %d\n",tmpt1);
        g_newfaultstatus.iOT4Flag = 1;
        break;
    case SESTOP:
        tmpt1=ioctl(fd_err,0,SESTOP);
        printf("###SESTOP = %d\n",tmpt1);
        g_newfaultstatus.iSESTOPFlag = 1;
        break;
    case FAULT1:
        tmpt1=ioctl(fd_err,0,FAULT1);
        printf("###FAULT1 = %d\n",tmpt1);
        g_newfaultstatus.iFAULT1Flag = 1;
        break;
    case FAULT2:
        tmpt1=ioctl(fd_err,0,FAULT2);
        printf("###FAULT2 = %d\n",tmpt1);
        g_newfaultstatus.iFAULT2Flag = 1;
        break;
    case FAULT3:
        tmpt1=ioctl(fd_err,0,FAULT3);
        printf("###FAULT3 = %d\n",tmpt1);
        g_newfaultstatus.iFAULT3Flag = 1;
        break;
    case FAULT4:
        tmpt1=ioctl(fd_err,0,FAULT4);
        printf("###FAULT4 = %d\n",tmpt1);
        g_newfaultstatus.iFAULT4Flag = 1;
        break;
    case KEYCOL6:
        tmpt1=ioctl(fd_err,0,KEYCOL6);
        printf("###KEYCOL6 = %d\n",tmpt1);
        g_newfaultstatus.iKEYCOL6Flag = 1;
        break;
    default:
        break;
    }
#endif
}

//打开一个指定的PWM
void CMymainWindow::OpenOnePWM(int p,int freq)
{
#ifdef UBUNTU_DEV
    ioctl(fd_pwm,p,freq);
    if(p == 6)
        p = 2;
    printf("###OPEN IMX_PWM%d successed, freq = %dHz###\n",p,freq);
#endif
}

//关闭一个指定的PWM
void CMymainWindow::CloseOnePWM(int p)
{
#ifdef UBUNTU_DEV
    printf("###CLOSE IMX_PWM%d successed###\n",p);
    ioctl(fd_pwm,p,0);
#endif
}

//关闭所有的PWM
void CMymainWindow::CloseAllPWM()
{
#ifdef UBUNTU_DEV
    printf("###CLOSE IMX_PWM2~4 successed###\n");
    ioctl(fd_pwm,IMX_PWM2,0);
    ioctl(fd_pwm,IMX_PWM3,0);
    ioctl(fd_pwm,IMX_PWM4,0);
#endif
}

//单个IO置1
void CMymainWindow::OpenOneOutIO(int p)
{
#ifdef UBUNTU_DEV
   ioctl(fd_ioout,1,p);
#endif
}

//单个IO置0
void CMymainWindow::CloseOneOutIO(int p)
{
#ifdef UBUNTU_DEV
   ioctl(fd_ioout,0,p);
#endif
}

//0~100加载增益
void CMymainWindow::zyNstart_ad5292(int perc)
{
#ifdef UBUNTU_DEV
    int ret,tmp;
    unsigned char bf_cmd[2];
    ret = -1;
    bf_cmd[0] = 0x20;
    bf_cmd[1] = 0x00;
    ret = write(fd_ad5292,bf_cmd,2);
    if(ret < 0)
        printf("ad5292 write 0x2000 power on failed!\n");
    usleep(10);
    bf_cmd[0] = 0x18;
    bf_cmd[1] = 0x07;
    ret = write(fd_ad5292,bf_cmd,2);
    if(ret < 0)
        printf("ad5292 write 0x1807 set model failed!\n");
    usleep(10);
    tmp = 1023*perc/100;
    bf_cmd[0] = 0x04 + (tmp>>8);
    bf_cmd[1] = tmp&0xFF;
    qDebug()<<"bf_cmd[0]"<<bf_cmd[0]<<"bf_cmd[1]"<<bf_cmd[1];
    ret = write(fd_ad5292,bf_cmd,2);
    if(ret < 0)
        printf("ad5292 write zy load failed!\n");
    usleep(10);
#endif
}

void CMymainWindow::zyStop_ad5292()
{
#ifdef UBUNTU_DEV
    int ret;
    unsigned char bf_cmd[2];
    ret = -1;
    bf_cmd[0] = 0x20;
    bf_cmd[1] = 0x01;
    ret = write(fd_ad5292,bf_cmd,2);
    if(ret < 0)
        printf("ad5292 write 0x2001 power off failed!\n");
    usleep(10);
    bf_cmd[0] = 0x04;
    bf_cmd[1] = 0x00;
    ret = write(fd_ad5292,bf_cmd,2);
    if(ret < 0)
        printf("ad5292 write 0x0400 set zero failed!\n");
    usleep(10);
#endif
}

void CMymainWindow::ADData_show()
{
//   m_pUi->a01->setText(QString::number(m_pdataReadThread->ain01[0],'f',2));
//   m_pUi->a02->setText(QString::number(m_pdataReadThread->ain01[1],'f',2));
//   m_pUi->a03->setText(QString::number(m_pdataReadThread->ain01[2],'f',2));
//   m_pUi->a04->setText(QString::number(m_pdataReadThread->ain01[3],'f',2));
//   m_pUi->a05->setText(QString::number(m_pdataReadThread->ain01[4],'f',2));
//   m_pUi->a06->setText(QString::number(m_pdataReadThread->ain01[5],'f',2));
//   m_pUi->a07->setText(QString::number(m_pdataReadThread->ain01[6],'f',2));
//   m_pUi->a08->setText(QString::number(m_pdataReadThread->ain01[7],'f',2));

//   m_pUi->b01->setText(QString::number(m_pGPIORecvThread->ain02[0],'f',2));
//   m_pUi->b02->setText(QString::number(m_pGPIORecvThread->ain02[1],'f',2));
//   m_pUi->b03->setText(QString::number(m_pGPIORecvThread->ain02[2],'f',2));
//   m_pUi->b04->setText(QString::number(m_pGPIORecvThread->ain02[3],'f',2));
//   m_pUi->b05->setText(QString::number(m_pGPIORecvThread->ain02[4],'f',2));
//   m_pUi->b06->setText(QString::number(m_pGPIORecvThread->ain02[5],'f',2));
//   m_pUi->b07->setText(QString::number(m_pGPIORecvThread->ain02[6],'f',2));
//   m_pUi->b08->setText(QString::number(m_pGPIORecvThread->ain02[7],'f',2));

   m_pUi->a01->setText(QString::number(g_newaddata.fSlave1VolDC,'f',2));
   m_pUi->a02->setText(QString::number(g_newaddata.fSlave2VolDC,'f',2));
   m_pUi->a03->setText(QString::number(g_newaddata.fSlave3VolDC,'f',2));
   m_pUi->a04->setText(QString::number(g_newaddata.fSlave4VolDC,'f',2));
   m_pUi->a05->setText(QString::number(g_newaddata.fExcitVolt,'f',2));
   m_pUi->a06->setText(QString::number(g_newaddata.fCustom11,'f',2));
   m_pUi->a07->setText(QString::number(g_newaddata.fCustom12,'f',2));
   switch (m_pdataReadThread->m_bMuxOut)
   {
   case TPH_A:     //三相电A项直流
       m_pUi->a08->setText(QString::number(g_newaddata.fTriPhaseAVolDC,'f',2));
       break;
   case TPH_B:     //三相电B项直流
       m_pUi->a08->setText(QString::number(g_newaddata.fTriPhaseBVolDC,'f',2));
       break;
   case TPH_C:     //三相电C项直流
       m_pUi->a08->setText(QString::number(g_newaddata.fTriPhaseCVolDC,'f',2));
       break;
   default:
       break;
   }
   m_pUi->a08->setText(QString::number(g_newaddata.fTriPhaseAVolDC,'f',2));

   m_pUi->b01->setText(QString::number(g_newaddata.fTotalVolAC,'f',2));
   m_pUi->b02->setText(QString::number(g_newaddata.fTotalVolDC,'f',2));
   m_pUi->b03->setText(QString::number(g_newaddata.fSlave1CurDC,'f',2));
   m_pUi->b04->setText(QString::number(g_newaddata.fSlave2CurDC,'f',2));
   m_pUi->b05->setText(QString::number(g_newaddata.fSlave3CurDC,'f',2));
   m_pUi->b06->setText(QString::number(g_newaddata.fSlave4CurDC,'f',2));
   m_pUi->b07->setText(QString::number(g_newaddata.fTotalSlaveCurAC,'f',2));
   m_pUi->b08->setText(QString::number(g_newaddata.fExcitCur,'f',2));
}








//end add by zw 20220223
