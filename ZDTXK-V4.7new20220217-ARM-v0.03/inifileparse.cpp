/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: inifileparse.cpp
** 摘要: 配置文件解析类
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.02.01
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.02.01   V1.0      创建
**
****************************************************************************/
#include "inifileparse.h"
#include <QApplication>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QString>
#include <QObject>
#include <QDateTime>
#include <QDebug>


CInifileparse::CInifileparse()
{
    memset(&m_struTotaltime,0,sizeof(m_struTotaltime));
}
CInifileparse::~CInifileparse()
{
}
//失效设置读配置文件
bool CInifileparse::readInifile(STRU_TOTALRUNNING &stru_Totalrunning)
{
#ifdef WIN_DEV
    QString filepathname="./debug/invalidset.ini";
#else
    QString filepathname=QApplication::applicationDirPath() + "/" +"invalidset.ini";
#endif

    QFile file(filepathname);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
    if(linelist.size()!=3)
    {
        return false;
    }
    memset(&stru_Totalrunning,0,sizeof(stru_Totalrunning));

    QString strTmp;
    strTmp=linelist.at(0);
    strTmp.remove(QRegExp("ActivationDate="));//系统激活时间，add by 2020.11.17
    stru_Totalrunning.activeTime=strTmp.toFloat(&ok);
    strActiveDate=strTmp;// add by 2020.11.18
    active_date_time = QDateTime::fromString(strTmp,"yyyy.MM.dd hh:mm:ss");// add by 2020.11.18

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("CalendarDay=")); //自然天数上限，add by 2020.11.17
    stru_Totalrunning.lSetCalendarDay=strTmp.toFloat(&ok);
    calendarDay=stru_Totalrunning.lSetCalendarDay;// add by 2020.11.18

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("OperatingTime="));//累计运行时间上限，add by 2020.11.17
    stru_Totalrunning.lSetValue=strTmp.toFloat(&ok);

    file.close();//关闭文件
    return true;
}
//失效设置写配置文件
bool CInifileparse::writeInifile(STRU_TOTALRUNNING &stru_Totalrunning)
{
    QStringList linelist;
    QString strHeader,strText;
#ifdef WIN_DEV
    QString filepathname="./debug/invalidset.ini";
#else
    QString filepathname=QApplication::applicationDirPath() + "/" +"invalidset.ini";
#endif


    QFile file(filepathname);
    if(linelist.size()>0)
    {
    linelist.clear();
    }

    strHeader="ActivationDate=";     //系统激活时间，add by 2020.11.17
    strText=strHeader+strActiveDate;//add by 2020.11.18
    linelist.append(strText);

    strHeader="CalendarDay=";     //自然天数上限，add by 2020.11.17
    strText=strHeader+QString::number(stru_Totalrunning.lSetCalendarDay,'f',1);
    linelist.append(strText);

    strHeader="OperatingTime=";     //累计运行时间上限，add by 2020.11.17
    strText=strHeader+QString::number(stru_Totalrunning.lSetValue,'f',1);
    linelist.append(strText);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        printf( "####Cannot open file for Writing####\n");
        return false;
    }
    int nlist=linelist.size();
    QString strtest;
    for(int i=0;i<linelist.size();i++)
    {
        strtest=linelist.at(i);
        file.write(linelist.at(i).toUtf8());
        file.write(QObject::tr("\n").toUtf8());
    }
    file.close();

    return true;
}
STRU_TOTALRUNNING CInifileparse::getTotaltimePara()
{
    return m_struTotaltime;
}
//读取procvalueset.ini配置文件
bool CInifileparse::readProcValueSetInifile(STRU_PROCVALUEDATA &stru_ProcValData)
{
#ifdef WIN_DEV
    QString filepathname="./debug/invalidset.ini";
#else
    QString filepathname=QApplication::applicationDirPath() + "/" +"invalidset.ini";
#endif

    QFile file(filepathname);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
    if(linelist.size()!=15)
    {
        return false;
    }
    memset(&stru_ProcValData,0,sizeof(stru_ProcValData));
    QString strTmp=linelist.at(1);
    strTmp.remove(QRegExp("outvolt_low="));
    stru_ProcValData.fOutVoltLow=strTmp.toFloat(&ok);
    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("outvolt_up="));
    stru_ProcValData.fOutVoltUp= strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("dcvolt_low="));
    stru_ProcValData.fDCVoltOverLow=strTmp.toFloat(&ok);
    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("dcvolt_up="));
    stru_ProcValData.fDCVoltOverUp= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("currprocvalue="));
    stru_ProcValData.fCurrentProcVal=strTmp.toFloat(&ok);
    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("currwarnvalue="));
    stru_ProcValData.fCurrentWarnVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("IGBT_temper1="));
    stru_ProcValData.fIGBTGW1=strTmp.toFloat(&ok);
    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("IGBT_temper2="));
    stru_ProcValData.fIGBTGW2= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("IDUCT_temper1="));
    stru_ProcValData.fIDCUTGW1=strTmp.toFloat(&ok);
    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("IDUCT_temper2="));
    stru_ProcValData.fIDCUTGW2= strTmp.toFloat(&ok);
    file.close();
    return true;
}
//写入procvalueset.ini配置文件
int  CInifileparse::writeProcValueSetInifile()
{
    return 0;
}
//读取basicparaset.ini配置文件
bool CInifileparse::readBasicParaInifile(STRU_BASICPARA &stru_BasicPara)
{
#ifdef WIN_DEV
    m_strBasicFilepathName="./debug/basicparaset.ini";
#else
    m_strBasicFilepathName=QApplication::applicationDirPath() + "/" +"basicparaset.ini";
#endif

    QFile file(m_strBasicFilepathName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
    if(linelist.size()!=16)
    {
        return false;
    }
    memset(&stru_BasicPara,0,sizeof(stru_BasicPara));

    QString strTmp;
    strTmp=linelist.at(0);
    strTmp.remove(QRegExp("busvoltup="));//母线电压过高参数，add by 2019.05.28
    stru_BasicPara.fBusvoltUp= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("busvoltlow="));//母线电压过低参数，add by 2019.05.28
    stru_BasicPara.fBusvoltLow=strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("threevoltup="));//三相电压过高参数，add by 2019.05.28
    stru_BasicPara.fThreevoltUp= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("threevoltlow="));//三相电压过低参数，add by 2019.05.28
    stru_BasicPara.fThreevoltLow=strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("busimbalance="));//母线电压不均衡参数，add by 2019.05.28
    stru_BasicPara.fBusImbalance= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("voltimbalance="));//三相电压不均衡参数，add by 2019.05.28
    stru_BasicPara.fVoltimbalance=strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("sub1cabinetcurrentup="));//分柜1输出电流过高参数，add by 2019.05.28
    stru_BasicPara.fSub1CabinetcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("sub2cabinetcurrentup="));//分柜2输出电流过高参数，add by 2019.05.28
    stru_BasicPara.fSub2CabinetcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("sub3cabinetcurrentup="));//分柜3输出电流过高参数，add by 2019.05.28
    stru_BasicPara.fSub3CabinetcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("sub4cabinetcurrentup="));//分柜4输出电流过高参数，add by 2019.05.28
    stru_BasicPara.fSub4CabinetcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("totalvoltup="));//功放总输出电压过高参数，add by 2019.05.28
    stru_BasicPara.fTotalvoltUp= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("totalcurrentup="));//功放总输出电流过高参数，add by 2019.05.28
    stru_BasicPara.fTotalcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("sub1cabopen="));//分柜1接入标记参数，add by 2019.06.02
    stru_BasicPara.iSub1CabOpen=(int)strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("sub2cabopen="));//分柜2接入标记参数，add by 2019.06.02
    stru_BasicPara.iSub2CabOpen=(int)strTmp.toFloat(&ok);


    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("sub3cabopen="));//分柜3接入标记参数，add by 2019.06.02
    stru_BasicPara.iSub3CabOpen=(int)strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("sub4cabopen="));//分柜4接入标记参数，add by 2019.06.02
    stru_BasicPara.iSub4CabOpen=(int)strTmp.toFloat(&ok);
    file.close();
    return true;
}
//写入basicparaset.ini配置文件,add by zqc 2019.06.02
bool CInifileparse::writeBasicParaInifile(STRU_BASICPARA stru_BasicPara)
{
    QStringList linelist;
    QString strHeader,strText;
#ifdef WIN_DEV
    m_strBasicFilepathName="./debug/basicparaset.ini";
#else
    m_strBasicFilepathName=QApplication::applicationDirPath() + "/" +"basicparaset.ini";
#endif
    QFile file(m_strBasicFilepathName);
    if(linelist.size()>0)
    {
        linelist.clear();
    }
    strHeader="busvoltup=";     //母线电压过高参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fBusvoltUp,'f',1);
    linelist.append(strText);

    strHeader="busvoltlow=";    //母线电压过低参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fBusvoltLow,'f',1);
    linelist.append(strText);

    strHeader="threevoltup="; //三相电压过高参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fThreevoltUp,'f',1);
    linelist.append(strText);

    strHeader="threevoltlow="; //三相电压过低参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fThreevoltLow,'f',1);
    linelist.append(strText);

    strHeader="busimbalance=";//母线电压不均衡参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fBusImbalance,'f',1);
    linelist.append(strText);

    strHeader="voltimbalance="; //三相电压不均衡参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fVoltimbalance,'f',1);
    linelist.append(strText);

    strHeader="sub1cabinetcurrentup=";//分柜1输出电流过高参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fSub1CabinetcurrentUp,'f',1);
    linelist.append(strText);

    strHeader="sub2cabinetcurrentup=";//分柜2输出电流过高参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fSub2CabinetcurrentUp,'f',1);
    linelist.append(strText);

    strHeader="sub3cabinetcurrentup=";//分柜3输出电流过高参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fSub3CabinetcurrentUp,'f',1);
    linelist.append(strText);

    strHeader="sub4cabinetcurrentup=";//分柜4输出电流过高参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fSub4CabinetcurrentUp,'f',1);
    linelist.append(strText);


    strHeader="totalvoltup="; //功放总输出电压过高参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fTotalvoltUp,'f',1);
    linelist.append(strText);

    strHeader="totalcurrentup=";//功放总输出电流过高参数，add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fTotalcurrentUp,'f',1);
    linelist.append(strText);

     strHeader="sub1cabopen=";//分柜1接入标记参数，add by 2019.06.02
     strText=strHeader+QString::number(stru_BasicPara.iSub1CabOpen,'f',1);
     linelist.append(strText);

     strHeader="sub2cabopen=";//分柜2接入标记参数，add by 2019.06.02
     strText=strHeader+QString::number(stru_BasicPara.iSub2CabOpen,'f',1);
     linelist.append(strText);

     strHeader="sub3cabopen=";//分柜3接入标记参数，add by 2019.06.02
     strText=strHeader+QString::number(stru_BasicPara.iSub3CabOpen,'f',1);
     linelist.append(strText);

     strHeader="sub4cabopen=";//分柜4接入标记参数，add by 2019.06.02
     strText=strHeader+QString::number(stru_BasicPara.iSub4CabOpen,'f',1);
     linelist.append(strText);
      if(!file.open(QFile::WriteOnly | QFile::Text))
      {
          printf( "####Cannot open file for Writing####\n");
          return false;
      }
      int nlist=linelist.size();
      QString strtest;
      for(int i=0;i<linelist.size();i++)
      {
          strtest=linelist.at(i);
          file.write(linelist.at(i).toUtf8());
          file.write(QObject::tr("\n").toUtf8());
      }
      file.close();

    return true;
}
//校准系数读配置文件函数
bool CInifileparse::readAdjcoefInifile(STRU_ADJCOEF &stru_AdjCoef)
{
#ifdef WIN_DEV
    m_strAdjFilepathName="./debug/adjcoef.ini";
#else
    m_strAdjFilepathName=QApplication::applicationDirPath() + "/" +"adjcoef.ini";

#endif

    QFile file(m_strAdjFilepathName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
    if(linelist.size()!=50)
    {
        return false;
    }
    memset(&stru_AdjCoef,0,sizeof(stru_AdjCoef));

    QString strTmp;
    strTmp=linelist.at(0);
    strTmp.remove(QRegExp("sub1voltk="));//从柜1母线电压校准参数K
    stru_AdjCoef.fSub1voltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("sub1voltb="));//从柜1母线电压校准参数B
    stru_AdjCoef.fSub1voltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("sub1actvoltk="));//从柜1正母线电压校准参数K
    stru_AdjCoef.fSub1ActvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("sub1actvoltb="));//从柜1正母线电压校准参数B
    stru_AdjCoef.fSub1ActvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("sub1negvoltk="));//从柜1负母线电压校准参数K
    stru_AdjCoef.fSub1negvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("sub1negvoltb="));//从柜1负母线电压校准参数B
    stru_AdjCoef.fSub1negvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("sub1outvoltk="));//从柜1输出电压校准参数K
    stru_AdjCoef.fSub1outvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("sub1outvoltb="));//从柜1输出电压校准参数B
    stru_AdjCoef.fSub1outvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("sub1outcurrk="));//从柜1输出电流校准参数K
    stru_AdjCoef.fSub1outcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("sub1outcurrb="));//从柜1输出电流校准参数B
    stru_AdjCoef.fSub1outcurrB=strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("sub2voltk="));//从柜2母线电压校准参数K
    stru_AdjCoef.fSub2voltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("sub2voltb="));//从柜2母线电压校准参数B
    stru_AdjCoef.fSub2voltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("sub2actvoltk="));//从柜2正母线电压校准参数K
    stru_AdjCoef.fSub2ActvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("sub2actvoltb="));//从柜2正母线电压校准参数B
    stru_AdjCoef.fSub2ActvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("sub2negvoltk="));//从柜2负母线电压校准参数K
    stru_AdjCoef.fSub2negvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("sub2negvoltb="));//从柜2负母线电压校准参数B
    stru_AdjCoef.fSub2negvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(16);
    strTmp.remove(QRegExp("sub2outvoltk="));//从柜2输出电压校准参数K
    stru_AdjCoef.fSub2outvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(17);
    strTmp.remove(QRegExp("sub2outvoltb="));//从柜2输出电压校准参数B
    stru_AdjCoef.fSub2outvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(18);
    strTmp.remove(QRegExp("sub2outcurrk="));//从柜2输出电流校准参数K
    stru_AdjCoef.fSub2outcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(19);
    strTmp.remove(QRegExp("sub2outcurrb="));//从柜2输出电流校准参数B
    stru_AdjCoef.fSub2outcurrB=strTmp.toFloat(&ok);

    strTmp=linelist.at(20);
    strTmp.remove(QRegExp("sub3voltk="));//从柜3母线电压校准参数K
    stru_AdjCoef.fSub3voltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(21);
    strTmp.remove(QRegExp("sub3voltb="));//从柜3母线电压校准参数B
    stru_AdjCoef.fSub3voltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(22);
    strTmp.remove(QRegExp("sub3actvoltk="));//从柜3正母线电压校准参数K
    stru_AdjCoef.fSub3ActvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(23);
    strTmp.remove(QRegExp("sub3actvoltb="));//从柜3正母线电压校准参数B
    stru_AdjCoef.fSub3ActvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(24);
    strTmp.remove(QRegExp("sub3negvoltk="));//从柜3负母线电压校准参数K
    stru_AdjCoef.fSub3negvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(25);
    strTmp.remove(QRegExp("sub3negvoltb="));//从柜3负母线电压校准参数B
    stru_AdjCoef.fSub3negvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(26);
    strTmp.remove(QRegExp("sub3outvoltk="));//从柜3输出电压校准参数K
    stru_AdjCoef.fSub3outvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(27);
    strTmp.remove(QRegExp("sub3outvoltb="));//从柜3输出电压校准参数B
    stru_AdjCoef.fSub3outvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(28);
    strTmp.remove(QRegExp("sub3outcurrk="));//从柜3输出电流校准参数K
    stru_AdjCoef.fSub3outcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(29);
    strTmp.remove(QRegExp("sub3outcurrb="));//从柜3输出电流校准参数B
    stru_AdjCoef.fSub3outcurrB=strTmp.toFloat(&ok);

    strTmp=linelist.at(30);
    strTmp.remove(QRegExp("sub4voltk="));//从柜4母线电压校准参数K
    stru_AdjCoef.fSub4voltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(31);
    strTmp.remove(QRegExp("sub4voltb="));//从柜4母线电压校准参数B
    stru_AdjCoef.fSub4voltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(32);
    strTmp.remove(QRegExp("sub4actvoltk="));//从柜4正母线电压校准参数K
    stru_AdjCoef.fSub4ActvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(33);
    strTmp.remove(QRegExp("sub4actvoltb="));//从柜4正母线电压校准参数B
    stru_AdjCoef.fSub4ActvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(34);
    strTmp.remove(QRegExp("sub4negvoltk="));//从柜4负母线电压校准参数K
    stru_AdjCoef.fSub4negvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(35);
    strTmp.remove(QRegExp("sub4negvoltb="));//从柜4负母线电压校准参数B
    stru_AdjCoef.fSub4negvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(36);
    strTmp.remove(QRegExp("sub4outvoltk="));//从柜4输出电压校准参数K
    stru_AdjCoef.fSub4outvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(37);
    strTmp.remove(QRegExp("sub4outvoltb="));//从柜4输出电压校准参数B
    stru_AdjCoef.fSub4outvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(38);
    strTmp.remove(QRegExp("sub4outcurrk="));//从柜4输出电流校准参数K
    stru_AdjCoef.fSub4outcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(39);
    strTmp.remove(QRegExp("sub4outcurrb="));//从柜4输出电流校准参数B
    stru_AdjCoef.fSub4outcurrB=strTmp.toFloat(&ok);

    strTmp=linelist.at(40);
    strTmp.remove(QRegExp("mavoltk="));//A相电压校准参数K
    stru_AdjCoef.fMAvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(41);
    strTmp.remove(QRegExp("mavoltb="));//A相电压校准参数B
    stru_AdjCoef.fMAvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(42);
    strTmp.remove(QRegExp("mbvoltk="));//B相电压校准参数K
    stru_AdjCoef.fMBvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(43);
    strTmp.remove(QRegExp("mbvoltb="));//B相电压校准参数B
    stru_AdjCoef.fMBvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(44);
    strTmp.remove(QRegExp("mcvoltk="));//C相电压校准参数K
    stru_AdjCoef.fMCvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(45);
    strTmp.remove(QRegExp("mcvoltb="));//C相电压校准参数B
    stru_AdjCoef.fMCvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(46);
    strTmp.remove(QRegExp("mevoltk="));//励磁电压校准参数K
    stru_AdjCoef.fMEvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(47);
    strTmp.remove(QRegExp("mevoltb="));//励磁电压校准参数B
    stru_AdjCoef.fMEvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(48);
    strTmp.remove(QRegExp("mecurrk="));//励磁电流校准参数K
    stru_AdjCoef.fMEcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(49);
    strTmp.remove(QRegExp("mecurrb="));//励磁电流校准参数B
    stru_AdjCoef.fMEcurrB=strTmp.toFloat(&ok);
    file.close();
    return true;
}
bool CInifileparse::writeAdjcoefInifile(STRU_ADJCOEF stru_AdjCoef)
{
    QStringList linelist;
    QString strHeader,strText;
#ifdef WIN_DEV
    m_strAdjFilepathName="./debug/adjcoef.ini";
#else
    m_strAdjFilepathName=QApplication::applicationDirPath() + "/" +"adjcoef.ini";
#endif

    QFile file(m_strAdjFilepathName);
    if(linelist.size()>0)
    {
        linelist.clear();
    }
    strHeader="sub1voltk=";     //从柜1母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1voltK,'f',3);
    linelist.append(strText);

    strHeader="sub1voltb=";    //从柜1母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1voltB,'f',3);
    linelist.append(strText);

    strHeader="sub1actvoltk=";     //从柜1正母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1ActvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub1actvoltb=";    //从柜1正母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1ActvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub1negvoltk=";     //从柜1负母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1negvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub1negvoltb=";    //从柜1负母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1negvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub1outvoltk=";     //从柜1输出电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1outvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub1outvoltb=";    //从柜1输出电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1outvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub1outcurrk=";     //从柜1输出电流参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1outcurrK,'f',3);
    linelist.append(strText);

    strHeader="sub1outcurrb=";    //从柜1输出电流参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1outcurrB,'f',3);
    linelist.append(strText);

    strHeader="sub2voltk=";     //从柜2母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2voltK,'f',3);
    linelist.append(strText);

    strHeader="sub2voltb=";    //从柜2母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2voltB,'f',3);
    linelist.append(strText);

    strHeader="sub2actvoltk=";     //从柜2正母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2ActvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub2actvoltb=";    //从柜2正母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2ActvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub2negvoltk=";     //从柜2负母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2negvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub2negvoltb=";    //从柜2负母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2negvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub2outvoltk=";     //从柜2输出电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2outvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub2outvoltb=";    //从柜2输出电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2outvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub2outcurrk=";     //从柜2输出电流参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2outcurrK,'f',3);
    linelist.append(strText);

    strHeader="sub2outcurrb=";    //从柜2输出电流参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2outcurrB,'f',3);
    linelist.append(strText);

    strHeader="sub3voltk=";     //从柜3母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3voltK,'f',3);
    linelist.append(strText);

    strHeader="sub3voltb=";    //从柜3母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3voltB,'f',3);
    linelist.append(strText);

    strHeader="sub3actvoltk=";     //从柜3正母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3ActvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub3actvoltb=";    //从柜3正母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3ActvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub3negvoltk=";     //从柜3负母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3negvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub3negvoltb=";    //从柜3负母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3negvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub3outvoltk=";     //从柜3输出电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3outvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub3outvoltb=";    //从柜3输出电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3outvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub3outcurrk=";     //从柜3输出电流参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3outcurrK,'f',3);
    linelist.append(strText);

    strHeader="sub3outcurrb=";    //从柜3输出电流参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3outcurrB,'f',3);
    linelist.append(strText);

    strHeader="sub4voltk=";     //从柜4母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4voltK,'f',3);
    linelist.append(strText);

    strHeader="sub4voltb=";    //从柜4母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4voltB,'f',3);
    linelist.append(strText);

    strHeader="sub4actvoltk=";     //从柜4正母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4ActvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub4actvoltb=";    //从柜4正母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4ActvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub4negvoltk=";     //从柜4负母线电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4negvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub4negvoltb=";    //从柜4负母线电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4negvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub4outvoltk=";     //从柜4输出电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4outvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub4outvoltb=";    //从柜4输出电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4outvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub4outcurrk=";     //从柜4输出电流参数k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4outcurrK,'f',3);
    linelist.append(strText);

    strHeader="sub4outcurrb=";    //从柜4输出电流参数b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4outcurrB,'f',3);
    linelist.append(strText);

    strHeader="mavoltk=";     //A相电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fMAvoltK,'f',3);
    linelist.append(strText);

    strHeader="mavoltb=";    //A相电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fMAvoltB,'f',3);
    linelist.append(strText);

    strHeader="mbvoltk=";     //B相电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fMBvoltK,'f',3);
    linelist.append(strText);

    strHeader="mbvoltb=";    //B相电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fMBvoltB,'f',3);
    linelist.append(strText);

    strHeader="mcvoltk=";     //C相电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fMCvoltK,'f',3);
    linelist.append(strText);

    strHeader="mcvoltb=";    //C相电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fMCvoltB,'f',3);
    linelist.append(strText);

    strHeader="mevoltk=";     //励磁电压参数k
    strText=strHeader+QString::number(stru_AdjCoef.fMEvoltK,'f',3);
    linelist.append(strText);

    strHeader="mevoltb=";    //励磁电压参数b
    strText=strHeader+QString::number(stru_AdjCoef.fMEvoltB,'f',3);
    linelist.append(strText);

    strHeader="mecurrk=";     //励磁电流参数k
    strText=strHeader+QString::number(stru_AdjCoef.fMEcurrK,'f',3);
    linelist.append(strText);

    strHeader="mecurrb=";    //励磁电流参数b
    strText=strHeader+QString::number(stru_AdjCoef.fMEcurrB,'f',3);
    linelist.append(strText);
      if(!file.open(QFile::WriteOnly | QFile::Text))
      {
          printf( "####Cannot open file for Writing####\n");
          return false;
      }
      int nlist=linelist.size();
      QString strtest;
      for(int i=0;i<linelist.size();i++)
      {
          strtest=linelist.at(i);
          file.write(linelist.at(i).toUtf8());
          file.write(QObject::tr("\n").toUtf8());
      }
      file.close();

    return true;
}
//写入totaltime.ini配置文件
bool CInifileparse::writeStatusRecordInifile(STRU_STATUSRECORD stru_StatusRecord)
{
    //读totaltime.ini配置文件已有内容

    QStringList linelist;
    QString strHeader,strText;
#ifdef WIN_DEV
    m_strStatusFilepathName="./debug/totaltime.ini";
#else
    m_strStatusFilepathName=QApplication::applicationDirPath() + "/" +"totaltime.ini";
#endif

    QFile file(m_strStatusFilepathName);

    if(linelist.size()>0)
    {
        linelist.clear();
    }
    strHeader="totaltime=";     //总运行时间
    strText=strHeader+QString::number(stru_StatusRecord.lTotaltime,10);
    linelist.append(strText);

    strHeader="sumtime=";     //最后一次总运行时间
    strText=strHeader+QString::number(stru_StatusRecord.iSumtime,10);
    linelist.append(strText);
    if(!file.open(QFile::WriteOnly | QFile::Text))
     {
          printf( "####Cannot open file for Writing####\n");
          return false;
     }
     int nlist=linelist.size();
     QString strtest;
     for(int i=0;i<linelist.size();i++)
     {
          strtest=linelist.at(i);
          file.write(linelist.at(i).toUtf8());
          file.write(QObject::tr("\n").toUtf8());
     }
     file.close();
    return true;
}
//读取totaltime.ini配置文件
bool CInifileparse::readStatusRecordInifile(STRU_STATUSRECORD &stru_StatusRecord)
{
#ifdef WIN_DEV
    m_strStatusFilepathName="./debug/totaltime.ini";
#else
    m_strStatusFilepathName=QApplication::applicationDirPath() + "/" +"totaltime.ini";
    qDebug()<<"##m_strStatusFilepathName##"<<m_strStatusFilepathName;
#endif
    QFile file(m_strStatusFilepathName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
    if(linelist.size()!=2)
    {
        return false;
    }
    memset(&stru_StatusRecord,0,sizeof(stru_StatusRecord));

    QString strTmp;
    strTmp=linelist.at(0);
    strTmp.remove(QRegExp("totaltime="));//总运行时间
    stru_StatusRecord.lTotaltime= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("sumtime="));//最后一次总运行时间
    stru_StatusRecord.iSumtime= strTmp.toFloat(&ok);
    file.close();
    return true;
}//写chainset.ini配置文件
bool CInifileparse::writeChainsetInifile(STRU_CHAINSETDATA stru_Chainset)
{
    QStringList linelist;
    QString strHeader,strText;
#ifdef WIN_DEV
    m_strStatusFilepathName="./debug/chainset.ini";
#else
    m_strStatusFilepathName=QApplication::applicationDirPath() + "/" +"chainset.ini";
#endif

    QFile file(m_strStatusFilepathName);

    if(linelist.size()>0)
    {
        linelist.clear();
    }
    strHeader="iJjtjVal=";     //紧急停机
    strText=strHeader+QString::number(stru_Chainset.iJjtjVal,10);
    linelist.append(strText);

    strHeader="iHtgwyVal=";     //滑台过位移
    strText=strHeader+QString::number(stru_Chainset.iHtgwyVal,10);
    linelist.append(strText);

    strHeader="iZdtgwyVal=";     //振动台过位移
    strText=strHeader+QString::number(stru_Chainset.iZdtgwyVal,10);
    linelist.append(strText);

    strHeader="iHtdywVal=";     //滑台低液位
    strText=strHeader+QString::number(stru_Chainset.iHtdywVal,10);
    linelist.append(strText);

    strHeader="iHtqyVal=";     //滑台轴承低压
    strText=strHeader+QString::number(stru_Chainset.iHtqyVal,10);
    linelist.append(strText);

    strHeader="iZdtgwVal=";     //振动台过温
    strText=strHeader+QString::number(stru_Chainset.iZdtgwVal,10);
    linelist.append(strText);

    strHeader="iEzgwyVal=";     //耳轴过位移
    strText=strHeader+QString::number(stru_Chainset.iEzgwyVal,10);
    linelist.append(strText);

    strHeader="iGfrjbhVal=";     //功放热继保护
    strText=strHeader+QString::number(stru_Chainset.iGfrjbhVal,10);
    linelist.append(strText);

    strHeader="iJyzcdyVal=";     //静压轴承低压
    strText=strHeader+QString::number(stru_Chainset.iJyzcdyVal,10);
    linelist.append(strText);

    strHeader="iZgMenbVal=";     //主柜门保护
    strText=strHeader+QString::number(stru_Chainset.iZgMenbVal,10);
    linelist.append(strText);

    strHeader="iSubMenbVal=";     //从柜门保护
    strText=strHeader+QString::number(stru_Chainset.iSubMenbVal,10);
    linelist.append(strText);

    strHeader="iXtlqdyVal=";     //系统冷却单元
    strText=strHeader+QString::number(stru_Chainset.iXtlqdyVal,10);
    linelist.append(strText);

    strHeader="iHtqywVal=";     //主柜整流桥过温
    strText=strHeader+QString::number(stru_Chainset.iHtqywVal,10);
    linelist.append(strText);

    strHeader="iSubzlqgwVal=";     //从柜整流桥过温
    strText=strHeader+QString::number(stru_Chainset.iSubzlqgwVal,10);
    linelist.append(strText);

    strHeader="iSelfdefineVal1=";     //自定义1
    strText=strHeader+QString::number(stru_Chainset.iSelfdefineVal1,10);
    linelist.append(strText);

    strHeader="iSelfdefineVal2=";     //自定义2
    strText=strHeader+QString::number(stru_Chainset.iSelfdefineVal2,10);
    linelist.append(strText);

    strHeader="iSelfdefineVal3=";     //自定义3
    strText=strHeader+QString::number(stru_Chainset.iSelfdefineVal3,10);
    linelist.append(strText);

    strHeader="iSubyuliuPorcVal=";     //从柜预留保护
    strText=strHeader+QString::number(stru_Chainset.iSubyuliuPorcVal,10);
    linelist.append(strText);

//  触点切换写配置文件，add by 2020.11.24
    strHeader="iSwitch_Jjtj=";     //紧急停机
    strText=strHeader+QString::number(stru_Chainset.iSwitch_Jjtj,10);
    linelist.append(strText);

    strHeader="iSwitch_htgwy=";     //滑台过位移
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htgwy,10);
    linelist.append(strText);

    strHeader="iSwitch_zdtgwy=";    //振动台过位移
    strText=strHeader+QString::number(stru_Chainset.iSwitch_zdtgwy,10);
    linelist.append(strText);

    strHeader="iSwitch_htdyw=";    //滑台低液位
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htdyw,10);
    linelist.append(strText);

    strHeader="iSwitch_htqy=";    //滑台轴承低压
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htqy,10);
    linelist.append(strText);

    strHeader="iSwitch_zdtgw=";    //振动台过温
    strText=strHeader+QString::number(stru_Chainset.iSwitch_zdtgw,10);
    linelist.append(strText);

    strHeader="iSwitch_ezgwy=";    //耳轴过位移
    strText=strHeader+QString::number(stru_Chainset.iSwitch_ezgwy,10);
    linelist.append(strText);

    strHeader="iSwitch_gfrjbh=";    //功放热继保护
    strText=strHeader+QString::number(stru_Chainset.iSwitch_gfrjbh,10);
    linelist.append(strText);

    strHeader="iSwitch_jyzcdy=";    //静压轴承低压
    strText=strHeader+QString::number(stru_Chainset.iSwitch_jyzcdy,10);
    linelist.append(strText);

    strHeader="iSwitch_zgmenbh=";    //主柜门
    strText=strHeader+QString::number(stru_Chainset.iSwitch_zgmenbh,10);
    linelist.append(strText);

    strHeader="iSwitch_htgw=";    //从柜门
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htgw,10);
    linelist.append(strText);

    strHeader="iSwitch_xtlqdy=";    //系统冷却单元
    strText=strHeader+QString::number(stru_Chainset.iSwitch_xtlqdy,10);
    linelist.append(strText);

    strHeader="iSwitch_htqyw=";    //主柜整流器过温
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htqyw,10);
    linelist.append(strText);

    strHeader="iSwitch_subzlqgw=";    //从柜整流器过温
    strText=strHeader+QString::number(stru_Chainset.iSwitch_subzlqgw,10);
    linelist.append(strText);

    strHeader="iSwitch_selfdefine1=";    //自定义1
    strText=strHeader+QString::number(stru_Chainset.iSwitch_selfdefine1,10);
    linelist.append(strText);

    strHeader="iSwitch_selfdefine2=";    //自定义2
    strText=strHeader+QString::number(stru_Chainset.iSwitch_selfdefine2,10);
    linelist.append(strText);

    strHeader="iSwitch_selfdefine3=";    //自定义3
    strText=strHeader+QString::number(stru_Chainset.iSwitch_selfdefine3,10);
    linelist.append(strText);

    strHeader="iSwitch_subyuliu=";    //从柜预留
    strText=strHeader+QString::number(stru_Chainset.iSwitch_subyuliu,10);
    linelist.append(strText);

    if(!file.open(QFile::WriteOnly | QFile::Text))
     {
          printf( "####Cannot open file for Writing####\n");
          return false;
     }
     int nlist=linelist.size();
     QString strtest;
     for(int i=0;i<linelist.size();i++)
     {
          strtest=linelist.at(i);
          file.write(linelist.at(i).toUtf8());
          file.write(QObject::tr("\n").toUtf8());
     }
     file.close();
    return true;
}
//读取chainset.ini配置文件
bool CInifileparse::readChainsetInifile(STRU_CHAINSETDATA &stru_Chainset)
{
#ifdef WIN_DEV
    m_strStatusFilepathName="./debug/chainset.ini";
#else
    m_strStatusFilepathName=QApplication::applicationDirPath() + "/" +"chainset.ini";
#endif

    QFile file(m_strStatusFilepathName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
//	if(linelist.size()!=18)
    if(linelist.size()!=36) //add by 2020.11.24
    {
        return false;
    }
    memset(&stru_Chainset,0,sizeof(stru_Chainset));

    QString strTmp;
    strTmp=linelist.at(0);
    strTmp.remove(QRegExp("iJjtjVal="));//紧机停机
    stru_Chainset.iJjtjVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("iHtgwyVal="));//滑台过位移
    stru_Chainset.iHtgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("iZdtgwyVal="));//振动台过温
    stru_Chainset.iZdtgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("iHtdywVal="));//滑台低液位
    stru_Chainset.iHtdywVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("iHtqyVal="));//滑台轴承低压
    stru_Chainset.iHtqyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("iZdtgwVal="));//振动台过温
    stru_Chainset.iZdtgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("iEzgwyVal="));//耳轴过位移
    stru_Chainset.iEzgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("iGfrjbhVal="));//功放热继保护
    stru_Chainset.iGfrjbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("iJyzcdyVal="));//静压轴承低压
    stru_Chainset.iJyzcdyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("iZgMenbVal="));//主柜门保护
    stru_Chainset.iZgMenbVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("iSubMenbVal="));//从柜门保护
    stru_Chainset.iSubMenbVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("iXtlqdyVal="));//系统冷却单元
    stru_Chainset.iXtlqdyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("iHtqywVal="));//主柜整流桥过温
    stru_Chainset.iHtqywVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("iSubzlqgwVal="));//从柜整流桥过温
    stru_Chainset.iSubzlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("iSelfdefineVal1="));//自定义1
    stru_Chainset.iSelfdefineVal1= strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("iSelfdefineVal2="));//自定义2
    stru_Chainset.iSelfdefineVal2= strTmp.toFloat(&ok);

    strTmp=linelist.at(16);
    strTmp.remove(QRegExp("iSelfdefineVal3="));//自定义3
    stru_Chainset.iSelfdefineVal3= strTmp.toFloat(&ok);

    strTmp=linelist.at(17);
    strTmp.remove(QRegExp("iSubyuliuPorcVal="));//从柜预留保护
    stru_Chainset.iSubyuliuPorcVal= strTmp.toFloat(&ok);

//  触点切换读配置文件，add by 2020.11.24

    strTmp=linelist.at(18);
    strTmp.remove(QRegExp("iSwitch_Jjtj="));//紧急停机
    stru_Chainset.iSwitch_Jjtj= strTmp.toFloat(&ok);

    strTmp=linelist.at(19);
    strTmp.remove(QRegExp("iSwitch_htgwy="));//滑台过位移
    stru_Chainset.iSwitch_htgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(20);
    strTmp.remove(QRegExp("iSwitch_zdtgwy="));//振动台过位移
    stru_Chainset.iSwitch_zdtgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(21);
    strTmp.remove(QRegExp("iSwitch_htdyw="));//滑台低液位
    stru_Chainset.iSwitch_htdyw= strTmp.toFloat(&ok);

    strTmp=linelist.at(22);
    strTmp.remove(QRegExp("iSwitch_htqy="));//滑台轴承低压
    stru_Chainset.iSwitch_htqy= strTmp.toFloat(&ok);

    strTmp=linelist.at(23);
    strTmp.remove(QRegExp("iSwitch_zdtgw="));//振动台过温
    stru_Chainset.iSwitch_zdtgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(24);
    strTmp.remove(QRegExp("iSwitch_ezgwy="));//耳轴过位移
    stru_Chainset.iSwitch_ezgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(25);
    strTmp.remove(QRegExp("iSwitch_gfrjbh="));//功放热继保护
    stru_Chainset.iSwitch_gfrjbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(26);
    strTmp.remove(QRegExp("iSwitch_jyzcdy="));//静压轴承低压
    stru_Chainset.iSwitch_jyzcdy= strTmp.toFloat(&ok);

    strTmp=linelist.at(27);
    strTmp.remove(QRegExp("iSwitch_zgmenbh="));//主柜门
    stru_Chainset.iSwitch_zgmenbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(28);
    strTmp.remove(QRegExp("iSwitch_htgw="));//从柜门
    stru_Chainset.iSwitch_htgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(29);
    strTmp.remove(QRegExp("iSwitch_xtlqdy="));//系统冷却单元
    stru_Chainset.iSwitch_xtlqdy= strTmp.toFloat(&ok);

    strTmp=linelist.at(30);
    strTmp.remove(QRegExp("iSwitch_htqyw="));//主柜整流器过温
    stru_Chainset.iSwitch_htqyw= strTmp.toFloat(&ok);

    strTmp=linelist.at(31);
    strTmp.remove(QRegExp("iSwitch_subzlqgw="));//从柜整流器过温
    stru_Chainset.iSwitch_subzlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(32);
    strTmp.remove(QRegExp("iSwitch_selfdefine1="));//自定义1
    stru_Chainset.iSwitch_selfdefine1= strTmp.toFloat(&ok);

    strTmp=linelist.at(33);
    strTmp.remove(QRegExp("iSwitch_selfdefine2="));//自定义2
    stru_Chainset.iSwitch_selfdefine2= strTmp.toFloat(&ok);

    strTmp=linelist.at(34);
    strTmp.remove(QRegExp("iSwitch_selfdefine3="));//自定义2
    stru_Chainset.iSwitch_selfdefine3= strTmp.toFloat(&ok);

    strTmp=linelist.at(35);
    strTmp.remove(QRegExp("iSwitch_subyuliu="));//从柜预留保护
    stru_Chainset.iSwitch_subyuliu= strTmp.toFloat(&ok);

    file.close();
    return true;
}
//写入OutputLog.ini配置文件 add by 2020.11.12
/*
bool CInifileparse::writeOutLogInifile()
{
    QStringList linelist;
    QString strHeader,strText;

    m_strOutLogFilepathName=QApplication::applicationDirPath() + "/" +"OutputLog.ini";
    QFile file(m_strOutLogFilepathName);

    if(linelist.size()>0)
    {
        linelist.clear();
    }
    strHeader="test1";
    strText=strHeader;
    linelist.append(strText);

    strHeader="test2";
    strText=strHeader;
    linelist.append(strText);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
          printf( "####Cannot open file for Writing####\n");
          return false;
     }
     int nlist=linelist.size();
     QString strtest;
     for(int i=0;i<linelist.size();i++)
     {
          strtest=linelist.at(i);
          file.write(linelist.at(i).toUtf8());
          file.write(QObject::tr("\n").toUtf8());
     }
     file.close();
     return true;
}
*/
//将功放启动记录写入OutputRecord文件 add by 2020.11.12
bool CInifileparse::writeStartOutputfile()
{
    QStringList linelist;
    QString strEnder,strText;
#ifdef WIN_DEV
    m_strOutLogFilepathName="./debug/OutputRecord.txt";
#else
    m_strOutLogFilepathName=QApplication::applicationDirPath() + "/" +"OutputRecord.txt";
#endif

    QFile file(m_strOutLogFilepathName);
    if(linelist.size()>0)
    {
        linelist.clear();
    }
    QDateTime current_date_time =	QDateTime::currentDateTime();
    QString current__date = current_date_time.toString("yyyy-MM-dd hh:mm:ss   ");
    strEnder="\345\212\237\346\224\276\345\220\257\345\212\250";
    strText=current__date+strEnder;
//	linelist.append(strText);

    if(!file.open(QFile::WriteOnly | QFile::Append))
     {
          printf( "####Cannot open file for Writing####\n");
          return false;
     }
     file.write(strText);
     file.write(QObject::tr("\n").toUtf8());
     file.close();
     return true;
}
//将功放停止记录写入OutputRecord文件 add by 2020.11.12
bool CInifileparse::writeStopOutputfile()
{
    QStringList linelist;
    QString strEnder,strText;
#ifdef WIN_DEV
    m_strOutLogFilepathName="./debug/OutputRecord.txt";
#else
    m_strOutLogFilepathName=QApplication::applicationDirPath() + "/" +"OutputRecord.txt";
#endif

    QFile file(m_strOutLogFilepathName);
    if(linelist.size()>0)
    {
        linelist.clear();
    }
    QDateTime current_date_time =	QDateTime::currentDateTime();
    QString current__date = current_date_time.toString("yyyy-MM-dd hh:mm:ss   ");
    strEnder="\345\212\237\346\224\276\345\201\234\346\255\242";
    strText=current__date+strEnder;
//	linelist.append(strText);

     if(!file.open(QFile::WriteOnly | QFile::Append))
     {
          printf( "####Cannot open file for Writing####\n");
          return false;
     }
     file.write(strText);
     file.write(QObject::tr("\n").toUtf8());
     file.close();
     return true;
}

//add by zw 20220223
//新校准系数读配置文件函数
bool CInifileparse::readnewAdjcoefInifile(STRU_NEWADJCOEF &stru_newAdjCoef)
{
#ifdef WIN_DEV
    m_strAdjFilepathName="./debug/newadjcoef.ini";
#else
    m_strAdjFilepathName=QApplication::applicationDirPath() + "/" +"newadjcoef.ini";

#endif

    QFile file(m_strAdjFilepathName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
    if(linelist.size()!=36)
    {
        return false;
    }
    memset(&stru_newAdjCoef,0,sizeof(stru_newAdjCoef));

    QString strTmp;
    strTmp=linelist.at(0);
    strTmp.remove(QRegExp("fTriPhaseAVolDCK="));//三相电A直流校准参数K
    stru_newAdjCoef.fTriPhaseAVolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("fTriPhaseAVolDCB="));//三相电A直流校准参数B
    stru_newAdjCoef.fTriPhaseAVolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("fTriPhaseBVolDCK="));//三相电B直流校准参数K
    stru_newAdjCoef.fTriPhaseBVolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("fTriPhaseBVolDCB="));//三相电B直流校准参数B
    stru_newAdjCoef.fTriPhaseBVolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("fTriPhaseCVolDCK="));//三相电C直流校准参数K
    stru_newAdjCoef.fTriPhaseCVolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("fTriPhaseCVolDCB="));//三相电C直流校准参数B
    stru_newAdjCoef.fTriPhaseCVolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("fExcitVoltK="));//励磁电压直流校准参数K
    stru_newAdjCoef.fExcitVoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("fExcitVoltB="));//励磁电压直流校准参数B
    stru_newAdjCoef.fExcitVoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("fExcitCurK="));//励磁电流直流校准参数K
    stru_newAdjCoef.fExcitCurK= strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("fExcitCurB="));//励磁电流直流校准参数B
    stru_newAdjCoef.fExcitCurB=strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("fSlave1VolDCK="));//从柜1电压直流校准参数K
    stru_newAdjCoef.fSlave1VolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("fSlave1VolDCB="));//从柜1电压直流校准参数B
    stru_newAdjCoef.fSlave1VolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("fSlave1CurDCK="));//从柜1电流直流校准参数K
    stru_newAdjCoef.fSlave1CurDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("fSlave1CurDCB="));//从柜1电流直流校准参数B
    stru_newAdjCoef.fSlave1CurDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("fSlave2VolDCK="));//从柜2电压直流校准参数K
    stru_newAdjCoef.fSlave2VolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("fSlave2VolDCB="));//从柜2电压直流校准参数B
    stru_newAdjCoef.fSlave2VolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(16);
    strTmp.remove(QRegExp("fSlave2CurDCK="));//从柜2电流直流校准参数K
    stru_newAdjCoef.fSlave2CurDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(17);
    strTmp.remove(QRegExp("fSlave2CurDCB="));//从柜2电流直流校准参数B
    stru_newAdjCoef.fSlave2CurDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(18);
    strTmp.remove(QRegExp("fSlave3VolDCK="));//从柜3电压直流校准参数K
    stru_newAdjCoef.fSlave3VolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(19);
    strTmp.remove(QRegExp("fSlave3VolDCB="));//从柜3电压直流校准参数B
    stru_newAdjCoef.fSlave3VolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(20);
    strTmp.remove(QRegExp("fSlave3CurDCK="));//从柜3电流直流校准参数K
    stru_newAdjCoef.fSlave3CurDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(21);
    strTmp.remove(QRegExp("fSlave3CurDCB="));//从柜3电流直流校准参数B
    stru_newAdjCoef.fSlave3CurDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(22);
    strTmp.remove(QRegExp("fSlave4VolDCK="));//从柜4电压直流校准参数K
    stru_newAdjCoef.fSlave4VolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(23);
    strTmp.remove(QRegExp("fSlave4VolDCB="));//从柜4电压直流校准参数B
    stru_newAdjCoef.fSlave4VolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(24);
    strTmp.remove(QRegExp("fSlave4CurDCK="));//从柜4电流直流校准参数K
    stru_newAdjCoef.fSlave4CurDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(25);
    strTmp.remove(QRegExp("fSlave4CurDCB="));//从柜4电流直流校准参数B
    stru_newAdjCoef.fSlave4CurDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(26);
    strTmp.remove(QRegExp("fTotalVolACK="));//总电压交流校准参数K
    stru_newAdjCoef.fTotalVolACK= strTmp.toFloat(&ok);

    strTmp=linelist.at(27);
    strTmp.remove(QRegExp("fTotalVolACB="));//总电压交流校准参数B
    stru_newAdjCoef.fTotalVolACB=strTmp.toFloat(&ok);

    strTmp=linelist.at(28);
    strTmp.remove(QRegExp("fTotalVolDCK="));//总电压直流校准参数K
    stru_newAdjCoef.fTotalVolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(29);
    strTmp.remove(QRegExp("fTotalVolDCB="));//总电压直流校准参数B
    stru_newAdjCoef.fTotalVolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(30);
    strTmp.remove(QRegExp("fCustom11K="));//外部预留11校准参数K
    stru_newAdjCoef.fCustom11K= strTmp.toFloat(&ok);

    strTmp=linelist.at(31);
    strTmp.remove(QRegExp("fCustom11B="));//外部预留11校准参数B
    stru_newAdjCoef.fCustom11B=strTmp.toFloat(&ok);

    strTmp=linelist.at(32);
    strTmp.remove(QRegExp("fCustom12K="));//外部预留12校准参数K
    stru_newAdjCoef.fCustom12K= strTmp.toFloat(&ok);

    strTmp=linelist.at(33);
    strTmp.remove(QRegExp("fCustom12B="));//外部预留12校准参数B
    stru_newAdjCoef.fCustom12B=strTmp.toFloat(&ok);

    strTmp=linelist.at(34);
    strTmp.remove(QRegExp("fTotalSlaveCurACK="));//从柜总电流交流校准参数K
    stru_newAdjCoef.fTotalSlaveCurACK= strTmp.toFloat(&ok);

    strTmp=linelist.at(35);
    strTmp.remove(QRegExp("fTotalSlaveCurACB="));//从柜总电流交流校准参数B
    stru_newAdjCoef.fTotalSlaveCurACB=strTmp.toFloat(&ok);

    file.close();
    return true;
}

bool CInifileparse::writeneweAdjcoefInifile(STRU_NEWADJCOEF stru_newAdjCoef)
{
    QStringList linelist;
    QString strHeader,strText;
#ifdef WIN_DEV
    m_strAdjFilepathName="./debug/newadjcoef.ini";
#else
    m_strAdjFilepathName=QApplication::applicationDirPath() + "/" +"newadjcoef.ini";
#endif

    QFile file(m_strAdjFilepathName);
    if(linelist.size()>0)
    {
        linelist.clear();
    }
    strHeader="fTriPhaseAVolDCK=";     //三相电A直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseAVolDCK,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseAVolDCB=";    //三相电A直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseAVolDCB,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseBVolDCK=";     //三相电B直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseBVolDCK,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseBVolDCB=";    //三相电B直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseBVolDCB,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseCVolDCK=";     //三相电C直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseCVolDCK,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseCVolDCB=";    //三相电C直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseCVolDCB,'f',3);
    linelist.append(strText);

    strHeader="fExcitVoltK=";     //励磁电压直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fExcitVoltK,'f',3);
    linelist.append(strText);

    strHeader="fExcitVoltB=";    //励磁电压直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fExcitVoltB,'f',3);
    linelist.append(strText);

    strHeader="fExcitCurK=";     //励磁电流直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fExcitCurK,'f',3);
    linelist.append(strText);

    strHeader="fExcitCurB=";    //励磁电流直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fExcitCurB,'f',3);
    linelist.append(strText);

    strHeader="fSlave1VolDCK=";     //从柜1电压直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave1VolDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave1VolDCB=";    //从柜1电压直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave1VolDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave1CurDCK=";     //从柜1电流直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave1CurDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave1CurDCB=";    //从柜1电流直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave1CurDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave2VolDCK=";     //从柜2电压直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave2VolDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave2VolDCB=";    //从柜2电压直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave2VolDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave2CurDCK=";     //从柜2电流直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave2CurDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave2CurDCB=";    //从柜2电流直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave2CurDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave3VolDCK=";     //从柜3电压直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave3VolDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave3VolDCB=";    //从柜3电压直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave3VolDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave3CurDCK=";     //从柜3电流直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave3CurDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave3CurDCB=";    //从柜3电流直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave3CurDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave4VolDCK=";     //从柜4电压直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave4VolDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave4VolDCB=";    //从柜4电压直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave4VolDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave4CurDCK=";     //从柜4电流直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave4CurDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave4CurDCB=";    //从柜4电流直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave4CurDCB,'f',3);
    linelist.append(strText);

    strHeader="fTotalVolACK=";     //总电压交流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalVolACK,'f',3);
    linelist.append(strText);

    strHeader="fTotalVolACB=";    //总电压交流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalVolACB,'f',3);
    linelist.append(strText);

    strHeader="fTotalVolDCK=";     //总电压直流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalVolDCK,'f',3);
    linelist.append(strText);

    strHeader="fTotalVolDCB=";    //总电压直流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalVolDCB,'f',3);
    linelist.append(strText);

    strHeader="fTotalSlaveCurACK=";     //从柜总电流交流参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalSlaveCurACK,'f',3);
    linelist.append(strText);

    strHeader="fTotalSlaveCurACB=";    //从柜总电流交流参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalSlaveCurACB,'f',3);
    linelist.append(strText);

    strHeader="fCustom11K=";     //外部预留11参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fCustom11K,'f',3);
    linelist.append(strText);

    strHeader="fCustom11B=";    //外部预留11参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fCustom11B,'f',3);
    linelist.append(strText);

    strHeader="fCustom12K=";     //外部预留12参数k
    strText=strHeader+QString::number(stru_newAdjCoef.fCustom12K,'f',3);
    linelist.append(strText);

    strHeader="fCustom12B=";    //外部预留12参数b
    strText=strHeader+QString::number(stru_newAdjCoef.fCustom12B,'f',3);
    linelist.append(strText);

      if(!file.open(QFile::WriteOnly | QFile::Text))
      {
          printf( "####Cannot open file for Writing####\n");
          return false;
      }
      int nlist=linelist.size();
      QString strtest;
      for(int i=0;i<linelist.size();i++)
      {
          strtest=linelist.at(i);
          file.write(linelist.at(i).toUtf8());
          file.write(QObject::tr("\n").toUtf8());
      }
      file.close();

    return true;
}

bool CInifileparse::readnewChainsetInifile(STRU_NEWCHASETDATA &stru_newChainset)
{
#ifdef WIN_DEV
    m_strStatusFilepathName="./debug/newchainset.ini";
#else
    m_strStatusFilepathName=QApplication::applicationDirPath() + "/" +"newchainset.ini";
#endif

    QFile file(m_strStatusFilepathName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    bool ok=false;
//	if(linelist.size()!=18)
    if(linelist.size()!=48) //add by 2020.11.24
    {
        return false;
    }
    memset(&stru_newChainset,0,sizeof(stru_newChainset));

    QString strTmp;
    strTmp=linelist.at(0);
    strTmp.remove(QRegExp("iJjtjVal="));//紧机停机
    stru_newChainset.iJjtjVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("iSJitiVal="));//S紧机停机
    stru_newChainset.iSJitiVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("iXtlqVal="));//系统冷却单元
    stru_newChainset.iXtlqVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("iZdtgwVal="));//振动台过温
    stru_newChainset.iZdtgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("iZdtgwyVal="));//振动台过位移
    stru_newChainset.iZdtgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("iHtgwyVal="));//滑台过位移
    stru_newChainset.iHtgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("iHtqyVal="));//滑台欠压
    stru_newChainset.iHtqyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("iHtqywVal="));//滑台欠液位
    stru_newChainset.iHtqywVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("iHtgwVal="));//滑台过温
    stru_newChainset.iHtgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("iGfrjbhVal="));//功放热继保护
    stru_newChainset.iGfrjbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("iJyzcdyVal="));//静压轴承低压
    stru_newChainset.iJyzcdyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("iZgmbhVal="));//主柜门保护
    stru_newChainset.iZgmbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("iSelfdefVal1="));//自定义1
    stru_newChainset.iSelfdefVal1= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("iSelfdefVal2="));//自定义2
    stru_newChainset.iSelfdefVal2= strTmp.toFloat(&ok);

    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("iSelfdefVal3="));//自定义3
    stru_newChainset.iSelfdefVal3= strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("iSelfdefVal4="));//自定义4
    stru_newChainset.iSelfdefVal4= strTmp.toFloat(&ok);

    strTmp=linelist.at(16);
    strTmp.remove(QRegExp("iC1zlqgwVal="));//从柜1整流器过温
    stru_newChainset.iC1zlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(17);
    strTmp.remove(QRegExp("iC2zlqgwVal="));//从柜2整流器过温
    stru_newChainset.iC2zlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(18);
    strTmp.remove(QRegExp("iC3zlqgwVal="));//从柜3整流器过温
    stru_newChainset.iC3zlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(19);
    strTmp.remove(QRegExp("iC4zlqgwVal="));//从柜4整流器过温
    stru_newChainset.iC4zlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(20);
    strTmp.remove(QRegExp("iC1cwbhVal="));//从柜1错误保护
    stru_newChainset.iC1cwbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(21);
    strTmp.remove(QRegExp("iC2cwbhVal="));//从柜2错误保护
    stru_newChainset.iC2cwbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(22);
    strTmp.remove(QRegExp("iC3cwbhVal="));//从柜3错误保护
    stru_newChainset.iC3cwbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(23);
    strTmp.remove(QRegExp("iC4cwbhVal="));//从柜4错误保护
    stru_newChainset.iC4cwbhVal= strTmp.toFloat(&ok);

//  触点切换读配置文件，add by 2020.11.24

    strTmp=linelist.at(24);
    strTmp.remove(QRegExp("isw_Jjtj="));//紧急停机
    stru_newChainset.isw_Jjtj= strTmp.toFloat(&ok);

    strTmp=linelist.at(25);
    strTmp.remove(QRegExp("isw_SJiti="));//S紧急停机
    stru_newChainset.isw_SJiti= strTmp.toFloat(&ok);

    strTmp=linelist.at(26);
    strTmp.remove(QRegExp("isw_Xtlq="));//系统冷却触电切换
    stru_newChainset.isw_Xtlq= strTmp.toFloat(&ok);

    strTmp=linelist.at(27);
    strTmp.remove(QRegExp("isw_Zdtgw="));//振动台过温触电切换
    stru_newChainset.isw_Zdtgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(28);
    strTmp.remove(QRegExp("isw_Zdtgwy="));//振动台过位移触电切换
    stru_newChainset.isw_Zdtgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(29);
    strTmp.remove(QRegExp("isw_Htgwy="));//滑台过位移触电切换
    stru_newChainset.isw_Htgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(30);
    strTmp.remove(QRegExp("isw_Htqy="));//滑台欠压触电切换
    stru_newChainset.isw_Htqy= strTmp.toFloat(&ok);

    strTmp=linelist.at(31);
    strTmp.remove(QRegExp("isw_Htqyw="));//滑台欠液位触电切换
    stru_newChainset.isw_Htqyw= strTmp.toFloat(&ok);

    strTmp=linelist.at(32);
    strTmp.remove(QRegExp("isw_Htgw="));//滑台过温触电切换
    stru_newChainset.isw_Htgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(33);
    strTmp.remove(QRegExp("isw_Gfrjbh="));//功放热继保护触电切换
    stru_newChainset.isw_Gfrjbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(34);
    strTmp.remove(QRegExp("isw_Jyzcdy="));//静压轴承低压触电切换
    stru_newChainset.isw_Jyzcdy= strTmp.toFloat(&ok);

    strTmp=linelist.at(35);
    strTmp.remove(QRegExp("isw_Zgmbh="));//主柜门保护触电切换
    stru_newChainset.isw_Zgmbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(36);
    strTmp.remove(QRegExp("isw_Selfdef1="));//自定义1触电切换
    stru_newChainset.isw_Selfdef1= strTmp.toFloat(&ok);

    strTmp=linelist.at(37);
    strTmp.remove(QRegExp("isw_Selfdef2="));//自定义2触电切换
    stru_newChainset.isw_Selfdef2= strTmp.toFloat(&ok);

    strTmp=linelist.at(38);
    strTmp.remove(QRegExp("isw_Selfdef3="));//自定义3触电切换
    stru_newChainset.isw_Selfdef3= strTmp.toFloat(&ok);

    strTmp=linelist.at(39);
    strTmp.remove(QRegExp("isw_Selfdef4="));//自定义4触电切换
    stru_newChainset.isw_Selfdef4= strTmp.toFloat(&ok);

    strTmp=linelist.at(40);
    strTmp.remove(QRegExp("isw_C1zlqgw="));//从柜1整流器过温触电切换
    stru_newChainset.isw_C1zlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(41);
    strTmp.remove(QRegExp("isw_C2zlqgw="));//从柜2整流器过温触电切换
    stru_newChainset.isw_C2zlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(42);
    strTmp.remove(QRegExp("isw_C3zlqgw="));//从柜3整流器过温触电切换
    stru_newChainset.isw_C3zlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(43);
    strTmp.remove(QRegExp("isw_C4zlqgw="));//从柜4整流器过温触电切换
    stru_newChainset.isw_C4zlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(44);
    strTmp.remove(QRegExp("isw_C1cwbh="));//从柜1错误保护触电切换
    stru_newChainset.isw_C1cwbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(45);
    strTmp.remove(QRegExp("isw_C2cwbh="));//从柜2错误保护触电切换
    stru_newChainset.isw_C2cwbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(46);
    strTmp.remove(QRegExp("isw_C3cwbh="));//从柜3错误保护触电切换
    stru_newChainset.isw_C3cwbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(47);
    strTmp.remove(QRegExp("isw_C4cwbh="));//从柜4错误保护触电切换
    stru_newChainset.isw_C4cwbh= strTmp.toFloat(&ok);

    file.close();
    return true;
}

bool CInifileparse::writenewChainsetInifile(STRU_NEWCHASETDATA stru_newChainset)
{
    QStringList linelist;
    QString strHeader,strText;
#ifdef WIN_DEV
    m_strStatusFilepathName="./debug/newchainset.ini";
#else
    m_strStatusFilepathName=QApplication::applicationDirPath() + "/" +"newchainset.ini";
#endif

    QFile file(m_strStatusFilepathName);

    if(linelist.size()>0)
    {
        linelist.clear();
    }
    strHeader="iJjtjVal=";     //紧急停机
    strText=strHeader+QString::number(stru_newChainset.iJjtjVal,10);
    linelist.append(strText);

    strHeader="iSJitiVal=";     //S紧急停机
    strText=strHeader+QString::number(stru_newChainset.iSJitiVal,10);
    linelist.append(strText);

    strHeader="iXtlqVal=";     //系统冷却
    strText=strHeader+QString::number(stru_newChainset.iXtlqVal,10);
    linelist.append(strText);

    strHeader="iZdtgwVal=";     //振动台过温
    strText=strHeader+QString::number(stru_newChainset.iZdtgwVal,10);
    linelist.append(strText);

    strHeader="iZdtgwyVal=";     //振动台过位移
    strText=strHeader+QString::number(stru_newChainset.iZdtgwyVal,10);
    linelist.append(strText);

    strHeader="iHtgwyVal=";     //滑台过位移
    strText=strHeader+QString::number(stru_newChainset.iHtgwyVal,10);
    linelist.append(strText);

    strHeader="iHtqyVal=";     //滑台欠压
    strText=strHeader+QString::number(stru_newChainset.iHtqyVal,10);
    linelist.append(strText);

    strHeader="iHtqywVal=";     //滑台欠液位
    strText=strHeader+QString::number(stru_newChainset.iHtqywVal,10);
    linelist.append(strText);

    strHeader="iHtgwVal=";     //滑台过温
    strText=strHeader+QString::number(stru_newChainset.iHtgwVal,10);
    linelist.append(strText);

    strHeader="iGfrjbhVal=";     //功放热继保护
    strText=strHeader+QString::number(stru_newChainset.iGfrjbhVal,10);
    linelist.append(strText);

    strHeader="iJyzcdyVal=";     //静压轴承低压
    strText=strHeader+QString::number(stru_newChainset.iJyzcdyVal,10);
    linelist.append(strText);

    strHeader="iZgmbhVal=";     //主柜门保护
    strText=strHeader+QString::number(stru_newChainset.iZgmbhVal,10);
    linelist.append(strText);

    strHeader="iSelfdefVal1=";     //自定义1
    strText=strHeader+QString::number(stru_newChainset.iSelfdefVal1,10);
    linelist.append(strText);

    strHeader="iSelfdefVal2=";     //自定义2
    strText=strHeader+QString::number(stru_newChainset.iSelfdefVal2,10);
    linelist.append(strText);

    strHeader="iSelfdefVal3=";     //自定义3
    strText=strHeader+QString::number(stru_newChainset.iSelfdefVal3,10);
    linelist.append(strText);

    strHeader="iSelfdefVal4=";     //自定义4
    strText=strHeader+QString::number(stru_newChainset.iSelfdefVal4,10);
    linelist.append(strText);

    strHeader="iC1zlqgwVal=";     //从柜1整流器过温
    strText=strHeader+QString::number(stru_newChainset.iC1zlqgwVal,10);
    linelist.append(strText);

    strHeader="iC2zlqgwVal=";     //从柜2整流器过温
    strText=strHeader+QString::number(stru_newChainset.iC2zlqgwVal,10);
    linelist.append(strText);

    strHeader="iC3zlqgwVal=";     //从柜3整流器过温
    strText=strHeader+QString::number(stru_newChainset.iC3zlqgwVal,10);
    linelist.append(strText);

    strHeader="iC4zlqgwVal=";     //从柜4整流器过温
    strText=strHeader+QString::number(stru_newChainset.iC4zlqgwVal,10);
    linelist.append(strText);

    strHeader="iC1cwbhVal=";     //从柜1错误保护
    strText=strHeader+QString::number(stru_newChainset.iC1cwbhVal,10);
    linelist.append(strText);

    strHeader="iC2cwbhVal=";     //从柜2错误保护
    strText=strHeader+QString::number(stru_newChainset.iC2cwbhVal,10);
    linelist.append(strText);

    strHeader="iC3cwbhVal=";     //从柜3错误保护
    strText=strHeader+QString::number(stru_newChainset.iC3cwbhVal,10);
    linelist.append(strText);

    strHeader="iC4cwbhVal=";     //从柜4错误保护
    strText=strHeader+QString::number(stru_newChainset.iC4cwbhVal,10);
    linelist.append(strText);

//  触点切换写配置文件，add by 2020.11.24
    strHeader="isw_Jjtj=";     //紧急停机
    strText=strHeader+QString::number(stru_newChainset.isw_Jjtj,10);
    linelist.append(strText);

    strHeader="isw_SJiti=";     //S紧急停机
    strText=strHeader+QString::number(stru_newChainset.isw_SJiti,10);
    linelist.append(strText);

    strHeader="isw_Xtlq=";     //系统冷却
    strText=strHeader+QString::number(stru_newChainset.isw_Xtlq,10);
    linelist.append(strText);

    strHeader="isw_Zdtgw=";     //振动台过温
    strText=strHeader+QString::number(stru_newChainset.isw_Zdtgw,10);
    linelist.append(strText);

    strHeader="isw_Zdtgwy=";     //振动台过位移
    strText=strHeader+QString::number(stru_newChainset.isw_Zdtgwy,10);
    linelist.append(strText);

    strHeader="isw_Htgwy=";     //滑台过位移
    strText=strHeader+QString::number(stru_newChainset.isw_Htgwy,10);
    linelist.append(strText);

    strHeader="isw_Htqy=";     //滑台欠压
    strText=strHeader+QString::number(stru_newChainset.isw_Htqy,10);
    linelist.append(strText);

    strHeader="isw_Htqyw=";     //滑台欠液位
    strText=strHeader+QString::number(stru_newChainset.isw_Htqyw,10);
    linelist.append(strText);

    strHeader="isw_Htgw=";     //滑台过温
    strText=strHeader+QString::number(stru_newChainset.isw_Htgw,10);
    linelist.append(strText);

    strHeader="isw_Gfrjbh=";     //功放热继保护
    strText=strHeader+QString::number(stru_newChainset.isw_Gfrjbh,10);
    linelist.append(strText);

    strHeader="isw_Jyzcdy=";     //静压轴承低压
    strText=strHeader+QString::number(stru_newChainset.isw_Jyzcdy,10);
    linelist.append(strText);

    strHeader="isw_Zgmbh=";     //主柜门保护
    strText=strHeader+QString::number(stru_newChainset.isw_Zgmbh,10);
    linelist.append(strText);

    strHeader="isw_Selfdef1=";     //自定义1
    strText=strHeader+QString::number(stru_newChainset.isw_Selfdef1,10);
    linelist.append(strText);

    strHeader="isw_Selfdef2=";     //自定义2
    strText=strHeader+QString::number(stru_newChainset.isw_Selfdef2,10);
    linelist.append(strText);

    strHeader="isw_Selfdef3=";     //自定义3
    strText=strHeader+QString::number(stru_newChainset.isw_Selfdef3,10);
    linelist.append(strText);

    strHeader="isw_Selfdef4=";     //自定义4
    strText=strHeader+QString::number(stru_newChainset.isw_Selfdef4,10);
    linelist.append(strText);

    strHeader="isw_C1zlqgw=";     //从柜1整流器过温
    strText=strHeader+QString::number(stru_newChainset.isw_C1zlqgw,10);
    linelist.append(strText);

    strHeader="isw_C2zlqgw=";     //从柜2整流器过温
    strText=strHeader+QString::number(stru_newChainset.isw_C2zlqgw,10);
    linelist.append(strText);

    strHeader="isw_C3zlqgw=";     //从柜3整流器过温
    strText=strHeader+QString::number(stru_newChainset.isw_C3zlqgw,10);
    linelist.append(strText);

    strHeader="isw_C4zlqgw=";     //从柜4整流器过温
    strText=strHeader+QString::number(stru_newChainset.isw_C4zlqgw,10);
    linelist.append(strText);

    strHeader="isw_C1cwbh=";     //从柜1错误保护
    strText=strHeader+QString::number(stru_newChainset.isw_C1cwbh,10);
    linelist.append(strText);

    strHeader="isw_C2cwbh=";     //从柜2错误保护
    strText=strHeader+QString::number(stru_newChainset.isw_C2cwbh,10);
    linelist.append(strText);

    strHeader="isw_C3cwbh=";     //从柜3错误保护
    strText=strHeader+QString::number(stru_newChainset.isw_C3cwbh,10);
    linelist.append(strText);

    strHeader="isw_C4cwbh=";     //从柜4错误保护
    strText=strHeader+QString::number(stru_newChainset.isw_C4cwbh,10);
    linelist.append(strText);



    if(!file.open(QFile::WriteOnly | QFile::Text))
     {
          printf( "####Cannot open file for Writing####\n");
          return false;
     }
     int nlist=linelist.size();
     QString strtest;
     for(int i=0;i<linelist.size();i++)
     {
          strtest=linelist.at(i);
          file.write(linelist.at(i).toUtf8());
          file.write(QObject::tr("\n").toUtf8());
     }
     file.close();
    return true;

}





