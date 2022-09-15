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
	void updateProgressBarValue(int nValue);//更新进度条-槽函数
	void okBtn_clicked();//确定-槽函数
	void cancelBtn_clicked();//取消-槽函数
private:
	Ui::gainsetDialog  *m_pUi;
	int m_iCurrValue;   //当前值
public:
	int getGainSetValue();//获取增益设置值

};
#endif //GAIN_SET_DLG_H