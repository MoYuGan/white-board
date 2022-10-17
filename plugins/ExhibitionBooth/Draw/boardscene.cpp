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
    QGraphicsScene::addItem(item);
}

void BoardScene::addItems(QVector<QGraphicsItem *> vector)
{
    if (0 == vector.size())
        return;

    this->pushToUndoData(vector, HistoryType::NewItemAdd);
    foreach(QGraphicsItem *item, vector) {
        QGraphicsScene::addItem(item);
    }
}

void BoardScene::deleteItems(QVector<QGraphicsItem *> vector)
{
    if (0 == vector.size())
        return;

    this->pushToUndoData(vector, HistoryType::ItemRemoved);
    for (int i = 0; i < vector.size(); i++) {
        this->removeItem(vector.at(i));
    }
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
    item->setPen(QPen(e_PenColor, e_PenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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

void BoardScene::eraserPressed(const QPointF &pt)
{
    m_pBeErasedItems.clear();

    m_pEraserItem = new QGraphicsPixmapItem;
    QPixmap pixmap = QPixmap(":/images/cachuzhuangtai@2x.png").scaled(e_EraserSize);
    pixmap.setDevicePixelRatio(1);
    m_pEraserItem->setPixmap(pixmap);
    m_pEraserItem->setOffset(QPointF(pt.x() - pixmap.width()/2.0,
                                     pt.y() - pixmap.height()/2.0));
    m_pEraserItem->setZValue(10);
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
            //addItem已经重写，应该调用默认的addItem函数，避免重复添加撤销集合以及出现其他错误
            QGraphicsScene::addItem(item);
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
            //addItem已经重写，应该调用默认的addItem函数，避免重复添加撤销集合以及出现其他错误
            QGraphicsScene::addItem(item);
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

void BoardScene::deleteAllItems()
{
    this->deleteItems(this->items().toVector());
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



