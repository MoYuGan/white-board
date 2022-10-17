#include "customwidget.h"
#include <QDebug>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

}

void CustomWidget::showText(const QString &text, const QFont &font, const QColor &color)
{
    m_pText = text;
    m_pFont = font;
    m_pTextColor = color;
    this->update();
}

void CustomWidget::clearText()
{
    m_pText = QString();
    this->update();
}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.fillRect(this->rect(), QBrush(QColor(80, 80, 80)));

    if (!m_pText.isEmpty()) {
        painter.setPen(QPen(m_pTextColor));
        painter.setFont(m_pFont);
        painter.drawText(this->rect(), Qt::AlignCenter, m_pText);
    }else if (!m_pPixmap.isNull()) {
        painter.drawPixmap(this->rect(), m_pPixmap.scaled(this->size()));
    } else {
        return QWidget::paintEvent(event);
    }
}
