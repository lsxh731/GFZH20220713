#include "newadjdlg.h"
#include "ui_newadjdlg.h"
#include <QMessageBox>
#include <QDebug>

STRU_ADJCOEF m_struAdjcoef;
STRU_NEWADJCOEF m_newAdjcoef;
STR_NEWADJVALUE m_newAdjValue;
extern STRU_NEWADJCOEF g_newAdjcoef;
extern STRU_ADDATANEW g_newaddata;

newadjdlg::newadjdlg(QWidget *parent) :
    QDialog(parent),
    m_pUi(new Ui::newadjdlg)
{
    m_pUi = new Ui::newadjdlg;
    m_pUi->setupUi(this);
    AdjInit();

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


    connect(m_pUi->adjcoefBtn,SIGNAL(clicked()),this,SLOT(adjcoefBtn_clicked()));
    connect(m_pUi->resetBtn,SIGNAL(clicked()),this,SLOT(resetBtn_clicked()));
    connect(m_pUi->zeroBtn,SIGNAL(clicked()),this,SLOT(zeroBtn_clicked()));
    connect(m_pUi->closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));


    connect(m_pUi->allcheckBox,SIGNAL(clicked()),SLOT(allcheckBox_clicked()));
    connect(m_pUi->maincheckBox,SIGNAL(clicked()),SLOT(maincheckBox_clicked()));
    connect(m_pUi->s12checkBox,SIGNAL(clicked()),SLOT(s12checkBox_clicked()));
    connect(m_pUi->s34checkBox,SIGNAL(clicked()),SLOT(s34checkBox_clicked()));
    connect(m_pUi->sallcheckBox,SIGNAL(clicked()),SLOT(sallcheckBox_clicked()));

    //主柜
    connect(m_pUi->lineEdit_mAzerovolt,SIGNAL(clicked()),SLOT(lineEdit_mAzerovolt_clicked()));
    connect(m_pUi->lineEdit_mAshowvolt,SIGNAL(clicked()),SLOT(lineEdit_mAshowvolt_clicked()));
    connect(m_pUi->lineEdit_mArealvolt,SIGNAL(clicked()),SLOT(lineEdit_mArealvolt_clicked()));
    connect(m_pUi->lineEdit_mBzerovolt,SIGNAL(clicked()),SLOT(lineEdit_mBzerovolt_clicked()));
    connect(m_pUi->lineEdit_mBshowvolt,SIGNAL(clicked()),SLOT(lineEdit_mBshowvolt_clicked()));
    connect(m_pUi->lineEdit_mBrealvolt,SIGNAL(clicked()),SLOT(lineEdit_mBrealvolt_clicked()));
    connect(m_pUi->lineEdit_mCzerovolt,SIGNAL(clicked()),SLOT(lineEdit_mCzerovolt_clicked()));
    connect(m_pUi->lineEdit_mCshowvolt,SIGNAL(clicked()),SLOT(lineEdit_mCshowvolt_clicked()));
    connect(m_pUi->lineEdit_mCrealvolt,SIGNAL(clicked()),SLOT(lineEdit_mCrealvolt_clicked()));
    connect(m_pUi->lineEdit_mevzerovolt,SIGNAL(clicked()),SLOT(lineEdit_mevzerovolt_clicked()));
    connect(m_pUi->lineEdit_mevshowvolt,SIGNAL(clicked()),SLOT(lineEdit_mevshowvolt_clicked()));
    connect(m_pUi->lineEdit_mevrealvolt,SIGNAL(clicked()),SLOT(lineEdit_mevrealvolt_clicked()));
    connect(m_pUi->lineEdit_meczerovolt,SIGNAL(clicked()),SLOT(lineEdit_meczerovolt_clicked()));
    connect(m_pUi->lineEdit_mecshowvolt,SIGNAL(clicked()),SLOT(lineEdit_mecshowvolt_clicked()));
    connect(m_pUi->lineEdit_mecrealvolt,SIGNAL(clicked()),SLOT(lineEdit_mecrealvolt_clicked()));

    connect(m_pUi->mAvcheckBox,SIGNAL(clicked()),SLOT(mAvcheckBox_clicked()));
    connect(m_pUi->mBvcheckBox,SIGNAL(clicked()),SLOT(mBvcheckBox_clicked()));
    connect(m_pUi->mCvcheckBox,SIGNAL(clicked()),SLOT(mCvcheckBox_clicked()));
    connect(m_pUi->mevcheckBox,SIGNAL(clicked()),SLOT(mevcheckBox_clicked()));
    connect(m_pUi->meccheckBox,SIGNAL(clicked()),SLOT(meccheckBox_clicked()));

    //从柜1-2
    connect(m_pUi->lineEdit_ms1vzerovolt,SIGNAL(clicked()),SLOT(lineEdit_ms1vzerovolt_clicked()));
    connect(m_pUi->lineEdit_ms1vshowvolt,SIGNAL(clicked()),SLOT(lineEdit_ms1vshowvolt_clicked()));
    connect(m_pUi->lineEdit_ms1vrealvolt,SIGNAL(clicked()),SLOT(lineEdit_ms1vrealvolt_clicked()));
    connect(m_pUi->lineEdit_ms1azerovolt,SIGNAL(clicked()),SLOT(lineEdit_ms1azerovolt_clicked()));
    connect(m_pUi->lineEdit_ms1ashowvolt,SIGNAL(clicked()),SLOT(lineEdit_ms1ashowvolt_clicked()));
    connect(m_pUi->lineEdit_ms1arealvolt,SIGNAL(clicked()),SLOT(lineEdit_ms1arealvolt_clicked()));

    connect(m_pUi->lineEdit_ms2vzerovolt,SIGNAL(clicked()),SLOT(lineEdit_ms2vzerovolt_clicked()));
    connect(m_pUi->lineEdit_ms2vshowvolt,SIGNAL(clicked()),SLOT(lineEdit_ms2vshowvolt_clicked()));
    connect(m_pUi->lineEdit_ms2vrealvolt,SIGNAL(clicked()),SLOT(lineEdit_ms2vrealvolt_clicked()));
    connect(m_pUi->lineEdit_ms2azerovolt,SIGNAL(clicked()),SLOT(lineEdit_ms2azerovolt_clicked()));
    connect(m_pUi->lineEdit_ms2ashowvolt,SIGNAL(clicked()),SLOT(lineEdit_ms2ashowvolt_clicked()));
    connect(m_pUi->lineEdit_ms2arealvolt,SIGNAL(clicked()),SLOT(lineEdit_ms2arealvolt_clicked()));

    connect(m_pUi->ms1vcheckBox,SIGNAL(clicked()),SLOT(ms1vcheckBox_clicked()));
    connect(m_pUi->ms1acheckBox,SIGNAL(clicked()),SLOT(ms1acheckBox_clicked()));
    connect(m_pUi->ms2vcheckBox,SIGNAL(clicked()),SLOT(ms2vcheckBox_clicked()));
    connect(m_pUi->ms2acheckBox,SIGNAL(clicked()),SLOT(ms2acheckBox_clicked()));

    //从柜3-4
    connect(m_pUi->lineEdit_ms3vzerovolt,SIGNAL(clicked()),SLOT(lineEdit_ms3vzerovolt_clicked()));
    connect(m_pUi->lineEdit_ms3vshowvolt,SIGNAL(clicked()),SLOT(lineEdit_ms3vshowvolt_clicked()));
    connect(m_pUi->lineEdit_ms3vrealvolt,SIGNAL(clicked()),SLOT(lineEdit_ms3vrealvolt_clicked()));
    connect(m_pUi->lineEdit_ms3azerovolt,SIGNAL(clicked()),SLOT(lineEdit_ms3azerovolt_clicked()));
    connect(m_pUi->lineEdit_ms3ashowvolt,SIGNAL(clicked()),SLOT(lineEdit_ms3ashowvolt_clicked()));
    connect(m_pUi->lineEdit_ms3arealvolt,SIGNAL(clicked()),SLOT(lineEdit_ms3arealvolt_clicked()));

    connect(m_pUi->lineEdit_ms4vzerovolt,SIGNAL(clicked()),SLOT(lineEdit_ms4vzerovolt_clicked()));
    connect(m_pUi->lineEdit_ms4vshowvolt,SIGNAL(clicked()),SLOT(lineEdit_ms4vshowvolt_clicked()));
    connect(m_pUi->lineEdit_ms4vrealvolt,SIGNAL(clicked()),SLOT(lineEdit_ms4vrealvolt_clicked()));
    connect(m_pUi->lineEdit_ms4azerovolt,SIGNAL(clicked()),SLOT(lineEdit_ms4azerovolt_clicked()));
    connect(m_pUi->lineEdit_ms4ashowvolt,SIGNAL(clicked()),SLOT(lineEdit_ms4ashowvolt_clicked()));
    connect(m_pUi->lineEdit_ms4arealvolt,SIGNAL(clicked()),SLOT(lineEdit_ms4arealvolt_clicked()));

    connect(m_pUi->ms3vcheckBox,SIGNAL(clicked()),SLOT(ms3vcheckBox_clicked()));
    connect(m_pUi->ms3acheckBox,SIGNAL(clicked()),SLOT(ms3acheckBox_clicked()));
    connect(m_pUi->ms4vcheckBox,SIGNAL(clicked()),SLOT(ms4vcheckBox_clicked()));
    connect(m_pUi->ms4acheckBox,SIGNAL(clicked()),SLOT(ms4acheckBox_clicked()));

    //从柜-总
    connect(m_pUi->lineEdit_movazerovolt,SIGNAL(clicked()),SLOT(lineEdit_movazerovolt_clicked()));
    connect(m_pUi->lineEdit_movashowvolt,SIGNAL(clicked()),SLOT(lineEdit_movashowvolt_clicked()));
    connect(m_pUi->lineEdit_movarealvolt,SIGNAL(clicked()),SLOT(lineEdit_movarealvolt_clicked()));
    connect(m_pUi->lineEdit_movdzerovolt,SIGNAL(clicked()),SLOT(lineEdit_movdzerovolt_clicked()));
    connect(m_pUi->lineEdit_movdshowvolt,SIGNAL(clicked()),SLOT(lineEdit_movdshowvolt_clicked()));
    connect(m_pUi->lineEdit_movdrealvolt,SIGNAL(clicked()),SLOT(lineEdit_movdrealvolt_clicked()));
    connect(m_pUi->lineEdit_mocazerovolt,SIGNAL(clicked()),SLOT(lineEdit_mocazerovolt_clicked()));
    connect(m_pUi->lineEdit_mocashowvolt,SIGNAL(clicked()),SLOT(lineEdit_mocashowvolt_clicked()));
    connect(m_pUi->lineEdit_mocarealvolt,SIGNAL(clicked()),SLOT(lineEdit_mocarealvolt_clicked()));
    connect(m_pUi->lineEdit_mcus1zerovolt,SIGNAL(clicked()),SLOT(lineEdit_mcus1zerovolt_clicked()));
    connect(m_pUi->lineEdit_mcus1showvolt,SIGNAL(clicked()),SLOT(lineEdit_mcus1showvolt_clicked()));
    connect(m_pUi->lineEdit_mcus1realvolt,SIGNAL(clicked()),SLOT(lineEdit_mcus1realvolt_clicked()));
    connect(m_pUi->lineEdit_mcus2zerovolt,SIGNAL(clicked()),SLOT(lineEdit_mcus2zerovolt_clicked()));
    connect(m_pUi->lineEdit_mcus2showvolt,SIGNAL(clicked()),SLOT(lineEdit_mcus2showvolt_clicked()));
    connect(m_pUi->lineEdit_mcus2realvolt,SIGNAL(clicked()),SLOT(lineEdit_mcus2realvolt_clicked()));

    connect(m_pUi->movacheckBox,SIGNAL(clicked()),SLOT(movacheckBox_clicked()));
    connect(m_pUi->movdcheckBox,SIGNAL(clicked()),SLOT(movdcheckBox_clicked()));
    connect(m_pUi->mocacheckBox,SIGNAL(clicked()),SLOT(mocacheckBox_clicked()));
    connect(m_pUi->mcus1checkBox,SIGNAL(clicked()),SLOT(mcus1checkBox_clicked()));
    connect(m_pUi->mcus2checkBox,SIGNAL(clicked()),SLOT(mcus2checkBox_clicked()));

    MainUnSeleck();
    S12UnSeleck();
    S34UnSeleck();
    SALLUnSeleck();


}

newadjdlg::~newadjdlg()
{
    delete m_pUi;
}

void newadjdlg::adjcoefBtn_clicked()
{
    bool ok=false;
    int cnt=0;
    int adjcnt=0;
    float fAdjcoefK=1.0;
    float fAdjcoefB=0.0;
    if(m_NewAdch.iMAvOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[0] = m_pUi->lineEdit_mAshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[0] = m_pUi->lineEdit_mArealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[0]-m_newAdjValue.fZeroValue[0])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[0]/(m_newAdjValue.fRealValue[0]-m_newAdjValue.fZeroValue[0]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[0]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fTriPhaseAVolDCK = fAdjcoefK;
                m_newAdjcoef.fTriPhaseAVolDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iMBvOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[1] = m_pUi->lineEdit_mBshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[1] = m_pUi->lineEdit_mBrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[1]-m_newAdjValue.fZeroValue[1])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[1]/(m_newAdjValue.fRealValue[1]-m_newAdjValue.fZeroValue[1]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[1]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fTriPhaseBVolDCK = fAdjcoefK;
                m_newAdjcoef.fTriPhaseBVolDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iMCvOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[2] = m_pUi->lineEdit_mCshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[2] = m_pUi->lineEdit_mCrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[2]-m_newAdjValue.fZeroValue[2])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[2]/(m_newAdjValue.fRealValue[2]-m_newAdjValue.fZeroValue[2]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[2]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fTriPhaseCVolDCK = fAdjcoefK;
                m_newAdjcoef.fTriPhaseCVolDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iEvOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[3] = m_pUi->lineEdit_mevshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[3] = m_pUi->lineEdit_mevrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[3]-m_newAdjValue.fZeroValue[3])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[3]/(m_newAdjValue.fRealValue[3]-m_newAdjValue.fZeroValue[3]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[3]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fExcitVoltK = fAdjcoefK;
                m_newAdjcoef.fExcitVoltB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iEcOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[4] = m_pUi->lineEdit_mecshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[4] = m_pUi->lineEdit_mecrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[4]-m_newAdjValue.fZeroValue[4])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[4]/(m_newAdjValue.fRealValue[4]-m_newAdjValue.fZeroValue[4]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[4]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fExcitCurK = fAdjcoefK;
                m_newAdjcoef.fExcitCurB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iS1vOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[5] = m_pUi->lineEdit_ms1vshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[5] = m_pUi->lineEdit_ms1vrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[5]-m_newAdjValue.fZeroValue[5])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[5]/(m_newAdjValue.fRealValue[5]-m_newAdjValue.fZeroValue[5]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[5]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fSlave1VolDCK = fAdjcoefK;
                m_newAdjcoef.fSlave1VolDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iS1cOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[6] = m_pUi->lineEdit_ms1ashowvolt->text().toFloat();
        m_newAdjValue.fRealValue[6] = m_pUi->lineEdit_ms1arealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[6]-m_newAdjValue.fZeroValue[6])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[6]/(m_newAdjValue.fRealValue[6]-m_newAdjValue.fZeroValue[6]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[6]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fSlave1CurDCK = fAdjcoefK;
                m_newAdjcoef.fSlave1CurDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iS2vOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[7] = m_pUi->lineEdit_ms2vshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[7] = m_pUi->lineEdit_ms2vrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[7]-m_newAdjValue.fZeroValue[7])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[7]/(m_newAdjValue.fRealValue[7]-m_newAdjValue.fZeroValue[7]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[7]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fSlave2VolDCK = fAdjcoefK;
                m_newAdjcoef.fSlave2VolDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iS2cOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[8] = m_pUi->lineEdit_ms2ashowvolt->text().toFloat();
        m_newAdjValue.fRealValue[8] = m_pUi->lineEdit_ms2arealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[8]-m_newAdjValue.fZeroValue[8])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[8]/(m_newAdjValue.fRealValue[8]-m_newAdjValue.fZeroValue[8]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[8]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fSlave2CurDCK = fAdjcoefK;
                m_newAdjcoef.fSlave2CurDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iS3vOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[9] = m_pUi->lineEdit_ms3vshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[9] = m_pUi->lineEdit_ms3vrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[9]-m_newAdjValue.fZeroValue[9])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[9]/(m_newAdjValue.fRealValue[9]-m_newAdjValue.fZeroValue[9]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[9]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fSlave3VolDCK = fAdjcoefK;
                m_newAdjcoef.fSlave3VolDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iS3cOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[10] = m_pUi->lineEdit_ms3ashowvolt->text().toFloat();
        m_newAdjValue.fRealValue[10] = m_pUi->lineEdit_ms3arealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[10]-m_newAdjValue.fZeroValue[10])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[10]/(m_newAdjValue.fRealValue[10]-m_newAdjValue.fZeroValue[10]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[10]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fSlave3CurDCK = fAdjcoefK;
                m_newAdjcoef.fSlave3CurDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iS4vOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[11] = m_pUi->lineEdit_ms4vshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[11] = m_pUi->lineEdit_ms4vrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[11]-m_newAdjValue.fZeroValue[11])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[11]/(m_newAdjValue.fRealValue[11]-m_newAdjValue.fZeroValue[11]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[11]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fSlave4VolDCK = fAdjcoefK;
                m_newAdjcoef.fSlave4VolDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iS4cOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[12] = m_pUi->lineEdit_ms4ashowvolt->text().toFloat();
        m_newAdjValue.fRealValue[12] = m_pUi->lineEdit_ms4arealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[12]-m_newAdjValue.fZeroValue[12])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[12]/(m_newAdjValue.fRealValue[12]-m_newAdjValue.fZeroValue[12]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[12]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fSlave4CurDCK = fAdjcoefK;
                m_newAdjcoef.fSlave4CurDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iSAvacOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[13] = m_pUi->lineEdit_movashowvolt->text().toFloat();
        m_newAdjValue.fRealValue[13] = m_pUi->lineEdit_movarealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[13]-m_newAdjValue.fZeroValue[13])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[13]/(m_newAdjValue.fRealValue[13]-m_newAdjValue.fZeroValue[13]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[13]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fTotalVolACK = fAdjcoefK;
                m_newAdjcoef.fTotalVolACB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iSAvdcOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[14] = m_pUi->lineEdit_movdshowvolt->text().toFloat();
        m_newAdjValue.fRealValue[14] = m_pUi->lineEdit_movdrealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[14]-m_newAdjValue.fZeroValue[14])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[14]/(m_newAdjValue.fRealValue[14]-m_newAdjValue.fZeroValue[14]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[14]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fTotalVolDCK = fAdjcoefK;
                m_newAdjcoef.fTotalVolDCB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iSAcacOpen==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[15] = m_pUi->lineEdit_mocashowvolt->text().toFloat();
        m_newAdjValue.fRealValue[15] = m_pUi->lineEdit_mocarealvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[15]-m_newAdjValue.fZeroValue[15])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[15]/(m_newAdjValue.fRealValue[15]-m_newAdjValue.fZeroValue[15]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[15]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fTotalSlaveCurACK = fAdjcoefK;
                m_newAdjcoef.fTotalSlaveCurACB = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iCus1Open==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[16] = m_pUi->lineEdit_mcus1showvolt->text().toFloat();
        m_newAdjValue.fRealValue[16] = m_pUi->lineEdit_mcus1realvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[16]-m_newAdjValue.fZeroValue[16])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[16]/(m_newAdjValue.fRealValue[16]-m_newAdjValue.fZeroValue[16]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[16]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fCustom11K = fAdjcoefK;
                m_newAdjcoef.fCustom11B = fAdjcoefB;
            }
            else
            {
                cnt++;
            }
        }
    }
    if(m_NewAdch.iCus2Open==SELECT_FLAG)
    {
        m_newAdjValue.fShowValue[17] = m_pUi->lineEdit_mcus2showvolt->text().toFloat();
        m_newAdjValue.fRealValue[17] = m_pUi->lineEdit_mcus2realvolt->text().toFloat();
        if(qAbs(m_newAdjValue.fShowValue[17]-m_newAdjValue.fZeroValue[17])>DELT_FVALUE)
        {
            fAdjcoefK = m_newAdjValue.fShowValue[17]/(m_newAdjValue.fRealValue[17]-m_newAdjValue.fZeroValue[17]);
            fAdjcoefB = -m_newAdjValue.fZeroValue[17]*fAdjcoefK;
            adjcnt++;
            if(fAdjcoefK>0.9 && fAdjcoefK<1.1)
            {
                m_newAdjcoef.fCustom12K = fAdjcoefK;
                m_newAdjcoef.fCustom12B = fAdjcoefB;
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
    if(m_IniAdjcoef.writeneweAdjcoefInifile(m_newAdjcoef))
    {
        //把参数m_newAdjcoef赋值给全局变量g_newAdjcoef,add by zw 2022.02.23
        memcpy(&g_newAdjcoef,&m_newAdjcoef,sizeof(m_newAdjcoef));
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

void newadjdlg::resetBtn_clicked()
{
    if(m_NewAdch.iMAvOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fTriPhaseAVolDCK = COMMON_K;
        m_newAdjcoef.fTriPhaseAVolDCB = COMMON_B;
    }
    if(m_NewAdch.iMBvOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fTriPhaseBVolDCK = COMMON_K;
        m_newAdjcoef.fTriPhaseBVolDCB = COMMON_B;
    }
    if(m_NewAdch.iMCvOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fTriPhaseCVolDCK = COMMON_K;
        m_newAdjcoef.fTriPhaseCVolDCB = COMMON_B;
    }
    if(m_NewAdch.iEvOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fExcitVoltK = COMMON_K;
        m_newAdjcoef.fExcitVoltB = COMMON_B;
    }
    if(m_NewAdch.iEcOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fExcitCurK = COMMON_K;
        m_newAdjcoef.fExcitCurB = COMMON_B;
    }
    if(m_NewAdch.iS1vOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fSlave1VolDCK = COMMON_K;
        m_newAdjcoef.fSlave1VolDCB = COMMON_B;
    }
    if(m_NewAdch.iS1cOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fSlave1CurDCK = COMMON_K;
        m_newAdjcoef.fSlave1CurDCB = COMMON_B;
    }
    if(m_NewAdch.iS2vOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fSlave2VolDCK = COMMON_K;
        m_newAdjcoef.fSlave2VolDCB = COMMON_B;
    }
    if(m_NewAdch.iS2cOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fSlave2CurDCK = COMMON_K;
        m_newAdjcoef.fSlave2CurDCB = COMMON_B;
    }
    if(m_NewAdch.iS3vOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fSlave3VolDCK = COMMON_K;
        m_newAdjcoef.fSlave3VolDCB = COMMON_B;
    }
    if(m_NewAdch.iS3cOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fSlave3CurDCK = COMMON_K;
        m_newAdjcoef.fSlave3CurDCB = COMMON_B;
    }
    if(m_NewAdch.iS4vOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fSlave4VolDCK = COMMON_K;
        m_newAdjcoef.fSlave4VolDCB = COMMON_B;
    }
    if(m_NewAdch.iS4cOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fSlave4CurDCK = COMMON_K;
        m_newAdjcoef.fSlave4CurDCB = COMMON_B;
    }
    if(m_NewAdch.iSAvacOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fTotalVolACK = COMMON_K;
        m_newAdjcoef.fTotalVolACB = COMMON_B;
    }
    if(m_NewAdch.iSAvdcOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fTotalVolDCK = COMMON_K;
        m_newAdjcoef.fTotalVolDCB = COMMON_B;
    }
    if(m_NewAdch.iSAcacOpen==SELECT_FLAG)
    {
        m_newAdjcoef.fTotalSlaveCurACK = COMMON_K;
        m_newAdjcoef.fTotalSlaveCurACB = COMMON_B;
    }
    if(m_NewAdch.iCus1Open==SELECT_FLAG)
    {
        m_newAdjcoef.fCustom11K = COMMON_K;
        m_newAdjcoef.fCustom11B = COMMON_B;
    }
    if(m_NewAdch.iCus2Open==SELECT_FLAG)
    {
        m_newAdjcoef.fCustom12K = COMMON_K;
        m_newAdjcoef.fCustom12B = COMMON_B;
    }

    if(m_IniAdjcoef.writeneweAdjcoefInifile(m_newAdjcoef))
    {
        //把参数m_newAdjcoef赋值给全局变量g_newAdjcoef,add by zw 2022.02.23
        memcpy(&g_newAdjcoef,&m_newAdjcoef,sizeof(m_newAdjcoef));
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

void newadjdlg::zeroBtn_clicked()
{
    if(m_NewAdch.iMAvOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[0] = g_newaddata.fTriPhaseAVolDC;
        m_pUi->lineEdit_mAzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[0],'f',2));
    }
    if(m_NewAdch.iMBvOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[1] = g_newaddata.fTriPhaseBVolDC;
        m_pUi->lineEdit_mBzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[1],'f',2));
    }
    if(m_NewAdch.iMCvOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[2] = g_newaddata.fTriPhaseCVolDC;
        m_pUi->lineEdit_mCzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[2],'f',2));
    }
    if(m_NewAdch.iEvOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[3] = g_newaddata.fExcitVolt;
        m_pUi->lineEdit_mevzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[3],'f',2));
    }
    if(m_NewAdch.iEcOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[4] = g_newaddata.fExcitCur;
        m_pUi->lineEdit_meczerovolt->setText(QString::number(m_newAdjValue.fZeroValue[4],'f',2));
    }
    if(m_NewAdch.iS1vOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[5] = g_newaddata.fSlave1VolDC;
        m_pUi->lineEdit_ms1vzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[5],'f',2));
    }
    if(m_NewAdch.iS1cOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[6] = g_newaddata.fSlave1CurDC;
        m_pUi->lineEdit_ms1azerovolt->setText(QString::number(m_newAdjValue.fZeroValue[6],'f',2));
    }
    if(m_NewAdch.iS2vOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[7] = g_newaddata.fSlave2VolDC;
        m_pUi->lineEdit_ms2vzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[7],'f',2));
    }
    if(m_NewAdch.iS2cOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[8] = g_newaddata.fSlave2CurDC;
        m_pUi->lineEdit_ms2azerovolt->setText(QString::number(m_newAdjValue.fZeroValue[8],'f',2));
    }
    if(m_NewAdch.iS3vOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[9] = g_newaddata.fSlave3VolDC;
        m_pUi->lineEdit_ms3vzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[9],'f',2));
    }
    if(m_NewAdch.iS3cOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[10] = g_newaddata.fSlave3CurDC;
        m_pUi->lineEdit_ms3azerovolt->setText(QString::number(m_newAdjValue.fZeroValue[10],'f',2));
    }
    if(m_NewAdch.iS4vOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[11] = g_newaddata.fSlave4VolDC;
        m_pUi->lineEdit_ms4vzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[11],'f',2));
    }
    if(m_NewAdch.iS4cOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[12] = g_newaddata.fSlave4CurDC;
        m_pUi->lineEdit_ms4azerovolt->setText(QString::number(m_newAdjValue.fZeroValue[12],'f',2));
    }
    if(m_NewAdch.iSAvacOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[13] = g_newaddata.fTotalVolAC;
        m_pUi->lineEdit_movazerovolt->setText(QString::number(m_newAdjValue.fZeroValue[13],'f',2));
    }
    if(m_NewAdch.iSAvdcOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[14] = g_newaddata.fTotalVolDC;
        m_pUi->lineEdit_movdzerovolt->setText(QString::number(m_newAdjValue.fZeroValue[14],'f',2));
    }
    if(m_NewAdch.iSAcacOpen==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[15] = g_newaddata.fTotalSlaveCurAC;
        m_pUi->lineEdit_mocazerovolt->setText(QString::number(m_newAdjValue.fZeroValue[15],'f',2));
    }
    if(m_NewAdch.iCus1Open==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[16] = g_newaddata.fCustom11;
        m_pUi->lineEdit_mcus1zerovolt->setText(QString::number(m_newAdjValue.fZeroValue[16],'f',2));
    }
    if(m_NewAdch.iCus2Open==SELECT_FLAG)
    {
        m_newAdjValue.fZeroValue[17] = g_newaddata.fCustom12;
        m_pUi->lineEdit_mcus2zerovolt->setText(QString::number(m_newAdjValue.fZeroValue[17],'f',2));
    }
}

void newadjdlg::AdjInit()
{
    int i;

    m_pUi->tabWidget->setCurrentIndex(0);
    m_NewAdchnum.m_nAllcheckCnt = 0;
    m_NewAdchnum.m_nMcheckCnt = 0;
    m_NewAdchnum.m_nS12checkCnt = 0;
    m_NewAdchnum.m_nS34checkCnt = 0;
    m_NewAdchnum.m_nSALLcheckCnt = 0;
    if(!m_IniAdjcoef.readnewAdjcoefInifile(m_newAdjcoef))
    {
        m_newAdjcoef.fSlave1VolDCK = COMMON_K;
        m_newAdjcoef.fSlave1VolDCB = COMMON_B;
        m_newAdjcoef.fSlave2VolDCK = COMMON_K;
        m_newAdjcoef.fSlave2VolDCB = COMMON_B;
        m_newAdjcoef.fSlave3VolDCK = COMMON_K;
        m_newAdjcoef.fSlave3VolDCB = COMMON_B;
        m_newAdjcoef.fSlave4VolDCK = COMMON_K;
        m_newAdjcoef.fSlave4VolDCB = COMMON_B;
        m_newAdjcoef.fExcitVoltK = COMMON_K;
        m_newAdjcoef.fExcitVoltB = COMMON_B;
        m_newAdjcoef.fCustom11K = COMMON_K;
        m_newAdjcoef.fCustom11B = COMMON_B;
        m_newAdjcoef.fCustom12K = COMMON_K;
        m_newAdjcoef.fCustom12B = COMMON_B;
        m_newAdjcoef.fTriPhaseAVolDCK = COMMON_K;
        m_newAdjcoef.fTriPhaseAVolDCB = COMMON_B;
        m_newAdjcoef.fTriPhaseBVolDCK = COMMON_K;
        m_newAdjcoef.fTriPhaseBVolDCB = COMMON_B;
        m_newAdjcoef.fTriPhaseCVolDCK = COMMON_K;
        m_newAdjcoef.fTriPhaseCVolDCB = COMMON_B;
        m_newAdjcoef.fTotalVolACK = COMMON_K;
        m_newAdjcoef.fTotalVolACB = COMMON_B;
        m_newAdjcoef.fTotalVolDCK = COMMON_K;
        m_newAdjcoef.fTotalVolDCB = COMMON_B;
        m_newAdjcoef.fSlave1CurDCK = COMMON_K;
        m_newAdjcoef.fSlave1CurDCB = COMMON_B;
        m_newAdjcoef.fSlave2CurDCK = COMMON_K;
        m_newAdjcoef.fSlave2CurDCB = COMMON_B;
        m_newAdjcoef.fSlave3CurDCK = COMMON_K;
        m_newAdjcoef.fSlave3CurDCB = COMMON_B;
        m_newAdjcoef.fSlave4CurDCK = COMMON_K;
        m_newAdjcoef.fSlave4CurDCB = COMMON_B;
        m_newAdjcoef.fTotalSlaveCurACK = COMMON_K;
        m_newAdjcoef.fTotalSlaveCurACB = COMMON_B;
        m_newAdjcoef.fExcitCurK = COMMON_K;
        m_newAdjcoef.fExcitCurB = COMMON_B;
    }

    for(i=0;i<18;i++)
    {
        m_newAdjValue.fRealValue[i] = 1.00;
        m_newAdjValue.fShowValue[i] = 1.00;
        m_newAdjValue.fZeroValue[i] = 0.00;
    }


//    m_pUi->lineEdit_mAzerovolt->setText(QString::number(m_newAdjcoef.fSlave1VolDCK,'f',2));
    m_IniAdjcoef.writeneweAdjcoefInifile(m_newAdjcoef);

}

void newadjdlg::allcheckBox_clicked()
{
    if(m_NewAdch.iAllOpen==SELECT_FLAG)
    {
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_NewAdch.iAllOpen=UNSELECT_FLAG;
        MainUnSeleck();
        S12UnSeleck();
        S34UnSeleck();
        SALLUnSeleck();
        m_NewAdchnum.m_nMcheckCnt=0;
        m_NewAdchnum.m_nS12checkCnt=0;
        m_NewAdchnum.m_nS34checkCnt=0;
        m_NewAdchnum.m_nSALLcheckCnt=0;
        m_NewAdchnum.m_nAllcheckCnt=0;
    }
    else
    {
        m_pUi->allcheckBox->setCheckState(Qt::Checked);
        m_NewAdch.iAllOpen=SELECT_FLAG;
        MainSeleck();
        S12Seleck();
        S34Seleck();
        SALLSeleck();
        m_NewAdchnum.m_nMcheckCnt=5;
        m_NewAdchnum.m_nS12checkCnt=4;
        m_NewAdchnum.m_nS34checkCnt=4;
        m_NewAdchnum.m_nSALLcheckCnt=5;
        m_NewAdchnum.m_nAllcheckCnt=4;
    }
}

void newadjdlg::maincheckBox_clicked()
{
    if(m_NewAdch.iMainOpen==SELECT_FLAG)
    {
        MainUnSeleck();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_NewAdch.iAllOpen=UNSELECT_FLAG;
        m_NewAdchnum.m_nMcheckCnt=0;
        m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
    {
        MainSeleck();
        m_NewAdchnum.m_nMcheckCnt=5;
        m_NewAdchnum.m_nAllcheckCnt++;
        if(m_NewAdchnum.m_nAllcheckCnt==4)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_NewAdch.iAllOpen=SELECT_FLAG;
        }
    }
}

void newadjdlg::s12checkBox_clicked()
{
    if(m_NewAdch.iS12Open==SELECT_FLAG)
    {
        S12UnSeleck();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_NewAdch.iAllOpen=UNSELECT_FLAG;
        m_NewAdchnum.m_nS12checkCnt=0;
        m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
    {
        S12Seleck();
        m_NewAdchnum.m_nS12checkCnt=4;
        m_NewAdchnum.m_nAllcheckCnt++;
        if(m_NewAdchnum.m_nAllcheckCnt==4)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_NewAdch.iAllOpen=SELECT_FLAG;
        }
    }
}

void newadjdlg::s34checkBox_clicked()
{
    if(m_NewAdch.iS34Open==SELECT_FLAG)
    {
        S34UnSeleck();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_NewAdch.iAllOpen=UNSELECT_FLAG;
        m_NewAdchnum.m_nS34checkCnt=0;
        m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
    {
        S34Seleck();
        m_NewAdchnum.m_nS34checkCnt=4;
        m_NewAdchnum.m_nAllcheckCnt++;
        if(m_NewAdchnum.m_nAllcheckCnt==4)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_NewAdch.iAllOpen=SELECT_FLAG;
        }
    }
}

void newadjdlg::sallcheckBox_clicked()
{
    if(m_NewAdch.iSAllOpen==SELECT_FLAG)
    {
        SALLUnSeleck();
        m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
        m_NewAdch.iAllOpen=UNSELECT_FLAG;
        m_NewAdchnum.m_nSALLcheckCnt=0;
        m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
    {
        SALLSeleck();
        m_NewAdchnum.m_nSALLcheckCnt=5;
        m_NewAdchnum.m_nAllcheckCnt++;
        if(m_NewAdchnum.m_nAllcheckCnt==4)
        {
            m_pUi->allcheckBox->setCheckState(Qt::Checked);
            m_NewAdch.iAllOpen=SELECT_FLAG;
        }
    }
}



//主柜checkbox
void newadjdlg::mAvcheckBox_clicked()
{
    if(m_NewAdch.iMAvOpen == SELECT_FLAG)
    {
       m_pUi->mAvcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iMAvOpen = UNSELECT_FLAG;
       m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iMainOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->mAvcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iMAvOpen = SELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt++;
       if(m_NewAdchnum.m_nMcheckCnt == 5)
       {
           m_pUi->maincheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iMainOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::mBvcheckBox_clicked()
{
    if(m_NewAdch.iMBvOpen == SELECT_FLAG)
    {
       m_pUi->mBvcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iMBvOpen = UNSELECT_FLAG;
       m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iMainOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->mBvcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iMBvOpen = SELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt++;
       if(m_NewAdchnum.m_nMcheckCnt == 5)
       {
           m_pUi->maincheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iMainOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::mCvcheckBox_clicked()
{
    if(m_NewAdch.iMCvOpen == SELECT_FLAG)
    {
       m_pUi->mCvcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iMCvOpen = UNSELECT_FLAG;
       m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iMainOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->mCvcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iMCvOpen = SELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt++;
       if(m_NewAdchnum.m_nMcheckCnt == 5)
       {
           m_pUi->maincheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iMainOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::mevcheckBox_clicked()
{
    if(m_NewAdch.iEvOpen == SELECT_FLAG)
    {
       m_pUi->mevcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iEvOpen = UNSELECT_FLAG;
       m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iMainOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->mevcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iEvOpen = SELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt++;
       if(m_NewAdchnum.m_nMcheckCnt == 5)
       {
           m_pUi->maincheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iMainOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::meccheckBox_clicked()
{
    if(m_NewAdch.iEcOpen == SELECT_FLAG)
    {
       m_pUi->meccheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iEcOpen = UNSELECT_FLAG;
       m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iMainOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->meccheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iEcOpen = SELECT_FLAG;
       m_NewAdchnum.m_nMcheckCnt++;
       if(m_NewAdchnum.m_nMcheckCnt == 5)
       {
           m_pUi->maincheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iMainOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

//S1-2 checkbox
void newadjdlg::ms1vcheckBox_clicked()
{
    if(m_NewAdch.iS1vOpen == SELECT_FLAG)
    {
       m_pUi->ms1vcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS1vOpen = UNSELECT_FLAG;
       m_pUi->s12checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS12Open = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nS12checkCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->ms1vcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iS1vOpen = SELECT_FLAG;
       m_NewAdchnum.m_nS12checkCnt++;
       if(m_NewAdchnum.m_nS12checkCnt == 4)
       {
           m_pUi->s12checkBox->setCheckState(Qt::Checked);
           m_NewAdch.iS12Open = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::ms1acheckBox_clicked()
{
    if(m_NewAdch.iS1cOpen == SELECT_FLAG)
    {
       m_pUi->ms1acheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS1cOpen = UNSELECT_FLAG;
       m_pUi->s12checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS12Open = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nS12checkCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->ms1acheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iS1cOpen = SELECT_FLAG;
       m_NewAdchnum.m_nS12checkCnt++;
       if(m_NewAdchnum.m_nS12checkCnt == 4)
       {
           m_pUi->s12checkBox->setCheckState(Qt::Checked);
           m_NewAdch.iS12Open = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::ms2vcheckBox_clicked()
{
    if(m_NewAdch.iS2vOpen == SELECT_FLAG)
    {
       m_pUi->ms2vcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS2vOpen = UNSELECT_FLAG;
       m_pUi->s12checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS12Open = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nS12checkCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->ms2vcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iS2vOpen = SELECT_FLAG;
       m_NewAdchnum.m_nS12checkCnt++;
       if(m_NewAdchnum.m_nS12checkCnt == 4)
       {
           m_pUi->s12checkBox->setCheckState(Qt::Checked);
           m_NewAdch.iS12Open = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::ms2acheckBox_clicked()
{
    if(m_NewAdch.iS2cOpen == SELECT_FLAG)
    {
       m_pUi->ms2acheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS2cOpen = UNSELECT_FLAG;
       m_pUi->s12checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS12Open = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nS12checkCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->ms2acheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iS2cOpen = SELECT_FLAG;
       m_NewAdchnum.m_nS12checkCnt++;
       if(m_NewAdchnum.m_nS12checkCnt == 4)
       {
           m_pUi->s12checkBox->setCheckState(Qt::Checked);
           m_NewAdch.iS12Open = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

//S3-4 checkbox
void newadjdlg::ms3vcheckBox_clicked()
{
    if(m_NewAdch.iS3vOpen == SELECT_FLAG)
    {
       m_pUi->ms3vcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS3vOpen = UNSELECT_FLAG;
       m_pUi->s34checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS34Open = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nS34checkCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->ms3vcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iS3vOpen = SELECT_FLAG;
       m_NewAdchnum.m_nS34checkCnt++;
       if(m_NewAdchnum.m_nS34checkCnt == 4)
       {
           m_pUi->s34checkBox->setCheckState(Qt::Checked);
           m_NewAdch.iS34Open = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::ms3acheckBox_clicked()
{
    if(m_NewAdch.iS3cOpen == SELECT_FLAG)
    {
       m_pUi->ms3acheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS3cOpen = UNSELECT_FLAG;
       m_pUi->s34checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS34Open = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nS34checkCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->ms3acheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iS3cOpen = SELECT_FLAG;
       m_NewAdchnum.m_nS34checkCnt++;
       if(m_NewAdchnum.m_nS34checkCnt == 4)
       {
           m_pUi->s34checkBox->setCheckState(Qt::Checked);
           m_NewAdch.iS34Open = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::ms4vcheckBox_clicked()
{
    if(m_NewAdch.iS4vOpen == SELECT_FLAG)
    {
       m_pUi->ms4vcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS4vOpen = UNSELECT_FLAG;
       m_pUi->s34checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS34Open = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nS34checkCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->ms4vcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iS4vOpen = SELECT_FLAG;
       m_NewAdchnum.m_nS34checkCnt++;
       if(m_NewAdchnum.m_nS34checkCnt == 4)
       {
           m_pUi->s34checkBox->setCheckState(Qt::Checked);
           m_NewAdch.iS34Open = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::ms4acheckBox_clicked()
{
    if(m_NewAdch.iS4cOpen == SELECT_FLAG)
    {
       m_pUi->ms4acheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS4cOpen = UNSELECT_FLAG;
       m_pUi->s34checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iS34Open = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nS34checkCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->ms4acheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iS4cOpen = SELECT_FLAG;
       m_NewAdchnum.m_nS34checkCnt++;
       if(m_NewAdchnum.m_nS34checkCnt == 4)
       {
           m_pUi->s34checkBox->setCheckState(Qt::Checked);
           m_NewAdch.iS34Open = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

//S-ALL checkbox
void newadjdlg::movacheckBox_clicked()
{
    if(m_NewAdch.iSAvacOpen == SELECT_FLAG)
    {
       m_pUi->movacheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iSAvacOpen = UNSELECT_FLAG;
       m_pUi->sallcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iSAllOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->movacheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iSAvacOpen = SELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt++;
       if(m_NewAdchnum.m_nSALLcheckCnt == 5)
       {
           m_pUi->sallcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iSAllOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::movdcheckBox_clicked()
{
    if(m_NewAdch.iSAvdcOpen == SELECT_FLAG)
    {
       m_pUi->movdcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iSAvdcOpen = UNSELECT_FLAG;
       m_pUi->sallcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iSAllOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->movdcheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iSAvdcOpen = SELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt++;
       if(m_NewAdchnum.m_nSALLcheckCnt == 5)
       {
           m_pUi->sallcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iSAllOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::mocacheckBox_clicked()
{
    if(m_NewAdch.iSAcacOpen == SELECT_FLAG)
    {
       m_pUi->mocacheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iSAcacOpen = UNSELECT_FLAG;
       m_pUi->sallcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iSAllOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->mocacheckBox->setCheckState(Qt::Checked);
       m_NewAdch.iSAcacOpen = SELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt++;
       if(m_NewAdchnum.m_nSALLcheckCnt == 5)
       {
           m_pUi->sallcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iSAllOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::mcus1checkBox_clicked()
{
    if(m_NewAdch.iCus1Open == SELECT_FLAG)
    {
       m_pUi->mcus1checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iCus1Open = UNSELECT_FLAG;
       m_pUi->sallcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iSAllOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->mcus1checkBox->setCheckState(Qt::Checked);
       m_NewAdch.iCus1Open = SELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt++;
       if(m_NewAdchnum.m_nSALLcheckCnt == 5)
       {
           m_pUi->sallcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iSAllOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}

void newadjdlg::mcus2checkBox_clicked()
{
    if(m_NewAdch.iCus2Open == SELECT_FLAG)
    {
       m_pUi->mcus2checkBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iCus2Open = UNSELECT_FLAG;
       m_pUi->sallcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iSAllOpen = UNSELECT_FLAG;
       m_pUi->allcheckBox->setCheckState(Qt::Unchecked);
       m_NewAdch.iAllOpen = UNSELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt--;
       m_NewAdchnum.m_nAllcheckCnt--;
    }
    else
   {
       m_pUi->mcus2checkBox->setCheckState(Qt::Checked);
       m_NewAdch.iCus2Open = SELECT_FLAG;
       m_NewAdchnum.m_nSALLcheckCnt++;
       if(m_NewAdchnum.m_nSALLcheckCnt == 5)
       {
           m_pUi->sallcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iSAllOpen = SELECT_FLAG;
       }
       m_NewAdchnum.m_nAllcheckCnt++;
       if(m_NewAdchnum.m_nAllcheckCnt == 18)
       {
           m_pUi->allcheckBox->setCheckState(Qt::Checked);
           m_NewAdch.iAllOpen = UNSELECT_FLAG;
       }
   }
}


void newadjdlg::lineEdit_mAzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mAzerovolt);
}

void newadjdlg::lineEdit_mAshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mAshowvolt);
}

void newadjdlg::lineEdit_mArealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mArealvolt);
}

void newadjdlg::lineEdit_mBzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mBzerovolt);
}

void newadjdlg::lineEdit_mBshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mBshowvolt);
}

void newadjdlg::lineEdit_mBrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mBrealvolt);
}

void newadjdlg::lineEdit_mCzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mCzerovolt);
}

void newadjdlg::lineEdit_mCshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mCshowvolt);
}

void newadjdlg::lineEdit_mCrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mCrealvolt);
}

void newadjdlg::lineEdit_mevzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mevzerovolt);
}

void newadjdlg::lineEdit_mevshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mevshowvolt);
}

void newadjdlg::lineEdit_mevrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mevrealvolt);
}

void newadjdlg::lineEdit_meczerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_meczerovolt);
}

void newadjdlg::lineEdit_mecshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mecshowvolt);
}

void newadjdlg::lineEdit_mecrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mecrealvolt);
}

void newadjdlg::lineEdit_ms1vzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms1vzerovolt);
}

void newadjdlg::lineEdit_ms1vshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms1vshowvolt);
}

void newadjdlg::lineEdit_ms1vrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms1vrealvolt);
}

void newadjdlg::lineEdit_ms1azerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms1azerovolt);
}

void newadjdlg::lineEdit_ms1ashowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms1ashowvolt);
}

void newadjdlg::lineEdit_ms1arealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms1arealvolt);
}

void newadjdlg::lineEdit_ms2vzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms2vzerovolt);
}

void newadjdlg::lineEdit_ms2vshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms2vshowvolt);
}

void newadjdlg::lineEdit_ms2vrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms2vrealvolt);
}

void newadjdlg::lineEdit_ms2azerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms2azerovolt);
}

void newadjdlg::lineEdit_ms2ashowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms2ashowvolt);
}

void newadjdlg::lineEdit_ms2arealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms2arealvolt);
}

void newadjdlg::lineEdit_ms3vzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms3vzerovolt);
}

void newadjdlg::lineEdit_ms3vshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms3vshowvolt);
}

void newadjdlg::lineEdit_ms3vrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms3vrealvolt);
}

void newadjdlg::lineEdit_ms3azerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms3azerovolt);
}

void newadjdlg::lineEdit_ms3ashowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms3ashowvolt);
}

void newadjdlg::lineEdit_ms3arealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms3arealvolt);
}


void newadjdlg::lineEdit_ms4vzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms4vzerovolt);
}

void newadjdlg::lineEdit_ms4vshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms4vshowvolt);
}

void newadjdlg::lineEdit_ms4vrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms4vrealvolt);
}

void newadjdlg::lineEdit_ms4azerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms4azerovolt);
}

void newadjdlg::lineEdit_ms4ashowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms4ashowvolt);
}

void newadjdlg::lineEdit_ms4arealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_ms4arealvolt);
}

void newadjdlg::lineEdit_movazerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_movazerovolt);
}

void newadjdlg::lineEdit_movashowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_movashowvolt);
}

void newadjdlg::lineEdit_movarealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_movarealvolt);
}

void newadjdlg::lineEdit_movdzerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_movdzerovolt);
}

void newadjdlg::lineEdit_movdshowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_movdshowvolt);
}

void newadjdlg::lineEdit_movdrealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_movdrealvolt);
}

void newadjdlg::lineEdit_mocazerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mocazerovolt);
}

void newadjdlg::lineEdit_mocashowvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mocashowvolt);
}

void newadjdlg::lineEdit_mocarealvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mocarealvolt);
}

void newadjdlg::lineEdit_mcus1zerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mcus1zerovolt);
}

void newadjdlg::lineEdit_mcus1showvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mcus1showvolt);
}

void newadjdlg::lineEdit_mcus1realvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mcus1realvolt);
}

void newadjdlg::lineEdit_mcus2zerovolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mcus2zerovolt);
}

void newadjdlg::lineEdit_mcus2showvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mcus2showvolt);
}

void newadjdlg::lineEdit_mcus2realvolt_clicked()
{
    openDigKeyBoardDlg(m_pUi->lineEdit_mcus2realvolt);
}


void newadjdlg::MainSeleck()
{
   m_pUi->maincheckBox->setCheckState(Qt::Checked);
   m_NewAdch.iMainOpen = SELECT_FLAG;
   m_pUi->mAvcheckBox->setCheckState(Qt::Checked);
   m_NewAdch.iMAvOpen = SELECT_FLAG;
   m_pUi->mBvcheckBox->setCheckState(Qt::Checked);
   m_NewAdch.iMBvOpen = SELECT_FLAG;
   m_pUi->mCvcheckBox->setCheckState(Qt::Checked);
   m_NewAdch.iMCvOpen = SELECT_FLAG;
   m_pUi->mevcheckBox->setCheckState(Qt::Checked);
   m_NewAdch.iEvOpen = SELECT_FLAG;
   m_pUi->meccheckBox->setCheckState(Qt::Checked);
   m_NewAdch.iEcOpen = SELECT_FLAG;
}

void newadjdlg::MainUnSeleck()
{
    m_pUi->maincheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iMainOpen = UNSELECT_FLAG;
    m_pUi->mAvcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iMAvOpen = UNSELECT_FLAG;
    m_pUi->mBvcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iMBvOpen = UNSELECT_FLAG;
    m_pUi->mCvcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iMCvOpen = UNSELECT_FLAG;
    m_pUi->mevcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iEvOpen = UNSELECT_FLAG;
    m_pUi->meccheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iEcOpen = UNSELECT_FLAG;
}

void newadjdlg::S12Seleck()
{
    m_pUi->s12checkBox->setCheckState(Qt::Checked);
    m_NewAdch.iS12Open = SELECT_FLAG;
    m_pUi->ms1vcheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iS1vOpen = SELECT_FLAG;
    m_pUi->ms1acheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iS1cOpen = SELECT_FLAG;
    m_pUi->ms2vcheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iS2vOpen = SELECT_FLAG;
    m_pUi->ms2acheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iS2cOpen = SELECT_FLAG;
}

void newadjdlg::S12UnSeleck()
{
    m_pUi->s12checkBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS12Open = UNSELECT_FLAG;
    m_pUi->ms1vcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS1vOpen = UNSELECT_FLAG;
    m_pUi->ms1acheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS1cOpen = UNSELECT_FLAG;
    m_pUi->ms2vcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS2vOpen = UNSELECT_FLAG;
    m_pUi->ms2acheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS2cOpen = UNSELECT_FLAG;
}

void newadjdlg::S34Seleck()
{
    m_pUi->s34checkBox->setCheckState(Qt::Checked);
    m_NewAdch.iS34Open = SELECT_FLAG;
    m_pUi->ms3vcheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iS3vOpen = SELECT_FLAG;
    m_pUi->ms3acheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iS3cOpen = SELECT_FLAG;
    m_pUi->ms4vcheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iS4vOpen = SELECT_FLAG;
    m_pUi->ms4acheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iS4cOpen = SELECT_FLAG;
}

void newadjdlg::S34UnSeleck()
{
    m_pUi->s34checkBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS34Open = UNSELECT_FLAG;
    m_pUi->ms3vcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS3vOpen = UNSELECT_FLAG;
    m_pUi->ms3acheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS3cOpen = UNSELECT_FLAG;
    m_pUi->ms4vcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS4vOpen = UNSELECT_FLAG;
    m_pUi->ms4acheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iS4cOpen = UNSELECT_FLAG;
}

void newadjdlg::SALLSeleck()
{
    m_pUi->sallcheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iSAllOpen = SELECT_FLAG;
    m_pUi->movacheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iSAvacOpen = SELECT_FLAG;
    m_pUi->movdcheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iSAvdcOpen = SELECT_FLAG;
    m_pUi->mocacheckBox->setCheckState(Qt::Checked);
    m_NewAdch.iSAcacOpen = SELECT_FLAG;
    m_pUi->mcus1checkBox->setCheckState(Qt::Checked);
    m_NewAdch.iCus1Open = SELECT_FLAG;
    m_pUi->mcus2checkBox->setCheckState(Qt::Checked);
    m_NewAdch.iCus2Open = SELECT_FLAG;
}

void newadjdlg::SALLUnSeleck()
{
    m_pUi->sallcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iSAllOpen = UNSELECT_FLAG;
    m_pUi->movacheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iSAvacOpen = UNSELECT_FLAG;
    m_pUi->movdcheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iSAvdcOpen = UNSELECT_FLAG;
    m_pUi->mocacheckBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iSAcacOpen = UNSELECT_FLAG;
    m_pUi->mcus1checkBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iCus1Open = UNSELECT_FLAG;
    m_pUi->mcus2checkBox->setCheckState(Qt::Unchecked);
    m_NewAdch.iCus2Open = UNSELECT_FLAG;
}


void newadjdlg::closeBtn_clicked()
{
    this->close();
}



void newadjdlg::openDigKeyBoardDlg(QLineEdit *lineEdit)
{
    float fValue=0.0;
    bool ok=false;
    m_KeyBoardDlg.exec();//打开键盘对话框
    m_KeyBoardDlg.clearBtn_clicked();//清除旧的输入痕迹
    ok=m_KeyBoardDlg.getInputValue(fValue);
    if(ok)
    {
        lineEdit->setText(QString::number(fValue,'f',2));
    }
    else
    {
        QMessageBox::warning(this,
                       tr(m_strErrinfo),
                       tr(m_strInvalidinfo));//输入的数值不合法
    }
}
