#include "frame_1.h"
#include <QtDebug>
#include <QEvent>

Frame_1::Frame_1(QWidget *parent, Qt::WindowFlags f) :
    QFrame(parent, f)
{
    m_pBorder = 0;
    m_pLeftMargin = 0;
    m_pTopMargin = 0;
    m_pRightMargin = 0;
    m_pBottomMargin = 0;
    m_pRadiusTopLeft = 0;
    m_pRadiusTopRight = 0;
    m_pRadiusBottomLeft = 0;
    m_pRadiusBottomRight = 0;
}

void Frame_1::show()
{
    QFrame::show();
    this->raise();
    emit this->frameShow();
}

void Frame_1::hide()
{
    QFrame::hide();
    emit this->frameHide();
}

void Frame_1::mSetBorder(int border)
{
    m_pBorder = border;
}

void Frame_1::mSetBackgroudColor(const QColor &color)
{
    m_pBackgroundColor = color;
}

void Frame_1::mSetBordRadius(int topLeft, int topRight, int bottomLeft, int bottomRight)
{
    m_pRadiusTopLeft = topLeft;
    m_pRadiusTopRight = topRight;
    m_pRadiusBottomLeft = bottomLeft;
    m_pRadiusBottomRight = bottomRight;
}

void Frame_1::mSetMargin(int left, int top, int right, int bottom)
{
    m_pLeftMargin = left;
    m_pTopMargin = top;
    m_pRightMargin = right;
    m_pBottomMargin = bottom;
}

void Frame_1::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QBrush(Qt::transparent));

    QColor color(135, 135, 135);
    int border = m_pBorder;
    int j;
    int i = 0;
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    do {
        path -= path;
        j = border - i;

        QPoint topLeft_p1 = QPoint(j + m_pLeftMargin, j + m_pTopMargin + m_pRadiusTopLeft);
        QPoint topLeft_p2 = QPoint(j + m_pLeftMargin + m_pRadiusTopLeft, j + m_pTopMargin);
        QPoint topRight_p1 = QPoint(this->width() - j - m_pRightMargin - m_pRadiusTopRight, topLeft_p2.y());
        QPoint topRight_p2 = QPoint(this->width() - j - m_pRightMargin, j + m_pTopMargin + m_pRadiusTopRight);
        QPoint BottomRight_p1 = QPoint(topRight_p2.x(), this->height() - j - m_pBottomMargin - m_pRadiusBottomRight);
        QPoint BottomRight_p2 = QPoint(this->width() - j - m_pRightMargin - m_pRadiusBottomRight,  this->height() - j - m_pBottomMargin);
        QPoint BottomLeft_p1 = QPoint(j + m_pLeftMargin + m_pRadiusBottomLeft, BottomRight_p2.y());
        QPoint BottomLeft_p2 = QPoint(topLeft_p1.x(),  this->height() - j - m_pBottomMargin - m_pRadiusBottomLeft);
        path.moveTo(topLeft_p1);
        path.cubicTo(topLeft_p1, QPoint(j + m_pLeftMargin, j + m_pTopMargin), topLeft_p2);
        path.lineTo(topRight_p1);
        path.cubicTo(topRight_p1, QPoint(this->width() - j - m_pRightMargin, j + m_pTopMargin), topRight_p2);
        path.lineTo(BottomRight_p1);
        path.cubicTo(BottomRight_p1, QPoint(this->width() - j - m_pRightMargin, this->height() - j - m_pBottomMargin), BottomRight_p2);
        path.lineTo(BottomLeft_p1);
        path.cubicTo(BottomLeft_p1, QPoint(j + m_pLeftMargin , this->height() - j - m_pBottomMargin),  BottomLeft_p2);
        path.lineTo(topLeft_p1);


        switch(i)
        {
        case 0:
            color.setAlpha(80);
            break;
        case 1:
            color.setAlpha(0);
            break;
        case 2:
            color.setAlpha(0);
            break;
        case 3:
            color.setAlpha(0);
            break;
        case 4:
            color.setAlpha(0);
            break;
        case 5:
            color.setAlpha(0);
            break;
        default:
            break;
        }

        QPen pen;
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        if (i == 0 && m_pBackgroundColor.isValid()) {
            painter.setBrush(QBrush(m_pBackgroundColor));
        }else {
            painter.setBrush(QBrush());
        }
        painter.drawPath(path);
        i++;
    }while(i < border);
}
