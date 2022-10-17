#ifndef CUBEITEM_H
#define CUBEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainterPath>
#include <Public/public_function.h>
#include <QGraphicsPathItem>
#include <QPainter>

class CubeItem : public QObject,public QGraphicsPathItem
{
    Q_OBJECT
public:
    explicit CubeItem(QGraphicsItem *parent = nullptr);
    void drawItemPath(QPainterPath ,QPainterPath);

protected:
    //QPainterPath shape()const;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


signals:

private:
    QPainterPath inpath;
    QPainterPath outpath;

};

#endif // CUBEITEM_H
