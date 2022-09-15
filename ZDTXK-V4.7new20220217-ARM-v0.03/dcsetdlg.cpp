/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: dcsetdlg.cpp
** ժҪ: ֱ�����ڶԻ���
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2019.02.01
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2019.02.01   V1.0      ����
** ������      2019.02.10   V1.1      �޸�
****************************************************************************/
#include "dcsetdlg.h"
#include "commmacro.h"
#include <QComboBox>
#include <QMessageBox>

CDCSetdlg::CDCSetdlg()
{
    m_pUi= new Ui::dcsetDialog;
    m_pUi->setupUi(this);

    m_strErrinfo = QApplication::translate("dcsetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//������ʾ

    m_strInvalidinfo = QApplication::translate("dcsetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//�������ֵ���Ϸ�������������

    m_strFriendlytips=QApplication::translate("dcsetDialog",
        "\345\217\213\346\203\205\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//������ʾ

    m_strListSuccess.clear();
    m_strListFailure.clear();
    for(int i=0;i<16;i++)
    {
     m_strListSuccess.append(QApplication::translate("dcsetDialog",
         tr("\345\212\237\346\224\276%1\347\233\264\346\265\201\350\260\203\350\212\202\346\210\220\345\212\237").arg(i+1),
         0,
         QApplication::UnicodeUTF8));

     m_strListFailure.append(QApplication::translate("dcsetDialog",
         tr("\345\212\237\346\224\276%1\347\233\264\346\265\201\350\260\203\350\212\202\345\244\261\350\264\245").arg(i+1),
             0,
             QApplication::UnicodeUTF8));
    }//for(int i=0;i<16;i++)
    m_nAdjtype = SOLE_ADJ_TYPE;
    m_pUi->lineEdit->setEnabled(false);
    m_pUi->setBtn->setEnabled(false);
    m_pUi->adjBtn->setEnabled(false);
    m_pUi->checkBox->setCheckState(Qt::Unchecked);
    m_isChkDigKeyBoard=false;

    //�ź����
    connect(m_pUi->adjBtn01,SIGNAL(clicked()),this,SLOT(adjBtn01_clicked()));
    connect(m_pUi->adjBtn02,SIGNAL(clicked()),this,SLOT(adjBtn02_clicked()));
    connect(m_pUi->adjBtn03,SIGNAL(clicked()),this,SLOT(adjBtn03_clicked()));
    connect(m_pUi->adjBtn04,SIGNAL(clicked()),this,SLOT(adjBtn04_clicked()));
    connect(m_pUi->adjBtn05,SIGNAL(clicked()),this,SLOT(adjBtn05_clicked()));
    connect(m_pUi->adjBtn06,SIGNAL(clicked()),this,SLOT(adjBtn06_clicked()));
    connect(m_pUi->adjBtn07,SIGNAL(clicked()),this,SLOT(adjBtn07_clicked()));
    connect(m_pUi->adjBtn08,SIGNAL(clicked()),this,SLOT(adjBtn08_clicked()));
    connect(m_pUi->adjBtn09,SIGNAL(clicked()),this,SLOT(adjBtn09_clicked()));
    connect(m_pUi->adjBtn10,SIGNAL(clicked()),this,SLOT(adjBtn10_clicked()));
    connect(m_pUi->adjBtn11,SIGNAL(clicked()),this,SLOT(adjBtn11_clicked()));
    connect(m_pUi->adjBtn12,SIGNAL(clicked()),this,SLOT(adjBtn12_clicked()));
    connect(m_pUi->adjBtn13,SIGNAL(clicked()),this,SLOT(adjBtn13_clicked()));
    connect(m_pUi->adjBtn14,SIGNAL(clicked()),this,SLOT(adjBtn14_clicked()));
    connect(m_pUi->adjBtn15,SIGNAL(clicked()),this,SLOT(adjBtn15_clicked()));
    connect(m_pUi->adjBtn16,SIGNAL(clicked()),this,SLOT(adjBtn16_clicked()));

    connect(m_pUi->comboBox,SIGNAL(activated(int)),this,SLOT(comboBox_clicked(int)));
    connect(m_pUi->setBtn,SIGNAL(clicked()),this,SLOT(setBtn_clicked()));
    connect(m_pUi->adjBtn,SIGNAL(clicked()),this,SLOT(adjBtn_clicked()));
    connect(m_pUi->checkBox,SIGNAL(clicked()),this,SLOT(checkBox_clicked()));//�Ƿ�ѡ�����ּ��ۺ���

}
CDCSetdlg::~CDCSetdlg()
{

}
//�Ƿ�ѡ���ּ��ۺ���
void CDCSetdlg::checkBox_clicked()
{
    if(!m_isChkDigKeyBoard)
    {
        //δ��ѡʱ
        m_pUi->checkBox->setCheckState(Qt::Checked);
        m_isChkDigKeyBoard=true;
        //�����ź���۹�ϵ
        connect(m_pUi->lineEdit,SIGNAL(clicked()),this,SLOT(lineEdit_clicked()));
        connect(m_pUi->lineEdit_01,SIGNAL(clicked()),this,SLOT(lineEdit01_clicked()));
        connect(m_pUi->lineEdit_02,SIGNAL(clicked()),this,SLOT(lineEdit02_clicked()));
        connect(m_pUi->lineEdit_03,SIGNAL(clicked()),this,SLOT(lineEdit03_clicked()));
        connect(m_pUi->lineEdit_04,SIGNAL(clicked()),this,SLOT(lineEdit04_clicked()));
        connect(m_pUi->lineEdit_05,SIGNAL(clicked()),this,SLOT(lineEdit05_clicked()));
        connect(m_pUi->lineEdit_06,SIGNAL(clicked()),this,SLOT(lineEdit06_clicked()));
        connect(m_pUi->lineEdit_07,SIGNAL(clicked()),this,SLOT(lineEdit07_clicked()));
        connect(m_pUi->lineEdit_08,SIGNAL(clicked()),this,SLOT(lineEdit08_clicked()));
        connect(m_pUi->lineEdit_09,SIGNAL(clicked()),this,SLOT(lineEdit09_clicked()));
        connect(m_pUi->lineEdit_10,SIGNAL(clicked()),this,SLOT(lineEdit10_clicked()));
        connect(m_pUi->lineEdit_11,SIGNAL(clicked()),this,SLOT(lineEdit11_clicked()));
        connect(m_pUi->lineEdit_12,SIGNAL(clicked()),this,SLOT(lineEdit12_clicked()));
        connect(m_pUi->lineEdit_13,SIGNAL(clicked()),this,SLOT(lineEdit13_clicked()));
        connect(m_pUi->lineEdit_14,SIGNAL(clicked()),this,SLOT(lineEdit14_clicked()));
        connect(m_pUi->lineEdit_15,SIGNAL(clicked()),this,SLOT(lineEdit15_clicked()));
        connect(m_pUi->lineEdit_16,SIGNAL(clicked()),this,SLOT(lineEdit16_clicked()));
    }
    else
    {
        //�ѹ�ѡʱ
        m_pUi->checkBox->setCheckState(Qt::Unchecked);
        m_isChkDigKeyBoard=false;
        //�Ͽ��ź���۹�ϵ
        disconnect(m_pUi->lineEdit,0,0,0);
        disconnect(m_pUi->lineEdit_01,0,0,0);
        disconnect(m_pUi->lineEdit_02,0,0,0);
        disconnect(m_pUi->lineEdit_03,0,0,0);
        disconnect(m_pUi->lineEdit_04,0,0,0);
        disconnect(m_pUi->lineEdit_05,0,0,0);
        disconnect(m_pUi->lineEdit_06,0,0,0);
        disconnect(m_pUi->lineEdit_07,0,0,0);
        disconnect(m_pUi->lineEdit_08,0,0,0);
        disconnect(m_pUi->lineEdit_09,0,0,0);
        disconnect(m_pUi->lineEdit_10,0,0,0);
        disconnect(m_pUi->lineEdit_11,0,0,0);
        disconnect(m_pUi->lineEdit_12,0,0,0);
        disconnect(m_pUi->lineEdit_13,0,0,0);
        disconnect(m_pUi->lineEdit_14,0,0,0);
        disconnect(m_pUi->lineEdit_15,0,0,0);
        disconnect(m_pUi->lineEdit_16,0,0,0);
    }
}
//����01ֱ�����ڲۺ���
void CDCSetdlg::adjBtn01_clicked()
{
 EffectiveJudge(m_pUi->lineEdit_01->text());
  QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(0)));
}
//����02ֱ�����ڲۺ���
void CDCSetdlg::adjBtn02_clicked()
{
 EffectiveJudge(m_pUi->lineEdit_02->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(1)));
}
//����03ֱ�����ڲۺ���
void CDCSetdlg::adjBtn03_clicked()
{
  EffectiveJudge(m_pUi->lineEdit_03->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(2)));
}
//����04ֱ�����ڲۺ���
void CDCSetdlg::adjBtn04_clicked()
{
     EffectiveJudge(m_pUi->lineEdit_04->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(3)));
}
//����05ֱ�����ڲۺ���
void CDCSetdlg::adjBtn05_clicked()
{
     EffectiveJudge(m_pUi->lineEdit_05->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(4)));
}
//����06ֱ�����ڲۺ���
void CDCSetdlg::adjBtn06_clicked()
{
     EffectiveJudge(m_pUi->lineEdit_06->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(5)));
}
//����07ֱ�����ڲۺ���
void CDCSetdlg::adjBtn07_clicked()
{
     EffectiveJudge(m_pUi->lineEdit_07->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(6)));
}
//����08ֱ�����ڲۺ���
void CDCSetdlg::adjBtn08_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_08->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(7)));
}
//����09ֱ�����ڲۺ���
void CDCSetdlg::adjBtn09_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_09->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(8)));
}
//����10ֱ�����ڲۺ���
void CDCSetdlg::adjBtn10_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_10->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(9)));
}
//����11ֱ�����ڲۺ���
void CDCSetdlg::adjBtn11_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_11->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(10)));
}
//����12ֱ�����ڲۺ���
void CDCSetdlg::adjBtn12_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_12->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(11)));
}
//����13ֱ�����ڲۺ���
void CDCSetdlg::adjBtn13_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_13->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(12)));
}
//����14ֱ�����ڲۺ���
void CDCSetdlg::adjBtn14_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_14->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(13)));
}
//����15ֱ�����ڲۺ���
void CDCSetdlg::adjBtn15_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_15->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(14)));
}
//����16ֱ�����ڲۺ���
void CDCSetdlg::adjBtn16_clicked()
{
    EffectiveJudge(m_pUi->lineEdit_16->text());
     QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(15)));
}
void CDCSetdlg::comboBox_clicked(int index)
{
    switch(index)
    {
    case 0:
        m_nAdjtype = SOLE_ADJ_TYPE;//��һ����ģʽ�����ͣ�
        m_pUi->lineEdit->setEnabled(false);
        m_pUi->setBtn->setEnabled(false);
        m_pUi->adjBtn->setEnabled(false);
        break;
    case 1:
        m_nAdjtype = UNIFY_ADJ_TYPE;//ͳһ����ģʽ�����ͣ�
        m_pUi->lineEdit->setEnabled(true);
        m_pUi->setBtn->setEnabled(true);
        m_pUi->adjBtn->setEnabled(true);
        break;
    default:
        m_nAdjtype = SOLE_ADJ_TYPE;//��һ����ģʽ�����ͣ�
        m_pUi->lineEdit->setEnabled(false);
        m_pUi->setBtn->setEnabled(false);
        m_pUi->adjBtn->setEnabled(false);
        break;
    }

}
//"����"�ۺ���
 void CDCSetdlg::setBtn_clicked()
{
    unifyset( m_pUi->lineEdit->text());

}
//"����"�ۺ���
void CDCSetdlg::adjBtn_clicked()
{

}
//ͳһ��������LineEdit
void CDCSetdlg::unifyset(QString text)
{
    bool ok =false;
    text.toFloat(&ok);
    if(ok)
    {
     m_pUi->lineEdit_01->setText(text);
     m_pUi->lineEdit_02->setText(text);
     m_pUi->lineEdit_03->setText(text);
     m_pUi->lineEdit_04->setText(text);
     m_pUi->lineEdit_05->setText(text);
     m_pUi->lineEdit_06->setText(text);
     m_pUi->lineEdit_07->setText(text);
     m_pUi->lineEdit_08->setText(text);
     m_pUi->lineEdit_09->setText(text);
     m_pUi->lineEdit_10->setText(text);
     m_pUi->lineEdit_11->setText(text);
     m_pUi->lineEdit_12->setText(text);
     m_pUi->lineEdit_13->setText(text);
     m_pUi->lineEdit_14->setText(text);
     m_pUi->lineEdit_15->setText(text);
     m_pUi->lineEdit_16->setText(text);
    }
    else
    {

        QMessageBox::warning(this,
            tr(m_strErrinfo),
            tr(m_strInvalidinfo));//�������ֵ���Ϸ�

    }

}
//�ж�lineEdit����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit);
    EffectiveJudge(m_pUi->lineEdit->text());
}
//�ж�lineEdit01����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit01_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_01);
    EffectiveJudge(m_pUi->lineEdit_01->text());
}
//�ж�lineEdit02����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit02_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_02);
    EffectiveJudge(m_pUi->lineEdit_02->text());
}
//�ж�lineEdit03����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit03_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_03);
    EffectiveJudge(m_pUi->lineEdit_03->text());
}
//�ж�lineEdit04����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit04_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_04);
    EffectiveJudge(m_pUi->lineEdit_04->text());
}
//�ж�lineEdit05����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit05_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_05);
    EffectiveJudge(m_pUi->lineEdit_05->text());
}
//�ж�lineEdit06����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit06_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_06);
    EffectiveJudge(m_pUi->lineEdit_06->text());
}
//�ж�lineEdit07����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit07_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_07);
    EffectiveJudge(m_pUi->lineEdit_07->text());
}
//�ж�lineEdit08����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit08_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_08);
    EffectiveJudge(m_pUi->lineEdit_08->text());
}
//�ж���ֵ�Ϸ��Ժ���
void CDCSetdlg::EffectiveJudge(QString text)
{
    bool ok =false;
    text.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,
            tr(m_strErrinfo),
            tr(m_strInvalidinfo));//�������ֵ���Ϸ�
    }
}
//�ж�lineEdit09����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit09_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_09);
    EffectiveJudge(m_pUi->lineEdit_09->text());
}
//�ж�lineEdit10����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit10_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_10);
    EffectiveJudge(m_pUi->lineEdit_10->text());
}
//�ж�lineEdit11����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit11_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_11);
    EffectiveJudge(m_pUi->lineEdit_11->text());
}
//�ж�lineEdit12����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit12_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_12);
    EffectiveJudge(m_pUi->lineEdit_12->text());
}
//�ж�lineEdit13����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit13_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_13);
    EffectiveJudge(m_pUi->lineEdit_13->text());
}
//�ж�lineEdit14����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit14_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_14);
    EffectiveJudge(m_pUi->lineEdit_14->text());
}
//�ж�lineEdit15����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit15_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_15);
    EffectiveJudge(m_pUi->lineEdit_15->text());
}
//�ж�lineEdit16����ĵ�����ֵ�Ƿ�Ϸ�
void CDCSetdlg::lineEdit16_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_16);
    EffectiveJudge(m_pUi->lineEdit_16->text());
}
//�����ּ��̶Ի���
void CDCSetdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    bool ok=false;
    if(m_isChkDigKeyBoard)
    {
        m_KeyBoardDlg.exec();//�򿪼��̶Ի���
        m_KeyBoardDlg.clearBtn_clicked();//����ɵ�����ۼ�
        ok=m_KeyBoardDlg.getInputValue(fValue);
        if(ok)
        {
            lineEdit->setText(QString::number(fValue,'f',1));
        }
        else
        {
            QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//�������ֵ���Ϸ�
        }
    }//if(m_isChkDigKeyBoard)
}
