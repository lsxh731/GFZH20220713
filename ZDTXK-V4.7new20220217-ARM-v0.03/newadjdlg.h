#ifndef NEWADJDLG_H
#define NEWADJDLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "commmacro.h"
#include "keyboarddlg.h"
#include "inifileparse.h"

namespace Ui {
class newadjdlg;
}

class newadjdlg : public QDialog
{
    Q_OBJECT

public:
    explicit newadjdlg(QWidget *parent = 0);
    ~newadjdlg();

public Q_SLOTS:
    void adjcoefBtn_clicked();
    void resetBtn_clicked();
    void zeroBtn_clicked();
    void closeBtn_clicked();

    void allcheckBox_clicked();
    void maincheckBox_clicked();
    void s12checkBox_clicked();
    void s34checkBox_clicked();
    void sallcheckBox_clicked();

    //主柜
    void lineEdit_mAzerovolt_clicked();
    void lineEdit_mAshowvolt_clicked();
    void lineEdit_mArealvolt_clicked();
    void lineEdit_mBzerovolt_clicked();
    void lineEdit_mBshowvolt_clicked();
    void lineEdit_mBrealvolt_clicked();
    void lineEdit_mCzerovolt_clicked();
    void lineEdit_mCshowvolt_clicked();
    void lineEdit_mCrealvolt_clicked();
    void lineEdit_mevzerovolt_clicked();
    void lineEdit_mevshowvolt_clicked();
    void lineEdit_mevrealvolt_clicked();
    void lineEdit_meczerovolt_clicked();
    void lineEdit_mecshowvolt_clicked();
    void lineEdit_mecrealvolt_clicked();

    void mAvcheckBox_clicked();
    void mBvcheckBox_clicked();
    void mCvcheckBox_clicked();
    void mevcheckBox_clicked();
    void meccheckBox_clicked();

    //从柜1-2
    void lineEdit_ms1vzerovolt_clicked();
    void lineEdit_ms1vshowvolt_clicked();
    void lineEdit_ms1vrealvolt_clicked();
    void lineEdit_ms1azerovolt_clicked();
    void lineEdit_ms1ashowvolt_clicked();
    void lineEdit_ms1arealvolt_clicked();
    void lineEdit_ms2vzerovolt_clicked();
    void lineEdit_ms2vshowvolt_clicked();
    void lineEdit_ms2vrealvolt_clicked();
    void lineEdit_ms2azerovolt_clicked();
    void lineEdit_ms2ashowvolt_clicked();
    void lineEdit_ms2arealvolt_clicked();

    void ms1vcheckBox_clicked();
    void ms1acheckBox_clicked();
    void ms2vcheckBox_clicked();
    void ms2acheckBox_clicked();

    //从柜3-4
    void lineEdit_ms3vzerovolt_clicked();
    void lineEdit_ms3vshowvolt_clicked();
    void lineEdit_ms3vrealvolt_clicked();
    void lineEdit_ms3azerovolt_clicked();
    void lineEdit_ms3ashowvolt_clicked();
    void lineEdit_ms3arealvolt_clicked();
    void lineEdit_ms4vzerovolt_clicked();
    void lineEdit_ms4vshowvolt_clicked();
    void lineEdit_ms4vrealvolt_clicked();
    void lineEdit_ms4azerovolt_clicked();
    void lineEdit_ms4ashowvolt_clicked();
    void lineEdit_ms4arealvolt_clicked();

    void ms3vcheckBox_clicked();
    void ms3acheckBox_clicked();
    void ms4vcheckBox_clicked();
    void ms4acheckBox_clicked();

    //从柜-总
    void lineEdit_movazerovolt_clicked();
    void lineEdit_movashowvolt_clicked();
    void lineEdit_movarealvolt_clicked();
    void lineEdit_movdzerovolt_clicked();
    void lineEdit_movdshowvolt_clicked();
    void lineEdit_movdrealvolt_clicked();
    void lineEdit_mocazerovolt_clicked();
    void lineEdit_mocashowvolt_clicked();
    void lineEdit_mocarealvolt_clicked();
    void lineEdit_mcus1zerovolt_clicked();
    void lineEdit_mcus1showvolt_clicked();
    void lineEdit_mcus1realvolt_clicked();
    void lineEdit_mcus2zerovolt_clicked();
    void lineEdit_mcus2showvolt_clicked();
    void lineEdit_mcus2realvolt_clicked();

    void movacheckBox_clicked();
    void movdcheckBox_clicked();
    void mocacheckBox_clicked();
    void mcus1checkBox_clicked();
    void mcus2checkBox_clicked();

public:
    void MainSeleck();
    void MainUnSeleck();
    void S12Seleck();
    void S12UnSeleck();
    void S34Seleck();
    void S34UnSeleck();
    void SALLSeleck();
    void SALLUnSeleck();
    void AdjInit();

private:
    void openDigKeyBoardDlg(QLineEdit *lineEdit);


    Ui::newadjdlg *m_pUi;
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

    STRU_NEWADCKNUM m_NewAdchnum;
    STRU_NEWADCK m_NewAdch;
    STR_NEWADJVALUE m_newAdjValue;

    CInifileparse m_IniAdjcoef;

};

#endif // NEWADJDLG_H
