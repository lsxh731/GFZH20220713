/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: adjcoefdlg.cpp
** 摘要: 校准系数对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.12.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2018.12.01   V1.0      创建
**
****************************************************************************/
#include "adjcoefdlg.h"
#include <QMessageBox>

STRU_ADJCOEF g_struAdjcoef;
extern STR_GPIODATA g_GPIOData;
extern QMutex g_Mutex;
extern int g_iLangChange;//add by 2019.10.3

//add by zw 20220223
extern STRU_NEWADJCOEF g_newAdjcoef;
//end add by zw 20220223

CAdjcoefdlg::CAdjcoefdlg(int nfd)
{
    m_pUi= new Ui::adjcoefDialog;
    m_pUi->setupUi(this);
    m_nGPIOfd=nfd;
    init();
    //add by zw 20220223
    newAdjcoefInit();
    //end add by zw 20220223
    m_strErrinfo = QApplication::translate("basicparasetDialog",
         "\351\224\231\350\257\257\346\217\220\347\244\272",
         0,
         QApplication::UnicodeUTF8);//错误提示

    m_strInvalidinfo = QApplication::translate("basicparasetDialog",
        "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
        0,
        QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入

    m_strInfo=QApplication::translate("basicparasetDialog",
        "\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//提示

    m_strFriendlytips=QApplication::translate("adjcoefDialog",
        "\345\217\213\346\203\205\346\217\220\347\244\272",
        0,
        QApplication::UnicodeUTF8);//友情提示

     m_strAdjSuccess=QApplication::translate("adjcoefDialog",
         "\346\240\241\345\207\206\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);//校准成功提示语

     m_strAdjFail=QApplication::translate("adjcoefDialog",
         "\345\255\230\345\234\250\351\235\236\346\263\225\346\240\241\345\207\206",
         0,
         QApplication::UnicodeUTF8);//校准失败提示语

     m_strSaveSuccess= QApplication::translate("adjcoefDialog", "\345\237\272\346\234\254\345\217\202\346\225\260\351\205\215\347\275\256\346\226\207\344\273\266\344\277\235\345\255\230\346\210\220\345\212\237",
        0,
        QApplication::UnicodeUTF8);//基本参数配置文件保存成功提示语

    m_strSaveFail= QApplication::translate("adjcoefDialog", "\345\237\272\346\234\254\345\217\202\346\225\260\351\205\215\347\275\256\346\226\207\344\273\266\344\277\235\345\255\230\345\244\261\350\264\245,\350\257\267\346\243\200\346\237\245",
        0,
        QApplication::UnicodeUTF8);//基本参数配置文件保存失败提示语

    m_strResetSuccess=QApplication::translate("adjcoefDialog",
         "\346\240\241\345\207\206\345\244\215\344\275\215\346\210\220\345\212\237",
         0,
         QApplication::UnicodeUTF8);//复位校准成功提示语

    m_strResetFail=QApplication::translate("adjcoefDialog",
         "\346\240\241\345\207\206\345\244\215\344\275\215\345\244\261\350\264\245",
         0,
         QApplication::UnicodeUTF8);//复位校准失败提示语

    //信号与槽关系
    connect(m_pUi->adjcoefBtn,SIGNAL(clicked()),this,SLOT(adjcoefBtn_clicked()));
    connect(m_pUi->zeroBtn,SIGNAL(clicked()),this,SLOT(zeroBtn_clicked()));
    connect(m_pUi->resetBtn,SIGNAL(clicked()),SLOT(resetadjBtn_clicked()));
    connect(m_pUi->lineEdit_sub1adjbusvolt,SIGNAL(clicked()),SLOT(Sub1AbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub1totalbusvolt,SIGNAL(clicked()),SLOT(Sub1TbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub1adjactbusvolt,SIGNAL(clicked()),SLOT(Sub1AactbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub1totalactbusvolt,SIGNAL(clicked()),SLOT(Sub1TactbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub1adjnegbusvolt,SIGNAL(clicked()),SLOT(Sub1AnegbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub1totalnegbusvolt,SIGNAL(clicked()),SLOT(Sub1TnegbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub1totaloutputvolt,SIGNAL(clicked()),SLOT(Sub1ToutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub1adjoutputvolt,SIGNAL(clicked()),SLOT(Sub1AoutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub1zerooutputvolt,SIGNAL(clicked()),SLOT(Sub1ZoutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub1totaloutputcurr,SIGNAL(clicked()),SLOT(Sub1ToutcurrlEdit_clicked()));
    connect(m_pUi->lineEdit_sub1adjoutputcurr,SIGNAL(clicked()),SLOT(Sub1AoutcurrlEdit_clicked()));
    connect(m_pUi->lineEdit_sub1zerooutputcurr,SIGNAL(clicked()),SLOT(Sub1ZoutcurrlEdit_clicked()));

    connect(m_pUi->lineEdit_sub2adjbusvolt,SIGNAL(clicked()),SLOT(Sub2AbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub2totalbusvolt,SIGNAL(clicked()),SLOT(Sub2TbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub2adjactbusvolt,SIGNAL(clicked()),SLOT(Sub2AactbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub2totalactbusvolt,SIGNAL(clicked()),SLOT(Sub2TactbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub2adjnegbusvolt,SIGNAL(clicked()),SLOT(Sub2AnegbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub2totalnegbusvolt,SIGNAL(clicked()),SLOT(Sub2TnegbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub2totaloutputvolt,SIGNAL(clicked()),SLOT(Sub2ToutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub2adjoutputvolt,SIGNAL(clicked()),SLOT(Sub2AoutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub2zerooutputvolt,SIGNAL(clicked()),SLOT(Sub2ZoutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub2totaloutputcurr,SIGNAL(clicked()),SLOT(Sub2ToutcurrlEdit_clicked()));
    connect(m_pUi->lineEdit_sub2adjoutputcurr,SIGNAL(clicked()),SLOT(Sub2AoutcurrlEdit_clicked()));
    connect(m_pUi->lineEdit_sub2zerooutputcurr,SIGNAL(clicked()),SLOT(Sub2ZoutcurrlEdit_clicked()));

    connect(m_pUi->lineEdit_sub3adjbusvolt,SIGNAL(clicked()),SLOT(Sub3AbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub3totalbusvolt,SIGNAL(clicked()),SLOT(Sub3TbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub3adjactbusvolt,SIGNAL(clicked()),SLOT(Sub3AactbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub3totalactbusvolt,SIGNAL(clicked()),SLOT(Sub3TactbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub3adjnegbusvolt,SIGNAL(clicked()),SLOT(Sub3AnegbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub3totalnegbusvolt,SIGNAL(clicked()),SLOT(Sub3TnegbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub3totaloutputvolt,SIGNAL(clicked()),SLOT(Sub3ToutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub3adjoutputvolt,SIGNAL(clicked()),SLOT(Sub3AoutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub3zerooutputvolt,SIGNAL(clicked()),SLOT(Sub3ZoutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub3totaloutputcurr,SIGNAL(clicked()),SLOT(Sub3ToutcurrlEdit_clicked()));
    connect(m_pUi->lineEdit_sub3adjoutputcurr,SIGNAL(clicked()),SLOT(Sub3AoutcurrlEdit_clicked()));
    connect(m_pUi->lineEdit_sub3zerooutputcurr,SIGNAL(clicked()),SLOT(Sub3ZoutcurrlEdit_clicked()));

    connect(m_pUi->lineEdit_sub4adjbusvolt,SIGNAL(clicked()),SLOT(Sub4AbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub4totalbusvolt,SIGNAL(clicked()),SLOT(Sub4TbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub4adjactbusvolt,SIGNAL(clicked()),SLOT(Sub4AactbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub4totalactbusvolt,SIGNAL(clicked()),SLOT(Sub4TactbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub4adjnegbusvolt,SIGNAL(clicked()),SLOT(Sub4AnegbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub4totalnegbusvolt,SIGNAL(clicked()),SLOT(Sub4TnegbuslEdit_clicked()));
    connect(m_pUi->lineEdit_sub4totaloutputvolt,SIGNAL(clicked()),SLOT(Sub4ToutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub4adjoutputvolt,SIGNAL(clicked()),SLOT(Sub4AoutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub4zerooutputvolt,SIGNAL(clicked()),SLOT(Sub4ZoutvoltlEdit_clicked()));
    connect(m_pUi->lineEdit_sub4totaloutputcurr,SIGNAL(clicked()),SLOT(Sub4ToutcurrlEdit_clicked()));
    connect(m_pUi->lineEdit_sub4adjoutputcurr,SIGNAL(clicked()),SLOT(Sub4AoutcurrlEdit_clicked()));
    connect(m_pUi->lineEdit_sub4zerooutputcurr,SIGNAL(clicked()),SLOT(Sub4ZoutcurrlEdit_clicked()));

    connect(m_pUi->lineEdit_mAtotalvolt,SIGNAL(clicked()),SLOT(MATlEdit_clicked()));
    connect(m_pUi->lineEdit_mAadjvolt,SIGNAL(clicked()),SLOT(MAAlEdit_clicked()));
    connect(m_pUi->lineEdit_mBtotalvolt,SIGNAL(clicked()),SLOT(MBTlEdit_clicked()));
    connect(m_pUi->lineEdit_mBadjvolt,SIGNAL(clicked()),SLOT(MBAlEdit_clicked()));
    connect(m_pUi->lineEdit_mCtotalvolt,SIGNAL(clicked()),SLOT(MCTlEdit_clicked()));
    connect(m_pUi->lineEdit_mCadjvolt,SIGNAL(clicked()),SLOT(MCAlEdit_clicked()));
    connect(m_pUi->lineEdit_evtotal,SIGNAL(clicked()),SLOT(MEVTlEdit_clicked()));
    connect(m_pUi->lineEdit_evadj,SIGNAL(clicked()),SLOT(MEVAlEdit_clicked()));
    connect(m_pUi->lineEdit_ectotal,SIGNAL(clicked()),SLOT(MECTlEdit_clicked()));
    connect(m_pUi->lineEdit_ecadj,SIGNAL(clicked()),SLOT(MECAlEdit_clicked()));

    connect(m_pUi->s1bvcheckBox,SIGNAL(clicked()),this,SLOT(s1bvcheckBox_clicked()));
    connect(m_pUi->s1abvcheckBox,SIGNAL(clicked()),this,SLOT(s1abvcheckBox_clicked()));
    connect(m_pUi->s1nbvcheckBox,SIGNAL(clicked()),this,SLOT(s1nbvcheckBox_clicked()));
    connect(m_pUi->s1ovcheckBox,SIGNAL(clicked()),this,SLOT(s1ovcheckBox_clicked()));
    connect(m_pUi->s1occheckBox,SIGNAL(clicked()),this,SLOT(s1occheckBox_clicked()));

    connect(m_pUi->s2bvcheckBox,SIGNAL(clicked()),this,SLOT(s2bvcheckBox_clicked()));
    connect(m_pUi->s2abvcheckBox,SIGNAL(clicked()),this,SLOT(s2abvcheckBox_clicked()));
    connect(m_pUi->s2nbvcheckBox,SIGNAL(clicked()),this,SLOT(s2nbvcheckBox_clicked()));
    connect(m_pUi->s2ovcheckBox,SIGNAL(clicked()),this,SLOT(s2ovcheckBox_clicked()));
    connect(m_pUi->s2occheckBox,SIGNAL(clicked()),this,SLOT(s2occheckBox_clicked()));

    connect(m_pUi->s3bvcheckBox,SIGNAL(clicked()),this,SLOT(s3bvcheckBox_clicked()));
    connect(m_pUi->s3abvcheckBox,SIGNAL(clicked()),this,SLOT(s3abvcheckBox_clicked()));
    connect(m_pUi->s3nbvcheckBox,SIGNAL(clicked()),this,SLOT(s3nbvcheckBox_clicked()));
    connect(m_pUi->s3ovcheckBox,SIGNAL(clicked()),this,SLOT(s3ovcheckBox_clicked()));
    connect(m_pUi->s3occheckBox,SIGNAL(clicked()),this,SLOT(s3occheckBox_clicked()));

    connect(m_pUi->s4bvcheckBox,SIGNAL(clicked()),this,SLOT(s4bvcheckBox_clicked()));
    connect(m_pUi->s4abvcheckBox,SIGNAL(clicked()),this,SLOT(s4abvcheckBox_clicked()));
    connect(m_pUi->s4nbvcheckBox,SIGNAL(clicked()),this,SLOT(s4nbvcheckBox_clicked()));
    connect(m_pUi->s4ovcheckBox,SIGNAL(clicked()),this,SLOT(s4ovcheckBox_clicked()));
    connect(m_pUi->s4occheckBox,SIGNAL(clicked()),this,SLOT(s4occheckBox_clicked()));

    connect(m_pUi->mAvcheckBox,SIGNAL(clicked()),this,SLOT(mAvcheckBox_clicked()));
    connect(m_pUi->mBvcheckBox,SIGNAL(clicked()),this,SLOT(mBvcheckBox_clicked()));
    connect(m_pUi->mCvcheckBox,SIGNAL(clicked()),this,SLOT(mCvcheckBox_clicked()));
    connect(m_pUi->mevcheckBox,SIGNAL(clicked()),this,SLOT(mevcheckBox_clicked()));
    connect(m_pUi->meccheckBox,SIGNAL(clicked()),this,SLOT(meccheckBox_clicked()));

    connect(m_pUi->s1checkBox,SIGNAL(clicked()),this,SLOT(s1checkBox_clicked()));
    connect(m_pUi->s2checkBox,SIGNAL(clicked()),this,SLOT(s2checkBox_clicked()));
    connect(m_pUi->s3checkBox,SIGNAL(clicked()),this,SLOT(s3checkBox_clicked()));
    connect(m_pUi->s4checkBox,SIGNAL(clicked()),this,SLOT(s4checkBox_clicked()));
    connect(m_pUi->maincheckBox,SIGNAL(clicked()),this,SLOT(maincheckBox_clicked()));
    connect(m_pUi->allcheckBox,SIGNAL(clicked()),this,SLOT(allcheckBox_clicked()));
    connect(m_pUi->closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));//返回键 add by 2020.08.10
}
CAdjcoefdlg::~CAdjcoefdlg()
{

}
//校准-槽函数
void CAdjcoefdlg::adjcoefBtn_clicked()
{
    bool ok=false;
    int cnt=0;
    int adjcnt=0;
    float fAdjcoefK=1.0;
    float fAdjcoefB=0.0;
    if(m_struAdjcheck.iS1bvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[0] = m_pUi->lineEdit_sub1totalbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[0] = m_pUi->lineEdit_sub1adjbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[0]-m_struAdjvalue.fZeroTotalvalue[0])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[0]/(m_struAdjvalue.fTotalvalue[0]-m_struAdjvalue.fZeroTotalvalue[0]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[0]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub1voltK = fAdjcoefK;
                m_struAdjcoef.fSub1voltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS1abvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[1] = m_pUi->lineEdit_sub1totalactbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[1] = m_pUi->lineEdit_sub1adjactbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[1]-m_struAdjvalue.fZeroTotalvalue[1])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[1]/(m_struAdjvalue.fTotalvalue[1]-m_struAdjvalue.fZeroTotalvalue[1]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[1]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub1ActvoltK = fAdjcoefK;
                m_struAdjcoef.fSub1ActvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS1nbvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[2] = m_pUi->lineEdit_sub1totalnegbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[2] = m_pUi->lineEdit_sub1adjnegbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[2]-m_struAdjvalue.fZeroTotalvalue[2])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[2]/(m_struAdjvalue.fTotalvalue[2]-m_struAdjvalue.fZeroTotalvalue[2]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[2]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub1negvoltK = fAdjcoefK;
                m_struAdjcoef.fSub1negvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS1ovCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fZeroTotalvalue[3] = m_pUi->lineEdit_sub1zerooutputvolt->text().toFloat(&ok);
        m_struAdjvalue.fTotalvalue[3] = m_pUi->lineEdit_sub1totaloutputvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[3] = m_pUi->lineEdit_sub1adjoutputvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[3]-m_struAdjvalue.fZeroTotalvalue[3])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[3]/(m_struAdjvalue.fTotalvalue[3]-m_struAdjvalue.fZeroTotalvalue[3]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[3]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub1outvoltK = fAdjcoefK;
                m_struAdjcoef.fSub1outvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS1ocCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fZeroTotalvalue[4] = m_pUi->lineEdit_sub1zerooutputcurr->text().toFloat(&ok);
        m_struAdjvalue.fTotalvalue[4] = m_pUi->lineEdit_sub1totaloutputcurr->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[4] = m_pUi->lineEdit_sub1adjoutputcurr->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[4]-m_struAdjvalue.fZeroTotalvalue[4])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[4]/(m_struAdjvalue.fTotalvalue[4]-m_struAdjvalue.fZeroTotalvalue[4]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[4]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub1outcurrK = fAdjcoefK;
                m_struAdjcoef.fSub1outcurrB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS2bvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[5] = m_pUi->lineEdit_sub2totalbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[5] = m_pUi->lineEdit_sub2adjbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[5]-m_struAdjvalue.fZeroTotalvalue[5])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[5]/(m_struAdjvalue.fTotalvalue[5]-m_struAdjvalue.fZeroTotalvalue[5]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[5]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub2voltK = fAdjcoefK;
                m_struAdjcoef.fSub2voltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS2abvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[6] = m_pUi->lineEdit_sub2totalactbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[6] = m_pUi->lineEdit_sub2adjactbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[6]-m_struAdjvalue.fZeroTotalvalue[6])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[6]/(m_struAdjvalue.fTotalvalue[6]-m_struAdjvalue.fZeroTotalvalue[6]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[6]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub2ActvoltK = fAdjcoefK;
                m_struAdjcoef.fSub2ActvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS2nbvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[7] = m_pUi->lineEdit_sub2totalnegbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[7] = m_pUi->lineEdit_sub2adjnegbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[7]-m_struAdjvalue.fZeroTotalvalue[7])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[7]/(m_struAdjvalue.fTotalvalue[7]-m_struAdjvalue.fZeroTotalvalue[7]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[7]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub2negvoltK = fAdjcoefK;
                m_struAdjcoef.fSub2negvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS2ovCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fZeroTotalvalue[8] = m_pUi->lineEdit_sub2zerooutputvolt->text().toFloat(&ok);
        m_struAdjvalue.fTotalvalue[8] = m_pUi->lineEdit_sub2totaloutputvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[8] = m_pUi->lineEdit_sub2adjoutputvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[8]-m_struAdjvalue.fZeroTotalvalue[8])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[8]/(m_struAdjvalue.fTotalvalue[8]-m_struAdjvalue.fZeroTotalvalue[8]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[8]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub2outvoltK = fAdjcoefK;
                m_struAdjcoef.fSub2outvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS2ocCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fZeroTotalvalue[9] = m_pUi->lineEdit_sub2zerooutputcurr->text().toFloat(&ok);
        m_struAdjvalue.fTotalvalue[9] = m_pUi->lineEdit_sub2totaloutputcurr->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[9] = m_pUi->lineEdit_sub2adjoutputcurr->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[9]-m_struAdjvalue.fZeroTotalvalue[9])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[9]/(m_struAdjvalue.fTotalvalue[9]-m_struAdjvalue.fZeroTotalvalue[9]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[9]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub2outcurrK = fAdjcoefK;
                m_struAdjcoef.fSub2outcurrB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS3bvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[10] = m_pUi->lineEdit_sub3totalbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[10] = m_pUi->lineEdit_sub3adjbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[10]-m_struAdjvalue.fZeroTotalvalue[10])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[10]/(m_struAdjvalue.fTotalvalue[10]-m_struAdjvalue.fZeroTotalvalue[10]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[10]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub3voltK = fAdjcoefK;
                m_struAdjcoef.fSub3voltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS3abvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[11] = m_pUi->lineEdit_sub3totalactbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[11] = m_pUi->lineEdit_sub3adjactbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[11]-m_struAdjvalue.fZeroTotalvalue[11])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[11]/(m_struAdjvalue.fTotalvalue[11]-m_struAdjvalue.fZeroTotalvalue[11]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[11]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub3ActvoltK = fAdjcoefK;
                m_struAdjcoef.fSub3ActvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS3nbvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[12] = m_pUi->lineEdit_sub3totalnegbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[12] = m_pUi->lineEdit_sub3adjnegbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[12]-m_struAdjvalue.fZeroTotalvalue[12])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[12]/(m_struAdjvalue.fTotalvalue[12]-m_struAdjvalue.fZeroTotalvalue[12]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[12]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub3negvoltK = fAdjcoefK;
                m_struAdjcoef.fSub3negvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS3ovCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fZeroTotalvalue[13] = m_pUi->lineEdit_sub3zerooutputvolt->text().toFloat(&ok);
        m_struAdjvalue.fTotalvalue[13] = m_pUi->lineEdit_sub3totaloutputvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[13] = m_pUi->lineEdit_sub3adjoutputvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[13]-m_struAdjvalue.fZeroTotalvalue[13])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[13]/(m_struAdjvalue.fTotalvalue[13]-m_struAdjvalue.fZeroTotalvalue[13]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[13]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub3outvoltK = fAdjcoefK;
                m_struAdjcoef.fSub3outvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS3ocCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fZeroTotalvalue[14] = m_pUi->lineEdit_sub3zerooutputcurr->text().toFloat(&ok);
        m_struAdjvalue.fTotalvalue[14] = m_pUi->lineEdit_sub3totaloutputcurr->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[14] = m_pUi->lineEdit_sub3adjoutputcurr->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[14]-m_struAdjvalue.fZeroTotalvalue[14])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[14]/(m_struAdjvalue.fTotalvalue[14]-m_struAdjvalue.fZeroTotalvalue[14]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[14]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub3outcurrK = fAdjcoefK;
                m_struAdjcoef.fSub3outcurrB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS4bvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[15] = m_pUi->lineEdit_sub4totalbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[15] = m_pUi->lineEdit_sub4adjbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[15]-m_struAdjvalue.fZeroTotalvalue[15])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[15]/(m_struAdjvalue.fTotalvalue[15]-m_struAdjvalue.fZeroTotalvalue[15]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[15]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub4voltK = fAdjcoefK;
                m_struAdjcoef.fSub4voltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS4abvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[16] = m_pUi->lineEdit_sub4totalactbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[16] = m_pUi->lineEdit_sub4adjactbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[16]-m_struAdjvalue.fZeroTotalvalue[16])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[16]/(m_struAdjvalue.fTotalvalue[16]-m_struAdjvalue.fZeroTotalvalue[16]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[16]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub4ActvoltK = fAdjcoefK;
                m_struAdjcoef.fSub4ActvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS4nbvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[17] = m_pUi->lineEdit_sub4totalnegbusvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[17] = m_pUi->lineEdit_sub4adjnegbusvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[17]-m_struAdjvalue.fZeroTotalvalue[17])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[17]/(m_struAdjvalue.fTotalvalue[17]-m_struAdjvalue.fZeroTotalvalue[17]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[17]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub4negvoltK = fAdjcoefK;
                m_struAdjcoef.fSub4negvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS4ovCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fZeroTotalvalue[18] = m_pUi->lineEdit_sub4zerooutputvolt->text().toFloat(&ok);
        m_struAdjvalue.fTotalvalue[18] = m_pUi->lineEdit_sub4totaloutputvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[18] = m_pUi->lineEdit_sub4adjoutputvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[18]-m_struAdjvalue.fZeroTotalvalue[18])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[18]/(m_struAdjvalue.fTotalvalue[18]-m_struAdjvalue.fZeroTotalvalue[18]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[18]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub4outvoltK = fAdjcoefK;
                m_struAdjcoef.fSub4outvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iS4ocCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fZeroTotalvalue[19] = m_pUi->lineEdit_sub4zerooutputcurr->text().toFloat(&ok);
        m_struAdjvalue.fTotalvalue[19] = m_pUi->lineEdit_sub4totaloutputcurr->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[19] = m_pUi->lineEdit_sub4adjoutputcurr->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[19]-m_struAdjvalue.fZeroTotalvalue[19])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[19]/(m_struAdjvalue.fTotalvalue[19]-m_struAdjvalue.fZeroTotalvalue[19]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[19]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fSub4outcurrK = fAdjcoefK;
                m_struAdjcoef.fSub4outcurrB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iMAvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[20] = m_pUi->lineEdit_mAtotalvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[20] = m_pUi->lineEdit_mAadjvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[20]-m_struAdjvalue.fZeroTotalvalue[20])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[20]/(m_struAdjvalue.fTotalvalue[20]-m_struAdjvalue.fZeroTotalvalue[20]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[20]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fMAvoltK = fAdjcoefK;
                m_struAdjcoef.fMAvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iMBvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[21] = m_pUi->lineEdit_mBtotalvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[21] = m_pUi->lineEdit_mBadjvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[21]-m_struAdjvalue.fZeroTotalvalue[21])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[21]/(m_struAdjvalue.fTotalvalue[21]-m_struAdjvalue.fZeroTotalvalue[21]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[21]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fMBvoltK = fAdjcoefK;
                m_struAdjcoef.fMBvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iMCvCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[22] = m_pUi->lineEdit_mCtotalvolt->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[22] = m_pUi->lineEdit_mCadjvolt->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[22]-m_struAdjvalue.fZeroTotalvalue[22])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[22]/(m_struAdjvalue.fTotalvalue[22]-m_struAdjvalue.fZeroTotalvalue[22]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[22]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fMCvoltK = fAdjcoefK;
                m_struAdjcoef.fMCvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iMevCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[23] = m_pUi->lineEdit_evtotal->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[23] = m_pUi->lineEdit_evadj->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[23]-m_struAdjvalue.fZeroTotalvalue[23])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[23]/(m_struAdjvalue.fTotalvalue[23]-m_struAdjvalue.fZeroTotalvalue[23]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[23]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fMEvoltK = fAdjcoefK;
                m_struAdjcoef.fMEvoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_struAdjcheck.iMecCabOpen==SELECT_FLAG)
    {
        m_struAdjvalue.fTotalvalue[24] = m_pUi->lineEdit_ectotal->text().toFloat(&ok);
        m_struAdjvalue.fAdjvalue[24] = m_pUi->lineEdit_ecadj->text().toFloat(&ok);
        if(qAbs(m_struAdjvalue.fTotalvalue[24]-m_struAdjvalue.fZeroTotalvalue[24])>DELT_FVALUE)
        {
            fAdjcoefK = m_struAdjvalue.fAdjvalue[24]/(m_struAdjvalue.fTotalvalue[24]-m_struAdjvalue.fZeroTotalvalue[24]);
            fAdjcoefB = -m_struAdjvalue.fZeroTotalvalue[24]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_struAdjcoef.fMEcurrK = fAdjcoefK;
                m_struAdjcoef.fMEcurrB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(cnt>0)
    {
        QMessageBox::warning(this,
                       tr(m_strInfo),
                       tr(m_strAdjFail));
    }
    else if(cnt==0 && adjcnt>0)
    {
        QMessageBox::warning(this,
                       tr(m_strInfo),
                       tr(m_strAdjSuccess));
    }
    else
    {
    }

    if(m_IniAdjcoef.writeAdjcoefInifile(m_struAdjcoef))
    {
        //把参数m_struBasicpara赋值给全局变量g_struBasicPara,add by zqc 2019.06.16
        memcpy(&g_struAdjcoef,&m_struAdjcoef,sizeof(m_struAdjcoef));
        /*QMessageBox::warning(this,
                       tr(m_strInfo),
                       tr(m_strSaveSuccess));*/  //基本校准系数文件保存成功
    }
    else
    {
        QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strSaveFail));//基本校准系数文件保存失败,请检查
    }
}
//零点采集-槽函数
void CAdjcoefdlg::zeroBtn_clicked()
{
    if(m_struAdjcheck.iS1bvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[0] = g_GPIOData.fSlaveBusVolt[0];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub1zerobusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[0],'f',2));
    }
    if(m_struAdjcheck.iS1abvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[1] = g_GPIOData.fSlaveActBusVolt[0];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub1zeroactbusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[1],'f',2));
    }
    if(m_struAdjcheck.iS1nbvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[2] = g_GPIOData.fSlaveNegBusVolt[0];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub1zeronegbusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[2],'f',2));
    }
    if(m_struAdjcheck.iS2bvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[5] = g_GPIOData.fSlaveBusVolt[1];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub2zerobusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[5],'f',2));
    }
    if(m_struAdjcheck.iS2abvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[6] = g_GPIOData.fSlaveActBusVolt[1];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub2zeroactbusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[6],'f',2));
    }
    if(m_struAdjcheck.iS2nbvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[7] = g_GPIOData.fSlaveNegBusVolt[1];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub2zeronegbusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[7],'f',2));
    }
    if(m_struAdjcheck.iS3bvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[10] = g_GPIOData.fSlaveBusVolt[2];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub3zerobusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[10],'f',2));
    }
    if(m_struAdjcheck.iS3abvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[11] = g_GPIOData.fSlaveActBusVolt[2];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub3zeroactbusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[11],'f',2));
    }
    if(m_struAdjcheck.iS3nbvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[12] = g_GPIOData.fSlaveNegBusVolt[2];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub3zeronegbusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[12],'f',2));
    }
    if(m_struAdjcheck.iS4bvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[15] = g_GPIOData.fSlaveBusVolt[3];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub4zerobusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[15],'f',2));
    }
    if(m_struAdjcheck.iS4abvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[16] = g_GPIOData.fSlaveActBusVolt[3];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub4zeroactbusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[16],'f',2));
    }
    if(m_struAdjcheck.iS4nbvCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[17] = g_GPIOData.fSlaveNegBusVolt[3];
        g_Mutex.unlock();
        m_pUi->lineEdit_sub4zeronegbusvolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[17],'f',2));
    }
    if(m_struAdjcheck.iMevCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[23] = g_GPIOData.fExcitVolt;
        g_Mutex.unlock();
        m_pUi->lineEdit_evzero->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[23],'f',2));
    }
    if(m_struAdjcheck.iMecCabOpen==SELECT_FLAG)
    {
        g_Mutex.lock();
        m_struAdjvalue.fZeroTotalvalue[24] = g_GPIOData.fExcitCurrent;
        g_Mutex.unlock();
        m_pUi->lineEdit_eczero->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[24],'f',2));
    }
}
void CAdjcoefdlg::resetadjBtn_clicked()
{

    if(m_struAdjcheck.iS1bvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub1voltK=COMMON_K;
         m_struAdjcoef.fSub1voltB=COMMON_B;
    }
    if(m_struAdjcheck.iS1abvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub1ActvoltK=COMMON_K;
         m_struAdjcoef.fSub1ActvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS1nbvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub1negvoltK=COMMON_K;
         m_struAdjcoef.fSub1negvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS1ovCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub1outvoltK=COMMON_K;
         m_struAdjcoef.fSub1outvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS1ocCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub1outcurrK=COMMON_K;
         m_struAdjcoef.fSub1outcurrB=COMMON_B;
    }
    if(m_struAdjcheck.iS2bvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub2voltK=COMMON_K;
         m_struAdjcoef.fSub2voltB=COMMON_B;
    }
    if(m_struAdjcheck.iS2abvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub2ActvoltK=COMMON_K;
         m_struAdjcoef.fSub2ActvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS2nbvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub2negvoltK=COMMON_K;
         m_struAdjcoef.fSub2negvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS2ovCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub2outvoltK=COMMON_K;
         m_struAdjcoef.fSub2outvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS2ocCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub2outcurrK=COMMON_K;
         m_struAdjcoef.fSub2outcurrB=COMMON_B;
    }
    if(m_struAdjcheck.iS3bvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub3voltK=COMMON_K;
         m_struAdjcoef.fSub3voltB=COMMON_B;
    }
    if(m_struAdjcheck.iS3abvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub3ActvoltK=COMMON_K;
         m_struAdjcoef.fSub3ActvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS3nbvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub3negvoltK=COMMON_K;
         m_struAdjcoef.fSub3negvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS3ovCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub3outvoltK=COMMON_K;
         m_struAdjcoef.fSub3outvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS3ocCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub3outcurrK=COMMON_K;
         m_struAdjcoef.fSub3outcurrB=COMMON_B;
    }
    if(m_struAdjcheck.iS4bvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub4voltK=COMMON_K;
         m_struAdjcoef.fSub4voltB=COMMON_B;
    }
    if(m_struAdjcheck.iS4abvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub4ActvoltK=COMMON_K;
         m_struAdjcoef.fSub4ActvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS4nbvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub4negvoltK=COMMON_K;
         m_struAdjcoef.fSub4negvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS4ovCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub4outvoltK=COMMON_K;
         m_struAdjcoef.fSub4outvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iS4ocCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fSub4outcurrK=COMMON_K;
         m_struAdjcoef.fSub4outcurrB=COMMON_B;
    }
    if(m_struAdjcheck.iMAvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fMAvoltK=COMMON_K;
         m_struAdjcoef.fMAvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iMBvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fMBvoltK=COMMON_K;
         m_struAdjcoef.fMBvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iMCvCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fMCvoltK=COMMON_K;
         m_struAdjcoef.fMCvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iMevCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fMEvoltK=COMMON_K;
         m_struAdjcoef.fMEvoltB=COMMON_B;
    }
    if(m_struAdjcheck.iMecCabOpen==SELECT_FLAG)
    {
         m_struAdjcoef.fMEcurrK=COMMON_K;
         m_struAdjcoef.fMEcurrB=COMMON_B;
    }
    if(m_IniAdjcoef.writeAdjcoefInifile(m_struAdjcoef))
    {
        //把参数m_struBasicpara赋值给全局变量g_struBasicPara,add by zqc 2019.06.16
        memcpy(&g_struAdjcoef,&m_struAdjcoef,sizeof(m_struAdjcoef));
        QMessageBox::warning(this,
                       tr(m_strInfo),
                       tr(m_strResetSuccess));//校准复位成功
    }
    else
    {
        QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strResetFail));//校准复位失败

    }
}
//初始化
void CAdjcoefdlg::init()
{
     int i;
     m_struAdjchecknum.m_nAllcheckCnt=0;
     m_struAdjchecknum.m_nMcheckCnt=0;
     m_struAdjchecknum.m_nRcheckCnt=0;
     m_struAdjchecknum.m_nS1checkCnt=0;
     m_struAdjchecknum.m_nS2checkCnt=0;
     m_struAdjchecknum.m_nS3checkCnt=0;
     m_struAdjchecknum.m_nS4checkCnt=0;
     if(!m_IniAdjcoef.readAdjcoefInifile(m_struAdjcoef))//校准系数的读取
     {
         m_struAdjcoef.fSub1voltK=COMMON_K;
         m_struAdjcoef.fSub1voltB=COMMON_B;
         m_struAdjcoef.fSub1ActvoltK=COMMON_K;
         m_struAdjcoef.fSub1ActvoltB=COMMON_B;
         m_struAdjcoef.fSub1negvoltK=COMMON_K;
         m_struAdjcoef.fSub1negvoltB=COMMON_B;
         m_struAdjcoef.fSub1outvoltK=COMMON_K;
         m_struAdjcoef.fSub1outvoltB=COMMON_B;
         m_struAdjcoef.fSub1outcurrK=COMMON_K;
         m_struAdjcoef.fSub1outcurrB=COMMON_B;

         m_struAdjcoef.fSub2voltK=COMMON_K;
         m_struAdjcoef.fSub2voltB=COMMON_B;
         m_struAdjcoef.fSub2ActvoltK=COMMON_K;
         m_struAdjcoef.fSub2ActvoltB=COMMON_B;
         m_struAdjcoef.fSub2negvoltK=COMMON_K;
         m_struAdjcoef.fSub2negvoltB=COMMON_B;
         m_struAdjcoef.fSub2outvoltK=COMMON_K;
         m_struAdjcoef.fSub2outvoltB=COMMON_B;
         m_struAdjcoef.fSub2outcurrK=COMMON_K;
         m_struAdjcoef.fSub2outcurrB=COMMON_B;

         m_struAdjcoef.fSub3voltK=COMMON_K;
         m_struAdjcoef.fSub3voltB=COMMON_B;
         m_struAdjcoef.fSub3ActvoltK=COMMON_K;
         m_struAdjcoef.fSub3ActvoltB=COMMON_B;
         m_struAdjcoef.fSub3negvoltK=COMMON_K;
         m_struAdjcoef.fSub3negvoltB=COMMON_B;
         m_struAdjcoef.fSub3outvoltK=COMMON_K;
         m_struAdjcoef.fSub3outvoltB=COMMON_B;
         m_struAdjcoef.fSub3outcurrK=COMMON_K;
         m_struAdjcoef.fSub3outcurrB=COMMON_B;

         m_struAdjcoef.fSub4voltK=COMMON_K;
         m_struAdjcoef.fSub4voltB=COMMON_B;
         m_struAdjcoef.fSub4ActvoltK=COMMON_K;
         m_struAdjcoef.fSub4ActvoltB=COMMON_B;
         m_struAdjcoef.fSub4negvoltK=COMMON_K;
         m_struAdjcoef.fSub4negvoltB=COMMON_B;
         m_struAdjcoef.fSub4outvoltK=COMMON_K;
         m_struAdjcoef.fSub4outvoltB=COMMON_B;
         m_struAdjcoef.fSub4outcurrK=COMMON_K;
         m_struAdjcoef.fSub4outcurrB=COMMON_B;

         m_struAdjcoef.fMAvoltK=COMMON_K;
         m_struAdjcoef.fMAvoltB=COMMON_B;
         m_struAdjcoef.fMBvoltK=COMMON_K;
         m_struAdjcoef.fMBvoltB=COMMON_B;
         m_struAdjcoef.fMCvoltK=COMMON_K;
         m_struAdjcoef.fMCvoltB=COMMON_B;
         m_struAdjcoef.fMEvoltK=COMMON_K;
         m_struAdjcoef.fMEvoltB=COMMON_B;
         m_struAdjcoef.fMEcurrK=COMMON_K;
         m_struAdjcoef.fMEcurrB=COMMON_B;
     }
     for(i=0;i<25;i++)
     {
        m_struAdjvalue.fAdjvalue[i]=1.0;
        m_struAdjvalue.fTotalvalue[i]=1.0;
        m_struAdjvalue.fZeroTotalvalue[i]=0.0;
     }
     m_struAdjvalue.fZeroTotalvalue[20] = APhaseVolt;
     m_struAdjvalue.fZeroTotalvalue[21] = BPhaseVolt;
     m_struAdjvalue.fZeroTotalvalue[22] = CPhaseVolt;
     m_pUi->lineEdit_mAzerovolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[20],'f',2));
     m_pUi->lineEdit_mBzerovolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[21],'f',2));
     m_pUi->lineEdit_mCzerovolt->setText(QString::number(m_struAdjvalue.fZeroTotalvalue[22],'f',2));
     //选择按钮的初始化
     m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
     m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
     s1select();
     s2select();
     s3select();
     s4select();
     mainselect();
     m_pUi->lineEdit_sub1zerobusvolt->setEnabled(false);
     m_pUi->lineEdit_sub1zeroactbusvolt->setEnabled(false);
     m_pUi->lineEdit_sub1zeronegbusvolt->setEnabled(false);
     m_pUi->lineEdit_sub2zerobusvolt->setEnabled(false);
     m_pUi->lineEdit_sub2zeroactbusvolt->setEnabled(false);
     m_pUi->lineEdit_sub2zeronegbusvolt->setEnabled(false);
     m_pUi->lineEdit_sub3zerobusvolt->setEnabled(false);
     m_pUi->lineEdit_sub3zeroactbusvolt->setEnabled(false);
     m_pUi->lineEdit_sub3zeronegbusvolt->setEnabled(false);
     m_pUi->lineEdit_sub4zerobusvolt->setEnabled(false);
     m_pUi->lineEdit_sub4zeroactbusvolt->setEnabled(false);
     m_pUi->lineEdit_sub4zeronegbusvolt->setEnabled(false);
     m_pUi->lineEdit_mAzerovolt->setEnabled(false);
     m_pUi->lineEdit_mBzerovolt->setEnabled(false);
     m_pUi->lineEdit_mCzerovolt->setEnabled(false);
     m_pUi->lineEdit_evzero->setEnabled(false);
     m_pUi->lineEdit_eczero->setEnabled(false);
}

//打开数字键盘对话框
void CAdjcoefdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    bool ok=false;
    m_KeyBoardDlg.exec();//打开键盘对话框
    m_KeyBoardDlg.clearBtn_clicked();//清除旧的输入痕迹
    ok=m_KeyBoardDlg.getInputValue(fValue);
    if(ok)
    {
        lineEdit->setText(QString::number(fValue,'f',1));
    }
    else
    {
        QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//输入的数值不合法
    }
}
//从柜1校准输入打开键盘
void CAdjcoefdlg::Sub1AactbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1adjactbusvolt);
}
void CAdjcoefdlg::Sub1TactbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1totalactbusvolt);
}
void CAdjcoefdlg::Sub1TbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1totalbusvolt);
}
void CAdjcoefdlg::Sub1AbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1adjbusvolt);
}
void CAdjcoefdlg::Sub1TnegbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1totalnegbusvolt);
}
void CAdjcoefdlg::Sub1AnegbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1adjnegbusvolt);
}
void CAdjcoefdlg::Sub1ToutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1totaloutputvolt);
}
void CAdjcoefdlg::Sub1ZoutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1zerooutputvolt);
}
void CAdjcoefdlg::Sub1AoutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1adjoutputvolt);
}
void CAdjcoefdlg::Sub1ToutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1totaloutputcurr);
}
void CAdjcoefdlg::Sub1AoutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1adjoutputcurr);
}
void CAdjcoefdlg::Sub1ZoutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub1zerooutputcurr);
}
//从柜2校准输入打开键盘
void CAdjcoefdlg::Sub2AactbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2adjactbusvolt);
}
void CAdjcoefdlg::Sub2TactbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2totalactbusvolt);
}
void CAdjcoefdlg::Sub2TbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2totalbusvolt);
}
void CAdjcoefdlg::Sub2AbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2adjbusvolt);
}
void CAdjcoefdlg::Sub2TnegbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2totalnegbusvolt);
}
void CAdjcoefdlg::Sub2AnegbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2adjnegbusvolt);
}
void CAdjcoefdlg::Sub2ToutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2totaloutputvolt);
}
void CAdjcoefdlg::Sub2ZoutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2zerooutputvolt);
}
void CAdjcoefdlg::Sub2AoutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2adjoutputvolt);
}
void CAdjcoefdlg::Sub2ToutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2totaloutputcurr);
}
void CAdjcoefdlg::Sub2AoutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2adjoutputcurr);
}
void CAdjcoefdlg::Sub2ZoutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub2zerooutputcurr);
}
//从柜3校准输入打开键盘
void CAdjcoefdlg::Sub3AactbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3adjactbusvolt);
}
void CAdjcoefdlg::Sub3TactbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3totalactbusvolt);
}
void CAdjcoefdlg::Sub3TbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3totalbusvolt);
}
void CAdjcoefdlg::Sub3AbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3adjbusvolt);
}
void CAdjcoefdlg::Sub3TnegbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3totalnegbusvolt);
}
void CAdjcoefdlg::Sub3AnegbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3adjnegbusvolt);
}
void CAdjcoefdlg::Sub3ToutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3totaloutputvolt);
}
void CAdjcoefdlg::Sub3ZoutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3zerooutputvolt);
}
void CAdjcoefdlg::Sub3AoutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3adjoutputvolt);
}
void CAdjcoefdlg::Sub3ToutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3totaloutputcurr);
}
void CAdjcoefdlg::Sub3AoutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3adjoutputcurr);
}
void CAdjcoefdlg::Sub3ZoutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub3zerooutputcurr);
}
//从柜4校准输入打开键盘
void CAdjcoefdlg::Sub4AactbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4adjactbusvolt);
}
void CAdjcoefdlg::Sub4TactbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4totalactbusvolt);
}
void CAdjcoefdlg::Sub4TbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4totalbusvolt);
}
void CAdjcoefdlg::Sub4AbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4adjbusvolt);
}
void CAdjcoefdlg::Sub4TnegbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4totalnegbusvolt);
}
void CAdjcoefdlg::Sub4AnegbuslEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4adjnegbusvolt);
}
void CAdjcoefdlg::Sub4ToutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4totaloutputvolt);
}
void CAdjcoefdlg::Sub4ZoutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4zerooutputvolt);
}
void CAdjcoefdlg::Sub4AoutvoltlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4adjoutputvolt);
}
void CAdjcoefdlg::Sub4ToutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4totaloutputcurr);
}
void CAdjcoefdlg::Sub4AoutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4adjoutputcurr);
}
void CAdjcoefdlg::Sub4ZoutcurrlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_sub4zerooutputcurr);
}
//主柜校准输入打开键盘
void CAdjcoefdlg::MATlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mAtotalvolt);
}
void CAdjcoefdlg::MAAlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mAadjvolt);
}
void CAdjcoefdlg::MBTlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mBtotalvolt);
}
void CAdjcoefdlg::MBAlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mBadjvolt);
}
void CAdjcoefdlg::MCTlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mCtotalvolt);
}
void CAdjcoefdlg::MCAlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mCadjvolt);
}
void CAdjcoefdlg::MEVTlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_evtotal);
}
void CAdjcoefdlg::MEVAlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_evadj);
}
void CAdjcoefdlg::MECTlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ectotal);
}
void CAdjcoefdlg::MECAlEdit_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ecadj);
}
//从柜1选择框勾选槽函数
void CAdjcoefdlg::s1bvcheckBox_clicked()
{
    printf("####SLOT TEST:s1bvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS1bvCabOpen==SELECT_FLAG)
    {
        m_pUi->s1bvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1bvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s1checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s1bvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS1bvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt++;
        if(m_struAdjchecknum.m_nS1checkCnt==5)
        {
            m_pUi->s1checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS1CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s1abvcheckBox_clicked()
{
    printf("####SLOT TEST:s1abvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS1abvCabOpen==SELECT_FLAG)
    {
        m_pUi->s1abvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1abvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s1checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s1abvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS1abvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt++;
        if(m_struAdjchecknum.m_nS1checkCnt==5)
        {
            m_pUi->s1checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS1CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s1nbvcheckBox_clicked()
{
    printf("####SLOT TEST:s1nbvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS1nbvCabOpen==SELECT_FLAG)
    {
        m_pUi->s1nbvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1nbvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s1checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s1nbvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS1nbvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt++;
        if(m_struAdjchecknum.m_nS1checkCnt==5)
        {
            m_pUi->s1checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS1CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s1ovcheckBox_clicked()
{
    printf("####SLOT TEST:s1ovcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS1ovCabOpen==SELECT_FLAG)
    {
        m_pUi->s1ovcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1ovCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s1checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s1ovcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS1ovCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt++;
        if(m_struAdjchecknum.m_nS1checkCnt==5)
        {
            m_pUi->s1checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS1CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s1occheckBox_clicked()
{
    printf("####SLOT TEST:s1occheckBox_clicked()####\n");
    if(m_struAdjcheck.iS1ocCabOpen==SELECT_FLAG)
    {
        m_pUi->s1occheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1ocCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s1checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS1CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s1occheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS1ocCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt++;
        if(m_struAdjchecknum.m_nS1checkCnt==5)
        {
            m_pUi->s1checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS1CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
//从柜2选择框勾选槽函数
void CAdjcoefdlg::s2bvcheckBox_clicked()
{
    printf("####SLOT TEST:s2bvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS2bvCabOpen==SELECT_FLAG)
    {
        m_pUi->s2bvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2bvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s2checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s2bvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS2bvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt++;
        if(m_struAdjchecknum.m_nS2checkCnt==5)
        {
            m_pUi->s2checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS2CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s2abvcheckBox_clicked()
{
    printf("####SLOT TEST:s2abvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS2abvCabOpen==SELECT_FLAG)
    {
        m_pUi->s2abvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2abvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s2checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s2abvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS2abvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt++;
        if(m_struAdjchecknum.m_nS2checkCnt==5)
        {
            m_pUi->s2checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS2CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s2nbvcheckBox_clicked()
{
    printf("####SLOT TEST:s2nbvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS2nbvCabOpen==SELECT_FLAG)
    {
        m_pUi->s2nbvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2nbvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s2checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s2nbvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS2nbvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt++;
        if(m_struAdjchecknum.m_nS2checkCnt==5)
        {
            m_pUi->s2checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS2CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s2ovcheckBox_clicked()
{
    printf("####SLOT TEST:s2ovcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS2ovCabOpen==SELECT_FLAG)
    {
        m_pUi->s2ovcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2ovCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s2checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s2ovcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS2ovCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt++;
        if(m_struAdjchecknum.m_nS2checkCnt==5)
        {
            m_pUi->s2checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS2CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s2occheckBox_clicked()
{
    printf("####SLOT TEST:s2occheckBox_clicked()####\n");
    if(m_struAdjcheck.iS2ocCabOpen==SELECT_FLAG)
    {
        m_pUi->s2occheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2ocCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s2checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS2CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s2occheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS2ocCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt++;
        if(m_struAdjchecknum.m_nS2checkCnt==5)
        {
            m_pUi->s2checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS2CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
//从柜3选择框勾选槽函数
void CAdjcoefdlg::s3bvcheckBox_clicked()
{
    printf("####SLOT TEST:s3bvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS3bvCabOpen==SELECT_FLAG)
    {
        m_pUi->s3bvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3bvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s3checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s3bvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS3bvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt++;
        if(m_struAdjchecknum.m_nS3checkCnt==5)
        {
            m_pUi->s3checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS3CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s3abvcheckBox_clicked()
{
    printf("####SLOT TEST:s3abvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS3abvCabOpen==SELECT_FLAG)
    {
        m_pUi->s3abvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3abvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s3checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s3abvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS3abvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt++;
        if(m_struAdjchecknum.m_nS3checkCnt==5)
        {
            m_pUi->s3checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS3CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s3nbvcheckBox_clicked()
{
    printf("####SLOT TEST:s3nbvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS3nbvCabOpen==SELECT_FLAG)
    {
        m_pUi->s3nbvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3nbvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s3checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s3nbvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS3nbvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt++;
        if(m_struAdjchecknum.m_nS3checkCnt==5)
        {
            m_pUi->s3checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS3CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s3ovcheckBox_clicked()
{
    printf("####SLOT TEST:s3ovcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS3ovCabOpen==SELECT_FLAG)
    {
        m_pUi->s3ovcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3ovCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s3checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s3ovcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS3ovCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt++;
        if(m_struAdjchecknum.m_nS3checkCnt==5)
        {
            m_pUi->s3checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS3CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s3occheckBox_clicked()
{
    printf("####SLOT TEST:s3occheckBox_clicked()####\n");
    if(m_struAdjcheck.iS3ocCabOpen==SELECT_FLAG)
    {
        m_pUi->s3occheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3ocCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s3checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS3CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s3occheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS3ocCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt++;
        if(m_struAdjchecknum.m_nS3checkCnt==5)
        {
            m_pUi->s3checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS3CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
//从柜4选择框勾选槽函数
void CAdjcoefdlg::s4bvcheckBox_clicked()
{
    printf("####SLOT TEST:s4bvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS4bvCabOpen==SELECT_FLAG)
    {
        m_pUi->s4bvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4bvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s4checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s4bvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS4bvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt++;
        if(m_struAdjchecknum.m_nS4checkCnt==5)
        {
            m_pUi->s4checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS4CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s4abvcheckBox_clicked()
{
    printf("####SLOT TEST:s4abvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS4abvCabOpen==SELECT_FLAG)
    {
        m_pUi->s4abvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4abvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s4checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s4abvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS4abvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt++;
        if(m_struAdjchecknum.m_nS4checkCnt==5)
        {
            m_pUi->s4checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS4CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s4nbvcheckBox_clicked()
{
    printf("####SLOT TEST:s4nbvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS4nbvCabOpen==SELECT_FLAG)
    {
        m_pUi->s4nbvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4nbvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s4checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s4nbvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS4nbvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt++;
        if(m_struAdjchecknum.m_nS4checkCnt==5)
        {
            m_pUi->s4checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS4CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s4ovcheckBox_clicked()
{
    printf("####SLOT TEST:s4ovcheckBox_clicked()####\n");
    if(m_struAdjcheck.iS4ovCabOpen==SELECT_FLAG)
    {
        m_pUi->s4ovcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4ovCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s4checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s4ovcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS4ovCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt++;
        if(m_struAdjchecknum.m_nS4checkCnt==5)
        {
            m_pUi->s4checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS4CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s4occheckBox_clicked()
{
    printf("####SLOT TEST:s4occheckBox_clicked()####\n");
    if(m_struAdjcheck.iS4ocCabOpen==SELECT_FLAG)
    {
        m_pUi->s4occheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4ocCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->s4checkBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iS4CabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->s4occheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iS4ocCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt++;
        if(m_struAdjchecknum.m_nS4checkCnt==5)
        {
            m_pUi->s4checkBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iS4CabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
//主柜选择框勾选槽函数
void CAdjcoefdlg::mAvcheckBox_clicked()
{
    printf("####SLOT TEST:mAvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iMAvCabOpen==SELECT_FLAG)
    {
        m_pUi->mAvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMAvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMainCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->mAvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iMAvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt++;
        if(m_struAdjchecknum.m_nMcheckCnt==5)
        {
            m_pUi->maincheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iMainCabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::mBvcheckBox_clicked()
{
    printf("####SLOT TEST:mBvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iMBvCabOpen==SELECT_FLAG)
    {
        m_pUi->mBvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMBvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMainCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->mBvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iMBvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt++;
        if(m_struAdjchecknum.m_nMcheckCnt==5)
        {
            m_pUi->maincheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iMainCabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::mCvcheckBox_clicked()
{
    printf("####SLOT TEST:mCvcheckBox_clicked()####\n");
    if(m_struAdjcheck.iMCvCabOpen==SELECT_FLAG)
    {
        m_pUi->mCvcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMCvCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMainCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->mCvcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iMCvCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt++;
        if(m_struAdjchecknum.m_nMcheckCnt==5)
        {
            m_pUi->maincheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iMainCabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::mevcheckBox_clicked()
{
    printf("####SLOT TEST:mevcheckBox_clicked()####\n");
    if(m_struAdjcheck.iMevCabOpen==SELECT_FLAG)
    {
        m_pUi->mevcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMevCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMainCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->mevcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iMevCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt++;
        if(m_struAdjchecknum.m_nMcheckCnt==5)
        {
            m_pUi->maincheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iMainCabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::meccheckBox_clicked()
{
    printf("####SLOT TEST:meccheckBox_clicked()####\n");
    if(m_struAdjcheck.iMecCabOpen==SELECT_FLAG)
    {
        m_pUi->meccheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMecCabOpen=UNSELECT_FLAG;
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iMainCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt--;
        m_struAdjchecknum.m_nAllcheckCnt--;
    }
    else
    {
        m_pUi->meccheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iMecCabOpen=SELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt++;
        if(m_struAdjchecknum.m_nMcheckCnt==5)
        {
            m_pUi->maincheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iMainCabOpen=SELECT_FLAG;
        }
        m_struAdjchecknum.m_nAllcheckCnt++;
        if(m_struAdjchecknum.m_nAllcheckCnt==25)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
//范围选择框勾选槽函数
void CAdjcoefdlg::s1checkBox_clicked()
{
    printf("####SLOT TEST:s1checkBox_clicked()####\n");
    if(m_struAdjcheck.iS1CabOpen==SELECT_FLAG)
    {
        s1select();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS1checkCnt=0;
        m_struAdjchecknum.m_nRcheckCnt--;
    }
    else
    {
        s1unselect();
        m_struAdjchecknum.m_nS1checkCnt=5;
        m_struAdjchecknum.m_nRcheckCnt++;
        if(m_struAdjchecknum.m_nRcheckCnt==5)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s2checkBox_clicked()
{
    printf("####SLOT TEST:s2checkBox_clicked()####\n");
    if(m_struAdjcheck.iS2CabOpen==SELECT_FLAG)
    {
        s2select();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS2checkCnt=0;
        m_struAdjchecknum.m_nRcheckCnt--;
    }
    else
    {
        s2unselect();
        m_struAdjchecknum.m_nS2checkCnt=5;
        m_struAdjchecknum.m_nRcheckCnt++;
        if(m_struAdjchecknum.m_nRcheckCnt==5)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s3checkBox_clicked()
{
    printf("####SLOT TEST:s3checkBox_clicked()####\n");
    if(m_struAdjcheck.iS3CabOpen==SELECT_FLAG)
    {
        s3select();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS3checkCnt=0;
        m_struAdjchecknum.m_nRcheckCnt--;
    }
    else
    {
        s3unselect();
        m_struAdjchecknum.m_nS3checkCnt=5;
        m_struAdjchecknum.m_nRcheckCnt++;
        if(m_struAdjchecknum.m_nRcheckCnt==5)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::s4checkBox_clicked()
{
    printf("####SLOT TEST:s4checkBox_clicked()####\n");
    if(m_struAdjcheck.iS4CabOpen==SELECT_FLAG)
    {
        s4select();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nS4checkCnt=0;
        m_struAdjchecknum.m_nRcheckCnt--;
    }
    else
    {
        s4unselect();
        m_struAdjchecknum.m_nS4checkCnt=5;
        m_struAdjchecknum.m_nRcheckCnt++;
        if(m_struAdjchecknum.m_nRcheckCnt==5)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::maincheckBox_clicked()
{
    printf("####SLOT TEST:maincheckBox_clicked()####\n");
    if(m_struAdjcheck.iMainCabOpen==SELECT_FLAG)
    {
        mainselect();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        m_struAdjchecknum.m_nMcheckCnt=0;
        m_struAdjchecknum.m_nRcheckCnt--;
    }
    else
    {
        mainunselect();
        m_struAdjchecknum.m_nMcheckCnt=5;
        m_struAdjchecknum.m_nRcheckCnt++;
        if(m_struAdjchecknum.m_nRcheckCnt==5)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        }
    }
}
void CAdjcoefdlg::allcheckBox_clicked()
{
    printf("####SLOT TEST:allcheckBox_clicked()####\n");
    if(m_struAdjcheck.iAllCabOpen==SELECT_FLAG)
    {
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_struAdjcheck.iAllCabOpen=UNSELECT_FLAG;
        s1select();
        s2select();
        s3select();
        s4select();
        mainselect();
        m_struAdjchecknum.m_nS1checkCnt=0;
        m_struAdjchecknum.m_nS2checkCnt=0;
        m_struAdjchecknum.m_nS3checkCnt=0;
        m_struAdjchecknum.m_nS4checkCnt=0;
        m_struAdjchecknum.m_nMcheckCnt=0;
        m_struAdjchecknum.m_nAllcheckCnt=0;
        m_struAdjchecknum.m_nRcheckCnt=0;
    }
    else
    {
        m_pUi->allcheckBox->setCheckState(Qt::Checked);
        m_struAdjcheck.iAllCabOpen=SELECT_FLAG;
        s1unselect();
        s2unselect();
        s3unselect();
        s4unselect();
        mainunselect();
        m_struAdjchecknum.m_nS1checkCnt=5;
        m_struAdjchecknum.m_nS2checkCnt=5;
        m_struAdjchecknum.m_nS3checkCnt=5;
        m_struAdjchecknum.m_nS4checkCnt=5;
        m_struAdjchecknum.m_nMcheckCnt=5;
        m_struAdjchecknum.m_nAllcheckCnt=25;
        m_struAdjchecknum.m_nRcheckCnt=5;
    }
}
void CAdjcoefdlg::s1select()
{
    m_pUi->s1checkBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS1CabOpen=UNSELECT_FLAG;
    m_pUi->s1bvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS1bvCabOpen=UNSELECT_FLAG;
    m_pUi->s1abvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS1abvCabOpen=UNSELECT_FLAG;
    m_pUi->s1nbvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS1nbvCabOpen=UNSELECT_FLAG;
    m_pUi->s1ovcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS1ovCabOpen=UNSELECT_FLAG;
    m_pUi->s1occheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS1ocCabOpen=UNSELECT_FLAG;
}
void CAdjcoefdlg::s1unselect()
{
    m_pUi->s1checkBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS1CabOpen=SELECT_FLAG;
    m_pUi->s1bvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS1bvCabOpen=SELECT_FLAG;
    m_pUi->s1abvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS1abvCabOpen=SELECT_FLAG;
    m_pUi->s1nbvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS1nbvCabOpen=SELECT_FLAG;
    m_pUi->s1ovcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS1ovCabOpen=SELECT_FLAG;
    m_pUi->s1occheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS1ocCabOpen=SELECT_FLAG;
}
void CAdjcoefdlg::s2select()
{
    m_pUi->s2checkBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS2CabOpen=UNSELECT_FLAG;
    m_pUi->s2bvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS2bvCabOpen=UNSELECT_FLAG;
    m_pUi->s2abvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS2abvCabOpen=UNSELECT_FLAG;
    m_pUi->s2nbvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS2nbvCabOpen=UNSELECT_FLAG;
    m_pUi->s2ovcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS2ovCabOpen=UNSELECT_FLAG;
    m_pUi->s2occheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS2ocCabOpen=UNSELECT_FLAG;
}
void CAdjcoefdlg::s2unselect()
{
    m_pUi->s2checkBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS2CabOpen=SELECT_FLAG;
    m_pUi->s2bvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS2bvCabOpen=SELECT_FLAG;
    m_pUi->s2abvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS2abvCabOpen=SELECT_FLAG;
    m_pUi->s2nbvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS2nbvCabOpen=SELECT_FLAG;
    m_pUi->s2ovcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS2ovCabOpen=SELECT_FLAG;
    m_pUi->s2occheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS2ocCabOpen=SELECT_FLAG;
}
void CAdjcoefdlg::s3select()
{
    m_pUi->s3checkBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS3CabOpen=UNSELECT_FLAG;
    m_pUi->s3bvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS3bvCabOpen=UNSELECT_FLAG;
    m_pUi->s3abvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS3abvCabOpen=UNSELECT_FLAG;
    m_pUi->s3nbvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS3nbvCabOpen=UNSELECT_FLAG;
    m_pUi->s3ovcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS3ovCabOpen=UNSELECT_FLAG;
    m_pUi->s3occheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS3ocCabOpen=UNSELECT_FLAG;
}
void CAdjcoefdlg::s3unselect()
{
    m_pUi->s3checkBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS3CabOpen=SELECT_FLAG;
    m_pUi->s3bvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS3bvCabOpen=SELECT_FLAG;
    m_pUi->s3abvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS3abvCabOpen=SELECT_FLAG;
    m_pUi->s3nbvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS3nbvCabOpen=SELECT_FLAG;
    m_pUi->s3ovcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS3ovCabOpen=SELECT_FLAG;
    m_pUi->s3occheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS3ocCabOpen=SELECT_FLAG;
}
void CAdjcoefdlg::s4select()
{
    m_pUi->s4checkBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS4CabOpen=UNSELECT_FLAG;
    m_pUi->s4bvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS4bvCabOpen=UNSELECT_FLAG;
    m_pUi->s4abvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS4abvCabOpen=UNSELECT_FLAG;
    m_pUi->s4nbvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS4nbvCabOpen=UNSELECT_FLAG;
    m_pUi->s4ovcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS4ovCabOpen=UNSELECT_FLAG;
    m_pUi->s4occheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iS4ocCabOpen=UNSELECT_FLAG;
}
void CAdjcoefdlg::s4unselect()
{
    m_pUi->s4checkBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS4CabOpen=SELECT_FLAG;
    m_pUi->s4bvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS4bvCabOpen=SELECT_FLAG;
    m_pUi->s4abvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS4abvCabOpen=SELECT_FLAG;
    m_pUi->s4nbvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS4nbvCabOpen=SELECT_FLAG;
    m_pUi->s4ovcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS4ovCabOpen=SELECT_FLAG;
    m_pUi->s4occheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iS4ocCabOpen=SELECT_FLAG;
}
void CAdjcoefdlg::mainselect()
{
    m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iMainCabOpen=UNSELECT_FLAG;
    m_pUi->mAvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iMAvCabOpen=UNSELECT_FLAG;
    m_pUi->mBvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iMBvCabOpen=UNSELECT_FLAG;
    m_pUi->mCvcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iMCvCabOpen=UNSELECT_FLAG;
    m_pUi->mevcheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iMevCabOpen=UNSELECT_FLAG;
    m_pUi->meccheckBox->setCheckState(Qt::Unchecked);
    m_struAdjcheck.iMecCabOpen=UNSELECT_FLAG;
}
void CAdjcoefdlg::mainunselect()
{
    m_pUi->maincheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iMainCabOpen=SELECT_FLAG;
    m_pUi->mAvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iMAvCabOpen=SELECT_FLAG;
    m_pUi->mBvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iMBvCabOpen=SELECT_FLAG;
    m_pUi->mCvcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iMCvCabOpen=SELECT_FLAG;
    m_pUi->mevcheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iMevCabOpen=SELECT_FLAG;
    m_pUi->meccheckBox->setCheckState(Qt::Checked);
    m_struAdjcheck.iMecCabOpen=SELECT_FLAG;
}
void CAdjcoefdlg::adjcoefLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("adjcoefDialog", "\346\240\241\345\207\206\347\263\273\346\225\260\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab), QApplication::translate("adjcoefDialog", "\344\270\273\346\237\234", 0, QApplication::UnicodeUTF8));
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab_2), QApplication::translate("adjcoefDialog", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab_3), QApplication::translate("adjcoefDialog", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab_4), QApplication::translate("adjcoefDialog", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab_5), QApplication::translate("adjcoefDialog", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));
        m_pUi->maincheckBox->setText(QApplication::translate("adjcoefDialog", " \344\270\273\346\237\234", 0, QApplication::UnicodeUTF8));
        m_pUi->s1checkBox->setText(QApplication::translate("adjcoefDialog", "\345\210\206\346\237\2341", 0, QApplication::UnicodeUTF8));
        m_pUi->s2checkBox->setText(QApplication::translate("adjcoefDialog", "\345\210\206\346\237\2342", 0, QApplication::UnicodeUTF8));
        m_pUi->s3checkBox->setText(QApplication::translate("adjcoefDialog", "\345\210\206\346\237\2343", 0, QApplication::UnicodeUTF8));
        m_pUi->s4checkBox->setText(QApplication::translate("adjcoefDialog", "\345\210\206\346\237\2344", 0, QApplication::UnicodeUTF8));
        m_pUi->allcheckBox->setText(QApplication::translate("adjcoefDialog", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
        m_pUi->label_9->setText(QApplication::translate("adjcoefDialog", "  \351\233\266\347\202\271\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_2->setText(QApplication::translate("adjcoefDialog", "  \346\230\276\347\244\272\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_3->setText(QApplication::translate("adjcoefDialog", "  \345\256\236\351\231\205\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->mAvcheckBox->setText(QApplication::translate("adjcoefDialog", "  A\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->mBvcheckBox->setText(QApplication::translate("adjcoefDialog", "  B\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->mCvcheckBox->setText(QApplication::translate("adjcoefDialog", "  C\347\233\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->mevcheckBox->setText(QApplication::translate("adjcoefDialog", "  \345\212\261\347\243\201\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->meccheckBox->setText(QApplication::translate("adjcoefDialog", "  \345\212\261\347\243\201\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_10->setText(QApplication::translate("adjcoefDialog", "  \351\233\266\347\202\271\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_4->setText(QApplication::translate("adjcoefDialog", "  \346\230\276\347\244\272\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_5->setText(QApplication::translate("adjcoefDialog", "  \345\256\236\351\231\205\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->s1bvcheckBox->setText(QApplication::translate("adjcoefDialog", "  \346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s1abvcheckBox->setText(QApplication::translate("adjcoefDialog", "\346\255\243\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s1nbvcheckBox->setText(QApplication::translate("adjcoefDialog", "\350\264\237\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s1ovcheckBox->setText(QApplication::translate("adjcoefDialog", "  \350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s1occheckBox->setText(QApplication::translate("adjcoefDialog", "  \350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_11->setText(QApplication::translate("adjcoefDialog", "  \351\233\266\347\202\271\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_6->setText(QApplication::translate("adjcoefDialog", "  \346\230\276\347\244\272\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_7->setText(QApplication::translate("adjcoefDialog", "  \345\256\236\351\231\205\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->s2bvcheckBox->setText(QApplication::translate("adjcoefDialog", "  \346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s2abvcheckBox->setText(QApplication::translate("adjcoefDialog", "\346\255\243\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s2nbvcheckBox->setText(QApplication::translate("adjcoefDialog", "\350\264\237\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s2ovcheckBox->setText(QApplication::translate("adjcoefDialog", "  \350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s2occheckBox->setText(QApplication::translate("adjcoefDialog", "  \350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_12->setText(QApplication::translate("adjcoefDialog", "  \351\233\266\347\202\271\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_8->setText(QApplication::translate("adjcoefDialog", "  \346\230\276\347\244\272\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_13->setText(QApplication::translate("adjcoefDialog", "  \345\256\236\351\231\205\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->s3bvcheckBox->setText(QApplication::translate("adjcoefDialog", "  \346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s3abvcheckBox->setText(QApplication::translate("adjcoefDialog", "\346\255\243\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s3nbvcheckBox->setText(QApplication::translate("adjcoefDialog", "\350\264\237\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s3ovcheckBox->setText(QApplication::translate("adjcoefDialog", "  \350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s3occheckBox->setText(QApplication::translate("adjcoefDialog", "  \350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->label_14->setText(QApplication::translate("adjcoefDialog", "  \351\233\266\347\202\271\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_15->setText(QApplication::translate("adjcoefDialog", "  \346\230\276\347\244\272\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->label_16->setText(QApplication::translate("adjcoefDialog", "  \345\256\236\351\231\205\345\200\274", 0, QApplication::UnicodeUTF8));
        m_pUi->s4bvcheckBox->setText(QApplication::translate("adjcoefDialog", "  \346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s4abvcheckBox->setText(QApplication::translate("adjcoefDialog", "\346\255\243\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s4nbvcheckBox->setText(QApplication::translate("adjcoefDialog", "\350\264\237\346\257\215\347\272\277\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s4ovcheckBox->setText(QApplication::translate("adjcoefDialog", "  \350\276\223\345\207\272\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        m_pUi->s4occheckBox->setText(QApplication::translate("adjcoefDialog", "  \350\276\223\345\207\272\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_pUi->zeroBtn->setText(QApplication::translate("adjcoefDialog", "\351\233\266\347\202\271\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8));
        m_pUi->adjcoefBtn->setText(QApplication::translate("adjcoefDialog", "\346\240\241 \345\207\206", 0, QApplication::UnicodeUTF8));
        m_pUi->resetBtn->setText(QApplication::translate("adjcoefDialog", "\345\244\215\344\275\215", 0, QApplication::UnicodeUTF8));
        m_strErrinfo = QApplication::translate("basicparasetDialog",
             "\351\224\231\350\257\257\346\217\220\347\244\272",
             0,
             QApplication::UnicodeUTF8);//错误提示
        m_strInvalidinfo = QApplication::translate("basicparasetDialog",
            "\350\276\223\345\205\245\347\232\204\346\225\260\345\200\274\344\270\215\345\220\210\346\263\225\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245",
            0,
            QApplication::UnicodeUTF8);//输入的数值不合法，请重新输入
        m_strInfo=QApplication::translate("basicparasetDialog",
            "\346\217\220\347\244\272",
            0,
            QApplication::UnicodeUTF8);//提示
        m_strFriendlytips=QApplication::translate("adjcoefDialog",
            "\345\217\213\346\203\205\346\217\220\347\244\272",
            0,
            QApplication::UnicodeUTF8);//友情提示
        m_strAdjSuccess=QApplication::translate("adjcoefDialog",
             "\346\240\241\345\207\206\346\210\220\345\212\237",
             0,
             QApplication::UnicodeUTF8);//校准成功提示语
        m_strAdjFail=QApplication::translate("adjcoefDialog",
             "\345\255\230\345\234\250\351\235\236\346\263\225\346\240\241\345\207\206",
             0,
             QApplication::UnicodeUTF8);//校准失败提示语
        m_strSaveSuccess= QApplication::translate("adjcoefDialog",
            "\345\237\272\346\234\254\345\217\202\346\225\260\351\205\215\347\275\256\346\226\207\344\273\266\344\277\235\345\255\230\346\210\220\345\212\237",
            0,
            QApplication::UnicodeUTF8);//基本参数配置文件保存成功提示语
        m_strSaveFail= QApplication::translate("adjcoefDialog",
            "\345\237\272\346\234\254\345\217\202\346\225\260\351\205\215\347\275\256\346\226\207\344\273\266\344\277\235\345\255\230\345\244\261\350\264\245,\350\257\267\346\243\200\346\237\245",
            0,
            QApplication::UnicodeUTF8);//基本参数配置文件保存失败提示语
        m_strResetSuccess=QApplication::translate("adjcoefDialog",
             "\346\240\241\345\207\206\345\244\215\344\275\215\346\210\220\345\212\237",
             0,
             QApplication::UnicodeUTF8);//复位校准成功提示语
        m_strResetFail=QApplication::translate("adjcoefDialog",
             "\346\240\241\345\207\206\345\244\215\344\275\215\345\244\261\350\264\245",
             0,
             QApplication::UnicodeUTF8);//复位校准失败提示语
    }
    else
    {
        setWindowTitle("Calibration");
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab), "Main");
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab_2), "Cab1");
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab_3), "Cab2");
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab_4), "Cab3");
        m_pUi->tabWidget->setTabText(m_pUi->tabWidget->indexOf(m_pUi->tab_5), "Cab4");
        m_pUi->maincheckBox->setText("Main");
        m_pUi->s1checkBox->setText("Cab1");
        m_pUi->s2checkBox->setText("Cab2");
        m_pUi->s3checkBox->setText("Cab3");
        m_pUi->s4checkBox->setText("Cab4");
        m_pUi->allcheckBox->setText("All");
        m_pUi->label_9->setText("     Zero value");
        m_pUi->label_2->setText("  Display value");
        m_pUi->label_3->setText("  Actual value");
        m_pUi->mAvcheckBox->setText("Phase A voltage");
        m_pUi->mBvcheckBox->setText("Phase B voltage");
        m_pUi->mCvcheckBox->setText("Phase C voltage");
        m_pUi->mevcheckBox->setText("Field voltage");
        m_pUi->meccheckBox->setText("Field current");
        m_pUi->label_10->setText("   Zero value");
        m_pUi->label_4->setText(" Display value");
        m_pUi->label_5->setText("  Actual value");
        m_pUi->s1bvcheckBox->setText("Bus voltage");
        m_pUi->s1abvcheckBox->setText("Positive Bus Voltage");
        m_pUi->s1nbvcheckBox->setText("Negative Bus Voltage");
        m_pUi->s1ovcheckBox->setText("Sub cabinet voltage");
        m_pUi->s1occheckBox->setText("Sub cabinet current");
        m_pUi->label_11->setText("   Zero value");
        m_pUi->label_6->setText(" Display value");
        m_pUi->label_7->setText("  Actual value");
        m_pUi->s2bvcheckBox->setText("Bus voltage");
        m_pUi->s2abvcheckBox->setText("Positive Bus Voltage");
        m_pUi->s2nbvcheckBox->setText("Negative Bus Voltage");
        m_pUi->s2ovcheckBox->setText("Sub cabinet voltage");
        m_pUi->s2occheckBox->setText("Sub cabinet current");
        m_pUi->label_12->setText("   Zero value");
        m_pUi->label_8->setText(" Display value");
        m_pUi->label_13->setText("  Actual value");
        m_pUi->s3bvcheckBox->setText("Bus voltage");
        m_pUi->s3abvcheckBox->setText("Positive Bus Voltage");
        m_pUi->s3nbvcheckBox->setText("Negative Bus Voltage");
        m_pUi->s3ovcheckBox->setText("Sub cabinet voltage");
        m_pUi->s3occheckBox->setText("Sub cabinet current");
        m_pUi->label_14->setText("   Zero value");
        m_pUi->label_15->setText(" Display value");
        m_pUi->label_16->setText("  Actual value");
        m_pUi->s4bvcheckBox->setText("Bus voltage");
        m_pUi->s4abvcheckBox->setText("Positive Bus Voltage");
        m_pUi->s4nbvcheckBox->setText("Negative Bus Voltage");
        m_pUi->s4ovcheckBox->setText("Sub cabinet voltage");
        m_pUi->s4occheckBox->setText("Sub cabinet current");
        m_pUi->zeroBtn->setText("Zero collect");
        m_pUi->adjcoefBtn->setText("Calibrat");
        m_pUi->resetBtn->setText("Reset");
        m_strErrinfo = "Error";//错误提示
        m_strInvalidinfo = "The value entered is not valid.Please re-enter it.";//输入的数值不合法，请重新输入
        m_strInfo="Prompting";//提示
        m_strFriendlytips="Tips";//友情提示
        m_strAdjSuccess="Calibration success";//校准成功提示语
        m_strAdjFail="Calibration failed";//校准失败提示语
        m_strSaveSuccess= "Basic parameter profile saved successfully";//基本参数配置文件保存成功提示语
        m_strSaveFail= "Basic parameter profile failed to save";//基本参数配置文件保存失败提示语
        m_strResetSuccess="Reset success";//复位校准成功提示语
        m_strResetFail="Reset failed";//复位校准失败提示语
    }
}
//返回键槽函数-实现部分,add by 2020.08.01
void CAdjcoefdlg::closeBtn_clicked()
{
     this->close();
}

//add by zw 20220223
//初始化新校准系数
void CAdjcoefdlg::newAdjcoefInit()
{
    g_newAdjcoef.fSlave1VolDCK = COMMON_K;
    g_newAdjcoef.fSlave1VolDCB = COMMON_B;
    g_newAdjcoef.fSlave2VolDCK = COMMON_K;
    g_newAdjcoef.fSlave2VolDCB = COMMON_B;
    g_newAdjcoef.fSlave3VolDCK = COMMON_K;
    g_newAdjcoef.fSlave3VolDCB = COMMON_B;
    g_newAdjcoef.fSlave4VolDCK = COMMON_K;
    g_newAdjcoef.fSlave4VolDCB = COMMON_B;
    g_newAdjcoef.fExcitVoltK = COMMON_K;
    g_newAdjcoef.fExcitVoltB = COMMON_B;
    g_newAdjcoef.fCustom11K = COMMON_K;
    g_newAdjcoef.fCustom11B = COMMON_B;
    g_newAdjcoef.fCustom12K = COMMON_K;
    g_newAdjcoef.fCustom12B = COMMON_B;
    g_newAdjcoef.fTriPhaseAVolDCK = COMMON_K;
    g_newAdjcoef.fTriPhaseAVolDCB = COMMON_B;
    g_newAdjcoef.fTriPhaseBVolDCK = COMMON_K;
    g_newAdjcoef.fTriPhaseBVolDCB = COMMON_B;
    g_newAdjcoef.fTriPhaseCVolDCK = COMMON_K;
    g_newAdjcoef.fTriPhaseCVolDCB = COMMON_B;
    g_newAdjcoef.fTotalVolACK = COMMON_K;
    g_newAdjcoef.fTotalVolACB = COMMON_B;
    g_newAdjcoef.fTotalVolDCK = COMMON_K;
    g_newAdjcoef.fTotalVolDCB = COMMON_B;
    g_newAdjcoef.fSlave1CurDCK = COMMON_K;
    g_newAdjcoef.fSlave1CurDCB = COMMON_B;
    g_newAdjcoef.fSlave2CurDCK = COMMON_K;
    g_newAdjcoef.fSlave2CurDCB = COMMON_B;
    g_newAdjcoef.fSlave3CurDCK = COMMON_K;
    g_newAdjcoef.fSlave3CurDCB = COMMON_B;
    g_newAdjcoef.fSlave4CurDCK = COMMON_K;
    g_newAdjcoef.fSlave4CurDCB = COMMON_B;
    g_newAdjcoef.fTotalSlaveCurACK = COMMON_K;
    g_newAdjcoef.fTotalSlaveCurACB = COMMON_B;
    g_newAdjcoef.fExcitCurK = COMMON_K;
    g_newAdjcoef.fExcitCurB = COMMON_B;

}

//end add by zw 20220223

