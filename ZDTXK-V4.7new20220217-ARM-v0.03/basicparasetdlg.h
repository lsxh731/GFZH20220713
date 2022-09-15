/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: basicparasetdlg.h
** 摘要: 基本参数对话框
**       
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.06.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.06.01   V1.0      创建
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
	void okBtn_clicked();                  //确定-槽函数
	void cancelBtn_clicked();              //取消-槽函数
	//删去母线电压和三相电压设置 add by 2020.18.19
	/*
	void BusVoltUplEdit_clicked();         //母线电压上限(V)-编辑槽函数
	void BusVoltDownlEdit_clicked();       //母线电压下限(V)-编辑槽函数
	void ThreeVoltUplEdit_clicked();       //三相电压上限(V)-编辑槽函数
	void ThreeVoltDownlEdit_clicked();     //三相电压下限(V)-编辑槽函数
	void ThreeVoltImbalancelEdit_clicked();//三相电压不均衡度(%)-编辑槽函数
	*/
	void Sub1CurrentUplEdit_clicked();      //分柜1输出电流上限(A)-编辑槽函数
	void Sub2CurrentUplEdit_clicked();      //分柜2输出电流上限(A)-编辑槽函数
	void Sub3CurrentUplEdit_clicked();      //分柜3输出电流上限(A)-编辑槽函数
	void Sub4CurrentUplEdit_clicked();      //分柜4输出电流上限(A)-编辑槽函数
	void GfTotalVoltUplEdit_clicked();     //功放总输出电压上限(V)-编辑槽函数
	void GfTotalCurrentUplEdit_clicked();  //功放总输出电流上限(A)-编辑槽函数

	void checkBoxSub1_clicked();          //分柜1选择-槽函数
	void checkBoxSub2_clicked();          //分柜2选择-槽函数
	void checkBoxSub3_clicked();          //分柜3选择-槽函数
	void checkBoxSub4_clicked();          //分柜4选择-槽函数
public:
	void basicparaLangChange();
	void initPara();//初始化参数改为public，add by 2020.11.23
private:
	void initSignalAndSlot();//初始化信号与槽关系
	void openDigKeyBoardDlg(QLineEdit *lineEdit);

public:
    Ui::basicparasetDialog *m_pUi;//改为public，add by 2020.11.23
private:
	CKeyBoardDlg m_KeyBoardDlg;    //数字键盘类对象
	QString m_strInfo;             //友情提示语
	QString m_strErrinfo;          //错误提示语
	QString m_strInvalidinfo;      //不合法提示
	QString m_strSaveSuccess;      //基本参数配置文件保存成功提示语
	QString m_strSaveFail;         //基本参数配置文件保存失败提示语
	STRU_BASICPARA m_struBasicpara;//基本参数变量
	CInifileparse  m_IniBasicParse;//基本参数ini文件读写类对象 
};
#endif //#define BASIC_PARA_SET_DLG_H