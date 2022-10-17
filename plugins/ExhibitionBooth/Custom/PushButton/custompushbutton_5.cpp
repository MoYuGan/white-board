#include "custompushbutton_5.h"

CustomPushButton_5::CustomPushButton_5(const QString &deviceName, QWidget *parent) :
    m_DeviceName(deviceName),
    QPushButton(parent)
{
}

void CustomPushButton_5::setIndex(int index)
{
    m_Index = index;
}

void CustomPushButton_5::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    int radius = PublicFunction::getScaleSize(5);
    int border = PublicFunction::getScaleSize(3);

    painter.fillPath(PublicFunction::getRoundRectPath(this->rect(), radius), QBrush(Qt::white));
    QRectF borderRect = QRectF(border/2.0, border/2.0, this->width() - border, this->height() - border);
    painter.setBrush(QBrush());
    if (this->isChecked()) {
        painter.setPen(QPen(QBrush(QColor(20,134,250)), border));
    }else  {
        painter.setPen(QPen(QBrush(QColor(224, 224, 224)), border));
    }
    painter.drawPath(PublicFunction::getRoundRectPath(borderRect, radius));

    QRect indexRect, pixmapRect, nameRect;
    indexRect = QRect(border, border, (this->width() - border*2)/5, this->height() - border*2);
    pixmapRect = QRect(0, 0, PublicFunction::getScaleSize(34), PublicFunction::getScaleSize(41));
    pixmapRect.moveCenter(QPoint(indexRect.x() + indexRect.width() + pixmapRect.width()/2, this->height()/2));
    nameRect = QRect(pixmapRect.x() + pixmapRect.width(), border,
                     this->width() - border*2 - indexRect.width() - pixmapRect.width(), this->height() - border*2);

    painter.setFont(PublicFunction::getFont(16));
    painter.setPen(QPen(QColor(102,102,102)));
    painter.drawText(indexRect, QString("%1").arg(m_Index + 1), QTextOption(Qt::AlignCenter));
    if (this->isChecked())
        painter.drawPixmap(pixmapRect, QPixmap("://images/shexiangtou2@2x.png"));
    else
        painter.drawPixmap(pixmapRect, QPixmap("://images/shexiangtou@2x.png"));
    painter.drawText(nameRect, m_DeviceName, QTextOption(Qt::AlignCenter));
}
