/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: basicparasetdlg.h
** ժҪ: ���������Ի���
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2019.06.01
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2019.06.01   V1.0      ����
**
****************************************************************************/
#ifndef BASIC_PARA_SET_DLG_H
#define BASIC_PARA_SET_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_basicparaset.h"
#include "inifileparse.h"
#include "keyboarddlg.h"
#include "commmacro.h"
namespace Ui
{
    class basicparasetDialog;
}
class CBasicParaSetdlg:public QDialog
{
    Q_OBJECT
public:
    CBasicParaSetdlg();
    ~CBasicParaSetdlg();
public Q_SLOTS:
	void okBtn_clicked();                  //ȷ��-�ۺ���
	void cancelBtn_clicked();              //ȡ��-�ۺ���
	//ɾȥĸ�ߵ�ѹ�������ѹ���� add by 2020.18.19
	/*
	void BusVoltUplEdit_clicked();         //ĸ�ߵ�ѹ����(V)-�༭�ۺ���
	void BusVoltDownlEdit_clicked();       //ĸ�ߵ�ѹ����(V)-�༭�ۺ���
	void ThreeVoltUplEdit_clicked();       //�����ѹ����(V)-�༭�ۺ���
	void ThreeVoltDownlEdit_clicked();     //�����ѹ����(V)-�༭�ۺ���
	void ThreeVoltImbalancelEdit_clicked();//�����ѹ�������(%)-�༭�ۺ���
	*/
	void Sub1CurrentUplEdit_clicked();      //�ֹ�1�����������(A)-�༭�ۺ���
	void Sub2CurrentUplEdit_clicked();      //�ֹ�2�����������(A)-�༭�ۺ���
	void Sub3CurrentUplEdit_clicked();      //�ֹ�3�����������(A)-�༭�ۺ���
	void Sub4CurrentUplEdit_clicked();      //�ֹ�4�����������(A)-�༭�ۺ���
	void GfTotalVoltUplEdit_clicked();     //�����������ѹ����(V)-�༭�ۺ���
	void GfTotalCurrentUplEdit_clicked();  //�����������������(A)-�༭�ۺ���

	void checkBoxSub1_clicked();          //�ֹ�1ѡ��-�ۺ���
	void checkBoxSub2_clicked();          //�ֹ�2ѡ��-�ۺ���
	void checkBoxSub3_clicked();          //�ֹ�3ѡ��-�ۺ���
	void checkBoxSub4_clicked();          //�ֹ�4ѡ��-�ۺ���
public:
	void basicparaLangChange();
	void initPara();//��ʼ��������Ϊpublic��add by 2020.11.23
private:
	void initSignalAndSlot();//��ʼ���ź���۹�ϵ
	void openDigKeyBoardDlg(QLineEdit *lineEdit);

public:
    Ui::basicparasetDialog *m_pUi;//��Ϊpublic��add by 2020.11.23
private:
	CKeyBoardDlg m_KeyBoardDlg;    //���ּ��������
	QString m_strInfo;             //������ʾ��
	QString m_strErrinfo;          //������ʾ��
	QString m_strInvalidinfo;      //���Ϸ���ʾ
	QString m_strSaveSuccess;      //�������������ļ�����ɹ���ʾ��
	QString m_strSaveFail;         //�������������ļ�����ʧ����ʾ��
	STRU_BASICPARA m_struBasicpara;//������������
	CInifileparse  m_IniBasicParse;//��������ini�ļ���д����� 
};
#endif //#define BASIC_PARA_SET_DLG_H