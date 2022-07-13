/****************************************************************************
** CopyRight(c) 2010,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: plot.cpp
** 摘要: 曲线绘制类
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
** 聂晓波      2017.12.09   V4.0     单坐标单曲线版本
**
****************************************************************************/

#include "plot.h"

#include <qwt_scale_engine.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_picker_machine.h>
#include <qwt_double_range.h>
#include "commmacro.h"


CPlot::CPlot(QWidget *pParent, 
	const int &nCurvesCount, 
	const int & nYAxisUsedMode,	 
	const int & nXAxisMode ,
	const QString &strTitle ,				 
	const QColor &rcBackGround )
	 :QwtPlot(pParent),
			 m_nCurveCount(nCurvesCount),
			 m_nYAxisUsedMode(nYAxisUsedMode),
			 m_nXAxisMode(nXAxisMode),
			 m_strTitle(strTitle),
			 m_rcBackGround(rcBackGround)
{
	m_dAxisMax=0.00;
	m_dAxisMin=0.00;
	m_pNewPlotCurve=NULL;
	m_pZoomer = NULL;
	m_pXScalDraw=NULL;
	init();
}

CPlot::~CPlot(void)
{
	/*if (m_pXScalDraw != NULL)
	{
	delete m_pXScalDraw;
	m_pXScalDraw = NULL;
	}
	if (m_pZoomer != NULL)
	{
	delete m_pZoomer;
	m_pZoomer = NULL;
	}
	if (m_pNewPlotCurve!=NULL)
	{
	delete m_pNewPlotCurve;
	m_pNewPlotCurve=NULL;
	}*/

}
//初始化Plot曲线界面元素
void CPlot::init()
{
	//设置画布背景色
	setCanvasBackground(Qt::gray);
	
	//创建图例
	m_pLegend = new QwtLegend();
	insertLegend(m_pLegend, QwtPlot::TopLegend);

	//背景表格
	m_pPlotGrid = new QwtPlotGrid();
	m_pPlotGrid->enableXMin(false);
	m_pPlotGrid->setMajPen(QPen(Qt::white, 0, Qt::DotLine));
	m_pPlotGrid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
	m_pPlotGrid->attach(this);
	init_XAxis();
	init_Curve(m_nCurveCount);
	initZoomer();
	
}

void CPlot::showCurve(const QTime &timeBegin,       //时间轴的基准时间
	                  const int &nTimeInterval,     //时间间隔
					  const QString &strCurveTtile,	//曲线名称
					  const QString &strXAxisTitle,	//X轴标注
					  const QString &strYAxisTitle,	//Y轴标注
					  const QList<double> &lstYValue,//Y轴数据值
					  QColor CurveColor)	//X、Y轴数据值
{
	
	int nAxisID = QwtPlot::yLeft;

	if (NULL==m_pXScalDraw)
	{
		return;
	}

	((CTimeScaleDraw*)m_pXScalDraw)->setBaseTime(timeBegin,nTimeInterval);

	//设置曲线颜色
	QPen pen = m_pNewPlotCurve->pen();
	pen.setColor(CurveColor);
	pen.setWidth(1);
	m_pNewPlotCurve->setPen(pen);
	m_pNewPlotCurve->attach(this);	

	//获取当前显示的曲线对象
	m_pNewPlotCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化 
	
	//Y轴坐标title
	QwtText yText(strYAxisTitle);
	yText.setFont(QFont("Helvetica", 10, QFont::DemiBold));
	yText.setColor(Qt::red);
	setAxisTitle(nAxisID,yText);

	QVector<QPointF> vector;
	QPointF point;

	//确定y轴最值
	int nIndex=0;
	int nXScale=lstYValue.size();
	for (nIndex=0;nIndex<lstYValue.size();nIndex++)
	{
		point.setX(nIndex);	
		point.setY(lstYValue[nIndex]);
		vector.append(point);
		m_dAxisMax=lstYValue[0];
		m_dAxisMin=lstYValue[0];
		if(lstYValue[nIndex]>m_dAxisMax)
		{
			m_dAxisMax = lstYValue[nIndex];//统计最大值 
		}
		if (lstYValue[nIndex]<m_dAxisMin)
		{
			m_dAxisMin = lstYValue[nIndex];//统计最小值 
		}
	}
	
	setAxisScale(QwtPlot::xBottom,0.0,nXScale);
	if ((fabs(m_dAxisMin)<1.00)&&(fabs(m_dAxisMax)<1.00))
	{
		setAxisScale(QwtPlot::yLeft,m_dAxisMin-1.00,m_dAxisMax+1.00);
	}
	else
	{
		setAxisScale(QwtPlot::yLeft,m_dAxisMin*0.95,m_dAxisMax*1.05);
	}
	//设置曲线title
	QwtText title(strCurveTtile);
	title.setFont(QFont("Helvetica", 11, QFont::Bold));
	title.setColor(QColor(Qt::black));
	m_pNewPlotCurve->setTitle(title);

	//坐标数据值
	m_pNewPlotCurve->setSamples(vector);
	m_pNewPlotCurve->attach( this );
	m_pNewPlotCurve->setLegendAttribute(m_pNewPlotCurve->LegendShowLine);//显示图例的标志，这里显示线的颜色

	replot();
	setAutoReplot( true );//设置自动重画，相当于更新

	//QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotCurve );//获取画了多少条曲线,如果为获取其他形状，注意改变参数  
	//  qDebug()<<items;  

}
void CPlot::init_XAxis()
{
	m_pXScalDraw = NULL;
	m_pXScalDraw = new CTimeScaleDraw(QTime::currentTime(),INTERVAL); 
	setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
	setAxisScaleDraw(QwtPlot::xBottom, m_pXScalDraw);//X轴时间信息
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom);

	//-----------设置x，y坐标和范围--------------//
	setAxisTitle( QwtPlot::yLeft, "ylabel" );
	setAxisTitle( QwtPlot::xBottom, "" );
	setAxisScale(QwtPlot::yLeft,-10.0,10.0);
	setAxisScale(QwtPlot::xBottom,0.0,1000.0);

}
//创建单条曲线对象
void CPlot::init_Curve()
{
	m_pNewPlotCurve = new QwtPlotCurve();
	m_pNewPlotCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
	m_pNewPlotCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
	QPen pen = m_pNewPlotCurve->pen();
	pen.setColor(Qt::red);
	pen.setWidth(1);
	m_pNewPlotCurve->setPen(pen);
	m_pNewPlotCurve->attach(this);	
	setAxisAutoScale(QwtPlot::yLeft, true);
}
//创建多条曲线对象
void CPlot::init_Curve(int nCurveCount)
{
	QwtPlotCurve *pNew = NULL;

	for(int nIndex = 0; nIndex < nCurveCount; nIndex++)
	{
		pNew = new QwtPlotCurve();
		pNew->setRenderHint(QwtPlotItem::RenderAntialiased);
		pNew->setLegendAttribute(QwtPlotCurve::LegendShowLine);
		QPen pen = pNew->pen();
		pen.setColor(Qt::red);
		pen.setWidth(1);
		pNew->setPen(pen);
		pNew->attach(this);
	}
   setAxisAutoScale(QwtPlot::yLeft, true);
}
//缩放初始化
void CPlot::initZoomer()
{
	//左坐标对应曲线缩放
	if (m_pZoomer != NULL)
	{
		delete m_pZoomer;
		m_pZoomer = NULL;
	}

	//m_pZoomer = new CZoomer( QwtPlot::xBottom, QwtPlot::yLeft, this->canvas());
	//m_pZoomer->setRubberBand(QwtPicker::RectRubberBand);
	//m_pZoomer->setRubberBandPen(QColor(Qt::green));
	//m_pZoomer->setTrackerMode(QwtPicker::ActiveOnly);
	//m_pZoomer->setTrackerPen(QColor(Qt::transparent));	
	////设置曲线缩放基础区域(避免重新绘制新曲线后，曲线记忆原有曲线坐标区域)此属性一定要加
	//m_pZoomer->setZoomBase(true);                 
}

	









