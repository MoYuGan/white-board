#ifndef CUSTOMPUSHBUTTON_4_H
#define CUSTOMPUSHBUTTON_4_H

#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QGestureEvent>
#include "Public/publicfunction.h"
#include "custompushbutton.h"
#include "Extern/extern.h"

class CustomPushButton_4 : public QPushButton
{
    Q_OBJECT
public:
    CustomPushButton_4(QWidget *parent = Q_NULLPTR);
    void mSetPixmap(const QPixmap &pixmap, int angle = 0);
    void mSetTipPixmap(const QPixmap &pixmap);
    void clearText();

    bool eventFilter(QObject *watched, QEvent *event);
    void setRotateAngle(int angle);
    int getRotateAngle();
    void zoomIn();
    void zoomOut();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

signals:
    void toScale(bool);
    void toClosed();

private slots:
    void onToggled(bool checked);
    void onScaleBtnClicked();
    void onCloseBtnClicked();

private:
    QPixmap m_pPixmap = QPixmap();
    QRect m_pPixmapRect = QRect();
    QPixmap m_pTipPixmap = QPixmap();
    CustomPushButton *m_pBtnClose;
    CustomPushButton *m_pBtnScale;
    bool m_pShowFullScreen = false;
    QPointF m_pMousePressedPoint;
    int m_RotateAngle = 0;
    int m_ZoomNum = 0;
    bool m_MousePressed = false;

    void initWidget();
    void resize();
    //获取夹角
    qreal getAngle(QPointF center, QPointF firstPoint, QPointF secondPoint);


};

#endif // CUSTOMPUSHBUTTON_4_H
