#include "custompushbutton_4.h"

CustomPushButton_4::CustomPushButton_4(QWidget *parent) :
    CustomPushButton(parent)
{
    m_pMouseEnter = false;
}

void CustomPushButton_4::mSetIconColor(const QColor &color)
{
    m_pIconColor = color;
}

void CustomPushButton_4::mSetIconSize(const QSize &size)
{
    m_pIconSize = size;
}

bool CustomPushButton_4::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        m_pMouseEnter = true;
        update();
    }else if (event->type() == QEvent::Leave) {
        m_pMouseEnter = false;
        update();
    }
    return CustomPushButton::eventFilter(watched, event);
}

void CustomPushButton_4::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QBrush(Qt::transparent));
    if (this->isChecked()) {
        int radius = PublicFunction::getScaleSize(12);
        QPainterPath path = PublicFunction::getRoundRectPath(this->rect(), radius);
        painter.setPen(QPen(QBrush(QColor(20, 134, 250)), PublicFunction::getScaleSize(2)));
        painter.setBrush(QBrush());
        painter.drawPath(path);
    }else {
        if (m_pMouseEnter) {
            int radius = PublicFunction::getScaleSize(12);
            QPainterPath path = PublicFunction::getRoundRectPath(this->rect(), radius);
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
        int radius = PublicFunction::getScaleSize(5);
        QPainterPath path = PublicFunction::getRoundRectPath(iconRect, radius);
        painter.drawPath(path);

        if (QColor(Qt::transparent) == m_pIconColor) {
            painter.setPen(QPen(QBrush(Qt::red), PublicFunction::getScaleSize(2)));
            painter.drawLine(QPointF(path.boundingRect().topRight().x() - PublicFunction::getScaleSize(2),
                                     path.boundingRect().topRight().y() + PublicFunction::getScaleSize(2)),
                             QPointF(path.boundingRect().bottomLeft().x() + PublicFunction::getScaleSize(2),
                                    path.boundingRect().bottomLeft().y() - PublicFunction::getScaleSize(2)));
        }
    }
}
