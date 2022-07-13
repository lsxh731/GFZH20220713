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

#define iDATA_COUNT_MAX  60*60*10//������ʾ������ add by 2020.09.05
//#define OTHER_ROLE_TYPE      0   //������ɫ���� add by 2020.08.15
//#define USER_ROLE_TYPE         1  //�û���ɫ���� add by 2020.08.15
//#define ADMIN_ROLE_TYPE       2  //����Ա��ɫ���� add by 2020.08.15
#define OTHER_ROLE_TYPE      0   //������ɫ���� add by 2020.12.01
#define USER_ROLE_TYPE         4  //�û���ɫ���� add by 2020.12.01
#define ADMIN_ROLE_TYPE       6  //����Ա��ɫ���� add by 2020.12.01
#define ENGINEER_ROLE_TYPE  5  //����ʦ��ɫ���� add by 2020.12.01

#define ROWS_PER_PAGE     100      //ÿҳĬ����ʾ100��,add by 2019.07.14
#define TEST_FLAG         1        //���Ա��,add by 2019.05.14
#define NOTEST_FLAG       0        //�ǲ���̬,add by 2019.05.14

#define HOME_PAGE_NUM     0
#define CONTROL_PAGE_NUM  1
#define STATUS_PAGE_NUM   2
#define SET_PAGE_NUM      3

#define  MAX_SIZE         16
#define  INTERVAL         1000

#define  MAX_RUNNING_TIME  qPow(2,32)  //ϵͳ��ۼ�����ʱ��(��λ����)
#define  SOLE_ADJ_TYPE     1    //��һ����ģʽ�����ͣ�
#define  UNIFY_ADJ_TYPE    2    //ͳһ����ģʽ�����ͣ�

#define  NORMAL_MODE       1   //����ģʽ
#define  DEBUG_MODE        0   //����ģʽ

#define   IGBT_TEMPERATURE_TYPE   1 //IGBT�¶�����
#define   IDCUT_TEMPERATURE_TYPE  2 //����¶�����

#define SWITCH_INIT       -1  //�������ó�ʼ̬
#define SWITCH_OFF        0   //�������öϿ�̬
#define SWITCH_ON         1   //�������ùر�̬

#define NORMAL_OPEN         0   //����״̬ add by 2020.09.03
#define NORMAL_CLOSE        1   //����״̬ add by 2020.09.03

#define  CHINESE_LANG      0   //���ģ��������ͣ�
#define  ENGLISH_LANG      1   //Ӣ�ģ��������ͣ�

#define  TOTAL_VOLT_TYPE    0  //�������ѹ���������ͣ�
#define  TOTAL_CURRENT_TYPE 1  //������������������ͣ�
#define  EXCIT_VOLT_TYPE    2  //���ŵ�ѹ���������ͣ�
#define  EXCIT_CURRENT_TYPE 3  //���ŵ������������ͣ�
#define  PHASE_AVOLT_TYPE   4  //A���ѹ���������ͣ�
#define  PHASE_BVOLT_TYPE   5  //B���ѹ���������ͣ�
#define  PHASE_CVOLT_TYPE   6  //C���ѹ���������ͣ�
#define  DATA_TYPE_NUM      7

#define  OVER_LOW_PROC   0  //���ͱ���
#define  OVER_UP_PROC    1  //���߱���
#define  NOMAL_PROC2     2  //��ͨ����2
#define  NOMAL_PROC3     3  //��ͨ����3


#define read_address_version_00 0x00//version

//Panel LED OUTPUT
#define	write_address_80 0x80
#define	write_address_82 0x82
#define	write_address_84 0x84

//DO OUTPUT
#define write_address_00 0x00 //�����λ
#define write_address_02 0x02 //�ж����ã�1-�ж�ʹ�ܣ�0-�жϽ�ֹ
#define	write_address_0C 0x0C //��ȴ��Ԫ��ͣ
#define	write_address_0E 0x0E //���ż̵���
#define	write_address_10 0x10 //D0�Զ���6
#define	write_address_12 0x12 //D0�Զ���5
#define	write_address_14 0x14 //D0�Զ���4

//write do
#define	write_address_16 0x16 //�ֹ�0������
#define	write_address_18 0x18 //�ֹ�0���̵���
#define	write_address_1A 0x1A //�ֹ�1������
#define	write_address_1C 0x1C //�ֹ�1���̵���
#define	write_address_1E 0x1E //�ֹ�2������
#define	write_address_20 0x20 //�ֹ�2���̵���
#define	write_address_22 0x22 //�ֹ�3������
#define	write_address_24 0x24 //�ֹ�3���̵���

#define write_address_5C  0x5C  //������������
#define write_address_5E  0x5E  //�������Ϳ���

//write data
#define	write_data_1  0x0001
#define	write_data_0  0x0000

//read DI
#define read_address_di_08 0x08//����DI״̬
#define	read_address_di_0A 0x0A//�ֹ�DI״̬

//read AI
#define read_address_ai_26 0x26//���ŵ�ѹ
#define	read_address_ai_28 0x28//���ŵ���

#define	read_address_ai_2A 0x2A//�����ѹA
#define	read_address_ai_2C 0x2C//�����ѹB
#define read_address_ai_2E 0x2E//�����ѹC

#define	read_address_ai_30 0x30//�Զ���11
#define	read_address_ai_32 0x32//�ӹ�0��ѹ
#define	read_address_ai_34 0x34//�ӹ�1��ѹ
#define	read_address_ai_36 0x36//�ӹ�2��ѹ
#define	read_address_ai_38 0x38//�ӹ�3��ѹ

#define	read_address_ai_3A 0x3A//�ӹ�0����
#define	read_address_ai_3C 0x3C//�ӹ�1����
#define	read_address_ai_3E 0x3E//�ӹ�2����
#define	read_address_ai_40 0x40//�ӹ�3����

#define	read_address_ai_42 0x42//�ӹ�0ĸ�ߵ�ѹ
#define	read_address_ai_44 0x44//�ӹ�1ĸ�ߵ�ѹ
#define	read_address_ai_46 0x46//�ӹ�2ĸ�ߵ�ѹ
#define	read_address_ai_48 0x48//�ӹ�3ĸ�ߵ�ѹ

#define	read_address_ai_4A 0x4A//�ӹ�0��ĸ�ߵ�ѹ
#define	read_address_ai_4C 0x4C//�ӹ�1��ĸ�ߵ�ѹ
#define	read_address_ai_4E 0x4E//�ӹ�2��ĸ�ߵ�ѹ
#define read_address_ai_50 0x50//�ӹ�3��ĸ�ߵ�ѹ

#define	read_address_ai_52 0x52//�ӹ�0��ĸ�ߵ�ѹ
#define	read_address_ai_54 0x54//�ӹ�1��ĸ�ߵ�ѹ
#define	read_address_ai_56 0x56//�ӹ�2��ĸ�ߵ�ѹ
#define	read_address_ai_58 0x58//�ӹ�3��ĸ�ߵ�ѹ

//internal AI
#define	read_address_ai_60 0x60//+5V����
#define	read_address_ai_62 0x62//ģ���
#define	read_address_ai_64 0x64//+12V��ѹ
#define	read_address_ai_66 0x66//-12V��ѹ
#define	read_address_ai_68 0x68//ģ�⹩��+5V��ѹ
#define	read_address_ai_6A 0x6A//ģ���
#define	read_address_ai_6C 0x6C//������

#define FULL_DATA_ON   0xFFFF

#define RATIO   10.0    //�Ŵ���

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

/*У׼ϵ���������*/
#define COMMON_K  1.00
#define COMMON_B  0.00
#define SELECT_FLAG  1    //ѡ���ǣ�add by 2019.07.10
#define UNSELECT_FLAG  0   //��ѡ���ǣ�add by 2019.07.10
#define APhaseVolt 2.0  //A���ѹ���ֵ
#define BPhaseVolt 2.0  //B���ѹ���ֵ
#define CPhaseVolt 2.0  //C���ѹ���ֵ

/*����״̬�������*/
#define Zerotime 0  //ʱ��Ϊ0
#define Limittime 86400  //����ʱ��Ϊ1��ʱ��ʼ��ʾ

/*�������ò������*/
#define EXCIT_CURRENT_LIMIT  0.5       //���ŵ�����ֵ�������ж��Ƿ�·��
#define EXCIT_VOLTAGE_LIMIT  10.0      //���ŵ�ѹ��ֵ�������ж�����ָʾ������
#define BUS_VOLT_UP_LIMIT    600.0      //ĸ�ߵ�ѹ��ֵ����
#define BUS_VOLT_DOWN_LIMIT  500.0      //ĸ�ߵ�ѹ��ֵ����

#define THREE_VOLT_UP       418.0      //�����ѹ����ֵ
#define THREE_VOLT_DOWN     342.0      //�����ѹ����ֵ

#define TOTAL_VOLT_UP_LIMIT   350.0    //�����������ѹ����ֵ
#define TOTAL_CURRENT_UP_LIMIT 3400.0   //�����������������ֵ

#define BUS_VOLT_UNBALANCE       3.0      //����ĸ�ߵ�ѹ��ֵ����3.0V
#define Threephase_VOLT_UNBALANCE    5.0    //�����ѹ�������
#define OUTPUT_CURRENT_UP_LIMIT  850.0    //����������������ֵ
#define OUTPUT_TOTAL_VOLTAGE_UP_LIMIT  350.0    //����������ѹ����ֵ��add by 2020.08.21
#define OUTPUT_TOTAL_CURRENT_UP_LIMIT  3400.0    //����������������ֵ��add by 2020.08.21

#define SUBCABOPEN_FLAG    1     //�ֹ������,add by zqc 2019.06.02
#define SUBCABCLOSE_FLAG   0     //�ֹ�Ͽ����,add by zqc 2019.06.02

#define DELT_FVALUE  0.01 //�������Ĳ�ֵ

#define PROCESS_SECTION_NULL    0
#define PROCESS_SECTION_01      1  //S1
#define PROCESS_SECTION_02      2  //S2
#define PROCESS_SECTION_03      3  //S3
#define PROCESS_SECTION_04      4  //S4

#define DELAY_TIME         100        //������ʱʱ��Ĭ��100ms
#define CANDATA_INTERNAL   50        //CAN�������ݼ��Ĭ��50ms
#define WRITE_WAIT_TIME    40       //д�����ȴ�ʱ��Ĭ��40ms,add by zqc 2019.06.02
#define GAIN_SET_INTERVAL  20       //�޼��϶�������ʱ��Ĭ��20ms,add by zqc 2019.06.02

enum
{
    JJTJ_INTERRUPT_MASK,//����ͣ��-�ж�����λ
    HTGWY_INTERRUPT_MASK,//��̨��λ��-�ж�����λ
    ZDTGWY_INTERRUPT_MASK,//��̨��λ��-�ж�����λ
    HTDYW_INTERRUPT_MASK,//��̨��Һλ-�ж�����λ
    SELFDEFINE1_INTERRUPT_MASK,//�Զ���1-�ж�����λ
    HTQY_INTERRUPT_MASK,//��̨Ƿѹ-�ж�����λ
    ZDTGW_INTERRUPT_MASK,//��̨����-�ж�����λ
    EZGWY_INTERRUPT_MASK,//�����λ��-�ж�����λ
    GFRJBH_INTERRUPT_MASK,//�����ȼ̱���-�ж�����λ
    JYZCDY_INTERRUPT_MASK,//��ѹ��е�ѹ-�ж�����λ
    ZGMBH_INTERRUPT_MASK,//�����ű���-�ж�����λ
    XTLQDY_INTERRUPT_MASK,//ϵͳ��ȴ��Ԫ-�ж�����λ
    HTQYW_INTERRUPT_MASK,//���������Ź���-�ж�����λ
    SELFDEFINE2_INTERRUPT_MASK,//�Զ���2-�ж�����λ
    SELFDEFINE3_INTERRUPT_MASK,//�Զ���3-�ж�����λ
    NULL_INTERRUPT_MASK, //������-�ж�����λ
    SUBZLQGW_INTERRUPT_MASK,//�ӹ�����������-�ж�����λ
    SUBMBH_INTERRUPT_MASK  //�ӹ��ű���-�ж�����λ
};
enum
{
    YLEFT_MODE,
    YRIGHT_MODE,
    YLEFTRIGHT_MODE
};
//״̬��¼�ṹ��
typedef struct STRU_STATUSRECORD
{
    quint64 lTotaltime;  //������ʱ��
    quint32 iSumtime;        //���һ������ʱ��
}STRU_STATUSRECORD;
//������ʱ��ṹ��
typedef struct STRU_TOTALRUNNING
{
    qint64 activeTime;             // �������� add by 2020.11.17
    qint64 lSetCalendarDay;     // �趨��Ȼ�� add by 2020.11.17
    qint64 lSetValue;                // �趨ֵ����λ���룩
    //bool   IsActived;              // �Ƿ񼤻��־
}STRU_TOTALRUNNING;

//����״̬���ݽṹ��
typedef struct STRU_FAULTSTATUS
{
    int8 iOutovervoltFlag;    //�����ѹ
    int8 iDCovervoltFlag;     //����ֱ����ѹ
    int8 iDCundervoltFlag;    //����ֱ��Ƿѹ
    int8 iACcurrentwarnFlag;  //���������������
    int8 iACcurrentprocFlag;  //���������������
    int8 iIGBT1overtempFlag;  //IGBT���±���
    int8 iIGBT2overtempFlag;  //����1
    int8 iIndu1overtempFlag;  //��й��±���
    int8 iIndu2overtempFlag;  //����2
    int8 iDripulseblockFlag;  //�����������
    int8 iDigspecinterFlag;   //����3
    int8 iAnaspecampoverFlag; //����4
    int8 iAnaspecfreqoverFlag;//����5
    int8 iDigspecampoverFlag; //����6
    int8 iDigspecfreqoverFlag;//����7
    int8 iIGBT1driprocFlag;   //IGBT1��������
    int8 iIGBT2driprocFlag;   //IGBT2��������
    int8 iIGBT3driprocFlag;   //IGBT3��������
    int8 iIGBT4driprocFlag;   //IGBT4��������
    int8 iIGBT5driprocFlag;   //IGBT5��������
    int8 iIGBT6driprocFlag;   //IGBT6��������
    int8 iOutputvoltwarnFlag; //�����ѹ����
}STRU_FAULTSTATUS;

//����ģ������ֱ����ѹ�ṹ��
typedef struct STRU_INPUTDCVOLTAGEMONI
{
    float fINPUTDCVoltage;//����ֱ����ѹ
}STRU_INPUTDCVOLTAGEMONI;
//IGBT�¶ȼ�����ݽṹ��
typedef struct STRU_IGBTTEMPERATUREMONI
{
    float fOUTPUTACCurrent;//�����������
    float fIGBT1Temper; //IGBT�¶�1
    float fIGBT2Temper; //IGBT�¶�2
}STRU_IGBTTEMPERATUREMONI;
//����¶ȼ�����ݽṹ��
typedef struct STRU_IDUCTTEMPERATUREMONI
{
    float fIDUCT1Temper;//����¶�1
    float fIDUCT2Temper;//����¶�2
    float fOUTPUTACVoltage;//���������ѹ
}STRU_IDUCTTEMPERATUREMONI;


//����״̬���ݽṹ��
typedef struct STRU_RUNNINGSTATUS
{
    QString strTime;      //ʱ��
    int8 iRestartprocFlag; //����������
    int8 iNormaloperFlag;  //��������
    int8 iFaultProtFlag;   //���ϱ�����
    int8 iFaultlockFlag;   //���ϱ���
    int iProtectedTimes;  //�ѱ�������
    int8 iBlockpulseFlag;  //��������
    int8 iRecstartsigFlag; //�յ������ź�
    int8 iRecshutsigFlag;  //�յ��ػ��ź�
    QString strOrigMsg;   //ԭʼ����

}STRU_RUNNINGSTATUS;
//�ֹ�ϵ���ṹ��
typedef struct STRU_SLAVECOEFDATA
{
    float fVolt;
    float fCurrent;
    float fBusVolt;
}STRU_SLAVECOEFDATA;

//������ֵ�����ṹ��
typedef struct STRU_PROCVALUEDATA
{
    float fOutVoltLow;    //�����ѹ����ֵ(����)
    float fOutVoltUp;     //�����ѹ����ֵ(����)
    float fDCVoltOverLow; //ֱ����ѹ��ѹ����ֵ(����)
    float fDCVoltOverUp;  //ֱ����ѹ��ѹ����ֵ(����)
    float fCurrentProcVal;//�������ֵ����ֵ
    float fCurrentWarnVal;//�������ֵ����ֵ
    float fIGBTGW1;       //IGBT���¶����¶�1
    float fIGBTGW2;       //IGBT���¶����¶�2
    float fIDCUTGW1;      //��й��¶����¶�1
    float fIDCUTGW2;      //��й��¶����¶�2

}STRU_PROCVALUEDATA;
//�������ò����ṹ��
typedef struct STRU_CHAINSETDATA
{
     int iJjtjVal;   //����ͣ��
     int iHtgwyVal;  //��̨��λ��
     int iZdtgwyVal; //��̨��λ��
     int iHtdywVal;  //��̨��Һλ
     int iHtqyVal; //��̨��е�ѹ
     int iZdtgwVal;  //��̨����
     int iEzgwyVal;  //�����λ��
     int iGfrjbhVal; //�����ȼ̱���
     int iJyzcdyVal; //��ѹ��е�ѹ
     int iZgMenbVal; //�����ű���
     int iSubMenbVal;//�ӹ��ű���
     int iXtlqdyVal; //ϵͳ��ȴ��Ԫ
     int iHtqywVal; //���������Ź���,add by 2019.05.25
     int iSubzlqgwVal;//�ӹ������Ź���,add by 2019.05.25
     int iSelfdefineVal1; //�Զ���1,add by 2019.05.25
     int iSelfdefineVal2; //�Զ���2,add by 2019.05.25
     int iSelfdefineVal3; //�Զ���3,add by 2019.05.25
     int iSubyuliuPorcVal; //�ӹ�Ԥ������,add by 2019.05.25

     int iSwitch_Jjtj;               //����ͣ�������л�  add by 2020.09.08
     int iSwitch_htgwy;          //��̨��λ�ƴ����л� add by 2020.09.08
     int iSwitch_zdtgwy;        //��̨��λ�ƴ����л� add by 2020.09.08
     int iSwitch_htdyw;         //��̨��Һλ�����л� add by 2020.09.08
     int iSwitch_htqy;        //��̨��е�ѹ�����л� add by 2020.09.08
     int iSwitch_zdtgw;        //��̨���´����л� add by 2020.09.08
     int iSwitch_ezgwy;        //�����λ�ƴ����л� add by 2020.09.08
     int iSwitch_gfrjbh;         //�����ȼ̱��������л� add by 2020.09.08
     int iSwitch_jyzcdy;        //��ѹ��е�ѹ�����л� add by 2020.09.08
     int iSwitch_zgmenbh;    //�����ű��������л� add by 2020.09.08
     int iSwitch_htgw;  //�ӹ��ű��������л� add by 2020.09.08
     int iSwitch_xtlqdy;          //ϵͳ��ȴ��Ԫ�����л� add by 2020.09.08
     int iSwitch_htqyw;      //�������������´����л� add by 2020.09.08
     int iSwitch_subzlqgw;    //�ӹ����������´����л� add by 2020.09.08
     int iSwitch_selfdefine1;  //�Զ���1���������л� add by 2020.09.08
     int iSwitch_selfdefine2;  //�Զ���2���������л� add by 2020.09.08
     int iSwitch_selfdefine3;  //�Զ���3���������л� add by 2020.09.08
     int iSwitch_subyuliu;       //�ӹ�Ԥ�����������л� add by 2020.09.08

}STRU_CHAINSETDATA;

//���������ṹ��,add by 2019.05.16
typedef struct STRU_BASICPARA
{
   float fVoltimbalance;      //�����ѹ��ƽ�⣬Ĭ��ֵ5%
   float fThreevoltUp;        //�����ѹ���ߣ�Ĭ��ֵ418.0V
   float fThreevoltLow;       //�����ѹ���ͣ�Ĭ��ֵ342.0V
   float fTotalvoltUp;        //�����������ѹ���ߣ�Ĭ��ֵ350.0V
   float fTotalcurrentUp;     //����������������ߣ�Ĭ��ֵ3400.0A
   float fBusvoltUp;          //ĸ�ߵ�ѹ���ߣ�Ĭ��ֵ600.0V
   float fBusvoltLow;         //ĸ�ߵ�ѹ���ͣ�Ĭ��ֵ500.0V
   float fBusImbalance;       //ĸ�ߵ�ѹ�����⣬Ĭ��ֵ3.0V
   float fSub1CabinetcurrentUp;//�ֹ�1����������ߣ�Ĭ��ֵ850.0A
   float fSub2CabinetcurrentUp;//�ֹ�2����������ߣ�Ĭ��ֵ850.0A
   float fSub3CabinetcurrentUp;//�ֹ�3����������ߣ�Ĭ��ֵ850.0A
   float fSub4CabinetcurrentUp;//�ֹ�4����������ߣ�Ĭ��ֵ850.0A
   int   iSub1CabOpen;        //�ֹ�1�����ǣ�1-���룻0-�Ͽ���add by zqc 2019.06.02
   int   iSub2CabOpen;        //�ֹ�2�����ǣ�1-���룻0-�Ͽ���add by zqc 2019.06.02
   int   iSub3CabOpen;        //�ֹ�3�����ǣ�1-���룻0-�Ͽ���add by zqc 2019.06.02
   int   iSub4CabOpen;        //�ֹ�4�����ǣ�1-���룻0-�Ͽ���add by zqc 2019.06.02
}STRU_BASICPARA;

//У׼���ݽṹ��

typedef struct STRU_ADJVALUE
{
    float fZeroTotalvalue[25];
    float fTotalvalue[25];
    float fAdjvalue[25];
}STRU_ADJVALUE;
//У׼ϵ���ṹ��
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
//У׼��ѡ�ṹ��
typedef struct STRU_ADJCHECK
{
    int iS1bvCabOpen;//�ֹ�1ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS1abvCabOpen;//�ֹ�1��ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS1nbvCabOpen;//�ֹ�1��ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS1ovCabOpen;//�ֹ�1�����ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS1ocCabOpen;//�ֹ�1�������У׼�����־��1-���룬0-�Ͽ�

    int iS2bvCabOpen;//�ֹ�2ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS2abvCabOpen;//�ֹ�2��ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS2nbvCabOpen;//�ֹ�2��ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS2ovCabOpen;//�ֹ�2�����ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS2ocCabOpen;//�ֹ�2�������У׼�����־��1-���룬0-�Ͽ�

    int iS3bvCabOpen;//�ֹ�3ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS3abvCabOpen;//�ֹ�3��ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS3nbvCabOpen;//�ֹ�3��ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS3ovCabOpen;//�ֹ�3�����ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS3ocCabOpen;//�ֹ�3�������У׼�����־��1-���룬0-�Ͽ�

    int iS4bvCabOpen;//�ֹ�4ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS4abvCabOpen;//�ֹ�4��ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS4nbvCabOpen;//�ֹ�4��ĸ�ߵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS4ovCabOpen;//�ֹ�4�����ѹУ׼�����־��1-���룬0-�Ͽ�
    int iS4ocCabOpen;//�ֹ�4�������У׼�����־��1-���룬0-�Ͽ�

    int iMAvCabOpen;//����A���ѹУ׼�����־��1-���룬0-�Ͽ�
    int iMBvCabOpen;//����B���ѹУ׼�����־��1-���룬0-�Ͽ�
    int iMCvCabOpen;//����C���ѹУ׼�����־��1-���룬0-�Ͽ�
    int iMevCabOpen;//�������ŵ�ѹУ׼�����־��1-���룬0-�Ͽ�
    int iMecCabOpen;//�������ŵ���У׼�����־��1-���룬0-�Ͽ�

    int iS1CabOpen;//�ӹ�1У׼�����־��1-���룬0-�Ͽ�
    int iS2CabOpen;//�ӹ�2У׼�����־��1-���룬0-�Ͽ�
    int iS3CabOpen;//�ӹ�3У׼�����־��1-���룬0-�Ͽ�
    int iS4CabOpen;//�ӹ�4У׼�����־��1-���룬0-�Ͽ�
    int iMainCabOpen;//����У׼�����־��1-���룬0-�Ͽ�
    int iAllCabOpen;//ȫ��У׼�����־��1-���룬0-�Ͽ�
}STRU_ADJCHECK;
//У׼��ѡ�������ṹ��
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
    int8   iRunningState;       //����״̬
    int8   iCoolingState;       //��ȴ״̬
    int8   iExcitationState;    //����״̬
    int8   iReadyState;         //׼��״̬
    int8   iGainState;          //����״̬
    int8   iFaultState;         //����״̬
    float fTotalVolt;          //�������ѹ(4���ֹ��ѹ��ֵ)
    float fTotalCurrent;       //���������(4���ֹ�������)
    float fExcitVolt;          //���ŵ�ѹ
    float fExcitCurrent;       //���ŵ���
    float fPhaseAVolt;         //A���ѹ
    float fPhaseBVolt;         //B���ѹ
    float fPhaseCVolt;         //C���ѹ
    float fSlaveVolt[4];       //�ӹ��ѹ;
    float fSlaveCurrent[4];    //�ӹ����;
    float fSlaveBusVolt[4];    //�ӹ�ĸ�ߵ�ѹ(������ĸ�ߵ�ѹ);
    float fSlaveActBusVolt[4]; //�ӹ���ĸ�ߵ�ѹ;
    float fSlaveNegBusVolt[4]; //�ӹ�ĸ�ߵ�ѹ;
    int8 iSlaveStaValue[4];   //�ӹ�����״ֵ̬
}STR_GPIODATA;

//״̬��¼��Ϣ�ṹ�壬add by zqc 2019.07.13
typedef struct STR_STATUSDATA
{
    QString strAlarmTime;    //����ʱ��
    QString strErrorType;    //��������
    float   fVoltRms;        //�����ѹ��Чֵ(V)
    float   fVoltMax;        //�����ѹ���ֵ(V)
    float   fCurrentRms;     //���������Чֵ(A)
    float   fCurrentMax;     //����������ֵ(A)
}STR_STATUSDATA;

typedef struct STRU_SIMUPROCSET
{
    float fSimuPhaseAVolt;         //ģ��-A���ѹ
    float fSimuPhaseBVolt;         //ģ��-B���ѹ
    float fSimuPhaseCVolt;         //ģ��-C���ѹ
    float fSimuBusVolt;            //ģ��-ĸ�ߵ�ѹ,add by 2019.05.25
    float fSimuExcitCurrent;       //ģ��-���ŵ���,add by 2019.05.25
     bool isSimuFlag;              //�Ƿ�ģ���ǣ�add by 2019.05.25
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





//�°��������ⲿ�����źŽṹ��
typedef struct STRU_NEWFAULTSTATUS
{

    int8 iVIBODFlag;        //��̨��λ��
    int8 iVIBCUFlag;        //��̨��ȴ����
    int8 iVIBOTFlag;        //�񶯹���
    int8 iSTODFlag;         //��̨��λ�Ʊ���
    int8 iSTUPFlag;         //��̨Ƿѹ
    int8 iSTOTFlag;         //��̨����
    int8 iSTOLFlag;         //��̨ǷҺλ
    int8 iRELAYFlag;        //�����ȼ̱���
    int8 iDOORFlag;         //�ű���
    int8 iHBUPFlag;         //��ѹ���Ƿѹ
    int8 iEXT1Flag;         //�Զ���1
    int8 iEXT2Flag;         //�Զ���2
    int8 iEXT3Flag;         //�Զ���3
    int8 iEXT4Flag;         //�Զ���4
    int8 iESTOPFlag;        //����ͣ��
    int8 iOT1Flag;          //�ӹ�1�����Ź���1
    int8 iOT2Flag;          //�ӹ�1�����Ź���2
    int8 iOT3Flag;          //�ӹ�1�����Ź���3
    int8 iOT4Flag;          //�ӹ�1�����Ź���4
    int8 iSESTOPFlag;       //S����ͣ��
    int8 iFAULT1Flag;       //�ӹ�1�����ź�
    int8 iFAULT2Flag;       //�ӹ�2�����ź�
    int8 iFAULT3Flag;       //�ӹ�3�����ź�
    int8 iFAULT4Flag;       //�ӹ�4�����ź�
    int8 iKEYCOL6Flag;      //VOL- for test
    int8 iFaultValue[25];   //��������IOֵ

}STRU_NEWFAULTSTATUS;

typedef struct STRU_ADDATANEW
{

    float fTriPhaseAVolDC;     //�����A��ֱ��
    float fTriPhaseBVolDC;     //�����B��ֱ��
    float fTriPhaseCVolDC;     //�����C��ֱ��
    float fExcitVolt;          //���ŵ�ѹֱ��
    float fExcitCur;           //���ŵ���ֱ��

    float fSlave1VolDC;        //�ӹ�1ĸ�ߵ�ѹֱ��
    float fSlave1CurDC;        //�ӹ�1����ֱ��
    float fSlave2VolDC;        //�ӹ�2ĸ�ߵ�ѹֱ��
    float fSlave2CurDC;        //�ӹ�2����ֱ��

    float fSlave3VolDC;        //�ӹ�3ĸ�ߵ�ѹֱ��
    float fSlave3CurDC;        //�ӹ�3����ֱ��
    float fSlave4VolDC;        //�ӹ�4ĸ�ߵ�ѹֱ��
    float fSlave4CurDC;        //�ӹ�4����ֱ��

    float fTotalVolAC;         //�ܵ�ѹ����
    float fTotalVolDC;         //�ܵ�ѹֱ��
    float fTotalSlaveCurAC;    //�ӹ��ܵ�������
    float fCustom11;           //�ⲿԤ��11
    float fCustom12;           //�ⲿԤ��12

    int8   iRunningState;       //����״̬
    int8   iCoolingState;       //��ȴ״̬
    int8   iExcitationState;    //����״̬
    int8   iReadyState;         //׼��״̬
    int8   iGainState;          //����״̬
    int8   iFaultState;         //����״̬
    int8   iSlaveStaValue[4];   //�ӹ�����״ֵ̬

}STRU_ADDATANEW;

//��У׼ϵ���ṹ��
typedef struct STRU_NEWADJCOEF
{
    //�����Aֱ��
    float fTriPhaseAVolDCK;
    float fTriPhaseAVolDCB;
    //�����Bֱ��
    float fTriPhaseBVolDCK;
    float fTriPhaseBVolDCB;
    //�����Cֱ��
    float fTriPhaseCVolDCK;
    float fTriPhaseCVolDCB;
    //���ŵ�ѹֱ��
    float fExcitVoltK;
    float fExcitVoltB;
    //���ŵ���ֱ��
    float fExcitCurK;
    float fExcitCurB;
    //�ӹ�1��ѹֱ��
    float fSlave1VolDCK;
    float fSlave1VolDCB;
    //�ӹ�1����ֱ��
    float fSlave1CurDCK;
    float fSlave1CurDCB;
    //�ӹ�2��ѹֱ��
    float fSlave2VolDCK;
    float fSlave2VolDCB;
    //�ӹ�2����ֱ��
    float fSlave2CurDCK;
    float fSlave2CurDCB;
    //�ӹ�3��ѹֱ��
    float fSlave3VolDCK;
    float fSlave3VolDCB;
    //�ӹ�3����ֱ��
    float fSlave3CurDCK;
    float fSlave3CurDCB;
    //�ӹ�4��ѹֱ��
    float fSlave4VolDCK;
    float fSlave4VolDCB;
    //�ӹ�4����ֱ��
    float fSlave4CurDCK;
    float fSlave4CurDCB;
    //�ܵ�ѹ����
    float fTotalVolACK;
    float fTotalVolACB;
    //�ܵ�ѹֱ��
    float fTotalVolDCK;
    float fTotalVolDCB;
    //�ӹ��ܵ�������
    float fTotalSlaveCurACK;
    float fTotalSlaveCurACB;
    //�ⲿԤ��11
    float fCustom11K;
    float fCustom11B;
    //�ⲿԤ��12
    float fCustom12K;
    float fCustom12B;
}STRU_NEWADJCOEF;
//У׼��ѡ�ṹ��

//��У׼��ѡ�������ṹ��
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
   int iMAvOpen; //���������A
   int iMBvOpen; //���������B
   int iMCvOpen; //���������C
   int iEvOpen;  //�������ŵ�ѹ
   int iEcOpen;  //�������ŵ�ѹ

   int iS1vOpen; //�ӹ�1��ѹ
   int iS1cOpen; //�ӹ�1����
   int iS2vOpen; //�ӹ�2��ѹ
   int iS2cOpen; //�ӹ�2����

   int iS3vOpen; //�ӹ�3��ѹ
   int iS3cOpen; //�ӹ�3����
   int iS4vOpen; //�ӹ�4��ѹ
   int iS4cOpen; //�ӹ�4����

   int iSAvacOpen; //�ӹ��ܵ�ѹAC
   int iSAvdcOpen; //�ӹ��ܵ�ѹDC
   int iSAcacOpen; //�ӹ��ܵ���AC
   int iCus1Open; //Ԥ��1
   int iCus2Open; //Ԥ��2

   int iMainOpen; //����
   int iS12Open; //�ӹ�12
   int iS34Open; //�ӹ�34
   int iSAllOpen; //�ӹ���
   int iAllOpen; //����

}STRU_NEWADCK;

typedef struct STR_NEWADJVALUE
{
    float fZeroValue[18];
    float fShowValue[18];
    float fRealValue[18];
}STR_NEWADJVALUE;

//���������ò����ṹ��
typedef struct STRU_NEWCHASETDATA
{
     int iJjtjVal;      //����ͣ��
     int iSJitiVal;     //S����ͣ��
     int iXtlqVal;      //ϵͳ��ȴ
     int iZdtgwVal;     //��̨����
     int iZdtgwyVal;    //��̨��λ��
     int iHtgwyVal;     //��̨��λ��
     int iHtqyVal;      //��̨Ƿѹ
     int iHtqywVal;     //��̨ǷҺλ
     int iHtgwVal;      //��̨����
     int iGfrjbhVal;    //�����ȼ̱���
     int iJyzcdyVal;    //��ѹ��е�ѹ
     int iZgmbhVal;     //�����ű���
     int iSelfdefVal1;  //�Զ���1
     int iSelfdefVal2;  //�Զ���2
     int iSelfdefVal3;  //�Զ���3
     int iSelfdefVal4;  //�Զ���4
     int iC1zlqgwVal;  //�ӹ�1����������
     int iC2zlqgwVal;  //�ӹ�2����������
     int iC3zlqgwVal;  //�ӹ�3����������
     int iC4zlqgwVal;  //�ӹ�4����������
     int iC1cwbhVal;  //�ӹ�1���󱣻�
     int iC2cwbhVal;  //�ӹ�2���󱣻�
     int iC3cwbhVal;  //�ӹ�3���󱣻�
     int iC4cwbhVal;  //�ӹ�4���󱣻�

     int isw_Jjtj;      //����ͣ�������л�
     int isw_SJiti;     //S����ͣ�������л�
     int isw_Xtlq;      //ϵͳ��ȴ�����л�
     int isw_Zdtgw;     //��̨���´����л�
     int isw_Zdtgwy;    //��̨��λ�ƴ����л�
     int isw_Htgwy;     //��̨��λ�ƴ����л�
     int isw_Htqy;      //��̨Ƿѹ�����л�
     int isw_Htqyw;     //��̨ǷҺλ�����л�
     int isw_Htgw;      //��̨���´����л�
     int isw_Gfrjbh;    //�����ȼ̱��������л�
     int isw_Jyzcdy;    //��ѹ��е�ѹ�����л�
     int isw_Zgmbh;     //�����ű��������л�
     int isw_Selfdef1;  //�Զ���1�����л�
     int isw_Selfdef2;  //�Զ���2�����л�
     int isw_Selfdef3;  //�Զ���3�����л�
     int isw_Selfdef4;  //�Զ���4�����л�
     int isw_C1zlqgw;   //�ӹ�1���������´����л�
     int isw_C2zlqgw;   //�ӹ�2���������´����л�
     int isw_C3zlqgw;   //�ӹ�3���������´����л�
     int isw_C4zlqgw;   //�ӹ�4���������´����л�
     int isw_C1cwbh;    //�ӹ�1���󱣻������л�
     int isw_C2cwbh;    //�ӹ�2���󱣻������л�
     int isw_C3cwbh;    //�ӹ�3���󱣻������л�
     int isw_C4cwbh;    //�ӹ�4���󱣻������л�
}STRU_NEWCHASETDATA;
enum
{


    JJTJ_MASK,      //����ͣ��-�ж�����λ
    SJJTJ_MASK,     //S����ͣ��-�ж�����λ
    XTLQ_MASK,      //ϵͳ��ȴ-�ж�����λ
    ZDTGW_MASK,     //��̨����-�ж�����λ
    ZDTGWY_MASK,    //��̨��λ��-�ж�����λ
    HTGWY_MASK,     //��̨��λ��-�ж�����λ
    HTQY_MASK,      //��̨Ƿѹ-�ж�����λ
    HTQYW_MASK,     //��̨ǷҺλ-�ж�����λ
    HTGW_MASK,      //��̨����-�ж�����λ
    GFRJBH_MASK,    //�����ȼ̱���-�ж�����λ
    JYZCDY_MASK,    //��ѹ��е�ѹ-�ж�����λ
    ZGMBH_MASK,     //�����ű���-�ж�����λ
    ZDY1_MASK,      //�Զ���1-�ж�����λ
    ZDY2_MASK,      //�Զ���2-�ж�����λ
    ZDY3_MASK,      //�Զ���3-�ж�����λ
    ZDY4_MASK,      //�Զ���4-�ж�����λ
    CG1ZLQGW_MASK,  //�ӹ�1����������-�ж�����λ
    CG2ZLQGW_MASK,  //�ӹ�2����������-�ж�����λ
    CG3ZLQGW_MASK,  //�ӹ�3����������-�ж�����λ
    CG4ZLQGW_MASK,  //�ӹ�4����������-�ж�����λ
    CG1CWBH_MASK,   //�ӹ�1���󱣻�-�ж�����λ
    CG2CWBH_MASK,   //�ӹ�2���󱣻�-�ж�����λ
    CG3CWBH_MASK,   //�ӹ�3���󱣻�-�ж�����λ
    CG4CWBH_MASK,   //�ӹ�4���󱣻�-�ж�����λ
};
#define LED_GREEN        1
#define LED_RED          0
#define LED_YELLOW      -1

//end add by zw 20220223

#endif//COMM_MACRO_H
