#ifndef PUSHBUTTON_1_H
#define PUSHBUTTON_1_H

#include <QPushButton>
#include <QPainter>
#include <QEvent>
#include "Public/public_function.h"
#include "pushbutton_basic.h"

//13
class PushButton_1 : public PushButton_Basic
{
    Q_OBJECT
public:
    PushButton_1(QWidget *parent = Q_NULLPTR);
    void mSetIconColor(const QColor &color);
    void mSetIconSize(const QSize &size);
    inline QColor mGetColor() { return m_pIconColor; }
    bool eventFilter(QObject *watched, QEvent *event);
    void setPixmap(QPixmap );

protected:
    void paintEvent(QPaintEvent *);

private:
    QColor m_pIconColor;
    QSize m_pIconSize;
    bool m_pMouseEnter;
    QPixmap pix;
};

#endif // PUSHBUTTON_1_H
