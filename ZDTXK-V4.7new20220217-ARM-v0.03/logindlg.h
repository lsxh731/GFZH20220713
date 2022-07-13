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
    void okBtn_clicked();    //“确定”槽函数
    void clearBtn_clicked(); //"清除"槽函数
    void cancelBtn_clicked();//"取消"槽函数

    void pushButton0_clicked();//"数字键0"槽函数
    void pushButton1_clicked();//"数字键1"槽函数
    void pushButton2_clicked();//"数字键2"槽函数
    void pushButton3_clicked();//"数字键3"槽函数
    void pushButton4_clicked();//"数字键4"槽函数
    void pushButton5_clicked();//"数字键5"槽函数
    void pushButton6_clicked();//"数字键6"槽函数
    void pushButton7_clicked();//"数字键7"槽函数
    void pushButton8_clicked();//"数字键8"槽函数
    void pushButton9_clicked();//"数字键9"槽函数
//	void adminradioBtn_clicked();//管理员角色槽函数 add by 2020.08.15
//	void engneerradioBtn_clicked();//工程师角色槽函数 add by 2020.08.15
//	void userradioBtn_clicked();//用户角色槽函数 add by 2020.08.15
public:
    int IsPWDCorrect();       //判断密码是否正确
    void loginLangChange();
private:
    bool readPwdFile(int nRoletype);       //读取密码配置文件(保存md5的密码)
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
