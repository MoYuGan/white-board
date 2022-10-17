#ifndef PUSHBUTTON_4_H
#define PUSHBUTTON_4_H

#include <QPushButton>
#include <QPainter>
#include "pushbutton_basic.h"
#include "Public/public_function.h"

//14
class PushButton_4 : public PushButton_Basic
{
public:
    PushButton_4(QWidget *parent = Q_NULLPTR);
    void mSetIconColor(const QColor &color);
    inline QColor mGetColor() { return m_pIconColor; }
    void mSetIconSize(const QSize &size);
    bool eventFilter(QObject *watched, QEvent *event);

protected:
    void paintEvent(QPaintEvent *);

private:
    QColor m_pIconColor;
    QSize m_pIconSize;
    bool m_pMouseEnter;
};

#endif // PUSHBUTTON_4_H
