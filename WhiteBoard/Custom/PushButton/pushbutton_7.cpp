#include "pushbutton_7.h"
#include <QDebug>

PushButton_7::PushButton_7(const QPixmap &icon, const QPixmap &checkedIcon, const QPixmap &hoverIcon, QWidget *parent):
    PushButton_Basic(parent) ,
    m_Icon(icon),
    m_CheckedIcon(checkedIcon),
    m_HoverIcon(hoverIcon)
{
    this->installEventFilter(this);
}

void PushButton_7::setHoverStyle(bool enabled)
{
    m_HasHoverStyle = enabled;
}

void PushButton_7::mSetIconSize(QSize iconSize)
{
    m_IconSize = iconSize;
}

bool PushButton_7::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        m_MouseEnter = true;
    }else if(event->type() == QEvent::Leave) {
        m_MouseEnter = false;
    }else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (this->rect().contains(mouseEvent->pos()) && this->isChecked())
            emit this->checkedClicked();
    }

    return PushButton_Basic::eventFilter(watched, event);
}

void PushButton_7::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.fillRect(this->rect(), Qt::transparent);

    QRect rect = QRect(1, 1, this->rect().width() - 2, this->rect().height() - 2);
    rect.moveCenter(this->rect().center());
    QPainterPath path;
    path.addRoundedRect(rect, rect.width()/2.0, rect.height()/2.0);

    if (!m_HasHoverStyle) {
        if (m_MouseEnter)
            painter.fillPath(path, QBrush(QColor(20,134,250)));
        else
            painter.fillPath(path, QBrush(Qt::white));
    }else {
        if (m_MouseEnter && !this->isChecked()) {
            painter.fillPath(path, QBrush(QColor(20,134,250)));
            if (!this->isChecked()) {
                if (m_HasHoverStyle && m_MouseEnter) {
                    path = QPainterPath();
                    int margin = Public_Function::getScaleSize(2);
                    rect = QRect(rect.x() + margin, rect.y() + margin, rect.width() - 2*margin, rect.height() - 2*margin);
                    path.addRoundedRect(rect, rect.width()/2.0, rect.height()/2.0);
                }
                painter.fillPath(path, QBrush(Qt::white));
            }
        }else if (this->isChecked()){
            painter.fillPath(path, QBrush(QColor(20,134,250)));
        }else {
            painter.fillPath(path, QBrush(Qt::white));
        }
    }

    QPixmap icon;
    if (this->isChecked() && !m_CheckedIcon.isNull())
        icon = m_CheckedIcon;
    else if (m_MouseEnter && !m_HoverIcon.isNull())
        icon = m_HoverIcon;
    else
        icon = m_Icon;

    if (!icon.isNull()) {
        QRect pixmapRect = QRect(0, 0, Public_Function::getScaleSize(34), Public_Function::getScaleSize(32));
        pixmapRect.moveCenter(this->rect().center());

        painter.drawPixmap(pixmapRect, icon);
    }
}
