/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: keyboraddlg.cpp
** ժҪ: "��������"�Ի���
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2019.02.23
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2019.02.23   V1.0      ����
**
****************************************************************************/
#include "keyboarddlg.h"
extern int g_iLangChange;//add by 2019.10.3
CKeyBoardDlg::CKeyBoardDlg()
{
    m_pUi= new Ui::keyBoardDialog;
    m_pUi->setupUi(this);
    init();
    //keyboardLangChange();
}
CKeyBoardDlg::~CKeyBoardDlg()
{
}
void CKeyBoardDlg::init()
{
    //�ź����
    connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    connect(m_pUi->cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_clicked()));
    connect(m_pUi->clearBtn,SIGNAL(clicked()),this,SLOT(clearBtn_clicked()));

    //pushButton_0
    connect(m_pUi->pushButton_0,SIGNAL(clicked()),this,SLOT(pushButton0_clicked()));
    //pushButton_1
    connect(m_pUi->pushButton_1,SIGNAL(clicked()),this,SLOT(pushButton1_clicked()));
    //pushButton_2
    connect(m_pUi->pushButton_2,SIGNAL(clicked()),this,SLOT(pushButton2_clicked()));
    //pushButton_3
    connect(m_pUi->pushButton_3,SIGNAL(clicked()),this,SLOT(pushButton3_clicked()));
    //pushButton_4
    connect(m_pUi->pushButton_4,SIGNAL(clicked()),this,SLOT(pushButton4_clicked()));
    //pushButton_5
    connect(m_pUi->pushButton_5,SIGNAL(clicked()),this,SLOT(pushButton5_clicked()));
    //pushButton_6
    connect(m_pUi->pushButton_6,SIGNAL(clicked()),this,SLOT(pushButton6_clicked()));
    //pushButton_7
    connect(m_pUi->pushButton_7,SIGNAL(clicked()),this,SLOT(pushButton7_clicked()));
    //pushButton_8
    connect(m_pUi->pushButton_8,SIGNAL(clicked()),this,SLOT(pushButton8_clicked()));
    //pushButton_9
    connect(m_pUi->pushButton_9,SIGNAL(clicked()),this,SLOT(pushButton9_clicked()));

    connect(m_pUi->pointBtn,SIGNAL(clicked()),this,SLOT(pointBtn_clicked()));
    connect(m_pUi->nagBtn,SIGNAL(clicked()),this,SLOT(nagBtn_clicked()));

    m_fInputValue=0.0;
    m_ok=false;

}
//ȷ��-�ۺ���
void CKeyBoardDlg::okBtn_clicked()
{
    m_ok=false;
    QString strInputText=m_pUi->lineEdit_input->text();
    m_fInputValue=strInputText.toFloat(&m_ok);
    this->close();
}
//ȡ��-�ۺ���
void CKeyBoardDlg::cancelBtn_clicked()
{
    QString strInputText=m_pUi->lineEdit_input->text();
    if(strInputText.length()>=1)
    {
        strInputText.chop(1);//ɾ�����һ���ַ�
    }
    m_pUi->lineEdit_input->setText(strInputText);
}
//���-�ۺ���
void CKeyBoardDlg::clearBtn_clicked()
{
    QString strInputText=m_pUi->lineEdit_input->text();
    if(!(strInputText.isEmpty()))
    {
        //�ǿ������
        m_pUi->lineEdit_input->clear();
    }
}
//��ȡ����ֵ
bool CKeyBoardDlg::getInputValue(float &fValue)
{
    fValue=m_fInputValue;
    return m_ok;
}
//"���ּ�0"�ۺ���
void CKeyBoardDlg::pushButton0_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_0);
}
//"���ּ�1"�ۺ���
void CKeyBoardDlg::pushButton1_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_1);
}
//"���ּ�2"�ۺ���
void CKeyBoardDlg::pushButton2_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_2);
}
//"���ּ�3"�ۺ���
void CKeyBoardDlg::pushButton3_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_3);
}
//"���ּ�4"�ۺ���
void CKeyBoardDlg::pushButton4_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_4);
}
//"���ּ�5"�ۺ���
void CKeyBoardDlg::pushButton5_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_5);
}
//"���ּ�6"�ۺ���
void CKeyBoardDlg::pushButton6_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_6);
}
//"���ּ�7"�ۺ���
void CKeyBoardDlg::pushButton7_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_7);
}
//"���ּ�8"�ۺ���
void CKeyBoardDlg::pushButton8_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_8);
}
//"���ּ�9"�ۺ���
void CKeyBoardDlg::pushButton9_clicked()
{
    getDigitalKeyboardText(m_pUi->pushButton_9);
}
//"С����"�ۺ���
void CKeyBoardDlg::pointBtn_clicked()
{
    getDigitalKeyboardText(m_pUi->pointBtn);
}
//"����"�ۺ���
void CKeyBoardDlg::nagBtn_clicked()
{
    getDigitalKeyboardText(m_pUi->nagBtn);
}
//��ȡ���ּ���
void CKeyBoardDlg::getDigitalKeyboardText(QPushButton *pushButton)
{
    bool editFlag=false;
    editFlag=m_pUi->lineEdit_input->hasAcceptableInput ();
    if (editFlag)
    {
        m_pUi->lineEdit_input->insert(pushButton->text());
    }
}
//��ֹ��ź͸��Ű�ť
void CKeyBoardDlg::disablePointAndNagBtn()
{
    m_pUi->pointBtn->setEnabled(false);
    m_pUi->nagBtn->setEnabled(false);
}
void CKeyBoardDlg::keyboardLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("keyBoardDialog", "\346\225\260\345\255\227\351\224\256\347\233\230", 0, QApplication::UnicodeUTF8));
        m_pUi->label->setText(QApplication::translate("keyBoardDialog", "\350\276\223\345\205\245\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->okBtn->setText(QApplication::translate("keyBoardDialog", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        m_pUi->cancelBtn->setText(QApplication::translate("keyBoardDialog", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        m_pUi->clearBtn->setText(QApplication::translate("keyBoardDialog", "\346\270\205 \351\231\244", 0, QApplication::UnicodeUTF8));
    }
    else
    {
        setWindowTitle("Digital keyboard");
        m_pUi->label->setText("Input value");
        m_pUi->okBtn->setText("OK");
        m_pUi->cancelBtn->setText("Cancel");
        m_pUi->clearBtn->setText("Clear");
    }
}
