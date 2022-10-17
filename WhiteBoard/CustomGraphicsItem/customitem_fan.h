#ifndef CUSTOMITEM_FAN_H
#define CUSTOMITEM_FAN_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsScene>
#include "Public/public_function.h"
#include <math.h>
#include <QStyleOptionGraphicsItem>

/*
*   扇形Item
*/

enum class FanItemAction {
    Move,
    Rotate,
    Zoom_TopLeft,
    Zoom_TopCenter,
    Zoom_TopRight,
    Zoom_RightCenter,
    Zoom_BottomLeft,
    Zoom_BottomCenter,
    Zoom_BottomRight,
    Zoom_LeftCenter,
    None
};


class CustomItem_Fan : public QGraphicsItem
{
public:
    CustomItem_Fan(QGraphicsItem *parent = Q_NULLPTR) : QGraphicsItem(parent)
    {
        this->setAcceptedMouseButtons(Qt::LeftButton);
        //开启鼠标跟踪
        this->setAcceptHoverEvents(true);
    }

    void setZooming(bool bo) {
        m_pItemZooming = bo;
    }

    void setPen(const QPen &pen) {
        m_pPen = pen;
    }

    void setBrush(const QBrush &brush){
        m_pBrush = brush;
    }

    //change now
    void setRect(const QRectF &rect) {
        /* 根据rect得到扇形路径，扇形的中心点一定在rect的右下角点，旋转点P1一定在rect的右上角点，旋转点P2一定在rect的左下角 */
        m_pP1 = rect.topRight();
        m_pP2 = rect.bottomLeft();
        QRectF drawRect = QRectF(rect.topLeft(), QPointF(rect.bottomRight().x() + rect.width(),
                                                         rect.bottomRight().y() + rect.height()));
        m_pDrawRect = drawRect;
        QPainterPath path;
        path.moveTo(drawRect.center());
        path.arcTo(drawRect, 90, 90);
        path.closeSubpath();
        m_pPath = path;
        m_pPathRect = m_pPath.boundingRect();
        /* 计算图标中心点位置 */
        int border = Public_Function::getScaleSize(2); //图标边框线与path边框的边距，防止边框线覆盖path线条
        m_pRotatePoint = QPointF(rect.center().x(), rect.topLeft().y() - Public_Function::getScaleSize(30));
        m_pTopLeftZoomPoint = QPointF(rect.topLeft().x() - border, rect.topLeft().y() - border);
        m_pTopRightZoomPoint = QPointF(rect.topRight().x() + border, rect.topRight().y() - border);
        m_pBottomRightZoomPoint = QPointF(rect.bottomRight().x() + border, rect.bottomRight().y() + border);
        m_pBottomLeftZoomPoint = QPointF(rect.bottomLeft().x() - border, rect.bottomLeft().y() + border);
        m_pTopCenterZoomPoint = QLineF(m_pTopLeftZoomPoint, m_pTopRightZoomPoint).center();
        m_pRightCenterZoomPoint = QLineF(m_pTopRightZoomPoint, m_pBottomRightZoomPoint).center();
        m_pBottomCenterZoomPoint = QLineF(m_pBottomRightZoomPoint, m_pBottomLeftZoomPoint).center();
        m_pLeftCenterZoomPoint = QLineF(m_pBottomLeftZoomPoint, m_pTopLeftZoomPoint).center();
        /* 计算等距线,当宽高相同时展示等距线 */
        int height = Public_Function::getScaleSize(15);
        m_pTopLeftEquidstantLine = QLineF(QPointF(rect.topLeft().x(), rect.topLeft().y() - height), rect.topLeft());
        m_pTopRightEquidstantLine = QLineF(QPointF(rect.topRight().x(), rect.topRight().y() - height), rect.topRight());
        m_pRightTopEquidstantLine = QLineF(QPointF(rect.topRight().x() + height, rect.topRight().y()), rect.topRight());
        m_pRightBottomEquidstantLine = QLineF(QPointF(rect.bottomRight().x() + height, rect.bottomRight().y()), rect.bottomRight());
    }

    void setPoint(const QRectF &drawrect, const QPointF &p1, const QPointF &p2) {
//        m_pDrawRect = drawrect;
//        m_pP1 = p1;
//        m_pP2 = p2;
//        QPainterPath path;
//        path.moveTo(drawrect.center());
//        path.arcTo(drawrect, -this->getRotateAngle(drawrect.center(), QPointF(drawrect.topRight().x(), drawrect.center().y()), p1),
//                      -this->getRotateAngle(drawrect.center(), QPointF(drawrect.topRight().x(), drawrect.center().y()), p1));
//        path.closeSubpath();
//        m_pPath = path;

//        QRectF pathrect = m_pPath.boundingRect();
//        QTransform transform;
//        transform.rotate(m_pRotationAngle, Qt::ZAxis);
//        /*根据item当前的旋转角度旋转path的boundrect*/
//        m_pPathRect = transform.mapRect(m_pPath.boundingRect());
//        m_pPathRect.translate(QPointF(m_pPathRect.center().x() - pathrect.center().x(),
//                               m_pPathRect.center().y() - pathrect.y()));

//        //设置旋转图标，缩放图标等矩形框的大小
//        QRectF rect = QRectF(0, 0, Public_Function::getScaleSize(20), Public_Function::getScaleSize(20));
//        //选中边框线与path边界的margin值，选中的时候不会覆盖path的线条
//        int border = 0;
//        /*根据item当前的旋转角度得到缩放图标，旋转图标等位置*/
//        rect.moveCenter(QPointF(pathrect.topLeft().x() - border,
//                                pathrect.topLeft().y() - border));
//        m_pTopLeftZoomRect = transform.mapRect(rect);
//        m_pTopLeftZoomRect.translate(QPointF(m_pTopLeftZoomRect.center().x() - rect.center().x(),
//                               m_pTopLeftZoomRect.center().y() - rect.center().y()));
//        rect.moveCenter(QPointF(pathrect.center().x(),
//                                pathrect.topLeft().y() - border));
//        m_pTopCenterZoomRect = transform.mapRect(rect);
//        m_pTopCenterZoomRect.translate(QPointF(m_pTopCenterZoomRect.center().x() - rect.center().x(),
//                               m_pTopCenterZoomRect.center().y() - rect.center().y()));
//        rect.moveCenter(QPointF(pathrect.topRight().x() + border,
//                                pathrect.topRight().y() - border));
//        m_pTopRightZoomRect = transform.mapRect(rect);
//        m_pTopRightZoomRect.translate(QPointF(m_pTopRightZoomRect.center().x() - rect.center().x(),
//                               m_pTopRightZoomRect.center().y() - rect.center().y()));
//        rect.moveCenter(QPointF(pathrect.topRight().x() + border,
//                                pathrect.center().y()));
//        m_pRightCenterZoomRect = transform.mapRect(rect);
//        m_pRightCenterZoomRect.translate(QPointF(m_pRightCenterZoomRect.center().x() - rect.center().x(),
//                               m_pRightCenterZoomRect.center().y() - rect.center().y()));
//        rect.moveCenter(QPointF(pathrect.bottomLeft().x() - border,
//                                pathrect.bottomLeft().y() + border));
//        m_pBottomLeftZoomRect = transform.mapRect(rect);
//        m_pBottomLeftZoomRect.translate(QPointF(m_pBottomLeftZoomRect.center().x() - rect.center().x(),
//                               m_pBottomLeftZoomRect.center().y() - rect.center().y()));
//        rect.moveCenter(QPointF(pathrect.center().x(),
//                                pathrect.bottomLeft().y() + border));
//        m_pBottomCenterZoomRect = transform.mapRect(rect);
//        m_pBottomCenterZoomRect.translate(QPointF(m_pBottomCenterZoomRect.center().x() - rect.center().x(),
//                               m_pBottomCenterZoomRect.center().y() - rect.center().y()));
//        rect.moveCenter(QPointF(pathrect.bottomRight().x() + border,
//                                pathrect.bottomRight().y() + border));
//        m_pBottomRightZoomRect = transform.mapRect(rect);
//        m_pBottomRightZoomRect.translate(QPointF(m_pBottomRightZoomRect.center().x() - rect.center().x(),
//                               m_pBottomRightZoomRect.center().y() - rect.center().y()));
//        rect.moveCenter(QPointF(pathrect.topLeft().x() - border,
//                                pathrect.center().y()));
//        m_pLeftCenterZoomRect = transform.mapRect(rect);
//        m_pLeftCenterZoomRect.translate(QPointF(m_pLeftCenterZoomRect.center().x() - rect.center().x(),
//                               m_pLeftCenterZoomRect.center().y() - rect.center().y()));
//        rect.moveCenter(QPointF(pathrect.center().x(), pathrect.topLeft().y() - border - Public_Function::getScaleSize(30)));
//        m_pRotatingRect = transform.mapRect(rect);
//        m_pRotatingRect.translate(QPointF(m_pRotatingRect.center().x() - rect.center().x(),
//                               m_pRotatingRect.center().y() - rect.center().y()));
//        rect.moveCenter(p1);
//        m_pP1Rect = transform.mapRect(rect);
//        m_pP1Rect.translate(QPointF(m_pP1Rect.center().x() - rect.center().x(),
//                               m_pP1Rect.center().y() - rect.center().y()));
//        rect.moveCenter(p2);
//        m_pP2Rect = transform.mapRect(rect);
//        m_pP2Rect.translate(QPointF(m_pP2Rect.center().x() - rect.center().x(),
//                               m_pP2Rect.center().y() - rect.center().y()));
//        //计算等距线,当宽高相同时展示等距线, 需要根据当前旋转角度旋转
//        int height = Public_Function::getScaleSize(15);
//        QLineF line = QLineF(QPointF(pathrect.topLeft().x(), pathrect.topLeft().y() - height), pathrect.topLeft());
//        m_pTopLeftEquidstantLine = transform.map(line);
//        m_pTopLeftEquidstantLine.translate(QPointF(m_pTopLeftEquidstantLine.center().x() - line.center().x(),
//                               m_pTopLeftEquidstantLine.center().y() - line.center().y()));
//        line = QLineF(QPointF(pathrect.topRight().x(), pathrect.topRight().y() - height), pathrect.topRight());
//        m_pTopRightEquidstantLine = transform.map(line);
//        m_pTopRightEquidstantLine.translate(QPointF(m_pTopRightEquidstantLine.center().x() - line.center().x(),
//                               m_pTopRightEquidstantLine.center().y() - line.center().y()));
//        line = QLineF(QPointF(pathrect.topRight().x() + height, pathrect.topRight().y()), pathrect.topRight());
//        m_pRightTopEquidstantLine = transform.map(line);
//        m_pRightTopEquidstantLine.translate(QPointF(m_pRightTopEquidstantLine.center().x() - line.center().x(),
//                               m_pRightTopEquidstantLine.center().y() - line.center().y()));
//        line = QLineF(QPointF(pathrect.bottomRight().x() + height, pathrect.bottomRight().y()), pathrect.bottomRight());
//        m_pRightBottomEquidstantLine = transform.map(line);
//        m_pRightBottomEquidstantLine.translate(QPointF(m_pRightBottomEquidstantLine.center().x() - line.center().x(),
//                               m_pRightBottomEquidstantLine.center().y() - line.center().y()));
//        rect = QRectF(QPointF(pathrect.topLeft().x(), pathrect.topLeft().y() - border
//                              - Public_Function::getScaleSize(30) - rect.width()/2),
//                      QPointF(pathrect.bottomRight().x() + height, pathrect.bottomRight().y() + border));
//        //获取包含所有图标以及线条在内的最小矩形框，需要根据当前旋转角度旋转
//        m_pBoundRect = transform.mapRect(rect);
//        m_pBoundRect.translate(QPointF(m_pBoundRect.center().x() - rect.center().x(),
//                               m_pBoundRect.center().y() - rect.center().y()));

    }

    /*自定义Type*/
    enum { Type = UserType + 101 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    QRectF boundingRect() const Q_DECL_OVERRIDE{
        // Item boundRect()，决定了item显示和刷新区域，必须确保包含所有图标和线条在内
        QVector<qreal> data;
        qreal minX, maxX, minY, maxY;
        data.push_back(m_pTopLeftEquidstantLine.p1().x());
        data.push_back(m_pTopRightEquidstantLine.p1().x());
        data.push_back(m_pRightTopEquidstantLine.p1().x());
        data.push_back(m_pRightBottomEquidstantLine.p1().x());
        data.push_back(m_pBottomLeftZoomPoint.x());
        data.push_back(m_pTopLeftZoomPoint.x());
        data.push_back(m_pRotatePoint.x());
        minX = this->getMin(data);
        maxX = this->getMax(data);
        data.clear();
        data.push_back(m_pTopLeftEquidstantLine.p1().y());
        data.push_back(m_pTopRightEquidstantLine.p1().y());
        data.push_back(m_pRightTopEquidstantLine.p1().y());
        data.push_back(m_pRightBottomEquidstantLine.p1().y());
        data.push_back(m_pBottomLeftZoomPoint.y());
        data.push_back(m_pTopLeftZoomPoint.y());
        data.push_back(m_pRotatePoint.y());
        minY = this->getMin(data);
        maxY = this->getMax(data);

        QRectF rect;
        /* 矩形需要偏离>=图标的一个半径长度 */
        int radius = Public_Function::getScaleSize(10);
        rect.setTopLeft(QPointF(minX - radius, minY - radius));
        rect.setBottomRight(QPointF(maxX + radius, maxY + radius));
        return rect;
    }

    QPainterPath shape() const Q_DECL_OVERRIDE{
        QPainterPath path;
        path.addRect(this->boundingRect());
        return path;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget)
    {
        QStyleOptionGraphicsItem op;
        op.initFrom(widget);

        if (option->state & QStyle::State_Selected) {
            op.state = QStyle::State_None;
        }

        if (!m_pItemMoving && (option->state & QStyle::State_Selected)) {
            //绘制扇形Path
            painter->setPen(m_pPen);
            painter->setBrush(m_pBrush);
            painter->drawPath(m_pPath);
            /*绘制各个图标连接线*/
            painter->setBrush(QBrush());
            painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
            painter->drawRect(QRectF(m_pTopLeftZoomPoint, m_pBottomRightZoomPoint));
            painter->setPen(QPen(QBrush(QColor(0,184,169)), Public_Function::getScaleSize(2)));
            painter->drawLine(m_pRotatePoint, m_pTopCenterZoomPoint);
            painter->setBrush(QBrush(QColor(0,184,169)));
            /*绘制各个图标*/
            int radius  = Public_Function::getScaleSize(9);   //图标半径
            if (FanItemAction::Rotate == m_pItemAction)    //如果鼠标正在进行旋转操作，旋转图标绘制白色边框
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_pRotatePoint, radius, radius);
            painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (FanItemAction::Zoom_TopLeft == m_pItemAction) {
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
                painter->drawEllipse(m_pTopLeftZoomPoint, radius, radius);
            }else {
                painter->drawEllipse(m_pTopLeftZoomPoint, radius, radius);
            }
            if (FanItemAction::Zoom_TopCenter == m_pItemAction) {
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
                painter->drawEllipse(m_pTopCenterZoomPoint, radius, radius);
            }else {
                painter->drawEllipse(m_pTopCenterZoomPoint, radius, radius);
            }
            if (FanItemAction::Zoom_TopRight == m_pItemAction) {
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
                painter->drawEllipse(m_pTopRightZoomPoint, radius, radius);
            }else {
                painter->drawEllipse(m_pTopRightZoomPoint, radius, radius);
            }
            if (FanItemAction::Zoom_RightCenter == m_pItemAction) {
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
                painter->drawEllipse(m_pRightCenterZoomPoint, radius, radius);
            }else {
                painter->drawEllipse(m_pRightCenterZoomPoint, radius, radius);
            }
            if (FanItemAction::Zoom_BottomRight == m_pItemAction) {
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
                painter->drawEllipse(m_pBottomRightZoomPoint, radius, radius);
            }else {
                painter->drawEllipse(m_pBottomRightZoomPoint, radius, radius);
            }
            if (FanItemAction::Zoom_BottomCenter == m_pItemAction) {
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
                painter->drawEllipse(m_pBottomCenterZoomPoint, radius, radius);
            }else {
                painter->drawEllipse(m_pBottomCenterZoomPoint, radius, radius);
            }
            if (FanItemAction::Zoom_BottomLeft == m_pItemAction) {
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
                painter->drawEllipse(m_pBottomLeftZoomPoint, radius, radius);
            }else {
                painter->drawEllipse(m_pBottomLeftZoomPoint, radius, radius);
            }
            if (FanItemAction::Zoom_LeftCenter == m_pItemAction) {
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
                painter->drawEllipse(m_pLeftCenterZoomPoint, radius, radius);
            }else {
                painter->drawEllipse(m_pLeftCenterZoomPoint, radius, radius);
            }
            painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->setBrush(QBrush(Qt::white));
            painter->drawEllipse(m_pP1, radius, radius);
            painter->drawEllipse(m_pP2, radius, radius);
        }else {
            if (m_pItemZooming) {
                /*长宽相等时画提示线条*/
                if (m_pPathRect.width() == m_pPathRect.height()) {
                    painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
                    painter->drawLine(m_pTopLeftEquidstantLine);
                    painter->drawLine(m_pTopRightEquidstantLine);
                    painter->drawLine(m_pRightTopEquidstantLine);
                    painter->drawLine(m_pRightBottomEquidstantLine);
                    painter->drawPath(getDoubleArrow(QLineF(m_pTopLeftEquidstantLine.center(), m_pTopRightEquidstantLine.center()),
                                                     Public_Function::getScaleSize(2)));
                    painter->drawPath(getDoubleArrow(QLineF(m_pRightTopEquidstantLine.center(), m_pRightBottomEquidstantLine.center()),
                                                     Public_Function::getScaleSize(2)));
                }
            }
            painter->setPen(m_pPen);
            painter->setBrush(m_pBrush);
            painter->drawPath(m_pPath);
        }
    }


    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event){
        QPointF pos = event->pos();
        //各个图标中心点的最大检测到鼠标距离
        int dh = Public_Function::getScaleSize(10);
        if (this->isSelected() && QLineF(m_pRotatePoint, pos).length() <= dh) {
            this->setCursor(Qt::PointingHandCursor);
        }else if (this->isSelected() && (QLineF(m_pP1, pos).length() <= dh ||
                                         QLineF(m_pP2, pos).length() <= dh)){
            this->setCursor(Qt::PointingHandCursor);
        }else if (this->isSelected() && (QLineF(m_pTopLeftZoomPoint, pos).length() <= dh ||
                                   QLineF(m_pBottomRightZoomPoint, pos).length() <= dh))
            this->setCursor(Qt::SizeFDiagCursor);
        else if (this->isSelected() && (QLineF(m_pTopRightZoomPoint, pos).length() <= dh ||
                                        QLineF(m_pBottomLeftZoomPoint, pos).length() <= dh)) {
            this->setCursor(Qt::SizeBDiagCursor);
        }else if (this->isSelected() && (QLineF(m_pTopCenterZoomPoint, pos).length() <= dh ||
                                         QLineF(m_pBottomCenterZoomPoint, pos).length() <= dh)) {
            this->setCursor(Qt::SizeVerCursor);
        }else if (this->isSelected() && (QLineF(m_pLeftCenterZoomPoint, pos).length() <= dh ||
                                         QLineF(m_pRightCenterZoomPoint, pos).length() <= dh)) {
            this->setCursor(Qt::SizeHorCursor);
        }else if (m_pPath.contains(pos)){
            this->setCursor(Qt::SizeAllCursor);
        }else {
            this->setCursor(Qt::ArrowCursor);
        }
        return QGraphicsItem::hoverMoveEvent(event);
    }

    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
        this->setCursor(Qt::ArrowCursor);
        return QGraphicsItem::hoverLeaveEvent(event);
    }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event){
        m_pMousePressedPoint = event->pos();
        m_pMouseLastPoint = event->pos();
        m_pHasMouseMove = false;

        QPointF pos = event->pos();
        //各个图标中心点的最大检测到鼠标距离
        int dh = Public_Function::getScaleSize(10);
        //刷新区域
        QRectF refreshRect = QRectF(0, 0, dh*2, dh*2);
        if (QLineF(m_pTopLeftZoomPoint, pos).length() <= dh) {
            m_pItemAction = FanItemAction::Zoom_TopLeft;
            refreshRect.moveCenter(m_pTopLeftZoomPoint);
            m_pScaleX = this->matrix().m11();
            m_pScaleY = this->matrix().m22();
            qDebug()<<this->matrix();
        }else if (QLineF(m_pTopRightZoomPoint, pos).length() <= dh) {
            m_pItemAction = FanItemAction::Zoom_TopRight;
            refreshRect.moveCenter(m_pTopRightZoomPoint);
        }else if (QLineF(m_pBottomLeftZoomPoint, pos).length() <= dh){
            m_pItemAction = FanItemAction::Zoom_BottomLeft;
            refreshRect.moveCenter(m_pBottomLeftZoomPoint);
        }else if (QLineF(m_pBottomRightZoomPoint, pos).length() <= dh){
            m_pItemAction = FanItemAction::Zoom_BottomRight;
            refreshRect.moveCenter(m_pBottomRightZoomPoint);
        }else if (QLineF(m_pTopCenterZoomPoint, pos).length() <= dh) {
            m_pItemAction = FanItemAction::Zoom_TopCenter;
            refreshRect.moveCenter(m_pTopCenterZoomPoint);
        }else if (QLineF(m_pRightCenterZoomPoint, pos).length() <= dh) {
            m_pItemAction = FanItemAction::Zoom_RightCenter;
            refreshRect.moveCenter(m_pRightCenterZoomPoint);
        }else if (QLineF(m_pBottomCenterZoomPoint, pos).length() <= dh) {
            m_pItemAction = FanItemAction::Zoom_BottomCenter;
            refreshRect.moveCenter(m_pBottomCenterZoomPoint);
        }else if (QLineF(m_pLeftCenterZoomPoint, pos).length() <= dh) {
            m_pItemAction = FanItemAction::Zoom_LeftCenter;
            refreshRect.moveCenter(m_pLeftCenterZoomPoint);
        }else if (QLineF(m_pRotatePoint, pos).length() <= dh){
            m_pItemAction = FanItemAction::Rotate;
            refreshRect.moveCenter(m_pRotatePoint);
        }else if (m_pPath.contains(pos))
            m_pItemAction = FanItemAction::Move;
        else
            m_pItemAction = FanItemAction::None;

        this->update(refreshRect);
        return;
    }

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
        m_pHasMouseMove = true;
        if (FanItemAction::None == m_pItemAction)
            return;

        QRectF sceneRefreshRect = this->boundingRect();
        m_pItemMoving = true;
        QPointF curPos = event->pos();
        if (FanItemAction::Move == m_pItemAction) {
            qreal subX = curPos.x() - m_pMousePressedPoint.x();
            qreal subY = curPos.y() - m_pMousePressedPoint.y();
            this->moveBy(subX, subY);
        }else if (FanItemAction::Rotate == m_pItemAction) {
            qreal angle = this->getRotateAngle(m_pPath.boundingRect().center(), m_pRotatePoint, curPos);
            this->setTransformOriginPoint(m_pPath.boundingRect().center());
            this->setRotation(this->rotation() + angle);
            return;
        }else if (FanItemAction::Zoom_TopLeft == m_pItemAction) {
            m_pItemZooming = true;
            qreal subX = m_pBottomRightZoomPoint.x() - curPos.x();
            qreal subY = m_pBottomRightZoomPoint.y() - curPos.y();
            subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
            subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
            qreal xFactor = subX/(m_pBottomRightZoomPoint.x() - m_pTopLeftZoomPoint.x());
            qreal yFactor = subY/(m_pBottomRightZoomPoint.y() - m_pTopLeftZoomPoint.y());
            if (1 == xFactor && 1 == yFactor)
                return;
            QTransform transform;
            //设置缩放因子
            transform.scale(xFactor, yFactor);
            //缩放路径(缩放中心是原点(0,0))
            this->resetTransform(transform);
        }
        //else if (FanItemAction::Zoom_TopRight == m_pItemAction) {
//            m_pItemZooming = true;
//            qreal subX = curPos.x() - m_pBottomLeftZoomRect.center().x();
//            qreal subY = m_pBottomLeftZoomRect.center().y() - curPos.y();
//            subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
//            subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
//            qreal xFactor = subX/(m_pBottomRightZoomRect.center().x() - m_pTopLeftZoomRect.center().x());
//            qreal yFactor = subY/(m_pBottomRightZoomRect.center().y() - m_pTopLeftZoomRect.center().y());
//            if (1 == xFactor && 1 == yFactor)
//                return;
//            QTransform transform;
//            //设置缩放因子
//            transform.scale(xFactor, yFactor);
//            //缩放路径(缩放中心是原点(0,0))
//            newpath = transform.map(path);
//            newpath.translate(QPointF(this->path().boundingRect().bottomLeft().x() - newpath.boundingRect().bottomLeft().x(),
//                                      this->path().boundingRect().bottomLeft().y() - newpath.boundingRect().bottomLeft().y()));
//        }else if (FanItemAction::Zoom_BottomLeft == m_pItemAction) {
//            m_pItemZooming = true;
//            qreal subX = m_pTopRightZoomRect.center().x() - curPos.x();
//            qreal subY = curPos.y() - m_pTopRightZoomRect.center().y();
//            subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
//            subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
//            qreal xFactor = subX/(m_pBottomRightZoomRect.center().x() - m_pTopLeftZoomRect.center().x());
//            qreal yFactor = subY/(m_pBottomRightZoomRect.center().y() - m_pTopLeftZoomRect.center().y());
//            if (1 == xFactor && 1 == yFactor)
//                return;
//            QTransform transform;
//            //设置缩放因子
//            transform.scale(xFactor, yFactor);
//            //缩放路径(缩放中心是原点(0,0))
//            newpath = transform.map(path);
//            newpath.translate(QPointF(this->path().boundingRect().topRight().x() - newpath.boundingRect().topRight().x(),
//                                      this->path().boundingRect().topRight().y() - newpath.boundingRect().topRight().y()));
//        }else if (FanItemAction::Zoom_BottomRight == m_pItemAction) {
//            m_pItemZooming = true;
//            qreal subX = curPos.x() - m_pTopLeftZoomRect.center().x();
//            qreal subY = curPos.y() - m_pTopLeftZoomRect.center().y();
//            subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
//            subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
//            qreal xFactor = subX/(m_pBottomRightZoomRect.center().x() - m_pTopLeftZoomRect.center().x());
//            qreal yFactor = subY/(m_pBottomRightZoomRect.center().y() - m_pTopLeftZoomRect.center().y());
//            if (1 == xFactor && 1 == yFactor)
//                return;
//            QTransform transform;
//            //设置缩放因子
//            transform.scale(xFactor, yFactor);
//            //缩放路径(缩放中心是原点(0,0))
//            newpath = transform.map(path);
//            newpath.translate(QPointF(this->path().boundingRect().topLeft().x() - newpath.boundingRect().topLeft().x(),
//                                      this->path().boundingRect().topLeft().y() - newpath.boundingRect().topLeft().y()));
//        }
//        //this->setPath(newpath);
        this->update();
        this->scene()->update();
        return;
    }

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
        //如果鼠标按下到释放没有移动过，并且item没有被选中，选中item
        if (!m_pHasMouseMove && !this->isSelected()) {
            this->setSelected(true);
        }
        m_pItemMoving = false;
        if (m_pItemZooming)
            m_pItemZooming = false;

//        if (FanItemAction::Rotate == m_pItemAction) {
//            /*旋转QLineF,旋转中心是（0， 0）*/
//            QTransform transform;
//            transform.rotate(this->rotation(), Qt::ZAxis);
//            QPainterPath path = transform.map(this->path());
//            /*不规则path旋转后的中心位置可能改变，无法通过旋转前的path的boundrect和旋转后的path的boundrect的中心点之间的差值来把path移动到正确位置，
//             * 这里使用QRect旋转相同角度，再根据旋转前后矩形框的中心点差值将旋转后的path移回正确位置*/
//            QRectF rect = QRectF(m_pTopLeftZoomRect.center(), m_pBottomRightZoomRect.center());
//            QRectF rotaterect = transform.mapRect(rect);
//            /*将旋转后的path中心设置回原来的QLineF的中心*/
//            path.translate(QPointF(rect.center().x() - rotaterect.center().x(),
//                                   rect.center().y() - rotaterect.center().y()));

//            this->setPath(path);
//            this->setRotation(0);
//        }

        m_pItemAction = FanItemAction::None;
        this->update();
        this->scene()->update();
        return;
    }

private:
    QPainterPath m_pPath;
    QRectF m_pPathRect;                     // 路径框，并不一定等于当前path的boundRect()，因为可能已经旋转过
    QPointF m_pRotatePoint;                 // 旋转图标中心点
    QPointF m_pTopLeftZoomPoint;            // 左上缩放图标中心点
    QPointF m_pTopRightZoomPoint;           // 右上缩放图标中心点
    QPointF m_pBottomRightZoomPoint;        // 右下缩放图标中心点
    QPointF m_pBottomLeftZoomPoint;         // 左下缩放图标中心点
    QPointF m_pTopCenterZoomPoint;          // 上中缩放图标中心点
    QPointF m_pRightCenterZoomPoint;        // 右中缩放图标中心点
    QPointF m_pBottomCenterZoomPoint;       // 下中缩放图标中心点
    QPointF m_pLeftCenterZoomPoint;         // 左中缩放图标中心点
    QRectF m_pDrawRect;                     // 扇形矩形框
    QPointF m_pP1;                          // 扇形的旋转点1
    QPointF m_pP2;                          // 扇形的旋转点2
    QLineF m_pTopLeftEquidstantLine;        // 上左方等距线
    QLineF m_pTopRightEquidstantLine;       // 上右方等距线
    QLineF m_pRightTopEquidstantLine;       // 右上方等距线
    QLineF m_pRightBottomEquidstantLine;    // 右下方等距线
    qreal m_pRotationAngle = 0;             // 旋转角度
    qreal m_pScaleX;
    qreal m_pScaleY;

    bool m_pItemMoving = false;             //正在移动标志位
    bool m_pItemZooming = false;            //正在缩放标志位
    FanItemAction m_pItemAction = FanItemAction::None;      //item操作
    QPen m_pPen;
    QBrush m_pBrush;
    QPointF m_pMousePressedPoint;
    QPointF m_pMouseLastPoint;
    bool m_pHasMouseMove;

    /*
     获取角度，如果firstPoint在secondPoint的左侧，则secondPoint在firstPoint所在直径的上方时角度为正，下方时为负；
        如果firstPoint在sceondpoint的右侧，如果secondPoint在firstpoing所在直径的上方时角度为负，下方时为正。
    */
    qreal getRotateAngle(QPointF center, QPointF firstPoint, QPointF secondPoint)
    {
        if(secondPoint == firstPoint)
            return 0;
        qreal ma_x = firstPoint.x() - center.x();
        qreal ma_y = firstPoint.y() - center.y();
        qreal mb_x = secondPoint.x() - center.x();
        qreal mb_y = secondPoint.y() - center.y();
        qreal v1 = (ma_x * mb_x) + (ma_y * mb_y);
        qreal ma_val = sqrt(ma_x * ma_x + ma_y * ma_y);
        qreal mb_val = sqrt(mb_x * mb_x + mb_y * mb_y);
        qreal cosm = v1 / (ma_val * mb_val);
        qreal angle = acos(cosm) * 180 / M_PI;
        if ((secondPoint.x() -firstPoint.x()) * (center.y() - firstPoint.y()) -
                (secondPoint.y() -firstPoint.y()) * (center.x() -firstPoint.x()) < 0) {
            angle = -angle;
        }
        return angle;
    }

    qreal getMin(QVector<qreal> vector) const{
        qreal min;
        for(int i = 0; i < vector.size(); i++) {
            if (0 == i)
                min = vector.at(i);
            else
                min = min > vector.at(i) ? vector.at(i) : min;
        }
        return min;
    }

    qreal getMax(QVector<qreal> vector) const{
        qreal max;
        for(int i = 0; i < vector.size(); i++) {
            if (0 == i)
                max = vector.at(i);
            else
                max = max < vector.at(i) ? vector.at(i) : max;
        }
        return max;
    }

    //获取双箭头线
    QPainterPath getDoubleArrow(QLineF line, int penWidth)
    {
        qreal angle = std::atan2(-line.dy(), line.dx());
        qreal arrowSize = penWidth*Public_Function::getScaleSize(5);
        QPointF arrowP1 = line.p2() - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);
        QPointF arrowP3 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP4 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

        QPainterPath path;
        path.moveTo(line.p1());
        path.lineTo(line.p2());
        path.lineTo(arrowP1);
        path.moveTo(line.p2());
        path.lineTo(arrowP2);
        path.moveTo(line.p1());
        path.lineTo(arrowP3);
        path.moveTo(line.p1());
        path.lineTo(arrowP4);
        return path;
    }

    void resetTransform(const QTransform &transform) {
        QPainterPath tPath;
        tPath = transform.map(m_pPath);
        tPath.translate(QPointF(m_pPath.boundingRect().bottomRight().x() - tPath.boundingRect().bottomRight().x(),
                                  m_pPath.boundingRect().bottomRight().y() - tPath.boundingRect().bottomRight().y()));
        m_pPath = tPath;
        m_pPathRect = m_pPath.boundingRect();
        /* 计算图标中心点位置 */
        int border = Public_Function::getScaleSize(2); //图标边框线与path边框的边距，防止边框线覆盖path线条
        m_pRotatePoint = QPointF(m_pPathRect.center().x(), m_pPathRect.topLeft().y() - Public_Function::getScaleSize(30));
        m_pTopLeftZoomPoint = QPointF(m_pPathRect.topLeft().x() - border, m_pPathRect.topLeft().y() - border);
        m_pTopRightZoomPoint = QPointF(m_pPathRect.topRight().x() + border, m_pPathRect.topRight().y() - border);
        m_pBottomRightZoomPoint = QPointF(m_pPathRect.bottomRight().x() + border, m_pPathRect.bottomRight().y() + border);
        m_pBottomLeftZoomPoint = QPointF(m_pPathRect.bottomLeft().x() - border, m_pPathRect.bottomLeft().y() + border);
        m_pTopCenterZoomPoint = QLineF(m_pTopLeftZoomPoint, m_pTopRightZoomPoint).center();
        m_pRightCenterZoomPoint = QLineF(m_pTopRightZoomPoint, m_pBottomRightZoomPoint).center();
        m_pBottomCenterZoomPoint = QLineF(m_pBottomRightZoomPoint, m_pBottomLeftZoomPoint).center();
        m_pLeftCenterZoomPoint = QLineF(m_pBottomLeftZoomPoint, m_pTopLeftZoomPoint).center();
        /* 计算等距线,当宽高相同时展示等距线 */
        int height = Public_Function::getScaleSize(15);
        m_pTopLeftEquidstantLine = QLineF(QPointF(m_pPathRect.topLeft().x(), m_pPathRect.topLeft().y() - height), m_pPathRect.topLeft());
        m_pTopRightEquidstantLine = QLineF(QPointF(m_pPathRect.topRight().x(), m_pPathRect.topRight().y() - height), m_pPathRect.topRight());
        m_pRightTopEquidstantLine = QLineF(QPointF(m_pPathRect.topRight().x() + height, m_pPathRect.topRight().y()), m_pPathRect.topRight());
        m_pRightBottomEquidstantLine = QLineF(QPointF(m_pPathRect.bottomRight().x() + height, m_pPathRect.bottomRight().y()), m_pPathRect.bottomRight());
    }

};

#endif // CUSTOMITEM_FAN_H
