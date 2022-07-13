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
    void okBtn_clicked();          //"ȷ��"�ۺ���
    void cancelBtn_clicked();      //"ȡ��"�ۺ���
    void lineEdit_clicked();
    void calendarDay_clicked();//��ȡ��Ȼ�����ۺ��� add by 2020.11.18
public:
    void invalidsetLangChange();
private:
    void openDigKeyBoardDlg(QLineEdit *lineEdit);//�����ּ��Ի�����
private:
    CInifileparse m_Inifileparse;
    STRU_TOTALRUNNING m_struTotaltime;
    CKeyBoardDlg m_KeyBoardDlg; //���ּ��������
    QString m_strErrinfo;//������ʾ��
    QString m_strInvalidinfo;//���Ϸ���ʾ

private:
    Ui::invalidSetDialog  *m_pUi;
};
#endif //INVALID_SET_DLG_H
