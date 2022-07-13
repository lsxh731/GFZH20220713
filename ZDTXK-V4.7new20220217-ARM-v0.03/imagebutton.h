#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H


#include <QWidget>
#include <QtGui>
#include <QPushButton>

class ImageButton : public QPushButton          //按钮类
{
    Q_OBJECT
public:
    explicit ImageButton(int x,int y,int width,int height,QString content="",QWidget *parent = 0);
    void setImages(QString normalName, QString horverName, QString pressName);
    void SetType(int type);
    int GetType();
    QString GetImage();
    void setPosAndSize(int x,int y,int width,int height);       //设置按钮的位置和大小
    void setIsPaly(bool isPlay);           //是否为图片轮播
    int ImageBtn_x;
    int ImageBtn_y;
    int ImageBtn_width;
    int ImageBtn_height;
protected:
    virtual void enterEvent(QEvent *);      //鼠标靠近事件
    virtual void leaveEvent(QEvent *);      //鼠标离开事件
    virtual void mousePressEvent(QMouseEvent *event);       //鼠标单击事件
    virtual void mouseReleaseEvent(QMouseEvent *event);     //鼠标放开事件
    virtual void paintEvent(QPaintEvent *);         //重绘事件
    void mouseMoveEvent(QMouseEvent *e){}           //鼠标移动事件
private:
    typedef enum {              //枚举类型,用于鼠标靠近点击判断
        ST_INIT, ST_NORMAL, ST_HOVER, ST_PRESS, ST_COUNT
    } Status;
    Status curStatus_;
    QString imageName_[ST_COUNT];
    QString Btn_Content;
    bool enterevent;
    int type;
    bool isPlay;

};

#endif // IMAGEBUTTON_H
