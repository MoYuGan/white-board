#ifndef MINWHITEBOARD_ERASETASK_H
#define MINWHITEBOARD_ERASETASK_H

#include <QObject>
#include <QRunnable>
#include <QGraphicsPathItem>
#include <QThread>
#include <QVector>
#include <QPainterPath>
#include <QMetaType>
#include "minwhiteboar_pathitem.h"

class MinWhiteBoard_EraseTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    MinWhiteBoard_EraseTask(MinWhiteBoar_PathItem *item, QPainterPath path);
    ~MinWhiteBoard_EraseTask();

protected:
    void run(void) override;

private:
    MinWhiteBoar_PathItem *m_Item = nullptr;
    QPainterPath m_ErasePath;
    QVector<QPainterPath> m_SubPathList;
private:
    void getEraserSubPath(MinWhiteBoar_PathItem *item);

signals:
    void eraseFinish(QPainterPath);

public slots:
};

#endif // MINWHITEBOARD_ERASETASK_H
