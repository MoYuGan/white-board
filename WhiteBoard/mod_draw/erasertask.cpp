#include "erasertask.h"
#include <QtDebug>

EraserTask::EraserTask(QGraphicsItem *item, QPainterPath path)
{
    m_Item = item;
    m_ErasePath = path;
    qRegisterMetaType<QPainterPath>("QPainterPath");
    qRegisterMetaType<QList<QPainterPath>>("QList<QPainterPath>");
}

EraserTask::~EraserTask()
{}

void EraserTask::run(void)
{
    if (nullptr == m_Item)
        return;

    if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == m_Item->type())  //pathitem
    {
        m_SubPathList.clear();
        PathItem *pathitem = static_cast<PathItem *>(m_Item);
        while (pathitem->m_EraseLock)
            QThread::sleep(2);

        pathitem->m_EraseLock = true;
        this->getEraserSubPath(pathitem);
        pathitem->m_EraseLock = false;
    }
}

void EraserTask::getEraserSubPath(PathItem *pathitem)
{
    QPainterPath srcPath = pathitem->path();
    QPainterPath::Element element;
    QPainterPath newPath;
    QPainterPath subPath;
    QList<QPainterPath> listPath;
    bool isMoveTo = true;
    for(int i = 0; i < srcPath.elementCount(); i++)
    {
        element = srcPath.elementAt(i);
        QPointF p = QPointF(element.x, element.y);
        if (m_ErasePath.contains(p)) {
            isMoveTo = true;
            continue;
        }else {
            if (isMoveTo || element.isMoveTo())
            {
                isMoveTo = false;
                if (!subPath.isEmpty()) {
                    listPath.push_back(subPath);
                    subPath = QPainterPath();
                    newPath.clear();
                }
                newPath.moveTo(p);
                subPath.moveTo(p);
            }else
            {
                newPath.lineTo(p);
                subPath.lineTo(p);
            }
        } 
    }
    listPath.push_back(newPath);
    if(listPath.at(0) != srcPath)
    {
        emit eraseFinish(listPath);
    }
}
