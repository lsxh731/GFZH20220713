/****************************************************************************
** CopyRight(c) 2017,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: plotyserclass.cpp
** ժҪ: ���ߴ��ڵ��û��Զ����picker��scaledraw��
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2017.12.10
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2017.12.10   V1.0      ����
**
****************************************************************************/

#include "plotuserclass.h"

//////////////////////////////////////////////////////////////////////////
//������ʱ�����д�����:  ��ʱ������ʾ/����ʾ����������ʽ
////////////////////////////////////////////////////////////////////////////
CTimeScaleDraw::CTimeScaleDraw(const QTime &base,int iMsecStep):baseTime(base)
{
	//���ݵ���벽�����룬��10����ʾ10����
	m_iMsecStep = iMsecStep;
	//m_nTimeType = TimeShowType::TIMESHOW_MSEC;
}

CTimeScaleDraw::~CTimeScaleDraw()
{
}

QwtText CTimeScaleDraw::label(double v) const
{
	//���㲢���ʱ���ַ�������ʾ�ں�������
	//��Ҫע�⣺�˴���char��ת����ʽ��������ʹ��QDateTime��toString�������ú���Ч�ʵ�
	char szTmpTime[30];
	memset(szTmpTime,0,sizeof(szTmpTime));
	QTime upTime = baseTime.addMSecs((int)((int)v)*m_iMsecStep);
	QString strTime;
	sprintf(szTmpTime, "%02d:%02d:%02d.%03d", upTime.hour(), 
		upTime.minute(), upTime.second(), upTime.msec());
	
	return QwtText(QString(szTmpTime));
}

//���û�׼ʱ��\���ݵ㵥λ����
void CTimeScaleDraw::setBaseTime(const QTime &base,const int &iMsecStep)
{
	baseTime = base;
	m_iMsecStep = iMsecStep;
	invalidateCache();//���ʱ�����겻��������
}

//��ȡ��׼ʱ��
QTime CTimeScaleDraw::getBaseTime()
{
	return baseTime;
}

//ʱ����ʾ����
void CTimeScaleDraw::setTimeShowType(const int &nTimeType)
{
	m_nTimeType = nTimeType;
}

//////////////////////////////////////////////////////////////////////////
//�����ٴ�����-��Ժ������¼�����
///////////////////////////////////////////////////////////////////////////
CTimePicker::CTimePicker(const QTime &base, int xAxis, int yAxis, 
			RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas *cavas):
			QwtPlotPicker (xAxis, yAxis, rubberBand, trackerMode, cavas),baseTime(base)
{
	m_nInterval = 20;
	
}

CTimePicker::~CTimePicker()
{

}

QwtText CTimePicker::trackerText (const QPoint & point) const
{
	QwtText text = QwtPlotPicker::trackerText(point);
	QString strText = text.text();

	double iXPos = strText.section(",",0,0).toDouble();
	double dValue = strText.section(",",1,1).toDouble();
	QString strLabel;
	char szTmpTime[30];
	memset( szTmpTime, 0, 30 );

	QTime upTime = baseTime.addMSecs((int)iXPos * m_nInterval);
	sprintf( szTmpTime, "%02d:%02d:%02d.%03d", upTime.hour(), upTime.minute(), upTime.second(), upTime.msec());
   
	strLabel.sprintf("%s", szTmpTime);
	QwtText showText(strLabel);
	return showText;
}

void CTimePicker::setBaseTime( const QTime &base,const int &nInterval)
{
	baseTime = base;
	m_nInterval = nInterval;
}

