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
    void adjBtn01_clicked();//����01ֱ�����ڲۺ���
    void adjBtn02_clicked();//����02ֱ�����ڲۺ���
    void adjBtn03_clicked();//����03ֱ�����ڲۺ���
    void adjBtn04_clicked();//����04ֱ�����ڲۺ���
    void adjBtn05_clicked();//����05ֱ�����ڲۺ���
    void adjBtn06_clicked();//����06ֱ�����ڲۺ���
    void adjBtn07_clicked();//����07ֱ�����ڲۺ���
    void adjBtn08_clicked();//����08ֱ�����ڲۺ���
    void adjBtn09_clicked();//����09ֱ�����ڲۺ���
    void adjBtn10_clicked();//����10ֱ�����ڲۺ���
    void adjBtn11_clicked();//����11ֱ�����ڲۺ���
    void adjBtn12_clicked();//����12ֱ�����ڲۺ���
    void adjBtn13_clicked();//����13ֱ�����ڲۺ���
    void adjBtn14_clicked();//����14ֱ�����ڲۺ���
    void adjBtn15_clicked();//����15ֱ�����ڲۺ���
    void adjBtn16_clicked();//����16ֱ�����ڲۺ���

    void comboBox_clicked(int index);
    void setBtn_clicked();    //"ȷ��"�ۺ���
    void adjBtn_clicked();    //"ȡ��"�ۺ���

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
    void checkBox_clicked();//�Ƿ�ѡ���ּ��ۺ���
private:
    void unifyset(QString text);
    void openDigKeyBoardDlg(QLineEdit *lineEdit);//�����ּ��Ի�����
    void EffectiveJudge(QString text);//�ж���ֵ�Ϸ���

private:
    Ui::dcsetDialog  *m_pUi;
private:
    int m_nAdjtype;//1���������ڣ�2��ͳһ����
    QString m_strErrinfo;//������ʾ��
    QString m_strInvalidinfo;//���Ϸ���ʾ
    QString m_strFriendlytips;//������ʾ��
    QStringList m_strListSuccess;
    QStringList m_strListFailure;
    bool m_isChkDigKeyBoard;    //�Ƿ�ѡ���ּ���
    CKeyBoardDlg m_KeyBoardDlg; //���ּ��������
};
#endif //DC_SET_DLG_H
