/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: thresholdsetdlg.cpp
** ժҪ: "������ֵ"�����ӶԻ���
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2018.12.10
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2018.12.10   V1.0      ����
** ������      2019.02.02   V1.1      �޸�
****************************************************************************/
#include "thresholdsetdlg.h"
#include <iostream>
#include <qlineedit.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qstringlist.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "commmacro.h"

#ifdef UBUNTU_DEV //Compiler Switch
#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/fs.h>
#include <termio.h>
#endif    //Compiler Switch
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <QFile>
#include <QTextStream>
#include <QDoubleValidator>

CThresholdsetdlg::CThresholdsetdlg()
{
    m_pUi= new Ui::thresholdsetDialog;
    m_pUi->setupUi(this);

    m_strErrinfo = QApplication::translate("thresholdsetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//������ʾ

    m_strInvalidinfo = QApplication::translate("thresholdsetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//�������ֵ���Ϸ�������������

    //�ź����
    connect(m_pUi->scbhSetBtn,SIGNAL(clicked()),this,SLOT(scbhSetBtn_clicked()));
    connect(m_pUi->gybhSetBtn,SIGNAL(clicked()),this,SLOT(gybhSetBtn_clicked()));
    connect(m_pUi->scdlSetBtn,SIGNAL(clicked()),this,SLOT(scdlSetBtn_clicked()));
    connect(m_pUi->IGBTgwSetBtn,SIGNAL(clicked()),this,SLOT(IGBTgwSetBtn_clicked()));
    connect(m_pUi->dggwSetBtn,SIGNAL(clicked()),this,SLOT(dggwSetBtn_clicked()));

    connect(m_pUi->scbhLowerEdit,SIGNAL(clicked()),this,SLOT(scbhLowerEdit_clicked()));
    connect(m_pUi->scbhUpEdit,SIGNAL(clicked()),this,SLOT(scbhUpEdit_clicked()));

    connect(m_pUi->gybhLowerEdit,SIGNAL(clicked()),this,SLOT(gybhLowerEdit_clicked()));
    connect(m_pUi->gybhUpEdit,SIGNAL(clicked()),this,SLOT(gybhUpEdit_clicked()));

    connect(m_pUi->scdlProcEdit,SIGNAL(clicked()),this,SLOT(scdlProcEdit_clicked()));
    connect(m_pUi->scdlWarningEdit,SIGNAL(clicked()),this,SLOT(scdlWarningEdit_clicked()));

    connect(m_pUi->IGBTgw1Edit,SIGNAL(clicked()),this,SLOT(IGBTgw1Edit_clicked()));
    connect(m_pUi->IGBTgw2Edit,SIGNAL(clicked()),this,SLOT(IGBTgw2Edit_clicked()));

    connect(m_pUi->dggw1Edit,SIGNAL(clicked()),this,SLOT(dggw1Edit_clicked()));
    connect(m_pUi->dggw2Edit,SIGNAL(clicked()),this,SLOT(dggw2Edit_clicked()));

    //connect(m_pUi->checkBox,SIGNAL(clicked()),this,SLOT(checkBox_clicked()));

    init();//��ʼ��

    m_strTips=QApplication::translate("thresholdsetDialog",
        "\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//��ʾ

    m_CANfd =-1;

#ifdef UBUNTU_DEV
    m_CANfd=m_CANDatarw.openCANSerialPort();
    if (m_CANfd < 0)
    {
        QMessageBox::warning(this, tr(m_strErrinfo), tr("Fail to open serial port!"));
        return ;
    }
    else
    {
        //QMessageBox::warning(this, tr("info"), tr("Success to open serial port!"));
        printf("####��CThresholdsetdlg::CThresholdsetdlg��Success to open serial port!####\n");
        return;
    }
#endif
}
CThresholdsetdlg::~CThresholdsetdlg()
{

}
void CThresholdsetdlg::init()
{

#ifdef WIN_DEV
    m_strFilepathName="./debug/procvalueset.ini";
#else
    m_strFilepathName=QApplication::applicationDirPath() + "/" +"procvalueset.ini";
#endif
    memset(&m_struProcValData,0,sizeof(m_struProcValData));
    m_Inifile.readProcValueSetInifile(m_struProcValData);
    m_pUi->scbhLowerEdit->setText(QString::number(m_struProcValData.fOutVoltLow,'f',1));
    m_pUi->scbhUpEdit->setText(QString::number(m_struProcValData.fOutVoltUp,'f',1));

    m_pUi->gybhLowerEdit->setText(QString::number(m_struProcValData.fDCVoltOverLow,'f',1));
    m_pUi->gybhUpEdit->setText(QString::number(m_struProcValData.fDCVoltOverUp,'f',1));

    m_pUi->scdlProcEdit->setText(QString::number(m_struProcValData.fCurrentProcVal,'f',1));
    m_pUi->scdlWarningEdit->setText(QString::number(m_struProcValData.fCurrentWarnVal,'f',1));

    m_pUi->IGBTgw1Edit->setText(QString::number(m_struProcValData.fIGBTGW1,'f',1));
    m_pUi->IGBTgw2Edit->setText(QString::number(m_struProcValData.fIGBTGW2,'f',1));

    m_pUi->dggw1Edit->setText(QString::number(m_struProcValData.fIDCUTGW1,'f',1));
    m_pUi->dggw2Edit->setText(QString::number(m_struProcValData.fIDCUTGW2,'f',1));

    //���Ƶ�ѹ����ֵ��Χ
     m_pUi->scbhLowerEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->scbhUpEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->gybhLowerEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->gybhUpEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->scdlProcEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
     m_pUi->scdlWarningEdit->setValidator(new QDoubleValidator(PROC_SET_VOLT_LOW,PROC_SET_VOLT_UP,1,this));
   //�����¶�����ֵ��Χ
     m_pUi->IGBTgw1Edit->setValidator(new QDoubleValidator(PROC_SET_TEMPER_LOW,PROC_SET_TEMPER_UP,1,this));
     m_pUi->IGBTgw2Edit->setValidator(new QDoubleValidator(PROC_SET_TEMPER_LOW,PROC_SET_TEMPER_UP,1,this));
     m_pUi->dggw1Edit->setValidator(new QDoubleValidator(PROC_SET_TEMPER_LOW,PROC_SET_TEMPER_UP,1,this));
     m_pUi->dggw2Edit->setValidator(new QDoubleValidator(PROC_SET_CURRENT_LOW,PROC_SET_CURRENT_UP,1,this));

     /*m_isChkDigKeyBoard=false;*/
}
//�����ѹ����ֵ����-�ۺ���
void CThresholdsetdlg::scbhSetBtn_clicked()
{
    //׼������
     bool ok=false;
     int iLowvalue=0;
     int iUpvalue =0;
     float fscbhLower=m_pUi->scbhLowerEdit->text().toFloat(&ok);
     float fscbhUp = m_pUi->scbhUpEdit->text().toFloat(&ok);
     fscbhLower=fscbhLower*RATIO;
     fscbhUp=fscbhUp*RATIO;
     iLowvalue=(int)(fscbhLower);//ǿ��ת�����ͣ�����Ŀ������ʧ����!!!
     iUpvalue=(int)(fscbhUp);    //ǿ��ת�����ͣ�����Ŀ������ʧ����!!!
     //��������
     //m_CANDatarw.sendOutPutVoltData(m_CANfd,iLowvalue>>8,iLowvalue,iUpvalue>>8,iUpvalue);
     //������ʾ��Ϣ
     QString strSuccessTmp=QApplication::translate("thresholdsetDialog",
         "\350\276\223\345\207\272\347\224\265\345\216\213\344\277\235\346\212\244\345\200\274\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);
    QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
     //�Ѳ��������¼���ļ���
    saveThresholdset(tr("outvolt_low=.*"),tr("outvolt_low="),m_pUi->scbhLowerEdit->text());
    saveThresholdset(tr("outvolt_up=.*"),tr("outvolt_up="),m_pUi->scbhUpEdit->text());
}
//��ѹ����ֵ����-�ۺ���
void CThresholdsetdlg::gybhSetBtn_clicked()
{
    //׼������
     bool ok=false;
     int iLowvalue=0;
     int iUpvalue =0;
     float fgybhLower= m_pUi->gybhLowerEdit->text().toFloat(&ok);
     fgybhLower =fgybhLower*RATIO;
     float fgybhUp=m_pUi->gybhUpEdit->text().toFloat(&ok);
     fgybhUp = fgybhUp*RATIO;
     iLowvalue=(int)(fgybhLower);//ǿ��ת�����ͣ�����Ŀ������ʧ����!!!
     iUpvalue=(int)(fgybhUp);   //ǿ��ת�����ͣ�����Ŀ������ʧ����!!!

#ifdef UBUNTU_DEV
     if (m_CANfd < 0)
     {
       m_CANfd=m_CANDatarw.openCANSerialPort();
       if (m_CANfd < 0)
       {
         QMessageBox::warning(this, tr(m_strErrinfo), tr("Fail to open serial port!"));
         return ;
       }
     }

     printf("####%X-%X####\n",iLowvalue>>8,iLowvalue);
     QString str1=QString::number(iLowvalue>>8,16).toUpper();
     QString str2=QString::number(iLowvalue,16).toUpper();
     //��������
     //m_CANDatarw.sendDCVoltLowData(m_CANfd,iLowvalue>>8,iLowvalue);
     //��ʱ2��
     sleep(2);
     //m_CANDatarw.sendDCVoltUpData(m_CANfd,iUpvalue>>8,iUpvalue);
     //������ʾ��Ϣ
     QString strSuccessTmp=QApplication::translate("thresholdsetDialog",
         "\345\212\237\347\216\207\346\250\241\345\235\227\350\276\223\345\205\245\347\233\264\346\265\201\347\224\265\345\216\213\350\277\207\345\216\213\344\277\235\346\212\244\345\200\274\350\256\276\347\275\256\346\210\220\345\212\237",
              0,
              QApplication::UnicodeUTF8);
     QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
     //�Ѳ��������¼���ļ���
    saveThresholdset(tr("dcvolt_low=.*"),tr("dcvolt_low="),m_pUi->gybhLowerEdit->text());
    saveThresholdset(tr("dcvolt_up=.*"),tr("dcvolt_up="),m_pUi->gybhUpEdit->text());
#endif
}
//�����������-�ۺ���
void CThresholdsetdlg::scdlSetBtn_clicked()
{
     //׼������
     bool ok=false;
     int iLowvalue=0;
     int iUpvalue=0;
     float fscdlProc=m_pUi->scdlProcEdit->text().toFloat(&ok);     //����ֵ
     float fscdlWarning=m_pUi->scdlWarningEdit->text().toFloat(&ok);//����ֵ
     fscdlProc=fscdlProc*RATIO;
     fscdlWarning=fscdlWarning*RATIO;
     iLowvalue=(int)(fscdlProc);  //ǿ��ת�����ͣ�����Ŀ������ʧ����!!!
     iUpvalue=(int)(fscdlWarning);//ǿ��ת�����ͣ�����Ŀ������ʧ����!!!
#ifdef UBUNTU_DEV
     if (m_CANfd < 0)
     {
       m_CANfd=m_CANDatarw.openCANSerialPort();
       if (m_CANfd < 0)
       {
         QMessageBox::warning(this, tr(m_strErrinfo), tr("Fail to open serial port!"));
         return ;
       }
     }
     //��������
    // m_CANDatarw.sendProcAndWarnData(m_CANfd,iLowvalue>>8,iLowvalue,iUpvalue>>8,iUpvalue);
     //������ʾ��Ϣ
     QString strSuccessTmp=QApplication::translate("thresholdsetDialog",
         "\345\212\237\347\216\207\346\250\241\345\235\227\350\276\223\345\207\272\347\224\265\346\265\201\345\200\274\344\270\212\351\231\220\350\256\276\347\275\256\346\210\220\345\212\237",
         0, QApplication::UnicodeUTF8);
     QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
      //�Ѳ��������¼���ļ���
    saveThresholdset(tr("currprocvalue=.*"),tr("currprocvalue="),m_pUi->scdlProcEdit->text());
    saveThresholdset(tr("currwarnvalue=.*"),tr("currwarnvalue="),m_pUi->scdlWarningEdit->text());
#endif
}
//IGBT���¶���ֵ����-�ۺ���
void CThresholdsetdlg::IGBTgwSetBtn_clicked()
{
    //׼������
     bool ok=false;
     int iGW1value=0;
     int iGW2value=0;
     float fIGBTgw1 = m_pUi->IGBTgw1Edit->text().toFloat(&ok);
     float fIGBTgw2 = m_pUi->IGBTgw2Edit->text().toFloat(&ok);
     fIGBTgw1=fIGBTgw1*RATIO;
     fIGBTgw2=fIGBTgw2*RATIO;
     iGW1value=(int)(fIGBTgw1);//ǿ��ת�����ͣ�����Ŀ������ʧ����!!!
     iGW2value=(int)(fIGBTgw2);//ǿ��ת�����ͣ�����Ŀ������ʧ����!!!
#ifdef UBUNTU_DEV
     //��������
     //m_CANDatarw.sendIGBTTemperData(m_CANfd,iGW1value>>8,iGW1value,iGW2value>>8,iGW2value);
     //������ʾ��Ϣ
     QString strSuccessTmp= QApplication::translate("thresholdsetDialog",
          "\345\212\237\347\216\207\346\250\241\345\235\227IGBT\350\277\207\346\270\251\345\212\250\344\275\234\345\200\274\350\256\276\347\275\256\346\210\220\345\212\237",
          0,
          QApplication::UnicodeUTF8);
     QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
    //�Ѳ��������¼���ļ���
    saveThresholdset(tr("IGBT_temper1=.*"),tr("IGBT_temper1="),m_pUi->IGBTgw1Edit->text());
    saveThresholdset(tr("IGBT_temper2=.*"),tr("IGBT_temper2="),m_pUi->IGBTgw2Edit->text());
#endif
}
//��й��¶���ֵ����-�ۺ���
void CThresholdsetdlg::dggwSetBtn_clicked()
{
    //׼������
     bool ok=false;
     int iDGGW1value=0;
     int iDGGW2value=0;   //ʵ��Ϊ�ܵ���ƽ��ֵ
     float fdggw1= m_pUi->dggw1Edit->text().toFloat(&ok);
     float fdggw2= m_pUi->dggw2Edit->text().toFloat(&ok);
     fdggw1=fdggw1*RATIO;
     fdggw2=fdggw2*RATIO;
     iDGGW1value=(int)(fdggw1);
     iDGGW2value=(int)(fdggw2);
#ifdef UBUNTU_DEV
     //��������
     //m_CANDatarw.sendIDUCTTemper1Data(m_CANfd,iDGGW1value>>8,iDGGW1value);
     //��ʱ2��
     sleep(2);
    // m_CANDatarw.sendIDUCTTemper2Data(m_CANfd,iDGGW2value>>8,iDGGW2value);
     //������ʾ��Ϣ
     QString strSuccessTmp=QApplication::translate("thresholdsetDialog",
         "\345\212\237\347\216\207\346\250\241\345\235\227\347\224\265\346\204\237\350\277\207\346\270\251\345\212\250\344\275\234\345\200\274\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);
     QMessageBox::information(this,
        tr(m_strTips),
        tr(strSuccessTmp));
     //�Ѳ��������¼���ļ���
    saveThresholdset(tr("IDUCT_temper=.*"),tr("IDUCT_temper="),m_pUi->dggw1Edit->text());
    saveThresholdset(tr("SUMCURRENT_AVE=.*"),tr("SUMCURRENT_AVE="),m_pUi->dggw2Edit->text());
#endif
}
//���汣����ֵ�������ļ���
bool CThresholdsetdlg::saveThresholdset(QString strRegExp,QString strReplace,QString strText)
{
     QFile file(m_strFilepathName);
     if(!file.open(QFile::ReadOnly | QFile::Text))
      {
          printf("####Cannot open file for Reading####\n");
          return false;
       }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    int i=0;
    for(i=0;i<linelist.size();i++)
    {
        QString strTmp=linelist.at(i);
     if(strTmp.contains(strReplace, Qt::CaseInsensitive))
      {
          strTmp.replace(QRegExp(strRegExp),(strReplace+strText));
          linelist.replace(i,strTmp);//�滻����
      }
    }
     file.close();
     QFile::remove(m_strFilepathName);
      if(!file.open(QFile::WriteOnly | QFile::Text))
      {
          printf( "####Cannot open file for Writing####\n");
          return false;
      }
      for(i=0;i<linelist.size();i++)
      {
          file.write(linelist.at(i).toUtf8());
          file.write(tr("\n").toUtf8());
      }
      file.close();
    return true;
}
//��Ч���ж�
void  CThresholdsetdlg::EffectiveJudge(QString text,int nDatatype)
{
    bool ok =false;
    float fValue=text.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,
            tr(m_strErrinfo),
            tr(m_strInvalidinfo));//�������ֵ���Ϸ�
    }
    else
    {
     switch(nDatatype)
       {
        case PROC_SET_VOLT_TYPE:
            {
                if(((fValue-PROC_SET_VOLT_UP)>0.01)||((fValue-PROC_SET_VOLT_LOW)<0.01))
                {
                    QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//�������ֵ���Ϸ�
                }
            }
            break;
        case PROC_SET_TEMPER_TYPE:
            {
                if(((fValue-PROC_SET_TEMPER_UP)>0.01)||((fValue-PROC_SET_TEMPER_LOW)<0.01))
                {
                    QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//�������ֵ���Ϸ�
                }
            }
            break;
        default:
            break;
       }//switch(nDatatype)
    }
}
//�����ּ��̶Ի���
void CThresholdsetdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    bool ok=false;
    /*if(m_isChkDigKeyBoard)*/
    //{
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
    //}//if(m_isChkDigKeyBoard)
}
void CThresholdsetdlg::scbhLowerEdit_clicked()
{
    //�����ּ��̶Ի���
     openDigKeyBoardDlg(m_pUi->scbhLowerEdit);

    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}

void CThresholdsetdlg::scbhUpEdit_clicked()
{
    //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->scbhUpEdit);
    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::gybhLowerEdit_clicked()
{
     //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->gybhLowerEdit);
    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::gybhUpEdit_clicked()
{
     //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->gybhUpEdit);
    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::scdlProcEdit_clicked()
{
     //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->scdlProcEdit);
    //��Ч���ж�
    //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::scdlWarningEdit_clicked()
{
     //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->scdlWarningEdit);
    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_VOLT_TYPE);
}
void CThresholdsetdlg::IGBTgw1Edit_clicked()
{
     //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->IGBTgw1Edit);
    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_TEMPER_TYPE);
}
void CThresholdsetdlg::IGBTgw2Edit_clicked()
{
     //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->IGBTgw2Edit);
    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_TEMPER_TYPE);
}
void CThresholdsetdlg::dggw1Edit_clicked()
{
     //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->dggw1Edit);
    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_TEMPER_TYPE);
}
void CThresholdsetdlg::dggw2Edit_clicked()
{
     //�����ּ��̶Ի���
    openDigKeyBoardDlg(m_pUi->dggw2Edit);
    //��Ч���ж�
     //EffectiveJudge(text,PROC_SET_TEMPER_TYPE);
}
//"�Ƿ�ѡ���ּ�"�ۺ���
//void CThresholdsetdlg::checkBox_clicked()
//{
//	if(m_pUi->checkBox->checkState()==Qt::Checked)
//	{
//		m_isChkDigKeyBoard=true;
//
//	}
//	else if(m_pUi->checkBox->checkState()==Qt::Unchecked)
//	{
//		m_isChkDigKeyBoard=false;
//	}
//
//}
