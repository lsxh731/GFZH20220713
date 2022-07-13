#ifndef RUNNING_STATUS_WIDGET_H
#define RUNNING_STATUS_WIDGET_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_runningstatus.h"
#include "commmacro.h"
#include <QLabel>
namespace Ui
{
	class runningstatusForm;
}
class CRunningStatusWidget:public QDialog//QWidget
{
	Q_OBJECT
public:
	CRunningStatusWidget(QWidget * ptr);
	~CRunningStatusWidget();
	void initRunningStatus();
public Q_SLOTS:
	void closeBtn_clicked();//·µ»Ø¼ü²Ûº¯Êý add by 2020.08.10
public:
	void updateRunningStatusData(STRU_RUNNINGSTATUS *pRunningStaData);
	void runningLangChange();
private:
	void updateLabelColor(int nValue,int nIndex,int nCol,QLabel *greenlabel,QLabel *redlabel,QLabel *yellowlabel);
protected:
	void closeEvent(QCloseEvent *event);
private:
	STRU_RUNNINGSTATUS m_struRunStaData[MAX_SIZE];
	QWidget *m_pWidget;
private:
	Ui::runningstatusForm  *m_pUi;
};
#endif //RUNNING_STATUS_WIDGET_H