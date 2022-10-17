#include "minwhiteboard_scene.h"
#include <QtDebug>

MinWhiteBoard_Scene::MinWhiteBoard_Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    QPixmapCache::setCacheLimit(204800);
    QThreadPool::globalInstance()->setMaxThreadCount(10);
}

MinWhiteBoard_Scene::~MinWhiteBoard_Scene()
{}

/* 添加一个pathItem */
MinWhiteBoar_PathItem *MinWhiteBoard_Scene::addPathItem(const QPainterPath &path, QGraphicsItem *parentItem)
{
    MinWhiteBoar_PathItem *item = new MinWhiteBoar_PathItem(parentItem);
    item->setPen(QPen(QBrush(e_MinBoardPenColor), e_MinBoardPenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    item->setPath(path);
    if (0 == parentItem)
        this->addItem(item);
    return item;
}

void MinWhiteBoard_Scene::eraseItems(QPainterPath path, QGraphicsItem *eraserItem)
{
    foreach(QGraphicsItem *item, eraserItem->collidingItems()) {
            MinWhiteBoard_EraseTask *task = new MinWhiteBoard_EraseTask((MinWhiteBoar_PathItem*)item, path);
            connect(task, &MinWhiteBoard_EraseTask::eraseFinish, this, [=](QPainterPath path){ ((MinWhiteBoar_PathItem *)item)->setPath(path); });
            task->setAutoDelete( true);
            QThreadPool::globalInstance()->start(task);
    }
}

void MinWhiteBoard_Scene::eraseFinished()
{
    QThreadPool::globalInstance()->waitForDone();
}
