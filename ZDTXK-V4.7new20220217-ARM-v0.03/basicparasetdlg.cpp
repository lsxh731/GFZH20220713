/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: basicparasetdlg.cpp
** 摘要: 基本参数对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.06.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.06.01   V1.0      创建
**
****************************************************************************/
#include "basicparasetdlg.h"
#include <QMessageBox>
extern STRU_BASICPARA g_struBasicPara;//add by 2019.06.16
extern int g_iLangChange;//add by 2019.10.3
CBasicParaSetdlg::CBasicParaSetdlg()
{
    m_pUi= new Ui::basicparasetDialog;
    m_pUi->setupUi(this);
    //初始化参数
    initPara();
    //初始化信号与槽关系
    initSignalAndSlot();
}
CBasicParaSetdlg::~CBasicParaSetdlg()
{

}
//初始化参数
void CBasicParaSetdlg::initPara()
{
    //m_pUi->lineEdit_ThreeVoltImbalance->setEnabled(false);
    if(!(m_IniBasicParse.readBasicParaInifile(m_struBasicpara)))
    {
    //	m_struBasicpara.fBusvoltLow=BUS_VOLT_DOWN_LIMIT;
    //	m_struBasicpara.fBusvoltUp=BUS_VOLT_UP_LIMIT;
        m_struBasicpara.fSub1CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
        m_struBasicpara.fSub2CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
        m_struBasicpara.fSub3CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
        m_struBasicpara.fSub4CabinetcurrentUp=OUTPUT_CURRENT_UP_LIMIT;
    //	m_struBasicpara.fThreevoltLow=THREE_VOLT_DOWN;
    //	m_struBasicpara.fThreevoltUp=THREE_VOLT_UP;
        m_struBasicpara.fTotalcurrentUp=TOTAL_CURRENT_UP_LIMIT;
        m_struBasicpara.fTotalvoltUp=TOTAL_VOLT_UP_LIMIT;
    //	m_struBasicpara.fVoltimbalance=Threephase_VOLT_UNBALANCE;
        m_struBasicpara.iSub1CabOpen=SUBCABOPEN_FLAG;
        m_struBasicpara.iSub2CabOpen=SUBCABOPEN_FLAG;
        m_struBasicpara.iSub3CabOpen=SUBCABOPEN_FLAG;
        m_struBasicpara.iSub4CabOpen=SUBCABOPEN_FLAG;
    }
    //界面基本参数值初始化
    //删去母线电压和三相电压设置 add by 2020.18.19
    /*
    m_pUi->lineEdit_BusVoltUp->setText(QString::number(m_struBasicpara.fBusvoltUp,'f',1));
    m_pUi->lineEdit_BusVoltDown->setText(QString::number(m_struBasicpara.fBusvoltLow,'f',1));
    m_pUi->lineEdit_ThreeVoltUp->setText(QString::number(m_struBasicpara.fThreevoltUp,'f',1));
    m_pUi->lineEdit_ThreeVoltDown->setText(QString::number(m_struBasicpara.fThreevoltLow,'f',1));
    m_pUi->lineEdit_ThreeVoltImbalance->setText(QString::number(m_struBasicpara.fVoltimbalance,'f',1));
    */
    m_pUi->lineEdit_SubCurrentUp->setText(QString::number(m_struBasicpara.fSub1CabinetcurrentUp,'f',1));
    m_pUi->lineEdit_SubCurrentUp_2->setText(QString::number(m_struBasicpara.fSub2CabinetcurrentUp,'f',1));
    m_pUi->lineEdit_SubCurrentUp_3->setText(QString::number(m_struBasicpara.fSub3CabinetcurrentUp,'f',1));
    m_pUi->lineEdit_SubCurrentUp_4->setText(QString::number(m_struBasicpara.fSub4CabinetcurrentUp,'f',1));
    m_pUi->lineEdit_GfTotalVoltUp->setText(QString::number(m_struBasicpara.fTotalvoltUp,'f',1));
    m_pUi->lineEdit_GfTotalCurrentUp->setText(QString::number(m_struBasicpara.fTotalcurrentUp,'f',1));
    if(m_struBasicpara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {
        m_pUi->checkBox_Sub1->setChecked(true);
    }
    else
    {
        m_pUi->checkBox_Sub1->setChecked(false);
    }
    if(m_struBasicpara.iSub2CabOpen==SUBCABOPEN_FLAG)
    {
        m_pUi->checkBox_Sub2->setChecked(true);
    }
    else
    {
        m_pUi->checkBox_Sub2->setChecked(false);
    }
    if(m_struBasicpara.iSub3CabOpen==SUBCABOPEN_FLAG)
    {
        m_pUi->checkBox_Sub3->setChecked(true);
    }
    else
    {
        m_pUi->checkBox_Sub3->setChecked(false);
    }
    if(m_struBasicpara.iSub4CabOpen==SUBCABOPEN_FLAG)
    {
        m_pUi->checkBox_Sub4->setChecked(true);
    }
    else
    {
        m_pUi->checkBox_Sub4->setChecked(false);
    }
    m_strErrinfo = QApplication::translate("basicparasetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示

    m_strInvalidinfo = QApplication::translate("basicparasetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入

    m_strSaveSuccess= QApplication::translate("basicparasetDialog", "\345\237\272\346\234\254\345\217\202\346\225\260\351\205\215\347\275\256\346\226\207\344\273\266\344\277\235\345\255\230\346\210\220\345\212\237",
        0,
        QApplication::UnicodeUTF8);//基本参数配置文件保存成功提示语

    m_strSaveFail= QApplication::translate("basicparasetDialog", "\345\237\272\346\234\254\345\217\202\346\225\260\351\205\215\347\275\256\346\226\207\344\273\266\344\277\235\345\255\230\345\244\261\350\264\245,\350\257\267\346\243\200\346\237\245",
        0,
        QApplication::UnicodeUTF8);//基本参数配置文件保存失败提示语

    m_strInfo=QApplication::translate("basicparasetDialog",
        "\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//提示
}
//初始化信号与槽关系
void CBasicParaSetdlg::initSignalAndSlot()
{
    connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    connect(m_pUi->cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_clicked()));
    //删去母线电压和三相电压设置 add by 2020.18.19
    /*
    connect(m_pUi->lineEdit_BusVoltUp,SIGNAL(clicked()),this,SLOT(BusVoltUplEdit_clicked()));
    connect(m_pUi->lineEdit_BusVoltDown,SIGNAL(clicked()),this,SLOT(BusVoltDownlEdit_clicked()));
    connect(m_pUi->lineEdit_ThreeVoltUp,SIGNAL(clicked()),this,SLOT(ThreeVoltUplEdit_clicked()));
    connect(m_pUi->lineEdit_ThreeVoltDown,SIGNAL(clicked()),this,SLOT(ThreeVoltDownlEdit_clicked()));
    connect(m_pUi->lineEdit_ThreeVoltImbalance,SIGNAL(clicked()),this,SLOT(ThreeVoltImbalancelEdit_clicked()));
    */
    connect(m_pUi->lineEdit_SubCurrentUp,SIGNAL(clicked()),this,SLOT(Sub1CurrentUplEdit_clicked()));
    connect(m_pUi->lineEdit_SubCurrentUp_2,SIGNAL(clicked()),this,SLOT(Sub2CurrentUplEdit_clicked()));
    connect(m_pUi->lineEdit_SubCurrentUp_3,SIGNAL(clicked()),this,SLOT(Sub3CurrentUplEdit_clicked()));
    connect(m_pUi->lineEdit_SubCurrentUp_4,SIGNAL(clicked()),this,SLOT(Sub4CurrentUplEdit_clicked()));
    connect(m_pUi->lineEdit_GfTotalVoltUp,SIGNAL(clicked()),this,SLOT(GfTotalVoltUplEdit_clicked()));
    connect(m_pUi->lineEdit_GfTotalCurrentUp,SIGNAL(clicked()),this,SLOT(GfTotalCurrentUplEdit_clicked()));

    connect(m_pUi->checkBox_Sub1,SIGNAL(clicked()),this,SLOT(checkBoxSub1_clicked()));
    connect(m_pUi->checkBox_Sub2,SIGNAL(clicked()),this,SLOT(checkBoxSub2_clicked()));
    connect(m_pUi->checkBox_Sub3,SIGNAL(clicked()),this,SLOT(checkBoxSub3_clicked()));
    connect(m_pUi->checkBox_Sub4,SIGNAL(clicked()),this,SLOT(checkBoxSub4_clicked()));
}
//确定-槽函数
void CBasicParaSetdlg::okBtn_clicked()
{
    bool ok =false;
    //删去母线电压和三相电压设置 add by 2020.08.19
    //m_struBasicpara.fBusvoltLow=m_pUi->lineEdit_BusVoltDown->text().toFloat(&ok);
    //m_struBasicpara.fBusvoltUp=m_pUi->lineEdit_BusVoltUp->text().toFloat(&ok);
    m_struBasicpara.fSub1CabinetcurrentUp=m_pUi->lineEdit_SubCurrentUp->text().toFloat(&ok);
    m_struBasicpara.fSub2CabinetcurrentUp=m_pUi->lineEdit_SubCurrentUp_2->text().toFloat(&ok);
    m_struBasicpara.fSub3CabinetcurrentUp=m_pUi->lineEdit_SubCurrentUp_3->text().toFloat(&ok);
    m_struBasicpara.fSub4CabinetcurrentUp=m_pUi->lineEdit_SubCurrentUp_4->text().toFloat(&ok);
    //m_struBasicpara.fThreevoltLow=m_pUi->lineEdit_ThreeVoltDown->text().toFloat(&ok);
    //m_struBasicpara.fThreevoltUp=m_pUi->lineEdit_ThreeVoltUp->text().toFloat(&ok);
    m_struBasicpara.fTotalcurrentUp=m_pUi->lineEdit_GfTotalCurrentUp->text().toFloat(&ok);
    m_struBasicpara.fTotalvoltUp=m_pUi->lineEdit_GfTotalVoltUp->text().toFloat(&ok);
    //m_struBasicpara.fVoltimbalance=m_pUi->lineEdit_ThreeVoltImbalance->text().toFloat(&ok);
    m_struBasicpara.iSub1CabOpen=m_pUi->checkBox_Sub1->isChecked();
    m_struBasicpara.iSub2CabOpen=m_pUi->checkBox_Sub2->isChecked();
    m_struBasicpara.iSub3CabOpen=m_pUi->checkBox_Sub3->isChecked();
    m_struBasicpara.iSub4CabOpen=m_pUi->checkBox_Sub4->isChecked();

    if(m_IniBasicParse.writeBasicParaInifile(m_struBasicpara))
    {
        //把参数m_struBasicpara赋值给全局变量g_struBasicPara,add by zqc 2019.06.16
        memcpy(&g_struBasicPara,&m_struBasicpara,sizeof(m_struBasicpara));
        QMessageBox::warning(this,
                       tr(m_strInfo),
                       tr(m_strSaveSuccess));//基本参数配置文件保存成功
    }
    else
    {
        QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strSaveFail));//基本参数配置文件保存失败,请检查

    }
    this->close();
}
//取消-槽函数
void CBasicParaSetdlg::cancelBtn_clicked()
{
    this->close();
}
//删去母线电压和三相电压设置 add by 2020.18.19
/*
//母线电压上限(V)-编辑槽函数
void CBasicParaSetdlg::BusVoltUplEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_BusVoltUp);
}
//母线电压下限(V)-编辑槽函数
void CBasicParaSetdlg::BusVoltDownlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_BusVoltDown);
}
//三相电压上限(V)-编辑槽函数
void CBasicParaSetdlg::ThreeVoltUplEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ThreeVoltUp);
}
 //三相电压下限(V)-编辑槽函数
void CBasicParaSetdlg::ThreeVoltDownlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ThreeVoltDown);
}
//三相电压不均衡度(%)-编辑槽函数
void CBasicParaSetdlg::ThreeVoltImbalancelEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ThreeVoltImbalance);
}
*/
//分柜1输出电流上限(A)-编辑槽函数
void CBasicParaSetdlg::Sub1CurrentUplEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_SubCurrentUp);
    bool ok =false;
    QString strErr1=QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2341\350\276\223\345\207\272\347\224\265\346\265\201\350\266\205\350\277\207\344\270\212\351\231\220", 0, QApplication::UnicodeUTF8);
    float fTemp=m_pUi->lineEdit_SubCurrentUp->text().toFloat(&ok);
    if(ok)
    {
        if((fTemp-OUTPUT_CURRENT_UP_LIMIT)>0.01)
        {
             QMessageBox::warning(this, tr(m_strErrinfo),strErr1);//分柜电流1超限提示,add by 2020.08.15
             m_pUi->lineEdit_SubCurrentUp->setText(QString::number(OUTPUT_CURRENT_UP_LIMIT,'f',1));
        }
    }
}
//分柜2输出电流上限(A)-编辑槽函数
void CBasicParaSetdlg::Sub2CurrentUplEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_SubCurrentUp_2);
    bool ok =false;
    QString strErr2= QApplication::translate("basicparasetDialog","\345\210\206\346\237\2342\350\276\223\345\207\272\347\224\265\346\265\201\350\266\205\350\277\207\344\270\212\351\231\220",0,QApplication::UnicodeUTF8);
    float fTemp=m_pUi->lineEdit_SubCurrentUp_2->text().toFloat(&ok);
    if(ok)
    {
        if((fTemp-OUTPUT_CURRENT_UP_LIMIT)>0.01)
        {
             QMessageBox::warning(this, tr(m_strErrinfo),strErr2);//分柜电流2超限提示,add by 2020.08.21
             m_pUi->lineEdit_SubCurrentUp_2->setText(QString::number(OUTPUT_CURRENT_UP_LIMIT,'f',1));
        }
    }

}
//分柜3输出电流上限(A)-编辑槽函数
void CBasicParaSetdlg::Sub3CurrentUplEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_SubCurrentUp_3);
    bool ok =false;
    QString strErr3= QApplication::translate("basicparasetDialog","\345\210\206\346\237\2343\350\276\223\345\207\272\347\224\265\346\265\201\350\266\205\350\277\207\344\270\212\351\231\220",0,QApplication::UnicodeUTF8);
    float fTemp=m_pUi->lineEdit_SubCurrentUp_3->text().toFloat(&ok);
    if(ok)
    {
        if((fTemp-OUTPUT_CURRENT_UP_LIMIT)>0.01)
        {
            QMessageBox::warning(this,tr(m_strErrinfo),strErr3);//分柜电流3超限提示，add by 2020.08.21
            m_pUi->lineEdit_SubCurrentUp_3->setText(QString::number(OUTPUT_CURRENT_UP_LIMIT,'f',1));
        }
    }
}
//分柜4输出电流上限(A)-编辑槽函数
void CBasicParaSetdlg::Sub4CurrentUplEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_SubCurrentUp_4);
    bool ok =false;
    QString strErr4= QApplication::translate("basicparasetDialog","\345\210\206\346\237\2344\350\276\223\345\207\272\347\224\265\346\265\201\350\266\205\350\277\207\344\270\212\351\231\220",0,QApplication::UnicodeUTF8);
    float fTemp=m_pUi->lineEdit_SubCurrentUp_4->text().toFloat(&ok);
    if(ok)
    {
        if((fTemp-OUTPUT_CURRENT_UP_LIMIT)>0.01)
        {
            QMessageBox::warning(this,tr(m_strErrinfo),strErr4);//分柜电流4超限提示，add by 2020.08.21
            m_pUi->lineEdit_SubCurrentUp_4->setText(QString::number(OUTPUT_CURRENT_UP_LIMIT,'f',1));
        }
    }
}
//功放总输出电压上限(V)-编辑槽函数
void CBasicParaSetdlg::GfTotalVoltUplEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_GfTotalVoltUp);
    bool ok =false;
    QString strErr5= QApplication::translate("basicparasetDialog", "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\345\216\213\350\266\205\350\277\207\344\270\212\351\231\220",0,QApplication::UnicodeUTF8);
    float fTemp=m_pUi->lineEdit_GfTotalVoltUp->text().toFloat(&ok);
    if(ok)
    {
        if((fTemp-OUTPUT_TOTAL_VOLTAGE_UP_LIMIT)>0.01)
        {
            QMessageBox::warning(this,tr(m_strErrinfo),strErr5);//总输出电压超限提示，add by 2020.08.21
            m_pUi->lineEdit_GfTotalVoltUp->setText(QString::number(OUTPUT_TOTAL_VOLTAGE_UP_LIMIT,'f',1));
        }
    }
}
 //功放总输出电流上限(A)-编辑槽函数
void CBasicParaSetdlg::GfTotalCurrentUplEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_GfTotalCurrentUp);
    bool ok =false;
    QString strErr6= QApplication::translate("basicparasetDialog", "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\346\265\201\350\266\205\350\277\207\344\270\212\351\231\220",0,QApplication::UnicodeUTF8);
    float fTemp=m_pUi->lineEdit_GfTotalCurrentUp->text().toFloat(&ok);
    if(ok)
    {
        if((fTemp-OUTPUT_TOTAL_CURRENT_UP_LIMIT)>0.01)
        {
            QMessageBox::warning(this,tr(m_strErrinfo),strErr6);//总输出电流超限提示，add by 2020.08.21
            m_pUi->lineEdit_GfTotalCurrentUp->setText(QString::number(OUTPUT_TOTAL_CURRENT_UP_LIMIT,'f',1));
        }
    }
}
//打开数字键盘对话框
void CBasicParaSetdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    bool ok=false;
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
}
//分柜1选择-槽函数
void CBasicParaSetdlg::checkBoxSub1_clicked()
{
    printf("####SLOT TEST:checkBoxSub1_clicked()####\n");
    if(m_struBasicpara.iSub1CabOpen==SUBCABOPEN_FLAG)
    {
        m_pUi->checkBox_Sub1->setCheckState(Qt::Unchecked);
        m_struBasicpara.iSub1CabOpen=SUBCABCLOSE_FLAG;
    }
    else
    {
        m_pUi->checkBox_Sub1->setCheckState(Qt::Checked);
        m_struBasicpara.iSub1CabOpen=SUBCABOPEN_FLAG;
    }
}
//分柜2选择-槽函数
void CBasicParaSetdlg::checkBoxSub2_clicked()
{
    printf("####SLOT TEST:checkBoxSub2_clicked()####\n");
    if(m_struBasicpara.iSub2CabOpen==SUBCABOPEN_FLAG)
    {
        m_pUi->checkBox_Sub2->setCheckState(Qt::Unchecked);
        m_struBasicpara.iSub2CabOpen=SUBCABCLOSE_FLAG;
    }
    else
    {
        m_pUi->checkBox_Sub2->setCheckState(Qt::Checked);
        m_struBasicpara.iSub2CabOpen=SUBCABOPEN_FLAG;
    }
}
//分柜3选择-槽函数
void CBasicParaSetdlg::checkBoxSub3_clicked()
{
    printf("####SLOT TEST:checkBoxSub3_clicked()####\n");
    if(m_struBasicpara.iSub3CabOpen==SUBCABOPEN_FLAG)
    {
        m_pUi->checkBox_Sub3->setCheckState(Qt::Unchecked);
        m_struBasicpara.iSub3CabOpen=SUBCABCLOSE_FLAG;
    }
    else
    {
        m_pUi->checkBox_Sub3->setCheckState(Qt::Checked);
        m_struBasicpara.iSub3CabOpen=SUBCABOPEN_FLAG;
    }
}
 //分柜4选择-槽函数
void CBasicParaSetdlg::checkBoxSub4_clicked()
{
    printf("####SLOT TEST:checkBoxSub4_clicked()####\n");
    if(m_struBasicpara.iSub4CabOpen==SUBCABOPEN_FLAG)
    {
        m_pUi->checkBox_Sub4->setCheckState(Qt::Unchecked);
        m_struBasicpara.iSub4CabOpen=SUBCABCLOSE_FLAG;
    }
    else
    {
        m_pUi->checkBox_Sub4->setCheckState(Qt::Checked);
        m_struBasicpara.iSub4CabOpen=SUBCABOPEN_FLAG;
    }
}
void CBasicParaSetdlg::basicparaLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("basicparasetDialog", "\345\237\272\346\234\254\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->groupBox_2->setTitle(QApplication::translate("basicparasetDialog", "\351\230\210\345\200\274\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
    //删去母线电压和三相电压设置 add by 2020.18.19
      /*
        m_pUi->label->setText(QApplication::translate("basicparasetDialog", "\346\257\215\347\272\277\347\224\265\345\216\213\344\270\212\351\231\220(V)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_2->setText(QApplication::translate("basicparasetDialog", "\346\257\215\347\272\277\347\224\265\345\216\213\344\270\213\351\231\220(V)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_3->setText(QApplication::translate("basicparasetDialog", "\344\270\211\347\233\270\347\224\265\345\216\213\344\270\212\351\231\220(V)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_4->setText(QApplication::translate("basicparasetDialog", "\344\270\211\347\233\270\347\224\265\345\216\213\344\270\213\351\231\220(V)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_8->setText(QApplication::translate("basicparasetDialog", "\344\270\211\347\233\270\347\224\265\345\216\213\344\270\215\345\235\207\350\241\241\345\272\246(%)", 0, QApplication::UnicodeUTF8));
        */
        m_pUi->label_9->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2341\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_10->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2342\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_11->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2343\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_12->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2344\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_5->setText(QApplication::translate("basicparasetDialog", "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\345\216\213\344\270\212\351\231\220(V)", 0, QApplication::UnicodeUTF8));
        m_pUi->label_6->setText(QApplication::translate("basicparasetDialog", "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        m_pUi->groupBox->setTitle(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\234\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_Sub1->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_Sub2->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_Sub3->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_Sub4->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));
        m_pUi->okBtn->setText(QApplication::translate("basicparasetDialog", "\347\241\256  \345\256\232", 0, QApplication::UnicodeUTF8));
        m_pUi->cancelBtn->setText(QApplication::translate("basicparasetDialog", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        m_strErrinfo = QApplication::translate("basicparasetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示

        m_strInvalidinfo = QApplication::translate("basicparasetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入

        m_strSaveSuccess= QApplication::translate("basicparasetDialog", "\345\237\272\346\234\254\345\217\202\346\225\260\351\205\215\347\275\256\346\226\207\344\273\266\344\277\235\345\255\230\346\210\220\345\212\237",
        0,
        QApplication::UnicodeUTF8);//基本参数配置文件保存成功提示语

        m_strSaveFail= QApplication::translate("basicparasetDialog", "\345\237\272\346\234\254\345\217\202\346\225\260\351\205\215\347\275\256\346\226\207\344\273\266\344\277\235\345\255\230\345\244\261\350\264\245,\350\257\267\346\243\200\346\237\245",
        0,
        QApplication::UnicodeUTF8);//基本参数配置文件保存失败提示语

        m_strInfo=QApplication::translate("basicparasetDialog",
        "\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//提示
    }
    else
    {
        setWindowTitle("Properties");
        m_pUi->groupBox_2->setTitle("Threshold parameter");
    //删去母线电压和三相电压设置 add by 2020.18.19
/*
        m_pUi->label->setText("DC Upper Limit(V)");
        m_pUi->label_2->setText("DC Lower Limit(V)");
        m_pUi->label_3->setText("3 Phase Upper Limit(V)");
        m_pUi->label_4->setText("3 Phase Lower Limit(V)");
        //m_pUi->label_7->setText("Bus voltage difference(V)");
        m_pUi->label_8->setText("3 Phase Unbalance(%)");
        */
        m_pUi->label_9->setText("Cab1 Current Upper Limit(A)");
        m_pUi->label_10->setText("Cab2 Current Upper Limit(A)");
        m_pUi->label_11->setText("Cab3 Current Upper Limit(A)");
        m_pUi->label_12->setText("Cab4 Current Upper Limit(A)");
        m_pUi->label_5->setText("PA Total Voltage Upper Limit(V)");
        m_pUi->label_6->setText("PA Total Current Upper Limit(A)");
        m_pUi->groupBox->setTitle("Selection");
        m_pUi->checkBox_Sub1->setText("Cab1");
        m_pUi->checkBox_Sub2->setText("Cab2");
        m_pUi->checkBox_Sub3->setText("Cab3");
        m_pUi->checkBox_Sub4->setText("Cab4");
        m_pUi->okBtn->setText("OK");
        m_pUi->cancelBtn->setText("Cancel");
        m_strErrinfo = "Error";//错误提示

        m_strInvalidinfo = "The value entered is not valid.Please re-enter it.";//输入的数值不合法，请重新输入

        m_strSaveSuccess= "Basic parameter profile saved successfully";//基本参数配置文件保存成功提示语

        m_strSaveFail= "Basic parameter profile failed to save";//基本参数配置文件保存失败提示语

        m_strInfo="Prompting";//提示
    }
}
