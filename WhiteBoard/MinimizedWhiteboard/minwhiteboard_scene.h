#ifndef MINWHITEBOARD_SCENE_H
#define MINWHITEBOARD_SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QThreadPool>
#include <QPixmapCache>
#include "minwhiteboar_pathitem.h"
#include "minwhiteboard_erasetask.h"
#include "mod_draw/erasertask.h"

class MinWhiteBoard_Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    MinWhiteBoard_Scene(QObject* parent = 0);
    ~MinWhiteBoard_Scene();
    MinWhiteBoar_PathItem *addPathItem(const QPainterPath &path = QPainterPath(), QGraphicsItem *parentItem = 0);

    //擦除item，参数一：橡皮擦移动的多边形路径，参数二：橡皮擦item
    void eraseItems(QPainterPath erasePath, QGraphicsItem *item);
    //擦除完成
    void eraseFinished();

private:
};
#endif // MINWHITEBOARD_SCENE_H
