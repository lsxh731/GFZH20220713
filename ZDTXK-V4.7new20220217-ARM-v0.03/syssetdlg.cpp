/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: syssetdlg.cpp
** ժҪ: У׼ϵ���Ի���
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2018.12.01
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2018.12.01   V1.0      ����
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
    connect(m_pUi->okBtn, SIGNAL(clicked()), this, SLOT(okBtn_clicked()));//ȷ���ۺ��� add by 2020.08.15
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateSystimeEdit()));
    connect(m_pUi->restorefactoryBtn, SIGNAL(clicked()), this, SLOT(restorefactoryBtn_clicked()));//�ָ��������òۺ��� add by 2020.11.18
    m_timer->start(1000);
}
CSyssetdlg::~CSyssetdlg()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
    }
}
//ϵͳʱ������ʵ�� add by 2020.08.15
void  CSyssetdlg::sysTimesetBtn_clicked()
{
    if(m_pUi->radioButton->isChecked())
    {
        m_isTimeEditFlag=true;	 //�༭̬
    }
    else
    {
        m_isTimeEditFlag=false; //�Ǳ༭̬
    }
}
void CSyssetdlg::updateSystimeEdit()
{
    if(!m_isTimeEditFlag)
    {
        //�Ǳ༭̬
      QDateTime current_date_time =QDateTime::currentDateTime();
      QString current_date =current_date_time.toString("yyyy.MM.dd \n hh:mm:ss");
      m_pUi->dateTimeEdit->setDateTime(current_date_time);
    }

}

//ȷ�����ۺ���ʵ�� add by 2020.08.15
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
         QMessageBox::warning(this, m_strErrinfo,strError1);//ϵͳʱ�����óɹ���ʾ,add by 2020.08.15
    }
    else
    {
        QString strError=QApplication::translate("syssetDialog", "\347\263\273\347\273\237\346\227\266\351\227\264\350\256\276\347\275\256\346\210\220\345\212\237", 0, QApplication::UnicodeUTF8);
         QMessageBox::warning(this, m_strErrinfo,strError);//ϵͳʱ������ʧ����ʾ,add by 2020.08.15
    }

#else
     QDateTime dt = m_pUi->dateTimeEdit->dateTime(); //��ȡ�����ؼ����û������õ����ں�ʱ��
     time_t  ttNewTime;
     ttNewTime = (time_t)dt.toTime_t();
     //ͬ���û����õ�ʱ�䵽ϵͳ
     int ret = stime(&ttNewTime);
     if(ret==0)
     {
        QString strError1=QApplication::translate("syssetDialog", "\347\263\273\347\273\237\346\227\266\351\227\264\350\256\276\347\275\256\345\244\261\350\264\245", 0, QApplication::UnicodeUTF8);
         QMessageBox::warning(this, m_strErrinfo,strError1);//ϵͳʱ�����óɹ���ʾ,add by 2020.08.15
     }
    else
    {
        QString strError=QApplication::translate("syssetDialog", "\347\263\273\347\273\237\346\227\266\351\227\264\350\256\276\347\275\256\346\210\220\345\212\237", 0, QApplication::UnicodeUTF8);
         QMessageBox::warning(this, m_strErrinfo,strError);//ϵͳʱ������ʧ����ʾ,add by 2020.08.15
    }
#endif
     m_isTimeEditFlag=false;

}
//�ָ��������òۺ���ʵ�� add by 2020.11.18
void  CSyssetdlg::restorefactoryBtn_clicked()
{
     int ret=-1;
     QString strYes;
     QString strNo;
     int nValue=0;
     QMessageBox *msgBox=new QMessageBox(QMessageBox::Question,m_strInfo, m_restorefactoryTips, QMessageBox::Yes | QMessageBox::No);
     if(g_iLangChange==1)
        {
            m_restorefactoryTips = QApplication::translate("syssetDialog", "\347\241\256\345\256\232\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256\345\220\227\357\274\237",  0, QApplication::UnicodeUTF8);//�ָ�����������ʾ��
            m_strYes=QApplication::translate("mainWindow",  "\346\230\257", 0, QApplication::UnicodeUTF8);
            m_strNo=QApplication::translate("mainWindow", "\345\220\246", 0, QApplication::UnicodeUTF8);
        }
        else
        {
            m_restorefactoryTips="Sure to restore the factory settings?";//�ָ�����������ʾ��
            m_strYes="Yes";
            m_strNo="No";
        }
     msgBox->setText(m_restorefactoryTips);
     msgBox->button(QMessageBox::Yes)->setText(m_strYes);
    // ��ԭ����ʾ��No���İ�ť��Ϊ��ʾ����
     msgBox->button(QMessageBox::No)->setText(m_strNo);
    // �����Ի���
     ret=msgBox->exec();
     if(ret==QMessageBox::Yes)
     {
         //У׼ϵ���ָ��������� add by 2020.11.23
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

         //���������ָ��������� add by 2020.11.23
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

          //���������ָ��������� add by 2020.11.24
         m_ChainSetData.iJjtjVal=SWITCH_OFF;  //����ͣ��
         m_ChainSetData.iHtgwyVal=SWITCH_OFF; //��̨��λ��
         m_ChainSetData.iZdtgwyVal=SWITCH_OFF;//��̨��λ��
         m_ChainSetData.iHtdywVal=SWITCH_OFF; //��̨��Һλ
         m_ChainSetData.iHtqyVal=SWITCH_OFF;//��̨Ƿѹ
         m_ChainSetData.iZdtgwVal=SWITCH_OFF; //��̨����
         m_ChainSetData.iEzgwyVal=SWITCH_OFF; //�����λ��
         m_ChainSetData.iGfrjbhVal=SWITCH_OFF;//�����ȼ̱���
         m_ChainSetData.iJyzcdyVal=SWITCH_OFF;//��ѹ��е�ѹ
         m_ChainSetData.iZgMenbVal=SWITCH_OFF;  //�����ű���
         m_ChainSetData.iXtlqdyVal=SWITCH_OFF;//ϵͳ��ȴ��Ԫ
         m_ChainSetData.iHtqywVal=SWITCH_OFF;//���������Ź���
         m_ChainSetData.iSubMenbVal=SWITCH_OFF;//�ӹ��ű���
         m_ChainSetData.iSubzlqgwVal=SWITCH_OFF;//�ӹ������Ź���
         m_ChainSetData.iSelfdefineVal1=SWITCH_OFF;//�Զ���1,
         m_ChainSetData.iSelfdefineVal2=SWITCH_OFF;//�Զ���2
         m_ChainSetData.iSelfdefineVal3=SWITCH_OFF;//�Զ���3
         m_ChainSetData.iSubyuliuPorcVal=SWITCH_OFF;//�ӹ�Ԥ������
         m_ChainSetData.iSwitch_Jjtj=NORMAL_OPEN;//����ͣ��
         m_ChainSetData.iSwitch_htgwy=NORMAL_OPEN;//��̨��λ��
         m_ChainSetData.iSwitch_zdtgwy=NORMAL_OPEN;//��̨��λ��
         m_ChainSetData.iSwitch_htdyw=NORMAL_OPEN;//��̨��Һλ
         m_ChainSetData.iSwitch_htqy=NORMAL_OPEN;//��̨��е�ѹ
         m_ChainSetData.iSwitch_zdtgw=NORMAL_OPEN;//��̨����
         m_ChainSetData.iSwitch_ezgwy=NORMAL_OPEN;//�����λ��
         m_ChainSetData.iSwitch_gfrjbh=NORMAL_OPEN;//�����ȼ̱���
         m_ChainSetData.iSwitch_jyzcdy=NORMAL_OPEN;//��ѹ��е�ѹ
         m_ChainSetData.iSwitch_zgmenbh=NORMAL_OPEN;//������
         m_ChainSetData.iSwitch_htgw=NORMAL_OPEN;//�ӹ���
         m_ChainSetData.iSwitch_xtlqdy=NORMAL_OPEN;//ϵͳ��ȴ��Ԫ
         m_ChainSetData.iSwitch_htqyw=NORMAL_OPEN;//��������������
         m_ChainSetData.iSwitch_subzlqgw=NORMAL_OPEN;//�ӹ�����������
         m_ChainSetData.iSwitch_selfdefine1=NORMAL_OPEN;//�Զ���1
         m_ChainSetData.iSwitch_selfdefine2=NORMAL_OPEN;//�Զ���2
         m_ChainSetData.iSwitch_selfdefine3=NORMAL_OPEN;//�Զ���3
         m_ChainSetData.iSwitch_subyuliu=NORMAL_OPEN;//�ӹ�Ԥ��
         m_IniChainset. writeChainsetInifile(m_ChainSetData);
     }
     else if(ret==QMessageBox::No)
     {
//		this->close();
        return;
     }
}
//�ָ��������������л��ۺ���ʵ�� add by 2020.11.23
void CSyssetdlg::syssetLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("syssetDialog", "\347\263\273\347\273\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        QApplication::translate("syssetDialog", "\346\217\220\347\244\272", 0, QApplication::UnicodeUTF8);//��ʾ
        m_restorefactoryTips = QApplication::translate("syssetDialog", "\347\241\256\345\256\232\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256\345\220\227\357\274\237",  0, QApplication::UnicodeUTF8);//�ָ�����������ʾ��
        m_strYes=QApplication::translate("mainWindow",  "\346\230\257", 0, QApplication::UnicodeUTF8);
        m_strNo=QApplication::translate("mainWindow", "\345\220\246", 0, QApplication::UnicodeUTF8);
    }
    else
    {
        setWindowTitle("System");
        m_strErrinfo = "Error";//������ʾ
        m_strInfo="Prompting";//��ʾ
        m_restorefactoryTips="Sure to restore the factory settings?";//�ָ�����������ʾ��
        m_strYes="Yes";
        m_strNo="No";
    }
}
