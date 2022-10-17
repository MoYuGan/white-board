#ifndef CUSTOMPUSHBUTTON_3_H
#define CUSTOMPUSHBUTTON_3_H

#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QGestureEvent>
#include "Public/function.h"
#include "custompushbutton.h"

class CustomPushButton_3 : public QPushButton
{
    Q_OBJECT
public:
    CustomPushButton_3(QWidget *parent = Q_NULLPTR);
    void registGestureType();
    void mSetPixmap(const QPixmap &pixmap);
    void toClearDisplay();
    bool eventFilter(QObject *watched, QEvent *event);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);
    bool gestureEvent(QGestureEvent *event);

signals:
    void toScale(bool);
    void toClosed();

private slots:
    void onToggled(bool checked);
    void onScaleBtnClicked();
    void onCloseBtnClicked();

private:
    QPixmap m_pPixmap;
    QRect m_pPixmapRect;
    CustomPushButton *m_pBtnClose;
    CustomPushButton *m_pBtnScale;
    bool m_pShowFullScreen = false;
    QPointF m_pMousePressedPoint;

    void initWidget();
    void resize();
    //获取夹角
    qreal getAngle(QPointF center, QPointF firstPoint, QPointF secondPoint);


};

#endif // CUSTOMPUSHBUTTON_3_H
