/****************************************************************************
** CopyRight(c) 2018,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: hisCurvePlot.cpp
** ժҪ: QWT��������������	
**       
**
** ��ǰ�汾: 1.0.0  2018-8-31
** ����:   ������
**
** ȡ���汾:
** ����:
** ������ڣ�2018-8-31
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾����������
** ������      2018-8-31   v1.0.0    �����汾
** ������	   2018-12-22  v1.1.0    ������������߰汾
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

#define MIN_Y_AXIS_LENGTH 60  //��������

//���������๹�캯��
WamsPlot::WamsPlot(int iCurveNum, QWidget *parent,int YModeType, int iChartNo) : QwtPlot(parent)
{
	if ( iCurveNum > 18 )
	{
		return;
	}
	m_iCurveNum = iCurveNum;
	m_iChartNo = iChartNo;

	setMouseTracking(true);
	
	//����ҳ�߾�,canvas��frame
	//setMargin(0);
	//����canvas��scale�䶯
	plotLayout()->setAlignCanvasToScales(true);
	//�������߱���
	setCanvasBackground(QColor(Qt::darkBlue));//Qt::darkBlue

    //��������
    m_grid = new QwtPlotGrid;
    m_grid->enableXMin(true);
    m_grid->setMajPen(QPen(QBrush(QColor(85, 85, 0)), 0, Qt::DotLine));
    m_grid->setMinPen(QPen(QBrush(QColor(85, 85, 0)), 0, Qt::DotLine));
    m_grid->attach(this);
	//������ֵ����ߣ�����С�����������С�������,���ĸ���
    m_mrk_min = new QwtPlotMarker();
    m_mrk_min->setLineStyle(QwtPlotMarker::HLine);
    m_mrk_min->setLabelAlignment(Qt::AlignLeft| Qt::AlignTop);
    m_mrk_min->setLinePen(QPen(QColor(Qt::yellow), 0, Qt::DashDotLine));
	//�������������ɫ����С   
	QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Diamond,QBrush( Qt::yellow ), QPen( Qt::green, 2 ), QSize( 7, 7) );
    m_mrk_min->attach(this);

    m_mrk_max = new QwtPlotMarker();
    m_mrk_max->setLineStyle(QwtPlotMarker::HLine);
    m_mrk_max->setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
    m_mrk_max->setLinePen(QPen(QColor(Qt::yellow), 0, Qt::DashDotLine));
    m_mrk_max->attach(this);

	//����
	m_mrk_vertical = new QwtPlotMarker();
	m_mrk_vertical->setLineStyle(QwtPlotMarker::VLine);
	m_mrk_vertical->setLabelAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_mrk_vertical->setLinePen(QPen(QColor(Qt::cyan), 0, Qt::DashDotLine));
	m_mrk_vertical->attach(this);
	m_mrk_vertical->hide();

	//�����߸�Ϊ�Զ��ػ�
    setAutoReplot(true);
	//��ʼ���α��Լ��������ŵȹ���
	initZoomAndPicker();
	

	//��ʼ��x���y��
	d_x = new double[iDATA_COUNT_MAX];
	for(int i = 0; i < iDATA_COUNT_MAX; i++)
	{
		d_x[i] = i;
	}
	//�������߱�����ʼ��
	m_dLeftYValue = new double*[m_iCurveNum-2];
	for ( int i=0; i<m_iCurveNum-2; i++ )
	{
		m_dLeftYValue[i] = new double[iDATA_COUNT_MAX];
		for(int k = 0; k < iDATA_COUNT_MAX; k++)
		{
			m_dLeftYValue[i][k] = QWT_NULL_POINT;
		}
	}
	//�������߱�����ʼ��,add by 2019.07.02
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
		setAxisScale(QwtPlot::yLeft, 0, 1000); //��ʼ����-y������Ϊ0-1000
		break;
	case 1:
		setAxisScale(QwtPlot::yRight, 0, 1000);//��ʼ����-y������Ϊ0-1000
		break;
	case 2:
		setAxisScale(QwtPlot::yLeft, 0, 1000); //��ʼ����-y������Ϊ0-1000
		setAxisScale(QwtPlot::yRight, 0, 1000);//��ʼ����-y������Ϊ0-1000
		break;
	}
	m_timeScaleDraw = new CTimeScaleDraw( QTime::currentTime(), 1000 );
	setAxisScaleDraw( QwtPlot::xBottom, m_timeScaleDraw );
	setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom );

	//���������Ӧ����5��
	m_crvLeft = new QwtPlotCurve[iCurveNum-2];
	//���������Ӧ����2��
	m_crvRight =new QwtPlotCurve[2];
	switch(YModeType)
	{
	case YLEFT_MODE:
		break;//����
	case YRIGHT_MODE:
		break;//����
	case YLEFTRIGHT_MODE:
		{
		   int i=0;
		   for ( i=0; i<iCurveNum-2; i++ )
	       {
		     m_crvLeft[i].setTitle("test"+QString("%1").arg( i+1));
		     m_crvLeft[i].setPen(QPen(QColor(g_curveColor[i])));//ǰ5����ɫֵ
		     m_crvLeft[i].setYAxis(QwtPlot::yLeft);//��ѹ�������߷�����
		     m_crvLeft[i].attach(this);
		     m_crvLeft[i].setRawSamples(d_x, m_dLeftYValue[i], iDATA_COUNT_MAX);
		     //m_crvLeft[i].setLegendAttribute(m_crvLeft[i].LegendShowLine);//��ʾͼ���ı�־��������ʾ�ߵ���ɫ��
	       }//for ( i=0; i<iCurveNum-2; i++ )
		   int j=0;
		   for ( j=0; j<2; j++ )
	       {
		     m_crvRight[j].setTitle("test"+QString("%1").arg( j+1));
		     m_crvRight[j].setPen(QPen(QColor(g_curveColor[j+5])));//��2����ɫֵ
		     m_crvRight[j].setYAxis(QwtPlot::yRight);//�����������߷�����
		     m_crvRight[j].attach(this);
		     m_crvRight[j].setRawSamples(d_x, m_dRightYValue[j], iDATA_COUNT_MAX);
		     //m_crvRight[j].setLegendAttribute(m_crvRight[j].LegendShowLine);//��ʾͼ���ı�־��������ʾ�ߵ���ɫ��
	       }//for ( j=0; j<2; j++ )
		}
		break;//������
	}
	//��ʼ�����ݵ����
	m_iPointCount = iDATA_COUNT_MAX;
	//�����������ֵ��ʼ��
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
    //�����������ֵ��ʼ��,add by 2019.07.02
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
		break;//����
	case 1:
		{
		  QwtScaleDraw *yRightAxis = new QwtScaleDraw;
	      yRightAxis->setMinimumExtent(MIN_Y_AXIS_LENGTH);
	      setAxisScaleDraw( QwtPlot::yRight, yRightAxis );
		}
		break;//����
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
	
	enableAxis(QwtPlot::yLeft,true); //�������������ʾ,add by zqc 2019.07.02
	enableAxis(QwtPlot::yRight,true);//�������������ʾ,add by zqc 2019.07.02
	//��ֹ���߷Ŵ�ʱ���߷��г������ 
	QwtPainter::setPolylineSplitting(false); 

	setMinimumHeight(150);
	setMinimumWidth(150);

	QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(1));
	setSizePolicy(sizePolicy2);
}
/*****************************************************************
* ��  �ܣ���������
* ��  �룺��
* ��  ������
* ����ֵ����
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

	
	//��������ָ������,add by 2019.07.02
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
	
	//��������ָ������
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

//���ͼ������ʾ��Ӧ������
void WamsPlot::showItem(const QVariant &itemInfo, bool on)
{
   /* QwtPlotItem *plotItem =infoToItem(itemInfo);
    if (plotItem)
        plotItem->setVisible( on );*/

}
/*****************************************************************
* ��  �ܣ���ʼ�����š��ƶ��ȹ���
* ��  �룺��
* ��  ������
* ����ֵ����
******************************************************************/
void WamsPlot::initZoomAndPicker()
{
	//�������Ӧ��������
	m_zoomer = new CZoomer( QwtPlot::xBottom, QwtPlot::yLeft, this->canvas());
	m_zoomer->setRubberBand(QwtPicker::RectRubberBand);
	m_zoomer->setRubberBandPen(QColor(Qt::green));
	m_zoomer->setTrackerMode(QwtPicker::ActiveOnly);
	m_zoomer->setTrackerPen(QColor(Qt::white));	
	m_zoomer->setZoomBase(false);	//�����������Ż������򣨱������»��������ߺ�,���߼���ԭ��������������--------������һ��Ҫ��!!!!!!!!!!!!!!

	//������м��ƶ�����
	m_panner = new QwtPlotPanner(this->canvas());
	m_panner->setMouseButton(Qt::MidButton);

	//��ȷ�ҵ���,ѡ�к���ʾ��ʮ���ֶ�λ���
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

	//ȷ�������ݵ�ʱ,��Ӧ���̶ȵ��¼���Ӧ
	//connect(m_picker,SIGNAL(sendXPos(int)),this,SLOT(setVerticalMark(int)));//add by zqc 2010.03.11
	//connect( m_zoomer, SIGNAL(zoomed(const QwtDoubleRect &)), this, SLOT(sendZoomInfo( const QwtDoubleRect & )) );

}
/*****************************************************************
* ��  �ܣ���ʼ����������
* ��  �룺iCurveNum:��������iDataCount�����ߵ���
* ��  ������
* ����ֵ����
******************************************************************/
void WamsPlot::initCurveData( int iDataCount )
{
	if(m_iPointCount == iDataCount)
		return;  
	m_iPointCount = iDataCount;	
}
/*****************************************************************
* ��  �ܣ��������ߺ���
* ��  �룺iCurIndex:���ߺ��룻startTime:������ʼʱ�䣻dValue��������ֵ��iCount�����ߵ���
* ��  ������
* ����ֵ����
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
		//��������1��x��+���ᣩ
	   if ( dValue != NULL )
	   { 
		for ( int i=0; i<iCount; i++ )
		{
			m_dLeftYValue[iCurIndex][i] = dValue[i];
		}
		setAxisScale( QwtPlot::xBottom, d_x[0], d_x[iCount-1] );
	   } 
	   m_crvLeft[iCurIndex].setTitle(strTitle);//�������߱��� 2019.03.31
	}
	else if(iYMode==YRIGHT_MODE)
	{
		//��������2��x��+���ᣩ
	   if ( dValue != NULL )
	   { 

		for ( int i=0; i<iCount; i++ )
		{
			m_dRightYValue[iCurIndex][i] = dValue[i];
		}
		setAxisScale( QwtPlot::xBottom, d_x[0], d_x[iCount-1] );
	   }  
	   //m_crvRight[iCurIndex].setTitle(strTitle);//�������߱��� 2019.03.31
	}
	
	m_mrk_vertical->hide();//20100725, add by wanghua,�����һ�β�ѯ��ʷ����ʱ,��ʾ���α�,�ڵڶ��β�ѯ��ʷ����ʱ����ʾ�ϴε��α�
	m_zoomer->setZoomBase(true);//����ȥ��   
}

/*****************************************************************
* ��  �ܣ���ʾ��ֵ��Ǻ�����dLeftvalueΪ��Ч��ʱ,��ʾ�Ҳ����߷�ֵ���,��֮��ʾ������߷�ֵ��ǣ�
* ��  �룺��ֵ��Ӧʱ��szTime,x����ֵdTime,����y1��ֵdLeftvalue,����y2��ֵdRightvalue
* ��  ������
* ����ֵ����
******************************************************************/
void WamsPlot::showPeak( const char *szTime, double dTime, double dValue )
{
	//�����������ֵ��Ϊ��Ч,����
	if ( dValue > QWT_NULL_POINT/10.0  )
	{
		return;
	}
 
	QString label;
	
	//������ָ�ʽ��
	label.sprintf("ʱ��:%s, ���ֵ: %.2f ",szTime,dValue );

	//�����������ݡ����塢��ɫ
	QwtText text(tr(label.toLatin1()));
	text.setFont(QFont("Helvetica", 10, QFont::Bold));
	text.setColor(QColor(Qt::cyan));

	//����߸�ֵ��ȷ������λ�ã��������ı���ǩ
	m_mrk_max->setValue(dTime, dValue);
	m_mrk_max->setLabel(text);	
}

/*****************************************************************
* ��  �ܣ���ʾ��ֵ��Ǻ�����dLeftvalueΪ��Ч��ʱ,��ʾ�Ҳ����߹�ֵ���,��֮��ʾ������߹�ֵ��ǣ�
* ��  �룺��ֵ��Ӧʱ��szTime,x����ֵdTime,����y1��ֵdLeftvalue,����y2��ֵdRightvalue
* ��  ������
* ����ֵ����
******************************************************************/
void WamsPlot::showPaddy(const char *szTime, double dTime, double dValue)
{
	//�����������ֵ��Ϊ��Ч,����
	if ( dValue > QWT_NULL_POINT/10.0 )
	{
		return;
	}
 
	QString label;
	//���������ֵΪ��Ч,��ʾ�����߼�ֵ���
	
	//������ָ�ʽ��
	label.sprintf("ʱ��:%s, ��Сֵ: %.2f ",szTime,dValue );

	//�����������ݡ����塢��ɫ
	QwtText text(tr(label.toLatin1()));
	text.setFont(QFont("Helvetica", 10, QFont::Bold));
	text.setColor(QColor(Qt::cyan));

	//����߸�ֵ��ȷ������λ�ã��������ı���ǩ
	m_mrk_min->setValue(dTime, dValue);
	m_mrk_min->setLabel(text);	
}

/*****************************************************************
* ��  �ܣ����������߼�ֵ���
* ��  �룺bool bLeftMark,ֵΪtrue��ʾ����,��֮��ʾ
* ��  ������
* ����ֵ����
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
	//����ɿ���,��ʾ����,������������ͬʱ��ʾ
	bool bRightOk = false;
	bool bLeftOk = false;

	//�жϵ�ǰ���Ƿ���Ч�㣨�Ƿ񳬳���������䣩,�Լ���ǰ���ֵ�Ƿ�Ϊ��Ч��,�������,����ı�����������QWT_NULL_POINT/1E100
	if ( iXPos < 0 || iXPos>m_iPointCount ) //|| fabs(m_dLeftYValue[0][iXPos]) > QWT_NULL_POINT/100 )
	{
		QwtText tmpText("");
		m_mrk_vertical->setLabel(tmpText);
		m_mrk_vertical->hide();
		return;
	}

	//������������,����ʾ
	QString label;
	char szTmpTime[13];
	QTime upTime = m_startTime.addMSecs( (int)iXPos*INTERVAL );
	sprintf( szTmpTime, "%02d:%02d:%02d.%03d", upTime.hour(), upTime.minute(), upTime.second(), upTime.msec() );
	label.sprintf("ʱ��:%s\n",szTmpTime );

	for ( int i=0; i<m_iCurveNum; i++ )
	{
		QString strTmp;

		if(m_crvLeft[i].isVisible())//���߿ɼ�
		{
			if ( m_dLeftYValue[i][iXPos] > 1e37 )
			{
				strTmp.sprintf("����%d: N/A\n", i );
			}
			else
			{
				strTmp.sprintf("����%d: %.3f\n", i, m_dLeftYValue[i][iXPos] );
			}
		}

		label += strTmp;
	}
		
	//�����������ݡ����塢��ɫ
	QwtText text(tr(label.toLatin1()));
	//text.setFont(QFont("Helvetica", 10, QFont::Bold));
	text.setColor(QColor(Qt::white));
	

	//����߸�ֵ��ȷ������λ�ã��������ı���ǩ
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
//ͳ��������ֵ����
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

	//���㼫ֵ��
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
		   if ( (m_dLeftAxisMax-m_dLeftAxisMin) < 0.0000001 )//����Ϊ0,��Ϊ����
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
		  if ( (m_dLeftAxisMax-m_dLeftAxisMin) < 0.0000001 )//����Ϊ0,��Ϊ����
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
		   if ( (m_dLeftAxisMax-m_dLeftAxisMin) < 0.0000001 )//����Ϊ0,��Ϊ����
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
//ͳ��������ֵ����,add by 2019.07.02
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

	//���㼫ֵ��
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
		   if ( (m_dRightAxisMax-m_dRightAxisMin) < 0.0000001 )//����Ϊ0,��Ϊ����
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
		  if ( (m_dRightAxisMax-m_dRightAxisMin) < 0.0000001 )//����Ϊ0,��Ϊ����
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
		    if ( (m_dRightAxisMax-m_dRightAxisMin) < 0.0000001 )//����Ϊ0,��Ϊ����
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
//˫����Ӧ�������˻ص���ԭʼ״̬  //20100804
void WamsPlot::mousePressEvent( QMouseEvent * event )
{
   if( (event->type() == QEvent::MouseButtonDblClick) && (event->button() == Qt::RightButton ) )//����Ҽ�˫��
	{
			m_zoomer->zoom(0);//��zoom(0)�����ᴥ��zoomed( const QwtDoubleRect &rect )�ź�,����ִ��sendZoomInfo( const QwtDoubleRect &rect )����,����sendZoomInfo( xp, dSendYp, w, dSendX )�ź�,��������ͼҳ����Ӧ
	}
	else if( (event->type() == QEvent::MouseButtonDblClick) && (event->button() == Qt::LeftButton ) )//������˫��
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
	//if ( (m_dLeftAxisMax - m_dLeftAxisMin) < 0.0001 )//�������
	//{
	//	dSendYp = (m_dLeftAxisMax+1-yp) / (m_dLeftAxisMax-m_dLeftAxisMin+2);
	//	//20110328 dSendX = 1;// ����Ϊ1,������y��
	//	dSendX = h / (m_dLeftAxisMax-m_dLeftAxisMin+2);
	//}
	//else
	//{
	//	dSendYp = (m_dLeftAxisMax-yp) / (m_dLeftAxisMax-m_dLeftAxisMin);
	//	//20110328 dSendX = 1;// ����Ϊ1,������y��
	//	dSendX = h / (m_dLeftAxisMax-m_dLeftAxisMin);
	//}

	//
	//if ( ((QWidget*)this)->testAttribute(Qt::WA_UnderMouse)  )//20100805 ��ֹ������Ϣ��ѭ��
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
	if ( (m_dLeftAxisMax - m_dLeftAxisMin) < 0.0001 )//�������
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
//���������Ƿ�ɼ�
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
	// �����������߷�Χ
	if (xPos >= m_iPointCount)
		return;

	if ( (xPos+width) >= m_iPointCount)
		return;

	// ��Ҫͳ�Ƶ����ݵ����Ϊ0
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