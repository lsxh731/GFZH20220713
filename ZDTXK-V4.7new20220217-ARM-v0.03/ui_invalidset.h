/********************************************************************************
** Form generated from reading UI file 'invalidset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVALIDSET_H
#define UI_INVALIDSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include <mylineedit.h>

QT_BEGIN_NAMESPACE

class Ui_invalidSetDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *okBtn;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_6;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label;
    mylineedit *lineEdit;
    QSpacerItem *horizontalSpacer_8;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_10;
    QLabel *activeTimeEdit;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    mylineedit *calendarDay;
    QSpacerItem *horizontalSpacer_12;

    void setupUi(QDialog *invalidSetDialog)
    {
        if (invalidSetDialog->objectName().isEmpty())
            invalidSetDialog->setObjectName(QString::fromUtf8("invalidSetDialog"));
        invalidSetDialog->resize(673, 306);
        QIcon icon;
        icon.addFile(QString::fromUtf8("invalidset.png"), QSize(), QIcon::Normal, QIcon::Off);
        invalidSetDialog->setWindowIcon(icon);
        layoutWidget = new QWidget(invalidSetDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 230, 296, 41));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        okBtn = new QPushButton(layoutWidget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        okBtn->setFont(font);

        horizontalLayout_3->addWidget(okBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        cancelBtn = new QPushButton(layoutWidget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setFont(font);

        horizontalLayout_3->addWidget(cancelBtn);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        layoutWidget1 = new QWidget(invalidSetDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 140, 421, 48));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(13, 46, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        lineEdit = new mylineedit(layoutWidget1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font);

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSpacer_8 = new QSpacerItem(13, 46, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        layoutWidget2 = new QWidget(invalidSetDialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 50, 611, 48));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_11 = new QSpacerItem(13, 43, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_11);

        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_10 = new QSpacerItem(13, 43, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        activeTimeEdit = new QLabel(layoutWidget2);
        activeTimeEdit->setObjectName(QString::fromUtf8("activeTimeEdit"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        activeTimeEdit->setFont(font1);
        activeTimeEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(activeTimeEdit);

        horizontalSpacer_2 = new QSpacerItem(18, 46, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);

        calendarDay = new mylineedit(layoutWidget2);
        calendarDay->setObjectName(QString::fromUtf8("calendarDay"));
        calendarDay->setEnabled(true);
        calendarDay->setFont(font);

        horizontalLayout->addWidget(calendarDay);

        horizontalSpacer_12 = new QSpacerItem(13, 43, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_12);


        retranslateUi(invalidSetDialog);

        QMetaObject::connectSlotsByName(invalidSetDialog);
    } // setupUi

    void retranslateUi(QDialog *invalidSetDialog)
    {
        invalidSetDialog->setWindowTitle(QApplication::translate("invalidSetDialog", "\345\244\261\346\225\210\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("invalidSetDialog", "\347\241\256  \345\256\232", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("invalidSetDialog", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("invalidSetDialog", "\347\264\257\350\256\241\350\277\220\350\241\214\346\227\266\351\227\264\344\270\212\351\231\220(\345\260\217\346\227\266)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("invalidSetDialog", "\346\277\200\346\264\273\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));
        activeTimeEdit->setText(QApplication::translate("invalidSetDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("invalidSetDialog", "\350\207\252\347\204\266\345\244\251\346\225\260\344\270\212\351\231\220(\345\244\251)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class invalidSetDialog: public Ui_invalidSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVALIDSET_H
