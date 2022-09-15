/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: hiscurveWidget.cpp
** 摘要: 历史曲线绘制对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.01.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.01.01   V1.0      创建
**
****************************************************************************/
#include "hiscurveWidget.h"
#include "commmacro.h"
#include "math.h"
#include <QFileDialog>
#include <QDateTime>
#include <QPalette>
extern int g_iLangChange;//add by 2019.10.3

CHiscurveWidget::CHiscurveWidget()
{
    m_pUi= new Ui::hiscurveForm;
    m_pUi->setupUi(this);


    // 设置日期时间格式
    m_pUi->dateTimeEdit_start->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    m_pUi->dateTimeEdit_end->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    m_pUi->dateTimeEdit_start->setDateTime(QDateTime::currentDateTime());
    m_pUi->dateTimeEdit_end->setDateTime(QDateTime::currentDateTime().addSecs(3600));
    m_tmBasetime=m_pUi->dateTimeEdit_start->time();

    m_pUi->checkBox_totalvolt->setCheckState(Qt::Unchecked);
    m_pUi->checkBox_totalcurr->setCheckState(Qt::Unchecked);
    m_pUi->checkBox_excitvolt->setCheckState(Qt::Unchecked);
    m_pUi->checkBox_excitcurr->setCheckState(Qt::Unchecked);
    m_pUi->checkBox_AVolt->setCheckState(Qt::Unchecked);
    m_pUi->checkBox_BVolt->setCheckState(Qt::Unchecked);
    m_pUi->checkBox_CVolt->setCheckState(Qt::Unchecked);
    m_pUi->checkBox_All->setCheckState(Qt::Unchecked);

    //信号与槽
    //connect(m_pUi->comboBox,SIGNAL(activated(int)),this,SLOT(comboBox_clicked(int)));
    //connect(m_pUi->queryBtn,SIGNAL(clicked()),this,SLOT(queryBtn_clicked()));
    connect(m_pUi->loadBtn,SIGNAL(clicked()),this,SLOT(loadBtn_clicked()));
    connect(m_pUi->checkBox_totalvolt,SIGNAL(clicked()),this,SLOT(totalvolt_clicked()));//总输出电压
    connect(m_pUi->checkBox_totalcurr,SIGNAL(clicked()),this,SLOT(totalcurr_clicked()));//总输出电流
    connect(m_pUi->checkBox_excitvolt,SIGNAL(clicked()),this,SLOT(excitvolt_clicked()));//励磁电压
    connect(m_pUi->checkBox_excitcurr,SIGNAL(clicked()),this,SLOT(excitcurr_clicked()));//励磁电流
    connect(m_pUi->checkBox_AVolt,SIGNAL(clicked()),this,SLOT(PhaseAVolt_clicked()));   //A相电压
    connect(m_pUi->checkBox_BVolt,SIGNAL(clicked()),this,SLOT(PhaseBVolt_clicked()));   //B相电压
    connect(m_pUi->checkBox_CVolt,SIGNAL(clicked()),this,SLOT(PhaseCVolt_clicked()));   //C相电压
    connect(m_pUi->checkBox_All,SIGNAL(clicked()),this,SLOT(AllChoose_clicked()));      //全选
    connect(m_pUi->closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));//返回键 add by 2020.08.10
    connect(m_pUi->recoverBtn,SIGNAL(clicked()),this,SLOT(recoverBtn_clicked()));//曲线复原键 add by 2020.11.11
    //添加曲线控件
    m_pWamsPlot= new WamsPlot(7,m_pUi->frame,2,0);
    QGridLayout *pLayOut = new QGridLayout(m_pUi->frame);
    setLayout(pLayOut);
    pLayOut->setContentsMargins(0,0,0,0);
    pLayOut->addWidget(m_pWamsPlot,0,0,1,1);
    pLayOut->setRowStretch(0,1);
    //初始化数据和曲线
    initDataAndCurve();
}
CHiscurveWidget::~CHiscurveWidget()
{
    if(m_pWamsPlot!=NULL)
    {
        delete m_pWamsPlot;
        m_pWamsPlot=NULL;
    }
}
void CHiscurveWidget::initVecData()
{
    m_vec_fTotalVolt.clear();
    m_vec_fTotalCurrent.clear();
    m_vec_fExcitVolt.clear();
    m_vec_fExcitCurrent.clear();
    m_vec_fPhaseAVolt.clear();
    m_vec_fPhaseBVolt.clear();
    m_vec_fPhaseCVolt.clear();

}
void CHiscurveWidget::initDataAndCurve()
{
    initVecData();
    m_strTotalVoltTitle =QApplication::translate("hiscurveForm",
            "\346\200\273\350\276\223\345\207\272\347\224\265\345\216\213",
            0, QApplication::UnicodeUTF8);//总输出电压
    printf("####m_strCveTitle01=%s####\n",m_strTotalVoltTitle.toAscii().constData());

    m_strTotalCurrentTitle =QApplication::translate("hiscurveForm",
            "\346\200\273\350\276\223\345\207\272\347\224\265\346\265\201",
            0, QApplication::UnicodeUTF8);//总输出电流
    printf("####m_strCveTitle02=%s####\n",m_strTotalCurrentTitle.toAscii().constData());

    m_strExcitVoltTitle=QApplication::translate("hiscurveForm",
        "\345\212\261\347\243\201\347\224\265\345\216\213",
        0, QApplication::UnicodeUTF8);
    m_strExcitCurrentTitle=QApplication::translate("hiscurveForm",
        "\345\212\261\347\243\201\347\224\265\346\265\201",
        0, QApplication::UnicodeUTF8);
    m_strPhaseAVoltTitle=QApplication::translate("hiscurveForm",
        "A\347\233\270\347\224\265\345\216\213",
        0, QApplication::UnicodeUTF8);
    m_strPhaseBVoltTitle=QApplication::translate("hiscurveForm",
        "B\347\233\270\347\224\265\345\216\213",
        0, QApplication::UnicodeUTF8);
    m_strPhaseCVoltTitle=QApplication::translate("hiscurveForm",
        "C\347\233\270\347\224\265\345\216\213",
        0, QApplication::UnicodeUTF8);

    for(int i=0;i<200;i++)
    {
        m_vec_fTotalVolt.append(50*3.1415926*sin(double(i))/180.0);
        m_vec_fTotalCurrent.append(40*3.1415926*sin(double(i))/180.0);
        m_vec_fExcitVolt.append(35*3.1415926*sin(double(i))/180.0);
        m_vec_fExcitCurrent.append(35*3.1415926*sin(double(i))/180.0);
        m_vec_fPhaseAVolt.append(31*3.1415926*sin(double(i))/180.0);
        m_vec_fPhaseBVolt.append(32*3.1415926*sin(double(i))/180.0);
        m_vec_fPhaseCVolt.append(33*3.1415926*sin(double(i))/180.0);
    }
    comboBox_clicked(TOTAL_VOLT_TYPE);
    comboBox_clicked(EXCIT_VOLT_TYPE);
    comboBox_clicked(PHASE_AVOLT_TYPE);
    comboBox_clicked(PHASE_BVOLT_TYPE);
    comboBox_clicked(PHASE_CVOLT_TYPE);

    comboBox_clicked(TOTAL_CURRENT_TYPE);
    comboBox_clicked(EXCIT_CURRENT_TYPE);

    m_pUi->checkBox_totalvolt->setCheckState(Qt::Checked);
    m_pUi->checkBox_excitvolt->setCheckState(Qt::Checked);
    m_pUi->checkBox_AVolt->setCheckState(Qt::Checked);
    m_pUi->checkBox_BVolt->setCheckState(Qt::Checked);
    m_pUi->checkBox_CVolt->setCheckState(Qt::Checked);

    m_pUi->checkBox_totalcurr->setCheckState(Qt::Checked);
    m_pUi->checkBox_excitcurr->setCheckState(Qt::Checked);
    m_pUi->checkBox_All->setCheckState(Qt::Checked);

    m_nDataTypeNum=7;
    m_nCurrentTypeNum=2;//add by 2019.07.03
    //总输出电压按钮背景色
    m_pUi->toolButton_totalvolt->setStyleSheet("background-color:#FFFF00");
    //励磁电压按钮背景色
    m_pUi->toolButton_excitvolt->setStyleSheet("background-color:#00FF00");
    //A相电压按钮背景色
    m_pUi->toolButton_phAvolt->setStyleSheet("background-color:#FF0000");
    //B相电压按钮背景色
    m_pUi->toolButton_phBvolt->setStyleSheet("background-color:#FF00FF");
    //C相电压按钮背景色
    m_pUi->toolButton_phCvolt->setStyleSheet("background-color:#55FFFF");

    //总输出电流按钮背景色
    m_pUi->toolButton_totalcurr->setStyleSheet("background-color:#AAAAFF");
    //励磁电流按钮背景色
    m_pUi->toolButton_excitcurr->setStyleSheet("background-color:#ffffff");//0055BB

    m_isChkTotalVolt=true;
    m_isChkTotalCurrent=true;
    m_isChkExcitVolt=true;
    m_isChkExcitCurrent=true;
    m_isChkPhaseAVolt=true;
    m_isChkPhaseBVolt=true;
    m_isChkPhaseCVolt=true;
    m_isChkAll=true;
}
//数据类型选择
void CHiscurveWidget::comboBox_clicked(int nIndex)
{
    switch(nIndex)
        {
        case TOTAL_VOLT_TYPE://总输出电压
            {
            int nDataNum=m_vec_fTotalVolt.size();
            double *dValue=new double[nDataNum];
            for(int i=0;i<nDataNum;i++)
            {
                dValue[i]=m_vec_fTotalVolt.at(i);
            }
            if(nDataNum<=iDATA_COUNT_MAX)
                {
                    m_pWamsPlot->showData(0,m_tmBasetime,YLEFT_MODE,dValue,m_strTotalVoltTitle,nDataNum);
                    m_pWamsPlot->setCurveVisible(0, true,YLEFT_MODE);
                    m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
                }
            }
            break;
        case TOTAL_CURRENT_TYPE://总输出电流
            {
            int nDataNum=m_vec_fTotalCurrent.size();
            double *dValue=new double[nDataNum];
            for(int i=0;i<nDataNum;i++)
            {
                dValue[i]=m_vec_fTotalCurrent.at(i);
            }
            if(nDataNum<=iDATA_COUNT_MAX)
            {
                m_pWamsPlot->showData(0,m_tmBasetime,YRIGHT_MODE,dValue,m_strTotalCurrentTitle,nDataNum);
                m_pWamsPlot->setCurveVisible(0,true,YRIGHT_MODE);
                m_pWamsPlot->statisticRightCurve(YRIGHT_MODE);
            }
            }
            break;
        case EXCIT_VOLT_TYPE:
            {
            int nDataNum=m_vec_fExcitVolt.size();
            double *dValue=new double[nDataNum];
            for(int i=0;i<nDataNum;i++)
            {
                dValue[i]=m_vec_fExcitVolt.at(i);
            }
            if(nDataNum<=iDATA_COUNT_MAX)
            {
                m_pWamsPlot->showData(1,m_tmBasetime,YLEFT_MODE,dValue,m_strExcitVoltTitle,nDataNum);
                m_pWamsPlot->setCurveVisible(1, true,YLEFT_MODE);
                m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
                m_pWamsPlot->replot();
            }
            }
            break;
        case EXCIT_CURRENT_TYPE:
            {
            int nDataNum=m_vec_fExcitCurrent.size();
            double *dValue=new double[nDataNum];
            for(int i=0;i<nDataNum;i++)
            {
                dValue[i]=m_vec_fExcitCurrent.at(i);
            }
            if(nDataNum<=iDATA_COUNT_MAX)
            {
                m_pWamsPlot->showData(1,m_tmBasetime,YRIGHT_MODE,dValue,m_strExcitCurrentTitle,nDataNum);
                m_pWamsPlot->setCurveVisible(1,true,YRIGHT_MODE);
                m_pWamsPlot->statisticRightCurve(YRIGHT_MODE);
                m_pWamsPlot->replot();
            }
            }
            break;
        case PHASE_AVOLT_TYPE:
            {
            int nDataNum=m_vec_fPhaseAVolt.size();
            double *dValue=new double[nDataNum];
            for(int i=0;i<nDataNum;i++)
            {
                dValue[i]=m_vec_fPhaseAVolt.at(i);
            }
            if(nDataNum<=iDATA_COUNT_MAX)
            {
                m_pWamsPlot->showData(2,m_tmBasetime,YLEFT_MODE,dValue,m_strPhaseAVoltTitle,nDataNum);
                m_pWamsPlot->setCurveVisible(2, true,YLEFT_MODE);
                m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
                m_pWamsPlot->replot();
            }
            }
            break;
        case PHASE_BVOLT_TYPE:
            {
            int nDataNum=m_vec_fPhaseBVolt.size();
            double *dValue=new double[nDataNum];
            for(int i=0;i<nDataNum;i++)
            {
                dValue[i]=m_vec_fPhaseBVolt.at(i);
            }
            if(nDataNum<=iDATA_COUNT_MAX)
            {
                m_pWamsPlot->showData(3,m_tmBasetime,YLEFT_MODE,dValue,m_strPhaseBVoltTitle,nDataNum);
                m_pWamsPlot->setCurveVisible(3, true,YLEFT_MODE);
                m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
                m_pWamsPlot->replot();
            }
            }
            break;
        case PHASE_CVOLT_TYPE:
            {
            int nDataNum=m_vec_fPhaseCVolt.size();
            double *dValue=new double[nDataNum];
            for(int i=0;i<nDataNum;i++)
            {
                dValue[i]=m_vec_fPhaseCVolt.at(i);
            }
            if(nDataNum<=iDATA_COUNT_MAX)
            {
                m_pWamsPlot->showData(4,m_tmBasetime,YLEFT_MODE,dValue,m_strPhaseCVoltTitle,nDataNum);
                m_pWamsPlot->setCurveVisible(4, true,YLEFT_MODE);
                m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
                m_pWamsPlot->replot();
            }
            }
            break;
        default:
            /*m_pPlot->showCurve(m_tmBasetime,
                INTERVAL,
                tr(m_strTotalVoltTitle),
                tr(""),
                tr(""),
                m_vec_fTotalVolt
                ,QColor(Qt::blue));*/
            break;

         }
}
//查询数据-槽函数
void CHiscurveWidget::queryBtn_clicked()
{
}
//加载文件-槽函数
void CHiscurveWidget::loadBtn_clicked()
{
#ifdef WIN_DEV
    QString filepathname="./debug/hisdata/";
#else
    QString filepathname=QApplication::applicationDirPath() + "/hisdata/";
#endif

     QString fileNameWithpath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 tr(filepathname),
                                                 tr("csv (*.csv)"));
     QFile file(fileNameWithpath);
     QString strfilename=fileNameWithpath.section('/', -1);
     QString stryear=strfilename.left(4);
     QString strmonth=strfilename.mid(4,2);
     QString strday=strfilename.mid(6,2);
     QString strhour=strfilename.mid(8,2);
     QString strminute=strfilename.mid(10,2);
     bool ok=false;
     m_tmBasetime=QTime(strhour.toInt(&ok,10), strminute.toInt(&ok,10), 0);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        printf("####【CHiscurveWidget::loadBtn_clicked()】Fail to open  hisdata file####\n");
        return ;
    }

    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
     QDateTime startTime,endTime;
     startTime.setDate(QDate(stryear.toInt(&ok,10),strmonth.toInt(&ok,10),strday.toInt(&ok,10)));
     startTime.setTime(m_tmBasetime);
     endTime.setDate(QDate(stryear.toInt(&ok,10),strmonth.toInt(&ok,10),strday.toInt(&ok,10)));
     endTime.setTime(m_tmBasetime.addSecs(linelist.size()));

     m_pUi->dateTimeEdit_start->setDateTime(startTime);
     m_pUi->dateTimeEdit_end->setDateTime(endTime);
     //解析数据
     parseData(linelist);
     //曲线绘制 add by 2019.10.03
    comboBox_clicked(TOTAL_VOLT_TYPE);
    comboBox_clicked(EXCIT_VOLT_TYPE);
    comboBox_clicked(PHASE_AVOLT_TYPE);
    comboBox_clicked(PHASE_BVOLT_TYPE);
    comboBox_clicked(PHASE_CVOLT_TYPE);
    comboBox_clicked(TOTAL_CURRENT_TYPE);
    comboBox_clicked(EXCIT_CURRENT_TYPE);
    AllChoose_clicked();
    //关闭文件
     file.close();
}
//解析数据并赋值到链表（容器）中
void CHiscurveWidget::parseData(QStringList linelist)
{
    int nsize= linelist.size();
    QString strTemp;
    bool ok=false;
    initVecData();
    for(int i=1;i<nsize;i++)
    {
        strTemp=linelist.at(i).section(',', 2, 2);
        m_vec_fTotalVolt.append(strTemp.toDouble(&ok));

        strTemp=linelist.at(i).section(',', 3, 3);
        m_vec_fTotalCurrent.append(strTemp.toDouble(&ok));

        strTemp=linelist.at(i).section(',', 4, 4);
        m_vec_fExcitVolt.append(strTemp.toDouble(&ok));

        strTemp=linelist.at(i).section(',', 5, 5);
        m_vec_fExcitCurrent.append(strTemp.toDouble(&ok));

        strTemp=linelist.at(i).section(',', 6, 6);
        m_vec_fPhaseAVolt.append(strTemp.toDouble(&ok));

        strTemp=linelist.at(i).section(',', 7, 7);
        m_vec_fPhaseBVolt.append(strTemp.toDouble(&ok));

        strTemp=linelist.at(i).section(',', 8, 8);
        m_vec_fPhaseCVolt.append(strTemp.toDouble(&ok));

    }
}
//"总输出电压"-槽函数
void CHiscurveWidget::totalvolt_clicked()
{
    if(!m_isChkTotalVolt)
    {
        //未勾选时，则勾选
        m_pUi->checkBox_totalvolt->setCheckState(Qt::Checked);
        m_mapDatatype.insert(m_strTotalVoltTitle,TOTAL_VOLT_TYPE);
        m_isChkTotalVolt=true;
        comboBox_clicked(TOTAL_VOLT_TYPE);
        m_nDataTypeNum++;
        if(m_nDataTypeNum==DATA_TYPE_NUM)
        {
            m_pUi->checkBox_All->setCheckState(Qt::Checked);
        }
    }
    else
    {
        //已勾选，则去勾选
        m_pUi->checkBox_totalvolt->setCheckState(Qt::Unchecked);
        m_mapDatatype.remove(m_strTotalVoltTitle);
        m_isChkTotalVolt=false;
        m_pWamsPlot->setCurveVisible(0, false,YLEFT_MODE);//隐藏总输出电压曲线
        m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
        m_nDataTypeNum--;
        m_pUi->checkBox_All->setCheckState(Qt::Unchecked);
        m_isChkAll=false;
    }

}
//"总输出电流"-槽函数
void CHiscurveWidget::totalcurr_clicked()
{
    if(!m_isChkTotalCurrent)
    {
        //未勾选时，则勾选
        m_pUi->checkBox_totalcurr->setCheckState(Qt::Checked);
        m_mapDatatype.insert(m_strTotalCurrentTitle,TOTAL_CURRENT_TYPE);
        m_isChkTotalCurrent=true;
        comboBox_clicked(TOTAL_CURRENT_TYPE);
        m_nDataTypeNum++;
        m_nCurrentTypeNum++;//add by 2019.07.03
        if(m_nDataTypeNum==DATA_TYPE_NUM)
        {
            m_pUi->checkBox_All->setCheckState(Qt::Checked);
        }
        m_pWamsPlot->enableAxis(QwtPlot::yRight,true);//允许右轴显示,add by zqc 2019.07.02
    }
    else
    {
        //已勾选，则去勾选
        m_pUi->checkBox_totalcurr->setCheckState(Qt::Unchecked);
        m_mapDatatype.remove(m_strTotalCurrentTitle);
        m_isChkTotalCurrent=false;
        m_pWamsPlot->setCurveVisible(0, false,YRIGHT_MODE);//隐藏总输出电流曲线
        m_nDataTypeNum--;
        m_nCurrentTypeNum--;//add by 2019.07.03
        if(m_nCurrentTypeNum==0)
        {
            //没有电流类型数据
            m_pWamsPlot->enableAxis(QwtPlot::yRight,false);//隐藏右轴显示,add by zqc 2019.07.02
        }
        m_pUi->checkBox_All->setCheckState(Qt::Unchecked);
        m_isChkAll=false;
    }
}
//"励磁电压"-槽函数
void CHiscurveWidget::excitvolt_clicked()
{
    if(!m_isChkExcitVolt)
    {
        //未勾选时，则勾选
        m_pUi->checkBox_excitvolt->setCheckState(Qt::Checked);
        m_mapDatatype.insert(m_strExcitVoltTitle,EXCIT_VOLT_TYPE);
        m_isChkExcitVolt=true;
        comboBox_clicked(EXCIT_VOLT_TYPE);
        //m_pWamsPlot->replot();
        m_nDataTypeNum++;
        if(m_nDataTypeNum==DATA_TYPE_NUM)
        {
            m_pUi->checkBox_All->setCheckState(Qt::Checked);
        }
    }
    else
    {
        //已勾选，则去勾选
        m_pUi->checkBox_excitvolt->setCheckState(Qt::Unchecked);
        m_mapDatatype.remove(m_strExcitVoltTitle);
        m_isChkExcitVolt=false;
        m_pWamsPlot->setCurveVisible(1, false,YLEFT_MODE);//隐藏励磁电压曲线
        m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
        m_nDataTypeNum--;
        m_pUi->checkBox_All->setCheckState(Qt::Unchecked);
        m_isChkAll=false;
    }
}
//"励磁电流"-槽函数
void CHiscurveWidget::excitcurr_clicked()
{
    if(!m_isChkExcitCurrent)
    {
        //未勾选时，则勾选
        m_pUi->checkBox_excitcurr->setCheckState(Qt::Checked);
        m_mapDatatype.insert(m_strExcitCurrentTitle,EXCIT_CURRENT_TYPE);
        m_isChkExcitCurrent=true;
        comboBox_clicked(EXCIT_CURRENT_TYPE);
        m_pWamsPlot->statisticRightCurve(YRIGHT_MODE);
        m_nDataTypeNum++;
        m_nCurrentTypeNum++;//add by 2019.07.03
        if(m_nDataTypeNum==DATA_TYPE_NUM)
        {
            m_pUi->checkBox_All->setCheckState(Qt::Checked);
        }
        m_pWamsPlot->enableAxis(QwtPlot::yRight,true);//允许右轴显示,add by zqc 2019.07.02
    }
    else
    {
        //已勾选，则去勾选
        m_pUi->checkBox_excitcurr->setCheckState(Qt::Unchecked);
        m_mapDatatype.remove(m_strExcitCurrentTitle);
        m_isChkExcitCurrent=false;
        m_pWamsPlot->setCurveVisible(1, false,YRIGHT_MODE);//隐藏励磁电流曲线
        m_nDataTypeNum--;
        m_nCurrentTypeNum--;//add by 2019.07.03
        if(m_nCurrentTypeNum==0)
        {
            //没有电流类型数据
            m_pWamsPlot->enableAxis(QwtPlot::yRight,false);//隐藏右轴显示,add by zqc 2019.07.02
        }
        m_pUi->checkBox_All->setCheckState(Qt::Unchecked);
        m_isChkAll=false;
    }
}
//"A相电压"-槽函数
void CHiscurveWidget::PhaseAVolt_clicked()
{
   if(!m_isChkPhaseAVolt)
    {
        //未勾选时，则勾选
        m_pUi->checkBox_AVolt->setCheckState(Qt::Checked);
        m_mapDatatype.insert(m_strPhaseAVoltTitle,PHASE_AVOLT_TYPE);
        m_isChkPhaseAVolt=true;
        comboBox_clicked(PHASE_AVOLT_TYPE);
        m_nDataTypeNum++;
        if(m_nDataTypeNum==DATA_TYPE_NUM)
        {
            m_pUi->checkBox_All->setCheckState(Qt::Checked);
        }
    }
    else
    {
        //已勾选，则去勾选
        m_pUi->checkBox_AVolt->setCheckState(Qt::Unchecked);
        m_mapDatatype.remove(m_strPhaseAVoltTitle);
        m_isChkPhaseAVolt=false;
        m_pWamsPlot->setCurveVisible(2, false,YLEFT_MODE);//隐藏A相电压曲线
        m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
        m_nDataTypeNum--;
        m_pUi->checkBox_All->setCheckState(Qt::Unchecked);
        m_isChkAll=false;
    }
}
//"B相电压"-槽函数
void CHiscurveWidget::PhaseBVolt_clicked()
{
    if(!m_isChkPhaseBVolt)
    {
        //未勾选时，则勾选
        m_pUi->checkBox_BVolt->setCheckState(Qt::Checked);
        m_mapDatatype.insert(m_strPhaseBVoltTitle,PHASE_BVOLT_TYPE);
        m_isChkPhaseBVolt=true;
        comboBox_clicked(PHASE_BVOLT_TYPE);
        m_nDataTypeNum++;
        if(m_nDataTypeNum==DATA_TYPE_NUM)
        {
            m_pUi->checkBox_All->setCheckState(Qt::Checked);
        }
    }
    else
    {
        //已勾选，则去勾选
        m_pUi->checkBox_BVolt->setCheckState(Qt::Unchecked);
        m_mapDatatype.remove(m_strPhaseBVoltTitle);
        m_isChkPhaseBVolt=false;
        m_pWamsPlot->setCurveVisible(3, false,YLEFT_MODE);//隐藏B相电压曲线
        m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
        m_nDataTypeNum--;
        m_pUi->checkBox_All->setCheckState(Qt::Unchecked);
        m_isChkAll=false;
    }
}
//"C相电压"-槽函数
void CHiscurveWidget::PhaseCVolt_clicked()
{
    if(!m_isChkPhaseCVolt)
    {
        //未勾选时，则勾选
        m_pUi->checkBox_CVolt->setCheckState(Qt::Checked);
        m_mapDatatype.insert(m_strPhaseCVoltTitle,PHASE_CVOLT_TYPE);
        m_isChkPhaseCVolt=true;
        comboBox_clicked(PHASE_CVOLT_TYPE);
        m_nDataTypeNum++;
        if(m_nDataTypeNum==DATA_TYPE_NUM)
        {
            m_pUi->checkBox_All->setCheckState(Qt::Checked);
        }
    }
    else
    {
        //已勾选，则去勾选
        m_pUi->checkBox_CVolt->setCheckState(Qt::Unchecked);
        m_mapDatatype.remove(m_strPhaseCVoltTitle);
        m_isChkPhaseCVolt=false;
        m_pWamsPlot->setCurveVisible(4, false,YLEFT_MODE);//隐藏C相电压曲线
        m_pWamsPlot->statisticLeftCurve(YLEFT_MODE);
        m_nDataTypeNum--;
        m_pUi->checkBox_All->setCheckState(Qt::Unchecked);
        m_isChkAll=false;
    }
}
//"全选"-槽函数
void CHiscurveWidget::AllChoose_clicked()
{
    if(!m_isChkAll)
    {
        //未勾选时，则勾选
        m_pUi->checkBox_totalvolt->setCheckState(Qt::Checked);
        m_pUi->checkBox_totalcurr->setCheckState(Qt::Checked);
        m_pUi->checkBox_excitvolt->setCheckState(Qt::Checked);
        m_pUi->checkBox_excitcurr->setCheckState(Qt::Checked);
        m_pUi->checkBox_AVolt->setCheckState(Qt::Checked);
        m_pUi->checkBox_BVolt->setCheckState(Qt::Checked);
        m_pUi->checkBox_CVolt->setCheckState(Qt::Checked);
        m_pUi->checkBox_All->setCheckState(Qt::Checked);
        m_isChkTotalVolt=true;
        m_isChkTotalCurrent=true;
        m_isChkExcitVolt=true;
        m_isChkExcitCurrent=true;
        m_isChkPhaseAVolt=true;
        m_isChkPhaseBVolt=true;
        m_isChkPhaseCVolt=true;
        m_isChkAll=true;
        m_nDataTypeNum=DATA_TYPE_NUM;
        m_nCurrentTypeNum=2;
        for(int i=0;i<5;i++)
        {
            m_pWamsPlot->setCurveVisible(i, true,YLEFT_MODE);
        }
        for(int j=0;j<2;j++)
        {
            m_pWamsPlot->setCurveVisible(j, true,YRIGHT_MODE);
        }
        m_pWamsPlot->enableAxis(QwtPlot::yRight,true);//允许右轴显示,add by zqc 2019.07.02
    }
    else
    {
        //已勾选，则去勾选
        m_pUi->checkBox_totalvolt->setCheckState(Qt::Unchecked);
        m_pUi->checkBox_totalcurr->setCheckState(Qt::Unchecked);
        m_pUi->checkBox_excitvolt->setCheckState(Qt::Unchecked);
        m_pUi->checkBox_excitcurr->setCheckState(Qt::Unchecked);
        m_pUi->checkBox_AVolt->setCheckState(Qt::Unchecked);
        m_pUi->checkBox_BVolt->setCheckState(Qt::Unchecked);
        m_pUi->checkBox_CVolt->setCheckState(Qt::Unchecked);
        m_pUi->checkBox_All->setCheckState(Qt::Unchecked);
        m_nDataTypeNum=0;
        m_nCurrentTypeNum=0;
        m_isChkTotalVolt=false;
        m_isChkTotalCurrent=false;
        m_isChkExcitVolt=false;
        m_isChkExcitCurrent=false;
        m_isChkPhaseAVolt=false;
        m_isChkPhaseBVolt=false;
        m_isChkPhaseCVolt=false;
        m_isChkAll=false;
        for(int i=0;i<5;i++)
        {
            m_pWamsPlot->setCurveVisible(i, false,YLEFT_MODE);
        }
        for(int j=0;j<2;j++)
        {
            m_pWamsPlot->setCurveVisible(j, false,YRIGHT_MODE);
        }
        m_pWamsPlot->enableAxis(QwtPlot::yRight,false);//隐藏右轴显示,add by zqc 2019.07.02
    }
}
void CHiscurveWidget::hiscurvelangchange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("hiscurveForm", "\345\216\206\345\217\262\346\233\262\347\272\277", 0, QApplication::UnicodeUTF8));
        m_pUi->label_starttime->setText(QApplication::translate("hiscurveForm", "\345\274\200\345\247\213\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        m_pUi->label_endtime->setText(QApplication::translate("hiscurveForm", "\347\273\223\346\235\237\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        m_pUi->loadBtn->setText(QApplication::translate("hiscurveForm", "\345\212\240 \350\275\275", 0, QApplication::UnicodeUTF8));
        m_pUi->groupBox->setTitle(QApplication::translate("hiscurveForm", "\346\225\260\346\215\256\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_AVolt->setText(QApplication::translate("hiscurveForm", "A\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_BVolt->setText(QApplication::translate("hiscurveForm", "B\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_CVolt->setText(QApplication::translate("hiscurveForm", "C\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_All->setText(QApplication::translate("hiscurveForm", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_totalvolt->setText(QApplication::translate("hiscurveForm", "\346\200\273\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_totalcurr->setText(QApplication::translate("hiscurveForm", "\346\200\273\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_excitvolt->setText(QApplication::translate("hiscurveForm", "\345\212\261\347\243\201\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->checkBox_excitcurr->setText(QApplication::translate("hiscurveForm", "\345\212\261\347\243\201\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
    }
    else
    {
        setWindowTitle("HisCurve");
        m_pUi->label_starttime->setText("Start time");
        m_pUi->label_endtime->setText("End time");
        m_pUi->loadBtn->setText("Loading");
        m_pUi->groupBox->setTitle("Data types");
        m_pUi->checkBox_AVolt->setText("Phase A voltage");
        m_pUi->checkBox_BVolt->setText("Phase B voltage");
        m_pUi->checkBox_CVolt->setText("Phase C voltage");
        m_pUi->checkBox_All->setText("Select All");
        m_pUi->checkBox_totalvolt->setText("Total output voltage");
        m_pUi->checkBox_totalcurr->setText("Total output current");
        m_pUi->checkBox_excitvolt->setText("Field voltage");
        m_pUi->checkBox_excitcurr->setText("Field current");
    }
}
/*返回槽函数实现部分 add by 2020.08.10*/
void CHiscurveWidget::closeBtn_clicked()
{
    this->close();
}

/*曲线复原函数实现部分 add by 2020.11.11*/
void CHiscurveWidget::recoverBtn_clicked()
{
    comboBox_clicked(TOTAL_VOLT_TYPE);
    comboBox_clicked(EXCIT_VOLT_TYPE);
    comboBox_clicked(PHASE_AVOLT_TYPE);
    comboBox_clicked(PHASE_BVOLT_TYPE);
    comboBox_clicked(PHASE_CVOLT_TYPE);
    comboBox_clicked(TOTAL_CURRENT_TYPE);
    comboBox_clicked(EXCIT_CURRENT_TYPE);
}
