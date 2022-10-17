#include "customframe.h"
#include <QEvent>
#include <QMouseEvent>

CustomFrame::CustomFrame(QWidget *parent, Qt::WindowFlags f) :
    QFrame(parent, f)
{
    this->installEventFilter(this);
}

bool CustomFrame::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseevent = static_cast<QMouseEvent *>(event);
        if (mouseevent->button() == Qt::LeftButton)
            emit frameClicked();
    }
    return QFrame::eventFilter(watched, event);
}
