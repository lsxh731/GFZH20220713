#include "imagebutton.h"


ImageButton::ImageButton(int x,int y,int width,int height,QString content,QWidget *parent)
    : QPushButton(parent)
    , curStatus_(ST_INIT)
    , Btn_Content(content)
    , ImageBtn_x(x)
    , ImageBtn_y(y)
    , ImageBtn_width(width)
    , ImageBtn_height(height)
    , enterevent(false)
    ,isPlay(false)
{
    this->setGeometry(x,y,width,height);
}

void ImageButton::setImages(QString normalName, QString horverName, QString pressName)
{
    curStatus_ = ST_NORMAL;
    imageName_[ST_NORMAL] = normalName;
    imageName_[ST_HOVER] = horverName;
    imageName_[ST_PRESS] = pressName;
}

void ImageButton::enterEvent(QEvent *)
{
    this->setGeometry(ImageBtn_x-5,ImageBtn_y-5,ImageBtn_width+10,ImageBtn_height+10);
    if (curStatus_ == ST_INIT) {
        return;
    }
    enterevent = true;
    curStatus_ = ST_HOVER;
    update();
    //MusicPlay::timemusic->music_play();
    QPixmap cursorPix("./image/mouse2.png");
    this->setCursor(cursorPix);
    if(isPlay)
    {
        //emit clicked();
    }
}

void ImageButton::leaveEvent(QEvent *)
{
    this->setGeometry(ImageBtn_x,ImageBtn_y,ImageBtn_width,ImageBtn_height);
    if (curStatus_ == ST_INIT) {
        return;
    }
    enterevent = false;
    curStatus_ = ST_NORMAL;
    update();
}

void ImageButton::mousePressEvent(QMouseEvent *event)
{
    //MusicPlay::btnmusic->music_play();
    if (curStatus_ == ST_INIT) {
        return;
    }

    if (event->button() == Qt::LeftButton) {
        curStatus_ = ST_PRESS;
        update();
    }
}

void ImageButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (curStatus_ != ST_INIT) {
            curStatus_ = ST_HOVER;
            update();
        }
        // 鼠标在弹起的时候光标在按钮上才激发clicked信号
        if (rect().contains(event->pos())) {
            emit clicked();
        }
    }
}

void ImageButton::paintEvent(QPaintEvent *event)
{
    if (curStatus_ == ST_INIT) {
        QPushButton::paintEvent(event);
        return;
    }

    QPainter painter(this);
    QPixmap pixmap(imageName_[curStatus_]);
    painter.drawPixmap(rect(), pixmap);
    painter.drawText(this->rect(),Qt::AlignCenter,Btn_Content);
    QPalette pal;
    if(enterevent)
        pal.setColor(QPalette::ButtonText,QColor(255,0,0));
    else
        pal.setColor(QPalette::ButtonText,QColor(0,0,255));
    this->setPalette(pal);
}

QString ImageButton::GetImage()
{
    return imageName_[ST_NORMAL];
}

void ImageButton::SetType(int type)
{
    this->type=type;
}

int ImageButton::GetType()
{
    return this->type;
}

void ImageButton::setPosAndSize(int x, int y, int width, int height)
{
    this->ImageBtn_x = x;
    this->ImageBtn_y = y;
    this->ImageBtn_width = width;
    this->ImageBtn_height = height;
    this->setGeometry(x,y,width,height);
}

void ImageButton::setIsPaly(bool isPlay)
{
    this->isPlay = isPlay;
}
