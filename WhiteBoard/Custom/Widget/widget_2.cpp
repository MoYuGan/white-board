#include "widget_2.h"
#include <QString>
#include <QDebug>
#include "Public/public_function.h"
Widget_2::Widget_2(QString text, QWidget *parent):str(text),QWidget(parent)
{

    this->setWindowFlag(Qt::FramelessWindowHint,true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    int w =fontMetrics().horizontalAdvance(str);
    int w2 =fontMetrics().lineSpacing();
    if(w +w2 <116)this->setFixedSize(Public_Function::getScaleSize(164,58));
    else if(w +w2 <180)this->setFixedSize(Public_Function::getScaleSize(308,58));
    else this->setFixedSize(Public_Function::getScaleSize(308,84));

    QTimer *timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        timer->stop();
        this->close();
    });
    timer->start(2000);
}

Widget_2::~Widget_2()
{
}

void Widget_2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(this->rect(),Public_Function::getScaleSize(8),Public_Function::getScaleSize(8));
    painter.setPen(QPen(QColor(68,68,68)));
    painter.setFont(Public_Function::getFont(18));
    QTextOption toption(Qt::AlignCenter);
    toption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    painter.drawText(QRect(Public_Function::getScaleSize(28),Public_Function::getScaleSize(20),this->width() -Public_Function::getScaleSize(56),
                           this->height() -Public_Function::getScaleSize(40)),str,toption);

}
