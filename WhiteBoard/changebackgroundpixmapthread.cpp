#include "changebackgroundpixmapthread.h"

ChangeBackgroundPixmapThread::ChangeBackgroundPixmapThread(QVector<BoardScene *> mscenelist,QPixmap mpix,int mid,QThread *parent)
    : QThread{parent}
{
    scenelist =mscenelist;
    pix =mpix;
    id =mid;
}

void ChangeBackgroundPixmapThread::run()
{
    foreach (BoardScene *scene, scenelist) {
        if (nullptr == scene)return;
        scene->setBackgroundBrush(QBrush(pix.scaled(scene->width(), scene->height())));
        scene->setProperty("bgNum", id);
    }
}
