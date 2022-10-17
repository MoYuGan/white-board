#include "pushbutton_basic.h"

PushButton_Basic::PushButton_Basic(QWidget *parent) :
    QPushButton(parent)
{
    this->installEventFilter(this);
}

bool PushButton_Basic::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        m_pOrgCursor = this->cursor();
        this->setCursor(Qt::PointingHandCursor);
    }else if (event->type() == QEvent::Leave) {
        this->setCursor(m_pOrgCursor);
    }
    return QPushButton::eventFilter(watched, event);
}
