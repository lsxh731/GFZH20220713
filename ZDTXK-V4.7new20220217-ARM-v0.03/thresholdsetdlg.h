#ifndef THRESHOLDSETDLG_H
#define THRESHOLDSETDLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_thresholdset.h"
#include <QDialog>
#include <qsocketnotifier.h>
#include "CANdatarw.h"
#include "inifileparse.h"
#include "keyboarddlg.h"

namespace Ui
{
    class thresholdsetDialog;
}
class CThresholdsetdlg:public QDialog
{
    Q_OBJECT
public:
    CThresholdsetdlg();
    ~CThresholdsetdlg();
public Q_SLOTS:

private slots:
    void scbhSetBtn_clicked();//�����ѹ����ֵ����-�ۺ���
    void gybhSetBtn_clicked();//��ѹ����ֵ����-�ۺ���
    void scdlSetBtn_clicked();//�����������-�ۺ���
    void IGBTgwSetBtn_clicked();//IGBT���¶���ֵ����-�ۺ���
    void dggwSetBtn_clicked();//��й��¶���ֵ����-�ۺ���
    void scbhLowerEdit_clicked();
    void scbhUpEdit_clicked();
    void gybhLowerEdit_clicked();
    void gybhUpEdit_clicked();
    void scdlProcEdit_clicked();
    void scdlWarningEdit_clicked();
    void IGBTgw1Edit_clicked();
    void IGBTgw2Edit_clicked();
    void dggw1Edit_clicked();
    void dggw2Edit_clicked();
    //void checkBox_clicked();
private:
    void  openDigKeyBoardDlg(QLineEdit *lineEdit);//�����ּ��̶Ի���
    void  EffectiveJudge(QString text,int nDatatype);//��Ч���ж�
    void  init();                      //��ʼ��
    bool  saveThresholdset(QString strRegExp,QString strReplace,QString strText);//���汣����ֵ�������ļ���
private:
    int m_CANfd;
    CCANDataRW m_CANDatarw;
    QString m_strErrinfo;    //������ʾ��
    QString m_strTips;       //��ʾ
    QString m_strInvalidinfo;//���Ϸ���ʾ
    STRU_PROCVALUEDATA m_struProcValData;
    CInifileparse m_Inifile;
    QString m_strFilepathName;//ȫ·�����ļ�
     //bool m_isChkDigKeyBoard;    //�Ƿ�ѡ���ּ���
     CKeyBoardDlg m_KeyBoardDlg; //���ּ��������
private:
    Ui::thresholdsetDialog *m_pUi;
};
#endif // THRESHOLDSETDLG_H
