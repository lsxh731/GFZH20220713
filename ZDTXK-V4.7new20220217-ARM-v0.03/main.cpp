/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: main.cpp
** 摘要: 主程序入库
**
**
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2018.11.27
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波     2018.11.27   V1.0      创建
**
****************************************************************************/
#include <QTextCodec>
#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include "mainwindow.h"
#include "md5encode.h"
#include <QWSServer>

int main(int argc, char *argv[])
{
    printf("2020-05-08-1\n");
    QApplication app(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));        //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //支持中文文件名显示
    QFont font;
    font.setPointSize(16);  //改成16，16可以在开发板显示16号字
    font.setFamily(("wenquanyi"));
    font.setBold(false);
    app.setFont(font);
    QApplication::setStyle("CleanLooks");
    CMymainWindow MymainWin;
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap("/bin/png/background.jpg")));
    MymainWin.setPalette(pal);//更新样式背景文件,add by 2020.04.04
#ifdef WIN_DEV
    MymainWin.showNormal();
#else
//	MymainWin.showMaximized();
    QWSServer::setCursorVisible(false);
    MymainWin.showFullScreen();
#endif
    return app.exec();
}
