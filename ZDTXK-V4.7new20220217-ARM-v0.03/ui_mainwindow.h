/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jul 26 18:35:31 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "mylineedit.h"

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QToolButton *toolButton_Home;
    QToolButton *toolButton_Slave;
    QToolButton *toolButton_StaRecord;
    QToolButton *toolButton_Set;
    QToolButton *toolButton_Master;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_5;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_31;
    QStackedWidget *stackedWidget;
    QWidget *homepage;
    QToolButton *toolButton_logo;
    QToolButton *toolButton_gfstate;
    QToolButton *toolButton_gainctl;
    QToolButton *toolButton_staIndicator;
    QFrame *frame_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_67;
    QLabel *label_lqstatus;
    QLabel *label_licistatus;
    QLabel *label_readystatus;
    QLabel *label_zengyistatus;
    QLabel *label_faultstatus;
    QToolButton *toolButton_gfctl;
    QFrame *frame_3;
    QLabel *proctypelabel;
    QLabel *label_feedback;
    QLabel *label_connect;
    QLabel *label_procinfo;
    QFrame *frame_4;
    QLabel *label_3;
    QLabel *label_14;
    QLCDNumber *lineEdit_totalcurrent;
    QLCDNumber *lineEdit_totalvolt;
    QLineEdit *lineEdit_AVolt;
    QLabel *label_18;
    QLabel *label_16;
    QLineEdit *lineEdit_exitvolt;
    QLabel *label_36;
    QLineEdit *lineEdit_exitcurrent;
    QLabel *label_47;
    QLabel *label_20;
    QLabel *label_71;
    QLabel *label_22;
    QLineEdit *lineEdit_BVolt;
    QLabel *label_74;
    QLabel *label_24;
    QLineEdit *lineEdit_CVolt;
    QLabel *label_76;
    QFrame *frame_5;
    QScrollBar *horizontalScrollBar;
    QLabel *label_slider;
    QLabel *label_4;
    QLabel *label_28;
    QComboBox *comboBox_gear;
    QToolButton *toolButton_zystart;
    QFrame *frame_6;
    QLabel *label_emergency;
    QLabel *label_start;
    QLabel *label_stop;
    QLabel *label_reset;
    QPushButton *jjtjBtn;
    QToolButton *toolButton_gfstart;
    QToolButton *toolButton_gfreset;
    QToolButton *toolButton_gfstop;
    QLabel *curtime_label;
    QPushButton *pushButton_CN;
    QPushButton *pushButton_EN;
    QWidget *fenguipage;
    QToolButton *toolButton_TempCtl;
    QToolButton *toolButton_FaultSta;
    QToolButton *toolButton_RunningSta;
    QToolButton *toolButton_HisCurve;
    QPushButton *fgDigBtn;
    QStackedWidget *SubStackedWidget;
    QWidget *sub1page;
    QLineEdit *busvolt_label_1;
    QLabel *label_sub1volt;
    QLabel *label_75;
    QLCDNumber *slavevolt_label_1;
    QLabel *label_sub1current;
    QFrame *frame_17;
    QToolButton *toolButton_fgstatus_1;
    QLabel *sub1label_runstate;
    QLabel *busvolt_1;
    QLCDNumber *slavecurrent_label_1;
    QWidget *sub2page;
    QLabel *label_78;
    QLabel *busvolt_2;
    QFrame *frame_18;
    QToolButton *toolButton_fgstatus_2;
    QLabel *sub2label_runstate;
    QLCDNumber *slavevolt_label_2;
    QLabel *label_sub2volt;
    QLCDNumber *slavecurrent_label_2;
    QLabel *label_sub2current;
    QLineEdit *busvolt_label_2;
    QWidget *sub3page;
    QLabel *label_sub3current;
    QLCDNumber *slavevolt_label_3;
    QLCDNumber *slavecurrent_label_3;
    QLabel *label_sub3volt;
    QFrame *frame_14;
    QToolButton *toolButton_fgstatus_3;
    QLabel *sub3label_runstate;
    QLabel *busvolt_3;
    QLineEdit *busvolt_label_3;
    QLabel *label_56;
    QWidget *sub4page;
    QLineEdit *busvolt_label_4;
    QLabel *label_sub4volt;
    QLabel *label_68;
    QLCDNumber *slavevolt_label_4;
    QLabel *label_sub4current;
    QFrame *frame_15;
    QToolButton *toolButton_fgstatus_4;
    QLabel *sub4label_runstate;
    QLabel *busvolt_4;
    QLCDNumber *slavecurrent_label_4;
    QFrame *frame_7;
    QFrame *frame_8;
    QLabel *label_7;
    QLabel *label_2;
    QToolButton *toolButton_fg1mbh;
    QToolButton *toolButton_fg1zlqgw;
    QLabel *label_sub1;
    QFrame *frame_9;
    QLabel *label_30;
    QToolButton *toolButton_fg2mbh;
    QToolButton *toolButton_fg2zlqgw;
    QLabel *label_13;
    QLabel *label_sub2;
    QFrame *frame_10;
    QLabel *label_32;
    QToolButton *toolButton_fg3mbh;
    QLabel *label_15;
    QToolButton *toolButton_fg3zlqgw;
    QLabel *label_sub3;
    QFrame *frame_13;
    QLabel *label_34;
    QToolButton *toolButton_fg4mbh;
    QToolButton *toolButton_fg4zlqgw;
    QLabel *label_26;
    QLabel *label_sub4;
    QPushButton *sub1Btn;
    QPushButton *sub2Btn;
    QPushButton *sub3Btn;
    QPushButton *sub4Btn;
    QWidget *ztjlpage;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_25;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_29;
    QLabel *totaltime_label;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_31;
    QLabel *lasttime_label;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLabel *label_totalrecord;
    QLabel *label_69;
    QLabel *label_70;
    QLabel *label_totalpage;
    QLabel *label_72;
    QLabel *label_5;
    mylineedit *lineEdit_page;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_30;
    QPushButton *upBtn;
    QSpacerItem *horizontalSpacer_31;
    QPushButton *nextBtn;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *firstBtn;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *tailBtn;
    QSpacerItem *horizontalSpacer_11;
    QTableWidget *tableWidget;
    QWidget *shezhipage;
    QToolButton *adjBtn;
    QToolButton *chainBtn;
    QToolButton *invalidBtn;
    QToolButton *pwdsetBtn;
    QToolButton *basicparaBtn;
    QToolButton *lrctlBtn;
    QToolButton *syssetBtn;
    QWidget *zhuguipage;
    QFrame *frame_16;
    QLabel *label_46;
    QToolButton *toolButton_jjtj;
    QToolButton *toolButton_jjtjchain;
    QFrame *frame_19;
    QLabel *label_49;
    QToolButton *toolButton_htgwy;
    QToolButton *toolButton_htgwychain;
    QFrame *frame_21;
    QLabel *label_58;
    QToolButton *toolButton_htgwy_2;
    QToolButton *toolButton_htgwychain_2;
    QFrame *frame_22;
    QLabel *label_48;
    QToolButton *toolButton_jjtj_2;
    QToolButton *toolButton_jjtjchain_2;
    QFrame *frame_20;
    QLabel *label_59;
    QLabel *label_57;
    QLabel *label_77;
    QFrame *frame_23;
    QFrame *frame_25;
    QToolButton *toolButton_zdtgwy;
    QToolButton *toolButton_zdtgwychain;
    QLabel *label_99;
    QFrame *frame_24;
    QLabel *label_100;
    QToolButton *toolButton_htdyw;
    QToolButton *toolButton_htdywchain;
    QFrame *frame_26;
    QLabel *label_102;
    QToolButton *toolButton_htzcdy;
    QToolButton *toolButton_htzcdychain;
    QFrame *frame_27;
    QLabel *label_103;
    QToolButton *toolButton_zdtgw;
    QToolButton *toolButton_zdtgwchain;
    QFrame *frame_28;
    QToolButton *toolButton_htgwchain;
    QLabel *label_112;
    QToolButton *toolButton_htgw;
    QFrame *frame_29;
    QLabel *label_73;
    QLabel *label_84;
    QLabel *label_79;
    QFrame *frame_30;
    QLabel *label_104;
    QToolButton *toolButton_sjjtj;
    QToolButton *toolButton_sjjtjchain;
    QFrame *frame_34;
    QLabel *label_105;
    QToolButton *toolButton_gfrjbh;
    QToolButton *toolButton_gfrjbhchain;
    QFrame *frame_35;
    QLabel *label_106;
    QToolButton *toolButton_jyzcdy;
    QToolButton *toolButton_jyzcdychain;
    QFrame *frame_36;
    QLabel *label_107;
    QToolButton *toolButton_zgmbh;
    QToolButton *toolButton_zgmbhchain;
    QFrame *frame_37;
    QLabel *label_108;
    QToolButton *toolButton_xtlqdy;
    QToolButton *toolButton_xtlqdychain;
    QFrame *frame_38;
    QLabel *label_109;
    QToolButton *toolButton_seldefine4;
    QToolButton *toolButton_seldefine4chain;
    QFrame *frame_39;
    QLabel *label_110;
    QToolButton *toolButton_seldefine2;
    QToolButton *toolButton_seldefine2chain;
    QFrame *frame_40;
    QLabel *label_111;
    QToolButton *toolButton_seldefine3;
    QToolButton *toolButton_seldefine3chain;
    QFrame *frame_41;
    QLabel *label_101;
    QToolButton *toolButton_seldefine1;
    QToolButton *toolButton_seldefine1chain;
    QToolButton *toolButton_Debug;
    QToolButton *OutLogBtn;
    QWidget *debugpage;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QLabel *label_51;
    mylineedit *lEdit_AVolt_Simu;
    QLabel *label_54;
    QLabel *label_52;
    mylineedit *lEdit_BVolt_Simu;
    QLabel *label_55;
    QLabel *label_53;
    mylineedit *lEdit_CVolt_Simu;
    QLabel *label_60;
    QLabel *label_64;
    mylineedit *lEdit_BusVolt_Simu;
    QLabel *label_63;
    QLabel *label_61;
    mylineedit *lEdit_ExcitCurrent_Simu;
    QLabel *label_62;
    QLabel *label_65;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *a01;
    QLabel *a02;
    QLabel *a03;
    QLabel *a04;
    QLabel *a05;
    QLabel *a06;
    QLabel *a07;
    QLabel *a08;
    QVBoxLayout *verticalLayout_7;
    QLabel *b01;
    QLabel *b02;
    QLabel *b03;
    QLabel *b04;
    QLabel *b05;
    QLabel *b06;
    QLabel *b07;
    QLabel *b08;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_66;
    QLabel *label_key;
    QTextEdit *DebugTextEdit;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_sendmsg;
    QPushButton *pushButton_Send;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *updatesetBtn;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *clearlogBtn;
    QSpacerItem *horizontalSpacer_12;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->resize(1210, 621);
        mainWindow->setBaseSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8("logo_top.png"), QSize(), QIcon::Normal, QIcon::Off);
        mainWindow->setWindowIcon(icon);
        mainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 141, 581));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 98, 132);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButton_Home = new QToolButton(frame);
        toolButton_Home->setObjectName(QString::fromUtf8("toolButton_Home"));
        toolButton_Home->setGeometry(QRect(10, 5, 125, 110));
        toolButton_Home->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        toolButton_Home->setFont(font);
        toolButton_Home->setStyleSheet(QString::fromUtf8("background-color: rgb(191, 110, 40);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("bin/png/homedefault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Home->setIcon(icon1);
        toolButton_Home->setIconSize(QSize(128, 128));
        toolButton_Slave = new QToolButton(frame);
        toolButton_Slave->setObjectName(QString::fromUtf8("toolButton_Slave"));
        toolButton_Slave->setGeometry(QRect(10, 115, 125, 110));
        toolButton_Slave->setFont(font);
        toolButton_Slave->setStyleSheet(QString::fromUtf8("background-color: rgb(191, 110, 40);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("bin/png/fenguidefault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Slave->setIcon(icon2);
        toolButton_Slave->setIconSize(QSize(128, 128));
        toolButton_StaRecord = new QToolButton(frame);
        toolButton_StaRecord->setObjectName(QString::fromUtf8("toolButton_StaRecord"));
        toolButton_StaRecord->setGeometry(QRect(10, 225, 125, 110));
        toolButton_StaRecord->setFont(font);
        toolButton_StaRecord->setStyleSheet(QString::fromUtf8("background-color: rgb(191, 110, 40);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("bin/png/ztjldefault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_StaRecord->setIcon(icon3);
        toolButton_StaRecord->setIconSize(QSize(128, 128));
        toolButton_Set = new QToolButton(frame);
        toolButton_Set->setObjectName(QString::fromUtf8("toolButton_Set"));
        toolButton_Set->setGeometry(QRect(10, 335, 125, 110));
        toolButton_Set->setFont(font);
        toolButton_Set->setStyleSheet(QString::fromUtf8("background-color: rgb(191, 110, 40);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("bin/png/shezhidefault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Set->setIcon(icon4);
        toolButton_Set->setIconSize(QSize(128, 128));
        toolButton_Master = new QToolButton(frame);
        toolButton_Master->setObjectName(QString::fromUtf8("toolButton_Master"));
        toolButton_Master->setGeometry(QRect(10, 445, 125, 110));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolButton_Master->sizePolicy().hasHeightForWidth());
        toolButton_Master->setSizePolicy(sizePolicy);
        toolButton_Master->setFont(font);
        toolButton_Master->setStyleSheet(QString::fromUtf8("background-color: rgb(191, 110, 40);"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("bin/png/zhuguikgdefault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Master->setIcon(icon5);
        toolButton_Master->setIconSize(QSize(128, 128));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_5 = new QVBoxLayout(layoutWidget1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_6 = new QVBoxLayout(layoutWidget2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        frame_31 = new QFrame(centralwidget);
        frame_31->setObjectName(QString::fromUtf8("frame_31"));
        frame_31->setGeometry(QRect(145, 0, 881, 581));
        frame_31->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 98, 132);"));
        frame_31->setFrameShape(QFrame::StyledPanel);
        frame_31->setFrameShadow(QFrame::Raised);
        stackedWidget = new QStackedWidget(frame_31);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 10, 891, 541));
        homepage = new QWidget();
        homepage->setObjectName(QString::fromUtf8("homepage"));
        toolButton_logo = new QToolButton(homepage);
        toolButton_logo->setObjectName(QString::fromUtf8("toolButton_logo"));
        toolButton_logo->setGeometry(QRect(770, 450, 91, 91));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("logo_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_logo->setIcon(icon6);
        toolButton_logo->setIconSize(QSize(107, 107));
        toolButton_gfstate = new QToolButton(homepage);
        toolButton_gfstate->setObjectName(QString::fromUtf8("toolButton_gfstate"));
        toolButton_gfstate->setGeometry(QRect(3, 2, 361, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        toolButton_gfstate->setFont(font1);
        toolButton_gfstate->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(58, 130, 191);"));
        toolButton_gfstate->setToolButtonStyle(Qt::ToolButtonTextOnly);
        toolButton_gainctl = new QToolButton(homepage);
        toolButton_gainctl->setObjectName(QString::fromUtf8("toolButton_gainctl"));
        toolButton_gainctl->setGeometry(QRect(380, 290, 471, 31));
        toolButton_gainctl->setFont(font1);
        toolButton_gainctl->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(58, 130, 191);"));
        toolButton_gainctl->setToolButtonStyle(Qt::ToolButtonTextOnly);
        toolButton_staIndicator = new QToolButton(homepage);
        toolButton_staIndicator->setObjectName(QString::fromUtf8("toolButton_staIndicator"));
        toolButton_staIndicator->setGeometry(QRect(380, 2, 471, 31));
        toolButton_staIndicator->setFont(font1);
        toolButton_staIndicator->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(58, 130, 191);"));
        toolButton_staIndicator->setToolButtonStyle(Qt::ToolButtonTextOnly);
        frame_2 = new QFrame(homepage);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(380, 33, 471, 106));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 98, 132);"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(210, 70, 90, 36));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(11);
        label_11->setFont(font2);
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(300, 70, 90, 36));
        label_12->setFont(font2);
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 70, 41, 36));
        label_9->setFont(font2);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(120, 70, 41, 36));
        label_10->setFont(font2);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_67 = new QLabel(frame_2);
        label_67->setObjectName(QString::fromUtf8("label_67"));
        label_67->setGeometry(QRect(390, 70, 41, 36));
        label_67->setFont(font2);
        label_67->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_lqstatus = new QLabel(frame_2);
        label_lqstatus->setObjectName(QString::fromUtf8("label_lqstatus"));
        label_lqstatus->setGeometry(QRect(20, 10, 60, 60));
        label_lqstatus->setStyleSheet(QString::fromUtf8("border-image: url(:/gct_ied_gray.png);"));
        label_licistatus = new QLabel(frame_2);
        label_licistatus->setObjectName(QString::fromUtf8("label_licistatus"));
        label_licistatus->setGeometry(QRect(110, 10, 60, 60));
        label_licistatus->setStyleSheet(QString::fromUtf8("border-image: url(:/gct_ied_gray.png);"));
        label_readystatus = new QLabel(frame_2);
        label_readystatus->setObjectName(QString::fromUtf8("label_readystatus"));
        label_readystatus->setGeometry(QRect(200, 10, 60, 60));
        label_readystatus->setStyleSheet(QString::fromUtf8("border-image: url(:/gct_ied_gray.png);"));
        label_zengyistatus = new QLabel(frame_2);
        label_zengyistatus->setObjectName(QString::fromUtf8("label_zengyistatus"));
        label_zengyistatus->setGeometry(QRect(290, 10, 60, 60));
        label_zengyistatus->setStyleSheet(QString::fromUtf8("border-image: url(:/gct_ied_gray.png);"));
        label_faultstatus = new QLabel(frame_2);
        label_faultstatus->setObjectName(QString::fromUtf8("label_faultstatus"));
        label_faultstatus->setGeometry(QRect(380, 10, 60, 60));
        label_faultstatus->setStyleSheet(QString::fromUtf8("border-image: url(:/gct_ied_gray.png);"));
        toolButton_gfctl = new QToolButton(homepage);
        toolButton_gfctl->setObjectName(QString::fromUtf8("toolButton_gfctl"));
        toolButton_gfctl->setGeometry(QRect(380, 150, 471, 31));
        toolButton_gfctl->setFont(font1);
        toolButton_gfctl->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(58, 130, 191);"));
        toolButton_gfctl->setToolButtonStyle(Qt::ToolButtonTextOnly);
        frame_3 = new QFrame(homepage);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(0, 460, 540, 80));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 98, 132);"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        proctypelabel = new QLabel(frame_3);
        proctypelabel->setObjectName(QString::fromUtf8("proctypelabel"));
        proctypelabel->setGeometry(QRect(10, 40, 121, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(14);
        proctypelabel->setFont(font3);
        proctypelabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_feedback = new QLabel(frame_3);
        label_feedback->setObjectName(QString::fromUtf8("label_feedback"));
        label_feedback->setGeometry(QRect(10, 10, 121, 31));
        label_feedback->setFont(font3);
        label_feedback->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_connect = new QLabel(frame_3);
        label_connect->setObjectName(QString::fromUtf8("label_connect"));
        label_connect->setGeometry(QRect(135, 11, 391, 31));
        label_connect->setMaximumSize(QSize(16777215, 50));
        label_connect->setFont(font3);
        label_connect->setStyleSheet(QString::fromUtf8("color: rgb(66, 212, 254);"));
        label_procinfo = new QLabel(frame_3);
        label_procinfo->setObjectName(QString::fromUtf8("label_procinfo"));
        label_procinfo->setGeometry(QRect(140, 39, 391, 31));
        label_procinfo->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0);"));
        label_connect->raise();
        proctypelabel->raise();
        label_feedback->raise();
        label_procinfo->raise();
        frame_4 = new QFrame(homepage);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(3, 32, 361, 411));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 98, 132);"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 141, 31));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font4.setPointSize(18);
        label_3->setFont(font4);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_14 = new QLabel(frame_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(180, 10, 141, 31));
        label_14->setFont(font4);
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_totalcurrent = new QLCDNumber(frame_4);
        lineEdit_totalcurrent->setObjectName(QString::fromUtf8("lineEdit_totalcurrent"));
        lineEdit_totalcurrent->setGeometry(QRect(195, 40, 151, 100));
        lineEdit_totalcurrent->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);"));
        lineEdit_totalvolt = new QLCDNumber(frame_4);
        lineEdit_totalvolt->setObjectName(QString::fromUtf8("lineEdit_totalvolt"));
        lineEdit_totalvolt->setGeometry(QRect(15, 40, 151, 100));
        lineEdit_totalvolt->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);"));
        lineEdit_AVolt = new QLineEdit(frame_4);
        lineEdit_AVolt->setObjectName(QString::fromUtf8("lineEdit_AVolt"));
        lineEdit_AVolt->setGeometry(QRect(170, 265, 150, 35));
        lineEdit_AVolt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_18 = new QLabel(frame_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(12, 215, 140, 35));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font5.setPointSize(16);
        label_18->setFont(font5);
        label_18->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_16 = new QLabel(frame_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(12, 165, 140, 35));
        label_16->setFont(font5);
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_exitvolt = new QLineEdit(frame_4);
        lineEdit_exitvolt->setObjectName(QString::fromUtf8("lineEdit_exitvolt"));
        lineEdit_exitvolt->setGeometry(QRect(170, 165, 150, 35));
        lineEdit_exitvolt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_36 = new QLabel(frame_4);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(337, 165, 16, 35));
        QFont font6;
        font6.setPointSize(16);
        label_36->setFont(font6);
        label_36->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_exitcurrent = new QLineEdit(frame_4);
        lineEdit_exitcurrent->setObjectName(QString::fromUtf8("lineEdit_exitcurrent"));
        lineEdit_exitcurrent->setGeometry(QRect(170, 215, 150, 35));
        lineEdit_exitcurrent->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_47 = new QLabel(frame_4);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setGeometry(QRect(337, 215, 16, 35));
        label_47->setFont(font6);
        label_47->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_20 = new QLabel(frame_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(12, 265, 140, 35));
        label_20->setFont(font5);
        label_20->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_71 = new QLabel(frame_4);
        label_71->setObjectName(QString::fromUtf8("label_71"));
        label_71->setGeometry(QRect(337, 265, 16, 35));
        label_71->setFont(font6);
        label_71->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_22 = new QLabel(frame_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(12, 315, 140, 35));
        label_22->setFont(font5);
        label_22->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_BVolt = new QLineEdit(frame_4);
        lineEdit_BVolt->setObjectName(QString::fromUtf8("lineEdit_BVolt"));
        lineEdit_BVolt->setGeometry(QRect(170, 315, 150, 35));
        lineEdit_BVolt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_74 = new QLabel(frame_4);
        label_74->setObjectName(QString::fromUtf8("label_74"));
        label_74->setGeometry(QRect(337, 315, 16, 35));
        label_74->setFont(font6);
        label_74->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_24 = new QLabel(frame_4);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(12, 365, 140, 35));
        label_24->setFont(font5);
        label_24->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_CVolt = new QLineEdit(frame_4);
        lineEdit_CVolt->setObjectName(QString::fromUtf8("lineEdit_CVolt"));
        lineEdit_CVolt->setGeometry(QRect(170, 365, 150, 35));
        lineEdit_CVolt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_76 = new QLabel(frame_4);
        label_76->setObjectName(QString::fromUtf8("label_76"));
        label_76->setGeometry(QRect(337, 365, 16, 35));
        label_76->setFont(font6);
        label_76->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_5 = new QFrame(homepage);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(381, 322, 471, 121));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 98, 132);"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalScrollBar = new QScrollBar(frame_5);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(20, 70, 400, 51));
        horizontalScrollBar->setMaximum(100);
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        label_slider = new QLabel(frame_5);
        label_slider->setObjectName(QString::fromUtf8("label_slider"));
        label_slider->setGeometry(QRect(420, 70, 41, 41));
        QFont font7;
        font7.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font7.setPointSize(20);
        label_slider->setFont(font7);
        label_slider->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_4 = new QLabel(frame_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(11, 22, 71, 28));
        label_4->setFont(font3);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_28 = new QLabel(frame_5);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(271, 22, 51, 28));
        label_28->setFont(font3);
        label_28->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        comboBox_gear = new QComboBox(frame_5);
        comboBox_gear->setObjectName(QString::fromUtf8("comboBox_gear"));
        comboBox_gear->setGeometry(QRect(330, 10, 102, 45));
        comboBox_gear->setFont(font7);
        comboBox_gear->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);"));
        toolButton_zystart = new QToolButton(frame_5);
        toolButton_zystart->setObjectName(QString::fromUtf8("toolButton_zystart"));
        toolButton_zystart->setGeometry(QRect(82, 10, 111, 50));
        toolButton_zystart->setFont(font6);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("Gain-off.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zystart->setIcon(icon7);
        toolButton_zystart->setIconSize(QSize(100, 100));
        frame_6 = new QFrame(homepage);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(381, 181, 471, 101));
        frame_6->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 98, 132);"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        label_emergency = new QLabel(frame_6);
        label_emergency->setObjectName(QString::fromUtf8("label_emergency"));
        label_emergency->setGeometry(QRect(400, 80, 51, 25));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font8.setPointSize(10);
        label_emergency->setFont(font8);
        label_emergency->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_start = new QLabel(frame_6);
        label_start->setObjectName(QString::fromUtf8("label_start"));
        label_start->setGeometry(QRect(50, 80, 42, 25));
        label_start->setFont(font8);
        label_start->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_stop = new QLabel(frame_6);
        label_stop->setObjectName(QString::fromUtf8("label_stop"));
        label_stop->setGeometry(QRect(170, 80, 42, 25));
        label_stop->setFont(font8);
        label_stop->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_reset = new QLabel(frame_6);
        label_reset->setObjectName(QString::fromUtf8("label_reset"));
        label_reset->setGeometry(QRect(280, 80, 42, 25));
        label_reset->setFont(font8);
        label_reset->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        jjtjBtn = new QPushButton(frame_6);
        jjtjBtn->setObjectName(QString::fromUtf8("jjtjBtn"));
        jjtjBtn->setGeometry(QRect(376, 3, 74, 73));
        jjtjBtn->setFont(font4);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("debug/emergency.png"), QSize(), QIcon::Normal, QIcon::Off);
        jjtjBtn->setIcon(icon8);
        jjtjBtn->setIconSize(QSize(64, 64));
        jjtjBtn->setCheckable(true);
        jjtjBtn->setAutoExclusive(true);
        jjtjBtn->setDefault(true);
        jjtjBtn->setFlat(false);
        toolButton_gfstart = new QToolButton(frame_6);
        toolButton_gfstart->setObjectName(QString::fromUtf8("toolButton_gfstart"));
        toolButton_gfstart->setGeometry(QRect(31, 3, 74, 73));
        toolButton_gfstart->setFont(font6);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("start-default.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_gfstart->setIcon(icon9);
        toolButton_gfstart->setIconSize(QSize(64, 64));
        toolButton_gfstart->setCheckable(false);
        toolButton_gfreset = new QToolButton(frame_6);
        toolButton_gfreset->setObjectName(QString::fromUtf8("toolButton_gfreset"));
        toolButton_gfreset->setGeometry(QRect(261, 3, 74, 73));
        toolButton_gfreset->setFont(font6);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("bin/png/reset-default.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_gfreset->setIcon(icon10);
        toolButton_gfreset->setIconSize(QSize(64, 64));
        toolButton_gfstop = new QToolButton(frame_6);
        toolButton_gfstop->setObjectName(QString::fromUtf8("toolButton_gfstop"));
        toolButton_gfstop->setGeometry(QRect(146, 3, 74, 73));
        toolButton_gfstop->setFont(font6);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("stop-default.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_gfstop->setIcon(icon11);
        toolButton_gfstop->setIconSize(QSize(64, 64));
        curtime_label = new QLabel(homepage);
        curtime_label->setObjectName(QString::fromUtf8("curtime_label"));
        curtime_label->setGeometry(QRect(550, 460, 111, 80));
        QFont font9;
        font9.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font9.setPointSize(13);
        curtime_label->setFont(font9);
        pushButton_CN = new QPushButton(homepage);
        pushButton_CN->setObjectName(QString::fromUtf8("pushButton_CN"));
        pushButton_CN->setGeometry(QRect(675, 460, 80, 40));
        pushButton_CN->setFont(font4);
        pushButton_CN->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 225, 255);"));
        pushButton_EN = new QPushButton(homepage);
        pushButton_EN->setObjectName(QString::fromUtf8("pushButton_EN"));
        pushButton_EN->setGeometry(QRect(675, 500, 80, 40));
        QFont font10;
        font10.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font10.setPointSize(18);
        font10.setBold(false);
        font10.setWeight(50);
        pushButton_EN->setFont(font10);
        pushButton_EN->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 225, 255)"));
        stackedWidget->addWidget(homepage);
        fenguipage = new QWidget();
        fenguipage->setObjectName(QString::fromUtf8("fenguipage"));
        toolButton_TempCtl = new QToolButton(fenguipage);
        toolButton_TempCtl->setObjectName(QString::fromUtf8("toolButton_TempCtl"));
        toolButton_TempCtl->setGeometry(QRect(60, 7, 141, 81));
        toolButton_TempCtl->setFont(font3);
        toolButton_TempCtl->setStyleSheet(QString::fromUtf8("background-color: rgb(214, 214, 214);\n"
"color: rgb(67, 70, 82);"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("bin/png/temperctldefault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TempCtl->setIcon(icon12);
        toolButton_TempCtl->setIconSize(QSize(64, 64));
        toolButton_TempCtl->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_FaultSta = new QToolButton(fenguipage);
        toolButton_FaultSta->setObjectName(QString::fromUtf8("toolButton_FaultSta"));
        toolButton_FaultSta->setGeometry(QRect(270, 7, 141, 81));
        toolButton_FaultSta->setFont(font3);
        toolButton_FaultSta->setStyleSheet(QString::fromUtf8("background-color: rgb(214, 214, 214);\n"
"color: rgb(67, 70, 82);"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8("bin/png/faultctlfault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_FaultSta->setIcon(icon13);
        toolButton_FaultSta->setIconSize(QSize(256, 256));
        toolButton_FaultSta->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_RunningSta = new QToolButton(fenguipage);
        toolButton_RunningSta->setObjectName(QString::fromUtf8("toolButton_RunningSta"));
        toolButton_RunningSta->setGeometry(QRect(480, 7, 141, 81));
        toolButton_RunningSta->setFont(font3);
        toolButton_RunningSta->setStyleSheet(QString::fromUtf8("background-color: rgb(214, 214, 214);\n"
"color: rgb(67, 70, 82);"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("bin/png/runingctlfault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_RunningSta->setIcon(icon14);
        toolButton_RunningSta->setIconSize(QSize(256, 256));
        toolButton_RunningSta->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_HisCurve = new QToolButton(fenguipage);
        toolButton_HisCurve->setObjectName(QString::fromUtf8("toolButton_HisCurve"));
        toolButton_HisCurve->setGeometry(QRect(690, 7, 141, 81));
        toolButton_HisCurve->setFont(font3);
        toolButton_HisCurve->setStyleSheet(QString::fromUtf8("background-color: rgb(214, 214, 214);\n"
"color: rgb(67, 70, 82);"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8("bin/png/historycuvfault.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_HisCurve->setIcon(icon15);
        toolButton_HisCurve->setIconSize(QSize(256, 256));
        toolButton_HisCurve->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        fgDigBtn = new QPushButton(fenguipage);
        fgDigBtn->setObjectName(QString::fromUtf8("fgDigBtn"));
        fgDigBtn->setGeometry(QRect(480, 120, 371, 41));
        fgDigBtn->setFont(font1);
        fgDigBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-color: rgb(58, 130, 191);"));
        SubStackedWidget = new QStackedWidget(fenguipage);
        SubStackedWidget->setObjectName(QString::fromUtf8("SubStackedWidget"));
        SubStackedWidget->setGeometry(QRect(50, 160, 341, 341));
        SubStackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 61, 97);"));
        sub1page = new QWidget();
        sub1page->setObjectName(QString::fromUtf8("sub1page"));
        busvolt_label_1 = new QLineEdit(sub1page);
        busvolt_label_1->setObjectName(QString::fromUtf8("busvolt_label_1"));
        busvolt_label_1->setGeometry(QRect(150, 260, 140, 41));
        busvolt_label_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_sub1volt = new QLabel(sub1page);
        label_sub1volt->setObjectName(QString::fromUtf8("label_sub1volt"));
        label_sub1volt->setGeometry(QRect(70, 110, 121, 35));
        label_sub1volt->setFont(font4);
        label_sub1volt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_75 = new QLabel(sub1page);
        label_75->setObjectName(QString::fromUtf8("label_75"));
        label_75->setGeometry(QRect(290, 260, 21, 35));
        label_75->setFont(font4);
        label_75->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        slavevolt_label_1 = new QLCDNumber(sub1page);
        slavevolt_label_1->setObjectName(QString::fromUtf8("slavevolt_label_1"));
        slavevolt_label_1->setGeometry(QRect(40, 150, 121, 96));
        slavevolt_label_1->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);\n"
"background-color: rgb(9, 57, 93);"));
        label_sub1current = new QLabel(sub1page);
        label_sub1current->setObjectName(QString::fromUtf8("label_sub1current"));
        label_sub1current->setGeometry(QRect(220, 110, 121, 35));
        label_sub1current->setFont(font4);
        label_sub1current->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_17 = new QFrame(sub1page);
        frame_17->setObjectName(QString::fromUtf8("frame_17"));
        frame_17->setGeometry(QRect(60, 30, 240, 58));
        frame_17->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 61, 97);"));
        frame_17->setFrameShape(QFrame::StyledPanel);
        frame_17->setFrameShadow(QFrame::Raised);
        toolButton_fgstatus_1 = new QToolButton(frame_17);
        toolButton_fgstatus_1->setObjectName(QString::fromUtf8("toolButton_fgstatus_1"));
        toolButton_fgstatus_1->setGeometry(QRect(160, 8, 38, 38));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8("gct_ied_green.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_fgstatus_1->setIcon(icon16);
        toolButton_fgstatus_1->setIconSize(QSize(32, 32));
        sub1label_runstate = new QLabel(frame_17);
        sub1label_runstate->setObjectName(QString::fromUtf8("sub1label_runstate"));
        sub1label_runstate->setGeometry(QRect(40, 10, 120, 35));
        sub1label_runstate->setFont(font4);
        sub1label_runstate->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        busvolt_1 = new QLabel(sub1page);
        busvolt_1->setObjectName(QString::fromUtf8("busvolt_1"));
        busvolt_1->setGeometry(QRect(30, 261, 120, 35));
        busvolt_1->setFont(font4);
        busvolt_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        slavecurrent_label_1 = new QLCDNumber(sub1page);
        slavecurrent_label_1->setObjectName(QString::fromUtf8("slavecurrent_label_1"));
        slavecurrent_label_1->setGeometry(QRect(189, 150, 121, 96));
        QFont font11;
        font11.setPointSize(18);
        slavecurrent_label_1->setFont(font11);
        slavecurrent_label_1->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);\n"
"background-color: rgb(9, 57, 93);"));
        SubStackedWidget->addWidget(sub1page);
        sub2page = new QWidget();
        sub2page->setObjectName(QString::fromUtf8("sub2page"));
        label_78 = new QLabel(sub2page);
        label_78->setObjectName(QString::fromUtf8("label_78"));
        label_78->setGeometry(QRect(290, 261, 21, 35));
        label_78->setFont(font4);
        label_78->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        busvolt_2 = new QLabel(sub2page);
        busvolt_2->setObjectName(QString::fromUtf8("busvolt_2"));
        busvolt_2->setGeometry(QRect(30, 261, 120, 35));
        busvolt_2->setFont(font4);
        busvolt_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_18 = new QFrame(sub2page);
        frame_18->setObjectName(QString::fromUtf8("frame_18"));
        frame_18->setGeometry(QRect(60, 30, 240, 58));
        frame_18->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 61, 97);"));
        frame_18->setFrameShape(QFrame::StyledPanel);
        frame_18->setFrameShadow(QFrame::Raised);
        toolButton_fgstatus_2 = new QToolButton(frame_18);
        toolButton_fgstatus_2->setObjectName(QString::fromUtf8("toolButton_fgstatus_2"));
        toolButton_fgstatus_2->setGeometry(QRect(160, 8, 38, 38));
        toolButton_fgstatus_2->setIcon(icon16);
        toolButton_fgstatus_2->setIconSize(QSize(32, 32));
        sub2label_runstate = new QLabel(frame_18);
        sub2label_runstate->setObjectName(QString::fromUtf8("sub2label_runstate"));
        sub2label_runstate->setGeometry(QRect(40, 10, 120, 35));
        sub2label_runstate->setFont(font4);
        sub2label_runstate->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        slavevolt_label_2 = new QLCDNumber(sub2page);
        slavevolt_label_2->setObjectName(QString::fromUtf8("slavevolt_label_2"));
        slavevolt_label_2->setGeometry(QRect(40, 150, 121, 96));
        slavevolt_label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);\n"
"background-color: rgb(9, 57, 93);"));
        label_sub2volt = new QLabel(sub2page);
        label_sub2volt->setObjectName(QString::fromUtf8("label_sub2volt"));
        label_sub2volt->setGeometry(QRect(70, 110, 121, 35));
        label_sub2volt->setFont(font4);
        label_sub2volt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        slavecurrent_label_2 = new QLCDNumber(sub2page);
        slavecurrent_label_2->setObjectName(QString::fromUtf8("slavecurrent_label_2"));
        slavecurrent_label_2->setGeometry(QRect(189, 150, 121, 96));
        slavecurrent_label_2->setFont(font11);
        slavecurrent_label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);\n"
"background-color: rgb(9, 57, 93);"));
        label_sub2current = new QLabel(sub2page);
        label_sub2current->setObjectName(QString::fromUtf8("label_sub2current"));
        label_sub2current->setGeometry(QRect(220, 110, 121, 35));
        label_sub2current->setFont(font4);
        label_sub2current->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        busvolt_label_2 = new QLineEdit(sub2page);
        busvolt_label_2->setObjectName(QString::fromUtf8("busvolt_label_2"));
        busvolt_label_2->setGeometry(QRect(150, 260, 140, 41));
        busvolt_label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        SubStackedWidget->addWidget(sub2page);
        sub3page = new QWidget();
        sub3page->setObjectName(QString::fromUtf8("sub3page"));
        label_sub3current = new QLabel(sub3page);
        label_sub3current->setObjectName(QString::fromUtf8("label_sub3current"));
        label_sub3current->setGeometry(QRect(220, 110, 121, 35));
        label_sub3current->setFont(font4);
        label_sub3current->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        slavevolt_label_3 = new QLCDNumber(sub3page);
        slavevolt_label_3->setObjectName(QString::fromUtf8("slavevolt_label_3"));
        slavevolt_label_3->setGeometry(QRect(40, 150, 121, 96));
        slavevolt_label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);\n"
"background-color: rgb(9, 57, 93);"));
        slavecurrent_label_3 = new QLCDNumber(sub3page);
        slavecurrent_label_3->setObjectName(QString::fromUtf8("slavecurrent_label_3"));
        slavecurrent_label_3->setGeometry(QRect(189, 150, 121, 96));
        slavecurrent_label_3->setFont(font11);
        slavecurrent_label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);\n"
"background-color: rgb(9, 57, 93);"));
        label_sub3volt = new QLabel(sub3page);
        label_sub3volt->setObjectName(QString::fromUtf8("label_sub3volt"));
        label_sub3volt->setGeometry(QRect(70, 110, 121, 35));
        label_sub3volt->setFont(font4);
        label_sub3volt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_14 = new QFrame(sub3page);
        frame_14->setObjectName(QString::fromUtf8("frame_14"));
        frame_14->setGeometry(QRect(60, 30, 240, 58));
        frame_14->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 61, 97);"));
        frame_14->setFrameShape(QFrame::StyledPanel);
        frame_14->setFrameShadow(QFrame::Raised);
        toolButton_fgstatus_3 = new QToolButton(frame_14);
        toolButton_fgstatus_3->setObjectName(QString::fromUtf8("toolButton_fgstatus_3"));
        toolButton_fgstatus_3->setGeometry(QRect(160, 8, 38, 38));
        toolButton_fgstatus_3->setIcon(icon16);
        toolButton_fgstatus_3->setIconSize(QSize(32, 32));
        sub3label_runstate = new QLabel(frame_14);
        sub3label_runstate->setObjectName(QString::fromUtf8("sub3label_runstate"));
        sub3label_runstate->setGeometry(QRect(40, 10, 120, 35));
        sub3label_runstate->setFont(font4);
        sub3label_runstate->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        busvolt_3 = new QLabel(sub3page);
        busvolt_3->setObjectName(QString::fromUtf8("busvolt_3"));
        busvolt_3->setGeometry(QRect(30, 261, 120, 35));
        busvolt_3->setFont(font4);
        busvolt_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        busvolt_label_3 = new QLineEdit(sub3page);
        busvolt_label_3->setObjectName(QString::fromUtf8("busvolt_label_3"));
        busvolt_label_3->setGeometry(QRect(150, 260, 140, 41));
        busvolt_label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_56 = new QLabel(sub3page);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setGeometry(QRect(290, 261, 21, 35));
        label_56->setFont(font4);
        label_56->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        SubStackedWidget->addWidget(sub3page);
        sub4page = new QWidget();
        sub4page->setObjectName(QString::fromUtf8("sub4page"));
        busvolt_label_4 = new QLineEdit(sub4page);
        busvolt_label_4->setObjectName(QString::fromUtf8("busvolt_label_4"));
        busvolt_label_4->setGeometry(QRect(150, 260, 140, 41));
        busvolt_label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_sub4volt = new QLabel(sub4page);
        label_sub4volt->setObjectName(QString::fromUtf8("label_sub4volt"));
        label_sub4volt->setGeometry(QRect(70, 110, 121, 35));
        label_sub4volt->setFont(font4);
        label_sub4volt->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_68 = new QLabel(sub4page);
        label_68->setObjectName(QString::fromUtf8("label_68"));
        label_68->setGeometry(QRect(290, 261, 21, 35));
        label_68->setFont(font4);
        label_68->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        slavevolt_label_4 = new QLCDNumber(sub4page);
        slavevolt_label_4->setObjectName(QString::fromUtf8("slavevolt_label_4"));
        slavevolt_label_4->setGeometry(QRect(40, 150, 121, 96));
        slavevolt_label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);\n"
"background-color: rgb(9, 57, 93);"));
        label_sub4current = new QLabel(sub4page);
        label_sub4current->setObjectName(QString::fromUtf8("label_sub4current"));
        label_sub4current->setGeometry(QRect(220, 110, 121, 35));
        label_sub4current->setFont(font4);
        label_sub4current->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_15 = new QFrame(sub4page);
        frame_15->setObjectName(QString::fromUtf8("frame_15"));
        frame_15->setGeometry(QRect(60, 30, 240, 58));
        frame_15->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 61, 97);"));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Raised);
        toolButton_fgstatus_4 = new QToolButton(frame_15);
        toolButton_fgstatus_4->setObjectName(QString::fromUtf8("toolButton_fgstatus_4"));
        toolButton_fgstatus_4->setGeometry(QRect(160, 8, 38, 38));
        toolButton_fgstatus_4->setIcon(icon16);
        toolButton_fgstatus_4->setIconSize(QSize(32, 32));
        sub4label_runstate = new QLabel(frame_15);
        sub4label_runstate->setObjectName(QString::fromUtf8("sub4label_runstate"));
        sub4label_runstate->setGeometry(QRect(40, 10, 120, 35));
        sub4label_runstate->setFont(font4);
        sub4label_runstate->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        busvolt_4 = new QLabel(sub4page);
        busvolt_4->setObjectName(QString::fromUtf8("busvolt_4"));
        busvolt_4->setGeometry(QRect(30, 261, 120, 35));
        busvolt_4->setFont(font4);
        busvolt_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        slavecurrent_label_4 = new QLCDNumber(sub4page);
        slavecurrent_label_4->setObjectName(QString::fromUtf8("slavecurrent_label_4"));
        slavecurrent_label_4->setGeometry(QRect(189, 150, 121, 96));
        slavecurrent_label_4->setFont(font11);
        slavecurrent_label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 198, 255);\n"
"background-color: rgb(9, 57, 93);"));
        SubStackedWidget->addWidget(sub4page);
        frame_7 = new QFrame(fenguipage);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(480, 160, 371, 341));
        frame_7->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 98, 132);"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        frame_8 = new QFrame(frame_7);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setGeometry(QRect(5, 10, 360, 80));
        frame_8->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        label_7 = new QLabel(frame_8);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(270, 50, 50, 15));
        QFont font12;
        font12.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font12.setPointSize(9);
        label_7->setFont(font12);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_2 = new QLabel(frame_8);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(145, 50, 81, 16));
        label_2->setFont(font12);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_fg1mbh = new QToolButton(frame_8);
        toolButton_fg1mbh->setObjectName(QString::fromUtf8("toolButton_fg1mbh"));
        toolButton_fg1mbh->setGeometry(QRect(275, 10, 39, 38));
        toolButton_fg1mbh->setIcon(icon16);
        toolButton_fg1mbh->setIconSize(QSize(32, 32));
        toolButton_fg1zlqgw = new QToolButton(frame_8);
        toolButton_fg1zlqgw->setObjectName(QString::fromUtf8("toolButton_fg1zlqgw"));
        toolButton_fg1zlqgw->setGeometry(QRect(165, 10, 39, 38));
        toolButton_fg1zlqgw->setIcon(icon16);
        toolButton_fg1zlqgw->setIconSize(QSize(32, 32));
        label_sub1 = new QLabel(frame_8);
        label_sub1->setObjectName(QString::fromUtf8("label_sub1"));
        label_sub1->setGeometry(QRect(30, 20, 81, 31));
        label_sub1->setFont(font11);
        label_sub1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_9 = new QFrame(frame_7);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setGeometry(QRect(5, 90, 360, 80));
        frame_9->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);;"));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        label_30 = new QLabel(frame_9);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(270, 50, 50, 15));
        label_30->setFont(font12);
        label_30->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_fg2mbh = new QToolButton(frame_9);
        toolButton_fg2mbh->setObjectName(QString::fromUtf8("toolButton_fg2mbh"));
        toolButton_fg2mbh->setGeometry(QRect(275, 10, 39, 38));
        toolButton_fg2mbh->setIcon(icon16);
        toolButton_fg2mbh->setIconSize(QSize(32, 32));
        toolButton_fg2zlqgw = new QToolButton(frame_9);
        toolButton_fg2zlqgw->setObjectName(QString::fromUtf8("toolButton_fg2zlqgw"));
        toolButton_fg2zlqgw->setGeometry(QRect(165, 10, 39, 38));
        toolButton_fg2zlqgw->setIcon(icon16);
        toolButton_fg2zlqgw->setIconSize(QSize(32, 32));
        label_13 = new QLabel(frame_9);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(145, 50, 81, 16));
        label_13->setFont(font12);
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_sub2 = new QLabel(frame_9);
        label_sub2->setObjectName(QString::fromUtf8("label_sub2"));
        label_sub2->setGeometry(QRect(30, 20, 81, 31));
        label_sub2->setFont(font11);
        label_sub2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_10 = new QFrame(frame_7);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setGeometry(QRect(5, 170, 360, 80));
        frame_10->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));
        frame_10->setFrameShape(QFrame::StyledPanel);
        frame_10->setFrameShadow(QFrame::Raised);
        label_32 = new QLabel(frame_10);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(270, 50, 50, 15));
        label_32->setFont(font12);
        label_32->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_fg3mbh = new QToolButton(frame_10);
        toolButton_fg3mbh->setObjectName(QString::fromUtf8("toolButton_fg3mbh"));
        toolButton_fg3mbh->setGeometry(QRect(275, 10, 39, 38));
        toolButton_fg3mbh->setIcon(icon16);
        toolButton_fg3mbh->setIconSize(QSize(32, 32));
        label_15 = new QLabel(frame_10);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(145, 50, 81, 16));
        label_15->setFont(font12);
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_fg3zlqgw = new QToolButton(frame_10);
        toolButton_fg3zlqgw->setObjectName(QString::fromUtf8("toolButton_fg3zlqgw"));
        toolButton_fg3zlqgw->setGeometry(QRect(165, 10, 39, 38));
        toolButton_fg3zlqgw->setIcon(icon16);
        toolButton_fg3zlqgw->setIconSize(QSize(32, 32));
        label_sub3 = new QLabel(frame_10);
        label_sub3->setObjectName(QString::fromUtf8("label_sub3"));
        label_sub3->setGeometry(QRect(30, 20, 81, 31));
        label_sub3->setFont(font11);
        label_sub3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_13 = new QFrame(frame_7);
        frame_13->setObjectName(QString::fromUtf8("frame_13"));
        frame_13->setGeometry(QRect(5, 250, 360, 80));
        frame_13->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));
        frame_13->setFrameShape(QFrame::StyledPanel);
        frame_13->setFrameShadow(QFrame::Raised);
        label_34 = new QLabel(frame_13);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(270, 50, 50, 15));
        label_34->setFont(font12);
        label_34->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_fg4mbh = new QToolButton(frame_13);
        toolButton_fg4mbh->setObjectName(QString::fromUtf8("toolButton_fg4mbh"));
        toolButton_fg4mbh->setGeometry(QRect(275, 10, 39, 38));
        toolButton_fg4mbh->setIcon(icon16);
        toolButton_fg4mbh->setIconSize(QSize(32, 32));
        toolButton_fg4zlqgw = new QToolButton(frame_13);
        toolButton_fg4zlqgw->setObjectName(QString::fromUtf8("toolButton_fg4zlqgw"));
        toolButton_fg4zlqgw->setGeometry(QRect(165, 10, 39, 38));
        toolButton_fg4zlqgw->setIcon(icon16);
        toolButton_fg4zlqgw->setIconSize(QSize(32, 32));
        label_26 = new QLabel(frame_13);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(145, 50, 81, 16));
        label_26->setFont(font12);
        label_26->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_sub4 = new QLabel(frame_13);
        label_sub4->setObjectName(QString::fromUtf8("label_sub4"));
        label_sub4->setGeometry(QRect(30, 20, 81, 31));
        label_sub4->setFont(font11);
        label_sub4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        sub1Btn = new QPushButton(fenguipage);
        sub1Btn->setObjectName(QString::fromUtf8("sub1Btn"));
        sub1Btn->setGeometry(QRect(50, 121, 85, 39));
        sub1Btn->setFont(font1);
        sub1Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172);\n"
"font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        sub2Btn = new QPushButton(fenguipage);
        sub2Btn->setObjectName(QString::fromUtf8("sub2Btn"));
        sub2Btn->setGeometry(QRect(135, 121, 85, 39));
        sub2Btn->setFont(font1);
        sub2Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172);\n"
"font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        sub3Btn = new QPushButton(fenguipage);
        sub3Btn->setObjectName(QString::fromUtf8("sub3Btn"));
        sub3Btn->setGeometry(QRect(220, 121, 85, 39));
        sub3Btn->setFont(font1);
        sub3Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172);\n"
"font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        sub4Btn = new QPushButton(fenguipage);
        sub4Btn->setObjectName(QString::fromUtf8("sub4Btn"));
        sub4Btn->setGeometry(QRect(305, 121, 85, 39));
        sub4Btn->setFont(font1);
        sub4Btn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(138, 157, 172);\n"
"font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        stackedWidget->addWidget(fenguipage);
        sub1Btn->raise();
        sub2Btn->raise();
        sub3Btn->raise();
        sub4Btn->raise();
        toolButton_TempCtl->raise();
        toolButton_FaultSta->raise();
        toolButton_RunningSta->raise();
        toolButton_HisCurve->raise();
        fgDigBtn->raise();
        SubStackedWidget->raise();
        frame_7->raise();
        ztjlpage = new QWidget();
        ztjlpage->setObjectName(QString::fromUtf8("ztjlpage"));
        gridLayout_6 = new QGridLayout(ztjlpage);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_29 = new QLabel(ztjlpage);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        QFont font13;
        font13.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font13.setPointSize(14);
        font13.setBold(true);
        font13.setWeight(75);
        label_29->setFont(font13);
        label_29->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_7->addWidget(label_29);

        totaltime_label = new QLabel(ztjlpage);
        totaltime_label->setObjectName(QString::fromUtf8("totaltime_label"));
        totaltime_label->setFont(font13);
        totaltime_label->setStyleSheet(QString::fromUtf8("color: rgb(254, 254, 0);"));

        horizontalLayout_7->addWidget(totaltime_label);


        horizontalLayout_25->addLayout(horizontalLayout_7);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_15);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_31 = new QLabel(ztjlpage);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setFont(font13);
        label_31->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_23->addWidget(label_31);

        lasttime_label = new QLabel(ztjlpage);
        lasttime_label->setObjectName(QString::fromUtf8("lasttime_label"));
        lasttime_label->setFont(font13);
        lasttime_label->setStyleSheet(QString::fromUtf8("color: rgb(254, 254, 0);"));

        horizontalLayout_23->addWidget(lasttime_label);


        horizontalLayout_25->addLayout(horizontalLayout_23);


        gridLayout_6->addLayout(horizontalLayout_25, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(ztjlpage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font3);

        horizontalLayout_5->addWidget(label);

        label_totalrecord = new QLabel(ztjlpage);
        label_totalrecord->setObjectName(QString::fromUtf8("label_totalrecord"));
        label_totalrecord->setFont(font3);

        horizontalLayout_5->addWidget(label_totalrecord);

        label_69 = new QLabel(ztjlpage);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setFont(font3);

        horizontalLayout_5->addWidget(label_69);

        label_70 = new QLabel(ztjlpage);
        label_70->setObjectName(QString::fromUtf8("label_70"));
        label_70->setFont(font3);

        horizontalLayout_5->addWidget(label_70);

        label_totalpage = new QLabel(ztjlpage);
        label_totalpage->setObjectName(QString::fromUtf8("label_totalpage"));
        label_totalpage->setFont(font3);

        horizontalLayout_5->addWidget(label_totalpage);

        label_72 = new QLabel(ztjlpage);
        label_72->setObjectName(QString::fromUtf8("label_72"));
        label_72->setFont(font3);

        horizontalLayout_5->addWidget(label_72);

        label_5 = new QLabel(ztjlpage);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font3);

        horizontalLayout_5->addWidget(label_5);

        lineEdit_page = new mylineedit(ztjlpage);
        lineEdit_page->setObjectName(QString::fromUtf8("lineEdit_page"));
        lineEdit_page->setBaseSize(QSize(0, 0));
        QFont font14;
        font14.setPointSize(14);
        lineEdit_page->setFont(font14);
        lineEdit_page->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(lineEdit_page);

        label_6 = new QLabel(ztjlpage);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font3);

        horizontalLayout_5->addWidget(label_6);

        horizontalSpacer_30 = new QSpacerItem(13, 41, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_30);

        upBtn = new QPushButton(ztjlpage);
        upBtn->setObjectName(QString::fromUtf8("upBtn"));
        upBtn->setFont(font3);
        upBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(35, 210, 92);"));

        horizontalLayout_5->addWidget(upBtn);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_31);

        nextBtn = new QPushButton(ztjlpage);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setFont(font3);

        horizontalLayout_5->addWidget(nextBtn);

        horizontalSpacer_9 = new QSpacerItem(13, 41, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        firstBtn = new QPushButton(ztjlpage);
        firstBtn->setObjectName(QString::fromUtf8("firstBtn"));
        firstBtn->setFont(font3);

        horizontalLayout_5->addWidget(firstBtn);

        horizontalSpacer_10 = new QSpacerItem(13, 41, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        tailBtn = new QPushButton(ztjlpage);
        tailBtn->setObjectName(QString::fromUtf8("tailBtn"));
        tailBtn->setFont(font3);

        horizontalLayout_5->addWidget(tailBtn);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);


        gridLayout_6->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        tableWidget = new QTableWidget(ztjlpage);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QFont font15;
        font15.setPointSize(14);
        font15.setBold(true);
        font15.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font15);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font15);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font15);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font15);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font15);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font15);
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 10)
            tableWidget->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem15);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        QFont font16;
        font16.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font16.setPointSize(18);
        font16.setKerning(true);
        tableWidget->setFont(font16);
        tableWidget->setAutoFillBackground(false);
        tableWidget->setStyleSheet(QString::fromUtf8("QScrollBar::vertical\n"
"{\n"
"    width: 35px;\n"
"}\n"
"QScrollBar::horizontal\n"
"{\n"
"    height: 35px;\n"
"}\n"
"color: rgb(57, 201, 255);"));
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setFrameShadow(QFrame::Sunken);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setProperty("showDropIndicator", QVariant(true));
        tableWidget->setDragDropOverwriteMode(true);
        tableWidget->setShowGrid(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);

        gridLayout_6->addWidget(tableWidget, 1, 0, 1, 1);

        stackedWidget->addWidget(ztjlpage);
        shezhipage = new QWidget();
        shezhipage->setObjectName(QString::fromUtf8("shezhipage"));
        adjBtn = new QToolButton(shezhipage);
        adjBtn->setObjectName(QString::fromUtf8("adjBtn"));
        adjBtn->setGeometry(QRect(20, 80, 200, 130));
        adjBtn->setMaximumSize(QSize(250, 250));
        adjBtn->setFont(font5);
        adjBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8("adjcoef.png"), QSize(), QIcon::Normal, QIcon::Off);
        adjBtn->setIcon(icon17);
        adjBtn->setIconSize(QSize(108, 108));
        chainBtn = new QToolButton(shezhipage);
        chainBtn->setObjectName(QString::fromUtf8("chainBtn"));
        chainBtn->setGeometry(QRect(560, 80, 200, 130));
        chainBtn->setFont(font5);
        chainBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8("chainset.png"), QSize(), QIcon::Normal, QIcon::Off);
        chainBtn->setIcon(icon18);
        chainBtn->setIconSize(QSize(108, 108));
        invalidBtn = new QToolButton(shezhipage);
        invalidBtn->setObjectName(QString::fromUtf8("invalidBtn"));
        invalidBtn->setGeometry(QRect(780, 200, 81, 81));
        QFont font17;
        font17.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font17.setPointSize(8);
        invalidBtn->setFont(font17);
        invalidBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8("invalidset.png"), QSize(), QIcon::Normal, QIcon::Off);
        invalidBtn->setIcon(icon19);
        invalidBtn->setIconSize(QSize(20, 20));
        pwdsetBtn = new QToolButton(shezhipage);
        pwdsetBtn->setObjectName(QString::fromUtf8("pwdsetBtn"));
        pwdsetBtn->setGeometry(QRect(290, 80, 200, 130));
        pwdsetBtn->setFont(font5);
        pwdsetBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8("passwordset.png"), QSize(), QIcon::Normal, QIcon::Off);
        pwdsetBtn->setIcon(icon20);
        pwdsetBtn->setIconSize(QSize(108, 108));
        basicparaBtn = new QToolButton(shezhipage);
        basicparaBtn->setObjectName(QString::fromUtf8("basicparaBtn"));
        basicparaBtn->setGeometry(QRect(560, 280, 200, 130));
        basicparaBtn->setFont(font5);
        basicparaBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8("basicpara.png"), QSize(), QIcon::Normal, QIcon::Off);
        basicparaBtn->setIcon(icon21);
        basicparaBtn->setIconSize(QSize(108, 108));
        lrctlBtn = new QToolButton(shezhipage);
        lrctlBtn->setObjectName(QString::fromUtf8("lrctlBtn"));
        lrctlBtn->setGeometry(QRect(20, 280, 200, 130));
        lrctlBtn->setFont(font5);
        lrctlBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8("remotectl.png"), QSize(), QIcon::Normal, QIcon::Off);
        lrctlBtn->setIcon(icon22);
        lrctlBtn->setIconSize(QSize(108, 108));
        syssetBtn = new QToolButton(shezhipage);
        syssetBtn->setObjectName(QString::fromUtf8("syssetBtn"));
        syssetBtn->setGeometry(QRect(290, 280, 200, 130));
        syssetBtn->setFont(font5);
        syssetBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);"));
        syssetBtn->setIcon(icon21);
        syssetBtn->setIconSize(QSize(108, 108));
        stackedWidget->addWidget(shezhipage);
        zhuguipage = new QWidget();
        zhuguipage->setObjectName(QString::fromUtf8("zhuguipage"));
        frame_16 = new QFrame(zhuguipage);
        frame_16->setObjectName(QString::fromUtf8("frame_16"));
        frame_16->setGeometry(QRect(440, 190, 420, 48));
        frame_16->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Raised);
        label_46 = new QLabel(frame_16);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setGeometry(QRect(10, 10, 211, 30));
        label_46->setFont(font4);
        label_46->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jjtj = new QToolButton(frame_16);
        toolButton_jjtj->setObjectName(QString::fromUtf8("toolButton_jjtj"));
        toolButton_jjtj->setGeometry(QRect(225, 6, 39, 38));
        toolButton_jjtj->setIcon(icon16);
        toolButton_jjtj->setIconSize(QSize(32, 32));
        toolButton_jjtjchain = new QToolButton(frame_16);
        toolButton_jjtjchain->setObjectName(QString::fromUtf8("toolButton_jjtjchain"));
        toolButton_jjtjchain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_jjtjchain->setFont(font5);
        QIcon icon23;
        icon23.addFile(QString::fromUtf8("yb_on.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_jjtjchain->setIcon(icon23);
        toolButton_jjtjchain->setIconSize(QSize(66, 48));
        frame_19 = new QFrame(zhuguipage);
        frame_19->setObjectName(QString::fromUtf8("frame_19"));
        frame_19->setGeometry(QRect(0, 334, 420, 48));
        frame_19->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_19->setFrameShape(QFrame::StyledPanel);
        frame_19->setFrameShadow(QFrame::Raised);
        label_49 = new QLabel(frame_19);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setGeometry(QRect(10, 10, 211, 31));
        label_49->setFont(font4);
        label_49->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_htgwy = new QToolButton(frame_19);
        toolButton_htgwy->setObjectName(QString::fromUtf8("toolButton_htgwy"));
        toolButton_htgwy->setGeometry(QRect(225, 6, 39, 38));
        toolButton_htgwy->setIcon(icon16);
        toolButton_htgwy->setIconSize(QSize(32, 32));
        toolButton_htgwychain = new QToolButton(frame_19);
        toolButton_htgwychain->setObjectName(QString::fromUtf8("toolButton_htgwychain"));
        toolButton_htgwychain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_htgwychain->setFont(font5);
        toolButton_htgwychain->setIcon(icon23);
        toolButton_htgwychain->setIconSize(QSize(66, 48));
        frame_21 = new QFrame(frame_19);
        frame_21->setObjectName(QString::fromUtf8("frame_21"));
        frame_21->setGeometry(QRect(0, 90, 361, 48));
        frame_21->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_21->setFrameShape(QFrame::StyledPanel);
        frame_21->setFrameShadow(QFrame::Raised);
        label_58 = new QLabel(frame_21);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        label_58->setGeometry(QRect(10, 10, 120, 31));
        label_58->setFont(font4);
        label_58->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_htgwy_2 = new QToolButton(frame_21);
        toolButton_htgwy_2->setObjectName(QString::fromUtf8("toolButton_htgwy_2"));
        toolButton_htgwy_2->setGeometry(QRect(170, 10, 39, 38));
        toolButton_htgwy_2->setIcon(icon16);
        toolButton_htgwy_2->setIconSize(QSize(32, 32));
        toolButton_htgwychain_2 = new QToolButton(frame_21);
        toolButton_htgwychain_2->setObjectName(QString::fromUtf8("toolButton_htgwychain_2"));
        toolButton_htgwychain_2->setGeometry(QRect(270, 0, 73, 54));
        toolButton_htgwychain_2->setFont(font5);
        toolButton_htgwychain_2->setIcon(icon23);
        toolButton_htgwychain_2->setIconSize(QSize(66, 48));
        frame_22 = new QFrame(frame_19);
        frame_22->setObjectName(QString::fromUtf8("frame_22"));
        frame_22->setGeometry(QRect(0, 50, 361, 48));
        frame_22->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_22->setFrameShape(QFrame::StyledPanel);
        frame_22->setFrameShadow(QFrame::Raised);
        label_48 = new QLabel(frame_22);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setGeometry(QRect(10, 10, 96, 30));
        label_48->setFont(font4);
        label_48->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jjtj_2 = new QToolButton(frame_22);
        toolButton_jjtj_2->setObjectName(QString::fromUtf8("toolButton_jjtj_2"));
        toolButton_jjtj_2->setGeometry(QRect(170, 10, 39, 37));
        toolButton_jjtj_2->setIcon(icon16);
        toolButton_jjtj_2->setIconSize(QSize(32, 32));
        toolButton_jjtjchain_2 = new QToolButton(frame_22);
        toolButton_jjtjchain_2->setObjectName(QString::fromUtf8("toolButton_jjtjchain_2"));
        toolButton_jjtjchain_2->setGeometry(QRect(270, 0, 73, 40));
        toolButton_jjtjchain_2->setFont(font5);
        toolButton_jjtjchain_2->setIcon(icon23);
        toolButton_jjtjchain_2->setIconSize(QSize(66, 48));
        frame_20 = new QFrame(zhuguipage);
        frame_20->setObjectName(QString::fromUtf8("frame_20"));
        frame_20->setGeometry(QRect(0, 54, 420, 43));
        frame_20->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_20->setFrameShape(QFrame::StyledPanel);
        frame_20->setFrameShadow(QFrame::Raised);
        label_59 = new QLabel(frame_20);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        label_59->setGeometry(QRect(300, 10, 121, 28));
        label_59->setFont(font1);
        label_59->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(57, 201, 255);"));
        label_57 = new QLabel(frame_20);
        label_57->setObjectName(QString::fromUtf8("label_57"));
        label_57->setGeometry(QRect(170, 10, 141, 28));
        label_57->setFont(font1);
        label_57->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(57, 201, 255);"));
        label_77 = new QLabel(frame_20);
        label_77->setObjectName(QString::fromUtf8("label_77"));
        label_77->setGeometry(QRect(20, 10, 101, 28));
        label_77->setFont(font1);
        label_77->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(57, 201, 255);"));
        frame_23 = new QFrame(zhuguipage);
        frame_23->setObjectName(QString::fromUtf8("frame_23"));
        frame_23->setGeometry(QRect(0, 190, 420, 48));
        frame_23->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_23->setFrameShape(QFrame::StyledPanel);
        frame_23->setFrameShadow(QFrame::Raised);
        frame_25 = new QFrame(frame_23);
        frame_25->setObjectName(QString::fromUtf8("frame_25"));
        frame_25->setGeometry(QRect(160, 39, 71, 51));
        frame_25->setFrameShape(QFrame::StyledPanel);
        frame_25->setFrameShadow(QFrame::Raised);
        toolButton_zdtgwy = new QToolButton(frame_23);
        toolButton_zdtgwy->setObjectName(QString::fromUtf8("toolButton_zdtgwy"));
        toolButton_zdtgwy->setGeometry(QRect(225, 6, 39, 38));
        toolButton_zdtgwy->setIcon(icon16);
        toolButton_zdtgwy->setIconSize(QSize(32, 32));
        toolButton_zdtgwychain = new QToolButton(frame_23);
        toolButton_zdtgwychain->setObjectName(QString::fromUtf8("toolButton_zdtgwychain"));
        toolButton_zdtgwychain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_zdtgwychain->setFont(font5);
        toolButton_zdtgwychain->setIcon(icon23);
        toolButton_zdtgwychain->setIconSize(QSize(66, 48));
        label_99 = new QLabel(frame_23);
        label_99->setObjectName(QString::fromUtf8("label_99"));
        label_99->setGeometry(QRect(10, 10, 211, 31));
        label_99->setFont(font4);
        label_99->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_24 = new QFrame(zhuguipage);
        frame_24->setObjectName(QString::fromUtf8("frame_24"));
        frame_24->setGeometry(QRect(0, 238, 420, 48));
        frame_24->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_24->setFrameShape(QFrame::StyledPanel);
        frame_24->setFrameShadow(QFrame::Raised);
        label_100 = new QLabel(frame_24);
        label_100->setObjectName(QString::fromUtf8("label_100"));
        label_100->setGeometry(QRect(10, 10, 211, 30));
        label_100->setFont(font4);
        label_100->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_htdyw = new QToolButton(frame_24);
        toolButton_htdyw->setObjectName(QString::fromUtf8("toolButton_htdyw"));
        toolButton_htdyw->setGeometry(QRect(225, 6, 39, 38));
        toolButton_htdyw->setIcon(icon16);
        toolButton_htdyw->setIconSize(QSize(32, 32));
        toolButton_htdywchain = new QToolButton(frame_24);
        toolButton_htdywchain->setObjectName(QString::fromUtf8("toolButton_htdywchain"));
        toolButton_htdywchain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_htdywchain->setFont(font5);
        toolButton_htdywchain->setIcon(icon23);
        toolButton_htdywchain->setIconSize(QSize(66, 48));
        frame_26 = new QFrame(zhuguipage);
        frame_26->setObjectName(QString::fromUtf8("frame_26"));
        frame_26->setGeometry(QRect(0, 286, 420, 48));
        frame_26->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_26->setFrameShape(QFrame::StyledPanel);
        frame_26->setFrameShadow(QFrame::Raised);
        label_102 = new QLabel(frame_26);
        label_102->setObjectName(QString::fromUtf8("label_102"));
        label_102->setGeometry(QRect(10, 10, 211, 31));
        label_102->setFont(font4);
        label_102->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_htzcdy = new QToolButton(frame_26);
        toolButton_htzcdy->setObjectName(QString::fromUtf8("toolButton_htzcdy"));
        toolButton_htzcdy->setGeometry(QRect(225, 6, 39, 38));
        toolButton_htzcdy->setIcon(icon16);
        toolButton_htzcdy->setIconSize(QSize(32, 32));
        toolButton_htzcdychain = new QToolButton(frame_26);
        toolButton_htzcdychain->setObjectName(QString::fromUtf8("toolButton_htzcdychain"));
        toolButton_htzcdychain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_htzcdychain->setFont(font5);
        toolButton_htzcdychain->setIcon(icon23);
        toolButton_htzcdychain->setIconSize(QSize(66, 48));
        frame_27 = new QFrame(zhuguipage);
        frame_27->setObjectName(QString::fromUtf8("frame_27"));
        frame_27->setGeometry(QRect(0, 142, 420, 48));
        frame_27->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_27->setFrameShape(QFrame::StyledPanel);
        frame_27->setFrameShadow(QFrame::Raised);
        label_103 = new QLabel(frame_27);
        label_103->setObjectName(QString::fromUtf8("label_103"));
        label_103->setGeometry(QRect(10, 10, 211, 31));
        label_103->setFont(font4);
        label_103->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_zdtgw = new QToolButton(frame_27);
        toolButton_zdtgw->setObjectName(QString::fromUtf8("toolButton_zdtgw"));
        toolButton_zdtgw->setGeometry(QRect(225, 6, 39, 38));
        toolButton_zdtgw->setIcon(icon16);
        toolButton_zdtgw->setIconSize(QSize(32, 32));
        toolButton_zdtgwchain = new QToolButton(frame_27);
        toolButton_zdtgwchain->setObjectName(QString::fromUtf8("toolButton_zdtgwchain"));
        toolButton_zdtgwchain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_zdtgwchain->setFont(font5);
        toolButton_zdtgwchain->setIcon(icon23);
        toolButton_zdtgwchain->setIconSize(QSize(66, 48));
        frame_28 = new QFrame(zhuguipage);
        frame_28->setObjectName(QString::fromUtf8("frame_28"));
        frame_28->setGeometry(QRect(0, 382, 420, 48));
        frame_28->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_28->setFrameShape(QFrame::StyledPanel);
        frame_28->setFrameShadow(QFrame::Raised);
        toolButton_htgwchain = new QToolButton(frame_28);
        toolButton_htgwchain->setObjectName(QString::fromUtf8("toolButton_htgwchain"));
        toolButton_htgwchain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_htgwchain->setFont(font5);
        toolButton_htgwchain->setIcon(icon23);
        toolButton_htgwchain->setIconSize(QSize(66, 48));
        label_112 = new QLabel(frame_28);
        label_112->setObjectName(QString::fromUtf8("label_112"));
        label_112->setGeometry(QRect(10, 10, 211, 31));
        label_112->setFont(font4);
        label_112->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_htgw = new QToolButton(frame_28);
        toolButton_htgw->setObjectName(QString::fromUtf8("toolButton_htgw"));
        toolButton_htgw->setGeometry(QRect(225, 6, 39, 38));
        toolButton_htgw->setIcon(icon16);
        toolButton_htgw->setIconSize(QSize(32, 32));
        frame_29 = new QFrame(zhuguipage);
        frame_29->setObjectName(QString::fromUtf8("frame_29"));
        frame_29->setGeometry(QRect(440, 54, 421, 43));
        frame_29->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_29->setFrameShape(QFrame::StyledPanel);
        frame_29->setFrameShadow(QFrame::Raised);
        label_73 = new QLabel(frame_29);
        label_73->setObjectName(QString::fromUtf8("label_73"));
        label_73->setGeometry(QRect(300, 10, 121, 28));
        label_73->setFont(font1);
        label_73->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(57, 201, 255);"));
        label_84 = new QLabel(frame_29);
        label_84->setObjectName(QString::fromUtf8("label_84"));
        label_84->setGeometry(QRect(170, 10, 131, 28));
        label_84->setFont(font1);
        label_84->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(57, 201, 255);"));
        label_79 = new QLabel(frame_29);
        label_79->setObjectName(QString::fromUtf8("label_79"));
        label_79->setGeometry(QRect(20, 10, 111, 28));
        label_79->setFont(font1);
        label_79->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(57, 201, 255);"));
        frame_30 = new QFrame(zhuguipage);
        frame_30->setObjectName(QString::fromUtf8("frame_30"));
        frame_30->setGeometry(QRect(440, 238, 420, 48));
        frame_30->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_30->setFrameShape(QFrame::StyledPanel);
        frame_30->setFrameShadow(QFrame::Raised);
        label_104 = new QLabel(frame_30);
        label_104->setObjectName(QString::fromUtf8("label_104"));
        label_104->setGeometry(QRect(10, 10, 221, 31));
        label_104->setFont(font4);
        label_104->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_sjjtj = new QToolButton(frame_30);
        toolButton_sjjtj->setObjectName(QString::fromUtf8("toolButton_sjjtj"));
        toolButton_sjjtj->setGeometry(QRect(225, 6, 39, 38));
        toolButton_sjjtj->setIcon(icon16);
        toolButton_sjjtj->setIconSize(QSize(32, 32));
        toolButton_sjjtjchain = new QToolButton(frame_30);
        toolButton_sjjtjchain->setObjectName(QString::fromUtf8("toolButton_sjjtjchain"));
        toolButton_sjjtjchain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_sjjtjchain->setFont(font5);
        toolButton_sjjtjchain->setIcon(icon23);
        toolButton_sjjtjchain->setIconSize(QSize(66, 48));
        frame_34 = new QFrame(zhuguipage);
        frame_34->setObjectName(QString::fromUtf8("frame_34"));
        frame_34->setGeometry(QRect(0, 430, 420, 48));
        frame_34->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_34->setFrameShape(QFrame::StyledPanel);
        frame_34->setFrameShadow(QFrame::Raised);
        label_105 = new QLabel(frame_34);
        label_105->setObjectName(QString::fromUtf8("label_105"));
        label_105->setGeometry(QRect(10, 10, 221, 31));
        label_105->setFont(font4);
        label_105->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_gfrjbh = new QToolButton(frame_34);
        toolButton_gfrjbh->setObjectName(QString::fromUtf8("toolButton_gfrjbh"));
        toolButton_gfrjbh->setGeometry(QRect(225, 6, 39, 38));
        toolButton_gfrjbh->setIcon(icon16);
        toolButton_gfrjbh->setIconSize(QSize(32, 32));
        toolButton_gfrjbhchain = new QToolButton(frame_34);
        toolButton_gfrjbhchain->setObjectName(QString::fromUtf8("toolButton_gfrjbhchain"));
        toolButton_gfrjbhchain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_gfrjbhchain->setFont(font5);
        toolButton_gfrjbhchain->setIcon(icon23);
        toolButton_gfrjbhchain->setIconSize(QSize(66, 48));
        frame_35 = new QFrame(zhuguipage);
        frame_35->setObjectName(QString::fromUtf8("frame_35"));
        frame_35->setGeometry(QRect(440, 97, 420, 48));
        frame_35->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_35->setFrameShape(QFrame::StyledPanel);
        frame_35->setFrameShadow(QFrame::Raised);
        label_106 = new QLabel(frame_35);
        label_106->setObjectName(QString::fromUtf8("label_106"));
        label_106->setGeometry(QRect(10, 10, 191, 31));
        label_106->setFont(font4);
        label_106->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_jyzcdy = new QToolButton(frame_35);
        toolButton_jyzcdy->setObjectName(QString::fromUtf8("toolButton_jyzcdy"));
        toolButton_jyzcdy->setGeometry(QRect(225, 6, 39, 38));
        toolButton_jyzcdy->setIcon(icon16);
        toolButton_jyzcdy->setIconSize(QSize(32, 32));
        toolButton_jyzcdychain = new QToolButton(frame_35);
        toolButton_jyzcdychain->setObjectName(QString::fromUtf8("toolButton_jyzcdychain"));
        toolButton_jyzcdychain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_jyzcdychain->setFont(font5);
        toolButton_jyzcdychain->setIcon(icon23);
        toolButton_jyzcdychain->setIconSize(QSize(66, 48));
        frame_36 = new QFrame(zhuguipage);
        frame_36->setObjectName(QString::fromUtf8("frame_36"));
        frame_36->setGeometry(QRect(440, 142, 420, 48));
        frame_36->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_36->setFrameShape(QFrame::StyledPanel);
        frame_36->setFrameShadow(QFrame::Raised);
        label_107 = new QLabel(frame_36);
        label_107->setObjectName(QString::fromUtf8("label_107"));
        label_107->setGeometry(QRect(10, 10, 211, 31));
        label_107->setFont(font4);
        label_107->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_zgmbh = new QToolButton(frame_36);
        toolButton_zgmbh->setObjectName(QString::fromUtf8("toolButton_zgmbh"));
        toolButton_zgmbh->setGeometry(QRect(225, 6, 39, 38));
        toolButton_zgmbh->setIcon(icon16);
        toolButton_zgmbh->setIconSize(QSize(32, 32));
        toolButton_zgmbhchain = new QToolButton(frame_36);
        toolButton_zgmbhchain->setObjectName(QString::fromUtf8("toolButton_zgmbhchain"));
        toolButton_zgmbhchain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_zgmbhchain->setFont(font5);
        toolButton_zgmbhchain->setIcon(icon23);
        toolButton_zgmbhchain->setIconSize(QSize(66, 48));
        frame_37 = new QFrame(zhuguipage);
        frame_37->setObjectName(QString::fromUtf8("frame_37"));
        frame_37->setGeometry(QRect(0, 97, 420, 48));
        frame_37->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_37->setFrameShape(QFrame::StyledPanel);
        frame_37->setFrameShadow(QFrame::Raised);
        label_108 = new QLabel(frame_37);
        label_108->setObjectName(QString::fromUtf8("label_108"));
        label_108->setGeometry(QRect(10, 10, 221, 31));
        label_108->setFont(font4);
        label_108->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_xtlqdy = new QToolButton(frame_37);
        toolButton_xtlqdy->setObjectName(QString::fromUtf8("toolButton_xtlqdy"));
        toolButton_xtlqdy->setGeometry(QRect(225, 6, 39, 38));
        toolButton_xtlqdy->setIcon(icon16);
        toolButton_xtlqdy->setIconSize(QSize(32, 32));
        toolButton_xtlqdychain = new QToolButton(frame_37);
        toolButton_xtlqdychain->setObjectName(QString::fromUtf8("toolButton_xtlqdychain"));
        toolButton_xtlqdychain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_xtlqdychain->setFont(font5);
        toolButton_xtlqdychain->setIcon(icon23);
        toolButton_xtlqdychain->setIconSize(QSize(66, 48));
        frame_38 = new QFrame(zhuguipage);
        frame_38->setObjectName(QString::fromUtf8("frame_38"));
        frame_38->setGeometry(QRect(440, 430, 420, 48));
        frame_38->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_38->setFrameShape(QFrame::StyledPanel);
        frame_38->setFrameShadow(QFrame::Raised);
        label_109 = new QLabel(frame_38);
        label_109->setObjectName(QString::fromUtf8("label_109"));
        label_109->setGeometry(QRect(10, 10, 221, 31));
        label_109->setFont(font4);
        label_109->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_seldefine4 = new QToolButton(frame_38);
        toolButton_seldefine4->setObjectName(QString::fromUtf8("toolButton_seldefine4"));
        toolButton_seldefine4->setGeometry(QRect(225, 6, 39, 38));
        toolButton_seldefine4->setIcon(icon16);
        toolButton_seldefine4->setIconSize(QSize(32, 32));
        toolButton_seldefine4chain = new QToolButton(frame_38);
        toolButton_seldefine4chain->setObjectName(QString::fromUtf8("toolButton_seldefine4chain"));
        toolButton_seldefine4chain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_seldefine4chain->setFont(font5);
        toolButton_seldefine4chain->setIcon(icon23);
        toolButton_seldefine4chain->setIconSize(QSize(66, 48));
        frame_39 = new QFrame(zhuguipage);
        frame_39->setObjectName(QString::fromUtf8("frame_39"));
        frame_39->setGeometry(QRect(440, 334, 420, 48));
        frame_39->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 120);"));
        frame_39->setFrameShape(QFrame::StyledPanel);
        frame_39->setFrameShadow(QFrame::Raised);
        label_110 = new QLabel(frame_39);
        label_110->setObjectName(QString::fromUtf8("label_110"));
        label_110->setGeometry(QRect(10, 10, 221, 31));
        label_110->setFont(font4);
        label_110->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_seldefine2 = new QToolButton(frame_39);
        toolButton_seldefine2->setObjectName(QString::fromUtf8("toolButton_seldefine2"));
        toolButton_seldefine2->setGeometry(QRect(225, 6, 39, 38));
        toolButton_seldefine2->setIcon(icon16);
        toolButton_seldefine2->setIconSize(QSize(32, 32));
        toolButton_seldefine2chain = new QToolButton(frame_39);
        toolButton_seldefine2chain->setObjectName(QString::fromUtf8("toolButton_seldefine2chain"));
        toolButton_seldefine2chain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_seldefine2chain->setFont(font5);
        toolButton_seldefine2chain->setIcon(icon23);
        toolButton_seldefine2chain->setIconSize(QSize(66, 48));
        frame_40 = new QFrame(zhuguipage);
        frame_40->setObjectName(QString::fromUtf8("frame_40"));
        frame_40->setGeometry(QRect(440, 382, 420, 48));
        frame_40->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_40->setFrameShape(QFrame::StyledPanel);
        frame_40->setFrameShadow(QFrame::Raised);
        label_111 = new QLabel(frame_40);
        label_111->setObjectName(QString::fromUtf8("label_111"));
        label_111->setGeometry(QRect(10, 10, 221, 31));
        label_111->setFont(font4);
        label_111->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_seldefine3 = new QToolButton(frame_40);
        toolButton_seldefine3->setObjectName(QString::fromUtf8("toolButton_seldefine3"));
        toolButton_seldefine3->setGeometry(QRect(225, 6, 39, 38));
        toolButton_seldefine3->setIcon(icon16);
        toolButton_seldefine3->setIconSize(QSize(32, 32));
        toolButton_seldefine3chain = new QToolButton(frame_40);
        toolButton_seldefine3chain->setObjectName(QString::fromUtf8("toolButton_seldefine3chain"));
        toolButton_seldefine3chain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_seldefine3chain->setFont(font5);
        toolButton_seldefine3chain->setIcon(icon23);
        toolButton_seldefine3chain->setIconSize(QSize(66, 48));
        frame_41 = new QFrame(zhuguipage);
        frame_41->setObjectName(QString::fromUtf8("frame_41"));
        frame_41->setGeometry(QRect(440, 286, 420, 48));
        frame_41->setStyleSheet(QString::fromUtf8("background-color: rgb(2, 59, 101);"));
        frame_41->setFrameShape(QFrame::StyledPanel);
        frame_41->setFrameShadow(QFrame::Raised);
        label_101 = new QLabel(frame_41);
        label_101->setObjectName(QString::fromUtf8("label_101"));
        label_101->setGeometry(QRect(10, 10, 211, 31));
        label_101->setFont(font4);
        label_101->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        toolButton_seldefine1 = new QToolButton(frame_41);
        toolButton_seldefine1->setObjectName(QString::fromUtf8("toolButton_seldefine1"));
        toolButton_seldefine1->setGeometry(QRect(225, 6, 39, 38));
        toolButton_seldefine1->setIcon(icon16);
        toolButton_seldefine1->setIconSize(QSize(32, 32));
        toolButton_seldefine1chain = new QToolButton(frame_41);
        toolButton_seldefine1chain->setObjectName(QString::fromUtf8("toolButton_seldefine1chain"));
        toolButton_seldefine1chain->setGeometry(QRect(320, 0, 73, 40));
        toolButton_seldefine1chain->setFont(font5);
        toolButton_seldefine1chain->setIcon(icon23);
        toolButton_seldefine1chain->setIconSize(QSize(66, 48));
        toolButton_Debug = new QToolButton(zhuguipage);
        toolButton_Debug->setObjectName(QString::fromUtf8("toolButton_Debug"));
        toolButton_Debug->setGeometry(QRect(750, 10, 75, 41));
        toolButton_Debug->setFont(font4);
        OutLogBtn = new QToolButton(zhuguipage);
        OutLogBtn->setObjectName(QString::fromUtf8("OutLogBtn"));
        OutLogBtn->setGeometry(QRect(544, 10, 171, 41));
        OutLogBtn->setFont(font4);
        stackedWidget->addWidget(zhuguipage);
        debugpage = new QWidget();
        debugpage->setObjectName(QString::fromUtf8("debugpage"));
        gridLayout_4 = new QGridLayout(debugpage);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        groupBox_2 = new QGroupBox(debugpage);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(300, 16777215));
        groupBox_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_51 = new QLabel(groupBox_2);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        QFont font18;
        font18.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        label_51->setFont(font18);
        label_51->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_51, 0, 0, 1, 1);

        lEdit_AVolt_Simu = new mylineedit(groupBox_2);
        lEdit_AVolt_Simu->setObjectName(QString::fromUtf8("lEdit_AVolt_Simu"));
        lEdit_AVolt_Simu->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));

        gridLayout_5->addWidget(lEdit_AVolt_Simu, 0, 1, 1, 1);

        label_54 = new QLabel(groupBox_2);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setFont(font18);
        label_54->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_54, 0, 2, 1, 1);

        label_52 = new QLabel(groupBox_2);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setFont(font18);
        label_52->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_52, 1, 0, 1, 1);

        lEdit_BVolt_Simu = new mylineedit(groupBox_2);
        lEdit_BVolt_Simu->setObjectName(QString::fromUtf8("lEdit_BVolt_Simu"));
        lEdit_BVolt_Simu->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));

        gridLayout_5->addWidget(lEdit_BVolt_Simu, 1, 1, 1, 1);

        label_55 = new QLabel(groupBox_2);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setFont(font18);
        label_55->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_55, 1, 2, 1, 1);

        label_53 = new QLabel(groupBox_2);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setFont(font18);
        label_53->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_53, 2, 0, 1, 1);

        lEdit_CVolt_Simu = new mylineedit(groupBox_2);
        lEdit_CVolt_Simu->setObjectName(QString::fromUtf8("lEdit_CVolt_Simu"));
        lEdit_CVolt_Simu->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));

        gridLayout_5->addWidget(lEdit_CVolt_Simu, 2, 1, 1, 1);

        label_60 = new QLabel(groupBox_2);
        label_60->setObjectName(QString::fromUtf8("label_60"));
        label_60->setFont(font18);
        label_60->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_60, 2, 2, 1, 1);

        label_64 = new QLabel(groupBox_2);
        label_64->setObjectName(QString::fromUtf8("label_64"));
        label_64->setFont(font18);
        label_64->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_64, 3, 0, 1, 1);

        lEdit_BusVolt_Simu = new mylineedit(groupBox_2);
        lEdit_BusVolt_Simu->setObjectName(QString::fromUtf8("lEdit_BusVolt_Simu"));
        lEdit_BusVolt_Simu->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));

        gridLayout_5->addWidget(lEdit_BusVolt_Simu, 3, 1, 1, 1);

        label_63 = new QLabel(groupBox_2);
        label_63->setObjectName(QString::fromUtf8("label_63"));
        label_63->setFont(font18);
        label_63->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_63, 3, 2, 1, 1);

        label_61 = new QLabel(groupBox_2);
        label_61->setObjectName(QString::fromUtf8("label_61"));
        label_61->setFont(font18);
        label_61->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_61, 4, 0, 1, 1);

        lEdit_ExcitCurrent_Simu = new mylineedit(groupBox_2);
        lEdit_ExcitCurrent_Simu->setObjectName(QString::fromUtf8("lEdit_ExcitCurrent_Simu"));
        lEdit_ExcitCurrent_Simu->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));

        gridLayout_5->addWidget(lEdit_ExcitCurrent_Simu, 4, 1, 1, 1);

        label_62 = new QLabel(groupBox_2);
        label_62->setObjectName(QString::fromUtf8("label_62"));
        label_62->setFont(font18);
        label_62->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_62, 4, 2, 1, 1);

        label_65 = new QLabel(groupBox_2);
        label_65->setObjectName(QString::fromUtf8("label_65"));
        label_65->setFont(font18);
        label_65->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout_5->addWidget(label_65, 5, 0, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 57, 93);"));

        gridLayout_5->addWidget(comboBox, 5, 1, 1, 1);


        horizontalLayout_10->addWidget(groupBox_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        a01 = new QLabel(debugpage);
        a01->setObjectName(QString::fromUtf8("a01"));

        verticalLayout_3->addWidget(a01);

        a02 = new QLabel(debugpage);
        a02->setObjectName(QString::fromUtf8("a02"));

        verticalLayout_3->addWidget(a02);

        a03 = new QLabel(debugpage);
        a03->setObjectName(QString::fromUtf8("a03"));

        verticalLayout_3->addWidget(a03);

        a04 = new QLabel(debugpage);
        a04->setObjectName(QString::fromUtf8("a04"));

        verticalLayout_3->addWidget(a04);

        a05 = new QLabel(debugpage);
        a05->setObjectName(QString::fromUtf8("a05"));

        verticalLayout_3->addWidget(a05);

        a06 = new QLabel(debugpage);
        a06->setObjectName(QString::fromUtf8("a06"));

        verticalLayout_3->addWidget(a06);

        a07 = new QLabel(debugpage);
        a07->setObjectName(QString::fromUtf8("a07"));

        verticalLayout_3->addWidget(a07);

        a08 = new QLabel(debugpage);
        a08->setObjectName(QString::fromUtf8("a08"));

        verticalLayout_3->addWidget(a08);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        b01 = new QLabel(debugpage);
        b01->setObjectName(QString::fromUtf8("b01"));

        verticalLayout_7->addWidget(b01);

        b02 = new QLabel(debugpage);
        b02->setObjectName(QString::fromUtf8("b02"));

        verticalLayout_7->addWidget(b02);

        b03 = new QLabel(debugpage);
        b03->setObjectName(QString::fromUtf8("b03"));

        verticalLayout_7->addWidget(b03);

        b04 = new QLabel(debugpage);
        b04->setObjectName(QString::fromUtf8("b04"));

        verticalLayout_7->addWidget(b04);

        b05 = new QLabel(debugpage);
        b05->setObjectName(QString::fromUtf8("b05"));

        verticalLayout_7->addWidget(b05);

        b06 = new QLabel(debugpage);
        b06->setObjectName(QString::fromUtf8("b06"));

        verticalLayout_7->addWidget(b06);

        b07 = new QLabel(debugpage);
        b07->setObjectName(QString::fromUtf8("b07"));

        verticalLayout_7->addWidget(b07);

        b08 = new QLabel(debugpage);
        b08->setObjectName(QString::fromUtf8("b08"));

        verticalLayout_7->addWidget(b08);


        horizontalLayout->addLayout(verticalLayout_7);


        horizontalLayout_10->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_66 = new QLabel(debugpage);
        label_66->setObjectName(QString::fromUtf8("label_66"));
        label_66->setFont(font3);
        label_66->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 0);"));

        horizontalLayout_8->addWidget(label_66);

        label_key = new QLabel(debugpage);
        label_key->setObjectName(QString::fromUtf8("label_key"));
        QFont font19;
        font19.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font19.setPointSize(12);
        label_key->setFont(font19);
        label_key->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_8->addWidget(label_key);


        verticalLayout->addLayout(horizontalLayout_8);

        DebugTextEdit = new QTextEdit(debugpage);
        DebugTextEdit->setObjectName(QString::fromUtf8("DebugTextEdit"));

        verticalLayout->addWidget(DebugTextEdit);


        horizontalLayout_10->addLayout(verticalLayout);

        horizontalLayout_10->setStretch(0, 4);
        horizontalLayout_10->setStretch(1, 5);
        horizontalLayout_10->setStretch(2, 8);

        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_sendmsg = new QLineEdit(debugpage);
        lineEdit_sendmsg->setObjectName(QString::fromUtf8("lineEdit_sendmsg"));

        horizontalLayout_4->addWidget(lineEdit_sendmsg);

        pushButton_Send = new QPushButton(debugpage);
        pushButton_Send->setObjectName(QString::fromUtf8("pushButton_Send"));

        horizontalLayout_4->addWidget(pushButton_Send);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_13);

        updatesetBtn = new QPushButton(debugpage);
        updatesetBtn->setObjectName(QString::fromUtf8("updatesetBtn"));
        updatesetBtn->setFont(font4);

        horizontalLayout_2->addWidget(updatesetBtn);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_14);

        clearlogBtn = new QPushButton(debugpage);
        clearlogBtn->setObjectName(QString::fromUtf8("clearlogBtn"));
        clearlogBtn->setFont(font4);

        horizontalLayout_2->addWidget(clearlogBtn);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);


        horizontalLayout_6->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_6);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);

        stackedWidget->addWidget(debugpage);
        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1210, 23));
        mainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        mainWindow->setStatusBar(statusbar);

        retranslateUi(mainWindow);

        stackedWidget->setCurrentIndex(0);
        SubStackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "\346\214\257\345\212\250\345\217\260\347\224\265\346\272\220\346\216\247\345\210\266\347\263\273\347\273\237\350\275\257\344\273\266 2020.08.15-1", 0, QApplication::UnicodeUTF8));
        toolButton_Home->setText(QApplication::translate("mainWindow", "\344\270\273\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
        toolButton_Slave->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\234\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        toolButton_StaRecord->setText(QApplication::translate("mainWindow", "\347\212\266\346\200\201\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        toolButton_Set->setText(QApplication::translate("mainWindow", "\350\256\276\347\275\256\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        toolButton_Master->setText(QApplication::translate("mainWindow", "\344\270\273\346\237\234\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        toolButton_logo->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_gfstate->setText(QApplication::translate("mainWindow", "\345\212\237\346\224\276\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        toolButton_gainctl->setText(QApplication::translate("mainWindow", "\345\242\236\347\233\212\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        toolButton_staIndicator->setText(QApplication::translate("mainWindow", "\347\212\266\346\200\201\346\214\207\347\244\272\347\201\257", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("mainWindow", "\345\207\206\345\244\207", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("mainWindow", "\345\242\236\347\233\212", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("mainWindow", "\345\206\267\345\215\264", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("mainWindow", "\345\212\261\347\243\201", 0, QApplication::UnicodeUTF8));
        label_67->setText(QApplication::translate("mainWindow", "\346\225\205\351\232\234", 0, QApplication::UnicodeUTF8));
        label_lqstatus->setText(QString());
        label_licistatus->setText(QString());
        label_readystatus->setText(QString());
        label_zengyistatus->setText(QString());
        label_faultstatus->setText(QString());
        toolButton_gfctl->setText(QApplication::translate("mainWindow", "\345\212\237\346\224\276\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        proctypelabel->setText(QApplication::translate("mainWindow", "  \344\277\235\346\212\244\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        label_feedback->setText(QApplication::translate("mainWindow", "  \346\266\210\346\201\257\345\217\215\351\246\210:", 0, QApplication::UnicodeUTF8));
        label_connect->setText(QApplication::translate("mainWindow", "\350\256\276\345\244\207\350\277\236\346\216\245\347\212\266\346\200\201\346\255\243\345\270\270", 0, QApplication::UnicodeUTF8));
        label_procinfo->setText(QString());
        label_3->setText(QApplication::translate("mainWindow", "     \347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("mainWindow", "     \347\224\265\346\265\201\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("mainWindow", "   \345\212\261\347\243\201\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("mainWindow", "   \345\212\261\347\243\201\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_47->setText(QApplication::translate("mainWindow", "A", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("mainWindow", "   A\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        label_71->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("mainWindow", "   B\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        label_74->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("mainWindow", "   C\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        label_76->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_slider->setText(QApplication::translate("mainWindow", "0%", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mainWindow", "  \345\274\200\345\205\263", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("mainWindow", "\346\241\243\344\275\215", 0, QApplication::UnicodeUTF8));
        comboBox_gear->clear();
        comboBox_gear->insertItems(0, QStringList()
         << QApplication::translate("mainWindow", "10%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mainWindow", "30%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mainWindow", "50%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mainWindow", "80%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mainWindow", "100%", 0, QApplication::UnicodeUTF8)
        );
        toolButton_zystart->setText(QApplication::translate("mainWindow", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        label_emergency->setText(QApplication::translate("mainWindow", "\346\200\245\345\201\234", 0, QApplication::UnicodeUTF8));
        label_start->setText(QApplication::translate("mainWindow", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        label_stop->setText(QApplication::translate("mainWindow", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        label_reset->setText(QApplication::translate("mainWindow", "\345\244\215\344\275\215", 0, QApplication::UnicodeUTF8));
        jjtjBtn->setText(QString());
        toolButton_gfstart->setText(QApplication::translate("mainWindow", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        toolButton_gfreset->setText(QApplication::translate("mainWindow", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        toolButton_gfstop->setText(QApplication::translate("mainWindow", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        curtime_label->setText(QApplication::translate("mainWindow", "2019.02.11 13:13:00", 0, QApplication::UnicodeUTF8));
        pushButton_CN->setText(QApplication::translate("mainWindow", "\344\270\255\346\226\207", 0, QApplication::UnicodeUTF8));
        pushButton_EN->setText(QApplication::translate("mainWindow", "\350\213\261\346\226\207", 0, QApplication::UnicodeUTF8));
        toolButton_TempCtl->setText(QApplication::translate("mainWindow", "\346\270\251\345\272\246\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        toolButton_FaultSta->setText(QApplication::translate("mainWindow", "\346\225\205\351\232\234\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        toolButton_RunningSta->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        toolButton_HisCurve->setText(QApplication::translate("mainWindow", "\345\216\206\345\217\262\346\233\262\347\272\277", 0, QApplication::UnicodeUTF8));
        fgDigBtn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\234\345\274\200\345\205\263\351\207\217\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_sub1volt->setText(QApplication::translate("mainWindow", "\347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        label_75->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_sub1current->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\234\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
        toolButton_fgstatus_1->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        sub1label_runstate->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        busvolt_1->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        label_78->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        busvolt_2->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        toolButton_fgstatus_2->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        sub2label_runstate->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_sub2volt->setText(QApplication::translate("mainWindow", "\347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        label_sub2current->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\234\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
        label_sub3current->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\234\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
        label_sub3volt->setText(QApplication::translate("mainWindow", "\347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        toolButton_fgstatus_3->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        sub3label_runstate->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        busvolt_3->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        label_56->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_sub4volt->setText(QApplication::translate("mainWindow", "\347\224\265\345\216\213\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        label_68->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_sub4current->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\234\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
        toolButton_fgstatus_4->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        sub4label_runstate->setText(QApplication::translate("mainWindow", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        busvolt_4->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("mainWindow", "\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mainWindow", "\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
        toolButton_fg1mbh->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_fg1zlqgw->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_sub1->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("mainWindow", "\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        toolButton_fg2mbh->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_fg2zlqgw->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("mainWindow", "\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
        label_sub2->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("mainWindow", "\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        toolButton_fg3mbh->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("mainWindow", "\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
        toolButton_fg3zlqgw->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_sub3->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("mainWindow", "\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        toolButton_fg4mbh->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_fg4zlqgw->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("mainWindow", "\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
        label_sub4->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));
        sub1Btn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));
        sub2Btn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));
        sub3Btn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));
        sub4Btn->setText(QApplication::translate("mainWindow", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("mainWindow", "\347\263\273\347\273\237\346\200\273\350\277\220\350\241\214\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        totaltime_label->setText(QApplication::translate("mainWindow", "1\345\244\25115\345\260\217\346\227\26620\345\210\206\351\222\23710\347\247\222", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("mainWindow", "\346\234\254\346\254\241\350\277\220\350\241\214\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        lasttime_label->setText(QApplication::translate("mainWindow", "1\345\244\25115\345\260\217\346\227\26620\345\210\206\351\222\23710\347\247\222", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainWindow", "\345\205\261", 0, QApplication::UnicodeUTF8));
        label_totalrecord->setText(QApplication::translate("mainWindow", "XXXX", 0, QApplication::UnicodeUTF8));
        label_69->setText(QApplication::translate("mainWindow", "\346\235\241\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        label_70->setText(QApplication::translate("mainWindow", "\345\205\261", 0, QApplication::UnicodeUTF8));
        label_totalpage->setText(QApplication::translate("mainWindow", "XX", 0, QApplication::UnicodeUTF8));
        label_72->setText(QApplication::translate("mainWindow", "\351\241\265", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mainWindow", "\347\254\254", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("mainWindow", "\351\241\265", 0, QApplication::UnicodeUTF8));
        upBtn->setText(QApplication::translate("mainWindow", "\344\270\212\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
        nextBtn->setText(QApplication::translate("mainWindow", "\344\270\213\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
        firstBtn->setText(QApplication::translate("mainWindow", "\351\246\226  \351\241\265", 0, QApplication::UnicodeUTF8));
        tailBtn->setText(QApplication::translate("mainWindow", " \345\260\276  \351\241\265", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("mainWindow", "\346\212\245\350\255\246\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("mainWindow", "\344\277\235\346\212\244\347\261\273\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\347\224\265\345\216\213\346\234\211\346\225\210\345\200\274\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\347\224\265\345\216\213\346\234\200\345\244\247\345\200\274\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\347\224\265\346\265\201\346\234\211\346\225\210\345\200\274\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\347\224\265\346\265\201\346\234\200\345\244\247\345\200\274\357\274\210A\357\274\211", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("mainWindow", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("mainWindow", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("mainWindow", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("mainWindow", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem10->setText(QApplication::translate("mainWindow", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem11->setText(QApplication::translate("mainWindow", "6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem12->setText(QApplication::translate("mainWindow", "7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem13->setText(QApplication::translate("mainWindow", "8", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem14->setText(QApplication::translate("mainWindow", "9", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem15->setText(QApplication::translate("mainWindow", "10", 0, QApplication::UnicodeUTF8));
        adjBtn->setText(QApplication::translate("mainWindow", "\346\240\241\345\207\206\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        chainBtn->setText(QApplication::translate("mainWindow", "\350\201\224\351\224\201\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        invalidBtn->setText(QApplication::translate("mainWindow", "\345\244\261\346\225\210\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pwdsetBtn->setText(QApplication::translate("mainWindow", "\345\257\206\347\240\201\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        basicparaBtn->setText(QApplication::translate("mainWindow", "\345\237\272\346\234\254\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        lrctlBtn->setText(QApplication::translate("mainWindow", "\350\277\234\347\250\213\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        syssetBtn->setText(QApplication::translate("mainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("mainWindow", "\347\264\247\346\200\245\345\201\234\346\234\272", 0, QApplication::UnicodeUTF8));
        toolButton_jjtj->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_jjtjchain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_49->setText(QApplication::translate("mainWindow", "\346\273\221\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        toolButton_htgwy->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_htgwychain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_58->setText(QApplication::translate("mainWindow", "\346\273\221\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        toolButton_htgwy_2->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_htgwychain_2->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_48->setText(QApplication::translate("mainWindow", "\347\264\247\346\200\245\345\201\234\346\234\272", 0, QApplication::UnicodeUTF8));
        toolButton_jjtj_2->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_jjtjchain_2->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_59->setText(QApplication::translate("mainWindow", "  \345\261\217\350\224\275\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_57->setText(QApplication::translate("mainWindow", "   \345\275\223\345\211\215\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_77->setText(QApplication::translate("mainWindow", "\344\270\273\346\237\234\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        toolButton_zdtgwy->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_zdtgwychain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_99->setText(QApplication::translate("mainWindow", "\346\214\257\345\212\250\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        label_100->setText(QApplication::translate("mainWindow", "\346\273\221\345\217\260\344\275\216\346\266\262\344\275\215", 0, QApplication::UnicodeUTF8));
        toolButton_htdyw->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_htdywchain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_102->setText(QApplication::translate("mainWindow", "\346\273\221\345\217\260\346\254\240\345\216\213", 0, QApplication::UnicodeUTF8));
        toolButton_htzcdy->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_htzcdychain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_103->setText(QApplication::translate("mainWindow", "\346\214\257\345\212\250\345\217\260\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
        toolButton_zdtgw->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_zdtgwchain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        toolButton_htgwchain->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        label_112->setText(QApplication::translate("mainWindow", "\346\273\221\345\217\260\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
        toolButton_htgw->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        label_73->setText(QApplication::translate("mainWindow", "  \345\261\217\350\224\275\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_84->setText(QApplication::translate("mainWindow", "   \345\275\223\345\211\215\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_79->setText(QApplication::translate("mainWindow", "\344\270\273\346\237\234\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_104->setText(QApplication::translate("mainWindow", "S\347\264\247\346\200\245\345\201\234\346\234\272", 0, QApplication::UnicodeUTF8));
        toolButton_sjjtj->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_sjjtjchain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_105->setText(QApplication::translate("mainWindow", "\345\212\237\346\224\276\347\203\255\347\273\247\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        toolButton_gfrjbh->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_gfrjbhchain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_106->setText(QApplication::translate("mainWindow", "\351\235\231\345\216\213\350\275\264\346\211\277\344\275\216\345\216\213", 0, QApplication::UnicodeUTF8));
        toolButton_jyzcdy->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_jyzcdychain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_107->setText(QApplication::translate("mainWindow", "\344\270\273\346\237\234\351\227\250\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        toolButton_zgmbh->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_zgmbhchain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_108->setText(QApplication::translate("mainWindow", "\347\263\273\347\273\237\345\206\267\345\215\264\345\215\225\345\205\203", 0, QApplication::UnicodeUTF8));
        toolButton_xtlqdy->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_xtlqdychain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_109->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2114", 0, QApplication::UnicodeUTF8));
        toolButton_seldefine4->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_seldefine4chain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_110->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2112", 0, QApplication::UnicodeUTF8));
        toolButton_seldefine2->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_seldefine2chain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_111->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2113", 0, QApplication::UnicodeUTF8));
        toolButton_seldefine3->setText(QApplication::translate("mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_seldefine3chain->setText(QApplication::translate("mainWindow", "\345\205\263", 0, QApplication::UnicodeUTF8));
        label_101->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        toolButton_seldefine1->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        toolButton_seldefine1chain->setText(QApplication::translate("mainWindow", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        toolButton_Debug->setText(QApplication::translate("mainWindow", "\350\260\203 \350\257\225", 0, QApplication::UnicodeUTF8));
        OutLogBtn->setText(QApplication::translate("mainWindow", "\350\276\223\345\207\272\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("mainWindow", "\344\277\235\346\212\244\346\250\241\346\213\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_51->setText(QApplication::translate("mainWindow", "A\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        lEdit_AVolt_Simu->setText(QApplication::translate("mainWindow", "350.0", 0, QApplication::UnicodeUTF8));
        label_54->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_52->setText(QApplication::translate("mainWindow", "B\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        lEdit_BVolt_Simu->setText(QApplication::translate("mainWindow", "350.0", 0, QApplication::UnicodeUTF8));
        label_55->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("mainWindow", "C\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        lEdit_CVolt_Simu->setText(QApplication::translate("mainWindow", "350.0", 0, QApplication::UnicodeUTF8));
        label_60->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_64->setText(QApplication::translate("mainWindow", "\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        lEdit_BusVolt_Simu->setText(QApplication::translate("mainWindow", "550.0", 0, QApplication::UnicodeUTF8));
        label_63->setText(QApplication::translate("mainWindow", "V", 0, QApplication::UnicodeUTF8));
        label_61->setText(QApplication::translate("mainWindow", "\345\212\261\347\243\201\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        lEdit_ExcitCurrent_Simu->setText(QApplication::translate("mainWindow", "0.6", 0, QApplication::UnicodeUTF8));
        label_62->setText(QApplication::translate("mainWindow", "A", 0, QApplication::UnicodeUTF8));
        label_65->setText(QApplication::translate("mainWindow", "\346\230\257\345\220\246\346\250\241\346\213\237", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("mainWindow", "\345\220\246", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mainWindow", "\346\230\257", 0, QApplication::UnicodeUTF8)
        );
        a01->setText(QApplication::translate("mainWindow", "a01", 0, QApplication::UnicodeUTF8));
        a02->setText(QApplication::translate("mainWindow", "a02", 0, QApplication::UnicodeUTF8));
        a03->setText(QApplication::translate("mainWindow", "a03", 0, QApplication::UnicodeUTF8));
        a04->setText(QApplication::translate("mainWindow", "a04", 0, QApplication::UnicodeUTF8));
        a05->setText(QApplication::translate("mainWindow", "a05", 0, QApplication::UnicodeUTF8));
        a06->setText(QApplication::translate("mainWindow", "a06", 0, QApplication::UnicodeUTF8));
        a07->setText(QApplication::translate("mainWindow", "a07", 0, QApplication::UnicodeUTF8));
        a08->setText(QApplication::translate("mainWindow", "a08", 0, QApplication::UnicodeUTF8));
        b01->setText(QApplication::translate("mainWindow", "b01", 0, QApplication::UnicodeUTF8));
        b02->setText(QApplication::translate("mainWindow", "b02", 0, QApplication::UnicodeUTF8));
        b03->setText(QApplication::translate("mainWindow", "b03", 0, QApplication::UnicodeUTF8));
        b04->setText(QApplication::translate("mainWindow", "b04", 0, QApplication::UnicodeUTF8));
        b05->setText(QApplication::translate("mainWindow", "b05", 0, QApplication::UnicodeUTF8));
        b06->setText(QApplication::translate("mainWindow", "b06", 0, QApplication::UnicodeUTF8));
        b07->setText(QApplication::translate("mainWindow", "b07", 0, QApplication::UnicodeUTF8));
        b08->setText(QApplication::translate("mainWindow", "b08", 0, QApplication::UnicodeUTF8));
        label_66->setText(QApplication::translate("mainWindow", "\345\205\263\351\224\256\345\217\230\351\207\217:", 0, QApplication::UnicodeUTF8));
        label_key->setText(QApplication::translate("mainWindow", "test info", 0, QApplication::UnicodeUTF8));
        pushButton_Send->setText(QApplication::translate("mainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        updatesetBtn->setText(QApplication::translate("mainWindow", "\346\233\264\346\226\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        clearlogBtn->setText(QApplication::translate("mainWindow", "\346\270\205\351\231\244\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
