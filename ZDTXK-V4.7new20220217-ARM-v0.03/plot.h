/****************************************************************************
** CopyRight(c) 2010,　北京交通大学
** All rights reserved
**
** 文件名称: plot.h
** 摘要: 曲线窗口
**       
**
** 当前版本: 4.0.0.0
** 作者:  聂晓波
** 完成日期: 2017.12.09
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2017.12.09   V4.0      创建
**
****************************************************************************/
#pragma once
#include <QMouseEvent>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_marker.h>

#include "plotuserclass.h"

//曲线处理类
class CPlot :public QwtPlot
{
	Q_OBJECT
public:
	CPlot(QWidget *pParent = NULL, 
			const int &nCurvesCount = 1, //曲线个数
			const int & nYAxisUsedMode = CPlot::YAxis_Left,	 //Y坐标使用类型
			const int & nXAxisMode = CPlot::XScale_Default,//X轴坐标模式
			const QString &strTitle = "",				 //PLOT名称
			const QColor &rcBackGround = QColor(Qt::black)); //背景颜色 //Qt::black  //lightGray
	~CPlot(void);

public:
	//Y坐标使用模式，分左坐标显示模式、右坐标显示模式、左右坐标显示模式
	enum
	{
		YAxis_Left = 0,//左坐标显示模式
		YAxis_Right,   //右坐标显示模式
		YAxis_LeftRight//左右坐标显示模式
	};

	//X坐标模式，分默认数值类、时间类、频率类
	enum
	{
		XScale_Default = 3,
		XScale_Time,
		XScale_RMSTime,
		XScale_Freq
	};

public slots:
signals:

public:
	//显示曲线
	void showCurve(const QTime &timeBegin,          //时间轴的基准时间
		           const int &nTimeInterval,        //时间间隔
				   const QString &strCurveTtile,	//曲线名称
				   const QString &strXAxisTitle,	//X轴标注
				   const QString &strYAxisTitle,	//Y轴标注
				   const QList<double> &lstYValue,  //Y轴数据值
				   QColor CurveColor);	            //X、Y轴数据值
private:
	void init();
	void init_Curve();               //创建单曲线对象
	void init_Curve(int nCurveCount);//创建多曲线对象
	void init_XAxis();
	void initZoomer();
private:
	QwtPlotCurve *m_pNewPlotCurve;
	QwtLegend *m_pLegend;
	QwtPlotGrid *m_pPlotGrid;	
	CZoomer *m_pZoomer;//缩放、跟踪、平移、游标

	CTimeScaleDraw *m_pXScalDraw;

	float m_dAxisMax;
	float m_dAxisMin;
	
	int m_nCurveCount;    //曲线个数
	int m_nYAxisUsedMode; //YAxis使用模式
	int m_nXAxisMode;     //X轴坐标模式

	QString m_strTitle;   //Plot Title
	QColor m_rcBackGround;//背景颜色
};
