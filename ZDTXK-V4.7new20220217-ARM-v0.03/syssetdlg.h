#ifndef SYS_SET_DLG_H
#define SYS_SET_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_sysset.h"
#include "commmacro.h"
#include "gpiorw.h"
#include "keyboarddlg.h"
#include "inifileparse.h"
#include "basicparasetdlg.h"
#include "ui_basicparaset.h"

namespace Ui
{
    class syssetDialog;
}
class CSyssetdlg:public QDialog
{
    Q_OBJECT
public:
    CSyssetdlg();
    ~CSyssetdlg();
public Q_SLOTS:
     void  updateSystimeEdit();
    //void closeBtn_clicked();        //返回键槽函数，add by 2020.08.01
     void okBtn_clicked();        //确定键槽函数，add by 2020.08.15
    void sysTimesetBtn_clicked(); //系统时间设置槽函数，add by 2020.08.15
    void  restorefactoryBtn_clicked();//恢复出厂设置槽函数，add by 2020.11.18
public:
    void syssetLangChange();//系统设置界面语言切换 add by 2020.11.20
private:
    QTimer *m_timer;
    bool m_isTimeEditFlag;
private:
    QString m_strErrinfo; //错误提示语
    QString m_strInfo;  //提示 add by 2020.11.18
    QString m_restorefactoryTips;  //恢复出厂设置提示 add by 2020.11.18
    QString m_strYes;//"是"提示 add by 2020.11.18
    QString m_strNo; //"否"提示 add by 2020.11.18
private:
        Ui::syssetDialog  *m_pUi;
private:
    STRU_ADJCOEF m_struAdjcoef;//校准系数变量，add by 2020.11.23
    STRU_BASICPARA  m_struBasicpara;//基本参数变量，add by 2020.11.23
    STRU_CHAINSETDATA m_ChainSetData;//连锁设置结构体对象,add by 2020.11.24

    CInifileparse  m_IniBasicParse;//基本参数ini文件读写类对象，add by 2020.11.23
    CInifileparse  m_IniAdjcoef;//校准系数ini文件读写类对象，add by 2020.11.23
    CInifileparse  m_IniChainset;//基本参数ini文件读写类对象，add by 2020.11.24
};
#endif //SYS_SET_DLG_H
