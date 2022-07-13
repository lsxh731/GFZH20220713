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
    //新检测是否有内外部保护 add by zw 2022.02.23
    bool newCheckExterProcExist(STRU_NEWCHASETDATA stru_newChainSetData,int cnt_proc,QStringList &strlistProcType);
    //检测是否有外部保护 add by 2019.05.14
    bool CheckExterProcExist(int8 *buffer_read,STRU_CHAINSETDATA stru_ChainSetData,QStringList &strlistProcType);

    //检测是否存在三相电压不平衡(三相电取均值后的5%)
    bool CheckVoltImbalance(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt);
    //新检测是否存在三相电压不平衡(三相电取均值后的5%) add by zw 2022.02.23
    bool newCheckVoltImbalance(STRU_ADDATANEW stru_newaddata);

    //检测是否存在三相电压过高
    bool CheckOverVolt(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt);
    //新检测是否存在三相电压过高 add by zw 2022.02.23
    bool newCheckOverVolt(STRU_ADDATANEW stru_newaddata);

    //检测是否存在三相电压过低
    bool CheckLowVolt(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt);
    //新检测是否存在三相电压过低 add by zw 2022.02.23
    bool newCheckLowVolt(STRU_ADDATANEW stru_newaddata);

    //检测母线电压是否过高
    bool CheckBusVoltUpExist(STR_GPIODATA GPIOData,int &iBusVoltUpCnt);
    //新检测母线电压是否过高 add by zw 2022.02.23
    bool newCheckBusVoltUpExist(STRU_ADDATANEW stru_newaddata,int &iBusVoltUpCnt);


    //检测母线电压是否过低
    bool CheckBusVoltDownExist(STR_GPIODATA GPIOData,int &iBusVoltDownCnt);
    //新检测母线电压是否过低 add by zw 2022.02.23
    bool newCheckBusVoltDownExist(STRU_ADDATANEW stru_newaddata, int &iBusVoltDownCnt);

    //检测母线电压不均衡
    bool CheckBusVoltUnbalance(STR_GPIODATA GPIOData,int &iUnbalanceCnt);
    //新检测母线电压不均衡 add by zw 2022.02.23 函数未编写
    bool newCheckBusVoltUnbalance(STRU_ADDATANEW stru_newaddata);

    //检测分柜输出电流是否过高
    bool CheckOutputCurrentOver(STR_GPIODATA GPIOData,int &iCurrOverCnt);
    //新检测分柜输出电流是否过高 add bu zw 20220223
    bool newCheckOutputCurrentOver(STRU_ADDATANEW stru_newaddata,int &iCurrOverCnt);

    //检测是否存在励磁开路
    bool CheckExcitProcExist(STR_GPIODATA GPIOData);
    //新检测是否存在励磁开路 add by zw 20220223
    bool newCheckExcitProcExist(STRU_ADDATANEW stru_newaddata);
    //新检测是否存在励磁电压来控制励磁指示灯 add by zw 20220223
    void newCheckExcitVolExist();

    //检测是否存在从柜门保护
    bool CheckSubDoorProcExist(STR_GPIODATA GPIOData,STRU_CHAINSETDATA stru_ChainSetData);
    //新检测是否存在从柜门保护 add by zw 20220223 函数未编写
    bool newCheckSubDoorProcExist(STRU_NEWFAULTSTATUS stru_newfaultdata,STRU_NEWCHASETDATA stru_newChainSetData);

    //新检测是否存在冷却保护 add by zw 20220223
    bool newCheckXtlqProcExist(STRU_NEWCHASETDATA stru_newChainSetData);

    //检测是否存在从柜整流桥过温
    bool CheckSubRectBridgeOverheat(STR_GPIODATA GPIOData,STRU_CHAINSETDATA stru_ChainSetData);
    //新检测是否存在从柜整流桥过温 add by zw 20220223
    bool newCheckSubRectBridgeOverheat(STRU_NEWCHASETDATA stru_newChainSetData);

    //检测是否存在从柜预留保护
    bool CheckSubReserveProcExist(STR_GPIODATA GPIOData,STRU_CHAINSETDATA stru_ChainSetData);
    //检测是否存在通用模块保护(除了序号29-模块直流欠压)
    bool CheckGenModuleProcExist(int nModuleNum,STRU_FAULTSTATUS *pStru_FaultDATA,QStringList &strlistGenModuProc);
    //add by zw 20220223 STR_STATUSDATA组包
    STR_STATUSDATA  organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal);

    void judgeLangChange();
private:
    void initProctype();
public:
    /*外部保护类型字符串*/
     QString m_strxtlqdy;//系统冷却单元,add by 2019.05.14
     QString m_strzdtgwy;//振动台过位移,add by 2019.05.14
     QString m_strzdtgw;//振动台过温,add by 2019.05.14
     QString m_strhtgwy;//滑台过位移,add by 2019.05.14
     QString m_strhtdyw;//滑台低液位,add by 2019.05.14
     QString m_strhtqy;//滑台轴承低压,add by 2019.05.14
     QString m_strezgwy;//耳轴过位移,add by 2019.05.14
     QString m_strjyzcdy;//静压轴承低压,add by 2019.05.14

     QString m_strjjtj;//紧急停机(预留),add by 2019.05.14
     QString m_strsjjtj;//紧急停机(预留),add by 2019.05.14
     QString m_strzdtlq;//振动台冷却(预留),add by 2019.05.14


//     QString m_strhtqy; //滑台欠压,add by zw 2022.02.23
     QString m_strhtgw; //滑台过温,add by zw 2022.02.23
     QString m_strelfdef1; //自定义1,add by zw 2022.02.23
     QString m_strelfdef2; //自定义1,add by zw 2022.02.23
     QString m_strelfdef3; //自定义1,add by zw 2022.02.23
     QString m_strelfdef4; //自定义1,add by zw 2022.02.23
     QString m_strc1zlqgw; //从柜1整流桥过温,add by zw 2022.02.23
     QString m_strc2zlqgw; //从柜2整流桥过温,add by zw 2022.02.23
     QString m_strc3zlqgw; //从柜3整流桥过温,add by zw 2022.02.23
     QString m_strc4zlqgw; //从柜4整流桥过温,add by zw 2022.02.23
     QString m_strc1cwbh;  //从柜1错误,add by zw 2022.02.23
     QString m_strc2cwbh;  //从柜2错误,add by zw 2022.02.23
     QString m_strc3cwbh;  //从柜3错误,add by zw 2022.02.23
     QString m_strc4cwbh;  //从柜4错误,add by zw 2022.02.23



     /*内部保护类型字符串*/
     QString m_strmbh;          //主柜门保护,add by 2019.05.14
     QString m_strgfrjbh;       //功放热继保护,add by 2019.05.14
     QString m_strhtqyw;      //主柜整流桥过温，add by 2019.05.17
     QString m_strVoltUnbalance;//三相电压不平衡，
     QString m_strVoltUp;       //三相电压过高,
     QString m_strVoltDown;     //三相电压过低，
     QString m_strOutVoltUp;    //总输出电压过高
     QString m_strOutCurrentUp; //总输出电流过高
     QString m_strExcitopen;    //励磁开路
     QString m_strSubmbh;       //从柜门保护
     QString m_strSubzlqgw;     //从柜整流桥过温
     QString m_strSubylproc;    //从柜预留保护
     QString m_strBusVoltUp;    //母线电压过高
     QString m_strBusVoltDown;  //母线电压过低
     QString m_strBusVoltUnbalance;//母线电压不均衡
     QString m_strSubCurrentUp;    //分柜输出电流过高
     QString m_strModuleUnderVolt;  //模块直流欠压,add by zqc 2019.07.15

     int m_nTestFlag;//测试标志
};
#endif //JUDGE_PROTECTION_H
