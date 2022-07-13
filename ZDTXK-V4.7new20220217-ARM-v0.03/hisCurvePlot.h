/****************************************************************************
** CopyRight(c) 2018,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: wamscurve_plot.h
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
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾����������
** ������      2009-8-31   v1.0.0    �����汾
** ������	   2009-12-22  v1.1.0    ������������߰汾
****************************************************************************/
#ifndef WAMSCURVE_PLOT_H
#define WAMSCURVE_PLOT_H
#include <QTime>

#define QWT_NULL_POINT 1E308
#define INVALID_FLOAT_VALUE 1E37

const double g_dBalance = 0.2;//����ԣ��
//static unsigned int g_curveColor[7] = { 0xffffff00, 0xff00ff00, 0xffff0000,
//0xffff00ff, 0xff55ffff, 0xffaaaaff, 0xff005500};//del by 2019.04.21
//static unsigned int g_curveColor[7] = { 0xffff00, 0x00ff00, 0xff0000,
//0xff00ff, 0x55ffff, 0xaaaaff, 0x005500};
static unsigned int g_curveColor[7] = { 0xffff00, 0x00ff00, 0xff0000,
0xff00ff, 0x55ffff, 0xaaaaff, 0xffffff};

// �������ֵ��Сֵ��Ϣ
struct SMaxMin
{
    double dMax;	// ���ֵ
    double dMin;	// ��Сֵ

    QTime tMax;		// ���ֵ��Ӧ��ʱ��
    QTime tMin;		// ��Сֵ��Ӧ��ʱ��

    SMaxMin()
    {
        dMax = -QWT_NULL_POINT;
        dMin = QWT_NULL_POINT;
    }
};


#include <qwt_plot.h>
#include <qwt_plot_zoomer.h>

//#include <qwt_polygon.h>
#include <qwt_plot_panner.h>
#include <qwt_scale_draw.h>

#include <QDateTime>
#include <QTime>

#include "plotuserclass.h"
#include <qwt_double_range.h>
#include <qwt_picker.h>

//#include "qwttimepicker.h"

class QwtPlotCurve;
class QwtPlotMarker;
class QwtPlotGrid;

class WamsPlot;


class WamsPlot: public QwtPlot
{
    Q_OBJECT
public:
    WamsPlot(int iCurveNum, QWidget *parent=0,int YModeType=2,int iChartNo = 0);//modify 20120313
    ~WamsPlot();

    //�������ߺ���������ѯ������Ӧ���ã�
    void showData(int iCurIndex, QTime startTime,int iYMode, double *dValue,QString strTitle, int iCount);
    //��ʾ���ֵ(����ֵ)����
    void showPeak(const char *szTime, double dTime,double dValue);
    //��ʾ��Сֵ����ֵ������
    void showPaddy(const char *szTime, double dTime,double dValue);
    //�����������߼�ֵ���
    void hideMark(bool bLeftMark );
    //��ʼ�����š��ƶ��ȹ���
    void initZoomAndPicker();

    //add 20100806
    void setZoomerEnable( bool b );

    void initCurveData( int iDataCount );

    void setPeakMarkShown( QDateTime dateTime, bool iState );

    void clearStatisticInfo();
    void statisticLeftCurve(int YModeType);
    void statisticRightCurve(int YModeType);

    //���������Ƿ�ɼ� add 20120313
    void setCurveVisible(int iIndex,bool on,int iYMode);
    void showItem(const QVariant &itemInfo,bool on);//���ͼ������ʾ��Ӧ������

public slots:
    //20100726 void showCurve(QwtPlotItem *item, bool on);
    void setVerticalMark( int iXPos );
    void zoom( double Xp, double Yp, double w, double x );

    void sendZoomInfo( const QwtDoubleRange &rect );

signals:
    void sendZoomInfo( double Xp, double Yp, double w, double x );
    //������˫���ź� add 20120313
    void SendMouseDoubleClickedMessage(int iChartNo);

    /**
        @param	curveInfo	�������ֵ����Сֵ��Ϣ����
        @param	curveCount	������������curveInfo����Ԫ������һֱ
    */
    void SendCurveInfo(SMaxMin *curveInfo, int curveCount);

private:
    /**
        @brief	ͳ���������ֵ����Сֵ
        @param	xPos	x����ʼλ��
        @param	width	���ݴ��ڿ�ȣ�Ҳ�������ݵ����
    */
    void GetMaxMin(double xPos, double width);

protected :
    //˫����Ӧ�������˻ص���ԭʼ״̬ //20100804
    virtual void mousePressEvent( QMouseEvent * event );

private:
    int m_iCurveNum;//������Ŀ
    QTime m_startTime;
    int m_iChartNo;//����ͼ��� add 20120313

public:
    //���߼�ֵ��Ƕ���
    QwtPlotMarker *m_mrk_min;
    QwtPlotMarker *m_mrk_max;
    QwtPlotMarker *m_mrk_vertical;

    //ʱ������
    CTimeScaleDraw  *m_timeScaleDraw;

    //��������߶���
    QwtPlotGrid *m_grid;

    QwtPlotCurve *m_crvLeft;
    QwtPlotCurve *m_crvRight;

    double *d_x;
    //����������ر���
    double **m_dLeftYValue;
    double *m_dLeftMax;
    double *m_dLeftMin;
    double m_dLeftAxisMax, m_dLeftAxisMin;
    int *m_iLeftMaxID;
    int *m_iLeftMinID;

    //����������ر���
    double **m_dRightYValue;
    double *m_dRightMax;
    double *m_dRightMin;
    double m_dRightAxisMax, m_dRightAxisMin;
    int *m_iRightMaxID;
    int *m_iRightMinID;

    //���ݵ����
    int m_iPointCount;

    CZoomer *m_zoomer;
    QwtPicker *m_picker;
    QwtPlotPanner *m_panner;
};

#endif //WAMSCURVE_PLOT_H
