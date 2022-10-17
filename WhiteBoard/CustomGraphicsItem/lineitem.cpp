#include "lineitem.h"
#include <QtDebug>

LineItem::LineItem(LineItem::LineType type, QGraphicsItem *parent) :
    m_LineType(type), QGraphicsLineItem(parent)
{
    this->setAcceptedMouseButtons(Qt::LeftButton);  //只接受鼠标左键
    this->setAcceptHoverEvents(true);   //开启鼠标跟踪
    this->setAcceptTouchEvents(true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setZValue(z_ValueMax);
    z_ValueMax++;
    m_pUndoData.clear();
    m_pUndoType.clear();
    m_pRedoData.clear();
    m_pRedoType.clear();


}

QRectF LineItem::boundingRect() const
{
    QPainterPathStroker pathStroker;
    pathStroker.setWidth(this->pen().width());
    QPainterPath path = pathStroker.createStroke(m_LinePath);
    return path.boundingRect();
}

QPainterPath LineItem::shape() const
{
    QPainterPathStroker stroker;
    int checkWidth = this->pen().width();
    //检测范围至少10个像素点（1920分辨率下）
    checkWidth > Public_Function::getScaleSize(10) ? checkWidth : Public_Function::getScaleSize(10);
    stroker.setWidth(checkWidth);
    return stroker.createStroke(m_LinePath);
}


void LineItem::setLine(const QLineF &line)
{
    QPainterPath path;
    if (LineType::StraightLine == m_LineType) {
        path.moveTo(line.p1());
        path.lineTo(line.p2());
    }else if (LineType::SingleArrow == m_LineType) {
        path = this->getArrow(line, this->pen().width());
    }else if (LineType::DoubleArrow == m_LineType) {
        path = this->getDoubleArrow(line, this->pen().width());
    }else if (LineType::LineSegment == m_LineType) {
        path = this->getLineSegment(line);
    }

    m_LinePath = path;
    QGraphicsLineItem::setLine(line);
}

void LineItem::firstSetPen(const QPen &pen)
{
    QGraphicsLineItem::setPen(pen);



}

void LineItem::m_setPen(const QPen &pen)
{
    this->pushDataToUndoData(HistoryType::Pen);
    //设置新的画笔
    QGraphicsLineItem::setPen(pen);
    /***********change123 解决大小不能立刻改变的问题***********/
    setLine(this->line());
    update();
}

void LineItem::m_setZValue(qreal z)
{
    this->pushDataToUndoData(HistoryType::ZValue);
    //设置新的图层级数
    QGraphicsLineItem::setZValue(z);
}

void LineItem::setSelected(bool selected)
{
    if (ToolType::Cursor == g_ToolType)
        QGraphicsLineItem::setSelected(selected);
}

void LineItem::moveItem(const QPointF &pt)
{
    QLineF line = this->line();
    line.translate(pt);
    this->setLine(line);

    if (m_ErasePathList.size() > 0) {
        if (!m_ActionStart) {
            m_ActionStart = true;
            m_UndoErasePathList.push_back(m_ErasePathList);
        }

        for(int i = 0; i < m_ErasePathList.size(); i++)
        {
            QList<QPainterPath> newPathList;
            for(int j = 0; j < m_ErasePathList.at(i).size(); j++)
            {
                QPainterPath path = m_ErasePathList.at(i).at(j);
                path.translate(pt);
                newPathList.push_back(path);
            }
            m_ErasePathList.replace(i, newPathList);
        }
    }
}

void LineItem::rotateItem(const qreal &angle, const QPointF &center)
{
    QTransform transform;
    transform.rotate(angle, Qt::ZAxis);
    this->setLine(this->getTransformLine(this->line(), &transform, center));

    if (m_ErasePathList.size() > 0) {
        if (!m_ActionStart) {
            m_ActionStart = true;
            m_UndoErasePathList.push_back(m_ErasePathList);
        }

        for(int i = 0; i < m_ErasePathList.size(); i++)
        {
            QList<QPainterPath> newPathList;
            for(int j = 0; j < m_ErasePathList.at(i).size(); j++)
            {
                QPainterPath path = m_ErasePathList.at(i).at(j);
                newPathList.push_back(this->getTransformPath(path, &transform, center));
            }
            m_ErasePathList.replace(i, newPathList);
        }
    }
}

void LineItem::scaleItem(const qreal &xFactor, const qreal &yFactor, const QPointF &center)
{
    QTransform transform;
    transform.scale(xFactor, yFactor);
    /* 设置缩放中心 */
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    //缩放路径(缩放中心是原点(0,0))
//    QPointF p1 = transform.map(this->line().p1());
//    QPointF p2 = transform.map(this->line().p2());
    QPointF p1 = transform.map(m_itemline.p1());
    QPointF p2 = transform.map(m_itemline.p2());
    this->setLine(QLineF(p1, p2));

    if (m_ErasePathList.size() > 0) {
        if (!m_ActionStart) {
            m_ActionStart = true;
            m_UndoErasePathList.push_back(m_ErasePathList);
        }

        for(int i = 0; i < m_ErasePathList.size(); i++)
        {
            QList<QPainterPath> newPathList;
            for(int j = 0; j < m_ErasePathList.at(i).size(); j++)
            {
                QPainterPath path = m_ErasePathList.at(i).at(j);
                newPathList.push_back(this->getTransformPath(path, &transform, center));
            }
            m_ErasePathList.replace(i, newPathList);
        }
    }
}

void LineItem::actionFinished()
{
    m_ActionStart = false;
}

void LineItem::flipItemHorizontal(const QPointF &center)
{
    QTransform transform;
//    transform.rotate(180, Qt::YAxis);
    transform.rotate(180, Qt::XAxis);
    QLineF newLine = this->getTransformLine(this->line(), &transform, center);
    //调换p1点和p2点，否则旋转点会改变方向
    this->setLine(QLineF(newLine.p2(), newLine.p1()));

    if (m_ErasePathList.size() > 0) {
        m_UndoErasePathList.push_back(m_ErasePathList);
        for(int i = 0; i < m_ErasePathList.size(); i++)
        {
            QList<QPainterPath> newPathList;
            for(int j = 0; j < m_ErasePathList.at(i).size(); j++)
            {
                QPainterPath path = m_ErasePathList.at(i).at(j);
                newPathList.push_back(this->getTransformPath(path, &transform, center));
            }
            m_ErasePathList.replace(i, newPathList);
        }
    }
}

void LineItem::flipItemVertical(const QPointF &center)
{
    QTransform transform;
    transform.rotate(180, Qt::YAxis);
    //transform.rotate(180, Qt::XAxis);
    QLineF newLine = this->getTransformLine(this->line(), &transform, center);
    //调换p1点和p2点，否则旋转点会改变方向
    this->setLine(QLineF(newLine.p2(), newLine.p1()));

    if (m_ErasePathList.size() > 0) {
        m_UndoErasePathList.push_back(m_ErasePathList);
        for(int i = 0; i < m_ErasePathList.size(); i++)
        {
            QList<QPainterPath> newPathList;
            for(int j = 0; j < m_ErasePathList.at(i).size(); j++)
            {
                QPainterPath path = m_ErasePathList.at(i).at(j);
                newPathList.push_back(this->getTransformPath(path, &transform, center));
            }
            m_ErasePathList.replace(i, newPathList);
        }
    }
}

LineItem *LineItem::mirrorItemHorizontal(qreal p)
{
    QTransform transform;
    QPointF center;
    transform.rotate(180, Qt::YAxis);
    center = QPointF(p, this->boundingRect().center().x());
    QLineF line = this->getTransformLine(this->line(), &transform, center);
    /**********change123 解决水平镜像只有一条直线的问题************/
    LineItem *lineItem = new LineItem(this->m_LineType);
    lineItem->firstSetPen(this->pen());
    lineItem->setLine(line);
    return lineItem;
}

LineItem *LineItem::mirrorItemVertical(qreal p)
{
    QTransform transform;
    QPointF center;
    transform.rotate(180, Qt::XAxis);
    center = QPointF(this->boundingRect().center().x(), p);
    QLineF line = this->getTransformLine(this->line(), &transform, center);
    /**********change123 解决垂直镜像只有一条直线的问题************/
    LineItem *lineItem = new LineItem(this->m_LineType);
    lineItem->firstSetPen(this->pen());
    lineItem->setLine(line);
    return lineItem;
}

LineItem *LineItem::cloneItem(const QPointF &pt)
{
    QLineF line = this->line();
    line.translate(pt);
    /**********change123 解决克隆只有一条直线的问题*************/
    LineItem *lineItem = new LineItem(this->m_LineType);
    lineItem->firstSetPen(this->pen());
    lineItem->setLine(line);
    return lineItem;
}

void LineItem::pushDataToUndoData(LineItem::HistoryType type)
{
    QVariant variant;
    switch(type)
    {
    case HistoryType::Line: { variant.setValue(this->line()); }break;
    case HistoryType::Pen: { variant.setValue(this->pen()); }break;
    case HistoryType::ZValue: { variant.setValue(this->zValue()); }break;
    case HistoryType::Erase: { variant = QVariant(); }break;
    default: break;
    }
    m_pUndoData.push_back(variant);
    m_pUndoType.push_back(type);
    m_pRedoData.clear();
    m_pRedoType.clear();
    //emit this->itemChanged(this);
}

void LineItem::undo() {
    if (0 == m_pUndoType.size())
        return;
    switch(m_pUndoType.last())
    {
    case HistoryType::Line: {
        //将当前的QLine加入恢复集合
        QVariant variant;
        variant.setValue(this->line());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Line);
        //从撤销集合里面获取QLine，重新设置QLine
        QLineF line = m_pUndoData.last().toLineF();
        this->setLine(line);
    }break;
    case HistoryType::Pen: {
        QVariant variant;
        variant.setValue(this->pen());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Pen);
        QPen pen = m_pUndoData.last().value<QPen>();
        this->setPen(pen);
        update();
    }break;
    case HistoryType::ZValue: {
        QVariant variant;
        variant.setValue(this->zValue());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::ZValue);
        qreal zvalue = m_pUndoData.last().toReal();
        this->setZValue(zvalue);
    }break;
    case HistoryType::Erase: {
        QVariant variant;
        variant.setValue(m_ErasePathList.last());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Erase);
        m_ErasePathList.pop_back();
    }break;
    default:
        break;
    }
    m_pUndoData.pop_back();
    m_pUndoType.pop_back();
}

void LineItem::redo() {
    if (0 == m_pRedoType.size())
        return;

    switch(m_pRedoType.last())
    {
    case HistoryType::Line: {
        QVariant variant;
        variant.setValue(this->line());
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Line);
        QLineF line = m_pRedoData.last().toLineF();
        this->setLine(line);
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
    case HistoryType::Erase: {
        QList<QPainterPath> pathList = m_pRedoData.last().value<QList<QPainterPath>>();
        m_ErasePathList.push_back(pathList);
        QVariant variant = QVariant();
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Erase);
    }break;
    default:
        break;
    }
    m_pRedoData.pop_back();
    m_pRedoType.pop_back();
}

void LineItem::eraseWithPath(QPainterPath path)
{
    if (!m_EraseStart) {
        m_ErasePathList.push_back(QList<QPainterPath>() << path);
        m_EraseStart = true;
    }else {
        m_ErasePathList.last().push_back(path);
    }
}

void LineItem::eraseFinished()
{
    this->pushDataToUndoData(HistoryType::Erase);
    m_EraseStart = false;
}

void LineItem::setOrgErasePath(QList<QPainterPath> pathList)
{
    m_OrgErasePathList = pathList;
}

void LineItem::getItemLine()
{
    m_itemline =this->line();
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    QPainterPath path = m_LinePath;
#if  0
    if (!path.isEmpty()) {
        QRectF rect = this->boundingRect();
        QPixmap pixmap = QPixmap(rect.size().toSize());
        pixmap.fill(Qt::transparent);
        QPainter pixmapPainter;
        pixmapPainter.begin(&pixmap);
        pixmapPainter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        path.translate(QPointF(-rect.x(), -rect.y()));
        //pixmapPainter.setPen(this->pen());
        QPen pen(this->pen().color(),this->pen().width(),this->pen().style(),Qt::RoundCap,Qt::RoundJoin);
        pixmapPainter.setPen(pen);
        //if (LineType::StraightLine == m_LineType)
            pixmapPainter.drawPath(path);
        //else
            //pixmapPainter.drawPath(path);    //填充轮廓
        foreach(QList<QPainterPath> pathList, m_ErasePathList) {
            for(QPainterPath erasePath : pathList) {
                pixmapPainter.setCompositionMode(QPainter::CompositionMode_Clear);
                erasePath.translate(QPointF(-rect.x(), -rect.y()));
                pixmapPainter.fillPath(erasePath, QBrush(Qt::green));
            }
        }

        pixmapPainter.end();
        painter->drawPixmap(rect.toRect(), pixmap);
    }
#endif
    QPen pen(this->pen().color(),this->pen().width(),this->pen().style(),Qt::RoundCap,Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawPath(path);
}

void LineItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return QGraphicsLineItem::hoverMoveEvent(event);

    QPointF pos = event->pos();
    QSize cursorSize = Public_Function::getScaleSize(QSize(24, 24));
    QCursor cursor;
    if (this->shape().contains(pos)){
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png").scaled(cursorSize));
    }else {
        cursor = Qt::ArrowCursor;
    }
    this->setCursor(cursor);
    return QGraphicsLineItem::hoverMoveEvent(event);
}

void LineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return QGraphicsLineItem::hoverLeaveEvent(event);

    this->setCursor(Qt::ArrowCursor);
    return QGraphicsLineItem::hoverLeaveEvent(event);
}

void LineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressEvent(event->pos());
    return;
}

void LineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    moveEvent(event->pos());
}

void LineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    releaseEvent();
    return QGraphicsLineItem::mouseReleaseEvent(event);
}

bool LineItem::sceneEvent(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            pointid =ev->touchPoints().at(0).id();
            pressEvent(ev->touchPoints().at(0).pos());
            return true;
            break;
        }
        case QEvent::TouchUpdate:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            foreach (QTouchEvent::TouchPoint tp, ev->touchPoints()) {
               if(tp.id() ==pointid)moveEvent(tp.pos());
            }
            return true;
            break;
        }
        case QEvent::TouchEnd:
        {
            releaseEvent();
            return true;
            break;
        }
        default:
        {
            break;
        }
    }
    return QGraphicsItem::sceneEvent(event);
}

void LineItem::pressEvent(QPointF pos)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return;

    m_pHasMouseMove = false;
    m_pMouseLastPoint = pos;
    m_pMousePressedPoint = pos;
}

void LineItem::moveEvent(QPointF pos)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return;

    /* 移动不超过5个像素点，当做单击，不移动lineItem */
    QPointF mousePos = pos;
    if (qAbs(mousePos.x() - m_pMousePressedPoint.x()) < 5 &&
            qAbs(mousePos.y() - m_pMousePressedPoint.y()) < 5)
        return;

    if (!m_IsPushToHistory) {
        this->pushDataToUndoData(HistoryType::Line);   //加入撤销记录
        m_IsPushToHistory = true;
    }

    m_pHasMouseMove = true;
    qreal subX = mousePos.x() - m_pMouseLastPoint.x();
    qreal subY = mousePos.y() - m_pMouseLastPoint.y();
    this->moveItem(QPointF(subX, subY));
    m_pMouseLastPoint = mousePos;
}

void LineItem::releaseEvent()
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return;

    if (!m_pHasMouseMove) {
        emit itemClicked(this);  //发送选中信号
    }else {
        m_IsPushToHistory = false;
        emit this->itemChanged(this);
    }
}

QPainterPath LineItem::getArrow(QLineF line, int penWidth) {
    qreal angle = atan2(-line.dy(), line.dx());
    qreal arrowSize = penWidth * Public_Function::getScaleSize(8);
    QPointF arrowP1 = line.p2() - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                          cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                          cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPainterPath path;
    path.moveTo(line.p1());
    path.lineTo(line.p2());
    path.lineTo(arrowP1);
    path.moveTo(line.p2());
    path.lineTo(arrowP2);
    return path;
}

QPainterPath LineItem::getDoubleArrow(QLineF line, int penWidth)
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

QPainterPath LineItem::getLineSegment(QLineF line) {
    QPointF p1 = line.p1();
    QPointF p2 = line.p2();
    QPointF ePoint1, ePoint2;
    int height = Public_Function::getScaleSize(10);
    if (p1.y() == p2.y() && p1.x() < p2.x()) {
        ePoint1 = QPointF(p1.x(), p1.y() - height);
        ePoint2 = QPointF(p2.x(), p2.y() - height);
    }else if(p1.y() == p2.y() && p1.x() < p2.x()) {
        ePoint1 = QPointF(p1.x(), p1.y() + height);
        ePoint2 = QPointF(p2.x(), p2.y() + height);
    }else if(p1.x() <= p2.x() && p1.y() <= p2.y()) {
        qreal a = atan(qAbs(p1.y() - p2.y())/qAbs(p1.x() - p2.x()));
        ePoint1 = QPointF(p1.x() + height*sin(a),
                          p1.y() - height*cos(a));
        ePoint2 = QPointF(p2.x() + height*sin(a),
                          p2.y() - height*cos(a));
    }else if (p2.x() <= p1.x() && p2.y() <= p1.y()){
        qreal a = atan(qAbs(p1.y() - p2.y())/qAbs(p1.x() - p2.x()));
        ePoint1 = QPointF(p1.x() - height*sin(a),
                          p1.y() + height*cos(a));
        ePoint2 = QPointF(p2.x() - height*sin(a),
                          p2.y() + height*cos(a));
    }else if (p1.x() <= p2.x() && p1.y() >= p2.y()){
        qreal a = atan(qAbs(p1.y() - p2.y())/qAbs(p1.x() - p2.x()));
        ePoint1 = QPointF(p1.x() - height*sin(a),
                          p1.y() - height*cos(a));
        ePoint2 = QPointF(p2.x() - height*sin(a),
                          p2.y() - height*cos(a));
    }else{
        qreal a = atan(qAbs(p1.y() - p2.y())/qAbs(p1.x() - p2.x()));
        ePoint1 = QPointF(p1.x() + height*sin(a),
                          p1.y() + height*cos(a));
        ePoint2 = QPointF(p2.x() + height*sin(a),
                          p2.y() + height*cos(a));
    }
    QPainterPath path;
    path.moveTo(ePoint1);
    path.lineTo(p1);
    path.lineTo(p2);
    path.lineTo(ePoint2);

//    QPainterPathStroker stroker;
//    stroker.setWidth(this->pen().width());
//    stroker.setCapStyle(Qt::SquareCap);
//    stroker.setJoinStyle(Qt::MiterJoin);
//    return stroker.createStroke(path);
    return path;
}

QLineF LineItem::getTransformLine(const QLineF &srcLine, QTransform *transform, const QPointF &center)
{
    QPointF tCenter = transform->map(center);
    transform->setMatrix(transform->m11(), transform->m12(), transform->m13(),
                        transform->m21(), transform->m22(), transform->m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform->m33());
    return transform->map(srcLine);
}

QPainterPath LineItem::getTransformPath(const QPainterPath &srcPath, QTransform *transform, const QPointF &center)
{
    /* 设置旋转中心 */
    QPointF tCenter = transform->map(center);
    transform->setMatrix(transform->m11(), transform->m12(), transform->m13(),
                        transform->m21(), transform->m22(), transform->m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform->m33());
    return transform->map(srcPath);
}


