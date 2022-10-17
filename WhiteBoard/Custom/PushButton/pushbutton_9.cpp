#include "pushbutton_9.h"
#include "Public/public_function.h"
#include <math.h>
#include <QDebug>

PushButton_9::PushButton_9(QWidget *parent) : QPushButton(parent)
{
    this->setCheckable(true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}


void PushButton_9::msetShape(int num)
{
    m_lineshape =num;
}

void PushButton_9::mSetRoundSize(const QSize size)
{
    this->setFixedSize(size);
}

void PushButton_9::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    painter.setRenderHint(QPainter::Antialiasing,true);
    path.addPath(Public_Function::getRoundRectPath(this->rect(),Public_Function::getScaleSize(10)));
    if(this->isChecked())
    {
       painter.setPen(QPen(QColor(20,134,250),Public_Function::getScaleSize(2)));
       painter.setBrush(Qt::white);
       painter.drawPath(path);
    }
    else if(!m_isout)
    {
       painter.setPen(Qt::NoPen);
       painter.setBrush(QColor(238,238,238));
       painter.drawPath(path);
    }
    if(m_lineshape ==0)painter.setPen(QPen(QColor(136,136,136),Public_Function::getScaleSize(2),Qt::SolidLine,Qt::SquareCap));
    else if(m_lineshape ==1)painter.setPen(QPen(QColor(136,136,136),Public_Function::getScaleSize(2),Qt::DotLine,Qt::SquareCap));
    else if(m_lineshape ==2)painter.setPen(QPen(QColor(136,136,136),Public_Function::getScaleSize(2),Qt::DashLine,Qt::SquareCap));
    painter.drawLine(QPoint(Public_Function::getScaleSize(8),Public_Function::getScaleSize(18)),QPoint(Public_Function::getScaleSize(46),Public_Function::getScaleSize(18)));
}

void PushButton_9::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_isout =false;
}

void PushButton_9::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_isout =true;
}

