/********************************************************************************
** Form generated from reading UI file 'hiscurve.ui'
**
** Created: Thu Jul 7 23:40:55 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISCURVE_H
#define UI_HISCURVE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hiscurveForm
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_starttime;
    QDateTimeEdit *dateTimeEdit_start;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_endtime;
    QDateTimeEdit *dateTimeEdit_end;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *loadBtn;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *recoverBtn;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *closeBtn;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_AVolt;
    QToolButton *toolButton_phAvolt;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *checkBox_BVolt;
    QToolButton *toolButton_phBvolt;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *checkBox_CVolt;
    QToolButton *toolButton_phCvolt;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *checkBox_All;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_totalvolt;
    QToolButton *toolButton_totalvolt;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_totalcurr;
    QToolButton *toolButton_totalcurr;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_excitvolt;
    QToolButton *toolButton_excitvolt;
    QSpacerItem *horizontalSpacer_11;
    QCheckBox *checkBox_excitcurr;
    QToolButton *toolButton_excitcurr;
    QSpacerItem *horizontalSpacer_12;
    QFrame *frame;

    void setupUi(QWidget *hiscurveForm)
    {
        if (hiscurveForm->objectName().isEmpty())
            hiscurveForm->setObjectName(QString::fromUtf8("hiscurveForm"));
        hiscurveForm->resize(975, 564);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        hiscurveForm->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("logo_home.png"), QSize(), QIcon::Normal, QIcon::Off);
        hiscurveForm->setWindowIcon(icon);
        gridLayout = new QGridLayout(hiscurveForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_starttime = new QLabel(hiscurveForm);
        label_starttime->setObjectName(QString::fromUtf8("label_starttime"));
        QFont font1;
        font1.setPointSize(14);
        label_starttime->setFont(font1);

        horizontalLayout->addWidget(label_starttime);

        dateTimeEdit_start = new QDateTimeEdit(hiscurveForm);
        dateTimeEdit_start->setObjectName(QString::fromUtf8("dateTimeEdit_start"));
        dateTimeEdit_start->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout->addWidget(dateTimeEdit_start);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_endtime = new QLabel(hiscurveForm);
        label_endtime->setObjectName(QString::fromUtf8("label_endtime"));
        label_endtime->setFont(font1);

        horizontalLayout->addWidget(label_endtime);

        dateTimeEdit_end = new QDateTimeEdit(hiscurveForm);
        dateTimeEdit_end->setObjectName(QString::fromUtf8("dateTimeEdit_end"));
        dateTimeEdit_end->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout->addWidget(dateTimeEdit_end);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        loadBtn = new QPushButton(hiscurveForm);
        loadBtn->setObjectName(QString::fromUtf8("loadBtn"));
        loadBtn->setFont(font1);

        horizontalLayout->addWidget(loadBtn);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        recoverBtn = new QPushButton(hiscurveForm);
        recoverBtn->setObjectName(QString::fromUtf8("recoverBtn"));

        horizontalLayout->addWidget(recoverBtn);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        closeBtn = new QPushButton(hiscurveForm);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setEnabled(true);
        closeBtn->setMaximumSize(QSize(150, 37));

        horizontalLayout->addWidget(closeBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox = new QGroupBox(hiscurveForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox_AVolt = new QCheckBox(groupBox);
        checkBox_AVolt->setObjectName(QString::fromUtf8("checkBox_AVolt"));

        horizontalLayout_3->addWidget(checkBox_AVolt);

        toolButton_phAvolt = new QToolButton(groupBox);
        toolButton_phAvolt->setObjectName(QString::fromUtf8("toolButton_phAvolt"));
        toolButton_phAvolt->setIconSize(QSize(16, 16));

        horizontalLayout_3->addWidget(toolButton_phAvolt);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        checkBox_BVolt = new QCheckBox(groupBox);
        checkBox_BVolt->setObjectName(QString::fromUtf8("checkBox_BVolt"));

        horizontalLayout_3->addWidget(checkBox_BVolt);

        toolButton_phBvolt = new QToolButton(groupBox);
        toolButton_phBvolt->setObjectName(QString::fromUtf8("toolButton_phBvolt"));
        toolButton_phBvolt->setIconSize(QSize(16, 16));

        horizontalLayout_3->addWidget(toolButton_phBvolt);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        checkBox_CVolt = new QCheckBox(groupBox);
        checkBox_CVolt->setObjectName(QString::fromUtf8("checkBox_CVolt"));

        horizontalLayout_3->addWidget(checkBox_CVolt);

        toolButton_phCvolt = new QToolButton(groupBox);
        toolButton_phCvolt->setObjectName(QString::fromUtf8("toolButton_phCvolt"));
        toolButton_phCvolt->setIconSize(QSize(16, 16));

        horizontalLayout_3->addWidget(toolButton_phCvolt);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        checkBox_All = new QCheckBox(groupBox);
        checkBox_All->setObjectName(QString::fromUtf8("checkBox_All"));

        horizontalLayout_3->addWidget(checkBox_All);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox_totalvolt = new QCheckBox(groupBox);
        checkBox_totalvolt->setObjectName(QString::fromUtf8("checkBox_totalvolt"));

        horizontalLayout_2->addWidget(checkBox_totalvolt);

        toolButton_totalvolt = new QToolButton(groupBox);
        toolButton_totalvolt->setObjectName(QString::fromUtf8("toolButton_totalvolt"));
        toolButton_totalvolt->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(toolButton_totalvolt);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        checkBox_totalcurr = new QCheckBox(groupBox);
        checkBox_totalcurr->setObjectName(QString::fromUtf8("checkBox_totalcurr"));

        horizontalLayout_2->addWidget(checkBox_totalcurr);

        toolButton_totalcurr = new QToolButton(groupBox);
        toolButton_totalcurr->setObjectName(QString::fromUtf8("toolButton_totalcurr"));
        toolButton_totalcurr->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(toolButton_totalcurr);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        checkBox_excitvolt = new QCheckBox(groupBox);
        checkBox_excitvolt->setObjectName(QString::fromUtf8("checkBox_excitvolt"));

        horizontalLayout_2->addWidget(checkBox_excitvolt);

        toolButton_excitvolt = new QToolButton(groupBox);
        toolButton_excitvolt->setObjectName(QString::fromUtf8("toolButton_excitvolt"));
        toolButton_excitvolt->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(toolButton_excitvolt);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);

        checkBox_excitcurr = new QCheckBox(groupBox);
        checkBox_excitcurr->setObjectName(QString::fromUtf8("checkBox_excitcurr"));

        horizontalLayout_2->addWidget(checkBox_excitcurr);

        toolButton_excitcurr = new QToolButton(groupBox);
        toolButton_excitcurr->setObjectName(QString::fromUtf8("toolButton_excitcurr"));
        toolButton_excitcurr->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(toolButton_excitcurr);

        horizontalSpacer_12 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 2);


        verticalLayout_2->addWidget(groupBox);

        frame = new QFrame(hiscurveForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(hiscurveForm);

        QMetaObject::connectSlotsByName(hiscurveForm);
    } // setupUi

    void retranslateUi(QWidget *hiscurveForm)
    {
        hiscurveForm->setWindowTitle(QApplication::translate("hiscurveForm", "\345\216\206\345\217\262\346\233\262\347\272\277", 0, QApplication::UnicodeUTF8));
        label_starttime->setText(QApplication::translate("hiscurveForm", "\345\274\200\345\247\213\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_endtime->setText(QApplication::translate("hiscurveForm", "\347\273\223\346\235\237\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        loadBtn->setText(QApplication::translate("hiscurveForm", "\345\212\240 \350\275\275", 0, QApplication::UnicodeUTF8));
        recoverBtn->setText(QApplication::translate("hiscurveForm", "\346\233\262\347\272\277\345\244\215\345\216\237", 0, QApplication::UnicodeUTF8));
        closeBtn->setText(QApplication::translate("hiscurveForm", "\350\277\224 \345\233\236", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("hiscurveForm", "\346\225\260\346\215\256\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        checkBox_AVolt->setText(QApplication::translate("hiscurveForm", "A\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        toolButton_phAvolt->setText(QString());
        checkBox_BVolt->setText(QApplication::translate("hiscurveForm", "B\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        toolButton_phBvolt->setText(QString());
        checkBox_CVolt->setText(QApplication::translate("hiscurveForm", "C\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        toolButton_phCvolt->setText(QString());
        checkBox_All->setText(QApplication::translate("hiscurveForm", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
        checkBox_totalvolt->setText(QApplication::translate("hiscurveForm", "\346\200\273\350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        toolButton_totalvolt->setText(QString());
        checkBox_totalcurr->setText(QApplication::translate("hiscurveForm", "\346\200\273\350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        toolButton_totalcurr->setText(QString());
        checkBox_excitvolt->setText(QApplication::translate("hiscurveForm", "\345\212\261\347\243\201\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        toolButton_excitvolt->setText(QString());
        checkBox_excitcurr->setText(QApplication::translate("hiscurveForm", "\345\212\261\347\243\201\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        toolButton_excitcurr->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class hiscurveForm: public Ui_hiscurveForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISCURVE_H
