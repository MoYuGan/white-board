#include "custompushbutton.h"

CustomPushButton::CustomPushButton(QWidget *parent) :
    QPushButton(parent)
{
    m_pCursor = QCursor(Qt::PointingHandCursor);
    this->installEventFilter(this);
}

bool CustomPushButton::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        m_pOrgCursor = this->cursor();
        this->setCursor(m_pCursor);
    }else if (event->type() == QEvent::Leave) {
        this->setCursor(m_pOrgCursor);
    }
    return QPushButton::eventFilter(watched, event);
}

void CustomPushButton::setEnterCursor(const QCursor &cursor)
{
    m_pCursor = cursor;
}
