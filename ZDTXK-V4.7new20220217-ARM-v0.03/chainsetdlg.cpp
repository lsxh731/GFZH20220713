/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: chainsetdlg.cpp
** 摘要: "连锁设置"子对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.11.10
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2018.11.10   V1.0      创建
** 聂晓波      2019.02.10   V1.1      修改
****************************************************************************/
#include "chainsetdlg.h"
#include <QMessageBox>
extern struct STRU_CHAINSETDATA g_ChainSetData;//连锁设置参数-全局变量,add by 2019.05.14
extern int g_iLangChange;               //语言切换标识符,1-中文，0-英文

extern STRU_NEWCHASETDATA g_newchasetdata;  //add by zw 20220223
extern STRU_NEWFAULTSTATUS g_newfaultstatus; //add by zw 20220223
CChainsetdlg::CChainsetdlg(int nfd)
{
    m_pUi= new Ui::chainsetDialog;
    m_pUi->setupUi(this);
    m_nGPIOfd=nfd;
    init();
    //信号与槽关系
    connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    connect(m_pUi->toolButton_tongyi,SIGNAL(clicked()),this,SLOT(tongyiSwitch_clicked()));
    connect(m_pUi->closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));//返回键 add by 2020.08.10

    //所有toolbutton切换-槽函数
//    disableChainSet();
//    connect(m_pUi->toolButton_subzlqgw,SIGNAL(clicked()),this,SLOT(subzlqgwSwitch_clicked()));
//    connect(m_pUi->toolButton_htdyw,SIGNAL(clicked()),this,SLOT(htdywSwitch_clicked()));
//    connect(m_pUi->toolButton_ezgwy,SIGNAL(clicked()),this,SLOT(ezgwySwitch_clicked()));

    connect(m_pUi->toolButton_xtlqdy,SIGNAL(clicked()),this,SLOT(xtlqdySwitch_clicked()));
    connect(m_pUi->toolButton_zdtgw,SIGNAL(clicked()),this,SLOT(zdtgwSwitch_clicked()));
    connect(m_pUi->toolButton_zdtgwy,SIGNAL(clicked()),this,SLOT(zdtgwySwitch_clicked()));
    connect(m_pUi->toolButton_htgwy,SIGNAL(clicked()),this,SLOT(htgwySwitch_clicked()));
    connect(m_pUi->toolButton_htqy,SIGNAL(clicked()),this,SLOT(htqySwitch_clicked()));
    connect(m_pUi->toolButton_htqyw,SIGNAL(clicked()),this,SLOT(htqywSwitch_clicked()));
    connect(m_pUi->toolButton_htgw,SIGNAL(clicked()),this,SLOT(htgwSwitch_clicked()));

    connect(m_pUi->toolButton_gfrjbh,SIGNAL(clicked()),this,SLOT(gfrhbhSwitch_clicked()));
    connect(m_pUi->toolButton_jyzcdy,SIGNAL(clicked()),this,SLOT(jyzcdySwitch_clicked()));
    connect(m_pUi->toolButton_zgmenbh,SIGNAL(clicked()),this,SLOT(zgmenbhSwitch_clicked()));
    connect(m_pUi->toolButton_selfdefine1,SIGNAL(clicked()),this,SLOT(selfdefine1Switch_clicked()));
    connect(m_pUi->toolButton_selfdefine2,SIGNAL(clicked()),this,SLOT(selfdefine2Switch_clicked()));
    connect(m_pUi->toolButton_selfdefine3,SIGNAL(clicked()),this,SLOT(selfdefine3Switch_clicked()));
    connect(m_pUi->toolButton_selfdefine4,SIGNAL(clicked()),this,SLOT(selfdefine4Switch_clicked()));

    connect(m_pUi->toolButton_c1zlqgw,SIGNAL(clicked()),this,SLOT(c1zlqgwSwitch_clicked()));
    connect(m_pUi->toolButton_c2zlqgw,SIGNAL(clicked()),this,SLOT(c2zlqgwSwitch_clicked()));
    connect(m_pUi->toolButton_c3zlqgw,SIGNAL(clicked()),this,SLOT(c3zlqgwSwitch_clicked()));
    connect(m_pUi->toolButton_c4zlqgw,SIGNAL(clicked()),this,SLOT(c4zlqgwSwitch_clicked()));
    connect(m_pUi->toolButton_c1cwbh,SIGNAL(clicked()),this,SLOT(c1cwbhSwitch_clicked()));
    connect(m_pUi->toolButton_c2cwbh,SIGNAL(clicked()),this,SLOT(c2cwbhSwitch_clicked()));
    connect(m_pUi->toolButton_c3cwbh,SIGNAL(clicked()),this,SLOT(c3cwbhSwitch_clicked()));
    connect(m_pUi->toolButton_c4cwbh,SIGNAL(clicked()),this,SLOT(c4cwbhSwitch_clicked()));


    connect(m_pUi->comboBox_xtlqdy,SIGNAL(activated(int )),SLOT(comboBox_xtlqdy_activated(int)));//系统冷却单元触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_zdtgw,SIGNAL(activated(int)),SLOT(comboBox_zdtgw_activated(int)));//振动台过温触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_zdtgwy,SIGNAL(activated(int )),SLOT(comboBox_zdtgwy_activated(int)));//振动台过位移触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_htgwy,SIGNAL(activated(int )),SLOT(comboBox_htgwy_activated(int)));//滑台过位移触点切换槽函数 add by 2020.09.05
    connect(m_pUi->comboBox_htqy,SIGNAL(activated(int )),SLOT(comboBox_htqy_activated(int)));//滑台轴承低压触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_htqyw,SIGNAL(activated(int )),SLOT(comboBox_htqyw_activated(int)));//主柜整流器过温触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_htgw,SIGNAL(activated(int )),SLOT(comboBox_htgw_activated(int)));//从柜门保护触点切换槽函数 add by 2020.09.08

    connect(m_pUi->comboBox_gfrjbh,SIGNAL(activated(int )),SLOT(comboBox_gfrjbh_activated(int)));//功放热继保护触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_jyzcdy,SIGNAL(activated(int )),SLOT(comboBox_jyzcdy_activated(int)));//静压轴承低压触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_zgmenbh,SIGNAL(activated(int )),SLOT(comboBox_zgmenbh_activated(int)));//主柜门保护触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_selfdefine1,SIGNAL(activated(int )),SLOT(comboBox_selfdefine1_activated(int)));//自定义1保护触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_selfdefine2,SIGNAL(activated(int )),SLOT(comboBox_selfdefine2_activated(int)));//自定义2保护触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_selfdefine3,SIGNAL(activated(int )),SLOT(comboBox_selfdefine3_activated(int)));//自定义3保护触点切换槽函数 add by 2020.09.08
    connect(m_pUi->comboBox_selfdefine4,SIGNAL(activated(int )),SLOT(comboBox_selfdefine4_activated(int)));//自定义4保护触点切换槽函数 add by 2022.02.23

    connect(m_pUi->comboBox_c1zlqgw,SIGNAL(activated(int )),SLOT(comboBox_c1zlqgw_activated(int)));//从柜1整流器过温触点切换槽函数 add by 2022.02.23
    connect(m_pUi->comboBox_c2zlqgw,SIGNAL(activated(int )),SLOT(comboBox_c2zlqgw_activated(int)));//从柜2整流器过温触点切换槽函数 add by 2022.02.23
    connect(m_pUi->comboBox_c3zlqgw,SIGNAL(activated(int )),SLOT(comboBox_c3zlqgw_activated(int)));//从柜3整流器过温触点切换槽函数 add by 2022.02.23
    connect(m_pUi->comboBox_c4zlqgw,SIGNAL(activated(int )),SLOT(comboBox_c4zlqgw_activated(int)));//从柜4整流器过温触点切换槽函数 add by 2022.02.23
    connect(m_pUi->comboBox_c1cwbh,SIGNAL(activated(int )),SLOT(comboBox_c1cwbh_activated(int)));  //从柜1错误信号触点切换槽函数 add by 2022.02.23
    connect(m_pUi->comboBox_c2cwbh,SIGNAL(activated(int )),SLOT(comboBox_c2cwbh_activated(int)));  //从柜1错误信号触点切换槽函数 add by 2022.02.23
    connect(m_pUi->comboBox_c3cwbh,SIGNAL(activated(int )),SLOT(comboBox_c3cwbh_activated(int)));  //从柜1错误信号触点切换槽函数 add by 2022.02.23
    connect(m_pUi->comboBox_c4cwbh,SIGNAL(activated(int )),SLOT(comboBox_c4cwbh_activated(int)));  //从柜1错误信号触点切换槽函数 add by 2022.02.23

//    connect(m_pUi->comboBox_subyuliu,SIGNAL(activated(int )),this,SLOT(comboBox_subyuliu_activated(int)));//从柜预留保护触点切换槽函数 add by 2020.09.08
//    connect(m_pUi->comboBox_htdyw,SIGNAL(activated(int )),this,SLOT(comboBox_htdyw_activated(int)));//滑台低液位触点切换槽函数 add by 2020.09.08
//    connect(m_pUi->comboBox_subzlqgw,SIGNAL(activated(int )),this,SLOT(comboBox_subzlqgw_activated(int)));//从柜整流器过温触点切换槽函数 add by 2020.09.08
//    connect(m_pUi->comboBox_ezgwy,SIGNAL(activated(int )),this,SLOT(comboBox_ezgwy_activated(int)));//耳轴过位移触点切换槽函数 add by 2020.09.08
    //模式切换槽函数
    connect(m_pUi->normalBtn,SIGNAL(clicked()),this,SLOT(normal_clicked()));
    connect(m_pUi->debugBtn,SIGNAL(clicked()),this,SLOT(debug_clicked()));
    normal_clicked();
}
CChainsetdlg::~CChainsetdlg()
{
    //程序退出时对连锁屏蔽设置变量g_ChainSetData,add by 2019.05.26
    memcpy(&g_ChainSetData,&m_ChainSetData,sizeof(m_ChainSetData));

}
//禁用部分连锁屏蔽设置,add by 2019.05.25
void CChainsetdlg::disableChainSet()
{
    //--禁用自定义1操作
    m_pUi->toolButton_selfdefine1->setEnabled(false);
    //--禁用自定义2操作
    m_pUi->toolButton_selfdefine2->setEnabled(false);
    //--禁用自定义3操作
    m_pUi->toolButton_selfdefine3->setEnabled(false);
    //--禁用从柜预留保护操作
//    m_pUi->toolButton_subyuliu->setEnabled(false);
}
//模式选择-调试模式
void CChainsetdlg::debug_clicked()
{
    m_iMode=DEBUG_MODE;
    m_pUi->normalBtn->setEnabled(true);
    m_pUi->normalBtn->setDown(false);
    m_pUi->debugBtn->setEnabled(false);
    m_pUi->debugBtn->setDown(true);
}
//模式选择-正常模式
void CChainsetdlg::normal_clicked()
{
    m_iMode=NORMAL_MODE;
    m_pUi->normalBtn->setEnabled(false);
    m_pUi->normalBtn->setDown(true);
    m_pUi->debugBtn->setEnabled(true);
    m_pUi->debugBtn->setDown(false);
}
//获取模式,add by 2019.04.27
int CChainsetdlg::getMode()
{
    return m_iMode;
}
//初始化连锁屏蔽设置页面
void CChainsetdlg::init()
{
     allSetBtnEnable(false);
    m_ybonicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"yb_on.png"), QSize(66, 48), QIcon::Normal, QIcon::Off);
    m_ybofficon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"yb_off.png"), QSize(66, 48), QIcon::Normal, QIcon::Off);

     //QColor openBgColor("#279b14"); //"开"颜色
     //QColor closeBgColor("#5c606a");//"关"颜色
     setAllSwitchIcon(m_ybofficon);
     m_iChainsetval=FULL_DATA_ON;
     m_strListSuccess.clear();
     m_strListFailure.clear();
     QString strSuccess=QApplication::translate("chainsetDialog",
         "\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);   //设置成功

     QString strFail=QApplication::translate("chainsetDialog",
         "\350\256\276\347\275\256\345\244\261\350\264\245",
         0, QApplication::UnicodeUTF8);//设置失败
     m_strListSuccess.append(m_pUi->label_2->text()+strSuccess);//
     m_strListSuccess.append(m_pUi->label_3->text()+strSuccess);
//     m_strListSuccess.append(m_pUi->label_4->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_6->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_7->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_8->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_9->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_10->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_11->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_12->text()+strSuccess);
//     m_strListSuccess.append(m_pUi->label_18->text()+strSuccess);//主柜整流器过温,add by 2019.05.25
//     m_strListSuccess.append(m_pUi->label_20->text()+strSuccess);//从柜整流器过温,add by 2019.05.25
     m_strListSuccess.append(m_pUi->label_21->text()+strSuccess);//从柜门保护,add by 2019.05.25
     m_strListSuccess.append(m_pUi->label_14->text()+strSuccess);//系统冷却单元,add by 2019.05.25

     m_strListFailure.append(m_pUi->label_2->text()+strFail);
     m_strListFailure.append(m_pUi->label_3->text()+strFail);
//     m_strListFailure.append(m_pUi->label_4->text()+strFail);
     m_strListFailure.append(m_pUi->label_6->text()+strFail);
     m_strListFailure.append(m_pUi->label_7->text()+strFail);
     m_strListFailure.append(m_pUi->label_8->text()+strFail);
     m_strListFailure.append(m_pUi->label_9->text()+strFail);
     m_strListFailure.append(m_pUi->label_10->text()+strFail);
     m_strListFailure.append(m_pUi->label_11->text()+strFail);
     m_strListFailure.append(m_pUi->label_12->text()+strFail);
//     m_strListSuccess.append(m_pUi->label_18->text()+strFail);//主柜整流器过温,add by 2019.05.25
//     m_strListSuccess.append(m_pUi->label_20->text()+strFail);//从柜整流器过温,add by 2019.05.25
     m_strListSuccess.append(m_pUi->label_21->text()+strFail);//从柜门保护,add by 2019.05.25
     m_strListSuccess.append(m_pUi->label_14->text()+strFail);//系统冷却单元,add by 2019.05.25

     m_strFriendlytips=QApplication::translate("chainsetDialog",
        "\345\217\213\346\203\205\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//友情提示


     m_strAllSuccess=QApplication::translate("chainsetDialog",
         "\346\211\200\346\234\211\350\277\236\351\224\201\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);   //所有连锁设置成功

     m_strAllFailure=QApplication::translate("chainsetDialog",
         "\346\211\200\346\234\211\350\277\236\351\224\201\350\256\276\347\275\256\345\244\261\350\264\245",
         0, QApplication::UnicodeUTF8); //所有连锁设置失败

//     initChainSetData();//初始化连锁屏蔽设置m_ChainSetData,add by 2019.05.26
     newinitChainSetData();//初始化连锁屏蔽设置m_newChaSetData,add by zw 2022.02.23
     m_iMode=DEBUG_MODE;//调试模式
//     m_iMode=NORMAL_MODE;
     m_isTongyi=true;
}
//初始化m_ChainSetData变量,add by 2019.05.26
void CChainsetdlg::initChainSetData()
{
     //连锁参数结构体变量初始化,add by 2019.04.13
    if(!(m_IniChainset.readChainsetInifile(m_ChainSetData)))
    {
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
     //触点切换初始化-常开
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
    }
      m_iSwitchFlag[0]=m_ChainSetData.iJjtjVal;   //紧急停机
      m_iSwitchFlag[1]=m_ChainSetData.iHtgwyVal;   //滑台过位移
      m_iSwitchFlag[2]=m_ChainSetData.iZdtgwyVal;   //振动台过位移
      m_iSwitchFlag[3]=m_ChainSetData.iHtdywVal;   //滑台低液位
      m_iSwitchFlag[4]=m_ChainSetData.iSelfdefineVal1;  //自定义1(替代"振动台冷却")
      m_iSwitchFlag[5]=m_ChainSetData.iHtqyVal;   //滑台轴承低压
      m_iSwitchFlag[6]=m_ChainSetData.iZdtgwVal;   //振动台过温
      m_iSwitchFlag[7]=m_ChainSetData.iEzgwyVal;   //耳轴过位移
      m_iSwitchFlag[8]=m_ChainSetData.iGfrjbhVal;   //功放热继保护
      m_iSwitchFlag[9]=m_ChainSetData.iJyzcdyVal;   //静压轴承低压
      m_iSwitchFlag[10]=m_ChainSetData.iZgMenbVal;  //主柜门保护
      m_iSwitchFlag[11]=m_ChainSetData.iXtlqdyVal;  //系统冷却单元
      m_iSwitchFlag[12]=m_ChainSetData.iHtqywVal;  //主柜整流桥过温,add by 2019.05.25
      m_iSwitchFlag[13]=m_ChainSetData.iSelfdefineVal2;  //自定义2,add by 2019.05.25
      m_iSwitchFlag[14]=m_ChainSetData.iSelfdefineVal3;  //自定义3,add by 2019.05.25
      m_iSwitchFlag[15]=m_ChainSetData.iSubyuliuPorcVal;  //从柜预留保护，add by 2019.12.20
      m_iSwitchFlag[16]=m_ChainSetData.iSubzlqgwVal;  //从柜整流桥过温,add by 2019.05.25
      m_iSwitchFlag[17]=m_ChainSetData.iSubMenbVal;  //从柜门保护,add by 2019.05.25

     memcpy(&g_ChainSetData,&m_ChainSetData,sizeof(m_ChainSetData));//连锁屏蔽设置变量g_ChainSetData初始化,add by 2019.05.26
     //滑台过位移-显示-函数
    showChainButton(HTGWY_INTERRUPT_MASK, m_pUi->toolButton_htgwy);
    //振动台过位移-显示-函数
    showChainButton(ZDTGWY_INTERRUPT_MASK, m_pUi->toolButton_zdtgwy);
    //滑台低液位-显示-函数
//    showChainButton(HTDYW_INTERRUPT_MASK, m_pUi->toolButton_htdyw);
   //滑台轴承低压-显示-函数
    showChainButton(HTQY_INTERRUPT_MASK, m_pUi->toolButton_htqy);
    //振动台过温-显示-函数
    showChainButton(ZDTGW_INTERRUPT_MASK, m_pUi->toolButton_zdtgw);
    //耳轴过位移-显示-函数
//    showChainButton(EZGWY_INTERRUPT_MASK, m_pUi->toolButton_ezgwy);
    //功放热继保护-显示-函数
    showChainButton(GFRJBH_INTERRUPT_MASK, m_pUi->toolButton_gfrjbh);
    //静压轴承低压-显示-函数
    showChainButton(JYZCDY_INTERRUPT_MASK,m_pUi->toolButton_jyzcdy);
    //主柜门保护-显示-函数
    showChainButton(ZGMBH_INTERRUPT_MASK,m_pUi->toolButton_zgmenbh);
     //系统冷却单元-显示-函数
    showChainButton(XTLQDY_INTERRUPT_MASK,m_pUi->toolButton_xtlqdy);
    //自定义1-显示-函数,add by 2019.05.18
    showChainButton(SELFDEFINE1_INTERRUPT_MASK, m_pUi->toolButton_selfdefine1);
    //自定义2-显示-函数,add by 2019.05.18
    showChainButton(SELFDEFINE2_INTERRUPT_MASK,m_pUi->toolButton_selfdefine2);
    //自定义3-显示-函数,add by 2019.05.18
    showChainButton(SELFDEFINE3_INTERRUPT_MASK,m_pUi->toolButton_selfdefine3);
    //从柜门保护-显示-函数,add by 2019.05.18
    showChainButton(SUBMBH_INTERRUPT_MASK,m_pUi->toolButton_htgw);
    //主柜整流器过温-显示-函数,add by 2019.05.25
    showChainButton(HTQYW_INTERRUPT_MASK,m_pUi->toolButton_htqyw);
    //从柜整流器过温-显示-函数,add by 2019.05.25
//    showChainButton(SUBZLQGW_INTERRUPT_MASK,m_pUi->toolButton_subzlqgw);
    //从柜预留保护-显示-函数,add by 2019.05.25
//    showChainButton(NULL_INTERRUPT_MASK,m_pUi->toolButton_subyuliu);

    //触点切换-显示-函数,add by 2020.11.24
    m_pUi->comboBox_htgwy->setCurrentIndex(m_ChainSetData.iSwitch_htgwy);
    m_pUi->comboBox_zdtgwy->setCurrentIndex(m_ChainSetData.iSwitch_zdtgwy);
//    m_pUi->comboBox_htdyw->setCurrentIndex(m_ChainSetData.iSwitch_htdyw);
    m_pUi->comboBox_htqy->setCurrentIndex(m_ChainSetData.iSwitch_htqy);
    m_pUi->comboBox_zdtgw->setCurrentIndex(m_ChainSetData.iSwitch_zdtgw);
//    m_pUi->comboBox_ezgwy->setCurrentIndex(m_ChainSetData.iSwitch_ezgwy);
    m_pUi->comboBox_gfrjbh->setCurrentIndex(m_ChainSetData.iSwitch_gfrjbh);
    m_pUi->comboBox_jyzcdy->setCurrentIndex(m_ChainSetData.iSwitch_jyzcdy);
    m_pUi->comboBox_zgmenbh->setCurrentIndex(m_ChainSetData.iSwitch_zgmenbh);
    m_pUi->comboBox_htgw->setCurrentIndex(m_ChainSetData.iSwitch_htgw);
    m_pUi->comboBox_xtlqdy->setCurrentIndex(m_ChainSetData.iSwitch_xtlqdy);
    m_pUi->comboBox_htqyw->setCurrentIndex(m_ChainSetData.iSwitch_htqyw);
//    m_pUi->comboBox_subzlqgw->setCurrentIndex(m_ChainSetData.iSwitch_subzlqgw);
    m_pUi->comboBox_selfdefine1->setCurrentIndex(m_ChainSetData.iSwitch_selfdefine1);
    m_pUi->comboBox_selfdefine2->setCurrentIndex(m_ChainSetData.iSwitch_selfdefine2);
    m_pUi->comboBox_selfdefine3->setCurrentIndex(m_ChainSetData.iSwitch_selfdefine3);
//    m_pUi->comboBox_subyuliu->setCurrentIndex(m_ChainSetData.iSwitch_subyuliu);
}
//设置所有切换按钮值
void CChainsetdlg::setAllSwitchValue(int nValue)
{
    for(int i=0;i<24;i++)
    {
        if((i==0)||(i==1))
        {
            continue;//忽略这几个赋值
        }
        m_iNewswFlag[i]=nValue;
    }
}
//设置所有切换按钮图标，2019.05.25
void CChainsetdlg::setAllSwitchIcon(QIcon icon)
{
     m_pUi->toolButton_tongyi->setIcon(icon);       //统一按钮,add by 2019.05.25
     m_pUi->toolButton_tongyi->setIconSize(QSize(66, 48));

     m_pUi->toolButton_xtlqdy->setIcon(icon);       //系统冷却单元
     m_pUi->toolButton_xtlqdy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_zdtgw->setIcon(icon);        //振动台过温
     m_pUi->toolButton_zdtgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_zdtgwy->setIcon(icon);       //振动台过位移
     m_pUi->toolButton_zdtgwy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_htgwy->setIcon(icon);        //滑台过位移
     m_pUi->toolButton_htgwy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_htqy->setIcon(icon);       //滑台欠压
     m_pUi->toolButton_htqy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_htqyw->setIcon(icon);       //滑台欠液位,add by 2019.05.25
     m_pUi->toolButton_htqyw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_htgw->setIcon(icon);       //滑台过温，add by 2019.05.25
     m_pUi->toolButton_htgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_gfrjbh->setIcon(icon);        //功放热继保护,add by 2019.04.27
     m_pUi->toolButton_gfrjbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_jyzcdy->setIcon(icon);       //静压轴承低压
     m_pUi->toolButton_jyzcdy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_zgmenbh->setIcon(icon);      //主柜门保护
     m_pUi->toolButton_zgmenbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_selfdefine1->setIcon(icon);  //自定义1
     m_pUi->toolButton_selfdefine1->setIconSize(QSize(66, 48));
     m_pUi->toolButton_selfdefine2->setIcon(icon);  //自定义2
     m_pUi->toolButton_selfdefine2->setIconSize(QSize(66, 48));
     m_pUi->toolButton_selfdefine3->setIcon(icon);  //自定义3
     m_pUi->toolButton_selfdefine3->setIconSize(QSize(66, 48));
     m_pUi->toolButton_selfdefine4->setIcon(icon);  //自定义4
     m_pUi->toolButton_selfdefine4->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c1zlqgw->setIcon(icon);  //从柜1整流器过温
     m_pUi->toolButton_c1zlqgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c2zlqgw->setIcon(icon);  //从柜2整流器过温
     m_pUi->toolButton_c2zlqgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c3zlqgw->setIcon(icon);  //从柜3整流器过温
     m_pUi->toolButton_c3zlqgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c4zlqgw->setIcon(icon);  //从柜4整流器过温
     m_pUi->toolButton_c4zlqgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c1cwbh->setIcon(icon);  //从柜1错误
     m_pUi->toolButton_c1cwbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c2cwbh->setIcon(icon);  //从柜2错误
     m_pUi->toolButton_c2cwbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c3cwbh->setIcon(icon);  //从柜3错误
     m_pUi->toolButton_c3cwbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c4cwbh->setIcon(icon);  //从柜4错误
     m_pUi->toolButton_c4cwbh->setIconSize(QSize(66, 48));



//     m_pUi->toolButton_htdyw->setIcon(icon);        // 滑台低液位
//     m_pUi->toolButton_htdyw->setIconSize(QSize(66, 48));
//     m_pUi->toolButton_ezgwy->setIcon(icon);        //耳轴过位移
//     m_pUi->toolButton_ezgwy->setIconSize(QSize(66, 48));
//     m_pUi->toolButton_subzlqgw->setIcon(icon);       //从柜整流器过温,add by 2019.05.25
//     m_pUi->toolButton_subzlqgw->setIconSize(QSize(66, 48));
//     m_pUi->toolButton_subyuliu->setIcon(icon);    //从柜预留保护
//     m_pUi->toolButton_subyuliu->setIconSize(QSize(66, 48));
}
//统一按钮槽函数
void CChainsetdlg::tongyiSwitch_clicked()
{
    if(m_isTongyi)
    {
      m_pUi->toolButton_tongyi->setIcon(m_ybofficon);
      m_pUi->toolButton_tongyi->setIconSize(QSize(66, 48));
      m_isTongyi=false;
      setAllSwitchIcon(m_ybofficon);
      setAllSwitchValue(SWITCH_OFF);
    }
    else
    {
       m_pUi->toolButton_tongyi->setIcon(m_ybonicon);
       m_pUi->toolButton_tongyi->setIconSize(QSize(66, 48));
       m_isTongyi=true;
       setAllSwitchIcon(m_ybonicon);
       setAllSwitchValue(SWITCH_ON);
    }

}
//统一连锁设置-槽函数
void  CChainsetdlg::okBtn_clicked()
{
     //m_ChainSetData.iJjtjVal  = m_iSwitchFlag[0];   //紧急停机
//     m_ChainSetData.iHtgwyVal = m_iSwitchFlag[1];   //滑台过位移
//     m_ChainSetData.iZdtgwyVal= m_iSwitchFlag[2];   //振动台过位移
//     m_ChainSetData.iHtdywVal = m_iSwitchFlag[3];   //滑台低液位
//     m_ChainSetData.iSelfdefineVal1= m_iSwitchFlag[4];  //自定义1(替代"振动台冷却")
//     m_ChainSetData.iHtqyVal= m_iSwitchFlag[5];   //滑台轴承低压
//     m_ChainSetData.iZdtgwVal = m_iSwitchFlag[6];   //振动台过温
//     m_ChainSetData.iEzgwyVal = m_iSwitchFlag[7];   //耳轴过位移
//     m_ChainSetData.iGfrjbhVal= m_iSwitchFlag[8];   //功放热继保护
//     m_ChainSetData.iJyzcdyVal= m_iSwitchFlag[9];   //静压轴承低压
//     m_ChainSetData.iZgMenbVal  = m_iSwitchFlag[10];  //主柜门保护
//     m_ChainSetData.iXtlqdyVal= m_iSwitchFlag[11];  //系统冷却单元
//     m_ChainSetData.iHtqywVal= m_iSwitchFlag[12];  //主柜整流桥过温,add by 2019.05.25
//     m_ChainSetData.iSelfdefineVal2= m_iSwitchFlag[13];  //自定义2,add by 2019.05.25
//     m_ChainSetData.iSelfdefineVal3= m_iSwitchFlag[14];  //自定义3,add by 2019.05.25
//     m_ChainSetData.iSubyuliuPorcVal= m_iSwitchFlag[15];  //从柜预留保护，add by 2019.12.20
//     m_ChainSetData.iSubzlqgwVal= m_iSwitchFlag[16];  //从柜整流桥过温,add by 2019.05.25
//     m_ChainSetData.iSubMenbVal= m_iSwitchFlag[17];  //从柜门保护,add by 2019.05.25
//    if(m_IniChainset.writeChainsetInifile(m_ChainSetData))
//    {
//       memcpy(&g_ChainSetData,&m_ChainSetData,sizeof(m_ChainSetData));//更新连锁屏蔽设置参数给全局变量g_ChainSetData,add by 2019.12.19
//       QMessageBox::warning(this,
//                      tr(m_strFriendlytips),
//                      tr(m_strAllSuccess));//连锁设置配置文件保存成功
//   }
//   else
//   {
//       QMessageBox::warning(this,
//                      tr(m_strFriendlytips),
//                      tr(m_strAllFailure));//连锁设置配置文件保存失败,请检查
//    }

//     m_newChaSetData.iJjtjVal = m_iNewswFlag[0];           //紧急停机
//     m_newChaSetData.iSJitiVal = m_iNewswFlag[1];          //S紧急停机
     m_newChaSetData.iXtlqVal = m_iNewswFlag[2];           //系统冷却
     m_newChaSetData.iZdtgwVal = m_iNewswFlag[3];          //振动台过温
     m_newChaSetData.iZdtgwyVal = m_iNewswFlag[4];         //振动台过位移
     m_newChaSetData.iHtgwyVal = m_iNewswFlag[5];          //滑台过位移
     m_newChaSetData.iHtqyVal = m_iNewswFlag[6];           //滑台欠压
     m_newChaSetData.iHtqywVal = m_iNewswFlag[7];          //滑台欠液位
     m_newChaSetData.iHtgwVal = m_iNewswFlag[8];           //滑台过温
     m_newChaSetData.iGfrjbhVal = m_iNewswFlag[9];         //功放热继保护
     m_newChaSetData.iJyzcdyVal = m_iNewswFlag[10];        //静压轴承低压
     m_newChaSetData.iZgmbhVal = m_iNewswFlag[11];         //主柜门保护
     m_newChaSetData.iSelfdefVal1 = m_iNewswFlag[12];      //自定义1
     m_newChaSetData.iSelfdefVal2 = m_iNewswFlag[13];      //自定义2
     m_newChaSetData.iSelfdefVal3 = m_iNewswFlag[14];      //自定义3
     m_newChaSetData.iSelfdefVal4 = m_iNewswFlag[15];      //自定义4
     m_newChaSetData.iC1zlqgwVal = m_iNewswFlag[16];       //从柜1整流器过温
     m_newChaSetData.iC2zlqgwVal = m_iNewswFlag[17];       //从柜2整流器过温
     m_newChaSetData.iC3zlqgwVal = m_iNewswFlag[18];       //从柜3整流器过温
     m_newChaSetData.iC4zlqgwVal = m_iNewswFlag[19];       //从柜4整流器过温
     m_newChaSetData.iC1cwbhVal = m_iNewswFlag[20];        //从柜1错误保护
     m_newChaSetData.iC2cwbhVal = m_iNewswFlag[21];        //从柜2错误保护
     m_newChaSetData.iC3cwbhVal = m_iNewswFlag[22];        //从柜3错误保护
     m_newChaSetData.iC4cwbhVal = m_iNewswFlag[23];        //从柜4错误保护


     if(m_IniChainset.writenewChainsetInifile(m_newChaSetData))
     {
        memcpy(&g_newchasetdata,&m_newChaSetData,sizeof(m_newChaSetData));//更新连锁屏蔽设置参数给全局变量g_newchasetdata,add by zw 2022.02.23
        printf("####CChainsetdlg::okBtn_clicked()####g_newchasetdata.iC4zlqgwVal=%d\n",g_newchasetdata.iC4zlqgwVal);
        QMessageBox::warning(this,
                       tr(m_strFriendlytips),
                       tr(m_strAllSuccess));//连锁设置配置文件保存成功
    }
    else
    {
        QMessageBox::warning(this,
                       tr(m_strFriendlytips),
                       tr(m_strAllFailure));//连锁设置配置文件保存失败,请检查
     }

    this->close();

}

//滑台过位移2-连锁屏蔽设置-槽函数
void  CChainsetdlg::htgwysetBtn_clicked()
{
   m_ChainSetData.iHtgwyVal=m_iSwitchFlag[1];
   printf("####CChainsetdlg::htgwysetBtn_clicked()####m_ChainSetData.iHtgwyVal=%d\n",m_ChainSetData.iHtgwyVal);
   QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(0)));
}
//振动台过位移-连锁屏蔽设置-槽函数
void  CChainsetdlg::zdtgwysetBtn_clicked()
{
    m_ChainSetData.iZdtgwyVal=m_iSwitchFlag[2];
    printf("####CChainsetdlg::zdtgwysetBtn_clicked()####m_ChainSetData.iZdtgwyVal=%d\n",m_ChainSetData.iZdtgwyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(1)));
}
// 滑台低液位-连锁屏蔽设置-槽函数
void  CChainsetdlg::htdywsetBtn_clicked()
{
    m_ChainSetData.iHtdywVal=m_iSwitchFlag[3];
    printf("####CChainsetdlg::htdywsetBtn_clicked()####m_ChainSetData.iHtdywVal=%d\n",m_ChainSetData.iHtdywVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(2)));
}
//滑台轴承低压-连锁屏蔽设置-槽函数
void  CChainsetdlg::htqysetBtn_clicked()
{
    m_ChainSetData.iHtqyVal=m_iSwitchFlag[5];
    printf("####CChainsetdlg::htqysetBtn_clicked()####m_ChainSetData.iHtqyVal=%d\n",m_ChainSetData.iHtqyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(3)));
}
//振动台过温-连锁屏蔽设置-槽函数
void  CChainsetdlg::zdtgwsetBtn_clicked()
{
    m_ChainSetData.iZdtgwVal=m_iSwitchFlag[6];
    printf("####CChainsetdlg::zdtgwsetBtn_clicked()####m_ChainSetData.iZdtgwVal=%d\n",m_ChainSetData.iZdtgwVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(4)));
}
//耳轴过位移-连锁屏蔽设置-槽函数
void  CChainsetdlg::ezgwysetBtn_clicked()
{
    m_ChainSetData.iEzgwyVal=m_iSwitchFlag[7];
    printf("####CChainsetdlg::ezgwysetBtn_clicked()####m_ChainSetData.iEzgwyVal=%d\n",m_ChainSetData.iEzgwyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(5)));
}
//功放热继保护-连锁屏蔽设置-槽函数
void  CChainsetdlg::gfrjbhsetBtn_clicked()
{
    m_ChainSetData.iGfrjbhVal=m_iSwitchFlag[8];
    printf("####CChainsetdlg::gfrjbhsetBtn_clicked####m_ChainSetData.iGfrjbhVal=%d\n",m_ChainSetData.iGfrjbhVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(6)));
}
//静压轴承低压-连锁屏蔽设置-槽函数
void  CChainsetdlg::jyzcdysetBtn_clicked()
{
    m_ChainSetData.iJyzcdyVal=m_iSwitchFlag[9];
    printf("####CChainsetdlg::jyzcdysetBtn_clicked()####m_ChainSetData.iJyzcdyVal=%d\n",m_ChainSetData.iJyzcdyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(9)));
}
 //主柜门保护-连锁屏蔽设置-槽函数
void  CChainsetdlg::zgmenbhsetBtn_clicked()
{
    m_ChainSetData.iZgMenbVal=m_iSwitchFlag[10];
    printf("####CChainsetdlg::zgmenbhsetBtn_clicked()####m_ChainSetData.iZgMenbVal=%d\n",m_ChainSetData.iZgMenbVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(10)));
}
 //系统冷却单元-连锁屏蔽设置-槽函数
void  CChainsetdlg::xtlqdysetBtn_clicked()
{
    m_ChainSetData.iXtlqdyVal=m_iSwitchFlag[11];
    printf("####CChainsetdlg::xtlqdysetBtn_clicked()####m_ChainSetData.iXtlqdyVal=%d\n",m_ChainSetData.iXtlqdyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(13)));
}
//自定义1-连锁屏蔽设置-槽函数,add by 2019.05.25
void CChainsetdlg::selfdefine1setBtn_clicked()
{
    m_ChainSetData.iSelfdefineVal1=m_iSwitchFlag[4];
    printf("####CChainsetdlg::selfdefine1setBtn_clicked()####m_ChainSetData.iSelfdefineVal1=%d\n",m_ChainSetData.iSelfdefineVal1);
    /*QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(4)));*/
}
//自定义2-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::selfdefine2setBtn_clicked()
{
}
//自定义3-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::selfdefine3setBtn_clicked()
{
}

//从柜整流桥过温-连锁屏蔽设置-槽函数,add by 2019.05.25
void  CChainsetdlg::subzlqgwsetBtn_clicked()
{
    m_ChainSetData.iSubzlqgwVal=m_iSwitchFlag[16];
    printf("####CChainsetdlg::subzlqgwsetBtn_clicked()####m_ChainSetData.iSubzlqgwVal=%d\n",m_ChainSetData.iSubzlqgwVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(11)));

}
//从柜门保护-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::htgwsetBtn_clicked()
{
    m_ChainSetData.iSubMenbVal=m_iSwitchFlag[17];
    printf("####CChainsetdlg::htgwsetBtn_clicked()####m_ChainSetData.iSubMenbVal=%d\n",m_ChainSetData.iSubMenbVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(12)));
}
//主柜整流桥过温-连锁屏蔽设置-槽函数,add by 2019.05.25
void CChainsetdlg::htqywsetBtn_clicked()
{
    m_ChainSetData.iHtqywVal=m_iSwitchFlag[12];
    printf("####CChainsetdlg::zdtlqsetBtn_clicked()####m_ChainSetData.iHtqywVal=%d\n",m_ChainSetData.iHtqywVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(10)));

}
//从柜预留保护-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::subyuliubhsetBtn_clicked()
{

}
//所有设置按钮使能
void  CChainsetdlg::allSetBtnEnable(bool enable)
{
}
//系统冷却单元-切换-槽函数
void  CChainsetdlg::xtlqdySwitch_clicked()
{
   refreshChainButton(XTLQ_MASK,m_pUi->toolButton_xtlqdy);
}
//振动台过温-切换-槽函数
void  CChainsetdlg::zdtgwSwitch_clicked()
{
    refreshChainButton(ZDTGW_MASK, m_pUi->toolButton_zdtgw);
}
//振动台过位移-切换-槽函数
void  CChainsetdlg::zdtgwySwitch_clicked()
{
    refreshChainButton(ZDTGWY_MASK, m_pUi->toolButton_zdtgwy);
}
//滑台过位移-切换-槽函数
void  CChainsetdlg::htgwySwitch_clicked()
{
    refreshChainButton(HTGWY_MASK, m_pUi->toolButton_htgwy);
}
//滑台欠压-切换-槽函数
void  CChainsetdlg::htqySwitch_clicked()
{
    refreshChainButton(HTQY_MASK, m_pUi->toolButton_htqy);
}
//滑台欠液位-切换-槽函数
void CChainsetdlg::htqywSwitch_clicked()
{
    refreshChainButton(HTQYW_MASK,m_pUi->toolButton_htqyw);
}
//滑台过温-切换-槽函数
void CChainsetdlg::htgwSwitch_clicked()
{
    refreshChainButton(HTGW_MASK,m_pUi->toolButton_htgw);
}
//功放热继保护-切换-槽函数
void  CChainsetdlg::gfrhbhSwitch_clicked()
{
    refreshChainButton(GFRJBH_MASK, m_pUi->toolButton_gfrjbh);
}
//静压轴承低压-切换-槽函数
void  CChainsetdlg::jyzcdySwitch_clicked()
{
    refreshChainButton(JYZCDY_MASK,m_pUi->toolButton_jyzcdy);
}
//主柜门保护-切换-槽函数
void  CChainsetdlg::zgmenbhSwitch_clicked()
{
   refreshChainButton(ZGMBH_MASK,m_pUi->toolButton_zgmenbh);
}
//自定义1-切换-槽函数,add by 2019.05.18
void  CChainsetdlg::selfdefine1Switch_clicked()
{
    refreshChainButton(ZDY1_MASK, m_pUi->toolButton_selfdefine1);
}
//自定义2-切换-槽函数,add by 2019.05.18
void CChainsetdlg::selfdefine2Switch_clicked()
{
    refreshChainButton(ZDY2_MASK,m_pUi->toolButton_selfdefine2);
}
//自定义3-切换-槽函数,add by 2019.05.18
void CChainsetdlg::selfdefine3Switch_clicked()
{
    refreshChainButton(ZDY3_MASK,m_pUi->toolButton_selfdefine3);
}
//自定义4-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::selfdefine4Switch_clicked()
{
    refreshChainButton(ZDY4_MASK,m_pUi->toolButton_selfdefine4);
}
//从柜1整流器过温-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::c1zlqgwSwitch_clicked()
{
    refreshChainButton(CG1ZLQGW_MASK,m_pUi->toolButton_c1zlqgw);
}
//从柜2整流器过温-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::c2zlqgwSwitch_clicked()
{
    refreshChainButton(CG2ZLQGW_MASK,m_pUi->toolButton_c2zlqgw);
}
//从柜3整流器过温-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::c3zlqgwSwitch_clicked()
{
    refreshChainButton(CG3ZLQGW_MASK,m_pUi->toolButton_c3zlqgw);
}
//从柜4整流器过温-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::c4zlqgwSwitch_clicked()
{
    refreshChainButton(CG4ZLQGW_MASK,m_pUi->toolButton_c4zlqgw);
}
//从柜1错误保护-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::c1cwbhSwitch_clicked()
{
    refreshChainButton(CG1CWBH_MASK,m_pUi->toolButton_c1cwbh);
}
//从柜2错误保护-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::c2cwbhSwitch_clicked()
{
    refreshChainButton(CG2CWBH_MASK,m_pUi->toolButton_c2cwbh);
}
//从柜3错误保护-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::c3cwbhSwitch_clicked()
{
    refreshChainButton(CG3CWBH_MASK,m_pUi->toolButton_c3cwbh);
}
//从柜4错误保护-连锁屏蔽设置-槽函数,add by 2019.05.18
void CChainsetdlg::c4cwbhSwitch_clicked()
{
    refreshChainButton(CG4CWBH_MASK,m_pUi->toolButton_c4cwbh);
}
//从柜预留保护-切换-槽函数,add by 2019.05.18
void  CChainsetdlg::subyuliuSwitch_clicked()
{
}
//滑台低液位-切换-槽函数
void  CChainsetdlg::htdywSwitch_clicked()
{
//    refreshChainButton(HTDYW_INTERRUPT_MASK, m_pUi->toolButton_htdyw);
}


//耳轴过位移-切换-槽函数
void  CChainsetdlg::ezgwySwitch_clicked()
{
//    refreshChainButton(EZGWY_INTERRUPT_MASK, m_pUi->toolButton_ezgwy);
}






//从柜整流器过温-切换-槽函数,add by 2019.05.25
void CChainsetdlg::subzlqgwSwitch_clicked()
{
//    refreshChainButton(SUBZLQGW_INTERRUPT_MASK,m_pUi->toolButton_subzlqgw);
}
//刷新连锁按钮状态
void  CChainsetdlg::refreshChainButton(int nIndex,QToolButton *toolButton)
{
//    if(m_iSwitchFlag[nIndex]==1)
//    {
//     toolButton->setIcon(m_ybofficon);
//     toolButton->setIconSize(QSize(66, 48));
//     m_iSwitchFlag[nIndex]=0;
//    }
//    else
//    {
//      toolButton->setIcon(m_ybonicon);
//      toolButton->setIconSize(QSize(66, 48));
//      m_iSwitchFlag[nIndex]=1;
//    }
    if(m_iNewswFlag[nIndex]==1)
    {
     toolButton->setIcon(m_ybofficon);
     toolButton->setIconSize(QSize(66, 48));
     m_iNewswFlag[nIndex]=0;
    }
    else
    {
      toolButton->setIcon(m_ybonicon);
      toolButton->setIconSize(QSize(66, 48));
      m_iNewswFlag[nIndex]=1;
    }
//     m_iChainsetval=m_Gpiorw.ai_data_compute(m_iSwitchFlag);
     switch (nIndex) {
     case 4:
         m_iChainsetval = g_newfaultstatus.iVIBODFlag;
         break;
     case 2:
         m_iChainsetval = g_newfaultstatus.iVIBCUFlag;
         break;
     case 3:
         m_iChainsetval = g_newfaultstatus.iVIBOTFlag;
         break;
     case 5:
         m_iChainsetval = g_newfaultstatus.iSTODFlag;
         break;
     case 6:
         m_iChainsetval = g_newfaultstatus.iSTUPFlag;
         break;
     case 8:
         m_iChainsetval = g_newfaultstatus.iSTOTFlag;
         break;
     case 7:
         m_iChainsetval = g_newfaultstatus.iSTOLFlag;
         break;
     case 9:
         m_iChainsetval = g_newfaultstatus.iRELAYFlag;
         break;
     case 11:
         m_iChainsetval = g_newfaultstatus.iDOORFlag;
         break;
     case 10:
         m_iChainsetval = g_newfaultstatus.iHBUPFlag;
         break;
     case 12:
         m_iChainsetval = g_newfaultstatus.iEXT1Flag;
         break;
     case 13:
         m_iChainsetval = g_newfaultstatus.iEXT2Flag;
         break;
     case 14:
         m_iChainsetval = g_newfaultstatus.iEXT3Flag;
         break;
     case 15:
         m_iChainsetval = g_newfaultstatus.iEXT4Flag;
         break;
     case 0:
         m_iChainsetval = g_newfaultstatus.iESTOPFlag;
         break;
     case 16:
         m_iChainsetval = g_newfaultstatus.iOT1Flag;
         break;
     case 17:
         m_iChainsetval = g_newfaultstatus.iOT2Flag;
         break;
     case 18:
         m_iChainsetval = g_newfaultstatus.iOT3Flag;
         break;
     case 19:
         m_iChainsetval = g_newfaultstatus.iOT4Flag;
         break;
     case 1:
         m_iChainsetval = g_newfaultstatus.iSESTOPFlag;
         break;
     case 20:
         m_iChainsetval = g_newfaultstatus.iFAULT1Flag;
         break;
     case 21:
         m_iChainsetval = g_newfaultstatus.iFAULT2Flag;
         break;
     case 22:
         m_iChainsetval = g_newfaultstatus.iFAULT3Flag;
         break;
     case 23:
         m_iChainsetval = g_newfaultstatus.iFAULT4Flag;
         break;
     default:
         break;
     }
     printf("####nIndex=%d,m_iChainsetval=%d####\n",nIndex,m_iChainsetval);
}
void  CChainsetdlg::showChainButton(int nIndex,QToolButton *toolButton)
{
    if(m_iNewswFlag[nIndex]==1)
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
//获取连锁参数数据
STRU_CHAINSETDATA CChainsetdlg::getChainSetData()
{
    return m_ChainSetData;
}
void CChainsetdlg::chainLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("chainsetDialog", "\350\277\236\351\224\201\345\261\217\350\224\275\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_12->setText(QApplication::translate("chainsetDialog", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
        m_pUi->label_13->setText(QApplication::translate("chainsetDialog", "\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        m_pUi->normalBtn->setText(QApplication::translate("chainsetDialog", "\346\255\243\345\270\270", 0, QApplication::UnicodeUTF8));
        m_pUi->debugBtn->setText(QApplication::translate("chainsetDialog", "\350\260\203\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pUi->okBtn->setText(QApplication::translate("chainsetDialog", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        m_pUi->label_14->setText(QApplication::translate("chainsetDialog", "\347\263\273\347\273\237\345\206\267\345\215\264\345\215\225\345\205\203", 0, QApplication::UnicodeUTF8));
        //m_pUi->xtlqdysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_7->setText(QApplication::translate("chainsetDialog", "\346\214\257\345\212\250\345\217\260\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
        //m_pUi->zdtgwsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_2->setText(QApplication::translate("chainsetDialog", "\346\273\221\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        //m_pUi->htgwysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_8->setText(QApplication::translate("chainsetDialog", "\350\200\263\350\275\264\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        //m_pUi->ezgwysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_3->setText(QApplication::translate("chainsetDialog", "\346\214\257\345\212\250\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        //m_pUi->zdtgwysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_10->setText(QApplication::translate("chainsetDialog", "\351\235\231\345\216\213\350\275\264\346\211\277\344\275\216\345\216\213", 0, QApplication::UnicodeUTF8));
        //m_pUi->jyzcdysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
//        m_pUi->label_4->setText(QApplication::translate("chainsetDialog", " \346\273\221\345\217\260\344\275\216\346\266\262\344\275\215", 0, QApplication::UnicodeUTF8));
        //m_pUi->htdywsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_21->setText(QApplication::translate("chainsetDialog", "\344\273\216\346\237\234\351\227\250\344\277\235\346\212\244      ", 0, QApplication::UnicodeUTF8));
        //m_pUi->htgwsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_6->setText(QApplication::translate("chainsetDialog", "\346\273\221\345\217\260\350\275\264\346\211\277\344\275\216\345\216\213", 0, QApplication::UnicodeUTF8));
        //m_pUi->htqysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_15->setText(QApplication::translate("chainsetDialog", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        //m_pUi->selfdefine1setBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_9->setText(QApplication::translate("chainsetDialog", "\345\212\237\346\224\276\347\203\255\347\273\247\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        //m_pUi->gfrjbhsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_16->setText(QApplication::translate("chainsetDialog", "\350\207\252\345\256\232\344\271\2112", 0, QApplication::UnicodeUTF8));
        //m_pUi->selfdefine2setBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
//        m_pUi->label_18->setText(QApplication::translate("chainsetDialog", "\344\270\273\346\237\234\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251   ", 0, QApplication::UnicodeUTF8));
        //m_pUi->htqywsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_17->setText(QApplication::translate("chainsetDialog", "\350\207\252\345\256\232\344\271\2113", 0, QApplication::UnicodeUTF8));
        //m_pUi->selfdefine3setBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
//        m_pUi->label_20->setText(QApplication::translate("chainsetDialog", "\344\273\216\346\237\234\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251  ", 0, QApplication::UnicodeUTF8));
        //m_pUi->subzlqgwsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
//        m_pUi->label_19->setText(QApplication::translate("chainsetDialog", "\344\273\216\346\237\234\351\242\204\347\225\231\344\277\235\346\212\244   ", 0, QApplication::UnicodeUTF8));
        //m_pUi->subyuliubhsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_11->setText(QApplication::translate("chainsetDialog", "\344\270\273\346\237\234\351\227\250\344\277\235\346\212\244      ", 0, QApplication::UnicodeUTF8));
        //m_pUi->zgmenbhsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_26->setText(QApplication::translate("chainsetDialog", "\350\201\224\351\224\201\345\261\217\350\224\275", 0, QApplication::UnicodeUTF8));//add by 2020.09.01
        m_pUi->label_27->setText(QApplication::translate("chainsetDialog","\350\201\224\351\224\201\345\261\217\350\224\275", 0, QApplication::UnicodeUTF8));//add by 2020.09.01
        m_pUi->label_28->setText(QApplication::translate("chainsetDialog", "\350\247\246\347\202\271\345\210\207\346\215\242", 0, QApplication::UnicodeUTF8));//add by 2020.09.01
        m_pUi->label_29->setText(QApplication::translate("chainsetDialog", "\350\247\246\347\202\271\345\210\207\346\215\242", 0, QApplication::UnicodeUTF8));//add by 2020.09.01

        m_strFriendlytips=QApplication::translate("chainsetDialog",
        "\345\217\213\346\203\205\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//友情提示

     m_strAllSuccess=QApplication::translate("chainsetDialog",
         "\346\211\200\346\234\211\350\277\236\351\224\201\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);   //所有连锁设置成功

     m_strAllFailure=QApplication::translate("chainsetDialog",
         "\346\211\200\346\234\211\350\277\236\351\224\201\350\256\276\347\275\256\345\244\261\350\264\245",
         0, QApplication::UnicodeUTF8); //所有连锁设置失败
    }
    else
    {
        setWindowTitle("Interlock");
        m_pUi->label_12->setText("All");
        m_pUi->label_13->setText("Mode");
        m_pUi->normalBtn->setText("Normal");
        m_pUi->debugBtn->setText("Debug");
        m_pUi->okBtn->setText("OK");
        m_pUi->label_14->setText("S.C.U.");
        //m_pUi->xtlqdysetBtn->setText("Set");
        m_pUi->label_7->setText("VIB. OverTEMP");
        //m_pUi->zdtgwsetBtn->setText("Set");
        m_pUi->label_2->setText("S.T. Overtravel");
        //m_pUi->htgwysetBtn->setText("Set");
        m_pUi->label_8->setText("TRUN. O/T");
        //m_pUi->ezgwysetBtn->setText("Set");
        m_pUi->label_3->setText("VIB. Overtravel");
        //m_pUi->zdtgwysetBtn->setText("Set");
        m_pUi->label_10->setText("VIB. U/P");
        //m_pUi->jyzcdysetBtn->setText("Set");
//        m_pUi->label_4->setText("S.T. U/L");
        //m_pUi->htdywsetBtn->setText("Set");
        m_pUi->label_21->setText("Cab Doors");
        //m_pUi->htgwsetBtn->setText("Set");
        m_pUi->label_6->setText("S.T. U/P");
        //m_pUi->htqysetBtn->setText("Set");
        m_pUi->label_15->setText("External1");
        //m_pUi->selfdefine1setBtn->setText("Set");
        m_pUi->label_9->setText("Relay O/L");
        //m_pUi->gfrjbhsetBtn->setText("Set");
        m_pUi->label_16->setText("External2");
        //m_pUi->selfdefine2setBtn->setText("Set");
//        m_pUi->label_18->setText("M.R. OverTEMP");
        //m_pUi->htqywsetBtn->setText("Set");
        m_pUi->label_17->setText("External3");
        //m_pUi->selfdefine3setBtn->setText("Set");
//        m_pUi->label_20->setText("C.R. OverTEMP");
        //m_pUi->subzlqgwsetBtn->setText("Set");
//        m_pUi->label_19->setText("Cab Reserved");
        //m_pUi->subyuliubhsetBtn->setText("Set");
        m_pUi->label_11->setText("Main Doors");
        //m_pUi->zgmenbhsetBtn->setText("Set");

        m_pUi->label_26->setText("Interlock Shield");//add by 2020.09.01
        m_pUi->label_27->setText("Interlock Shield");//add by 2020.09.01
        m_pUi->label_28->setText("Contact Switch");//add by 2020.09.01
        m_pUi->label_29->setText("Contact Switch");//add by 2020.09.01

        m_strFriendlytips="Friendly tips";//友情提示

        m_strAllSuccess="Interlock set successfully";   //所有连锁设置成功

        m_strAllFailure="Interlock setting failed";    //所有连锁设置失败
    }
}
//返回键槽函数实现 add by 2020.08.10@@@
void CChainsetdlg::closeBtn_clicked()
{
    this->close();
}

//系统冷却单元保护触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_xtlqdy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Xtlq=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Xtlq=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Xtlq=NORMAL_OPEN;
        break;
    }
    printf("isw_Xtlq = %d",index,m_newChaSetData.isw_Xtlq);
}
//振动台过温触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_zdtgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Zdtgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Zdtgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Zdtgw=NORMAL_OPEN;
        break;
    }
    printf("isw_Zdtgw = %d",index,m_newChaSetData.isw_Zdtgw);
}
//振动台过位移触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_zdtgwy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Zdtgwy=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Zdtgwy=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Zdtgwy=NORMAL_OPEN;
        break;
    }
    printf("isw_Zdtgwy = %d",index,m_newChaSetData.isw_Zdtgwy);
}
//滑台过位移触点切换槽函数实现 add by 2020.09.05
void CChainsetdlg::comboBox_htgwy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Htgwy=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Htgwy=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Htgwy=NORMAL_OPEN;
        break;
    }
    printf("isw_Htgwy = %d",index,m_newChaSetData.isw_Htgwy);
}
//滑台欠压触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_htqy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Htqy=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Htqy=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Htqy=NORMAL_OPEN;
        break;
    }
    printf("isw_Htqy = %d",index,m_newChaSetData.isw_Htqy);
}
//滑台欠液位触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_htqyw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Htqyw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Htqyw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Htqyw=NORMAL_OPEN;
        break;
    }
    printf("isw_Htqyw = %d",index,m_newChaSetData.isw_Htqyw);
}
//滑台过温触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_htgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Htgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Htgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Htgw=NORMAL_OPEN;
        break;
    }
    printf("isw_Htgw = %d",index,m_newChaSetData.isw_Htgw);
}
//功放热继保护触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_gfrjbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Gfrjbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Gfrjbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Gfrjbh=NORMAL_OPEN;
        break;
    }
    printf("isw_Gfrjbh = %d",index,m_newChaSetData.isw_Gfrjbh);
}
//静压轴承低压触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_jyzcdy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Jyzcdy=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Jyzcdy=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Jyzcdy=NORMAL_OPEN;
        break;
    }
    printf("isw_Jyzcdy = %d",index,m_newChaSetData.isw_Jyzcdy);
}
//主柜门保护触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_zgmenbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Zgmbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Zgmbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Zgmbh=NORMAL_OPEN;
        break;
    }
    printf("isw_Zgmbh = %d",index,m_newChaSetData.isw_Zgmbh);
}
//自定义1保护触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_selfdefine1_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Selfdef1=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Selfdef1=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Selfdef1=NORMAL_OPEN;
        break;
    }
    printf("isw_Selfdef1 = %d",index,m_newChaSetData.isw_Selfdef1);
}
//自定义2保护触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_selfdefine2_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Selfdef2=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Selfdef2=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Selfdef2=NORMAL_OPEN;
        break;
    }
    printf("isw_Selfdef2 = %d",index,m_newChaSetData.isw_Selfdef2);
}
//自定义3保护触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_selfdefine3_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Selfdef3=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Selfdef3=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Selfdef3=NORMAL_OPEN;
        break;
    }
    printf("isw_Selfdef3 = %d",index,m_newChaSetData.isw_Selfdef3);
}
//自定义4保护触点切换槽函数实现 add by zw 2022.02.23
void CChainsetdlg::comboBox_selfdefine4_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Selfdef4=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Selfdef4=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Selfdef4=NORMAL_OPEN;
        break;
    }
    printf("isw_Selfdef4 = %d",index,m_newChaSetData.isw_Selfdef4);
}
//从柜1整流器过温触点切换槽函数 add by zw 2022.02.23
void CChainsetdlg::comboBox_c1zlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C1zlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C1zlqgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C1zlqgw=NORMAL_OPEN;
        break;
    }
    printf("isw_C1zlqgw = %d",index,m_newChaSetData.isw_C1zlqgw);
}
//从柜2整流器过温触点切换槽函数 add by zw 2022.02.23
void CChainsetdlg::comboBox_c2zlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C2zlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C2zlqgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C2zlqgw=NORMAL_OPEN;
        break;
    }
    printf("isw_C2zlqgw = %d",index,m_newChaSetData.isw_C2zlqgw);
}
//从柜3整流器过温触点切换槽函数 add by zw 2022.02.23
void CChainsetdlg::comboBox_c3zlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C3zlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C3zlqgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C3zlqgw=NORMAL_OPEN;
        break;
    }
    printf("isw_C3zlqgw = %d",index,m_newChaSetData.isw_C3zlqgw);
}
//从柜4整流器过温触点切换槽函数 add by zw 2022.02.23
void CChainsetdlg::comboBox_c4zlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C4zlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C4zlqgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C4zlqgw=NORMAL_OPEN;
        break;
    }
    printf("isw_C4zlqgw = %d",index,m_newChaSetData.isw_C4zlqgw);
}
//从柜1错误信号触点切换槽函数 add by zw 2022.02.23
void CChainsetdlg::comboBox_c1cwbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C1cwbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C1cwbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C1cwbh=NORMAL_OPEN;
        break;
    }
    printf("isw_C1cwbh = %d",index,m_newChaSetData.isw_C1cwbh);
}
//从柜2错误信号触点切换槽函数 add by zw 2022.02.23
void CChainsetdlg::comboBox_c2cwbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C2cwbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C2cwbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C2cwbh=NORMAL_OPEN;
        break;
    }
    printf("isw_C2cwbh = %d",index,m_newChaSetData.isw_C2cwbh);
}
//从柜3错误信号触点切换槽函数 add by zw 2022.02.23
void CChainsetdlg::comboBox_c3cwbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C3cwbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C3cwbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C3cwbh=NORMAL_OPEN;
        break;
    }
    printf("isw_C3cwbh = %d",index,m_newChaSetData.isw_C3cwbh);
}
//从柜4错误信号触点切换槽函数 add by zw 2022.02.23
void CChainsetdlg::comboBox_c4cwbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C4cwbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C4cwbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C4cwbh=NORMAL_OPEN;
        break;
    }
    printf("isw_C4cwbh = %d",index,m_newChaSetData.isw_C4cwbh);
}

//滑台低液位触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_htdyw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_ChainSetData.iSwitch_htdyw=NORMAL_OPEN;
        break;
    case 1:
        m_ChainSetData.iSwitch_htdyw=NORMAL_CLOSE;
        break;
    default:
        m_ChainSetData.iSwitch_htdyw=NORMAL_OPEN;
        break;
    }
    printf("isw_Xtlq = %d",index,m_newChaSetData.isw_Xtlq);
}



//从柜整流器过温触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_subzlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_ChainSetData.iSwitch_subzlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_ChainSetData.iSwitch_subzlqgw=NORMAL_CLOSE;
        break;
    default:
        m_ChainSetData.iSwitch_subzlqgw=NORMAL_OPEN;
        break;
    }

}


//耳轴过位移触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_ezgwy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_ChainSetData.iSwitch_ezgwy=NORMAL_OPEN;
        break;
    case 1:
        m_ChainSetData.iSwitch_ezgwy=NORMAL_CLOSE;
        break;
    default:
        m_ChainSetData.iSwitch_ezgwy=NORMAL_OPEN;
        break;
    }

}



//从柜预留保护触点切换槽函数实现 add by 2020.09.08
void CChainsetdlg::comboBox_subyuliu_activated(int index)
{
    switch(index)
    {
    case 0:
        m_ChainSetData.iSwitch_subyuliu=NORMAL_OPEN;
        break;
    case 1:
        m_ChainSetData.iSwitch_subyuliu=NORMAL_CLOSE;
        break;
    default:
        m_ChainSetData.iSwitch_subyuliu=NORMAL_OPEN;
        break;
    }

}


//初始化m_newChaSetData变量,add by zw 2022.02.23
void CChainsetdlg::newinitChainSetData()
{
     //连锁参数结构体变量初始化,add by 2019.04.13
    if(!(m_IniChainset.readnewChainsetInifile(m_newChaSetData)))
    {
     m_newChaSetData.iJjtjVal=SWITCH_OFF;       //紧急停机
     m_newChaSetData.iSJitiVal=SWITCH_OFF;      //S紧急停机
     m_newChaSetData.iXtlqVal=SWITCH_OFF;       //系统冷却
     m_newChaSetData.iZdtgwVal=SWITCH_OFF;      //振动台过温
     m_newChaSetData.iZdtgwyVal=SWITCH_OFF;     //振动台过位移
     m_newChaSetData.iHtgwyVal=SWITCH_OFF;      //滑台过位移
     m_newChaSetData.iHtqyVal=SWITCH_OFF;       //滑台欠压
     m_newChaSetData.iHtqywVal=SWITCH_OFF;      //滑台欠液位
     m_newChaSetData.iHtgwVal=SWITCH_OFF;       //滑台过温
     m_newChaSetData.iGfrjbhVal=SWITCH_OFF;     //功放热继保护
     m_newChaSetData.iJyzcdyVal=SWITCH_OFF;     //静压轴承低压
     m_newChaSetData.iZgmbhVal=SWITCH_OFF;      //主柜门保护
     m_newChaSetData.iSelfdefVal1=SWITCH_OFF;   //自定义1
     m_newChaSetData.iSelfdefVal2=SWITCH_OFF;   //自定义2
     m_newChaSetData.iSelfdefVal3=SWITCH_OFF;   //自定义3
     m_newChaSetData.iSelfdefVal4=SWITCH_OFF;   //自定义4
     m_newChaSetData.iC1zlqgwVal=SWITCH_OFF;    //从柜1整流器过温
     m_newChaSetData.iC2zlqgwVal=SWITCH_OFF;    //从柜2整流器过温
     m_newChaSetData.iC3zlqgwVal=SWITCH_OFF;    //从柜3整流器过温
     m_newChaSetData.iC4zlqgwVal=SWITCH_OFF;    //从柜4整流器过温
     m_newChaSetData.iC1cwbhVal=SWITCH_OFF;     //从柜1错误保护
     m_newChaSetData.iC2cwbhVal=SWITCH_OFF;     //从柜2错误保护
     m_newChaSetData.iC3cwbhVal=SWITCH_OFF;     //从柜3错误保护
     m_newChaSetData.iC4cwbhVal=SWITCH_OFF;     //从柜4错误保护

     //触点切换初始化-常开
     m_newChaSetData.isw_Jjtj=SWITCH_OFF;       //紧急停机
     m_newChaSetData.isw_SJiti=SWITCH_OFF;      //S紧急停机
     m_newChaSetData.isw_Xtlq=SWITCH_OFF;       //系统冷却
     m_newChaSetData.isw_Zdtgw=SWITCH_OFF;      //振动台过温
     m_newChaSetData.isw_Zdtgwy=SWITCH_OFF;     //振动台过位移
     m_newChaSetData.isw_Htgwy=SWITCH_OFF;      //滑台过位移
     m_newChaSetData.isw_Htqy=SWITCH_OFF;       //滑台欠压
     m_newChaSetData.isw_Htqyw=SWITCH_OFF;      //滑台欠液位
     m_newChaSetData.isw_Htgw=SWITCH_OFF;       //滑台过温
     m_newChaSetData.isw_Gfrjbh=SWITCH_OFF;     //功放热继保护
     m_newChaSetData.isw_Jyzcdy=SWITCH_OFF;     //静压轴承低压
     m_newChaSetData.isw_Zgmbh=SWITCH_OFF;      //主柜门保护
     m_newChaSetData.isw_Selfdef1=SWITCH_OFF;   //自定义1
     m_newChaSetData.isw_Selfdef2=SWITCH_OFF;   //自定义2
     m_newChaSetData.isw_Selfdef3=SWITCH_OFF;   //自定义3
     m_newChaSetData.isw_Selfdef4=SWITCH_OFF;   //自定义4
     m_newChaSetData.isw_C1zlqgw=SWITCH_OFF;    //从柜1整流器过温
     m_newChaSetData.isw_C2zlqgw=SWITCH_OFF;    //从柜2整流器过温
     m_newChaSetData.isw_C3zlqgw=SWITCH_OFF;    //从柜3整流器过温
     m_newChaSetData.isw_C4zlqgw=SWITCH_OFF;    //从柜4整流器过温
     m_newChaSetData.isw_C1cwbh=SWITCH_OFF;     //从柜1错误保护
     m_newChaSetData.isw_C2cwbh=SWITCH_OFF;     //从柜2错误保护
     m_newChaSetData.isw_C3cwbh=SWITCH_OFF;     //从柜3错误保护
     m_newChaSetData.isw_C4cwbh=SWITCH_OFF;     //从柜4错误保护
    }
      m_iNewswFlag[0] = m_newChaSetData.iJjtjVal;           //紧急停机
      m_iNewswFlag[1] = m_newChaSetData.iSJitiVal;          //S紧急停机
      m_iNewswFlag[2] = m_newChaSetData.iXtlqVal;           //系统冷却
      m_iNewswFlag[3] = m_newChaSetData.iZdtgwVal;          //振动台过温
      m_iNewswFlag[4] = m_newChaSetData.iZdtgwyVal;         //振动台过位移
      m_iNewswFlag[5] = m_newChaSetData.iHtgwyVal;          //滑台过位移
      m_iNewswFlag[6] = m_newChaSetData.iHtqyVal;           //滑台欠压
      m_iNewswFlag[7] = m_newChaSetData.iHtqywVal;          //滑台欠液位
      m_iNewswFlag[8] = m_newChaSetData.iHtgwVal;           //滑台过温
      m_iNewswFlag[9] = m_newChaSetData.iGfrjbhVal;         //功放热继保护
      m_iNewswFlag[10] = m_newChaSetData.iJyzcdyVal;        //静压轴承低压
      m_iNewswFlag[11] = m_newChaSetData.iZgmbhVal;         //主柜门保护
      m_iNewswFlag[12] = m_newChaSetData.iSelfdefVal1;      //自定义1
      m_iNewswFlag[13] = m_newChaSetData.iSelfdefVal2;      //自定义2
      m_iNewswFlag[14] = m_newChaSetData.iSelfdefVal3;      //自定义3
      m_iNewswFlag[15] = m_newChaSetData.iSelfdefVal4;      //自定义4
      m_iNewswFlag[16] = m_newChaSetData.iC1zlqgwVal;       //从柜1整流器过温
      m_iNewswFlag[17] = m_newChaSetData.iC2zlqgwVal;       //从柜2整流器过温
      m_iNewswFlag[18] = m_newChaSetData.iC3zlqgwVal;       //从柜3整流器过温
      m_iNewswFlag[19] = m_newChaSetData.iC4zlqgwVal;       //从柜4整流器过温
      m_iNewswFlag[20] = m_newChaSetData.iC1cwbhVal;        //从柜1错误保护
      m_iNewswFlag[21] = m_newChaSetData.iC2cwbhVal;        //从柜2错误保护
      m_iNewswFlag[22] = m_newChaSetData.iC3cwbhVal;        //从柜3错误保护
      m_iNewswFlag[23] = m_newChaSetData.iC4cwbhVal;        //从柜4错误保护

    memcpy(&g_newchasetdata,&m_newChaSetData,sizeof(m_newChaSetData));//连锁屏蔽设置变量g_newchasetdata初始化

//    showChainButton(JJTJ_MASK, m_pUi->tool);           //紧急停机
//    showChainButton(SJJTJ_MASK, m_pUi->toolButton_xtlqdy);          //S紧急停机
    showChainButton(XTLQ_MASK, m_pUi->toolButton_xtlqdy);               //系统冷却
    showChainButton(ZDTGW_MASK, m_pUi->toolButton_zdtgw);               //振动台过温
    showChainButton(ZDTGWY_MASK, m_pUi->toolButton_zdtgwy);             //振动台过位移
    showChainButton(HTGWY_MASK, m_pUi->toolButton_htgwy);               //滑台过位移
    showChainButton(HTQY_MASK, m_pUi->toolButton_htqy);                 //滑台欠压
    showChainButton(HTQYW_MASK, m_pUi->toolButton_htqyw);               //滑台欠液位
    showChainButton(HTGW_MASK, m_pUi->toolButton_htgw);                 //滑台过温
    showChainButton(GFRJBH_MASK, m_pUi->toolButton_gfrjbh);             //功放热继保护
    showChainButton(JYZCDY_MASK, m_pUi->toolButton_jyzcdy);             //静压轴承低压
    showChainButton(ZGMBH_MASK, m_pUi->toolButton_zgmenbh);             //主柜门保护
    showChainButton(ZDY1_MASK, m_pUi->toolButton_selfdefine1);          //自定义1
    showChainButton(ZDY2_MASK, m_pUi->toolButton_selfdefine2);          //自定义2
    showChainButton(ZDY3_MASK, m_pUi->toolButton_selfdefine3);          //自定义3
    showChainButton(ZDY4_MASK, m_pUi->toolButton_selfdefine4);          //自定义4
    showChainButton(CG1ZLQGW_MASK, m_pUi->toolButton_c1zlqgw);          //从柜1整流器过温
    showChainButton(CG2ZLQGW_MASK, m_pUi->toolButton_c2zlqgw);          //从柜2整流器过温
    showChainButton(CG3ZLQGW_MASK, m_pUi->toolButton_c3zlqgw);          //从柜3整流器过温
    showChainButton(CG4ZLQGW_MASK, m_pUi->toolButton_c4zlqgw);          //从柜4整流器过温
    showChainButton(CG1CWBH_MASK, m_pUi->toolButton_c1cwbh);            //从柜1错误保护
    showChainButton(CG2CWBH_MASK, m_pUi->toolButton_c2cwbh);            //从柜2错误保护
    showChainButton(CG3CWBH_MASK, m_pUi->toolButton_c3cwbh);            //从柜3错误保护
    showChainButton(CG4CWBH_MASK, m_pUi->toolButton_c4cwbh);            //从柜4错误保护

    //触点切换-显示-函数
    m_pUi->comboBox_xtlqdy->setCurrentIndex(m_newChaSetData.isw_Xtlq);                  //系统冷却
    m_pUi->comboBox_zdtgw->setCurrentIndex(m_newChaSetData.isw_Zdtgw);                 //振动台过温
    m_pUi->comboBox_zdtgwy->setCurrentIndex(m_newChaSetData.isw_Zdtgwy);                //振动台过位移
    m_pUi->comboBox_htgwy->setCurrentIndex(m_newChaSetData.isw_Htgwy);                 //滑台过位移
    m_pUi->comboBox_htqy->setCurrentIndex(m_newChaSetData.isw_Htqy);                  //滑台欠压
    m_pUi->comboBox_htqyw->setCurrentIndex(m_newChaSetData.isw_Htqyw);                 //滑台欠液位
    m_pUi->comboBox_htgw->setCurrentIndex(m_newChaSetData.isw_Htgw);                  //滑台过温
    m_pUi->comboBox_gfrjbh->setCurrentIndex(m_newChaSetData.isw_Gfrjbh);                //功放热继保护
    m_pUi->comboBox_jyzcdy->setCurrentIndex(m_newChaSetData.isw_Jyzcdy);                //静压轴承低压
    m_pUi->comboBox_zgmenbh->setCurrentIndex(m_newChaSetData.isw_Zgmbh);                 //主柜门保护
    m_pUi->comboBox_selfdefine1->setCurrentIndex(m_newChaSetData.isw_Selfdef1);              //自定义1
    m_pUi->comboBox_selfdefine2->setCurrentIndex(m_newChaSetData.isw_Selfdef2);              //自定义2
    m_pUi->comboBox_selfdefine3->setCurrentIndex(m_newChaSetData.isw_Selfdef3);              //自定义3
    m_pUi->comboBox_selfdefine4->setCurrentIndex(m_newChaSetData.isw_Selfdef4);              //自定义4
    m_pUi->comboBox_c1zlqgw->setCurrentIndex(m_newChaSetData.isw_C1zlqgw);               //从柜1整流器过温
    m_pUi->comboBox_c2zlqgw->setCurrentIndex(m_newChaSetData.isw_C2zlqgw);               //从柜2整流器过温
    m_pUi->comboBox_c3zlqgw->setCurrentIndex(m_newChaSetData.isw_C3zlqgw);               //从柜3整流器过温
    m_pUi->comboBox_c4zlqgw->setCurrentIndex(m_newChaSetData.isw_C4zlqgw);               //从柜4整流器过温
    m_pUi->comboBox_c1cwbh->setCurrentIndex(m_newChaSetData.isw_C1cwbh);                //从柜1错误保护
    m_pUi->comboBox_c2cwbh->setCurrentIndex(m_newChaSetData.isw_C2cwbh);                //从柜2错误保护
    m_pUi->comboBox_c3cwbh->setCurrentIndex(m_newChaSetData.isw_C3cwbh);                //从柜3错误保护
    m_pUi->comboBox_c4cwbh->setCurrentIndex(m_newChaSetData.isw_C4cwbh);                //从柜4错误保护

}
