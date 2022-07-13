#ifndef INVALID_SET_DLG_H
#define INVALID_SET_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_invalidset.h"
#include "inifileparse.h"
#include "keyboarddlg.h"

namespace Ui
{
    class invalidSetDialog;
}
class CInvalidSetdlg:public QDialog
{
    Q_OBJECT
public:
    CInvalidSetdlg();
    ~CInvalidSetdlg();
public Q_SLOTS:
    void okBtn_clicked();          //"确定"槽函数
    void cancelBtn_clicked();      //"取消"槽函数
    void lineEdit_clicked();
    void calendarDay_clicked();//获取自然天数槽函数 add by 2020.11.18
public:
    void invalidsetLangChange();
private:
    void openDigKeyBoardDlg(QLineEdit *lineEdit);//打开数字键对话框函数
private:
    CInifileparse m_Inifileparse;
    STRU_TOTALRUNNING m_struTotaltime;
    CKeyBoardDlg m_KeyBoardDlg; //数字键盘类对象
    QString m_strErrinfo;//错误提示语
    QString m_strInvalidinfo;//不合法提示

private:
    Ui::invalidSetDialog  *m_pUi;
};
#endif //INVALID_SET_DLG_H
