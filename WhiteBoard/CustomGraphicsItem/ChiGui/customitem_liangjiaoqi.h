#ifndef CUSTOMITEM_LIANGJIAOQI_H
#define CUSTOMITEM_LIANGJIAOQI_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QRect>
#include <QTouchEvent>

class CustomItem_LiangJiaoQi : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum MOUSEPOS4{
        inRectClose4 =1,
        inRectRotate4,
        inRectDrag4,
        inRectMove4,
        move_rect1,
        move_rect2,
        inRectNo4
    };

    /*自定义Type*/
    enum { Type = UserType + 108 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

public:
    explicit CustomItem_LiangJiaoQi(QObject *parent = nullptr);
    QPainterPath outDrawArea();             //最外圈大半圆
    QPainterPath inDrawArea4();
    QPainterPath inDrawArea3();
    QPainterPath inDrawArea2();
    QPainterPath inDrawArea1();             //最小半圆
    QPainterPath getIconrect(QString str);  //绘制图标
    void getRectStyle(QPoint );             //获得鼠标位置
    void getrotate(QPointF cen, QPointF second, QPointF first);     //计算整体旋转角度
    void getrotate2(QPointF cen, QPointF second, QPointF first);    //计算外部小圆1旋转角度
    void getrotate3();      //获得拉伸后小圆1圆心坐标
    void getrotate4(QPointF cen, QPointF second, QPointF first);    //计算外部小圆2旋转角度
    void getrotate5();      //获得拉伸后小圆2圆心坐标
    int adapt(int );

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QPainterPath test();    //测试shape外观
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF ,QPointF );
    void moveEvent(QPointF ,QPointF );
    void releaseEvent(QPointF ,QPointF );
    int pointid =0;

signals:
//    void sendrotate4(int ); //发送旋转角度
    void deleteitem4(QGraphicsItem *);    //发送删除信号
    void refresh();

private:
    QRectF m_rect;          //最外边框
    QRectF mrect;           //刻度边框
    QRectF rect;            //临时记录尺寸框
    QRect drag_rect;        //拉伸图标区域
    QRect close_rect;       //关闭图标区域
    QRect rotate_rect;      //旋转图标区域
    QRect move_rect3;       //外部小圆1
    QRect move_rect4;       //外部小圆2
    QPointF start;          //鼠标按下点
    QPointF end;            //鼠标移动或松开点
    QPointF store;          //备用点
    QPointF movedot1;       //外部小圆1圆心坐标
    QPointF movedot2;       //外部小圆2圆心坐标
    MOUSEPOS4 mousepos4 = MOUSEPOS4::inRectNo4;
    bool mousestate =false; //鼠标按下标志位
    int rotate_angle =0;    //整体旋转角度
    int change_angle =0;    //整体旋转角度改变
    int move_angle1 =-30;   //外部小圆1旋转角度
    int move_change1 =-30;  //外部小圆1旋转角度改变
    int move_angle2 =0;     //外部小圆2旋转角度
    int move_change2 =0;    //外部小圆2旋转角度改变
    int showtext =0;        //角度文本显示
    int xx =0;              //临时宽度记录
    int yy =0;              //临时高度记录

    int mheight =20;
    int Iconlength =50;
    int deviation =10;
};
#endif // CUSTOMITEM_LIANGJIAOQI_H
