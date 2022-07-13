/********************************************************************************
** Form generated from reading UI file 'runningstatus.ui'
**
** Created: Thu Jul 7 23:40:54 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNNINGSTATUS_H
#define UI_RUNNINGSTATUS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_runningstatusForm
{
public:
    QTableWidget *operstatus_tableWidget;
    QPushButton *closeBtn;

    void setupUi(QWidget *runningstatusForm)
    {
        if (runningstatusForm->objectName().isEmpty())
            runningstatusForm->setObjectName(QString::fromUtf8("runningstatusForm"));
        runningstatusForm->resize(1011, 574);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        runningstatusForm->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("logo_top.png"), QSize(), QIcon::Normal, QIcon::Off);
        runningstatusForm->setWindowIcon(icon);
        operstatus_tableWidget = new QTableWidget(runningstatusForm);
        if (operstatus_tableWidget->columnCount() < 9)
            operstatus_tableWidget->setColumnCount(9);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font1);
        operstatus_tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        if (operstatus_tableWidget->rowCount() < 16)
            operstatus_tableWidget->setRowCount(16);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        operstatus_tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem24);
        operstatus_tableWidget->setObjectName(QString::fromUtf8("operstatus_tableWidget"));
        operstatus_tableWidget->setGeometry(QRect(11, 11, 991, 511));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(12);
        operstatus_tableWidget->setFont(font2);
        operstatus_tableWidget->setStyleSheet(QString::fromUtf8("QScrollBar::vertical\n"
"{\n"
"    width: 35px;\n"
"}\n"
"QScrollBar::horizontal\n"
"{\n"
"    height: 35px;\n"
"}"));
        closeBtn = new QPushButton(runningstatusForm);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setGeometry(QRect(890, 527, 93, 41));
        closeBtn->setMaximumSize(QSize(128, 128));
        closeBtn->setIconSize(QSize(128, 128));

        retranslateUi(runningstatusForm);

        QMetaObject::connectSlotsByName(runningstatusForm);
    } // setupUi

    void retranslateUi(QWidget *runningstatusForm)
    {
        runningstatusForm->setWindowTitle(QApplication::translate("runningstatusForm", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = operstatus_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("runningstatusForm", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = operstatus_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("runningstatusForm", "\351\207\215\345\220\257\350\277\207\347\250\213\344\270\255", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = operstatus_tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("runningstatusForm", "\346\255\243\345\270\270\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = operstatus_tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("runningstatusForm", "\346\225\205\351\232\234\344\277\235\346\212\244\344\270\255", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = operstatus_tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("runningstatusForm", "\346\225\205\351\232\234\351\227\255\351\224\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = operstatus_tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("runningstatusForm", "\345\267\262\344\277\235\346\212\244\346\254\241\346\225\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = operstatus_tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("runningstatusForm", "\345\260\201\351\224\201\350\204\211\345\206\262", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = operstatus_tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("runningstatusForm", "\346\224\266\345\210\260\345\220\257\345\212\250\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = operstatus_tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("runningstatusForm", "\346\224\266\345\210\260\345\205\263\346\234\272\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = operstatus_tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22701", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = operstatus_tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22702", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = operstatus_tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22703", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = operstatus_tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22704", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = operstatus_tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem13->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22705", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = operstatus_tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem14->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22706", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = operstatus_tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem15->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22707", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = operstatus_tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem16->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22708", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = operstatus_tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem17->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22709", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = operstatus_tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem18->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22710", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = operstatus_tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem19->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22711", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = operstatus_tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem20->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22712", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = operstatus_tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem21->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22713", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = operstatus_tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem22->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22714", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = operstatus_tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem23->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22715", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = operstatus_tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem24->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22716", 0, QApplication::UnicodeUTF8));
        closeBtn->setText(QApplication::translate("runningstatusForm", "\350\277\224 \345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class runningstatusForm: public Ui_runningstatusForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNNINGSTATUS_H
