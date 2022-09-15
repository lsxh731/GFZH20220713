#ifndef GAIN_SET_DLG_H
#define GAIN_SET_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_gainset.h"

namespace Ui
{
	class gainsetDialog;
}
class CGainSetdlg:public QDialog
{
	Q_OBJECT
public:
	CGainSetdlg();
	~CGainSetdlg();
public Q_SLOTS:
	void updateProgressBarValue(int nValue);//���½�����-�ۺ���
	void okBtn_clicked();//ȷ��-�ۺ���
	void cancelBtn_clicked();//ȡ��-�ۺ���
private:
	Ui::gainsetDialog  *m_pUi;
	int m_iCurrValue;   //��ǰֵ
public:
	int getGainSetValue();//��ȡ��������ֵ

};
#endif //GAIN_SET_DLG_H