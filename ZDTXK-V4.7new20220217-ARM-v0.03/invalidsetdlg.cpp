/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: invalidsetdlg.cpp
** ժҪ: ʧЧ���öԻ���
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2019.02.01
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2019.02.01   V1.0      ����
**
****************************************************************************/
#include "invalidsetdlg.h"
#include "inifileparse.h"
#include "qmath.h"
#include "qmessagebox.h"
#include "commmacro.h"
#include <stdio.h>
extern int g_iLangChange;//add by 2019.10.3
CInvalidSetdlg::CInvalidSetdlg()
{
    m_pUi= new Ui::invalidSetDialog;
    m_pUi->setupUi(this);
    m_pUi->activeTimeEdit->setEnabled(false);//���ü������ڣ�add by 2020.11.17
    memset(&m_struTotaltime,0,sizeof(m_struTotaltime));
    if(!(m_Inifileparse.readInifile(m_struTotaltime)))
    {
        //��ȡinvalidset.ini�����ļ�ʧ��
        qDebug("####��CInvalidSetdlg::CInvalidSetdlg()��Fail to open  invalidset file####\n");
    }
    else
    {
        //��ȡinvalidset.ini�����ļ��ɹ�
        qDebug("####��CInvalidSetdlg::CInvalidSetdlg()��Success to open  invalidset file####\n");
        //m_struTotaltime=m_Inifileparse.getTotaltimePara();
    }
    //�ź����
    connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    connect(m_pUi->cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_clicked()));

    connect(m_pUi->lineEdit,SIGNAL(clicked()),this,SLOT(lineEdit_clicked()));
    connect(m_pUi->calendarDay,SIGNAL(clicked()),this,SLOT(calendarDay_clicked()));//��ȡ��Ȼ�����ۺ��� add by 2020.11.18
    m_pUi->lineEdit->setText(tr("0"));
    m_pUi->lineEdit->setMaxLength(10);
    m_pUi->calendarDay->setText(tr("0"));     //add by 2020.11.18
    m_pUi->calendarDay->setMaxLength(10);//add by 2020.11.18
    m_pUi->activeTimeEdit->setText(m_Inifileparse.strActiveDate);  //add by 2020.11.18

    m_strErrinfo = QApplication::translate("invalidSetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//������ʾ

    m_strInvalidinfo = QApplication::translate("invalidSetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//�������ֵ���Ϸ�������������
}
CInvalidSetdlg::~CInvalidSetdlg()
{
}
//"ȷ��"-�ۺ���
void CInvalidSetdlg::okBtn_clicked()
{
    bool ok =false;
    double dValue=0.0;

    m_struTotaltime.lSetValue=m_pUi->lineEdit->text().toLongLong(&ok,10)*3600;
    m_struTotaltime.lSetCalendarDay=m_pUi->calendarDay->text().toInt(&ok,10);//add by 2020.11.18
    if(m_struTotaltime.lSetValue>MAX_RUNNING_TIME)
    {
        m_pUi->lineEdit->setText(QString::number((qlonglong)MAX_RUNNING_TIME/3600,10));
        QMessageBox::warning(this,
            tr(m_strErrinfo),
            tr("exceeding the upper limit %1\n").arg((qlonglong)MAX_RUNNING_TIME));
    }
    QString strSetVal;
    //strCurrVal=tr("2000");
    dValue=m_pUi->lineEdit->text().toLongLong(&ok,10)*3600;//�趨����ֵ
    strSetVal=QString::number((qlonglong)dValue,10);
    //strActiveFlag=QString::number(m_struTotaltime.IsActived,10);
    bool nWritefile=m_Inifileparse.writeInifile(m_struTotaltime);
    this->close();
}
//"ȡ��"-�ۺ���
void CInvalidSetdlg::cancelBtn_clicked()
{
    this->close();
}
//"����"-�ۺ���
//void CInvalidSetdlg::radioButtonYes_clicked()
//{
//	if(!m_struTotaltime.IsActived)
//	{
//		m_pUi->radioButtonYes->setChecked(true);
//		m_struTotaltime.IsActived =true;
//	}
//}
//"������"-�ۺ���
//void CInvalidSetdlg::radioButtonNo_clicked()
//{
//	if(m_struTotaltime.IsActived)
//	{
//		m_pUi->radioButtonNo->setChecked(true);
//		m_struTotaltime.IsActived =false;
//	}
//}
void CInvalidSetdlg::lineEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit);
    //bool ok=false;
}
//��ȡ��Ȼ�����ۺ���ʵ�� add by 2020.11.18
void CInvalidSetdlg::calendarDay_clicked()
{
    openDigKeyBoardDlg(m_pUi->calendarDay);
}

//�����ּ��̶Ի���
void CInvalidSetdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    double dValue=0.0;
    bool ok=false;

    m_KeyBoardDlg.exec();//�򿪼��̶Ի���
    m_KeyBoardDlg.disablePointAndNagBtn();//��ֹ����븺�Ű�ť
    m_KeyBoardDlg.clearBtn_clicked();//����ɵ�����ۼ�
    ok=m_KeyBoardDlg.getInputValue(fValue);
    if(ok)
    {
        dValue=fValue*3600;
        if(dValue>MAX_RUNNING_TIME)
        {
            m_pUi->lineEdit->setText(QString::number((qlonglong)MAX_RUNNING_TIME/3600,10));
            QMessageBox::warning(this,
                tr(m_strErrinfo),
                tr("exceeding the upper limit %1\n").arg((qlonglong)MAX_RUNNING_TIME));
        }
        else
        {
            lineEdit->setText(QString::number((qlonglong)fValue,10));
        }
    }
    else
    {
        QMessageBox::warning(this,
                    tr(m_strErrinfo),
                    tr(m_strInvalidinfo));//�������ֵ���Ϸ�
    }
}
void CInvalidSetdlg::invalidsetLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("invalidSetDialog", "\345\244\261\346\225\210\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->okBtn->setText(QApplication::translate("invalidSetDialog", "\347\241\256  \345\256\232", 0, QApplication::UnicodeUTF8));
        m_pUi->cancelBtn->setText(QApplication::translate("invalidSetDialog", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        m_pUi->label->setText(QApplication::translate("invalidSetDialog", "\347\264\257\350\256\241\350\277\220\350\241\214\346\227\266\351\227\264\344\270\212\351\231\220(\345\260\217\346\227\266)", 0, QApplication::UnicodeUTF8));
        m_strErrinfo = QApplication::translate("invalidSetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//������ʾ

    m_strInvalidinfo = QApplication::translate("invalidSetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//�������ֵ���Ϸ�������������
    }
    else
    {
        setWindowTitle("Expiration");
        m_pUi->okBtn->setText("Ok");
        m_pUi->cancelBtn->setText("Cancel");
        m_pUi->label->setText("Upper limit of running time(h)");
        m_strErrinfo = "Error prompt ";//������ʾ

        m_strInvalidinfo = "The value entered is not valid. Please retype it";//�������ֵ���Ϸ�������������
    }
}
