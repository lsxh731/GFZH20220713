#ifndef TEMPERATURE_MONITOR_WIDGET_H
#define TEMPERATURE_MONITOR_WIDGET_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_temperaturemonitor.h"
#include "commmacro.h"
namespace Ui
{
	class tempermonitorForm;
}
class CTempMonitorWidget:public QDialog//QWidget
{
	Q_OBJECT
public:
	CTempMonitorWidget(QWidget * ptr);
	~CTempMonitorWidget();
public Q_SLOTS:
	void temperLangChange();
	void sub1Btn_clicked();            //�ֹ���Ϣҳ��-�ֹ�1�л��ۺ���,add by 2020.04.18
	void sub2Btn_clicked();            //�ֹ���Ϣҳ��-�ֹ�2�л��ۺ���,add by 2020.04.18
	void sub3Btn_clicked();            //�ֹ���Ϣҳ��-�ֹ�3�л��ۺ���,add by 2020.04.18
	void sub4Btn_clicked();            //�ֹ���Ϣҳ��-�ֹ�4�л��ۺ���,add by 2020.04.18
	void closeBtn_clicked();           //���ؼ��ۺ�����add by 2020.08.10
public:
	void updateTemperatureData(STRU_IGBTTEMPERATUREMONI *pStruIGBTTemperData,STRU_IDUCTTEMPERATUREMONI *pStruIDUCTTemperData,STRU_INPUTDCVOLTAGEMONI *pStruDCInputVoltageData);
private:
	void init();
protected:
     void closeEvent(QCloseEvent *event);
private:
	STRU_IGBTTEMPERATUREMONI m_struIGBTTemperData[MAX_SIZE];
	STRU_IDUCTTEMPERATUREMONI m_struIDUCTTemperData[MAX_SIZE];
	STRU_INPUTDCVOLTAGEMONI m_struDCInputVoltageData[MAX_SIZE];
	 QWidget *m_pWidget;
private:
	Ui::tempermonitorForm  *m_pUi;

};
#endif //TEMPERATURE_MONITOR_WIDGET_H