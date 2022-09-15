#ifndef ADJ_COEF_DLG_H
#define ADJ_COEF_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_adjcoef.h"
#include "commmacro.h"
#include "gpiorw.h"
#include "keyboarddlg.h"
#include "inifileparse.h"
namespace Ui
{
    class adjcoefDialog;
}
class CAdjcoefdlg:public QDialog
{
    Q_OBJECT
public:
    CAdjcoefdlg(int nfd);
    ~CAdjcoefdlg();
public Q_SLOTS:
    void adjcoefBtn_clicked();//校准-槽函数
    void zeroBtn_clicked(); //零点采集-槽函数
    void resetadjBtn_clicked();//复位校准-槽函数
    void Sub1TbuslEdit_clicked();//从柜1母线电压实际值-编辑槽函数
    void Sub1AbuslEdit_clicked();//从柜1母线电压校准值-编辑槽函数
    void Sub1TactbuslEdit_clicked();//从柜1正母线电压实际值-编辑槽函数
    void Sub1AactbuslEdit_clicked();//从柜1正母线电压校准值-编辑槽函数
    void Sub1TnegbuslEdit_clicked();//从柜1负母线电压实际值-编辑槽函数
    void Sub1AnegbuslEdit_clicked();//从柜1负母线电压校准值-编辑槽函数
    void Sub1ToutvoltlEdit_clicked();//从柜1输出电压实际值-编辑槽函数
    void Sub1AoutvoltlEdit_clicked();//从柜1输出电压校准值-编辑槽函数
    void Sub1ZoutvoltlEdit_clicked();//从柜1输出电压零点值-编辑槽函数
    void Sub1ToutcurrlEdit_clicked();//从柜1输出电流实际值-编辑槽函数
    void Sub1AoutcurrlEdit_clicked();//从柜1输出电流校准值-编辑槽函数
    void Sub1ZoutcurrlEdit_clicked();//从柜1输出电流校准值-编辑槽函数

    void Sub2TbuslEdit_clicked();//从柜2母线电压实际值-编辑槽函数
    void Sub2AbuslEdit_clicked();//从柜2母线电压校准值-编辑槽函数
    void Sub2TactbuslEdit_clicked();//从柜2正母线电压实际值-编辑槽函数
    void Sub2AactbuslEdit_clicked();//从柜2正母线电压校准值-编辑槽函数
    void Sub2TnegbuslEdit_clicked();//从柜2负母线电压实际值-编辑槽函数
    void Sub2AnegbuslEdit_clicked();//从柜2负母线电压校准值-编辑槽函数
    void Sub2ToutvoltlEdit_clicked();//从柜2输出电压实际值-编辑槽函数
    void Sub2AoutvoltlEdit_clicked();//从柜2输出电压校准值-编辑槽函数
    void Sub2ZoutvoltlEdit_clicked();//从柜2输出电压零点值-编辑槽函数
    void Sub2ToutcurrlEdit_clicked();//从柜2输出电流实际值-编辑槽函数
    void Sub2AoutcurrlEdit_clicked();//从柜2输出电流校准值-编辑槽函数
    void Sub2ZoutcurrlEdit_clicked();//从柜2输出电流校准值-编辑槽函数

    void Sub3TbuslEdit_clicked();//从柜3母线电压实际值-编辑槽函数
    void Sub3AbuslEdit_clicked();//从柜3母线电压校准值-编辑槽函数
    void Sub3TactbuslEdit_clicked();//从柜3正母线电压实际值-编辑槽函数
    void Sub3AactbuslEdit_clicked();//从柜3正母线电压校准值-编辑槽函数
    void Sub3TnegbuslEdit_clicked();//从柜3负母线电压实际值-编辑槽函数
    void Sub3AnegbuslEdit_clicked();//从柜3负母线电压校准值-编辑槽函数
    void Sub3ToutvoltlEdit_clicked();//从柜3输出电压实际值-编辑槽函数
    void Sub3AoutvoltlEdit_clicked();//从柜3输出电压校准值-编辑槽函数
    void Sub3ZoutvoltlEdit_clicked();//从柜3输出电压零点值-编辑槽函数
    void Sub3ToutcurrlEdit_clicked();//从柜3输出电流实际值-编辑槽函数
    void Sub3AoutcurrlEdit_clicked();//从柜3输出电流校准值-编辑槽函数
    void Sub3ZoutcurrlEdit_clicked();//从柜3输出电流校准值-编辑槽函数

    void Sub4TbuslEdit_clicked();//从柜4母线电压实际值-编辑槽函数
    void Sub4AbuslEdit_clicked();//从柜4母线电压校准值-编辑槽函数
    void Sub4TactbuslEdit_clicked();//从柜4正母线电压实际值-编辑槽函数
    void Sub4AactbuslEdit_clicked();//从柜4正母线电压校准值-编辑槽函数
    void Sub4TnegbuslEdit_clicked();//从柜4负母线电压实际值-编辑槽函数
    void Sub4AnegbuslEdit_clicked();//从柜4负母线电压校准值-编辑槽函数
    void Sub4ToutvoltlEdit_clicked();//从柜4输出电压实际值-编辑槽函数
    void Sub4AoutvoltlEdit_clicked();//从柜4输出电压校准值-编辑槽函数
    void Sub4ZoutvoltlEdit_clicked();//从柜4输出电压零点值-编辑槽函数
    void Sub4ToutcurrlEdit_clicked();//从柜4输出电流实际值-编辑槽函数
    void Sub4AoutcurrlEdit_clicked();//从柜4输出电流校准值-编辑槽函数
    void Sub4ZoutcurrlEdit_clicked();//从柜4输出电流校准值-编辑槽函数

    void MATlEdit_clicked();//主柜A相电压实际值-编辑槽函数
    void MAAlEdit_clicked();//主柜A相电压校准值-编辑槽函数
    void MBTlEdit_clicked();//主柜B相电压实际值-编辑槽函数
    void MBAlEdit_clicked();//主柜B相电压校准值-编辑槽函数
    void MCTlEdit_clicked();//主柜C相电压实际值-编辑槽函数
    void MCAlEdit_clicked();//主柜C相电压校准值-编辑槽函数
    void MEVTlEdit_clicked();//主柜励磁电压实际值-编辑槽函数
    void MEVAlEdit_clicked();//主柜励磁电压校准值-编辑槽函数
    //void MEVZlEdit_clicked();//主柜励磁电压零点值-编辑槽函数
    void MECTlEdit_clicked();//主柜励磁电流实际值-编辑槽函数
    void MECAlEdit_clicked();//主柜励磁电流校准值-编辑槽函数
    //void MECZlEdit_clicked();//主柜励磁电流零点值-编辑槽函数
    //从柜1选择框勾选槽函数
    void s1bvcheckBox_clicked();
    void s1abvcheckBox_clicked();
    void s1nbvcheckBox_clicked();
    void s1ovcheckBox_clicked();
    void s1occheckBox_clicked();
    //从柜2选择框勾选槽函数
    void s2bvcheckBox_clicked();
    void s2abvcheckBox_clicked();
    void s2nbvcheckBox_clicked();
    void s2ovcheckBox_clicked();
    void s2occheckBox_clicked();
    //从柜3选择框勾选槽函数
    void s3bvcheckBox_clicked();
    void s3abvcheckBox_clicked();
    void s3nbvcheckBox_clicked();
    void s3ovcheckBox_clicked();
    void s3occheckBox_clicked();
    //从柜4选择框勾选槽函数
    void s4bvcheckBox_clicked();
    void s4abvcheckBox_clicked();
    void s4nbvcheckBox_clicked();
    void s4ovcheckBox_clicked();
    void s4occheckBox_clicked();
    //主柜选择框勾选槽函数
    void mAvcheckBox_clicked();
    void mBvcheckBox_clicked();
    void mCvcheckBox_clicked();
    void mevcheckBox_clicked();
    void meccheckBox_clicked();
    //范围选择选择框勾选槽函数
    void s1checkBox_clicked();
    void s2checkBox_clicked();
    void s3checkBox_clicked();
    void s4checkBox_clicked();
    void maincheckBox_clicked();
    void allcheckBox_clicked();

    void s1select();
    void s1unselect();
    void s2select();
    void s2unselect();
    void s3select();
    void s3unselect();
    void s4select();
    void s4unselect();
    void mainselect();
    void mainunselect();
    void closeBtn_clicked();        //返回键槽函数，add by 2020.08.10
public:
    void adjcoefLangChange();
public:
    void init();//改为public，add by 2020.11.23
    //add by zw 20220223
    void newAdjcoefInit();
    //end add by zw 20220223
private:
    void openDigKeyBoardDlg(QLineEdit *lineEdit);
private:
    CGPIORW m_Gpiorw;//GPIO读写类对象
    int m_nGPIOfd;
    CKeyBoardDlg m_KeyBoardDlg;    //数字键盘类对象
    QString m_strInfo;             //友情提示语
    QString m_strErrinfo;          //错误提示语
    QString m_strInvalidinfo;      //不合法提示
    QString m_strFriendlytips;//友情提示语
    QString m_strAdjSuccess;//校准成功提示语
    QString m_strAdjFail;   //校准失败提示语
    QString m_strSaveSuccess;      //基本参数配置文件保存成功提示语
    QString m_strSaveFail;         //基本参数配置文件保存失败提示语
    QString m_strResetSuccess;    //校准复位成功提示语
    QString m_strResetFail;    //校准复位失败提示语
private:
    Ui::adjcoefDialog  *m_pUi;
    STRU_ADJCOEF m_struAdjcoef;
    CInifileparse m_IniAdjcoef;
    STRU_ADJVALUE m_struAdjvalue;
    STRU_ADJCHECK m_struAdjcheck;
    STR_ADJCHECKNUM m_struAdjchecknum;
};
#endif //ADJ_COEF_DLG_H
