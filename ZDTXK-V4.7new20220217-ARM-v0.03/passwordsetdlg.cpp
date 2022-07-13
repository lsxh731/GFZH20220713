/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: passwordsetdlg.cpp
** ժҪ: �������öԻ���
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2019.01.27
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2019.01.27   V1.0      ����
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
    //�ź����
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
    m_pUi->lineEdit_currpwd->setMaxLength(6);//�����6λ����
    m_pUi->lineEdit_currpwd->clear();

    m_pUi->lineEdit_newpwd->setEchoMode(QLineEdit::Password);
    m_pUi->lineEdit_newpwd->setMaxLength(6);//�����6λ����
    m_pUi->lineEdit_newpwd->clear();

    m_pUi->lineEdit_checkpwd->setEchoMode(QLineEdit::Password);
    m_pUi->lineEdit_checkpwd->setMaxLength(6);//�����6λ����
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
//"ȷ��"�ۺ���
void CPasswordSetdlg::okBtn_clicked()
{
     QString strErrinfo=QApplication::translate("pwdSetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//������ʾ
     QString stroldpwdErr=QApplication::translate("pwdSetDialog",
         "\346\227\247\345\257\206\347\240\201\350\276\223\345\205\245\351\224\231\350\257\257",
         0,
         QApplication::UnicodeUTF8);//�������������
     QString strcheckpwdErr=QApplication::translate("pwdSetDialog",
         "\346\226\260\345\257\206\347\240\201\344\270\216\347\241\256\350\256\244\345\257\206\347\240\201\344\270\215\344\270\200\350\207\264",
         0,
         QApplication::UnicodeUTF8);//��������ȷ�����벻һ��
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
    file.close();//�ر��ļ�

#ifdef WIN_DEV
    std::string srcpwd = m_pUi->lineEdit_currpwd->text();//.toStdString();//�����ַ������ͳһ
#else
     QString srcpwd = m_pUi->lineEdit_currpwd->text();
#endif
     Md5Encode encode_obj;
#ifdef WIN_DEV
     std::string retpwd = encode_obj.Encode(srcpwd);
     std::string rettemp= m_strcurrPwdfromfile.toAscii();//UTF-8����
     //std::string rettemp= m_strcurrPwdfromfile.toStdString();//�����ַ������ͳһ
     if( retpwd.compare(rettemp)!=0)
    {
        //������������󣬸�����ʾ
        QMessageBox::warning(this,
            tr(strErrinfo),
            tr(stroldpwdErr));

        return;
    }
#else
     QString retpwd = QString::fromStdString(encode_obj.Encode(srcpwd.toStdString()));
     if(retpwd!=m_strcurrPwdfromfile)
    {
        //������������󣬸�����ʾ
        QMessageBox::warning(this,
            tr(strErrinfo),
            tr(stroldpwdErr));

        return;
    }
#endif

    if(m_pUi->lineEdit_newpwd->text()!=m_pUi->lineEdit_checkpwd->text())
    {
        //��������ȷ�����벻һ�£�������ʾ
        QMessageBox::warning(this,
            tr(strErrinfo),
            tr(strcheckpwdErr));
    }
    else
    {
        //���浽���������ļ����رնԻ���

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
            //����ɫ����д��ͬ�������ļ� add by 2020.08.15
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
            //д�ļ�ʧ��
            QMessageBox::warning(this,
            tr(strErrinfo),
            tr("Fail to write file\n"));
            outfile.close();//�ر��ļ�
        }
        else
        {  //д�ļ��ɹ�
            outfile.close();
            this->close();//�ر��ļ�
        }

    }

}
//"ȡ��"�ۺ���
void CPasswordSetdlg::cancelBtn_clicked()
{
    this->close();
}
//"���"�ۺ���
void CPasswordSetdlg::clearBtn_clicked()
{
    m_pUi->lineEdit_currpwd->clear();
    m_pUi->lineEdit_newpwd->clear();
    m_pUi->lineEdit_checkpwd->clear();
    m_pUi->radioBtn_currpwd->setChecked(true);//Ĭ��radio��ťʹ�ܾ�����
    m_iCurrLineEdit =1;
    m_pUi->radioBtn_newpwd->setChecked(false);
    m_pUi->radioBtn_checkpwd->setChecked(false);
}
//"������"�ۺ���
void CPasswordSetdlg::rBtncurrpwd_clicked()
{
    m_iCurrLineEdit =1;
    m_pUi->lineEdit_currpwd->setEdited(true);
    m_pUi->lineEdit_newpwd->setEdited(false);
    m_pUi->lineEdit_checkpwd->setEdited(false);
    m_pUi->lineEdit_currpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
    m_pUi->lineEdit_newpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
    m_pUi->lineEdit_checkpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
}
//"������"�ۺ���
void CPasswordSetdlg::rBtnnewpwd_clicked()
{
    m_iCurrLineEdit =2;
    m_pUi->lineEdit_currpwd->setEdited(false);
    m_pUi->lineEdit_newpwd->setEdited(true);
    m_pUi->lineEdit_checkpwd->setEdited(false);
    m_pUi->lineEdit_currpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
    m_pUi->lineEdit_newpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
    m_pUi->lineEdit_checkpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
}
//"����ȷ��"�ۺ���
void CPasswordSetdlg::rBtncheckpwd_clicked()
{
    m_iCurrLineEdit =3;
    m_pUi->lineEdit_currpwd->setEdited(false);
    m_pUi->lineEdit_newpwd->setEdited(false);
    m_pUi->lineEdit_checkpwd->setEdited(true);
    m_pUi->lineEdit_currpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
    m_pUi->lineEdit_newpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
    m_pUi->lineEdit_checkpwd->setMaxLength(m_iRoletype);//����Ȩ���趨����λ������ add by 2020.12.01
}
//��ȡ���ּ���
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
//"���ּ�0"�ۺ���
void CPasswordSetdlg::pushButton0_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_0);
}
//"���ּ�1"�ۺ���
void CPasswordSetdlg::pushButton1_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_1);
}
//"���ּ�2"�ۺ���
void CPasswordSetdlg::pushButton2_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_2);
}
//"���ּ�3"�ۺ���
void CPasswordSetdlg::pushButton3_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_3);
}
//"���ּ�4"�ۺ���
void CPasswordSetdlg::pushButton4_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_4);
}
//"���ּ�5"�ۺ���
void CPasswordSetdlg::pushButton5_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_5);
}
//"���ּ�6"�ۺ���
void CPasswordSetdlg::pushButton6_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_6);
}
//"���ּ�7"�ۺ���
void CPasswordSetdlg::pushButton7_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_7);
}
//"���ּ�8"�ۺ���
void CPasswordSetdlg::pushButton8_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_8);
}
//"���ּ�9"�ۺ���
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
         QApplication::UnicodeUTF8);//������ʾ
     QString stroldpwdErr=QApplication::translate("pwdSetDialog",
         "\346\227\247\345\257\206\347\240\201\350\276\223\345\205\245\351\224\231\350\257\257",
         0,
         QApplication::UnicodeUTF8);//�������������
     QString strcheckpwdErr=QApplication::translate("pwdSetDialog",
         "\346\226\260\345\257\206\347\240\201\344\270\216\347\241\256\350\256\244\345\257\206\347\240\201\344\270\215\344\270\200\350\207\264",
         0,
         QApplication::UnicodeUTF8);//��������ȷ�����벻һ��
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
        QString strErrinfo="Error prompt";//������ʾ
        QString stroldpwdErr="Old password input error";//�������������
        QString strcheckpwdErr="The new password does not match the confirmed password";//��������ȷ�����벻һ��
    }
}
