#ifndef JUDGE_PROTECTION_H
#define JUDGE_PROTECTION_H
#include "commmacro.h"
#include <QWidget>
#include <QDateTime>

class CJudgeProc
{
public:
    CJudgeProc();
    ~CJudgeProc();
public:
    //�¼���Ƿ������ⲿ���� add by zw 2022.02.23
    bool newCheckExterProcExist(STRU_NEWCHASETDATA stru_newChainSetData,int cnt_proc,QStringList &strlistProcType);
    //����Ƿ����ⲿ���� add by 2019.05.14
    bool CheckExterProcExist(int8 *buffer_read,STRU_CHAINSETDATA stru_ChainSetData,QStringList &strlistProcType);

    //����Ƿ���������ѹ��ƽ��(�����ȡ��ֵ���5%)
    bool CheckVoltImbalance(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt);
    //�¼���Ƿ���������ѹ��ƽ��(�����ȡ��ֵ���5%) add by zw 2022.02.23
    bool newCheckVoltImbalance(STRU_ADDATANEW stru_newaddata);

    //����Ƿ���������ѹ����
    bool CheckOverVolt(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt);
    //�¼���Ƿ���������ѹ���� add by zw 2022.02.23
    bool newCheckOverVolt(STRU_ADDATANEW stru_newaddata);

    //����Ƿ���������ѹ����
    bool CheckLowVolt(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt);
    //�¼���Ƿ���������ѹ���� add by zw 2022.02.23
    bool newCheckLowVolt(STRU_ADDATANEW stru_newaddata);

    //���ĸ�ߵ�ѹ�Ƿ����
    bool CheckBusVoltUpExist(STR_GPIODATA GPIOData,int &iBusVoltUpCnt);
    //�¼��ĸ�ߵ�ѹ�Ƿ���� add by zw 2022.02.23
    bool newCheckBusVoltUpExist(STRU_ADDATANEW stru_newaddata,int &iBusVoltUpCnt);


    //���ĸ�ߵ�ѹ�Ƿ����
    bool CheckBusVoltDownExist(STR_GPIODATA GPIOData,int &iBusVoltDownCnt);
    //�¼��ĸ�ߵ�ѹ�Ƿ���� add by zw 2022.02.23
    bool newCheckBusVoltDownExist(STRU_ADDATANEW stru_newaddata, int &iBusVoltDownCnt);

    //���ĸ�ߵ�ѹ������
    bool CheckBusVoltUnbalance(STR_GPIODATA GPIOData,int &iUnbalanceCnt);
    //�¼��ĸ�ߵ�ѹ������ add by zw 2022.02.23 ����δ��д
    bool newCheckBusVoltUnbalance(STRU_ADDATANEW stru_newaddata);

    //���ֹ���������Ƿ����
    bool CheckOutputCurrentOver(STR_GPIODATA GPIOData,int &iCurrOverCnt);
    //�¼��ֹ���������Ƿ���� add bu zw 20220223
    bool newCheckOutputCurrentOver(STRU_ADDATANEW stru_newaddata,int &iCurrOverCnt);

    //����Ƿ�������ſ�·
    bool CheckExcitProcExist(STR_GPIODATA GPIOData);
    //�¼���Ƿ�������ſ�· add by zw 20220223
    bool newCheckExcitProcExist(STRU_ADDATANEW stru_newaddata);
    //�¼���Ƿ�������ŵ�ѹ����������ָʾ�� add by zw 20220223
    void newCheckExcitVolExist();

    //����Ƿ���ڴӹ��ű���
    bool CheckSubDoorProcExist(STR_GPIODATA GPIOData,STRU_CHAINSETDATA stru_ChainSetData);
    //�¼���Ƿ���ڴӹ��ű��� add by zw 20220223 ����δ��д
    bool newCheckSubDoorProcExist(STRU_NEWFAULTSTATUS stru_newfaultdata,STRU_NEWCHASETDATA stru_newChainSetData);

    //�¼���Ƿ������ȴ���� add by zw 20220223
    bool newCheckXtlqProcExist(STRU_NEWCHASETDATA stru_newChainSetData);

    //����Ƿ���ڴӹ������Ź���
    bool CheckSubRectBridgeOverheat(STR_GPIODATA GPIOData,STRU_CHAINSETDATA stru_ChainSetData);
    //�¼���Ƿ���ڴӹ������Ź��� add by zw 20220223
    bool newCheckSubRectBridgeOverheat(STRU_NEWCHASETDATA stru_newChainSetData);

    //����Ƿ���ڴӹ�Ԥ������
    bool CheckSubReserveProcExist(STR_GPIODATA GPIOData,STRU_CHAINSETDATA stru_ChainSetData);
    //����Ƿ����ͨ��ģ�鱣��(�������29-ģ��ֱ��Ƿѹ)
    bool CheckGenModuleProcExist(int nModuleNum,STRU_FAULTSTATUS *pStru_FaultDATA,QStringList &strlistGenModuProc);
    //add by zw 20220223 STR_STATUSDATA���
    STR_STATUSDATA  organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal);

    void judgeLangChange();
private:
    void initProctype();
public:
    /*�ⲿ���������ַ���*/
     QString m_strxtlqdy;//ϵͳ��ȴ��Ԫ,add by 2019.05.14
     QString m_strzdtgwy;//��̨��λ��,add by 2019.05.14
     QString m_strzdtgw;//��̨����,add by 2019.05.14
     QString m_strhtgwy;//��̨��λ��,add by 2019.05.14
     QString m_strhtdyw;//��̨��Һλ,add by 2019.05.14
     QString m_strhtqy;//��̨��е�ѹ,add by 2019.05.14
     QString m_strezgwy;//�����λ��,add by 2019.05.14
     QString m_strjyzcdy;//��ѹ��е�ѹ,add by 2019.05.14

     QString m_strjjtj;//����ͣ��(Ԥ��),add by 2019.05.14
     QString m_strsjjtj;//����ͣ��(Ԥ��),add by 2019.05.14
     QString m_strzdtlq;//��̨��ȴ(Ԥ��),add by 2019.05.14


//     QString m_strhtqy; //��̨Ƿѹ,add by zw 2022.02.23
     QString m_strhtgw; //��̨����,add by zw 2022.02.23
     QString m_strelfdef1; //�Զ���1,add by zw 2022.02.23
     QString m_strelfdef2; //�Զ���1,add by zw 2022.02.23
     QString m_strelfdef3; //�Զ���1,add by zw 2022.02.23
     QString m_strelfdef4; //�Զ���1,add by zw 2022.02.23
     QString m_strc1zlqgw; //�ӹ�1�����Ź���,add by zw 2022.02.23
     QString m_strc2zlqgw; //�ӹ�2�����Ź���,add by zw 2022.02.23
     QString m_strc3zlqgw; //�ӹ�3�����Ź���,add by zw 2022.02.23
     QString m_strc4zlqgw; //�ӹ�4�����Ź���,add by zw 2022.02.23
     QString m_strc1cwbh;  //�ӹ�1����,add by zw 2022.02.23
     QString m_strc2cwbh;  //�ӹ�2����,add by zw 2022.02.23
     QString m_strc3cwbh;  //�ӹ�3����,add by zw 2022.02.23
     QString m_strc4cwbh;  //�ӹ�4����,add by zw 2022.02.23



     /*�ڲ����������ַ���*/
     QString m_strmbh;          //�����ű���,add by 2019.05.14
     QString m_strgfrjbh;       //�����ȼ̱���,add by 2019.05.14
     QString m_strhtqyw;      //���������Ź��£�add by 2019.05.17
     QString m_strVoltUnbalance;//�����ѹ��ƽ�⣬
     QString m_strVoltUp;       //�����ѹ����,
     QString m_strVoltDown;     //�����ѹ���ͣ�
     QString m_strOutVoltUp;    //�������ѹ����
     QString m_strOutCurrentUp; //�������������
     QString m_strExcitopen;    //���ſ�·
     QString m_strSubmbh;       //�ӹ��ű���
     QString m_strSubzlqgw;     //�ӹ������Ź���
     QString m_strSubylproc;    //�ӹ�Ԥ������
     QString m_strBusVoltUp;    //ĸ�ߵ�ѹ����
     QString m_strBusVoltDown;  //ĸ�ߵ�ѹ����
     QString m_strBusVoltUnbalance;//ĸ�ߵ�ѹ������
     QString m_strSubCurrentUp;    //�ֹ������������
     QString m_strModuleUnderVolt;  //ģ��ֱ��Ƿѹ,add by zqc 2019.07.15

     int m_nTestFlag;//���Ա�־
};
#endif //JUDGE_PROTECTION_H
