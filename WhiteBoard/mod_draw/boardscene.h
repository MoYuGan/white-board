
#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPointF>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsPixmapItem>
#include <QThreadPool>

#include "ItemTool/itemtool.h"
#include "Public/public_function.h"
#include "Extern/extern.h"
#include "CustomGraphicsItem/ChiGui/customitem_zhichi.h"
#include "CustomGraphicsItem/ChiGui/customitem_dengyao.h"
#include "CustomGraphicsItem/ChiGui/customitem_liangjiaoqi.h"
#include "CustomGraphicsItem/ChiGui/customitem_yuangui.h"
#include "CustomGraphicsItem/ChiGui/customitem_zhijiao.h"
#include "CustomGraphicsItem/pathitem.h"
#include "CustomGraphicsItem/graphicsitem.h"
#include "CustomGraphicsItem/lineitem.h"
#include "CustomGraphicsItem/pixmapitem.h"
#include "CustomGraphicsItem/selectedrectitem.h"
#include "erasertask.h"

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
    PathItem *addPathItem(QPainterPath path = QPainterPath(),int num =0,int num1 =0,QGraphicsItem *parentItem = 0);
    PathItem *addMiniPathItem(QPainterPath path = QPainterPath(),int num =0,int num1 =0,QColor color=Qt::gray,QGraphicsItem *parentItem = 0);
    LineItem *addLineItem(const QLineF &line = QLine(), GraphicType type = GraphicType::ZhiXian);
    GraphicsItem *addGraphicItem(const QPainterPath &path = QPainterPath());
    PixmapItem *addPixmapItem(const QPixmap &pixmap, const QRect &pixmapRect,QString fileName =QString());
    void setSelectionAreaRect(const QRectF &rect);
    void clearSelection();
    void addTuAnPixmap(QPixmap ,QRect );

    // 获取场景图像
    QPixmap getSceneToPixmap();
    // 添加几何图形
    // void addGeometricStep1(int id, const QPointF &p1, const QPointF &p2);
    // void addGeometricStep2(int id, qreal height);
    // void addFanItem(int id, const QRectF &rect);
    // void addGraphicItemFinished();
    //将所有尺规item设置为顶层状态
    void stayChiguiItemOnTop(int zValue);
    //撤消
    void undo();
    //恢复
    void redo();
    //添加尺规
    void addChiGuiItem(int type);
    //擦除item，参数一：橡皮擦移动的多边形路径，参数二：橡皮擦item
    void eraseItems(QPainterPath erasePath, QGraphicsItem *item,int );
    //擦除完成
    void eraseFinished();
    int getMaxZValue();
    int getMinZValue();
    void pushToUndoData(QList<QGraphicsItem*> items, HistoryType type);
    bool isMouseInChiGuiItem(const QPointF &pressedPoint);

    /*记录当前场景包含的 item，不含新添加的*/
    QList<QGraphicsItem *> sceneitemlist;
    /*获取新添加的item集合*/
    QList<QGraphicsItem *> additemlist;

    QList<QPainterPath> itempathlist;

    void savePixmap(QPixmap );
    QPixmap getPixmap();

    //djf language change
    void updateLanguage();

public slots:
    void onItemClicked(QGraphicsItem *item);
    void onItemChanged(QGraphicsItem *item);
    void onSelectionChanged();
    void deleteSelectedItems();
    /*删除橡皮擦碰到的图形*/
    void deleteSelectedItems(QGraphicsItem *item);

    void deleteAllItems();
    void loadPicture(const QString &fileName);
    void loadPDFPixmap(const QPixmap &pixmap);
    void onBorderSizeChanged(int size);
    void onBorderColorChanged(QColor color);
    void onBorderLineChanged(Qt::PenStyle penstyle);
    void onFillColorChanged(QColor color);
    void onStayOnTop();
    void onStayOnBottom();
    void onFlipItems(int direction, const QPointF &center);
    void onMirrorItems(int direction, qreal p);
    void selectedItemsActionFinished();
    void onCloneItems(const QPointF &subPt);
    void selectHave3DShape(bool* );

    // 划线，尺规专用
    void drawLinePath(const QPointF &p1, const QPointF &p2);
    // 画圆，尺规专用
    void drawRoundPath(const QPointF &center, qreal r, qreal rotateStart, qreal rotateChanged);
    // 画线结束，尺规专用
    void drawLineFinished(const QPointF &p1, const QPointF &p2);
    // 画圆结束，尺规专用
    void drawRoundFinished(const QPointF &center, qreal r, qreal rotateStart, qreal rotateChanged);
    // 删除item，尺规专用
    void deleteChiGuiItem(QGraphicsItem *item);

private:
    /*撤销恢复*/
    QList<QList<QGraphicsItem*>> m_pUndoData;               //撤销Item集合
    QList<HistoryType> m_pUndoType;                         //撤销数据类型
    QList<QList<QGraphicsItem*>> m_pRedoData;               //恢复Item集合
    QList<HistoryType> m_pRedoType;                         //恢复数据类型

    /*尺规*/
    QList<QGraphicsItem *> m_pChiGuiItems;
    QMap<QObject*,QGraphicsItem*> m_mapTempItem;

    /*选择功能使用相关*/
    QList<QGraphicsItem*> m_SelectedItems;
    SelectedRectItem *m_selectedRectItem = nullptr;
    QList<QGraphicsItem *> m_CloneItems;

    /*橡皮擦使用相关*/
    QList<QGraphicsItem *> m_BeEraseItems;
    QList<EraserTask*> m_TaskList;


private:
    void setItemsSelected();
    //递归子item
    void recursiveChildItem(QList<QGraphicsItem*> *colldingItems,  QList<QGraphicsItem*> *pathItems, QGraphicsItem *parentItem);
    //递归父item
    void recursiveParentItem(QList<QGraphicsItem*> *colldingItems, QList<QGraphicsItem*> *pathItems, QGraphicsItem *childItem);

    void pushToUndoData(QList<QGraphicsItem*> vector1, QList<QGraphicsItem*> vector2, HistoryType type);

    QPixmap tabpixmap;

signals:
    void moveArcItemToScene(QPainterPath ,int ,QObject*);
    void moveLineItemToScene(QLineF ,int ,QObject* );
};



#endif // BOARDSCENE_H
