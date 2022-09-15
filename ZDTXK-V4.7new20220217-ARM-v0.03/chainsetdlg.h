#ifndef CHAINSETDLG_H
#define CHAINSETDLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_chainset.h"
#include "commmacro.h"
#include "gpiorw.h"
#include "inifileparse.h"
namespace Ui
{
    class chainsetDialog;
}
class CChainsetdlg:public QDialog
{
    Q_OBJECT
public:
    CChainsetdlg(int nfd);
    ~CChainsetdlg();
public Q_SLOTS:
    void tongyiSwitch_clicked();   //ͳһ��ť�ۺ���,add by 2019.05.25
    void okBtn_clicked();       //ͳһ��������-�ۺ���

    void xtlqdysetBtn_clicked();    //ϵͳ��ȴ��Ԫ-������������-�ۺ���
    void zdtgwsetBtn_clicked();     //��̨����-������������-�ۺ���
    void zdtgwysetBtn_clicked();    //��̨��λ��-������������-�ۺ���
    void htgwysetBtn_clicked();     //��̨��λ��-������������-�ۺ���
    void htqysetBtn_clicked();      //��̨Ƿѹ-������������-�ۺ���
    void htqywsetBtn_clicked();     //��̨ǷҺλ-������������-�ۺ���
    void htgwsetBtn_clicked();      //��̨����-������������-�ۺ���

    void gfrjbhsetBtn_clicked();        //�����ȼ̱���-������������-�ۺ���
    void jyzcdysetBtn_clicked();        //��ѹ��е�ѹ-������������-�ۺ���
    void zgmenbhsetBtn_clicked();       //�����ű���-������������-�ۺ���
    void selfdefine1setBtn_clicked();   //�Զ���1-������������-�ۺ���
    void selfdefine2setBtn_clicked();   //�Զ���2-������������-�ۺ���
    void selfdefine3setBtn_clicked();   //�Զ���3-������������-�ۺ���


    void htdywsetBtn_clicked(); //��̨��Һλ-������������-�ۺ���


    void ezgwysetBtn_clicked(); //�����λ��-������������-�ۺ���







    void subzlqgwsetBtn_clicked();   //�ӹ������Ź���-������������-�ۺ���,add by 2019.05.25

    void subyuliubhsetBtn_clicked(); //�ӹ�Ԥ������-������������-�ۺ���,add by 2019.05.18




    void htdywSwitch_clicked();         //��̨��Һλ-�л�-�ۺ���
    void ezgwySwitch_clicked();         //�����λ��-�л�-�ۺ���
    void subyuliuSwitch_clicked();      //�ӹ�Ԥ������-�л�-�ۺ���,add by 2019.05.18
    void subzlqgwSwitch_clicked();      //�ӹ�����������-�л�-�ۺ���,add by 2019.05.25

    void xtlqdySwitch_clicked();        //ϵͳ��ȴ��Ԫ-�л�-�ۺ���
    void zdtgwSwitch_clicked();         //��̨����-�л�-�ۺ���
    void zdtgwySwitch_clicked();        //��̨��λ��-�л�-�ۺ���
    void htgwySwitch_clicked();         //��̨��λ��-�л�-�ۺ���
    void htqySwitch_clicked();          //��̨Ƿѹ-�л�-�ۺ���
    void htqywSwitch_clicked();         //��̨ǷҺλ-�л�-�ۺ���,add by 2019.05.25
    void htgwSwitch_clicked();          //��̨����-�л�-�ۺ���,add by 2019.05.18

    void gfrhbhSwitch_clicked();        //�����ȼ̱���-�л�-�ۺ���
    void jyzcdySwitch_clicked();        //��ѹ��е�ѹ-�л�-�ۺ���
    void zgmenbhSwitch_clicked();       //�����ű���-�л�-�ۺ���
    void selfdefine1Switch_clicked();   //�Զ���1-�л�-�ۺ���,add by 2019.05.18
    void selfdefine2Switch_clicked();   //�Զ���2-�л�-�ۺ���,add by 2019.05.18
    void selfdefine3Switch_clicked();   //�Զ���3-�л�-�ۺ���,add by 2019.05.18
    void selfdefine4Switch_clicked();   //�Զ���4-������������-�ۺ���

    void c1zlqgwSwitch_clicked();       //�ӹ�1����������-������������-�ۺ���
    void c2zlqgwSwitch_clicked();       //�ӹ�2����������-������������-�ۺ���
    void c3zlqgwSwitch_clicked();       //�ӹ�3����������-������������-�ۺ���
    void c4zlqgwSwitch_clicked();       //�ӹ�4����������-������������-�ۺ���
    void c1cwbhSwitch_clicked();        //�ӹ�1���󱣻�-������������-�ۺ���
    void c2cwbhSwitch_clicked();        //�ӹ�2���󱣻�-������������-�ۺ���
    void c3cwbhSwitch_clicked();        //�ӹ�3���󱣻�-������������-�ۺ���
    void c4cwbhSwitch_clicked();        //�ӹ�4���󱣻�-������������-�ۺ���

    void comboBox_xtlqdy_activated(int index);   //ϵͳ��ȴ��Ԫ���������л��ۺ����� add by 2020.09.08
    void comboBox_zdtgw_activated(int index);   //��̨���´����л��ۺ����� add by 2020.09.08
    void comboBox_zdtgwy_activated(int index);   //��̨��λ�ƴ����л��ۺ����� add by 2020.09.08
    void comboBox_htgwy_activated(int index);   //��̨��λ�ƴ����л��ۺ����� add by 2020.09.05
    void comboBox_htqy_activated(int index);   //��̨��е�ѹ�����л��ۺ����� add by 2020.09.08
    void comboBox_htqyw_activated(int index);   //�������������´����л��ۺ����� add by 2020.09.08

    void comboBox_gfrjbh_activated(int index);   //�����ȼ̱��������л��ۺ����� add by 2020.09.08
    void comboBox_jyzcdy_activated(int index);   //��ѹ��е�ѹ�����л��ۺ����� add by 2020.09.08
    void comboBox_zgmenbh_activated(int index);   //�����ű��������л��ۺ����� add by 2020.09.08
    void comboBox_selfdefine1_activated(int index);   //�Զ���1���������л��ۺ����� add by 2020.09.08
    void comboBox_selfdefine2_activated(int index);   //�Զ���2���������л��ۺ����� add by 2020.09.08
    void comboBox_selfdefine3_activated(int index);   //�Զ���3���������л��ۺ����� add by 2020.09.08
    void comboBox_selfdefine4_activated(int index);   //�Զ���4���������л��ۺ����� add by 2022.02.23

    void comboBox_c1zlqgw_activated(int index);     //�ӹ�1���������´����л��ۺ��� add by 2022.02.23
    void comboBox_c2zlqgw_activated(int index);     //�ӹ�2���������´����л��ۺ��� add by 2022.02.23
    void comboBox_c3zlqgw_activated(int index);     //�ӹ�3���������´����л��ۺ��� add by 2022.02.23
    void comboBox_c4zlqgw_activated(int index);     //�ӹ�4���������´����л��ۺ��� add by 2022.02.23
    void comboBox_c1cwbh_activated(int index);      //�ӹ�1�����źŴ����л��ۺ��� add by 2022.02.23
    void comboBox_c2cwbh_activated(int index);      //�ӹ�2�����źŴ����л��ۺ��� add by 2022.02.23
    void comboBox_c3cwbh_activated(int index);      //�ӹ�3�����źŴ����л��ۺ��� add by 2022.02.23
    void comboBox_c4cwbh_activated(int index);      //�ӹ�4�����źŴ����л��ۺ��� add by 2022.02.23

    void comboBox_subzlqgw_activated(int index);   //�ӹ����������´����л��ۺ����� add by 2020.09.08
    void comboBox_ezgwy_activated(int index);   //�����λ�ƴ����л��ۺ����� add by 2020.09.08
    void comboBox_htgw_activated(int index);   //�ӹ��ű��������л��ۺ����� add by 2020.09.08
    void comboBox_subyuliu_activated(int index);   //�Զ���3���������л��ۺ����� add by 2020.09.08
    void comboBox_htdyw_activated(int index);   //��̨��Һλ�����л��ۺ����� add by 2020.09.08


    void debug_clicked();            //����ģʽ-�ۺ���
    void normal_clicked();            //����ģʽ-�ۺ���
    void closeBtn_clicked();         //���ؼ��ۺ�����add by 2020.08.10
public:
    int getMode();//��ȡģʽ,add by 2019.04.27
    void chainLangChange();
public:
    STRU_CHAINSETDATA getChainSetData();//��ȡ������������
     int m_iSwitchFlag[MAX_SIZE+3];
     int m_iNewswFlag[25];
private:
    Ui::chainsetDialog *m_pUi;
public:
    void init(); //��ʼ����������ҳ���Ϊpublic��add by 2020.11.24
private:
//	void init();                                                //��ʼ����������ҳ��
    void allSetBtnEnable(bool enable);                          //��������ʹ��
    void refreshChainButton(int nIndex,QToolButton *toolButton);//ˢ��������ť״̬
    void showChainButton(int nIndex,QToolButton *toolButton);  //��ʾ������ť״̬
    void disableChainSet();
    void setAllSwitchIcon(QIcon icon);//���������л���ťͼ�꣬add by 2019.05.25
    void setAllSwitchValue(int nValue);//���������л���ťֵ��add by 2019.05.25
    void initChainSetData();//��ʼ��������������m_ChainSetData,add by 2019.05.26
    void newinitChainSetData();//��ʼ��������������m_ChainSetData,add by zw 2022.02.23
private:
     QIcon m_ybonicon;  //ѹ��-��ͼ��
     QIcon m_ybofficon; //ѹ��-��ͼ��
     int m_iChainsetval;//��������ֵ
     CGPIORW m_Gpiorw;//GPIO��д�����
     int m_nGPIOfd;
     QString m_strFriendlytips;//������ʾ��
     QStringList m_strListSuccess;
     QStringList m_strListFailure;
     QString  m_strAllSuccess;
     QString  m_strAllFailure;

     STRU_CHAINSETDATA m_ChainSetData;//�������ýṹ�����,add by 2019.04.13
     STRU_NEWCHASETDATA m_newChaSetData;//�������ýṹ�����,add by zw 2022.02.23
     int m_iMode;//ģʽ
     bool m_isTongyi;//ͳһ��ť�л���־λ,add by 2019.05.25
     CInifileparse  m_IniChainset;//��������ini�ļ���д�����
};
#endif // CHAINSETDLG_H
