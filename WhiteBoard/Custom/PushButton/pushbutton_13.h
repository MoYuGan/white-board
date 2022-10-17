#ifndef PUSHBUTTON_13_H
#define PUSHBUTTON_13_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include "Public/public_function.h"

class PushButton_13 : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton_13(QWidget *parent = nullptr);
    bool isOpen();

protected:
    void paintEvent(QPaintEvent *);

signals:

private:
    bool open =true;

};

#endif // PUSHBUTTON_13_H
