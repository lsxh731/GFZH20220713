#include "mylineedit.h"

mylineedit::mylineedit(QWidget *parent) :
    QLineEdit(parent)
{

}
//��дmousePressEvent�¼�,����¼������ǲ��ǵ����������
void mylineedit::mousePressEvent(QMouseEvent *event)
{
    //��������˾ʹ���clicked�ź�
    if (event->button() == Qt::LeftButton)
    {
        //����clicked�ź�
        emit clicked();
    }
    //�����¼��������ദ��
    QLineEdit::mousePressEvent(event);
}