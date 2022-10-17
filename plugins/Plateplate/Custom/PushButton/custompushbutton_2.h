#ifndef CUSTOMPUSHBUTTON_2_H
#define CUSTOMPUSHBUTTON_2_H

#include <QPushButton>
#include <QPixmap>
#include <QEvent>
#include <QFrame>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include "Public/publicfunction.h"

class CustomPushButton_2 : public QPushButton
{
    Q_OBJECT
public:
    CustomPushButton_2(const QPixmap &pixmap, int pageIndex, QWidget *parent = Q_NULLPTR);
    void mSetPixmap(const QPixmap &pixmap);
    void mSetIndex(int index);
    bool eventFilter(QObject *watched, QEvent *event);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_pPixmap;
    int m_pPageIndex;
    QRect m_pDelectRect;

signals:
    void deleteItem();
};

#endif // CUSTOMPUSHBUTTON_2_H
