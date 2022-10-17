#include "c_slider.h"

C_Slider::C_Slider(QWidget *parent, Qt::WindowFlags f) :
    QLabel(parent, f)
{
    m_SubWidth = 0;
}

void C_Slider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    QPainterPath path = PublicFunction::getRoundRectPath(this->rect(), this->height()/2);
    painter.fillPath(path, QBrush(QColor(199, 226, 254)));

    if (m_SubWidth > 0) {
        QRect subRect = QRect(0, 0, m_SubWidth, this->height());
        if (m_SubWidth == this->width())
            path = PublicFunction::getRoundRectPath(subRect, this->height()/2);
        else
            path = PublicFunction::getRoundRectPath(subRect, this->height()/2, 0, 0, this->height()/2);

        painter.fillPath(path, QBrush(QColor(20, 134, 250)));
    }
}

void C_Slider::mSizeChanged(qint64 currentSize, qint64 totalSize)
{
    qreal subWidth = ((qreal)currentSize)/((qreal)totalSize) * this->width();
    if (subWidth > 0 && subWidth > m_SubWidth && subWidth <= this->width()) {
        m_SubWidth = subWidth;
        update();
    }
}
