#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_login.h"
#include "commmacro.h"

namespace Ui
{
    class loginDialog;
}
class  CLogindlg:public QDialog
{
    Q_OBJECT
public:
    CLogindlg();
    ~CLogindlg();
public Q_SLOTS:
    void okBtn_clicked();    //��ȷ�����ۺ���
    void clearBtn_clicked(); //"���"�ۺ���
    void cancelBtn_clicked();//"ȡ��"�ۺ���

    void pushButton0_clicked();//"���ּ�0"�ۺ���
    void pushButton1_clicked();//"���ּ�1"�ۺ���
    void pushButton2_clicked();//"���ּ�2"�ۺ���
    void pushButton3_clicked();//"���ּ�3"�ۺ���
    void pushButton4_clicked();//"���ּ�4"�ۺ���
    void pushButton5_clicked();//"���ּ�5"�ۺ���
    void pushButton6_clicked();//"���ּ�6"�ۺ���
    void pushButton7_clicked();//"���ּ�7"�ۺ���
    void pushButton8_clicked();//"���ּ�8"�ۺ���
    void pushButton9_clicked();//"���ּ�9"�ۺ���
//	void adminradioBtn_clicked();//����Ա��ɫ�ۺ��� add by 2020.08.15
//	void engneerradioBtn_clicked();//����ʦ��ɫ�ۺ��� add by 2020.08.15
//	void userradioBtn_clicked();//�û���ɫ�ۺ��� add by 2020.08.15
public:
    int IsPWDCorrect();       //�ж������Ƿ���ȷ
    void loginLangChange();
private:
    bool readPwdFile(int nRoletype);       //��ȡ���������ļ�(����md5������)
private:
    Ui::loginDialog  *m_pUi;
    int m_bPwdCorrect;
    int m_iRoletype;//add by 2020.08.15
#ifdef WIN_DEV
    std::string m_strPwd;
#else
    QString m_strPwd;
#endif
};
#endif
