/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: judgeprotection.cpp
** 摘要: 判断保护信息类
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.05.17
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.05.17   V1.0      创建

****************************************************************************/
#include "judgeprotection.h"
#include <qapplication.h>
#include <qobject.h>
STRU_BASICPARA g_struBasicPara;
extern int g_iLangChange;
//add by zw 20220223
extern STRU_NEWFAULTSTATUS g_newfaultstatus;
extern QVector<STR_STATUSDATA>g_vec_StatusRecord;
extern STRU_ADDATANEW g_newaddata;
//end add by zw 20220223
CJudgeProc::CJudgeProc()
{
    initProctype();//初始化保护信息 add by 2019.05.17
    m_nTestFlag=NOTEST_FLAG;
}
CJudgeProc::~CJudgeProc()
{
}
//初始化保护类型(数据)
void CJudgeProc::initProctype()
{
    //特紧急停机
    m_strsjjtj=QApplication::translate("mainWindow",
        "\347\211\271\347\264\247\346\200\245\345\201\234\346\234\272",
        0,
        QApplication::UnicodeUTF8);
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
     //主柜整流桥过温
     m_strhtqyw=QApplication::translate("mainWindow",
         "\344\270\273\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251",
         0,
         QApplication::UnicodeUTF8);
     //系统冷却单元
     m_strxtlqdy=QApplication::translate("mainWindow",
         "\347\263\273\347\273\237\345\206\267\345\215\264\345\215\225\345\205\203",
         0,
         QApplication::UnicodeUTF8);
     //三相电压不平衡
     m_strVoltUnbalance=QApplication::translate("mainWindow",
         "\344\270\211\347\233\270\347\224\265\345\216\213\344\270\215\345\271\263\350\241\241",
         0,
         QApplication::UnicodeUTF8);
//     printf("####m_strVoltUnbalance=%s####\n",m_strVoltUnbalance.toAscii().constData());
     //三相电压过高
     m_strVoltUp=QApplication::translate("mainWindow",
         "\344\270\211\347\233\270\347\224\265\345\216\213\350\277\207\351\253\230",
         0,
         QApplication::UnicodeUTF8);
     //三相电压过低
     m_strVoltDown=QApplication::translate("mainWindow",
         "\344\270\211\347\233\270\347\224\265\345\216\213\350\277\207\344\275\216",
         0,
         QApplication::UnicodeUTF8);
     //总输出电压过高
     m_strOutVoltUp=QApplication::translate("mainWindow",
         "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\345\216\213\350\277\207\351\253\230",
         0,
         QApplication::UnicodeUTF8);
     //总输出电流过高
     m_strOutCurrentUp=QApplication::translate("mainWindow",
         "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\346\265\201\350\277\207\351\253\230",
         0,
         QApplication::UnicodeUTF8);
     //励磁开路
     m_strExcitopen=QApplication::translate("mainWindow",
         "\345\212\261\347\243\201\345\274\200\350\267\257",
         0,
         QApplication::UnicodeUTF8);
     //从柜门保护
     m_strSubmbh=QApplication::translate("mainWindow",
         "\344\273\216\346\237\234\351\227\250\344\277\235\346\212\244",
         0,
         QApplication::UnicodeUTF8);
     //从柜整流桥过温
     m_strSubzlqgw=QApplication::translate("mainWindow",
         "\344\273\216\346\237\234\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251",
         0,
         QApplication::UnicodeUTF8);
     //从柜预留保护
     m_strSubylproc=QApplication::translate("mainWindow",
         "\344\273\216\346\237\234\351\242\204\347\225\231\344\277\235\346\212\244",
         0,
         QApplication::UnicodeUTF8);
     //母线电压过高
     m_strBusVoltUp=QApplication::translate("mainWindow",
         "\346\257\215\347\272\277\347\224\265\345\216\213\350\277\207\351\253\230",
         0,
         QApplication::UnicodeUTF8);
     //母线电压过低
     m_strBusVoltDown=QApplication::translate("mainWindow",
         "\346\257\215\347\272\277\347\224\265\345\216\213\350\277\207\344\275\216",
         0,
         QApplication::UnicodeUTF8);
     //母线电压不均衡
     m_strBusVoltUnbalance=QApplication::translate("mainWindow",
         "\346\257\215\347\272\277\344\270\215\345\235\207\350\241\241",
         0,
         QApplication::UnicodeUTF8);
     //分柜输出电流过高
     m_strSubCurrentUp=QApplication::translate("mainWindow",
         "\345\210\206\346\237\234\350\276\223\345\207\272\347\224\265\346\265\201\350\277\207\351\253\230",
         0,
         QApplication::UnicodeUTF8);
     //模块直流欠压,add by zqc 2019.07.15
     m_strModuleUnderVolt=QApplication::translate("mainWindow", "\346\250\241\345\235\227\347\233\264\346\265\201\346\254\240\345\216\213",
         0, QApplication::UnicodeUTF8);


     //滑台过温,add by zw 2022.02.23
     m_strhtgw=QApplication::translate("mainWindow", "\346\273\221\345\217\260\350\277\207\346\270\251",
         0, QApplication::UnicodeUTF8);
     //自定义1,add by zw 2022.02.23
     m_strelfdef1=QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\211",
         0, QApplication::UnicodeUTF8);
     m_strelfdef1 = QString("%1-1").arg(m_strelfdef1);
     //自定义2,add by zw 2022.02.23
     m_strelfdef2=QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\211",
         0, QApplication::UnicodeUTF8);
     m_strelfdef2 = QString("%1-2").arg(m_strelfdef2);
     //自定义3,add by zw 2022.02.23
     m_strelfdef3=QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\211",
         0, QApplication::UnicodeUTF8);
     m_strelfdef3 = QString("%1-3").arg(m_strelfdef3);
     //自定义4,add by zw 2022.02.23
     m_strelfdef4=QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\211",
         0, QApplication::UnicodeUTF8);
     m_strelfdef4 = QString("%1-4").arg(m_strelfdef4);
     //从柜1整流桥过温,add by zw 2022.02.23
     m_strc1zlqgw=QApplication::translate("mainWindow", "\344\273\216\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251",
         0, QApplication::UnicodeUTF8);
     m_strc1zlqgw = QString("%1-1").arg(m_strc1zlqgw);
     //从柜2整流桥过温,add by zw 2022.02.23
     m_strc2zlqgw=QApplication::translate("mainWindow", "\344\273\216\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251",
         0, QApplication::UnicodeUTF8);
     m_strc2zlqgw = QString("%1-2").arg(m_strc2zlqgw);
     //从柜3整流桥过温,add by zw 2022.02.23
     m_strc3zlqgw=QApplication::translate("mainWindow", "\344\273\216\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251",
         0, QApplication::UnicodeUTF8);
     m_strc3zlqgw = QString("%1-3").arg(m_strc3zlqgw);
     //从柜4整流桥过温,add by zw 2022.02.23
     m_strc4zlqgw=QApplication::translate("mainWindow", "\344\273\216\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251",
         0, QApplication::UnicodeUTF8);
     m_strc4zlqgw = QString("%1-4").arg(m_strc4zlqgw);
     //从柜1错误,add by zw 2022.02.23
     m_strc1cwbh=QApplication::translate("mainWindow", "\344\273\216\346\237\234\351\224\231\350\257\257",
         0, QApplication::UnicodeUTF8);
     m_strc1cwbh = QString("%1-1").arg(m_strc1cwbh);
     //从柜2错误,add by zw 2022.02.23
     m_strc2cwbh=QApplication::translate("mainWindow", "\344\273\216\346\237\234\351\224\231\350\257\257",
         0, QApplication::UnicodeUTF8);
     m_strc2cwbh = QString("%1-2").arg(m_strc2cwbh);
     //从柜3错误,add by zw 2022.02.23
     m_strc3cwbh=QApplication::translate("mainWindow", "\344\273\216\346\237\234\351\224\231\350\257\257",
         0, QApplication::UnicodeUTF8);
     m_strc3cwbh = QString("%1-3").arg(m_strc3cwbh);
     //从柜4错误,add by zw 2022.02.23
     m_strc4cwbh=QApplication::translate("mainWindow", "\344\273\216\346\237\234\351\224\231\350\257\257",
         0, QApplication::UnicodeUTF8);
     m_strc4cwbh = QString("%1-4").arg(m_strc4cwbh);




}
//检测是否有外部保护 add by 2019.05.14
bool CJudgeProc::CheckExterProcExist(int8 *buffer_read,STRU_CHAINSETDATA stru_ChainSetData,QStringList &strlistProcType)
{
    int cnt_proc=0;
    //需与连锁设置参数“与逻辑”，add by 2019.04.14
    //常开常闭触点切换 add by 2020.09.05
    if(stru_ChainSetData.iSwitch_htgwy==NORMAL_OPEN)
    {
        if(buffer_read[1]==1)
         {
             if(stru_ChainSetData.iHtgwyVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strhtgwy);//滑台过位移-外部 (序号4)
                 cnt_proc++;
                 printf("##CheckProcExist()::iHtgwyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iHtgwyVal,cnt_proc);
             }
        }
    }
    else if(stru_ChainSetData.iSwitch_htgwy==NORMAL_CLOSE)
    {
        if(buffer_read[1]==0)
            {
                if(stru_ChainSetData.iHtgwyVal==SWITCH_ON)
                {
                    strlistProcType.append(m_strhtgwy);//滑台过位移-外部 (序号4)
                    cnt_proc++;
                    printf("##CheckProcExist()::iHtgwyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iHtgwyVal,cnt_proc);
                }
            }
    }
    if(stru_ChainSetData.iSwitch_zdtgwy==NORMAL_OPEN)
    {
        if(buffer_read[2]==1)
         {
         if(stru_ChainSetData.iZdtgwyVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strzdtgwy);//振动台过位移-外部(序号2)
                  cnt_proc++;
                  printf("##CheckProcExist()::iZdtgwyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iZdtgwyVal,cnt_proc);
             }
         }
    }
    else if(stru_ChainSetData.iSwitch_zdtgwy==NORMAL_CLOSE)
    {
        if(buffer_read[2]==0)
         {
         if(stru_ChainSetData.iZdtgwyVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strzdtgwy);//振动台过位移-外部(序号2)
                  cnt_proc++;
                  printf("##CheckProcExist()::iZdtgwyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iZdtgwyVal,cnt_proc);
             }
         }
    }
    if(stru_ChainSetData.iSwitch_htdyw==NORMAL_OPEN)
    {
         if(buffer_read[3]==1)
         {
             if(stru_ChainSetData.iHtdywVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strhtdyw);//滑台低液位-外部（序号5）
                  cnt_proc++;
                  printf("##CheckProcExist()::iHtdywVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iHtdywVal,cnt_proc);
             }
         }
    }
    else if(stru_ChainSetData.iSwitch_htdyw==NORMAL_CLOSE)
    {
         if(buffer_read[3]==0)
         {
             if(stru_ChainSetData.iHtdywVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strhtdyw);//滑台低液位-外部（序号5）
                  cnt_proc++;
                  printf("##CheckProcExist()::iHtdywVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iHtdywVal,cnt_proc);
             }
         }
    }
    if(stru_ChainSetData.iSwitch_htqy==NORMAL_OPEN)
    {
         if(buffer_read[5]==1)
         {
             if(stru_ChainSetData.iHtqyVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strhtqy);//滑台轴承低压-外部(序号6)
                  cnt_proc++;
                  printf("##CheckProcExist()::iHtqyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iHtqyVal,cnt_proc);
             }
         }
    }
    else if(stru_ChainSetData.iSwitch_htqy==NORMAL_CLOSE)
    {
        if(buffer_read[5]==0)
        {
            if(stru_ChainSetData.iHtqyVal==SWITCH_ON)
            {
                strlistProcType.append(m_strhtqy);//滑台轴承低压-外部(序号6)
                cnt_proc++;
                printf("##CheckProcExist()::iHtqyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iHtqyVal,cnt_proc);
            }
        }
    }
    if(stru_ChainSetData.iSwitch_zdtgw==NORMAL_OPEN)
    {
         if(buffer_read[6]==1)
         {
             if(stru_ChainSetData.iZdtgwVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strzdtgw); //振动台过温-外部(序号3)
                  cnt_proc++;
                  printf("##CheckProcExist()::iZdtgwVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iZdtgwVal,cnt_proc);
             }
         }
    }
    else if(stru_ChainSetData.iSwitch_zdtgw==NORMAL_CLOSE)
    {
        if(buffer_read[6]==0)
         {
             if(stru_ChainSetData.iZdtgwVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strzdtgw); //振动台过温-外部(序号3)
                  cnt_proc++;
                  printf("##CheckProcExist()::iZdtgwVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iZdtgwVal,cnt_proc);
             }
         }
    }
    if(stru_ChainSetData.iSwitch_ezgwy==NORMAL_OPEN)
    {
         if(buffer_read[7]==1)
         {
             if(stru_ChainSetData.iEzgwyVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strezgwy);//耳轴过位移-外部(序号7)
                 cnt_proc++;
                 printf("##CheckProcExist()::iEzgwyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iEzgwyVal,cnt_proc);
             }
         }
    }
    else if(stru_ChainSetData.iSwitch_ezgwy==NORMAL_CLOSE)
    {
         if(buffer_read[7]==0)
         {
             if(stru_ChainSetData.iEzgwyVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strezgwy);//耳轴过位移-外部(序号7)
                 cnt_proc++;
                 printf("##CheckProcExist()::iEzgwyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iEzgwyVal,cnt_proc);
             }
         }
    }
    if(stru_ChainSetData.iSwitch_gfrjbh==NORMAL_OPEN)
    {
        if(buffer_read[8]==1)
         {
             if(stru_ChainSetData.iGfrjbhVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strgfrjbh);//功放热继保护-内部(序号13)
                  cnt_proc++;
                  printf("##CheckProcExist()::iGfrjbhVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iGfrjbhVal,cnt_proc);
             }
         }
    }
    if(stru_ChainSetData.iSwitch_gfrjbh==NORMAL_CLOSE)
    {

        if(buffer_read[8]==0)
         {
             if(stru_ChainSetData.iGfrjbhVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strgfrjbh);//功放热继保护-内部(序号13)
                  cnt_proc++;
                  printf("##CheckProcExist()::iGfrjbhVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iGfrjbhVal,cnt_proc);
             }
         }
    }
    if(stru_ChainSetData.iSwitch_jyzcdy==NORMAL_OPEN)
    {
         if(buffer_read[9]==1)
         {
             if(stru_ChainSetData.iJyzcdyVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strjyzcdy);//静压轴承低压-外部(序号8)
                  cnt_proc++;
                  printf("##CheckProcExist()::iJyzcdyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iJyzcdyVal,cnt_proc);
             }
         }
    }
    else if(stru_ChainSetData.iSwitch_jyzcdy==NORMAL_CLOSE)
    {
        if(buffer_read[9]==0)
         {
             if(stru_ChainSetData.iJyzcdyVal==SWITCH_ON)
             {
                  strlistProcType.append(m_strjyzcdy);//静压轴承低压-外部(序号8)
                  cnt_proc++;
                  printf("##CheckProcExist()::iJyzcdyVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iJyzcdyVal,cnt_proc);
             }
         }
    }
    if(stru_ChainSetData.iSwitch_zgmenbh==NORMAL_OPEN)
    {
         if(buffer_read[10]==1)
         {
             if(stru_ChainSetData.iZgMenbVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strmbh);  //主柜门保护-内部(序号12)
                 cnt_proc++;
                 printf("##CheckProcExist()::iMenbVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iZgMenbVal,cnt_proc);
             }
         }
    }
    else if(stru_ChainSetData.iSwitch_zgmenbh==NORMAL_CLOSE)
    {
         if(buffer_read[10]==0)
         {
             if(stru_ChainSetData.iZgMenbVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strmbh);  //主柜门保护-内部(序号12)
                 cnt_proc++;
                 printf("##CheckProcExist()::iMenbVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iZgMenbVal,cnt_proc);
             }
         }
    }
    if(stru_ChainSetData.iSwitch_htqyw==NORMAL_OPEN)
    {
        if(buffer_read[12]==1)
         {
             if(stru_ChainSetData.iHtqywVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strhtqyw);  //主柜整流器过温-内部(序号14),add by 2019.05.25
                 cnt_proc++;
                 printf("##CheckProcExist()::iHtqywVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iHtqywVal,cnt_proc);
             }
         }
    }
    else if(stru_ChainSetData.iSwitch_htqyw==NORMAL_CLOSE)
    {
        if(buffer_read[12]==0)
         {
             if(stru_ChainSetData.iHtqywVal==SWITCH_ON)
             {
                 strlistProcType.append(m_strhtqyw);  //主柜整流器过温-内部(序号14),add by 2019.05.25
                 cnt_proc++;
                 printf("##CheckProcExist()::iHtqywVal=%d--cnt_proc=%d##\n",stru_ChainSetData.iHtqywVal,cnt_proc);
             }
         }
    }
     if(cnt_proc==0)
     {
         //不存在外部保护,add by 2019.05.14
         return false;
     }
     else
     {
         //存在外部保护, add by 2019.05.14
         return true;
     }
}

//检测是否存在三相电压不平衡(三相电取均值后的5%)
bool CJudgeProc::CheckVoltImbalance(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt)
{
    float fsum=0.00;
    float favg=0.00;
    fsum+=fPhaseAVolt;
    fsum+=fPhaseBVolt;
    fsum+=fPhaseCVolt;
    favg=fsum/3.0;
    float ftempA=100*qAbs(fPhaseAVolt-favg)/favg;
    if((ftempA-g_struBasicPara.fVoltimbalance)>DELT_FVALUE)
    {
         return true;
    }
    float ftempB=100*qAbs(fPhaseBVolt-favg)/favg;
    if((ftempB-g_struBasicPara.fVoltimbalance)>DELT_FVALUE)
    {
         return true;
    }
    float ftempC=100*qAbs(fPhaseCVolt-favg)/favg;
    if((ftempC-g_struBasicPara.fVoltimbalance)>DELT_FVALUE)
    {
         return true;
    }
    return false;
}
//新检测是否存在三相电压不平衡(三相电取均值后的5%)，add by zw 2022.02.23
bool CJudgeProc::newCheckVoltImbalance(STRU_ADDATANEW stru_newaddata)
{
    float fsum=0.00;
    float favg=0.00;
    fsum+=stru_newaddata.fTriPhaseAVolDC;
    fsum+=stru_newaddata.fTriPhaseBVolDC;
    fsum+=stru_newaddata.fTriPhaseCVolDC;
    favg=fsum/3.0;
    float ftempA=100*qAbs(stru_newaddata.fTriPhaseAVolDC-favg)/favg;
    if((ftempA-g_struBasicPara.fVoltimbalance)>DELT_FVALUE)
    {
         return true;
    }
    float ftempB=100*qAbs(stru_newaddata.fTriPhaseBVolDC-favg)/favg;
    if((ftempB-g_struBasicPara.fVoltimbalance)>DELT_FVALUE)
    {
         return true;
    }
    float ftempC=100*qAbs(stru_newaddata.fTriPhaseCVolDC-favg)/favg;
    if((ftempC-g_struBasicPara.fVoltimbalance)>DELT_FVALUE)
    {
         return true;
    }
    return false;
}

//检测是否存在三相电压过高
bool CJudgeProc::CheckOverVolt(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt)
{
    float fsum=0.00;
    float favg=0.00;
    fsum+=fPhaseAVolt;
    fsum+=fPhaseBVolt;
    fsum+=fPhaseCVolt;
    favg=fsum/3.0;
    float fdelt=favg-g_struBasicPara.fThreevoltUp;
    if(fdelt>DELT_FVALUE)
    {
        return true;
    }
    return false;
}
//新检测是否存在三相电压过高，add by zw 2022.02.23
bool CJudgeProc::newCheckOverVolt(STRU_ADDATANEW stru_newaddata)
{
    float fsum=0.00;
    float favg=0.00;
    fsum+=stru_newaddata.fTriPhaseAVolDC;
    fsum+=stru_newaddata.fTriPhaseBVolDC;
    fsum+=stru_newaddata.fTriPhaseCVolDC;
    favg=fsum/3.0;
    float fdelt=favg-g_struBasicPara.fThreevoltUp;
    if(fdelt>DELT_FVALUE)
    {
        return true;
    }
    return false;
}
//检测是否存在三相电压过低
bool CJudgeProc::CheckLowVolt(float fPhaseAVolt,float fPhaseBVolt,float fPhaseCVolt)
{
    float fsum=0.00;
    float favg=0.00;
    fsum+=fPhaseAVolt;
    fsum+=fPhaseBVolt;
    fsum+=fPhaseCVolt;
    favg=fsum/3.0;
    float fdelt=favg-g_struBasicPara.fThreevoltLow;
    if(fdelt<DELT_FVALUE)
    {
        return true;
    }
    return false;
}
//新检测是否存在三相电压过低，add by zw 2022.02.23
bool CJudgeProc::newCheckLowVolt(STRU_ADDATANEW stru_newaddata)
{
    float fsum=0.00;
    float favg=0.00;
    fsum+=stru_newaddata.fTriPhaseAVolDC;
    fsum+=stru_newaddata.fTriPhaseBVolDC;
    fsum+=stru_newaddata.fTriPhaseCVolDC;
    favg=fsum/3.0;
    float fdelt=favg-g_struBasicPara.fThreevoltLow;
    if(fdelt<DELT_FVALUE)
    {
        return true;
    }
    return false;
}
//检测是否存在母线电压过高
bool CJudgeProc::CheckBusVoltUpExist(STR_GPIODATA GPIOData,int &iBusVoltUpCnt)
{
     float fdeltTemp=0.00;
     iBusVoltUpCnt=0;
#ifdef UBUNTU_DEV //Compiler Switch
     if(m_nTestFlag==TEST_FLAG)
     {
          //--测试态，只有分柜1满足测试条件 add by 2019.05.14
          fdeltTemp=GPIOData.fSlaveBusVolt[0]-g_struBasicPara.fBusvoltUp;
         /* printf("fdeltTemp=%6.3f-fSlaveBusVolt[0]=%6.3f-BUS_VOLT_UP_LIMIT=%6.3f",
                      fdeltTemp,GPIOData.fSlaveBusVolt[0],BUS_VOLT_UP_LIMIT);*/
          if(fdeltTemp>DELT_FVALUE)
            {
               iBusVoltUpCnt++;
              //printf("####sub1-OVER BUS VOLTAGE####\n");
             }
      }
     else
      {
         //--非测试态,4个分柜作逐一检测
        if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
        {
         fdeltTemp=GPIOData.fSlaveBusVolt[0]-g_struBasicPara.fBusvoltUp;
         if(fdeltTemp>DELT_FVALUE)
         {
           iBusVoltUpCnt++;
           //printf("####sub1-OVER BUS VOLTAGE####\n");
         }
        }

        if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
        {
         fdeltTemp=GPIOData.fSlaveBusVolt[1]-g_struBasicPara.fBusvoltUp;
         if(fdeltTemp>DELT_FVALUE)
         {
           iBusVoltUpCnt++;
           //printf("####sub2-OVER BUS VOLTAGE####\n");
         }
        }

        if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
        {
         fdeltTemp=GPIOData.fSlaveBusVolt[2]-g_struBasicPara.fBusvoltUp;
         if(fdeltTemp>DELT_FVALUE)
         {
           iBusVoltUpCnt++;
           //printf("####sub3-OVER BUS VOLTAGE####\n");
         }
        }

        if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
        {
         fdeltTemp=GPIOData.fSlaveBusVolt[3]-g_struBasicPara.fBusvoltUp;
         if(fdeltTemp>DELT_FVALUE)
         {
           iBusVoltUpCnt++;
           //printf("####sub4-OVER BUS VOLTAGE####\n");
         }
        }
      }
#endif  //Compiler Switch
     if(iBusVoltUpCnt==0)
     {
         return false;
     }
     else
     {
         return true;
     }
}
//新检测是否存在母线电压过高 add by zw 20220223
bool CJudgeProc::newCheckBusVoltUpExist(STRU_ADDATANEW stru_newaddata, int &iBusVoltUpCnt)
{
    float fdeltTemp=0.00;
    iBusVoltUpCnt=0;
#ifdef UBUNTU_DEV //Compiler Switch
    if(m_nTestFlag==TEST_FLAG)
    {
         //--测试态，只有分柜1满足测试条件 add by 2019.05.14
         fdeltTemp=stru_newaddata.fSlave1VolDC-g_struBasicPara.fBusvoltUp;
        /* printf("fdeltTemp=%6.3f-fSlaveBusVolt[0]=%6.3f-BUS_VOLT_UP_LIMIT=%6.3f",
                     fdeltTemp,GPIOData.fSlaveBusVolt[0],BUS_VOLT_UP_LIMIT);*/
         if(fdeltTemp>DELT_FVALUE)
           {
              iBusVoltUpCnt++;
             //printf("####sub1-OVER BUS VOLTAGE####\n");
            }
     }
    else
     {
        //--非测试态,4个分柜作逐一检测
       if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
       {
        fdeltTemp=stru_newaddata.fSlave1VolDC-g_struBasicPara.fBusvoltUp;
        if(fdeltTemp>DELT_FVALUE)
        {
          iBusVoltUpCnt++;
          //printf("####sub1-OVER BUS VOLTAGE####\n");
        }
       }

       if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
       {
        fdeltTemp=stru_newaddata.fSlave2VolDC-g_struBasicPara.fBusvoltUp;
        if(fdeltTemp>DELT_FVALUE)
        {
          iBusVoltUpCnt++;
          //printf("####sub2-OVER BUS VOLTAGE####\n");
        }
       }

       if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
       {
        fdeltTemp=stru_newaddata.fSlave3VolDC-g_struBasicPara.fBusvoltUp;
        if(fdeltTemp>DELT_FVALUE)
        {
          iBusVoltUpCnt++;
          //printf("####sub3-OVER BUS VOLTAGE####\n");
        }
       }

       if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
       {
        fdeltTemp=stru_newaddata.fSlave4VolDC-g_struBasicPara.fBusvoltUp;
        if(fdeltTemp>DELT_FVALUE)
        {
          iBusVoltUpCnt++;
          //printf("####sub4-OVER BUS VOLTAGE####\n");
        }
       }
     }
#endif  //Compiler Switch
    if(iBusVoltUpCnt==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//检测是否存在母线电压过低
bool CJudgeProc::CheckBusVoltDownExist(STR_GPIODATA GPIOData,int &iBusVoltDownCnt)
{
iBusVoltDownCnt=0;
#ifdef UBUNTU_DEV //Compiler Switch
   if(m_nTestFlag==TEST_FLAG)
    {
      //--测试态，只有分柜1满足测试条件 add by 2019.05.14
       //printf("GPIOData.fSlaveBusVolt[0]=%f-BUS_VOLT_DOWN_LIMIT=%f\n",GPIOData.fSlaveBusVolt[0],BUS_VOLT_DOWN_LIMIT);
       if((GPIOData.fSlaveBusVolt[0]-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
       {
            iBusVoltDownCnt++;
            //printf("####sub1-LOW BUS VOLTAGE####\n");
       }
    }
    else
    {
      //--非测试态，4个分柜作逐一检测
        if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
        {
          if((GPIOData.fSlaveBusVolt[0]-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
            {
                iBusVoltDownCnt++;
                //printf("####sub1-LOW BUS VOLTAGE####\n");
            }
        }

        if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
        {
          if((GPIOData.fSlaveBusVolt[1]-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
            {
                iBusVoltDownCnt++;
                //printf("####sub2-LOW BUS VOLTAGE####\n");
            }
        }

        if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
        {
          if((GPIOData.fSlaveBusVolt[2]-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
            {
                iBusVoltDownCnt++;
                //printf("####sub3-LOW BUS VOLTAGE####\n");
            }
        }

        if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
        {
          if((GPIOData.fSlaveBusVolt[3]-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
            {
                iBusVoltDownCnt++;
                //printf("####sub4-LOW BUS VOLTAGE####\n");
            }
        }
    }
#endif  //Compiler Switch
    if(iBusVoltDownCnt==0)
     {
         return false;
     }
     else
     {
         return true;
     }
}
//新检测是否存在母线电压过低 add by zw 20220223
bool CJudgeProc::newCheckBusVoltDownExist(STRU_ADDATANEW stru_newaddata, int &iBusVoltDownCnt)
{
    iBusVoltDownCnt=0;
    #ifdef UBUNTU_DEV //Compiler Switch
       if(m_nTestFlag==TEST_FLAG)
        {
          //--测试态，只有分柜1满足测试条件 add by 2019.05.14
           //printf("GPIOData.fSlaveBusVolt[0]=%f-BUS_VOLT_DOWN_LIMIT=%f\n",GPIOData.fSlaveBusVolt[0],BUS_VOLT_DOWN_LIMIT);
           if((stru_newaddata.fSlave1VolDC-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
           {
                iBusVoltDownCnt++;
                //printf("####sub1-LOW BUS VOLTAGE####\n");
           }
        }
        else
        {
          //--非测试态，4个分柜作逐一检测
            if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
            {
              if((stru_newaddata.fSlave1VolDC-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
                {
                    iBusVoltDownCnt++;
                    //printf("####sub1-LOW BUS VOLTAGE####\n");
                }
            }

            if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
            {
              if((stru_newaddata.fSlave2VolDC-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
                {
                    iBusVoltDownCnt++;
                    //printf("####sub2-LOW BUS VOLTAGE####\n");
                }
            }

            if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
            {
              if((stru_newaddata.fSlave3VolDC-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
                {
                    iBusVoltDownCnt++;
                    //printf("####sub3-LOW BUS VOLTAGE####\n");
                }
            }

            if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
            {
              if((stru_newaddata.fSlave4VolDC-g_struBasicPara.fBusvoltLow)<DELT_FVALUE)
                {
                    iBusVoltDownCnt++;
                    //printf("####sub4-LOW BUS VOLTAGE####\n");
                }
            }
        }
    #endif  //Compiler Switch
        if(iBusVoltDownCnt==0)
         {
             return false;
         }
         else
         {
             return true;
         }
}
//检测是否存在母线电压不均衡
bool CJudgeProc::CheckBusVoltUnbalance(STR_GPIODATA GPIOData,int &iUnbalanceCnt)
{
    iUnbalanceCnt=0;
    float ftempAbs=0.0;

#ifdef UBUNTU_DEV //Compiler Switch
    if(m_nTestFlag==TEST_FLAG)
    {
         //--测试态，只有分柜1满足测试条件 add by 2019.05.14
        ftempAbs=qAbs(GPIOData.fSlaveActBusVolt[0]+GPIOData.fSlaveNegBusVolt[0]);
       if((ftempAbs-g_struBasicPara.fBusImbalance)>DELT_FVALUE)
        {
           printf("fSlaveActBusVolt[0]=%3.2f-fSlaveNegBusVolt[0]=%3.2f-ftempAbs=%3.2f-fBusImbalance=%3.2f\n",
               GPIOData.fSlaveActBusVolt[0],
               GPIOData.fSlaveNegBusVolt[0],
               ftempAbs,
               g_struBasicPara.fBusImbalance);
           //printf("####sub1-UNBALANCE BUS VOLTAGE####\n");
           iUnbalanceCnt++;
        }
    }
    else
    {
        //--非测试态，4个分柜作逐一检测
        if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
        {
          ftempAbs=qAbs(GPIOData.fSlaveActBusVolt[0]+GPIOData.fSlaveNegBusVolt[0]);
          if((ftempAbs-g_struBasicPara.fBusImbalance)>DELT_FVALUE)
            {
                iUnbalanceCnt++;
                //printf("####sub1-UNBALANCE BUS VOLTAGE####\n");
            }
        }

        if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
        {
          ftempAbs=qAbs(GPIOData.fSlaveActBusVolt[1]+GPIOData.fSlaveNegBusVolt[1]);
          if((ftempAbs-g_struBasicPara.fBusImbalance)>DELT_FVALUE)
            {
                iUnbalanceCnt++;
                //printf("####sub2-UNBALANCE BUS VOLTAGE####\n");
            }
        }

        if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
        {
          ftempAbs=qAbs(GPIOData.fSlaveActBusVolt[2]+GPIOData.fSlaveNegBusVolt[2]);
          if((ftempAbs-g_struBasicPara.fBusImbalance)>DELT_FVALUE)
            {
                iUnbalanceCnt++;
                //printf("####sub3-UNBALANCE BUS VOLTAGE####\n");
            }
        }

        if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
        {
          ftempAbs=qAbs(GPIOData.fSlaveActBusVolt[3]+GPIOData.fSlaveNegBusVolt[3]);
          if((ftempAbs-g_struBasicPara.fBusImbalance)>DELT_FVALUE)
            {
                iUnbalanceCnt++;
                //printf("####sub4-UNBALANCE BUS VOLTAGE####\n");
            }
        }
    }
#endif  //Compiler Switch
    if(iUnbalanceCnt==0)
     {
         return false;
     }
     else
     {
         return true;
     }
}
//新检测是否存在母线电压不均衡 add by zw 20220223
bool CJudgeProc::newCheckBusVoltUnbalance(STRU_ADDATANEW stru_newaddata)
{
    return false;
}
//检测分柜输出电流是否过高
bool CJudgeProc::CheckOutputCurrentOver(STR_GPIODATA GPIOData,int &iCurrOverCnt)
{
    iCurrOverCnt=0;
#ifdef UBUNTU_DEV //Compiler Switch
    if(m_nTestFlag==TEST_FLAG)
    {
        //--测试态，只有分柜1满足测试条件 add by 2019.05.18
        if((GPIOData.fSlaveCurrent[0]-g_struBasicPara.fSub1CabinetcurrentUp)>DELT_FVALUE)
        {
             iCurrOverCnt++;
             //printf("####sub1-OVER OUTPUT CURRENT####\n");
        }
    }
    else
    {
        //--非测试态，4个分柜作一并检测
        if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
        {
                if((GPIOData.fSlaveCurrent[0]-g_struBasicPara.fSub1CabinetcurrentUp)>DELT_FVALUE)
                {
                    iCurrOverCnt++;
                    //printf("####sub1-OVER OUTPUT CURRENT####\n");
                }
        }

        if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
        {
                if((GPIOData.fSlaveCurrent[1]-g_struBasicPara.fSub2CabinetcurrentUp)>DELT_FVALUE)
                {
                    iCurrOverCnt++;
                    //printf("####sub2-OVER OUTPUT CURRENT####\n");
                }
        }

        if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
        {
                if((GPIOData.fSlaveCurrent[2]-g_struBasicPara.fSub3CabinetcurrentUp)>DELT_FVALUE)
                {
                    iCurrOverCnt++;
                    //printf("####sub3-OVER OUTPUT CURRENT####\n");
                }
        }

        if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
        {
                if((GPIOData.fSlaveCurrent[3]-g_struBasicPara.fSub4CabinetcurrentUp)>DELT_FVALUE)
                {
                    iCurrOverCnt++;
                    //printf("####sub4-OVER OUTPUT CURRENT####\n");
                }
        }
    }
#endif  //Compiler Switch
    if(iCurrOverCnt==0)
     {
         return false;
     }
     else
     {
         return true;
     }
}
//新检测分柜输出电流是否过高 add by zw 20220223
bool CJudgeProc::newCheckOutputCurrentOver(STRU_ADDATANEW stru_newaddata, int &iCurrOverCnt)
{
    iCurrOverCnt=0;
#ifdef UBUNTU_DEV //Compiler Switch
    if(m_nTestFlag==TEST_FLAG)
    {
        //--测试态，只有分柜1满足测试条件 add by 2019.05.18
        if((stru_newaddata.fSlave1CurDC-g_struBasicPara.fSub1CabinetcurrentUp)>DELT_FVALUE)
        {
             iCurrOverCnt++;
             //printf("####sub1-OVER OUTPUT CURRENT####\n");
        }
    }
    else
    {
        //--非测试态，4个分柜作一并检测
        if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
        {
                if((stru_newaddata.fSlave1CurDC-g_struBasicPara.fSub1CabinetcurrentUp)>DELT_FVALUE)
                {
                    iCurrOverCnt++;
                    //printf("####sub1-OVER OUTPUT CURRENT####\n");
                }
        }

        if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
        {
                if((stru_newaddata.fSlave2CurDC-g_struBasicPara.fSub2CabinetcurrentUp)>DELT_FVALUE)
                {
                    iCurrOverCnt++;
                    //printf("####sub2-OVER OUTPUT CURRENT####\n");
                }
        }

        if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
        {
                if((stru_newaddata.fSlave3CurDC-g_struBasicPara.fSub3CabinetcurrentUp)>DELT_FVALUE)
                {
                    iCurrOverCnt++;
                    //printf("####sub3-OVER OUTPUT CURRENT####\n");
                }
        }

        if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
        {
                if((stru_newaddata.fSlave4CurDC-g_struBasicPara.fSub4CabinetcurrentUp)>DELT_FVALUE)
                {
                    iCurrOverCnt++;
                    //printf("####sub4-OVER OUTPUT CURRENT####\n");
                }
        }
    }
#endif  //Compiler Switch
    if(iCurrOverCnt==0)
     {
         return false;
     }
     else
     {
         return true;
     }
}
//检测励磁开路保护是否存在
bool CJudgeProc::CheckExcitProcExist(STR_GPIODATA GPIOData)
{
    if((GPIOData.fExcitCurrent-EXCIT_CURRENT_LIMIT)<DELT_FVALUE)
    {
        return true;
    }
    else
    {
        return false;
//        return true;//测试
    }
}
//新检测励磁开路保护是否存在 add by zw 20220223
bool CJudgeProc::newCheckExcitProcExist(STRU_ADDATANEW stru_newaddata)
{
//    if((stru_newaddata.fExcitCur-EXCIT_CURRENT_LIMIT)<DELT_FVALUE)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
    return false;
}
//新检测是否存在励磁电压来控制励磁指示灯 add by zw 20220223
void CJudgeProc::newCheckExcitVolExist()
{
    if((g_newaddata.fExcitVolt-EXCIT_VOLTAGE_LIMIT)<DELT_FVALUE)
    {
        g_newaddata.iExcitationState = LED_RED;
    }
    else
    {
        g_newaddata.iExcitationState = LED_GREEN;
    }
//    stru_newaddata.iExcitationState = LED_GREEN;
}
//检测是否存在从柜门保护
bool CJudgeProc::CheckSubDoorProcExist(STR_GPIODATA GPIOData,STRU_CHAINSETDATA stru_ChainSetData)
{
     int cnt=0;
     if((GPIOData.iSlaveDI[1]==1)&&(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG))
     {//存在分柜1门保护
         cnt++;
     }
     if((GPIOData.iSlaveDI[2]==1)&&(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG))
     {//存在分柜2门保护
         cnt++;
     }
     if((GPIOData.iSlaveDI[4]==1)&&(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG))
     {//存在分柜3门保护
         cnt++;
     }
     if((GPIOData.iSlaveDI[7]==1)&&(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG))
     {//存在分柜4门保护
         cnt++;
     }
     if(cnt>0)
     {
         if(stru_ChainSetData.iSubMenbVal==SWITCH_ON)
         {
             return true;
         }
         return false;
     }
     else
     {
        return false;
     }
}
//新检测是否存在从柜门保护 add by zw 20220223
bool CJudgeProc::newCheckSubDoorProcExist(STRU_NEWFAULTSTATUS stru_newfaultdata, STRU_NEWCHASETDATA stru_newChainSetData)
{
    return false;
}
//检测是否存在从柜整流桥过温
bool CJudgeProc::CheckSubRectBridgeOverheat(STR_GPIODATA GPIOData,STRU_CHAINSETDATA stru_ChainSetData)
{
    int cnt=0;
     if((GPIOData.iSlaveDI[0]==1)&&(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG))
     {//存在分柜1整流器过温
         cnt++;
     }
     if((GPIOData.iSlaveDI[3]==1)&&(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG))
     {//存在分柜2整流器过温
         cnt++;
     }
     if((GPIOData.iSlaveDI[5]==1)&&(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG))
     {//存在分柜3整流器过温
         cnt++;
     }
     if((GPIOData.iSlaveDI[6]==1)&&(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG))
     {//存在分柜4整流器过温
         cnt++;
     }
     if(cnt>0)
     {
         if(stru_ChainSetData.iSubzlqgwVal==SWITCH_ON)
         {
             return true;
         }
         return false;
     }
     else
     {
        return false;
     }
}
//新检测是否存在冷却保护 add by zw 20220223
bool CJudgeProc::newCheckXtlqProcExist(STRU_NEWCHASETDATA stru_newChainSetData)
{
    int cnt=0;
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {
        if(stru_newChainSetData.isw_Xtlq==NORMAL_OPEN)
        {
            if(g_newfaultstatus.iFaultValue[1]==1)
             {
                 if(stru_newChainSetData.iXtlqVal==SWITCH_ON)
                 {
                     g_newfaultstatus.iVIBCUFlag=LED_RED;
                     cnt++;
                     printf("##newCheckXtlqProcExist()::iXtlqVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iXtlqVal,cnt);
                 }
            }
            else
               g_newfaultstatus.iVIBCUFlag=LED_GREEN;
        }
        else if(stru_newChainSetData.isw_Xtlq==NORMAL_CLOSE)
        {
            if(g_newfaultstatus.iFaultValue[1]==0)
                {
                    if(stru_newChainSetData.iXtlqVal==SWITCH_ON)
                    {
                        g_newfaultstatus.iVIBCUFlag=LED_RED;
                        cnt++;
                        printf("##newCheckXtlqProcExist()::iXtlqVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iXtlqVal,cnt);
                    }
                }
            else
               g_newfaultstatus.iVIBCUFlag=LED_GREEN;
        }
    }
    if(cnt>0)
    {
       return true;
    }
    else
    {
       return false;
    }
}
//新检测是否存在从柜整流桥过温 add by zw 20220223
bool CJudgeProc::newCheckSubRectBridgeOverheat(STRU_NEWCHASETDATA stru_newChainSetData)
{
    int cnt=0;
    if(g_struBasicPara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {
        if(stru_newChainSetData.isw_C1zlqgw==NORMAL_OPEN)
        {
            if(g_newfaultstatus.iFaultValue[15]==1)
             {
                 if(stru_newChainSetData.iC1zlqgwVal==SWITCH_ON)
                 {
                     g_newfaultstatus.iOT1Flag=LED_RED;
                     cnt++;
                     printf("##newCheckSubRectBridgeOverheat()::iC1zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC1zlqgwVal,cnt);
                 }
            }
            else
                g_newfaultstatus.iOT1Flag=LED_GREEN;
        }
        else if(stru_newChainSetData.isw_C1zlqgw==NORMAL_CLOSE)
        {
            if(g_newfaultstatus.iFaultValue[15]==0)
                {
                    if(stru_newChainSetData.iC1zlqgwVal==SWITCH_ON)
                    {
                        g_newfaultstatus.iOT1Flag=LED_RED;
                        cnt++;
                        printf("##newCheckSubRectBridgeOverheat()::iC1zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC1zlqgwVal,cnt);
                    }
                }
            else
                g_newfaultstatus.iOT1Flag=LED_GREEN;
        }
    }
    if(g_struBasicPara.iSub2CabOpen==SUBCABOPEN_FLAG)
    {
        if(stru_newChainSetData.isw_C2zlqgw==NORMAL_OPEN)
        {
            if(g_newfaultstatus.iFaultValue[16]==1)
             {
                 if(stru_newChainSetData.iC2zlqgwVal==SWITCH_ON)
                 {
                     g_newfaultstatus.iOT2Flag=LED_RED;
                     cnt++;
                     printf("##newCheckSubRectBridgeOverheat()::iC2zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC2zlqgwVal,cnt);
                 }
            }
            else
                g_newfaultstatus.iOT2Flag=LED_GREEN;
        }
        else if(stru_newChainSetData.isw_C2zlqgw==NORMAL_CLOSE)
        {
            if(g_newfaultstatus.iFaultValue[16]==0)
                {
                    if(stru_newChainSetData.iC2zlqgwVal==SWITCH_ON)
                    {
                        g_newfaultstatus.iOT2Flag=LED_RED;
                        cnt++;
                        printf("##newCheckSubRectBridgeOverheat()::iC2zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC2zlqgwVal,cnt);
                    }
                }
            else
                g_newfaultstatus.iOT2Flag=LED_GREEN;
        }
    }
    if(g_struBasicPara.iSub3CabOpen==SUBCABOPEN_FLAG)
    {
        if(stru_newChainSetData.isw_C3zlqgw==NORMAL_OPEN)
        {
            if(g_newfaultstatus.iFaultValue[17]==1)
             {
                 if(stru_newChainSetData.iC3zlqgwVal==SWITCH_ON)
                 {
                     g_newfaultstatus.iOT3Flag=LED_RED;
                     cnt++;
                     printf("##newCheckSubRectBridgeOverheat()::iC3zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC3zlqgwVal,cnt);
                 }
            }
            else
                g_newfaultstatus.iOT3Flag=LED_GREEN;
        }
        else if(stru_newChainSetData.isw_C3zlqgw==NORMAL_CLOSE)
        {
            if(g_newfaultstatus.iFaultValue[17]==0)
                {
                    if(stru_newChainSetData.iC3zlqgwVal==SWITCH_ON)
                    {
                        g_newfaultstatus.iOT3Flag=LED_RED;
                        cnt++;
                        printf("##newCheckSubRectBridgeOverheat()::iC3zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC3zlqgwVal,cnt);
                    }
                }
            else
                g_newfaultstatus.iOT3Flag=LED_GREEN;
        }
    }
    if(g_struBasicPara.iSub4CabOpen==SUBCABOPEN_FLAG)
    {
        if(stru_newChainSetData.isw_C4zlqgw==NORMAL_OPEN)
        {
            if(g_newfaultstatus.iFaultValue[18]==1)
             {
                 if(stru_newChainSetData.iC4zlqgwVal==SWITCH_ON)
                 {
                     g_newfaultstatus.iOT4Flag=LED_RED;
                     cnt++;
                     printf("##newCheckSubRectBridgeOverheat()::iC4zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC4zlqgwVal,cnt);
                 }
            }
            else
                g_newfaultstatus.iOT4Flag=LED_GREEN;
        }
        else if(stru_newChainSetData.isw_C4zlqgw==NORMAL_CLOSE)
        {
            if(g_newfaultstatus.iFaultValue[18]==0)
                {
                    if(stru_newChainSetData.iC4zlqgwVal==SWITCH_ON)
                    {
                        g_newfaultstatus.iOT4Flag=LED_RED;
                        cnt++;
                        printf("##newCheckSubRectBridgeOverheat()::iC4zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC4zlqgwVal,cnt);
                    }
                }
            else
                g_newfaultstatus.iOT4Flag=LED_GREEN;
        }
    }
     if(cnt>0)
     {
        return true;
     }
     else
     {
        return false;
     }
}
//检测是否存在通用模块保护(除了序号29-模块直流欠压，目前只考虑1个功率模块)
bool  CJudgeProc::CheckGenModuleProcExist(int nModuleNum,STRU_FAULTSTATUS *pStru_FaultDATA,QStringList &strlistGenModuProc)
{
#ifdef UBUNTU_DEV //Compiler Switch
     int iIGBTdriprocCnt=0;
     strlistGenModuProc.clear();
      QString strtemp;
     for(int i=0;i<nModuleNum;i++)
     {
         if(pStru_FaultDATA[i].iDCovervoltFlag)
         {
          //--输入直流过压
            strtemp=QApplication::translate("faultconditionForm", "\350\276\223\345\205\245\347\233\264\346\265\201\350\277\207\345\216\213",
                 0, QApplication::UnicodeUTF8);
            strlistGenModuProc.append(strtemp);
            return true;
          }
         if(pStru_FaultDATA[i].iOutovervoltFlag)
         {
          //--输出过压
            strtemp=QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\350\277\207\345\216\213",
                 0, QApplication::UnicodeUTF8);
            strlistGenModuProc.append(strtemp);
            return true;
          }

              //--同时判断6个IGBT驱动保护
        if(pStru_FaultDATA[i].iIGBT1driprocFlag)
         {
            iIGBTdriprocCnt++;
            if(g_iLangChange==1)
            {
                strtemp=QApplication::translate("faultconditionForm", "IGBT1\351\251\261\345\212\250\344\277\235\346\212\244",
                     0,
                     QApplication::UnicodeUTF8);
            }
            else
            {
                strtemp="IGBT1 drive protection";
            }
            strlistGenModuProc.append(strtemp);
         }
      if(pStru_FaultDATA[i].iIGBT2driprocFlag)
         {
            iIGBTdriprocCnt++;
            if(g_iLangChange==1)
            {
                strtemp=QApplication::translate("faultconditionForm", "IGBT2\351\251\261\345\212\250\344\277\235\346\212\244",
                     0,
                     QApplication::UnicodeUTF8);
            }
            else
            {
                strtemp="IGBT2 drive protection";
            }
            strlistGenModuProc.append(strtemp);
          }
       if(pStru_FaultDATA[i].iIGBT3driprocFlag)
         {
            iIGBTdriprocCnt++;
            if(g_iLangChange==1)
            {
                strtemp=QApplication::translate("faultconditionForm", "IGBT3\351\251\261\345\212\250\344\277\235\346\212\244",
                     0,
                     QApplication::UnicodeUTF8);
            }
            else
            {
                strtemp="IGBT3 drive protection";
            }
            strlistGenModuProc.append(strtemp);
          }
       if(pStru_FaultDATA[i].iIGBT4driprocFlag)
         {
            iIGBTdriprocCnt++;
            if(g_iLangChange==1)
            {
                strtemp=QApplication::translate("faultconditionForm", "IGBT4\351\251\261\345\212\250\344\277\235\346\212\244",
                     0,
                     QApplication::UnicodeUTF8);
            }
            else
            {
                strtemp="IGBT4 drive protection";
            }
            strlistGenModuProc.append(strtemp);
         }
        if(pStru_FaultDATA[i].iIGBT5driprocFlag)
          {
            iIGBTdriprocCnt++;
            if(g_iLangChange==1)
            {
                strtemp=QApplication::translate("faultconditionForm", "IGBT5\351\251\261\345\212\250\344\277\235\346\212\244",
                     0,
                     QApplication::UnicodeUTF8);
            }
            else
            {
                strtemp="IGBT5 drive protection";
            }
            strlistGenModuProc.append(strtemp);
           }
        if(pStru_FaultDATA[i].iIGBT6driprocFlag)
          {
            iIGBTdriprocCnt++;
            if(g_iLangChange==1)
            {
                strtemp=QApplication::translate("faultconditionForm", "IGBT6\351\251\261\345\212\250\344\277\235\346\212\244",
                     0,
                     QApplication::UnicodeUTF8);
            }
            else
            {
                strtemp="IGBT6 drive protection";
            }
            strlistGenModuProc.append(strtemp);
          }
     }
    if(iIGBTdriprocCnt>0)
    {
        return true;
    }
#endif  //Compiler Switch
   return false;
}
void CJudgeProc::judgeLangChange()
{
    if(g_iLangChange==1)
    {
        //S紧急停机
        m_strsjjtj=QApplication::translate("mainWindow",
            "\347\211\271\347\264\247\346\200\245\345\201\234\346\234\272",
            0,
            QApplication::UnicodeUTF8);
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
         //主柜整流桥过温
         m_strhtqyw=QApplication::translate("mainWindow",
             "\344\270\273\346\237\234\346\225\264\346\265\201\346\241\245\350\277\207\346\270\251",
             0,
             QApplication::UnicodeUTF8);
         //系统冷却单元
         m_strxtlqdy=QApplication::translate("mainWindow",
             "\347\263\273\347\273\237\345\206\267\345\215\264\345\215\225\345\205\203",
             0,
             QApplication::UnicodeUTF8);
         //三相电压不平衡
         m_strVoltUnbalance=QApplication::translate("mainWindow",
             "\344\270\211\347\233\270\347\224\265\345\216\213\344\270\215\345\271\263\350\241\241",
             0,
             QApplication::UnicodeUTF8);
         //三相电压过高
         m_strVoltUp=QApplication::translate("mainWindow",
             "\344\270\211\347\233\270\347\224\265\345\216\213\350\277\207\351\253\230",
             0,
             QApplication::UnicodeUTF8);
         //三相电压过低
         m_strVoltDown=QApplication::translate("mainWindow",
             "\344\270\211\347\233\270\347\224\265\345\216\213\350\277\207\344\275\216",
             0,
             QApplication::UnicodeUTF8);
         //总输出电压过高
         m_strOutVoltUp=QApplication::translate("mainWindow",
             "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\345\216\213\350\277\207\351\253\230",
             0,
             QApplication::UnicodeUTF8);
         //总输出电流过高
         m_strOutCurrentUp=QApplication::translate("mainWindow",
             "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\346\265\201\350\277\207\351\253\230",
             0,
             QApplication::UnicodeUTF8);
         //励磁开路
         m_strExcitopen=QApplication::translate("mainWindow",
             "\345\212\261\347\243\201\345\274\200\350\267\257",
             0,
             QApplication::UnicodeUTF8);
         //从柜门保护
         m_strSubmbh=QApplication::translate("mainWindow",
             "\344\273\216\346\237\234\351\227\250\344\277\235\346\212\244",
             0,
             QApplication::UnicodeUTF8);
         //从柜整流桥过温
         m_strSubzlqgw=QApplication::translate("mainWindow",
             "\344\273\216\346\237\234\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251",
             0,
             QApplication::UnicodeUTF8);
         //从柜预留保护
         m_strSubylproc=QApplication::translate("mainWindow",
             "\344\273\216\346\237\234\351\242\204\347\225\231\344\277\235\346\212\244",
             0,
             QApplication::UnicodeUTF8);
         //母线电压过高
         m_strBusVoltUp=QApplication::translate("mainWindow",
             "\346\257\215\347\272\277\347\224\265\345\216\213\350\277\207\351\253\230",
             0,
             QApplication::UnicodeUTF8);
         //母线电压过低
         m_strBusVoltDown=QApplication::translate("mainWindow",
             "\346\257\215\347\272\277\347\224\265\345\216\213\350\277\207\344\275\216",
             0,
             QApplication::UnicodeUTF8);
         //母线电压不均衡
         m_strBusVoltUnbalance=QApplication::translate("mainWindow",
             "\346\257\215\347\272\277\344\270\215\345\235\207\350\241\241",
             0,
             QApplication::UnicodeUTF8);
         //分柜输出电流过高
         m_strSubCurrentUp=QApplication::translate("mainWindow",
             "\345\210\206\346\237\234\350\276\223\345\207\272\347\224\265\346\265\201\350\277\207\351\253\230",
             0,
             QApplication::UnicodeUTF8);
         //模块直流欠压,add by zqc 2019.07.15
         m_strModuleUnderVolt=QApplication::translate("mainWindow", "\346\250\241\345\235\227\347\233\264\346\265\201\346\254\240\345\216\213",
             0, QApplication::UnicodeUTF8);
    }
    else
    {
        //S紧急停机
         m_strsjjtj="S Emergency shutdown";
        //紧急停机
         m_strjjtj="Emergency shutdown";
        //滑台过位移
         m_strhtgwy="S.T. Overtravel";
         //振动台过位移
         m_strzdtgwy="VIB. Overtravel";
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
         //主柜整流桥过温
         m_strhtqyw="M.R. OverTEMP";
         //系统冷却单元
         m_strxtlqdy="S.C.U.";
         //三相电压不平衡
         m_strVoltUnbalance="Three-phase voltage imbalance";
         //三相电压过高
         m_strVoltUp="Three-phase overvoltage";
         //三相电压过低
         m_strVoltDown="Three phase voltage is too low";
         //总输出电压过高
         m_strOutVoltUp="Over-high total output voltage";
         //总输出电流过高
         m_strOutCurrentUp="Over-high total output current";
         //励磁开路
         m_strExcitopen="Cab Doors";
         //从柜门保护
         m_strSubmbh="C.R. OverTEMP";
         //从柜整流桥过温
         m_strSubzlqgw="Overheating of sub-cabinet rectifier bridge";
         //从柜预留保护
         m_strSubylproc="Reserved protection for sub-cabinet";
         //母线电压过高
         m_strBusVoltUp="Bus voltage is too high";
         //母线电压过低
         m_strBusVoltDown="Bus voltage is too low";
         //母线电压不均衡
         m_strBusVoltUnbalance="Bus voltage imbalance";
         //分柜输出电流过高
         m_strSubCurrentUp="Output current of sub-cabinet is too high";
         //模块直流欠压,add by zqc 2019.07.15
         m_strModuleUnderVolt="DC undervoltage of module";
    }
}
//add by zw 2022.02.23
bool CJudgeProc::newCheckExterProcExist(STRU_NEWCHASETDATA stru_newChainSetData,int cnt_proc,QStringList &strlistProcType)
{
    STR_STATUSDATA statusrec;
    cnt_proc=0;
    //需与连锁设置参数“与逻辑”
    //常开常闭触点切换
    if(stru_newChainSetData.isw_Xtlq==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[1]==1)
         {
             if(stru_newChainSetData.iXtlqVal==SWITCH_ON)
             {
                 g_newfaultstatus.iVIBCUFlag=LED_RED;
                 strlistProcType.append(m_strxtlqdy);//系统冷却故障-外部（故障号2）
                 statusrec=organizationStatusRecord(m_strxtlqdy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iXtlqVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iXtlqVal,cnt_proc);
             }
        }
        else
           g_newfaultstatus.iVIBCUFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Xtlq==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[1]==0)
            {
                if(stru_newChainSetData.iXtlqVal==SWITCH_ON)
                {
                    g_newfaultstatus.iVIBCUFlag=LED_RED;
                    strlistProcType.append(m_strxtlqdy);//系统冷却故障-外部（故障号2）
                    statusrec=organizationStatusRecord(m_strxtlqdy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iXtlqVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iXtlqVal,cnt_proc);
                }
            }
        else
           g_newfaultstatus.iVIBCUFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Zdtgw==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[2]==1)
         {
             if(stru_newChainSetData.iZdtgwVal==SWITCH_ON)
             {
                 g_newfaultstatus.iVIBOTFlag=LED_RED;
                 strlistProcType.append(m_strzdtgw);//振动台过温-外部（故障号3）
                 statusrec=organizationStatusRecord(m_strzdtgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iZdtgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iZdtgwVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iVIBOTFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Zdtgw==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[2]==0)
            {
                if(stru_newChainSetData.iZdtgwVal==SWITCH_ON)
                {
                    g_newfaultstatus.iVIBOTFlag=LED_RED;
                    strlistProcType.append(m_strzdtgw);//振动台过温-外部（故障号3）
                    statusrec=organizationStatusRecord(m_strzdtgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iZdtgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iZdtgwVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iVIBOTFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Zdtgwy==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[0]==1)
         {
             if(stru_newChainSetData.iZdtgwyVal==SWITCH_ON)
             {
                 g_newfaultstatus.iVIBODFlag=LED_RED;
                 strlistProcType.append(m_strzdtgwy);//振动台过位移-外部（故障号4）
                 statusrec=organizationStatusRecord(m_strzdtgwy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iZdtgwyVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iZdtgwyVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iVIBODFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Zdtgwy==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[0]==0)
            {
                if(stru_newChainSetData.iZdtgwyVal==SWITCH_ON)
                {
                    g_newfaultstatus.iVIBODFlag=LED_RED;
                    strlistProcType.append(m_strzdtgwy);//振动台过位移-外部（故障号4）
                    statusrec=organizationStatusRecord(m_strzdtgwy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iZdtgwyVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iZdtgwyVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iVIBODFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Htgwy==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[3]==1)
         {
             if(stru_newChainSetData.iHtgwyVal==SWITCH_ON)
             {
                 g_newfaultstatus.iSTODFlag=LED_RED;
                 strlistProcType.append(m_strhtgwy);//滑台过位移-外部（故障号5）
                 statusrec=organizationStatusRecord(m_strhtgwy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iHtgwyVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iHtgwyVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iSTODFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Htgwy==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[3]==0)
            {
                if(stru_newChainSetData.iHtgwyVal==SWITCH_ON)
                {
                    g_newfaultstatus.iSTODFlag=LED_RED;
                    strlistProcType.append(m_strhtgwy);//滑台过位移-外部（故障号5）
                    statusrec=organizationStatusRecord(m_strhtgwy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iHtgwyVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iHtgwyVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iSTODFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Htqy==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[4]==1)
         {
             if(stru_newChainSetData.iHtqyVal==SWITCH_ON)
             {
                 g_newfaultstatus.iSTUPFlag=LED_RED;
                 strlistProcType.append(m_strhtqy);//滑台欠压-外部（故障号6）
                 statusrec=organizationStatusRecord(m_strhtqy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iHtqyVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iHtqyVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iSTUPFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Htqy==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[4]==0)
            {
                if(stru_newChainSetData.iHtqyVal==SWITCH_ON)
                {
                    g_newfaultstatus.iSTUPFlag=LED_RED;
                    strlistProcType.append(m_strhtqy);//滑台欠压-外部（故障号6）
                    statusrec=organizationStatusRecord(m_strhtqy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iHtqyVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iHtqyVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iSTUPFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Htqyw==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[6]==1)
         {
             if(stru_newChainSetData.iHtqywVal==SWITCH_ON)
             {
                 g_newfaultstatus.iSTOLFlag=LED_RED;
                 strlistProcType.append(m_strhtdyw);//滑台欠液位-外部（故障号7）
                 statusrec=organizationStatusRecord(m_strhtdyw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iHtqywVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iHtqywVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iSTOLFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Htqyw==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[6]==0)
            {
                if(stru_newChainSetData.iHtqywVal==SWITCH_ON)
                {
                    g_newfaultstatus.iSTOLFlag=LED_RED;
                    strlistProcType.append(m_strhtdyw);//滑台欠液位-外部（故障号7）
                    statusrec=organizationStatusRecord(m_strhtdyw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iHtqywVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iHtqywVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iSTOLFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Htgw==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[5]==1)
         {
             if(stru_newChainSetData.iHtgwVal==SWITCH_ON)
             {
                 g_newfaultstatus.iSTOTFlag=LED_RED;
                 strlistProcType.append(m_strhtgw);//滑台过温-外部（故障号8）
                 statusrec=organizationStatusRecord(m_strhtgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iHtgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iHtgwVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iSTOTFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Htgw==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[5]==0)
            {
                if(stru_newChainSetData.iHtgwVal==SWITCH_ON)
                {
                    g_newfaultstatus.iSTOTFlag=LED_RED;
                    strlistProcType.append(m_strhtgw);//滑台过温-外部（故障号8）
                    statusrec=organizationStatusRecord(m_strhtgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iHtgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iHtgwVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iSTOTFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Gfrjbh==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[7]==1)
         {
             if(stru_newChainSetData.iGfrjbhVal==SWITCH_ON)
             {
                 g_newfaultstatus.iRELAYFlag=LED_RED;
                 strlistProcType.append(m_strgfrjbh);//功放热继保护-外部（故障号9）
                 statusrec=organizationStatusRecord(m_strgfrjbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iGfrjbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iGfrjbhVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iRELAYFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Gfrjbh==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[7]==0)
            {
                if(stru_newChainSetData.iGfrjbhVal==SWITCH_ON)
                {
                    g_newfaultstatus.iRELAYFlag=LED_RED;
                    strlistProcType.append(m_strgfrjbh);//功放热继保护-外部（故障号9）
                    statusrec=organizationStatusRecord(m_strgfrjbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iGfrjbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iGfrjbhVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iRELAYFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Jyzcdy==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[9]==1)
         {
             if(stru_newChainSetData.iJyzcdyVal==SWITCH_ON)
             {
                 g_newfaultstatus.iHBUPFlag=LED_RED;
                 strlistProcType.append(m_strjyzcdy);//静压轴承低压-外部（故障号10）
                 statusrec=organizationStatusRecord(m_strjyzcdy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iJyzcdyVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iJyzcdyVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iHBUPFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Jyzcdy==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[9]==0)
            {
                if(stru_newChainSetData.iJyzcdyVal==SWITCH_ON)
                {
                    g_newfaultstatus.iHBUPFlag=LED_RED;
                    strlistProcType.append(m_strjyzcdy);//静压轴承低压-外部（故障号10）
                    statusrec=organizationStatusRecord(m_strjyzcdy,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iJyzcdyVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iJyzcdyVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iHBUPFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Zgmbh==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[8]==1)
         {
             if(stru_newChainSetData.iZgmbhVal==SWITCH_ON)
             {
                 g_newfaultstatus.iDOORFlag=LED_RED;
                 strlistProcType.append(m_strmbh);//主柜门保护-外部（故障号11）
                 statusrec=organizationStatusRecord(m_strmbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iZgmbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iZgmbhVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iDOORFlag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Zgmbh==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[8]==0)
            {
                if(stru_newChainSetData.iZgmbhVal==SWITCH_ON)
                {
                    g_newfaultstatus.iDOORFlag=LED_RED;
                    strlistProcType.append(m_strmbh);//主柜门保护-外部（故障号11）
                    statusrec=organizationStatusRecord(m_strmbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iZgmbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iZgmbhVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iDOORFlag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Selfdef1==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[10]==1)
         {
             if(stru_newChainSetData.iSelfdefVal1==SWITCH_ON)
             {
                 g_newfaultstatus.iEXT1Flag=LED_RED;
                 strlistProcType.append(m_strelfdef1);//自定义1-外部（故障号12）
                 statusrec=organizationStatusRecord(m_strelfdef1,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iSelfdefVal1=%d--cnt_proc=%d##\n",stru_newChainSetData.iSelfdefVal1,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iEXT1Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Selfdef1==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[10]==0)
            {
                if(stru_newChainSetData.iSelfdefVal1==SWITCH_ON)
                {
                    g_newfaultstatus.iEXT1Flag=LED_RED;
                    strlistProcType.append(m_strelfdef1);//自定义1-外部（故障号12）
                    statusrec=organizationStatusRecord(m_strelfdef1,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iSelfdefVal1=%d--cnt_proc=%d##\n",stru_newChainSetData.iSelfdefVal1,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iEXT1Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Selfdef2==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[11]==1)
         {
             if(stru_newChainSetData.iSelfdefVal2==SWITCH_ON)
             {
                 g_newfaultstatus.iEXT2Flag=LED_RED;
                 strlistProcType.append(m_strelfdef2);//自定义2-外部（故障号13）
                 statusrec=organizationStatusRecord(m_strelfdef2,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iSelfdefVal2=%d--cnt_proc=%d##\n",stru_newChainSetData.iSelfdefVal2,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iEXT2Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Selfdef2==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[11]==0)
            {
                if(stru_newChainSetData.iSelfdefVal2==SWITCH_ON)
                {
                    g_newfaultstatus.iEXT2Flag=LED_RED;
                    strlistProcType.append(m_strelfdef2);//自定义2-外部（故障号13）
                    statusrec=organizationStatusRecord(m_strelfdef2,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iSelfdefVal2=%d--cnt_proc=%d##\n",stru_newChainSetData.iSelfdefVal2,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iEXT2Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Selfdef3==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[12]==1)
         {
             if(stru_newChainSetData.iSelfdefVal3==SWITCH_ON)
             {
                 g_newfaultstatus.iEXT3Flag=LED_RED;
                 strlistProcType.append(m_strelfdef3);//自定义3-外部（故障号14）
                 statusrec=organizationStatusRecord(m_strelfdef3,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iSelfdefVal3=%d--cnt_proc=%d##\n",stru_newChainSetData.iSelfdefVal3,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iEXT3Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Selfdef3==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[12]==0)
            {
                if(stru_newChainSetData.iSelfdefVal3==SWITCH_ON)
                {
                    g_newfaultstatus.iEXT3Flag=LED_RED;
                    strlistProcType.append(m_strelfdef3);//自定义3-外部（故障号14）
                    statusrec=organizationStatusRecord(m_strelfdef3,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iSelfdefVal3=%d--cnt_proc=%d##\n",stru_newChainSetData.iSelfdefVal3,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iEXT3Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_Selfdef4==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[13]==1)
         {
             if(stru_newChainSetData.iSelfdefVal4==SWITCH_ON)
             {
                 g_newfaultstatus.iEXT4Flag=LED_RED;
                 strlistProcType.append(m_strelfdef4);//自定义4-外部（故障号15）
                 statusrec=organizationStatusRecord(m_strelfdef4,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iSelfdefVal4=%d--cnt_proc=%d##\n",stru_newChainSetData.iSelfdefVal4,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iEXT4Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_Selfdef4==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[13]==0)
            {
                if(stru_newChainSetData.iSelfdefVal4==SWITCH_ON)
                {
                    g_newfaultstatus.iEXT4Flag=LED_RED;
                    strlistProcType.append(m_strelfdef4);//自定义4-外部（故障号15）
                    statusrec=organizationStatusRecord(m_strelfdef4,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iSelfdefVal4=%d--cnt_proc=%d##\n",stru_newChainSetData.iSelfdefVal4,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iEXT4Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_C1zlqgw==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[15]==1)
         {
             if(stru_newChainSetData.iC1zlqgwVal==SWITCH_ON)
             {
                 g_newfaultstatus.iOT1Flag=LED_RED;
                 strlistProcType.append(m_strc1zlqgw);//从柜1整流器过温-外部（故障号16）
                 statusrec=organizationStatusRecord(m_strc1zlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iC1zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC1zlqgwVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iOT1Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_C1zlqgw==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[15]==0)
            {
                if(stru_newChainSetData.iC1zlqgwVal==SWITCH_ON)
                {
                    g_newfaultstatus.iOT1Flag=LED_RED;
                    strlistProcType.append(m_strc1zlqgw);//从柜1整流器过温-外部（故障号16）
                    statusrec=organizationStatusRecord(m_strc1zlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iC1zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC1zlqgwVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iOT1Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_C2zlqgw==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[16]==1)
         {
             if(stru_newChainSetData.iC2zlqgwVal==SWITCH_ON)
             {
                 g_newfaultstatus.iOT2Flag=LED_RED;
                 strlistProcType.append(m_strc2zlqgw);//从柜2整流器过温-外部（故障号17）
                 statusrec=organizationStatusRecord(m_strc2zlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iC2zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC2zlqgwVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iOT2Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_C2zlqgw==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[16]==0)
            {
                if(stru_newChainSetData.iC2zlqgwVal==SWITCH_ON)
                {
                    g_newfaultstatus.iOT2Flag=LED_RED;
                    strlistProcType.append(m_strc2zlqgw);//从柜2整流器过温-外部（故障号17）
                    statusrec=organizationStatusRecord(m_strc2zlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iC2zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC2zlqgwVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iOT2Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_C3zlqgw==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[17]==1)
         {
             if(stru_newChainSetData.iC3zlqgwVal==SWITCH_ON)
             {
                 g_newfaultstatus.iOT3Flag=LED_RED;
                 strlistProcType.append(m_strc3zlqgw);//从柜3整流器过温-外部（故障号18）
                 statusrec=organizationStatusRecord(m_strc3zlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iC3zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC3zlqgwVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iOT3Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_C3zlqgw==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[17]==0)
            {
                if(stru_newChainSetData.iC3zlqgwVal==SWITCH_ON)
                {
                    g_newfaultstatus.iOT3Flag=LED_RED;
                    strlistProcType.append(m_strc3zlqgw);//从柜3整流器过温-外部（故障号18）
                    statusrec=organizationStatusRecord(m_strc3zlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iC3zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC3zlqgwVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iOT3Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_C4zlqgw==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[18]==1)
         {
             if(stru_newChainSetData.iC4zlqgwVal==SWITCH_ON)
             {
                 g_newfaultstatus.iOT4Flag=LED_RED;
                 strlistProcType.append(m_strc4zlqgw);//从柜4整流器过温-外部（故障号19）
                 statusrec=organizationStatusRecord(m_strc4zlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iC4zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC4zlqgwVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iOT4Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_C4zlqgw==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[18]==0)
            {
                if(stru_newChainSetData.iC4zlqgwVal==SWITCH_ON)
                {
                    g_newfaultstatus.iOT4Flag=LED_RED;
                    strlistProcType.append(m_strc4zlqgw);//从柜4整流器过温-外部（故障号19）
                    statusrec=organizationStatusRecord(m_strc4zlqgw,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iC4zlqgwVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC4zlqgwVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iOT4Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_C1cwbh==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[20]==1)
         {
             if(stru_newChainSetData.iC1cwbhVal==SWITCH_ON)
             {
                 g_newfaultstatus.iFAULT1Flag=LED_RED;
                 strlistProcType.append(m_strc1cwbh);//从柜1错误保护-外部（故障号20）
                 statusrec=organizationStatusRecord(m_strc1cwbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iC1cwbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC1cwbhVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iFAULT1Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_C1cwbh==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[20]==0)
            {
                if(stru_newChainSetData.iC1cwbhVal==SWITCH_ON)
                {
                    g_newfaultstatus.iFAULT1Flag=LED_RED;
                    strlistProcType.append(m_strc1cwbh);//从柜1错误保护-外部（故障号20）
                    statusrec=organizationStatusRecord(m_strc1cwbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iC1cwbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC1cwbhVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iFAULT1Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_C2cwbh==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[21]==1)
         {
             if(stru_newChainSetData.iC2cwbhVal==SWITCH_ON)
             {
                 g_newfaultstatus.iFAULT2Flag=LED_RED;
                 strlistProcType.append(m_strc2cwbh);//从柜2错误保护-外部（故障号21）
                 statusrec=organizationStatusRecord(m_strc2cwbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iC2cwbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC2cwbhVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iFAULT2Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_C2cwbh==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[21]==0)
            {
                if(stru_newChainSetData.iC2cwbhVal==SWITCH_ON)
                {
                    g_newfaultstatus.iFAULT2Flag=LED_RED;
                    strlistProcType.append(m_strc2cwbh);//从柜2错误保护-外部（故障号21）
                    statusrec=organizationStatusRecord(m_strc2cwbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iC2cwbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC2cwbhVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iFAULT2Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_C3cwbh==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[22]==1)
         {
             if(stru_newChainSetData.iC3cwbhVal==SWITCH_ON)
             {
                 g_newfaultstatus.iFAULT3Flag=LED_RED;
                 strlistProcType.append(m_strc3cwbh);//从柜3错误保护-外部（故障号22）
                 statusrec=organizationStatusRecord(m_strc3cwbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iC3cwbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC3cwbhVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iFAULT3Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_C3cwbh==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[22]==0)
            {
                if(stru_newChainSetData.iC3cwbhVal==SWITCH_ON)
                {
                    g_newfaultstatus.iFAULT3Flag=LED_RED;
                    strlistProcType.append(m_strc3cwbh);//从柜3错误保护-外部（故障号22）
                    statusrec=organizationStatusRecord(m_strc3cwbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iC2cwbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC2cwbhVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iFAULT3Flag=LED_GREEN;
    }
    if(stru_newChainSetData.isw_C4cwbh==NORMAL_OPEN)
    {
        if(g_newfaultstatus.iFaultValue[23]==1)
         {
             if(stru_newChainSetData.iC4cwbhVal==SWITCH_ON)
             {
                 g_newfaultstatus.iFAULT4Flag=LED_RED;
                 strlistProcType.append(m_strc4cwbh);//从柜4错误保护-外部（故障号23）
                 statusrec=organizationStatusRecord(m_strc4cwbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                 g_vec_StatusRecord.push_back(statusrec);
                 cnt_proc++;
                 printf("##newCheckExterProcExist()::iC4cwbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC4cwbhVal,cnt_proc);
             }
        }
        else
            g_newfaultstatus.iFAULT4Flag=LED_GREEN;
    }
    else if(stru_newChainSetData.isw_C4cwbh==NORMAL_CLOSE)
    {
        if(g_newfaultstatus.iFaultValue[23]==0)
            {
                if(stru_newChainSetData.iC4cwbhVal==SWITCH_ON)
                {
                    g_newfaultstatus.iFAULT4Flag=LED_RED;
                    strlistProcType.append(m_strc4cwbh);//从柜4错误保护-外部（故障号23）
                    statusrec=organizationStatusRecord(m_strc4cwbh,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
                    g_vec_StatusRecord.push_back(statusrec);
                    cnt_proc++;
                    printf("##newCheckExterProcExist()::iC4cwbhVal=%d--cnt_proc=%d##\n",stru_newChainSetData.iC4cwbhVal,cnt_proc);
                }
            }
        else
            g_newfaultstatus.iFAULT4Flag=LED_GREEN;
    }
    if(g_newfaultstatus.iFaultValue[14]==0)
    {
        g_newfaultstatus.iESTOPFlag=LED_RED;
        strlistProcType.append(m_strjjtj);//紧急停机
        statusrec=organizationStatusRecord(m_strjjtj,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
        g_vec_StatusRecord.push_back(statusrec);
        cnt_proc++;
        printf("##newCheckExterProcExist()::m_strjjtj=%d--cnt_proc=%d##\n",g_newfaultstatus.iESTOPFlag,cnt_proc);
    }
    else
        g_newfaultstatus.iESTOPFlag=LED_GREEN;
//    if(g_newfaultstatus.iFaultValue[19]==0)
    if(g_newfaultstatus.iFaultValue[19]==1)   //change by zw 20220719
    {
        if(stru_newChainSetData.iXtlqVal==SWITCH_ON)
            {
            g_newfaultstatus.iSESTOPFlag=LED_RED;
            strlistProcType.append(m_strsjjtj);//S紧急停机
            statusrec=organizationStatusRecord(m_strsjjtj,g_newaddata.fTotalVolAC,g_newaddata.fTotalSlaveCurAC);
            g_vec_StatusRecord.push_back(statusrec);
            cnt_proc++;
            printf("##newCheckExterProcExist()::m_strsjjtj=%d--cnt_proc=%d##\n",g_newfaultstatus.iSESTOPFlag=0,cnt_proc);
        }
    }
    else
        g_newfaultstatus.iSESTOPFlag=LED_GREEN;

     if(cnt_proc==0)
     {
         return false;//不存在外部保护
     }
     else
     {
         return true;//存在外部保护
     }
}

STR_STATUSDATA  CJudgeProc::organizationStatusRecord(QString strProctype,float fVoltVal,float fCurrVal)
{
    STR_STATUSDATA tmpStatusData;//由于成员变量有QString类型的，所以不能用memset函数初始化该结构体
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    QString filedate =current_date_time.toString("yyyyMMddhhmm");
    tmpStatusData.strAlarmTime=current_date;

    //保护类型
    tmpStatusData.strErrorType=strProctype;
    //输出电压有效值
    tmpStatusData.fVoltRms=fVoltVal;
    //输出电压最大值
    tmpStatusData.fVoltMax=fVoltVal*qSqrt(2.0);
    //输出电流有效值
    tmpStatusData.fCurrentRms=fCurrVal;
    //	printf("fCurrentRms=%f--i=%d\n",tmpStatusData.fCurrentRms,i);
    //输出电流最大值
    tmpStatusData.fCurrentMax=fCurrVal*qSqrt(2.0);
    return tmpStatusData;

}

















