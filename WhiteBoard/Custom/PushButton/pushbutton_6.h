#ifndef PUSHBUTTON_6_H
#define PUSHBUTTON_6_H

#include <QPushButton>
#include <QPixmap>
#include <QEvent>
#include <QFrame>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QHBoxLayout>
#include "Public/public_function.h"

class PushButton_6 : public QPushButton
{
    Q_OBJECT
public:
    PushButton_6(const QPixmap &pixmap, int pageIndex, QWidget *parent = Q_NULLPTR);
    void mSetPixmap(const QPixmap &pixmap);
    void mSetIndex(int index);
    bool eventFilter(QObject *watched, QEvent *event);
    inline QGraphicsView *mGetView() { return m_View; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_pPixmap;
    int m_pPageIndex;
    QRect m_pDelectRect;
    QGraphicsView *m_View;

    void initWidget();

signals:
    void deleteItem();

};

#endif // PUSHBUTTON_6_H
