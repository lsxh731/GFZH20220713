#ifndef INI_FILE_PARSE_H
#define INI_FILE_PARSE_H
#include "commmacro.h"
#include <QString>
#include <QDateTime>

class CInifileparse
{
public:
    CInifileparse();
    ~CInifileparse();
public:
    //�������ļ�
    bool readInifile(STRU_TOTALRUNNING &stru_Totalrunning);
    //д�����ļ�
    bool writeInifile(STRU_TOTALRUNNING &stru_Totalrunning);
    //��ȡ�ۼ����еȲ���ֵ
    STRU_TOTALRUNNING getTotaltimePara();
    //��ȡprocvalueset.ini�����ļ�
    bool readProcValueSetInifile(STRU_PROCVALUEDATA &stru_ProcValData);
    //д��procvalueset.ini�����ļ�
    int  writeProcValueSetInifile();
    //��ȡbasicparaset.ini�����ļ�
    bool readBasicParaInifile(STRU_BASICPARA &stru_BasicPara);
    //д��basicparaset.ini�����ļ�,add by zqc 2019.06.02
    bool writeBasicParaInifile(STRU_BASICPARA stru_BasicPara);
    //��ȡadjcoef.ini�����ļ���add by 2019.07.08
    bool readAdjcoefInifile(STRU_ADJCOEF &stru_AdjCoef);
    //д��adjcoef.ini�����ļ���add by 2019.07.08
    bool writeAdjcoefInifile(STRU_ADJCOEF stru_AdjCoef);
    //��ȡtotaltime.ini�����ļ�
    bool readStatusRecordInifile(STRU_STATUSRECORD &stru_StatusRecord);
    //д��totaltime.ini�����ļ�
    bool writeStatusRecordInifile(STRU_STATUSRECORD stru_StatusRecord);
    //д��chainset.ini�����ļ�
    bool writeChainsetInifile(STRU_CHAINSETDATA stru_Chainset);
    //��ȡchainset.ini�����ļ�
    bool readChainsetInifile(STRU_CHAINSETDATA &stru_Chainset);
    //д��OutputLog.ini�����ļ�
    bool writeOutLogInifile(); //add by 2020.11.12
    //������������¼д���ļ�
    bool writeStartOutputfile(); //add by 2020.11.12
    //������ֹͣ��¼д���ļ�
    bool writeStopOutputfile(); //add by 2020.11.12

    //��ȡnewadjcoef.ini�����ļ���add by 2022.02.23
    bool readnewAdjcoefInifile(STRU_NEWADJCOEF &stru_newAdjCoef);
    //д��newadjcoef.ini�����ļ���add by 2022.02.23
    bool writeneweAdjcoefInifile(STRU_NEWADJCOEF stru_newAdjCoef);
    //д��newchainset.ini�����ļ���add by 2022.02.23
    bool writenewChainsetInifile(STRU_NEWCHASETDATA stru_newChainset);
    //��ȡnewchainset.ini�����ļ���add by 2022.02.23
    bool readnewChainsetInifile(STRU_NEWCHASETDATA &stru_newChainset);

private:
    STRU_TOTALRUNNING m_struTotaltime;
    QString m_strBasicFilepathName;
    QString m_strAdjFilepathName;
    QString m_strStatusFilepathName;
    QString m_strOutLogFilepathName;    //�����־·��  add by 2020.11.12
public:
    QDateTime active_date_time;  //����ʱ�� add by 2020.11.18
    int calendarDay;   //��Ȼ���� add by 2020.11.18
    QString strActiveDate;  //����ʱ�� add by 2020.11.18
};
#endif //INI_FILE_PARSE_H
