/****************************************************************************
** CopyRight(c) 2018,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: wamscurve_plot.h
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
** 聂晓波      2009-8-31   v1.0.0    创建版本
** 聂晓波	   2009-12-22  v1.1.0    单坐标多条曲线版本
****************************************************************************/
#ifndef WAMSCURVE_PLOT_H
#define WAMSCURVE_PLOT_H
#include <QTime>

#define QWT_NULL_POINT 1E308
#define INVALID_FLOAT_VALUE 1E37

const double g_dBalance = 0.2;//坐标裕度
//static unsigned int g_curveColor[7] = { 0xffffff00, 0xff00ff00, 0xffff0000,
//0xffff00ff, 0xff55ffff, 0xffaaaaff, 0xff005500};//del by 2019.04.21
//static unsigned int g_curveColor[7] = { 0xffff00, 0x00ff00, 0xff0000,
//0xff00ff, 0x55ffff, 0xaaaaff, 0x005500};
static unsigned int g_curveColor[7] = { 0xffff00, 0x00ff00, 0xff0000,
0xff00ff, 0x55ffff, 0xaaaaff, 0xffffff};

// 曲线最大值最小值信息
struct SMaxMin
{
    double dMax;	// 最大值
    double dMin;	// 最小值

    QTime tMax;		// 最大值对应的时间
    QTime tMin;		// 最小值对应的时间

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

    //绘制曲线函数（供查询界面响应调用）
    void showData(int iCurIndex, QTime startTime,int iYMode, double *dValue,QString strTitle, int iCount);
    //显示最大值(（峰值)函数
    void showPeak(const char *szTime, double dTime,double dValue);
    //显示最小值（谷值）函数
    void showPaddy(const char *szTime, double dTime,double dValue);
    //隐藏左轴曲线极值标记
    void hideMark(bool bLeftMark );
    //初始化缩放、移动等功能
    void initZoomAndPicker();

    //add 20100806
    void setZoomerEnable( bool b );

    void initCurveData( int iDataCount );

    void setPeakMarkShown( QDateTime dateTime, bool iState );

    void clearStatisticInfo();
    void statisticLeftCurve(int YModeType);
    void statisticRightCurve(int YModeType);

    //设置曲线是否可见 add 20120313
    void setCurveVisible(int iIndex,bool on,int iYMode);
    void showItem(const QVariant &itemInfo,bool on);//点击图例并显示相应的曲线

public slots:
    //20100726 void showCurve(QwtPlotItem *item, bool on);
    void setVerticalMark( int iXPos );
    void zoom( double Xp, double Yp, double w, double x );

    void sendZoomInfo( const QwtDoubleRange &rect );

signals:
    void sendZoomInfo( double Xp, double Yp, double w, double x );
    //鼠标左键双击信号 add 20120313
    void SendMouseDoubleClickedMessage(int iChartNo);

    /**
        @param	curveInfo	曲线最大值、最小值信息数组
        @param	curveCount	曲线数量，与curveInfo数组元素数量一直
    */
    void SendCurveInfo(SMaxMin *curveInfo, int curveCount);

private:
    /**
        @brief	统计曲线最大值，最小值
        @param	xPos	x轴起始位置
        @param	width	数据窗口宽度，也就是数据点个数
    */
    void GetMaxMin(double xPos, double width);

protected :
    //双击响应：曲线退回到最原始状态 //20100804
    virtual void mousePressEvent( QMouseEvent * event );

private:
    int m_iCurveNum;//曲线数目
    QTime m_startTime;
    int m_iChartNo;//曲线图编号 add 20120313

public:
    //曲线极值标记定义
    QwtPlotMarker *m_mrk_min;
    QwtPlotMarker *m_mrk_max;
    QwtPlotMarker *m_mrk_vertical;

    //时间坐标
    CTimeScaleDraw  *m_timeScaleDraw;

    //网格和曲线定义
    QwtPlotGrid *m_grid;

    QwtPlotCurve *m_crvLeft;
    QwtPlotCurve *m_crvRight;

    double *d_x;
    //左轴曲线相关变量
    double **m_dLeftYValue;
    double *m_dLeftMax;
    double *m_dLeftMin;
    double m_dLeftAxisMax, m_dLeftAxisMin;
    int *m_iLeftMaxID;
    int *m_iLeftMinID;

    //右轴曲线相关变量
    double **m_dRightYValue;
    double *m_dRightMax;
    double *m_dRightMin;
    double m_dRightAxisMax, m_dRightAxisMin;
    int *m_iRightMaxID;
    int *m_iRightMinID;

    //数据点个数
    int m_iPointCount;

    CZoomer *m_zoomer;
    QwtPicker *m_picker;
    QwtPlotPanner *m_panner;
};

#endif //WAMSCURVE_PLOT_H
