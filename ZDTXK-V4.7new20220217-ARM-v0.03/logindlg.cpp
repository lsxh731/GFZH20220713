/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: logindlg.cpp
** 摘要: 输入密码登录对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.01.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.01.01   V1.0      创建
**
****************************************************************************/
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QByteArray>

#include "logindlg.h"
#include "md5encode.h"
#include "ui_login.h"
extern int g_iLangChange;//add by 2019.10.3

CLogindlg::CLogindlg()
{
    m_pUi= new Ui::loginDialog;
    m_pUi->setupUi(this);
    //信号与槽关系
    connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    connect(m_pUi->clearBtn,SIGNAL(clicked()),this,SLOT(clearBtn_clicked()));
    connect(m_pUi->cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_clicked()));
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
//	connect(m_pUi->adminradioBtn,SIGNAL(clicked()),this,SLOT(adminradioBtn_clicked()));     //管理员槽函数 add by 2020.08.15
//	connect(m_pUi->engneerradioBtn,SIGNAL(clicked()),this,SLOT(engneerradioBtn_clicked()));//工程师槽函数 add by 2020.08.15
//	connect(m_pUi->userradioBtn,SIGNAL(clicked()),this,SLOT(userradioBtn_clicked()));            //用户槽函数 add by 2020.08.15
    m_pUi->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    m_pUi->lineEdit_pwd->setMaxLength(6);//最多是6位密码
    m_bPwdCorrect=OTHER_ROLE_TYPE;
    m_iRoletype=USER_ROLE_TYPE;//add by 2020.08.15
}

CLogindlg::~CLogindlg()
{

}
/*
//管理员角色槽函数实现 add by 2020.08.15
void CLogindlg::adminradioBtn_clicked()
{
    m_iRoletype=ADMIN_ROLE_TYPE;

}
//工程师角色槽函数实现 add by 2020.08.15
void CLogindlg::engneerradioBtn_clicked()
{
    m_iRoletype=ENGINEER_ROLE_TYPE;
}
//用户角色槽函数实现 add by 2020.08.15
void CLogindlg::userradioBtn_clicked()
{
    m_iRoletype=USER_ROLE_TYPE;
}
*/
void CLogindlg::okBtn_clicked()
{
#ifdef WIN_DEV
    std::string srcpwd = m_pUi->lineEdit_pwd->text();//.toStdString();//保持字符串类型统一
    //QString qstr =  m_pUi->lineEdit_pwd->text();
    //std::string srcpwd = qstr.toStdString(); //.toStdString();//保持字符串类型统一 add by 20201110
#else
     QString srcpwd = m_pUi->lineEdit_pwd->text();
#endif
     Md5Encode encode_obj;
     m_iRoletype =srcpwd.size();  //获取输入密码位数 add by 2020.12.01
#ifdef WIN_DEV
     std::string retpwd = encode_obj.Encode(srcpwd);
#else
     QString retpwd = QString::fromStdString(encode_obj.Encode(srcpwd.toStdString()));
#endif
     // m_strPwd=tr("a7fa5385c99fecb3642a8e1f7333b8a5");//测试密码
      //从文件中获取密码信息

     if(readPwdFile(m_iRoletype))
      {
      //std::string rettemp= m_strPwd.toAscii();//UTF-8编码
     if(retpwd==m_strPwd)
       {
          m_bPwdCorrect=m_iRoletype;
          this->close();
       }
      else
      {
          m_bPwdCorrect=OTHER_ROLE_TYPE;
          //"\350\255\246\345\221\212"：警告
         if(g_iLangChange==1)
          {
            QMessageBox::warning(this, tr("\350\255\246\345\221\212"),
                                tr("\346\202\250\350\276\223\345\205\245\347\232\204\345\257\206\347\240\201\351\224\231\350\257\257,\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245"));
          }
          else
          {
            QMessageBox::warning(this, tr("Waring"),
                                tr("Password input error "));
          }
       }
     }
     else
     {
           QMessageBox::warning(this, tr("\350\255\246\345\221\212"),
                                tr("fail to read password file\n"));

     }
}
//判断密码是否正确
int CLogindlg::IsPWDCorrect()
{
    return m_bPwdCorrect;
}
//"数字键0"槽函数
void CLogindlg::pushButton0_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("0"));
}
//"数字键1"槽函数
void CLogindlg::pushButton1_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("1"));
}
//"数字键2"槽函数
void CLogindlg::pushButton2_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("2"));
}
//"数字键3"槽函数
void CLogindlg::pushButton3_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("3"));
}
//"数字键4"槽函数
void CLogindlg::pushButton4_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("4"));
}
//"数字键5"槽函数
void CLogindlg::pushButton5_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("5"));
}
//"数字键6槽函数
void CLogindlg::pushButton6_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("6"));
}
//"数字键7"槽函数
void CLogindlg::pushButton7_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("7"));
}
//"数字键8"槽函数
void CLogindlg::pushButton8_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("8"));
}
//"数字键9"槽函数
void CLogindlg::pushButton9_clicked()
{
    m_pUi->lineEdit_pwd->insert(tr("9"));
}
//"清除"槽函数
void CLogindlg::clearBtn_clicked()
{
    if(!(m_pUi->lineEdit_pwd->text().isEmpty()))
    {
        m_pUi->lineEdit_pwd->clear();
        m_bPwdCorrect= OTHER_ROLE_TYPE;
    }
}
//"取消"槽函数
void CLogindlg::cancelBtn_clicked()
{
    m_bPwdCorrect= OTHER_ROLE_TYPE;
    this->close();
}
//读取密码配置文件
bool CLogindlg::readPwdFile(int nRoletype)
{
    QString filepathname;
    switch(nRoletype)
    {
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
    case USER_ROLE_TYPE:
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
    }//switch(nRoletype)

    QFile file(filepathname);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        printf("####【CLogindlg::readPwdFile】Fail to open  password file####\n");
        return false;
    }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    m_strPwd=linelist.at(0);
    file.close();//关闭文件

    return true;
}
void CLogindlg::loginLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("loginDialog", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_2->setText(QApplication::translate("loginDialog", "  \345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        m_pUi->okBtn->setText(QApplication::translate("loginDialog", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        m_pUi->cancelBtn->setText(QApplication::translate("loginDialog", "\345\217\226 \346\266\210 ", 0, QApplication::UnicodeUTF8));
        m_pUi->clearBtn->setText(QApplication::translate("loginDialog", "\346\270\205 \351\231\244", 0, QApplication::UnicodeUTF8));
        m_pUi->groupBox->setTitle(QApplication::translate("loginDialog", "\346\225\260\345\255\227\351\224\256\347\233\230", 0, QApplication::UnicodeUTF8));
    }
    else
    {
        setWindowTitle("Please input a password");
        m_pUi->label_2->setText("Password");
        m_pUi->okBtn->setText("OK");
        m_pUi->cancelBtn->setText("Cancel");
        m_pUi->clearBtn->setText("Clear");
        m_pUi->groupBox->setTitle("Keyboard");
    }
}
