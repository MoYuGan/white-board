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
#include <mod_draw/graphic.h>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QDateTime>


BoardScene::BoardScene(QObject *parent) :
    QGraphicsScene(parent)
{
    QPixmapCache::setCacheLimit(204800);
    this->installEventFilter(this);
    QThreadPool::globalInstance()->setMaxThreadCount(10);
    m_pUndoData.clear();
    m_pUndoType.clear();
    m_pRedoData.clear();
    m_pRedoType.clear();

}

BoardScene::~BoardScene()
{}

/* 添加一个pathItem */
PathItem *BoardScene::addPathItem(QPainterPath path,int num,int num1,QGraphicsItem *parentItem)
{
    PathItem *item = new PathItem(parentItem,num,num1);
    connect(item, &PathItem::itemClicked, this, &BoardScene::onItemClicked);
    connect(item, &PathItem::itemChanged, this, &BoardScene::onItemChanged);
    item->firstSetPen(QPen(QBrush(g_PenColor), g_PenSize));
    item->setPath(path);
    if (0 == parentItem)
    {
        this->addItem(item);
    }
    return item;
}

PathItem *BoardScene::addMiniPathItem(QPainterPath path, int num, int num1, QColor color, QGraphicsItem *parentItem)
{
    PathItem *item = new PathItem(parentItem,num,num1);
    connect(item, &PathItem::itemClicked, this, &BoardScene::onItemClicked);
    connect(item, &PathItem::itemChanged, this, &BoardScene::onItemChanged);
    item->firstSetPen(QPen(QBrush(color), g_PenSize));
    item->setPath(path);
    if (0 == parentItem)
    {
        this->addItem(item);
    }
    return item;
}

/* 添加一个lineItem */
LineItem *BoardScene::addLineItem(const QLineF &line, GraphicType type)
{
    QPen pen = QPen(QBrush(Qt::white), Public_Function::getScaleSize(3),
                    Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    LineItem *item = nullptr;
    switch(type)
    {
    case GraphicType::ZhiXian: { item = new LineItem(LineItem::StraightLine);}break;
        case GraphicType::JianTou:  { item = new LineItem(LineItem::SingleArrow); }break;
        case GraphicType::ShuangJianTou:    { item = new LineItem(LineItem::DoubleArrow); }break;
        case GraphicType::XianDuan: { item = new LineItem(LineItem::LineSegment); }break;
        case GraphicType::XvXian: { pen.setStyle(Qt::DashLine); item = new LineItem(LineItem::StraightLine); }break;
        default: return item;
    }
    connect(item, &LineItem::itemClicked, this, &BoardScene::onItemClicked);
    connect(item, &LineItem::itemChanged, this, &BoardScene::onItemChanged);
    item->firstSetPen(pen);
    item->setLine(line);
    this->addItem(item);
    return item;
}

/* 添加一个图形item */
GraphicsItem *BoardScene::addGraphicItem(const QPainterPath &path)
{
    QPen pen = QPen(QBrush(Qt::white), Public_Function::getScaleSize(3),
                    Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    GraphicsItem *item = new GraphicsItem;
    connect(item, &GraphicsItem::itemClicked, this, &BoardScene::onItemClicked);
    connect(item, &GraphicsItem::itemChanged, this, &BoardScene::onItemChanged);
    item->firstSetPen(pen);
    item->setPath(path);
    this->addItem(item);
    return item;
}

/* 添加一个图片item */
PixmapItem *BoardScene::addPixmapItem(const QPixmap &pixmap,const QRect &pixmapRect,QString fileName)
{
    QList<QGraphicsItem *> addItems;
    PixmapItem *item = new PixmapItem;
    connect(item, &PixmapItem::itemClicked, this, &BoardScene::onItemClicked);
    connect(item, &PixmapItem::itemChanged, this, &BoardScene::onItemChanged);
    QString suffix = fileName.mid(fileName.length() -4);
    if(suffix.compare(".gif") ==0)
    {
        item->m_setGifPixmap(fileName, pixmapRect);
    }
    else
    {
        item->m_setPixmap(pixmap, pixmapRect);
    }
    this->addItem(item);
    addItems.push_back(item);
    this->pushToUndoData(addItems, BoardScene::NewItemAdd);
    return item;
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

void BoardScene::undo()
{
    if (0 == m_pUndoType.size())
        return;
    /*清除选择框，避免恢复是选择框还在,导致异常出现*/
    this->clearSelection();

    switch(m_pUndoType.last()) {
    case HistoryType::NewItemAdd: {
        QList<QGraphicsItem *> items = m_pUndoData.last();
        m_pRedoData.push_back(items);
        m_pRedoType.push_back(HistoryType::ItemRemoved);
        foreach(QGraphicsItem *item, items) {
            if(this->items().contains(item))
            this->removeItem(item);
        }
    }break;
    case HistoryType::ItemRemoved: {
        QList<QGraphicsItem *> items = m_pUndoData.last();
        m_pRedoData.push_back(items);
        m_pRedoType.push_back(HistoryType::NewItemAdd);
        foreach(QGraphicsItem *item, items) {
            //addItem已经重写，应该调用默认的addItem函数，避免重复添加撤销集合以及出现其他错误
            QGraphicsScene::addItem(item);
        }
    }break;
    case HistoryType::ItemChanged: {
        QList<QGraphicsItem *> items = m_pUndoData.last();
        m_pRedoData.push_back(items);
        m_pRedoType.push_back(HistoryType::ItemChanged);
        foreach(QGraphicsItem *item, items) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                pathItem->undo();
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *pathItem = static_cast<GraphicsItem*>(item);
                pathItem->undo();
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                lineItem->undo();
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                pixmapItem->undo();
            }
        }
    }break;
    case HistoryType::AddAndRemove: {
        QList<QGraphicsItem *> removeitems = m_pUndoData.last();
        m_pUndoData.pop_back();
        QList<QGraphicsItem *> additems = m_pUndoData.last();
        m_pRedoData.push_back(additems);
        m_pRedoData.push_back(removeitems);
        m_pRedoType.push_back(HistoryType::RemoveAndAdd);
        foreach(QGraphicsItem *item, additems) {
            if(this->items().contains(item))
            this->removeItem(item);
        }
        foreach(QGraphicsItem *item, removeitems) {
            if(!this->items().contains(item))
            {
                QGraphicsScene::addItem(item);
                item->show();
            }
            else
            {
                item->show();
            }
        } 
    }break;
    case HistoryType::RemoveAndAdd: {
        QList<QGraphicsItem *> additems = m_pUndoData.last();
        m_pUndoData.pop_back();
        QList<QGraphicsItem *> removeitems = m_pUndoData.last();
        m_pRedoData.push_back(removeitems);
        m_pRedoData.push_back(additems);
        m_pRedoType.push_back(HistoryType::AddAndRemove);
        foreach(QGraphicsItem *item, additems) {
            if(item->scene() !=nullptr)
            this->removeItem(item);
        }
        foreach(QGraphicsItem *item, removeitems) {
            if(!this->items().contains(item))
            {
                QGraphicsScene::addItem(item);
                item->show();
            }
            else
            {
                item->show();
            }
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
    /*清除选择框，避免恢复是选择框还在,导致异常出现*/
    this->clearSelection();

    switch(m_pRedoType.last()) {
    case HistoryType::NewItemAdd: {
        QList<QGraphicsItem *> items = m_pRedoData.last();
        m_pUndoData.push_back(items);
        m_pUndoType.push_back(HistoryType::ItemRemoved);
        foreach(QGraphicsItem *item, items) {
            if(this->items().contains(item))
            this->removeItem(item);
        }
    }break;
    case HistoryType::ItemRemoved: {
        QList<QGraphicsItem *> items = m_pRedoData.last();
        m_pUndoData.push_back(items);
        m_pUndoType.push_back(HistoryType::NewItemAdd);
        foreach(QGraphicsItem *item, items) {
            //addItem已经重写，应该调用默认的addItem函数，避免重复添加撤销集合以及出现其他错误
            if(!this->items().contains(item))
            QGraphicsScene::addItem(item);
        }
    }break;
    case HistoryType::ItemChanged: {
        QList<QGraphicsItem *> items = m_pRedoData.last();
        m_pUndoData.push_back(items);
        m_pUndoType.push_back(HistoryType::ItemChanged);
        foreach(QGraphicsItem *item, items) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                pathItem->redo();
            }else if ((QGraphicsItem::UserType + 100) == item->type()) {
                GraphicsItem *pathItem = static_cast<GraphicsItem*>(item);
                pathItem->redo();
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                lineItem->redo();
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                pixmapItem->redo();
            }
        }
    }break;
    case HistoryType::AddAndRemove: {
        QList<QGraphicsItem *> removeitems = m_pRedoData.last();
        m_pRedoData.pop_back();
        QList<QGraphicsItem *> additems = m_pRedoData.last();
        m_pUndoData.push_back(additems);
        m_pUndoData.push_back(removeitems);
        m_pUndoType.push_back(HistoryType::RemoveAndAdd);
        foreach(QGraphicsItem *item, removeitems) {
            if(!this->items().contains(item))
            QGraphicsScene::addItem(item);
        }
        foreach(QGraphicsItem *item, additems) {
            if(this->items().contains(item))
            this->removeItem(item);
        }
    }break;
    case HistoryType::RemoveAndAdd: {
        QList<QGraphicsItem *> additems = m_pRedoData.last();
        m_pRedoData.pop_back();
        QList<QGraphicsItem *> removeitems = m_pRedoData.last();
        m_pUndoData.push_back(removeitems);
        m_pUndoData.push_back(additems);
        m_pUndoType.push_back(HistoryType::AddAndRemove);
        foreach(QGraphicsItem *item, additems) {
            if(this->items().contains(item))
            this->removeItem(item);
        }
        foreach(QGraphicsItem *item, removeitems) {
            if(!this->items().contains(item))
            {
                QGraphicsScene::addItem(item);
            }
        }
    }break;
    default:
        break;
    }
    m_pRedoData.pop_back();
    m_pRedoType.pop_back();
    this->update();
}

void BoardScene::addChiGuiItem(int type)
{
    QGraphicsItem *gItem = nullptr;
    if (0 == type) {
        CustomItem_ZhiChi *item = new CustomItem_ZhiChi;
        connect(item, &CustomItem_ZhiChi::sendline11, this, &BoardScene::drawLinePath);
        connect(item, &CustomItem_ZhiChi::sendline12, this, &BoardScene::drawLineFinished);
        connect(item, &CustomItem_ZhiChi::deleteitem, this, &BoardScene::deleteChiGuiItem);
        gItem = (QGraphicsItem *)item;
    }else if (1 == type) {
        CustomItem_ZhiJiao *item = new CustomItem_ZhiJiao;
        connect(item, &CustomItem_ZhiJiao::sendline31, this, &BoardScene::drawLinePath);
        connect(item, &CustomItem_ZhiJiao::sendline32, this, &BoardScene::drawLineFinished);
        connect(item, &CustomItem_ZhiJiao::deleteitem3, this, &BoardScene::deleteChiGuiItem);
        connect(item, &CustomItem_ZhiJiao::refresh, this,[=](){this->update();});
        gItem = (QGraphicsItem *)item;
    }else if (2 == type) {
        CustomItem_DengYao *item = new CustomItem_DengYao;
        connect(item, &CustomItem_DengYao::sendline21, this, &BoardScene::drawLinePath);
        connect(item, &CustomItem_DengYao::sendline22, this, &BoardScene::drawLineFinished);
        connect(item, &CustomItem_DengYao::deleteitem2, this, &BoardScene::deleteChiGuiItem);
        connect(item, &CustomItem_DengYao::refresh, this,[=](){this->update();});
        gItem = (QGraphicsItem *)item;
    }else if (3 == type) {
        CustomItem_LiangJiaoQi *item = new CustomItem_LiangJiaoQi;
        connect(item, &CustomItem_LiangJiaoQi::deleteitem4, this, &BoardScene::deleteChiGuiItem);
        connect(item, &CustomItem_LiangJiaoQi::refresh, this,[=](){this->update();});
        gItem = (QGraphicsItem *)item;
    }else if (4 == type) {
        CustomItem_YuanGui *item = new CustomItem_YuanGui(this);
        connect(item, &CustomItem_YuanGui::sendarc51, this, &BoardScene::drawRoundPath);
        connect(item, &CustomItem_YuanGui::sendarc52, this, &BoardScene::drawRoundFinished);
        connect(item, &CustomItem_YuanGui::deleteitem5, this, &BoardScene::deleteChiGuiItem);
        gItem = (QGraphicsItem *)item;
        this->update();
    }

    gItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    //gItem->setEnabled(false);
    if (0 == m_pChiGuiItems.size())
    {
        gItem->setZValue(this->getMaxZValue() + 3000);
    }else {
        gItem->setZValue(m_pChiGuiItems.at(m_pChiGuiItems.size() - 1)->zValue() + 3000);
    }
    m_pChiGuiItems.push_back(gItem);
    //this->mAddItem(gItem);
    gItem->moveBy((this->sceneRect().width() - gItem->boundingRect().width())/2,
                  (this->sceneRect().height() - gItem->boundingRect().height())/2);
    this->addItem(gItem);
}

void BoardScene::eraseItems(QPainterPath path, QGraphicsItem *eraserItem,int m)
{
    //qDebug()<<"time------------------1----0"<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    if(m ==1)
    {
        sceneitemlist.clear();
        sceneitemlist =this->items();
        m_BeEraseItems.clear();
        itempathlist.clear();
    }

    foreach(QGraphicsItem *item, eraserItem->collidingItems()) {
        if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
            if (-1 == m_BeEraseItems.indexOf(item))
            {
                if(sceneitemlist.contains(item))
                m_BeEraseItems.push_back(item);
            }
            EraserTask *task = new EraserTask(item, path);
            //if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type())

          connect(task, &EraserTask::eraseFinish, this, [=](QList<QPainterPath>listpath){
                item->hide();
                if(!sceneitemlist.contains(item))
                    this->removeItem(item);
                QList<QPainterPath>m_listpath;
                for(int m=0; m<listpath.count();m++)
                {
                    //if(listpath.at(m).elementCount() >1)m_listpath.append(listpath.at(m));
                    /*为了绘制曲线效果，最低需要三个点，所以两个点的路径被移出，不进行item添加到场景*/
                    if(listpath.at(m).elementCount() >2)m_listpath.append(listpath.at(m));
                }

                for(int i=0;i <m_listpath.count();i++)
                {
                    if(itempathlist.contains(m_listpath.at(i)))
                    {
                        continue;
                    }
                    else
                    {
                       PathItem *pathItem = static_cast<PathItem*>(item);
                       PathItem *m_item =addPathItem(m_listpath.at(i));
                       if(pathItem->getPathShape() ==1)
                       {
                            if(m_listpath.count() ==1)
                            {
                                m_item->m_setNumber(pathItem->m_getNumber());
                                m_item->m_comparePath(m_item->path(),pathItem->path());
                                m_item->changePathShape(1);
                            }
                            else
                            {
                                if(i < m_listpath.count() -1)
                                {
                                    m_item->changePathShape(0);
                                    m_item->m_comparePath(m_item->path(),pathItem->path());
                                }
                                else
                                {
                                    m_item->m_setNumber(pathItem->m_getNumber());
                                    m_item->m_comparePath(m_item->path(),pathItem->path());
                                    m_item->changePathShape(1);
                                }
                            }
                       }
                       else if(pathItem->getPathShape() ==0)
                       {
                           m_item->changePathShape(0);
                       }
                        static_cast<PathItem *>(m_item)->setPen(static_cast<PathItem *>(item)->getItemPen());
                        m_item->setZValue(static_cast<PathItem *>(item)->getItemZvalue());
                        additemlist.push_back(m_item);
                    }
                }
                itempathlist =listpath;
                this->removeItem(item);
             });

            task->setAutoDelete( true);
            QThreadPool::globalInstance()->start(task);
            //qDebug()<<"time------------------1----2"<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
//            GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
//            graphicItem->eraseWithPath(path);
//            this->update();
            GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
            deleteSelectedItems(graphicItem);
            this->update();
        }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
//            LineItem *lineItem = static_cast<LineItem*>(item);
//            lineItem->eraseWithPath(path);
//            this->update();
            LineItem *lineItem = static_cast<LineItem*>(item);
            deleteSelectedItems(lineItem);
            this->update();
        }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                    PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                    if(pixmapItem->isDelete())deleteSelectedItems(pixmapItem);
                    this->update();
        }
    }
    //qDebug()<<"time------------------1----3"<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
}

void BoardScene::eraseFinished()
{
    if(!additemlist.isEmpty())
    {
        pushToUndoData(additemlist,m_BeEraseItems,HistoryType::AddAndRemove);
        additemlist.clear();
        m_BeEraseItems.clear();
    }
}

/*获取位于最顶层图元的图层，除了特殊的图元的*/
int BoardScene::getMaxZValue()
{
    int maxZValue = 0;
    foreach (QGraphicsItem *item, this->items()) {
        if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type())
        {
            if (maxZValue < item->zValue())
                maxZValue = item->zValue();
        }
    }
    return maxZValue;
}

/*获取位于最底层图元的图层，除了特殊的图元的*/
int BoardScene::getMinZValue()
{
    int minZValue = 0;
    foreach (QGraphicsItem *item, this->items()) {
        if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type())
        {
            if (minZValue > item->zValue())
                minZValue = item->zValue();
        }
    }
    return minZValue;
}

void BoardScene::pushToUndoData(QList<QGraphicsItem *> items, BoardScene::HistoryType type)
{
    if(items.isEmpty())return;
    m_pUndoData.push_back(items);
    m_pUndoType.push_back(type);
    while(m_pUndoType.count() >MAX_HISTORY_NUM)
    {
        m_pUndoType.removeFirst();
        m_pUndoData.removeFirst();
    }

    m_pRedoData.clear();
    m_pRedoType.clear();
}


bool BoardScene::isMouseInChiGuiItem(const QPointF &pressedPoint)
{
    QGraphicsItem *item  = this->itemAt(pressedPoint, QTransform());
    if (nullptr == item)
        return false;
    if ((QGraphicsItem::UserType + (int)(ItemType::ChiGuiItem)) == item->type())
        return true;

    return false;
}

void BoardScene::savePixmap(QPixmap pix)
{
    tabpixmap =pix;
}

QPixmap BoardScene::getPixmap()
{
    return tabpixmap;
}

void BoardScene::updateLanguage()
{
    if( m_selectedRectItem != nullptr)
    {
        m_selectedRectItem->updateLanguage();
    }

}


void BoardScene::onItemClicked(QGraphicsItem *item)
{
    this->clearSelection();
    m_SelectedItems.push_back(item);
    this->setItemsSelected();
}

void BoardScene::onItemChanged(QGraphicsItem *item)
{
    QList<QGraphicsItem*> vector;
    vector.push_back(item);
    this->pushToUndoData(vector, HistoryType::ItemChanged);
}

void BoardScene::onSelectionChanged()
{
    if (nullptr != m_selectedRectItem) {
        //djf
//        this->removeItem(m_selectedRectItem);
//        //delete m_selectedRectItem;
//        m_selectedRectItem->deleteLater();
//        m_selectedRectItem = nullptr;
        m_selectedRectItem->updateSelectItem(m_SelectedItems);
        return;
    }

    if (0 == m_SelectedItems.size())
        return;
//djf sugeest to changed these code , it is not a good way to renew the selectedRectItem each time
    m_selectedRectItem = new SelectedRectItem(m_SelectedItems);
    m_selectedRectItem->setZValue(2000);
    this->addItem(m_selectedRectItem);

    connect(m_selectedRectItem, SIGNAL(deleteItems()), this, SLOT(deleteSelectedItems()), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(borderSizeChanged(int)), this, SLOT(onBorderSizeChanged(int)), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(borderColorChanged(QColor)), this, SLOT(onBorderColorChanged(QColor)), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(borderLineChanged(Qt::PenStyle)), this, SLOT(onBorderLineChanged(Qt::PenStyle)), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(fillColorChanged(QColor)), this, SLOT(onFillColorChanged(QColor)), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(stayOnTop()), this, SLOT(onStayOnTop()), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(stayOnBottom()), this, SLOT(onStayOnBottom()), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(flipItems(int,QPointF)), this, SLOT(onFlipItems(int,QPointF)), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(mirrorItems(int,qreal)), this, SLOT(onMirrorItems(int,qreal)), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(actionFinished()), this, SLOT(selectedItemsActionFinished()), Qt::DirectConnection);
    connect(m_selectedRectItem, SIGNAL(cloneItems(QPointF)), this, SLOT(onCloneItems(QPointF)), Qt::DirectConnection);
    connect(m_selectedRectItem, &SelectedRectItem::cloneFinished, this,[=](){ m_CloneItems.clear(); });

    connect(m_selectedRectItem,&SelectedRectItem::checkIs3DShape,this,&BoardScene::selectHave3DShape, Qt::DirectConnection);
}

/* 删除选中items */
void BoardScene::deleteSelectedItems()
{
    QList<QGraphicsItem *> deleteItems;
    foreach(QGraphicsItem* item, m_SelectedItems) {
           item->setSelected(false);
        this->removeItem(item);
        deleteItems.push_back(item);
    }

    m_SelectedItems.clear();
    this->onSelectionChanged();
    this->pushToUndoData(deleteItems, HistoryType::ItemRemoved);
}

void BoardScene::deleteSelectedItems(QGraphicsItem *item)
{
    QList<QGraphicsItem *> deleteItems;
    this->removeItem(item);
    deleteItems.push_back(item);
    this->pushToUndoData(deleteItems, HistoryType::ItemRemoved);
}

/* 删除所有Item */
void BoardScene::deleteAllItems()
{
    QList<QGraphicsItem *> deleteItems;
    for(QGraphicsItem *item : this->items())
    {
        if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type() ||
                (QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type())
        {
            item->setSelected(false);
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type() &&
                    item->parentItem() != 0)
                continue;
            this->removeItem(item);
            deleteItems.push_back(item);
        }
    }
    m_SelectedItems.clear();
    this->onSelectionChanged();
    this->pushToUndoData(deleteItems, HistoryType::ItemRemoved);
}

void BoardScene::setSelectionAreaRect(const QRectF &rect)
{
    this->clearSelection();

    QList<QGraphicsItem *> collidingItems;
    QPainterPath path;
    path.addRect(rect);
    const auto items = this->items(path, Qt::IntersectsItemShape);
    //获取跟矩形框有触碰，并且可被选中的item，加入触碰列表
    for (QGraphicsItem *item : items) {
        if (item->flags() & QGraphicsItem::ItemIsSelectable) {
            collidingItems.push_back(item);
        }
    }

    int i = 0;
    //遍历触碰列表
    while(i < collidingItems.size()) {
        QGraphicsItem *item = collidingItems.at(i);
        m_SelectedItems.push_back(item);    //加入线条集合
        ++i;
    }

    this->setItemsSelected();
}

/* 清除选中 */
void BoardScene::clearSelection()
{
    QGraphicsScene::clearSelection();
    m_SelectedItems.clear();
    this->onSelectionChanged();
}

void BoardScene::addTuAnPixmap(QPixmap pix,QRect rect)
{
    PixmapItem *item = new PixmapItem;
    item->setDelete(true);
    item->m_setPixmap(pix,rect);
    connect(item, &PixmapItem::itemClicked, this, &BoardScene::onItemClicked);
    connect(item, &PixmapItem::itemChanged, this, &BoardScene::onItemChanged);
    this->addItem(item);
}

/*设置item为选中状态*/
void BoardScene::setItemsSelected()
{
    foreach(QGraphicsItem *item, m_SelectedItems) {
            item->setSelected(true);
    }
    this->onSelectionChanged();
}

#if 0
void BoardScene::addGeometricStep1(int id, const QPointF &p1, const QPointF &p2)
{
    QGraphicsItem* item = m_pItemMap.value(id, nullptr);
    CustomItem_Cube *cubeItem;
    if (nullptr == item)
    {
        cubeItem = new CustomItem_Cube;
        connect(cubeItem, &CustomItem_Cube::adjustStart, this, &BoardScene::onAdjustStart);
        connect(cubeItem, &CustomItem_Cube::adjustFinished, this, &BoardScene::onAdjustFinished);
        connect(cubeItem, &CustomItem_Cube::itemSelected, this, [=](){ this->clearSelection(); }, Qt::DirectConnection);
        cubeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        cubeItem->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(3),
                              Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        cubeItem->addRect(p1, p2);
        cubeItem->setZValue(this->getMaxZValue() + 1);
        //this->mAddItem(cubeItem);
        m_pItemMap.insert(id, cubeItem);
    }else {
        cubeItem = static_cast<CustomItem_Cube*>(m_pItemMap.value(id));
        cubeItem->addRect(p1, p2);
    }
    this->update();
}

void BoardScene::addGeometricStep2(int id, qreal height)
{
    QGraphicsItem* item = m_pItemMap.value(id, nullptr);
    if (nullptr == item)
        return;

    CustomItem_Cube *cubeItem = static_cast<CustomItem_Cube*>(item);
    cubeItem->addRect2(height);
    this->update();
}

void BoardScene::addFanItem(int id, const QRectF &rect)
{
    QGraphicsItem* item = m_pItemMap.value(id, nullptr);
    CustomItem_Fan *pathItem;
    if (nullptr == item)
    {
        pathItem = new CustomItem_Fan;
        pathItem->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(3)));
        pathItem->setZooming(true);
        pathItem->setRect(rect);
        pathItem->setZValue(this->getMaxZValue() + 1);
        //this->mAddItem(pathItem);
        m_pItemMap.insert(id, pathItem);
    }else {
        pathItem = static_cast<CustomItem_Fan*>(m_pItemMap.value(id));
        pathItem->setRect(rect);
    }
    this->update();
}

/* 添加图形完成 */
void BoardScene::addGraphicItemFinished()
{
    foreach(QGraphicsItem* item, m_pItemMap.values()) {
        if ((QGraphicsItem::UserType + 100) == item->type()) {
            GraphicsItem *pathItem = static_cast<GraphicsItem*>(item);
            //pathItem->refreshPathSave(pathItem->path());
        }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
            LineItem *lineItem = static_cast<LineItem*>(item);
            //lineItem->refreshLineSave(lineItem->line());
        }else if ((QGraphicsItem::UserType + 103) == item->type()) {
            CustomItem_Cube *cubeItem = static_cast<CustomItem_Cube*>(item);
            cubeItem->createdCubeFinish();
        }
        this->clearSelection();
        item->setSelected(true);
    }
    m_pItemMap.clear();
}
#endif


void BoardScene::stayChiguiItemOnTop(int zValue)
{
    for(int i = 0; i < m_pChiGuiItems.size(); i++) {
        m_pChiGuiItems.at(i)->setZValue(zValue + (i + 1));
    }
}

/* 加载图片 */
void BoardScene::loadPicture(const QString &fileName)
{ 
    QPixmap pixmap;
    pixmap.load(fileName);
    QSize size = Public_Function::getScaleSize(QSize(800, 800));
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

    QRect pixmapRect = QRect(0, 0, scaleW, scaleH);
    pixmapRect.moveCenter(this->sceneRect().center().toPoint());

//    QString suffix = fileName.mid(fileName.length() -4);
//    if(suffix.compare(".gif") ==0)this->addPixmapItem(QPixmap(),fileName, pixmapRect);
//    else if(suffix.compare(".gif") !=0)this->addPixmapItem(pixmap,QString(), pixmapRect);
    this->addPixmapItem(pixmap, pixmapRect,fileName);
}

/* 加载PDF图片 */
void BoardScene::loadPDFPixmap(const QPixmap &pixmap)
{
    int pWidth = pixmap.width();
    int pHeight = pixmap.height();
    QRectF rect = this->sceneRect();
    qreal scaleW, scaleH, dpW, dpH;
    if (pWidth <= rect.width() && pHeight <= rect.height()) {
        scaleW = pWidth;
        scaleH = pHeight;
    }else if (pWidth < rect.width()){
        scaleH = rect.height();
        dpH = (qreal)pHeight/scaleH;
        scaleW = pWidth/dpH;
    }else if (pHeight < rect.height()) {
        scaleW = rect.width();
        dpW = (qreal)pWidth/scaleW;
        scaleH = pHeight/dpW;
    }else {
        qreal dpW = (qreal)pWidth/rect.width();
        qreal dpH = (qreal)pHeight/rect.height();
        scaleW = pWidth/dpW;
        scaleH = pHeight/dpH;
        dpW > dpH ? (scaleH = pHeight/dpW) : (scaleW = pWidth/dpH);
    }
    QRect pixmapRect = QRect(0, 0, scaleW, scaleH);
    pixmapRect.moveCenter(this->sceneRect().center().toPoint());
    this->addPixmapItem(pixmap,pixmapRect);
}

void BoardScene::onBorderSizeChanged(int size)
{
    foreach(QGraphicsItem* item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                QPen pen = graphicItem->pen();
                pen.setWidth(size);
                graphicItem->m_setPen(pen);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                QPen pen = lineItem->pen();
                pen.setWidth(size);
                lineItem->m_setPen(pen);
            }
    }
    this->selectedItemsActionFinished();
}

void BoardScene::onBorderColorChanged(QColor color)
{
    foreach(QGraphicsItem *item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                QPen pen = graphicItem->pen();
                pen.setBrush(QBrush(color));
                graphicItem->m_setPen(pen);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                QPen pen = lineItem->pen();
                pen.setBrush(QBrush(color));
                lineItem->m_setPen(pen);
            }
    }
    this->selectedItemsActionFinished();
}

void BoardScene::onBorderLineChanged(Qt::PenStyle penstyle)
{
    foreach(QGraphicsItem *item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                QPen pen = graphicItem->pen();
                pen.setStyle(penstyle);
                graphicItem->m_setPen(pen);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                QPen pen = lineItem->pen();
                pen.setStyle(penstyle);
                lineItem->m_setPen(pen);
            }
    }
    this->selectedItemsActionFinished();
}

void BoardScene::onFillColorChanged(QColor color)
{
    foreach(QGraphicsItem* item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                graphicItem->m_setBrush(QBrush(color));
            }
    }
    this->selectedItemsActionFinished();
}

void BoardScene::onStayOnTop()
{
    int maxZValue = this->getMaxZValue();
    m_selectedRectItem->setZValue(maxZValue +m_SelectedItems.count() +1); //保持此item置顶
    this->stayChiguiItemOnTop(maxZValue +m_SelectedItems.count() +2); //将尺规item置顶
    foreach(QGraphicsItem* item, m_SelectedItems) { //将选中的item置顶
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                pathItem->m_setZValue(maxZValue + 1);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                graphicItem->m_setZValue(maxZValue + 1);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                lineItem->m_setZValue(maxZValue + 1);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                pixmapItem->m_setZValue(maxZValue + 1);
            }
    }
   this->selectedItemsActionFinished();
}

void BoardScene::onStayOnBottom()
{
    int minZValue = this->getMinZValue();
    foreach(QGraphicsItem* item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                pathItem->m_setZValue(minZValue - 1);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                graphicItem->m_setZValue(minZValue - 1);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                lineItem->m_setZValue(minZValue - 1);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                pixmapItem->m_setZValue(minZValue - 1);
            }
    }
    this->selectedItemsActionFinished();
}

void BoardScene::onFlipItems(int direction, const QPointF &center)
{
    QList<QGraphicsItem *> newitemlist;
    foreach(QGraphicsItem* item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                if (0 == direction)
                {
                    PathItem *Temporary_path =new PathItem;
                    newitemlist.append(Temporary_path);
                    this->addItem(Temporary_path);
                    Temporary_path->setPath(pathItem->flipItemHorizontal(center));
                    Temporary_path->setPen(pathItem->pen());
                    Temporary_path->setZValue(pathItem->ZValue);
                    if(pathItem->getPathShape() ==0)Temporary_path->changePathShape(0);
                    else if(pathItem->getPathShape() ==1)Temporary_path->changePathShape(1);
                    Temporary_path->m_setNumber(pathItem->m_getNumber());
                }
                else
                {
                    PathItem *Temporary_path =new PathItem;
                    newitemlist.append(Temporary_path);
                    this->addItem(Temporary_path);
                    Temporary_path->setPath(pathItem->flipItemVertical(center));
                    Temporary_path->setPen(pathItem->pen());
                    Temporary_path->setZValue(pathItem->ZValue);
                    if(pathItem->getPathShape() ==0)Temporary_path->changePathShape(0);
                    else if(pathItem->getPathShape() ==1)Temporary_path->changePathShape(1);
                    Temporary_path->m_setNumber(pathItem->m_getNumber());
                }
                this->removeItem(pathItem);
            }
//            else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {              //图形
//                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
//                if (0 == direction)
//                    graphicItem->flipItemHorizontal(center);
//                else
//                    graphicItem->flipItemVertical(center);
//            }
            else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {        //线条图形
                LineItem *lineItem = static_cast<LineItem*>(item);
                if (0 == direction)
                {
                    lineItem->flipItemHorizontal(center);
                }
                else
                {
                    lineItem->flipItemVertical(center);
                }
                if (1 == m_SelectedItems.size()) {
                    m_selectedRectItem->setLine(lineItem->line());
                }
            }
        }
     pushToUndoData(newitemlist,m_SelectedItems,HistoryType::AddAndRemove);
     m_SelectedItems.clear();
     m_SelectedItems =newitemlist;
     onSelectionChanged();
}

void BoardScene::onMirrorItems(int direction, qreal p)
{
    QList<QGraphicsItem *> addItems;
    QGraphicsItem *parentItem;
    QGraphicsItem *newItem;
    foreach(QGraphicsItem* item, m_SelectedItems) {
        parentItem = 0;
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                PathItem *newPathItem;
                if (0 == direction || 1 == direction)
                    newPathItem = pathItem->mirrorItemVertical(p, parentItem);
                else
                    newPathItem = pathItem->mirrorItemHorizontal(p, parentItem);
                connect(newPathItem, &PathItem::itemClicked, this, &BoardScene::onItemClicked);
                connect(newPathItem, &PathItem::itemChanged, this, &BoardScene::onItemChanged);
                newItem = newPathItem;
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                GraphicsItem *newGraphicItem;
                if (0 == direction || 1 == direction)
                    newGraphicItem = graphicItem->mirrorItemVertical(p);
                else
                    newGraphicItem = graphicItem->mirrorItemHorizontal(p);
                connect(newGraphicItem, &GraphicsItem::itemClicked, this, &BoardScene::onItemClicked);
                connect(newGraphicItem, &GraphicsItem::itemChanged, this, &BoardScene::onItemChanged);
                newItem = newGraphicItem;
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                LineItem *newLineItem;
                if (0 == direction || 1 == direction)
                    newLineItem = lineItem->mirrorItemVertical(p);
                else
                    newLineItem = lineItem->mirrorItemHorizontal(p);
                connect(newLineItem, &LineItem::itemClicked, this, &BoardScene::onItemClicked);
                connect(newLineItem, &LineItem::itemChanged, this, &BoardScene::onItemChanged);
                newItem = newLineItem;
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
            }
            addItems.push_back(newItem);
            if (0 == parentItem) {
                this->addItem(newItem);
                newItem->stackBefore(m_selectedRectItem);
                parentItem = newItem;
            }
        }
    this->pushToUndoData(addItems, BoardScene::NewItemAdd);
}

/* 选中状态的item完成了一个操作（包括移动，旋转，翻转等等） */
void BoardScene::selectedItemsActionFinished()
{
    this->pushToUndoData(m_SelectedItems, HistoryType::ItemChanged);
}

void BoardScene::onCloneItems(const QPointF &subPt)
{
    if (0 == m_CloneItems.size()) {
        QGraphicsItem *parentItem;
        QGraphicsItem *newItem;
        for(int i= m_SelectedItems.count() -1; i >=0;i--)
           {
           QGraphicsItem* item =m_SelectedItems[i];
            parentItem = 0;
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                PathItem *newPathItem;
                newPathItem = pathItem->cloneItem(subPt, parentItem);
                connect(newPathItem, &PathItem::itemClicked, this, &BoardScene::onItemClicked);
                connect(newPathItem, &PathItem::itemChanged, this, &BoardScene::onItemChanged);
                newItem = newPathItem;
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                GraphicsItem *newGraphicItem;
                newGraphicItem = graphicItem->cloneItem(subPt);
                connect(newGraphicItem, &GraphicsItem::itemClicked, this, &BoardScene::onItemClicked);
                connect(newGraphicItem, &GraphicsItem::itemChanged, this, &BoardScene::onItemChanged);
                newItem = newGraphicItem;
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                LineItem *newLineItem;
                newLineItem = lineItem->cloneItem(subPt);
                connect(newLineItem, &LineItem::itemClicked, this, &BoardScene::onItemClicked);
                connect(newLineItem, &LineItem::itemChanged, this, &BoardScene::onItemChanged);
                newItem = newLineItem;
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
            }
            m_CloneItems.push_back(newItem);
            if (0 == parentItem) {
                this->addItem(newItem);
                newItem->stackBefore(m_selectedRectItem);
                parentItem = newItem;
            }
        }
        this->pushToUndoData(m_CloneItems, BoardScene::NewItemAdd);
    }else {
        for(QGraphicsItem *item : m_CloneItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                pathItem->moveItem(subPt);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                graphicItem->moveItem(subPt);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                lineItem->moveItem(subPt);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                //PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                //pixmapItem->rotateItem(angle, center);
            }
        }
    }
}

void BoardScene::selectHave3DShape(bool* bo)
{
    int num =1;
    foreach(QGraphicsItem* item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                if(!graphicItem->is3DShape())num++;
            }
    }
    if(num ==1)*bo =true;
    else *bo =false;
}


void BoardScene::drawLinePath(const QPointF &p1, const QPointF &p2)
{
//    QPainterPath path;
//    path.moveTo(p1);
//    path.lineTo(p2);
    QLineF line(p1, p2);
    if (!m_mapTempItem.contains(sender())) {
        m_mapTempItem.insert(sender(),this->addLineItem(line));
        LineItem *lineItem = static_cast<LineItem*>(m_mapTempItem.value(sender()));
        lineItem->setPen(QPen(g_PenColor,g_PenSize));
        if(g_ToolType ==ToolType::Pen)emit moveLineItemToScene(line,1,sender());
    }else {
        LineItem *lineItem = static_cast<LineItem*>(m_mapTempItem.value(sender()));
        lineItem->setLine(line);
        if(g_ToolType ==ToolType::Pen)emit moveLineItemToScene(line,2,sender());
    }
}

void BoardScene::drawRoundPath(const QPointF &center, qreal r, qreal rotateStart, qreal rotateChanged)
{
    QPainterPath path;
    path.arcMoveTo(center.x() -r, center.y() -r, 2*r, 2*r, rotateStart);
    path.arcTo(center.x() -r, center.y() -r, 2*r, 2*r, rotateStart, -rotateChanged);
    if (!m_mapTempItem.contains(sender())) {
        m_mapTempItem.insert(sender(),this->addGraphicItem(path));
        GraphicsItem *graphicsItem = static_cast<GraphicsItem*>(m_mapTempItem.value(sender()));
        graphicsItem->setPen(QPen(g_PenColor,g_PenSize));
        if(g_ToolType ==ToolType::Pen)emit moveArcItemToScene(path,1,sender());
    }else {
        GraphicsItem *graphicsItem = static_cast<GraphicsItem*>(m_mapTempItem.value(sender()));
        graphicsItem->setPath(path);
        if(g_ToolType ==ToolType::Pen)emit moveArcItemToScene(path,2,sender());
    }

}

void BoardScene::drawLineFinished(const QPointF &p1, const QPointF &p2)
{
    if (p1 == p2) {
        drawLinePath(p1,p2);
        this->removeItem(m_mapTempItem.value(sender()));
        LineItem *lineItem = static_cast<LineItem*>(m_mapTempItem.value(sender()));
        lineItem->deleteLater();
    }else
        this->pushToUndoData(QList<QGraphicsItem *>() << m_mapTempItem.value(sender()), HistoryType::NewItemAdd);
    LineItem *lineItem = static_cast<LineItem*>(m_mapTempItem.value(sender()));
    if(g_ToolType ==ToolType::Pen)emit moveLineItemToScene(lineItem->line(),3,sender());
    m_mapTempItem.take(sender());
}

void BoardScene::drawRoundFinished(const QPointF &center, qreal r, qreal rotateStart, qreal rotateChanged)
{
    Q_UNUSED(center)
    Q_UNUSED(r)
    Q_UNUSED(rotateStart)
    if (0 == rotateChanged) {
        this->removeItem(m_mapTempItem.value(sender()));
        GraphicsItem *graphicsItem = static_cast<GraphicsItem*>(m_mapTempItem.value(sender()));
        graphicsItem->deleteLater();
    }else
        this->pushToUndoData(QList<QGraphicsItem *>() << m_mapTempItem.value(sender()), HistoryType::NewItemAdd);
        GraphicsItem *graphicsItem = static_cast<GraphicsItem*>(m_mapTempItem.value(sender()));
        if(g_ToolType ==ToolType::Pen)moveArcItemToScene(graphicsItem->path(),3,sender());
        m_mapTempItem.take(sender());
}

void BoardScene::deleteChiGuiItem(QGraphicsItem *item)
{
    this->removeItem(item);
    m_pChiGuiItems.removeOne(item);
    delete item;
}

#if  0
bool BoardScene::event(QEvent *event)
{

     qDebug()<< "event->type(456) " << event->type() <<Qt::endl;
     switch (event->type()) {
     case QEvent::TouchBegin:
     {
         QGraphicsSceneMouseEvent *mouseevent =static_cast<QGraphicsSceneMouseEvent*>(event);
         QGraphicsScene::mousePressEvent(mouseevent);
         return QGraphicsScene::event(event);
     }
         break;
     case QEvent::TouchUpdate:
     {
         QGraphicsSceneMouseEvent *mouseevent =static_cast<QGraphicsSceneMouseEvent*>(event);
         QGraphicsScene::mouseMoveEvent(mouseevent);
         return QGraphicsScene::event(event);
     }
         break;
     case QEvent::TouchEnd:
     {
         QGraphicsSceneMouseEvent *mouseevent =static_cast<QGraphicsSceneMouseEvent*>(event);
         QGraphicsScene::mouseReleaseEvent(mouseevent);
         return QGraphicsScene::event(event);
     }
         break;
     default:
         break;
     }

     return QGraphicsScene::event(event);
}
#endif

void BoardScene::recursiveChildItem(QList<QGraphicsItem *> *colldingItems,
                                    QList<QGraphicsItem *> *pathItems, QGraphicsItem *parentItem)
{
    QList<QGraphicsItem *> childItems = parentItem->childItems();
    for(QGraphicsItem *item : childItems) {
        if (colldingItems->contains(item))
            colldingItems->removeOne(item);

        pathItems->push_back(item);
        this->recursiveChildItem(colldingItems, pathItems, item);
    }
}

void BoardScene::recursiveParentItem(QList<QGraphicsItem *> *colldingItems,
                                     QList<QGraphicsItem *> *pathItems, QGraphicsItem *childItem)
{
    QGraphicsItem* parentItem = childItem->parentItem();
    if (0 != parentItem) {
        if (colldingItems->contains(parentItem))
            colldingItems->removeOne(parentItem);

        pathItems->insert(0, parentItem);
        this->recursiveParentItem(colldingItems, pathItems, parentItem);
    }
}

//add item1  delete item2
void BoardScene::pushToUndoData(QList<QGraphicsItem *> items1, QList<QGraphicsItem *> items2, BoardScene::HistoryType type)
{
   if(items1.isEmpty()||items2.isEmpty())return;
    if (HistoryType::AddAndRemove != type &&
            HistoryType::RemoveAndAdd != type)
        return;
    m_pUndoData.push_back(items1);
    m_pUndoData.push_back(items2);
    m_pUndoType.push_back(type);

    while(m_pUndoType.count() >MAX_HISTORY_NUM)
    {
        m_pUndoType.removeFirst();
        m_pUndoData.removeFirst();
    }

    for(int i = 0; i < m_pRedoType.size(); i++) {
        if (HistoryType::ItemRemoved == m_pRedoType.at(i)) {
            QList<QGraphicsItem *> removeItems = m_pRedoData.at(i);
            foreach (QGraphicsItem *item, removeItems) {
                delete item;
            }
        }
    }
    m_pRedoData.clear();
    m_pRedoType.clear();
}





