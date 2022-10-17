#ifndef MINWHITEBOAR_PATHITEM_H
#define MINWHITEBOAR_PATHITEM_H

#include <QGraphicsPathItem>

class MinWhiteBoar_PathItem : public QGraphicsPathItem
{
public:
    MinWhiteBoar_PathItem(QGraphicsItem *parent = Q_NULLPTR) : QGraphicsPathItem(parent){}

    bool m_EraseLock = false;   //擦除锁，擦除时候多个线程对同一个item进行擦除时，防止同时擦除
};

#endif // MINWHITEBOAR_PATHITEM_H
