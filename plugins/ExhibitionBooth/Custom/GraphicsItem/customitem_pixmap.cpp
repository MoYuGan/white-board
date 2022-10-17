#include "customitem_pixmap.h"


CustomItem_Pixmap::CustomItem_Pixmap(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    //只接受鼠标左键
    this->setAcceptedMouseButtons(Qt::LeftButton);
    //开启鼠标跟踪
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
}

QRectF CustomItem_Pixmap::boundingRect() const
{
    QRectF retRect;
    if (0!= m_pRotateAngle) {
        QTransform transform;
        transform.rotate(m_pRotateAngle, Qt::ZAxis);
        QPointF center = m_pRotateCenter;
        QPointF tCenter = transform.map(center);
        /* 设置旋转中心 */
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
        QRectF rect = transform.mapRect(m_pPixmapRect);
        QPointF r_TopLeft = rect.topLeft();
        QPointF r_TopRight = rect.topRight();
        QPointF r_BottomLeft = rect.bottomLeft();
        QPointF r_BottomRight = rect.bottomRight();
        qreal minX, minY, maxX, maxY;
        minX = PublicFunction::getMin(QVector<qreal>() << r_TopLeft.x() << r_TopRight.x() << r_BottomLeft.x() << r_BottomRight.x());
        maxX = PublicFunction::getMax(QVector<qreal>() << r_TopLeft.x() << r_TopRight.x() << r_BottomLeft.x() << r_BottomRight.x());
        minY = PublicFunction::getMin(QVector<qreal>() << r_TopLeft.y() << r_TopRight.y() << r_BottomLeft.y() << r_BottomRight.y());
        maxY = PublicFunction::getMax(QVector<qreal>() << r_TopLeft.y() << r_TopRight.y() << r_BottomLeft.y() << r_BottomRight.y());
        retRect = QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
    }else {
        retRect = m_pPixmapRect;
    }

    if (retRect.width() < PublicFunction::getScaleSize(10))
        retRect.setWidth(PublicFunction::getScaleSize(10));
    if (retRect.height() < PublicFunction::getScaleSize(10))
        retRect.setWidth(PublicFunction::getScaleSize(10));

    return retRect;
}

QPainterPath CustomItem_Pixmap::shape() const
{
    QPainterPath path;
    QTransform transform;
    transform.rotate(m_pRotateAngle, Qt::ZAxis);
    /* 设置旋转中心 */
    QPointF center = m_pRotateCenter;
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    QPointF topleft = transform.map(m_pPixmapRect.topLeft());
    QPointF topRight = transform.map(m_pPixmapRect.topRight());
    QPointF bottomLeft = transform.map(m_pPixmapRect.bottomLeft());
    QPointF bottomRight = transform.map(m_pPixmapRect.bottomRight());
    path.moveTo(topleft);
    path.lineTo(topRight);
    path.lineTo(bottomRight);
    path.lineTo(bottomLeft);
    path.lineTo(topleft);
    return path;
}

QRect CustomItem_Pixmap::getPixmapRect()
{
    return m_pPixmapRect;
}

void CustomItem_Pixmap::setPixmap(const QPixmap &pixmap, const QRect &pixmapRect,
                                  qreal rotateAngle, QPointF rotateCenter)
{
    QGraphicsPixmapItem::setPixmap(pixmap);
    m_pPixmapRect = pixmapRect;
    m_pTempPixmapRect = pixmapRect;
    m_pRotateAngle = rotateAngle;
    if (!rotateCenter.isNull())
        m_pRotateCenter = pixmapRect.center();
    m_pTempZValue = this->zValue();
    update();
}

void CustomItem_Pixmap::setZValue(qreal value)
{
    m_pActionType = ActionType::ZValue;
    QGraphicsPixmapItem::setZValue(value);
}

void CustomItem_Pixmap::scaleItemWithFactor(const qreal &xFactor, const qreal &yFactor, const QPointF &center)
{
    m_pActionType = ActionType::Scale;
    m_pScaleCenter = center;
    QTransform transform;
    //设置缩放因子
    transform.scale(xFactor, yFactor);
    /* 设置缩放中心 */
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    m_pPixmapRect = transform.mapRect(m_pPixmapRect);
    m_pRotateCenter = transform.map(m_pRotateCenter);
    update();
}

void CustomItem_Pixmap::scaleItemWithLength(qreal length, const QPointF &center)
{
    QRectF rect = this->boundingRect();
    qreal len = sqrt(rect.width() * rect.width() + rect.height() * rect.height());
    qreal minLen = sqrt(PublicFunction::getScaleSize(10) * PublicFunction::getScaleSize(10) * 2);
    qreal factor = (len + length) > minLen ? (len + length)/len : minLen/len;
    this->scaleItemWithFactor(factor, factor, center);
}

void CustomItem_Pixmap::rotateItem(qreal angle, const QPointF &center)
{
    m_pActionType = ActionType::Rotation;
    m_pTempRotateAngle += angle;
    m_pRotateAngle += angle;
    m_pRotateCenter = center;
    update();
}

void CustomItem_Pixmap::moveItem(const QPointF &subPt)
{
    m_pActionType = ActionType::Move;
    m_pPixmapRect.translate(subPt.x(), subPt.y());
    m_pRotateCenter = m_pPixmapRect.center();
    this->scene()->update();
}

void CustomItem_Pixmap::flipItem(int direction, QPointF center)
{
//    this->setTransformOriginPoint(center);
//    QTransform transform;
//    QPointF tCenter;
//    QTransform itemTransform = this->transform();
//    if (0 == direction) {
//        if (transform.m11() == -1) {
//            transform.rotate(0, Qt::YAxis);
//            tCenter = transform.map(center);
//            itemTransform.setMatrix(1, itemTransform.m12(), itemTransform.m13(),
//                                itemTransform.m21(), itemTransform.m22(), itemTransform.m23(),
//                                0, 0, itemTransform.m33());
//        }else {
//            transform.rotate(180, Qt::YAxis);
//            tCenter = transform.map(center);
//            itemTransform.setMatrix(-1, itemTransform.m12(), itemTransform.m13(),
//                                itemTransform.m21(), itemTransform.m22(), itemTransform.m23(),
//                                0, 0, itemTransform.m33());
//        }
//    }else {
//        if (transform.m22() == -1) {
//            transform.rotate(0, Qt::XAxis);
//            tCenter = transform.map(center);
//            itemTransform.setMatrix(1, itemTransform.m12(), itemTransform.m13(),
//                                itemTransform.m21(), 1, itemTransform.m23(),
//                                center.x() - tCenter.x(), center.y() - tCenter.y(), itemTransform.m33());
//        }else {
//            transform.rotate(180, Qt::XAxis);
//            tCenter = transform.map(center);
//            itemTransform.setMatrix(1, itemTransform.m12(), itemTransform.m13(),
//                                itemTransform.m21(), -1, itemTransform.m23(),
//                                center.x() - tCenter.x(), center.y() - tCenter.y(), itemTransform.m33());
//        }
//    }
//    this->setTransform(transform);
    //this->newActionFinished();
}


void CustomItem_Pixmap::actionFinished()
{
    if (m_pActionType == ActionType::None)
        return;

    QVariant variant;
    if (m_pActionType == ActionType::ZValue) {
        variant.setValue(QList<QVariant>() << m_pTempZValue);
        m_pTempZValue = this->zValue();
    }else if (m_pActionType == ActionType::Rotation) {
        //保存旋转角度的变化值和旋转中心，注意角度变化值取相反数，便于恢复操作
        variant.setValue(QList<QVariant>() << (-m_pTempRotateAngle) << m_pRotateCenter);
        m_pTempRotateAngle = 0;
    }else if (m_pActionType == ActionType::Move){
        variant.setValue(QList<QVariant>() << QPointF(-(m_pPixmapRect.center().x() - m_pTempPixmapRect.center().x()),
                                                      -(m_pPixmapRect.center().y() - m_pTempPixmapRect.center().y())));
        m_pTempPixmapRect = m_pPixmapRect;
    }else if (m_pActionType == ActionType::Scale) {
        variant.setValue(QList<QVariant>() << (qreal)m_pTempPixmapRect.width()/m_pPixmapRect.width()
                         << (qreal)m_pTempPixmapRect.height()/m_pPixmapRect.height() << m_pScaleCenter);
        m_pTempPixmapRect = m_pPixmapRect;
    }
    //加入历史记录
    this->pushDataToUndoData(variant, m_pActionType);
}

void CustomItem_Pixmap::setClone(bool bo)
{
    m_pIsClone = bo;
}

void CustomItem_Pixmap::toClone(qreal dx, qreal dy)
{
    if (nullptr == m_pCloneItem) {
        QPixmap pixmap = this->pixmap();
        m_pCloneItem = new CustomItem_Pixmap;
        m_pCloneItem->setPixmap(pixmap, m_pPixmapRect, m_pRotateAngle, m_pRotateCenter);
        m_pCloneItem->setFlags(QGraphicsItem::ItemIsSelectable);
        emit newItemCreated(m_pCloneItem);
    }else { //不为空，移动克隆item
        m_pCloneItem->moveItem(QPointF(dx, dy));
    }
}

void CustomItem_Pixmap::cloneFinished()
{
    m_pCloneItem = nullptr;
}

void CustomItem_Pixmap::undo()
{
    if (0 == m_pUndoType.size())
        return;

    QList<QVariant> dataList = m_pUndoData.last().value<QList<QVariant>>();
    switch(m_pUndoType.last())
    {
    case ActionType::Rotation: {
        qreal angle = dataList.at(0).toReal();
        QPointF center = dataList.at(1).toPointF();
        m_pRedoData.push_back(QList<QVariant>() << (-angle) << center);
        m_pRedoType.push_back(ActionType::Rotation);
        m_pRotateAngle += angle;
        m_pRotateCenter = center;
        update();
    }break;
    case ActionType::Move: {
        QPointF subPt = dataList.at(0).toPointF();
        m_pRedoData.push_back(QList<QVariant>() << QPointF(-subPt.x(), -subPt.y()));
        m_pRedoType.push_back(ActionType::Move);
        this->moveItem(subPt);
        m_pTempPixmapRect = m_pPixmapRect;
    }break;
    case ActionType::Scale: {
        qreal xFactor = dataList.at(0).toReal();
        qreal yFactor = dataList.at(1).toReal();
        QPointF scaleCenter = dataList.at(2).toPointF();
        this->scaleItemWithFactor(xFactor, yFactor, scaleCenter);
        m_pRedoData.push_back(QList<QVariant>() << (qreal)m_pTempPixmapRect.width()/m_pPixmapRect.width()
                              << (qreal)m_pTempPixmapRect.height()/m_pPixmapRect.height() << m_pScaleCenter);
        m_pRedoType.push_back(ActionType::Scale);
        m_pTempPixmapRect = m_pPixmapRect;
    }break;
    case ActionType::ZValue: {
        int zvalue = dataList.at(0).toInt();
        m_pRedoData.push_back(QList<QVariant>() << this->zValue());
        m_pRedoType.push_back(ActionType::ZValue);
        this->setZValue(zvalue);
    }break;
    default:
        break;
    }
    m_pUndoData.pop_back();
    m_pUndoType.pop_back();
}

void CustomItem_Pixmap::redo()
{
    if (0 == m_pRedoType.size())
        return;

    QList<QVariant> dataList = m_pRedoData.last().value<QList<QVariant>>();
    switch(m_pRedoType.last())
    {
    case ActionType::Rotation: {
        qreal angle = dataList.at(0).toReal();
        QPointF center = dataList.at(1).toPointF();
        m_pUndoData.push_back(QList<QVariant>() << (-angle) << center);
        m_pUndoType.push_back(ActionType::Rotation);
        m_pRotateAngle += angle;
        m_pRotateCenter = center;
        update();
    }break;
    case ActionType::Move: {
        QPointF subPt = dataList.at(0).toPointF();
        m_pUndoData.push_back(QList<QVariant>() << QPointF(-subPt.x(), -subPt.y()));
        m_pUndoType.push_back(ActionType::Move);
        this->moveItem(subPt);
        m_pTempPixmapRect = m_pPixmapRect;
    }break;
    case ActionType::Scale: {
        qreal xFactor = dataList.at(0).toReal();
        qreal yFactor = dataList.at(1).toReal();
        QPointF scaleCenter = dataList.at(2).toPointF();
        this->scaleItemWithFactor(xFactor, yFactor, scaleCenter);
        m_pUndoData.push_back(QList<QVariant>() << (qreal)m_pTempPixmapRect.width()/m_pPixmapRect.width()
                              << (qreal)m_pTempPixmapRect.height()/m_pPixmapRect.height() << m_pScaleCenter);
        m_pUndoType.push_back(ActionType::Scale);
        m_pTempPixmapRect = m_pPixmapRect;
    }break;
    case ActionType::ZValue: {
        int zvalue = dataList.at(0).toInt();
        m_pUndoData.push_back(QList<QVariant>() << this->zValue());
        m_pUndoType.push_back(ActionType::ZValue);
        this->setZValue(zvalue);
    }break;
    default:
        break;
    }
    m_pRedoData.pop_back();
    m_pRedoType.pop_back();
}

void CustomItem_Pixmap::clearRedoList()
{
    m_pRedoData.clear();
    m_pRedoType.clear();
}

void CustomItem_Pixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QStyleOptionGraphicsItem op = *option;

    if (op.state & QStyle::State_Selected) {
        op.state &= (~QStyle::State_Selected);
    }

    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    if (m_pRotateAngle != 0) {
        QTransform transform;
        transform.rotate(m_pRotateAngle, Qt::ZAxis);
        QPointF tCenter = transform.map(m_pRotateCenter);
        painter->translate(QPointF(m_pRotateCenter.x() - tCenter.x(), m_pRotateCenter.y() - tCenter.y()));
        painter->rotate(m_pRotateAngle);
    }
    painter->drawPixmap(m_pPixmapRect, this->pixmap());
}

void CustomItem_Pixmap::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
        return;

    QPointF pos = event->pos();
    if (this->isSelected())
        return QGraphicsPixmapItem::hoverMoveEvent(event);

    QSize cursorSize = PublicFunction::getScaleSize(QSize(24, 24));
    QCursor cursor;
    if (this->shape().contains(pos)){
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png").scaled(cursorSize));
    }else {
        cursor = Qt::ArrowCursor;
    }
    this->setCursor(cursor);
    return QGraphicsPixmapItem::hoverMoveEvent(event);
}

void CustomItem_Pixmap::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
        return;

    this->setCursor(Qt::ArrowCursor);
    return QGraphicsPixmapItem::hoverLeaveEvent(event);
}

void CustomItem_Pixmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
        return;

    if (this->isSelected())
        return;
    m_pHasMouseMove = false;
    m_pMouseLastPoint = event->pos();
    m_pMousePressedPoint = event->pos();
    return;
}

void CustomItem_Pixmap::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
        return;

    if (this->isSelected())
        return;
    QPointF mousePos = event->pos();

    //移动值超过5个像素点才算移动事件,避免大屏上运行时每次手指单击都误认为是移动事件，无法选中
    if ((qAbs(mousePos.x() - m_pMousePressedPoint.x()) < 5 &&
           qAbs(mousePos.y() - m_pMousePressedPoint.y()) < 5) && !m_pHasMouseMove)
        return;

    m_pHasMouseMove = true;
    qreal subX = mousePos.x() - m_pMouseLastPoint.x();
    qreal subY = mousePos.y() - m_pMouseLastPoint.y();
    if (m_pIsClone) {
        this->toClone(subX, subY);
    }else {
        this->moveItem(QPointF(subX, subY));
    }

    m_pMouseLastPoint = mousePos;
}

void CustomItem_Pixmap::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
        return;

    if (!m_pHasMouseMove && !this->isSelected()) {
        emit itemSelected();
        this->setSelected(true);
    }

    if (m_pHasMouseMove && m_pIsClone)
        this->cloneFinished();
    else if (m_pHasMouseMove) {
        this->actionFinished();
        emit itemHasChanged(this);
    }
}


