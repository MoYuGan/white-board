#ifndef CUSTOMITEM_ZHICHI_H
#define CUSTOMITEM_ZHICHI_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "Extern/extern.h"
#include "QDesktopWidget"
#include <QTouchEvent>


class CustomItem_ZhiChi : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    //鼠标位置标志
    enum MOUSEPOS{
        inRectClose =1,
        inRectRotate,
        inRectDrag,
        inRectLine,
        inRectMove,
        inRectNo
    };

    /*自定义Type*/
    enum { Type = UserType + 108 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

public:
    explicit CustomItem_ZhiChi(QObject *parent = nullptr);
    void getRectStyle(QPoint );                 //获得鼠标所在位置
    QPainterPath getCalibrationrect();          //绘制刻度区域
    QPainterPath getIconrect(QString str);      //绘制图标
    void getrotate(QPointF cen, QPointF second, QPointF first); //计算旋转角度
    QPointF getpoint(QPointF, QPointF , QPointF );              //获得划线坐标
    int adapt(int );

signals:
    void sendrotate(int );                      //发送旋转角度
    void deleteitem(QGraphicsItem *);                         //发送删除信号
    void sendline11(QPointF ,QPointF );         //鼠标移动绘制动态信号
    void sendline12(QPointF ,QPointF );         //鼠标松开时绘制定型信号

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);//实现鼠标追踪效果
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF ,QPointF );
    void moveEvent(QPointF ,QPointF );
    void releaseEvent(QPointF ,QPointF );
    int pointid =0;

    QRectF boundingRect() const;
    QPainterPath shape() const;
private:
    QRect m_rect;               //总区域
    QRect drag_rect;            //拉伸图标区域
    QRect close_rect;           //关闭图标区域
    QRect rotate_rect;          //旋转图标区域
    QRect line_rect;            //划线区域
    QRect move_rect;            //移动区域
    float mm;                   //单位换算
    MOUSEPOS mousepos = MOUSEPOS::inRectNo;
    bool mousestate =false;     //鼠标移动或松开标志位
    QPointF start;              //鼠标按下点
    QPointF drawlinedot;        //临时记录数据点
    QPointF end;                //鼠标移动或松开标志位
    QPointF movedot;            //临时记录数据点
    int rotate_angle =0;        //角度
    int change_angle =0;        //角度改变
    int change_lenght =0;       //划线长度
    int showrotate = 0;         //获得划线笔宽
    int  mheight;  //刻度值高度
    int  deviation;  //划线区域高度
    int Iconlength;  //图标大小
    int  RoundAngle;  //圆角大小
};

#endif // CUSTOMITEM_ZHICHI_H
