#include "custompushbutton_3.h"

CustomPushButton_3::CustomPushButton_3(QWidget *parent) :
    CustomPushButton(parent)
{
    m_pMouseEnter = false;
    m_pValue = 0;
}

void CustomPushButton_3::mSetRoundSize(const QSize &size)
{
    m_pRoundSize = size;
}

void CustomPushButton_3::mSetValue(int value)
{
    m_pValue = value;
}

bool CustomPushButton_3::eventFilter(QObject *watched, QEvent *event)
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

void CustomPushButton_3::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Qt4CompatiblePainting);
    painter.fillRect(this->rect(), QBrush(Qt::transparent));
    if (this->isChecked()) {
        painter.setPen(QPen(QBrush(QColor(20, 134, 250)), PublicFunction::getScaleSize(2)));
        painter.setBrush(QBrush());
        painter.drawEllipse(this->rect().center(), this->width()/2 - PublicFunction::getScaleSize(2),
                            this->height()/2 - PublicFunction::getScaleSize(2));
    }else {
        if (m_pMouseEnter)  {
            painter.setPen(QPen(QBrush(QColor(238, 238, 238)), PublicFunction::getScaleSize(2)));
            painter.setBrush(QBrush(QColor(238, 238, 238)));
            painter.drawEllipse(this->rect().center(), this->width()/2 - PublicFunction::getScaleSize(2),
                                this->height()/2 - PublicFunction::getScaleSize(2));
        }
    }
    painter.setPen(QPen(QColor(136, 136, 136)));
    painter.setBrush(QBrush(QColor(136, 136, 136)));
    painter.drawEllipse(this->rect().center(), m_pRoundSize.width()/2, m_pRoundSize.height()/2);
}
