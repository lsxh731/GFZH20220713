/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: dcsetdlg.cpp
** 摘要: 直流调节对话框
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
** 聂晓波      2019.02.10   V1.1      修改
****************************************************************************/
#include "dcsetdlg.h"
#include "commmacro.h"
#include <QComboBox>
#include <QMessageBox>

CDCSetdlg::CDCSetdlg()
{
    m_pUi= new Ui::dcsetDialog;
    m_pUi->setupUi(this);

    m_strErrinfo = QApplication::translate("dcsetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示

    m_strInvalidinfo = QApplication::translate("dcsetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入

    m_strFriendlytips=QApplication::translate("dcsetDialog",
        "\345\217\213\346\203\205\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//友情提示

    m_strListSuccess.clear();
    m_strListFailure.clear();
    for(int i=0;i<16;i++)
    {
     m_strListSuccess.append(QApplication::translate("dcsetDialog",
         tr("\345\212\237\346\224\276%1\347\233\264\346\265\201\350\260\203\350\212\202\346\210\220\345\212\237").arg(i+1),
         0,
         QApplication::UnicodeUTF8));

     m_strListFailure.append(QApplication::translate("dcsetDialog",
         tr("\345\212\237\346\224\276%1\347\233\264\346\265\201\350\260\203\350\212\202\345\244\261\350\264\245").arg(i+1),
             0,
             QApplication::UnicodeUTF8));
    }//for(int i=0;i<16;i++)
    m_nAdjtype = SOLE_ADJ_TYPE;
    m_pUi->lineEdit->setEnabled(false);
    m_pUi->setBtn->setEnabled(false);
    m_pUi->adjBtn->setEnabled(false);
    m_pUi->checkBox->setCheckState(Qt::Unchecked);
    m_isChkDigKeyBoard=false;

    //信号与槽
    connect(m_pUi->adjBtn01,SIGNAL(clicked()),this,SLOT(adjBtn01_clicked()));
    connect(m_pUi->adjBtn02,SIGNAL(clicked()),this,SLOT(adjBtn02_clicked()));
    connect(m_pUi->adjBtn03,SIGNAL(clicked()),this,SLOT(adjBtn03_clicked()));
    connect(m_pUi->adjBtn04,SIGNAL(clicked()),this,SLOT(adjBtn04_clicked()));
    connect(m_pUi->adjBtn05,SIGNAL(clicked()),this,SLOT(adjBtn05_clicked()));
    connect(m_pUi->adjBtn06,SIGNAL(clicked()),this,SLOT(adjBtn06_clicked()));
    connect(m_pUi->adjBtn07,SIGNAL(clicked()),this,SLOT(adjBtn07_clicked()));
    connect(m_pUi->adjBtn08,SIGNAL(clicked()),this,SLOT(adjBtn08_clicked()));
    connect(m_pUi->adjBtn09,SIGNAL(clicked()),this,SLOT(adjBtn09_clicked()));
    connect(m_pUi->adjBtn10,SIGNAL(clicked()),this,SLOT(adjBtn10_clicked()));
    connect(m_pUi->adjBtn11,SIGNAL(clicked()),this,SLOT(adjBtn11_clicked()));
    connect(m_pUi->adjBtn12,SIGNAL(clicked()),this,SLOT(adjBtn12_clicked()));
    connect(m_pUi->adjBtn13,SIGNAL(clicked()),this,SLOT(adjBtn13_clicked()));
    connect(m_pUi->adjBtn14,SIGNAL(clicked()),this,SLOT(adjBtn14_clicked()));
    connect(m_pUi->adjBtn15,SIGNAL(clicked()),this,SLOT(adjBtn15_clicked()));
    connect(m_pUi->adjBtn16,SIGNAL(clicked()),this,SLOT(adjBtn16_clicked()));

    connect(m_pUi->comboBox,SIGNAL(activated(int)),this,SLOT(comboBox_clicked(int)));
    connect(m_pUi->setBtn,SIGNAL(clicked()),this,SLOT(setBtn_clicked()));
    connect(m_pUi->adjBtn,SIGNAL(clicked()),this,SLOT(adjBtn_clicked()));
    connect(m_pUi->checkBox,SIGNAL(clicked()),this,SLOT(checkBox_clicked()));//是否选择数字键槽函数

}
CDCSetdlg::~CDCSetdlg()
{

}
//是否勾选数字键槽函数
void CDCSetdlg::checkBox_clicked()
{
    if(!m_isChkDigKeyBoard)
    {
        //未勾选时
        m_pUi->checkBox->setCheckState(Qt::Checked);
        m_isChkDigKeyBoard=true;
        //建立信号与槽关系
        connect(m_pUi->lineEdit,SIGNAL(clicked()),this,SLOT(lineEdit_clicked()));
        connect(m_pUi->lineEdit_01,SIGNAL(clicked()),this,SLOT(lineEdit01_clicked()));
        connect(m_pUi->lineEdit_02,SIGNAL(clicked()),this,SLOT(lineEdit02_clicked()));
        connect(m_pUi->lineEdit_03,SIGNAL(clicked()),this,SLOT(lineEdit03_clicked()));
        connect(m_pUi->lineEdit_04,SIGNAL(clicked()),this,SLOT(lineEdit04_clicked()));
        connect(m_pUi->lineEdit_05,SIGNAL(clicked()),this,SLOT(lineEdit05_clicked()));
        connect(m_pUi->lineEdit_06,SIGNAL(clicked()),this,SLOT(lineEdit06_clicked()));
        connect(m_pUi->lineEdit_07,SIGNAL(clicked()),this,SLOT(lineEdit07_clicked()));
        connect(m_pUi->lineEdit_08,SIGNAL(clicked()),this,SLOT(lineEdit08_clicked()));
        connect(m_pUi->lineEdit_09,SIGNAL(clicked()),this,SLOT(lineEdit09_clicked()));
        connect(m_pUi->lineEdit_10,SIGNAL(clicked()),this,SLOT(lineEdit10_clicked()));
        connect(m_pUi->lineEdit_11,SIGNAL(clicked()),this,SLOT(lineEdit11_clicked()));
        connect(m_pUi->lineEdit_12,SIGNAL(clicked()),this,SLOT(lineEdit12_clicked()));
        connect(m_pUi->lineEdit_13,SIGNAL(clicked()),this,SLOT(lineEdit13_clicked()));
        connect(m_pUi->lineEdit_14,SIGNAL(clicked()),this,SLOT(lineEdit14_clicked()));
        connect(m_pUi->lineEdit_15,SIGNAL(clicked()),this,SLOT(lineEdit15_clicked()));
        connect(m_pUi->lineEdit_16,SIGNAL(clicked()),this,SLOT(lineEdit16_clicked()));
    }
    else
    {
        //已勾选时
        m_pUi->checkBox->setCheckState(Qt::Unchecked);
        m_isChkDigKeyBoard=false;
        //断开信号与槽关系
        disconnect(m_pUi->lineEdit,0,0,0);
        disconnect(m_pUi->lineEdit_01,0,0,0);
        disconnect(m_pUi->lineEdit_02,0,0,0);
        disconnect(m_pUi->lineEdit_03,0,0,0);
        disconnect(m_pUi->lineEdit_04,0,0,0);
        disconnect(m_pUi->lineEdit_05,0,0,0);
        disconnect(m_pUi->lineEdit_06,0,0,0);
        disconnect(m_pUi->lineEdit_07,0,0,0);
        disconnect(m_pUi->lineEdit_08,0,0,0);
        disconnect(m_pUi->lineEdit_09,0,0,0);
        disconnect(m_pUi->lineEdit_10,0,0,0);
        disconnect(m_pUi->lineEdit_11,0,0,0);
        disconnect(m_pUi->lineEdit_12,0,0,0);
        disconnect(m_pUi->lineEdit_13,0,0,0);
        disconnect(m_pUi->lineEdit_14,0,0,0);
        disconnect(m_pUi->lineEdit_15,0,0,0);
        disconnect(m_pUi->lineEdit_16,0,0,0);
    }
}
//功放01直流调节槽函数
void CDCSetdlg::adjBtn01_clicked()
{
 EffectiveJudge(m_pUi->lineEdit_01->text());
  QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(0)));
}
//功放02直流调节槽函数
void CDCSetdlg::adjBtn02_clicked()
{
 EffectiveJudge(m_pUi->lineEdit_02->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(1)));
}
//功放03直流调节槽函数
void CDCSetdlg::adjBtn03_clicked()
{
  EffectiveJudge(m_pUi->lineEdit_03->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(2)));
}
//功放04直流调节槽函数
void CDCSetdlg::adjBtn04_clicked()
{
     EffectiveJudge(m_pUi->lineEdit_04->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(3)));
}
//功放05直流调节槽函数
void CDCSetdlg::adjBtn05_clicked()
{
     EffectiveJudge(m_pUi->lineEdit_05->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(4)));
}
//功放06直流调节槽函数
void CDCSetdlg::adjBtn06_clicked()
{
     EffectiveJudge(m_pUi->lineEdit_06->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(5)));
}
//功放07直流调节槽函数
void CDCSetdlg::adjBtn07_clicked()
{
     EffectiveJudge(m_pUi->lineEdit_07->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(6)));
}
//功放08直流调节槽函数
void CDCSetdlg::adjBtn08_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_08->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(7)));
}
//功放09直流调节槽函数
void CDCSetdlg::adjBtn09_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_09->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(8)));
}
//功放10直流调节槽函数
void CDCSetdlg::adjBtn10_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_10->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(9)));
}
//功放11直流调节槽函数
void CDCSetdlg::adjBtn11_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_11->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(10)));
}
//功放12直流调节槽函数
void CDCSetdlg::adjBtn12_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_12->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(11)));
}
//功放13直流调节槽函数
void CDCSetdlg::adjBtn13_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_13->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(12)));
}
//功放14直流调节槽函数
void CDCSetdlg::adjBtn14_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_14->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(13)));
}
//功放15直流调节槽函数
void CDCSetdlg::adjBtn15_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_15->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(14)));
}
//功放16直流调节槽函数
void CDCSetdlg::adjBtn16_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_16->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(15)));
}
void CDCSetdlg::comboBox_clicked(int index)
{
    switch(index)
    {
    case 0:
        m_nAdjtype = SOLE_ADJ_TYPE;//单一调节模式（类型）
        m_pUi->lineEdit->setEnabled(false);
        m_pUi->setBtn->setEnabled(false);
        m_pUi->adjBtn->setEnabled(false);
        break;
    case 1:
        m_nAdjtype = UNIFY_ADJ_TYPE;//统一调节模式（类型）
        m_pUi->lineEdit->setEnabled(true);
        m_pUi->setBtn->setEnabled(true);
        m_pUi->adjBtn->setEnabled(true);
        break;
    default:
        m_nAdjtype = SOLE_ADJ_TYPE;//单一调节模式（类型）
        m_pUi->lineEdit->setEnabled(false);
        m_pUi->setBtn->setEnabled(false);
        m_pUi->adjBtn->setEnabled(false);
        break;
    }

}
//"设置"槽函数
 void CDCSetdlg::setBtn_clicked()
{
    unifyset( m_pUi->lineEdit->text());

}
//"调节"槽函数
void CDCSetdlg::adjBtn_clicked()
{

}
//统一设置所有LineEdit
void CDCSetdlg::unifyset(QString text)
{
    bool ok =false;
    text.toFloat(&ok);
    if(ok)
    {
     m_pUi->lineEdit_01->setText(text);
     m_pUi->lineEdit_02->setText(text);
     m_pUi->lineEdit_03->setText(text);
     m_pUi->lineEdit_04->setText(text);
     m_pUi->lineEdit_05->setText(text);
     m_pUi->lineEdit_06->setText(text);
     m_pUi->lineEdit_07->setText(text);
     m_pUi->lineEdit_08->setText(text);
     m_pUi->lineEdit_09->setText(text);
     m_pUi->lineEdit_10->setText(text);
     m_pUi->lineEdit_11->setText(text);
     m_pUi->lineEdit_12->setText(text);
     m_pUi->lineEdit_13->setText(text);
     m_pUi->lineEdit_14->setText(text);
     m_pUi->lineEdit_15->setText(text);
     m_pUi->lineEdit_16->setText(text);
    }
    else
    {

        QMessageBox::warning(this,
            tr(m_strErrinfo),
            tr(m_strInvalidinfo));//输入的数值不合法

    }

}
//判断lineEdit输入的调节数值是否合法
void CDCSetdlg::lineEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit);
    EffectiveJudge(m_pUi->lineEdit->text());
}
//判断lineEdit01输入的调节数值是否合法
void CDCSetdlg::lineEdit01_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_01);
    EffectiveJudge(m_pUi->lineEdit_01->text());
}
//判断lineEdit02输入的调节数值是否合法
void CDCSetdlg::lineEdit02_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_02);
    EffectiveJudge(m_pUi->lineEdit_02->text());
}
//判断lineEdit03输入的调节数值是否合法
void CDCSetdlg::lineEdit03_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_03);
    EffectiveJudge(m_pUi->lineEdit_03->text());
}
//判断lineEdit04输入的调节数值是否合法
void CDCSetdlg::lineEdit04_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_04);
    EffectiveJudge(m_pUi->lineEdit_04->text());
}
//判断lineEdit05输入的调节数值是否合法
void CDCSetdlg::lineEdit05_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_05);
    EffectiveJudge(m_pUi->lineEdit_05->text());
}
//判断lineEdit06输入的调节数值是否合法
void CDCSetdlg::lineEdit06_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_06);
    EffectiveJudge(m_pUi->lineEdit_06->text());
}
//判断lineEdit07输入的调节数值是否合法
void CDCSetdlg::lineEdit07_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_07);
    EffectiveJudge(m_pUi->lineEdit_07->text());
}
//判断lineEdit08输入的调节数值是否合法
void CDCSetdlg::lineEdit08_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_08);
    EffectiveJudge(m_pUi->lineEdit_08->text());
}
//判断数值合法性函数
void CDCSetdlg::EffectiveJudge(QString text)
{
    bool ok =false;
    text.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,
            tr(m_strErrinfo),
            tr(m_strInvalidinfo));//输入的数值不合法
    }
}
//判断lineEdit09输入的调节数值是否合法
void CDCSetdlg::lineEdit09_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_09);
    EffectiveJudge(m_pUi->lineEdit_09->text());
}
//判断lineEdit10输入的调节数值是否合法
void CDCSetdlg::lineEdit10_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_10);
    EffectiveJudge(m_pUi->lineEdit_10->text());
}
//判断lineEdit11输入的调节数值是否合法
void CDCSetdlg::lineEdit11_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_11);
    EffectiveJudge(m_pUi->lineEdit_11->text());
}
//判断lineEdit12输入的调节数值是否合法
void CDCSetdlg::lineEdit12_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_12);
    EffectiveJudge(m_pUi->lineEdit_12->text());
}
//判断lineEdit13输入的调节数值是否合法
void CDCSetdlg::lineEdit13_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_13);
    EffectiveJudge(m_pUi->lineEdit_13->text());
}
//判断lineEdit14输入的调节数值是否合法
void CDCSetdlg::lineEdit14_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_14);
    EffectiveJudge(m_pUi->lineEdit_14->text());
}
//判断lineEdit15输入的调节数值是否合法
void CDCSetdlg::lineEdit15_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_15);
    EffectiveJudge(m_pUi->lineEdit_15->text());
}
//判断lineEdit16输入的调节数值是否合法
void CDCSetdlg::lineEdit16_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_16);
    EffectiveJudge(m_pUi->lineEdit_16->text());
}
//打开数字键盘对话框
void CDCSetdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    bool ok=false;
    if(m_isChkDigKeyBoard)
    {
        m_KeyBoardDlg.exec();//打开键盘对话框
        m_KeyBoardDlg.clearBtn_clicked();//清除旧的输入痕迹
        ok=m_KeyBoardDlg.getInputValue(fValue);
        if(ok)
        {
            lineEdit->setText(QString::number(fValue,'f',1));
        }
        else
        {
            QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//输入的数值不合法
        }
    }//if(m_isChkDigKeyBoard)
}
