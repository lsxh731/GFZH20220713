/********************************************************************************
** Form generated from reading UI file 'thresholdset.ui'
**
** Created: Tue Jul 26 18:35:31 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THRESHOLDSET_H
#define UI_THRESHOLDSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include "mylineedit.h"

QT_BEGIN_NAMESPACE

class Ui_thresholdsetDialog
{
public:
    QLabel *label_15;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_2;
    mylineedit *scbhLowerEdit;
    QLabel *label;
    mylineedit *scbhUpEdit;
    QPushButton *scbhSetBtn;
    QLabel *label_12;
    QLabel *label_4;
    mylineedit *gybhLowerEdit;
    QLabel *label_5;
    mylineedit *gybhUpEdit;
    QPushButton *gybhSetBtn;
    QLabel *label_13;
    QLabel *label_6;
    mylineedit *scdlProcEdit;
    mylineedit *scdlWarningEdit;
    QPushButton *scdlSetBtn;
    QLabel *label_14;
    QLabel *label_8;
    mylineedit *IGBTgw1Edit;
    mylineedit *IGBTgw2Edit;
    QPushButton *IGBTgwSetBtn;
    mylineedit *dggw1Edit;
    QLabel *label_11;
    mylineedit *dggw2Edit;
    QPushButton *dggwSetBtn;

    void setupUi(QDialog *thresholdsetDialog)
    {
        if (thresholdsetDialog->objectName().isEmpty())
            thresholdsetDialog->setObjectName(QString::fromUtf8("thresholdsetDialog"));
        thresholdsetDialog->resize(610, 485);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(16);
        thresholdsetDialog->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("procvalue.png"), QSize(), QIcon::Normal, QIcon::Off);
        thresholdsetDialog->setWindowIcon(icon);
        label_15 = new QLabel(thresholdsetDialog);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 337, 231, 28));
        label_15->setFont(font);
        label_9 = new QLabel(thresholdsetDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(282, 294, 54, 28));
        label_9->setFont(font);
        label_7 = new QLabel(thresholdsetDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(282, 212, 63, 28));
        label_3 = new QLabel(thresholdsetDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 147, 28));
        label_3->setFont(font);
        label_2 = new QLabel(thresholdsetDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(29, 48, 54, 28));
        label_2->setFont(font);
        scbhLowerEdit = new mylineedit(thresholdsetDialog);
        scbhLowerEdit->setObjectName(QString::fromUtf8("scbhLowerEdit"));
        scbhLowerEdit->setGeometry(QRect(94, 49, 162, 34));
        label = new QLabel(thresholdsetDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(282, 48, 54, 28));
        label->setFont(font);
        scbhUpEdit = new mylineedit(thresholdsetDialog);
        scbhUpEdit->setObjectName(QString::fromUtf8("scbhUpEdit"));
        scbhUpEdit->setGeometry(QRect(348, 49, 162, 34));
        scbhSetBtn = new QPushButton(thresholdsetDialog);
        scbhSetBtn->setObjectName(QString::fromUtf8("scbhSetBtn"));
        scbhSetBtn->setGeometry(QRect(516, 48, 75, 36));
        scbhSetBtn->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("conf.png"), QSize(), QIcon::Normal, QIcon::Off);
        scbhSetBtn->setIcon(icon1);
        label_12 = new QLabel(thresholdsetDialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 92, 315, 28));
        label_12->setFont(font);
        label_4 = new QLabel(thresholdsetDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(29, 130, 54, 28));
        label_4->setFont(font);
        gybhLowerEdit = new mylineedit(thresholdsetDialog);
        gybhLowerEdit->setObjectName(QString::fromUtf8("gybhLowerEdit"));
        gybhLowerEdit->setGeometry(QRect(94, 131, 162, 34));
        label_5 = new QLabel(thresholdsetDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(282, 130, 54, 28));
        label_5->setFont(font);
        gybhUpEdit = new mylineedit(thresholdsetDialog);
        gybhUpEdit->setObjectName(QString::fromUtf8("gybhUpEdit"));
        gybhUpEdit->setGeometry(QRect(348, 131, 162, 34));
        gybhSetBtn = new QPushButton(thresholdsetDialog);
        gybhSetBtn->setObjectName(QString::fromUtf8("gybhSetBtn"));
        gybhSetBtn->setGeometry(QRect(516, 130, 75, 36));
        gybhSetBtn->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("conf.png"), QSize(), QIcon::Disabled, QIcon::Off);
        gybhSetBtn->setIcon(icon2);
        label_13 = new QLabel(thresholdsetDialog);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 174, 231, 28));
        label_13->setFont(font);
        label_6 = new QLabel(thresholdsetDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(29, 212, 63, 28));
        label_6->setFont(font);
        scdlProcEdit = new mylineedit(thresholdsetDialog);
        scdlProcEdit->setObjectName(QString::fromUtf8("scdlProcEdit"));
        scdlProcEdit->setGeometry(QRect(94, 213, 162, 34));
        scdlWarningEdit = new mylineedit(thresholdsetDialog);
        scdlWarningEdit->setObjectName(QString::fromUtf8("scdlWarningEdit"));
        scdlWarningEdit->setGeometry(QRect(348, 213, 162, 34));
        scdlSetBtn = new QPushButton(thresholdsetDialog);
        scdlSetBtn->setObjectName(QString::fromUtf8("scdlSetBtn"));
        scdlSetBtn->setGeometry(QRect(516, 212, 75, 36));
        scdlSetBtn->setFont(font);
        scdlSetBtn->setIcon(icon2);
        label_14 = new QLabel(thresholdsetDialog);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 256, 235, 28));
        label_14->setFont(font);
        label_8 = new QLabel(thresholdsetDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(29, 294, 54, 28));
        label_8->setFont(font);
        IGBTgw1Edit = new mylineedit(thresholdsetDialog);
        IGBTgw1Edit->setObjectName(QString::fromUtf8("IGBTgw1Edit"));
        IGBTgw1Edit->setGeometry(QRect(94, 295, 162, 34));
        IGBTgw2Edit = new mylineedit(thresholdsetDialog);
        IGBTgw2Edit->setObjectName(QString::fromUtf8("IGBTgw2Edit"));
        IGBTgw2Edit->setGeometry(QRect(348, 295, 162, 34));
        IGBTgwSetBtn = new QPushButton(thresholdsetDialog);
        IGBTgwSetBtn->setObjectName(QString::fromUtf8("IGBTgwSetBtn"));
        IGBTgwSetBtn->setGeometry(QRect(516, 294, 75, 36));
        IGBTgwSetBtn->setFont(font);
        IGBTgwSetBtn->setIcon(icon2);
        dggw1Edit = new mylineedit(thresholdsetDialog);
        dggw1Edit->setObjectName(QString::fromUtf8("dggw1Edit"));
        dggw1Edit->setGeometry(QRect(94, 377, 162, 34));
        label_11 = new QLabel(thresholdsetDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(270, 340, 231, 28));
        label_11->setFont(font);
        dggw2Edit = new mylineedit(thresholdsetDialog);
        dggw2Edit->setObjectName(QString::fromUtf8("dggw2Edit"));
        dggw2Edit->setGeometry(QRect(348, 377, 162, 34));
        dggwSetBtn = new QPushButton(thresholdsetDialog);
        dggwSetBtn->setObjectName(QString::fromUtf8("dggwSetBtn"));
        dggwSetBtn->setGeometry(QRect(516, 376, 75, 36));
        dggwSetBtn->setFont(font);
        dggwSetBtn->setIcon(icon2);

        retranslateUi(thresholdsetDialog);

        QMetaObject::connectSlotsByName(thresholdsetDialog);
    } // setupUi

    void retranslateUi(QDialog *thresholdsetDialog)
    {
        thresholdsetDialog->setWindowTitle(QApplication::translate("thresholdsetDialog", "\344\277\235\346\212\244\351\230\210\345\200\274\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("thresholdsetDialog", "\345\212\237\347\216\207\346\250\241\345\235\227\347\224\265\346\204\237\350\277\207\346\270\251\345\212\250\344\275\234\345\200\274", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("thresholdsetDialog", "\346\270\251\345\272\2462", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("thresholdsetDialog", "\346\212\245\350\255\246\345\200\274", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("thresholdsetDialog", "\350\276\223\345\207\272\347\224\265\345\216\213\344\277\235\346\212\244\345\200\274", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("thresholdsetDialog", " \344\270\213 \351\231\220", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("thresholdsetDialog", " \344\270\212 \351\231\220", 0, QApplication::UnicodeUTF8));
        scbhSetBtn->setText(QApplication::translate("thresholdsetDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("thresholdsetDialog", "\345\212\237\347\216\207\346\250\241\345\235\227\350\276\223\345\205\245\347\233\264\346\265\201\347\224\265\345\216\213\350\277\207\345\216\213\344\277\235\346\212\244\345\200\274", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("thresholdsetDialog", " \344\270\213 \351\231\220", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("thresholdsetDialog", " \344\270\212 \351\231\220", 0, QApplication::UnicodeUTF8));
        gybhSetBtn->setText(QApplication::translate("thresholdsetDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("thresholdsetDialog", "\345\212\237\347\216\207\346\250\241\345\235\227\350\276\223\345\207\272\347\224\265\346\265\201\345\200\274\344\270\212\351\231\220", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("thresholdsetDialog", "\344\277\235\346\212\244\345\200\274", 0, QApplication::UnicodeUTF8));
        scdlSetBtn->setText(QApplication::translate("thresholdsetDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("thresholdsetDialog", "\345\212\237\347\216\207\346\250\241\345\235\227IGBT\350\277\207\346\270\251\345\212\250\344\275\234\345\200\274", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("thresholdsetDialog", "\346\270\251\345\272\2461", 0, QApplication::UnicodeUTF8));
        IGBTgwSetBtn->setText(QApplication::translate("thresholdsetDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("thresholdsetDialog", " \346\200\273\347\224\265\346\265\201\345\271\263\345\235\207\345\200\274", 0, QApplication::UnicodeUTF8));
        dggwSetBtn->setText(QApplication::translate("thresholdsetDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class thresholdsetDialog: public Ui_thresholdsetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THRESHOLDSET_H
