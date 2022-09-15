/****************************************************************************
** CopyRight(c) 2019,������֪�����ܿƼ����޹�˾
** All rights reserved
**
** �ļ�����: inifileparse.cpp
** ժҪ: �����ļ�������
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
//ʧЧ���ö������ļ�
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
    strTmp.remove(QRegExp("ActivationDate="));//ϵͳ����ʱ�䣬add by 2020.11.17
    stru_Totalrunning.activeTime=strTmp.toFloat(&ok);
    strActiveDate=strTmp;// add by 2020.11.18
    active_date_time = QDateTime::fromString(strTmp,"yyyy.MM.dd hh:mm:ss");// add by 2020.11.18

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("CalendarDay=")); //��Ȼ�������ޣ�add by 2020.11.17
    stru_Totalrunning.lSetCalendarDay=strTmp.toFloat(&ok);
    calendarDay=stru_Totalrunning.lSetCalendarDay;// add by 2020.11.18

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("OperatingTime="));//�ۼ�����ʱ�����ޣ�add by 2020.11.17
    stru_Totalrunning.lSetValue=strTmp.toFloat(&ok);

    file.close();//�ر��ļ�
    return true;
}
//ʧЧ����д�����ļ�
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

    strHeader="ActivationDate=";     //ϵͳ����ʱ�䣬add by 2020.11.17
    strText=strHeader+strActiveDate;//add by 2020.11.18
    linelist.append(strText);

    strHeader="CalendarDay=";     //��Ȼ�������ޣ�add by 2020.11.17
    strText=strHeader+QString::number(stru_Totalrunning.lSetCalendarDay,'f',1);
    linelist.append(strText);

    strHeader="OperatingTime=";     //�ۼ�����ʱ�����ޣ�add by 2020.11.17
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
//��ȡprocvalueset.ini�����ļ�
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
//д��procvalueset.ini�����ļ�
int  CInifileparse::writeProcValueSetInifile()
{
    return 0;
}
//��ȡbasicparaset.ini�����ļ�
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
    strTmp.remove(QRegExp("busvoltup="));//ĸ�ߵ�ѹ���߲�����add by 2019.05.28
    stru_BasicPara.fBusvoltUp= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("busvoltlow="));//ĸ�ߵ�ѹ���Ͳ�����add by 2019.05.28
    stru_BasicPara.fBusvoltLow=strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("threevoltup="));//�����ѹ���߲�����add by 2019.05.28
    stru_BasicPara.fThreevoltUp= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("threevoltlow="));//�����ѹ���Ͳ�����add by 2019.05.28
    stru_BasicPara.fThreevoltLow=strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("busimbalance="));//ĸ�ߵ�ѹ�����������add by 2019.05.28
    stru_BasicPara.fBusImbalance= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("voltimbalance="));//�����ѹ�����������add by 2019.05.28
    stru_BasicPara.fVoltimbalance=strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("sub1cabinetcurrentup="));//�ֹ�1����������߲�����add by 2019.05.28
    stru_BasicPara.fSub1CabinetcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("sub2cabinetcurrentup="));//�ֹ�2����������߲�����add by 2019.05.28
    stru_BasicPara.fSub2CabinetcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("sub3cabinetcurrentup="));//�ֹ�3����������߲�����add by 2019.05.28
    stru_BasicPara.fSub3CabinetcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("sub4cabinetcurrentup="));//�ֹ�4����������߲�����add by 2019.05.28
    stru_BasicPara.fSub4CabinetcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("totalvoltup="));//�����������ѹ���߲�����add by 2019.05.28
    stru_BasicPara.fTotalvoltUp= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("totalcurrentup="));//����������������߲�����add by 2019.05.28
    stru_BasicPara.fTotalcurrentUp=strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("sub1cabopen="));//�ֹ�1�����ǲ�����add by 2019.06.02
    stru_BasicPara.iSub1CabOpen=(int)strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("sub2cabopen="));//�ֹ�2�����ǲ�����add by 2019.06.02
    stru_BasicPara.iSub2CabOpen=(int)strTmp.toFloat(&ok);


    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("sub3cabopen="));//�ֹ�3�����ǲ�����add by 2019.06.02
    stru_BasicPara.iSub3CabOpen=(int)strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("sub4cabopen="));//�ֹ�4�����ǲ�����add by 2019.06.02
    stru_BasicPara.iSub4CabOpen=(int)strTmp.toFloat(&ok);
    file.close();
    return true;
}
//д��basicparaset.ini�����ļ�,add by zqc 2019.06.02
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
    strHeader="busvoltup=";     //ĸ�ߵ�ѹ���߲�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fBusvoltUp,'f',1);
    linelist.append(strText);

    strHeader="busvoltlow=";    //ĸ�ߵ�ѹ���Ͳ�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fBusvoltLow,'f',1);
    linelist.append(strText);

    strHeader="threevoltup="; //�����ѹ���߲�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fThreevoltUp,'f',1);
    linelist.append(strText);

    strHeader="threevoltlow="; //�����ѹ���Ͳ�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fThreevoltLow,'f',1);
    linelist.append(strText);

    strHeader="busimbalance=";//ĸ�ߵ�ѹ�����������add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fBusImbalance,'f',1);
    linelist.append(strText);

    strHeader="voltimbalance="; //�����ѹ�����������add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fVoltimbalance,'f',1);
    linelist.append(strText);

    strHeader="sub1cabinetcurrentup=";//�ֹ�1����������߲�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fSub1CabinetcurrentUp,'f',1);
    linelist.append(strText);

    strHeader="sub2cabinetcurrentup=";//�ֹ�2����������߲�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fSub2CabinetcurrentUp,'f',1);
    linelist.append(strText);

    strHeader="sub3cabinetcurrentup=";//�ֹ�3����������߲�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fSub3CabinetcurrentUp,'f',1);
    linelist.append(strText);

    strHeader="sub4cabinetcurrentup=";//�ֹ�4����������߲�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fSub4CabinetcurrentUp,'f',1);
    linelist.append(strText);


    strHeader="totalvoltup="; //�����������ѹ���߲�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fTotalvoltUp,'f',1);
    linelist.append(strText);

    strHeader="totalcurrentup=";//����������������߲�����add by 2019.06.02
    strText=strHeader+QString::number(stru_BasicPara.fTotalcurrentUp,'f',1);
    linelist.append(strText);

     strHeader="sub1cabopen=";//�ֹ�1�����ǲ�����add by 2019.06.02
     strText=strHeader+QString::number(stru_BasicPara.iSub1CabOpen,'f',1);
     linelist.append(strText);

     strHeader="sub2cabopen=";//�ֹ�2�����ǲ�����add by 2019.06.02
     strText=strHeader+QString::number(stru_BasicPara.iSub2CabOpen,'f',1);
     linelist.append(strText);

     strHeader="sub3cabopen=";//�ֹ�3�����ǲ�����add by 2019.06.02
     strText=strHeader+QString::number(stru_BasicPara.iSub3CabOpen,'f',1);
     linelist.append(strText);

     strHeader="sub4cabopen=";//�ֹ�4�����ǲ�����add by 2019.06.02
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
//У׼ϵ���������ļ�����
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
    strTmp.remove(QRegExp("sub1voltk="));//�ӹ�1ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub1voltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("sub1voltb="));//�ӹ�1ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub1voltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("sub1actvoltk="));//�ӹ�1��ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub1ActvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("sub1actvoltb="));//�ӹ�1��ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub1ActvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("sub1negvoltk="));//�ӹ�1��ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub1negvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("sub1negvoltb="));//�ӹ�1��ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub1negvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("sub1outvoltk="));//�ӹ�1�����ѹУ׼����K
    stru_AdjCoef.fSub1outvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("sub1outvoltb="));//�ӹ�1�����ѹУ׼����B
    stru_AdjCoef.fSub1outvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("sub1outcurrk="));//�ӹ�1�������У׼����K
    stru_AdjCoef.fSub1outcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("sub1outcurrb="));//�ӹ�1�������У׼����B
    stru_AdjCoef.fSub1outcurrB=strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("sub2voltk="));//�ӹ�2ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub2voltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("sub2voltb="));//�ӹ�2ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub2voltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("sub2actvoltk="));//�ӹ�2��ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub2ActvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("sub2actvoltb="));//�ӹ�2��ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub2ActvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("sub2negvoltk="));//�ӹ�2��ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub2negvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("sub2negvoltb="));//�ӹ�2��ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub2negvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(16);
    strTmp.remove(QRegExp("sub2outvoltk="));//�ӹ�2�����ѹУ׼����K
    stru_AdjCoef.fSub2outvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(17);
    strTmp.remove(QRegExp("sub2outvoltb="));//�ӹ�2�����ѹУ׼����B
    stru_AdjCoef.fSub2outvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(18);
    strTmp.remove(QRegExp("sub2outcurrk="));//�ӹ�2�������У׼����K
    stru_AdjCoef.fSub2outcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(19);
    strTmp.remove(QRegExp("sub2outcurrb="));//�ӹ�2�������У׼����B
    stru_AdjCoef.fSub2outcurrB=strTmp.toFloat(&ok);

    strTmp=linelist.at(20);
    strTmp.remove(QRegExp("sub3voltk="));//�ӹ�3ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub3voltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(21);
    strTmp.remove(QRegExp("sub3voltb="));//�ӹ�3ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub3voltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(22);
    strTmp.remove(QRegExp("sub3actvoltk="));//�ӹ�3��ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub3ActvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(23);
    strTmp.remove(QRegExp("sub3actvoltb="));//�ӹ�3��ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub3ActvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(24);
    strTmp.remove(QRegExp("sub3negvoltk="));//�ӹ�3��ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub3negvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(25);
    strTmp.remove(QRegExp("sub3negvoltb="));//�ӹ�3��ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub3negvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(26);
    strTmp.remove(QRegExp("sub3outvoltk="));//�ӹ�3�����ѹУ׼����K
    stru_AdjCoef.fSub3outvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(27);
    strTmp.remove(QRegExp("sub3outvoltb="));//�ӹ�3�����ѹУ׼����B
    stru_AdjCoef.fSub3outvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(28);
    strTmp.remove(QRegExp("sub3outcurrk="));//�ӹ�3�������У׼����K
    stru_AdjCoef.fSub3outcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(29);
    strTmp.remove(QRegExp("sub3outcurrb="));//�ӹ�3�������У׼����B
    stru_AdjCoef.fSub3outcurrB=strTmp.toFloat(&ok);

    strTmp=linelist.at(30);
    strTmp.remove(QRegExp("sub4voltk="));//�ӹ�4ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub4voltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(31);
    strTmp.remove(QRegExp("sub4voltb="));//�ӹ�4ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub4voltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(32);
    strTmp.remove(QRegExp("sub4actvoltk="));//�ӹ�4��ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub4ActvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(33);
    strTmp.remove(QRegExp("sub4actvoltb="));//�ӹ�4��ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub4ActvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(34);
    strTmp.remove(QRegExp("sub4negvoltk="));//�ӹ�4��ĸ�ߵ�ѹУ׼����K
    stru_AdjCoef.fSub4negvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(35);
    strTmp.remove(QRegExp("sub4negvoltb="));//�ӹ�4��ĸ�ߵ�ѹУ׼����B
    stru_AdjCoef.fSub4negvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(36);
    strTmp.remove(QRegExp("sub4outvoltk="));//�ӹ�4�����ѹУ׼����K
    stru_AdjCoef.fSub4outvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(37);
    strTmp.remove(QRegExp("sub4outvoltb="));//�ӹ�4�����ѹУ׼����B
    stru_AdjCoef.fSub4outvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(38);
    strTmp.remove(QRegExp("sub4outcurrk="));//�ӹ�4�������У׼����K
    stru_AdjCoef.fSub4outcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(39);
    strTmp.remove(QRegExp("sub4outcurrb="));//�ӹ�4�������У׼����B
    stru_AdjCoef.fSub4outcurrB=strTmp.toFloat(&ok);

    strTmp=linelist.at(40);
    strTmp.remove(QRegExp("mavoltk="));//A���ѹУ׼����K
    stru_AdjCoef.fMAvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(41);
    strTmp.remove(QRegExp("mavoltb="));//A���ѹУ׼����B
    stru_AdjCoef.fMAvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(42);
    strTmp.remove(QRegExp("mbvoltk="));//B���ѹУ׼����K
    stru_AdjCoef.fMBvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(43);
    strTmp.remove(QRegExp("mbvoltb="));//B���ѹУ׼����B
    stru_AdjCoef.fMBvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(44);
    strTmp.remove(QRegExp("mcvoltk="));//C���ѹУ׼����K
    stru_AdjCoef.fMCvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(45);
    strTmp.remove(QRegExp("mcvoltb="));//C���ѹУ׼����B
    stru_AdjCoef.fMCvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(46);
    strTmp.remove(QRegExp("mevoltk="));//���ŵ�ѹУ׼����K
    stru_AdjCoef.fMEvoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(47);
    strTmp.remove(QRegExp("mevoltb="));//���ŵ�ѹУ׼����B
    stru_AdjCoef.fMEvoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(48);
    strTmp.remove(QRegExp("mecurrk="));//���ŵ���У׼����K
    stru_AdjCoef.fMEcurrK= strTmp.toFloat(&ok);

    strTmp=linelist.at(49);
    strTmp.remove(QRegExp("mecurrb="));//���ŵ���У׼����B
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
    strHeader="sub1voltk=";     //�ӹ�1ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1voltK,'f',3);
    linelist.append(strText);

    strHeader="sub1voltb=";    //�ӹ�1ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1voltB,'f',3);
    linelist.append(strText);

    strHeader="sub1actvoltk=";     //�ӹ�1��ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1ActvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub1actvoltb=";    //�ӹ�1��ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1ActvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub1negvoltk=";     //�ӹ�1��ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1negvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub1negvoltb=";    //�ӹ�1��ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1negvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub1outvoltk=";     //�ӹ�1�����ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1outvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub1outvoltb=";    //�ӹ�1�����ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1outvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub1outcurrk=";     //�ӹ�1�����������k
    strText=strHeader+QString::number(stru_AdjCoef.fSub1outcurrK,'f',3);
    linelist.append(strText);

    strHeader="sub1outcurrb=";    //�ӹ�1�����������b
    strText=strHeader+QString::number(stru_AdjCoef.fSub1outcurrB,'f',3);
    linelist.append(strText);

    strHeader="sub2voltk=";     //�ӹ�2ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2voltK,'f',3);
    linelist.append(strText);

    strHeader="sub2voltb=";    //�ӹ�2ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2voltB,'f',3);
    linelist.append(strText);

    strHeader="sub2actvoltk=";     //�ӹ�2��ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2ActvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub2actvoltb=";    //�ӹ�2��ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2ActvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub2negvoltk=";     //�ӹ�2��ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2negvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub2negvoltb=";    //�ӹ�2��ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2negvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub2outvoltk=";     //�ӹ�2�����ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2outvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub2outvoltb=";    //�ӹ�2�����ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2outvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub2outcurrk=";     //�ӹ�2�����������k
    strText=strHeader+QString::number(stru_AdjCoef.fSub2outcurrK,'f',3);
    linelist.append(strText);

    strHeader="sub2outcurrb=";    //�ӹ�2�����������b
    strText=strHeader+QString::number(stru_AdjCoef.fSub2outcurrB,'f',3);
    linelist.append(strText);

    strHeader="sub3voltk=";     //�ӹ�3ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3voltK,'f',3);
    linelist.append(strText);

    strHeader="sub3voltb=";    //�ӹ�3ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3voltB,'f',3);
    linelist.append(strText);

    strHeader="sub3actvoltk=";     //�ӹ�3��ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3ActvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub3actvoltb=";    //�ӹ�3��ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3ActvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub3negvoltk=";     //�ӹ�3��ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3negvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub3negvoltb=";    //�ӹ�3��ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3negvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub3outvoltk=";     //�ӹ�3�����ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3outvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub3outvoltb=";    //�ӹ�3�����ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3outvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub3outcurrk=";     //�ӹ�3�����������k
    strText=strHeader+QString::number(stru_AdjCoef.fSub3outcurrK,'f',3);
    linelist.append(strText);

    strHeader="sub3outcurrb=";    //�ӹ�3�����������b
    strText=strHeader+QString::number(stru_AdjCoef.fSub3outcurrB,'f',3);
    linelist.append(strText);

    strHeader="sub4voltk=";     //�ӹ�4ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4voltK,'f',3);
    linelist.append(strText);

    strHeader="sub4voltb=";    //�ӹ�4ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4voltB,'f',3);
    linelist.append(strText);

    strHeader="sub4actvoltk=";     //�ӹ�4��ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4ActvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub4actvoltb=";    //�ӹ�4��ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4ActvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub4negvoltk=";     //�ӹ�4��ĸ�ߵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4negvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub4negvoltb=";    //�ӹ�4��ĸ�ߵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4negvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub4outvoltk=";     //�ӹ�4�����ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4outvoltK,'f',3);
    linelist.append(strText);

    strHeader="sub4outvoltb=";    //�ӹ�4�����ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4outvoltB,'f',3);
    linelist.append(strText);

    strHeader="sub4outcurrk=";     //�ӹ�4�����������k
    strText=strHeader+QString::number(stru_AdjCoef.fSub4outcurrK,'f',3);
    linelist.append(strText);

    strHeader="sub4outcurrb=";    //�ӹ�4�����������b
    strText=strHeader+QString::number(stru_AdjCoef.fSub4outcurrB,'f',3);
    linelist.append(strText);

    strHeader="mavoltk=";     //A���ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fMAvoltK,'f',3);
    linelist.append(strText);

    strHeader="mavoltb=";    //A���ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fMAvoltB,'f',3);
    linelist.append(strText);

    strHeader="mbvoltk=";     //B���ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fMBvoltK,'f',3);
    linelist.append(strText);

    strHeader="mbvoltb=";    //B���ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fMBvoltB,'f',3);
    linelist.append(strText);

    strHeader="mcvoltk=";     //C���ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fMCvoltK,'f',3);
    linelist.append(strText);

    strHeader="mcvoltb=";    //C���ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fMCvoltB,'f',3);
    linelist.append(strText);

    strHeader="mevoltk=";     //���ŵ�ѹ����k
    strText=strHeader+QString::number(stru_AdjCoef.fMEvoltK,'f',3);
    linelist.append(strText);

    strHeader="mevoltb=";    //���ŵ�ѹ����b
    strText=strHeader+QString::number(stru_AdjCoef.fMEvoltB,'f',3);
    linelist.append(strText);

    strHeader="mecurrk=";     //���ŵ�������k
    strText=strHeader+QString::number(stru_AdjCoef.fMEcurrK,'f',3);
    linelist.append(strText);

    strHeader="mecurrb=";    //���ŵ�������b
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
//д��totaltime.ini�����ļ�
bool CInifileparse::writeStatusRecordInifile(STRU_STATUSRECORD stru_StatusRecord)
{
    //��totaltime.ini�����ļ���������

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
    strHeader="totaltime=";     //������ʱ��
    strText=strHeader+QString::number(stru_StatusRecord.lTotaltime,10);
    linelist.append(strText);

    strHeader="sumtime=";     //���һ��������ʱ��
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
//��ȡtotaltime.ini�����ļ�
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
    strTmp.remove(QRegExp("totaltime="));//������ʱ��
    stru_StatusRecord.lTotaltime= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("sumtime="));//���һ��������ʱ��
    stru_StatusRecord.iSumtime= strTmp.toFloat(&ok);
    file.close();
    return true;
}//дchainset.ini�����ļ�
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
    strHeader="iJjtjVal=";     //����ͣ��
    strText=strHeader+QString::number(stru_Chainset.iJjtjVal,10);
    linelist.append(strText);

    strHeader="iHtgwyVal=";     //��̨��λ��
    strText=strHeader+QString::number(stru_Chainset.iHtgwyVal,10);
    linelist.append(strText);

    strHeader="iZdtgwyVal=";     //��̨��λ��
    strText=strHeader+QString::number(stru_Chainset.iZdtgwyVal,10);
    linelist.append(strText);

    strHeader="iHtdywVal=";     //��̨��Һλ
    strText=strHeader+QString::number(stru_Chainset.iHtdywVal,10);
    linelist.append(strText);

    strHeader="iHtqyVal=";     //��̨��е�ѹ
    strText=strHeader+QString::number(stru_Chainset.iHtqyVal,10);
    linelist.append(strText);

    strHeader="iZdtgwVal=";     //��̨����
    strText=strHeader+QString::number(stru_Chainset.iZdtgwVal,10);
    linelist.append(strText);

    strHeader="iEzgwyVal=";     //�����λ��
    strText=strHeader+QString::number(stru_Chainset.iEzgwyVal,10);
    linelist.append(strText);

    strHeader="iGfrjbhVal=";     //�����ȼ̱���
    strText=strHeader+QString::number(stru_Chainset.iGfrjbhVal,10);
    linelist.append(strText);

    strHeader="iJyzcdyVal=";     //��ѹ��е�ѹ
    strText=strHeader+QString::number(stru_Chainset.iJyzcdyVal,10);
    linelist.append(strText);

    strHeader="iZgMenbVal=";     //�����ű���
    strText=strHeader+QString::number(stru_Chainset.iZgMenbVal,10);
    linelist.append(strText);

    strHeader="iSubMenbVal=";     //�ӹ��ű���
    strText=strHeader+QString::number(stru_Chainset.iSubMenbVal,10);
    linelist.append(strText);

    strHeader="iXtlqdyVal=";     //ϵͳ��ȴ��Ԫ
    strText=strHeader+QString::number(stru_Chainset.iXtlqdyVal,10);
    linelist.append(strText);

    strHeader="iHtqywVal=";     //���������Ź���
    strText=strHeader+QString::number(stru_Chainset.iHtqywVal,10);
    linelist.append(strText);

    strHeader="iSubzlqgwVal=";     //�ӹ������Ź���
    strText=strHeader+QString::number(stru_Chainset.iSubzlqgwVal,10);
    linelist.append(strText);

    strHeader="iSelfdefineVal1=";     //�Զ���1
    strText=strHeader+QString::number(stru_Chainset.iSelfdefineVal1,10);
    linelist.append(strText);

    strHeader="iSelfdefineVal2=";     //�Զ���2
    strText=strHeader+QString::number(stru_Chainset.iSelfdefineVal2,10);
    linelist.append(strText);

    strHeader="iSelfdefineVal3=";     //�Զ���3
    strText=strHeader+QString::number(stru_Chainset.iSelfdefineVal3,10);
    linelist.append(strText);

    strHeader="iSubyuliuPorcVal=";     //�ӹ�Ԥ������
    strText=strHeader+QString::number(stru_Chainset.iSubyuliuPorcVal,10);
    linelist.append(strText);

//  �����л�д�����ļ���add by 2020.11.24
    strHeader="iSwitch_Jjtj=";     //����ͣ��
    strText=strHeader+QString::number(stru_Chainset.iSwitch_Jjtj,10);
    linelist.append(strText);

    strHeader="iSwitch_htgwy=";     //��̨��λ��
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htgwy,10);
    linelist.append(strText);

    strHeader="iSwitch_zdtgwy=";    //��̨��λ��
    strText=strHeader+QString::number(stru_Chainset.iSwitch_zdtgwy,10);
    linelist.append(strText);

    strHeader="iSwitch_htdyw=";    //��̨��Һλ
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htdyw,10);
    linelist.append(strText);

    strHeader="iSwitch_htqy=";    //��̨��е�ѹ
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htqy,10);
    linelist.append(strText);

    strHeader="iSwitch_zdtgw=";    //��̨����
    strText=strHeader+QString::number(stru_Chainset.iSwitch_zdtgw,10);
    linelist.append(strText);

    strHeader="iSwitch_ezgwy=";    //�����λ��
    strText=strHeader+QString::number(stru_Chainset.iSwitch_ezgwy,10);
    linelist.append(strText);

    strHeader="iSwitch_gfrjbh=";    //�����ȼ̱���
    strText=strHeader+QString::number(stru_Chainset.iSwitch_gfrjbh,10);
    linelist.append(strText);

    strHeader="iSwitch_jyzcdy=";    //��ѹ��е�ѹ
    strText=strHeader+QString::number(stru_Chainset.iSwitch_jyzcdy,10);
    linelist.append(strText);

    strHeader="iSwitch_zgmenbh=";    //������
    strText=strHeader+QString::number(stru_Chainset.iSwitch_zgmenbh,10);
    linelist.append(strText);

    strHeader="iSwitch_htgw=";    //�ӹ���
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htgw,10);
    linelist.append(strText);

    strHeader="iSwitch_xtlqdy=";    //ϵͳ��ȴ��Ԫ
    strText=strHeader+QString::number(stru_Chainset.iSwitch_xtlqdy,10);
    linelist.append(strText);

    strHeader="iSwitch_htqyw=";    //��������������
    strText=strHeader+QString::number(stru_Chainset.iSwitch_htqyw,10);
    linelist.append(strText);

    strHeader="iSwitch_subzlqgw=";    //�ӹ�����������
    strText=strHeader+QString::number(stru_Chainset.iSwitch_subzlqgw,10);
    linelist.append(strText);

    strHeader="iSwitch_selfdefine1=";    //�Զ���1
    strText=strHeader+QString::number(stru_Chainset.iSwitch_selfdefine1,10);
    linelist.append(strText);

    strHeader="iSwitch_selfdefine2=";    //�Զ���2
    strText=strHeader+QString::number(stru_Chainset.iSwitch_selfdefine2,10);
    linelist.append(strText);

    strHeader="iSwitch_selfdefine3=";    //�Զ���3
    strText=strHeader+QString::number(stru_Chainset.iSwitch_selfdefine3,10);
    linelist.append(strText);

    strHeader="iSwitch_subyuliu=";    //�ӹ�Ԥ��
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
//��ȡchainset.ini�����ļ�
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
    strTmp.remove(QRegExp("iJjtjVal="));//����ͣ��
    stru_Chainset.iJjtjVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("iHtgwyVal="));//��̨��λ��
    stru_Chainset.iHtgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("iZdtgwyVal="));//��̨����
    stru_Chainset.iZdtgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("iHtdywVal="));//��̨��Һλ
    stru_Chainset.iHtdywVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("iHtqyVal="));//��̨��е�ѹ
    stru_Chainset.iHtqyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("iZdtgwVal="));//��̨����
    stru_Chainset.iZdtgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("iEzgwyVal="));//�����λ��
    stru_Chainset.iEzgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("iGfrjbhVal="));//�����ȼ̱���
    stru_Chainset.iGfrjbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("iJyzcdyVal="));//��ѹ��е�ѹ
    stru_Chainset.iJyzcdyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("iZgMenbVal="));//�����ű���
    stru_Chainset.iZgMenbVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("iSubMenbVal="));//�ӹ��ű���
    stru_Chainset.iSubMenbVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("iXtlqdyVal="));//ϵͳ��ȴ��Ԫ
    stru_Chainset.iXtlqdyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("iHtqywVal="));//���������Ź���
    stru_Chainset.iHtqywVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("iSubzlqgwVal="));//�ӹ������Ź���
    stru_Chainset.iSubzlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("iSelfdefineVal1="));//�Զ���1
    stru_Chainset.iSelfdefineVal1= strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("iSelfdefineVal2="));//�Զ���2
    stru_Chainset.iSelfdefineVal2= strTmp.toFloat(&ok);

    strTmp=linelist.at(16);
    strTmp.remove(QRegExp("iSelfdefineVal3="));//�Զ���3
    stru_Chainset.iSelfdefineVal3= strTmp.toFloat(&ok);

    strTmp=linelist.at(17);
    strTmp.remove(QRegExp("iSubyuliuPorcVal="));//�ӹ�Ԥ������
    stru_Chainset.iSubyuliuPorcVal= strTmp.toFloat(&ok);

//  �����л��������ļ���add by 2020.11.24

    strTmp=linelist.at(18);
    strTmp.remove(QRegExp("iSwitch_Jjtj="));//����ͣ��
    stru_Chainset.iSwitch_Jjtj= strTmp.toFloat(&ok);

    strTmp=linelist.at(19);
    strTmp.remove(QRegExp("iSwitch_htgwy="));//��̨��λ��
    stru_Chainset.iSwitch_htgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(20);
    strTmp.remove(QRegExp("iSwitch_zdtgwy="));//��̨��λ��
    stru_Chainset.iSwitch_zdtgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(21);
    strTmp.remove(QRegExp("iSwitch_htdyw="));//��̨��Һλ
    stru_Chainset.iSwitch_htdyw= strTmp.toFloat(&ok);

    strTmp=linelist.at(22);
    strTmp.remove(QRegExp("iSwitch_htqy="));//��̨��е�ѹ
    stru_Chainset.iSwitch_htqy= strTmp.toFloat(&ok);

    strTmp=linelist.at(23);
    strTmp.remove(QRegExp("iSwitch_zdtgw="));//��̨����
    stru_Chainset.iSwitch_zdtgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(24);
    strTmp.remove(QRegExp("iSwitch_ezgwy="));//�����λ��
    stru_Chainset.iSwitch_ezgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(25);
    strTmp.remove(QRegExp("iSwitch_gfrjbh="));//�����ȼ̱���
    stru_Chainset.iSwitch_gfrjbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(26);
    strTmp.remove(QRegExp("iSwitch_jyzcdy="));//��ѹ��е�ѹ
    stru_Chainset.iSwitch_jyzcdy= strTmp.toFloat(&ok);

    strTmp=linelist.at(27);
    strTmp.remove(QRegExp("iSwitch_zgmenbh="));//������
    stru_Chainset.iSwitch_zgmenbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(28);
    strTmp.remove(QRegExp("iSwitch_htgw="));//�ӹ���
    stru_Chainset.iSwitch_htgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(29);
    strTmp.remove(QRegExp("iSwitch_xtlqdy="));//ϵͳ��ȴ��Ԫ
    stru_Chainset.iSwitch_xtlqdy= strTmp.toFloat(&ok);

    strTmp=linelist.at(30);
    strTmp.remove(QRegExp("iSwitch_htqyw="));//��������������
    stru_Chainset.iSwitch_htqyw= strTmp.toFloat(&ok);

    strTmp=linelist.at(31);
    strTmp.remove(QRegExp("iSwitch_subzlqgw="));//�ӹ�����������
    stru_Chainset.iSwitch_subzlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(32);
    strTmp.remove(QRegExp("iSwitch_selfdefine1="));//�Զ���1
    stru_Chainset.iSwitch_selfdefine1= strTmp.toFloat(&ok);

    strTmp=linelist.at(33);
    strTmp.remove(QRegExp("iSwitch_selfdefine2="));//�Զ���2
    stru_Chainset.iSwitch_selfdefine2= strTmp.toFloat(&ok);

    strTmp=linelist.at(34);
    strTmp.remove(QRegExp("iSwitch_selfdefine3="));//�Զ���2
    stru_Chainset.iSwitch_selfdefine3= strTmp.toFloat(&ok);

    strTmp=linelist.at(35);
    strTmp.remove(QRegExp("iSwitch_subyuliu="));//�ӹ�Ԥ������
    stru_Chainset.iSwitch_subyuliu= strTmp.toFloat(&ok);

    file.close();
    return true;
}
//д��OutputLog.ini�����ļ� add by 2020.11.12
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
//������������¼д��OutputRecord�ļ� add by 2020.11.12
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
//������ֹͣ��¼д��OutputRecord�ļ� add by 2020.11.12
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
//��У׼ϵ���������ļ�����
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
    strTmp.remove(QRegExp("fTriPhaseAVolDCK="));//�����Aֱ��У׼����K
    stru_newAdjCoef.fTriPhaseAVolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("fTriPhaseAVolDCB="));//�����Aֱ��У׼����B
    stru_newAdjCoef.fTriPhaseAVolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("fTriPhaseBVolDCK="));//�����Bֱ��У׼����K
    stru_newAdjCoef.fTriPhaseBVolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("fTriPhaseBVolDCB="));//�����Bֱ��У׼����B
    stru_newAdjCoef.fTriPhaseBVolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("fTriPhaseCVolDCK="));//�����Cֱ��У׼����K
    stru_newAdjCoef.fTriPhaseCVolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("fTriPhaseCVolDCB="));//�����Cֱ��У׼����B
    stru_newAdjCoef.fTriPhaseCVolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("fExcitVoltK="));//���ŵ�ѹֱ��У׼����K
    stru_newAdjCoef.fExcitVoltK= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("fExcitVoltB="));//���ŵ�ѹֱ��У׼����B
    stru_newAdjCoef.fExcitVoltB=strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("fExcitCurK="));//���ŵ���ֱ��У׼����K
    stru_newAdjCoef.fExcitCurK= strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("fExcitCurB="));//���ŵ���ֱ��У׼����B
    stru_newAdjCoef.fExcitCurB=strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("fSlave1VolDCK="));//�ӹ�1��ѹֱ��У׼����K
    stru_newAdjCoef.fSlave1VolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("fSlave1VolDCB="));//�ӹ�1��ѹֱ��У׼����B
    stru_newAdjCoef.fSlave1VolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("fSlave1CurDCK="));//�ӹ�1����ֱ��У׼����K
    stru_newAdjCoef.fSlave1CurDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("fSlave1CurDCB="));//�ӹ�1����ֱ��У׼����B
    stru_newAdjCoef.fSlave1CurDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("fSlave2VolDCK="));//�ӹ�2��ѹֱ��У׼����K
    stru_newAdjCoef.fSlave2VolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("fSlave2VolDCB="));//�ӹ�2��ѹֱ��У׼����B
    stru_newAdjCoef.fSlave2VolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(16);
    strTmp.remove(QRegExp("fSlave2CurDCK="));//�ӹ�2����ֱ��У׼����K
    stru_newAdjCoef.fSlave2CurDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(17);
    strTmp.remove(QRegExp("fSlave2CurDCB="));//�ӹ�2����ֱ��У׼����B
    stru_newAdjCoef.fSlave2CurDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(18);
    strTmp.remove(QRegExp("fSlave3VolDCK="));//�ӹ�3��ѹֱ��У׼����K
    stru_newAdjCoef.fSlave3VolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(19);
    strTmp.remove(QRegExp("fSlave3VolDCB="));//�ӹ�3��ѹֱ��У׼����B
    stru_newAdjCoef.fSlave3VolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(20);
    strTmp.remove(QRegExp("fSlave3CurDCK="));//�ӹ�3����ֱ��У׼����K
    stru_newAdjCoef.fSlave3CurDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(21);
    strTmp.remove(QRegExp("fSlave3CurDCB="));//�ӹ�3����ֱ��У׼����B
    stru_newAdjCoef.fSlave3CurDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(22);
    strTmp.remove(QRegExp("fSlave4VolDCK="));//�ӹ�4��ѹֱ��У׼����K
    stru_newAdjCoef.fSlave4VolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(23);
    strTmp.remove(QRegExp("fSlave4VolDCB="));//�ӹ�4��ѹֱ��У׼����B
    stru_newAdjCoef.fSlave4VolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(24);
    strTmp.remove(QRegExp("fSlave4CurDCK="));//�ӹ�4����ֱ��У׼����K
    stru_newAdjCoef.fSlave4CurDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(25);
    strTmp.remove(QRegExp("fSlave4CurDCB="));//�ӹ�4����ֱ��У׼����B
    stru_newAdjCoef.fSlave4CurDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(26);
    strTmp.remove(QRegExp("fTotalVolACK="));//�ܵ�ѹ����У׼����K
    stru_newAdjCoef.fTotalVolACK= strTmp.toFloat(&ok);

    strTmp=linelist.at(27);
    strTmp.remove(QRegExp("fTotalVolACB="));//�ܵ�ѹ����У׼����B
    stru_newAdjCoef.fTotalVolACB=strTmp.toFloat(&ok);

    strTmp=linelist.at(28);
    strTmp.remove(QRegExp("fTotalVolDCK="));//�ܵ�ѹֱ��У׼����K
    stru_newAdjCoef.fTotalVolDCK= strTmp.toFloat(&ok);

    strTmp=linelist.at(29);
    strTmp.remove(QRegExp("fTotalVolDCB="));//�ܵ�ѹֱ��У׼����B
    stru_newAdjCoef.fTotalVolDCB=strTmp.toFloat(&ok);

    strTmp=linelist.at(30);
    strTmp.remove(QRegExp("fCustom11K="));//�ⲿԤ��11У׼����K
    stru_newAdjCoef.fCustom11K= strTmp.toFloat(&ok);

    strTmp=linelist.at(31);
    strTmp.remove(QRegExp("fCustom11B="));//�ⲿԤ��11У׼����B
    stru_newAdjCoef.fCustom11B=strTmp.toFloat(&ok);

    strTmp=linelist.at(32);
    strTmp.remove(QRegExp("fCustom12K="));//�ⲿԤ��12У׼����K
    stru_newAdjCoef.fCustom12K= strTmp.toFloat(&ok);

    strTmp=linelist.at(33);
    strTmp.remove(QRegExp("fCustom12B="));//�ⲿԤ��12У׼����B
    stru_newAdjCoef.fCustom12B=strTmp.toFloat(&ok);

    strTmp=linelist.at(34);
    strTmp.remove(QRegExp("fTotalSlaveCurACK="));//�ӹ��ܵ�������У׼����K
    stru_newAdjCoef.fTotalSlaveCurACK= strTmp.toFloat(&ok);

    strTmp=linelist.at(35);
    strTmp.remove(QRegExp("fTotalSlaveCurACB="));//�ӹ��ܵ�������У׼����B
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
    strHeader="fTriPhaseAVolDCK=";     //�����Aֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseAVolDCK,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseAVolDCB=";    //�����Aֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseAVolDCB,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseBVolDCK=";     //�����Bֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseBVolDCK,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseBVolDCB=";    //�����Bֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseBVolDCB,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseCVolDCK=";     //�����Cֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseCVolDCK,'f',3);
    linelist.append(strText);

    strHeader="fTriPhaseCVolDCB=";    //�����Cֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fTriPhaseCVolDCB,'f',3);
    linelist.append(strText);

    strHeader="fExcitVoltK=";     //���ŵ�ѹֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fExcitVoltK,'f',3);
    linelist.append(strText);

    strHeader="fExcitVoltB=";    //���ŵ�ѹֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fExcitVoltB,'f',3);
    linelist.append(strText);

    strHeader="fExcitCurK=";     //���ŵ���ֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fExcitCurK,'f',3);
    linelist.append(strText);

    strHeader="fExcitCurB=";    //���ŵ���ֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fExcitCurB,'f',3);
    linelist.append(strText);

    strHeader="fSlave1VolDCK=";     //�ӹ�1��ѹֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave1VolDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave1VolDCB=";    //�ӹ�1��ѹֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave1VolDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave1CurDCK=";     //�ӹ�1����ֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave1CurDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave1CurDCB=";    //�ӹ�1����ֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave1CurDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave2VolDCK=";     //�ӹ�2��ѹֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave2VolDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave2VolDCB=";    //�ӹ�2��ѹֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave2VolDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave2CurDCK=";     //�ӹ�2����ֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave2CurDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave2CurDCB=";    //�ӹ�2����ֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave2CurDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave3VolDCK=";     //�ӹ�3��ѹֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave3VolDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave3VolDCB=";    //�ӹ�3��ѹֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave3VolDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave3CurDCK=";     //�ӹ�3����ֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave3CurDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave3CurDCB=";    //�ӹ�3����ֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave3CurDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave4VolDCK=";     //�ӹ�4��ѹֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave4VolDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave4VolDCB=";    //�ӹ�4��ѹֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave4VolDCB,'f',3);
    linelist.append(strText);

    strHeader="fSlave4CurDCK=";     //�ӹ�4����ֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave4CurDCK,'f',3);
    linelist.append(strText);

    strHeader="fSlave4CurDCB=";    //�ӹ�4����ֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fSlave4CurDCB,'f',3);
    linelist.append(strText);

    strHeader="fTotalVolACK=";     //�ܵ�ѹ��������k
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalVolACK,'f',3);
    linelist.append(strText);

    strHeader="fTotalVolACB=";    //�ܵ�ѹ��������b
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalVolACB,'f',3);
    linelist.append(strText);

    strHeader="fTotalVolDCK=";     //�ܵ�ѹֱ������k
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalVolDCK,'f',3);
    linelist.append(strText);

    strHeader="fTotalVolDCB=";    //�ܵ�ѹֱ������b
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalVolDCB,'f',3);
    linelist.append(strText);

    strHeader="fTotalSlaveCurACK=";     //�ӹ��ܵ�����������k
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalSlaveCurACK,'f',3);
    linelist.append(strText);

    strHeader="fTotalSlaveCurACB=";    //�ӹ��ܵ�����������b
    strText=strHeader+QString::number(stru_newAdjCoef.fTotalSlaveCurACB,'f',3);
    linelist.append(strText);

    strHeader="fCustom11K=";     //�ⲿԤ��11����k
    strText=strHeader+QString::number(stru_newAdjCoef.fCustom11K,'f',3);
    linelist.append(strText);

    strHeader="fCustom11B=";    //�ⲿԤ��11����b
    strText=strHeader+QString::number(stru_newAdjCoef.fCustom11B,'f',3);
    linelist.append(strText);

    strHeader="fCustom12K=";     //�ⲿԤ��12����k
    strText=strHeader+QString::number(stru_newAdjCoef.fCustom12K,'f',3);
    linelist.append(strText);

    strHeader="fCustom12B=";    //�ⲿԤ��12����b
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
    strTmp.remove(QRegExp("iJjtjVal="));//����ͣ��
    stru_newChainset.iJjtjVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("iSJitiVal="));//S����ͣ��
    stru_newChainset.iSJitiVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("iXtlqVal="));//ϵͳ��ȴ��Ԫ
    stru_newChainset.iXtlqVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(3);
    strTmp.remove(QRegExp("iZdtgwVal="));//��̨����
    stru_newChainset.iZdtgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(4);
    strTmp.remove(QRegExp("iZdtgwyVal="));//��̨��λ��
    stru_newChainset.iZdtgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(5);
    strTmp.remove(QRegExp("iHtgwyVal="));//��̨��λ��
    stru_newChainset.iHtgwyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(6);
    strTmp.remove(QRegExp("iHtqyVal="));//��̨Ƿѹ
    stru_newChainset.iHtqyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(7);
    strTmp.remove(QRegExp("iHtqywVal="));//��̨ǷҺλ
    stru_newChainset.iHtqywVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(8);
    strTmp.remove(QRegExp("iHtgwVal="));//��̨����
    stru_newChainset.iHtgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(9);
    strTmp.remove(QRegExp("iGfrjbhVal="));//�����ȼ̱���
    stru_newChainset.iGfrjbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(10);
    strTmp.remove(QRegExp("iJyzcdyVal="));//��ѹ��е�ѹ
    stru_newChainset.iJyzcdyVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(11);
    strTmp.remove(QRegExp("iZgmbhVal="));//�����ű���
    stru_newChainset.iZgmbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(12);
    strTmp.remove(QRegExp("iSelfdefVal1="));//�Զ���1
    stru_newChainset.iSelfdefVal1= strTmp.toFloat(&ok);

    strTmp=linelist.at(13);
    strTmp.remove(QRegExp("iSelfdefVal2="));//�Զ���2
    stru_newChainset.iSelfdefVal2= strTmp.toFloat(&ok);

    strTmp=linelist.at(14);
    strTmp.remove(QRegExp("iSelfdefVal3="));//�Զ���3
    stru_newChainset.iSelfdefVal3= strTmp.toFloat(&ok);

    strTmp=linelist.at(15);
    strTmp.remove(QRegExp("iSelfdefVal4="));//�Զ���4
    stru_newChainset.iSelfdefVal4= strTmp.toFloat(&ok);

    strTmp=linelist.at(16);
    strTmp.remove(QRegExp("iC1zlqgwVal="));//�ӹ�1����������
    stru_newChainset.iC1zlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(17);
    strTmp.remove(QRegExp("iC2zlqgwVal="));//�ӹ�2����������
    stru_newChainset.iC2zlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(18);
    strTmp.remove(QRegExp("iC3zlqgwVal="));//�ӹ�3����������
    stru_newChainset.iC3zlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(19);
    strTmp.remove(QRegExp("iC4zlqgwVal="));//�ӹ�4����������
    stru_newChainset.iC4zlqgwVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(20);
    strTmp.remove(QRegExp("iC1cwbhVal="));//�ӹ�1���󱣻�
    stru_newChainset.iC1cwbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(21);
    strTmp.remove(QRegExp("iC2cwbhVal="));//�ӹ�2���󱣻�
    stru_newChainset.iC2cwbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(22);
    strTmp.remove(QRegExp("iC3cwbhVal="));//�ӹ�3���󱣻�
    stru_newChainset.iC3cwbhVal= strTmp.toFloat(&ok);

    strTmp=linelist.at(23);
    strTmp.remove(QRegExp("iC4cwbhVal="));//�ӹ�4���󱣻�
    stru_newChainset.iC4cwbhVal= strTmp.toFloat(&ok);

//  �����л��������ļ���add by 2020.11.24

    strTmp=linelist.at(24);
    strTmp.remove(QRegExp("isw_Jjtj="));//����ͣ��
    stru_newChainset.isw_Jjtj= strTmp.toFloat(&ok);

    strTmp=linelist.at(25);
    strTmp.remove(QRegExp("isw_SJiti="));//S����ͣ��
    stru_newChainset.isw_SJiti= strTmp.toFloat(&ok);

    strTmp=linelist.at(26);
    strTmp.remove(QRegExp("isw_Xtlq="));//ϵͳ��ȴ�����л�
    stru_newChainset.isw_Xtlq= strTmp.toFloat(&ok);

    strTmp=linelist.at(27);
    strTmp.remove(QRegExp("isw_Zdtgw="));//��̨���´����л�
    stru_newChainset.isw_Zdtgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(28);
    strTmp.remove(QRegExp("isw_Zdtgwy="));//��̨��λ�ƴ����л�
    stru_newChainset.isw_Zdtgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(29);
    strTmp.remove(QRegExp("isw_Htgwy="));//��̨��λ�ƴ����л�
    stru_newChainset.isw_Htgwy= strTmp.toFloat(&ok);

    strTmp=linelist.at(30);
    strTmp.remove(QRegExp("isw_Htqy="));//��̨Ƿѹ�����л�
    stru_newChainset.isw_Htqy= strTmp.toFloat(&ok);

    strTmp=linelist.at(31);
    strTmp.remove(QRegExp("isw_Htqyw="));//��̨ǷҺλ�����л�
    stru_newChainset.isw_Htqyw= strTmp.toFloat(&ok);

    strTmp=linelist.at(32);
    strTmp.remove(QRegExp("isw_Htgw="));//��̨���´����л�
    stru_newChainset.isw_Htgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(33);
    strTmp.remove(QRegExp("isw_Gfrjbh="));//�����ȼ̱��������л�
    stru_newChainset.isw_Gfrjbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(34);
    strTmp.remove(QRegExp("isw_Jyzcdy="));//��ѹ��е�ѹ�����л�
    stru_newChainset.isw_Jyzcdy= strTmp.toFloat(&ok);

    strTmp=linelist.at(35);
    strTmp.remove(QRegExp("isw_Zgmbh="));//�����ű��������л�
    stru_newChainset.isw_Zgmbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(36);
    strTmp.remove(QRegExp("isw_Selfdef1="));//�Զ���1�����л�
    stru_newChainset.isw_Selfdef1= strTmp.toFloat(&ok);

    strTmp=linelist.at(37);
    strTmp.remove(QRegExp("isw_Selfdef2="));//�Զ���2�����л�
    stru_newChainset.isw_Selfdef2= strTmp.toFloat(&ok);

    strTmp=linelist.at(38);
    strTmp.remove(QRegExp("isw_Selfdef3="));//�Զ���3�����л�
    stru_newChainset.isw_Selfdef3= strTmp.toFloat(&ok);

    strTmp=linelist.at(39);
    strTmp.remove(QRegExp("isw_Selfdef4="));//�Զ���4�����л�
    stru_newChainset.isw_Selfdef4= strTmp.toFloat(&ok);

    strTmp=linelist.at(40);
    strTmp.remove(QRegExp("isw_C1zlqgw="));//�ӹ�1���������´����л�
    stru_newChainset.isw_C1zlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(41);
    strTmp.remove(QRegExp("isw_C2zlqgw="));//�ӹ�2���������´����л�
    stru_newChainset.isw_C2zlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(42);
    strTmp.remove(QRegExp("isw_C3zlqgw="));//�ӹ�3���������´����л�
    stru_newChainset.isw_C3zlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(43);
    strTmp.remove(QRegExp("isw_C4zlqgw="));//�ӹ�4���������´����л�
    stru_newChainset.isw_C4zlqgw= strTmp.toFloat(&ok);

    strTmp=linelist.at(44);
    strTmp.remove(QRegExp("isw_C1cwbh="));//�ӹ�1���󱣻������л�
    stru_newChainset.isw_C1cwbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(45);
    strTmp.remove(QRegExp("isw_C2cwbh="));//�ӹ�2���󱣻������л�
    stru_newChainset.isw_C2cwbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(46);
    strTmp.remove(QRegExp("isw_C3cwbh="));//�ӹ�3���󱣻������л�
    stru_newChainset.isw_C3cwbh= strTmp.toFloat(&ok);

    strTmp=linelist.at(47);
    strTmp.remove(QRegExp("isw_C4cwbh="));//�ӹ�4���󱣻������л�
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
    strHeader="iJjtjVal=";     //����ͣ��
    strText=strHeader+QString::number(stru_newChainset.iJjtjVal,10);
    linelist.append(strText);

    strHeader="iSJitiVal=";     //S����ͣ��
    strText=strHeader+QString::number(stru_newChainset.iSJitiVal,10);
    linelist.append(strText);

    strHeader="iXtlqVal=";     //ϵͳ��ȴ
    strText=strHeader+QString::number(stru_newChainset.iXtlqVal,10);
    linelist.append(strText);

    strHeader="iZdtgwVal=";     //��̨����
    strText=strHeader+QString::number(stru_newChainset.iZdtgwVal,10);
    linelist.append(strText);

    strHeader="iZdtgwyVal=";     //��̨��λ��
    strText=strHeader+QString::number(stru_newChainset.iZdtgwyVal,10);
    linelist.append(strText);

    strHeader="iHtgwyVal=";     //��̨��λ��
    strText=strHeader+QString::number(stru_newChainset.iHtgwyVal,10);
    linelist.append(strText);

    strHeader="iHtqyVal=";     //��̨Ƿѹ
    strText=strHeader+QString::number(stru_newChainset.iHtqyVal,10);
    linelist.append(strText);

    strHeader="iHtqywVal=";     //��̨ǷҺλ
    strText=strHeader+QString::number(stru_newChainset.iHtqywVal,10);
    linelist.append(strText);

    strHeader="iHtgwVal=";     //��̨����
    strText=strHeader+QString::number(stru_newChainset.iHtgwVal,10);
    linelist.append(strText);

    strHeader="iGfrjbhVal=";     //�����ȼ̱���
    strText=strHeader+QString::number(stru_newChainset.iGfrjbhVal,10);
    linelist.append(strText);

    strHeader="iJyzcdyVal=";     //��ѹ��е�ѹ
    strText=strHeader+QString::number(stru_newChainset.iJyzcdyVal,10);
    linelist.append(strText);

    strHeader="iZgmbhVal=";     //�����ű���
    strText=strHeader+QString::number(stru_newChainset.iZgmbhVal,10);
    linelist.append(strText);

    strHeader="iSelfdefVal1=";     //�Զ���1
    strText=strHeader+QString::number(stru_newChainset.iSelfdefVal1,10);
    linelist.append(strText);

    strHeader="iSelfdefVal2=";     //�Զ���2
    strText=strHeader+QString::number(stru_newChainset.iSelfdefVal2,10);
    linelist.append(strText);

    strHeader="iSelfdefVal3=";     //�Զ���3
    strText=strHeader+QString::number(stru_newChainset.iSelfdefVal3,10);
    linelist.append(strText);

    strHeader="iSelfdefVal4=";     //�Զ���4
    strText=strHeader+QString::number(stru_newChainset.iSelfdefVal4,10);
    linelist.append(strText);

    strHeader="iC1zlqgwVal=";     //�ӹ�1����������
    strText=strHeader+QString::number(stru_newChainset.iC1zlqgwVal,10);
    linelist.append(strText);

    strHeader="iC2zlqgwVal=";     //�ӹ�2����������
    strText=strHeader+QString::number(stru_newChainset.iC2zlqgwVal,10);
    linelist.append(strText);

    strHeader="iC3zlqgwVal=";     //�ӹ�3����������
    strText=strHeader+QString::number(stru_newChainset.iC3zlqgwVal,10);
    linelist.append(strText);

    strHeader="iC4zlqgwVal=";     //�ӹ�4����������
    strText=strHeader+QString::number(stru_newChainset.iC4zlqgwVal,10);
    linelist.append(strText);

    strHeader="iC1cwbhVal=";     //�ӹ�1���󱣻�
    strText=strHeader+QString::number(stru_newChainset.iC1cwbhVal,10);
    linelist.append(strText);

    strHeader="iC2cwbhVal=";     //�ӹ�2���󱣻�
    strText=strHeader+QString::number(stru_newChainset.iC2cwbhVal,10);
    linelist.append(strText);

    strHeader="iC3cwbhVal=";     //�ӹ�3���󱣻�
    strText=strHeader+QString::number(stru_newChainset.iC3cwbhVal,10);
    linelist.append(strText);

    strHeader="iC4cwbhVal=";     //�ӹ�4���󱣻�
    strText=strHeader+QString::number(stru_newChainset.iC4cwbhVal,10);
    linelist.append(strText);

//  �����л�д�����ļ���add by 2020.11.24
    strHeader="isw_Jjtj=";     //����ͣ��
    strText=strHeader+QString::number(stru_newChainset.isw_Jjtj,10);
    linelist.append(strText);

    strHeader="isw_SJiti=";     //S����ͣ��
    strText=strHeader+QString::number(stru_newChainset.isw_SJiti,10);
    linelist.append(strText);

    strHeader="isw_Xtlq=";     //ϵͳ��ȴ
    strText=strHeader+QString::number(stru_newChainset.isw_Xtlq,10);
    linelist.append(strText);

    strHeader="isw_Zdtgw=";     //��̨����
    strText=strHeader+QString::number(stru_newChainset.isw_Zdtgw,10);
    linelist.append(strText);

    strHeader="isw_Zdtgwy=";     //��̨��λ��
    strText=strHeader+QString::number(stru_newChainset.isw_Zdtgwy,10);
    linelist.append(strText);

    strHeader="isw_Htgwy=";     //��̨��λ��
    strText=strHeader+QString::number(stru_newChainset.isw_Htgwy,10);
    linelist.append(strText);

    strHeader="isw_Htqy=";     //��̨Ƿѹ
    strText=strHeader+QString::number(stru_newChainset.isw_Htqy,10);
    linelist.append(strText);

    strHeader="isw_Htqyw=";     //��̨ǷҺλ
    strText=strHeader+QString::number(stru_newChainset.isw_Htqyw,10);
    linelist.append(strText);

    strHeader="isw_Htgw=";     //��̨����
    strText=strHeader+QString::number(stru_newChainset.isw_Htgw,10);
    linelist.append(strText);

    strHeader="isw_Gfrjbh=";     //�����ȼ̱���
    strText=strHeader+QString::number(stru_newChainset.isw_Gfrjbh,10);
    linelist.append(strText);

    strHeader="isw_Jyzcdy=";     //��ѹ��е�ѹ
    strText=strHeader+QString::number(stru_newChainset.isw_Jyzcdy,10);
    linelist.append(strText);

    strHeader="isw_Zgmbh=";     //�����ű���
    strText=strHeader+QString::number(stru_newChainset.isw_Zgmbh,10);
    linelist.append(strText);

    strHeader="isw_Selfdef1=";     //�Զ���1
    strText=strHeader+QString::number(stru_newChainset.isw_Selfdef1,10);
    linelist.append(strText);

    strHeader="isw_Selfdef2=";     //�Զ���2
    strText=strHeader+QString::number(stru_newChainset.isw_Selfdef2,10);
    linelist.append(strText);

    strHeader="isw_Selfdef3=";     //�Զ���3
    strText=strHeader+QString::number(stru_newChainset.isw_Selfdef3,10);
    linelist.append(strText);

    strHeader="isw_Selfdef4=";     //�Զ���4
    strText=strHeader+QString::number(stru_newChainset.isw_Selfdef4,10);
    linelist.append(strText);

    strHeader="isw_C1zlqgw=";     //�ӹ�1����������
    strText=strHeader+QString::number(stru_newChainset.isw_C1zlqgw,10);
    linelist.append(strText);

    strHeader="isw_C2zlqgw=";     //�ӹ�2����������
    strText=strHeader+QString::number(stru_newChainset.isw_C2zlqgw,10);
    linelist.append(strText);

    strHeader="isw_C3zlqgw=";     //�ӹ�3����������
    strText=strHeader+QString::number(stru_newChainset.isw_C3zlqgw,10);
    linelist.append(strText);

    strHeader="isw_C4zlqgw=";     //�ӹ�4����������
    strText=strHeader+QString::number(stru_newChainset.isw_C4zlqgw,10);
    linelist.append(strText);

    strHeader="isw_C1cwbh=";     //�ӹ�1���󱣻�
    strText=strHeader+QString::number(stru_newChainset.isw_C1cwbh,10);
    linelist.append(strText);

    strHeader="isw_C2cwbh=";     //�ӹ�2���󱣻�
    strText=strHeader+QString::number(stru_newChainset.isw_C2cwbh,10);
    linelist.append(strText);

    strHeader="isw_C3cwbh=";     //�ӹ�3���󱣻�
    strText=strHeader+QString::number(stru_newChainset.isw_C3cwbh,10);
    linelist.append(strText);

    strHeader="isw_C4cwbh=";     //�ӹ�4���󱣻�
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





