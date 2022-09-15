#ifndef ADJ_COEF_DLG_H
#define ADJ_COEF_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_adjcoef.h"
#include "commmacro.h"
#include "gpiorw.h"
#include "keyboarddlg.h"
#include "inifileparse.h"
namespace Ui
{
    class adjcoefDialog;
}
class CAdjcoefdlg:public QDialog
{
    Q_OBJECT
public:
    CAdjcoefdlg(int nfd);
    ~CAdjcoefdlg();
public Q_SLOTS:
    void adjcoefBtn_clicked();//У׼-�ۺ���
    void zeroBtn_clicked(); //���ɼ�-�ۺ���
    void resetadjBtn_clicked();//��λУ׼-�ۺ���
    void Sub1TbuslEdit_clicked();//�ӹ�1ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub1AbuslEdit_clicked();//�ӹ�1ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub1TactbuslEdit_clicked();//�ӹ�1��ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub1AactbuslEdit_clicked();//�ӹ�1��ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub1TnegbuslEdit_clicked();//�ӹ�1��ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub1AnegbuslEdit_clicked();//�ӹ�1��ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub1ToutvoltlEdit_clicked();//�ӹ�1�����ѹʵ��ֵ-�༭�ۺ���
    void Sub1AoutvoltlEdit_clicked();//�ӹ�1�����ѹУ׼ֵ-�༭�ۺ���
    void Sub1ZoutvoltlEdit_clicked();//�ӹ�1�����ѹ���ֵ-�༭�ۺ���
    void Sub1ToutcurrlEdit_clicked();//�ӹ�1�������ʵ��ֵ-�༭�ۺ���
    void Sub1AoutcurrlEdit_clicked();//�ӹ�1�������У׼ֵ-�༭�ۺ���
    void Sub1ZoutcurrlEdit_clicked();//�ӹ�1�������У׼ֵ-�༭�ۺ���

    void Sub2TbuslEdit_clicked();//�ӹ�2ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub2AbuslEdit_clicked();//�ӹ�2ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub2TactbuslEdit_clicked();//�ӹ�2��ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub2AactbuslEdit_clicked();//�ӹ�2��ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub2TnegbuslEdit_clicked();//�ӹ�2��ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub2AnegbuslEdit_clicked();//�ӹ�2��ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub2ToutvoltlEdit_clicked();//�ӹ�2�����ѹʵ��ֵ-�༭�ۺ���
    void Sub2AoutvoltlEdit_clicked();//�ӹ�2�����ѹУ׼ֵ-�༭�ۺ���
    void Sub2ZoutvoltlEdit_clicked();//�ӹ�2�����ѹ���ֵ-�༭�ۺ���
    void Sub2ToutcurrlEdit_clicked();//�ӹ�2�������ʵ��ֵ-�༭�ۺ���
    void Sub2AoutcurrlEdit_clicked();//�ӹ�2�������У׼ֵ-�༭�ۺ���
    void Sub2ZoutcurrlEdit_clicked();//�ӹ�2�������У׼ֵ-�༭�ۺ���

    void Sub3TbuslEdit_clicked();//�ӹ�3ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub3AbuslEdit_clicked();//�ӹ�3ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub3TactbuslEdit_clicked();//�ӹ�3��ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub3AactbuslEdit_clicked();//�ӹ�3��ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub3TnegbuslEdit_clicked();//�ӹ�3��ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub3AnegbuslEdit_clicked();//�ӹ�3��ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub3ToutvoltlEdit_clicked();//�ӹ�3�����ѹʵ��ֵ-�༭�ۺ���
    void Sub3AoutvoltlEdit_clicked();//�ӹ�3�����ѹУ׼ֵ-�༭�ۺ���
    void Sub3ZoutvoltlEdit_clicked();//�ӹ�3�����ѹ���ֵ-�༭�ۺ���
    void Sub3ToutcurrlEdit_clicked();//�ӹ�3�������ʵ��ֵ-�༭�ۺ���
    void Sub3AoutcurrlEdit_clicked();//�ӹ�3�������У׼ֵ-�༭�ۺ���
    void Sub3ZoutcurrlEdit_clicked();//�ӹ�3�������У׼ֵ-�༭�ۺ���

    void Sub4TbuslEdit_clicked();//�ӹ�4ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub4AbuslEdit_clicked();//�ӹ�4ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub4TactbuslEdit_clicked();//�ӹ�4��ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub4AactbuslEdit_clicked();//�ӹ�4��ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub4TnegbuslEdit_clicked();//�ӹ�4��ĸ�ߵ�ѹʵ��ֵ-�༭�ۺ���
    void Sub4AnegbuslEdit_clicked();//�ӹ�4��ĸ�ߵ�ѹУ׼ֵ-�༭�ۺ���
    void Sub4ToutvoltlEdit_clicked();//�ӹ�4�����ѹʵ��ֵ-�༭�ۺ���
    void Sub4AoutvoltlEdit_clicked();//�ӹ�4�����ѹУ׼ֵ-�༭�ۺ���
    void Sub4ZoutvoltlEdit_clicked();//�ӹ�4�����ѹ���ֵ-�༭�ۺ���
    void Sub4ToutcurrlEdit_clicked();//�ӹ�4�������ʵ��ֵ-�༭�ۺ���
    void Sub4AoutcurrlEdit_clicked();//�ӹ�4�������У׼ֵ-�༭�ۺ���
    void Sub4ZoutcurrlEdit_clicked();//�ӹ�4�������У׼ֵ-�༭�ۺ���

    void MATlEdit_clicked();//����A���ѹʵ��ֵ-�༭�ۺ���
    void MAAlEdit_clicked();//����A���ѹУ׼ֵ-�༭�ۺ���
    void MBTlEdit_clicked();//����B���ѹʵ��ֵ-�༭�ۺ���
    void MBAlEdit_clicked();//����B���ѹУ׼ֵ-�༭�ۺ���
    void MCTlEdit_clicked();//����C���ѹʵ��ֵ-�༭�ۺ���
    void MCAlEdit_clicked();//����C���ѹУ׼ֵ-�༭�ۺ���
    void MEVTlEdit_clicked();//�������ŵ�ѹʵ��ֵ-�༭�ۺ���
    void MEVAlEdit_clicked();//�������ŵ�ѹУ׼ֵ-�༭�ۺ���
    //void MEVZlEdit_clicked();//�������ŵ�ѹ���ֵ-�༭�ۺ���
    void MECTlEdit_clicked();//�������ŵ���ʵ��ֵ-�༭�ۺ���
    void MECAlEdit_clicked();//�������ŵ���У׼ֵ-�༭�ۺ���
    //void MECZlEdit_clicked();//�������ŵ������ֵ-�༭�ۺ���
    //�ӹ�1ѡ���ѡ�ۺ���
    void s1bvcheckBox_clicked();
    void s1abvcheckBox_clicked();
    void s1nbvcheckBox_clicked();
    void s1ovcheckBox_clicked();
    void s1occheckBox_clicked();
    //�ӹ�2ѡ���ѡ�ۺ���
    void s2bvcheckBox_clicked();
    void s2abvcheckBox_clicked();
    void s2nbvcheckBox_clicked();
    void s2ovcheckBox_clicked();
    void s2occheckBox_clicked();
    //�ӹ�3ѡ���ѡ�ۺ���
    void s3bvcheckBox_clicked();
    void s3abvcheckBox_clicked();
    void s3nbvcheckBox_clicked();
    void s3ovcheckBox_clicked();
    void s3occheckBox_clicked();
    //�ӹ�4ѡ���ѡ�ۺ���
    void s4bvcheckBox_clicked();
    void s4abvcheckBox_clicked();
    void s4nbvcheckBox_clicked();
    void s4ovcheckBox_clicked();
    void s4occheckBox_clicked();
    //����ѡ���ѡ�ۺ���
    void mAvcheckBox_clicked();
    void mBvcheckBox_clicked();
    void mCvcheckBox_clicked();
    void mevcheckBox_clicked();
    void meccheckBox_clicked();
    //��Χѡ��ѡ���ѡ�ۺ���
    void s1checkBox_clicked();
    void s2checkBox_clicked();
    void s3checkBox_clicked();
    void s4checkBox_clicked();
    void maincheckBox_clicked();
    void allcheckBox_clicked();

    void s1select();
    void s1unselect();
    void s2select();
    void s2unselect();
    void s3select();
    void s3unselect();
    void s4select();
    void s4unselect();
    void mainselect();
    void mainunselect();
    void closeBtn_clicked();        //���ؼ��ۺ�����add by 2020.08.10
public:
    void adjcoefLangChange();
public:
    void init();//��Ϊpublic��add by 2020.11.23
    //add by zw 20220223
    void newAdjcoefInit();
    //end add by zw 20220223
private:
    void openDigKeyBoardDlg(QLineEdit *lineEdit);
private:
    CGPIORW m_Gpiorw;//GPIO��д�����
    int m_nGPIOfd;
    CKeyBoardDlg m_KeyBoardDlg;    //���ּ��������
    QString m_strInfo;             //������ʾ��
    QString m_strErrinfo;          //������ʾ��
    QString m_strInvalidinfo;      //���Ϸ���ʾ
    QString m_strFriendlytips;//������ʾ��
    QString m_strAdjSuccess;//У׼�ɹ���ʾ��
    QString m_strAdjFail;   //У׼ʧ����ʾ��
    QString m_strSaveSuccess;      //�������������ļ�����ɹ���ʾ��
    QString m_strSaveFail;         //�������������ļ�����ʧ����ʾ��
    QString m_strResetSuccess;    //У׼��λ�ɹ���ʾ��
    QString m_strResetFail;    //У׼��λʧ����ʾ��
private:
    Ui::adjcoefDialog  *m_pUi;
    STRU_ADJCOEF m_struAdjcoef;
    CInifileparse m_IniAdjcoef;
    STRU_ADJVALUE m_struAdjvalue;
    STRU_ADJCHECK m_struAdjcheck;
    STR_ADJCHECKNUM m_struAdjchecknum;
};
#endif //ADJ_COEF_DLG_H
