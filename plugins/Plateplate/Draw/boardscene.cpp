#include "boardscene.h"
#include <QtDebug>
#include <QTouchEvent>
#include <QPainter>
#include <QPixmapCache>
#include <QPainterPathStroker>
#include <QDateTime>
#include <QGraphicsPathItem>
#include <QTransform>
#include <QMatrix>
#include <math.h>
#include <QGraphicsProxyWidget>
#include <QDebug>

BoardScene::BoardScene(QObject *parent) :
    QGraphicsScene(parent)
{
    QPixmapCache::setCacheLimit(204800);
    this->installEventFilter(this);

    connect(this, &BoardScene::selectionChanged, this, &BoardScene::onSelectionChanged);
    m_pUndoData.clear();
    m_pUndoType.clear();
    m_pRedoData.clear();
    m_pRedoType.clear();
}

BoardScene::~BoardScene()
{}

void BoardScene::addItem(QGraphicsItem *item)
{
    QVector<QGraphicsItem*> vector;
    vector.push_back(item);
    this->pushToUndoData(vector, HistoryType::NewItemAdd);
    item->setFlag(QGraphicsItem::ItemIsSelectable, m_pItemIsSelectable);
    QGraphicsScene::addItem(item);
}

void BoardScene::addItems(QVector<QGraphicsItem *> vector)
{
    if (0 == vector.size())
        return;

    this->pushToUndoData(vector, HistoryType::NewItemAdd);
    foreach(QGraphicsItem *item, vector) {
        item->setFlag(QGraphicsItem::ItemIsSelectable, m_pItemIsSelectable);
        QGraphicsScene::addItem(item);
    }
}

void BoardScene::deleteItems(QVector<QGraphicsItem *> vector)
{
    if (0 == vector.size())
        return;

    this->pushToUndoData(vector, HistoryType::ItemRemoved);
    disconnect(this, &BoardScene::selectionChanged, this, &BoardScene::onSelectionChanged);
    for (int i = 0; i < vector.size(); i++) {
        this->removeItem(vector.at(i));
    }
    connect(this, &BoardScene::selectionChanged, this, &BoardScene::onSelectionChanged);
}

QPixmap BoardScene::getSceneToPixmap()
{
    QPixmap pixmap(this->width(), this->height());
    QPainter painter;
    painter.begin(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    this->render(&painter, QRectF(), QRectF(), Qt::IgnoreAspectRatio);
    painter.end();
    return pixmap;
}

void BoardScene::drawBegin()
{
    //清空临时更改集合
    m_pTempChanged.clear();
}

void BoardScene::drawPressed(int id, const QPointF &pt)
{
    Q_UNUSED(pt)

    CustomItem_Path *item = new CustomItem_Path;
    connect(item, &CustomItem_Path::itemHasChanged, this, &BoardScene::onItemHasChanged);
    connect(item, &CustomItem_Path::itemSelected, this, [=](){ this->clearSelection(); }, Qt::DirectConnection);
    connect(item, &CustomItem_Path::newItemCreated, this, &BoardScene::onNewItemCreated, Qt::DirectConnection);
    item->setPen(QPen(e_PenColor, e_PenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    item->setZValue(this->getMaxZValue() + 1);
    QGraphicsScene::addItem(item);

    m_pItemMap.insert(id, item);
}

void BoardScene::drawMove(int id, const QPointF &p1, const QPointF &p2)
{
    CustomItem_Path *item = static_cast<CustomItem_Path*>(m_pItemMap.value(id, nullptr));
    if (!item)
        return;

    QPainterPath path = item->path();
    if (0 == path.elementCount())
        path.moveTo(p1);
    QPointF pt = p2 - p1;
    if (qAbs(pt.x()) > 0 || qAbs(pt.y()) > 0)
        path.quadTo(p1, (p1 + p2)/2);

    item->setPath(PublicFunction::cubToLine(path));
}

void BoardScene::drawReleased(int id, const QPointF &pt)
{
    CustomItem_Path *item = static_cast<CustomItem_Path*>(m_pItemMap.value(id, nullptr));
    if (!item)
        return;

    QPainterPath path = item->path();
    if (0 == path.elementCount()) {
        qreal radius = item->pen().width();
        path.addEllipse(QRectF(pt.x() - radius/2.0, pt.y() - radius/2.0, radius, radius));
        item->setBrush(QBrush(item->pen().color()));
        item->setPath(path);
    }
    m_pTempChanged.push_back(item);
    m_pItemMap.remove(id);
}

void BoardScene::drawEnd()
{
    foreach(QGraphicsItem *item, m_pTempChanged) {
        CustomItem_Path *pathitem = static_cast<CustomItem_Path*>(item);
        pathitem->refreshPathSave(pathitem->path());
    }
    this->pushToUndoData(m_pTempChanged, HistoryType::NewItemAdd);
}

void BoardScene::dragPressed(const QPointF &pt)
{
    m_pDragRectItem = new QGraphicsRectItem;
    m_pDragRectItem->setRect(QRectF());
    m_pDragRectItem->setPen(QPen(QBrush(QColor(255,168,0)), PublicFunction::getScaleSize(2),
                             Qt::DashLine, Qt::SquareCap, Qt::RoundJoin));
    m_pDragRectItem->setBrush(QBrush(QColor(255, 200, 0, 50)));
    m_pDragRectItem->setZValue(this->getMaxZValue() + 1);
    QGraphicsScene::addItem(m_pDragRectItem);
}

void BoardScene::dragMove(QRectF rect)
{
    if (nullptr != m_pDragRectItem) {
        m_pDragRectItem->setRect(rect);
        this->update();
    }
}

void BoardScene::dragRelease()
{
    if (nullptr != m_pDragRectItem) {
        QRectF rect = m_pDragRectItem->rect();
        this->setSelectionAreaRect(rect);
        delete m_pDragRectItem;
        m_pDragRectItem = nullptr;
        this->update();
    }
}

void BoardScene::eraserPressed(const QPointF &pt)
{
    m_pBeErasedItems.clear();

    m_pEraserItem = new QGraphicsPixmapItem;
    QPixmap pixmap = QPixmap(":/images/cachuzhuangtai@2x.png").scaled(e_EraserSize);
    pixmap.setDevicePixelRatio(1);
    m_pEraserItem->setPixmap(pixmap);
    m_pEraserItem->setOffset(QPointF(pt.x() - pixmap.width()/2.0,
                                     pt.y() - pixmap.height()/2.0));
    m_pEraserItem->setZValue(this->getMaxZValue() + 1);
    QGraphicsScene::addItem(m_pEraserItem);
    this->eraserItems(pt, pt);
}

void BoardScene::eraserMove(const QPointF &p1, const QPointF &p2)
{
    if (nullptr != m_pEraserItem) {
        m_pEraserItem->setOffset(QPointF(p2.x() - m_pEraserItem->boundingRect().width()/2.0,
                                         p2.y() - m_pEraserItem->boundingRect().height()/2.0));
        this->eraserItems(p1, p2);
    }
}

void BoardScene::eraserReleased()
{
    if (nullptr == m_pEraserItem)
        return;

    QVector<QGraphicsItem*> addItemList;
    QVector<QGraphicsItem*> removeItemList;
    foreach(QGraphicsItem *item, m_pBeErasedItems.keys()) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            QVector<QGraphicsItem *> itemList = pathItem->eraserFinished();
            this->removeItem(pathItem);
            removeItemList.push_back(pathItem);
            foreach(QGraphicsItem *newItem, itemList) {
                QGraphicsScene::addItem(newItem);
                addItemList.push_back(newItem);
            }
        }else if ((QGraphicsItem::UserType + 100) == item->type() ||
                  (QGraphicsItem::UserType + 101) == item->type()) {
            removeItemList.push_back(item);
        }
    }

    this->pushToUndoData(addItemList, removeItemList, HistoryType::AddAndRemove);

    this->removeItem(m_pEraserItem);
    delete m_pEraserItem;
    m_pEraserItem = nullptr;
}

void BoardScene::undo()
{
    if (0 == m_pUndoType.size())
        return;

    if (nullptr != m_pSelectedRectItem) {
        this->clearSelection();
    }

    switch(m_pUndoType.last()) {
    case HistoryType::NewItemAdd: {
        QVector<QGraphicsItem *> items = m_pUndoData.last();
        m_pRedoData.push_back(items);
        m_pRedoType.push_back(HistoryType::ItemRemoved);
        foreach(QGraphicsItem *item, items) {
            this->removeItem(item);
        }
    }break;
    case HistoryType::ItemRemoved: {
        QVector<QGraphicsItem *> items = m_pUndoData.last();
        m_pRedoData.push_back(items);
        m_pRedoType.push_back(HistoryType::NewItemAdd);
        foreach(QGraphicsItem *item, items) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, m_pItemIsSelectable);
            //addItem已经重写，应该调用默认的addItem函数，避免重复添加撤销集合以及出现其他错误
            QGraphicsScene::addItem(item);
        }
    }break;
    case HistoryType::ItemChanged: {
        QVector<QGraphicsItem *> items = m_pUndoData.last();
        m_pRedoData.push_back(items);
        m_pRedoType.push_back(HistoryType::ItemChanged);
        foreach(QGraphicsItem *item, items) {
            if ((QGraphicsItem::UserType + 99) == item->type()) {
                CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
                pathItem->undo();
            }else if ((QGraphicsItem::UserType + 102) == item->type()) {
                CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
                pixmapItem->undo();
            }
        }
    }break;
    case HistoryType::AddAndRemove: {
        QVector<QGraphicsItem *> removeitems = m_pUndoData.last();
        m_pUndoData.pop_back();
        QVector<QGraphicsItem *> additems = m_pUndoData.last();
        m_pRedoData.push_back(additems);
        m_pRedoData.push_back(removeitems);
        m_pRedoType.push_back(HistoryType::RemoveAndAdd);
        foreach(QGraphicsItem *item, additems) {
            this->removeItem(item);
        }
        foreach(QGraphicsItem *item, removeitems) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, m_pItemIsSelectable);
            QGraphicsScene::addItem(item);
        }

    }break;
    case HistoryType::RemoveAndAdd: {
        QVector<QGraphicsItem *> additems = m_pUndoData.last();
        m_pUndoData.pop_back();
        QVector<QGraphicsItem *> removeitems = m_pUndoData.last();
        m_pRedoData.push_back(removeitems);
        m_pRedoData.push_back(additems);
        m_pRedoType.push_back(HistoryType::AddAndRemove);
        foreach(QGraphicsItem *item, additems) {
            this->removeItem(item);
        }
        foreach(QGraphicsItem *item, removeitems) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, m_pItemIsSelectable);
            QGraphicsScene::addItem(item);
        }
    }break;
    default:
        break;
    }
    m_pUndoData.pop_back();
    m_pUndoType.pop_back();
    this->update();
}

void BoardScene::redo()
{
    if (0 == m_pRedoType.size())
        return;

    if (nullptr != m_pSelectedRectItem) {
        this->clearSelection();
    }

    switch(m_pRedoType.last()) {
    case HistoryType::NewItemAdd: {
        QVector<QGraphicsItem *> items = m_pRedoData.last();
        m_pUndoData.push_back(items);
        m_pUndoType.push_back(HistoryType::ItemRemoved);
        foreach(QGraphicsItem *item, items) {
            this->removeItem(item);
        }
    }break;
    case HistoryType::ItemRemoved: {
        QVector<QGraphicsItem *> items = m_pRedoData.last();
        m_pUndoData.push_back(items);
        m_pUndoType.push_back(HistoryType::NewItemAdd);
        foreach(QGraphicsItem *item, items) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, m_pItemIsSelectable);
            //addItem已经重写，应该调用默认的addItem函数，避免重复添加撤销集合以及出现其他错误
            QGraphicsScene::addItem(item);
        }
    }break;
    case HistoryType::ItemChanged: {
        QVector<QGraphicsItem *> items = m_pRedoData.last();
        m_pUndoData.push_back(items);
        m_pUndoType.push_back(HistoryType::ItemChanged);
        foreach(QGraphicsItem *item, items) {
            if ((QGraphicsItem::UserType + 99) == item->type()) {
                CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
                pathItem->redo();
            }else if ((QGraphicsItem::UserType + 102) == item->type()) {
                CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
                pixmapItem->redo();
            }
        }
    }break;
    case HistoryType::AddAndRemove: {
        QVector<QGraphicsItem *> removeitems = m_pRedoData.last();
        m_pRedoData.pop_back();
        QVector<QGraphicsItem *> additems = m_pRedoData.last();
        m_pUndoData.push_back(additems);
        m_pUndoData.push_back(removeitems);
        m_pUndoType.push_back(HistoryType::RemoveAndAdd);
        foreach(QGraphicsItem *item, removeitems) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, m_pItemIsSelectable);
            QGraphicsScene::addItem(item);
        }
        foreach(QGraphicsItem *item, additems) {
            this->removeItem(item);
        }
    }break;
    case HistoryType::RemoveAndAdd: {
        QVector<QGraphicsItem *> additems = m_pRedoData.last();
        m_pRedoData.pop_back();
        QVector<QGraphicsItem *> removeitems = m_pRedoData.last();
        m_pUndoData.push_back(removeitems);
        m_pUndoData.push_back(additems);
        m_pUndoType.push_back(HistoryType::AddAndRemove);
        foreach(QGraphicsItem *item, additems) {
            this->removeItem(item);
        }
        foreach(QGraphicsItem *item, removeitems) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, m_pItemIsSelectable);
            QGraphicsScene::addItem(item);
        }
    }break;
    default:
        break;
    }
    m_pRedoData.pop_back();
    m_pRedoType.pop_back();
    this->update();
}

void BoardScene::setSelectionAreaRect(const QRectF &rect)
{
    QPainterPath path;
    path.addRect(rect);
    //设置可选择区域之前，先把尺规enabled设置为false，否则会被选中
    foreach(QGraphicsItem *item, m_pChiGuiItems)
        item->setEnabled(false);
    this->setSelectionArea(path);
    foreach(QGraphicsItem *item, m_pChiGuiItems)
        item->setEnabled(true);
}

bool BoardScene::isMouseInSpecialItem(const QPointF &pressedPoint, int itemType)
{
    QGraphicsItem *item  = this->itemAt(pressedPoint, QTransform());
    if (-1 == itemType) {   //任意Item上面
        if (nullptr != item)
            return true;
        else
            return false;
    }else { //特殊itemType的item上面
        if (item != nullptr && itemType == item->type())
            return true;
        else
            return false;
    }
}

void BoardScene::onSelectionChanged()
{
    if (nullptr != m_pSelectedRectItem) {
        this->removeItem(m_pSelectedRectItem);
        delete m_pSelectedRectItem;
        m_pSelectedRectItem = nullptr;
    }

    QList<QGraphicsItem *> itemList = this->selectedItems();
    if (0 == itemList.size())
        return;

    bool isClone = false;
    QRectF rect = this->getSelectedIemsRect(&isClone);
    if (!rect.isEmpty()) {
        m_pSelectedRectItem = new CustomItem_SelectedRect;
        int margin = PublicFunction::getScaleSize(2);
        m_pSelectedRectItem->setRect(QRectF(QPointF(rect.topLeft().x() - margin, rect.topLeft().y() - margin),
                                            QPointF(rect.bottomRight().x() + margin, rect.bottomRight().y() + margin)));
    }

    m_pSelectedRectItem->setZValue(this->getMaxZValue() + 1);
    if (nullptr != m_pSelectedRectItem) {
        m_pSelectedRectItem->createTool(isClone);
        QGraphicsScene::addItem(m_pSelectedRectItem);
        connect(m_pSelectedRectItem, SIGNAL(actionRotate(qreal,QPointF)), this, SLOT(rotateItems(qreal,QPointF)), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(actionRotateFinished()), this, SLOT(onRotateItemsFinished()),  Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(actionMove(QPointF)), this, SLOT(moveSelectedItems(QPointF)), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(actionScale(qreal,qreal,QPointF)), this, SLOT(scaleSelectedItems(qreal,qreal,QPointF)), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(actionScaleFinished()), this, SLOT(onRotateItemsFinished()), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(actionFinished()), this, SLOT(onItemsActionFinished()), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(cloneModeChanged(bool)), this, SLOT(onCloneModeChanged(bool)), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(toClone(qreal,qreal)), this, SLOT(cloneSelectedItems(qreal,qreal)), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(cloneFinished()), this, SLOT(onCloneFinished()), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(stayTop()), this, SLOT(staySelectedItemsToTop()), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(stayBottom()), this, SLOT(staySelectedItemsToBottom()), Qt::DirectConnection);
        connect(m_pSelectedRectItem, SIGNAL(toDelete()), this, SLOT(deleteSelectedItems()), Qt::DirectConnection);
    }
}

void BoardScene::rotateItems(const qreal &angle, const QPointF &center)
{
    QList<QGraphicsItem*> itemList = this->selectedItems();
    foreach(QGraphicsItem *item, itemList) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->rotateItem(angle, center);
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->rotateItem(angle, center);
        }
    }

    this->update();
}

void BoardScene::onRotateItemsFinished()
{
    qDebug()<<"rotate finished";
    // 加入撤销集合
    QList<QGraphicsItem*> itemList = this->selectedItems();
    foreach(QGraphicsItem* item, itemList) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->newActionFinished();
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->actionFinished();
        }
    }
    this->pushToUndoData(itemList.toVector(), HistoryType::ItemChanged);

    QRectF rect = this->getSelectedIemsRect();
    if (!rect.isEmpty()) {
        int margin = PublicFunction::getScaleSize(2);
        m_pSelectedRectItem->setRect(QRectF(QPointF(rect.topLeft().x() - margin, rect.topLeft().y() - margin),
                                        QPointF(rect.bottomRight().x() + margin, rect.bottomRight().y() + margin)));
    }
}

void BoardScene::moveSelectedItems(const QPointF &subPt)
{
    foreach(QGraphicsItem *item, this->selectedItems()) {
        if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->moveItem(subPt);
        }else if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->moveItem(subPt);
        }
    }
    this->update();
}

void BoardScene::moveAllItems(const QPointF &subPt)
{
    foreach(QGraphicsItem *item, this->items()) {
        if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->moveItem(subPt);
        }else if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->moveItem(subPt);
        }
    }
    this->update();
}

void BoardScene::onItemsActionFinished()
{
    // 加入撤销集合
    QList<QGraphicsItem*> itemList = this->selectedItems();
    foreach(QGraphicsItem* item, itemList) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->newActionFinished();
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->actionFinished();
        }
    }
    this->pushToUndoData(itemList.toVector(), HistoryType::ItemChanged);
}

void BoardScene::scaleSelectedItems(const qreal &xFactor, const qreal &yFactor, const QPointF &center)
{
    foreach(QGraphicsItem *item, this->selectedItems()) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->scaleItemWithFactor(xFactor, yFactor, center);
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->scaleItemWithFactor(xFactor, yFactor, center);
        }
    }
    this->update();
}

void BoardScene::scaleAllItems(qreal length, const QPointF &center)
{
    QPointF scaleCenter;
    if (center.isNull())
        scaleCenter = this->sceneRect().center();
    else
        scaleCenter = center;
    foreach(QGraphicsItem *item, this->items()) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->scaleItemWithLength(length, scaleCenter);
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->scaleItemWithLength(length, scaleCenter);
        }
    }
    this->update();
}

void BoardScene::onCloneModeChanged(bool bo)
{
    foreach(QGraphicsItem *item, this->selectedItems()) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {              //图形
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->setClone(bo);
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {        //线条图形
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->setClone(bo);
        }
    }
}

void BoardScene::cloneSelectedItems(qreal dx, qreal dy)
{
    foreach(QGraphicsItem *item, this->selectedItems()) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {              //图形
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->toClone(dx, dy);
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {        //线条图形
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->toClone(dx, dy);
        }
    }
}

void BoardScene::onCloneFinished()
{
    foreach(QGraphicsItem *item, this->selectedItems()) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {              //图形
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->cloneFinished();
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {        //线条图形
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->cloneFinished();
        }
    }
}

void BoardScene::staySelectedItemsToTop()
{
    int maxZValue = this->getMaxZValue();

    QList<QGraphicsItem*> selectItemList = this->selectedItems();
    foreach(QGraphicsItem *item, selectItemList) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->setZValue(maxZValue + 1);
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->setZValue(maxZValue + 1);
            pixmapItem->actionFinished();
        }
    }

    if (m_pSelectedRectItem != nullptr)
        m_pSelectedRectItem->setZValue(maxZValue + 2);

    for(int i = 0; i < m_pChiGuiItems.size(); ) {
        m_pChiGuiItems.at(i)->setZValue(maxZValue + 3 + (++i));
    }

    // 加入撤销集合
    this->pushToUndoData(selectItemList.toVector(), HistoryType::ItemChanged);
}

void BoardScene::staySelectedItemsToBottom()
{
    int minZValue = this->getMinZValue() + 1;

    QList<QGraphicsItem*> selectItemList = this->selectedItems();
    foreach(QGraphicsItem *item, selectItemList) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            pathItem->setZValue(minZValue - 1);
        }else if ((QGraphicsItem::UserType + 102) == item->type()) {
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            pixmapItem->setZValue(minZValue - 1);
            pixmapItem->actionFinished();
        }
    }

    // 加入撤销集合
    this->pushToUndoData(selectItemList.toVector(), HistoryType::ItemChanged);
}

void BoardScene::deleteSelectedItems()
{
    QList<QGraphicsItem *> itemList = this->selectedItems();
    this->deleteItems(itemList.toVector());
    if (nullptr != m_pSelectedRectItem) {
        this->removeItem(m_pSelectedRectItem);
        m_pSelectedRectItem->deleteLater();
        m_pSelectedRectItem = nullptr;
    }
}

void BoardScene::deleteAllItems()
{
    if (nullptr != m_pSelectedRectItem) {
        this->removeItem(m_pSelectedRectItem);
        delete m_pSelectedRectItem;
        m_pSelectedRectItem = nullptr;
    }
    this->deleteItems(this->items().toVector());
}

void BoardScene::setItemsSelectable(bool bo)
{
    m_pItemIsSelectable = bo;
    foreach(QGraphicsItem* item, this->items()) {
        if ((QGraphicsItem::UserType + 108) != item->type())
            item->setFlag(QGraphicsItem::ItemIsSelectable, bo);
        else if ((QGraphicsItem::UserType + 99) != item->type())
            item->setFlag(QGraphicsItem::ItemIsSelectable, bo);
        else if ((QGraphicsItem::UserType + 102) != item->type())
            item->setFlag(QGraphicsItem::ItemIsSelectable, bo);
    }
}

void BoardScene::loadPicture(const QString &fileName)
{ 
    QPixmap pixmap;
    pixmap.load(fileName);
    QSize size = PublicFunction::getScaleSize(QSize(800, 800));
    //图片宽或高超出size的宽或高，缩放图片
    int scaleW;
    int scaleH;
    if (pixmap.width() > size.width() || pixmap.height() > size.height()) {
        scaleW = size.width();
        scaleH = size.height();
        qreal dpW = (qreal)pixmap.width()/(qreal)size.width();
        qreal dpH = (qreal)pixmap.height()/(qreal)size.height();
        dpW > dpH ? (scaleH = pixmap.height()/dpW) : (scaleW = pixmap.width()/dpH);
    }else {
        scaleW = pixmap.width();
        scaleH = pixmap.height();
    }
    CustomItem_Pixmap *item = new CustomItem_Pixmap;
    connect(item, &CustomItem_Pixmap::itemHasChanged, this, &BoardScene::onItemHasChanged);
    connect(item, &CustomItem_Pixmap::itemSelected, this, [=](){ this->clearSelection(); }, Qt::DirectConnection);
    connect(item, &CustomItem_Pixmap::newItemCreated, this, &BoardScene::onNewItemCreated, Qt::DirectConnection);
    if (m_pItemIsSelectable)
        item->setFlag(QGraphicsItem::ItemIsSelectable, true);

    QRect pixmapRect = QRect(0, 0, scaleW, scaleH);
    pixmapRect.moveCenter(this->sceneRect().center().toPoint());
    item->setPixmap(pixmap, pixmapRect);
    item->setZValue(this->getMaxZValue() + 1);
    this->addItem(item);
}

void BoardScene::onItemHasChanged(QGraphicsItem *item)
{
    QVector<QGraphicsItem*> vector;
    vector.push_back(item);
    this->pushToUndoData(vector, HistoryType::ItemChanged);
}


void BoardScene::onNewItemCreated(QGraphicsItem *item)
{
    item->setZValue(this->getMaxZValue() + 1);
    if ((QGraphicsItem::UserType + 99) == item->type()) {
        CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
        connect(pathItem, &CustomItem_Path::itemHasChanged, this, &BoardScene::onItemHasChanged);
        connect(pathItem, &CustomItem_Path::itemSelected, this, [=](){ this->clearSelection(); }, Qt::DirectConnection);
        connect(pathItem, &CustomItem_Path::newItemCreated, this, &BoardScene::onNewItemCreated, Qt::DirectConnection);
    }else if ((QGraphicsItem::UserType + 102) == item->type()) {
        CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
        connect(pixmapItem, &CustomItem_Pixmap::itemHasChanged, this, &BoardScene::onItemHasChanged);
        connect(pixmapItem, &CustomItem_Pixmap::itemSelected, this, [=](){ this->clearSelection(); }, Qt::DirectConnection);
        connect(pixmapItem, &CustomItem_Pixmap::newItemCreated, this, &BoardScene::onNewItemCreated, Qt::DirectConnection);
    }
    this->addItem(item);
}



/* 返回选中items的最小矩形框，并返回需要移除的工具，画笔，填充色，是否开启克隆模式 */
QRectF BoardScene::getSelectedIemsRect(bool *cloneMode)
{
    QList<QGraphicsItem*> itemList = this->selectedItems();
    if (0 == itemList.size())
        return QRectF();
    QPointF topLeft;
    QPointF bottomRight;
    QRectF rect;
    int count = 0;
    bool isClone = true;
    foreach(QGraphicsItem *item, itemList) {
        rect = item->boundingRect();
        if (0 == count) {
            topLeft = rect.topLeft();
            bottomRight = rect.bottomRight();
            count++;
        }else {
            if (topLeft.x() > rect.topLeft().x())
                topLeft.setX(rect.topLeft().x());
            if (topLeft.y() > rect.topLeft().y())
                topLeft.setY(rect.topLeft().y());
            if (bottomRight.x() < rect.bottomRight().x())
                bottomRight.setX(rect.bottomRight().x());
            if (bottomRight.y() < rect.bottomRight().y())
                bottomRight.setY(rect.bottomRight().y());
        }

        if ((QGraphicsItem::UserType + 102) == item->type()) {        //图片
            CustomItem_Pixmap *pixmapItem = static_cast<CustomItem_Pixmap*>(item);
            if (!pixmapItem->isClone())
                isClone = false;
        }else if ((QGraphicsItem::UserType + 99) == item->type()) {         //笔迹
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            if (!pathItem->isClone())
                isClone = false;
        }
    }

    *cloneMode = isClone;
    return QRectF(topLeft, bottomRight);
}

/* 返回选中items的最小矩形框 */
QRectF BoardScene::getSelectedIemsRect()
{
    QList<QGraphicsItem*> itemList = this->selectedItems();
    if (0 == itemList.size())
        return QRectF();

    QPointF topLeft;
    QPointF bottomRight;
    QRectF rect;
    int count = 0;
    foreach(QGraphicsItem *item, itemList) {
        rect = item->boundingRect();
        if (0 == count) {
            topLeft = rect.topLeft();
            bottomRight = rect.bottomRight();
            count++;
        }else {
            if (topLeft.x() > rect.topLeft().x())
                topLeft.setX(rect.topLeft().x());
            if (topLeft.y() > rect.topLeft().y())
                topLeft.setY(rect.topLeft().y());
            if (bottomRight.x() < rect.bottomRight().x())
                bottomRight.setX(rect.bottomRight().x());
            if (bottomRight.y() < rect.bottomRight().y())
                bottomRight.setY(rect.bottomRight().y());
        }
    }

    return QRectF(topLeft, bottomRight);
}

/* 擦除Item */
void BoardScene::eraserItems(const QPointF &lastPoint, const QPointF &curPoint)
{
    QVector<QLineF> eraserLines;
    QPainterPath eraserPath;
    eraserLines = this->getEraserPolygon(lastPoint, curPoint, &eraserPath);

    foreach(QGraphicsItem *item, m_pEraserItem->collidingItems()) {
        if ((QGraphicsItem::UserType + 99) == item->type()) {
            CustomItem_Path *pathItem = static_cast<CustomItem_Path*>(item);
            //加入临时更改集合
            if (!m_pBeErasedItems.contains(pathItem)) {
                QVariant variant;
                variant.setValue(pathItem->path());
                m_pBeErasedItems.insert(pathItem, variant);
            }

            CustomItem_Path *pathitem = static_cast<CustomItem_Path*> (item);
            pathitem->setPath(this->getEraserSubPath(eraserPath, eraserLines, pathItem->path()));
        }else if ((QGraphicsItem::UserType + 100) == item->type() ||
                  (QGraphicsItem::UserType + 101) == item->type()) {
            this->removeItem(item);
            m_pBeErasedItems.insert(item, QVariant());
        }
    }
}

/* 获取橡皮擦移动时的多边形区域 */
QVector<QLineF> BoardScene::getEraserPolygon(const QPointF &lastPos, const QPointF &currentPos , QPainterPath *eraserPath) {
    QVector<QLineF> eraserLines;
    QPainterPath path;
    int subX = lastPos.x() - currentPos.x();
    int subY = lastPos.y() - currentPos.y();
    QRectF lastEraserRect = m_pEraserItem->boundingRect();
    lastEraserRect.moveCenter(lastPos);
    QRectF currentEraserRect = m_pEraserItem->boundingRect();
    currentEraserRect.moveCenter(currentPos);
    if (subX < 0 && subY < 0) {
        path.moveTo(lastEraserRect.topLeft());
        path.lineTo(lastEraserRect.topRight());
        path.lineTo(currentEraserRect.topRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.lineTo(currentEraserRect.bottomLeft());
        path.lineTo(lastEraserRect.bottomLeft());
        path.closeSubpath();
        //记录多边形的每一条边
        eraserLines.push_back(QLineF(lastEraserRect.topLeft(), lastEraserRect.topRight()));
        eraserLines.push_back(QLineF(lastEraserRect.topRight(), currentEraserRect.topRight()));
        eraserLines.push_back(QLineF(currentEraserRect.topRight(), currentEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomRight(), currentEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomLeft(), lastEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomLeft(), lastEraserRect.topLeft()));
    }else if (subX < 0 && subY > 0) {
        path.moveTo(lastEraserRect.topLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.lineTo(currentEraserRect.topRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.lineTo(lastEraserRect.bottomLeft());
        path.closeSubpath();

        //记录多边形的每一条边
        eraserLines.push_back(QLineF(lastEraserRect.topLeft(), currentEraserRect.topLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.topLeft(), currentEraserRect.topRight()));
        eraserLines.push_back(QLineF(currentEraserRect.topRight(), currentEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomRight(), lastEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomRight(), lastEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomLeft(), lastEraserRect.topLeft()));
    }else if (subX > 0 && subY > 0) {
        path.moveTo(lastEraserRect.topRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.lineTo(lastEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.lineTo(currentEraserRect.topRight());
        path.closeSubpath();

        //记录多边形的每一条边
        eraserLines.push_back(QLineF(lastEraserRect.topRight(), lastEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomRight(), lastEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomLeft(), currentEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomLeft(), currentEraserRect.topLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.topLeft(), currentEraserRect.topRight()));
        eraserLines.push_back(QLineF(currentEraserRect.topRight(), lastEraserRect.topRight()));
    }else if (subX > 0 && subY < 0) {
        path.moveTo(lastEraserRect.topLeft());
        path.lineTo(lastEraserRect.topRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.lineTo(currentEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.closeSubpath();

        //记录多边形的每一条边
        eraserLines.push_back(QLineF(lastEraserRect.topLeft(), lastEraserRect.topRight()));
        eraserLines.push_back(QLineF(lastEraserRect.topRight(), lastEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomRight(), currentEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomRight(), currentEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomLeft(), currentEraserRect.topLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.topLeft(), lastEraserRect.topLeft()));
    }else if (0 == subX && subY > 0) {
        path.moveTo(lastEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.lineTo(currentEraserRect.topRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.closeSubpath();

        //记录多边形的每一条边
        eraserLines.push_back(QLineF(lastEraserRect.bottomLeft(), currentEraserRect.topLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.topLeft(), currentEraserRect.topRight()));
        eraserLines.push_back(QLineF(currentEraserRect.topRight(), lastEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomRight(), lastEraserRect.bottomLeft()));
    }else if (0 == subX && subY < 0) {
        path.moveTo(currentEraserRect.bottomLeft());
        path.lineTo(lastEraserRect.topLeft());
        path.lineTo(lastEraserRect.topRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.closeSubpath();

        //记录多边形的每一条边
        eraserLines.push_back(QLineF(currentEraserRect.bottomLeft(), lastEraserRect.topLeft()));
        eraserLines.push_back(QLineF(lastEraserRect.topLeft(), lastEraserRect.topRight()));
        eraserLines.push_back(QLineF(lastEraserRect.topRight(), currentEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomRight(), currentEraserRect.bottomLeft()));
    }else if (subX > 0 && subY == 0) {
        path.moveTo(lastEraserRect.topRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.lineTo(currentEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.closeSubpath();

        //记录多边形的每一条边
        eraserLines.push_back(QLineF(lastEraserRect.topRight(), lastEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomRight(), currentEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomLeft(), currentEraserRect.topLeft()));
        eraserLines.push_back(QLineF(currentEraserRect.topLeft(), lastEraserRect.topRight()));
    }else if (subX < 0 && subY == 0) {
        path.moveTo(currentEraserRect.topRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.lineTo(lastEraserRect.bottomLeft());
        path.lineTo(lastEraserRect.topLeft());
        path.closeSubpath();

        //记录多边形的每一条边
        eraserLines.push_back(QLineF(currentEraserRect.topRight(), currentEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(currentEraserRect.bottomRight(), lastEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomLeft(), lastEraserRect.topLeft()));
        eraserLines.push_back(QLineF(lastEraserRect.topLeft(), currentEraserRect.topRight()));
    }else {
        path.addRect(lastEraserRect);

        //记录多边形的每一条边
        eraserLines.push_back(QLineF(lastEraserRect.topLeft(), lastEraserRect.topRight()));
        eraserLines.push_back(QLineF(lastEraserRect.topRight(), lastEraserRect.bottomRight()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomRight(), lastEraserRect.bottomLeft()));
        eraserLines.push_back(QLineF(lastEraserRect.bottomLeft(), lastEraserRect.topLeft()));
    }
    *eraserPath = path;
    return eraserLines;
}

/* 获取擦除后的路径 */
QPainterPath BoardScene::getEraserSubPath(const QPainterPath &eraserPath, QVector<QLineF> eraserLines, const QPainterPath &srcPath)
{
    QPainterPath subPath;
    int eCount = srcPath.elementCount();
    if (eCount < 0 || !eraserPath.intersects(srcPath))
        return srcPath;

    //qDebug()<<"---------"<<srcPath;
    QPainterPath::Element element1 = srcPath.elementAt(0);
    QPointF ePoint1 = QPointF(element1.x, element1.y);
    if (0 == eCount) {
        if (!eraserPath.contains(ePoint1)) {
            subPath.moveTo(ePoint1);
        }
    }

    QPainterPath::Element element2;
    QPointF ePoint2;

    QPainterPath elementPath;
    QLineF eLine;
    QPointF iPoint;         //相交点
    QVector<QPointF> iPointList;    //相交点集合
    for (int i = 1; i < eCount; i++)
    {
        element2 = srcPath.elementAt(i);
        ePoint2 = QPointF(element2.x, element2.y);
        if (element2.isMoveTo()) {
            if (!eraserPath.contains(ePoint1)) {
                if (element1.isMoveTo())    //前点是moveTo，未被记录
                    subPath.moveTo(ePoint1);
            }

            if (i == (eCount - 1) && !eraserPath.contains(ePoint2))
                subPath.moveTo(ePoint2);

            element1 = element2;
            ePoint1 = ePoint2;
            continue;
        }

        elementPath &= QPainterPath();
        elementPath.moveTo(ePoint1);
        elementPath.lineTo(ePoint2);
        if (!eraserPath.intersects(elementPath)) {  //没有交点（在外部）
            if (element1.isMoveTo())    //前点是moveTo，未被记录
                subPath.moveTo(ePoint1);
            subPath.lineTo(ePoint2);
            element1 = element2;
            ePoint1 = ePoint2;
            continue;
        }else {     //相交或包含
            if (eraserPath.contains(elementPath)) {  //橡皮擦路径完全包含元素点路径
                element1 = element2;
                ePoint1 = ePoint2;
                continue;
            }

            eLine = QLineF(ePoint1, ePoint2);
            iPointList.clear();
            //遍历橡皮擦所有边与元素点线段的相交情况（QLineF::BoundedIntersection表示相交点不是位于延长线上（真实相交））
            foreach(QLineF linef, eraserLines) {
                if (QLineF::BoundedIntersection == eLine.intersect(linef, &iPoint)) { //与多边形区域的边是否相交
                    iPointList.push_back(iPoint);
                }
            }
            if (1 == iPointList.size()) //一个交点
            {
                if (!eraserPath.contains(ePoint1) && !eraserPath.contains(ePoint2)) //相切
                {
                    if (element1.isMoveTo())    //前点是moveTo，未被记录
                        subPath.moveTo(ePoint1);
                    subPath.lineTo(ePoint2);
                    element1 = element2;
                    ePoint1 = ePoint2;
                    continue;
                }else if (eraserPath.contains(ePoint1)){    //前点在里面
                    subPath.moveTo(iPointList.at(0));
                    subPath.lineTo(ePoint2);
                    element1 = element2;
                    ePoint1 = ePoint2;
                    continue;
                }else { //后点在里面
                    if (element1.isMoveTo())    //前点是moveTo，未被记录
                        subPath.moveTo(ePoint1);
                    subPath.lineTo(iPointList.at(0));
                    element1 = element2;
                    ePoint1 = ePoint2;
                    continue;
                }
            }else if (iPointList.at(0) == iPointList.at(1)) {   //相切
                if (element1.isMoveTo())    //前点是moveTo，未被记录
                    subPath.moveTo(ePoint1);
                subPath.lineTo(ePoint2);
                element1 = element2;
                ePoint1 = ePoint2;
                continue;
            }else{      //两个交点
                QPointF iPoint1, iPoint2;
                /*判断线段两个端点和两个交点的位置关系，顺序关系为：ePoint1->iPoint1->iPoint2->ePoint2*/
                if (ePoint1.x() == ePoint2.x()) {   //线段是竖直方向垂直过矩形框
                    if (ePoint1.y() < ePoint2.y()) {    //向下垂直
                        if (iPointList.at(0).y() < iPointList.at(1).y()) {
                            iPoint1 = iPointList.at(0);
                            iPoint2 = iPointList.at(1);
                        }else {
                            iPoint1 = iPointList.at(1);
                            iPoint2 = iPointList.at(0);
                        }
                    }else {     //向上垂直
                        if (iPointList.at(0).y() > iPointList.at(1).y()) {
                            iPoint1 = iPointList.at(0);
                            iPoint2 = iPointList.at(1);
                        }else {
                            iPoint1 = iPointList.at(1);
                            iPoint2 = iPointList.at(0);
                        }
                    }
                }else if (ePoint1.x() < ePoint2.x()) {  //线段是水平坐标系左方往右方向过矩形框
                    if (iPointList.at(0).x() < iPointList.at(1).x()) {
                        iPoint1 = iPointList.at(0);
                        iPoint2 = iPointList.at(1);
                    }else {
                        iPoint1 = iPointList.at(1);
                        iPoint2 = iPointList.at(0);
                    }
                }else {     //线段是水平坐标系右方往左方向过矩形框
                    if (iPointList.at(0).x() > iPointList.at(1).x()) {
                        iPoint1 = iPointList.at(0);
                        iPoint2 = iPointList.at(1);
                    }else {
                        iPoint1 = iPointList.at(1);
                        iPoint2 = iPointList.at(0);
                    }
                }

                if (element1.isMoveTo())    //前点是moveTo，未被记录
                    subPath.moveTo(ePoint1);
                subPath.lineTo(iPoint1);
                subPath.moveTo(iPoint2);
                subPath.lineTo(ePoint2);
                element1 = element2;
                ePoint1 = ePoint2;
                continue;
            }
        }
    }
    //qDebug()<<"===="<<subPath;
    return subPath;
}

void BoardScene::pushToUndoData(QVector<QGraphicsItem *> vector, BoardScene::HistoryType type)
{
    m_pUndoData.push_back(vector);
    m_pUndoType.push_back(type);
    for(int i = 0; i < m_pRedoType.size(); i++) {
        if (HistoryType::ItemRemoved == m_pRedoType.at(i)) {
            QVector<QGraphicsItem *> removeItems = m_pRedoData.at(i);
            foreach (QGraphicsItem *item, removeItems) {
                delete item;
            }
        }
    }
    m_pRedoData.clear();
    m_pRedoType.clear();
}

void BoardScene::pushToUndoData(QVector<QGraphicsItem *> vector1, QVector<QGraphicsItem *> vector2, BoardScene::HistoryType type)
{
    if (HistoryType::AddAndRemove != type &&
            HistoryType::RemoveAndAdd != type)
        return;

    m_pUndoData.push_back(vector1);
    m_pUndoData.push_back(vector2);
    m_pUndoType.push_back(type);
    for(int i = 0; i < m_pRedoType.size(); i++) {
        if (HistoryType::ItemRemoved == m_pRedoType.at(i)) {
            QVector<QGraphicsItem *> removeItems = m_pRedoData.at(i);
            foreach (QGraphicsItem *item, removeItems) {
                delete item;
            }
        }
    }
    m_pRedoData.clear();
    m_pRedoType.clear();
}

int BoardScene::getMaxZValue()
{
    int maxZValue = 0;
    foreach (QGraphicsItem *item, this->items()) {
        if (maxZValue < item->zValue())
            maxZValue = item->zValue();
    }
    return maxZValue;
}

int BoardScene::getMinZValue()
{
    int minZValue = 0;
    foreach (QGraphicsItem *item, this->items()) {
        if (minZValue > item->zValue())
            minZValue = item->zValue();
    }
    return minZValue;
}



