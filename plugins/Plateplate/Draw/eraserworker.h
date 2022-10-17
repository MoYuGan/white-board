#ifndef ERASERWORKER_H
#define ERASERWORKER_H

#include <QObject>
#include <QGraphicsPathItem>
#include <QThread>
#include <QMap>
#include <QVector>
#include <QPainterPath>
#include <QtDebug>

class EraserWorker : public QObject
{
    Q_OBJECT
public:
    EraserWorker(QObject *parent = Q_NULLPTR) : QObject(parent)
    {
        m_pItemsVector.clear();
        m_pItemMap.clear();
    }

    void setNewAction(QVector<QGraphicsItem *> items,
                      const QPainterPath &path,
                      QVector<QLineF> lineVector) {
        qDebug()<<"insert";
        m_pItemsVector.insert(0, items);
        m_pPathVector.insert(0, path);
        m_pLineVector.insert(0, lineVector);
        qDebug()<<"insert finished";
    }

    QMap<QGraphicsItem *, QPainterPath> getResult() {
        return m_pItemMap;
    }

    void stop() {
        m_pContinue = false;
    }

    bool isFinished() {
        if (m_pItemsVector.isEmpty())
            return true;
        else
            return false;
    }

public slots:
    void startWorker() {
        m_pContinue = true;
        while(1) {
            qDebug()<<"==="<<m_pContinue<<m_pItemsVector.size();
            if (!m_pContinue && 0 == m_pItemsVector.size())
                break;
            if (m_pItemsVector.size() > 0)
            {
                qDebug()<<"conntinue--1";
                QVector<QGraphicsItem *> itemList = m_pItemsVector.last();
                qDebug()<<"conntinue--1-1";
                m_pItemsVector.pop_back();
                qDebug()<<"conntinue--1-1-1";
                QPainterPath path = m_pPathVector.last();
                qDebug()<<"conntinue--1-1-2";
                m_pPathVector.pop_back();
                qDebug()<<"conntinue--1-2";
                QVector<QLineF> lineVector = m_pLineVector.last();
                qDebug()<<"conntinue--1-3";
                m_pLineVector.pop_back();
                qDebug()<<"conntinue--2";
                QGraphicsPathItem *pathItem;
                QPainterPath itemPath;
                QPainterPath subPath;
                foreach(QGraphicsItem *item, itemList) {
                    if (-1 == item->zValue())
                        continue;
                    pathItem = (QGraphicsPathItem *)item;

                    if (-1 == m_pItemMap.keys().indexOf(item))
                        itemPath = pathItem->path();
                    else
                        itemPath = m_pItemMap.value(item);
                    //if (itemPath.intersects(path)) {   //Item路径的封闭区域与橡皮擦发生触碰
                    subPath = getEraserSubPath(path, lineVector, itemPath);
                    //}
                    qDebug()<<"conntinue--3";
                    //路径跟原路径不相同，说明有被擦除
                    if (subPath != itemPath) {
                        m_pItemMap.insert(item, subPath);
                    }
                }
                QThread::msleep(20);
            }
        }
        emit workFinished();
    }
signals:
    void workFinished();

private:
    bool m_pContinue;
    bool m_pNewAction;
    QVector<QVector<QGraphicsItem *>> m_pItemsVector;
    QVector<QPainterPath> m_pPathVector;
    QVector<QVector<QLineF>> m_pLineVector;
    QMap<QGraphicsItem *, QPainterPath> m_pItemMap;

    QPainterPath getEraserSubPath(const QPainterPath &path, QVector<QLineF> lineVector, const QPainterPath &srcPath)
    {
        QPainterPath::Element element1;
        QPainterPath::Element element2;

        QPainterPath subPath;

        int eCount = srcPath.elementCount();
        QPointF ePoint1, ePoint2;
        QLineF eLine;
        QPointF iPoint;         //相交点
        QVector<QPointF> iPointList;    //相交点集合
        for (int i = 0; i < eCount - 1;) {
            iPointList.clear();

            element1 = srcPath.elementAt(i);
            element2 = srcPath.elementAt(++i);
            ePoint1 = QPointF(element1.x, element1.y);
            ePoint2 = QPointF(element2.x, element2.y);

            if (element1.type != QPainterPath::MoveToElement && element2.isMoveTo())
                continue;
            else if (element1.isMoveTo() && element2.isMoveTo()) {
                if (!path.contains(ePoint1))
                    subPath.moveTo(ePoint1);
                continue;
            }
            /*
             * 当前点是MoveTo，后点是LineTo，或者两点都是LineTo才判断交点
             */
            eLine = QLineF(ePoint1, ePoint2);
            if (path.contains(ePoint1) && path.contains(ePoint2)) {       //两个点都在橡皮擦内
                continue;
            }

            //判断两点组成得线段与擦除矩形框得相交情况，QLineF::BoundedIntersection表示相交点不是位于延长线上（真实相交）
            foreach(QLineF linef, lineVector) {
                if (QLineF::BoundedIntersection == eLine.intersect(linef, &iPoint)) { //与多边形区域的边是否相交
                    iPointList.push_back(iPoint);
                }
            }

            if (iPointList.size() > 1) //两个交点
            {
                if (path.contains(ePoint1)) {   //前点在边缘
                    iPointList.removeOne(ePoint1);
                    subPath.moveTo(iPointList.at(0));
                    subPath.lineTo(ePoint2);
                }else if (path.contains(ePoint2)) {     //后点在边缘
                    if (element1.isMoveTo()) {      //前点是MoveTo,还未被记录
                        subPath.moveTo(ePoint1);
                    }
                    iPointList.removeOne(ePoint2);
                    subPath.lineTo(iPointList.at(0));
                }else {     //两个端点都不在橡皮擦内
                    if (element1.isMoveTo()) {      //前点是MoveTo,还未被记录
                        subPath.moveTo(ePoint1);
                    }

                    /*判断线段两个端点和两个交点的位置关系*/
                    if (ePoint1.x() == ePoint2.x()) {   //线段是竖直方向垂直过矩形框
                        if (ePoint1.y() < ePoint2.y()) {    //向下垂直
                            if (iPointList.at(0).y() < iPointList.at(1).y()) {
                                subPath.lineTo(iPointList.at(0));
                                subPath.moveTo(iPointList.at(1));
                            }else {
                                subPath.lineTo(iPointList.at(1));
                                subPath.moveTo(iPointList.at(0));
                            }
                        }else {     //向上垂直
                            if (iPointList.at(0).y() > iPointList.at(1).y()) {
                                subPath.lineTo(iPointList.at(0));
                                subPath.moveTo(iPointList.at(1));
                            }else {
                                subPath.lineTo(iPointList.at(1));
                                subPath.moveTo(iPointList.at(0));
                            }
                        }
                    }else if (ePoint1.x() < ePoint2.x()) {  //线段是水平坐标系左方往右方向过矩形框
                        if (iPointList.at(0).x() < iPointList.at(1).x()) {
                            subPath.lineTo(iPointList.at(0));
                            subPath.moveTo(iPointList.at(1));
                        }else {
                            subPath.lineTo(iPointList.at(1));
                            subPath.moveTo(iPointList.at(0));
                        }
                    }else {     //线段是水平坐标系右方往左方向过矩形框
                        if (iPointList.at(0).x() > iPointList.at(1).x()) {
                            subPath.lineTo(iPointList.at(0));
                            subPath.moveTo(iPointList.at(1));
                        }else {
                            subPath.lineTo(iPointList.at(1));
                            subPath.moveTo(iPointList.at(0));
                        }
                    }
                    subPath.lineTo(ePoint2);
                }
            }
            else if (1 == iPointList.size() && !path.contains(ePoint1) && !path.contains(ePoint2))  //相切,一个交点
            {
                if (element1.isMoveTo()) {  //前点是MoveTo,还未被记录
                    subPath.moveTo(ePoint1);
                }
                subPath.lineTo(iPointList.at(0));
            }
            else if (1 == iPointList.size()) //其中一个点在橡皮擦框里面
            {
                if (path.contains(ePoint1)) { //前点在框里
                    subPath.moveTo(iPointList.at(0));
                    subPath.lineTo(ePoint2);
                }else {
                    if (element1.isMoveTo())
                        subPath.moveTo(ePoint1);

                    subPath.lineTo(iPointList.at(0));
                }
            }else {
                if (element1.isMoveTo())
                    subPath.moveTo(ePoint1);
                subPath.lineTo(ePoint2);
            }
        }

        return subPath;
    }
};

#endif // ERASERWORKER_H
