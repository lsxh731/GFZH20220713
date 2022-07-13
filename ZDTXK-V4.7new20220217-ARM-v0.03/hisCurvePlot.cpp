/****************************************************************************
** CopyRight(c) 2018,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: hisCurvePlot.cpp
** 摘要: QWT曲线重载类声明	
**       
**
** 当前版本: 1.0.0  2018-8-31
** 作者:   聂晓波
**
** 取代版本:
** 作者:
** 完成日期：2018-8-31
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　描述
** 聂晓波      2018-8-31   v1.0.0    创建版本
** 聂晓波	   2018-12-22  v1.1.0    单坐标多条曲线版本
****************************************************************************/
#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_text.h>
#include <qwt_plot_layout.h>
#include <qdatetime.h>
#include <qwt_scale_widget.h>
#include <qwt_painter.h>

#include "hisCurvePlot.h"
#include "commmacro.h"
#include <QSizePolicy>
#include <QMessageBox>
#include <QMouseEvent>

#define MIN_Y_AXIS_LENGTH 60  //纵坐标宽度

//曲线重载类构造函数
WamsPlot::WamsPlot(int iCurveNum, QWidget *parent,int YModeType, int iChartNo) : QwtPlot(parent)
{
	if ( iCurveNum > 18 )
	{
		return;
	}
	m_iCurveNum = iCurveNum;
	m_iChartNo = iChartNo;

	setMouseTracking(true);
	
	//设置页边距,canvas与frame
	//setMargin(0);
	//设置canvas随scale变动
	plotLayout()->setAlignCanvasToScales(true);
	//设置曲线标题
	setCanvasBackground(QColor(Qt::darkBlue));//Qt::darkBlue

    //创建网格
    m_grid = new QwtPlotGrid;
    m_grid->enableXMin(true);
    m_grid->setMajPen(QPen(QBrush(QColor(85, 85, 0)), 0, Qt::DotLine));
    m_grid->setMinPen(QPen(QBrush(QColor(85, 85, 0)), 0, Qt::DotLine));
    m_grid->attach(this);
	//创建极值标记线（左最小、左最大、右最小、右最大,共四个）
    m_mrk_min = new QwtPlotMarker();
    m_mrk_min->setLineStyle(QwtPlotMarker::HLine);
    m_mrk_min->setLabelAlignment(Qt::AlignLeft| Qt::AlignTop);
    m_mrk_min->setLinePen(QPen(QColor(Qt::yellow), 0, Qt::DashDotLine));
	//设置样本点的颜色、大小   
	QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Diamond,QBrush( Qt::yellow ), QPen( Qt::green, 2 ), QSize( 7, 7) );
    m_mrk_min->attach(this);

    m_mrk_max = new QwtPlotMarker();
    m_mrk_max->setLineStyle(QwtPlotMarker::HLine);
    m_mrk_max->setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
    m_mrk_max->setLinePen(QPen(QColor(Qt::yellow), 0, Qt::DashDotLine));
    m_mrk_max->attach(this);

	//拉杆
	m_mrk_vertical = new QwtPlotMarker();
	m_mrk_vertical->setLineStyle(QwtPlotMarker::VLine);
	m_mrk_vertical->setLabelAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_mrk_vertical->setLinePen(QPen(QColor(Qt::cyan), 0, Qt::DashDotLine));
	m_mrk_vertical->attach(this);
	m_mrk_vertical->hide();

	//将曲线改为自动重绘
    setAutoReplot(true);
	//初始化游标以及曲线缩放等功能
	initZoomAndPicker();
	

	//初始化x轴和y轴
	d_x = new double[iDATA_COUNT_MAX];
	for(int i = 0; i < iDATA_COUNT_MAX; i++)
	{
		d_x[i] = i;
	}
	//左轴曲线变量初始化
	m_dLeftYValue = new double*[m_iCurveNum-2];
	for ( int i=0; i<m_iCurveNum-2; i++ )
	{
		m_dLeftYValue[i] = new double[iDATA_COUNT_MAX];
		for(int k = 0; k < iDATA_COUNT_MAX; k++)
		{
			m_dLeftYValue[i][k] = QWT_NULL_POINT;
		}
	}
	//右轴曲线变量初始化,add by 2019.07.02
	m_dRightYValue = new double*[2];
	for ( int i=0; i<2; i++ )
	{
		m_dRightYValue[i] = new double[iDATA_COUNT_MAX];
		for(int k = 0; k < iDATA_COUNT_MAX; k++)
		{
			m_dRightYValue[i][k] = QWT_NULL_POINT;
		}
	}

	switch(YModeType)
	{
	case 0:
		setAxisScale(QwtPlot::yLeft, 0, 1000); //初始化左-y轴坐标为0-1000
		break;
	case 1:
		setAxisScale(QwtPlot::yRight, 0, 1000);//初始化右-y轴坐标为0-1000
		break;
	case 2:
		setAxisScale(QwtPlot::yLeft, 0, 1000); //初始化左-y轴坐标为0-1000
		setAxisScale(QwtPlot::yRight, 0, 1000);//初始化右-y轴坐标为0-1000
		break;
	}
	m_timeScaleDraw = new CTimeScaleDraw( QTime::currentTime(), 1000 );
	setAxisScaleDraw( QwtPlot::xBottom, m_timeScaleDraw );
	setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom );

	//创建左轴对应曲线5条
	m_crvLeft = new QwtPlotCurve[iCurveNum-2];
	//创建右轴对应曲线2条
	m_crvRight =new QwtPlotCurve[2];
	switch(YModeType)
	{
	case YLEFT_MODE:
		break;//左轴
	case YRIGHT_MODE:
		break;//右轴
	case YLEFTRIGHT_MODE:
		{
		   int i=0;
		   for ( i=0; i<iCurveNum-2; i++ )
	       {
		     m_crvLeft[i].setTitle("test"+QString("%1").arg( i+1));
		     m_crvLeft[i].setPen(QPen(QColor(g_curveColor[i])));//前5个颜色值
		     m_crvLeft[i].setYAxis(QwtPlot::yLeft);//电压数据曲线放左轴
		     m_crvLeft[i].attach(this);
		     m_crvLeft[i].setRawSamples(d_x, m_dLeftYValue[i], iDATA_COUNT_MAX);
		     //m_crvLeft[i].setLegendAttribute(m_crvLeft[i].LegendShowLine);//显示图例的标志，这里显示线的颜色。
	       }//for ( i=0; i<iCurveNum-2; i++ )
		   int j=0;
		   for ( j=0; j<2; j++ )
	       {
		     m_crvRight[j].setTitle("test"+QString("%1").arg( j+1));
		     m_crvRight[j].setPen(QPen(QColor(g_curveColor[j+5])));//后2个颜色值
		     m_crvRight[j].setYAxis(QwtPlot::yRight);//电流数据曲线放右轴
		     m_crvRight[j].attach(this);
		     m_crvRight[j].setRawSamples(d_x, m_dRightYValue[j], iDATA_COUNT_MAX);
		     //m_crvRight[j].setLegendAttribute(m_crvRight[j].LegendShowLine);//显示图例的标志，这里显示线的颜色。
	       }//for ( j=0; j<2; j++ )
		}
		break;//左右轴
	}
	//初始化数据点个数
	m_iPointCount = iDATA_COUNT_MAX;
	//左轴曲线相关值初始化
	m_dLeftMax = new double[m_iCurveNum-2];
	m_dLeftMin = new double[m_iCurveNum-2];
	m_iLeftMaxID = new int[m_iCurveNum-2];
	m_iLeftMinID = new int[m_iCurveNum-2];
	for ( int i=0; i<m_iCurveNum-2; i++ )
	{
		m_dLeftMax[i] = -QWT_NULL_POINT;
		m_dLeftMin[i] = QWT_NULL_POINT;
		m_iLeftMaxID[i] = -1;
		m_iLeftMinID[i] = -1;
	}
    //右轴曲线相关值初始化,add by 2019.07.02
	m_dRightMax = new double[2];
	m_dRightMin = new double[2];
	m_iRightMaxID = new int[2];
	m_iRightMinID = new int[2];
	for ( int j=0; j<2; j++ )
	{
		m_dRightMax[j] = -QWT_NULL_POINT;
		m_dRightMin[j] = QWT_NULL_POINT;
		m_iRightMaxID[j] = -1;
		m_iRightMinID[j] = -1;
	}
	switch(YModeType)
	{
	case 0:
		{
		  QwtScaleDraw *yLeftAxis = new QwtScaleDraw;
	      yLeftAxis->setMinimumExtent(MIN_Y_AXIS_LENGTH);
	      setAxisScaleDraw( QwtPlot::yLeft, yLeftAxis );
		}
		break;//左轴
	case 1:
		{
		  QwtScaleDraw *yRightAxis = new QwtScaleDraw;
	      yRightAxis->setMinimumExtent(MIN_Y_AXIS_LENGTH);
	      setAxisScaleDraw( QwtPlot::yRight, yRightAxis );
		}
		break;//右轴
	case 2:
		{
		   QwtScaleDraw *yLeftAxis = new QwtScaleDraw;
	      yLeftAxis->setMinimumExtent(MIN_Y_AXIS_LENGTH);
	      setAxisScaleDraw( QwtPlot::yLeft, yLeftAxis );

		  QwtScaleDraw *yRightAxis = new QwtScaleDraw;
	      yRightAxis->setMinimumExtent(MIN_Y_AXIS_LENGTH);
	      setAxisScaleDraw( QwtPlot::yRight, yRightAxis );
		}
		break;
	}//switch(YModeType)
	
	enableAxis(QwtPlot::yLeft,true); //允许左轴可以显示,add by zqc 2019.07.02
	enableAxis(QwtPlot::yRight,true);//允许右轴可以显示,add by zqc 2019.07.02
	//防止曲线放大时曲线分列成许多条 
	QwtPainter::setPolylineSplitting(false); 

	setMinimumHeight(150);
	setMinimumWidth(150);

	QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(1));
	setSizePolicy(sizePolicy2);
}
/*****************************************************************
* 功  能：析构函数
* 输  入：无
* 输  出：无
* 返回值：无
******************************************************************/
WamsPlot::~WamsPlot()
{
	if(m_mrk_vertical!=NULL)
	{
		delete m_mrk_vertical;
		m_mrk_vertical=NULL;
	}
	delete []m_crvRight;
	delete []m_crvLeft;

	
	//右轴曲线指针析构,add by 2019.07.02
	for ( int j=0;j<2; j++ )
	{
		delete []m_dRightYValue[j];
	}
	if(m_dRightYValue != NULL)
	{
		delete m_dRightYValue;
	}
	delete []m_dRightMax;
	delete []m_dRightMin;
	delete []m_iRightMaxID;
	delete []m_iRightMinID;
	
	//左轴曲线指针析构
	for ( int i=0; i<m_iCurveNum-2; i++ )
	{
		delete []m_dLeftYValue[i];
	}
	if(m_dLeftYValue != NULL)
	{
		delete m_dLeftYValue;
	}
	delete []m_dLeftMax;
	delete []m_dLeftMin;
	delete []m_iLeftMaxID;
	delete []m_iLeftMinID;

	delete []d_x;
}

//点击图例，显示相应的曲线
void WamsPlot::showItem(const QVariant &itemInfo, bool on)
{
   /* QwtPlotItem *plotItem =infoToItem(itemInfo);
    if (plotItem)
        plotItem->setVisible( on );*/

}
/*****************************************************************
* 功  能：初始化缩放、移动等功能
* 输  入：无
* 输  出：无
* 返回值：无
******************************************************************/
void WamsPlot::initZoomAndPicker()
{
	//左坐标对应曲线缩放
	m_zoomer = new CZoomer( QwtPlot::xBottom, QwtPlot::yLeft, this->canvas());
	m_zoomer->setRubberBand(QwtPicker::RectRubberBand);
	m_zoomer->setRubberBandPen(QColor(Qt::green));
	m_zoomer->setTrackerMode(QwtPicker::ActiveOnly);
	m_zoomer->setTrackerPen(QColor(Qt::white));	
	m_zoomer->setZoomBase(false);	//设置曲线缩放基础区域（避免重新绘制新曲线后,曲线记忆原有曲线坐标区域）--------此属性一定要加!!!!!!!!!!!!!!

	//按鼠标中键移动曲线
	m_panner = new QwtPlotPanner(this->canvas());
	m_panner->setMouseButton(Qt::MidButton);

	//精确找点标记,选中后显示“十”字定位测点
	/*m_picker = new QwtTimePicker(QTime::currentTime(), QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPicker::PointSelection | QwtPicker::DragSelection, 
		QwtPlotPicker::CrossRubberBand, 
		QwtPicker::AlwaysOn, 
		this->canvas());*/
	/*m_picker->setRubberBandPen(QColor(Qt::green));
	m_picker->setRubberBand(QwtPicker::NoRubberBand);
	m_picker->setTrackerPen(QColor(Qt::white));
	m_picker->setTrackerMode(QwtPicker::AlwaysOn);
	m_picker->setEnabled(true);*/

	//确定好数据点时,响应画刻度的事件响应
	//connect(m_picker,SIGNAL(sendXPos(int)),this,SLOT(setVerticalMark(int)));//add by zqc 2010.03.11
	//connect( m_zoomer, SIGNAL(zoomed(const QwtDoubleRect &)), this, SLOT(sendZoomInfo( const QwtDoubleRect & )) );

}
/*****************************************************************
* 功  能：初始化曲线数据
* 输  入：iCurveNum:曲线数；iDataCount：曲线点数
* 输  出：无
* 返回值：无
******************************************************************/
void WamsPlot::initCurveData( int iDataCount )
{
	if(m_iPointCount == iDataCount)
		return;  
	m_iPointCount = iDataCount;	
}
/*****************************************************************
* 功  能：绘制曲线函数
* 输  入：iCurIndex:曲线号码；startTime:坐标起始时间；dValue：曲线数值；iCount：曲线点数
* 输  出：无
* 返回值：无
******************************************************************/
void WamsPlot::showData(int iCurIndex, QTime startTime,int iYMode, double *dValue, QString strTitle,int iCount)
{
	if ( iCurIndex > m_iCurveNum )
	{
		return;
	}

	m_startTime = startTime;
	m_timeScaleDraw->setBaseTime(startTime,1000);
	if(iYMode==YLEFT_MODE)
	{
		//绘制曲线1（x轴+左轴）
	   if ( dValue != NULL )
	   { 
		for ( int i=0; i<iCount; i++ )
		{
			m_dLeftYValue[iCurIndex][i] = dValue[i];
		}
		setAxisScale( QwtPlot::xBottom, d_x[0], d_x[iCount-1] );
	   } 
	   m_crvLeft[iCurIndex].setTitle(strTitle);//更新曲线标题 2019.03.31
	}
	else if(iYMode==YRIGHT_MODE)
	{
		//绘制曲线2（x轴+右轴）
	   if ( dValue != NULL )
	   { 

		for ( int i=0; i<iCount; i++ )
		{
			m_dRightYValue[iCurIndex][i] = dValue[i];
		}
		setAxisScale( QwtPlot::xBottom, d_x[0], d_x[iCount-1] );
	   }  
	   //m_crvRight[iCurIndex].setTitle(strTitle);//更新曲线标题 2019.03.31
	}
	
	m_mrk_vertical->hide();//20100725, add by wanghua,避免第一次查询历史曲线时,显示了游标,在第二次查询历史数据时还显示上次的游标
	m_zoomer->setZoomBase(true);//不能去掉   
}

/*****************************************************************
* 功  能：显示峰值标记函数（dLeftvalue为无效数时,显示右侧曲线峰值标记,反之显示左侧曲线峰值标记）
* 输  入：峰值对应时间szTime,x轴数值dTime,左轴y1数值dLeftvalue,右轴y2数值dRightvalue
* 输  出：无
* 返回值：无
******************************************************************/
void WamsPlot::showPeak( const char *szTime, double dTime, double dValue )
{
	//如果左、右曲线值都为无效,返回
	if ( dValue > QWT_NULL_POINT/10.0  )
	{
		return;
	}
 
	QString label;
	
	//标记文字格式化
	label.sprintf("时间:%s, 最大值: %.2f ",szTime,dValue );

	//设置文字内容、字体、颜色
	QwtText text(tr(label.toLatin1()));
	text.setFont(QFont("Helvetica", 10, QFont::Bold));
	text.setColor(QColor(Qt::cyan));

	//标记线赋值（确定绘制位置）、设置文本标签
	m_mrk_max->setValue(dTime, dValue);
	m_mrk_max->setLabel(text);	
}

/*****************************************************************
* 功  能：显示谷值标记函数（dLeftvalue为无效数时,显示右侧曲线谷值标记,反之显示左侧曲线谷值标记）
* 输  入：峰值对应时间szTime,x轴数值dTime,左轴y1数值dLeftvalue,右轴y2数值dRightvalue
* 输  出：无
* 返回值：无
******************************************************************/
void WamsPlot::showPaddy(const char *szTime, double dTime, double dValue)
{
	//如果左、右曲线值都为无效,返回
	if ( dValue > QWT_NULL_POINT/10.0 )
	{
		return;
	}
 
	QString label;
	//如果左曲线值为无效,显示右曲线极值标记
	
	//标记文字格式化
	label.sprintf("时间:%s, 最小值: %.2f ",szTime,dValue );

	//设置文字内容、字体、颜色
	QwtText text(tr(label.toLatin1()));
	text.setFont(QFont("Helvetica", 10, QFont::Bold));
	text.setColor(QColor(Qt::cyan));

	//标记线赋值（确定绘制位置）、设置文本标签
	m_mrk_min->setValue(dTime, dValue);
	m_mrk_min->setLabel(text);	
}

/*****************************************************************
* 功  能：隐藏左曲线极值标记
* 输  入：bool bLeftMark,值为true表示隐藏,反之显示
* 输  出：无
* 返回值：无
******************************************************************/
void WamsPlot::hideMark(bool bLeftMark )
{
	if ( bLeftMark )
	{
		m_mrk_min->hide();
		m_mrk_max->hide();
	}
	else
	{
		m_mrk_min->show();
		m_mrk_max->show();
	}
}
void WamsPlot::setVerticalMark( int iXPos )
{
	//鼠标松开后,显示拉杆,而且两个曲线同时显示
	bool bRightOk = false;
	bool bLeftOk = false;

	//判断当前点是否有效点（是否超出横轴的区间）,以及当前点的值是否为无效数,如果满足,清空文本、隐藏拉杆QWT_NULL_POINT/1E100
	if ( iXPos < 0 || iXPos>m_iPointCount ) //|| fabs(m_dLeftYValue[0][iXPos]) > QWT_NULL_POINT/100 )
	{
		QwtText tmpText("");
		m_mrk_vertical->setLabel(tmpText);
		m_mrk_vertical->hide();
		return;
	}

	//拉杆属性设置,及显示
	QString label;
	char szTmpTime[13];
	QTime upTime = m_startTime.addMSecs( (int)iXPos*INTERVAL );
	sprintf( szTmpTime, "%02d:%02d:%02d.%03d", upTime.hour(), upTime.minute(), upTime.second(), upTime.msec() );
	label.sprintf("时间:%s\n",szTmpTime );

	for ( int i=0; i<m_iCurveNum; i++ )
	{
		QString strTmp;

		if(m_crvLeft[i].isVisible())//曲线可见
		{
			if ( m_dLeftYValue[i][iXPos] > 1e37 )
			{
				strTmp.sprintf("曲线%d: N/A\n", i );
			}
			else
			{
				strTmp.sprintf("曲线%d: %.3f\n", i, m_dLeftYValue[i][iXPos] );
			}
		}

		label += strTmp;
	}
		
	//设置文字内容、字体、颜色
	QwtText text(tr(label.toLatin1()));
	//text.setFont(QFont("Helvetica", 10, QFont::Bold));
	text.setColor(QColor(Qt::white));
	

	//标记线赋值（确定绘制位置）、设置文本标签
	if ( iXPos < m_iPointCount / 2 )
	{
		m_mrk_vertical->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
	}
	else
	{
		m_mrk_vertical->setLabelAlignment(Qt::AlignLeft | Qt::AlignTop);
	}
	m_mrk_vertical->setValue(d_x[iXPos], m_dLeftYValue[0][iXPos]);
	m_mrk_vertical->setLabel(text);
	m_mrk_vertical->show();
}
void WamsPlot::clearStatisticInfo()
{
	for ( int i=0; i<m_iCurveNum-2; i++ )
	{
		m_dLeftMax[i] = -QWT_NULL_POINT;
		m_dLeftMin[i] = QWT_NULL_POINT;
	}
	for ( int j=0; j<2; j++ )
	{
		m_dRightMax[j] = -QWT_NULL_POINT;
		m_dRightMin[j] = QWT_NULL_POINT;
	}
}
//统计左轴最值函数
void WamsPlot::statisticLeftCurve(int YModeType)
{
	clearStatisticInfo();//20100427

	m_dLeftAxisMax = -QWT_NULL_POINT;
	m_dLeftAxisMin = QWT_NULL_POINT;
	int iMaxID = -1;
	int iMinID = -1;

	char szCurTime[13];
	char szMaxTime[13];
	char szMinTime[13];
	memset( szCurTime, 0, 13 ); 
	memset( szMaxTime, 0, 13 );
	memset( szMinTime, 0, 13 );

	//计算极值点
	for ( int j=0; j<m_iCurveNum-2; j++ )
	{
		for ( int i = 0; i < m_iPointCount; i ++ )
		{
			if ( fabs( m_dLeftYValue[j][i] ) > INVALID_FLOAT_VALUE )
			{
				continue;
			}
			if ( m_dLeftYValue[j][i] > m_dLeftMax[j] )
			{
				m_dLeftMax[j] = m_dLeftYValue[j][i];
				m_iLeftMaxID[j] = i;
			}

			if ( m_dLeftYValue[j][i] < m_dLeftMin[j] )
			{
				m_dLeftMin[j] = m_dLeftYValue[j][i];
				m_iLeftMinID[j] = i;
			}		
		}
	}
	for ( int i=0; i<m_iCurveNum-2; i++ )
	{
		if ( m_dLeftMax[i] > m_dLeftAxisMax )
		{
			m_dLeftAxisMax = m_dLeftMax[i];
		}
		if ( m_dLeftMin[i] < m_dLeftAxisMin )
		{
			m_dLeftAxisMin = m_dLeftMin[i];
		}
	}
	switch(YModeType)
	{
	case YLEFT_MODE:
		{
		 if ( fabs(m_dLeftAxisMax) > INVALID_FLOAT_VALUE || fabs(m_dLeftAxisMin) > INVALID_FLOAT_VALUE )
	     {
		  setAxisScale(QwtPlot::yLeft, 0, 1000);
	     }
	     else
	     {
		   if ( (m_dLeftAxisMax-m_dLeftAxisMin) < 0.0000001 )//曲线为0,或为常数
		    {
			setAxisScale(QwtPlot::yLeft, m_dLeftAxisMin-1, m_dLeftAxisMax+1);
		    }
		  else
		    {
			double dTmp = (m_dLeftAxisMax-m_dLeftAxisMin) * g_dBalance;
			setAxisScale(QwtPlot::yLeft, m_dLeftAxisMin-dTmp, m_dLeftAxisMax+dTmp);
		    }
	      }
		}
		break;
	case YRIGHT_MODE:
		{
	    if ( fabs(m_dLeftAxisMax) > INVALID_FLOAT_VALUE || fabs(m_dLeftAxisMin) > INVALID_FLOAT_VALUE )
	     {
		    setAxisScale(QwtPlot::yLeft, 0, 1000);
	     }
	    else
	    {
		  if ( (m_dLeftAxisMax-m_dLeftAxisMin) < 0.0000001 )//曲线为0,或为常数
		  {
			setAxisScale(QwtPlot::yLeft, m_dLeftAxisMin-1, m_dLeftAxisMax+1);
		  }
		  else
		  {
			double dTmp = (m_dLeftAxisMax-m_dLeftAxisMin) * g_dBalance;
			setAxisScale(QwtPlot::yLeft, m_dLeftAxisMin-dTmp, m_dLeftAxisMax+dTmp);
		  }
	     }
		}
		break;
	case YLEFTRIGHT_MODE:
		{
		 if ( fabs(m_dLeftAxisMax) > INVALID_FLOAT_VALUE || fabs(m_dLeftAxisMin) > INVALID_FLOAT_VALUE )
	       {
		     setAxisScale(QwtPlot::yLeft, 0, 1000);
		     setAxisScale(QwtPlot::yRight, 0, 1000);
	       }
	     else
	    {
		   if ( (m_dLeftAxisMax-m_dLeftAxisMin) < 0.0000001 )//曲线为0,或为常数
		   {
			 setAxisScale(QwtPlot::yLeft, m_dLeftAxisMin-1, m_dLeftAxisMax+1);
			 setAxisScale(QwtPlot::yRight, m_dLeftAxisMin-1, m_dLeftAxisMax+1);
		    }
		   else
		   {
			 double dTmp = (m_dLeftAxisMax-m_dLeftAxisMin) * g_dBalance;
			 setAxisScale(QwtPlot::yLeft, m_dLeftAxisMin-dTmp, m_dLeftAxisMax+dTmp);
			 setAxisScale(QwtPlot::yRight, m_dLeftAxisMin-dTmp, m_dLeftAxisMax+dTmp);
		   }
	     }
		}
		break;
	}
	m_zoomer->setZoomBase(true);
}
//统计右轴最值函数,add by 2019.07.02
void WamsPlot::statisticRightCurve(int YModeType)
{
	clearStatisticInfo();//20100427

	m_dRightAxisMax = -QWT_NULL_POINT;
	m_dRightAxisMin = QWT_NULL_POINT;
	int iMaxID = -1;
	int iMinID = -1;

	char szCurTime[13];
	char szMaxTime[13];
	char szMinTime[13];
	memset( szCurTime, 0, 13 ); 
	memset( szMaxTime, 0, 13 );
	memset( szMinTime, 0, 13 );

	//计算极值点
	for ( int j=0; j<2; j++ )
	{
		for ( int i = 0; i < m_iPointCount; i ++ )
		{
			if ( fabs( m_dRightYValue[j][i] ) > INVALID_FLOAT_VALUE )
			{
				continue;
			}
			if ( m_dRightYValue[j][i] > m_dRightMax[j] )
			{
				m_dRightMax[j] = m_dRightYValue[j][i];
				m_iRightMaxID[j] = i;
			}

			if ( m_dRightYValue[j][i] < m_dRightMin[j] )
			{
				m_dRightMin[j] = m_dRightYValue[j][i];
				m_iRightMinID[j] = i;
			}		
		}
	}

	for ( int i=0; i<2; i++ )
	{
		if ( m_dRightMax[i] > m_dRightAxisMax )
		{
			m_dRightAxisMax = m_dRightMax[i];
		}
		if ( m_dRightMin[i] < m_dRightAxisMin )
		{
			m_dRightAxisMin = m_dRightMin[i];
		}
	}
	switch(YModeType)
	{
	case YLEFT_MODE:
		{
		 if ( fabs(m_dRightAxisMax) > INVALID_FLOAT_VALUE || fabs(m_dRightAxisMin) > INVALID_FLOAT_VALUE )
	     {
		    setAxisScale(QwtPlot::yLeft, 0, 1000);
	     }
	     else
	     {
		   if ( (m_dRightAxisMax-m_dRightAxisMin) < 0.0000001 )//曲线为0,或为常数
		    {
			 setAxisScale(QwtPlot::yLeft, m_dLeftAxisMin-1, m_dLeftAxisMax+1);
		    }
		  else
		    {
			 double dTmp = (m_dRightAxisMax-m_dRightAxisMin) * g_dBalance;
			 setAxisScale(QwtPlot::yLeft, m_dRightAxisMin-dTmp, m_dRightAxisMax+dTmp);
		    }
	      }
		}
		break;
	case YRIGHT_MODE:
		{
	    if ( fabs(m_dRightAxisMax) > INVALID_FLOAT_VALUE || fabs(m_dRightAxisMin) > INVALID_FLOAT_VALUE )
	     {
		     setAxisScale(QwtPlot::yRight, 0, 1000);
	     }
	    else
	    {
		  if ( (m_dRightAxisMax-m_dRightAxisMin) < 0.0000001 )//曲线为0,或为常数
		  {
			setAxisScale(QwtPlot::yRight, m_dRightAxisMin-1, m_dRightAxisMax+1);
		  }
		  else
		  {
			double dTmp = (m_dRightAxisMax-m_dRightAxisMin) * g_dBalance;
			setAxisScale(QwtPlot::yRight, m_dRightAxisMin-dTmp, m_dRightAxisMax+dTmp);
		  }
	     }
		}
		break;
	case YLEFTRIGHT_MODE:
		{
		 if ( fabs(m_dRightAxisMax) > INVALID_FLOAT_VALUE || fabs(m_dRightAxisMin) > INVALID_FLOAT_VALUE )
	       {
		      setAxisScale(QwtPlot::yLeft, 0, 1000);
		      setAxisScale(QwtPlot::yRight, 0, 1000);
	       }
	     else
	    {
		    if ( (m_dRightAxisMax-m_dRightAxisMin) < 0.0000001 )//曲线为0,或为常数
		   {
			  setAxisScale(QwtPlot::yLeft, m_dRightAxisMin-1, m_dRightAxisMax+1);
			  setAxisScale(QwtPlot::yRight, m_dRightAxisMin-1, m_dRightAxisMax+1);
		    }
		   else
		   {
			double dTmp = (m_dRightAxisMax-m_dRightAxisMin) * g_dBalance;
			setAxisScale(QwtPlot::yLeft, m_dRightAxisMin-dTmp, m_dRightAxisMax+dTmp);
			setAxisScale(QwtPlot::yRight, m_dRightAxisMin-dTmp, m_dRightAxisMax+dTmp);
		   }
	     }
		}
		break;
	}
	m_zoomer->setZoomBase(true);
}
//双击响应：曲线退回到最原始状态  //20100804
void WamsPlot::mousePressEvent( QMouseEvent * event )
{
   if( (event->type() == QEvent::MouseButtonDblClick) && (event->button() == Qt::RightButton ) )//鼠标右键双击
	{
			m_zoomer->zoom(0);//此zoom(0)函数会触发zoomed( const QwtDoubleRect &rect )信号,接着执行sendZoomInfo( const QwtDoubleRect &rect )函数,发送sendZoomInfo( xp, dSendYp, w, dSendX )信号,导致其他图页会响应
	}
	else if( (event->type() == QEvent::MouseButtonDblClick) && (event->button() == Qt::LeftButton ) )//鼠标左键双击
	{
			emit SendMouseDoubleClickedMessage(m_iChartNo);
	}
}
void WamsPlot::sendZoomInfo( const QwtDoubleRange &rect )
{

	//double xp = rect.x();
	//double yp = rect.y();
	//double w = rect.width();
	//double h = rect.height();

	//if ( fabs(h)<0.001 || fabs(w)<0.001 )
	//{
	//	return;
	//}	

	//double dSendYp;
	//double dSendX;
	//if ( (m_dLeftAxisMax - m_dLeftAxisMin) < 0.0001 )//常数情况
	//{
	//	dSendYp = (m_dLeftAxisMax+1-yp) / (m_dLeftAxisMax-m_dLeftAxisMin+2);
	//	//20110328 dSendX = 1;// 比例为1,不缩放y轴
	//	dSendX = h / (m_dLeftAxisMax-m_dLeftAxisMin+2);
	//}
	//else
	//{
	//	dSendYp = (m_dLeftAxisMax-yp) / (m_dLeftAxisMax-m_dLeftAxisMin);
	//	//20110328 dSendX = 1;// 比例为1,不缩放y轴
	//	dSendX = h / (m_dLeftAxisMax-m_dLeftAxisMin);
	//}

	//
	//if ( ((QWidget*)this)->testAttribute(Qt::WA_UnderMouse)  )//20100805 防止出现消息死循环
	//{
	//	GetMaxMin(xp, w);
	//	emit sendZoomInfo( xp, dSendYp, w, dSendX );
	//}
}
void WamsPlot::zoom( double Xp, double Yp, double w, double x )
{
	if ( fabs(m_dLeftAxisMax)>INVALID_FLOAT_VALUE || fabs(m_dLeftAxisMin)>INVALID_FLOAT_VALUE )
	{
		return;
	}

	double dZoomYp;
	double dZoomX;
	if ( (m_dLeftAxisMax - m_dLeftAxisMin) < 0.0001 )//常数情况
	{
		dZoomYp = m_dLeftAxisMax+1 - Yp * (m_dLeftAxisMax-m_dLeftAxisMin+2);
		dZoomX = x * (m_dLeftAxisMax+1-m_dLeftAxisMin+1);
	}
	else
	{
		dZoomYp = m_dLeftAxisMax - Yp * (m_dLeftAxisMax-m_dLeftAxisMin);
		dZoomX = x * (m_dLeftAxisMax-m_dLeftAxisMin)*( 1 + g_dBalance);
	}
	//QwtDoubleRect rect( Xp, dZoomYp, w, dZoomX );

	GetMaxMin(Xp, w);

	//m_zoomer->zoom(rect);
}
//add 20100806
void WamsPlot::setZoomerEnable( bool b )
{
	m_zoomer->setEnabled(b);
}
//设置曲线是否可见
void WamsPlot::setCurveVisible(int iIndex, bool on,int iYMode)
{
	if(iYMode==YLEFT_MODE)
	{
		m_crvLeft[iIndex].setVisible(on);
	}
	else if(iYMode==YRIGHT_MODE)
	{
		m_crvRight[iIndex].setVisible(on);
	}
}
void WamsPlot::GetMaxMin(double xPos, double width)
{
	// 超出数据曲线范围
	if (xPos >= m_iPointCount)
		return;

	if ( (xPos+width) >= m_iPointCount)
		return;

	// 需要统计的数据点个数为0
	if (width <= 0)
		return;

	SMaxMin *curveInfo = new SMaxMin[m_iCurveNum];
	int iPosMax;
	int iPosMin;

	for (int i=0; i<m_iCurveNum; i++)
	{
		iPosMax = 0;
		iPosMin = 0;
		for (int j=xPos; j<xPos+width; j++)
		{
			if ((curveInfo[i].dMax < m_dLeftYValue[i][j]) && (fabs(m_dLeftYValue[i][j]) < INVALID_FLOAT_VALUE))
			{
				curveInfo[i].dMax = m_dLeftYValue[i][j];
				iPosMax = j;
			}

			if ((curveInfo[i].dMin > m_dLeftYValue[i][j]) && (fabs(m_dLeftYValue[i][j]) < INVALID_FLOAT_VALUE))
			{
				curveInfo[i].dMin = m_dLeftYValue[i][j];
				iPosMin = j;
			}
		}

		curveInfo[i].tMax = m_startTime.addMSecs(iPosMax*INTERVAL);
		curveInfo[i].tMin = m_startTime.addMSecs(iPosMin*INTERVAL);
	}

	emit SendCurveInfo(curveInfo, m_iCurveNum);
}