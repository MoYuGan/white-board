#ifndef CUSTOMITEM_PATH_H
#define CUSTOMITEM_PATH_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include "Public/publicfunction.h"

/*
 *  笔迹Item
*/

class CustomItem_Path : public QObject, public QGraphicsPathItem
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
    enum { Type = UserType + 99 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
public:
    CustomItem_Path(QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    //第一次绘图（一个完整的操作）结束后应该调用此函数初始化m_pItemPath用于保存当前路径
    void refreshPathSave(const QPainterPath &path);
    // 一个完整的绘图操作（鼠标按下到释放），包括旋转，缩放等后应该调用此函数将先前的路径m_pItemPath加入撤销集合，再刷新m_pItemPath为当前路径。
    void newActionFinished();
    void setPen(const QPen &pen);
    void setZValue(qreal z);
    //移动item
    void moveItem(const QPointF &pt);
    //旋转Item
    void rotateItem(const qreal &angle, const QPointF &center);
    //根据缩放因子缩放Item
    void scaleItemWithFactor(const qreal &xFactor, const qreal &yFactor, const QPointF &center);
    //根据长度缩放Item
    void scaleItemWithLength(qreal length, const QPointF &center);
    //翻转，参数一：翻转方向(0=水平，1=垂直)
    void flip(int direction, QPointF center);
    //镜像, 参数一：镜像方向(0=向上/向下，1=向左/向右)，参数二：向上向下翻转时是翻转线的Y坐标，向左向右翻转时是翻转线的X坐标
    void mirror(int direction, qreal p);
    //设置克隆模式，如果为真，移动item将变成克隆item
    void setClone(bool bo);
    inline bool isClone() { return m_pIsClone; }
    //克隆item，参数一：最近两个鼠标点之间X方向差值，参数二：最近两个鼠标点之间Y方向差值
    void toClone(qreal dx, qreal dy);
    //克隆完成
    void cloneFinished();
    //擦除完成
    QVector<QGraphicsItem *> eraserFinished();
    //撤销
    void undo();
    //恢复
    void redo();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
private:
    QPainterPath m_pItemPath;                   //用于保存item路径，当一个完整的绘图操作（鼠标按下到释放），包括旋转，缩放等后先将此路径加入撤销集合，再刷新此路径。
    bool m_pHasMouseMove = false;
    QPointF m_pMouseLastPoint;
    bool m_pIsClone = false;
    CustomItem_Path *m_pCloneItem = nullptr;
    QVector<QVariant> m_pUndoData;              //撤销数据集合
    QVector<HistoryType> m_pUndoType;           //撤销数据类型
    QVector<QVariant> m_pRedoData;              //恢复数据集合
    QVector<HistoryType> m_pRedoType;           //恢复数据类型
    QPointF m_pMousePressedPoint;
    QPainterPathStroker m_PathStroker;

    void pushDataToUndoData(QVariant variant, HistoryType type);

signals:
     void itemHasChanged(QGraphicsItem *);
     void itemSelected();
     void newItemCreated(QGraphicsItem *);
};


#endif // CUSTOMITEM_PATH_H
