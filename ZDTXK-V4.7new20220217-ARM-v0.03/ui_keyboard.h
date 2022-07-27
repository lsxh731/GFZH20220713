/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created: Tue Jul 26 18:35:31 2022
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_keyBoardDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_input;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_9;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pointBtn;
    QPushButton *pushButton_0;
    QPushButton *nagBtn;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QPushButton *clearBtn;

    void setupUi(QDialog *keyBoardDialog)
    {
        if (keyBoardDialog->objectName().isEmpty())
            keyBoardDialog->setObjectName(QString::fromUtf8("keyBoardDialog"));
        keyBoardDialog->resize(333, 275);
        QIcon icon;
        icon.addFile(QString::fromUtf8("keyboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        keyBoardDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(keyBoardDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(keyBoardDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(16);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit_input = new QLineEdit(keyBoardDialog);
        lineEdit_input->setObjectName(QString::fromUtf8("lineEdit_input"));
        lineEdit_input->setFont(font);

        horizontalLayout->addWidget(lineEdit_input);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_1 = new QPushButton(keyBoardDialog);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setFont(font);

        horizontalLayout_2->addWidget(pushButton_1);

        pushButton_2 = new QPushButton(keyBoardDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font);

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(keyBoardDialog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font);

        horizontalLayout_2->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_6 = new QPushButton(keyBoardDialog);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setFont(font);

        horizontalLayout_3->addWidget(pushButton_6);

        pushButton_5 = new QPushButton(keyBoardDialog);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setFont(font);

        horizontalLayout_3->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(keyBoardDialog);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setFont(font);

        horizontalLayout_3->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_9 = new QPushButton(keyBoardDialog);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setFont(font);

        horizontalLayout_4->addWidget(pushButton_9);

        pushButton_8 = new QPushButton(keyBoardDialog);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setFont(font);

        horizontalLayout_4->addWidget(pushButton_8);

        pushButton_7 = new QPushButton(keyBoardDialog);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setFont(font);

        horizontalLayout_4->addWidget(pushButton_7);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pointBtn = new QPushButton(keyBoardDialog);
        pointBtn->setObjectName(QString::fromUtf8("pointBtn"));
        pointBtn->setFont(font);

        horizontalLayout_5->addWidget(pointBtn);

        pushButton_0 = new QPushButton(keyBoardDialog);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setFont(font);

        horizontalLayout_5->addWidget(pushButton_0);

        nagBtn = new QPushButton(keyBoardDialog);
        nagBtn->setObjectName(QString::fromUtf8("nagBtn"));
        nagBtn->setFont(font);

        horizontalLayout_5->addWidget(nagBtn);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        okBtn = new QPushButton(keyBoardDialog);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setFont(font);

        horizontalLayout_6->addWidget(okBtn);

        cancelBtn = new QPushButton(keyBoardDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setFont(font);

        horizontalLayout_6->addWidget(cancelBtn);

        clearBtn = new QPushButton(keyBoardDialog);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));
        clearBtn->setFont(font);

        horizontalLayout_6->addWidget(clearBtn);


        verticalLayout->addLayout(horizontalLayout_6);


        retranslateUi(keyBoardDialog);

        QMetaObject::connectSlotsByName(keyBoardDialog);
    } // setupUi

    void retranslateUi(QDialog *keyBoardDialog)
    {
        keyBoardDialog->setWindowTitle(QApplication::translate("keyBoardDialog", "\346\225\260\345\255\227\351\224\256\347\233\230", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("keyBoardDialog", "\350\276\223\345\205\245\345\200\274", 0, QApplication::UnicodeUTF8));
        pushButton_1->setText(QApplication::translate("keyBoardDialog", "1", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("keyBoardDialog", "2", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("keyBoardDialog", "3", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("keyBoardDialog", "4", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("keyBoardDialog", "5", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("keyBoardDialog", "6", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("keyBoardDialog", "7", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("keyBoardDialog", "8", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("keyBoardDialog", "9", 0, QApplication::UnicodeUTF8));
        pointBtn->setText(QApplication::translate("keyBoardDialog", ".", 0, QApplication::UnicodeUTF8));
        pushButton_0->setText(QApplication::translate("keyBoardDialog", "0", 0, QApplication::UnicodeUTF8));
        nagBtn->setText(QApplication::translate("keyBoardDialog", "-", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("keyBoardDialog", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("keyBoardDialog", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        clearBtn->setText(QApplication::translate("keyBoardDialog", "\346\270\205 \351\231\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class keyBoardDialog: public Ui_keyBoardDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
