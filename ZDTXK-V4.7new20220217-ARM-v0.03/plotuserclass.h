/****************************************************************************
** CopyRight(c) 2010,　北京交通大学
** All rights reserved
**
** 文件名称: plotyserclass.h
** 摘要: 曲线窗口的用户自定义的picker、scaledraw等
**       
**
** 当前版本: 4.0.0.0
** 作者:  聂晓波
** 完成日期: 2011.10.25
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2011.10.25   V4.0      创建
**
****************************************************************************/
#pragma once
#include <QTime>
#include <qwt_scale_draw.h>
#include <qwt_plot_zoomer.h>
#include <QMouseEvent>

//////////////////////////////////////////////////////////////////////////
//横坐标时间序列处理类:  暂时处理显示/不显示毫秒两种形式
////////////////////////////////////////////////////////////////////////////
class CTimeScaleDraw: public QwtScaleDraw
{
public:
	CTimeScaleDraw(const QTime &base,int iMsecStep);
	~CTimeScaleDraw();

public:
	virtual QwtText label(double v) const;

	//设置基准时间\数据点单位步长
	virtual void setBaseTime(const QTime &base,const int &iMsecStep);

	//获取基准时间
	QTime getBaseTime();
	
	//时间显示类型
	void setTimeShowType(const int &nTimeType);
private:
	QTime baseTime;//横坐标起始时间
	int m_iMsecStep;//数据点单位步长
	int m_nTimeType;//时间显示类型，相见TimeShowType的定义
};

//////////////////////////////////////////////////////////////////////////
//鼠标跟踪处理类-针对横坐标时间序列
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
	QPoint m_CurrPoint;//鼠标当前位置
	QTime baseTime;//横坐标起始时间
	int m_nInterval;//时间间隔
};

//////////////////////////////////////////////////////////////////////////
//缩放处理类
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