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
    void scbhSetBtn_clicked();//输出电压保护值设置-槽函数
    void gybhSetBtn_clicked();//过压保护值设置-槽函数
    void scdlSetBtn_clicked();//输出电流设置-槽函数
    void IGBTgwSetBtn_clicked();//IGBT过温动作值设置-槽函数
    void dggwSetBtn_clicked();//电感过温动作值设置-槽函数
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
    void  openDigKeyBoardDlg(QLineEdit *lineEdit);//打开数字键盘对话框
    void  EffectiveJudge(QString text,int nDatatype);//有效性判断
    void  init();                      //初始化
    bool  saveThresholdset(QString strRegExp,QString strReplace,QString strText);//保存保护阈值参数到文件中
private:
    int m_CANfd;
    CCANDataRW m_CANDatarw;
    QString m_strErrinfo;    //错误提示语
    QString m_strTips;       //提示
    QString m_strInvalidinfo;//不合法提示
    STRU_PROCVALUEDATA m_struProcValData;
    CInifileparse m_Inifile;
    QString m_strFilepathName;//全路径名文件
     //bool m_isChkDigKeyBoard;    //是否勾选数字键盘
     CKeyBoardDlg m_KeyBoardDlg; //数字键盘类对象
private:
    Ui::thresholdsetDialog *m_pUi;
};
#endif // THRESHOLDSETDLG_H
