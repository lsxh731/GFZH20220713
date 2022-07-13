/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: gainsetdlg.cpp
** 摘要: 增益设置对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.05.12
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.05.12   V1.0      创建
****************************************************************************/
#include "gainsetdlg.h"

CGainSetdlg::CGainSetdlg()
{
    m_pUi= new Ui::gainsetDialog;
    m_pUi->setupUi(this);
    //connect (m_pUi->horizontalSlider, SIGNAL(valueChanged (int)), this, SLOT(updateProgressBarValue(int)));
    //connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    //connect(m_pUi->cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_clicked()));
}
CGainSetdlg::~CGainSetdlg()
{
}
//更新进度条-槽函数
void CGainSetdlg::updateProgressBarValue(int nValue)
{
    m_pUi->progressBar->setValue(nValue);//任何百分比都显示为宜
    m_iCurrValue=nValue;
}
//获取增益设置值
int  CGainSetdlg::getGainSetValue()
{
    return m_iCurrValue;
}
//确定槽函数
void CGainSetdlg::okBtn_clicked()
{
    this->close();
}
//取消槽函数
void CGainSetdlg::cancelBtn_clicked()
{
    this->close();
}
