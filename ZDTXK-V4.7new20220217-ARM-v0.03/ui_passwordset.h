/********************************************************************************
** Form generated from reading UI file 'passwordset.ui'
**
** Created: Thu Jul 7 23:40:55 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDSET_H
#define UI_PASSWORDSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pwdSetDialog
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButton_1;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_18;
    QPushButton *pushButton_7;
    QSpacerItem *horizontalSpacer_19;
    QPushButton *pushButton_8;
    QSpacerItem *horizontalSpacer_20;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_21;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *clearBtn;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *pushButton_0;
    QSpacerItem *horizontalSpacer_23;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_24;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QRadioButton *radioBtn_currpwd;
    QLineEdit *lineEdit_currpwd;
    QRadioButton *radioBtn_newpwd;
    QLineEdit *lineEdit_newpwd;
    QRadioButton *radioBtn_checkpwd;
    QLineEdit *lineEdit_checkpwd;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *okBtn;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *pwdSetDialog)
    {
        if (pwdSetDialog->objectName().isEmpty())
            pwdSetDialog->setObjectName(QString::fromUtf8("pwdSetDialog"));
        pwdSetDialog->resize(476, 416);
        QIcon icon;
        icon.addFile(QString::fromUtf8("C:/Users/zhanqingcai/.designer/backup/login.png"), QSize(), QIcon::Normal, QIcon::Off);
        pwdSetDialog->setWindowIcon(icon);
        groupBox = new QGroupBox(pwdSetDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(12, 145, 452, 259));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);

        pushButton_1 = new QPushButton(groupBox);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(16);
        pushButton_1->setFont(font1);

        horizontalLayout_8->addWidget(pushButton_1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_11);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font1);

        horizontalLayout_8->addWidget(pushButton_2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font1);

        horizontalLayout_8->addWidget(pushButton_3);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);


        gridLayout->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_14);

        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setFont(font1);

        horizontalLayout_9->addWidget(pushButton_4);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_15);

        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setFont(font1);

        horizontalLayout_9->addWidget(pushButton_5);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_16);

        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setFont(font1);

        horizontalLayout_9->addWidget(pushButton_6);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_17);


        gridLayout->addLayout(horizontalLayout_9, 1, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_18);

        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setFont(font1);

        horizontalLayout_10->addWidget(pushButton_7);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_19);

        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setFont(font1);

        horizontalLayout_10->addWidget(pushButton_8);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_20);

        pushButton_9 = new QPushButton(groupBox);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setFont(font1);

        horizontalLayout_10->addWidget(pushButton_9);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_21);


        gridLayout->addLayout(horizontalLayout_10, 2, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_8);

        clearBtn = new QPushButton(groupBox);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));
        clearBtn->setFont(font1);

        horizontalLayout_11->addWidget(clearBtn);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_22);

        pushButton_0 = new QPushButton(groupBox);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setFont(font1);

        horizontalLayout_11->addWidget(pushButton_0);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_23);

        cancelBtn = new QPushButton(groupBox);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setFont(font1);

        horizontalLayout_11->addWidget(cancelBtn);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_24);


        gridLayout->addLayout(horizontalLayout_11, 3, 0, 1, 1);

        layoutWidget = new QWidget(pwdSetDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(21, 14, 341, 141));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        radioBtn_currpwd = new QRadioButton(layoutWidget);
        radioBtn_currpwd->setObjectName(QString::fromUtf8("radioBtn_currpwd"));
        radioBtn_currpwd->setFont(font);

        gridLayout_2->addWidget(radioBtn_currpwd, 0, 0, 1, 1);

        lineEdit_currpwd = new QLineEdit(layoutWidget);
        lineEdit_currpwd->setObjectName(QString::fromUtf8("lineEdit_currpwd"));

        gridLayout_2->addWidget(lineEdit_currpwd, 0, 1, 1, 1);

        radioBtn_newpwd = new QRadioButton(layoutWidget);
        radioBtn_newpwd->setObjectName(QString::fromUtf8("radioBtn_newpwd"));
        radioBtn_newpwd->setFont(font);

        gridLayout_2->addWidget(radioBtn_newpwd, 1, 0, 1, 1);

        lineEdit_newpwd = new QLineEdit(layoutWidget);
        lineEdit_newpwd->setObjectName(QString::fromUtf8("lineEdit_newpwd"));

        gridLayout_2->addWidget(lineEdit_newpwd, 1, 1, 1, 1);

        radioBtn_checkpwd = new QRadioButton(layoutWidget);
        radioBtn_checkpwd->setObjectName(QString::fromUtf8("radioBtn_checkpwd"));
        radioBtn_checkpwd->setFont(font);

        gridLayout_2->addWidget(radioBtn_checkpwd, 2, 0, 1, 1);

        lineEdit_checkpwd = new QLineEdit(layoutWidget);
        lineEdit_checkpwd->setObjectName(QString::fromUtf8("lineEdit_checkpwd"));

        gridLayout_2->addWidget(lineEdit_checkpwd, 2, 1, 1, 1);

        layoutWidget1 = new QWidget(pwdSetDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(370, 10, 95, 141));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        okBtn = new QPushButton(layoutWidget1);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setFont(font1);

        verticalLayout_2->addWidget(okBtn);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(pwdSetDialog);

        QMetaObject::connectSlotsByName(pwdSetDialog);
    } // setupUi

    void retranslateUi(QDialog *pwdSetDialog)
    {
        pwdSetDialog->setWindowTitle(QApplication::translate("pwdSetDialog", "\345\257\206\347\240\201\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("pwdSetDialog", "\346\225\260\345\255\227\351\224\256\347\233\230", 0, QApplication::UnicodeUTF8));
        pushButton_1->setText(QApplication::translate("pwdSetDialog", "1", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("pwdSetDialog", "2", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("pwdSetDialog", "3", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("pwdSetDialog", "4", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("pwdSetDialog", "5", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("pwdSetDialog", "6", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("pwdSetDialog", "7", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("pwdSetDialog", "8", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("pwdSetDialog", "9", 0, QApplication::UnicodeUTF8));
        clearBtn->setText(QApplication::translate("pwdSetDialog", "\346\270\205 \351\231\244", 0, QApplication::UnicodeUTF8));
        pushButton_0->setText(QApplication::translate("pwdSetDialog", "0", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("pwdSetDialog", "\350\277\224 \345\233\236", 0, QApplication::UnicodeUTF8));
        radioBtn_currpwd->setText(QApplication::translate("pwdSetDialog", "\346\227\247\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        radioBtn_newpwd->setText(QApplication::translate("pwdSetDialog", "\346\226\260\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        radioBtn_checkpwd->setText(QApplication::translate("pwdSetDialog", "\345\257\206\347\240\201\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        lineEdit_checkpwd->setText(QString());
        okBtn->setText(QApplication::translate("pwdSetDialog", "\344\277\235 \345\255\230", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class pwdSetDialog: public Ui_pwdSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDSET_H
