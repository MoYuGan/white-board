#include "label_1.h"
#include "Public/public_function.h"
#include <QDebug>

Label_1::Label_1(QWidget *parent)
    : QLabel{parent}
{
    this->setFixedSize(Public_Function::getScaleSize(130,100));
    timer =new QTimer(this);
    pixmap =QPixmap(":/images/load/jiazai_1.png");
    connect(timer,&QTimer::timeout,this,[=](){
        number++;
        pixmap =QPixmap(QString(":/images/load/jiazai_%1.png").arg(number));
        pixmap =pixmap.scaled(Public_Function::getScaleSize(130,80),Qt::IgnoreAspectRatio);
        if(number >95)
        {
            number =1;
        }
        update();
    });
}

void Label_1::show()
{
    number =1;
    timer->start(41);
    QLabel::show();
}

void Label_1::hide()
{
    timer->stop();
    QLabel::hide();
}


void Label_1::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawPixmap(QPoint(0,0),pixmap);
    painter.setPen(QPen(Qt::white));
    painter.drawText(QRect(0,this->height() -Public_Function::getScaleSize(15),this->width(),
                           Public_Function::getScaleSize(15)),Qt::AlignCenter,"正在检测记忆黑板");
}
