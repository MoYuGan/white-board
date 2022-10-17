#ifndef WIDGET_2_H
#define WIDGET_2_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPainter>

class Widget_2 : public QWidget
{
    Q_OBJECT
public:
    Widget_2(QString text,QWidget *parent =nullptr);
    virtual ~Widget_2();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString str;
    QTimer *timer;

};

#endif // WIDGET_2_H
