#ifndef LINEITEM_H
#define LINEITEM_H

//#include <QObject>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include "Public/public_function.h"
#include "Extern/extern.h"
#include <QtMath>
#include <QTouchEvent>
#include "../Shape/Base/baseshapeobject.h"

class LineItem :  public QObject ,public QGraphicsLineItem
{
    Q_OBJECT
public:
    enum LineType {
        StraightLine,       //直线
        LineSegment,        //线段
        SingleArrow,        //单箭头
        DoubleArrow         //双箭头
    };

    //历史修改类型
    enum HistoryType {
        Line,       //修改了路径
        Pen,        //修改了画笔
        ZValue,     //修改了图层级数
        Erase
    };

    /*自定义Type*/
    enum { Type = UserType + (int)((int)(ItemType::LineItem)) };
    int type() const { return Type; }

public:
    LineItem(LineType type= LineType::StraightLine, QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void setLine(const QLineF &line);
    void firstSetPen(const QPen &pen);
    void m_setPen(const QPen &pen);
    void m_setZValue(qreal z);
    void setSelected(bool selected);
    inline LineType getLineType() { return m_LineType; }

    void updateFromRecord() {}

    //移动item
    void moveItem(const QPointF &pt);
    //旋转item
    void rotateItem(const qreal &angle, const QPointF &center);
    //缩放Item
    void scaleItem(const qreal &xFactor, const qreal &yFactor, const QPointF &center);
    void actionFinished();

    //翻转
    void flipItemHorizontal(const QPointF &center);
    void flipItemVertical(const QPointF &center);
    //镜像, 参数一：翻转线，(垂直翻转时是Y坐标，水平翻转时是X坐标)
    LineItem* mirrorItemHorizontal(qreal p);
    LineItem* mirrorItemVertical(qreal p);
    //克隆
    LineItem* cloneItem(const QPointF &pt);
    // 加入撤销集合
    void pushDataToUndoData(HistoryType type);
    //撤销
    void undo();
    //恢复
    void redo();

    void eraseWithPath(QPainterPath path);
    void eraseFinished();
    void setOrgErasePath(QList<QPainterPath> pathList);
    void getItemLine();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF );
    void moveEvent(QPointF );
    void releaseEvent();
    int pointid =0;

private:
    QPainterPath m_LinePath;
    QPointF m_pMouseLastPoint;
    bool m_pHasMouseMove = false;
    LineType m_LineType;
    QVector<QVariant> m_pUndoData;              //撤销数据集合
    QVector<HistoryType> m_pUndoType;           //撤销数据类型
    QVector<QVariant> m_pRedoData;              //恢复数据集合
    QVector<HistoryType> m_pRedoType;           //恢复数据类型
    QPointF m_pMousePressedPoint;
    bool m_IsPushToHistory = false;
    bool m_ActionStart = false;
    QLineF m_itemline;

    /* 橡皮擦使用 */
    bool m_EraseStart = false;
    QList<QList<QPainterPath>> m_ErasePathList; //橡皮擦擦除路径集合，可撤销
    QList<QPainterPath> m_OrgErasePathList;     //原有擦除路径集合，不可撤销
    QList<QList<QList<QPainterPath>>> m_UndoErasePathList;
    QList<QList<QList<QPainterPath>>> m_RedoErasePathList;

private:
    //获取单箭头线
    QPainterPath getArrow(QLineF line, int penWidth);
    //获取双箭头线
    QPainterPath getDoubleArrow(QLineF line, int penWidth);
    //获取线段
    QPainterPath getLineSegment(QLineF line);

    QLineF getTransformLine(const QLineF &srcLine, QTransform *transform, const QPointF &center = QPointF());
    QPainterPath getTransformPath(const QPainterPath &srcPath, QTransform *transform, const QPointF &center);

signals:
    void itemClicked(QGraphicsItem *);
    void itemChanged(QGraphicsItem *);
};

#endif // LINEITEM_H
