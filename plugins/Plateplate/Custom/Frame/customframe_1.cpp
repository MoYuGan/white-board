#include "customframe_1.h"

CustomFrame_1::CustomFrame_1(QWidget *parent, Qt::WindowFlags f) :
    QFrame(parent, f)
{
    m_pRadiusTopLeft = 0;
    m_pRadiusTopRight = 0;
    m_pRadiusBottomLeft = 0;
    m_pRadiusBottomRight = 0;
}

void CustomFrame_1::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QBrush(Qt::transparent));

    QColor color(135, 135, 135);
    int border = 6;
    int radius = PublicFunction::getScaleSize(12);
    for(int i = 0; i < border; i++)
    {
        QRect rect = QRect(QPoint(border - i, border - i), QPoint(this->width() - border - i, this->height() - border - i));

        QPainterPath path;
        path = PublicFunction::getRoundRectPath(rect, radius, radius, radius, radius);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }

        switch(i)
        {
        case 0:
            color.setAlpha(80);
            break;
        case 1:
            color.setAlpha(50);
            break;
        case 2:
            color.setAlpha(20);
            break;
        case 3:
            color.setAlpha(15);
            break;
        case 4:
            color.setAlpha(10);
            break;
        case 5:
            color.setAlpha(7);
            break;
        default:
            break;
        }
        QPen pen;
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}
