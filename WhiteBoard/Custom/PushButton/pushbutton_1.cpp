#include "pushbutton_1.h"

PushButton_1::PushButton_1(QWidget *parent) :
    PushButton_Basic(parent)
{
    m_pMouseEnter = false;
    this->setCheckable(true);
}

void PushButton_1::mSetIconColor(const QColor &color)
{
    m_pIconColor = color;
}

void PushButton_1::mSetIconSize(const QSize &size)
{
    m_pIconSize = size;
}

bool PushButton_1::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        m_pMouseEnter = true;
        update();
    }else if (event->type() == QEvent::Leave) {
        m_pMouseEnter = false;
        update();
    }
    return PushButton_Basic::eventFilter(watched, event);
}

void PushButton_1::setPixmap(QPixmap pixmap)
{
    pix =pixmap;
    update();
}

void PushButton_1::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QBrush(Qt::transparent));
    if (this->isChecked()) {
        int radius = Public_Function::getScaleSize(12);
        QPainterPath path = Public_Function::getRoundRectPath(this->rect(), radius);
        painter.setPen(QPen(QBrush(QColor(20, 134, 250)), Public_Function::getScaleSize(2)));
        painter.setBrush(QBrush());
        painter.drawPath(path);
    }else {
        if (m_pMouseEnter) {
            int radius = Public_Function::getScaleSize(12);
            QPainterPath path = Public_Function::getRoundRectPath(this->rect(), radius);
            painter.setPen(QPen(QColor(238, 238, 238)));
            painter.setBrush(QBrush(QColor(238, 238, 238)));
            painter.drawPath(path);
        }
    }

    if (m_pIconColor.isValid()) {
        if (QColor(Qt::white) == m_pIconColor ||
                QColor(Qt::transparent) == m_pIconColor) {
            painter.setPen(QPen(QColor(224, 224, 224)));
        }else
            painter.setPen(QPen(m_pIconColor));
        if (QColor(Qt::transparent) == m_pIconColor)
            painter.setBrush(QBrush(Qt::white));
        else
            painter.setBrush(QBrush(m_pIconColor));
        QRectF iconRect =  QRectF((this->width() - m_pIconSize.width())/2.0, (this->height() - m_pIconSize.height())/2.0,
                                 m_pIconSize.width(), m_pIconSize.height());
        int radius = Public_Function::getScaleSize(5);
        QPainterPath path = Public_Function::getRoundRectPath(iconRect, radius);
        painter.drawPath(path);

        if (QColor(Qt::transparent) == m_pIconColor) {
            painter.setPen(QPen(QBrush(Qt::red), Public_Function::getScaleSize(2)));
            painter.drawLine(QPointF(path.boundingRect().topRight().x() - Public_Function::getScaleSize(2),
                                     path.boundingRect().topRight().y() + Public_Function::getScaleSize(2)),
                             QPointF(path.boundingRect().bottomLeft().x() + Public_Function::getScaleSize(2),
                                    path.boundingRect().bottomLeft().y() - Public_Function::getScaleSize(2)));
        }
    }
    if(!pix.isNull())
    {
        painter.drawPixmap(this->rect(),pix);
    }
}
