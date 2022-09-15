#ifndef FAULT_COND_WIDGET_H
#define FAULT_COND_WIDGET_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_faultcondition.h"
#include "commmacro.h"
namespace Ui
{
    class faultconditionForm;
}
class CFaultConditionWidget:public QDialog//QWidget
{
    Q_OBJECT
public:
    CFaultConditionWidget();
    ~CFaultConditionWidget();
public Q_SLOTS:
    //"故障状态页面"槽函数定义,modify by zqc 2018.12.02
    void radioButton0102_clicked();
    void radioButton0304_clicked();
    void radioButton0506_clicked();
    void radioButton0708_clicked();
    void radioButton0910_clicked();
    void radioButton1112_clicked();
    void radioButton1314_clicked();
    void radioButton1516_clicked();
    void closeBtn_clicked();//返回键槽函数 add by 2020.08.10
public:
    void updateFaultConditionData(int index,
        STRU_FAULTSTATUS *pLeftFaultStatData,
        STRU_FAULTSTATUS *pRightStruFaultStatData);//更新故障状态数据灯
    void faultLangChange();
    int ifaultindex;
private:
    void init(QIcon icon);             //初始化
    QIcon IconColorByValue(int nValue);//依照数值判断图标颜色
private:
    Ui::faultconditionForm  *m_pUi;
private:
     QIcon m_greenicon;
     QIcon m_redicon;
     QIcon m_yellowicon;
};
#endif //FAULT_COND_WIDGET_H
