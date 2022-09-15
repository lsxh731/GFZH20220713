/****************************************************************************
** CopyRight(c) 2017,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: plotyserclass.cpp
** 摘要: 曲线窗口的用户自定义的picker、scaledraw等
**       
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2017.12.10
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2017.12.10   V1.0      创建
**
****************************************************************************/

#include "plotuserclass.h"

//////////////////////////////////////////////////////////////////////////
//横坐标时间序列处理类:  暂时处理显示/不显示毫秒两种形式
////////////////////////////////////////////////////////////////////////////
CTimeScaleDraw::CTimeScaleDraw(const QTime &base,int iMsecStep):baseTime(base)
{
	//数据点毫秒步长输入，如10，表示10毫秒
	m_iMsecStep = iMsecStep;
	//m_nTimeType = TimeShowType::TIMESHOW_MSEC;
}

CTimeScaleDraw::~CTimeScaleDraw()
{
}

QwtText CTimeScaleDraw::label(double v) const
{
	//计算并组成时标字符串，显示在横坐标上
	//需要注意：此处用char来转换格式，不建议使用QDateTime的toString函数，该函数效率低
	char szTmpTime[30];
	memset(szTmpTime,0,sizeof(szTmpTime));
	QTime upTime = baseTime.addMSecs((int)((int)v)*m_iMsecStep);
	QString strTime;
	sprintf(szTmpTime, "%02d:%02d:%02d.%03d", upTime.hour(), 
		upTime.minute(), upTime.second(), upTime.msec());
	
	return QwtText(QString(szTmpTime));
}

//设置基准时间\数据点单位步长
void CTimeScaleDraw::setBaseTime(const QTime &base,const int &iMsecStep)
{
	baseTime = base;
	m_iMsecStep = iMsecStep;
	invalidateCache();//解决时间坐标不调整问题
}

//获取基准时间
QTime CTimeScaleDraw::getBaseTime()
{
	return baseTime;
}

//时间显示类型
void CTimeScaleDraw::setTimeShowType(const int &nTimeType)
{
	m_nTimeType = nTimeType;
}

//////////////////////////////////////////////////////////////////////////
//鼠标跟踪处理类-针对横坐标事件序列
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

