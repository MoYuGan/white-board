#include "graphicsitem.h"
#include <QtDebug>

GraphicsItem::GraphicsItem(QGraphicsItem *parent) :
    QGraphicsPathItem(parent)
{
    this->setAcceptedMouseButtons(Qt::LeftButton);  //只接受鼠标左键
    this->setAcceptHoverEvents(true);   //开启鼠标跟踪
    this->setAcceptTouchEvents(true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);

    m_pUndoData.clear();
    m_pUndoType.clear();
    m_pRedoData.clear();
    m_pRedoType.clear();
}

QRectF GraphicsItem::boundingRect() const
{
    QPainterPathStroker pathStroker;
    pathStroker.setWidth(this->pen().width());
    QPainterPath path = pathStroker.createStroke(this->path());
    return path.boundingRect();
}

QPainterPath GraphicsItem::shape() const
{
    QPainterPath path;
    path.addPath(this->path());
    return path;
}

bool GraphicsItem::is3DShape()
{
    if(inpath.isEmpty())return false;
    else return true;
}

void GraphicsItem::firstSetPen(const QPen &pen)
{
    QGraphicsPathItem::setPen(pen);
}

void GraphicsItem::m_setPen(const QPen &pen)
{
    this->pushDataToUndoData(HistoryType::Pen);
    //设置新的画笔
    QGraphicsPathItem::setPen(pen);
    update();
}

void GraphicsItem::firsetSetBrush(const QBrush &brush)
{
    QGraphicsPathItem::setBrush(brush);
}

void GraphicsItem::m_setBrush(const QBrush &brush)
{
    this->pushDataToUndoData(HistoryType::Brush);
    //设置新的画笔
    QGraphicsPathItem::setBrush(brush);
}

void GraphicsItem::m_setZValue(qreal z)
{
    this->pushDataToUndoData(HistoryType::ZValue);

    //设置新的图层级数
    QGraphicsPathItem::setZValue(z);
}

void GraphicsItem::setSelected(bool selected)
{
    if (ToolType::Cursor == g_ToolType)
        QGraphicsPathItem::setSelected(selected);
}

void GraphicsItem::setPath(QPainterPath path, QPainterPath path2)
{
    if(!path2.isEmpty())inpath =path2;
    QGraphicsPathItem::setPath(path);
}

void GraphicsItem::moveItem(const QPointF &pt)
{
    QPainterPath path = this->path();
    path.translate(pt.x(), pt.y());
    if(!inpath.isEmpty())inpath.translate(pt.x(), pt.y());
    this->setPath(path);
}

void GraphicsItem::rotateItem(const qreal &angle, const QPointF &center)
{
      QTransform transform;
      transform.rotate(angle, Qt::ZAxis);
      this->setPath(this->getTransformPath(this->path(), transform, center));
      if(!inpath.isEmpty())inpath =this->getTransformPath(inpath, transform, center);
}

void GraphicsItem::scaleItem(const qreal &xFactor, const qreal &yFactor, const QPointF &center)
{
    QTransform transform;
    transform.scale(xFactor, yFactor);
    this->setPath(this->getTransformPath(m_itemoutpath, transform, center));
    if(!inpath.isEmpty())inpath =this->getTransformPath(m_iteminpath, transform, center);
}

void GraphicsItem::getDrawPath(QPainterPath *path1, QPainterPath *path2)
{
    *path1 =this->path();
    *path2 =inpath;
}

void GraphicsItem::flipItemHorizontal(const QPointF &center)
{
    QTransform transform;
    transform.rotate(180, Qt::YAxis);
    this->setPath(this->getTransformPath(this->path(), transform, center));
    if(!inpath.isEmpty())inpath =this->getTransformPath(inpath, transform, center);
    if (m_ErasePathList.size() > 0) {
        m_UndoErasePathList.push_back(m_ErasePathList);
        for(int i = 0; i < m_ErasePathList.size(); i++)
        {
            QList<QPainterPath> newPathList;
            for(int j = 0; j < m_ErasePathList.at(i).size(); j++)
            {
                QPainterPath path = m_ErasePathList.at(i).at(j);
                newPathList.push_back(this->getTransformPath(path, transform, center));
            }
            m_ErasePathList.replace(i, newPathList);
        }
    }
}

void GraphicsItem::flipItemVertical(const QPointF &center)
{
    QTransform transform;
    transform.rotate(180, Qt::XAxis);
    this->setPath(this->getTransformPath(this->path(), transform, center));
    if(!inpath.isEmpty())inpath =this->getTransformPath(inpath, transform, center);
    if (m_ErasePathList.size() > 0) {
        m_UndoErasePathList.push_back(m_ErasePathList);
        for(int i = 0; i < m_ErasePathList.size(); i++)
        {
            QList<QPainterPath> newPathList;
            for(int j = 0; j < m_ErasePathList.at(i).size(); j++)
            {
                QPainterPath path = m_ErasePathList.at(i).at(j);
                newPathList.push_back(this->getTransformPath(path, transform, center));
            }
            m_ErasePathList.replace(i, newPathList);
        }
    }
}

GraphicsItem *GraphicsItem::mirrorItemHorizontal(qreal p)
{
    QTransform transform;
    QPointF center;
    transform.rotate(180, Qt::YAxis);
    center = QPointF(p, this->boundingRect().center().x());
    QPainterPath path = this->getTransformPath(this->path(), transform, center);
    if(!inpath.isEmpty())inpath =this->getTransformPath(inpath, transform, center);

    GraphicsItem *graphicItem = new GraphicsItem;
    graphicItem->firstSetPen(this->pen());
    graphicItem->setPath(path);
    return graphicItem;
}

GraphicsItem *GraphicsItem::mirrorItemVertical(qreal p)
{
    QTransform transform;
    QPointF center;
    transform.rotate(180, Qt::XAxis);
    center = QPointF(this->boundingRect().center().x(), p);
    QPainterPath path = this->getTransformPath(this->path(), transform, center);
    if(!inpath.isEmpty())inpath =this->getTransformPath(inpath, transform, center);

    GraphicsItem *graphicItem = new GraphicsItem;
    graphicItem->firstSetPen(this->pen());
    graphicItem->setPath(path);
    return graphicItem;
}

GraphicsItem* GraphicsItem::cloneItem(const QPointF &pt)
{
    QPainterPath path = this->path();
    path.translate(pt.x(), pt.y());
    GraphicsItem *graphicItem = new GraphicsItem;
    graphicItem->firstSetPen(this->pen());
    graphicItem->setBrush(this->brush());
    if(!inpath.isEmpty())
    {
        QPainterPath temppath =inpath;
        temppath.translate(pt.x(), pt.y());
        graphicItem->setPath(path,temppath);
    }
    else graphicItem->setPath(path);
    return graphicItem;
}

void GraphicsItem::getItemPath()
{
    m_itemoutpath =this->path();
    m_iteminpath =inpath;
}

void GraphicsItem::undo()
{
    if (0 == m_pUndoType.size())
        return;

    switch(m_pUndoType.last())
    {
    case HistoryType::Path: {
        QVariant variant;
        QList<QPainterPath> listpath;
        listpath.append(this->path());
        if(!inpath.isEmpty())listpath.append(inpath);
        variant.setValue(listpath);
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Path);
        QList<QPainterPath> list = m_pUndoData.last().value<QList<QPainterPath>>();
        this->setPath(list.at(0));
        if(list.count()>1)inpath =list.at(1);
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
    case HistoryType::Brush: {
        QVariant variant;
        variant.setValue(this->brush());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Brush);
        QBrush brush = m_pUndoData.last().value<QBrush>();
        this->setBrush(brush);
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

void GraphicsItem::redo()
{
    if (0 == m_pRedoType.size())
        return;

    switch(m_pRedoType.last())
    {
    case HistoryType::Path: {
        QVariant variant;
        QList<QPainterPath> listpath;
        listpath.append(this->path());
        if(!inpath.isEmpty())listpath.append(inpath);
        variant.setValue(listpath);
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Path);
        QList<QPainterPath> list = m_pRedoData.last().value<QList<QPainterPath>>();
        this->setPath(list.at(0));
        if(list.count()>1)inpath =list.at(1);
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
    case HistoryType::Brush: {
        QVariant variant;
        variant.setValue(this->brush());
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Brush);
        QBrush brush = m_pRedoData.last().value<QBrush>();
        this->setBrush(brush);
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

void GraphicsItem::pushDataToUndoData(GraphicsItem::HistoryType type)
{
    QVariant variant;
    QList<QPainterPath> listpath;
    listpath.append(this->path());
    if(!inpath.isEmpty())listpath.append(inpath);
    switch(type)
    {
    case HistoryType::Path: { variant.setValue(listpath);}break;
    case HistoryType::Pen: { variant.setValue(this->pen()); }break;
    case HistoryType::ZValue: { variant.setValue(this->zValue()); }break;
    case HistoryType::Brush: { variant.setValue(this->brush()); }break;
    case HistoryType::Erase: { variant.setValue(m_MaskBitmap); }break;
    default: break;
    }

    m_pUndoData.push_back(variant);
    m_pUndoType.push_back(type);
    m_pRedoData.clear();
    m_pRedoType.clear();
}

void GraphicsItem::eraseWithPath(QPainterPath path)
{
    if (!m_EraseStart) {
        m_ErasePathList.push_back(QList<QPainterPath>() << path);
        m_EraseStart = true;
    }else {
        m_ErasePathList.last().push_back(path);
    }

    QPainter painter;
    QRectF rect = this->boundingRect();
    if (m_MaskBitmap.isNull()) {
        m_MaskBitmap = QBitmap(rect.size().toSize());
        m_MaskBitmap.fill(Qt::black);
    }
    painter.begin(&m_MaskBitmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    path.translate(QPointF(-rect.x(), -rect.y()));
    painter.fillPath(path, Qt::white);
    painter.end();
    update();
}

void GraphicsItem::eraseFinished()
{
    this->pushDataToUndoData(HistoryType::Erase);
    m_EraseStart = false;
}

void GraphicsItem::setOrgErasePath(QList<QPainterPath> pathList)
{
    m_OrgErasePathList = pathList;
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
    QPainterPath path = this->path();
#if  0
    if (!path.isEmpty()) {
        QRectF rect = this->boundingRect();
        QPixmap pixmap = QPixmap(rect.size().toSize());
        pixmap.fill(Qt::transparent);
        QPainter pixmapPainter;
        pixmapPainter.begin(&pixmap);
        pixmapPainter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        if(!inpath.isEmpty())
        {
            pixmapPainter.setPen(QPen(this->pen().color(),this->pen().width(),Qt::DashLine));
            inpath.translate(QPointF(-rect.x(), -rect.y()));
            pixmapPainter.drawPath(inpath);
            inpath.translate(QPointF(rect.x(), rect.y()));
        }
        pixmapPainter.setPen(QPen(this->pen().color(),this->pen().width(),Qt::SolidLine));
        pixmapPainter.setBrush(this->brush());
        path.translate(QPointF(-rect.x(), -rect.y()));
        pixmapPainter.drawPath(path);
        pixmapPainter.end();

        if (!m_MaskBitmap.isNull()) {
            pixmap.setMask(m_MaskBitmap); //设置遮掩图,黑色区域表示显示的部分,白色区域表示不显示部分
        }

        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter->drawPixmap(rect.toRect(), pixmap);
    }
#endif

    if (!path.isEmpty()) {
          painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        if(!inpath.isEmpty())
        {
            painter->setPen(QPen(this->pen().color(),this->pen().width(),Qt::DashLine,Qt::RoundCap));
            painter->drawPath(inpath);
        }
        if (!inpath.isEmpty()) painter->setPen(QPen(this->pen().color(),this->pen().width(),Qt::SolidLine,Qt::RoundCap));
        else if (inpath.isEmpty()) painter->setPen(QPen(this->pen().color(),this->pen().width(),this->pen().style(),Qt::RoundCap));
        painter->setBrush(this->brush());
        painter->drawPath(path);
    }
}

void GraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return QGraphicsPathItem::hoverMoveEvent(event);

    QPointF pos = event->pos();
    QSize cursorSize = Public_Function::getScaleSize(QSize(24, 24));
    QCursor cursor;
    if (this->shape().contains(pos)){
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png").scaled(cursorSize));
    }else {
        cursor = Qt::ArrowCursor;
    }
    this->setCursor(cursor);
    return QGraphicsPathItem::hoverMoveEvent(event);
}

void GraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return QGraphicsPathItem::hoverLeaveEvent(event);

    this->setCursor(Qt::ArrowCursor);
    return QGraphicsPathItem::hoverLeaveEvent(event);
}

void GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressEvent(event->pos());
    return;
}

void GraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    moveEvent(event->pos());
}

void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    releaseEvent();
    return QGraphicsPathItem::mouseReleaseEvent(event);
}

bool GraphicsItem::sceneEvent(QEvent *event)
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

void GraphicsItem::pressEvent(QPointF pos)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return;

    m_pHasMouseMove = false;
    m_pMouseLastPoint = pos;
}

void GraphicsItem::moveEvent(QPointF pos)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return;

    /* 移动不超过5个像素点，当做单击，不移动pathItem */
    QPointF mousePos = pos;
    if (qAbs(mousePos.x() - m_pMouseLastPoint.x()) < 5 &&
            qAbs(mousePos.y() - m_pMouseLastPoint.y()) < 5)
        return;

    m_pHasMouseMove = true;
    if (!m_IsPushToHistory) {
        this->pushDataToUndoData(HistoryType::Path);
        m_IsPushToHistory = true;
    }

    /* 移动pathItem */
    qreal subX = mousePos.x() - m_pMouseLastPoint.x();
    qreal subY = mousePos.y() - m_pMouseLastPoint.y();
    this->moveItem(QPointF(subX, subY));

    m_pMouseLastPoint = mousePos;
}

void GraphicsItem::releaseEvent()
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

QPainterPath GraphicsItem::getTransformPath(const QPainterPath &srcPath, QTransform transform, const QPointF &center)
{
    /* 设置旋转中心 */
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    return transform.map(srcPath);
}
