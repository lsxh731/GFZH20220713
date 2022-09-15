/****************************************************************************
** CopyRight(c) 2010,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: plot.cpp
** ժҪ: ���߻�����
**       
**
** ��ǰ�汾: 4.0.0.0
** ����:  ������
** �������: 2017.12.09
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2017.12.09   V4.0     �����굥���߰汾
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
//��ʼ��Plot���߽���Ԫ��
void CPlot::init()
{
	//���û�������ɫ
	setCanvasBackground(Qt::gray);
	
	//����ͼ��
	m_pLegend = new QwtLegend();
	insertLegend(m_pLegend, QwtPlot::TopLegend);

	//�������
	m_pPlotGrid = new QwtPlotGrid();
	m_pPlotGrid->enableXMin(false);
	m_pPlotGrid->setMajPen(QPen(Qt::white, 0, Qt::DotLine));
	m_pPlotGrid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
	m_pPlotGrid->attach(this);
	init_XAxis();
	init_Curve(m_nCurveCount);
	initZoomer();
	
}

void CPlot::showCurve(const QTime &timeBegin,       //ʱ����Ļ�׼ʱ��
	                  const int &nTimeInterval,     //ʱ����
					  const QString &strCurveTtile,	//��������
					  const QString &strXAxisTitle,	//X���ע
					  const QString &strYAxisTitle,	//Y���ע
					  const QList<double> &lstYValue,//Y������ֵ
					  QColor CurveColor)	//X��Y������ֵ
{
	
	int nAxisID = QwtPlot::yLeft;

	if (NULL==m_pXScalDraw)
	{
		return;
	}

	((CTimeScaleDraw*)m_pXScalDraw)->setBaseTime(timeBegin,nTimeInterval);

	//����������ɫ
	QPen pen = m_pNewPlotCurve->pen();
	pen.setColor(CurveColor);
	pen.setWidth(1);
	m_pNewPlotCurve->setPen(pen);
	m_pNewPlotCurve->attach(this);	

	//��ȡ��ǰ��ʾ�����߶���
	m_pNewPlotCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//�����⻬�� 
	
	//Y������title
	QwtText yText(strYAxisTitle);
	yText.setFont(QFont("Helvetica", 10, QFont::DemiBold));
	yText.setColor(Qt::red);
	setAxisTitle(nAxisID,yText);

	QVector<QPointF> vector;
	QPointF point;

	//ȷ��y����ֵ
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
			m_dAxisMax = lstYValue[nIndex];//ͳ�����ֵ 
		}
		if (lstYValue[nIndex]<m_dAxisMin)
		{
			m_dAxisMin = lstYValue[nIndex];//ͳ����Сֵ 
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
	//��������title
	QwtText title(strCurveTtile);
	title.setFont(QFont("Helvetica", 11, QFont::Bold));
	title.setColor(QColor(Qt::black));
	m_pNewPlotCurve->setTitle(title);

	//��������ֵ
	m_pNewPlotCurve->setSamples(vector);
	m_pNewPlotCurve->attach( this );
	m_pNewPlotCurve->setLegendAttribute(m_pNewPlotCurve->LegendShowLine);//��ʾͼ���ı�־��������ʾ�ߵ���ɫ

	replot();
	setAutoReplot( true );//�����Զ��ػ����൱�ڸ���

	//QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotCurve );//��ȡ���˶���������,���Ϊ��ȡ������״��ע��ı����  
	//  qDebug()<<items;  

}
void CPlot::init_XAxis()
{
	m_pXScalDraw = NULL;
	m_pXScalDraw = new CTimeScaleDraw(QTime::currentTime(),INTERVAL); 
	setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
	setAxisScaleDraw(QwtPlot::xBottom, m_pXScalDraw);//X��ʱ����Ϣ
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom);

	//-----------����x��y����ͷ�Χ--------------//
	setAxisTitle( QwtPlot::yLeft, "ylabel" );
	setAxisTitle( QwtPlot::xBottom, "" );
	setAxisScale(QwtPlot::yLeft,-10.0,10.0);
	setAxisScale(QwtPlot::xBottom,0.0,1000.0);

}
//�����������߶���
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
//�����������߶���
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
//���ų�ʼ��
void CPlot::initZoomer()
{
	//�������Ӧ��������
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
	////�����������Ż�������(�������»��������ߺ����߼���ԭ��������������)������һ��Ҫ��
	//m_pZoomer->setZoomBase(true);                 
}

	









