#include "pushbutton_10.h"

PushButton_10::PushButton_10(QWidget *parent) :
    QPushButton(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(100,48));
    this->setCheckable(true);
}

void PushButton_10::m_setText(QString str)
{
    text_Str =str;
    update();
}

void PushButton_10::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    if(this->isChecked())painter.setBrush(Qt::white);
    else painter.setBrush(QColor(238,238,238));
    painter.drawRect(this->rect());
    painter.setFont(Public_Function::getFont(14));
    painter.setPen(QPen(QColor(68,68,68)));
    painter.drawText(this->rect(),Qt::AlignCenter,text_Str);
}
