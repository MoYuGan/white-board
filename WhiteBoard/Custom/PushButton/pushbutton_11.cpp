#include "pushbutton_11.h"

PushButton_11::PushButton_11(QWidget *parent) :
    QPushButton(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(208,142));
    this->setCheckable(true);
}

void PushButton_11::m_setText(QString str, QColor color, QPixmap pix)
{
    text_Str =str;
    color_Col =color;
    pixmap_Pix =pix;
    update();
}

void PushButton_11::setLocalTest(const QString& str)
{
     text_Str =str;
     update();
}

void PushButton_11::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(this->isChecked())
    {
        painter.setPen(QPen(QColor(20,134,250),Public_Function::getScaleSize(2)));
        QRect rect(QPoint(Public_Function::getScaleSize(1),Public_Function::getScaleSize(1)),Public_Function::getScaleSize(206,120));
        painter.drawRoundedRect(rect,Public_Function::getScaleSize(8),Public_Function::getScaleSize(8));
    }

    if(!pixmap_Pix.isNull())
    {
        QRect mrect(QPoint(Public_Function::getScaleSize(6),Public_Function::getScaleSize(6)),Public_Function::getScaleSize(196,110));
        painter.drawPixmap(mrect,pixmap_Pix);
    }
    else
    {
        painter.setBrush(color_Col);
        painter.setPen(Qt::NoPen);
        QRect mrect(QPoint(Public_Function::getScaleSize(6),Public_Function::getScaleSize(6)),Public_Function::getScaleSize(196,110));
        painter.drawRoundedRect(mrect,Public_Function::getScaleSize(4),Public_Function::getScaleSize(4));
    }
    painter.setFont(Public_Function::getFont(14));
    painter.setPen(QPen(QColor(68,68,68)));
    QRect rect(QPoint(0,this->height() -Public_Function::getScaleSize(16)),Public_Function::getScaleSize(208,16));
    painter.drawText(rect,Qt::AlignCenter,text_Str);
}
