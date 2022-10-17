#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsPathItem>
#include <QObject>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBitmap>
#include <QTouchEvent>
#include "Public/public_function.h"
#include "Extern/extern.h"

class GraphicsItem : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
public:
    //历史记录类型
    enum HistoryType {
        Path,       //路径改变
        Pen,        //画笔改变
        ZValue,     //图层级数改变
        Brush,      //填充色改变
        Erase       //擦除
    };

    /*自定义Type*/
    enum { Type = UserType + (int)((int)(ItemType::GraphicItem)) };
    int type() const { return Type; }

public:
    GraphicsItem(QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    bool is3DShape();
    void firstSetPen(const QPen &pen);
    void m_setPen(const QPen &pen);
    void firsetSetBrush(const QBrush &brush);
    void m_setBrush(const QBrush &brush);
    void m_setZValue(qreal z);
    void setSelected(bool selected);
    void setPath(QPainterPath ,QPainterPath =QPainterPath());

    void moveItem(const QPointF &pt);
    void rotateItem(const qreal &angle, const QPointF &center);
    void scaleItem(const qreal &xFactor, const qreal &yFactor, const QPointF &center);
    void getDrawPath(QPainterPath* ,QPainterPath* );

    void flipItemHorizontal(const QPointF &center);
    void flipItemVertical(const QPointF &center);
    //镜像, 参数一：翻转线，(垂直翻转时是Y坐标，水平翻转时是X坐标)
    GraphicsItem* mirrorItemHorizontal(qreal p);
    GraphicsItem* mirrorItemVertical(qreal p);
    GraphicsItem* cloneItem(const QPointF &pt);
    void getItemPath();

    void undo();
    void redo();
    void pushDataToUndoData(HistoryType type);

    void eraseWithPath(QPainterPath path);
    void eraseFinished();
    void setOrgErasePath(QList<QPainterPath> pathList);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF );
    void moveEvent(QPointF );
    void releaseEvent();
    int pointid =0;

private:
    bool m_pHasMouseMove = false;
    QPointF m_pMouseLastPoint;

    /* 橡皮擦使用 */
    bool m_EraseStart = false;
    QList<QList<QPainterPath>> m_ErasePathList; //橡皮擦擦除路径集合，可撤销
    QList<QPainterPath> m_OrgErasePathList;     //原有擦除路径集合，不可撤销
    QList<QList<QList<QPainterPath>>> m_UndoErasePathList;
    QList<QList<QList<QPainterPath>>> m_RedoErasePathList;
    QBitmap m_MaskBitmap = QBitmap();   //遮罩
    QPainterPath inpath;

    /* 移动item使用 */
    bool m_IsPushToHistory = false;

    QVector<QVariant> m_pUndoData;              //撤销数据集合
    QVector<HistoryType> m_pUndoType;           //撤销数据类型
    QVector<QVariant> m_pRedoData;              //恢复数据集合
    QVector<HistoryType> m_pRedoType;           //恢复数据类型

    QPainterPath getTransformPath(const QPainterPath &srcPath, QTransform transform, const QPointF &center = QPointF());
    QPainterPath m_itemoutpath;
    QPainterPath m_iteminpath;

signals:
    void itemClicked(QGraphicsItem *);
    void itemChanged(QGraphicsItem *);
};

#endif // GRAPHICSITEM_H
