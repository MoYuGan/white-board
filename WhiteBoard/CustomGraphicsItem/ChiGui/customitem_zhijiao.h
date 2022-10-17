#ifndef CUSTOMITEM_ZHIJIAO_H
#define CUSTOMITEM_ZHIJIAO_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <qmath.h>
#include <QTouchEvent>
class CustomItem_ZhiJiao : public QObject, public QGraphicsItem
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
    explicit CustomItem_ZhiJiao(QObject *parent = nullptr);
    QPainterPath outDrawArea();                     //外部绘图路径
    QPainterPath inDrawArea();                      //内部绘图路径
    QPainterPath getIconrect(QString str);          //获得按钮图标
    QPainterPath test();                            //显示外部测试shape路径
    void getRectStyle(QPoint );                     //获得鼠标所在位置
    QPointF getpoint(QPointF ,QPointF ,QPointF );   //获得划线坐标
    bool getMousePos(QPoint );


protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void getrotate(QPointF cen, QPointF second, QPointF first);//获得旋转角度
    int adapt(int );
    QSize adapt(int ,int );
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF ,QPointF );
    void moveEvent(QPointF ,QPointF );
    void releaseEvent(QPointF ,QPointF );
    int pointid =0;


signals:
    void deleteitem3(QGraphicsItem *);   //发送删除信号
    void sendline31(QPointF ,QPointF );  //鼠标移动绘制动态信号
    void sendline32(QPointF ,QPointF );  //鼠标松开时绘制定型信号
    void refresh();
public slots:

private:
    QRect *m_rect;
    QRect mrect;
    QRect drag_rect;      //拉伸按钮区域
    QRect close_rect;     //关闭按钮区域
    QRect rotate_rect;    //旋转按钮区域
    QRect linedown_rect;  //底部划线区域
    QRect lineleft_rect;  //左边划线区域

    QPolygon lineup_rect; //斜边划线区域
    QPolygon move_rect;   //移动区域
    float mm;
    bool mousestate =false; //鼠标按下或松开标志位
    QPointF start[4];          //鼠标按下点
    QPointF end;            //鼠标移动或松开点
    QPointF store;          //临时记录数据点
    int rotate_angle =0;    //角度
    int change_angle =0;    //角度改变
    int change_lenght =0;   //划线长度
    int showrotate = 0;     //数值是否显示判断标志
    int xx;                 //临时宽
    int yy;                 //临时高
    double san =sqrt(3);    //根号3
    int mheight =20;
    int Iconlength =50;
    int deviation =30;
    int mousepos = 0x0000;//上检测区01下检测区02左检测区04移动80旋转40删除20拉伸10
    int num =0;
};

#endif // CUSTOMITEM_ZHIJIAO_H
