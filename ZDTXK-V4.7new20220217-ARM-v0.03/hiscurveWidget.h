/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: hiscurveWidget.h
** 摘要: 历史曲线绘制窗口
**       
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.01.27
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.01.27   V1.0      创建
**
****************************************************************************/
#ifndef HISCURVE_WIDGET_H
#define HISCURVE_WIDGET_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_hiscurve.h"
#include <QMap>
#include "hisCurvePlot.h"

namespace Ui
{
	class hiscurveForm;
}
class CHiscurveWidget:public QDialog//QWidget
{
	Q_OBJECT
public:
	CHiscurveWidget();
	~CHiscurveWidget();
public Q_SLOTS:
	void comboBox_clicked(int nIndex);//数据类型选择
	void queryBtn_clicked();          //查询数据-槽函数
	void loadBtn_clicked();           //加载文件-槽函数
	void totalvolt_clicked();         //"总输出电压"-槽函数
	void totalcurr_clicked();         //"总输出电流"-槽函数
	void excitvolt_clicked();         //"励磁电压"-槽函数
	void excitcurr_clicked();         //"励磁电流"-槽函数
	void PhaseAVolt_clicked();        //"A相电压"-槽函数
	void PhaseBVolt_clicked();        //"B相电压"-槽函数
	void PhaseCVolt_clicked();        //"C相电压"-槽函数
	void AllChoose_clicked();         //"全选"-槽函数
	void closeBtn_clicked();           //"返回"-槽函数 add by 2020.08.10
	void recoverBtn_clicked();       //"曲线复原"-槽函数 add by 2020.11.11

public:
	void hiscurvelangchange();        //历史曲线界面语言切换
private:
	void initVecData();                  //初始化链表（容器）变量数据
	void initDataAndCurve();             //初始化数据和曲线
	void parseData(QStringList linelist);//解析数据
private:
	 WamsPlot *m_pWamsPlot;              //多曲线对象指针
	 QTime m_tmBasetime;                 //基准时间
	 QList<double>m_vec_fTotalVolt;   //存放总输出电压数据的链表(容器)
	 QList<double>m_vec_fTotalCurrent;//存放总输出电流数据的链表(容器)
	 QList<double>m_vec_fExcitVolt;   //存放励磁电压数据的链表(容器)
	 QList<double>m_vec_fExcitCurrent;//存放励磁电流数据的链表(容器)
	 QList<double>m_vec_fPhaseAVolt;  //存放A相电压数据的链表(容器)
	 QList<double>m_vec_fPhaseBVolt;  //存放B相电压数据的链表(容器)
	 QList<double>m_vec_fPhaseCVolt;  //存放C相电压数据的链表(容器)
	 QString m_strTotalVoltTitle;     //总输出电压曲线标题
	 QString m_strTotalCurrentTitle;  //总输出电流曲线标题
	 QString m_strExcitVoltTitle;     //励磁电压曲线标题
	 QString m_strExcitCurrentTitle;  //励磁电流曲线标题
	 QString m_strPhaseAVoltTitle;    //A相电压曲线标题
	 QString m_strPhaseBVoltTitle;    //B相电压曲线标题
	 QString m_strPhaseCVoltTitle;    //C相电压曲线标题
	 QMap<QString, int>m_mapDatatype; //数据类型map
	 bool m_isChkTotalVolt;
	 bool m_isChkTotalCurrent;
	 bool m_isChkExcitVolt;
	 bool m_isChkExcitCurrent;
	 bool m_isChkPhaseAVolt;
	 bool m_isChkPhaseBVolt;
	 bool m_isChkPhaseCVolt;
	 bool m_isChkAll;
	  int m_nDataTypeNum;               //数据类型数量
	  int m_nCurrentTypeNum;            //电流类型数量,add by zqc 2019.07.03
private:
	Ui::hiscurveForm  *m_pUi;
};
#endif //HISCURVE_WIDGET_H