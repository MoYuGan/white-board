#include "customitem_path.h"

CustomItem_Path::CustomItem_Path(QGraphicsItem *parent) :
    QGraphicsPathItem(parent)
{
    //只接受鼠标左键
    this->setAcceptedMouseButtons(Qt::LeftButton);
    //开启鼠标跟踪
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);

    m_pUndoData.clear();
    m_pUndoType.clear();
    m_pRedoData.clear();
    m_pRedoType.clear();
    m_pItemPath = QPainterPath();
}

QRectF CustomItem_Path::boundingRect() const
{
    QRectF rect = QGraphicsPathItem::boundingRect();
    QRectF retRect = rect;
    if (rect.width() < PublicFunction::getScaleSize(10))
        retRect.setWidth(PublicFunction::getScaleSize(10));
    if (rect.height() < PublicFunction::getScaleSize(10))
        retRect.setWidth(PublicFunction::getScaleSize(10));

    return retRect;
}

QPainterPath CustomItem_Path::shape() const
{
    QPainterPathStroker stroker;
    stroker.setWidth(this->pen().width() + PublicFunction::getScaleSize(10));
    return stroker.createStroke(this->path());
}

void CustomItem_Path::refreshPathSave(const QPainterPath &path)
{
    m_pItemPath = path;
}

void CustomItem_Path::newActionFinished()
{
    //将路径加入撤销集合
    QVariant variant;
    variant.setValue(m_pItemPath);
    this->pushDataToUndoData(variant, HistoryType::Path);
    //保存当前路径
    this->refreshPathSave(this->path());
}

void CustomItem_Path::setPen(const QPen &pen)
{
    //将笔类型加入撤销集合
    QPainterPath itemPath = this->path();
    if (!itemPath.isEmpty() && m_pUndoType.size() > 0) {    //防止第一次设置QPen加入撤销集合
        QVariant variant;
        variant.setValue(this->pen());
        this->pushDataToUndoData(variant, HistoryType::Pen);
    }
    //设置新的画笔
    QGraphicsPathItem::setPen(pen);
}

void CustomItem_Path::setZValue(qreal z)
{
    //将当前图层级数加入撤销集合
    QPainterPath itemPath = this->path();
    if (!itemPath.isEmpty() && m_pUndoType.size() > 0) {    //防止第一次设置ZValue加入撤销集合
        QVariant variant;
        variant.setValue(this->zValue());
        this->pushDataToUndoData(variant, HistoryType::ZValue);
    }
    //设置新的图层级数
    QGraphicsPathItem::setZValue(z);
}

void CustomItem_Path::moveItem(const QPointF &pt)
{
    QPainterPath path = this->path();
    path.translate(pt);
    this->setPath(path);
}

void CustomItem_Path::rotateItem(const qreal &angle, const QPointF &center)
{
    /*旋转QLineF,旋转中心是（0， 0）*/
    QTransform transform;
    transform.rotate(angle, Qt::ZAxis);
    /* 设置旋转中心 */
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    QPainterPath path = transform.map(this->path());
    this->setPath(path);
    return;
}

void CustomItem_Path::scaleItemWithFactor(const qreal &xFactor, const qreal &yFactor, const QPointF &center)
{
    qDebug()<<xFactor<<yFactor<<center;
    QTransform transform;
    //设置缩放因子
    transform.scale(xFactor, yFactor);
    /* 设置缩放中心 */
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    //缩放路径(缩放中心是原点(0,0))
    QPainterPath path = transform.map(this->path());
    this->setPath(path);
}

void CustomItem_Path::scaleItemWithLength(qreal length, const QPointF &center)
{
    QRectF rect = this->boundingRect();
    qreal len = sqrt(rect.width() * rect.width() + rect.height() * rect.height());
    qreal minLen = sqrt(PublicFunction::getScaleSize(10) * PublicFunction::getScaleSize(10) * 2);
    qreal factor = (len + length) > minLen ? (len + length)/len : minLen/len;
    this->scaleItemWithFactor(factor, factor, center);
}

void CustomItem_Path::flip(int direction, QPointF center)
{
    QTransform transform;
    if (0 == direction)
        transform.rotate(180, Qt::YAxis);
    else
        transform.rotate(180, Qt::XAxis);
    /* 设置旋转中心 */
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    QPainterPath path = transform.map(this->path());
    this->setPath(path);
    this->newActionFinished();
}

void CustomItem_Path::mirror(int direction, qreal p)
{
    QTransform transform;
    QPointF center;
    if (0 == direction) {
        transform.rotate(180, Qt::XAxis);
        center = QPointF(this->boundingRect().center().x(), p);
    }else {
        transform.rotate(180, Qt::YAxis);
        center = QPointF(p, this->boundingRect().center().x());
    }
    /* 设置旋转中心 */
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    QPainterPath path = transform.map(this->path());
    CustomItem_Path *pathItem = new CustomItem_Path;
    pathItem->setFlags(QGraphicsItem::ItemIsSelectable);
    pathItem->setPen(this->pen());
    pathItem->setPath(path);
    emit newItemCreated(pathItem);
}

void CustomItem_Path::setClone(bool bo)
{
    m_pIsClone = bo;
}

void CustomItem_Path::toClone(qreal dx, qreal dy)
{
    QTransform transform;
    transform.translate(dx, dy);
    QPainterPath path;
    if (nullptr == m_pCloneItem) {
        path = transform.map(this->path());
        m_pCloneItem = new CustomItem_Path;
        m_pCloneItem->setFlags(QGraphicsItem::ItemIsSelectable);
        m_pCloneItem->setPen(this->pen());
        m_pCloneItem->setPath(path);
        emit newItemCreated(m_pCloneItem);
    }else { //不为空，移动克隆item
        path = transform.map(m_pCloneItem->path());
        m_pCloneItem->setPath(path);
    }
}

void CustomItem_Path::cloneFinished()
{
    m_pCloneItem = nullptr;
}

QVector<QGraphicsItem *> CustomItem_Path::eraserFinished()
{
    QPainterPath path = this->path();
    QVector<QGraphicsItem *> newItemList;

    if (path.isEmpty())     //被完全擦除
        return newItemList;

    QPainterPath newPath;
    QVector<QPainterPath> subPathList;
    //根据Element::Type和Element::QPointF判断路径是否连续，加以分割
    for(int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        if (element.isMoveTo()) {
            if (newPath.length() > 1) {
                subPathList.push_back(newPath);
                newPath &= QPainterPath();
            }

            newPath.moveTo(element.x, element.y);
        }else if(element.isLineTo()){
            newPath.lineTo(element.x, element.y);
        }

        if (i == (path.elementCount() - 1) && newPath.length() > 1)  //最后一条路径加入路径集合
            subPathList.push_back(newPath);

    }

    for(int i = 0; i < subPathList.size(); i++) {
        //根据分割的路径列表创建新的item
        CustomItem_Path *item = new CustomItem_Path;
        item->setPath(subPathList.at(i));
        item->setPen(this->pen());
        item->setZValue(this->zValue());
        newItemList.push_back(item);
    }
    //此item将会被移除，设置回原来的路径，方便撤销时重新显示
    this->setPath(m_pItemPath);
    return newItemList;
}

void CustomItem_Path::undo()
{
    if (0 == m_pUndoType.size())
        return;

    switch(m_pUndoType.last())
    {
    case HistoryType::Path: {
        QVariant variant;
        variant.setValue(m_pItemPath);
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Path);
        QPainterPath path = m_pUndoData.last().value<QPainterPath>();
        this->setPath(path);
        m_pItemPath = path;
    }break;
    case HistoryType::Pen: {
        QVariant variant;
        variant.setValue(this->pen());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Pen);
        QPen pen = m_pUndoData.last().value<QPen>();
        this->setPen(pen);
    }break;
    case HistoryType::ZValue: {
        QVariant variant;
        variant.setValue(this->zValue());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::ZValue);
        qreal zvalue = m_pUndoData.last().toReal();
        this->setZValue(zvalue);
    }break;
    default:
        break;
    }
    m_pUndoData.pop_back();
    m_pUndoType.pop_back();
}

void CustomItem_Path::redo()
{
    if (0 == m_pRedoType.size())
        return;

    switch(m_pRedoType.last())
    {
    case HistoryType::Path: {
        QVariant variant;
        variant.setValue(m_pItemPath);
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Path);
        QPainterPath path = m_pRedoData.last().value<QPainterPath>();
        this->setPath(path);
        m_pItemPath = path;
    }break;
    case HistoryType::Pen: {
        QVariant variant;
        variant.setValue(this->pen());
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Pen);
        QPen pen = m_pRedoData.last().value<QPen>();
        this->setPen(pen);
    }break;
    case HistoryType::ZValue: {
        QVariant variant;
        variant.setValue(this->zValue());
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::ZValue);
        qreal zvalue = m_pRedoData.last().toReal();
        this->setZValue(zvalue);
    }break;
    default:
        break;
    }
    m_pRedoData.pop_back();
    m_pRedoType.pop_back();
}

void CustomItem_Path::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionGraphicsItem op = *option;

    if (op.state & QStyle::State_Selected) {
        op.state &= (~QStyle::State_Selected);
    }

    return QGraphicsPathItem::paint(painter, &op, widget);
}

void CustomItem_Path::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
        return;

    QPointF pos = event->pos();
    if (this->isSelected())
        return QGraphicsPathItem::hoverMoveEvent(event);

    QSize cursorSize = PublicFunction::getScaleSize(QSize(24, 24));
    QCursor cursor;
    if (this->shape().contains(pos)){
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png").scaled(cursorSize));
    }else {
        cursor = Qt::ArrowCursor;
    }
    this->setCursor(cursor);
    return QGraphicsPathItem::hoverMoveEvent(event);
}

void CustomItem_Path::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    return QGraphicsPathItem::hoverLeaveEvent(event);
}

void CustomItem_Path::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void CustomItem_Path::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ((this->flags() & QGraphicsItem::ItemIsSelectable) != QGraphicsItem::ItemIsSelectable)
        return;

    if (this->isSelected())
        return;

    QPointF mousePos = event->pos();
    if (qAbs(mousePos.x() - m_pMousePressedPoint.x()) < 5 &&
            qAbs(mousePos.y() - m_pMousePressedPoint.y()) < 5)
        return;

    m_pHasMouseMove = true;
    qreal subX = mousePos.x() - m_pMouseLastPoint.x();
    qreal subY = mousePos.y() - m_pMouseLastPoint.y();
    if (m_pIsClone) {
        this->toClone(subX, subY);
    }else {
        QPainterPath path = this->path();
        path.translate(QPointF(subX, subY));
        this->setPath(path);
    }
    m_pMouseLastPoint = mousePos;
}

void CustomItem_Path::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
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
        this->newActionFinished();
        emit this->itemHasChanged(this);
    }
}

void CustomItem_Path::pushDataToUndoData(QVariant variant, CustomItem_Path::HistoryType type)
{
    m_pUndoData.push_back(variant);
    m_pUndoType.push_back(type);

    m_pRedoData.clear();
    m_pRedoType.clear();
}

