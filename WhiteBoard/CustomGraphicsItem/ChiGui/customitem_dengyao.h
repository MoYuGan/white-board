#ifndef CUSTOMITEM_DENGYAO_H
#define CUSTOMITEM_DENGYAO_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <math.h>
#include <QTouchEvent>

class CustomItem_DengYao : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    /*自定义Type*/
    enum { Type = UserType + 108 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

public:
    explicit CustomItem_DengYao(QObject *parent = nullptr);
    QPainterPath outDrawArea();
    QPainterPath inDrawArea();
    QPainterPath getIconrect(QString str);
    void getRectStyle(QPoint );
    QPointF getpoint(QPointF ,QPointF ,QPointF );
    QPainterPath test();
    int adapt(int );

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void getrotate(QPointF cen, QPointF second, QPointF first);
    bool getMousePos(QPoint );
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF ,QPointF );
    void moveEvent(QPointF ,QPointF );
    void releaseEvent(QPointF ,QPointF );
    int pointid =0;

signals:
    void deleteitem2(QGraphicsItem *);
    void sendline21(QPointF ,QPointF ); //鼠标移动绘制动态信号
    void sendline22(QPointF ,QPointF ); //鼠标松开时绘制定型信号
    void refresh();

public slots:

private:
    QRect *m_rect;
    QRect mrect;
    QRect drag_rect;
    QRect close_rect;
    QRect rotate_rect;
    QRect linedown_rect;
    QRect lineleft_rect;
    QRect rrect;
    QPolygon lineup_rect;
    QPolygon move_rect;
    float mm;
    bool mousestate =false;
    QPointF start[4];
    QPointF end;
    QPointF store;
    int rotate_angle =0;
    int change_angle =0;
    int change_lenght =0;
    int showrotate =0;
    double two =sqrt(2);    //根号2
    int xx;
    int yy;
    int num =0;
    int mousepos = 0x0000;//上检测区01下检测区02左检测区04移动80旋转40删除20拉伸10
    int mheight =20;//内部刻度和检测区域
    int Iconlength =50;//内部图标大小
    int deviation =30;//外部刻度和检测区域
};

#endif // CUSTOMITEM_DENGYAO_H
