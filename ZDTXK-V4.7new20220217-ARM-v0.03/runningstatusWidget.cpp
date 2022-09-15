/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: runningstatusWidget.cpp
** 摘要: "运行状态"子对话框
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.12.10
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2018.12.10   V1.0      创建
** 聂晓波      2019.02.11   V1.1      修改
****************************************************************************/
#include "runningstatusWidget.h"
#include <QDateTime>
extern int g_iLangChange;//add by 2019.10.3

CRunningStatusWidget::CRunningStatusWidget(QWidget *ptr)
{
    m_pUi= new Ui::runningstatusForm;
    m_pUi->setupUi(this);
    m_pWidget=ptr;
    initRunningStatus();
    connect(m_pUi->closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));//返回键 add by 2020.08.10
}
CRunningStatusWidget::~CRunningStatusWidget()
{
    QCoreApplication::postEvent(m_pWidget,new QCustomEvent(QEvent::User + 4000),0);
    printf("QCoreApplication::postEvent(m_pWidget,new QCustomEvent(QEvent::User + 4000),0)\n");
}
void CRunningStatusWidget::closeEvent(QCloseEvent *event)
{
    /*QCoreApplication::postEvent(m_pWidget,new QCustomEvent(QEvent::User + 4000),0);
    printf("closeEvent--postEvent(m_pWidget,new QCustomEvent(QEvent::User + 4000),0)\n");*/
}
//初始化运行状态表格
void CRunningStatusWidget::initRunningStatus()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    for(int k=0;k<MAX_SIZE;k++)
    {
        m_struRunStaData[k].strTime=current_date;//时间
        m_struRunStaData[k].iRestartprocFlag=-1; //重启过程中
        m_struRunStaData[k].iNormaloperFlag=-1;  //正常运行
        m_struRunStaData[k].iFaultProtFlag=-1;   //故障保护中
        m_struRunStaData[k].iFaultlockFlag=-1;   //故障闭锁
        m_struRunStaData[k].iProtectedTimes=0;   //已保护次数
        m_struRunStaData[k].iBlockpulseFlag=-1;  //封锁脉冲
        m_struRunStaData[k].iRecstartsigFlag=-1; //收到启动信号
        m_struRunStaData[k].iRecshutsigFlag=-1;  //收到关机信号
    }//for(int k=0;k<MAX_SIZE;k++)

    int nRows=m_pUi->operstatus_tableWidget->rowCount();
    int nCols=m_pUi->operstatus_tableWidget->columnCount();
    //设置表头颜色
    m_pUi->operstatus_tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:skyblue}");
    m_pUi->operstatus_tableWidget->verticalHeader()->setDefaultSectionSize(32); //设置行高
    for(int i=0;i<nRows;i++)
    {

        QLabel *yellowlabel1 = new QLabel();
        QLabel *yellowlabel2 = new QLabel();
        QLabel *yellowlabel3 = new QLabel();
        QLabel *yellowlabel4 = new QLabel();
        QLabel *yellowlabel6 = new QLabel();
        QLabel *yellowlabel7 = new QLabel();
        QLabel *yellowlabel8 = new QLabel();

        yellowlabel1->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel2->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel3->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel4->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel6->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel7->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel8->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));

        yellowlabel1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel4->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel6->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel7->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel8->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        QTableWidgetItem *pItem=new QTableWidgetItem(m_struRunStaData[i].strTime,0);
        m_pUi->operstatus_tableWidget->setItem(i,0,pItem);
        m_pUi->operstatus_tableWidget->setCellWidget(i,1,yellowlabel1);
        m_pUi->operstatus_tableWidget->setCellWidget(i,2,yellowlabel2);
        m_pUi->operstatus_tableWidget->setCellWidget(i,3,yellowlabel3);
        m_pUi->operstatus_tableWidget->setCellWidget(i,4,yellowlabel4);
        m_pUi->operstatus_tableWidget->setCellWidget(i,6,yellowlabel6);
        m_pUi->operstatus_tableWidget->setCellWidget(i,7,yellowlabel7);
        m_pUi->operstatus_tableWidget->setCellWidget(i,8,yellowlabel8);

        QTableWidgetItem *pTimesItem=new QTableWidgetItem(QString::number(m_struRunStaData[i].iProtectedTimes,10),0);
        m_pUi->operstatus_tableWidget->setItem(i,5,pTimesItem);
        m_pUi->operstatus_tableWidget->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    }//for(int i=0;i<nRows;i++)
    //设置选中背景色
    m_pUi->operstatus_tableWidget->setStyleSheet("selection-background-color:lightblue;");
    m_pUi->operstatus_tableWidget->resizeColumnsToContents();
}
//更新运行状态数据
void CRunningStatusWidget::updateRunningStatusData(STRU_RUNNINGSTATUS *pRunningStaData)
{
    int nRows=m_pUi->operstatus_tableWidget->rowCount();
    int nCols=m_pUi->operstatus_tableWidget->columnCount();
    //设置表头颜色
    m_pUi->operstatus_tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:skyblue}");
    m_pUi->operstatus_tableWidget->verticalHeader()->setDefaultSectionSize(32); //设置行高
    for(int i=0;i<nRows;i++)
    {
        QLabel *greenlabel1 = new QLabel();
        QLabel *greenlabel2 = new QLabel();
        QLabel *greenlabel3 = new QLabel();
        QLabel *greenlabel4 = new QLabel();
        QLabel *greenlabel6 = new QLabel();
        QLabel *greenlabel7 = new QLabel();
        QLabel *greenlabel8 = new QLabel();

        QLabel *redlabel1 = new QLabel();
        QLabel *redlabel2 = new QLabel();
        QLabel *redlabel3 = new QLabel();
        QLabel *redlabel4 = new QLabel();
        QLabel *redlabel6 = new QLabel();
        QLabel *redlabel7 = new QLabel();
        QLabel *redlabel8 = new QLabel();

        QLabel *yellowlabel1 = new QLabel();
        QLabel *yellowlabel2 = new QLabel();
        QLabel *yellowlabel3 = new QLabel();
        QLabel *yellowlabel4 = new QLabel();
        QLabel *yellowlabel6 = new QLabel();
        QLabel *yellowlabel7 = new QLabel();
        QLabel *yellowlabel8 = new QLabel();

        greenlabel1->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_green.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        greenlabel2->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_green.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        greenlabel3->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_green.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        greenlabel4->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_green.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        greenlabel6->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_green.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        greenlabel7->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_green.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        greenlabel8->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_green.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));

        redlabel1->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_red.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        redlabel2->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_red.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        redlabel3->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_red.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        redlabel4->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_red.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        redlabel6->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_red.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        redlabel7->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_red.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        redlabel8->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_red.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));

        yellowlabel1->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel2->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel3->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel4->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel6->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel7->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));
        yellowlabel8->setPixmap(QPixmap(QApplication::applicationDirPath()+"/"+"gct_ied_yellow.png").scaled(QSize(32,32),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation));

        greenlabel1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        greenlabel2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        greenlabel3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        greenlabel4->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        greenlabel6->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        greenlabel7->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        greenlabel8->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        redlabel1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        redlabel2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        redlabel3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        redlabel4->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        redlabel6->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        redlabel7->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        redlabel8->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        yellowlabel1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel4->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel6->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel7->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        yellowlabel8->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //更新"时间"列
        QTableWidgetItem *pItem=new QTableWidgetItem(pRunningStaData[i].strTime,0);
        m_pUi->operstatus_tableWidget->setItem(i,0,pItem);
        //更新"重启过程中"列
        updateLabelColor(pRunningStaData[i].iRestartprocFlag,i,1,greenlabel1,redlabel1,yellowlabel1);
        //更新"正常运行"列
        updateLabelColor(pRunningStaData[i].iNormaloperFlag,i,2,greenlabel2,redlabel2,yellowlabel2);
        //更新"故障保护中"列
        updateLabelColor(pRunningStaData[i].iFaultProtFlag,i,3,greenlabel3,redlabel3,yellowlabel3);
        //更新"故障闭锁"列
        updateLabelColor(pRunningStaData[i].iFaultlockFlag,i,4,greenlabel4,redlabel4,yellowlabel4);
        //更新"封锁脉冲"列
        updateLabelColor(pRunningStaData[i].iBlockpulseFlag,i,6,greenlabel6,redlabel6,yellowlabel6);
        //更新"收到启动信号"列
        updateLabelColor(pRunningStaData[i].iRecstartsigFlag,i,7,greenlabel7,redlabel7,yellowlabel7);
        //更新"收到关机信号"列
        updateLabelColor(pRunningStaData[i].iRecshutsigFlag,i,8,greenlabel8,redlabel8,yellowlabel8);
        //更新"已保护次数"列
        QTableWidgetItem *pTimesItem=new QTableWidgetItem(QString::number(pRunningStaData[i].iProtectedTimes,10),0);
        m_pUi->operstatus_tableWidget->setItem(i,5,pTimesItem);
        m_pUi->operstatus_tableWidget->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //更新"原始报文"列
        QTableWidgetItem *pOrigMsgItem=new QTableWidgetItem(pRunningStaData[i].strOrigMsg,0);
        m_pUi->operstatus_tableWidget->setItem(i,9,pOrigMsgItem);
    }//for(int i=0;i<nRows;i++)
    m_pUi->operstatus_tableWidget->resizeColumnsToContents();
}
//更新单元格Label灯颜色
void CRunningStatusWidget::updateLabelColor(int nValue,int nIndex,int nCol,QLabel *greenlabel,QLabel *redlabel,QLabel *yellowlabel)
{
       switch(nValue)
        {
        case 1:
             m_pUi->operstatus_tableWidget->setCellWidget(nIndex,nCol,redlabel);
            break;
        case 0:
             m_pUi->operstatus_tableWidget->setCellWidget(nIndex,nCol,greenlabel);
            break;
        case -1:
             m_pUi->operstatus_tableWidget->setCellWidget(nIndex,nCol,yellowlabel);
            break;
        default:
             m_pUi->operstatus_tableWidget->setCellWidget(nIndex,nCol,yellowlabel);
            break;
        }// switch(nValue)
}
void CRunningStatusWidget::runningLangChange()
{
    if(g_iLangChange==1)
    {
        setWindowTitle(QApplication::translate("runningstatusForm", "\350\277\220\350\241\214\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = m_pUi->operstatus_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("runningstatusForm", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(0,___qtablewidgetitem);
        QTableWidgetItem *___qtablewidgetitem1 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("runningstatusForm", "\351\207\215\345\220\257\350\277\207\347\250\213\344\270\255", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(1,___qtablewidgetitem1);
        QTableWidgetItem *___qtablewidgetitem2 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("runningstatusForm", "\346\255\243\345\270\270\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(2,___qtablewidgetitem2);
        QTableWidgetItem *___qtablewidgetitem3 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("runningstatusForm", "\346\225\205\351\232\234\344\277\235\346\212\244\344\270\255", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(3,___qtablewidgetitem3);
        QTableWidgetItem *___qtablewidgetitem4 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("runningstatusForm", "\346\225\205\351\232\234\351\227\255\351\224\201", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(4,___qtablewidgetitem4);
        QTableWidgetItem *___qtablewidgetitem5 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("runningstatusForm", "\345\267\262\344\277\235\346\212\244\346\254\241\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(5,___qtablewidgetitem5);
        QTableWidgetItem *___qtablewidgetitem6 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("runningstatusForm", "\345\260\201\351\224\201\350\204\211\345\206\262", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(6,___qtablewidgetitem6);
        QTableWidgetItem *___qtablewidgetitem7 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("runningstatusForm", "\346\224\266\345\210\260\345\220\257\345\212\250\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(7,___qtablewidgetitem7);
        QTableWidgetItem *___qtablewidgetitem8 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("runningstatusForm", "\346\224\266\345\210\260\345\205\263\346\234\272\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(8,___qtablewidgetitem8);
        QTableWidgetItem *___qtablewidgetitem9 = m_pUi->operstatus_tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22701", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(0,___qtablewidgetitem9);
        QTableWidgetItem *___qtablewidgetitem10 = m_pUi->operstatus_tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22702", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(1,___qtablewidgetitem10);
        QTableWidgetItem *___qtablewidgetitem11 = m_pUi->operstatus_tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22703", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(2,___qtablewidgetitem11);
        QTableWidgetItem *___qtablewidgetitem12 = m_pUi->operstatus_tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22704", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(3,___qtablewidgetitem12);
        QTableWidgetItem *___qtablewidgetitem13 = m_pUi->operstatus_tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem13->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22705", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(4,___qtablewidgetitem13);
        QTableWidgetItem *___qtablewidgetitem14 = m_pUi->operstatus_tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem14->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22706", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(5,___qtablewidgetitem14);
        QTableWidgetItem *___qtablewidgetitem15 = m_pUi->operstatus_tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem15->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22707", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(6,___qtablewidgetitem15);
        QTableWidgetItem *___qtablewidgetitem16 = m_pUi->operstatus_tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem16->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22708", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(7,___qtablewidgetitem16);
        QTableWidgetItem *___qtablewidgetitem17 = m_pUi->operstatus_tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem17->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22709", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(8,___qtablewidgetitem17);
        QTableWidgetItem *___qtablewidgetitem18 = m_pUi->operstatus_tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem18->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22710", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(9,___qtablewidgetitem18);
        QTableWidgetItem *___qtablewidgetitem19 = m_pUi->operstatus_tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem19->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22711", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(10,___qtablewidgetitem19);
        QTableWidgetItem *___qtablewidgetitem20 = m_pUi->operstatus_tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem20->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22712", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(11,___qtablewidgetitem20);
        QTableWidgetItem *___qtablewidgetitem21 = m_pUi->operstatus_tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem21->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22713", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(12,___qtablewidgetitem21);
        QTableWidgetItem *___qtablewidgetitem22 = m_pUi->operstatus_tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem22->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22714", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(13,___qtablewidgetitem22);
        QTableWidgetItem *___qtablewidgetitem23 = m_pUi->operstatus_tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem23->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22715", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(14,___qtablewidgetitem23);
        QTableWidgetItem *___qtablewidgetitem24 = m_pUi->operstatus_tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem24->setText(QApplication::translate("runningstatusForm", "\346\250\241\345\235\22716", 0, QApplication::UnicodeUTF8));
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(15,___qtablewidgetitem24);
    }
    else
    {
        setWindowTitle("Running");
        QTableWidgetItem *___qtablewidgetitem = m_pUi->operstatus_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText("Time");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(0,___qtablewidgetitem);
        QTableWidgetItem *___qtablewidgetitem1 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText("Restarting");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(1,___qtablewidgetitem1);
        QTableWidgetItem *___qtablewidgetitem2 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText("Working");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(2,___qtablewidgetitem2);
        QTableWidgetItem *___qtablewidgetitem3 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText("Protect");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(3,___qtablewidgetitem3);
        QTableWidgetItem *___qtablewidgetitem4 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText("Locking");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(4,___qtablewidgetitem4);
        QTableWidgetItem *___qtablewidgetitem5 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText("Protection times");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(5,___qtablewidgetitem5);
        QTableWidgetItem *___qtablewidgetitem6 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText("Blocking pulse");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(6,___qtablewidgetitem6);
        QTableWidgetItem *___qtablewidgetitem7 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText("Receive startup signal");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(7,___qtablewidgetitem7);
        QTableWidgetItem *___qtablewidgetitem8 = m_pUi->operstatus_tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText("Receive shutdown signal");
        m_pUi->operstatus_tableWidget->setHorizontalHeaderItem(8,___qtablewidgetitem8);
        QTableWidgetItem *___qtablewidgetitem9 = m_pUi->operstatus_tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText("Module1");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(0,___qtablewidgetitem9);
        QTableWidgetItem *___qtablewidgetitem10 = m_pUi->operstatus_tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem10->setText("Module2");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(1,___qtablewidgetitem10);
        QTableWidgetItem *___qtablewidgetitem11 = m_pUi->operstatus_tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem11->setText("Module3");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(2,___qtablewidgetitem11);
        QTableWidgetItem *___qtablewidgetitem12 = m_pUi->operstatus_tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem12->setText("Module4");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(3,___qtablewidgetitem12);
        QTableWidgetItem *___qtablewidgetitem13 = m_pUi->operstatus_tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem13->setText("Module5");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(4,___qtablewidgetitem13);
        QTableWidgetItem *___qtablewidgetitem14 = m_pUi->operstatus_tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem14->setText("Module6");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(5,___qtablewidgetitem14);
        QTableWidgetItem *___qtablewidgetitem15 = m_pUi->operstatus_tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem15->setText("Module7");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(6,___qtablewidgetitem15);
        QTableWidgetItem *___qtablewidgetitem16 = m_pUi->operstatus_tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem16->setText("Module8");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(7,___qtablewidgetitem16);
        QTableWidgetItem *___qtablewidgetitem17 = m_pUi->operstatus_tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem17->setText("Module9");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(8,___qtablewidgetitem17);
        QTableWidgetItem *___qtablewidgetitem18 = m_pUi->operstatus_tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem18->setText("Module10");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(9,___qtablewidgetitem18);
        QTableWidgetItem *___qtablewidgetitem19 = m_pUi->operstatus_tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem19->setText("Module11");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(10,___qtablewidgetitem19);
        QTableWidgetItem *___qtablewidgetitem20 = m_pUi->operstatus_tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem20->setText("Module12");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(11,___qtablewidgetitem20);
        QTableWidgetItem *___qtablewidgetitem21 = m_pUi->operstatus_tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem21->setText("Module13");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(12,___qtablewidgetitem21);
        QTableWidgetItem *___qtablewidgetitem22 = m_pUi->operstatus_tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem22->setText("Module14");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(13,___qtablewidgetitem22);
        QTableWidgetItem *___qtablewidgetitem23 = m_pUi->operstatus_tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem23->setText("Module15");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(14,___qtablewidgetitem23);
        QTableWidgetItem *___qtablewidgetitem24 = m_pUi->operstatus_tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem24->setText("Module16");
        m_pUi->operstatus_tableWidget->setVerticalHeaderItem(15,___qtablewidgetitem24);
    }
}
/*返回槽函数实现部分 2020.08.10*/
void CRunningStatusWidget::closeBtn_clicked()
{
    this->close();
}
