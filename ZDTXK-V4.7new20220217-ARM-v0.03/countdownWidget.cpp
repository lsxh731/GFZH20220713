#include "countdownWidget.h"
extern int g_iLangChange;//add by 2019.10.3
CCountDownWidget::CCountDownWidget()
{
    m_pUi= new Ui::countdownForm;
    m_pUi->setupUi(this);
}
CCountDownWidget::~CCountDownWidget()
{
}
//显示剩余时间(单位秒)
void CCountDownWidget::showRemainingTime(int nSecond)
{
   m_pUi->lineEdit->setText(QString::number(nSecond));
}
void CCountDownWidget::countdownLangChange()
{
    if(g_iLangChange==1)
    {
        m_pUi->label->setText(QApplication::translate("countdownForm", "\345\200\222\350\256\241\346\227\266", 0, QApplication::UnicodeUTF8));
    }
    else
    {
        m_pUi->label->setText("Count down");
    }
}
