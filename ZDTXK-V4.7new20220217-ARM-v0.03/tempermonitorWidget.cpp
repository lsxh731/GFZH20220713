/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: tempermonitorWidget.cpp
** 摘要: "温度监控"子对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.12.10
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2018.12.10   V1.0      创建
** 聂晓波      2019.02.11   V1.1      修改
****************************************************************************/
#include "tempermonitorWidget.h"
extern int g_iLangChange;//add by 2019.10.3

CTempMonitorWidget::CTempMonitorWidget(QWidget *ptr)
{
    m_pUi= new Ui::tempermonitorForm;
    m_pUi->setupUi(this);
    m_pWidget=ptr;
    init();
    //信号与槽关系
    connect(m_pUi->sub1Btn,SIGNAL(clicked()),this,SLOT(sub1Btn_clicked()));
    connect(m_pUi->sub2Btn,SIGNAL(clicked()),this,SLOT(sub2Btn_clicked()));
    connect(m_pUi->sub3Btn,SIGNAL(clicked()),this,SLOT(sub3Btn_clicked()));
    connect(m_pUi->sub4Btn,SIGNAL(clicked()),this,SLOT(sub4Btn_clicked()));
    sub1Btn_clicked();
    connect(m_pUi->closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));//返回键 add by 2020.08.10
}
CTempMonitorWidget::~CTempMonitorWidget()
{
    QCoreApplication::postEvent(m_pWidget,new QCustomEvent(QEvent::User + 4000),0);
    printf("QCoreApplication::postEvent(m_pWidget,new QCustomEvent(QEvent::User + 4000),0)\n");
}
void CTempMonitorWidget::closeEvent(QCloseEvent *event)
{
    /*QCoreApplication::postEvent(m_pWidget,new QCustomEvent(QEvent::User + 4000),0);
    printf("closeEvent--postEvent(m_pWidget,new QCustomEvent(QEvent::User + 4000),0)\n");*/
}
void CTempMonitorWidget::init()
{
    //温度监控数据初始化
    memset(&m_struIGBTTemperData,0,sizeof(m_struIGBTTemperData));
    memset(&m_struIDUCTTemperData,0,sizeof(m_struIDUCTTemperData));
    memset(&m_struDCInputVoltageData,0,sizeof(m_struDCInputVoltageData));

    //设置晶体管控件QLCDNumber能显示的位数
    m_pUi->M1DCVolt_lcdNumber->setDigitCount(5);
    m_pUi->M1ACCurr_lcdNumber->setDigitCount(5);
    m_pUi->M1ACVolt_lcdNumber->setDigitCount(5);
    m_pUi->M2DCVolt_lcdNumber->setDigitCount(5);
    m_pUi->M2ACCurr_lcdNumber->setDigitCount(5);
    m_pUi->M2ACVolt_lcdNumber->setDigitCount(5);
    m_pUi->M3DCVolt_lcdNumber->setDigitCount(5);
    m_pUi->M3ACCurr_lcdNumber->setDigitCount(5);
    m_pUi->M3ACVolt_lcdNumber->setDigitCount(5);
    m_pUi->M4DCVolt_lcdNumber->setDigitCount(5);
    m_pUi->M4ACCurr_lcdNumber->setDigitCount(5);
    m_pUi->M4ACVolt_lcdNumber->setDigitCount(5);
    m_pUi->M1DCVolt_lcdNumber_2->setDigitCount(5);
    m_pUi->M1ACCurr_lcdNumber_2->setDigitCount(5);
    m_pUi->M1ACVolt_lcdNumber_2->setDigitCount(5);
    m_pUi->M2DCVolt_lcdNumber_2->setDigitCount(5);
    m_pUi->M2ACCurr_lcdNumber_2->setDigitCount(5);
    m_pUi->M2ACVolt_lcdNumber_2->setDigitCount(5);
    m_pUi->M3DCVolt_lcdNumber_2->setDigitCount(5);
    m_pUi->M3ACCurr_lcdNumber_2->setDigitCount(5);
    m_pUi->M3ACVolt_lcdNumber_2->setDigitCount(5);
    m_pUi->M4DCVolt_lcdNumber_2->setDigitCount(5);
    m_pUi->M4ACCurr_lcdNumber_2->setDigitCount(5);
    m_pUi->M4ACVolt_lcdNumber_2->setDigitCount(5);
    m_pUi->M1DCVolt_lcdNumber_3->setDigitCount(5);
    m_pUi->M1ACCurr_lcdNumber_3->setDigitCount(5);
    m_pUi->M1ACVolt_lcdNumber_3->setDigitCount(5);
    m_pUi->M2DCVolt_lcdNumber_3->setDigitCount(5);
    m_pUi->M2ACCurr_lcdNumber_3->setDigitCount(5);
    m_pUi->M2ACVolt_lcdNumber_3->setDigitCount(5);
    m_pUi->M3DCVolt_lcdNumber_3->setDigitCount(5);
    m_pUi->M3ACCurr_lcdNumber_3->setDigitCount(5);
    m_pUi->M3ACVolt_lcdNumber_3->setDigitCount(5);
    m_pUi->M4DCVolt_lcdNumber_3->setDigitCount(5);
    m_pUi->M4ACCurr_lcdNumber_3->setDigitCount(5);
    m_pUi->M4ACVolt_lcdNumber_3->setDigitCount(5);
    m_pUi->M1DCVolt_lcdNumber_4->setDigitCount(5);
    m_pUi->M1ACCurr_lcdNumber_4->setDigitCount(5);
    m_pUi->M1ACVolt_lcdNumber_4->setDigitCount(5);
    m_pUi->M2DCVolt_lcdNumber_4->setDigitCount(5);
    m_pUi->M2ACCurr_lcdNumber_4->setDigitCount(5);
    m_pUi->M2ACVolt_lcdNumber_4->setDigitCount(5);
    m_pUi->M3DCVolt_lcdNumber_4->setDigitCount(5);
    m_pUi->M3ACCurr_lcdNumber_4->setDigitCount(5);
    m_pUi->M3ACVolt_lcdNumber_4->setDigitCount(5);
    m_pUi->M4DCVolt_lcdNumber_4->setDigitCount(5);
    m_pUi->M4ACCurr_lcdNumber_4->setDigitCount(5);
    m_pUi->M4ACVolt_lcdNumber_4->setDigitCount(5);
     //设置显示的模式为十进制
    m_pUi->M1DCVolt_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M1ACCurr_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M1ACVolt_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M2DCVolt_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M2ACCurr_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M2ACVolt_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M3DCVolt_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M3ACCurr_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M3ACVolt_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M4DCVolt_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M4ACCurr_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M4ACVolt_lcdNumber->setMode(QLCDNumber::Dec);
    m_pUi->M1DCVolt_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M1ACCurr_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M1ACVolt_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M2DCVolt_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M2ACCurr_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M2ACVolt_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M3DCVolt_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M3ACCurr_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M3ACVolt_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M4DCVolt_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M4ACCurr_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M4ACVolt_lcdNumber_2->setMode(QLCDNumber::Dec);
    m_pUi->M1DCVolt_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M1ACCurr_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M1ACVolt_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M2DCVolt_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M2ACCurr_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M2ACVolt_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M3DCVolt_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M3ACCurr_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M3ACVolt_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M4DCVolt_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M4ACCurr_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M4ACVolt_lcdNumber_3->setMode(QLCDNumber::Dec);
    m_pUi->M1DCVolt_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M1ACCurr_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M1ACVolt_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M2DCVolt_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M2ACCurr_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M2ACVolt_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M3DCVolt_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M3ACCurr_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M3ACVolt_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M4DCVolt_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M4ACCurr_lcdNumber_4->setMode(QLCDNumber::Dec);
    m_pUi->M4ACVolt_lcdNumber_4->setMode(QLCDNumber::Dec);
     //设置显示方式
    m_pUi->M1DCVolt_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1ACCurr_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1ACVolt_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2DCVolt_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2ACCurr_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2ACVolt_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3DCVolt_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3ACCurr_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3ACVolt_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4DCVolt_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4ACCurr_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4ACVolt_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1DCVolt_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1ACCurr_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1ACVolt_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2DCVolt_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2ACCurr_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2ACVolt_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3DCVolt_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3ACCurr_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3ACVolt_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4DCVolt_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4ACCurr_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4ACVolt_lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1DCVolt_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1ACCurr_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1ACVolt_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2DCVolt_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2ACCurr_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2ACVolt_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3DCVolt_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3ACCurr_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3ACVolt_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4DCVolt_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4ACCurr_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4ACVolt_lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1DCVolt_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1ACCurr_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M1ACVolt_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2DCVolt_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2ACCurr_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M2ACVolt_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3DCVolt_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3ACCurr_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M3ACVolt_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4DCVolt_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4ACCurr_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    m_pUi->M4ACVolt_lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);
    //updateTemperatureData(0,m_struIGBTTemperData,m_struIDUCTTemperData,m_struDCInputVoltageData);//初始化显示温度监控数据
}
//更新温度监控数据
void CTempMonitorWidget::updateTemperatureData(STRU_IGBTTEMPERATUREMONI *pStruIGBTTemperData,STRU_IDUCTTEMPERATUREMONI *pStruIDUCTTemperData,STRU_INPUTDCVOLTAGEMONI *pStruDCInputVoltageData)
{
    //功率模块1数据显示
    m_pUi->M1IGBTWD1_lEdit->setText(QString::number(pStruIGBTTemperData[0].fIGBT1Temper,'f',0));
    m_pUi->M1IGBTWD2_lEdit->setText(QString::number(pStruIGBTTemperData[0].fIGBT2Temper,'f',0));
    m_pUi->M1DGWD1_lEdit->setText(QString::number(pStruIDUCTTemperData[0].fIDUCT1Temper,'f',0));
    m_pUi->M1DGWD2_lEdit->setText(QString::number(pStruIDUCTTemperData[0].fIDUCT2Temper,'f',0));
    m_pUi->M1DCVolt_lcdNumber->display(QString::number(pStruDCInputVoltageData[0].fINPUTDCVoltage,'f',0));
    m_pUi->M1ACCurr_lcdNumber->display(QString::number(pStruIGBTTemperData[0].fOUTPUTACCurrent,'f',0));
    m_pUi->M1ACVolt_lcdNumber->display(QString::number(pStruIDUCTTemperData[0].fOUTPUTACVoltage,'f',0));
    //功率模块2数据显示
    m_pUi->M2IGBTWD1_lEdit->setText(QString::number(pStruIGBTTemperData[1].fIGBT1Temper,'f',0));
    m_pUi->M2IGBTWD2_lEdit->setText(QString::number(pStruIGBTTemperData[1].fIGBT2Temper,'f',0));
    m_pUi->M2DGWD1_lEdit->setText(QString::number(pStruIDUCTTemperData[1].fIDUCT1Temper,'f',0));
    m_pUi->M2DGWD2_lEdit->setText(QString::number(pStruIDUCTTemperData[1].fIDUCT2Temper,'f',0));
    m_pUi->M2DCVolt_lcdNumber->display(QString::number(pStruDCInputVoltageData[1].fINPUTDCVoltage,'f',0));
    m_pUi->M2ACCurr_lcdNumber->display(QString::number(pStruIGBTTemperData[1].fOUTPUTACCurrent,'f',0));
    m_pUi->M2ACVolt_lcdNumber->display(QString::number(pStruIDUCTTemperData[1].fOUTPUTACVoltage,'f',0));
    //功率模块3数据显示
    m_pUi->M3IGBTWD1_lEdit->setText(QString::number(pStruIGBTTemperData[2].fIGBT1Temper,'f',0));
    m_pUi->M3IGBTWD2_lEdit->setText(QString::number(pStruIGBTTemperData[2].fIGBT2Temper,'f',0));
    m_pUi->M3DGWD1_lEdit->setText(QString::number(pStruIDUCTTemperData[2].fIDUCT1Temper,'f',0));
    m_pUi->M3DGWD2_lEdit->setText(QString::number(pStruIDUCTTemperData[2].fIDUCT2Temper,'f',0));
    m_pUi->M3DCVolt_lcdNumber->display(QString::number(pStruDCInputVoltageData[2].fINPUTDCVoltage,'f',0));
    m_pUi->M3ACCurr_lcdNumber->display(QString::number(pStruIGBTTemperData[2].fOUTPUTACCurrent,'f',0));
    m_pUi->M3ACVolt_lcdNumber->display(QString::number(pStruIDUCTTemperData[2].fOUTPUTACVoltage,'f',0));
    //功率模块4数据显示
    m_pUi->M4IGBTWD1_lEdit->setText(QString::number(pStruIGBTTemperData[3].fIGBT1Temper,'f',0));
    m_pUi->M4IGBTWD2_lEdit->setText(QString::number(pStruIGBTTemperData[3].fIGBT2Temper,'f',0));
    m_pUi->M4DGWD1_lEdit->setText(QString::number(pStruIDUCTTemperData[3].fIDUCT1Temper,'f',0));
    m_pUi->M4DGWD2_lEdit->setText(QString::number(pStruIDUCTTemperData[3].fIDUCT2Temper,'f',0));
    m_pUi->M4DCVolt_lcdNumber->display(QString::number(pStruDCInputVoltageData[3].fINPUTDCVoltage,'f',0));
    m_pUi->M4ACCurr_lcdNumber->display(QString::number(pStruIGBTTemperData[3].fOUTPUTACCurrent,'f',0));
    m_pUi->M4ACVolt_lcdNumber->display(QString::number(pStruIDUCTTemperData[3].fOUTPUTACVoltage,'f',0));
    //功率模块5数据显示
    m_pUi->M1IGBTWD1_lEdit_2->setText(QString::number(pStruIGBTTemperData[4].fIGBT1Temper,'f',0));
    m_pUi->M1IGBTWD2_lEdit_2->setText(QString::number(pStruIGBTTemperData[4].fIGBT2Temper,'f',0));
    m_pUi->M1DGWD1_lEdit_2->setText(QString::number(pStruIDUCTTemperData[4].fIDUCT1Temper,'f',0));
    m_pUi->M1DGWD2_lEdit_2->setText(QString::number(pStruIDUCTTemperData[4].fIDUCT2Temper,'f',0));
    m_pUi->M1DCVolt_lcdNumber_2->display(QString::number(pStruDCInputVoltageData[4].fINPUTDCVoltage,'f',0));
    m_pUi->M1ACCurr_lcdNumber_2->display(QString::number(pStruIGBTTemperData[4].fOUTPUTACCurrent,'f',0));
    m_pUi->M1ACVolt_lcdNumber_2->display(QString::number(pStruIDUCTTemperData[4].fOUTPUTACVoltage,'f',0));
    //功率模块6数据显示
    m_pUi->M2IGBTWD1_lEdit_2->setText(QString::number(pStruIGBTTemperData[5].fIGBT1Temper,'f',0));
    m_pUi->M2IGBTWD2_lEdit_2->setText(QString::number(pStruIGBTTemperData[5].fIGBT2Temper,'f',0));
    m_pUi->M2DGWD1_lEdit_2->setText(QString::number(pStruIDUCTTemperData[5].fIDUCT1Temper,'f',0));
    m_pUi->M2DGWD2_lEdit_2->setText(QString::number(pStruIDUCTTemperData[5].fIDUCT2Temper,'f',0));
    m_pUi->M2DCVolt_lcdNumber_2->display(QString::number(pStruDCInputVoltageData[5].fINPUTDCVoltage,'f',0));
    m_pUi->M2ACCurr_lcdNumber_2->display(QString::number(pStruIGBTTemperData[5].fOUTPUTACCurrent,'f',0));
    m_pUi->M2ACVolt_lcdNumber_2->display(QString::number(pStruIDUCTTemperData[5].fOUTPUTACVoltage,'f',0));
    //功率模块7数据显示
    m_pUi->M3IGBTWD1_lEdit_2->setText(QString::number(pStruIGBTTemperData[6].fIGBT1Temper,'f',0));
    m_pUi->M3IGBTWD2_lEdit_2->setText(QString::number(pStruIGBTTemperData[6].fIGBT2Temper,'f',0));
    m_pUi->M3DGWD1_lEdit_2->setText(QString::number(pStruIDUCTTemperData[6].fIDUCT1Temper,'f',0));
    m_pUi->M3DGWD2_lEdit_2->setText(QString::number(pStruIDUCTTemperData[6].fIDUCT2Temper,'f',0));
    m_pUi->M3DCVolt_lcdNumber_2->display(QString::number(pStruDCInputVoltageData[6].fINPUTDCVoltage,'f',0));
    m_pUi->M3ACCurr_lcdNumber_2->display(QString::number(pStruIGBTTemperData[6].fOUTPUTACCurrent,'f',0));
    m_pUi->M3ACVolt_lcdNumber_2->display(QString::number(pStruIDUCTTemperData[6].fOUTPUTACVoltage,'f',0));
    //功率模块8数据显示
    m_pUi->M4IGBTWD1_lEdit_2->setText(QString::number(pStruIGBTTemperData[7].fIGBT1Temper,'f',0));
    m_pUi->M4IGBTWD2_lEdit_2->setText(QString::number(pStruIGBTTemperData[7].fIGBT2Temper,'f',0));
    m_pUi->M4DGWD1_lEdit_2->setText(QString::number(pStruIDUCTTemperData[7].fIDUCT1Temper,'f',0));
    m_pUi->M4DGWD2_lEdit_2->setText(QString::number(pStruIDUCTTemperData[7].fIDUCT2Temper,'f',0));
    m_pUi->M4DCVolt_lcdNumber_2->display(QString::number(pStruDCInputVoltageData[7].fINPUTDCVoltage,'f',0));
    m_pUi->M4ACCurr_lcdNumber_2->display(QString::number(pStruIGBTTemperData[7].fOUTPUTACCurrent,'f',0));
    m_pUi->M4ACVolt_lcdNumber_2->display(QString::number(pStruIDUCTTemperData[7].fOUTPUTACVoltage,'f',0));
    //功率模块9数据显示
    m_pUi->M1IGBTWD1_lEdit_3->setText(QString::number(pStruIGBTTemperData[8].fIGBT1Temper,'f',0));
    m_pUi->M1IGBTWD2_lEdit_3->setText(QString::number(pStruIGBTTemperData[8].fIGBT2Temper,'f',0));
    m_pUi->M1DGWD1_lEdit_3->setText(QString::number(pStruIDUCTTemperData[8].fIDUCT1Temper,'f',0));
    m_pUi->M1DGWD2_lEdit_3->setText(QString::number(pStruIDUCTTemperData[8].fIDUCT2Temper,'f',0));
    m_pUi->M1DCVolt_lcdNumber_3->display(QString::number(pStruDCInputVoltageData[8].fINPUTDCVoltage,'f',0));
    m_pUi->M1ACCurr_lcdNumber_3->display(QString::number(pStruIGBTTemperData[8].fOUTPUTACCurrent,'f',0));
    m_pUi->M1ACVolt_lcdNumber_3->display(QString::number(pStruIDUCTTemperData[8].fOUTPUTACVoltage,'f',0));
    //功率模块10数据显示
    m_pUi->M2IGBTWD1_lEdit_3->setText(QString::number(pStruIGBTTemperData[9].fIGBT1Temper,'f',0));
    m_pUi->M2IGBTWD2_lEdit_3->setText(QString::number(pStruIGBTTemperData[9].fIGBT2Temper,'f',0));
    m_pUi->M2DGWD1_lEdit_3->setText(QString::number(pStruIDUCTTemperData[9].fIDUCT1Temper,'f',0));
    m_pUi->M2DGWD2_lEdit_3->setText(QString::number(pStruIDUCTTemperData[9].fIDUCT2Temper,'f',0));
    m_pUi->M2DCVolt_lcdNumber_3->display(QString::number(pStruDCInputVoltageData[9].fINPUTDCVoltage,'f',0));
    m_pUi->M2ACCurr_lcdNumber_3->display(QString::number(pStruIGBTTemperData[9].fOUTPUTACCurrent,'f',0));
    m_pUi->M2ACVolt_lcdNumber_3->display(QString::number(pStruIDUCTTemperData[9].fOUTPUTACVoltage,'f',0));
    //功率模块11数据显示
    m_pUi->M3IGBTWD1_lEdit_3->setText(QString::number(pStruIGBTTemperData[10].fIGBT1Temper,'f',0));
    m_pUi->M3IGBTWD2_lEdit_3->setText(QString::number(pStruIGBTTemperData[10].fIGBT2Temper,'f',0));
    m_pUi->M3DGWD1_lEdit_3->setText(QString::number(pStruIDUCTTemperData[10].fIDUCT1Temper,'f',0));
    m_pUi->M3DGWD2_lEdit_3->setText(QString::number(pStruIDUCTTemperData[10].fIDUCT2Temper,'f',0));
    m_pUi->M3DCVolt_lcdNumber_3->display(QString::number(pStruDCInputVoltageData[10].fINPUTDCVoltage,'f',0));
    m_pUi->M3ACCurr_lcdNumber_3->display(QString::number(pStruIGBTTemperData[10].fOUTPUTACCurrent,'f',0));
    m_pUi->M3ACVolt_lcdNumber_3->display(QString::number(pStruIDUCTTemperData[10].fOUTPUTACVoltage,'f',0));
    //功率模块12数据显示
    m_pUi->M4IGBTWD1_lEdit_3->setText(QString::number(pStruIGBTTemperData[11].fIGBT1Temper,'f',0));
    m_pUi->M4IGBTWD2_lEdit_3->setText(QString::number(pStruIGBTTemperData[11].fIGBT2Temper,'f',0));
    m_pUi->M4DGWD1_lEdit_3->setText(QString::number(pStruIDUCTTemperData[11].fIDUCT1Temper,'f',0));
    m_pUi->M4DGWD2_lEdit_3->setText(QString::number(pStruIDUCTTemperData[11].fIDUCT2Temper,'f',0));
    m_pUi->M4DCVolt_lcdNumber_3->display(QString::number(pStruDCInputVoltageData[11].fINPUTDCVoltage,'f',0));
    m_pUi->M4ACCurr_lcdNumber_3->display(QString::number(pStruIGBTTemperData[11].fOUTPUTACCurrent,'f',0));
    m_pUi->M4ACVolt_lcdNumber_3->display(QString::number(pStruIDUCTTemperData[11].fOUTPUTACVoltage,'f',0));
    //功率模块13数据显示
    m_pUi->M1IGBTWD1_lEdit_4->setText(QString::number(pStruIGBTTemperData[12].fIGBT1Temper,'f',0));
    m_pUi->M1IGBTWD2_lEdit_4->setText(QString::number(pStruIGBTTemperData[12].fIGBT2Temper,'f',0));
    m_pUi->M1DGWD1_lEdit_4->setText(QString::number(pStruIDUCTTemperData[12].fIDUCT1Temper,'f',0));
    m_pUi->M1DGWD2_lEdit_4->setText(QString::number(pStruIDUCTTemperData[12].fIDUCT2Temper,'f',0));
    m_pUi->M1DCVolt_lcdNumber_4->display(QString::number(pStruDCInputVoltageData[12].fINPUTDCVoltage,'f',0));
    m_pUi->M1ACCurr_lcdNumber_4->display(QString::number(pStruIGBTTemperData[12].fOUTPUTACCurrent,'f',0));
    m_pUi->M1ACVolt_lcdNumber_4->display(QString::number(pStruIDUCTTemperData[12].fOUTPUTACVoltage,'f',0));
    //功率模块14数据显示
    m_pUi->M2IGBTWD1_lEdit_4->setText(QString::number(pStruIGBTTemperData[13].fIGBT1Temper,'f',0));
    m_pUi->M2IGBTWD2_lEdit_4->setText(QString::number(pStruIGBTTemperData[13].fIGBT2Temper,'f',0));
    m_pUi->M2DGWD1_lEdit_4->setText(QString::number(pStruIDUCTTemperData[13].fIDUCT1Temper,'f',0));
    m_pUi->M2DGWD2_lEdit_4->setText(QString::number(pStruIDUCTTemperData[13].fIDUCT2Temper,'f',0));
    m_pUi->M2DCVolt_lcdNumber_4->display(QString::number(pStruDCInputVoltageData[13].fINPUTDCVoltage,'f',0));
    m_pUi->M2ACCurr_lcdNumber_4->display(QString::number(pStruIGBTTemperData[13].fOUTPUTACCurrent,'f',0));
    m_pUi->M2ACVolt_lcdNumber_4->display(QString::number(pStruIDUCTTemperData[13].fOUTPUTACVoltage,'f',0));
    //功率模块15数据显示
    m_pUi->M3IGBTWD1_lEdit_4->setText(QString::number(pStruIGBTTemperData[14].fIGBT1Temper,'f',0));
    m_pUi->M3IGBTWD2_lEdit_4->setText(QString::number(pStruIGBTTemperData[14].fIGBT2Temper,'f',0));
    m_pUi->M3DGWD1_lEdit_4->setText(QString::number(pStruIDUCTTemperData[14].fIDUCT1Temper,'f',0));
    m_pUi->M3DGWD2_lEdit_4->setText(QString::number(pStruIDUCTTemperData[14].fIDUCT2Temper,'f',0));
    m_pUi->M3DCVolt_lcdNumber_4->display(QString::number(pStruDCInputVoltageData[14].fINPUTDCVoltage,'f',0));
    m_pUi->M3ACCurr_lcdNumber_4->display(QString::number(pStruIGBTTemperData[14].fOUTPUTACCurrent,'f',0));
    m_pUi->M3ACVolt_lcdNumber_4->display(QString::number(pStruIDUCTTemperData[14].fOUTPUTACVoltage,'f',0));
    //功率模块16数据显示
    m_pUi->M4IGBTWD1_lEdit_4->setText(QString::number(pStruIGBTTemperData[15].fIGBT1Temper,'f',0));
    m_pUi->M4IGBTWD2_lEdit_4->setText(QString::number(pStruIGBTTemperData[15].fIGBT2Temper,'f',0));
    m_pUi->M4DGWD1_lEdit_4->setText(QString::number(pStruIDUCTTemperData[15].fIDUCT1Temper,'f',0));
    m_pUi->M4DGWD2_lEdit_4->setText(QString::number(pStruIDUCTTemperData[15].fIDUCT2Temper,'f',0));
    m_pUi->M4DCVolt_lcdNumber_4->display(QString::number(pStruDCInputVoltageData[15].fINPUTDCVoltage,'f',0));
    m_pUi->M4ACCurr_lcdNumber_4->display(QString::number(pStruIGBTTemperData[15].fOUTPUTACCurrent,'f',0));
    m_pUi->M4ACVolt_lcdNumber_4->display(QString::number(pStruIDUCTTemperData[15].fOUTPUTACVoltage,'f',0));
}
void CTempMonitorWidget::temperLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("tempermonitorForm", "\346\270\251\345\272\246\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        //分柜号
        m_pUi->sub1Btn->setText(QApplication::translate("tempermonitorForm", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));
        m_pUi->sub2Btn->setText(QApplication::translate("tempermonitorForm", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));
        m_pUi->sub3Btn->setText(QApplication::translate("tempermonitorForm", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));
        m_pUi->sub4Btn->setText(QApplication::translate("tempermonitorForm", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));
        //模块号
        m_pUi->toolButton_glmk_1->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2271",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_2->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2272",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_3->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2273",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_4->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2274",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_5->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2275",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_6->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2276",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_7->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2277",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_8->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2278",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_9->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\2279",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_10->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\22710",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_11->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\22711",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_12->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\22712",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_13->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\22713",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_14->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\22714",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_15->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\22715",0,QApplication::UnicodeUTF8));
        m_pUi->toolButton_glmk_16->setText(QApplication::translate("tempermonitorForm","\345\212\237\347\216\207\346\250\241\345\235\22716",0,QApplication::UnicodeUTF8));
        //模块1
        m_pUi->label_110->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_112->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_114->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_116->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_118->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_120->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_158->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块2
        m_pUi->label_122->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_124->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_126->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_128->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_130->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_132->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_160->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块3
        m_pUi->label_134->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_136->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_138->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_140->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_142->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_144->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_163->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块4
        m_pUi->label_146->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_148->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_150->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_152->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_154->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_156->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_165->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块5
        m_pUi->label_200->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_202->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_204->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_206->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_198->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_196->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_194->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块6
        m_pUi->label_174->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_176->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_170->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_178->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_168->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_172->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_166->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块7
        m_pUi->label_208->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_216->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_214->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_210->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_212->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_218->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_220->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块8
        m_pUi->label_180->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_186->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_188->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_192->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_184->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_190->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_182->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块9
        m_pUi->label_256->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_258->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_260->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_262->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_254->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_252->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_250->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块10
        m_pUi->label_230->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_232->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_226->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_234->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_224->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_228->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_222->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块11
        m_pUi->label_264->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_272->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_270->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_266->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_268->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_274->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_276->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块12
        m_pUi->label_236->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_242->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_244->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_248->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_240->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_246->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_238->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块13
        m_pUi->label_312->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_314->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_316->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_318->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_310->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_308->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_306->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块14
        m_pUi->label_286->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_288->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_282->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_290->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_280->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_284->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_278->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块15
        m_pUi->label_320->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_328->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_326->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_322->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_324->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_330->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_332->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        //模块16
        m_pUi->label_292->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_298->setText(QApplication::translate("tempermonitorForm", "IGBT\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_300->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        m_pUi->label_304->setText(QApplication::translate("tempermonitorForm", "\347\224\265\346\204\237\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        m_pUi->label_296->setText(QApplication::translate("tempermonitorForm", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_302->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_294->setText(QApplication::translate("tempermonitorForm", "\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
    }
    else
    {
        setWindowTitle("Monitor");
        //分柜号
        m_pUi->sub1Btn->setText(tr("Sub1"));
        m_pUi->sub2Btn->setText(tr("Sub2"));
        m_pUi->sub3Btn->setText(tr("Sub3"));
        m_pUi->sub4Btn->setText(tr("Sub4"));
        //模块号
        m_pUi->toolButton_glmk_1->setText("Module1");
        m_pUi->toolButton_glmk_2->setText("Module2");
        m_pUi->toolButton_glmk_3->setText("Module3");
        m_pUi->toolButton_glmk_4->setText("Module4");
        m_pUi->toolButton_glmk_5->setText("Module5");
        m_pUi->toolButton_glmk_6->setText("Module6");
        m_pUi->toolButton_glmk_7->setText("Module7");
        m_pUi->toolButton_glmk_8->setText("Module8");
        m_pUi->toolButton_glmk_9->setText("Module9");
        m_pUi->toolButton_glmk_10->setText("Module10");
        m_pUi->toolButton_glmk_11->setText("Module11");
        m_pUi->toolButton_glmk_12->setText("Module12");
        m_pUi->toolButton_glmk_13->setText("Module13");
        m_pUi->toolButton_glmk_14->setText("Module14");
        m_pUi->toolButton_glmk_15->setText("Module15");
        m_pUi->toolButton_glmk_16->setText("Module16");
        //模块1
        m_pUi->label_110->setText("IGBT T1");
        m_pUi->label_112->setText("IGBT T2");
        m_pUi->label_114->setText("Inductor T1");
        m_pUi->label_116->setText("Inductor T2");
        m_pUi->label_118->setText("Module DC");
        m_pUi->label_120->setText("Output Cur");
        m_pUi->label_158->setText("Output Vol");
        //模块2
        m_pUi->label_122->setText("IGBT T1");
        m_pUi->label_124->setText("IGBT T2");
        m_pUi->label_126->setText("Inductor T1");
        m_pUi->label_128->setText("Inductor T2");
        m_pUi->label_130->setText("Module DC");
        m_pUi->label_132->setText("Output Cur");
        m_pUi->label_160->setText("Output Vol");
        //模块3
        m_pUi->label_134->setText("IGBT T1");
        m_pUi->label_136->setText("IGBT T2");
        m_pUi->label_138->setText("Inductor T1");
        m_pUi->label_140->setText("Inductor T2");
        m_pUi->label_142->setText("Module DC");
        m_pUi->label_144->setText("Output Cur");
        m_pUi->label_163->setText("Output Vol");
        //模块4
        m_pUi->label_146->setText("IGBT T1");
        m_pUi->label_148->setText("IGBT T2");
        m_pUi->label_150->setText("Inductor T1");
        m_pUi->label_152->setText("Inductor T2");
        m_pUi->label_154->setText("Module DC");
        m_pUi->label_156->setText("Output Cur");
        m_pUi->label_165->setText("Output Vol");
        //模块5
        m_pUi->label_200->setText("IGBT T1");
        m_pUi->label_202->setText("IGBT T2");
        m_pUi->label_204->setText("Inductor T1");
        m_pUi->label_206->setText("Inductor T2");
        m_pUi->label_198->setText("Module DC");
        m_pUi->label_196->setText("Output Cur");
        m_pUi->label_194->setText("Output Vol");
        //模块6
        m_pUi->label_174->setText("IGBT T1");
        m_pUi->label_176->setText("IGBT T2");
        m_pUi->label_170->setText("Inductor T1");
        m_pUi->label_178->setText("Inductor T2");
        m_pUi->label_168->setText("Module DC");
        m_pUi->label_172->setText("Output Cur");
        m_pUi->label_166->setText("Output Vol");
        //模块7
        m_pUi->label_208->setText("IGBT T1");
        m_pUi->label_216->setText("IGBT T2");
        m_pUi->label_214->setText("Inductor T1");
        m_pUi->label_210->setText("Inductor T2");
        m_pUi->label_212->setText("Module DC");
        m_pUi->label_218->setText("Output Cur");
        m_pUi->label_220->setText("Output Vol");
        //模块8
        m_pUi->label_180->setText("IGBT T1");
        m_pUi->label_186->setText("IGBT T2");
        m_pUi->label_188->setText("Inductor T1");
        m_pUi->label_192->setText("Inductor T2");
        m_pUi->label_184->setText("Module DC");
        m_pUi->label_190->setText("Output Cur");
        m_pUi->label_182->setText("Output Vol");
        //模块9
        m_pUi->label_256->setText("IGBT T1");
        m_pUi->label_258->setText("IGBT T2");
        m_pUi->label_260->setText("Inductor T1");
        m_pUi->label_262->setText("Inductor T2");
        m_pUi->label_254->setText("Module DC");
        m_pUi->label_252->setText("Output Cur");
        m_pUi->label_250->setText("Output Vol");
        //模块10
        m_pUi->label_230->setText("IGBT T1");
        m_pUi->label_232->setText("IGBT T2");
        m_pUi->label_226->setText("Inductor T1");
        m_pUi->label_234->setText("Inductor T2");
        m_pUi->label_224->setText("Module DC");
        m_pUi->label_228->setText("Output Cur");
        m_pUi->label_222->setText("Output Vol");
        //模块11
        m_pUi->label_264->setText("IGBT T1");
        m_pUi->label_272->setText("IGBT T2");
        m_pUi->label_270->setText("Inductor T1");
        m_pUi->label_266->setText("Inductor T2");
        m_pUi->label_268->setText("Module DC");
        m_pUi->label_274->setText("Output Cur");
        m_pUi->label_276->setText("Output Vol");
        //模块12
        m_pUi->label_236->setText("IGBT T1");
        m_pUi->label_242->setText("IGBT T2");
        m_pUi->label_244->setText("Inductor T1");
        m_pUi->label_248->setText("Inductor T2");
        m_pUi->label_240->setText("Module DC");
        m_pUi->label_246->setText("Output Cur");
        m_pUi->label_238->setText("Output Vol");
        //模块13
        m_pUi->label_312->setText("IGBT T1");
        m_pUi->label_314->setText("IGBT T2");
        m_pUi->label_316->setText("Inductor T1");
        m_pUi->label_318->setText("Inductor T2");
        m_pUi->label_310->setText("Module DC");
        m_pUi->label_308->setText("Output Cur");
        m_pUi->label_306->setText("Output Vol");
        //模块14
        m_pUi->label_286->setText("IGBT T1");
        m_pUi->label_288->setText("IGBT T2");
        m_pUi->label_282->setText("Inductor T1");
        m_pUi->label_290->setText("Inductor T2");
        m_pUi->label_280->setText("Module DC");
        m_pUi->label_284->setText("Output Cur");
        m_pUi->label_278->setText("Output Vol");
        //模块15
        m_pUi->label_320->setText("IGBT T1");
        m_pUi->label_328->setText("IGBT T2");
        m_pUi->label_326->setText("Inductor T1");
        m_pUi->label_322->setText("Inductor T2");
        m_pUi->label_324->setText("Module DC");
        m_pUi->label_330->setText("Output Cur");
        m_pUi->label_332->setText("Output Vol");
        //模块16
        m_pUi->label_292->setText("IGBT T1");
        m_pUi->label_298->setText("IGBT T2");
        m_pUi->label_300->setText("Inductor T1");
        m_pUi->label_304->setText("Inductor T2");
        m_pUi->label_296->setText("Module DC");
        m_pUi->label_302->setText("Output Cur");
        m_pUi->label_294->setText("Output Vol");
    }
}
//分柜信息页面-分柜1切换槽函数,add by 2020.04.18
void CTempMonitorWidget::sub1Btn_clicked()
{
    //if(m_pUi->SubStackedWidget->currentIndex()!=0)
    //{
        m_pUi->SubStackedWidget->setCurrentIndex(0);
        m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));//亮色
        m_pUi->sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
        m_pUi->sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
        m_pUi->sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    //}
}
//分柜信息页面-分柜2切换槽函数,add by 2020.04.18
void CTempMonitorWidget::sub2Btn_clicked()
{
    m_pUi->SubStackedWidget->setCurrentIndex(1);
    m_pUi->sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));//亮色
    m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    //}
}
//分柜信息页面-分柜3切换槽函数,add by 2020.04.18
void CTempMonitorWidget::sub3Btn_clicked()
{
    m_pUi->SubStackedWidget->setCurrentIndex(2);
    m_pUi->sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));//亮色
    m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
}
//分柜信息页面-分柜4切换槽函数,add by 2020.04.18
void CTempMonitorWidget::sub4Btn_clicked()
{
    m_pUi->SubStackedWidget->setCurrentIndex(3);
    m_pUi->sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(36, 210, 92)"));//亮色
    m_pUi->sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
    m_pUi->sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172)"));//默认色
}
/*返回键槽函数实现 add by 2020.08.10*/
void CTempMonitorWidget::closeBtn_clicked()
{
    this->close();
}
