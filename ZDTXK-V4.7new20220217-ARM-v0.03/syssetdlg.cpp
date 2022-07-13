/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: syssetdlg.cpp
** 摘要: 校准系数对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.12.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2018.12.01   V1.0      创建
**
****************************************************************************/
#include "syssetdlg.h"
#include <QMessageBox>
#include <qtimer.h>
#ifdef WIN_DEV
#include <windows.h>
#else
#include <time.h>
#endif
extern int g_iLangChange;//add by 2020.11.20
CSyssetdlg::CSyssetdlg()
{
    m_pUi= new Ui::syssetDialog;
    m_pUi->setupUi(this);
    m_timer = new QTimer(this);
    m_isTimeEditFlag=false;
    connect(m_pUi->radioButton, SIGNAL(clicked()), this, SLOT(sysTimesetBtn_clicked()));
    connect(m_pUi->okBtn, SIGNAL(clicked()), this, SLOT(okBtn_clicked()));//确定槽函数 add by 2020.08.15
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateSystimeEdit()));
    connect(m_pUi->restorefactoryBtn, SIGNAL(clicked()), this, SLOT(restorefactoryBtn_clicked()));//恢复出厂设置槽函数 add by 2020.11.18
    m_timer->start(1000);
}
CSyssetdlg::~CSyssetdlg()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
    }
}
//系统时间设置实现 add by 2020.08.15
void  CSyssetdlg::sysTimesetBtn_clicked()
{
    if(m_pUi->radioButton->isChecked())
    {
        m_isTimeEditFlag=true;	 //编辑态
    }
    else
    {
        m_isTimeEditFlag=false; //非编辑态
    }
}
void CSyssetdlg::updateSystimeEdit()
{
    if(!m_isTimeEditFlag)
    {
        //非编辑态
      QDateTime current_date_time =QDateTime::currentDateTime();
      QString current_date =current_date_time.toString("yyyy.MM.dd \n hh:mm:ss");
      m_pUi->dateTimeEdit->setDateTime(current_date_time);
    }

}

//确定键槽函数实现 add by 2020.08.15
void  CSyssetdlg::okBtn_clicked()
{
    #ifdef WIN_DEV
    SYSTEMTIME st;
    QString strYear=m_pUi->dateTimeEdit->sectionText(QDateTimeEdit::YearSection);
    QString strMonth=m_pUi->dateTimeEdit->sectionText(QDateTimeEdit::MonthSection);
    QString strDay = m_pUi->dateTimeEdit->sectionText(QDateTimeEdit::DaySection);
    QString strHour = m_pUi->dateTimeEdit->sectionText(QDateTimeEdit::HourSection);
    QString strMinute = m_pUi->dateTimeEdit->sectionText(QDateTimeEdit::MinuteSection);
    QString strSecond = m_pUi->dateTimeEdit->sectionText(QDateTimeEdit::SecondSection);
    bool ok =false;
    st.wYear=strYear.toInt(&ok,10);
    st.wMonth=strMonth.toInt(&ok,10);
    st.wDay=strDay.toInt(&ok,10);
    st.wHour=strHour.toInt(&ok,10)-8;
    st.wMinute=strMinute.toInt(&ok,10);
    st.wSecond=strSecond.toInt(&ok,10);
    bool tmsetflag=false;
    tmsetflag=SetSystemTime(&st);
    if(tmsetflag)
    {
        QString strError1=QApplication::translate("syssetDialog", "\347\263\273\347\273\237\346\227\266\351\227\264\350\256\276\347\275\256\345\244\261\350\264\245", 0, QApplication::UnicodeUTF8);
         QMessageBox::warning(this, m_strErrinfo,strError1);//系统时间设置成功提示,add by 2020.08.15
    }
    else
    {
        QString strError=QApplication::translate("syssetDialog", "\347\263\273\347\273\237\346\227\266\351\227\264\350\256\276\347\275\256\346\210\220\345\212\237", 0, QApplication::UnicodeUTF8);
         QMessageBox::warning(this, m_strErrinfo,strError);//系统时间设置失败提示,add by 2020.08.15
    }

#else
     QDateTime dt = m_pUi->dateTimeEdit->dateTime(); //获取日历控件上用户新设置的日期和时间
     time_t  ttNewTime;
     ttNewTime = (time_t)dt.toTime_t();
     //同步用户设置的时间到系统
     int ret = stime(&ttNewTime);
     if(ret==0)
     {
        QString strError1=QApplication::translate("syssetDialog", "\347\263\273\347\273\237\346\227\266\351\227\264\350\256\276\347\275\256\345\244\261\350\264\245", 0, QApplication::UnicodeUTF8);
         QMessageBox::warning(this, m_strErrinfo,strError1);//系统时间设置成功提示,add by 2020.08.15
     }
    else
    {
        QString strError=QApplication::translate("syssetDialog", "\347\263\273\347\273\237\346\227\266\351\227\264\350\256\276\347\275\256\346\210\220\345\212\237", 0, QApplication::UnicodeUTF8);
         QMessageBox::warning(this, m_strErrinfo,strError);//系统时间设置失败提示,add by 2020.08.15
    }
#endif
     m_isTimeEditFlag=false;

}
//恢复出厂设置槽函数实现 add by 2020.11.18
void  CSyssetdlg::restorefactoryBtn_clicked()
{
     int ret=-1;
     QString strYes;
     QString strNo;
     int nValue=0;
     QMessageBox *msgBox=new QMessageBox(QMessageBox::Question,m_strInfo, m_restorefactoryTips, QMessageBox::Yes | QMessageBox::No);
     if(g_iLangChange==1)
        {
            m_restorefactoryTips = QApplication::translate("syssetDialog", "\347\241\256\345\256\232\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256\345\220\227\357\274\237",  0, QApplication::UnicodeUTF8);//恢复出厂设置提示语
            m_strYes=QApplication::translate("mainWindow",  "\346\230\257", 0, QApplication::UnicodeUTF8);
            m_strNo=QApplication::translate("mainWindow", "\345\220\246", 0, QApplication::UnicodeUTF8);
        }
        else
        {
            m_restorefactoryTips="Sure to restore the factory settings?";//恢复出厂设置提示语
            m_strYes="Yes";
            m_strNo="No";
        }
     msgBox->setText(m_restorefactoryTips);
     msgBox->button(QMessageBox::Yes)->setText(m_strYes);
    // 将原本显示“No”的按钮改为显示“否”
     msgBox->button(QMessageBox::No)->setText(m_strNo);
    // 弹出对话框
     ret=msgBox->exec();
     if(ret==QMessageBox::Yes)
     {
         //校准系数恢复出厂设置 add by 2020.11.23
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
         m_IniAdjcoef.writeAdjcoefInifile(m_struAdjcoef);

         //基本参数恢复出厂设置 add by 2020.11.23
         m_struBasicpara.fSub1CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
         m_struBasicpara.fSub2CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
         m_struBasicpara.fSub3CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
         m_struBasicpara.fSub4CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
    //   m_struBasicpara.fThreevoltLow=THREE_VOLT_DOWN;
    //	 m_struBasicpara.fThreevoltUp=THREE_VOLT_UP;
         m_struBasicpara.fTotalcurrentUp=TOTAL_CURRENT_UP_LIMIT;
         m_struBasicpara.fTotalvoltUp=TOTAL_VOLT_UP_LIMIT;
    //	 m_struBasicpara.fVoltimbalance=Threephase_VOLT_UNBALANCE;
         m_struBasicpara.iSub1CabOpen=SUBCABOPEN_FLAG;
         m_struBasicpara.iSub2CabOpen=SUBCABOPEN_FLAG;
         m_struBasicpara.iSub3CabOpen=SUBCABOPEN_FLAG;
         m_struBasicpara.iSub4CabOpen=SUBCABOPEN_FLAG;
         m_IniBasicParse.writeBasicParaInifile(m_struBasicpara);

          //联锁保护恢复出厂设置 add by 2020.11.24
         m_ChainSetData.iJjtjVal=SWITCH_OFF;  //紧急停机
         m_ChainSetData.iHtgwyVal=SWITCH_OFF; //滑台过位移
         m_ChainSetData.iZdtgwyVal=SWITCH_OFF;//振动台过位移
         m_ChainSetData.iHtdywVal=SWITCH_OFF; //滑台低液位
         m_ChainSetData.iHtqyVal=SWITCH_OFF;//滑台欠压
         m_ChainSetData.iZdtgwVal=SWITCH_OFF; //振动台过温
         m_ChainSetData.iEzgwyVal=SWITCH_OFF; //耳轴过位移
         m_ChainSetData.iGfrjbhVal=SWITCH_OFF;//功放热继保护
         m_ChainSetData.iJyzcdyVal=SWITCH_OFF;//静压轴承低压
         m_ChainSetData.iZgMenbVal=SWITCH_OFF;  //主柜门保护
         m_ChainSetData.iXtlqdyVal=SWITCH_OFF;//系统冷却单元
         m_ChainSetData.iHtqywVal=SWITCH_OFF;//主柜整流桥过温
         m_ChainSetData.iSubMenbVal=SWITCH_OFF;//从柜门保护
         m_ChainSetData.iSubzlqgwVal=SWITCH_OFF;//从柜整流桥过温
         m_ChainSetData.iSelfdefineVal1=SWITCH_OFF;//自定义1,
         m_ChainSetData.iSelfdefineVal2=SWITCH_OFF;//自定义2
         m_ChainSetData.iSelfdefineVal3=SWITCH_OFF;//自定义3
         m_ChainSetData.iSubyuliuPorcVal=SWITCH_OFF;//从柜预留保护
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
         m_IniChainset. writeChainsetInifile(m_ChainSetData);
     }
     else if(ret==QMessageBox::No)
     {
//		this->close();
        return;
     }
}
//恢复出厂设置语言切换槽函数实现 add by 2020.11.23
void CSyssetdlg::syssetLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("syssetDialog", "\347\263\273\347\273\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        QApplication::translate("syssetDialog", "\346\217\220\347\244\272", 0, QApplication::UnicodeUTF8);//提示
        m_restorefactoryTips = QApplication::translate("syssetDialog", "\347\241\256\345\256\232\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256\345\220\227\357\274\237",  0, QApplication::UnicodeUTF8);//恢复出厂设置提示语
        m_strYes=QApplication::translate("mainWindow",  "\346\230\257", 0, QApplication::UnicodeUTF8);
        m_strNo=QApplication::translate("mainWindow", "\345\220\246", 0, QApplication::UnicodeUTF8);
    }
    else
    {
        setWindowTitle("System");
        m_strErrinfo = "Error";//错误提示
        m_strInfo="Prompting";//提示
        m_restorefactoryTips="Sure to restore the factory settings?";//恢复出厂设置提示语
        m_strYes="Yes";
        m_strNo="No";
    }
}
