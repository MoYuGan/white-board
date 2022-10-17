#ifndef PUSHBUTTON_10_H
#define PUSHBUTTON_10_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include "Public/public_function.h"

class PushButton_10 : public QPushButton
{
    Q_OBJECT
public:
    PushButton_10(QWidget *parent = Q_NULLPTR);
    void m_setText(QString );

protected:
    void paintEvent(QPaintEvent *);

private:
    QString text_Str;

};

#endif // PUSHBUTTON_10_H
