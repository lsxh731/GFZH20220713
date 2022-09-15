/****************************************************************************
** CopyRight(c) 2010,��������ͨ��ѧ
** All rights reserved
**
** �ļ�����: plotyserclass.h
** ժҪ: ���ߴ��ڵ��û��Զ����picker��scaledraw��
**       
**
** ��ǰ�汾: 4.0.0.0
** ����:  ������
** �������: 2011.10.25
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2011.10.25   V4.0      ����
**
****************************************************************************/
#pragma once
#include <QTime>
#include <qwt_scale_draw.h>
#include <qwt_plot_zoomer.h>
#include <QMouseEvent>

//////////////////////////////////////////////////////////////////////////
//������ʱ�����д�����:  ��ʱ������ʾ/����ʾ����������ʽ
////////////////////////////////////////////////////////////////////////////
class CTimeScaleDraw: public QwtScaleDraw
{
public:
	CTimeScaleDraw(const QTime &base,int iMsecStep);
	~CTimeScaleDraw();

public:
	virtual QwtText label(double v) const;

	//���û�׼ʱ��\���ݵ㵥λ����
	virtual void setBaseTime(const QTime &base,const int &iMsecStep);

	//��ȡ��׼ʱ��
	QTime getBaseTime();
	
	//ʱ����ʾ����
	void setTimeShowType(const int &nTimeType);
private:
	QTime baseTime;//��������ʼʱ��
	int m_iMsecStep;//���ݵ㵥λ����
	int m_nTimeType;//ʱ����ʾ���ͣ����TimeShowType�Ķ���
};

//////////////////////////////////////////////////////////////////////////
//�����ٴ�����-��Ժ�����ʱ������
///////////////////////////////////////////////////////////////////////////
class CTimePicker: public QwtPlotPicker
{
	Q_OBJECT

public:
	CTimePicker(const QTime &base, int xAxis, int yAxis, 
				RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas *cavas);
	~CTimePicker();

	virtual QwtText trackerText (const QPoint & point) const;

	virtual void setBaseTime( const QTime &base,const int &nInterval);
    	
public:
	QPoint m_CurrPoint;//��굱ǰλ��
	QTime baseTime;//��������ʼʱ��
	int m_nInterval;//ʱ����
};

//////////////////////////////////////////////////////////////////////////
//���Ŵ�����
//////////////////////////////////////////////////////////////////////////
class CZoomer: public QwtPlotZoomer
{
public:
	CZoomer(int xAxis, int yAxis, QwtPlotCanvas *canvas): QwtPlotZoomer(xAxis, yAxis, canvas)
	{
		setTrackerMode(QwtPicker::AlwaysOff);
		setRubberBand(QwtPicker::NoRubberBand);

		setMousePattern(QwtEventPattern::MouseSelect2,
			Qt::RightButton, Qt::ControlModifier);
		setMousePattern(QwtEventPattern::MouseSelect3,
			Qt::RightButton);
	}
};