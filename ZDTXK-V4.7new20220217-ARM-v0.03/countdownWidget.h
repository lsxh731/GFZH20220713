#ifndef COUNT_DOWN_WIDGET_H
#define COUNT_DOWN_WIDGET_H

#include <QObject>
#include <QDialog>
#include "ui_countdown.h"
#include "commmacro.h"
#include <QLabel>
namespace Ui
{
	class countdownForm;
}
class CCountDownWidget:public QDialog//QWidget
{
	Q_OBJECT
public:
	CCountDownWidget();
	~CCountDownWidget();
public Q_SLOTS:
public:
	void showRemainingTime(int nSecond);//显示剩余时间(单位秒)
	void countdownLangChange();
private:
	
private:
	Ui::countdownForm  *m_pUi;
};
#endif //RUNNING_STATUS_WIDGET_H