#ifndef DB_SCREENSHOTS_H
#define DB_SCREENSHOTS_H

#include <QWidget>
#include "ShareStyle/db_scale.h"

namespace Ui {
class DB_ScreenShots;
}

class DB_ScreenShots : public QWidget
{
    Q_OBJECT

public:
    explicit DB_ScreenShots(QWidget *parent = 0);
    ~DB_ScreenShots();
    void show();
    void resize();
    bool eventFilter(QObject *watched, QEvent *event);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::DB_ScreenShots *ui;
    bool m_pMousePressed;
    QPointF m_pPressedPoint;
    QRectF m_pDragRect;             //选择框
    QPointF m_pUpCenterPoint;       //选择框上左边线中点
    QPointF m_pRightCenterPoint;    //选择框右左边线中点
    QPointF m_pDownCenterPoint;     //选择框下左边线中点
    QPointF m_pLeftCenterPoint;     //选择框左边线中点
    int m_pDirection;               //缩放方向，0=左上，1=上，2=右上，3=右，4=右下，5=下，6=左下，7=左
    QSize m_pDragRectMinSize;

    void initWidget();
    void scaleDragRect(QPointF mousePos);
    void resizeDragRect(QPointF pressedPoint, QPointF currentPoint);
    void showToolWidget();

signals:
    void screenShots(QRectF);
};

#endif // DB_SCREENSHOTS_H
