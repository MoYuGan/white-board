#include "pixmapitem.h"
#include <QtDebug>
#include <QScreen>
PixmapItem::PixmapItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    this->setAcceptedMouseButtons(Qt::LeftButton);  //只接受鼠标左键
    this->setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
    this->setAcceptHoverEvents(true);   //开启鼠标跟踪
    this->setAcceptTouchEvents(true);
    this->setZValue(z_ValueMax);
    z_ValueMax++;
    m_pUndoData.clear();
    m_pUndoType.clear();
    m_pRedoData.clear();
    m_pRedoType.clear();
    movie =new QMovie;
}

QRectF PixmapItem::boundingRect() const
{
    QRectF retRect;
    if (0 == m_RotateAngle)
        retRect = m_PixmapRect;
    else {
        QPainterPath path;
        QTransform transform;
        transform.rotate(m_RotateAngle, Qt::ZAxis);
        QPointF tCenter = transform.map(m_RotateCenter);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            m_RotateCenter.x() - tCenter.x(), m_RotateCenter.y() - tCenter.y(), transform.m33());
        QRectF rect = transform.mapRect(m_PixmapRect);
        path.addRect(rect);
        retRect = path.boundingRect();
    }
    return retRect;
}

QPainterPath PixmapItem::shape() const
{
    QPainterPath path;
    if (0 != m_RotateAngle) {
        QTransform transform;
        transform.rotate(m_RotateAngle, Qt::ZAxis);
        QPointF tCenter = transform.map(m_RotateCenter);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            m_RotateCenter.x() - tCenter.x(), m_RotateCenter.y() - tCenter.y(), transform.m33());
        path.moveTo(transform.map(m_PixmapRect.topLeft()));
        path.lineTo(transform.map(m_PixmapRect.topRight()));
        path.lineTo(transform.map(m_PixmapRect.bottomRight()));
        path.lineTo(transform.map(m_PixmapRect.bottomLeft()));
    }else {
        path.addRect(m_PixmapRect);
    }
    return path;
}

/*GIF图片*/
void PixmapItem::m_setGifPixmap(const QString fileName, const QRect &rect, QPointF rotateCenter, qreal rotateAngle)
{
    this->setZValue(1999);
    QString suffix = fileName.mid(fileName.length() -4);
    if(suffix.compare(".gif") ==0) {
        isgif =true;
        movie = new QMovie(fileName);
        movie->start();
        m_Pixmap =movie->currentPixmap();
        QTimer *timer =new QTimer(this);
        timer->start(30);
        connect(timer,&QTimer::timeout,this,[=](){
            m_Pixmap =movie->currentPixmap();
            update();
        });
    }

    m_PixmapRect = rect;
    m_RotateAngle = rotateAngle;
    if (0 == rotateAngle)
        m_RotateCenter = rect.center();
    else
        m_RotateCenter = rotateCenter;
    this->prepareGeometryChange();
    update();
}
/*普通图片*/
void PixmapItem::m_setPixmap(const QPixmap &pixmap, const QRect &rect, QPointF rotateCenter, qreal rotateAngle)
{
    m_Pixmap = pixmap;
    m_PixmapRect = rect;
    m_RotateAngle = rotateAngle;
    if (0 == rotateAngle)
        m_RotateCenter = rect.center();
    else
        m_RotateCenter = rotateCenter;
    this->prepareGeometryChange();
    update();
}

bool PixmapItem::IsGifPixmap()
{
    return isgif;
}

void PixmapItem::m_setZValue(qreal value)
{
    this->pushDataToUndoData(HistoryType::ZValue);
    QGraphicsItem::setZValue(value);
}

void PixmapItem:: scaleItem(const qreal &xFactor, const qreal &yFactor, const QPointF &center)
{
//    /* 设置缩放中心 */
//    tCenter = transform.map(center);
//    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
//                        transform.m21(), transform.m22(), transform.m23(),
//                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
//    m_PixmapRect = transform.mapRect(m_PixmapRect);
//    this->prepareGeometryChange();
//    update();

    QTransform transform;
    transform.scale(xFactor,yFactor);
    QPointF tCenter = transform.map(center);
    m_PixmapRect =transform.mapRect(m_itemrect);
    m_PixmapRect.translate(center.toPoint() -tCenter.toPoint());
    this->prepareGeometryChange();
    update();
}

void PixmapItem::rotateItem(qreal angle, const QPointF &center)
{
    m_RotateAngle += angle;
    m_RotateCenter = center;

    this->prepareGeometryChange();
    update();
}

void PixmapItem::moveItem(const QPointF &subPt)
{

    m_PixmapRect.translate(subPt.x(), subPt.y());
    m_RotateCenter = QPointF(m_RotateCenter.x() + subPt.x(), m_RotateCenter.y() + subPt.y());

    //update之前先调用prepareGeometryChange()避免原来的item区域不刷新导致图片残留
    this->prepareGeometryChange();
    update();
}

void PixmapItem::undo()
{
    if (0 == m_pUndoType.size())
        return;

    switch(m_pUndoType.last())
    {
    case HistoryType::Move: {
        QVariant variant;
        variant.setValue(m_PixmapRect);
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Move);
        QRect rect = m_pUndoData.last().value<QRect>();
        m_PixmapRect = rect;

        this->prepareGeometryChange();
        update();
    }break;
    case HistoryType::ZValue: {
        int zvalue = m_pUndoData.last().value<int>();
        QVariant variant;
        variant.setValue(this->zValue());
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::ZValue);
        this->setZValue(zvalue);
    }break;
    case HistoryType::Rotate: {
        QList<QVariant> list = m_pUndoData.last().value<QList<QVariant>>();
        if (2 != list.size())
            return;
        qreal angle = list.at(0).toReal();
        QPointF center = list.at(1).toPointF();
        QVariant variant;
        variant.setValue(QList<QVariant>() << QVariant(m_RotateAngle) << QVariant(m_RotateCenter));
        m_pRedoData.push_back(variant);
        m_pRedoType.push_back(HistoryType::Rotate);
        m_RotateAngle = angle;
        m_RotateCenter = center;

        this->prepareGeometryChange();
        update();
    }break;
    default:
        break;
    }
    m_pUndoData.pop_back();
    m_pUndoType.pop_back();
}

void PixmapItem::redo()
{
    if (0 == m_pRedoType.size())
        return;

    switch(m_pRedoType.last())
    {
    case HistoryType::Move: {
        QVariant variant;
        variant.setValue(m_PixmapRect);
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Move);
        QRect rect = m_pRedoData.last().value<QRect>();
        m_PixmapRect = rect;

        this->prepareGeometryChange();
        update();
    }break;
    case HistoryType::ZValue: {
        int zvalue = m_pRedoData.last().value<int>();
        QVariant variant;
        variant.setValue(this->zValue());
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::ZValue);
        this->setZValue(zvalue);
    }break;
    case HistoryType::Rotate: {
        QList<QVariant> list = m_pRedoData.last().value<QList<QVariant>>();
        if (2 != list.size())
            return;
        qreal angle = list.at(0).toReal();
        QPointF center = list.at(1).toPointF();
        QVariant variant;
        variant.setValue(QList<QVariant>() << QVariant(m_RotateAngle) << QVariant(m_RotateCenter));
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(HistoryType::Rotate);
        m_RotateAngle = angle;
        m_RotateCenter = center;

        this->prepareGeometryChange();
        update();
    }break;
    default:
        break;
    }
    m_pRedoData.pop_back();
    m_pRedoType.pop_back();
}

void PixmapItem::pushDataToUndoData(PixmapItem::HistoryType type)
{
    QVariant variant;
    switch(type)
    {
    case HistoryType::Move: { variant.setValue(m_PixmapRect); }break;
    case HistoryType::ZValue: { variant.setValue(this->zValue()); }break;
    case HistoryType::Rotate: { variant.setValue(QList<QVariant>() << QVariant(m_RotateAngle) << QVariant(m_RotateCenter));}break;
    default: break;
    }
    m_pUndoData.push_back(variant);
    m_pUndoType.push_back(type);
    m_pRedoData.clear();
    m_pRedoType.clear();
}

bool PixmapItem::isDelete()
{
    return m_delete;
}

void PixmapItem::setDelete(bool bo)
{
    m_delete =bo;
}

void PixmapItem::getItemRect()
{
    m_itemrect =m_PixmapRect;
}

void PixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if (!m_Pixmap.isNull()) {
        if (0 != m_RotateAngle) {
            QTransform transform;
            transform.rotate(m_RotateAngle, Qt::ZAxis);
            QPointF tCenter = transform.map(m_RotateCenter);
            transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                                transform.m21(), transform.m22(), transform.m23(),
                                m_RotateCenter.x() - tCenter.x(), m_RotateCenter.y() - tCenter.y(), transform.m33());
            painter->setTransform(transform);
        }
        painter->drawPixmap(m_PixmapRect, m_Pixmap);
    }
}

void PixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return QGraphicsItem::hoverMoveEvent(event);

    QPointF pos = event->pos();

    QSize cursorSize = Public_Function::getScaleSize(QSize(24, 24));
    QCursor cursor;
    if (this->shape().contains(pos)){
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png").scaled(cursorSize));
    }else {
        cursor = Qt::ArrowCursor;
    }
    this->setCursor(cursor);
    return QGraphicsItem::hoverMoveEvent(event);
}

void PixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return QGraphicsItem::hoverMoveEvent(event);

    this->setCursor(Qt::ArrowCursor);
}

void PixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressEvent(event->pos());
    return;
}

void PixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   moveEvent(event->pos());
}

void PixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    releaseEvent();
}

bool PixmapItem::sceneEvent(QEvent *event)
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

void PixmapItem::pressEvent(QPointF pos)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return;

    m_pHasMouseMove = false;
    m_pMouseLastPoint = pos;
}

void PixmapItem::moveEvent(QPointF pos)
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return ;
    QPointF mousePos = pos;
    //移动值超过5个像素点才算移动事件,避免大屏上运行时每次手指单击都误认为是移动事件，无法选中
    if ((qAbs(mousePos.x() - m_pMouseLastPoint.x()) < 5 &&
           qAbs(mousePos.y() - m_pMouseLastPoint.y()) < 5) && !m_pHasMouseMove)
        return;

    m_pHasMouseMove = true;
    if (m_IsPushToHistory) {
        this->pushDataToUndoData(HistoryType::Move);   //加入撤销记录
        m_IsPushToHistory = false;
    }

    qreal subX = mousePos.x() - m_pMouseLastPoint.x();
    qreal subY = mousePos.y() - m_pMouseLastPoint.y();
    this->moveItem(QPointF(subX, subY));
    m_pMouseLastPoint = mousePos;
}

void PixmapItem::releaseEvent()
{
    if (this->isSelected() || g_ToolType != ToolType::Cursor)
        return;

    if (!m_pHasMouseMove) {
        emit itemClicked(this);  //发送选中信号
    }else {
        m_IsPushToHistory = true;
        emit this->itemChanged(this);
    }
}

QPainterPath PixmapItem::getTransformPath(const QPainterPath &srcPath, QTransform *transform, const QPointF &center) const
{
    /* 设置旋转中心 */
    QPointF tCenter = transform->map(center);
    transform->setMatrix(transform->m11(), transform->m12(), transform->m13(),
                        transform->m21(), transform->m22(), transform->m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform->m33());
    return transform->map(srcPath);
}

