#ifndef CUSTOMITEM_YUANGUI_H
#define CUSTOMITEM_YUANGUI_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QDebug>
#include <QCursor>
#include <qmath.h>
#include <QTouchEvent>
#include "Public/public_function.h"
/*************************************************************************
                                圆规左边腿绘制
*************************************************************************/
class YuanGui_leftFoot : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit YuanGui_leftFoot(QObject *parent = nullptr);
    /*自定义Type*/
    enum { Type = UserType + 108 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

protected:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   QRectF boundingRect() const;
   bool sceneEvent(QEvent *event);
   QPainterPath downShape( );
   QPainterPath upShape( );
   QPainterPath shape() const;
signals:

private:
   QRectF rect;
   int pointid =0;

};



/*************************************************************************
                                圆规右边腿绘制
*************************************************************************/
class YuanGui_rightFoot : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit YuanGui_rightFoot(QObject *parent = nullptr);
    /*自定义Type*/
    enum { Type = UserType + 108 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    bool sceneEvent(QEvent *event);
    QPainterPath shape() const;

    QPainterPath downShape( );
    void upShape(QPainter* );
    void penPointShape(QPainter* );
    void penNibShape(QPainter* );
    void penHandShape(QPainter* );
    void pendDragRect(QPainter* );

signals:
    void sendDragPressMessage(QPointF );
    void sendDragMoveMessage(QPointF ,QPointF );
    void sendDragReleaseMessage(QPointF );

    void sendRotatePressMessage();
    void sendRotateMoveMessage(QPointF ,QPointF );
    void sendRotateReleaseMessage();

private:
    QRectF *rect;
    QPainterPath pointshape;
    QPainterPath handshape;
    QPainterPath handpath;
    QPainterPath pointpath;
    QPainterPath downpath;
    QPainterPath uppath;
    bool mousestate =false;
    int num =0;
    int pointid =0;
};



/*************************************************************************
                                圆规绞合处绘制
*************************************************************************/
class YuanGui_hinge : public QObject ,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit YuanGui_hinge(QObject *parent = nullptr);
    /*自定义Type*/
    enum { Type = UserType + 108 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void moveShape(QPainter* );
    void closeShape(QPainter* );
    void arrowsShape(QPainter* );
    void headShape(QPainter* );
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    bool sceneEvent(QEvent *event);
    QPainterPath shape() const;

signals:
    void sendMoveMessage(QPointF );
    void sendCloseMessage();

private:
    QRectF rect;
    QRectF moverect;
    QRectF closerect;
    QPainterPath headpath;

    bool mousepress =false;
    int pointid =0;

};


/*************************************************************************
                                圆规各部件组装
*************************************************************************/
class CustomItem_YuanGui : public QObject ,public QGraphicsItem
    {
        Q_OBJECT
    public:
        explicit CustomItem_YuanGui(QObject *parent = nullptr);
        void connectInit();
        void mouseDraw(QPointF =QPointF(0,0),QPointF =QPointF(0,0));
        void mouseRotate(QPointF ,QPointF );

        /*自定义Type*/
        enum { Type = UserType + 108 };
        int type() const
        {
            // Enable the use of qgraphicsitem_cast with this item.
            return Type;
        }

    protected:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const;
        QPointF getMoveCenter();
        void getRotate(QPointF , QPointF , QPointF );

    signals:
    void sendrotate5(int );
    void deleteitem5(QGraphicsItem *);
    void sendarc51(QPointF ,qreal ,qreal, qreal);
    void sendarc52(QPointF ,qreal ,qreal, qreal);

    private:
        YuanGui_leftFoot* left;
        YuanGui_rightFoot* right;
        YuanGui_hinge* zhuanzhou;
        QRectF rect;
        qreal rotate=0;
        float angle =30;
        double rotatechange=0;
        double rotateangle=0;
    };

#endif // CUSTOMITEM_YUANGUI_H
