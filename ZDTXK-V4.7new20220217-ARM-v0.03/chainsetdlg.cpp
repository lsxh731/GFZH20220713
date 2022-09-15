/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: chainsetdlg.cpp
** ժҪ: "��������"�ӶԻ���
**
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2018.11.10
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2018.11.10   V1.0      ����
** ������      2019.02.10   V1.1      �޸�
****************************************************************************/
#include "chainsetdlg.h"
#include <QMessageBox>
extern struct STRU_CHAINSETDATA g_ChainSetData;//�������ò���-ȫ�ֱ���,add by 2019.05.14
extern int g_iLangChange;               //�����л���ʶ��,1-���ģ�0-Ӣ��

extern STRU_NEWCHASETDATA g_newchasetdata;  //add by zw 20220223
extern STRU_NEWFAULTSTATUS g_newfaultstatus; //add by zw 20220223
CChainsetdlg::CChainsetdlg(int nfd)
{
    m_pUi= new Ui::chainsetDialog;
    m_pUi->setupUi(this);
    m_nGPIOfd=nfd;
    init();
    //�ź���۹�ϵ
    connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
    connect(m_pUi->toolButton_tongyi,SIGNAL(clicked()),this,SLOT(tongyiSwitch_clicked()));
    connect(m_pUi->closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));//���ؼ� add by 2020.08.10

    //����toolbutton�л�-�ۺ���
//    disableChainSet();
//    connect(m_pUi->toolButton_subzlqgw,SIGNAL(clicked()),this,SLOT(subzlqgwSwitch_clicked()));
//    connect(m_pUi->toolButton_htdyw,SIGNAL(clicked()),this,SLOT(htdywSwitch_clicked()));
//    connect(m_pUi->toolButton_ezgwy,SIGNAL(clicked()),this,SLOT(ezgwySwitch_clicked()));

    connect(m_pUi->toolButton_xtlqdy,SIGNAL(clicked()),this,SLOT(xtlqdySwitch_clicked()));
    connect(m_pUi->toolButton_zdtgw,SIGNAL(clicked()),this,SLOT(zdtgwSwitch_clicked()));
    connect(m_pUi->toolButton_zdtgwy,SIGNAL(clicked()),this,SLOT(zdtgwySwitch_clicked()));
    connect(m_pUi->toolButton_htgwy,SIGNAL(clicked()),this,SLOT(htgwySwitch_clicked()));
    connect(m_pUi->toolButton_htqy,SIGNAL(clicked()),this,SLOT(htqySwitch_clicked()));
    connect(m_pUi->toolButton_htqyw,SIGNAL(clicked()),this,SLOT(htqywSwitch_clicked()));
    connect(m_pUi->toolButton_htgw,SIGNAL(clicked()),this,SLOT(htgwSwitch_clicked()));

    connect(m_pUi->toolButton_gfrjbh,SIGNAL(clicked()),this,SLOT(gfrhbhSwitch_clicked()));
    connect(m_pUi->toolButton_jyzcdy,SIGNAL(clicked()),this,SLOT(jyzcdySwitch_clicked()));
    connect(m_pUi->toolButton_zgmenbh,SIGNAL(clicked()),this,SLOT(zgmenbhSwitch_clicked()));
    connect(m_pUi->toolButton_selfdefine1,SIGNAL(clicked()),this,SLOT(selfdefine1Switch_clicked()));
    connect(m_pUi->toolButton_selfdefine2,SIGNAL(clicked()),this,SLOT(selfdefine2Switch_clicked()));
    connect(m_pUi->toolButton_selfdefine3,SIGNAL(clicked()),this,SLOT(selfdefine3Switch_clicked()));
    connect(m_pUi->toolButton_selfdefine4,SIGNAL(clicked()),this,SLOT(selfdefine4Switch_clicked()));

    connect(m_pUi->toolButton_c1zlqgw,SIGNAL(clicked()),this,SLOT(c1zlqgwSwitch_clicked()));
    connect(m_pUi->toolButton_c2zlqgw,SIGNAL(clicked()),this,SLOT(c2zlqgwSwitch_clicked()));
    connect(m_pUi->toolButton_c3zlqgw,SIGNAL(clicked()),this,SLOT(c3zlqgwSwitch_clicked()));
    connect(m_pUi->toolButton_c4zlqgw,SIGNAL(clicked()),this,SLOT(c4zlqgwSwitch_clicked()));
    connect(m_pUi->toolButton_c1cwbh,SIGNAL(clicked()),this,SLOT(c1cwbhSwitch_clicked()));
    connect(m_pUi->toolButton_c2cwbh,SIGNAL(clicked()),this,SLOT(c2cwbhSwitch_clicked()));
    connect(m_pUi->toolButton_c3cwbh,SIGNAL(clicked()),this,SLOT(c3cwbhSwitch_clicked()));
    connect(m_pUi->toolButton_c4cwbh,SIGNAL(clicked()),this,SLOT(c4cwbhSwitch_clicked()));


    connect(m_pUi->comboBox_xtlqdy,SIGNAL(activated(int )),SLOT(comboBox_xtlqdy_activated(int)));//ϵͳ��ȴ��Ԫ�����л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_zdtgw,SIGNAL(activated(int)),SLOT(comboBox_zdtgw_activated(int)));//��̨���´����л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_zdtgwy,SIGNAL(activated(int )),SLOT(comboBox_zdtgwy_activated(int)));//��̨��λ�ƴ����л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_htgwy,SIGNAL(activated(int )),SLOT(comboBox_htgwy_activated(int)));//��̨��λ�ƴ����л��ۺ��� add by 2020.09.05
    connect(m_pUi->comboBox_htqy,SIGNAL(activated(int )),SLOT(comboBox_htqy_activated(int)));//��̨��е�ѹ�����л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_htqyw,SIGNAL(activated(int )),SLOT(comboBox_htqyw_activated(int)));//�������������´����л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_htgw,SIGNAL(activated(int )),SLOT(comboBox_htgw_activated(int)));//�ӹ��ű��������л��ۺ��� add by 2020.09.08

    connect(m_pUi->comboBox_gfrjbh,SIGNAL(activated(int )),SLOT(comboBox_gfrjbh_activated(int)));//�����ȼ̱��������л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_jyzcdy,SIGNAL(activated(int )),SLOT(comboBox_jyzcdy_activated(int)));//��ѹ��е�ѹ�����л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_zgmenbh,SIGNAL(activated(int )),SLOT(comboBox_zgmenbh_activated(int)));//�����ű��������л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_selfdefine1,SIGNAL(activated(int )),SLOT(comboBox_selfdefine1_activated(int)));//�Զ���1���������л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_selfdefine2,SIGNAL(activated(int )),SLOT(comboBox_selfdefine2_activated(int)));//�Զ���2���������л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_selfdefine3,SIGNAL(activated(int )),SLOT(comboBox_selfdefine3_activated(int)));//�Զ���3���������л��ۺ��� add by 2020.09.08
    connect(m_pUi->comboBox_selfdefine4,SIGNAL(activated(int )),SLOT(comboBox_selfdefine4_activated(int)));//�Զ���4���������л��ۺ��� add by 2022.02.23

    connect(m_pUi->comboBox_c1zlqgw,SIGNAL(activated(int )),SLOT(comboBox_c1zlqgw_activated(int)));//�ӹ�1���������´����л��ۺ��� add by 2022.02.23
    connect(m_pUi->comboBox_c2zlqgw,SIGNAL(activated(int )),SLOT(comboBox_c2zlqgw_activated(int)));//�ӹ�2���������´����л��ۺ��� add by 2022.02.23
    connect(m_pUi->comboBox_c3zlqgw,SIGNAL(activated(int )),SLOT(comboBox_c3zlqgw_activated(int)));//�ӹ�3���������´����л��ۺ��� add by 2022.02.23
    connect(m_pUi->comboBox_c4zlqgw,SIGNAL(activated(int )),SLOT(comboBox_c4zlqgw_activated(int)));//�ӹ�4���������´����л��ۺ��� add by 2022.02.23
    connect(m_pUi->comboBox_c1cwbh,SIGNAL(activated(int )),SLOT(comboBox_c1cwbh_activated(int)));  //�ӹ�1�����źŴ����л��ۺ��� add by 2022.02.23
    connect(m_pUi->comboBox_c2cwbh,SIGNAL(activated(int )),SLOT(comboBox_c2cwbh_activated(int)));  //�ӹ�1�����źŴ����л��ۺ��� add by 2022.02.23
    connect(m_pUi->comboBox_c3cwbh,SIGNAL(activated(int )),SLOT(comboBox_c3cwbh_activated(int)));  //�ӹ�1�����źŴ����л��ۺ��� add by 2022.02.23
    connect(m_pUi->comboBox_c4cwbh,SIGNAL(activated(int )),SLOT(comboBox_c4cwbh_activated(int)));  //�ӹ�1�����źŴ����л��ۺ��� add by 2022.02.23

//    connect(m_pUi->comboBox_subyuliu,SIGNAL(activated(int )),this,SLOT(comboBox_subyuliu_activated(int)));//�ӹ�Ԥ�����������л��ۺ��� add by 2020.09.08
//    connect(m_pUi->comboBox_htdyw,SIGNAL(activated(int )),this,SLOT(comboBox_htdyw_activated(int)));//��̨��Һλ�����л��ۺ��� add by 2020.09.08
//    connect(m_pUi->comboBox_subzlqgw,SIGNAL(activated(int )),this,SLOT(comboBox_subzlqgw_activated(int)));//�ӹ����������´����л��ۺ��� add by 2020.09.08
//    connect(m_pUi->comboBox_ezgwy,SIGNAL(activated(int )),this,SLOT(comboBox_ezgwy_activated(int)));//�����λ�ƴ����л��ۺ��� add by 2020.09.08
    //ģʽ�л��ۺ���
    connect(m_pUi->normalBtn,SIGNAL(clicked()),this,SLOT(normal_clicked()));
    connect(m_pUi->debugBtn,SIGNAL(clicked()),this,SLOT(debug_clicked()));
    normal_clicked();
}
CChainsetdlg::~CChainsetdlg()
{
    //�����˳�ʱ�������������ñ���g_ChainSetData,add by 2019.05.26
    memcpy(&g_ChainSetData,&m_ChainSetData,sizeof(m_ChainSetData));

}
//���ò���������������,add by 2019.05.25
void CChainsetdlg::disableChainSet()
{
    //--�����Զ���1����
    m_pUi->toolButton_selfdefine1->setEnabled(false);
    //--�����Զ���2����
    m_pUi->toolButton_selfdefine2->setEnabled(false);
    //--�����Զ���3����
    m_pUi->toolButton_selfdefine3->setEnabled(false);
    //--���ôӹ�Ԥ����������
//    m_pUi->toolButton_subyuliu->setEnabled(false);
}
//ģʽѡ��-����ģʽ
void CChainsetdlg::debug_clicked()
{
    m_iMode=DEBUG_MODE;
    m_pUi->normalBtn->setEnabled(true);
    m_pUi->normalBtn->setDown(false);
    m_pUi->debugBtn->setEnabled(false);
    m_pUi->debugBtn->setDown(true);
}
//ģʽѡ��-����ģʽ
void CChainsetdlg::normal_clicked()
{
    m_iMode=NORMAL_MODE;
    m_pUi->normalBtn->setEnabled(false);
    m_pUi->normalBtn->setDown(true);
    m_pUi->debugBtn->setEnabled(true);
    m_pUi->debugBtn->setDown(false);
}
//��ȡģʽ,add by 2019.04.27
int CChainsetdlg::getMode()
{
    return m_iMode;
}
//��ʼ��������������ҳ��
void CChainsetdlg::init()
{
     allSetBtnEnable(false);
    m_ybonicon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"yb_on.png"), QSize(66, 48), QIcon::Normal, QIcon::Off);
    m_ybofficon.addFile(QString::fromUtf8(QApplication::applicationDirPath()+"/"+"yb_off.png"), QSize(66, 48), QIcon::Normal, QIcon::Off);

     //QColor openBgColor("#279b14"); //"��"��ɫ
     //QColor closeBgColor("#5c606a");//"��"��ɫ
     setAllSwitchIcon(m_ybofficon);
     m_iChainsetval=FULL_DATA_ON;
     m_strListSuccess.clear();
     m_strListFailure.clear();
     QString strSuccess=QApplication::translate("chainsetDialog",
         "\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);   //���óɹ�

     QString strFail=QApplication::translate("chainsetDialog",
         "\350\256\276\347\275\256\345\244\261\350\264\245",
         0, QApplication::UnicodeUTF8);//����ʧ��
     m_strListSuccess.append(m_pUi->label_2->text()+strSuccess);//
     m_strListSuccess.append(m_pUi->label_3->text()+strSuccess);
//     m_strListSuccess.append(m_pUi->label_4->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_6->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_7->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_8->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_9->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_10->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_11->text()+strSuccess);
     m_strListSuccess.append(m_pUi->label_12->text()+strSuccess);
//     m_strListSuccess.append(m_pUi->label_18->text()+strSuccess);//��������������,add by 2019.05.25
//     m_strListSuccess.append(m_pUi->label_20->text()+strSuccess);//�ӹ�����������,add by 2019.05.25
     m_strListSuccess.append(m_pUi->label_21->text()+strSuccess);//�ӹ��ű���,add by 2019.05.25
     m_strListSuccess.append(m_pUi->label_14->text()+strSuccess);//ϵͳ��ȴ��Ԫ,add by 2019.05.25

     m_strListFailure.append(m_pUi->label_2->text()+strFail);
     m_strListFailure.append(m_pUi->label_3->text()+strFail);
//     m_strListFailure.append(m_pUi->label_4->text()+strFail);
     m_strListFailure.append(m_pUi->label_6->text()+strFail);
     m_strListFailure.append(m_pUi->label_7->text()+strFail);
     m_strListFailure.append(m_pUi->label_8->text()+strFail);
     m_strListFailure.append(m_pUi->label_9->text()+strFail);
     m_strListFailure.append(m_pUi->label_10->text()+strFail);
     m_strListFailure.append(m_pUi->label_11->text()+strFail);
     m_strListFailure.append(m_pUi->label_12->text()+strFail);
//     m_strListSuccess.append(m_pUi->label_18->text()+strFail);//��������������,add by 2019.05.25
//     m_strListSuccess.append(m_pUi->label_20->text()+strFail);//�ӹ�����������,add by 2019.05.25
     m_strListSuccess.append(m_pUi->label_21->text()+strFail);//�ӹ��ű���,add by 2019.05.25
     m_strListSuccess.append(m_pUi->label_14->text()+strFail);//ϵͳ��ȴ��Ԫ,add by 2019.05.25

     m_strFriendlytips=QApplication::translate("chainsetDialog",
        "\345\217\213\346\203\205\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//������ʾ


     m_strAllSuccess=QApplication::translate("chainsetDialog",
         "\346\211\200\346\234\211\350\277\236\351\224\201\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);   //�����������óɹ�

     m_strAllFailure=QApplication::translate("chainsetDialog",
         "\346\211\200\346\234\211\350\277\236\351\224\201\350\256\276\347\275\256\345\244\261\350\264\245",
         0, QApplication::UnicodeUTF8); //������������ʧ��

//     initChainSetData();//��ʼ��������������m_ChainSetData,add by 2019.05.26
     newinitChainSetData();//��ʼ��������������m_newChaSetData,add by zw 2022.02.23
     m_iMode=DEBUG_MODE;//����ģʽ
//     m_iMode=NORMAL_MODE;
     m_isTongyi=true;
}
//��ʼ��m_ChainSetData����,add by 2019.05.26
void CChainsetdlg::initChainSetData()
{
     //���������ṹ�������ʼ��,add by 2019.04.13
    if(!(m_IniChainset.readChainsetInifile(m_ChainSetData)))
    {
     m_ChainSetData.iJjtjVal=SWITCH_OFF;  //����ͣ��
     m_ChainSetData.iHtgwyVal=SWITCH_OFF; //��̨��λ��
     m_ChainSetData.iZdtgwyVal=SWITCH_OFF;//��̨��λ��
     m_ChainSetData.iHtdywVal=SWITCH_OFF; //��̨��Һλ
     m_ChainSetData.iHtqyVal=SWITCH_OFF;//��̨��е�ѹ
     m_ChainSetData.iZdtgwVal=SWITCH_OFF; //��̨����
     m_ChainSetData.iEzgwyVal=SWITCH_OFF; //�����λ��
     m_ChainSetData.iGfrjbhVal=SWITCH_OFF;//�����ȼ̱���
     m_ChainSetData.iJyzcdyVal=SWITCH_OFF;//��ѹ��е�ѹ
     m_ChainSetData.iZgMenbVal=SWITCH_OFF;  //�����ű���
     m_ChainSetData.iXtlqdyVal=SWITCH_OFF;//ϵͳ��ȴ��Ԫ
     m_ChainSetData.iHtqywVal=SWITCH_OFF;//���������Ź���,add by 2019.05.25
     m_ChainSetData.iSubMenbVal=SWITCH_OFF;//�ӹ��ű���
     m_ChainSetData.iSubzlqgwVal=SWITCH_OFF;//�ӹ������Ź���,add by 2019.05.25
     m_ChainSetData.iSelfdefineVal1=SWITCH_OFF;//�Զ���1,add by 2019.05.25
     m_ChainSetData.iSelfdefineVal2=SWITCH_OFF;//�Զ���2,add by 2019.05.25
     m_ChainSetData.iSelfdefineVal3=SWITCH_OFF;//�Զ���3,add by 2019.05.25
     m_ChainSetData.iSubyuliuPorcVal=SWITCH_OFF;//�ӹ�Ԥ������,add by 2019.05.25
     //�����л���ʼ��-����
     m_ChainSetData.iSwitch_Jjtj=NORMAL_OPEN;//����ͣ��
     m_ChainSetData.iSwitch_htgwy=NORMAL_OPEN;//��̨��λ��
     m_ChainSetData.iSwitch_zdtgwy=NORMAL_OPEN;//��̨��λ��
     m_ChainSetData.iSwitch_htdyw=NORMAL_OPEN;//��̨��Һλ
     m_ChainSetData.iSwitch_htqy=NORMAL_OPEN;//��̨��е�ѹ
     m_ChainSetData.iSwitch_zdtgw=NORMAL_OPEN;//��̨����
     m_ChainSetData.iSwitch_ezgwy=NORMAL_OPEN;//�����λ��
     m_ChainSetData.iSwitch_gfrjbh=NORMAL_OPEN;//�����ȼ̱���
     m_ChainSetData.iSwitch_jyzcdy=NORMAL_OPEN;//��ѹ��е�ѹ
     m_ChainSetData.iSwitch_zgmenbh=NORMAL_OPEN;//������
     m_ChainSetData.iSwitch_htgw=NORMAL_OPEN;//�ӹ���
     m_ChainSetData.iSwitch_xtlqdy=NORMAL_OPEN;//ϵͳ��ȴ��Ԫ
     m_ChainSetData.iSwitch_htqyw=NORMAL_OPEN;//��������������
     m_ChainSetData.iSwitch_subzlqgw=NORMAL_OPEN;//�ӹ�����������
     m_ChainSetData.iSwitch_selfdefine1=NORMAL_OPEN;//�Զ���1
     m_ChainSetData.iSwitch_selfdefine2=NORMAL_OPEN;//�Զ���2
     m_ChainSetData.iSwitch_selfdefine3=NORMAL_OPEN;//�Զ���3
     m_ChainSetData.iSwitch_subyuliu=NORMAL_OPEN;//�ӹ�Ԥ��
    }
      m_iSwitchFlag[0]=m_ChainSetData.iJjtjVal;   //����ͣ��
      m_iSwitchFlag[1]=m_ChainSetData.iHtgwyVal;   //��̨��λ��
      m_iSwitchFlag[2]=m_ChainSetData.iZdtgwyVal;   //��̨��λ��
      m_iSwitchFlag[3]=m_ChainSetData.iHtdywVal;   //��̨��Һλ
      m_iSwitchFlag[4]=m_ChainSetData.iSelfdefineVal1;  //�Զ���1(���"��̨��ȴ")
      m_iSwitchFlag[5]=m_ChainSetData.iHtqyVal;   //��̨��е�ѹ
      m_iSwitchFlag[6]=m_ChainSetData.iZdtgwVal;   //��̨����
      m_iSwitchFlag[7]=m_ChainSetData.iEzgwyVal;   //�����λ��
      m_iSwitchFlag[8]=m_ChainSetData.iGfrjbhVal;   //�����ȼ̱���
      m_iSwitchFlag[9]=m_ChainSetData.iJyzcdyVal;   //��ѹ��е�ѹ
      m_iSwitchFlag[10]=m_ChainSetData.iZgMenbVal;  //�����ű���
      m_iSwitchFlag[11]=m_ChainSetData.iXtlqdyVal;  //ϵͳ��ȴ��Ԫ
      m_iSwitchFlag[12]=m_ChainSetData.iHtqywVal;  //���������Ź���,add by 2019.05.25
      m_iSwitchFlag[13]=m_ChainSetData.iSelfdefineVal2;  //�Զ���2,add by 2019.05.25
      m_iSwitchFlag[14]=m_ChainSetData.iSelfdefineVal3;  //�Զ���3,add by 2019.05.25
      m_iSwitchFlag[15]=m_ChainSetData.iSubyuliuPorcVal;  //�ӹ�Ԥ��������add by 2019.12.20
      m_iSwitchFlag[16]=m_ChainSetData.iSubzlqgwVal;  //�ӹ������Ź���,add by 2019.05.25
      m_iSwitchFlag[17]=m_ChainSetData.iSubMenbVal;  //�ӹ��ű���,add by 2019.05.25

     memcpy(&g_ChainSetData,&m_ChainSetData,sizeof(m_ChainSetData));//�����������ñ���g_ChainSetData��ʼ��,add by 2019.05.26
     //��̨��λ��-��ʾ-����
    showChainButton(HTGWY_INTERRUPT_MASK, m_pUi->toolButton_htgwy);
    //��̨��λ��-��ʾ-����
    showChainButton(ZDTGWY_INTERRUPT_MASK, m_pUi->toolButton_zdtgwy);
    //��̨��Һλ-��ʾ-����
//    showChainButton(HTDYW_INTERRUPT_MASK, m_pUi->toolButton_htdyw);
   //��̨��е�ѹ-��ʾ-����
    showChainButton(HTQY_INTERRUPT_MASK, m_pUi->toolButton_htqy);
    //��̨����-��ʾ-����
    showChainButton(ZDTGW_INTERRUPT_MASK, m_pUi->toolButton_zdtgw);
    //�����λ��-��ʾ-����
//    showChainButton(EZGWY_INTERRUPT_MASK, m_pUi->toolButton_ezgwy);
    //�����ȼ̱���-��ʾ-����
    showChainButton(GFRJBH_INTERRUPT_MASK, m_pUi->toolButton_gfrjbh);
    //��ѹ��е�ѹ-��ʾ-����
    showChainButton(JYZCDY_INTERRUPT_MASK,m_pUi->toolButton_jyzcdy);
    //�����ű���-��ʾ-����
    showChainButton(ZGMBH_INTERRUPT_MASK,m_pUi->toolButton_zgmenbh);
     //ϵͳ��ȴ��Ԫ-��ʾ-����
    showChainButton(XTLQDY_INTERRUPT_MASK,m_pUi->toolButton_xtlqdy);
    //�Զ���1-��ʾ-����,add by 2019.05.18
    showChainButton(SELFDEFINE1_INTERRUPT_MASK, m_pUi->toolButton_selfdefine1);
    //�Զ���2-��ʾ-����,add by 2019.05.18
    showChainButton(SELFDEFINE2_INTERRUPT_MASK,m_pUi->toolButton_selfdefine2);
    //�Զ���3-��ʾ-����,add by 2019.05.18
    showChainButton(SELFDEFINE3_INTERRUPT_MASK,m_pUi->toolButton_selfdefine3);
    //�ӹ��ű���-��ʾ-����,add by 2019.05.18
    showChainButton(SUBMBH_INTERRUPT_MASK,m_pUi->toolButton_htgw);
    //��������������-��ʾ-����,add by 2019.05.25
    showChainButton(HTQYW_INTERRUPT_MASK,m_pUi->toolButton_htqyw);
    //�ӹ�����������-��ʾ-����,add by 2019.05.25
//    showChainButton(SUBZLQGW_INTERRUPT_MASK,m_pUi->toolButton_subzlqgw);
    //�ӹ�Ԥ������-��ʾ-����,add by 2019.05.25
//    showChainButton(NULL_INTERRUPT_MASK,m_pUi->toolButton_subyuliu);

    //�����л�-��ʾ-����,add by 2020.11.24
    m_pUi->comboBox_htgwy->setCurrentIndex(m_ChainSetData.iSwitch_htgwy);
    m_pUi->comboBox_zdtgwy->setCurrentIndex(m_ChainSetData.iSwitch_zdtgwy);
//    m_pUi->comboBox_htdyw->setCurrentIndex(m_ChainSetData.iSwitch_htdyw);
    m_pUi->comboBox_htqy->setCurrentIndex(m_ChainSetData.iSwitch_htqy);
    m_pUi->comboBox_zdtgw->setCurrentIndex(m_ChainSetData.iSwitch_zdtgw);
//    m_pUi->comboBox_ezgwy->setCurrentIndex(m_ChainSetData.iSwitch_ezgwy);
    m_pUi->comboBox_gfrjbh->setCurrentIndex(m_ChainSetData.iSwitch_gfrjbh);
    m_pUi->comboBox_jyzcdy->setCurrentIndex(m_ChainSetData.iSwitch_jyzcdy);
    m_pUi->comboBox_zgmenbh->setCurrentIndex(m_ChainSetData.iSwitch_zgmenbh);
    m_pUi->comboBox_htgw->setCurrentIndex(m_ChainSetData.iSwitch_htgw);
    m_pUi->comboBox_xtlqdy->setCurrentIndex(m_ChainSetData.iSwitch_xtlqdy);
    m_pUi->comboBox_htqyw->setCurrentIndex(m_ChainSetData.iSwitch_htqyw);
//    m_pUi->comboBox_subzlqgw->setCurrentIndex(m_ChainSetData.iSwitch_subzlqgw);
    m_pUi->comboBox_selfdefine1->setCurrentIndex(m_ChainSetData.iSwitch_selfdefine1);
    m_pUi->comboBox_selfdefine2->setCurrentIndex(m_ChainSetData.iSwitch_selfdefine2);
    m_pUi->comboBox_selfdefine3->setCurrentIndex(m_ChainSetData.iSwitch_selfdefine3);
//    m_pUi->comboBox_subyuliu->setCurrentIndex(m_ChainSetData.iSwitch_subyuliu);
}
//���������л���ťֵ
void CChainsetdlg::setAllSwitchValue(int nValue)
{
    for(int i=0;i<24;i++)
    {
        if((i==0)||(i==1))
        {
            continue;//�����⼸����ֵ
        }
        m_iNewswFlag[i]=nValue;
    }
}
//���������л���ťͼ�꣬2019.05.25
void CChainsetdlg::setAllSwitchIcon(QIcon icon)
{
     m_pUi->toolButton_tongyi->setIcon(icon);       //ͳһ��ť,add by 2019.05.25
     m_pUi->toolButton_tongyi->setIconSize(QSize(66, 48));

     m_pUi->toolButton_xtlqdy->setIcon(icon);       //ϵͳ��ȴ��Ԫ
     m_pUi->toolButton_xtlqdy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_zdtgw->setIcon(icon);        //��̨����
     m_pUi->toolButton_zdtgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_zdtgwy->setIcon(icon);       //��̨��λ��
     m_pUi->toolButton_zdtgwy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_htgwy->setIcon(icon);        //��̨��λ��
     m_pUi->toolButton_htgwy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_htqy->setIcon(icon);       //��̨Ƿѹ
     m_pUi->toolButton_htqy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_htqyw->setIcon(icon);       //��̨ǷҺλ,add by 2019.05.25
     m_pUi->toolButton_htqyw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_htgw->setIcon(icon);       //��̨���£�add by 2019.05.25
     m_pUi->toolButton_htgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_gfrjbh->setIcon(icon);        //�����ȼ̱���,add by 2019.04.27
     m_pUi->toolButton_gfrjbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_jyzcdy->setIcon(icon);       //��ѹ��е�ѹ
     m_pUi->toolButton_jyzcdy->setIconSize(QSize(66, 48));
     m_pUi->toolButton_zgmenbh->setIcon(icon);      //�����ű���
     m_pUi->toolButton_zgmenbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_selfdefine1->setIcon(icon);  //�Զ���1
     m_pUi->toolButton_selfdefine1->setIconSize(QSize(66, 48));
     m_pUi->toolButton_selfdefine2->setIcon(icon);  //�Զ���2
     m_pUi->toolButton_selfdefine2->setIconSize(QSize(66, 48));
     m_pUi->toolButton_selfdefine3->setIcon(icon);  //�Զ���3
     m_pUi->toolButton_selfdefine3->setIconSize(QSize(66, 48));
     m_pUi->toolButton_selfdefine4->setIcon(icon);  //�Զ���4
     m_pUi->toolButton_selfdefine4->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c1zlqgw->setIcon(icon);  //�ӹ�1����������
     m_pUi->toolButton_c1zlqgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c2zlqgw->setIcon(icon);  //�ӹ�2����������
     m_pUi->toolButton_c2zlqgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c3zlqgw->setIcon(icon);  //�ӹ�3����������
     m_pUi->toolButton_c3zlqgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c4zlqgw->setIcon(icon);  //�ӹ�4����������
     m_pUi->toolButton_c4zlqgw->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c1cwbh->setIcon(icon);  //�ӹ�1����
     m_pUi->toolButton_c1cwbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c2cwbh->setIcon(icon);  //�ӹ�2����
     m_pUi->toolButton_c2cwbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c3cwbh->setIcon(icon);  //�ӹ�3����
     m_pUi->toolButton_c3cwbh->setIconSize(QSize(66, 48));
     m_pUi->toolButton_c4cwbh->setIcon(icon);  //�ӹ�4����
     m_pUi->toolButton_c4cwbh->setIconSize(QSize(66, 48));



//     m_pUi->toolButton_htdyw->setIcon(icon);        // ��̨��Һλ
//     m_pUi->toolButton_htdyw->setIconSize(QSize(66, 48));
//     m_pUi->toolButton_ezgwy->setIcon(icon);        //�����λ��
//     m_pUi->toolButton_ezgwy->setIconSize(QSize(66, 48));
//     m_pUi->toolButton_subzlqgw->setIcon(icon);       //�ӹ�����������,add by 2019.05.25
//     m_pUi->toolButton_subzlqgw->setIconSize(QSize(66, 48));
//     m_pUi->toolButton_subyuliu->setIcon(icon);    //�ӹ�Ԥ������
//     m_pUi->toolButton_subyuliu->setIconSize(QSize(66, 48));
}
//ͳһ��ť�ۺ���
void CChainsetdlg::tongyiSwitch_clicked()
{
    if(m_isTongyi)
    {
      m_pUi->toolButton_tongyi->setIcon(m_ybofficon);
      m_pUi->toolButton_tongyi->setIconSize(QSize(66, 48));
      m_isTongyi=false;
      setAllSwitchIcon(m_ybofficon);
      setAllSwitchValue(SWITCH_OFF);
    }
    else
    {
       m_pUi->toolButton_tongyi->setIcon(m_ybonicon);
       m_pUi->toolButton_tongyi->setIconSize(QSize(66, 48));
       m_isTongyi=true;
       setAllSwitchIcon(m_ybonicon);
       setAllSwitchValue(SWITCH_ON);
    }

}
//ͳһ��������-�ۺ���
void  CChainsetdlg::okBtn_clicked()
{
     //m_ChainSetData.iJjtjVal  = m_iSwitchFlag[0];   //����ͣ��
//     m_ChainSetData.iHtgwyVal = m_iSwitchFlag[1];   //��̨��λ��
//     m_ChainSetData.iZdtgwyVal= m_iSwitchFlag[2];   //��̨��λ��
//     m_ChainSetData.iHtdywVal = m_iSwitchFlag[3];   //��̨��Һλ
//     m_ChainSetData.iSelfdefineVal1= m_iSwitchFlag[4];  //�Զ���1(���"��̨��ȴ")
//     m_ChainSetData.iHtqyVal= m_iSwitchFlag[5];   //��̨��е�ѹ
//     m_ChainSetData.iZdtgwVal = m_iSwitchFlag[6];   //��̨����
//     m_ChainSetData.iEzgwyVal = m_iSwitchFlag[7];   //�����λ��
//     m_ChainSetData.iGfrjbhVal= m_iSwitchFlag[8];   //�����ȼ̱���
//     m_ChainSetData.iJyzcdyVal= m_iSwitchFlag[9];   //��ѹ��е�ѹ
//     m_ChainSetData.iZgMenbVal  = m_iSwitchFlag[10];  //�����ű���
//     m_ChainSetData.iXtlqdyVal= m_iSwitchFlag[11];  //ϵͳ��ȴ��Ԫ
//     m_ChainSetData.iHtqywVal= m_iSwitchFlag[12];  //���������Ź���,add by 2019.05.25
//     m_ChainSetData.iSelfdefineVal2= m_iSwitchFlag[13];  //�Զ���2,add by 2019.05.25
//     m_ChainSetData.iSelfdefineVal3= m_iSwitchFlag[14];  //�Զ���3,add by 2019.05.25
//     m_ChainSetData.iSubyuliuPorcVal= m_iSwitchFlag[15];  //�ӹ�Ԥ��������add by 2019.12.20
//     m_ChainSetData.iSubzlqgwVal= m_iSwitchFlag[16];  //�ӹ������Ź���,add by 2019.05.25
//     m_ChainSetData.iSubMenbVal= m_iSwitchFlag[17];  //�ӹ��ű���,add by 2019.05.25
//    if(m_IniChainset.writeChainsetInifile(m_ChainSetData))
//    {
//       memcpy(&g_ChainSetData,&m_ChainSetData,sizeof(m_ChainSetData));//���������������ò�����ȫ�ֱ���g_ChainSetData,add by 2019.12.19
//       QMessageBox::warning(this,
//                      tr(m_strFriendlytips),
//                      tr(m_strAllSuccess));//�������������ļ�����ɹ�
//   }
//   else
//   {
//       QMessageBox::warning(this,
//                      tr(m_strFriendlytips),
//                      tr(m_strAllFailure));//�������������ļ�����ʧ��,����
//    }

//     m_newChaSetData.iJjtjVal = m_iNewswFlag[0];           //����ͣ��
//     m_newChaSetData.iSJitiVal = m_iNewswFlag[1];          //S����ͣ��
     m_newChaSetData.iXtlqVal = m_iNewswFlag[2];           //ϵͳ��ȴ
     m_newChaSetData.iZdtgwVal = m_iNewswFlag[3];          //��̨����
     m_newChaSetData.iZdtgwyVal = m_iNewswFlag[4];         //��̨��λ��
     m_newChaSetData.iHtgwyVal = m_iNewswFlag[5];          //��̨��λ��
     m_newChaSetData.iHtqyVal = m_iNewswFlag[6];           //��̨Ƿѹ
     m_newChaSetData.iHtqywVal = m_iNewswFlag[7];          //��̨ǷҺλ
     m_newChaSetData.iHtgwVal = m_iNewswFlag[8];           //��̨����
     m_newChaSetData.iGfrjbhVal = m_iNewswFlag[9];         //�����ȼ̱���
     m_newChaSetData.iJyzcdyVal = m_iNewswFlag[10];        //��ѹ��е�ѹ
     m_newChaSetData.iZgmbhVal = m_iNewswFlag[11];         //�����ű���
     m_newChaSetData.iSelfdefVal1 = m_iNewswFlag[12];      //�Զ���1
     m_newChaSetData.iSelfdefVal2 = m_iNewswFlag[13];      //�Զ���2
     m_newChaSetData.iSelfdefVal3 = m_iNewswFlag[14];      //�Զ���3
     m_newChaSetData.iSelfdefVal4 = m_iNewswFlag[15];      //�Զ���4
     m_newChaSetData.iC1zlqgwVal = m_iNewswFlag[16];       //�ӹ�1����������
     m_newChaSetData.iC2zlqgwVal = m_iNewswFlag[17];       //�ӹ�2����������
     m_newChaSetData.iC3zlqgwVal = m_iNewswFlag[18];       //�ӹ�3����������
     m_newChaSetData.iC4zlqgwVal = m_iNewswFlag[19];       //�ӹ�4����������
     m_newChaSetData.iC1cwbhVal = m_iNewswFlag[20];        //�ӹ�1���󱣻�
     m_newChaSetData.iC2cwbhVal = m_iNewswFlag[21];        //�ӹ�2���󱣻�
     m_newChaSetData.iC3cwbhVal = m_iNewswFlag[22];        //�ӹ�3���󱣻�
     m_newChaSetData.iC4cwbhVal = m_iNewswFlag[23];        //�ӹ�4���󱣻�


     if(m_IniChainset.writenewChainsetInifile(m_newChaSetData))
     {
        memcpy(&g_newchasetdata,&m_newChaSetData,sizeof(m_newChaSetData));//���������������ò�����ȫ�ֱ���g_newchasetdata,add by zw 2022.02.23
        printf("####CChainsetdlg::okBtn_clicked()####g_newchasetdata.iC4zlqgwVal=%d\n",g_newchasetdata.iC4zlqgwVal);
        QMessageBox::warning(this,
                       tr(m_strFriendlytips),
                       tr(m_strAllSuccess));//�������������ļ�����ɹ�
    }
    else
    {
        QMessageBox::warning(this,
                       tr(m_strFriendlytips),
                       tr(m_strAllFailure));//�������������ļ�����ʧ��,����
     }

    this->close();

}

//��̨��λ��2-������������-�ۺ���
void  CChainsetdlg::htgwysetBtn_clicked()
{
   m_ChainSetData.iHtgwyVal=m_iSwitchFlag[1];
   printf("####CChainsetdlg::htgwysetBtn_clicked()####m_ChainSetData.iHtgwyVal=%d\n",m_ChainSetData.iHtgwyVal);
   QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(0)));
}
//��̨��λ��-������������-�ۺ���
void  CChainsetdlg::zdtgwysetBtn_clicked()
{
    m_ChainSetData.iZdtgwyVal=m_iSwitchFlag[2];
    printf("####CChainsetdlg::zdtgwysetBtn_clicked()####m_ChainSetData.iZdtgwyVal=%d\n",m_ChainSetData.iZdtgwyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(1)));
}
// ��̨��Һλ-������������-�ۺ���
void  CChainsetdlg::htdywsetBtn_clicked()
{
    m_ChainSetData.iHtdywVal=m_iSwitchFlag[3];
    printf("####CChainsetdlg::htdywsetBtn_clicked()####m_ChainSetData.iHtdywVal=%d\n",m_ChainSetData.iHtdywVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(2)));
}
//��̨��е�ѹ-������������-�ۺ���
void  CChainsetdlg::htqysetBtn_clicked()
{
    m_ChainSetData.iHtqyVal=m_iSwitchFlag[5];
    printf("####CChainsetdlg::htqysetBtn_clicked()####m_ChainSetData.iHtqyVal=%d\n",m_ChainSetData.iHtqyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(3)));
}
//��̨����-������������-�ۺ���
void  CChainsetdlg::zdtgwsetBtn_clicked()
{
    m_ChainSetData.iZdtgwVal=m_iSwitchFlag[6];
    printf("####CChainsetdlg::zdtgwsetBtn_clicked()####m_ChainSetData.iZdtgwVal=%d\n",m_ChainSetData.iZdtgwVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(4)));
}
//�����λ��-������������-�ۺ���
void  CChainsetdlg::ezgwysetBtn_clicked()
{
    m_ChainSetData.iEzgwyVal=m_iSwitchFlag[7];
    printf("####CChainsetdlg::ezgwysetBtn_clicked()####m_ChainSetData.iEzgwyVal=%d\n",m_ChainSetData.iEzgwyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(5)));
}
//�����ȼ̱���-������������-�ۺ���
void  CChainsetdlg::gfrjbhsetBtn_clicked()
{
    m_ChainSetData.iGfrjbhVal=m_iSwitchFlag[8];
    printf("####CChainsetdlg::gfrjbhsetBtn_clicked####m_ChainSetData.iGfrjbhVal=%d\n",m_ChainSetData.iGfrjbhVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(6)));
}
//��ѹ��е�ѹ-������������-�ۺ���
void  CChainsetdlg::jyzcdysetBtn_clicked()
{
    m_ChainSetData.iJyzcdyVal=m_iSwitchFlag[9];
    printf("####CChainsetdlg::jyzcdysetBtn_clicked()####m_ChainSetData.iJyzcdyVal=%d\n",m_ChainSetData.iJyzcdyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(9)));
}
 //�����ű���-������������-�ۺ���
void  CChainsetdlg::zgmenbhsetBtn_clicked()
{
    m_ChainSetData.iZgMenbVal=m_iSwitchFlag[10];
    printf("####CChainsetdlg::zgmenbhsetBtn_clicked()####m_ChainSetData.iZgMenbVal=%d\n",m_ChainSetData.iZgMenbVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(10)));
}
 //ϵͳ��ȴ��Ԫ-������������-�ۺ���
void  CChainsetdlg::xtlqdysetBtn_clicked()
{
    m_ChainSetData.iXtlqdyVal=m_iSwitchFlag[11];
    printf("####CChainsetdlg::xtlqdysetBtn_clicked()####m_ChainSetData.iXtlqdyVal=%d\n",m_ChainSetData.iXtlqdyVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(13)));
}
//�Զ���1-������������-�ۺ���,add by 2019.05.25
void CChainsetdlg::selfdefine1setBtn_clicked()
{
    m_ChainSetData.iSelfdefineVal1=m_iSwitchFlag[4];
    printf("####CChainsetdlg::selfdefine1setBtn_clicked()####m_ChainSetData.iSelfdefineVal1=%d\n",m_ChainSetData.iSelfdefineVal1);
    /*QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(4)));*/
}
//�Զ���2-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::selfdefine2setBtn_clicked()
{
}
//�Զ���3-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::selfdefine3setBtn_clicked()
{
}

//�ӹ������Ź���-������������-�ۺ���,add by 2019.05.25
void  CChainsetdlg::subzlqgwsetBtn_clicked()
{
    m_ChainSetData.iSubzlqgwVal=m_iSwitchFlag[16];
    printf("####CChainsetdlg::subzlqgwsetBtn_clicked()####m_ChainSetData.iSubzlqgwVal=%d\n",m_ChainSetData.iSubzlqgwVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(11)));

}
//�ӹ��ű���-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::htgwsetBtn_clicked()
{
    m_ChainSetData.iSubMenbVal=m_iSwitchFlag[17];
    printf("####CChainsetdlg::htgwsetBtn_clicked()####m_ChainSetData.iSubMenbVal=%d\n",m_ChainSetData.iSubMenbVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(12)));
}
//���������Ź���-������������-�ۺ���,add by 2019.05.25
void CChainsetdlg::htqywsetBtn_clicked()
{
    m_ChainSetData.iHtqywVal=m_iSwitchFlag[12];
    printf("####CChainsetdlg::zdtlqsetBtn_clicked()####m_ChainSetData.iHtqywVal=%d\n",m_ChainSetData.iHtqywVal);
    QMessageBox::information(this,
            tr(m_strFriendlytips),
            tr(m_strListSuccess.at(10)));

}
//�ӹ�Ԥ������-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::subyuliubhsetBtn_clicked()
{

}
//�������ð�ťʹ��
void  CChainsetdlg::allSetBtnEnable(bool enable)
{
}
//ϵͳ��ȴ��Ԫ-�л�-�ۺ���
void  CChainsetdlg::xtlqdySwitch_clicked()
{
   refreshChainButton(XTLQ_MASK,m_pUi->toolButton_xtlqdy);
}
//��̨����-�л�-�ۺ���
void  CChainsetdlg::zdtgwSwitch_clicked()
{
    refreshChainButton(ZDTGW_MASK, m_pUi->toolButton_zdtgw);
}
//��̨��λ��-�л�-�ۺ���
void  CChainsetdlg::zdtgwySwitch_clicked()
{
    refreshChainButton(ZDTGWY_MASK, m_pUi->toolButton_zdtgwy);
}
//��̨��λ��-�л�-�ۺ���
void  CChainsetdlg::htgwySwitch_clicked()
{
    refreshChainButton(HTGWY_MASK, m_pUi->toolButton_htgwy);
}
//��̨Ƿѹ-�л�-�ۺ���
void  CChainsetdlg::htqySwitch_clicked()
{
    refreshChainButton(HTQY_MASK, m_pUi->toolButton_htqy);
}
//��̨ǷҺλ-�л�-�ۺ���
void CChainsetdlg::htqywSwitch_clicked()
{
    refreshChainButton(HTQYW_MASK,m_pUi->toolButton_htqyw);
}
//��̨����-�л�-�ۺ���
void CChainsetdlg::htgwSwitch_clicked()
{
    refreshChainButton(HTGW_MASK,m_pUi->toolButton_htgw);
}
//�����ȼ̱���-�л�-�ۺ���
void  CChainsetdlg::gfrhbhSwitch_clicked()
{
    refreshChainButton(GFRJBH_MASK, m_pUi->toolButton_gfrjbh);
}
//��ѹ��е�ѹ-�л�-�ۺ���
void  CChainsetdlg::jyzcdySwitch_clicked()
{
    refreshChainButton(JYZCDY_MASK,m_pUi->toolButton_jyzcdy);
}
//�����ű���-�л�-�ۺ���
void  CChainsetdlg::zgmenbhSwitch_clicked()
{
   refreshChainButton(ZGMBH_MASK,m_pUi->toolButton_zgmenbh);
}
//�Զ���1-�л�-�ۺ���,add by 2019.05.18
void  CChainsetdlg::selfdefine1Switch_clicked()
{
    refreshChainButton(ZDY1_MASK, m_pUi->toolButton_selfdefine1);
}
//�Զ���2-�л�-�ۺ���,add by 2019.05.18
void CChainsetdlg::selfdefine2Switch_clicked()
{
    refreshChainButton(ZDY2_MASK,m_pUi->toolButton_selfdefine2);
}
//�Զ���3-�л�-�ۺ���,add by 2019.05.18
void CChainsetdlg::selfdefine3Switch_clicked()
{
    refreshChainButton(ZDY3_MASK,m_pUi->toolButton_selfdefine3);
}
//�Զ���4-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::selfdefine4Switch_clicked()
{
    refreshChainButton(ZDY4_MASK,m_pUi->toolButton_selfdefine4);
}
//�ӹ�1����������-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::c1zlqgwSwitch_clicked()
{
    refreshChainButton(CG1ZLQGW_MASK,m_pUi->toolButton_c1zlqgw);
}
//�ӹ�2����������-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::c2zlqgwSwitch_clicked()
{
    refreshChainButton(CG2ZLQGW_MASK,m_pUi->toolButton_c2zlqgw);
}
//�ӹ�3����������-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::c3zlqgwSwitch_clicked()
{
    refreshChainButton(CG3ZLQGW_MASK,m_pUi->toolButton_c3zlqgw);
}
//�ӹ�4����������-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::c4zlqgwSwitch_clicked()
{
    refreshChainButton(CG4ZLQGW_MASK,m_pUi->toolButton_c4zlqgw);
}
//�ӹ�1���󱣻�-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::c1cwbhSwitch_clicked()
{
    refreshChainButton(CG1CWBH_MASK,m_pUi->toolButton_c1cwbh);
}
//�ӹ�2���󱣻�-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::c2cwbhSwitch_clicked()
{
    refreshChainButton(CG2CWBH_MASK,m_pUi->toolButton_c2cwbh);
}
//�ӹ�3���󱣻�-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::c3cwbhSwitch_clicked()
{
    refreshChainButton(CG3CWBH_MASK,m_pUi->toolButton_c3cwbh);
}
//�ӹ�4���󱣻�-������������-�ۺ���,add by 2019.05.18
void CChainsetdlg::c4cwbhSwitch_clicked()
{
    refreshChainButton(CG4CWBH_MASK,m_pUi->toolButton_c4cwbh);
}
//�ӹ�Ԥ������-�л�-�ۺ���,add by 2019.05.18
void  CChainsetdlg::subyuliuSwitch_clicked()
{
}
//��̨��Һλ-�л�-�ۺ���
void  CChainsetdlg::htdywSwitch_clicked()
{
//    refreshChainButton(HTDYW_INTERRUPT_MASK, m_pUi->toolButton_htdyw);
}


//�����λ��-�л�-�ۺ���
void  CChainsetdlg::ezgwySwitch_clicked()
{
//    refreshChainButton(EZGWY_INTERRUPT_MASK, m_pUi->toolButton_ezgwy);
}






//�ӹ�����������-�л�-�ۺ���,add by 2019.05.25
void CChainsetdlg::subzlqgwSwitch_clicked()
{
//    refreshChainButton(SUBZLQGW_INTERRUPT_MASK,m_pUi->toolButton_subzlqgw);
}
//ˢ��������ť״̬
void  CChainsetdlg::refreshChainButton(int nIndex,QToolButton *toolButton)
{
//    if(m_iSwitchFlag[nIndex]==1)
//    {
//     toolButton->setIcon(m_ybofficon);
//     toolButton->setIconSize(QSize(66, 48));
//     m_iSwitchFlag[nIndex]=0;
//    }
//    else
//    {
//      toolButton->setIcon(m_ybonicon);
//      toolButton->setIconSize(QSize(66, 48));
//      m_iSwitchFlag[nIndex]=1;
//    }
    if(m_iNewswFlag[nIndex]==1)
    {
     toolButton->setIcon(m_ybofficon);
     toolButton->setIconSize(QSize(66, 48));
     m_iNewswFlag[nIndex]=0;
    }
    else
    {
      toolButton->setIcon(m_ybonicon);
      toolButton->setIconSize(QSize(66, 48));
      m_iNewswFlag[nIndex]=1;
    }
//     m_iChainsetval=m_Gpiorw.ai_data_compute(m_iSwitchFlag);
     switch (nIndex) {
     case 4:
         m_iChainsetval = g_newfaultstatus.iVIBODFlag;
         break;
     case 2:
         m_iChainsetval = g_newfaultstatus.iVIBCUFlag;
         break;
     case 3:
         m_iChainsetval = g_newfaultstatus.iVIBOTFlag;
         break;
     case 5:
         m_iChainsetval = g_newfaultstatus.iSTODFlag;
         break;
     case 6:
         m_iChainsetval = g_newfaultstatus.iSTUPFlag;
         break;
     case 8:
         m_iChainsetval = g_newfaultstatus.iSTOTFlag;
         break;
     case 7:
         m_iChainsetval = g_newfaultstatus.iSTOLFlag;
         break;
     case 9:
         m_iChainsetval = g_newfaultstatus.iRELAYFlag;
         break;
     case 11:
         m_iChainsetval = g_newfaultstatus.iDOORFlag;
         break;
     case 10:
         m_iChainsetval = g_newfaultstatus.iHBUPFlag;
         break;
     case 12:
         m_iChainsetval = g_newfaultstatus.iEXT1Flag;
         break;
     case 13:
         m_iChainsetval = g_newfaultstatus.iEXT2Flag;
         break;
     case 14:
         m_iChainsetval = g_newfaultstatus.iEXT3Flag;
         break;
     case 15:
         m_iChainsetval = g_newfaultstatus.iEXT4Flag;
         break;
     case 0:
         m_iChainsetval = g_newfaultstatus.iESTOPFlag;
         break;
     case 16:
         m_iChainsetval = g_newfaultstatus.iOT1Flag;
         break;
     case 17:
         m_iChainsetval = g_newfaultstatus.iOT2Flag;
         break;
     case 18:
         m_iChainsetval = g_newfaultstatus.iOT3Flag;
         break;
     case 19:
         m_iChainsetval = g_newfaultstatus.iOT4Flag;
         break;
     case 1:
         m_iChainsetval = g_newfaultstatus.iSESTOPFlag;
         break;
     case 20:
         m_iChainsetval = g_newfaultstatus.iFAULT1Flag;
         break;
     case 21:
         m_iChainsetval = g_newfaultstatus.iFAULT2Flag;
         break;
     case 22:
         m_iChainsetval = g_newfaultstatus.iFAULT3Flag;
         break;
     case 23:
         m_iChainsetval = g_newfaultstatus.iFAULT4Flag;
         break;
     default:
         break;
     }
     printf("####nIndex=%d,m_iChainsetval=%d####\n",nIndex,m_iChainsetval);
}
void  CChainsetdlg::showChainButton(int nIndex,QToolButton *toolButton)
{
    if(m_iNewswFlag[nIndex]==1)
    {
     toolButton->setIcon(m_ybonicon);
     toolButton->setIconSize(QSize(66, 48));
    }
    else
    {
      toolButton->setIcon(m_ybofficon);
      toolButton->setIconSize(QSize(66, 48));
    }
}
//��ȡ������������
STRU_CHAINSETDATA CChainsetdlg::getChainSetData()
{
    return m_ChainSetData;
}
void CChainsetdlg::chainLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("chainsetDialog", "\350\277\236\351\224\201\345\261\217\350\224\275\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_12->setText(QApplication::translate("chainsetDialog", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
        m_pUi->label_13->setText(QApplication::translate("chainsetDialog", "\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        m_pUi->normalBtn->setText(QApplication::translate("chainsetDialog", "\346\255\243\345\270\270", 0, QApplication::UnicodeUTF8));
        m_pUi->debugBtn->setText(QApplication::translate("chainsetDialog", "\350\260\203\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pUi->okBtn->setText(QApplication::translate("chainsetDialog", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        m_pUi->label_14->setText(QApplication::translate("chainsetDialog", "\347\263\273\347\273\237\345\206\267\345\215\264\345\215\225\345\205\203", 0, QApplication::UnicodeUTF8));
        //m_pUi->xtlqdysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_7->setText(QApplication::translate("chainsetDialog", "\346\214\257\345\212\250\345\217\260\350\277\207\346\270\251", 0, QApplication::UnicodeUTF8));
        //m_pUi->zdtgwsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_2->setText(QApplication::translate("chainsetDialog", "\346\273\221\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        //m_pUi->htgwysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_8->setText(QApplication::translate("chainsetDialog", "\350\200\263\350\275\264\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        //m_pUi->ezgwysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_3->setText(QApplication::translate("chainsetDialog", "\346\214\257\345\212\250\345\217\260\350\277\207\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        //m_pUi->zdtgwysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_10->setText(QApplication::translate("chainsetDialog", "\351\235\231\345\216\213\350\275\264\346\211\277\344\275\216\345\216\213", 0, QApplication::UnicodeUTF8));
        //m_pUi->jyzcdysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
//        m_pUi->label_4->setText(QApplication::translate("chainsetDialog", " \346\273\221\345\217\260\344\275\216\346\266\262\344\275\215", 0, QApplication::UnicodeUTF8));
        //m_pUi->htdywsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_21->setText(QApplication::translate("chainsetDialog", "\344\273\216\346\237\234\351\227\250\344\277\235\346\212\244      ", 0, QApplication::UnicodeUTF8));
        //m_pUi->htgwsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_6->setText(QApplication::translate("chainsetDialog", "\346\273\221\345\217\260\350\275\264\346\211\277\344\275\216\345\216\213", 0, QApplication::UnicodeUTF8));
        //m_pUi->htqysetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_15->setText(QApplication::translate("chainsetDialog", "\350\207\252\345\256\232\344\271\2111", 0, QApplication::UnicodeUTF8));
        //m_pUi->selfdefine1setBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_9->setText(QApplication::translate("chainsetDialog", "\345\212\237\346\224\276\347\203\255\347\273\247\344\277\235\346\212\244", 0, QApplication::UnicodeUTF8));
        //m_pUi->gfrjbhsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_16->setText(QApplication::translate("chainsetDialog", "\350\207\252\345\256\232\344\271\2112", 0, QApplication::UnicodeUTF8));
        //m_pUi->selfdefine2setBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
//        m_pUi->label_18->setText(QApplication::translate("chainsetDialog", "\344\270\273\346\237\234\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251   ", 0, QApplication::UnicodeUTF8));
        //m_pUi->htqywsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_17->setText(QApplication::translate("chainsetDialog", "\350\207\252\345\256\232\344\271\2113", 0, QApplication::UnicodeUTF8));
        //m_pUi->selfdefine3setBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
//        m_pUi->label_20->setText(QApplication::translate("chainsetDialog", "\344\273\216\346\237\234\346\225\264\346\265\201\345\231\250\350\277\207\346\270\251  ", 0, QApplication::UnicodeUTF8));
        //m_pUi->subzlqgwsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
//        m_pUi->label_19->setText(QApplication::translate("chainsetDialog", "\344\273\216\346\237\234\351\242\204\347\225\231\344\277\235\346\212\244   ", 0, QApplication::UnicodeUTF8));
        //m_pUi->subyuliubhsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_11->setText(QApplication::translate("chainsetDialog", "\344\270\273\346\237\234\351\227\250\344\277\235\346\212\244      ", 0, QApplication::UnicodeUTF8));
        //m_pUi->zgmenbhsetBtn->setText(QApplication::translate("chainsetDialog", "\350\256\276 \347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUi->label_26->setText(QApplication::translate("chainsetDialog", "\350\201\224\351\224\201\345\261\217\350\224\275", 0, QApplication::UnicodeUTF8));//add by 2020.09.01
        m_pUi->label_27->setText(QApplication::translate("chainsetDialog","\350\201\224\351\224\201\345\261\217\350\224\275", 0, QApplication::UnicodeUTF8));//add by 2020.09.01
        m_pUi->label_28->setText(QApplication::translate("chainsetDialog", "\350\247\246\347\202\271\345\210\207\346\215\242", 0, QApplication::UnicodeUTF8));//add by 2020.09.01
        m_pUi->label_29->setText(QApplication::translate("chainsetDialog", "\350\247\246\347\202\271\345\210\207\346\215\242", 0, QApplication::UnicodeUTF8));//add by 2020.09.01

        m_strFriendlytips=QApplication::translate("chainsetDialog",
        "\345\217\213\346\203\205\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//������ʾ

     m_strAllSuccess=QApplication::translate("chainsetDialog",
         "\346\211\200\346\234\211\350\277\236\351\224\201\350\256\276\347\275\256\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);   //�����������óɹ�

     m_strAllFailure=QApplication::translate("chainsetDialog",
         "\346\211\200\346\234\211\350\277\236\351\224\201\350\256\276\347\275\256\345\244\261\350\264\245",
         0, QApplication::UnicodeUTF8); //������������ʧ��
    }
    else
    {
        setWindowTitle("Interlock");
        m_pUi->label_12->setText("All");
        m_pUi->label_13->setText("Mode");
        m_pUi->normalBtn->setText("Normal");
        m_pUi->debugBtn->setText("Debug");
        m_pUi->okBtn->setText("OK");
        m_pUi->label_14->setText("S.C.U.");
        //m_pUi->xtlqdysetBtn->setText("Set");
        m_pUi->label_7->setText("VIB. OverTEMP");
        //m_pUi->zdtgwsetBtn->setText("Set");
        m_pUi->label_2->setText("S.T. Overtravel");
        //m_pUi->htgwysetBtn->setText("Set");
        m_pUi->label_8->setText("TRUN. O/T");
        //m_pUi->ezgwysetBtn->setText("Set");
        m_pUi->label_3->setText("VIB. Overtravel");
        //m_pUi->zdtgwysetBtn->setText("Set");
        m_pUi->label_10->setText("VIB. U/P");
        //m_pUi->jyzcdysetBtn->setText("Set");
//        m_pUi->label_4->setText("S.T. U/L");
        //m_pUi->htdywsetBtn->setText("Set");
        m_pUi->label_21->setText("Cab Doors");
        //m_pUi->htgwsetBtn->setText("Set");
        m_pUi->label_6->setText("S.T. U/P");
        //m_pUi->htqysetBtn->setText("Set");
        m_pUi->label_15->setText("External1");
        //m_pUi->selfdefine1setBtn->setText("Set");
        m_pUi->label_9->setText("Relay O/L");
        //m_pUi->gfrjbhsetBtn->setText("Set");
        m_pUi->label_16->setText("External2");
        //m_pUi->selfdefine2setBtn->setText("Set");
//        m_pUi->label_18->setText("M.R. OverTEMP");
        //m_pUi->htqywsetBtn->setText("Set");
        m_pUi->label_17->setText("External3");
        //m_pUi->selfdefine3setBtn->setText("Set");
//        m_pUi->label_20->setText("C.R. OverTEMP");
        //m_pUi->subzlqgwsetBtn->setText("Set");
//        m_pUi->label_19->setText("Cab Reserved");
        //m_pUi->subyuliubhsetBtn->setText("Set");
        m_pUi->label_11->setText("Main Doors");
        //m_pUi->zgmenbhsetBtn->setText("Set");

        m_pUi->label_26->setText("Interlock Shield");//add by 2020.09.01
        m_pUi->label_27->setText("Interlock Shield");//add by 2020.09.01
        m_pUi->label_28->setText("Contact Switch");//add by 2020.09.01
        m_pUi->label_29->setText("Contact Switch");//add by 2020.09.01

        m_strFriendlytips="Friendly tips";//������ʾ

        m_strAllSuccess="Interlock set successfully";   //�����������óɹ�

        m_strAllFailure="Interlock setting failed";    //������������ʧ��
    }
}
//���ؼ��ۺ���ʵ�� add by 2020.08.10@@@
void CChainsetdlg::closeBtn_clicked()
{
    this->close();
}

//ϵͳ��ȴ��Ԫ���������л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_xtlqdy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Xtlq=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Xtlq=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Xtlq=NORMAL_OPEN;
        break;
    }
    printf("isw_Xtlq = %d",index,m_newChaSetData.isw_Xtlq);
}
//��̨���´����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_zdtgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Zdtgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Zdtgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Zdtgw=NORMAL_OPEN;
        break;
    }
    printf("isw_Zdtgw = %d",index,m_newChaSetData.isw_Zdtgw);
}
//��̨��λ�ƴ����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_zdtgwy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Zdtgwy=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Zdtgwy=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Zdtgwy=NORMAL_OPEN;
        break;
    }
    printf("isw_Zdtgwy = %d",index,m_newChaSetData.isw_Zdtgwy);
}
//��̨��λ�ƴ����л��ۺ���ʵ�� add by 2020.09.05
void CChainsetdlg::comboBox_htgwy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Htgwy=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Htgwy=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Htgwy=NORMAL_OPEN;
        break;
    }
    printf("isw_Htgwy = %d",index,m_newChaSetData.isw_Htgwy);
}
//��̨Ƿѹ�����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_htqy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Htqy=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Htqy=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Htqy=NORMAL_OPEN;
        break;
    }
    printf("isw_Htqy = %d",index,m_newChaSetData.isw_Htqy);
}
//��̨ǷҺλ�����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_htqyw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Htqyw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Htqyw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Htqyw=NORMAL_OPEN;
        break;
    }
    printf("isw_Htqyw = %d",index,m_newChaSetData.isw_Htqyw);
}
//��̨���´����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_htgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Htgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Htgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Htgw=NORMAL_OPEN;
        break;
    }
    printf("isw_Htgw = %d",index,m_newChaSetData.isw_Htgw);
}
//�����ȼ̱��������л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_gfrjbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Gfrjbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Gfrjbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Gfrjbh=NORMAL_OPEN;
        break;
    }
    printf("isw_Gfrjbh = %d",index,m_newChaSetData.isw_Gfrjbh);
}
//��ѹ��е�ѹ�����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_jyzcdy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Jyzcdy=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Jyzcdy=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Jyzcdy=NORMAL_OPEN;
        break;
    }
    printf("isw_Jyzcdy = %d",index,m_newChaSetData.isw_Jyzcdy);
}
//�����ű��������л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_zgmenbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Zgmbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Zgmbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Zgmbh=NORMAL_OPEN;
        break;
    }
    printf("isw_Zgmbh = %d",index,m_newChaSetData.isw_Zgmbh);
}
//�Զ���1���������л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_selfdefine1_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Selfdef1=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Selfdef1=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Selfdef1=NORMAL_OPEN;
        break;
    }
    printf("isw_Selfdef1 = %d",index,m_newChaSetData.isw_Selfdef1);
}
//�Զ���2���������л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_selfdefine2_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Selfdef2=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Selfdef2=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Selfdef2=NORMAL_OPEN;
        break;
    }
    printf("isw_Selfdef2 = %d",index,m_newChaSetData.isw_Selfdef2);
}
//�Զ���3���������л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_selfdefine3_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Selfdef3=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Selfdef3=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Selfdef3=NORMAL_OPEN;
        break;
    }
    printf("isw_Selfdef3 = %d",index,m_newChaSetData.isw_Selfdef3);
}
//�Զ���4���������л��ۺ���ʵ�� add by zw 2022.02.23
void CChainsetdlg::comboBox_selfdefine4_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_Selfdef4=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_Selfdef4=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_Selfdef4=NORMAL_OPEN;
        break;
    }
    printf("isw_Selfdef4 = %d",index,m_newChaSetData.isw_Selfdef4);
}
//�ӹ�1���������´����л��ۺ��� add by zw 2022.02.23
void CChainsetdlg::comboBox_c1zlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C1zlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C1zlqgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C1zlqgw=NORMAL_OPEN;
        break;
    }
    printf("isw_C1zlqgw = %d",index,m_newChaSetData.isw_C1zlqgw);
}
//�ӹ�2���������´����л��ۺ��� add by zw 2022.02.23
void CChainsetdlg::comboBox_c2zlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C2zlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C2zlqgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C2zlqgw=NORMAL_OPEN;
        break;
    }
    printf("isw_C2zlqgw = %d",index,m_newChaSetData.isw_C2zlqgw);
}
//�ӹ�3���������´����л��ۺ��� add by zw 2022.02.23
void CChainsetdlg::comboBox_c3zlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C3zlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C3zlqgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C3zlqgw=NORMAL_OPEN;
        break;
    }
    printf("isw_C3zlqgw = %d",index,m_newChaSetData.isw_C3zlqgw);
}
//�ӹ�4���������´����л��ۺ��� add by zw 2022.02.23
void CChainsetdlg::comboBox_c4zlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C4zlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C4zlqgw=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C4zlqgw=NORMAL_OPEN;
        break;
    }
    printf("isw_C4zlqgw = %d",index,m_newChaSetData.isw_C4zlqgw);
}
//�ӹ�1�����źŴ����л��ۺ��� add by zw 2022.02.23
void CChainsetdlg::comboBox_c1cwbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C1cwbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C1cwbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C1cwbh=NORMAL_OPEN;
        break;
    }
    printf("isw_C1cwbh = %d",index,m_newChaSetData.isw_C1cwbh);
}
//�ӹ�2�����źŴ����л��ۺ��� add by zw 2022.02.23
void CChainsetdlg::comboBox_c2cwbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C2cwbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C2cwbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C2cwbh=NORMAL_OPEN;
        break;
    }
    printf("isw_C2cwbh = %d",index,m_newChaSetData.isw_C2cwbh);
}
//�ӹ�3�����źŴ����л��ۺ��� add by zw 2022.02.23
void CChainsetdlg::comboBox_c3cwbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C3cwbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C3cwbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C3cwbh=NORMAL_OPEN;
        break;
    }
    printf("isw_C3cwbh = %d",index,m_newChaSetData.isw_C3cwbh);
}
//�ӹ�4�����źŴ����л��ۺ��� add by zw 2022.02.23
void CChainsetdlg::comboBox_c4cwbh_activated(int index)
{
    switch(index)
    {
    case 0:
        m_newChaSetData.isw_C4cwbh=NORMAL_OPEN;
        break;
    case 1:
        m_newChaSetData.isw_C4cwbh=NORMAL_CLOSE;
        break;
    default:
        m_newChaSetData.isw_C4cwbh=NORMAL_OPEN;
        break;
    }
    printf("isw_C4cwbh = %d",index,m_newChaSetData.isw_C4cwbh);
}

//��̨��Һλ�����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_htdyw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_ChainSetData.iSwitch_htdyw=NORMAL_OPEN;
        break;
    case 1:
        m_ChainSetData.iSwitch_htdyw=NORMAL_CLOSE;
        break;
    default:
        m_ChainSetData.iSwitch_htdyw=NORMAL_OPEN;
        break;
    }
    printf("isw_Xtlq = %d",index,m_newChaSetData.isw_Xtlq);
}



//�ӹ����������´����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_subzlqgw_activated(int index)
{
    switch(index)
    {
    case 0:
        m_ChainSetData.iSwitch_subzlqgw=NORMAL_OPEN;
        break;
    case 1:
        m_ChainSetData.iSwitch_subzlqgw=NORMAL_CLOSE;
        break;
    default:
        m_ChainSetData.iSwitch_subzlqgw=NORMAL_OPEN;
        break;
    }

}


//�����λ�ƴ����л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_ezgwy_activated(int index)
{
    switch(index)
    {
    case 0:
        m_ChainSetData.iSwitch_ezgwy=NORMAL_OPEN;
        break;
    case 1:
        m_ChainSetData.iSwitch_ezgwy=NORMAL_CLOSE;
        break;
    default:
        m_ChainSetData.iSwitch_ezgwy=NORMAL_OPEN;
        break;
    }

}



//�ӹ�Ԥ�����������л��ۺ���ʵ�� add by 2020.09.08
void CChainsetdlg::comboBox_subyuliu_activated(int index)
{
    switch(index)
    {
    case 0:
        m_ChainSetData.iSwitch_subyuliu=NORMAL_OPEN;
        break;
    case 1:
        m_ChainSetData.iSwitch_subyuliu=NORMAL_CLOSE;
        break;
    default:
        m_ChainSetData.iSwitch_subyuliu=NORMAL_OPEN;
        break;
    }

}


//��ʼ��m_newChaSetData����,add by zw 2022.02.23
void CChainsetdlg::newinitChainSetData()
{
     //���������ṹ�������ʼ��,add by 2019.04.13
    if(!(m_IniChainset.readnewChainsetInifile(m_newChaSetData)))
    {
     m_newChaSetData.iJjtjVal=SWITCH_OFF;       //����ͣ��
     m_newChaSetData.iSJitiVal=SWITCH_OFF;      //S����ͣ��
     m_newChaSetData.iXtlqVal=SWITCH_OFF;       //ϵͳ��ȴ
     m_newChaSetData.iZdtgwVal=SWITCH_OFF;      //��̨����
     m_newChaSetData.iZdtgwyVal=SWITCH_OFF;     //��̨��λ��
     m_newChaSetData.iHtgwyVal=SWITCH_OFF;      //��̨��λ��
     m_newChaSetData.iHtqyVal=SWITCH_OFF;       //��̨Ƿѹ
     m_newChaSetData.iHtqywVal=SWITCH_OFF;      //��̨ǷҺλ
     m_newChaSetData.iHtgwVal=SWITCH_OFF;       //��̨����
     m_newChaSetData.iGfrjbhVal=SWITCH_OFF;     //�����ȼ̱���
     m_newChaSetData.iJyzcdyVal=SWITCH_OFF;     //��ѹ��е�ѹ
     m_newChaSetData.iZgmbhVal=SWITCH_OFF;      //�����ű���
     m_newChaSetData.iSelfdefVal1=SWITCH_OFF;   //�Զ���1
     m_newChaSetData.iSelfdefVal2=SWITCH_OFF;   //�Զ���2
     m_newChaSetData.iSelfdefVal3=SWITCH_OFF;   //�Զ���3
     m_newChaSetData.iSelfdefVal4=SWITCH_OFF;   //�Զ���4
     m_newChaSetData.iC1zlqgwVal=SWITCH_OFF;    //�ӹ�1����������
     m_newChaSetData.iC2zlqgwVal=SWITCH_OFF;    //�ӹ�2����������
     m_newChaSetData.iC3zlqgwVal=SWITCH_OFF;    //�ӹ�3����������
     m_newChaSetData.iC4zlqgwVal=SWITCH_OFF;    //�ӹ�4����������
     m_newChaSetData.iC1cwbhVal=SWITCH_OFF;     //�ӹ�1���󱣻�
     m_newChaSetData.iC2cwbhVal=SWITCH_OFF;     //�ӹ�2���󱣻�
     m_newChaSetData.iC3cwbhVal=SWITCH_OFF;     //�ӹ�3���󱣻�
     m_newChaSetData.iC4cwbhVal=SWITCH_OFF;     //�ӹ�4���󱣻�

     //�����л���ʼ��-����
     m_newChaSetData.isw_Jjtj=SWITCH_OFF;       //����ͣ��
     m_newChaSetData.isw_SJiti=SWITCH_OFF;      //S����ͣ��
     m_newChaSetData.isw_Xtlq=SWITCH_OFF;       //ϵͳ��ȴ
     m_newChaSetData.isw_Zdtgw=SWITCH_OFF;      //��̨����
     m_newChaSetData.isw_Zdtgwy=SWITCH_OFF;     //��̨��λ��
     m_newChaSetData.isw_Htgwy=SWITCH_OFF;      //��̨��λ��
     m_newChaSetData.isw_Htqy=SWITCH_OFF;       //��̨Ƿѹ
     m_newChaSetData.isw_Htqyw=SWITCH_OFF;      //��̨ǷҺλ
     m_newChaSetData.isw_Htgw=SWITCH_OFF;       //��̨����
     m_newChaSetData.isw_Gfrjbh=SWITCH_OFF;     //�����ȼ̱���
     m_newChaSetData.isw_Jyzcdy=SWITCH_OFF;     //��ѹ��е�ѹ
     m_newChaSetData.isw_Zgmbh=SWITCH_OFF;      //�����ű���
     m_newChaSetData.isw_Selfdef1=SWITCH_OFF;   //�Զ���1
     m_newChaSetData.isw_Selfdef2=SWITCH_OFF;   //�Զ���2
     m_newChaSetData.isw_Selfdef3=SWITCH_OFF;   //�Զ���3
     m_newChaSetData.isw_Selfdef4=SWITCH_OFF;   //�Զ���4
     m_newChaSetData.isw_C1zlqgw=SWITCH_OFF;    //�ӹ�1����������
     m_newChaSetData.isw_C2zlqgw=SWITCH_OFF;    //�ӹ�2����������
     m_newChaSetData.isw_C3zlqgw=SWITCH_OFF;    //�ӹ�3����������
     m_newChaSetData.isw_C4zlqgw=SWITCH_OFF;    //�ӹ�4����������
     m_newChaSetData.isw_C1cwbh=SWITCH_OFF;     //�ӹ�1���󱣻�
     m_newChaSetData.isw_C2cwbh=SWITCH_OFF;     //�ӹ�2���󱣻�
     m_newChaSetData.isw_C3cwbh=SWITCH_OFF;     //�ӹ�3���󱣻�
     m_newChaSetData.isw_C4cwbh=SWITCH_OFF;     //�ӹ�4���󱣻�
    }
      m_iNewswFlag[0] = m_newChaSetData.iJjtjVal;           //����ͣ��
      m_iNewswFlag[1] = m_newChaSetData.iSJitiVal;          //S����ͣ��
      m_iNewswFlag[2] = m_newChaSetData.iXtlqVal;           //ϵͳ��ȴ
      m_iNewswFlag[3] = m_newChaSetData.iZdtgwVal;          //��̨����
      m_iNewswFlag[4] = m_newChaSetData.iZdtgwyVal;         //��̨��λ��
      m_iNewswFlag[5] = m_newChaSetData.iHtgwyVal;          //��̨��λ��
      m_iNewswFlag[6] = m_newChaSetData.iHtqyVal;           //��̨Ƿѹ
      m_iNewswFlag[7] = m_newChaSetData.iHtqywVal;          //��̨ǷҺλ
      m_iNewswFlag[8] = m_newChaSetData.iHtgwVal;           //��̨����
      m_iNewswFlag[9] = m_newChaSetData.iGfrjbhVal;         //�����ȼ̱���
      m_iNewswFlag[10] = m_newChaSetData.iJyzcdyVal;        //��ѹ��е�ѹ
      m_iNewswFlag[11] = m_newChaSetData.iZgmbhVal;         //�����ű���
      m_iNewswFlag[12] = m_newChaSetData.iSelfdefVal1;      //�Զ���1
      m_iNewswFlag[13] = m_newChaSetData.iSelfdefVal2;      //�Զ���2
      m_iNewswFlag[14] = m_newChaSetData.iSelfdefVal3;      //�Զ���3
      m_iNewswFlag[15] = m_newChaSetData.iSelfdefVal4;      //�Զ���4
      m_iNewswFlag[16] = m_newChaSetData.iC1zlqgwVal;       //�ӹ�1����������
      m_iNewswFlag[17] = m_newChaSetData.iC2zlqgwVal;       //�ӹ�2����������
      m_iNewswFlag[18] = m_newChaSetData.iC3zlqgwVal;       //�ӹ�3����������
      m_iNewswFlag[19] = m_newChaSetData.iC4zlqgwVal;       //�ӹ�4����������
      m_iNewswFlag[20] = m_newChaSetData.iC1cwbhVal;        //�ӹ�1���󱣻�
      m_iNewswFlag[21] = m_newChaSetData.iC2cwbhVal;        //�ӹ�2���󱣻�
      m_iNewswFlag[22] = m_newChaSetData.iC3cwbhVal;        //�ӹ�3���󱣻�
      m_iNewswFlag[23] = m_newChaSetData.iC4cwbhVal;        //�ӹ�4���󱣻�

    memcpy(&g_newchasetdata,&m_newChaSetData,sizeof(m_newChaSetData));//�����������ñ���g_newchasetdata��ʼ��

//    showChainButton(JJTJ_MASK, m_pUi->tool);           //����ͣ��
//    showChainButton(SJJTJ_MASK, m_pUi->toolButton_xtlqdy);          //S����ͣ��
    showChainButton(XTLQ_MASK, m_pUi->toolButton_xtlqdy);               //ϵͳ��ȴ
    showChainButton(ZDTGW_MASK, m_pUi->toolButton_zdtgw);               //��̨����
    showChainButton(ZDTGWY_MASK, m_pUi->toolButton_zdtgwy);             //��̨��λ��
    showChainButton(HTGWY_MASK, m_pUi->toolButton_htgwy);               //��̨��λ��
    showChainButton(HTQY_MASK, m_pUi->toolButton_htqy);                 //��̨Ƿѹ
    showChainButton(HTQYW_MASK, m_pUi->toolButton_htqyw);               //��̨ǷҺλ
    showChainButton(HTGW_MASK, m_pUi->toolButton_htgw);                 //��̨����
    showChainButton(GFRJBH_MASK, m_pUi->toolButton_gfrjbh);             //�����ȼ̱���
    showChainButton(JYZCDY_MASK, m_pUi->toolButton_jyzcdy);             //��ѹ��е�ѹ
    showChainButton(ZGMBH_MASK, m_pUi->toolButton_zgmenbh);             //�����ű���
    showChainButton(ZDY1_MASK, m_pUi->toolButton_selfdefine1);          //�Զ���1
    showChainButton(ZDY2_MASK, m_pUi->toolButton_selfdefine2);          //�Զ���2
    showChainButton(ZDY3_MASK, m_pUi->toolButton_selfdefine3);          //�Զ���3
    showChainButton(ZDY4_MASK, m_pUi->toolButton_selfdefine4);          //�Զ���4
    showChainButton(CG1ZLQGW_MASK, m_pUi->toolButton_c1zlqgw);          //�ӹ�1����������
    showChainButton(CG2ZLQGW_MASK, m_pUi->toolButton_c2zlqgw);          //�ӹ�2����������
    showChainButton(CG3ZLQGW_MASK, m_pUi->toolButton_c3zlqgw);          //�ӹ�3����������
    showChainButton(CG4ZLQGW_MASK, m_pUi->toolButton_c4zlqgw);          //�ӹ�4����������
    showChainButton(CG1CWBH_MASK, m_pUi->toolButton_c1cwbh);            //�ӹ�1���󱣻�
    showChainButton(CG2CWBH_MASK, m_pUi->toolButton_c2cwbh);            //�ӹ�2���󱣻�
    showChainButton(CG3CWBH_MASK, m_pUi->toolButton_c3cwbh);            //�ӹ�3���󱣻�
    showChainButton(CG4CWBH_MASK, m_pUi->toolButton_c4cwbh);            //�ӹ�4���󱣻�

    //�����л�-��ʾ-����
    m_pUi->comboBox_xtlqdy->setCurrentIndex(m_newChaSetData.isw_Xtlq);                  //ϵͳ��ȴ
    m_pUi->comboBox_zdtgw->setCurrentIndex(m_newChaSetData.isw_Zdtgw);                 //��̨����
    m_pUi->comboBox_zdtgwy->setCurrentIndex(m_newChaSetData.isw_Zdtgwy);                //��̨��λ��
    m_pUi->comboBox_htgwy->setCurrentIndex(m_newChaSetData.isw_Htgwy);                 //��̨��λ��
    m_pUi->comboBox_htqy->setCurrentIndex(m_newChaSetData.isw_Htqy);                  //��̨Ƿѹ
    m_pUi->comboBox_htqyw->setCurrentIndex(m_newChaSetData.isw_Htqyw);                 //��̨ǷҺλ
    m_pUi->comboBox_htgw->setCurrentIndex(m_newChaSetData.isw_Htgw);                  //��̨����
    m_pUi->comboBox_gfrjbh->setCurrentIndex(m_newChaSetData.isw_Gfrjbh);                //�����ȼ̱���
    m_pUi->comboBox_jyzcdy->setCurrentIndex(m_newChaSetData.isw_Jyzcdy);                //��ѹ��е�ѹ
    m_pUi->comboBox_zgmenbh->setCurrentIndex(m_newChaSetData.isw_Zgmbh);                 //�����ű���
    m_pUi->comboBox_selfdefine1->setCurrentIndex(m_newChaSetData.isw_Selfdef1);              //�Զ���1
    m_pUi->comboBox_selfdefine2->setCurrentIndex(m_newChaSetData.isw_Selfdef2);              //�Զ���2
    m_pUi->comboBox_selfdefine3->setCurrentIndex(m_newChaSetData.isw_Selfdef3);              //�Զ���3
    m_pUi->comboBox_selfdefine4->setCurrentIndex(m_newChaSetData.isw_Selfdef4);              //�Զ���4
    m_pUi->comboBox_c1zlqgw->setCurrentIndex(m_newChaSetData.isw_C1zlqgw);               //�ӹ�1����������
    m_pUi->comboBox_c2zlqgw->setCurrentIndex(m_newChaSetData.isw_C2zlqgw);               //�ӹ�2����������
    m_pUi->comboBox_c3zlqgw->setCurrentIndex(m_newChaSetData.isw_C3zlqgw);               //�ӹ�3����������
    m_pUi->comboBox_c4zlqgw->setCurrentIndex(m_newChaSetData.isw_C4zlqgw);               //�ӹ�4����������
    m_pUi->comboBox_c1cwbh->setCurrentIndex(m_newChaSetData.isw_C1cwbh);                //�ӹ�1���󱣻�
    m_pUi->comboBox_c2cwbh->setCurrentIndex(m_newChaSetData.isw_C2cwbh);                //�ӹ�2���󱣻�
    m_pUi->comboBox_c3cwbh->setCurrentIndex(m_newChaSetData.isw_C3cwbh);                //�ӹ�3���󱣻�
    m_pUi->comboBox_c4cwbh->setCurrentIndex(m_newChaSetData.isw_C4cwbh);                //�ӹ�4���󱣻�

}
