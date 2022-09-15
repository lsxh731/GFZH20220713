#ifndef KEY_BOARD_DLG_H
#define KEY_BOARD_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_keyboard.h"
#include "commmacro.h"

namespace Ui
{
	class keyBoardDialog;
}
class CKeyBoardDlg:public QDialog
{
	Q_OBJECT
public:
	CKeyBoardDlg();
	~CKeyBoardDlg();
public Q_SLOTS:
	void okBtn_clicked();     //ȷ��-�ۺ���
	void cancelBtn_clicked(); //ȡ��-�ۺ���
	void clearBtn_clicked();  //���-�ۺ���
	

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
	void pointBtn_clicked();   //"С����"�ۺ���
	void nagBtn_clicked();     //"����"�ۺ���
public:
	bool getInputValue(float &fValue);//��ȡ����ֵ
	int setDatatype(int nDatatype);   //������������
	void disablePointAndNagBtn();     //���õ�ź͸��Ű�ť
	void keyboardLangChange();
private:
	void init();
	void getDigitalKeyboardText(QPushButton *pushButton);
private:
   QString m_strFriendlytips;//������ʾ��
     float m_fInputValue;   //����ֵ
	 bool m_ok;
private:
	Ui::keyBoardDialog  *m_pUi;
};
#endif //KEY_BOARD_DLG_H