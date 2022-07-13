/********************************************************************************
** Form generated from reading UI file 'sysset.ui'
**
** Created: Thu Jul 7 23:40:55 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSSET_H
#define UI_SYSSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_syssetDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QDateTimeEdit *dateTimeEdit;
    QPushButton *okBtn;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *restorefactoryBtn;

    void setupUi(QDialog *syssetDialog)
    {
        if (syssetDialog->objectName().isEmpty())
            syssetDialog->setObjectName(QString::fromUtf8("syssetDialog"));
        syssetDialog->resize(591, 461);
        horizontalLayoutWidget = new QWidget(syssetDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 50, 571, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(horizontalLayoutWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(radioButton);

        dateTimeEdit = new QDateTimeEdit(horizontalLayoutWidget);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout->addWidget(dateTimeEdit);

        okBtn = new QPushButton(horizontalLayoutWidget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        horizontalLayout->addWidget(okBtn);

        horizontalLayoutWidget_2 = new QWidget(syssetDialog);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 210, 211, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        restorefactoryBtn = new QPushButton(horizontalLayoutWidget_2);
        restorefactoryBtn->setObjectName(QString::fromUtf8("restorefactoryBtn"));

        horizontalLayout_2->addWidget(restorefactoryBtn);


        retranslateUi(syssetDialog);

        QMetaObject::connectSlotsByName(syssetDialog);
    } // setupUi

    void retranslateUi(QDialog *syssetDialog)
    {
        syssetDialog->setWindowTitle(QApplication::translate("syssetDialog", "\347\263\273\347\273\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("syssetDialog", "\344\277\256\346\224\271\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("syssetDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        restorefactoryBtn->setText(QApplication::translate("syssetDialog", "\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class syssetDialog: public Ui_syssetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSSET_H
