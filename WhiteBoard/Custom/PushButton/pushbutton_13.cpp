#include "pushbutton_13.h"

PushButton_13::PushButton_13(QWidget *parent)
    : QPushButton{parent}
{
    this->setFixedSize(Public_Function::getScaleSize(44,24));
    connect(this,&PushButton_13::clicked,this,[=](){
        if(open)open =false;
        else open =true;
        update();
    });
}

bool PushButton_13::isOpen()
{
 return open;
}

void PushButton_13::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(open)painter.drawPixmap(this->rect(),QPixmap(":/images/main/menu/xuanzhong-1@2x.png"));
    else painter.drawPixmap(this->rect(),QPixmap(":/images/main/menu/weixuanzhong@2x.png"));
}
