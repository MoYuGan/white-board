#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPointF>
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsPixmapItem>
#include "Custom/GraphicsItem/customitem_path.h"
#include "Custom/GraphicsItem/customitem_pixmap.h"
#include "Public/publicfunction.h"
#include "Extern/extern.h"


class BoardScene : public QGraphicsScene
{
    Q_OBJECT
public:
    //历史操作类型
    enum HistoryType
    {
        NewItemAdd,         //新的item被添加
        ItemRemoved,        //item被移除
        ItemChanged,        //item有变动
        AddAndRemove,       //有多个item被添加，有多个item被移除(当橡皮擦擦除item时，如果路径被分割成多段，就会产生新的item，同时原来的item路径被移除)，添加和移除的item列表会先后加入撤销（恢复）集合
        RemoveAndAdd        //有多个item被移除，有多个item被添加, ，移除和添加的item列表会先后加入撤销（恢复）集合
    };

public:
    BoardScene(QObject* parent = 0);
    ~BoardScene();
    //添加Item
    void addItem(QGraphicsItem *item);
    //添加多个item
    void addItems(QVector<QGraphicsItem*> vector);
    //删除Item
    void deleteItems(QVector<QGraphicsItem*> vector);
    /* 绘图--路径 */
    void drawBegin();
    void drawPressed(int id, const QPointF &pt);
    void drawMove(int id, const QPointF &p1, const QPointF &p2);
    void drawReleased(int id, const QPointF &pt);
    void drawEnd();
    /* 橡皮擦 */
    void eraserPressed(const QPointF &pt);
    void eraserMove(const QPointF &p1, const QPointF &p2);
    void eraserReleased();
    //设置item是否可被选中
    void setItemsSelectable(bool bo);
    //撤消
    void undo();
    //恢复
    void redo();
    //
    void deleteAllItems();

private:
    QGraphicsPixmapItem *m_pEraserItem = nullptr;           //橡皮擦Item
    QMap<QGraphicsItem *, QVariant> m_pBeErasedItems;       //被擦除Items
    QVector<QGraphicsItem *> m_pTempChanged;                //临时更改集合
    QVector<QVector<QGraphicsItem*>> m_pUndoData;           //撤销Item集合
    QVector<HistoryType> m_pUndoType;                       //撤销数据类型
    QVector<QVector<QGraphicsItem*>> m_pRedoData;           //恢复Item集合
    QVector<HistoryType> m_pRedoType;                       //恢复数据类型
    QMap<int, QGraphicsItem*> m_pItemMap;                   //正在添加的Items

private:
    void eraserItems(const QPointF &lastPoint, const QPointF &curPoint);
    QVector<QLineF> getEraserPolygon(const QPointF &lastPos, const QPointF &currentPos, QPainterPath *eraserPath);
    QPainterPath getEraserSubPath(const QPainterPath &path, QVector<QLineF> lineVector, const QPainterPath &srcPath);
    void pushToUndoData(QVector<QGraphicsItem*> vector, HistoryType type);
    void pushToUndoData(QVector<QGraphicsItem*> vector1, QVector<QGraphicsItem*> vector2, HistoryType type);
};



#endif // BOARDSCENE_H
