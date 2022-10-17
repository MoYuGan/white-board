#ifndef PUSHBUTTON_3_H
#define PUSHBUTTON_3_H

#include <QPushButton>
#include <QPainter>
#include "pushbutton_basic.h"
#include "Public/public_function.h"

//12
class PushButton_3 : public PushButton_Basic
{
    Q_OBJECT
public:
    PushButton_3(QWidget *parent = Q_NULLPTR);

    void mSetRoundSize(const QSize &size);
    void mSetValue(int value);
    inline int mGetValue() { return m_pValue; }
    bool eventFilter(QObject *watched, QEvent *event);

protected:
    void paintEvent(QPaintEvent *);

private:
    QSize m_pRoundSize;
    bool m_pMouseEnter;
    int m_pValue;
};

#endif // PUSHBUTTON_3_H
