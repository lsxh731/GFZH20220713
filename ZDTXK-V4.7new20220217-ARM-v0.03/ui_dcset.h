/********************************************************************************
** Form generated from reading UI file 'dcset.ui'
**
** Created: Tue Jul 26 18:35:31 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DCSET_H
#define UI_DCSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "mylineedit.h"

QT_BEGIN_NAMESPACE

class Ui_dcsetDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_19;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_18;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    mylineedit *lineEdit_01;
    QPushButton *adjBtn01;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_2;
    mylineedit *lineEdit_02;
    QPushButton *adjBtn02;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    mylineedit *lineEdit_03;
    QPushButton *adjBtn03;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    mylineedit *lineEdit_04;
    QPushButton *adjBtn04;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    mylineedit *lineEdit_05;
    QPushButton *adjBtn05;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    mylineedit *lineEdit_06;
    QPushButton *adjBtn06;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    mylineedit *lineEdit_07;
    QPushButton *adjBtn07;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    mylineedit *lineEdit_08;
    QPushButton *adjBtn08;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    mylineedit *lineEdit_09;
    QPushButton *adjBtn09;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    mylineedit *lineEdit_10;
    QPushButton *adjBtn10;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    mylineedit *lineEdit_11;
    QPushButton *adjBtn11;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    mylineedit *lineEdit_12;
    QPushButton *adjBtn12;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    mylineedit *lineEdit_13;
    QPushButton *adjBtn13;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_14;
    mylineedit *lineEdit_14;
    QPushButton *adjBtn14;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_15;
    mylineedit *lineEdit_15;
    QPushButton *adjBtn15;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_16;
    mylineedit *lineEdit_16;
    QPushButton *adjBtn16;
    QSpacerItem *horizontalSpacer_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_17;
    QComboBox *comboBox;
    mylineedit *lineEdit;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer;
    QPushButton *setBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *adjBtn;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *checkBox;

    void setupUi(QDialog *dcsetDialog)
    {
        if (dcsetDialog->objectName().isEmpty())
            dcsetDialog->setObjectName(QString::fromUtf8("dcsetDialog"));
        dcsetDialog->resize(737, 383);
        QIcon icon;
        icon.addFile(QString::fromUtf8("dcset.png"), QSize(), QIcon::Normal, QIcon::Off);
        dcsetDialog->setWindowIcon(icon);
        layoutWidget = new QWidget(dcsetDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 50, 726, 328));
        horizontalLayout_19 = new QHBoxLayout(layoutWidget);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_4);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        label->setFont(font);

        horizontalLayout_8->addWidget(label);

        lineEdit_01 = new mylineedit(layoutWidget);
        lineEdit_01->setObjectName(QString::fromUtf8("lineEdit_01"));
        lineEdit_01->setFont(font);

        horizontalLayout_8->addWidget(lineEdit_01);

        adjBtn01 = new QPushButton(layoutWidget);
        adjBtn01->setObjectName(QString::fromUtf8("adjBtn01"));
        adjBtn01->setFont(font);

        horizontalLayout_8->addWidget(adjBtn01);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_7->addWidget(label_2);

        lineEdit_02 = new mylineedit(layoutWidget);
        lineEdit_02->setObjectName(QString::fromUtf8("lineEdit_02"));
        lineEdit_02->setFont(font);

        horizontalLayout_7->addWidget(lineEdit_02);

        adjBtn02 = new QPushButton(layoutWidget);
        adjBtn02->setObjectName(QString::fromUtf8("adjBtn02"));
        adjBtn02->setFont(font);

        horizontalLayout_7->addWidget(adjBtn02);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_6->addWidget(label_3);

        lineEdit_03 = new mylineedit(layoutWidget);
        lineEdit_03->setObjectName(QString::fromUtf8("lineEdit_03"));
        lineEdit_03->setFont(font);

        horizontalLayout_6->addWidget(lineEdit_03);

        adjBtn03 = new QPushButton(layoutWidget);
        adjBtn03->setObjectName(QString::fromUtf8("adjBtn03"));
        adjBtn03->setFont(font);

        horizontalLayout_6->addWidget(adjBtn03);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_5->addWidget(label_4);

        lineEdit_04 = new mylineedit(layoutWidget);
        lineEdit_04->setObjectName(QString::fromUtf8("lineEdit_04"));
        lineEdit_04->setFont(font);

        horizontalLayout_5->addWidget(lineEdit_04);

        adjBtn04 = new QPushButton(layoutWidget);
        adjBtn04->setObjectName(QString::fromUtf8("adjBtn04"));
        adjBtn04->setFont(font);

        horizontalLayout_5->addWidget(adjBtn04);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        horizontalLayout_4->addWidget(label_5);

        lineEdit_05 = new mylineedit(layoutWidget);
        lineEdit_05->setObjectName(QString::fromUtf8("lineEdit_05"));
        lineEdit_05->setFont(font);

        horizontalLayout_4->addWidget(lineEdit_05);

        adjBtn05 = new QPushButton(layoutWidget);
        adjBtn05->setObjectName(QString::fromUtf8("adjBtn05"));
        adjBtn05->setFont(font);

        horizontalLayout_4->addWidget(adjBtn05);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        horizontalLayout_3->addWidget(label_6);

        lineEdit_06 = new mylineedit(layoutWidget);
        lineEdit_06->setObjectName(QString::fromUtf8("lineEdit_06"));
        lineEdit_06->setFont(font);

        horizontalLayout_3->addWidget(lineEdit_06);

        adjBtn06 = new QPushButton(layoutWidget);
        adjBtn06->setObjectName(QString::fromUtf8("adjBtn06"));
        adjBtn06->setFont(font);

        horizontalLayout_3->addWidget(adjBtn06);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        horizontalLayout_2->addWidget(label_7);

        lineEdit_07 = new mylineedit(layoutWidget);
        lineEdit_07->setObjectName(QString::fromUtf8("lineEdit_07"));
        lineEdit_07->setFont(font);

        horizontalLayout_2->addWidget(lineEdit_07);

        adjBtn07 = new QPushButton(layoutWidget);
        adjBtn07->setObjectName(QString::fromUtf8("adjBtn07"));
        adjBtn07->setFont(font);

        horizontalLayout_2->addWidget(adjBtn07);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        horizontalLayout->addWidget(label_8);

        lineEdit_08 = new mylineedit(layoutWidget);
        lineEdit_08->setObjectName(QString::fromUtf8("lineEdit_08"));
        lineEdit_08->setFont(font);

        horizontalLayout->addWidget(lineEdit_08);

        adjBtn08 = new QPushButton(layoutWidget);
        adjBtn08->setObjectName(QString::fromUtf8("adjBtn08"));
        adjBtn08->setFont(font);

        horizontalLayout->addWidget(adjBtn08);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_18->addLayout(verticalLayout);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        horizontalLayout_9->addWidget(label_9);

        lineEdit_09 = new mylineedit(layoutWidget);
        lineEdit_09->setObjectName(QString::fromUtf8("lineEdit_09"));
        lineEdit_09->setFont(font);

        horizontalLayout_9->addWidget(lineEdit_09);

        adjBtn09 = new QPushButton(layoutWidget);
        adjBtn09->setObjectName(QString::fromUtf8("adjBtn09"));
        adjBtn09->setFont(font);

        horizontalLayout_9->addWidget(adjBtn09);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);

        horizontalLayout_10->addWidget(label_10);

        lineEdit_10 = new mylineedit(layoutWidget);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        lineEdit_10->setFont(font);

        horizontalLayout_10->addWidget(lineEdit_10);

        adjBtn10 = new QPushButton(layoutWidget);
        adjBtn10->setObjectName(QString::fromUtf8("adjBtn10"));
        adjBtn10->setFont(font);

        horizontalLayout_10->addWidget(adjBtn10);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        horizontalLayout_11->addWidget(label_11);

        lineEdit_11 = new mylineedit(layoutWidget);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        lineEdit_11->setFont(font);

        horizontalLayout_11->addWidget(lineEdit_11);

        adjBtn11 = new QPushButton(layoutWidget);
        adjBtn11->setObjectName(QString::fromUtf8("adjBtn11"));
        adjBtn11->setFont(font);

        horizontalLayout_11->addWidget(adjBtn11);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        horizontalLayout_12->addWidget(label_12);

        lineEdit_12 = new mylineedit(layoutWidget);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setFont(font);

        horizontalLayout_12->addWidget(lineEdit_12);

        adjBtn12 = new QPushButton(layoutWidget);
        adjBtn12->setObjectName(QString::fromUtf8("adjBtn12"));
        adjBtn12->setFont(font);

        horizontalLayout_12->addWidget(adjBtn12);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);

        horizontalLayout_13->addWidget(label_13);

        lineEdit_13 = new mylineedit(layoutWidget);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        lineEdit_13->setFont(font);

        horizontalLayout_13->addWidget(lineEdit_13);

        adjBtn13 = new QPushButton(layoutWidget);
        adjBtn13->setObjectName(QString::fromUtf8("adjBtn13"));
        adjBtn13->setFont(font);

        horizontalLayout_13->addWidget(adjBtn13);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font);

        horizontalLayout_14->addWidget(label_14);

        lineEdit_14 = new mylineedit(layoutWidget);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        lineEdit_14->setFont(font);

        horizontalLayout_14->addWidget(lineEdit_14);

        adjBtn14 = new QPushButton(layoutWidget);
        adjBtn14->setObjectName(QString::fromUtf8("adjBtn14"));
        adjBtn14->setFont(font);

        horizontalLayout_14->addWidget(adjBtn14);


        verticalLayout_2->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font);

        horizontalLayout_15->addWidget(label_15);

        lineEdit_15 = new mylineedit(layoutWidget);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        lineEdit_15->setFont(font);

        horizontalLayout_15->addWidget(lineEdit_15);

        adjBtn15 = new QPushButton(layoutWidget);
        adjBtn15->setObjectName(QString::fromUtf8("adjBtn15"));
        adjBtn15->setFont(font);

        horizontalLayout_15->addWidget(adjBtn15);


        verticalLayout_2->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font);

        horizontalLayout_16->addWidget(label_16);

        lineEdit_16 = new mylineedit(layoutWidget);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        lineEdit_16->setFont(font);

        horizontalLayout_16->addWidget(lineEdit_16);

        adjBtn16 = new QPushButton(layoutWidget);
        adjBtn16->setObjectName(QString::fromUtf8("adjBtn16"));
        adjBtn16->setFont(font);

        horizontalLayout_16->addWidget(adjBtn16);


        verticalLayout_2->addLayout(horizontalLayout_16);


        horizontalLayout_18->addLayout(verticalLayout_2);


        horizontalLayout_19->addLayout(horizontalLayout_18);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_3);

        layoutWidget1 = new QWidget(dcsetDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 10, 716, 35));
        horizontalLayout_17 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
        label_17 = new QLabel(layoutWidget1);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font);

        horizontalLayout_17->addWidget(label_17);

        comboBox = new QComboBox(layoutWidget1);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setFont(font);

        horizontalLayout_17->addWidget(comboBox);

        lineEdit = new mylineedit(layoutWidget1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font);

        horizontalLayout_17->addWidget(lineEdit);

        label_18 = new QLabel(layoutWidget1);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font);

        horizontalLayout_17->addWidget(label_18);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer);

        setBtn = new QPushButton(layoutWidget1);
        setBtn->setObjectName(QString::fromUtf8("setBtn"));
        setBtn->setFont(font);

        horizontalLayout_17->addWidget(setBtn);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_2);

        adjBtn = new QPushButton(layoutWidget1);
        adjBtn->setObjectName(QString::fromUtf8("adjBtn"));
        adjBtn->setFont(font);

        horizontalLayout_17->addWidget(adjBtn);

        horizontalSpacer_6 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_6);

        checkBox = new QCheckBox(layoutWidget1);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFont(font);

        horizontalLayout_17->addWidget(checkBox);


        retranslateUi(dcsetDialog);

        QMetaObject::connectSlotsByName(dcsetDialog);
    } // setupUi

    void retranslateUi(QDialog *dcsetDialog)
    {
        dcsetDialog->setWindowTitle(QApplication::translate("dcsetDialog", "\347\233\264\346\265\201\350\260\203\350\212\202", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27601\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn01->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27602\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn02->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27603\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn03->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27604\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn04->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27605\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn05->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27606\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn06->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27607\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn07->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27608\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn08->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27609\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn09->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27610\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn10->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27611\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn11->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27612\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn12->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27613\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn13->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27614\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn14->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27615\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn15->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("dcsetDialog", "\345\212\237\346\224\27616\357\274\210V\357\274\211", 0, QApplication::UnicodeUTF8));
        adjBtn16->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("dcsetDialog", "\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("dcsetDialog", "\345\215\225\344\270\252\350\260\203\350\212\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dcsetDialog", "\347\273\237\344\270\200\350\260\203\350\212\202", 0, QApplication::UnicodeUTF8)
        );
        label_18->setText(QApplication::translate("dcsetDialog", "V", 0, QApplication::UnicodeUTF8));
        setBtn->setText(QApplication::translate("dcsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        adjBtn->setText(QApplication::translate("dcsetDialog", "\350\260\203 \350\212\202", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("dcsetDialog", "\346\225\260\345\255\227\351\224\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dcsetDialog: public Ui_dcsetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCSET_H
