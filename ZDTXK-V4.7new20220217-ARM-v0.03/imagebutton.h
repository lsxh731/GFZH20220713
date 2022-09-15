#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H


#include <QWidget>
#include <QtGui>
#include <QPushButton>

class ImageButton : public QPushButton          //��ť��
{
    Q_OBJECT
public:
    explicit ImageButton(int x,int y,int width,int height,QString content="",QWidget *parent = 0);
    void setImages(QString normalName, QString horverName, QString pressName);
    void SetType(int type);
    int GetType();
    QString GetImage();
    void setPosAndSize(int x,int y,int width,int height);       //���ð�ť��λ�úʹ�С
    void setIsPaly(bool isPlay);           //�Ƿ�ΪͼƬ�ֲ�
    int ImageBtn_x;
    int ImageBtn_y;
    int ImageBtn_width;
    int ImageBtn_height;
protected:
    virtual void enterEvent(QEvent *);      //��꿿���¼�
    virtual void leaveEvent(QEvent *);      //����뿪�¼�
    virtual void mousePressEvent(QMouseEvent *event);       //��굥���¼�
    virtual void mouseReleaseEvent(QMouseEvent *event);     //���ſ��¼�
    virtual void paintEvent(QPaintEvent *);         //�ػ��¼�
    void mouseMoveEvent(QMouseEvent *e){}           //����ƶ��¼�
private:
    typedef enum {              //ö������,������꿿������ж�
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
