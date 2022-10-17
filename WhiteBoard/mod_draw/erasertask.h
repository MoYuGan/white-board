#ifndef ERASERTASK_H
#define ERASERTASK_H

#include <QObject>
#include <QRunnable>
#include <QGraphicsItem>
#include <QThread>
#include <QVector>
#include <QPainterPath>
#include <QMetaType>
#include "CustomGraphicsItem/pathitem.h"
#include "CustomGraphicsItem/graphicsitem.h"
#include "CustomGraphicsItem/lineitem.h"

class EraserTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    EraserTask(QGraphicsItem *item, QPainterPath path);
    ~EraserTask();

protected:
    void run(void) override;

private:
    QGraphicsItem *m_Item = nullptr;
    QPainterPath m_ErasePath;
    QVector<QPainterPath> m_SubPathList;

private:
    void getEraserSubPath(PathItem *item);

signals:
    void eraseFinish(QList<QPainterPath> );

public slots:
};

#endif // ERASERTASK_H
