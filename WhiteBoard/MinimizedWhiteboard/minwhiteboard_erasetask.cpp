#include "minwhiteboard_erasetask.h"
#include <QtDebug>

MinWhiteBoard_EraseTask::MinWhiteBoard_EraseTask(MinWhiteBoar_PathItem *item, QPainterPath path)
{
    m_Item = item;
    m_ErasePath = path;
    qRegisterMetaType<QPainterPath>("QPainterPath");
}

MinWhiteBoard_EraseTask::~MinWhiteBoard_EraseTask()
{}

void MinWhiteBoard_EraseTask::run(void)
{
    if (nullptr == m_Item)
        return;

    while (m_Item->m_EraseLock)
        QThread::sleep(2);

    m_Item->m_EraseLock = true;
    this->getEraserSubPath(m_Item);
    m_Item->m_EraseLock = false;

}

void MinWhiteBoard_EraseTask::getEraserSubPath(MinWhiteBoar_PathItem *pathitem)
{
    QPainterPath srcPath = pathitem->path();
    QPainterPath::Element element;
    QPainterPath newPath;
    QPainterPath subPath;
    //QList<QPainterPath> subPaths;
    bool isMoveTo = true;
    for(int i = 0; i < srcPath.elementCount(); i++) {
        element = srcPath.elementAt(i);
        QPointF p = QPointF(element.x, element.y);
        if (m_ErasePath.contains(p)) {
            isMoveTo = true;
            continue;
        }else {
            if (isMoveTo || element.isMoveTo()) {
                isMoveTo = false;
                if (!subPath.isEmpty()) {
                    //subPaths.push_back(subPath);
                    subPath = QPainterPath();
                }
                newPath.moveTo(p);
                subPath.moveTo(p);
            }else {
                newPath.lineTo(p);
                subPath.lineTo(p);
            }
        }
    }
    emit eraseFinish(newPath);
}
