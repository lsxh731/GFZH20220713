/********************************************************************************
** Form generated from reading UI file 'countdown.ui'
**
** Created: Thu Jul 7 23:40:55 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTDOWN_H
#define UI_COUNTDOWN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_countdownForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_3;

    void setupUi(QWidget *countdownForm)
    {
        if (countdownForm->objectName().isEmpty())
            countdownForm->setObjectName(QString::fromUtf8("countdownForm"));
        countdownForm->resize(255, 103);
        gridLayout = new QGridLayout(countdownForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(countdownForm);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(18);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(countdownForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font);

        horizontalLayout->addWidget(lineEdit);

        label_3 = new QLabel(countdownForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(countdownForm);

        QMetaObject::connectSlotsByName(countdownForm);
    } // setupUi

    void retranslateUi(QWidget *countdownForm)
    {
        countdownForm->setWindowTitle(QApplication::translate("countdownForm", "\350\257\267\350\200\220\345\277\203\347\255\211\345\200\231", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("countdownForm", "\345\200\222\350\256\241\346\227\266", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("countdownForm", "S", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class countdownForm: public Ui_countdownForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTDOWN_H
