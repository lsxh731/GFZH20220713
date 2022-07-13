/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: invalidsetdlg.cpp
** 摘要: 失效设置对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.02.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.02.01   V1.0      创建
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
    m_pUi->activeTimeEdit->setEnabled(false);//禁用激活日期，add by 2020.11.17
    memset(&m_struTotaltime,0,sizeof(m_struTotaltime));
    if(!(m_Inifileparse.readInifile(m_struTotaltime)))
    {
        //读取invalidset.ini配置文件失败
        qDebug("####【CInvalidSetdlg::CInvalidSetdlg()】Fail to open  invalidset file####\n");
    }
    else
    {
        //读取invalidset.ini配置文件成功
        qDebug("####【CInvalidSetdlg::CInvalidSetdlg()】Success to open  invalidset file####\n");
        //m_struTotaltime=m_Inifileparse.getTotaltimePara();
    }
    //信号与槽
    connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    connect(m_pUi->cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_clicked()));

    connect(m_pUi->lineEdit,SIGNAL(clicked()),this,SLOT(lineEdit_clicked()));
    connect(m_pUi->calendarDay,SIGNAL(clicked()),this,SLOT(calendarDay_clicked()));//获取自然天数槽函数 add by 2020.11.18
    m_pUi->lineEdit->setText(tr("0"));
    m_pUi->lineEdit->setMaxLength(10);
    m_pUi->calendarDay->setText(tr("0"));     //add by 2020.11.18
    m_pUi->calendarDay->setMaxLength(10);//add by 2020.11.18
    m_pUi->activeTimeEdit->setText(m_Inifileparse.strActiveDate);  //add by 2020.11.18

    m_strErrinfo = QApplication::translate("invalidSetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示

    m_strInvalidinfo = QApplication::translate("invalidSetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入
}
CInvalidSetdlg::~CInvalidSetdlg()
{
}
//"确定"-槽函数
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
    dValue=m_pUi->lineEdit->text().toLongLong(&ok,10)*3600;//设定的限值
    strSetVal=QString::number((qlonglong)dValue,10);
    //strActiveFlag=QString::number(m_struTotaltime.IsActived,10);
    bool nWritefile=m_Inifileparse.writeInifile(m_struTotaltime);
    this->close();
}
//"取消"-槽函数
void CInvalidSetdlg::cancelBtn_clicked()
{
    this->close();
}
//"激活"-槽函数
//void CInvalidSetdlg::radioButtonYes_clicked()
//{
//	if(!m_struTotaltime.IsActived)
//	{
//		m_pUi->radioButtonYes->setChecked(true);
//		m_struTotaltime.IsActived =true;
//	}
//}
//"不激活"-槽函数
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
//获取自然天数槽函数实现 add by 2020.11.18
void CInvalidSetdlg::calendarDay_clicked()
{
    openDigKeyBoardDlg(m_pUi->calendarDay);
}

//打开数字键盘对话框
void CInvalidSetdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    double dValue=0.0;
    bool ok=false;

    m_KeyBoardDlg.exec();//打开键盘对话框
    m_KeyBoardDlg.disablePointAndNagBtn();//禁止点号与负号按钮
    m_KeyBoardDlg.clearBtn_clicked();//清除旧的输入痕迹
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
                    tr(m_strInvalidinfo));//输入的数值不合法
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
         QApplication::UnicodeUTF8);//错误提示

    m_strInvalidinfo = QApplication::translate("invalidSetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入
    }
    else
    {
        setWindowTitle("Expiration");
        m_pUi->okBtn->setText("Ok");
        m_pUi->cancelBtn->setText("Cancel");
        m_pUi->label->setText("Upper limit of running time(h)");
        m_strErrinfo = "Error prompt ";//错误提示

        m_strInvalidinfo = "The value entered is not valid. Please retype it";//输入的数值不合法，请重新输入
    }
}
