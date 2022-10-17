#ifndef PATHITEM_H
#define PATHITEM_H

#include <QObject>
#include <QGraphicsPathItem>
#include <QPen>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include "Extern/extern.h"
#include "Public/public_function.h"
#include <QTouchEvent>

class PathItem : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
public:
    //历史修改类型
    enum HistoryType {
        Path,       //修改了路径
        Pen,        //修改了画笔
        ZValue      //修改了图层级数
    };

    /*自定义Type*/
    enum { Type = UserType + (int)((int)(ItemType::PathItem)) };
    int type() const override{ return Type; }

public:
    //擦除锁，擦除时候多个线程对同一个item进行擦除时，防止同时擦除
    bool m_EraseLock = false;

public:
    PathItem(QGraphicsItem *parent = Q_NULLPTR,int num=0,int num1=0);
    QPainterPath shape() const;
    int getPathCount();
    void setSubPaths(QList<QPainterPath> subPaths);
    QList<QPainterPath> getSubPaths();
    void firstSetPen(const QPen &pen);
    void m_setPen(const QPen &pen);
    void m_setZValue(qreal z);
    void m_drawPath(QPainter* ,int );
    void m_comparePath(QPainterPath ,QPainterPath );
    int  m_getNumber();
    void m_setNumber(int );
    void m_getPathShapeData(PathItem* ,QPainterPath );
    void drawNib(QPainter* ,int ,int );
    void m_drawLine(QPainter* , QPointF dot1,QPointF dot2,double penwidth1,double penwidth2);
    double getrotate(QPointF , QPointF , QPointF );
    void getItemPath();


    int m_number =5;

    void changePathShape(int );
    int getPathShape();

    void setSelected(bool selected);
    QList<QGraphicsItem *> getFullPathItems();

    QPen getItemPen();
    int getItemZvalue();
    //递归子item
    void recursiveChildItem(QList<QGraphicsItem*> *childItems);
    //递归父item
    void recursiveParentItem(QList<QGraphicsItem*> *parentItems);
    //移动item
    void moveItem(const QPointF &pt);
    //移动item，参数一：当前item的递归子item和递归父item的集合， 参数二：移动差值（x和y）
    void moveItem(QGraphicsItem *items, const QPointF &pt);
    //旋转Item
    void rotateItem(const qreal &angle, const QPointF &center);
    //缩放Item
    void scaleItem(const qreal &xFactor, const qreal &yFactor, const QPointF &center);
    //翻转
    QPainterPath flipItemHorizontal(const QPointF &center);
    QPainterPath flipItemVertical(const QPointF &center);
    //镜像, 参数一：翻转线，(垂直翻转时是Y坐标，水平翻转时是X坐标)
    PathItem* mirrorItemHorizontal(qreal p, QGraphicsItem *parent = 0);
    PathItem* mirrorItemVertical(qreal p, QGraphicsItem *parent = 0);
    //克隆
    PathItem *cloneItem(const QPointF &pt, QGraphicsItem *parent = 0);
    //撤销
    void undo();
    //恢复
    void redo();
    //加入撤销集合
    void pushDataToUndoData(HistoryType type);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF );
    void moveEvent(QPointF );
    void releaseEvent();
    int pointid =0;

private:
    bool m_MousePressed = false;
    bool m_HasMoved = false;
    QPointF m_pMouseLastPoint;
    QPainterPath m_itempath;

    /* 橡皮擦使用 */
    QList<QPainterPath> m_SubPaths;

    /* 移动item使用 */
    QList<QGraphicsItem *> m_FullPathItems;     //当前pathItem所在路径包含的所有pathItem
    bool m_IsPushToHistory = false;

    QList<QVariant> m_pUndoData;              //撤销数据集合
    QList<HistoryType> m_pUndoType;           //撤销数据类型
    QList<QVariant> m_pRedoData;              //恢复数据集合
    QList<HistoryType> m_pRedoType;           //恢复数据类型

    QPainterPath getTransformPath(const QPainterPath &srcPath, QTransform *transform, const QPointF &center = QPointF());
    int pathshape =0;
    QPainterPath pathlist[11];

signals:
    void itemClicked(QGraphicsItem *);
    void itemChanged(QGraphicsItem *);
};

#endif // PATHITEM_H
