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
    //void closeBtn_clicked();        //���ؼ��ۺ�����add by 2020.08.01
     void okBtn_clicked();        //ȷ�����ۺ�����add by 2020.08.15
    void sysTimesetBtn_clicked(); //ϵͳʱ�����òۺ�����add by 2020.08.15
    void  restorefactoryBtn_clicked();//�ָ��������òۺ�����add by 2020.11.18
public:
    void syssetLangChange();//ϵͳ���ý��������л� add by 2020.11.20
private:
    QTimer *m_timer;
    bool m_isTimeEditFlag;
private:
    QString m_strErrinfo; //������ʾ��
    QString m_strInfo;  //��ʾ add by 2020.11.18
    QString m_restorefactoryTips;  //�ָ�����������ʾ add by 2020.11.18
    QString m_strYes;//"��"��ʾ add by 2020.11.18
    QString m_strNo; //"��"��ʾ add by 2020.11.18
private:
        Ui::syssetDialog  *m_pUi;
private:
    STRU_ADJCOEF m_struAdjcoef;//У׼ϵ��������add by 2020.11.23
    STRU_BASICPARA  m_struBasicpara;//��������������add by 2020.11.23
    STRU_CHAINSETDATA m_ChainSetData;//�������ýṹ�����,add by 2020.11.24

    CInifileparse  m_IniBasicParse;//��������ini�ļ���д�����add by 2020.11.23
    CInifileparse  m_IniAdjcoef;//У׼ϵ��ini�ļ���д�����add by 2020.11.23
    CInifileparse  m_IniChainset;//��������ini�ļ���д�����add by 2020.11.24
};
#endif //SYS_SET_DLG_H
