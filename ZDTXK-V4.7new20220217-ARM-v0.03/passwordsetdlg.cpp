/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: passwordsetdlg.cpp
** 摘要: 密码设置对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.01.27
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.01.27   V1.0      创建
**
****************************************************************************/
#include "passwordsetdlg.h"
#include "qmessagebox.h"
#include "md5encode.h"
#include "commmacro.h"
#include <QFile>
#include <QTextStream>
#include <QByteArray>
extern int g_iLangChange;//add by 2019.10.3
CPasswordSetdlg::CPasswordSetdlg()
{
    m_pUi= new Ui::pwdSetDialog;
    m_pUi->setupUi(this);
    //信号与槽
    connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    connect(m_pUi->cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_clicked()));
    connect(m_pUi->clearBtn,SIGNAL(clicked()),this,SLOT(clearBtn_clicked()));

    //pushButton_0
    connect(m_pUi->pushButton_0,SIGNAL(clicked()),this,SLOT(pushButton0_clicked()));
    //pushButton_1
    connect(m_pUi->pushButton_1,SIGNAL(clicked()),this,SLOT(pushButton1_clicked()));
    //pushButton_2
    connect(m_pUi->pushButton_2,SIGNAL(clicked()),this,SLOT(pushButton2_clicked()));
    //pushButton_3
    connect(m_pUi->pushButton_3,SIGNAL(clicked()),this,SLOT(pushButton3_clicked()));
    //pushButton_4
    connect(m_pUi->pushButton_4,SIGNAL(clicked()),this,SLOT(pushButton4_clicked()));
    //pushButton_5
    connect(m_pUi->pushButton_5,SIGNAL(clicked()),this,SLOT(pushButton5_clicked()));
    //pushButton_6
    connect(m_pUi->pushButton_6,SIGNAL(clicked()),this,SLOT(pushButton6_clicked()));
    //pushButton_7
    connect(m_pUi->pushButton_7,SIGNAL(clicked()),this,SLOT(pushButton7_clicked()));
    //pushButton_8
    connect(m_pUi->pushButton_8,SIGNAL(clicked()),this,SLOT(pushButton8_clicked()));
    //pushButton_9
    connect(m_pUi->pushButton_9,SIGNAL(clicked()),this,SLOT(pushButton9_clicked()));

    connect(m_pUi->radioBtn_currpwd,SIGNAL(clicked()),this,SLOT(rBtncurrpwd_clicked()));
    connect(m_pUi->radioBtn_newpwd,SIGNAL(clicked()),this,SLOT(rBtnnewpwd_clicked()));
    connect(m_pUi->radioBtn_checkpwd,SIGNAL(clicked()),this,SLOT(rBtncheckpwd_clicked()));

    m_pUi->lineEdit_currpwd->setEchoMode(QLineEdit::Password);
    m_pUi->lineEdit_currpwd->setMaxLength(6);//最多是6位密码
    m_pUi->lineEdit_currpwd->clear();

    m_pUi->lineEdit_newpwd->setEchoMode(QLineEdit::Password);
    m_pUi->lineEdit_newpwd->setMaxLength(6);//最多是6位密码
    m_pUi->lineEdit_newpwd->clear();

    m_pUi->lineEdit_checkpwd->setEchoMode(QLineEdit::Password);
    m_pUi->lineEdit_checkpwd->setMaxLength(6);//最多是6位密码
    m_pUi->lineEdit_checkpwd->clear();

    m_iCurrLineEdit =1;

    m_pUi->lineEdit_currpwd->setEdited(false);
    m_pUi->lineEdit_newpwd->setEdited(false);
    m_pUi->lineEdit_checkpwd->setEdited(false);
}
CPasswordSetdlg::~CPasswordSetdlg()
{

}
//add by 2020.08.15
void CPasswordSetdlg::getRoletype(int nRoletype)
{
    m_iRoletype=nRoletype;
}
//"确定"槽函数
void CPasswordSetdlg::okBtn_clicked()
{
     QString strErrinfo=QApplication::translate("pwdSetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示
     QString stroldpwdErr=QApplication::translate("pwdSetDialog",
         "\346\227\247\345\257\206\347\240\201\350\276\223\345\205\245\351\224\231\350\257\257",
         0,
         QApplication::UnicodeUTF8);//旧密码输入错误
     QString strcheckpwdErr=QApplication::translate("pwdSetDialog",
         "\346\226\260\345\257\206\347\240\201\344\270\216\347\241\256\350\256\244\345\257\206\347\240\201\344\270\215\344\270\200\350\207\264",
         0,
         QApplication::UnicodeUTF8);//新密码与确认密码不一致
     QString filepathname;
     switch(m_iRoletype)
     {
     case USER_ROLE_TYPE:
#ifdef WIN_DEV
    filepathname="./debug/userpassword.ini";
#else
    filepathname=QApplication::applicationDirPath() + "/" +"userpassword.ini";
#endif
         break;
    case ADMIN_ROLE_TYPE:
#ifdef WIN_DEV
    filepathname="./debug/adminpassword.ini";
#else
    filepathname=QApplication::applicationDirPath() + "/" +"adminpassword.ini";
#endif
         break;
    case ENGINEER_ROLE_TYPE:
#ifdef WIN_DEV
    filepathname="./debug/engineerpassword.ini";
#else
    filepathname=QApplication::applicationDirPath() + "/" +"engineerpassword.ini";
#endif
         break;
    case OTHER_ROLE_TYPE:
#ifdef WIN_DEV
    filepathname="./debug/userpassword.ini";
#else
    filepathname=QApplication::applicationDirPath() + "/" +"userpassword.ini";
#endif
         break;
    default:
#ifdef WIN_DEV
    filepathname="./debug/userpassword.ini";
#else
    filepathname=QApplication::applicationDirPath() + "/" +"userpassword.ini";
#endif
         break;
     }
     QFile file(filepathname);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        printf("####CPasswordSetdlg::okBtn_clicked()--Fail to open password file####\n");
        return;
    }
    else
    {
        printf("####CPasswordSetdlg::okBtn_clicked()--Success to open password file####\n");
    }

    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    m_strcurrPwdfromfile=linelist.at(0);
    file.close();//关闭文件

#ifdef WIN_DEV
    std::string srcpwd = m_pUi->lineEdit_currpwd->text();//.toStdString();//保持字符串风格统一
#else
     QString srcpwd = m_pUi->lineEdit_currpwd->text();
#endif
     Md5Encode encode_obj;
#ifdef WIN_DEV
     std::string retpwd = encode_obj.Encode(srcpwd);
     std::string rettemp= m_strcurrPwdfromfile.toAscii();//UTF-8编码
     //std::string rettemp= m_strcurrPwdfromfile.toStdString();//保持字符串风格统一
     if( retpwd.compare(rettemp)!=0)
    {
        //旧密码输入错误，给出提示
        QMessageBox::warning(this,
            tr(strErrinfo),
            tr(stroldpwdErr));

        return;
    }
#else
     QString retpwd = QString::fromStdString(encode_obj.Encode(srcpwd.toStdString()));
     if(retpwd!=m_strcurrPwdfromfile)
    {
        //旧密码输入错误，给出提示
        QMessageBox::warning(this,
            tr(strErrinfo),
            tr(stroldpwdErr));

        return;
    }
#endif

    if(m_pUi->lineEdit_newpwd->text()!=m_pUi->lineEdit_checkpwd->text())
    {
        //新密码与确认密码不一致，给出提示
        QMessageBox::warning(this,
            tr(strErrinfo),
            tr(strcheckpwdErr));
    }
    else
    {
        //保存到密码配置文件并关闭对话框

#ifdef WIN_DEV
        std::string srcpwd_out = m_pUi->lineEdit_newpwd->text();
#else
     QString srcpwd_out = m_pUi->lineEdit_newpwd->text();
#endif
     Md5Encode encode_obj;
#ifdef WIN_DEV
     std::string md5pwd_out = encode_obj.Encode(srcpwd_out);
#else
      QString md5pwd_out = QString::fromStdString(encode_obj.Encode(srcpwd_out.toStdString()));
#endif
        QString filepathname;
        switch(m_iRoletype)
        {
            //按角色类型写不同的密码文件 add by 2020.08.15
        case USER_ROLE_TYPE:
   #ifdef WIN_DEV
       filepathname="./debug/userpassword.ini";
   #else
       filepathname=QApplication::applicationDirPath() + "/" +"userpassword.ini";
   #endif
            break;
       case ADMIN_ROLE_TYPE:
   #ifdef WIN_DEV
       filepathname="./debug/adminpassword.ini";
   #else
       filepathname=QApplication::applicationDirPath() + "/" +"adminpassword.ini";
   #endif
            break;
       case ENGINEER_ROLE_TYPE:
   #ifdef WIN_DEV
       filepathname="./debug/engineerpassword.ini";
   #else
       filepathname=QApplication::applicationDirPath() + "/" +"engineerpassword.ini";
   #endif
            break;
       case OTHER_ROLE_TYPE:
   #ifdef WIN_DEV
       filepathname="./debug/userpassword.ini";
   #else
       filepathname=QApplication::applicationDirPath() + "/" +"userpassword.ini";
   #endif
            break;
       default:
   #ifdef WIN_DEV
       filepathname="./debug/userpassword.ini";
   #else
       filepathname=QApplication::applicationDirPath() + "/" +"userpassword.ini";
   #endif
            break;
        }
        QFile outfile(filepathname);
        if (!outfile.open(QFile::WriteOnly | QFile::Text))
        {
            printf("####Ready to write File--Fail to open password outfile####\n");
             return;
        }
        int nwritelen=0;
        nwritelen=md5pwd_out.length();
#ifdef WIN_DEV
        outfile.write(md5pwd_out.c_str(),nwritelen); // write to stderr
#else
        outfile.write(md5pwd_out.toAscii().constData(),nwritelen); // write to stderr
#endif
        if(nwritelen==0)
        {
            //写文件失败
            QMessageBox::warning(this,
            tr(strErrinfo),
            tr("Fail to write file\n"));
            outfile.close();//关闭文件
        }
        else
        {  //写文件成功
            outfile.close();
            this->close();//关闭文件
        }

    }

}
//"取消"槽函数
void CPasswordSetdlg::cancelBtn_clicked()
{
    this->close();
}
//"清除"槽函数
void CPasswordSetdlg::clearBtn_clicked()
{
    m_pUi->lineEdit_currpwd->clear();
    m_pUi->lineEdit_newpwd->clear();
    m_pUi->lineEdit_checkpwd->clear();
    m_pUi->radioBtn_currpwd->setChecked(true);//默认radio按钮使能旧密码
    m_iCurrLineEdit =1;
    m_pUi->radioBtn_newpwd->setChecked(false);
    m_pUi->radioBtn_checkpwd->setChecked(false);
}
//"旧密码"槽函数
void CPasswordSetdlg::rBtncurrpwd_clicked()
{
    m_iCurrLineEdit =1;
    m_pUi->lineEdit_currpwd->setEdited(true);
    m_pUi->lineEdit_newpwd->setEdited(false);
    m_pUi->lineEdit_checkpwd->setEdited(false);
    m_pUi->lineEdit_currpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
    m_pUi->lineEdit_newpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
    m_pUi->lineEdit_checkpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
}
//"新密码"槽函数
void CPasswordSetdlg::rBtnnewpwd_clicked()
{
    m_iCurrLineEdit =2;
    m_pUi->lineEdit_currpwd->setEdited(false);
    m_pUi->lineEdit_newpwd->setEdited(true);
    m_pUi->lineEdit_checkpwd->setEdited(false);
    m_pUi->lineEdit_currpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
    m_pUi->lineEdit_newpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
    m_pUi->lineEdit_checkpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
}
//"密码确认"槽函数
void CPasswordSetdlg::rBtncheckpwd_clicked()
{
    m_iCurrLineEdit =3;
    m_pUi->lineEdit_currpwd->setEdited(false);
    m_pUi->lineEdit_newpwd->setEdited(false);
    m_pUi->lineEdit_checkpwd->setEdited(true);
    m_pUi->lineEdit_currpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
    m_pUi->lineEdit_newpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
    m_pUi->lineEdit_checkpwd->setMaxLength(m_iRoletype);//根据权限设定密码位数上限 add by 2020.12.01
}
//获取数字键盘
void CPasswordSetdlg::getDigitalKeyboardText(QPushButton *pushButton)
{
    bool currpwdFlag=false;
    bool newpwdFlag=false;
    bool checkpwdFlag=false;
    currpwdFlag=m_pUi->lineEdit_currpwd->hasAcceptableInput ();
    if ((currpwdFlag)&&(m_iCurrLineEdit==1))
    {
        m_pUi->lineEdit_currpwd->insert(pushButton->text());
    }
    newpwdFlag=m_pUi->lineEdit_newpwd->hasAcceptableInput ();
    if((newpwdFlag)&&(m_iCurrLineEdit==2))
    {
        m_pUi->lineEdit_newpwd->insert(pushButton->text());
    }
    checkpwdFlag=m_pUi->lineEdit_checkpwd->hasAcceptableInput ();
    if((checkpwdFlag)&&(m_iCurrLineEdit==3))
    {
        m_pUi->lineEdit_checkpwd->insert(tr(pushButton->text()));
    }
}
//"数字键0"槽函数
void CPasswordSetdlg::pushButton0_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_0);
}
//"数字键1"槽函数
void CPasswordSetdlg::pushButton1_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_1);
}
//"数字键2"槽函数
void CPasswordSetdlg::pushButton2_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_2);
}
//"数字键3"槽函数
void CPasswordSetdlg::pushButton3_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_3);
}
//"数字键4"槽函数
void CPasswordSetdlg::pushButton4_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_4);
}
//"数字键5"槽函数
void CPasswordSetdlg::pushButton5_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_5);
}
//"数字键6"槽函数
void CPasswordSetdlg::pushButton6_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_6);
}
//"数字键7"槽函数
void CPasswordSetdlg::pushButton7_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_7);
}
//"数字键8"槽函数
void CPasswordSetdlg::pushButton8_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_8);
}
//"数字键9"槽函数
void CPasswordSetdlg::pushButton9_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_9);
}void CPasswordSetdlg::passwordLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("pwdSetDialog", "\345\257\206\347\240\201\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->radioBtn_currpwd->setText(QApplication::translate("pwdSetDialog", "\346\227\247\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        m_pUi->radioBtn_newpwd->setText(QApplication::translate("pwdSetDialog", "\346\226\260\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        m_pUi->radioBtn_checkpwd->setText(QApplication::translate("pwdSetDialog", "\345\257\206\347\240\201\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_pUi->okBtn->setText(QApplication::translate("pwdSetDialog", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        m_pUi->groupBox->setTitle(QApplication::translate("pwdSetDialog", "\346\225\260\345\255\227\351\224\256\347\233\230", 0, QApplication::UnicodeUTF8));
        m_pUi->cancelBtn->setText(QApplication::translate("pwdSetDialog", "\345\217\226  \346\266\210", 0, QApplication::UnicodeUTF8));
        m_pUi->clearBtn->setText(QApplication::translate("pwdSetDialog", "\346\270\205 \351\231\244", 0, QApplication::UnicodeUTF8));
       QString strErrinfo=QApplication::translate("pwdSetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示
     QString stroldpwdErr=QApplication::translate("pwdSetDialog",
         "\346\227\247\345\257\206\347\240\201\350\276\223\345\205\245\351\224\231\350\257\257",
         0,
         QApplication::UnicodeUTF8);//旧密码输入错误
     QString strcheckpwdErr=QApplication::translate("pwdSetDialog",
         "\346\226\260\345\257\206\347\240\201\344\270\216\347\241\256\350\256\244\345\257\206\347\240\201\344\270\215\344\270\200\350\207\264",
         0,
         QApplication::UnicodeUTF8);//新密码与确认密码不一致
    }
    else
    {
        setWindowTitle("Password");
        m_pUi->radioBtn_currpwd->setText("Old password");
        m_pUi->radioBtn_newpwd->setText("New password");
        m_pUi->radioBtn_checkpwd->setText("Confirm Password");
        m_pUi->okBtn->setText("OK");
        m_pUi->groupBox->setTitle("Keyboard");
        m_pUi->cancelBtn->setText("Cancel");
        m_pUi->clearBtn->setText("Clear");
        QString strErrinfo="Error prompt";//错误提示
        QString stroldpwdErr="Old password input error";//旧密码输入错误
        QString strcheckpwdErr="The new password does not match the confirmed password";//新密码与确认密码不一致
    }
}
