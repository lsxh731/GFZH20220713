/********************************************************************************
** Form generated from reading UI file 'gainset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAINSET_H
#define UI_GAINSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

QT_BEGIN_NAMESPACE

class Ui_gainsetDialog
{
public:
    QSlider *horizontalSlider;
    QProgressBar *progressBar;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *gainsetDialog)
    {
        if (gainsetDialog->objectName().isEmpty())
            gainsetDialog->setObjectName(QString::fromUtf8("gainsetDialog"));
        gainsetDialog->resize(407, 206);
        horizontalSlider = new QSlider(gainsetDialog);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(30, 30, 341, 60));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        horizontalSlider->setFont(font);
        horizontalSlider->setOrientation(Qt::Horizontal);
        progressBar = new QProgressBar(gainsetDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 110, 361, 23));
        progressBar->setValue(0);
        okBtn = new QPushButton(gainsetDialog);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(220, 170, 71, 23));
        cancelBtn = new QPushButton(gainsetDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(320, 170, 71, 23));

        retranslateUi(gainsetDialog);

        QMetaObject::connectSlotsByName(gainsetDialog);
    } // setupUi

    void retranslateUi(QDialog *gainsetDialog)
    {
        gainsetDialog->setWindowTitle(QApplication::translate("gainsetDialog", "\345\242\236\347\233\212\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("gainsetDialog", "\347\241\256  \345\256\232", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("gainsetDialog", "\345\217\226  \346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gainsetDialog: public Ui_gainsetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAINSET_H
