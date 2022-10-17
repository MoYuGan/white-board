#ifndef PUSHBUTTON_12_H
#define PUSHBUTTON_12_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include "Public/public_function.h"

class PushButton_12 : public QPushButton
{
    Q_OBJECT
public:
    PushButton_12(QWidget *parent = Q_NULLPTR);
    void changePixmap(QString );

protected:
    void paintEvent(QPaintEvent *);

signals:
    void sendShowButtonSignal(QString );

private:
    QString filepath =QString();
    QPushButton *btn;

};
#endif // PUSHBUTTON_12_H
