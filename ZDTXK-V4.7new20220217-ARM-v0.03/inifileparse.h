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
    //读配置文件
    bool readInifile(STRU_TOTALRUNNING &stru_Totalrunning);
    //写配置文件
    bool writeInifile(STRU_TOTALRUNNING &stru_Totalrunning);
    //获取累计运行等参数值
    STRU_TOTALRUNNING getTotaltimePara();
    //读取procvalueset.ini配置文件
    bool readProcValueSetInifile(STRU_PROCVALUEDATA &stru_ProcValData);
    //写入procvalueset.ini配置文件
    int  writeProcValueSetInifile();
    //读取basicparaset.ini配置文件
    bool readBasicParaInifile(STRU_BASICPARA &stru_BasicPara);
    //写入basicparaset.ini配置文件,add by zqc 2019.06.02
    bool writeBasicParaInifile(STRU_BASICPARA stru_BasicPara);
    //读取adjcoef.ini配置文件，add by 2019.07.08
    bool readAdjcoefInifile(STRU_ADJCOEF &stru_AdjCoef);
    //写入adjcoef.ini配置文件，add by 2019.07.08
    bool writeAdjcoefInifile(STRU_ADJCOEF stru_AdjCoef);
    //读取totaltime.ini配置文件
    bool readStatusRecordInifile(STRU_STATUSRECORD &stru_StatusRecord);
    //写入totaltime.ini配置文件
    bool writeStatusRecordInifile(STRU_STATUSRECORD stru_StatusRecord);
    //写入chainset.ini配置文件
    bool writeChainsetInifile(STRU_CHAINSETDATA stru_Chainset);
    //读取chainset.ini配置文件
    bool readChainsetInifile(STRU_CHAINSETDATA &stru_Chainset);
    //写入OutputLog.ini配置文件
    bool writeOutLogInifile(); //add by 2020.11.12
    //将功放启动记录写入文件
    bool writeStartOutputfile(); //add by 2020.11.12
    //将功放停止记录写入文件
    bool writeStopOutputfile(); //add by 2020.11.12

    //读取newadjcoef.ini配置文件，add by 2022.02.23
    bool readnewAdjcoefInifile(STRU_NEWADJCOEF &stru_newAdjCoef);
    //写入newadjcoef.ini配置文件，add by 2022.02.23
    bool writeneweAdjcoefInifile(STRU_NEWADJCOEF stru_newAdjCoef);
    //写入newchainset.ini配置文件，add by 2022.02.23
    bool writenewChainsetInifile(STRU_NEWCHASETDATA stru_newChainset);
    //读取newchainset.ini配置文件，add by 2022.02.23
    bool readnewChainsetInifile(STRU_NEWCHASETDATA &stru_newChainset);

private:
    STRU_TOTALRUNNING m_struTotaltime;
    QString m_strBasicFilepathName;
    QString m_strAdjFilepathName;
    QString m_strStatusFilepathName;
    QString m_strOutLogFilepathName;    //输出日志路径  add by 2020.11.12
public:
    QDateTime active_date_time;  //激活时间 add by 2020.11.18
    int calendarDay;   //自然天数 add by 2020.11.18
    QString strActiveDate;  //激活时间 add by 2020.11.18
};
#endif //INI_FILE_PARSE_H
