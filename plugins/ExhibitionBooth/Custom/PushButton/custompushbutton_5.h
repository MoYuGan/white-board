#ifndef CUSTOMPUSHBUTTON_5_H
#define CUSTOMPUSHBUTTON_5_H

#include <QPushButton>
#include <QPainter>
#include <QButtonGroup>
#include "Public/publicfunction.h"

class CustomPushButton_5 : public QPushButton
{
    Q_OBJECT
public:
    CustomPushButton_5(const QString &deviceName, QWidget *parent = Q_NULLPTR);
    void setIndex(int index);

private:
    QString m_DeviceName;
    int m_Index;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CUSTOMPUSHBUTTON_5_H
