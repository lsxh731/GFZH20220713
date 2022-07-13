#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>
#include <QMouseEvent>

class mylineedit: public QLineEdit
{
    Q_OBJECT
public:
   mylineedit();

    explicit mylineedit(QWidget *parent = 0);
protected:
    //��дmousePressEvent�¼�
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    //�Զ���clicked()�ź�,��mousePressEvent�¼�����ʱ����
    void clicked();

public slots:
};

#endif // MYLINEEDIT_H