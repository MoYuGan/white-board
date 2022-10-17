#ifndef PUSHBUTTON_9_H
#define PUSHBUTTON_9_H

#include <QWidget>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QEvent>

class PushButton_9 : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton_9(QWidget *parent = nullptr);
    void msetShape(int );
    void mSetRoundSize(const QSize size);

protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:

private:
    bool m_isout =true;
    int m_lineshape =0;
    int number =0;
};


#endif // PUSHBUTTON_9_H
