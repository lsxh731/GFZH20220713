/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: hiscurveWidget.h
** ժҪ: ��ʷ���߻��ƴ���
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2019.01.27
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2019.01.27   V1.0      ����
**
****************************************************************************/
#ifndef HISCURVE_WIDGET_H
#define HISCURVE_WIDGET_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_hiscurve.h"
#include <QMap>
#include "hisCurvePlot.h"

namespace Ui
{
	class hiscurveForm;
}
class CHiscurveWidget:public QDialog//QWidget
{
	Q_OBJECT
public:
	CHiscurveWidget();
	~CHiscurveWidget();
public Q_SLOTS:
	void comboBox_clicked(int nIndex);//��������ѡ��
	void queryBtn_clicked();          //��ѯ����-�ۺ���
	void loadBtn_clicked();           //�����ļ�-�ۺ���
	void totalvolt_clicked();         //"�������ѹ"-�ۺ���
	void totalcurr_clicked();         //"���������"-�ۺ���
	void excitvolt_clicked();         //"���ŵ�ѹ"-�ۺ���
	void excitcurr_clicked();         //"���ŵ���"-�ۺ���
	void PhaseAVolt_clicked();        //"A���ѹ"-�ۺ���
	void PhaseBVolt_clicked();        //"B���ѹ"-�ۺ���
	void PhaseCVolt_clicked();        //"C���ѹ"-�ۺ���
	void AllChoose_clicked();         //"ȫѡ"-�ۺ���
	void closeBtn_clicked();           //"����"-�ۺ��� add by 2020.08.10
	void recoverBtn_clicked();       //"���߸�ԭ"-�ۺ��� add by 2020.11.11

public:
	void hiscurvelangchange();        //��ʷ���߽��������л�
private:
	void initVecData();                  //��ʼ��������������������
	void initDataAndCurve();             //��ʼ�����ݺ�����
	void parseData(QStringList linelist);//��������
private:
	 WamsPlot *m_pWamsPlot;              //�����߶���ָ��
	 QTime m_tmBasetime;                 //��׼ʱ��
	 QList<double>m_vec_fTotalVolt;   //����������ѹ���ݵ�����(����)
	 QList<double>m_vec_fTotalCurrent;//���������������ݵ�����(����)
	 QList<double>m_vec_fExcitVolt;   //������ŵ�ѹ���ݵ�����(����)
	 QList<double>m_vec_fExcitCurrent;//������ŵ������ݵ�����(����)
	 QList<double>m_vec_fPhaseAVolt;  //���A���ѹ���ݵ�����(����)
	 QList<double>m_vec_fPhaseBVolt;  //���B���ѹ���ݵ�����(����)
	 QList<double>m_vec_fPhaseCVolt;  //���C���ѹ���ݵ�����(����)
	 QString m_strTotalVoltTitle;     //�������ѹ���߱���
	 QString m_strTotalCurrentTitle;  //������������߱���
	 QString m_strExcitVoltTitle;     //���ŵ�ѹ���߱���
	 QString m_strExcitCurrentTitle;  //���ŵ������߱���
	 QString m_strPhaseAVoltTitle;    //A���ѹ���߱���
	 QString m_strPhaseBVoltTitle;    //B���ѹ���߱���
	 QString m_strPhaseCVoltTitle;    //C���ѹ���߱���
	 QMap<QString, int>m_mapDatatype; //��������map
	 bool m_isChkTotalVolt;
	 bool m_isChkTotalCurrent;
	 bool m_isChkExcitVolt;
	 bool m_isChkExcitCurrent;
	 bool m_isChkPhaseAVolt;
	 bool m_isChkPhaseBVolt;
	 bool m_isChkPhaseCVolt;
	 bool m_isChkAll;
	  int m_nDataTypeNum;               //������������
	  int m_nCurrentTypeNum;            //������������,add by zqc 2019.07.03
private:
	Ui::hiscurveForm  *m_pUi;
};
#endif //HISCURVE_WIDGET_H