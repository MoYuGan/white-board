#ifndef CUSTOMITEM_CUBE_H
#define CUSTOMITEM_CUBE_H

/* 立方体 */

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include "Public/public_function.h"
#include <QtDebug>
#include <math.h>

class CustomItem_Cube : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:
    enum AdjustDirection {
        Long,
        Height,
        Width,
        None
    };

public:
    CustomItem_Cube(QGraphicsItem *parent = Q_NULLPTR) : QGraphicsPathItem(parent)
    {
        //开启鼠标跟踪
        this->setAcceptHoverEvents(true);
        this->setAcceptTouchEvents(true);

        m_pSolidPath = QPainterPath();
        m_pDashPath = QPainterPath();
        m_pAdjustDirection = AdjustDirection::None;
    }

    /*自定义Type*/
    enum { Type = UserType + 103 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    void setAdjust(bool bo) {
        m_pAdjustSize = bo;
        this->update();
    }

    inline bool isAdjustSize() { return m_pAdjustSize; }

    QRectF boundingRect() const Q_DECL_OVERRIDE{
        return m_pSolidPath.boundingRect();
    }

    QPainterPath shape() const Q_DECL_OVERRIDE{
        QPainterPath path;
        QPainterPath retPath;
        path.moveTo(m_pTopPointList.at(0));
        path.lineTo(m_pTopPointList.at(1));
        path.lineTo(m_pTopPointList.at(2));
        path.lineTo(m_pTopPointList.at(3));
        path.lineTo(m_pTopPointList.at(0));
        retPath += path;
        path -= path;
        path.moveTo(m_pTopPointList.at(0));
        path.lineTo(m_pBottomPointList.at(0));
        path.lineTo(m_pBottomPointList.at(3));
        path.lineTo(m_pTopPointList.at(3));
        path.lineTo(m_pTopPointList.at(0));
        retPath += path;
        path -= path;
        path.moveTo(m_pTopPointList.at(3));
        path.lineTo(m_pTopPointList.at(2));
        path.lineTo(m_pBottomPointList.at(2));
        path.lineTo(m_pBottomPointList.at(3));
        path.lineTo(m_pTopPointList.at(3));
        retPath += path;
        path -= path;
        int radius = Public_Function::getScaleSize(10);
        path.addEllipse(m_pAdjustHeightPoint, radius, radius);
        retPath += path;
        path -= path;
        path.addEllipse(m_pAdjustLongPoint, radius, radius);
        retPath += path;
        path -= path;
        path.addEllipse(m_pAdjustWidthPoint, radius, radius);
        retPath += path;

        return retPath;
    }

    //创建立方体完成，初始化调节点等
    void createdCubeFinish() {
        this->refreshPointList();
        if (m_pTopPointList.at(0).y() > m_pBottomPointList.at(0).y())      //第二次绘制的面是顶面,调换存储容器值
        {
            QList<QPointF> pointList = m_pBottomPointList;
            m_pBottomPointList = m_pTopPointList;
            m_pTopPointList = pointList;
        }
        m_pAdjustSize = true;
        this->refreshShow();
    }

    //绘制立方体的底面（上面）
    void addRect(const QPointF &topLeft, const QPointF &bottomRight) {
        QPointF interPoint1, interPoint2;
        this->getIntersectPoint(topLeft, bottomRight, &interPoint1, &interPoint2);

        QPainterPath solidPath;
        solidPath.moveTo(topLeft);
        solidPath.lineTo(interPoint1);
        solidPath.lineTo(bottomRight);
        solidPath.lineTo(interPoint2);
        solidPath.lineTo(topLeft);
        m_pSolidPath = solidPath;

        m_pTopPointList = QList<QPointF>() << topLeft << bottomRight << interPoint1 << interPoint2;
        this->update();
    }

    void addRect2(qreal height) {
        QPointF topLeft = QPointF(m_pTopPointList.at(0).x(), m_pTopPointList.at(0).y() + height);
        QPointF bottomRight = QPointF(m_pTopPointList.at(1).x(), m_pTopPointList.at(1).y() + height);
        QPointF interPoint1, interPoint2;
        this->getIntersectPoint(topLeft, bottomRight, &interPoint1, &interPoint2);

        QPainterPath solidPath;
        solidPath.moveTo(m_pTopPointList.at(0));
        solidPath.lineTo(m_pTopPointList.at(2));
        solidPath.lineTo(m_pTopPointList.at(1));
        solidPath.lineTo(m_pTopPointList.at(3));
        solidPath.lineTo(m_pTopPointList.at(0));

        solidPath.moveTo(topLeft);
        solidPath.lineTo(interPoint1);
        solidPath.lineTo(bottomRight);
        solidPath.lineTo(interPoint2);
        solidPath.lineTo(topLeft);

        solidPath.moveTo(m_pTopPointList.at(0));
        solidPath.lineTo(topLeft);
        solidPath.moveTo(m_pTopPointList.at(2));
        solidPath.lineTo(interPoint1);
        solidPath.moveTo(m_pTopPointList.at(3));
        solidPath.lineTo(interPoint2);
        m_pSolidPath = solidPath;

        m_pBottomPointList = QList<QPointF>() << topLeft << bottomRight << interPoint1 << interPoint2;
        this->update();
    }

    void setAdjustSize(bool bo) {
        m_pAdjustSize = bo;
    }

    void moveItem(const QPointF &pt) {
        qreal subX = pt.x();
        qreal subY = pt.y();
        //重新设置上下面的8个点
        m_pTopPointList.replace(0, QPointF(m_pTopPointList.at(0).x() + subX, m_pTopPointList.at(0).y() + subY));
        m_pTopPointList.replace(1, QPointF(m_pTopPointList.at(1).x() + subX, m_pTopPointList.at(1).y() + subY));
        m_pTopPointList.replace(2, QPointF(m_pTopPointList.at(2).x() + subX, m_pTopPointList.at(2).y() + subY));
        m_pTopPointList.replace(3, QPointF(m_pTopPointList.at(3).x() + subX, m_pTopPointList.at(3).y() + subY));
        m_pBottomPointList.replace(0, QPointF(m_pBottomPointList.at(0).x() + subX, m_pBottomPointList.at(0).y() + subY));
        m_pBottomPointList.replace(1, QPointF(m_pBottomPointList.at(1).x() + subX, m_pBottomPointList.at(1).y() + subY));
        m_pBottomPointList.replace(2, QPointF(m_pBottomPointList.at(2).x() + subX, m_pBottomPointList.at(2).y() + subY));
        m_pBottomPointList.replace(3, QPointF(m_pBottomPointList.at(3).x() + subX, m_pBottomPointList.at(3).y() + subY));
        this->refreshShow();
    }

    //旋转Item
    void rotateItem(const qreal &angle, const QPointF &center) {
        m_pRotateAngle += angle;
        /*旋转QLineF,旋转中心是（0， 0）*/
        QTransform transform;
        transform.rotate(angle, Qt::ZAxis);
        /* 设置旋转中心 */
        QPointF tCenter = transform.map(center);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());

        //重新设置上下面的8个点
        m_pTopPointList.replace(0, transform.map(m_pTopPointList.at(0)));
        m_pTopPointList.replace(1, transform.map(m_pTopPointList.at(1)));
        m_pTopPointList.replace(2, transform.map(m_pTopPointList.at(2)));
        m_pTopPointList.replace(3, transform.map(m_pTopPointList.at(3)));
        m_pBottomPointList.replace(0, transform.map(m_pBottomPointList.at(0)));
        m_pBottomPointList.replace(1, transform.map(m_pBottomPointList.at(1)));
        m_pBottomPointList.replace(2, transform.map(m_pBottomPointList.at(2)));
        m_pBottomPointList.replace(3, transform.map(m_pBottomPointList.at(3)));

        //this->refreshPointList();
        this->refreshShow();
        return;
    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {

        Q_UNUSED(option)
        Q_UNUSED(widget)

        if (!this->isSelected() && m_pAdjustSize)
            m_pAdjustSize = false;

        painter->setBrush(QBrush());
        QPen pen = this->pen();
        if (!m_pDashPath.isEmpty()) {
            pen.setStyle(Qt::DashLine);
            pen.setColor(QColor(135, 135, 135, 135));
            painter->setPen(pen);
            painter->drawPath(m_pDashPath);
        }else if (m_pBottomPointList.size() == 4 && !m_pBottomPointList.at(1).isNull()){
            pen.setColor(QColor(255,168,0));
            painter->setPen(pen);
            painter->drawLine(QLineF(m_pTopPointList.at(1), m_pBottomPointList.at(1)));
        }

        pen = this->pen();
        if (!m_pSolidPath.isEmpty()) {
            pen.setStyle(Qt::SolidLine);
            painter->setPen(pen);
            painter->drawPath(m_pSolidPath);
        }

        if (m_pAdjustSize) {
            int radius = Public_Function::getScaleSize(8);
            pen.setColor(QColor(103,194,85));
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(103,194,85)));
            painter->drawEllipse(m_pAdjustHeightPoint, radius, radius);
            painter->drawLine(QLineF(m_pAdjustHeightPoint, m_pBottomCenter));
            pen.setColor(QColor(84,155,235));
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(84,155,235)));
            painter->drawEllipse(m_pAdjustLongPoint, radius, radius);
            painter->drawLine(QLineF(m_pAdjustLongPoint, m_pBottomCenter));
            pen.setColor(QColor(235,99,65));
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(235,99,65)));
            painter->drawEllipse(m_pAdjustWidthPoint, radius, radius);
            painter->drawLine(QLineF(m_pAdjustWidthPoint, m_pBottomCenter));
        }
    }

    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event){
        QPointF mousePos = event->pos();
        if (m_pAdjustSize) {    //调节模式
            int radius = Public_Function::getScaleSize(10);
            if (QLineF(mousePos, m_pAdjustHeightPoint).length() <= radius ||
                    QLineF(mousePos, m_pAdjustWidthPoint).length() <= radius ||
                    QLineF(mousePos, m_pAdjustLongPoint).length() <= radius) {
                QCursor cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao5@2x.png")
                                         .scaled(Public_Function::getScaleSize(QSize(24, 24))));
                this->setCursor(cursor);
            }
        }else {
            if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
                return;
            if (this->isSelected())
                return;
            QCursor cursor;
            if (this->shape().contains(mousePos)){
                cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png")
                                 .scaled(Public_Function::getScaleSize(QSize(24, 24))));
            }else {
                cursor = Qt::ArrowCursor;
            }
        }
        return QGraphicsPathItem::hoverMoveEvent(event);
    }

    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
        this->setCursor(Qt::ArrowCursor);
        return QGraphicsPathItem::hoverLeaveEvent(event);
    }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event){
        QPointF mousePos = event->pos();
        if (m_pAdjustSize) {
            int radius = Public_Function::getScaleSize(10);
            if (QLineF(mousePos, m_pAdjustHeightPoint).length() <= radius) {
                m_pAdjustDirection = AdjustDirection::Height;
            }else if (QLineF(mousePos, m_pAdjustLongPoint).length() <= radius) {
                m_pAdjustDirection = AdjustDirection::Long;
            }else if (QLineF(mousePos, m_pAdjustWidthPoint).length() <= radius) {
                m_pAdjustDirection = AdjustDirection::Width;
            }
            if (m_pAdjustDirection != AdjustDirection::None)
                emit adjustStart();
        }else {
            if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
                return;
            if (this->isSelected())
                return;
            m_pHasMouseMove = false;
            m_pMouseLastPoint = event->pos();
            m_pMousePressedPoint = event->pos();
        }

        return;
    }

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
        QPointF mousePos = event->pos();
        if (m_pAdjustSize) {
            if (AdjustDirection::Height == m_pAdjustDirection) {
                //设置最小高度值
                qreal minHeight = Public_Function::getScaleSize(30);
                //得到新的高度调节点
                QPointF newAdjustHeightPoint = QPointF(m_pAdjustHeightPoint.x(), mousePos.y());
                //计算新的高度调节点与原高度调节点Y方向的差值
                qreal subY = m_pAdjustHeightPoint.y() - newAdjustHeightPoint.y();   //为正值时增加高度
                //判断原有高度值减去两倍差值（绝对值）是否小于最小高度值
                QLineF line = QLineF(m_pBottomCenter, m_pAdjustHeightPoint);
                if (line.length() + 2*subY < minHeight) {
                    if (line.length() == minHeight)    //已经是最小值，返回
                        return;
                    //计算新的差值
                    subY = subY < 0 ? -(line.length() - minHeight)/2.0  : (line.length() - minHeight)/2.0;
                }
                //重新设置上下面的8个点
                m_pTopPointList.replace(0, QPointF(m_pTopPointList.at(0).x(), m_pTopPointList.at(0).y() - subY));
                m_pTopPointList.replace(1, QPointF(m_pTopPointList.at(1).x(), m_pTopPointList.at(1).y() - subY));
                m_pTopPointList.replace(2, QPointF(m_pTopPointList.at(2).x(), m_pTopPointList.at(2).y() - subY));
                m_pTopPointList.replace(3, QPointF(m_pTopPointList.at(3).x(), m_pTopPointList.at(3).y() - subY));
                m_pBottomPointList.replace(0, QPointF(m_pBottomPointList.at(0).x(), m_pBottomPointList.at(0).y() + subY));
                m_pBottomPointList.replace(1, QPointF(m_pBottomPointList.at(1).x(), m_pBottomPointList.at(1).y() + subY));
                m_pBottomPointList.replace(2, QPointF(m_pBottomPointList.at(2).x(), m_pBottomPointList.at(2).y() + subY));
                m_pBottomPointList.replace(3, QPointF(m_pBottomPointList.at(3).x(), m_pBottomPointList.at(3).y() + subY));
            }else if (AdjustDirection::Width == m_pAdjustDirection) {
                //创建一条以鼠标点为基点，X轴正方向的射线
                QLineF line = QLineF(mousePos, QPointF(mousePos.x() + 10, mousePos.y()));
                //以鼠标点为圆心，将该射线旋转120度得到新的线
                QTransform transform;
                transform.rotate(120, Qt::ZAxis);
                QPointF rotateCenter = transform.map(mousePos);
                transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                                    transform.m21(), transform.m22(), transform.m23(),
                                    mousePos.x() - rotateCenter.x(), mousePos.y() - rotateCenter.y(), transform.m33());
                QLineF rotateLine = transform.map(line);

                /*旋转QLineF,旋转中心是（0， 0）*/
                transform = QTransform();
                transform.rotate(m_pRotateAngle, Qt::ZAxis);
                /* 设置旋转中心 */
                QPointF center = this->boundingRect().center();
                QPointF tCenter = transform.map(center);
                transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                                    transform.m21(), transform.m22(), transform.m23(),
                                    center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
                rotateLine = transform.map(rotateLine);

                //获取上面的射线与底部中心点到宽度调节点的线的交点就是新的长度调节点位置
                QPointF newAdjustWidthPoint;
                QLineF(m_pBottomCenter, m_pAdjustWidthPoint).intersect(rotateLine, &newAdjustWidthPoint);
                //如果新的调节点位于底部中心点的左方，无效点
                if (newAdjustWidthPoint.x() < m_pBottomCenter.x())
                    return;
                //判断中心点到调节点的长度是否小于最小值
                qreal minWidth = Public_Function::getScaleSize(30);
                line = QLineF(m_pBottomCenter, newAdjustWidthPoint);
                if (line.length() < minWidth) {
                    if (QLineF(m_pBottomCenter, m_pAdjustWidthPoint).length() == minWidth)  //已经是最小值
                        return;
                    //设置调节点为调节杆长度最小值那个点
                    line.setLength(minWidth);
                    newAdjustWidthPoint = line.p2();
                }

                //获取旧调节点与新调节点X方向和Y方向的一个差值
                qreal subX = m_pAdjustWidthPoint.x() - newAdjustWidthPoint.x(); //为负值时增加长度
                qreal subY = m_pAdjustWidthPoint.y() - newAdjustWidthPoint.y(); //为负值时增加长度
                //重新设置上下面的8个点
                m_pTopPointList.replace(0, QPointF(m_pTopPointList.at(0).x() + subX, m_pTopPointList.at(0).y() + subY));
                m_pTopPointList.replace(1, QPointF(m_pTopPointList.at(1).x() + subX, m_pTopPointList.at(1).y() + subY));
                m_pTopPointList.replace(2, QPointF(m_pTopPointList.at(2).x() - subX, m_pTopPointList.at(2).y() - subY));
                m_pTopPointList.replace(3, QPointF(m_pTopPointList.at(3).x() - subX, m_pTopPointList.at(3).y() - subY));
                m_pBottomPointList.replace(0, QPointF(m_pBottomPointList.at(0).x() + subX, m_pBottomPointList.at(0).y() + subY));
                m_pBottomPointList.replace(1, QPointF(m_pBottomPointList.at(1).x() + subX, m_pBottomPointList.at(1).y() + subY));
                m_pBottomPointList.replace(2, QPointF(m_pBottomPointList.at(2).x() - subX, m_pBottomPointList.at(2).y() - subY));
                m_pBottomPointList.replace(3, QPointF(m_pBottomPointList.at(3).x() - subX, m_pBottomPointList.at(3).y() - subY));
            }else if (AdjustDirection::Long == m_pAdjustDirection) {
                //创建一条以鼠标点为基点，X轴正方向的射线
                QLineF line = QLineF(mousePos, QPointF(mousePos.x() + 10, mousePos.y()));
                //以鼠标点为圆心，将该射线旋转60度得到新的线
                QTransform transform;
                transform.rotate(60, Qt::ZAxis);
                QPointF rotateCenter = transform.map(mousePos);
                transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                                    transform.m21(), transform.m22(), transform.m23(),
                                    mousePos.x() - rotateCenter.x(), mousePos.y() - rotateCenter.y(), transform.m33());
                QLineF rotateLine = transform.map(line);

                /*旋转QLineF,旋转中心是（0， 0）*/
                transform = QTransform();
                transform.rotate(m_pRotateAngle, Qt::ZAxis);
                /* 设置旋转中心 */
                QPointF center = this->boundingRect().center();
                QPointF tCenter = transform.map(center);
                transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                                    transform.m21(), transform.m22(), transform.m23(),
                                    center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
                rotateLine = transform.map(rotateLine);

                //获取上面的射线与底部中心点到长度调节点的线的交点就是新的长度调节点位置
                QPointF newAdjustLongPoint;
                QLineF(m_pBottomCenter, m_pAdjustLongPoint).intersect(rotateLine, &newAdjustLongPoint);
                //如果新的调节点位于底部中心点的上方，无效点
                if (newAdjustLongPoint.y() < m_pBottomCenter.y())
                    return;
                //判断中心点到调节点的长度是否小于最小值
                qreal minLength = Public_Function::getScaleSize(30);
                line = QLineF(m_pBottomCenter, newAdjustLongPoint);
                if (line.length() < minLength) {
                    line = QLineF(m_pBottomCenter, m_pAdjustLongPoint);
                    if (line.length() == minLength)  //已经是最小值
                        return;
                    //设置调节点为调节杆长度最小值那个点
                    newAdjustLongPoint = line.pointAt(minLength/line.length());
                }
                //获取旧调节点与新调节点X方向和Y方向的一个差值
                qreal subX = m_pAdjustLongPoint.x() - newAdjustLongPoint.x(); //为正值时增加长度
                qreal subY = m_pAdjustLongPoint.y() - newAdjustLongPoint.y(); //为负值时增加长度

                //重新设置上下面的8个点
                m_pTopPointList.replace(0, QPointF(m_pTopPointList.at(0).x() - subX, m_pTopPointList.at(0).y() - subY));
                m_pTopPointList.replace(1, QPointF(m_pTopPointList.at(1).x() + subX, m_pTopPointList.at(1).y() + subY));
                m_pTopPointList.replace(2, QPointF(m_pTopPointList.at(2).x() + subX, m_pTopPointList.at(2).y() + subY));
                m_pTopPointList.replace(3, QPointF(m_pTopPointList.at(3).x() - subX, m_pTopPointList.at(3).y() - subY));
                m_pBottomPointList.replace(0, QPointF(m_pBottomPointList.at(0).x() - subX, m_pBottomPointList.at(0).y() - subY));
                m_pBottomPointList.replace(1, QPointF(m_pBottomPointList.at(1).x() + subX, m_pBottomPointList.at(1).y() + subY));
                m_pBottomPointList.replace(2, QPointF(m_pBottomPointList.at(2).x() + subX, m_pBottomPointList.at(2).y() + subY));
                m_pBottomPointList.replace(3, QPointF(m_pBottomPointList.at(3).x() - subX, m_pBottomPointList.at(3).y() - subY));
            }
            this->refreshShow();
        }else {
            if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
                return;
            if (this->isSelected())
                return;

            //超过5个像素点才当做移动，防止大屏上面无法点击
            QPointF mousePos = event->pos();
            if (qAbs(mousePos.x() - m_pMousePressedPoint.x()) < 5 &&
                    qAbs(mousePos.y() - m_pMousePressedPoint.y()) < 5)
                return;

            m_pHasMouseMove = true;
            qreal subX = mousePos.x() - m_pMouseLastPoint.x();
            qreal subY = mousePos.y() - m_pMouseLastPoint.y();
            this->moveItem(QPointF(subX, subY));

            m_pMouseLastPoint = mousePos;
        }
    }

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
        if (m_pAdjustSize) {
            if (AdjustDirection::None != m_pAdjustDirection)
            {
                m_pAdjustDirection = AdjustDirection::None;
                emit adjustFinished();
            }
        }else {
            if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
                return;
            //单击事件，选中Item
            if (!m_pHasMouseMove && !this->isSelected()) {
                emit itemSelected();
                this->setSelected(true);
            }
        }
        //
//        if (m_pHasMouseMove) {
//            emit this->itemHasChanged(this);
//        }
    }

private:
    QList<QPointF> m_pTopPointList;        //立方体顶部四个点,先存储最左边的点，顺时针存储
    QList<QPointF> m_pBottomPointList;     //立方体底部四个点,先存储最左边的点，顺时针存储
    QPainterPath m_pSolidPath;              //实线路径
    QPainterPath m_pDashPath;               //虚线路径
    bool m_pAdjustSize = false;             //打开调节模式标志位
    QPointF m_pAdjustHeightPoint;           //高度调节点
    QPointF m_pAdjustLongPoint;             //长度调节点
    QPointF m_pAdjustWidthPoint;            //宽度调节点
    QPointF m_pBottomCenter;                //底部中点
    AdjustDirection m_pAdjustDirection;     //调节方向
    bool m_pHasMouseMove = false;
    QPointF m_pMouseLastPoint;
    QPointF m_pMousePressedPoint;
    qreal m_pRotateAngle = 0;

    //获取交点
    void getIntersectPoint(const QPointF &topLeft, const QPointF &bottomRight, QPointF *ipoint1, QPointF *ipoint2) {
        //以topleft点为基点作X轴负方向射线
        QLineF line1 = QLineF(topLeft, QPointF(topLeft.x() - 10, topLeft.y()));
        //以bottomRight为基点作X轴负方向射线
        QLineF line2 = QLineF(bottomRight, QPointF(bottomRight.x() - 10, bottomRight.y()));
        QTransform transform;
        //以topleft为旋转中心，旋转line1
        transform.rotate(-30, Qt::ZAxis);
        QPointF rotateCenter = transform.map(topLeft);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            topLeft.x() - rotateCenter.x(), topLeft.y() - rotateCenter.y(), transform.m33());
        QLineF rotateLine1 = transform.map(line1);
        //以bottomRight为旋转中心，旋转line2
        transform = QTransform();
        transform.rotate(10, Qt::ZAxis);
        rotateCenter = transform.map(bottomRight);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            bottomRight.x() - rotateCenter.x(), bottomRight.y() - rotateCenter.y(), transform.m33());
        //得到旋转后line1和旋转后line2线的交点
        QLineF rotateLine2 = transform.map(line2);
        rotateLine1.intersect(rotateLine2, ipoint1);

        //以topleft点为基点作X轴正方向射线
        QLineF line3 = QLineF(topLeft, QPointF(topLeft.x() + 10, topLeft.y()));
        //以bottomRight为基点作X轴正方向射线
        QLineF line4 = QLineF(bottomRight, QPointF(bottomRight.x() + 10, bottomRight.y()));
        //以topleft为旋转中心，旋转line3
        transform = QTransform();
        transform.rotate(10, Qt::ZAxis);
        rotateCenter = transform.map(topLeft);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            topLeft.x() - rotateCenter.x(), topLeft.y() - rotateCenter.y(), transform.m33());
        QLineF rotateLine3 = transform.map(line3);
        //以bottomRight为旋转中心，旋转line4
        transform = QTransform();
        transform.rotate(-30, Qt::ZAxis);
        rotateCenter = transform.map(bottomRight);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            bottomRight.x() - rotateCenter.x(), bottomRight.y() - rotateCenter.y(), transform.m33());
        //得到旋转后line3和旋转后line4线的交点
        QLineF rotateLine4 = transform.map(line4);
        rotateLine3.intersect(rotateLine4, ipoint2);
    }

    //对坐标点进行排序，根据X坐标值排序，返回值X由小到大(注意：立方体的顶部和底部四个点X坐标值一定是不同的)
    QList<QPointF> qSortPointsWithX(QList<QPointF> pointList) {
        QList<QPointF> newPointList;
        if (pointList.size() != 4)
            return newPointList;
        QList<qreal> list;
        list << pointList.at(0).x() << pointList.at(1).x()
             << pointList.at(2).x() << pointList.at(3).x();
        qSort(list.begin(), list.end());
        if (list.at(0) == pointList.at(0).x())
            newPointList.push_back(pointList.at(0));
        else if (list.at(0) == pointList.at(1).x())
            newPointList.push_back(pointList.at(1));
        else if (list.at(0) == pointList.at(2).x())
            newPointList.push_back(pointList.at(2));
        else if (list.at(0) == pointList.at(3).x())
            newPointList.push_back(pointList.at(3));

        if (list.at(1) == pointList.at(0).x())
            newPointList.push_back(pointList.at(0));
        else if (list.at(1) == pointList.at(1).x())
            newPointList.push_back(pointList.at(1));
        else if (list.at(1) == pointList.at(2).x())
            newPointList.push_back(pointList.at(2));
        else if (list.at(1) == pointList.at(3).x())
            newPointList.push_back(pointList.at(3));

        if (list.at(2) == pointList.at(0).x())
            newPointList.push_back(pointList.at(0));
        else if (list.at(2) == pointList.at(1).x())
            newPointList.push_back(pointList.at(1));
        else if (list.at(2) == pointList.at(2).x())
            newPointList.push_back(pointList.at(2));
        else if (list.at(2) == pointList.at(3).x())
            newPointList.push_back(pointList.at(3));

        if (list.at(3) == pointList.at(0).x())
            newPointList.push_back(pointList.at(0));
        else if (list.at(3) == pointList.at(1).x())
            newPointList.push_back(pointList.at(1));
        else if (list.at(3) == pointList.at(2).x())
            newPointList.push_back(pointList.at(2));
        else if (list.at(3) == pointList.at(3).x())
            newPointList.push_back(pointList.at(3));

        return newPointList;
    }

    //对坐标点进行排序，根据Y坐标值排序，返回值X由小到大(注意：立方体的顶部和底部四个点Y坐标值一定是不同的)
    QList<QPointF> qSortPointsWithY(QList<QPointF> pointList) {
        QList<QPointF> newPointList;
        if (pointList.size() != 4)
            return newPointList;
        QList<qreal> list;
        list << pointList.at(0).y() << pointList.at(1).y()
             << pointList.at(2).y() << pointList.at(3).y();
        qSort(list.begin(), list.end());
        if (list.at(0) == pointList.at(0).y())
            newPointList.push_back(pointList.at(0));
        else if (list.at(0) == pointList.at(1).y())
            newPointList.push_back(pointList.at(1));
        else if (list.at(0) == pointList.at(2).y())
            newPointList.push_back(pointList.at(2));
        else if (list.at(0) == pointList.at(3).y())
            newPointList.push_back(pointList.at(3));

        if (list.at(1) == pointList.at(0).y())
            newPointList.push_back(pointList.at(0));
        else if (list.at(1) == pointList.at(1).y())
            newPointList.push_back(pointList.at(1));
        else if (list.at(1) == pointList.at(2).y())
            newPointList.push_back(pointList.at(2));
        else if (list.at(1) == pointList.at(3).y())
            newPointList.push_back(pointList.at(3));

        if (list.at(2) == pointList.at(0).y())
            newPointList.push_back(pointList.at(0));
        else if (list.at(2) == pointList.at(1).y())
            newPointList.push_back(pointList.at(1));
        else if (list.at(2) == pointList.at(2).y())
            newPointList.push_back(pointList.at(2));
        else if (list.at(2) == pointList.at(3).y())
            newPointList.push_back(pointList.at(3));

        if (list.at(3) == pointList.at(0).y())
            newPointList.push_back(pointList.at(0));
        else if (list.at(3) == pointList.at(1).y())
            newPointList.push_back(pointList.at(1));
        else if (list.at(3) == pointList.at(2).y())
            newPointList.push_back(pointList.at(2));
        else if (list.at(3) == pointList.at(3).y())
            newPointList.push_back(pointList.at(3));

        return newPointList;
    }

    void refreshShow() {
        //得到实线部分
        QPainterPath solidPath;
        solidPath.moveTo(m_pTopPointList.at(0));
        solidPath.lineTo(m_pTopPointList.at(1));
        solidPath.lineTo(m_pTopPointList.at(2));
        solidPath.lineTo(m_pTopPointList.at(3));
        solidPath.lineTo(m_pTopPointList.at(0));
        solidPath.lineTo(m_pBottomPointList.at(0));
        solidPath.lineTo(m_pBottomPointList.at(3));
        solidPath.lineTo(m_pBottomPointList.at(2));
        solidPath.lineTo(m_pTopPointList.at(2));
        solidPath.moveTo(m_pTopPointList.at(3));
        solidPath.lineTo(m_pBottomPointList.at(3));
        //得到虚线部分
        QPainterPath dashPath;
        dashPath.moveTo(m_pTopPointList.at(1));
        dashPath.lineTo(m_pBottomPointList.at(1));
        dashPath.lineTo(m_pBottomPointList.at(0));
        dashPath.moveTo(m_pBottomPointList.at(1));
        dashPath.lineTo(m_pBottomPointList.at(2));
        m_pSolidPath = solidPath;
        m_pDashPath = dashPath;
        //得到调节点
        m_pAdjustHeightPoint = QPointF((m_pTopPointList.at(0).x() + m_pTopPointList.at(2).x())/2,
                                       (m_pTopPointList.at(1).y() + m_pTopPointList.at(3).y())/2);
        m_pBottomCenter = QPointF((m_pBottomPointList.at(0).x() + m_pBottomPointList.at(2).x())/2,
                                  (m_pBottomPointList.at(1).y() + m_pBottomPointList.at(3).y())/2);
        m_pAdjustLongPoint = QPointF(QLineF(m_pBottomPointList.at(0), m_pBottomPointList.at(3)).center());
        m_pAdjustWidthPoint = QPointF(QLineF(m_pBottomPointList.at(2), m_pBottomPointList.at(3)).center());

        update();
        this->scene()->update();
    }

    void refreshPointList() {
        QList<QPointF> pointList_X;
        QList<QPointF> pointList_Y;
        /* 将立方体顶部四个点按顺序存储，首先存储最左边的点，顺时针存储其他几个点 */
        //X坐标最小的点一定是立方体顶面最左边的点，X坐标最大的点一定是立方体顶面最右边的点
        pointList_X = qSortPointsWithX(m_pTopPointList);
        //Y坐标最小的点一定是立方体顶面最上边的点(连接着虚线点)，Y坐标最大的点一定是立方体顶面最下边的点
        pointList_Y = qSortPointsWithY(m_pTopPointList);
        m_pTopPointList.replace(0, pointList_X.at(0));
        m_pTopPointList.replace(2, pointList_X.at(3));
        m_pTopPointList.replace(1, pointList_Y.at(0));
        m_pTopPointList.replace(3, pointList_Y.at(3));
        /* 将立方体底部四个点按顺序存储，首先存储最左边的点，顺时针存储其他几个点 */
        //X坐标最小的点一定是立方体底面最左边的点，X坐标最大的点一定是立方体底面最右边的点
        pointList_X = qSortPointsWithX(m_pBottomPointList);
        //Y坐标最小的点一定是立方体底面最上边的点(连接着虚线点)，Y坐标最大的点一定是立方体底面最下边的点
        pointList_Y = qSortPointsWithY(m_pBottomPointList);
        m_pBottomPointList.replace(0, pointList_X.at(0));
        m_pBottomPointList.replace(2, pointList_X.at(3));
        m_pBottomPointList.replace(1, pointList_Y.at(0));
        m_pBottomPointList.replace(3, pointList_Y.at(3));
    }

signals:
    void adjustStart();
    void adjustFinished();
    void itemSelected();
};

#endif // CUSTOMITEM_CUBE_H
