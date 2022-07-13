#ifndef COMM_MACRO_H
#define COMM_MACRO_H

//#define WIN_DEV  //2019.01.18
#define UBUNTU_DEV
#define NEWCODE_SW //new code running switch by zw 20220223

#ifdef UBUNTU_DEV //Compiler Switch
#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <net/if.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <errno.h>
#endif          //Compiler Switch

#include "qmath.h"
#include <QString>

#ifndef PF_CAN
#define PF_CAN 29
#endif
#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif

typedef char  int8;
typedef short int16;
typedef int   int32;

#define iDATA_COUNT_MAX  60*60*10//曲线显示最大点数 add by 2020.09.05
//#define OTHER_ROLE_TYPE      0   //其他角色类型 add by 2020.08.15
//#define USER_ROLE_TYPE         1  //用户角色类型 add by 2020.08.15
//#define ADMIN_ROLE_TYPE       2  //管理员角色类型 add by 2020.08.15
#define OTHER_ROLE_TYPE      0   //其他角色类型 add by 2020.12.01
#define USER_ROLE_TYPE         4  //用户角色类型 add by 2020.12.01
#define ADMIN_ROLE_TYPE       6  //管理员角色类型 add by 2020.12.01
#define ENGINEER_ROLE_TYPE  5  //工程师角色类型 add by 2020.12.01

#define ROWS_PER_PAGE     100      //每页默认显示100行,add by 2019.07.14
#define TEST_FLAG         1        //测试标记,add by 2019.05.14
#define NOTEST_FLAG       0        //非测试态,add by 2019.05.14

#define HOME_PAGE_NUM     0
#define CONTROL_PAGE_NUM  1
#define STATUS_PAGE_NUM   2
#define SET_PAGE_NUM      3

#define  MAX_SIZE         16
#define  INTERVAL         1000

#define  MAX_RUNNING_TIME  qPow(2,32)  //系统最长累计运行时间(单位：秒)
#define  SOLE_ADJ_TYPE     1    //单一调节模式（类型）
#define  UNIFY_ADJ_TYPE    2    //统一调节模式（类型）

#define  NORMAL_MODE       1   //正常模式
#define  DEBUG_MODE        0   //调试模式

#define   IGBT_TEMPERATURE_TYPE   1 //IGBT温度类型
#define   IDCUT_TEMPERATURE_TYPE  2 //电感温度类型

#define SWITCH_INIT       -1  //连锁设置初始态
#define SWITCH_OFF        0   //连锁设置断开态
#define SWITCH_ON         1   //连锁设置关闭态

#define NORMAL_OPEN         0   //常开状态 add by 2020.09.03
#define NORMAL_CLOSE        1   //常闭状态 add by 2020.09.03

#define  CHINESE_LANG      0   //中文（语言类型）
#define  ENGLISH_LANG      1   //英文（语言类型）

#define  TOTAL_VOLT_TYPE    0  //总输出电压（数据类型）
#define  TOTAL_CURRENT_TYPE 1  //总输出电流（数据类型）
#define  EXCIT_VOLT_TYPE    2  //励磁电压（数据类型）
#define  EXCIT_CURRENT_TYPE 3  //励磁电流（数据类型）
#define  PHASE_AVOLT_TYPE   4  //A相电压（数据类型）
#define  PHASE_BVOLT_TYPE   5  //B相电压（数据类型）
#define  PHASE_CVOLT_TYPE   6  //C相电压（数据类型）
#define  DATA_TYPE_NUM      7

#define  OVER_LOW_PROC   0  //过低保护
#define  OVER_UP_PROC    1  //过高保护
#define  NOMAL_PROC2     2  //普通保护2
#define  NOMAL_PROC3     3  //普通保护3


#define read_address_version_00 0x00//version

//Panel LED OUTPUT
#define	write_address_80 0x80
#define	write_address_82 0x82
#define	write_address_84 0x84

//DO OUTPUT
#define write_address_00 0x00 //软件复位
#define write_address_02 0x02 //中断设置：1-中断使能；0-中断禁止
#define	write_address_0C 0x0C //冷却单元启停
#define	write_address_0E 0x0E //励磁继电器
#define	write_address_10 0x10 //D0自定义6
#define	write_address_12 0x12 //D0自定义5
#define	write_address_14 0x14 //D0自定义4

//write do
#define	write_address_16 0x16 //分柜0软启动
#define	write_address_18 0x18 //分柜0主继电器
#define	write_address_1A 0x1A //分柜1软启动
#define	write_address_1C 0x1C //分柜1主继电器
#define	write_address_1E 0x1E //分柜2软启动
#define	write_address_20 0x20 //分柜2主继电器
#define	write_address_22 0x22 //分柜3软启动
#define	write_address_24 0x24 //分柜3主继电器

#define write_address_5C  0x5C  //谱形增益设置
#define write_address_5E  0x5E  //数字谱型控制

//write data
#define	write_data_1  0x0001
#define	write_data_0  0x0000

//read DI
#define read_address_di_08 0x08//主柜DI状态
#define	read_address_di_0A 0x0A//分柜DI状态

//read AI
#define read_address_ai_26 0x26//励磁电压
#define	read_address_ai_28 0x28//励磁电流

#define	read_address_ai_2A 0x2A//三相电压A
#define	read_address_ai_2C 0x2C//三相电压B
#define read_address_ai_2E 0x2E//三相电压C

#define	read_address_ai_30 0x30//自定义11
#define	read_address_ai_32 0x32//从柜0电压
#define	read_address_ai_34 0x34//从柜1电压
#define	read_address_ai_36 0x36//从柜2电压
#define	read_address_ai_38 0x38//从柜3电压

#define	read_address_ai_3A 0x3A//从柜0电流
#define	read_address_ai_3C 0x3C//从柜1电流
#define	read_address_ai_3E 0x3E//从柜2电流
#define	read_address_ai_40 0x40//从柜3电流

#define	read_address_ai_42 0x42//从柜0母线电压
#define	read_address_ai_44 0x44//从柜1母线电压
#define	read_address_ai_46 0x46//从柜2母线电压
#define	read_address_ai_48 0x48//从柜3母线电压

#define	read_address_ai_4A 0x4A//从柜0正母线电压
#define	read_address_ai_4C 0x4C//从柜1正母线电压
#define	read_address_ai_4E 0x4E//从柜2正母线电压
#define read_address_ai_50 0x50//从柜3正母线电压

#define	read_address_ai_52 0x52//从柜0负母线电压
#define	read_address_ai_54 0x54//从柜1负母线电压
#define	read_address_ai_56 0x56//从柜2负母线电压
#define	read_address_ai_58 0x58//从柜3负母线电压

//internal AI
#define	read_address_ai_60 0x60//+5V电流
#define	read_address_ai_62 0x62//模拟地
#define	read_address_ai_64 0x64//+12V电压
#define	read_address_ai_66 0x66//-12V电压
#define	read_address_ai_68 0x68//模拟供电+5V电压
#define	read_address_ai_6A 0x6A//模拟地
#define	read_address_ai_6C 0x6C//采样率

#define FULL_DATA_ON   0xFFFF

#define RATIO   10.0    //放大倍数

#define CAN_ADDRESS_00  0x04002730
#define CAN_ADDRESS_01  0x04012730
#define CAN_ADDRESS_02  0x04022730
#define CAN_ADDRESS_03  0x04032730
#define CAN_ADDRESS_04  0x04042730
#define CAN_ADDRESS_05  0x04052730
#define CAN_ADDRESS_06  0x04062730
#define CAN_ADDRESS_07  0x04072730

#define PROC_SET_VOLT_UP   1000.0
#define PROC_SET_VOLT_LOW  0.0
#define PROC_SET_TEMPER_UP  150.0
#define PROC_SET_TEMPER_LOW -100.0
#define PROC_SET_CURRENT_UP  300.0
#define PROC_SET_CURRENT_LOW  -300.0
#define PROC_SET_VOLT_TYPE   0
#define PROC_SET_TEMPER_TYPE 1
#define BUS_VOLT_RATIO      81.0
#define THREE_VOLT_RATIO    -54.3
#define OUTPUT_CURRENT_RATIO  1000
#define EXCIT_CURRENT_RATIO  166.7
#define OUTPUT_VOLT_RATIO   132.4
#define EXCIT_VOLT_RATIO   41

/*校准系数参数相关*/
#define COMMON_K  1.00
#define COMMON_B  0.00
#define SELECT_FLAG  1    //选择标记，add by 2019.07.10
#define UNSELECT_FLAG  0   //不选择标记，add by 2019.07.10
#define APhaseVolt 2.0  //A相电压零点值
#define BPhaseVolt 2.0  //B相电压零点值
#define CPhaseVolt 2.0  //C相电压零点值

/*运行状态参数相关*/
#define Zerotime 0  //时间为0
#define Limittime 86400  //限制时间为1天时开始提示

/*保护设置参数相关*/
#define EXCIT_CURRENT_LIMIT  0.5       //励磁电流阈值（用于判断是否开路）
#define EXCIT_VOLTAGE_LIMIT  10.0      //励磁电压阈值（用于判断励磁指示灯亮灭）
#define BUS_VOLT_UP_LIMIT    600.0      //母线电压阀值上限
#define BUS_VOLT_DOWN_LIMIT  500.0      //母线电压阈值下限

#define THREE_VOLT_UP       418.0      //三相电压过高值
#define THREE_VOLT_DOWN     342.0      //三相电压过低值

#define TOTAL_VOLT_UP_LIMIT   350.0    //功放总输出电压上限值
#define TOTAL_CURRENT_UP_LIMIT 3400.0   //功放总输出电流上限值

#define BUS_VOLT_UNBALANCE       3.0      //正负母线电压差值大于3.0V
#define Threephase_VOLT_UNBALANCE    5.0    //三相电压不均衡度
#define OUTPUT_CURRENT_UP_LIMIT  850.0    //输出总输出电流上限值
#define OUTPUT_TOTAL_VOLTAGE_UP_LIMIT  350.0    //输出总输出电压上限值，add by 2020.08.21
#define OUTPUT_TOTAL_CURRENT_UP_LIMIT  3400.0    //输出总输出电流上限值，add by 2020.08.21

#define SUBCABOPEN_FLAG    1     //分柜接入标记,add by zqc 2019.06.02
#define SUBCABCLOSE_FLAG   0     //分柜断开标记,add by zqc 2019.06.02

#define DELT_FVALUE  0.01 //浮点数的差值

#define PROCESS_SECTION_NULL    0
#define PROCESS_SECTION_01      1  //S1
#define PROCESS_SECTION_02      2  //S2
#define PROCESS_SECTION_03      3  //S3
#define PROCESS_SECTION_04      4  //S4

#define DELAY_TIME         100        //处理延时时间默认100ms
#define CANDATA_INTERNAL   50        //CAN上送数据间隔默认50ms
#define WRITE_WAIT_TIME    40       //写操作等待时间默认40ms,add by zqc 2019.06.02
#define GAIN_SET_INTERVAL  20       //无极拖动滑块间隔时间默认20ms,add by zqc 2019.06.02

enum
{
    JJTJ_INTERRUPT_MASK,//紧急停机-中断屏蔽位
    HTGWY_INTERRUPT_MASK,//滑台过位移-中断屏蔽位
    ZDTGWY_INTERRUPT_MASK,//振动台过位移-中断屏蔽位
    HTDYW_INTERRUPT_MASK,//滑台低液位-中断屏蔽位
    SELFDEFINE1_INTERRUPT_MASK,//自定义1-中断屏蔽位
    HTQY_INTERRUPT_MASK,//滑台欠压-中断屏蔽位
    ZDTGW_INTERRUPT_MASK,//振动台过温-中断屏蔽位
    EZGWY_INTERRUPT_MASK,//耳轴过位移-中断屏蔽位
    GFRJBH_INTERRUPT_MASK,//功放热继保护-中断屏蔽位
    JYZCDY_INTERRUPT_MASK,//静压轴承低压-中断屏蔽位
    ZGMBH_INTERRUPT_MASK,//主柜门保护-中断屏蔽位
    XTLQDY_INTERRUPT_MASK,//系统冷却单元-中断屏蔽位
    HTQYW_INTERRUPT_MASK,//主柜整流桥过温-中断屏蔽位
    SELFDEFINE2_INTERRUPT_MASK,//自定义2-中断屏蔽位
    SELFDEFINE3_INTERRUPT_MASK,//自定义3-中断屏蔽位
    NULL_INTERRUPT_MASK, //无意义-中断屏蔽位
    SUBZLQGW_INTERRUPT_MASK,//从柜整流器过温-中断屏蔽位
    SUBMBH_INTERRUPT_MASK  //从柜门保护-中断屏蔽位
};
enum
{
    YLEFT_MODE,
    YRIGHT_MODE,
    YLEFTRIGHT_MODE
};
//状态记录结构体
typedef struct STRU_STATUSRECORD
{
    quint64 lTotaltime;  //总运行时间
    quint32 iSumtime;        //最后一次运行时长
}STRU_STATUSRECORD;
//总运行时间结构体
typedef struct STRU_TOTALRUNNING
{
    qint64 activeTime;             // 激活日期 add by 2020.11.17
    qint64 lSetCalendarDay;     // 设定自然日 add by 2020.11.17
    qint64 lSetValue;                // 设定值（单位：秒）
    //bool   IsActived;              // 是否激活标志
}STRU_TOTALRUNNING;

//故障状态数据结构体
typedef struct STRU_FAULTSTATUS
{
    int8 iOutovervoltFlag;    //输出过压
    int8 iDCovervoltFlag;     //输入直流过压
    int8 iDCundervoltFlag;    //输入直流欠压
    int8 iACcurrentwarnFlag;  //输出交流电流报警
    int8 iACcurrentprocFlag;  //输出交流电流保护
    int8 iIGBT1overtempFlag;  //IGBT过温保护
    int8 iIGBT2overtempFlag;  //备用1
    int8 iIndu1overtempFlag;  //电感过温保护
    int8 iIndu2overtempFlag;  //备用2
    int8 iDripulseblockFlag;  //驱动脉冲封锁
    int8 iDigspecinterFlag;   //备用3
    int8 iAnaspecampoverFlag; //备用4
    int8 iAnaspecfreqoverFlag;//备用5
    int8 iDigspecampoverFlag; //备用6
    int8 iDigspecfreqoverFlag;//备用7
    int8 iIGBT1driprocFlag;   //IGBT1驱动保护
    int8 iIGBT2driprocFlag;   //IGBT2驱动保护
    int8 iIGBT3driprocFlag;   //IGBT3驱动保护
    int8 iIGBT4driprocFlag;   //IGBT4驱动保护
    int8 iIGBT5driprocFlag;   //IGBT5驱动保护
    int8 iIGBT6driprocFlag;   //IGBT6驱动保护
    int8 iOutputvoltwarnFlag; //输出电压报警
}STRU_FAULTSTATUS;

//功率模块输入直流电压结构体
typedef struct STRU_INPUTDCVOLTAGEMONI
{
    float fINPUTDCVoltage;//输入直流电压
}STRU_INPUTDCVOLTAGEMONI;
//IGBT温度监控数据结构体
typedef struct STRU_IGBTTEMPERATUREMONI
{
    float fOUTPUTACCurrent;//输出交流电流
    float fIGBT1Temper; //IGBT温度1
    float fIGBT2Temper; //IGBT温度2
}STRU_IGBTTEMPERATUREMONI;
//电感温度监控数据结构体
typedef struct STRU_IDUCTTEMPERATUREMONI
{
    float fIDUCT1Temper;//电感温度1
    float fIDUCT2Temper;//电感温度2
    float fOUTPUTACVoltage;//输出交流电压
}STRU_IDUCTTEMPERATUREMONI;


//运行状态数据结构体
typedef struct STRU_RUNNINGSTATUS
{
    QString strTime;      //时间
    int8 iRestartprocFlag; //重启过程中
    int8 iNormaloperFlag;  //正常运行
    int8 iFaultProtFlag;   //故障保护中
    int8 iFaultlockFlag;   //故障闭锁
    int iProtectedTimes;  //已保护次数
    int8 iBlockpulseFlag;  //封锁脉冲
    int8 iRecstartsigFlag; //收到启动信号
    int8 iRecshutsigFlag;  //收到关机信号
    QString strOrigMsg;   //原始报文

}STRU_RUNNINGSTATUS;
//分柜系数结构体
typedef struct STRU_SLAVECOEFDATA
{
    float fVolt;
    float fCurrent;
    float fBusVolt;
}STRU_SLAVECOEFDATA;

//保护阈值参数结构体
typedef struct STRU_PROCVALUEDATA
{
    float fOutVoltLow;    //输出电压保护值(下限)
    float fOutVoltUp;     //输出电压保护值(上限)
    float fDCVoltOverLow; //直流电压过压保护值(下限)
    float fDCVoltOverUp;  //直流电压过压保护值(上限)
    float fCurrentProcVal;//输出电流值保护值
    float fCurrentWarnVal;//输出电流值报警值
    float fIGBTGW1;       //IGBT过温动作温度1
    float fIGBTGW2;       //IGBT过温动作温度2
    float fIDCUTGW1;      //电感过温动作温度1
    float fIDCUTGW2;      //电感过温动作温度2

}STRU_PROCVALUEDATA;
//连锁设置参数结构体
typedef struct STRU_CHAINSETDATA
{
     int iJjtjVal;   //紧急停机
     int iHtgwyVal;  //滑台过位移
     int iZdtgwyVal; //振动台过位移
     int iHtdywVal;  //滑台低液位
     int iHtqyVal; //滑台轴承低压
     int iZdtgwVal;  //振动台过温
     int iEzgwyVal;  //耳轴过位移
     int iGfrjbhVal; //功放热继保护
     int iJyzcdyVal; //静压轴承低压
     int iZgMenbVal; //主柜门保护
     int iSubMenbVal;//从柜门保护
     int iXtlqdyVal; //系统冷却单元
     int iHtqywVal; //主柜整流桥过温,add by 2019.05.25
     int iSubzlqgwVal;//从柜整流桥过温,add by 2019.05.25
     int iSelfdefineVal1; //自定义1,add by 2019.05.25
     int iSelfdefineVal2; //自定义2,add by 2019.05.25
     int iSelfdefineVal3; //自定义3,add by 2019.05.25
     int iSubyuliuPorcVal; //从柜预留保护,add by 2019.05.25

     int iSwitch_Jjtj;               //紧急停机触点切换  add by 2020.09.08
     int iSwitch_htgwy;          //滑台过位移触点切换 add by 2020.09.08
     int iSwitch_zdtgwy;        //振动台过位移触点切换 add by 2020.09.08
     int iSwitch_htdyw;         //滑台低液位触点切换 add by 2020.09.08
     int iSwitch_htqy;        //滑台轴承低压触点切换 add by 2020.09.08
     int iSwitch_zdtgw;        //振动台过温触点切换 add by 2020.09.08
     int iSwitch_ezgwy;        //耳轴过位移触点切换 add by 2020.09.08
     int iSwitch_gfrjbh;         //功放热继保护触点切换 add by 2020.09.08
     int iSwitch_jyzcdy;        //静压轴承低压触点切换 add by 2020.09.08
     int iSwitch_zgmenbh;    //主柜门保护触点切换 add by 2020.09.08
     int iSwitch_htgw;  //从柜门保护触点切换 add by 2020.09.08
     int iSwitch_xtlqdy;          //系统冷却单元触点切换 add by 2020.09.08
     int iSwitch_htqyw;      //主柜整流器过温触点切换 add by 2020.09.08
     int iSwitch_subzlqgw;    //从柜整流器过温触点切换 add by 2020.09.08
     int iSwitch_selfdefine1;  //自定义1保护触点切换 add by 2020.09.08
     int iSwitch_selfdefine2;  //自定义2保护触点切换 add by 2020.09.08
     int iSwitch_selfdefine3;  //自定义3保护触点切换 add by 2020.09.08
     int iSwitch_subyuliu;       //从柜预留保护触点切换 add by 2020.09.08

}STRU_CHAINSETDATA;

//基本参数结构体,add by 2019.05.16
typedef struct STRU_BASICPARA
{
   float fVoltimbalance;      //三相电压不平衡，默认值5%
   float fThreevoltUp;        //三相电压过高，默认值418.0V
   float fThreevoltLow;       //三相电压过低，默认值342.0V
   float fTotalvoltUp;        //功放总输出电压过高，默认值350.0V
   float fTotalcurrentUp;     //功放总输出电流过高，默认值3400.0A
   float fBusvoltUp;          //母线电压过高，默认值600.0V
   float fBusvoltLow;         //母线电压过低，默认值500.0V
   float fBusImbalance;       //母线电压不均衡，默认值3.0V
   float fSub1CabinetcurrentUp;//分柜1输出电流过高，默认值850.0A
   float fSub2CabinetcurrentUp;//分柜2输出电流过高，默认值850.0A
   float fSub3CabinetcurrentUp;//分柜3输出电流过高，默认值850.0A
   float fSub4CabinetcurrentUp;//分柜4输出电流过高，默认值850.0A
   int   iSub1CabOpen;        //分柜1接入标记，1-接入；0-断开；add by zqc 2019.06.02
   int   iSub2CabOpen;        //分柜2接入标记，1-接入；0-断开；add by zqc 2019.06.02
   int   iSub3CabOpen;        //分柜3接入标记，1-接入；0-断开；add by zqc 2019.06.02
   int   iSub4CabOpen;        //分柜4接入标记，1-接入；0-断开；add by zqc 2019.06.02
}STRU_BASICPARA;

//校准数据结构体

typedef struct STRU_ADJVALUE
{
    float fZeroTotalvalue[25];
    float fTotalvalue[25];
    float fAdjvalue[25];
}STRU_ADJVALUE;
//校准系数结构体
typedef struct STRU_ADJCOEF
{
    float fSub1voltK;
    float fSub1voltB;
    float fSub1ActvoltK;
    float fSub1ActvoltB;
    float fSub1negvoltK;
    float fSub1negvoltB;
    float fSub1outvoltK;
    float fSub1outvoltB;
    float fSub1outcurrK;
    float fSub1outcurrB;

    float fSub2voltK;
    float fSub2voltB;
    float fSub2ActvoltK;
    float fSub2ActvoltB;
    float fSub2negvoltK;
    float fSub2negvoltB;
    float fSub2outvoltK;
    float fSub2outvoltB;
    float fSub2outcurrK;
    float fSub2outcurrB;

    float fSub3voltK;
    float fSub3voltB;
    float fSub3ActvoltK;
    float fSub3ActvoltB;
    float fSub3negvoltK;
    float fSub3negvoltB;
    float fSub3outvoltK;
    float fSub3outvoltB;
    float fSub3outcurrK;
    float fSub3outcurrB;

    float fSub4voltK;
    float fSub4voltB;
    float fSub4ActvoltK;
    float fSub4ActvoltB;
    float fSub4negvoltK;
    float fSub4negvoltB;
    float fSub4outvoltK;
    float fSub4outvoltB;
    float fSub4outcurrK;
    float fSub4outcurrB;

    float fMAvoltK;
    float fMAvoltB;
    float fMBvoltK;
    float fMBvoltB;
    float fMCvoltK;
    float fMCvoltB;
    float fMEvoltK;
    float fMEvoltB;
    float fMEcurrK;
    float fMEcurrB;
}STRU_ADJCOEF;
//校准框勾选结构体
typedef struct STRU_ADJCHECK
{
    int iS1bvCabOpen;//分柜1母线电压校准接入标志，1-接入，0-断开
    int iS1abvCabOpen;//分柜1正母线电压校准接入标志，1-接入，0-断开
    int iS1nbvCabOpen;//分柜1负母线电压校准接入标志，1-接入，0-断开
    int iS1ovCabOpen;//分柜1输出电压校准接入标志，1-接入，0-断开
    int iS1ocCabOpen;//分柜1输出电流校准接入标志，1-接入，0-断开

    int iS2bvCabOpen;//分柜2母线电压校准接入标志，1-接入，0-断开
    int iS2abvCabOpen;//分柜2正母线电压校准接入标志，1-接入，0-断开
    int iS2nbvCabOpen;//分柜2负母线电压校准接入标志，1-接入，0-断开
    int iS2ovCabOpen;//分柜2输出电压校准接入标志，1-接入，0-断开
    int iS2ocCabOpen;//分柜2输出电流校准接入标志，1-接入，0-断开

    int iS3bvCabOpen;//分柜3母线电压校准接入标志，1-接入，0-断开
    int iS3abvCabOpen;//分柜3正母线电压校准接入标志，1-接入，0-断开
    int iS3nbvCabOpen;//分柜3负母线电压校准接入标志，1-接入，0-断开
    int iS3ovCabOpen;//分柜3输出电压校准接入标志，1-接入，0-断开
    int iS3ocCabOpen;//分柜3输出电流校准接入标志，1-接入，0-断开

    int iS4bvCabOpen;//分柜4母线电压校准接入标志，1-接入，0-断开
    int iS4abvCabOpen;//分柜4正母线电压校准接入标志，1-接入，0-断开
    int iS4nbvCabOpen;//分柜4负母线电压校准接入标志，1-接入，0-断开
    int iS4ovCabOpen;//分柜4输出电压校准接入标志，1-接入，0-断开
    int iS4ocCabOpen;//分柜4输出电流校准接入标志，1-接入，0-断开

    int iMAvCabOpen;//主柜A相电压校准接入标志，1-接入，0-断开
    int iMBvCabOpen;//主柜B相电压校准接入标志，1-接入，0-断开
    int iMCvCabOpen;//主柜C相电压校准接入标志，1-接入，0-断开
    int iMevCabOpen;//主柜励磁电压校准接入标志，1-接入，0-断开
    int iMecCabOpen;//主柜励磁电流校准接入标志，1-接入，0-断开

    int iS1CabOpen;//从柜1校准接入标志，1-接入，0-断开
    int iS2CabOpen;//从柜2校准接入标志，1-接入，0-断开
    int iS3CabOpen;//从柜3校准接入标志，1-接入，0-断开
    int iS4CabOpen;//从柜4校准接入标志，1-接入，0-断开
    int iMainCabOpen;//主柜校准接入标志，1-接入，0-断开
    int iAllCabOpen;//全部校准接入标志，1-接入，0-断开
}STRU_ADJCHECK;
//校准勾选计数器结构体
typedef struct STR_ADJCHECKNUM
{
    int m_nAllcheckCnt;
    int m_nS1checkCnt;
    int m_nS2checkCnt;
    int m_nS3checkCnt;
    int m_nS4checkCnt;
    int m_nMcheckCnt;
    int m_nRcheckCnt;
}STR_ADJCHECKNUM;
typedef struct STR_GPIODATA
{
    int8   iMasterDI[16];
    int8   iSlaveDI[16];
    int8   iRunningState;       //运行状态
    int8   iCoolingState;       //冷却状态
    int8   iExcitationState;    //励磁状态
    int8   iReadyState;         //准备状态
    int8   iGainState;          //增益状态
    int8   iFaultState;         //故障状态
    float fTotalVolt;          //总输出电压(4个分柜电压均值)
    float fTotalCurrent;       //总输出电流(4个分柜电流求和)
    float fExcitVolt;          //励磁电压
    float fExcitCurrent;       //励磁电流
    float fPhaseAVolt;         //A相电压
    float fPhaseBVolt;         //B相电压
    float fPhaseCVolt;         //C相电压
    float fSlaveVolt[4];       //从柜电压;
    float fSlaveCurrent[4];    //从柜电流;
    float fSlaveBusVolt[4];    //从柜母线电压(即正负母线电压);
    float fSlaveActBusVolt[4]; //从柜正母线电压;
    float fSlaveNegBusVolt[4]; //从柜负母线电压;
    int8 iSlaveStaValue[4];   //从柜运行状态值
}STR_GPIODATA;

//状态记录信息结构体，add by zqc 2019.07.13
typedef struct STR_STATUSDATA
{
    QString strAlarmTime;    //报警时间
    QString strErrorType;    //错误类型
    float   fVoltRms;        //输出电压有效值(V)
    float   fVoltMax;        //输出电压最大值(V)
    float   fCurrentRms;     //输出电流有效值(A)
    float   fCurrentMax;     //输出电流最大值(A)
}STR_STATUSDATA;

typedef struct STRU_SIMUPROCSET
{
    float fSimuPhaseAVolt;         //模拟-A相电压
    float fSimuPhaseBVolt;         //模拟-B相电压
    float fSimuPhaseCVolt;         //模拟-C相电压
    float fSimuBusVolt;            //模拟-母线电压,add by 2019.05.25
    float fSimuExcitCurrent;       //模拟-励磁电流,add by 2019.05.25
     bool isSimuFlag;              //是否模拟标记，add by 2019.05.25
}STRU_SIMUPROCSET;

//add by zw 20220223
//IO_OUT
#define COOLING         0
#define FIELD           1
#define FAN             2
#define HB              3
#define MUX_A0          4
#define MUX_A1          5
#define MUX_A2          6
#define MUX_A3          7
#define K1_0            8
#define K1_1            9
#define K2_0            10
#define K2_1            11
#define K3_0            12
#define K3_1            13
#define K4_0            14
#define K4_1            15
#define RUN             16
#define CUS12EN         17
#define AD01_CA         18
#define ST              19
#define EXT21           20

//ERR_INPUT
#define VIBOD         0
#define VIBCU         1
#define VIBOT         2
#define STOD          3
#define STUP          4
#define STOT          5
#define STOL          6
#define RELAY         7
#define DOOR          8
#define HBUP          9
#define EXT1          10
#define EXT2          11
#define EXT3          12
#define EXT4          13
#define ESTOP         14
#define OT1           15
#define OT2           16
#define OT3           17
#define OT4           18
#define SESTOP        19
#define FAULT1        20
#define FAULT2        21
#define FAULT3        22
#define FAULT4        23
#define KEYCOL6       24

//PWM
#define IMX_PWM2      6
#define IMX_PWM3      3
#define IMX_PWM4      4

//TriPhase
#define TPH_A         0
#define TPH_B         1
#define TPH_C         2

//AD ratio
#define ADK100  1.0
#define ADK101  1.0
#define ADK102  1.0
#define ADK103  1.0
#define ADK104  1.0
#define ADK105  1.0
#define ADK106  1.0
#define ADK107A 1.0
#define ADK107B 1.0
#define ADK107C 1.0

#define ADK200  1.0
#define ADK201  100.0
#define ADK202  1.0
#define ADK203  1.0
#define ADK204  1.0
#define ADK205  1.0
#define ADK206  1.0
#define ADK207  1.0





//新版主控内外部错误信号结构体
typedef struct STRU_NEWFAULTSTATUS
{

    int8 iVIBODFlag;        //振动台过位移
    int8 iVIBCUFlag;        //振动台冷却故障
    int8 iVIBOTFlag;        //振动过温
    int8 iSTODFlag;         //滑台过位移保护
    int8 iSTUPFlag;         //滑台欠压
    int8 iSTOTFlag;         //滑台过温
    int8 iSTOLFlag;         //滑台欠液位
    int8 iRELAYFlag;        //功放热继保护
    int8 iDOORFlag;         //门保护
    int8 iHBUPFlag;         //静压轴承欠压
    int8 iEXT1Flag;         //自定义1
    int8 iEXT2Flag;         //自定义2
    int8 iEXT3Flag;         //自定义3
    int8 iEXT4Flag;         //自定义4
    int8 iESTOPFlag;        //紧急停机
    int8 iOT1Flag;          //从柜1整流桥过温1
    int8 iOT2Flag;          //从柜1整流桥过温2
    int8 iOT3Flag;          //从柜1整流桥过温3
    int8 iOT4Flag;          //从柜1整流桥过温4
    int8 iSESTOPFlag;       //S紧急停机
    int8 iFAULT1Flag;       //从柜1错误信号
    int8 iFAULT2Flag;       //从柜2错误信号
    int8 iFAULT3Flag;       //从柜3错误信号
    int8 iFAULT4Flag;       //从柜4错误信号
    int8 iKEYCOL6Flag;      //VOL- for test
    int8 iFaultValue[25];   //错入输入IO值

}STRU_NEWFAULTSTATUS;

typedef struct STRU_ADDATANEW
{

    float fTriPhaseAVolDC;     //三相电A项直流
    float fTriPhaseBVolDC;     //三相电B项直流
    float fTriPhaseCVolDC;     //三相电C项直流
    float fExcitVolt;          //励磁电压直流
    float fExcitCur;           //励磁电流直流

    float fSlave1VolDC;        //从柜1母线电压直流
    float fSlave1CurDC;        //从柜1电流直流
    float fSlave2VolDC;        //从柜2母线电压直流
    float fSlave2CurDC;        //从柜2电流直流

    float fSlave3VolDC;        //从柜3母线电压直流
    float fSlave3CurDC;        //从柜3电流直流
    float fSlave4VolDC;        //从柜4母线电压直流
    float fSlave4CurDC;        //从柜4电流直流

    float fTotalVolAC;         //总电压交流
    float fTotalVolDC;         //总电压直流
    float fTotalSlaveCurAC;    //从柜总电流交流
    float fCustom11;           //外部预留11
    float fCustom12;           //外部预留12

    int8   iRunningState;       //运行状态
    int8   iCoolingState;       //冷却状态
    int8   iExcitationState;    //励磁状态
    int8   iReadyState;         //准备状态
    int8   iGainState;          //增益状态
    int8   iFaultState;         //故障状态
    int8   iSlaveStaValue[4];   //从柜运行状态值

}STRU_ADDATANEW;

//新校准系数结构体
typedef struct STRU_NEWADJCOEF
{
    //三相电A直流
    float fTriPhaseAVolDCK;
    float fTriPhaseAVolDCB;
    //三相电B直流
    float fTriPhaseBVolDCK;
    float fTriPhaseBVolDCB;
    //三相电C直流
    float fTriPhaseCVolDCK;
    float fTriPhaseCVolDCB;
    //励磁电压直流
    float fExcitVoltK;
    float fExcitVoltB;
    //励磁电流直流
    float fExcitCurK;
    float fExcitCurB;
    //从柜1电压直流
    float fSlave1VolDCK;
    float fSlave1VolDCB;
    //从柜1电流直流
    float fSlave1CurDCK;
    float fSlave1CurDCB;
    //从柜2电压直流
    float fSlave2VolDCK;
    float fSlave2VolDCB;
    //从柜2电流直流
    float fSlave2CurDCK;
    float fSlave2CurDCB;
    //从柜3电压直流
    float fSlave3VolDCK;
    float fSlave3VolDCB;
    //从柜3电流直流
    float fSlave3CurDCK;
    float fSlave3CurDCB;
    //从柜4电压直流
    float fSlave4VolDCK;
    float fSlave4VolDCB;
    //从柜4电流直流
    float fSlave4CurDCK;
    float fSlave4CurDCB;
    //总电压交流
    float fTotalVolACK;
    float fTotalVolACB;
    //总电压直流
    float fTotalVolDCK;
    float fTotalVolDCB;
    //从柜总电流交流
    float fTotalSlaveCurACK;
    float fTotalSlaveCurACB;
    //外部预留11
    float fCustom11K;
    float fCustom11B;
    //外部预留12
    float fCustom12K;
    float fCustom12B;
}STRU_NEWADJCOEF;
//校准框勾选结构体

//新校准勾选计数器结构体
typedef struct STRU_NEWADCKNUM
{
    int m_nAllcheckCnt;
    int m_nMcheckCnt;
    int m_nS12checkCnt;
    int m_nS34checkCnt;
    int m_nSALLcheckCnt;
}STRU_NEWADCKNUM;

typedef struct STRU_NEWADCK
{
   int iMAvOpen; //主柜三相电A
   int iMBvOpen; //主柜三相电B
   int iMCvOpen; //主柜三相电C
   int iEvOpen;  //主柜励磁电压
   int iEcOpen;  //主柜励磁电压

   int iS1vOpen; //从柜1电压
   int iS1cOpen; //从柜1电流
   int iS2vOpen; //从柜2电压
   int iS2cOpen; //从柜2电流

   int iS3vOpen; //从柜3电压
   int iS3cOpen; //从柜3电流
   int iS4vOpen; //从柜4电压
   int iS4cOpen; //从柜4电流

   int iSAvacOpen; //从柜总电压AC
   int iSAvdcOpen; //从柜总电压DC
   int iSAcacOpen; //从柜总电流AC
   int iCus1Open; //预留1
   int iCus2Open; //预留2

   int iMainOpen; //主柜
   int iS12Open; //从柜12
   int iS34Open; //从柜34
   int iSAllOpen; //从柜总
   int iAllOpen; //所有

}STRU_NEWADCK;

typedef struct STR_NEWADJVALUE
{
    float fZeroValue[18];
    float fShowValue[18];
    float fRealValue[18];
}STR_NEWADJVALUE;

//新连锁设置参数结构体
typedef struct STRU_NEWCHASETDATA
{
     int iJjtjVal;      //紧急停机
     int iSJitiVal;     //S紧急停机
     int iXtlqVal;      //系统冷却
     int iZdtgwVal;     //振动台过温
     int iZdtgwyVal;    //振动台过位移
     int iHtgwyVal;     //滑台过位移
     int iHtqyVal;      //滑台欠压
     int iHtqywVal;     //滑台欠液位
     int iHtgwVal;      //滑台过温
     int iGfrjbhVal;    //功放热继保护
     int iJyzcdyVal;    //静压轴承低压
     int iZgmbhVal;     //主柜门保护
     int iSelfdefVal1;  //自定义1
     int iSelfdefVal2;  //自定义2
     int iSelfdefVal3;  //自定义3
     int iSelfdefVal4;  //自定义4
     int iC1zlqgwVal;  //从柜1整流器过温
     int iC2zlqgwVal;  //从柜2整流器过温
     int iC3zlqgwVal;  //从柜3整流器过温
     int iC4zlqgwVal;  //从柜4整流器过温
     int iC1cwbhVal;  //从柜1错误保护
     int iC2cwbhVal;  //从柜2错误保护
     int iC3cwbhVal;  //从柜3错误保护
     int iC4cwbhVal;  //从柜4错误保护

     int isw_Jjtj;      //紧急停机触电切换
     int isw_SJiti;     //S紧急停机触电切换
     int isw_Xtlq;      //系统冷却触电切换
     int isw_Zdtgw;     //振动台过温触电切换
     int isw_Zdtgwy;    //振动台过位移触电切换
     int isw_Htgwy;     //滑台过位移触电切换
     int isw_Htqy;      //滑台欠压触电切换
     int isw_Htqyw;     //滑台欠液位触电切换
     int isw_Htgw;      //滑台过温触电切换
     int isw_Gfrjbh;    //功放热继保护触电切换
     int isw_Jyzcdy;    //静压轴承低压触电切换
     int isw_Zgmbh;     //主柜门保护触电切换
     int isw_Selfdef1;  //自定义1触电切换
     int isw_Selfdef2;  //自定义2触电切换
     int isw_Selfdef3;  //自定义3触电切换
     int isw_Selfdef4;  //自定义4触电切换
     int isw_C1zlqgw;   //从柜1整流器过温触电切换
     int isw_C2zlqgw;   //从柜2整流器过温触电切换
     int isw_C3zlqgw;   //从柜3整流器过温触电切换
     int isw_C4zlqgw;   //从柜4整流器过温触电切换
     int isw_C1cwbh;    //从柜1错误保护触电切换
     int isw_C2cwbh;    //从柜2错误保护触电切换
     int isw_C3cwbh;    //从柜3错误保护触电切换
     int isw_C4cwbh;    //从柜4错误保护触电切换
}STRU_NEWCHASETDATA;
enum
{


    JJTJ_MASK,      //紧急停机-中断屏蔽位
    SJJTJ_MASK,     //S紧急停机-中断屏蔽位
    XTLQ_MASK,      //系统冷却-中断屏蔽位
    ZDTGW_MASK,     //振动台过温-中断屏蔽位
    ZDTGWY_MASK,    //振动台过位移-中断屏蔽位
    HTGWY_MASK,     //滑台过位移-中断屏蔽位
    HTQY_MASK,      //滑台欠压-中断屏蔽位
    HTQYW_MASK,     //滑台欠液位-中断屏蔽位
    HTGW_MASK,      //滑台过温-中断屏蔽位
    GFRJBH_MASK,    //功放热继保护-中断屏蔽位
    JYZCDY_MASK,    //静压轴承低压-中断屏蔽位
    ZGMBH_MASK,     //主柜门保护-中断屏蔽位
    ZDY1_MASK,      //自定义1-中断屏蔽位
    ZDY2_MASK,      //自定义2-中断屏蔽位
    ZDY3_MASK,      //自定义3-中断屏蔽位
    ZDY4_MASK,      //自定义4-中断屏蔽位
    CG1ZLQGW_MASK,  //从柜1整流器过温-中断屏蔽位
    CG2ZLQGW_MASK,  //从柜2整流器过温-中断屏蔽位
    CG3ZLQGW_MASK,  //从柜3整流器过温-中断屏蔽位
    CG4ZLQGW_MASK,  //从柜4整流器过温-中断屏蔽位
    CG1CWBH_MASK,   //从柜1错误保护-中断屏蔽位
    CG2CWBH_MASK,   //从柜2错误保护-中断屏蔽位
    CG3CWBH_MASK,   //从柜3错误保护-中断屏蔽位
    CG4CWBH_MASK,   //从柜4错误保护-中断屏蔽位
};
#define LED_GREEN        1
#define LED_RED          0
#define LED_YELLOW      -1

//end add by zw 20220223

#endif//COMM_MACRO_H
