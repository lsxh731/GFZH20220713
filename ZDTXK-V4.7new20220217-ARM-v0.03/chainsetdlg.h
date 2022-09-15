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
    void tongyiSwitch_clicked();   //统一按钮槽函数,add by 2019.05.25
    void okBtn_clicked();       //统一连锁设置-槽函数

    void xtlqdysetBtn_clicked();    //系统冷却单元-连锁屏蔽设置-槽函数
    void zdtgwsetBtn_clicked();     //振动台过温-连锁屏蔽设置-槽函数
    void zdtgwysetBtn_clicked();    //振动台过位移-连锁屏蔽设置-槽函数
    void htgwysetBtn_clicked();     //滑台过位移-连锁屏蔽设置-槽函数
    void htqysetBtn_clicked();      //滑台欠压-连锁屏蔽设置-槽函数
    void htqywsetBtn_clicked();     //滑台欠液位-连锁屏蔽设置-槽函数
    void htgwsetBtn_clicked();      //滑台过温-连锁屏蔽设置-槽函数

    void gfrjbhsetBtn_clicked();        //功放热继保护-连锁屏蔽设置-槽函数
    void jyzcdysetBtn_clicked();        //静压轴承低压-连锁屏蔽设置-槽函数
    void zgmenbhsetBtn_clicked();       //主柜门保护-连锁屏蔽设置-槽函数
    void selfdefine1setBtn_clicked();   //自定义1-连锁屏蔽设置-槽函数
    void selfdefine2setBtn_clicked();   //自定义2-连锁屏蔽设置-槽函数
    void selfdefine3setBtn_clicked();   //自定义3-连锁屏蔽设置-槽函数


    void htdywsetBtn_clicked(); //滑台低液位-连锁屏蔽设置-槽函数


    void ezgwysetBtn_clicked(); //耳轴过位移-连锁屏蔽设置-槽函数







    void subzlqgwsetBtn_clicked();   //从柜整流桥过温-连锁屏蔽设置-槽函数,add by 2019.05.25

    void subyuliubhsetBtn_clicked(); //从柜预留保护-连锁屏蔽设置-槽函数,add by 2019.05.18




    void htdywSwitch_clicked();         //滑台低液位-切换-槽函数
    void ezgwySwitch_clicked();         //耳轴过位移-切换-槽函数
    void subyuliuSwitch_clicked();      //从柜预留保护-切换-槽函数,add by 2019.05.18
    void subzlqgwSwitch_clicked();      //从柜整流器过温-切换-槽函数,add by 2019.05.25

    void xtlqdySwitch_clicked();        //系统冷却单元-切换-槽函数
    void zdtgwSwitch_clicked();         //振动台过温-切换-槽函数
    void zdtgwySwitch_clicked();        //振动台过位移-切换-槽函数
    void htgwySwitch_clicked();         //滑台过位移-切换-槽函数
    void htqySwitch_clicked();          //滑台欠压-切换-槽函数
    void htqywSwitch_clicked();         //滑台欠液位-切换-槽函数,add by 2019.05.25
    void htgwSwitch_clicked();          //滑台过温-切换-槽函数,add by 2019.05.18

    void gfrhbhSwitch_clicked();        //功放热继保护-切换-槽函数
    void jyzcdySwitch_clicked();        //静压轴承低压-切换-槽函数
    void zgmenbhSwitch_clicked();       //主柜门保护-切换-槽函数
    void selfdefine1Switch_clicked();   //自定义1-切换-槽函数,add by 2019.05.18
    void selfdefine2Switch_clicked();   //自定义2-切换-槽函数,add by 2019.05.18
    void selfdefine3Switch_clicked();   //自定义3-切换-槽函数,add by 2019.05.18
    void selfdefine4Switch_clicked();   //自定义4-连锁屏蔽设置-槽函数

    void c1zlqgwSwitch_clicked();       //从柜1整流器过温-连锁屏蔽设置-槽函数
    void c2zlqgwSwitch_clicked();       //从柜2整流器过温-连锁屏蔽设置-槽函数
    void c3zlqgwSwitch_clicked();       //从柜3整流器过温-连锁屏蔽设置-槽函数
    void c4zlqgwSwitch_clicked();       //从柜4整流器过温-连锁屏蔽设置-槽函数
    void c1cwbhSwitch_clicked();        //从柜1错误保护-连锁屏蔽设置-槽函数
    void c2cwbhSwitch_clicked();        //从柜2错误保护-连锁屏蔽设置-槽函数
    void c3cwbhSwitch_clicked();        //从柜3错误保护-连锁屏蔽设置-槽函数
    void c4cwbhSwitch_clicked();        //从柜4错误保护-连锁屏蔽设置-槽函数

    void comboBox_xtlqdy_activated(int index);   //系统冷却单元保护触点切换槽函数， add by 2020.09.08
    void comboBox_zdtgw_activated(int index);   //振动台过温触点切换槽函数， add by 2020.09.08
    void comboBox_zdtgwy_activated(int index);   //振动台过位移触点切换槽函数， add by 2020.09.08
    void comboBox_htgwy_activated(int index);   //滑台过位移触点切换槽函数， add by 2020.09.05
    void comboBox_htqy_activated(int index);   //滑台轴承低压触点切换槽函数， add by 2020.09.08
    void comboBox_htqyw_activated(int index);   //主柜整流器过温触点切换槽函数， add by 2020.09.08

    void comboBox_gfrjbh_activated(int index);   //功放热继保护触点切换槽函数， add by 2020.09.08
    void comboBox_jyzcdy_activated(int index);   //静压轴承低压触点切换槽函数， add by 2020.09.08
    void comboBox_zgmenbh_activated(int index);   //主柜门保护触点切换槽函数， add by 2020.09.08
    void comboBox_selfdefine1_activated(int index);   //自定义1保护触点切换槽函数， add by 2020.09.08
    void comboBox_selfdefine2_activated(int index);   //自定义2保护触点切换槽函数， add by 2020.09.08
    void comboBox_selfdefine3_activated(int index);   //自定义3保护触点切换槽函数， add by 2020.09.08
    void comboBox_selfdefine4_activated(int index);   //自定义4保护触点切换槽函数， add by 2022.02.23

    void comboBox_c1zlqgw_activated(int index);     //从柜1整流器过温触点切换槽函数 add by 2022.02.23
    void comboBox_c2zlqgw_activated(int index);     //从柜2整流器过温触点切换槽函数 add by 2022.02.23
    void comboBox_c3zlqgw_activated(int index);     //从柜3整流器过温触点切换槽函数 add by 2022.02.23
    void comboBox_c4zlqgw_activated(int index);     //从柜4整流器过温触点切换槽函数 add by 2022.02.23
    void comboBox_c1cwbh_activated(int index);      //从柜1错误信号触点切换槽函数 add by 2022.02.23
    void comboBox_c2cwbh_activated(int index);      //从柜2错误信号触点切换槽函数 add by 2022.02.23
    void comboBox_c3cwbh_activated(int index);      //从柜3错误信号触点切换槽函数 add by 2022.02.23
    void comboBox_c4cwbh_activated(int index);      //从柜4错误信号触点切换槽函数 add by 2022.02.23

    void comboBox_subzlqgw_activated(int index);   //从柜整流器过温触点切换槽函数， add by 2020.09.08
    void comboBox_ezgwy_activated(int index);   //耳轴过位移触点切换槽函数， add by 2020.09.08
    void comboBox_htgw_activated(int index);   //从柜门保护触点切换槽函数， add by 2020.09.08
    void comboBox_subyuliu_activated(int index);   //自定义3保护触点切换槽函数， add by 2020.09.08
    void comboBox_htdyw_activated(int index);   //滑台低液位触点切换槽函数， add by 2020.09.08


    void debug_clicked();            //调试模式-槽函数
    void normal_clicked();            //正常模式-槽函数
    void closeBtn_clicked();         //返回键槽函数，add by 2020.08.10
public:
    int getMode();//获取模式,add by 2019.04.27
    void chainLangChange();
public:
    STRU_CHAINSETDATA getChainSetData();//获取连锁设置数据
     int m_iSwitchFlag[MAX_SIZE+3];
     int m_iNewswFlag[25];
private:
    Ui::chainsetDialog *m_pUi;
public:
    void init(); //初始化连锁设置页面改为public，add by 2020.11.24
private:
//	void init();                                                //初始化连锁设置页面
    void allSetBtnEnable(bool enable);                          //所有设置使能
    void refreshChainButton(int nIndex,QToolButton *toolButton);//刷新连锁按钮状态
    void showChainButton(int nIndex,QToolButton *toolButton);  //显示连锁按钮状态
    void disableChainSet();
    void setAllSwitchIcon(QIcon icon);//设置所有切换按钮图标，add by 2019.05.25
    void setAllSwitchValue(int nValue);//设置所有切换按钮值，add by 2019.05.25
    void initChainSetData();//初始化连锁屏蔽设置m_ChainSetData,add by 2019.05.26
    void newinitChainSetData();//初始化连锁屏蔽设置m_ChainSetData,add by zw 2022.02.23
private:
     QIcon m_ybonicon;  //压板-合图标
     QIcon m_ybofficon; //压板-开图标
     int m_iChainsetval;//连锁设置值
     CGPIORW m_Gpiorw;//GPIO读写类对象
     int m_nGPIOfd;
     QString m_strFriendlytips;//友情提示语
     QStringList m_strListSuccess;
     QStringList m_strListFailure;
     QString  m_strAllSuccess;
     QString  m_strAllFailure;

     STRU_CHAINSETDATA m_ChainSetData;//连锁设置结构体对象,add by 2019.04.13
     STRU_NEWCHASETDATA m_newChaSetData;//连锁设置结构体对象,add by zw 2022.02.23
     int m_iMode;//模式
     bool m_isTongyi;//统一按钮切换标志位,add by 2019.05.25
     CInifileparse  m_IniChainset;//基本参数ini文件读写类对象
};
#endif // CHAINSETDLG_H
