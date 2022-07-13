/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: thresholdsetdlg.cpp
** 摘要: "保护阈值"设置子对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.12.10
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2018.12.10   V1.0      创建
** 聂晓波      2019.02.02   V1.1      修改
****************************************************************************/
#include "thresholdsetdlg.h"
#include <iostream>
#include <qlineedit.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qstringlist.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "commmacro.h"

#ifdef UBUNTU_DEV //Compiler Switch
#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/fs.h>
#include <termio.h>
#endif    //Compiler Switch
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <QFile>
#include <QTextStream>
#include <QDoubleValidator>

CThresholdsetdlg::CThresholdsetdlg()
{
    m_pUi= new Ui::thresholdsetDialog;
    m_pUi->setupUi(this);

    m_strErrinfo = QApplication::translate("thresholdsetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示

    m_strInvalidinfo = QApplication::translate("thresholdsetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入

    //信号与槽
    connect(m_pUi->scbhSetBtn,SIGNAL(clicked()),this,SLOT(scbhSetBtn_clicked()));
    connect(m_pUi->gybhSetBtn,SIGNAL(clicked()),this,SLOT(gybhSetBtn_clicked()));
    connect(m_pUi->scdlSetBtn,SIGNAL(clicked()),this,SLOT(scdlSetBtn_clicked()));
    connect(m_pUi->IGBTgwSetBtn,SIGNAL(clicked()),this,SLOT(IGBTgwSetBtn_clicked()));
    connect(m_pUi->dggwSetBtn,SIGNAL(clicked()),this,SLOT(dggwSetBtn_clicked()));

    connect(m_pUi->scbhLowerEdit,SIGNAL(clicked()),this,SLOT(scbhLowerEdit_clicked()));
    connect(m_pUi->scbhUpEdit,SIGNAL(clicked()),this,SLOT(scbhUpEdit_clicked()));

    connect(m_pUi->gybhLowerEdit,SIGNAL(clicked()),this,SLOT(gybhLowerEdit_clicked()));
    connect(m_pUi->gybhUpEdit,SIGNAL(clicked()),this,SLOT(gybhUpEdit_clicked()));

    connect(m_pUi->scdlProcEdit,SIGNAL(clicked()),this,SLOT(scdlProcEdit_clicked()));
    connect(m_pUi->scdlWarningEdit,SIGNAL(clicked()),this,SLOT(scdlWarningEdit_clicked()));

    connect(m_pUi->IGBTgw1Edit,SIGNAL(clicked()),this,SLOT(IGBTgw1Edit_clicked()));
    connect(m_pUi->IGBTgw2Edit,SIGNAL(clicked()),this,SLOT(IGBTgw2Edit_clicked()));

    connect(m_pUi->dggw1Edit,SIGNAL(clicked()),this,SLOT(dggw1Edit_clicked()));
    connect(m_pUi->dggw2Edit,SIGNAL(clicked()),this,SLOT(dggw2Edit_clicked()));

    //connect(m_pUi->checkBox,SIGNAL(clicked()),this,SLOT(checkBox_clicked()));

    init();//初始化

    m_strTips=QApplication::translate("thresholdsetDialog",
        "\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//提示

    m_CANfd =-1;

#ifdef UBUNTU_DEV
    m_CANfd=m_CANDatarw.openCANSerialPort();
    if (m_CANfd < 0)
    {
        QMessageBox::warning(this, tr(m_strErrinfo), tr("Fail to open serial port!"));
        return ;
    }
    else
    {
        //QMessageBox::warning(this, tr("info"), tr("Success to open serial port!"));
        printf("####【CThresholdsetdlg::CThresholdsetdlg】Success to open serial port!####\n");
        return;
    }
#endif
}
CThresholdsetdlg::~CThresholdsetdlg()
{

}
void CThresholdsetdlg::init()
{

#ifdef WIN_DEV
    m_strFilepathName="./debug/procvalueset.ini";
#else
    m_strFilepathName=QApplication::applicationDirPath() + "/" +"procvalueset.ini";
#endif
    memset(&m_struProcValData,0,sizeof(m_struProcValData));
    m_Inifile.readProcValueSetInifile(m_struProcValData);
    m_pUi->scbhLowerEdit->setText(QString::number(m_struProcValData.fOutVoltLow,'f',1));
    m_pUi->scbhUpEdit->setText(QString::number(m_struProcValData.fOutVoltUp,'f',1));

    m_pUi->gybhLowerEdit->setText(QString::number(m_struProcValData.fDCVoltOverLow,'f',1));
    m_pUi->gybhUpEdit->setText(QString::number(m_struProcValData.fDCVoltOverUp,'f',1));

    m_pUi->scdlProcEdit->setText(QString::number(m_struProcValData.fCurrentProcVal,'f',1));
    m_pUi->scdlWarningEdit->setText(QString::number(m_struProcValData.fCurrentWarnVal,'f',1));

    m_pUi->IGBTgw1Edit->setText(QString::number(m_struProcValData.fIGBTGW1,'f',1));
    m_pUi->IGBTgw2Edit->setText(QString::number(m_struProcValData.fIGBTGW2,'f',1));

    m_pUi->dggw1Edit->setText(QString::number(m_struProcValData.fIDCUTGW1,'f',1));
    m_pUi->dggw2Edit->setText(QString::number(m_struProcValData.fIDCUTGW2,'f',1));

    //限制电压类型值范围
     m_pUi->scbhLowerEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->scbhUpEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->gybhLowerEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->gybhUpEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->scdlProcEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->scdlWarningEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
   //限制温度类型值范围
     m_pUi->IGBTgw1Edit->setValidator(new QDoubleValidator(PROC_SET_TEMPER_LOW,PROC_SET_TEMPER_UP,1,this));
     m_pUi->IGBTgw2Edit->setValidator(new QDoubleValidator(PROC_SET_TEMPER_LOW,PROC_SET_TEMPER_UP,1,this));
     m_pUi->dggw1Edit->setValidator(new QDoubleValidator(PROC_SET_TEMPER_LOW,PROC_SET_TEMPER_UP,1,this));
     m_pUi->dggw2Edit->setValidator(new QDoubleValidator(PROC_SET_CURRENT_LOW,PROC_SET_CURRENT_UP,1,this));

     /*m_isChkDigKeyBoard=false;*/
}
//输出电压保护值设置-槽函数
void CThresholdsetdlg::scbhSetBtn_clicked()
{
    //准备数据
     bool ok=false;
     int iLowvalue=0;
     int iUpvalue =0;
     float fscbhLower=m_pUi->scbhLowerEdit->text().toFloat(&ok);
     float fscbhUp = m_pUi->scbhUpEdit->text().toFloat(&ok);
     fscbhLower=fscbhLower*RATIO;
     fscbhUp=fscbhUp*RATIO;
     iLowvalue=(int)(fscbhLower);//强制转换类型，该项目不会损失精度!!!
     iUpvalue=(int)(fscbhUp);    //强制转换类型，该项目不会损失精度!!!
     //发送数据
     //m_CANDatarw.sendOutPutVoltData(m_CANfd,iLowvalue>>8,iLowvalue,iUpvalue>>8,iUpvalue);
     //操作提示信息
     QString strSuccessTmp=QApplication::translate("thresholdsetDialog",
         "\350\276\223\345\207\272\347\224\265\345\216\213\344\277\235\346\212\244\345\200\274\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);
    QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
     //把参数保存记录到文件中
    saveThresholdset(tr("outvolt_low=.*"),tr("outvolt_low="),m_pUi->scbhLowerEdit->text());
    saveThresholdset(tr("outvolt_up=.*"),tr("outvolt_up="),m_pUi->scbhUpEdit->text());
}
//过压保护值设置-槽函数
void CThresholdsetdlg::gybhSetBtn_clicked()
{
    //准备数据
     bool ok=false;
     int iLowvalue=0;
     int iUpvalue =0;
     float fgybhLower= m_pUi->gybhLowerEdit->text().toFloat(&ok);
     fgybhLower =fgybhLower*RATIO;
     float fgybhUp=m_pUi->gybhUpEdit->text().toFloat(&ok);
     fgybhUp = fgybhUp*RATIO;
     iLowvalue=(int)(fgybhLower);//强制转换类型，该项目不会损失精度!!!
     iUpvalue=(int)(fgybhUp);   //强制转换类型，该项目不会损失精度!!!

#ifdef UBUNTU_DEV
     if (m_CANfd < 0)
     {
       m_CANfd=m_CANDatarw.openCANSerialPort();
       if (m_CANfd < 0)
       {
         QMessageBox::warning(this, tr(m_strErrinfo), tr("Fail to open serial port!"));
         return ;
       }
     }

     printf("####%X-%X####\n",iLowvalue>>8,iLowvalue);
     QString str1=QString::number(iLowvalue>>8,16).toUpper();
     QString str2=QString::number(iLowvalue,16).toUpper();
     //发送数据
     //m_CANDatarw.sendDCVoltLowData(m_CANfd,iLowvalue>>8,iLowvalue);
     //延时2秒
     sleep(2);
     //m_CANDatarw.sendDCVoltUpData(m_CANfd,iUpvalue>>8,iUpvalue);
     //操作提示信息
     QString strSuccessTmp=QApplication::translate("thresholdsetDialog",
         "\345\212\237\347\216\207\346\250\241\345\235\227\350\276\223\345\205\245\347\233\264\346\265\201\347\224\265\345\216\213\350\277\207\345\216\213\344\277\235\346\212\244\345\200\274\350\256\276\347\275\256\346\210\220\345\212\237",
              0,
              QApplication::UnicodeUTF8);
     QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
     //把参数保存记录到文件中
    saveThresholdset(tr("dcvolt_low=.*"),tr("dcvolt_low="),m_pUi->gybhLowerEdit->text());
    saveThresholdset(tr("dcvolt_up=.*"),tr("dcvolt_up="),m_pUi->gybhUpEdit->text());
#endif
}
//输出电流设置-槽函数
void CThresholdsetdlg::scdlSetBtn_clicked()
{
     //准备数据
     bool ok=false;
     int iLowvalue=0;
     int iUpvalue=0;
     float fscdlProc=m_pUi->scdlProcEdit->text().toFloat(&ok);     //保护值
     float fscdlWarning=m_pUi->scdlWarningEdit->text().toFloat(&ok);//报警值
     fscdlProc=fscdlProc*RATIO;
     fscdlWarning=fscdlWarning*RATIO;
     iLowvalue=(int)(fscdlProc);  //强制转换类型，该项目不会损失精度!!!
     iUpvalue=(int)(fscdlWarning);//强制转换类型，该项目不会损失精度!!!
#ifdef UBUNTU_DEV
     if (m_CANfd < 0)
     {
       m_CANfd=m_CANDatarw.openCANSerialPort();
       if (m_CANfd < 0)
       {
         QMessageBox::warning(this, tr(m_strErrinfo), tr("Fail to open serial port!"));
         return ;
       }
     }
     //发送数据
    // m_CANDatarw.sendProcAndWarnData(m_CANfd,iLowvalue>>8,iLowvalue,iUpvalue>>8,iUpvalue);
     //操作提示信息
     QString strSuccessTmp=QApplication::translate("thresholdsetDialog",
         "\345\212\237\347\216\207\346\250\241\345\235\227\350\276\223\345\207\272\347\224\265\346\265\201\345\200\274\344\270\212\351\231\220\350\256\276\347\275\256\346\210\220\345\212\237",
         0, QApplication::UnicodeUTF8);
     QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
      //把参数保存记录到文件中
    saveThresholdset(tr("currprocvalue=.*"),tr("currprocvalue="),m_pUi->scdlProcEdit->text());
    saveThresholdset(tr("currwarnvalue=.*"),tr("currwarnvalue="),m_pUi->scdlWarningEdit->text());
#endif
}
//IGBT过温动作值设置-槽函数
void CThresholdsetdlg::IGBTgwSetBtn_clicked()
{
    //准备数据
     bool ok=false;
     int iGW1value=0;
     int iGW2value=0;
     float fIGBTgw1 = m_pUi->IGBTgw1Edit->text().toFloat(&ok);
     float fIGBTgw2 = m_pUi->IGBTgw2Edit->text().toFloat(&ok);
     fIGBTgw1=fIGBTgw1*RATIO;
     fIGBTgw2=fIGBTgw2*RATIO;
     iGW1value=(int)(fIGBTgw1);//强制转换类型，该项目不会损失精度!!!
     iGW2value=(int)(fIGBTgw2);//强制转换类型，该项目不会损失精度!!!
#ifdef UBUNTU_DEV
     //发送数据
     //m_CANDatarw.sendIGBTTemperData(m_CANfd,iGW1value>>8,iGW1value,iGW2value>>8,iGW2value);
     //操作提示信息
     QString strSuccessTmp= QApplication::translate("thresholdsetDialog",
          "\345\212\237\347\216\207\346\250\241\345\235\227IGBT\350\277\207\346\270\251\345\212\250\344\275\234\345\200\274\350\256\276\347\275\256\346\210\220\345\212\237",
          0,
          QApplication::UnicodeUTF8);
     QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
    //把参数保存记录到文件中
    saveThresholdset(tr("IGBT_temper1=.*"),tr("IGBT_temper1="),m_pUi->IGBTgw1Edit->text());
    saveThresholdset(tr("IGBT_temper2=.*"),tr("IGBT_temper2="),m_pUi->IGBTgw2Edit->text());
#endif
}
//电感过温动作值设置-槽函数
void CThresholdsetdlg::dggwSetBtn_clicked()
{
    //准备数据
     bool ok=false;
     int iDGGW1value=0;
     int iDGGW2value=0;   //实则为总电流平均值
     float fdggw1= m_pUi->dggw1Edit->text().toFloat(&ok);
     float fdggw2= m_pUi->dggw2Edit->text().toFloat(&ok);
     fdggw1=fdggw1*RATIO;
     fdggw2=fdggw2*RATIO;
     iDGGW1value=(int)(fdggw1);
     iDGGW2value=(int)(fdggw2);
#ifdef UBUNTU_DEV
     //发送数据
     //m_CANDatarw.sendIDUCTTemper1Data(m_CANfd,iDGGW1value>>8,iDGGW1value);
     //延时2秒
     sleep(2);
    // m_CANDatarw.sendIDUCTTemper2Data(m_CANfd,iDGGW2value>>8,iDGGW2value);
     //操作提示信息
     QString strSuccessTmp=QApplication::translate("thresholdsetDialog",
         "\345\212\237\347\216\207\346\250\241\345\235\227\347\224\265\346\204\237\350\277\207\346\270\251\345\212\250\344\275\234\345\200\274\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);
     QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
     //把参数保存记录到文件中
    saveThresholdset(tr("IDUCT_temper=.*"),tr("IDUCT_temper="),m_pUi->dggw1Edit->text());
    saveThresholdset(tr("SUMCURRENT_AVE=.*"),tr("SUMCURRENT_AVE="),m_pUi->dggw2Edit->text());
#endif
}
//保存保护阈值参数到文件中
bool CThresholdsetdlg::saveThresholdset(QString strRegExp,QString strReplace,QString strText)
{
     QFile file(m_strFilepathName);
     if(!file.open(QFile::ReadOnly | QFile::Text))
      {
          printf("####Cannot open file for Reading####\n");
          return false;
       }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    int i=0;
    for(i=0;i<linelist.size();i++)
    {
        QString strTmp=linelist.at(i);
     if(strTmp.contains(strReplace, Qt::CaseInsensitive))
      {
          strTmp.replace(QRegExp(strRegExp),(strReplace+strText));
          linelist.replace(i,strTmp);//替换内容
      }
    }
     file.close();
     QFile::remove(m_strFilepathName);
      if(!file.open(QFile::WriteOnly | QFile::Text))
      {
          printf( "####Cannot open file for Writing####\n");
          return false;
      }
      for(i=0;i<linelist.size();i++)
      {
          file.write(linelist.at(i).toUtf8());
          file.write(tr("\n").toUtf8());
      }
      file.close();
    return true;
}
//有效性判断
void  CThresholdsetdlg::EffectiveJudge(QString text,int nDatatype)
{
    bool ok =false;
    float fValue=text.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,
            tr(m_strErrinfo),
            tr(m_strInvalidinfo));//输入的数值不合法
    }
    else
    {
     switch(nDatatype)
       {
        case PROC_SET_VOLT_TYPE:
            {
                if(((fValue-PROC_SET_VOLT_UP)>0.01)||((fValue-PROC_SET_VOLT_LOW)<0.01))
                {
                    QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//输入的数值不合法
                }
            }
            break;
        case PROC_SET_TEMPER_TYPE:
            {
                if(((fValue-PROC_SET_TEMPER_UP)>0.01)||((fValue-PROC_SET_TEMPER_LOW)<0.01))
                {
                    QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//输入的数值不合法
                }
            }
            break;
        default:
            break;
       }//switch(nDatatype)
    }
}
//打开数字键盘对话框
void CThresholdsetdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    bool ok=false;
    /*if(m_isChkDigKeyBoard)*/
    //{
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
    //}//if(m_isChkDigKeyBoard)
}
void CThresholdsetdlg::scbhLowerEdit_clicked()
{
    //打开数字键盘对话框
     openDigKeyBoardDlg(m_pUi->scbhLowerEdit);

    //有效性判断
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}

void CThresholdsetdlg::scbhUpEdit_clicked()
{
    //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->scbhUpEdit);
    //有效性判断
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::gybhLowerEdit_clicked()
{
     //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->gybhLowerEdit);
    //有效性判断
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::gybhUpEdit_clicked()
{
     //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->gybhUpEdit);
    //有效性判断
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::scdlProcEdit_clicked()
{
     //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->scdlProcEdit);
    //有效性判断
    //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::scdlWarningEdit_clicked()
{
     //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->scdlWarningEdit);
    //有效性判断
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::IGBTgw1Edit_clicked()
{
     //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->IGBTgw1Edit);
    //有效性判断
     //EffectiveJudge(text,PROC_SET_TEMPER_TYPE);
}
void CThresholdsetdlg::IGBTgw2Edit_clicked()
{
     //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->IGBTgw2Edit);
    //有效性判断
     //EffectiveJudge(text,PROC_SET_TEMPER_TYPE);
}
void CThresholdsetdlg::dggw1Edit_clicked()
{
     //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->dggw1Edit);
    //有效性判断
     //EffectiveJudge(text,PROC_SET_TEMPER_TYPE);
}
void CThresholdsetdlg::dggw2Edit_clicked()
{
     //打开数字键盘对话框
    openDigKeyBoardDlg(m_pUi->dggw2Edit);
    //有效性判断
     //EffectiveJudge(text,PROC_SET_TEMPER_TYPE);
}
//"是否勾选数字键"槽函数
//void CThresholdsetdlg::checkBox_clicked()
//{
//	if(m_pUi->checkBox->checkState()==Qt::Checked)
//	{
//		m_isChkDigKeyBoard=true;
//
//	}
//	else if(m_pUi->checkBox->checkState()==Qt::Unchecked)
//	{
//		m_isChkDigKeyBoard=false;
//	}
//
//}
