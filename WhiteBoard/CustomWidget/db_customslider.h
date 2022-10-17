#ifndef DB_CUSTOMSLIDER_H
#define DB_CUSTOMSLIDER_H

#include <QSlider>
#include <QEvent>
#include <QMouseEvent>

class DB_CustomSlider : public QSlider
{
public:
    DB_CustomSlider(QWidget *parent = Q_NULLPTR) :
        QSlider(parent) {
        this->installEventFilter(this);
        //this->setMouseTracking(true);
    }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::MouseMove) {
        }else if (event->type() == QEvent::Enter) {
            this->setCursor(Qt::PointingHandCursor);
        }else if (event->type() == QEvent::Leave){
            this->setCursor(Qt::ArrowCursor);
        }
        return QSlider::eventFilter(watched, event);
    }


};

#endif // DB_CUSTOMSLIDER_H
