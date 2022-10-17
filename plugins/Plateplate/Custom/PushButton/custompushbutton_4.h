#ifndef CUSTOMPUSHBUTTON_4_H
#define CUSTOMPUSHBUTTON_4_H

#include <QPainter>
#include <QEvent>
#include "Custom/PushButton/custompushbutton.h"
#include "Public/publicfunction.h"

class CustomPushButton_4 : public CustomPushButton
{
    Q_OBJECT
public:
    CustomPushButton_4(QWidget *parent = nullptr);
    void mSetIconColor(const QColor &color);
    void mSetIconSize(const QSize &size);
    inline QColor mGetColor() { return m_pIconColor; }
    bool eventFilter(QObject *watched, QEvent *event);
protected:
    void paintEvent(QPaintEvent *);
private:
    QColor m_pIconColor;
    QSize m_pIconSize;
    bool m_pMouseEnter;
};

#endif // CUSTOMPUSHBUTTON_4_H
