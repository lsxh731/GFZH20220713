/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: gainsetdlg.cpp
** ժҪ: �������öԻ���
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2019.05.12
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2019.05.12   V1.0      ����
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
//���½�����-�ۺ���
void CGainSetdlg::updateProgressBarValue(int nValue)
{
    m_pUi->progressBar->setValue(nValue);//�κΰٷֱȶ���ʾΪ��
    m_iCurrValue=nValue;
}
//��ȡ��������ֵ
int  CGainSetdlg::getGainSetValue()
{
    return m_iCurrValue;
}
//ȷ���ۺ���
void CGainSetdlg::okBtn_clicked()
{
    this->close();
}
//ȡ���ۺ���
void CGainSetdlg::cancelBtn_clicked()
{
    this->close();
}
