#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QEvent>

class CustomPushButton : public QPushButton
{
public:
    CustomPushButton(QWidget *parent = nullptr) : QPushButton(parent) {}
    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::Enter) {
            this->setCursor(Qt::PointingHandCursor);
        }else if (event->type() == QEvent::Leave) {
            this->setCursor(Qt::ArrowCursor);
        }
        return QPushButton::eventFilter(watched, event);
    }
};

#endif // CUSTOMPUSHBUTTON_H
