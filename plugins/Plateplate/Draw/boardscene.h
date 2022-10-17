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
#include "eraserthread.h"
#include "ItemTool/itemtool.h"
#include "Custom/GraphicsItem/customitem_path.h"
#include "Custom/GraphicsItem/customitem_pixmap.h"
#include "Custom/GraphicsItem/customitem_selectedrect.h"
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
    //设置橡皮擦大小
    void setEraserSize(const QSize &size);
    // 获取场景图像
    QPixmap getSceneToPixmap();
    /* 绘图--路径 */
    void drawBegin();
    void drawPressed(int id, const QPointF &pt);
    void drawMove(int id, const QPointF &p1, const QPointF &p2);
    void drawReleased(int id, const QPointF &pt);
    void drawEnd();
    /* 选择 */
    void dragPressed(const QPointF &pt);
    void dragMove(QRectF rect);
    void dragRelease();
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
    // 设置选中区域
    void setSelectionAreaRect(const QRectF &rect);
    //
    bool isMouseInSpecialItem(const QPointF &pressedPoint, int itemType = -1);

public slots:
    // item被选中/取消选中
    void onSelectionChanged();
    // 旋转选中items
    void rotateItems(const qreal &angle, const QPointF &center);
    // 旋转结束
    void onRotateItemsFinished();
    // 移动选中items
    void moveSelectedItems(const QPointF &subPt);
    // 移动所有item
    void moveAllItems(const QPointF &subPt);
    // 移动结束
    void onItemsActionFinished();
    // 缩放选中items
    void scaleSelectedItems(const qreal &xFactor, const qreal &yFactor, const QPointF &center);
    // 缩放所有Item，缩放中心为场景中心
    void scaleAllItems(qreal length, const QPointF &center = QPointF());
    // 克隆模式改变
    void onCloneModeChanged(bool);
    // 克隆选中items
    void cloneSelectedItems(qreal dx, qreal dy);
    // 克隆完成
    void onCloneFinished();
    // 选中items置顶
    void staySelectedItemsToTop();
    // 选中items置底
    void staySelectedItemsToBottom();
    // 删除选中items
    void deleteSelectedItems();
    // 删除所有Item
    void deleteAllItems();
    // 加载图片
    void loadPicture(const QString &fileName);
    // item发生改变
    void onItemHasChanged(QGraphicsItem *item);
    // 新的Item被创建，克隆/镜像时用，添加到当前场景
    void onNewItemCreated(QGraphicsItem *item);

private:
    QGraphicsRectItem *m_pDragRectItem = nullptr;           //拖动框Item
    QGraphicsPixmapItem *m_pEraserItem = nullptr;           //橡皮擦Item
    CustomItem_SelectedRect *m_pSelectedRectItem = nullptr; //选中框Item
    QMap<QGraphicsItem *, QVariant> m_pBeErasedItems;       //被擦除Items
    QVector<QGraphicsItem *> m_pTempChanged;                //临时更改集合
    QVector<QVector<QGraphicsItem*>> m_pUndoData;           //撤销Item集合
    QVector<HistoryType> m_pUndoType;                       //撤销数据类型
    QVector<QVector<QGraphicsItem*>> m_pRedoData;           //恢复Item集合
    QVector<HistoryType> m_pRedoType;                       //恢复数据类型
    QMap<int, QGraphicsItem*> m_pItemMap;                   //正在添加的Items
    bool m_pItemIsSelectable = false;                       //item是否可被选中
    CustomItem_Path *m_pTempItem = nullptr;                 //临时Item，尺规专用
    QVector<QGraphicsItem *> m_pChiGuiItems;

private:
    QRectF getSelectedIemsRect(bool *cloneMode);
    QRectF getSelectedIemsRect();
    void eraserItems(const QPointF &lastPoint, const QPointF &curPoint);
    QVector<QLineF> getEraserPolygon(const QPointF &lastPos, const QPointF &currentPos, QPainterPath *eraserPath);
    QPainterPath getEraserSubPath(const QPainterPath &path, QVector<QLineF> lineVector, const QPainterPath &srcPath);
    void pushToUndoData(QVector<QGraphicsItem*> vector, HistoryType type);
    void pushToUndoData(QVector<QGraphicsItem*> vector1, QVector<QGraphicsItem*> vector2, HistoryType type);
    int getMaxZValue();
    int getMinZValue();
};



#endif // BOARDSCENE_H
