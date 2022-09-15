#ifndef PASSWORD_SET_DLG_H
#define PASSWORD_SET_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_passwordset.h"

namespace Ui
{
	class pwdSetDialog;
}
class CPasswordSetdlg:public QDialog
{
	Q_OBJECT
public:
	CPasswordSetdlg();
	~CPasswordSetdlg();
public Q_SLOTS:
	void okBtn_clicked();      //"确定"槽函数
	void cancelBtn_clicked();  //"取消"槽函数
	void clearBtn_clicked();   //"清除"槽函数

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

	void rBtncurrpwd_clicked(); //"旧密码"槽函数
	void rBtnnewpwd_clicked();  //"新密码"槽函数
	void rBtncheckpwd_clicked();//"密码确认"槽函数
public:
	void passwordLangChange();
	void getRoletype(int nRoletype);//add by 2020.08.15
private:
	void getDigitalKeyboardText(QPushButton *pushButton);//获取数字键盘数字(文本)
private:
	int m_iRoletype;//add by 2020.08.15
	int m_iCurrLineEdit;
	QString m_strcurrPwdfromfile;//从文件获取到的MD5密码
private:
	Ui::pwdSetDialog  *m_pUi;
	
};
#endif //PASSWORD_SET_DLG_H
