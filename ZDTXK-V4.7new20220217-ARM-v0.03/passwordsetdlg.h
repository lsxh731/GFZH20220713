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
	void okBtn_clicked();      //"ȷ��"�ۺ���
	void cancelBtn_clicked();  //"ȡ��"�ۺ���
	void clearBtn_clicked();   //"���"�ۺ���

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

	void rBtncurrpwd_clicked(); //"������"�ۺ���
	void rBtnnewpwd_clicked();  //"������"�ۺ���
	void rBtncheckpwd_clicked();//"����ȷ��"�ۺ���
public:
	void passwordLangChange();
	void getRoletype(int nRoletype);//add by 2020.08.15
private:
	void getDigitalKeyboardText(QPushButton *pushButton);//��ȡ���ּ�������(�ı�)
private:
	int m_iRoletype;//add by 2020.08.15
	int m_iCurrLineEdit;
	QString m_strcurrPwdfromfile;//���ļ���ȡ����MD5����
private:
	Ui::pwdSetDialog  *m_pUi;
	
};
#endif //PASSWORD_SET_DLG_H
