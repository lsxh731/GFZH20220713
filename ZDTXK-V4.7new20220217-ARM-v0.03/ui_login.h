/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Thu Jul 7 23:40:54 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLineEdit *lineEdit_pwd;
    QPushButton *okBtn;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_1;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButton_7;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *pushButton_8;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_19;
    QPushButton *clearBtn;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *pushButton_0;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_18;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName(QString::fromUtf8("loginDialog"));
        loginDialog->resize(535, 423);
        QIcon icon;
        icon.addFile(QString::fromUtf8("login.png"), QSize(), QIcon::Normal, QIcon::Off);
        loginDialog->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(loginDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        label_2 = new QLabel(loginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(16);
        label_2->setFont(font);

        horizontalLayout_6->addWidget(label_2);

        lineEdit_pwd = new QLineEdit(loginDialog);
        lineEdit_pwd->setObjectName(QString::fromUtf8("lineEdit_pwd"));

        horizontalLayout_6->addWidget(lineEdit_pwd);

        okBtn = new QPushButton(loginDialog);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setFont(font);

        horizontalLayout_6->addWidget(okBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        groupBox = new QGroupBox(loginDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_1 = new QPushButton(groupBox);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setFont(font);

        horizontalLayout->addWidget(pushButton_1);

        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font);

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_5 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font);

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer_6 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setFont(font);

        horizontalLayout_3->addWidget(pushButton_4);

        horizontalSpacer_8 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setFont(font);

        horizontalLayout_3->addWidget(pushButton_5);

        horizontalSpacer_9 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setFont(font);

        horizontalLayout_3->addWidget(pushButton_6);

        horizontalSpacer_10 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_11 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);

        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setFont(font);

        horizontalLayout_4->addWidget(pushButton_7);

        horizontalSpacer_12 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_12);

        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setFont(font);

        horizontalLayout_4->addWidget(pushButton_8);

        horizontalSpacer_13 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);

        pushButton_9 = new QPushButton(groupBox);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setFont(font);

        horizontalLayout_4->addWidget(pushButton_9);

        horizontalSpacer_14 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_14);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_19);

        clearBtn = new QPushButton(groupBox);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));
        clearBtn->setFont(font);

        horizontalLayout_5->addWidget(clearBtn);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_16);

        pushButton_0 = new QPushButton(groupBox);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setFont(font);

        horizontalLayout_5->addWidget(pushButton_0);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_17);

        cancelBtn = new QPushButton(groupBox);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setFont(font);

        horizontalLayout_5->addWidget(cancelBtn);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_18);


        gridLayout->addLayout(horizontalLayout_5, 3, 0, 1, 1);


        verticalLayout->addWidget(groupBox);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QApplication::translate("loginDialog", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("loginDialog", "  \345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        lineEdit_pwd->setText(QString());
        okBtn->setText(QApplication::translate("loginDialog", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("loginDialog", "\346\225\260\345\255\227\351\224\256\347\233\230", 0, QApplication::UnicodeUTF8));
        pushButton_1->setText(QApplication::translate("loginDialog", "1", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("loginDialog", "2", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("loginDialog", "3", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("loginDialog", "4", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("loginDialog", "5", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("loginDialog", "6", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("loginDialog", "7", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("loginDialog", "8", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("loginDialog", "9", 0, QApplication::UnicodeUTF8));
        clearBtn->setText(QApplication::translate("loginDialog", "\346\270\205 \351\231\244", 0, QApplication::UnicodeUTF8));
        pushButton_0->setText(QApplication::translate("loginDialog", "0", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("loginDialog", "\350\277\224 \345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
