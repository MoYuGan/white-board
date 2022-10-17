#include "pathitem.h"
#include <QtDebug>
#include <qmath.h>
PathItem::PathItem(QGraphicsItem *parent,int num,int num1) : QGraphicsPathItem(parent)
{
    this->setAcceptedMouseButtons(Qt::LeftButton);  //只接受鼠标左键
    this->setAcceptHoverEvents(true);   //开启鼠标跟踪
    this->setAcceptTouchEvents(true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setZValue(z_ValueMax);
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache,this->boundingRect().toRect().size());
    if(num ==0)
    z_ValueMax++;
    m_pUndoData.clear();
    m_pUndoType.clear();
    m_pRedoData.clear();
    m_pRedoType.clear();
    pathshape =num1;
}

QPainterPath PathItem::shape() const
{
    QPainterPathStroker stroker;
    int checkWidth = this->pen().width();
    //检测范围至少10个像素点（1920分辨率下）
    checkWidth > Public_Function::getScaleSize(10) ? checkWidth : Public_Function::getScaleSize(10);
    stroker.setWidth(checkWidth);
    return stroker.createStroke(this->path());
}

int PathItem::getPathCount()
{
    return this->path().elementCount();
}

void PathItem::setSubPaths(QList<QPainterPath> subPaths)
{
    m_SubPaths.clear();
    m_SubPaths = subPaths;
}

QList<QPainterPath> PathItem::getSubPaths()
{
    return m_SubPaths;
}

void PathItem::firstSetPen(const QPen &pen)
{
    QGraphicsPathItem::setPen(pen);
}

void PathItem::m_setPen(const QPen &pen)
{
    this->pushDataToUndoData(HistoryType::Pen);
    //设置新的画笔
    QGraphicsPathItem::setPen(pen);
}

void PathItem::m_setZValue(qreal z)
{
    this->pushDataToUndoData(HistoryType::ZValue);
    //设置新的图层级数
    QGraphicsPathItem::setZValue(z);
}

void PathItem:: m_drawPath(QPainter *painter, int number)
{
#if  1
    if(path().elementCount() <= number)
    {
        //djf
        for(int m=0;m<path().elementCount() -1;m++)
        {
          pathlist[m].clear();
          pathlist[m].moveTo(this->path().elementAt(path().elementCount() -m -2));
          pathlist[m].lineTo(this->path().elementAt(path().elementCount() -m -1));
        }
//        pathlist[0].clear();
//        pathlist[0].addPath(this->path());
        drawNib(painter,number,1);
    }
    else
    {
        QPainterPath mpath;
        for (int var = 0; var < this->path().elementCount() -number; ++var) {
             if(var ==0)mpath.moveTo((this->path().elementAt(0) +this->path().elementAt(1))/2);
             else mpath.quadTo(this->path().elementAt(var),(this->path().elementAt(var) +this->path().elementAt(var +1))/2);
        }
        int num =this->path().elementCount();
        mpath.quadTo((this->path().elementAt(num -number -1) +this->path().elementAt(num -number))/2,this->path().elementAt(num -number));
        painter->drawPath(mpath);

        //djf
        for(int m=0;m<number -1 ;m++)
        {
          pathlist[m].clear();
          pathlist[m].moveTo(this->path().elementAt(num -number +m));
          pathlist[m].lineTo(this->path().elementAt(num -number +m +1));
        }
//        pathlist[0].clear();
//        for(int m=0;m<number -1 ;m++)
//        {
//          if( m ==0)
//            pathlist[0].moveTo(this->path().elementAt(num -number +m));
//          else
//            pathlist[0].lineTo(this->path().elementAt(num -number +m));
//        }
        drawNib(painter,number,2);
    }
    update();
#endif

}

void PathItem::m_comparePath(QPainterPath currentpath, QPainterPath lastpath)
{
    int num =-1;
    QPointF dot =currentpath.elementAt(0);
    for (int var = 0; var < lastpath.elementCount(); ++var)
    {
        if(lastpath.elementAt(var) ==dot)
        {
          num =var;
          if(num >-1)break;
        }
    }

    if(num ==0)
    {
        if(lastpath.elementCount() -currentpath.elementCount() <6)
        {
            m_number -=(lastpath.elementCount() -currentpath.elementCount());
            pathshape =1;
        }
        else
        {
            pathshape =0;
        }
        update();
    }
    else if((num >0)&&(num <3))
    {

    }

}

int PathItem::m_getNumber()
{
    return m_number;
}

void PathItem::m_setNumber(int num)
{
    m_number =num;
}

void PathItem::m_getPathShapeData(PathItem *pathItem,QPainterPath path)
{
    pathItem->firstSetPen(this->pen());
    pathItem->setPath(path);
    if(pathshape ==0)pathItem->changePathShape(0);
    else if(pathshape ==1)pathItem->changePathShape(1);
    pathItem->m_setNumber(m_number);
}

void PathItem::drawNib(QPainter *painter,int number ,int num)
{
    qreal temp =(pen().width() -pen().width()/6)/5/100.;
    qreal mtemp =(pen().width() -pen().width()/6)/5;
    for(int m=0;m<number;m++)
    {
       int k = 0;
       for (qreal i = 0;i < 1; i+=0.01)
       {
           k++;
           qreal penwidth =0;
           if(num  ==1)penwidth =pen().width() - mtemp*(number -m -2) -temp*k;
           if(num  ==2)penwidth =pen().width() - mtemp*m -temp*k;
           if(penwidth <1)penwidth=1;
           painter->setPen(QPen(this->pen().color(),penwidth,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
           painter->drawPoint(pathlist[m].pointAtPercent(i));
       }
    }
//djf ruanbi bijian
//    qreal tmp = pen().width() * 0.01;
//    int penWidth = pen().width();
//    int k =0;
//       for( qreal i = 0.01; i < 1; i+= 0.01)
//       {
//            k++;
//            painter->setPen(QPen(this->pen().color(), penWidth - tmp * k , Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//            painter->drawPoint(pathlist[0].pointAtPercent(i));

//       }

}

void PathItem::m_drawLine(QPainter *painter, QPointF dot1, QPointF dot2, double penwidth1, double penwidth2)
{
    QPainterPath mpath;
    painter->save();
    painter->setPen(QPen(this->pen().color(),penwidth1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter->drawPoint(dot1);
    painter->setPen(QPen(this->pen().color(),penwidth2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter->drawPoint(dot2);
    painter->translate(dot2);
    QPointF dot3(dot2.x(),dot1.y());
    qreal num =getrotate(dot1,dot2,dot3);

    qreal length = sqrt((dot2.y() -dot3.y())*(dot2.y() -dot3.y()) +
                        (dot1.x() -dot3.x())*(dot1.x() -dot3.x()));
    painter->rotate(-num);
    mpath.moveTo(0,0);
    mpath.lineTo(0,-penwidth1/2);
    mpath.lineTo(length,-penwidth2/2);
    mpath.lineTo(length,penwidth2/2);
    mpath.lineTo(0,penwidth1/2);
    mpath.closeSubpath();
    painter->setPen(Qt::NoPen);
    painter->setBrush(this->pen().color());
    painter->drawPath(mpath);
    painter->restore();
}

double PathItem::getrotate(QPointF cen, QPointF second, QPointF first)
{
    double ma_x = first.x() - cen.x();
    double ma_y = first.y() - cen.y();
    double mb_x = second.x() - cen.x();
    double mb_y = second.y() - cen.y();
    double v1 = (ma_x * mb_x) + (ma_y * mb_y);
    double ma_val = sqrt(ma_x * ma_x + ma_y * ma_y);
    double mb_val = sqrt(mb_x * mb_x + mb_y * mb_y);
    double cosm = v1 / (ma_val * mb_val);
    double angleAMB = acos(cosm) * 180 / M_PI;
    return angleAMB;
}

void PathItem::getItemPath()
{
    m_itempath = this->path();
}

void PathItem::changePathShape(int num)
{
    pathshape =num;
    update();
}

int PathItem::getPathShape()
{
    return pathshape;
}

void PathItem::setSelected(bool selected)
{
    if (ToolType::Cursor == g_ToolType)
        QGraphicsPathItem::setSelected(selected);
}

QList<QGraphicsItem *> PathItem::getFullPathItems()
{
    return m_FullPathItems;
}

QPen PathItem::getItemPen()
{
    return this->pen();
}

int PathItem::getItemZvalue()
{
    return this->zValue();
}

void PathItem::recursiveChildItem(QList<QGraphicsItem *> *childItems)
{
    for(QGraphicsItem *item : this->childItems()) {
        childItems->push_back(item);
        PathItem *pathItem = static_cast<PathItem*>(item);
        pathItem->recursiveChildItem(childItems);
    }
}

void PathItem::recursiveParentItem(QList<QGraphicsItem *> *parentItems)
{
    QGraphicsItem* parentItem = this->parentItem();
    if (0 != parentItem) {
        parentItems->insert(0, parentItem);
        PathItem *pathItem = static_cast<PathItem*>(parentItem);
        pathItem->recursiveParentItem(parentItems);
    }
}

void PathItem::moveItem(const QPointF &pt)
{
    QPainterPath path = this->path();
    path.translate(pt.x(), pt.y());
    this->setPath(path);
}

void PathItem::moveItem(QGraphicsItem *item, const QPointF &pt)
{
        PathItem *pathItem = static_cast<PathItem*>(item);
        pathItem->moveItem(pt);
}

void PathItem::rotateItem(const qreal &angle, const QPointF &center)
{
    QTransform transform;
    transform.rotate(angle, Qt::ZAxis);
    this->setPath(this->getTransformPath(this->path(), &transform, center));
}

void PathItem::scaleItem(const qreal &xFactor, const qreal &yFactor, const QPointF &center)
{
//    QTransform transform;
//    transform.scale(xFactor, yFactor);
//    qDebug() << " xFactor" << xFactor <<yFactor <<Qt::endl;
//    this->setPath(this->getTransformPath(this->path(), &transform, center));

    QTransform transform;
    transform.scale(xFactor,yFactor);
//    QPointF tCenter = transform.map(center);
//    m_PixmapRect =transform.mapRect(m_itemrect);
//    m_PixmapRect.translate(center.toPoint() -tCenter.toPoint());

    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    QPainterPath path =transform.map(m_itempath);
    this->setPath(path);

    this->prepareGeometryChange();
    update();
}

QPainterPath PathItem::flipItemHorizontal(const QPointF &center)
{
    QTransform transform;
    transform.rotate(180, Qt::YAxis);
    QPainterPath path =this->getTransformPath(this->path(), &transform, center);
    return path;
}

QPainterPath PathItem::flipItemVertical(const QPointF &center)
{
    QTransform transform;
    transform.rotate(180, Qt::XAxis);
    QPainterPath path =this->getTransformPath(this->path(), &transform, center);
    return path;
}

PathItem* PathItem::mirrorItemHorizontal(qreal p, QGraphicsItem *parent)
{
    QTransform transform;
    QPointF center;
    transform.rotate(180, Qt::YAxis);
    center = QPointF(p, this->boundingRect().center().y());
    QPainterPath path = this->getTransformPath(this->path(), &transform, center);

    PathItem *pathItem = new PathItem(parent);
    m_getPathShapeData(pathItem,path);
    return pathItem;
}

PathItem* PathItem::mirrorItemVertical(qreal p, QGraphicsItem *parent)
{
    QTransform transform;
    QPointF center;
    transform.rotate(180, Qt::XAxis);
    center = QPointF(this->boundingRect().center().x(), p);
    QPainterPath path = this->getTransformPath(this->path(), &transform, center);

    PathItem *pathItem = new PathItem(parent);
    m_getPathShapeData(pathItem,path);
    return pathItem;
}

PathItem *PathItem::cloneItem(const QPointF &pt, QGraphicsItem *parent)
{
    QPainterPath path = this->path();
    path.translate(pt.x(), pt.y());

    PathItem *pathItem = new PathItem(parent);
    m_getPathShapeData(pathItem,path);
    return pathItem;
}

void PathItem::undo()
{
    if (0 == m_pUndoType.size())
        return;

    switch(m_pUndoType.last())
    {
    case HistoryType::Path: {
        QVariant variant;
        variant.setValue(this->path());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Path);
        QPainterPath path = m_pUndoData.last().value<QPainterPath>();
        this->setPath(path);
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

void PathItem::redo()
{
    if (0 == m_pRedoType.size())
        return;

    switch(m_pRedoType.last())
    {
    case HistoryType::Path: {
        QVariant variant;
        variant.setValue(this->path());
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Path);
        QPainterPath path = m_pRedoData.last().value<QPainterPath>();
        this->setPath(path);
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

void PathItem::pushDataToUndoData(PathItem::HistoryType type)
{
    QVariant variant;
    switch(type)
    {
    case HistoryType::Path: { variant.setValue(this->path()); }break;
    case HistoryType::Pen: { variant.setValue(this->pen()); }break;
    case HistoryType::ZValue: { variant.setValue(this->zValue()); }break;
    default: break;
    }

    m_pUndoData.push_back(variant);
    m_pUndoType.push_back(type);
    m_pRedoData.clear();
    m_pRedoType.clear();
}

void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(this->pen().color(),this->pen().width(),Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if(m_number <2)pathshape =0;
    if(pathshape ==1)
    {
        m_drawPath(painter,m_number);
    }
    else if(pathshape ==0)
    {
        QPainterPath mpath;
        for (int var = 0; var < this->path().elementCount() -1; ++var) {
               if(var ==0)mpath.moveTo((this->path().elementAt(0) +this->path().elementAt(1))/2);
               else mpath.quadTo(this->path().elementAt(var),(this->path().elementAt(var) +this->path().elementAt(var +1))/2);
            }
        painter->drawPath(mpath);
    }

//    painter->setPen(QPen(Qt::red,7,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//    for(int num =0;num <path().elementCount();num++)
//    {
//        painter->drawPoint(path().elementAt(num));
//    }
}

void PathItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
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

void PathItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return QGraphicsPathItem::hoverLeaveEvent(event);

    this->setCursor(Qt::ArrowCursor);
    return QGraphicsPathItem::hoverLeaveEvent(event);
}

void PathItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressEvent(event->pos());
    return;
}

void PathItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    moveEvent(event->pos());
}

void PathItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    releaseEvent();
    return QGraphicsPathItem::mouseReleaseEvent(event);
}

bool PathItem::sceneEvent(QEvent *event)
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

void PathItem::pressEvent(QPointF pos)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor ||
            !this->shape().contains(pos))
        return;

    m_MousePressed = true;
    m_pMouseLastPoint = pos;
}

void PathItem::moveEvent(QPointF pos)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor || !m_MousePressed)
        return;

    /* 移动不超过5个像素点，当做单击，不移动pathItem */
    QPointF mousePos = pos;
    if (qAbs(mousePos.x() - m_pMouseLastPoint.x()) < 5 &&
            qAbs(mousePos.y() - m_pMouseLastPoint.y()) < 5)
        return;

    if (!m_IsPushToHistory) {
            PathItem *pathItem = static_cast<PathItem*>(this);
            pathItem->pushDataToUndoData(HistoryType::Path);   //加入撤销记录
        m_IsPushToHistory = true;
    }

    /* 移动pathItem */
    m_HasMoved = true;
    qreal subX = mousePos.x() - m_pMouseLastPoint.x();
    qreal subY = mousePos.y() - m_pMouseLastPoint.y();
    this->moveItem(this, QPointF(subX, subY));
    m_pMouseLastPoint = mousePos;
}

void PathItem::releaseEvent()
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor || !m_MousePressed)
        return;

    if (!m_HasMoved) {
        emit itemClicked(this);  //发送选中信号
    }else {
        m_IsPushToHistory = false;
        emit this->itemChanged(this);
    }

    m_MousePressed = false;
    m_HasMoved = false;
}
QPainterPath PathItem::getTransformPath(const QPainterPath &srcPath, QTransform *transform, const QPointF &center)
{
    /* 设置旋转中心 */
    QPointF tCenter = transform->map(center);
    transform->setMatrix(transform->m11(), transform->m12(), transform->m13(),
                        transform->m21(), transform->m22(), transform->m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform->m33());
    return transform->map(srcPath);
}
