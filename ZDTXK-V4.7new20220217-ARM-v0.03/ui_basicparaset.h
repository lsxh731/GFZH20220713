/********************************************************************************
** Form generated from reading UI file 'basicparaset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICPARASET_H
#define UI_BASICPARASET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "mylineedit.h"

QT_BEGIN_NAMESPACE

class Ui_basicparasetDialog
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkBox_Sub1;
    QSpacerItem *verticalSpacer_6;
    QCheckBox *checkBox_Sub2;
    QSpacerItem *verticalSpacer_7;
    QCheckBox *checkBox_Sub3;
    QSpacerItem *verticalSpacer_8;
    QCheckBox *checkBox_Sub4;
    QSpacerItem *verticalSpacer_9;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    mylineedit *lineEdit_SubCurrentUp;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    mylineedit *lineEdit_SubCurrentUp_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    mylineedit *lineEdit_SubCurrentUp_3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    mylineedit *lineEdit_SubCurrentUp_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    mylineedit *lineEdit_GfTotalVoltUp;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    mylineedit *lineEdit_GfTotalCurrentUp;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QPushButton *okBtn;
    QSpacerItem *verticalSpacer_5;
    QPushButton *cancelBtn;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;

    void setupUi(QWidget *basicparasetDialog)
    {
        if (basicparasetDialog->objectName().isEmpty())
            basicparasetDialog->setObjectName(QString::fromUtf8("basicparasetDialog"));
        basicparasetDialog->resize(549, 593);
        groupBox = new QGroupBox(basicparasetDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(370, 30, 161, 411));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        groupBox->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        checkBox_Sub1 = new QCheckBox(groupBox);
        checkBox_Sub1->setObjectName(QString::fromUtf8("checkBox_Sub1"));
        checkBox_Sub1->setFont(font);

        verticalLayout_4->addWidget(checkBox_Sub1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        checkBox_Sub2 = new QCheckBox(groupBox);
        checkBox_Sub2->setObjectName(QString::fromUtf8("checkBox_Sub2"));
        checkBox_Sub2->setFont(font);

        verticalLayout_4->addWidget(checkBox_Sub2);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_7);

        checkBox_Sub3 = new QCheckBox(groupBox);
        checkBox_Sub3->setObjectName(QString::fromUtf8("checkBox_Sub3"));
        checkBox_Sub3->setFont(font);

        verticalLayout_4->addWidget(checkBox_Sub3);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_8);

        checkBox_Sub4 = new QCheckBox(groupBox);
        checkBox_Sub4->setObjectName(QString::fromUtf8("checkBox_Sub4"));
        checkBox_Sub4->setFont(font);

        verticalLayout_4->addWidget(checkBox_Sub4);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_9);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(basicparasetDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(13, 13, 352, 571));
        groupBox_2->setFont(font);
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 331, 531));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        horizontalLayout_9->addWidget(label_9);

        lineEdit_SubCurrentUp = new mylineedit(layoutWidget);
        lineEdit_SubCurrentUp->setObjectName(QString::fromUtf8("lineEdit_SubCurrentUp"));

        horizontalLayout_9->addWidget(lineEdit_SubCurrentUp);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);

        horizontalLayout_10->addWidget(label_10);

        lineEdit_SubCurrentUp_2 = new mylineedit(layoutWidget);
        lineEdit_SubCurrentUp_2->setObjectName(QString::fromUtf8("lineEdit_SubCurrentUp_2"));

        horizontalLayout_10->addWidget(lineEdit_SubCurrentUp_2);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        horizontalLayout_11->addWidget(label_11);

        lineEdit_SubCurrentUp_3 = new mylineedit(layoutWidget);
        lineEdit_SubCurrentUp_3->setObjectName(QString::fromUtf8("lineEdit_SubCurrentUp_3"));

        horizontalLayout_11->addWidget(lineEdit_SubCurrentUp_3);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        horizontalLayout_12->addWidget(label_12);

        lineEdit_SubCurrentUp_4 = new mylineedit(layoutWidget);
        lineEdit_SubCurrentUp_4->setObjectName(QString::fromUtf8("lineEdit_SubCurrentUp_4"));

        horizontalLayout_12->addWidget(lineEdit_SubCurrentUp_4);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        horizontalLayout_5->addWidget(label_5);

        lineEdit_GfTotalVoltUp = new mylineedit(layoutWidget);
        lineEdit_GfTotalVoltUp->setObjectName(QString::fromUtf8("lineEdit_GfTotalVoltUp"));

        horizontalLayout_5->addWidget(lineEdit_GfTotalVoltUp);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        horizontalLayout_6->addWidget(label_6);

        lineEdit_GfTotalCurrentUp = new mylineedit(layoutWidget);
        lineEdit_GfTotalCurrentUp->setObjectName(QString::fromUtf8("lineEdit_GfTotalCurrentUp"));

        horizontalLayout_6->addWidget(lineEdit_GfTotalCurrentUp);


        verticalLayout_2->addLayout(horizontalLayout_6);

        layoutWidget1 = new QWidget(basicparasetDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(380, 460, 141, 101));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        okBtn = new QPushButton(layoutWidget1);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setFont(font);

        verticalLayout_3->addWidget(okBtn);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        cancelBtn = new QPushButton(layoutWidget1);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setFont(font);

        verticalLayout_3->addWidget(cancelBtn);

        layoutWidget2 = new QWidget(basicparasetDialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(basicparasetDialog);

        QMetaObject::connectSlotsByName(basicparasetDialog);
    } // setupUi

    void retranslateUi(QWidget *basicparasetDialog)
    {
        basicparasetDialog->setWindowTitle(QApplication::translate("basicparasetDialog", "\345\237\272\346\234\254\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\234\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        checkBox_Sub1->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));
        checkBox_Sub2->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));
        checkBox_Sub3->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));
        checkBox_Sub4->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("basicparasetDialog", "\351\230\210\345\200\274\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2341\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        lineEdit_SubCurrentUp->setText(QApplication::translate("basicparasetDialog", "850.0", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2342\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        lineEdit_SubCurrentUp_2->setText(QApplication::translate("basicparasetDialog", "850.0", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2343\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        lineEdit_SubCurrentUp_3->setText(QApplication::translate("basicparasetDialog", "850.0", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("basicparasetDialog", "\345\210\206\346\237\2344\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        lineEdit_SubCurrentUp_4->setText(QApplication::translate("basicparasetDialog", "850.0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("basicparasetDialog", "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\345\216\213\344\270\212\351\231\220(V)", 0, QApplication::UnicodeUTF8));
        lineEdit_GfTotalVoltUp->setText(QApplication::translate("basicparasetDialog", "350.0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("basicparasetDialog", "\345\212\237\346\224\276\346\200\273\350\276\223\345\207\272\347\224\265\346\265\201\344\270\212\351\231\220(A)", 0, QApplication::UnicodeUTF8));
        lineEdit_GfTotalCurrentUp->setText(QApplication::translate("basicparasetDialog", "3400.0", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("basicparasetDialog", "\344\277\235 \345\255\230", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("basicparasetDialog", "\350\277\224 \345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class basicparasetDialog: public Ui_basicparasetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICPARASET_H
