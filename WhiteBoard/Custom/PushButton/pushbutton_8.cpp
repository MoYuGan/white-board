#include "pushbutton_8.h"
#include "Public/public_function.h"
PushButton_8::PushButton_8(QWidget *parent) : QPushButton(parent)
{
    this->setCheckable(true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}

void PushButton_8::msetTextAndPixmap(QString str, QPixmap pix)
{
    m_text =str;
    m_icon =pix;
    update();
}

void PushButton_8::mSetRoundSize(const QSize size)
{
    this->setFixedSize(size);
}

void PushButton_8::paintEvent(QPaintEvent *event)
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

    painter.drawPixmap(Public_Function::getScaleSize(24),Public_Function::getScaleSize(3),Public_Function::getScaleSize(50),Public_Function::getScaleSize(50),m_icon);
    QRect rect =QRect(Public_Function::getScaleSize(29),Public_Function::getScaleSize(57),Public_Function::getScaleSize(42),Public_Function::getScaleSize(12));
    painter.setPen(QPen(QColor(68,68,68)));
    painter.setFont(Public_Function::getFont(12));
    painter.drawText(rect, Qt::AlignCenter, m_text);
}

void PushButton_8::enterEvent(QEvent *event)
{
    m_isout =false;
}

void PushButton_8::leaveEvent(QEvent *event)
{
    m_isout =true;
}
