#include "pushbutton_4.h"

PushButton_4::PushButton_4(QWidget *parent) :
    PushButton_Basic(parent)
{
    m_pMouseEnter = false;
}

void PushButton_4::mSetIconColor(const QColor &color)
{
    m_pIconColor = color;
}

void PushButton_4::mSetIconSize(const QSize &size)
{
    m_pIconSize = size;
}

bool PushButton_4::eventFilter(QObject *watched, QEvent *event)
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

void PushButton_4::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QBrush(Qt::transparent));
    if (this->isChecked()) {
        painter.setPen(QPen(QBrush(QColor(20, 134, 250)), Public_Function::getScaleSize(2)));
        painter.setBrush(QBrush());
        painter.drawRoundedRect(this->rect(), Public_Function::getScaleSize(5),
                                Public_Function::getScaleSize(5));
    }else {
        painter.setPen(QPen(QBrush(QColor(238, 238, 238)), Public_Function::getScaleSize(2)));
        if (m_pMouseEnter) {
            painter.setBrush(QBrush(QColor(238, 238, 238)));
        }else {
            painter.setBrush(QBrush());
        }
        int border = Public_Function::getScaleSize(3);
        painter.drawRoundedRect(QRect((this->width() - m_pIconSize.width())/2 - border,
                                      (this->height() - m_pIconSize.height())/2 - border,
                                      m_pIconSize.width() + border*2, m_pIconSize.height() + border*2),
                                Public_Function::getScaleSize(3),
                                Public_Function::getScaleSize(3));
    }

    if (m_pIconColor.isValid()) {
        if (QColor(Qt::white) == m_pIconColor) {
            painter.setPen(QPen(QColor(224, 224, 224)));
        }else
            painter.setPen(QPen(m_pIconColor));
        painter.setBrush(QBrush(m_pIconColor));
        QRect rect = QRect((this->width() - m_pIconSize.width())/2, (this->height() - m_pIconSize.height())/2,
                           m_pIconSize.width(), m_pIconSize.height());
        painter.drawRoundedRect(rect, Public_Function::getScaleSize(3), Public_Function::getScaleSize(3));

        QPainterPath path;
        path.moveTo(rect.topRight().x() - Public_Function::getScaleSize(2),
                    rect.topRight().y() + Public_Function::getScaleSize(2));
        path.lineTo(rect.topRight().x() - Public_Function::getScaleSize(2) - Public_Function::getScaleSize(5),
                    rect.topRight().y() + Public_Function::getScaleSize(2));
        path.lineTo(rect.topRight().x() - Public_Function::getScaleSize(2),
                    rect.topRight().y() + Public_Function::getScaleSize(2) + Public_Function::getScaleSize(5));
        path.closeSubpath();
        painter.fillPath(path, QBrush(Qt::yellow));
    }
}
