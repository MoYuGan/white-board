#ifndef CUSTOMPUSHBUTTON_3_H
#define CUSTOMPUSHBUTTON_3_H

#include <QPushButton>
#include <QPainter>
#include "Custom/PushButton/custompushbutton.h"
#include "Public/publicfunction.h"

class CustomPushButton_3 : public CustomPushButton
{
    Q_OBJECT
public:
    CustomPushButton_3(QWidget *parent = nullptr);
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

#endif // CUSTOMPUSHBUTTON_3_H
