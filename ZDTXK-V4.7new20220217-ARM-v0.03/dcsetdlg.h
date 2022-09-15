#ifndef DC_SET_DLG_H
#define DC_SET_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QStringList>
#include "keyboarddlg.h"
#include "ui_dcset.h"

namespace Ui
{
    class dcsetDialog;
}
class CDCSetdlg:public QDialog
{
    Q_OBJECT
public:
    CDCSetdlg();
    ~CDCSetdlg();
public Q_SLOTS:
    void adjBtn01_clicked();//功放01直流调节槽函数
    void adjBtn02_clicked();//功放02直流调节槽函数
    void adjBtn03_clicked();//功放03直流调节槽函数
    void adjBtn04_clicked();//功放04直流调节槽函数
    void adjBtn05_clicked();//功放05直流调节槽函数
    void adjBtn06_clicked();//功放06直流调节槽函数
    void adjBtn07_clicked();//功放07直流调节槽函数
    void adjBtn08_clicked();//功放08直流调节槽函数
    void adjBtn09_clicked();//功放09直流调节槽函数
    void adjBtn10_clicked();//功放10直流调节槽函数
    void adjBtn11_clicked();//功放11直流调节槽函数
    void adjBtn12_clicked();//功放12直流调节槽函数
    void adjBtn13_clicked();//功放13直流调节槽函数
    void adjBtn14_clicked();//功放14直流调节槽函数
    void adjBtn15_clicked();//功放15直流调节槽函数
    void adjBtn16_clicked();//功放16直流调节槽函数

    void comboBox_clicked(int index);
    void setBtn_clicked();    //"确定"槽函数
    void adjBtn_clicked();    //"取消"槽函数

    void lineEdit_clicked();
    void lineEdit01_clicked();
    void lineEdit02_clicked();
    void lineEdit03_clicked();
    void lineEdit04_clicked();
    void lineEdit05_clicked();
    void lineEdit06_clicked();
    void lineEdit07_clicked();
    void lineEdit08_clicked();
    void lineEdit09_clicked();
    void lineEdit10_clicked();
    void lineEdit11_clicked();
    void lineEdit12_clicked();
    void lineEdit13_clicked();
    void lineEdit14_clicked();
    void lineEdit15_clicked();
    void lineEdit16_clicked();
    void checkBox_clicked();//是否勾选数字键槽函数
private:
    void unifyset(QString text);
    void openDigKeyBoardDlg(QLineEdit *lineEdit);//打开数字键对话框函数
    void EffectiveJudge(QString text);//判断数值合法性

private:
    Ui::dcsetDialog  *m_pUi;
private:
    int m_nAdjtype;//1：单个调节；2：统一调节
    QString m_strErrinfo;//错误提示语
    QString m_strInvalidinfo;//不合法提示
    QString m_strFriendlytips;//友情提示语
    QStringList m_strListSuccess;
    QStringList m_strListFailure;
    bool m_isChkDigKeyBoard;    //是否勾选数字键盘
    CKeyBoardDlg m_KeyBoardDlg; //数字键盘类对象
};
#endif //DC_SET_DLG_H
