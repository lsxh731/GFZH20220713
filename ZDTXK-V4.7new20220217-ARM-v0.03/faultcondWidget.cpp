/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: fautcondWidget.cpp
** 摘要: "故障状态"子对话框
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
**
****************************************************************************/
#include "faultcondWidget.h"
extern int g_iLangChange;//add by 2019.10.3
CFaultConditionWidget::CFaultConditionWidget()
{
    m_pUi= new Ui::faultconditionForm;
    m_pUi->setupUi(this);
    m_pUi->radioButton0102->setChecked(true);//默认选择模块01-02
    ifaultindex=0;
    connect(m_pUi->radioButton0102,SIGNAL(clicked()),this,SLOT(radioButton0102_clicked()));
    connect(m_pUi->radioButton0304,SIGNAL(clicked()),this,SLOT(radioButton0304_clicked()));
    connect(m_pUi->radioButton0506,SIGNAL(clicked()),this,SLOT(radioButton0506_clicked()));
    connect(m_pUi->radioButton0708,SIGNAL(clicked()),this,SLOT(radioButton0708_clicked()));
    connect(m_pUi->radioButton0910,SIGNAL(clicked()),this,SLOT(radioButton0910_clicked()));
    connect(m_pUi->radioButton1112,SIGNAL(clicked()),this,SLOT(radioButton1112_clicked()));
    connect(m_pUi->radioButton1314,SIGNAL(clicked()),this,SLOT(radioButton1314_clicked()));
    connect(m_pUi->radioButton1516,SIGNAL(clicked()),this,SLOT(radioButton1516_clicked()));
    connect(m_pUi->closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));//add by 2020.08.10
    m_greenicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"gct_ied_green.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_redicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"gct_ied_red.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_yellowicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png"), QSize(), QIcon::Normal, QIcon::Off);

    init(m_yellowicon);
}
CFaultConditionWidget::~CFaultConditionWidget()
{

}
void CFaultConditionWidget::radioButton0102_clicked()
{
    ifaultindex=0;
    if(g_iLangChange)
    {
        m_pUi->faultstatus_groupBox01->setTitle(QApplication::translate("faultconditionForm",
         "\346\250\241\345\235\2271",
         0,
         QApplication::UnicodeUTF8));

        m_pUi->faultstatus_groupBox02->setTitle(QApplication::translate("faultconditionForm",
          "\346\250\241\345\235\2272",
          0,
          QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->faultstatus_groupBox01->setTitle("Module1");
        m_pUi->faultstatus_groupBox02->setTitle("Module2");
    }
    init(m_yellowicon);//初始化
}
void CFaultConditionWidget::radioButton0304_clicked()
{
    ifaultindex=1;
    if(g_iLangChange)
    {
        m_pUi->faultstatus_groupBox01->setTitle(QApplication::translate("faultconditionForm",
         "\346\250\241\345\235\2273",
         0,
         QApplication::UnicodeUTF8));

        m_pUi->faultstatus_groupBox02->setTitle(QApplication::translate("faultconditionForm",
          "\346\250\241\345\235\2274",
          0,
          QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->faultstatus_groupBox01->setTitle("Module3");
        m_pUi->faultstatus_groupBox02->setTitle("Module4");
    }
     init(m_yellowicon);//初始化
}
void CFaultConditionWidget::radioButton0506_clicked()
{
    ifaultindex=2;
    if(g_iLangChange)
    {
        m_pUi->faultstatus_groupBox01->setTitle(QApplication::translate("faultconditionForm",
         "\346\250\241\345\235\2275",
         0,
         QApplication::UnicodeUTF8));

        m_pUi->faultstatus_groupBox02->setTitle(QApplication::translate("faultconditionForm",
          "\346\250\241\345\235\2276",
          0,
          QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->faultstatus_groupBox01->setTitle("Module5");
        m_pUi->faultstatus_groupBox02->setTitle("Module6");
    }
    init(m_yellowicon);//初始化
}
void CFaultConditionWidget::radioButton0708_clicked()
{
    ifaultindex=3;
    if(g_iLangChange)
    {
        m_pUi->faultstatus_groupBox01->setTitle(QApplication::translate("faultconditionForm",
         "\346\250\241\345\235\2277",
         0,
         QApplication::UnicodeUTF8));

        m_pUi->faultstatus_groupBox02->setTitle(QApplication::translate("faultconditionForm",
          "\346\250\241\345\235\2278",
          0,
          QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->faultstatus_groupBox01->setTitle("Module7");
        m_pUi->faultstatus_groupBox02->setTitle("Module8");
    }
    init(m_yellowicon);//初始化
}

void CFaultConditionWidget::radioButton0910_clicked()
{
    ifaultindex=4;
    if(g_iLangChange)
    {
        m_pUi->faultstatus_groupBox01->setTitle(QApplication::translate("faultconditionForm",
         "\346\250\241\345\235\2279",
         0,
         QApplication::UnicodeUTF8));

        m_pUi->faultstatus_groupBox02->setTitle(QApplication::translate("faultconditionForm",
          "\346\250\241\345\235\22710",
          0,
          QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->faultstatus_groupBox01->setTitle("Module9");
        m_pUi->faultstatus_groupBox02->setTitle("Module10");
    }
    init(m_yellowicon);//初始化
}

void CFaultConditionWidget::radioButton1112_clicked()
{
    ifaultindex=5;
    if(g_iLangChange)
    {
        m_pUi->faultstatus_groupBox01->setTitle(QApplication::translate("faultconditionForm",
         "\346\250\241\345\235\22711",
         0,
         QApplication::UnicodeUTF8));

        m_pUi->faultstatus_groupBox02->setTitle(QApplication::translate("faultconditionForm",
          "\346\250\241\345\235\22712",
          0,
          QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->faultstatus_groupBox01->setTitle("Module11");
        m_pUi->faultstatus_groupBox02->setTitle("Module12");
    }
    init(m_yellowicon);//初始化
}
void CFaultConditionWidget::radioButton1314_clicked()
{
    ifaultindex=6;
    if(g_iLangChange)
    {
        m_pUi->faultstatus_groupBox01->setTitle(QApplication::translate("faultconditionForm",
         "\346\250\241\345\235\22713",
         0,
         QApplication::UnicodeUTF8));

        m_pUi->faultstatus_groupBox02->setTitle(QApplication::translate("faultconditionForm",
          "\346\250\241\345\235\22714",
          0,
          QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->faultstatus_groupBox01->setTitle("Module13");
        m_pUi->faultstatus_groupBox02->setTitle("Module14");
    }
    init(m_yellowicon);//初始化
}
void CFaultConditionWidget::radioButton1516_clicked()
{
    ifaultindex=7;
    if(g_iLangChange)
    {
        m_pUi->faultstatus_groupBox01->setTitle(QApplication::translate("faultconditionForm",
         "\346\250\241\345\235\22715",
         0,
         QApplication::UnicodeUTF8));

        m_pUi->faultstatus_groupBox02->setTitle(QApplication::translate("faultconditionForm",
          "\346\250\241\345\235\22716",
          0,
          QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->faultstatus_groupBox01->setTitle("Module15");
        m_pUi->faultstatus_groupBox02->setTitle("Module16");
    }
    init(m_yellowicon);//初始化
}
void CFaultConditionWidget::init(QIcon icon)
{
    //左侧--输出过压
    m_pUi->toolButton_71->setIcon(icon);
    m_pUi->toolButton_71->setIconSize(QSize(28, 28));
    //左侧--模拟谱型信号幅值超范围
    m_pUi->toolButton_72->setIcon(icon);
    m_pUi->toolButton_72->setIconSize(QSize(28, 28));
    //左侧--输入直流过压
    m_pUi->toolButton_73->setIcon(icon);
    m_pUi->toolButton_73->setIconSize(QSize(28, 28));
    //左侧--模拟谱型信号频率超范围
    m_pUi->toolButton_74->setIcon(icon);
    m_pUi->toolButton_74->setIconSize(QSize(28, 28));
    //左侧--输入直流欠压
    m_pUi->toolButton_75->setIcon(icon);
    m_pUi->toolButton_75->setIconSize(QSize(28, 28));
    //左侧--数字谱型信号幅值超范围
    m_pUi->toolButton_76->setIcon(icon);
    m_pUi->toolButton_76->setIconSize(QSize(28, 28));
    //左侧--输出交流电流报警
    m_pUi->toolButton_77->setIcon(icon);
    m_pUi->toolButton_77->setIconSize(QSize(28, 28));
    //左侧--数字谱型信号频率超范围
    m_pUi->toolButton_78->setIcon(icon);
    m_pUi->toolButton_78->setIconSize(QSize(28, 28));
    //左侧--输出交流电流保护
    m_pUi->toolButton_79->setIcon(icon);
    m_pUi->toolButton_79->setIconSize(QSize(28, 28));
    //左侧--IGBT1驱动保护
    m_pUi->toolButton_80->setIcon(icon);
    m_pUi->toolButton_80->setIconSize(QSize(28, 28));
    //左侧--IGBT1过温保护
    m_pUi->toolButton_81->setIcon(icon);
    m_pUi->toolButton_81->setIconSize(QSize(28, 28));
    //左侧--IGBT2驱动保护
    m_pUi->toolButton_82->setIcon(icon);
    m_pUi->toolButton_82->setIconSize(QSize(28, 28));
    //左侧--IGBT2过温保护
    m_pUi->toolButton_83->setIcon(icon);
    m_pUi->toolButton_83->setIconSize(QSize(28, 28));
    //左侧--IGBT3驱动保护
    m_pUi->toolButton_84->setIcon(icon);
    m_pUi->toolButton_84->setIconSize(QSize(28, 28));
    //左侧--电感1过温保护
    m_pUi->toolButton_85->setIcon(icon);
    m_pUi->toolButton_85->setIconSize(QSize(28, 28));
    //左侧--IGBT4驱动保护
    m_pUi->toolButton_86->setIcon(icon);
    m_pUi->toolButton_86->setIconSize(QSize(28, 28));
    //左侧--电感2过温保护
    m_pUi->toolButton_87->setIcon(icon);
    m_pUi->toolButton_87->setIconSize(QSize(28, 28));
    //左侧--IGBT5驱动保护
    m_pUi->toolButton_88->setIcon(icon);
    m_pUi->toolButton_88->setIconSize(QSize(28, 28));
    //左侧--驱动脉冲封锁
    m_pUi->toolButton_89->setIcon(icon);
    m_pUi->toolButton_89->setIconSize(QSize(28, 28));
    //左侧--IGBT6驱动保护
    m_pUi->toolButton_90->setIcon(icon);
    m_pUi->toolButton_90->setIconSize(QSize(28, 28));
    //左侧--数字谱型信号中断
    m_pUi->toolButton_91->setIcon(icon);
    m_pUi->toolButton_91->setIconSize(QSize(28, 28));
    //左侧--输出电压报警
    m_pUi->toolButton_113->setIcon(icon);
    m_pUi->toolButton_113->setIconSize(QSize(28, 28));
    //右侧--输出过压
    m_pUi->toolButton_92->setIcon(icon);
    m_pUi->toolButton_92->setIconSize(QSize(28, 28));
    //右侧--模拟谱型信号幅值超范围
    m_pUi->toolButton_93->setIcon(icon);
    m_pUi->toolButton_93->setIconSize(QSize(28, 28));
    //右侧--输入直流过压
    m_pUi->toolButton_94->setIcon(icon);
    m_pUi->toolButton_94->setIconSize(QSize(28, 28));
    //右侧--模拟谱型信号频率超范围
    m_pUi->toolButton_95->setIcon(icon);
    m_pUi->toolButton_95->setIconSize(QSize(28, 28));
    //右侧--输入直流欠压
    m_pUi->toolButton_96->setIcon(icon);
    m_pUi->toolButton_96->setIconSize(QSize(28, 28));
    //右侧--数字谱型信号幅值超范围
    m_pUi->toolButton_97->setIcon(icon);
    m_pUi->toolButton_97->setIconSize(QSize(28, 28));
    //右侧--输出交流电流报警
    m_pUi->toolButton_98->setIcon(icon);
    m_pUi->toolButton_98->setIconSize(QSize(28, 28));
    //右侧--数字谱型信号频率超范围
    m_pUi->toolButton_99->setIcon(icon);
    m_pUi->toolButton_99->setIconSize(QSize(28, 28));
    //右侧--输出交流电流保护
    m_pUi->toolButton_100->setIcon(icon);
    m_pUi->toolButton_100->setIconSize(QSize(28, 28));
    //右侧--IGBT1驱动保护
    m_pUi->toolButton_101->setIcon(icon);
    m_pUi->toolButton_101->setIconSize(QSize(28, 28));
    //右侧--IGBT1过温保护
    m_pUi->toolButton_102->setIcon(icon);
    m_pUi->toolButton_102->setIconSize(QSize(28, 28));
    //右侧--IGBT2驱动保护
    m_pUi->toolButton_103->setIcon(icon);
    m_pUi->toolButton_103->setIconSize(QSize(28, 28));
    //右侧--IGBT2过温保护
    m_pUi->toolButton_104->setIcon(icon);
    m_pUi->toolButton_104->setIconSize(QSize(28, 28));
    //右侧--IGBT3驱动保护
    m_pUi->toolButton_105->setIcon(icon);
    m_pUi->toolButton_105->setIconSize(QSize(28, 28));
    //右侧--电感1过温保护
    m_pUi->toolButton_106->setIcon(icon);
    m_pUi->toolButton_106->setIconSize(QSize(28, 28));
    //右侧--IGBT4驱动保护
    m_pUi->toolButton_107->setIcon(icon);
    m_pUi->toolButton_107->setIconSize(QSize(28, 28));
    //右侧--电感2过温保护
    m_pUi->toolButton_108->setIcon(icon);
    m_pUi->toolButton_108->setIconSize(QSize(28, 28));
    //右侧--IGBT5驱动保护
    m_pUi->toolButton_109->setIcon(icon);
    m_pUi->toolButton_109->setIconSize(QSize(28, 28));
    //右侧--驱动脉冲封锁
    m_pUi->toolButton_110->setIcon(icon);
    m_pUi->toolButton_110->setIconSize(QSize(28, 28));
    //右侧--IGBT6驱动保护
    m_pUi->toolButton_111->setIcon(icon);
    m_pUi->toolButton_111->setIconSize(QSize(28, 28));
    //右侧--数字谱型信号中断
    m_pUi->toolButton_112->setIcon(icon);
    m_pUi->toolButton_112->setIconSize(QSize(28, 28));
    //右侧--输出电压报警
    m_pUi->toolButton_114->setIcon(icon);
    m_pUi->toolButton_114->setIconSize(QSize(28, 28));
}
//更新故障状态数据灯
void CFaultConditionWidget::updateFaultConditionData(int index,STRU_FAULTSTATUS *pLeftFaultStatData,STRU_FAULTSTATUS *pRightStruFaultStatData)
{
    //左侧--输出过压
    m_pUi->toolButton_71->setIcon(IconColorByValue(pLeftFaultStatData[index].iOutovervoltFlag));
    m_pUi->toolButton_71->setIconSize(QSize(28, 28));
    //左侧--模拟谱型信号幅值超范围
    m_pUi->toolButton_72->setIcon(IconColorByValue(pLeftFaultStatData[index].iAnaspecampoverFlag));
    m_pUi->toolButton_72->setIconSize(QSize(28, 28));
    //左侧--输入直流过压
    m_pUi->toolButton_73->setIcon(IconColorByValue(pLeftFaultStatData[index].iDCovervoltFlag));
    m_pUi->toolButton_73->setIconSize(QSize(28, 28));
    //左侧--模拟谱型信号频率超范围
    m_pUi->toolButton_74->setIcon(IconColorByValue(pLeftFaultStatData[index].iAnaspecfreqoverFlag));
    m_pUi->toolButton_74->setIconSize(QSize(28, 28));
    //左侧--输入直流欠压
    m_pUi->toolButton_75->setIcon(IconColorByValue(pLeftFaultStatData[index].iDCundervoltFlag));
    m_pUi->toolButton_75->setIconSize(QSize(28, 28));
    //左侧--数字谱型信号幅值超范围
    m_pUi->toolButton_76->setIcon(IconColorByValue(pLeftFaultStatData[index].iDigspecampoverFlag));
    m_pUi->toolButton_76->setIconSize(QSize(28, 28));
    //左侧--输出交流电流报警
    m_pUi->toolButton_77->setIcon(IconColorByValue(pLeftFaultStatData[index].iACcurrentwarnFlag));
    m_pUi->toolButton_77->setIconSize(QSize(28, 28));
    //左侧--数字谱型信号频率超范围
    m_pUi->toolButton_78->setIcon(IconColorByValue(pLeftFaultStatData[index].iDigspecfreqoverFlag));
    m_pUi->toolButton_78->setIconSize(QSize(28, 28));
    //左侧--输出交流电流保护
    m_pUi->toolButton_79->setIcon(IconColorByValue(pLeftFaultStatData[index].iACcurrentprocFlag));
    m_pUi->toolButton_79->setIconSize(QSize(28, 28));
    //左侧--IGBT1驱动保护
    m_pUi->toolButton_80->setIcon(IconColorByValue(pLeftFaultStatData[index].iIGBT1driprocFlag));
    m_pUi->toolButton_80->setIconSize(QSize(28, 28));
    //左侧--IGBT1过温保护
    m_pUi->toolButton_81->setIcon(IconColorByValue(pLeftFaultStatData[index].iIGBT1overtempFlag));
    m_pUi->toolButton_81->setIconSize(QSize(28, 28));
    //左侧--IGBT2驱动保护
    m_pUi->toolButton_82->setIcon(IconColorByValue(pLeftFaultStatData[index].iIGBT2driprocFlag));
    m_pUi->toolButton_82->setIconSize(QSize(28, 28));
    //左侧--IGBT2过温保护
    m_pUi->toolButton_83->setIcon(IconColorByValue(pLeftFaultStatData[index].iIGBT2overtempFlag));
    m_pUi->toolButton_83->setIconSize(QSize(28, 28));
    //左侧--IGBT3驱动保护
    m_pUi->toolButton_84->setIcon(IconColorByValue(pLeftFaultStatData[index].iIGBT3driprocFlag));
    m_pUi->toolButton_84->setIconSize(QSize(28, 28));
    //左侧--电感1过温保护
    m_pUi->toolButton_85->setIcon(IconColorByValue(pLeftFaultStatData[index].iIndu1overtempFlag));
    m_pUi->toolButton_85->setIconSize(QSize(28, 28));
    //左侧--IGBT4驱动保护
    m_pUi->toolButton_86->setIcon(IconColorByValue(pLeftFaultStatData[index].iIGBT4driprocFlag));
    m_pUi->toolButton_86->setIconSize(QSize(28, 28));
    //左侧--电感2过温保护
    m_pUi->toolButton_87->setIcon(IconColorByValue(pLeftFaultStatData[index].iIndu2overtempFlag));
    m_pUi->toolButton_87->setIconSize(QSize(28, 28));
    //左侧--IGBT5驱动保护
    m_pUi->toolButton_88->setIcon(IconColorByValue(pLeftFaultStatData[index].iIGBT5driprocFlag));
    m_pUi->toolButton_88->setIconSize(QSize(28, 28));
    //左侧--驱动脉冲封锁
    m_pUi->toolButton_89->setIcon(IconColorByValue(pLeftFaultStatData[index].iDripulseblockFlag));
    m_pUi->toolButton_89->setIconSize(QSize(28, 28));
    //左侧--IGBT6驱动保护
    m_pUi->toolButton_90->setIcon(IconColorByValue(pLeftFaultStatData[index].iIGBT6driprocFlag));
    m_pUi->toolButton_90->setIconSize(QSize(28, 28));
    //左侧--数字谱型信号中断
    m_pUi->toolButton_91->setIcon(IconColorByValue(pLeftFaultStatData[index].iDigspecinterFlag));
    m_pUi->toolButton_91->setIconSize(QSize(28, 28));
    //左侧--输出电压报警
    m_pUi->toolButton_113->setIcon(IconColorByValue(pLeftFaultStatData[index].iOutputvoltwarnFlag));
    m_pUi->toolButton_113->setIconSize(QSize(28, 28));

    //右侧--输出过压
    m_pUi->toolButton_92->setIcon(IconColorByValue(pRightStruFaultStatData[index].iOutovervoltFlag));
    m_pUi->toolButton_92->setIconSize(QSize(28, 28));
    //右侧--模拟谱型信号幅值超范围
    m_pUi->toolButton_93->setIcon(IconColorByValue(pRightStruFaultStatData[index].iAnaspecampoverFlag));
    m_pUi->toolButton_93->setIconSize(QSize(28, 28));
    //右侧--输入直流过压
    m_pUi->toolButton_94->setIcon(IconColorByValue(pRightStruFaultStatData[index].iDCovervoltFlag));
    m_pUi->toolButton_94->setIconSize(QSize(28, 28));
    //右侧--模拟谱型信号频率超范围
    m_pUi->toolButton_95->setIcon(IconColorByValue(pRightStruFaultStatData[index].iAnaspecfreqoverFlag));
    m_pUi->toolButton_95->setIconSize(QSize(28, 28));
    //右侧--输入直流欠压
    m_pUi->toolButton_96->setIcon(IconColorByValue(pRightStruFaultStatData[index].iDCundervoltFlag));
    m_pUi->toolButton_96->setIconSize(QSize(28, 28));
    //右侧--数字谱型信号幅值超范围
    m_pUi->toolButton_97->setIcon(IconColorByValue(pRightStruFaultStatData[index].iDigspecampoverFlag));
    m_pUi->toolButton_97->setIconSize(QSize(28, 28));
    //右侧--输出交流电流报警
    m_pUi->toolButton_98->setIcon(IconColorByValue(pRightStruFaultStatData[index].iACcurrentwarnFlag));
    m_pUi->toolButton_98->setIconSize(QSize(28, 28));
    //右侧--数字谱型信号频率超范围
    m_pUi->toolButton_99->setIcon(IconColorByValue(pRightStruFaultStatData[index].iDigspecfreqoverFlag));
    m_pUi->toolButton_99->setIconSize(QSize(28, 28));
    //右侧--输出交流电流保护
    m_pUi->toolButton_100->setIcon(IconColorByValue(pRightStruFaultStatData[index].iACcurrentprocFlag));
    m_pUi->toolButton_100->setIconSize(QSize(28, 28));
    //右侧--IGBT1驱动保护
    m_pUi->toolButton_101->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIGBT1driprocFlag));
    m_pUi->toolButton_101->setIconSize(QSize(28, 28));
    //右侧--IGBT1过温保护
    m_pUi->toolButton_102->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIGBT1overtempFlag));
    m_pUi->toolButton_102->setIconSize(QSize(28, 28));
    //右侧--IGBT2驱动保护
    m_pUi->toolButton_103->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIGBT2driprocFlag));
    m_pUi->toolButton_103->setIconSize(QSize(28, 28));
    //右侧--IGBT2过温保护
    m_pUi->toolButton_104->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIGBT2overtempFlag));
    m_pUi->toolButton_104->setIconSize(QSize(28, 28));
    //右侧--IGBT3驱动保护
    m_pUi->toolButton_105->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIGBT3driprocFlag));
    m_pUi->toolButton_105->setIconSize(QSize(28, 28));
    //右侧--电感1过温保护
    m_pUi->toolButton_106->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIndu1overtempFlag));
    m_pUi->toolButton_106->setIconSize(QSize(28, 28));
    //右侧--IGBT4驱动保护
    m_pUi->toolButton_107->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIGBT4driprocFlag));
    m_pUi->toolButton_107->setIconSize(QSize(28, 28));
    //右侧--电感2过温保护
    m_pUi->toolButton_108->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIndu2overtempFlag));
    m_pUi->toolButton_108->setIconSize(QSize(28, 28));
    //右侧--IGBT5驱动保护
    m_pUi->toolButton_109->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIGBT5driprocFlag));
    m_pUi->toolButton_109->setIconSize(QSize(28, 28));
    //右侧--驱动脉冲封锁
    m_pUi->toolButton_110->setIcon(IconColorByValue(pRightStruFaultStatData[index].iDripulseblockFlag));
    m_pUi->toolButton_110->setIconSize(QSize(28, 28));
    //右侧--IGBT6驱动保护
    m_pUi->toolButton_111->setIcon(IconColorByValue(pRightStruFaultStatData[index].iIGBT6driprocFlag));
    m_pUi->toolButton_111->setIconSize(QSize(28, 28));
    //右侧--数字谱型信号中断
    m_pUi->toolButton_112->setIcon(IconColorByValue(pRightStruFaultStatData[index].iDigspecinterFlag));
    m_pUi->toolButton_112->setIconSize(QSize(28, 28));
    //右侧--输出电压报警
    m_pUi->toolButton_114->setIcon(IconColorByValue(pRightStruFaultStatData[index].iOutputvoltwarnFlag));
    m_pUi->toolButton_114->setIconSize(QSize(28, 28));
}
QIcon CFaultConditionWidget::IconColorByValue(int nValue)
{
    QIcon Icon;
    switch(nValue)
    {
    case 0:
        Icon=m_greenicon;
        break;
    case 1:
        Icon=m_redicon;
        break;
    default:
        Icon=m_yellowicon;
        break;
    }
    return Icon;
}
void CFaultConditionWidget::faultLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("faultconditionForm", "\346\225\205\351\232\234\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        m_pUi->groupBox_8->setTitle(QApplication::translate("faultconditionForm", "\346\250\241\345\235\227\347\273\204\345\217\267\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        m_pUi->radioButton0102->setText(QApplication::translate("faultconditionForm", "\346\250\241\345\235\22701-02", 0, QApplication::UnicodeUTF8));
        m_pUi->radioButton0304->setText(QApplication::translate("faultconditionForm", "\346\250\241\345\235\22703-04", 0, QApplication::UnicodeUTF8));
        m_pUi->radioButton0506->setText(QApplication::translate("faultconditionForm", "\346\250\241\345\235\22705-06", 0, QApplication::UnicodeUTF8));
        m_pUi->radioButton0708->setText(QApplication::translate("faultconditionForm", "\346\250\241\345\235\22707-08", 0, QApplication::UnicodeUTF8));
        m_pUi->radioButton0910->setText(QApplication::translate("faultconditionForm", "\346\250\241\345\235\22709-10", 0, QApplication::UnicodeUTF8));
        m_pUi->radioButton1112->setText(QApplication::translate("faultconditionForm", "\346\250\241\345\235\22711-12", 0, QApplication::UnicodeUTF8));
        m_pUi->radioButton1314->setText(QApplication::translate("faultconditionForm", "\346\250\241\345\235\22713-14", 0, QApplication::UnicodeUTF8));
        m_pUi->radioButton1516->setText(QApplication::translate("faultconditionForm", "\346\250\241\345\235\22715-16", 0, QApplication::UnicodeUTF8));
        if(m_pUi->radioButton0102->isChecked())
        {
            radioButton0102_clicked();
        }
        if(m_pUi->radioButton0304->isChecked())
        {
            radioButton0304_clicked();
        }
        if(m_pUi->radioButton0506->isChecked())
        {
            radioButton0506_clicked();
        }
        if(m_pUi->radioButton0708->isChecked())
        {
            radioButton0708_clicked();
        }
        if(m_pUi->radioButton0910->isChecked())
        {
            radioButton0910_clicked();
        }
        if(m_pUi->radioButton1112->isChecked())
        {
            radioButton1112_clicked();
        }
        if(m_pUi->radioButton1314->isChecked())
        {
            radioButton1314_clicked();
        }
        if(m_pUi->radioButton1516->isChecked())
        {
            radioButton1516_clicked();
        }
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        m_pUi->label_164->setText(QApplication::translate("faultconditionForm", "\347\224\265\346\272\220\346\254\240\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_164->setFont(font);
        m_pUi->label_166->setText(QApplication::translate("faultconditionForm", "\346\257\215\347\272\277\347\224\265\345\216\213\350\277\207\344\275\216", 0, QApplication::UnicodeUTF8));
        m_pUi->label_166->setFont(font);
        m_pUi->label_204->setText(QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\347\224\265\345\216\213\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        m_pUi->label_204->setFont(font);
        m_pUi->label_162->setText(QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\347\224\265\345\216\213\350\277\207\351\253\230", 0, QApplication::UnicodeUTF8));
        m_pUi->label_162->setFont(font);
        m_pUi->label_168->setText(QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\347\224\265\346\265\201\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        m_pUi->label_168->setFont(font);
        m_pUi->label_170->setText(QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\347\224\265\346\265\201\350\277\207\351\253\230", 0, QApplication::UnicodeUTF8));
        m_pUi->label_170->setFont(font);
        m_pUi->label_176->setText(QApplication::translate("faultconditionForm", "\347\224\265\346\204\237\346\270\251\345\272\246\350\277\207\351\253\230", 0, QApplication::UnicodeUTF8));
        m_pUi->label_176->setFont(font);
        m_pUi->label_180->setText(QApplication::translate("faultconditionForm", "\351\251\261\345\212\250\350\204\211\345\206\262\345\260\201\351\224\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_180->setFont(font);
        m_pUi->label_174->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        m_pUi->label_174->setFont(font);
        m_pUi->label_178->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2112", 0, QApplication::UnicodeUTF8));
        m_pUi->label_178->setFont(font);
        m_pUi->label_182->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2113", 0, QApplication::UnicodeUTF8));
        m_pUi->label_182->setFont(font);
        m_pUi->label_172->setText(QApplication::translate("faultconditionForm", "IGBT\350\277\207\346\270\251\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_172->setFont(font);
        m_pUi->label_171->setText(QApplication::translate("faultconditionForm", "IGBT1\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_171->setFont(font);
        m_pUi->label_173->setText(QApplication::translate("faultconditionForm", "IGBT2\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_173->setFont(font);
        m_pUi->label_175->setText(QApplication::translate("faultconditionForm", "IGBT3\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_175->setFont(font);
        m_pUi->label_177->setText(QApplication::translate("faultconditionForm", "IGBT4\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_177->setFont(font);
        m_pUi->label_179->setText(QApplication::translate("faultconditionForm", "IGBT5\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_179->setFont(font);
        m_pUi->label_181->setText(QApplication::translate("faultconditionForm", "IGBT6\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_181->setFont(font);
        m_pUi->label_163->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2114", 0, QApplication::UnicodeUTF8));
        m_pUi->label_163->setFont(font);
        m_pUi->label_165->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2115", 0, QApplication::UnicodeUTF8));
        m_pUi->label_165->setFont(font);
        m_pUi->label_167->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2116", 0, QApplication::UnicodeUTF8));
        m_pUi->label_167->setFont(font);
        m_pUi->label_169->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2117", 0, QApplication::UnicodeUTF8));
        m_pUi->label_169->setFont(font);


        m_pUi->label_185->setText(QApplication::translate("faultconditionForm", "\347\224\265\346\272\220\346\254\240\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->label_185->setFont(font);
        m_pUi->label_187->setText(QApplication::translate("faultconditionForm", "\346\257\215\347\272\277\347\224\265\345\216\213\350\277\207\344\275\216", 0, QApplication::UnicodeUTF8));
        m_pUi->label_187->setFont(font);
        m_pUi->label_205->setText(QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\347\224\265\345\216\213\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        m_pUi->label_205->setFont(font);
        m_pUi->label_183->setText(QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\347\224\265\345\216\213\350\277\207\351\253\230", 0, QApplication::UnicodeUTF8));
        m_pUi->label_183->setFont(font);
        m_pUi->label_189->setText(QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\347\224\265\346\265\201\346\212\245\350\255\246", 0, QApplication::UnicodeUTF8));
        m_pUi->label_189->setFont(font);
        m_pUi->label_191->setText(QApplication::translate("faultconditionForm", "\350\276\223\345\207\272\347\224\265\346\265\201\350\277\207\351\253\230", 0, QApplication::UnicodeUTF8));
        m_pUi->label_191->setFont(font);
        m_pUi->label_197->setText(QApplication::translate("faultconditionForm", "\347\224\265\346\204\237\346\270\251\345\272\246\350\277\207\351\253\230", 0, QApplication::UnicodeUTF8));
        m_pUi->label_197->setFont(font);
        m_pUi->label_201->setText(QApplication::translate("faultconditionForm", "\351\251\261\345\212\250\350\204\211\345\206\262\345\260\201\351\224\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_201->setFont(font);
        m_pUi->label_195->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        m_pUi->label_195->setFont(font);
        m_pUi->label_199->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2112", 0, QApplication::UnicodeUTF8));
        m_pUi->label_199->setFont(font);
        m_pUi->label_203->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2113", 0, QApplication::UnicodeUTF8));
        m_pUi->label_203->setFont(font);
        m_pUi->label_193->setText(QApplication::translate("faultconditionForm", "IGBT\350\277\207\346\270\251\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_193->setFont(font);
        m_pUi->label_192->setText(QApplication::translate("faultconditionForm", "IGBT1\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_192->setFont(font);
        m_pUi->label_194->setText(QApplication::translate("faultconditionForm", "IGBT2\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_194->setFont(font);
        m_pUi->label_196->setText(QApplication::translate("faultconditionForm", "IGBT3\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_196->setFont(font);
        m_pUi->label_198->setText(QApplication::translate("faultconditionForm", "IGBT4\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_198->setFont(font);
        m_pUi->label_200->setText(QApplication::translate("faultconditionForm", "IGBT5\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_200->setFont(font);
        m_pUi->label_202->setText(QApplication::translate("faultconditionForm", "IGBT6\351\251\261\345\212\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        m_pUi->label_202->setFont(font);
        m_pUi->label_184->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2114", 0, QApplication::UnicodeUTF8));
        m_pUi->label_184->setFont(font);
        m_pUi->label_186->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2115", 0, QApplication::UnicodeUTF8));
        m_pUi->label_186->setFont(font);
        m_pUi->label_188->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2116", 0, QApplication::UnicodeUTF8));
        m_pUi->label_188->setFont(font);
        m_pUi->label_190->setText(QApplication::translate("faultconditionForm", "\350\207\252\345\256\232\344\271\2117", 0, QApplication::UnicodeUTF8));
        m_pUi->label_190->setFont(font);
    }
    else
    {
        setWindowTitle("Fault");
        m_pUi->groupBox_8->setTitle("Module Group Number Selection");
        m_pUi->radioButton0102->setText("Module01-02");
        m_pUi->radioButton0304->setText("Module03-04");
        m_pUi->radioButton0506->setText("Module05-06");
        m_pUi->radioButton0708->setText("Module07-08");
        m_pUi->radioButton0910->setText("Module09-10");
        m_pUi->radioButton1112->setText("Module11-12");
        m_pUi->radioButton1314->setText("Module13-14");
        m_pUi->radioButton1516->setText("Module15-16");
        if(m_pUi->radioButton0102->isChecked())
        {
            radioButton0102_clicked();
        }
        if(m_pUi->radioButton0304->isChecked())
        {
            radioButton0304_clicked();
        }
        if(m_pUi->radioButton0506->isChecked())
        {
            radioButton0506_clicked();
        }
        if(m_pUi->radioButton0708->isChecked())
        {
            radioButton0708_clicked();
        }
        if(m_pUi->radioButton0910->isChecked())
        {
            radioButton0910_clicked();
        }
        if(m_pUi->radioButton1112->isChecked())
        {
            radioButton1112_clicked();
        }
        if(m_pUi->radioButton1314->isChecked())
        {
            radioButton1314_clicked();
        }
        if(m_pUi->radioButton1516->isChecked())
        {
            radioButton1516_clicked();
        }
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        m_pUi->label_164->setText("Power U/V");
        m_pUi->label_164->setFont(font);
        m_pUi->label_166->setText("Module DC U/V");
        m_pUi->label_166->setFont(font);
        m_pUi->label_204->setText("Output Voltage Alarm");
        m_pUi->label_204->setFont(font);
        m_pUi->label_162->setText("Output Voltage O/V");
        m_pUi->label_162->setFont(font);
        m_pUi->label_168->setText("Output Current Alarm");
        m_pUi->label_168->setFont(font);
        m_pUi->label_170->setText("Output Current O/V");
        m_pUi->label_170->setFont(font);
        m_pUi->label_176->setText("L.T OverTEMP");
        m_pUi->label_176->setFont(font);
        m_pUi->label_180->setText("PWM Block");
        m_pUi->label_180->setFont(font);
        m_pUi->label_174->setText("External1");
        m_pUi->label_174->setFont(font);
        m_pUi->label_178->setText("External2");
        m_pUi->label_178->setFont(font);
        m_pUi->label_182->setText("External3");
        m_pUi->label_182->setFont(font);
        m_pUi->label_172->setText("IGBT OverTEMP");
        m_pUi->label_172->setFont(font);
        m_pUi->label_171->setText("IGBT1 drive protection");
        m_pUi->label_171->setFont(font);
        m_pUi->label_173->setText("IGBT2 drive protection");
        m_pUi->label_173->setFont(font);
        m_pUi->label_175->setText("IGBT3 drive protection");
        m_pUi->label_175->setFont(font);
        m_pUi->label_177->setText("IGBT4 drive protection");
        m_pUi->label_177->setFont(font);
        m_pUi->label_179->setText("IGBT5 drive protection");
        m_pUi->label_179->setFont(font);
        m_pUi->label_181->setText("IGBT6 drive protection");
        m_pUi->label_181->setFont(font);
        m_pUi->label_163->setText("External4");
        m_pUi->label_163->setFont(font);
        m_pUi->label_165->setText("External5");
        m_pUi->label_165->setFont(font);
        m_pUi->label_167->setText("External6");
        m_pUi->label_167->setFont(font);
        m_pUi->label_169->setText("External7");
        m_pUi->label_169->setFont(font);

        m_pUi->label_185->setText("Power U/V");
        m_pUi->label_185->setFont(font);
        m_pUi->label_187->setText("Module DC U/V");
        m_pUi->label_187->setFont(font);
        m_pUi->label_205->setText("Output Voltage Alarm");
        m_pUi->label_205->setFont(font);
        m_pUi->label_183->setText("Output Voltage O/V");
        m_pUi->label_183->setFont(font);
        m_pUi->label_189->setText("Output Current Alarm");
        m_pUi->label_189->setFont(font);
        m_pUi->label_191->setText("Output Current O/V");
        m_pUi->label_191->setFont(font);
        m_pUi->label_197->setText("L.T OverTEMP");
        m_pUi->label_197->setFont(font);
        m_pUi->label_201->setText("PWM Block");
        m_pUi->label_201->setFont(font);
        m_pUi->label_195->setText("External1");
        m_pUi->label_195->setFont(font);
        m_pUi->label_199->setText("External2");
        m_pUi->label_199->setFont(font);
        m_pUi->label_203->setText("External3");
        m_pUi->label_203->setFont(font);
        m_pUi->label_193->setText("IGBT OverTEMP");
        m_pUi->label_193->setFont(font);
        m_pUi->label_192->setText("IGBT1 drive protection");
        m_pUi->label_192->setFont(font);
        m_pUi->label_194->setText("IGBT2 drive protection");
        m_pUi->label_194->setFont(font);
        m_pUi->label_196->setText("IGBT3 drive protection");
        m_pUi->label_196->setFont(font);
        m_pUi->label_198->setText("IGBT4 drive protection");
        m_pUi->label_198->setFont(font);
        m_pUi->label_200->setText("IGBT5 drive protection");
        m_pUi->label_200->setFont(font);
        m_pUi->label_202->setText("IGBT6 drive protection");
        m_pUi->label_202->setFont(font);
        m_pUi->label_184->setText("External4");
        m_pUi->label_184->setFont(font);
        m_pUi->label_186->setText("External5");
        m_pUi->label_186->setFont(font);
        m_pUi->label_188->setText("External6");
        m_pUi->label_188->setFont(font);
        m_pUi->label_190->setText("External7");
        m_pUi->label_190->setFont(font);
    }
}
/*返回键槽函数实现 add by 2020.08.10*/
void CFaultConditionWidget::closeBtn_clicked()
{
        close();
}
