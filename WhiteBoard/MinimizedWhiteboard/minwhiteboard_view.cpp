#include "minwhiteboard_view.h"
#include <QtDebug>

#define MOUSE_PRESSED_ID 101

MinWhiteBoard_View::MinWhiteBoard_View(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet("border: none;");
    this->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    MinWhiteBoard_Scene *scene = new MinWhiteBoard_Scene(this);
    this->setScene(scene);
}

void MinWhiteBoard_View::setTool(ViewTool tool)
{
    if(ViewTool::Erase ==tool)
    {
        m_pixmap =this->getViewPixmap();
    }
    m_Tool = tool;
}

void MinWhiteBoard_View::clearScene()
{
    //MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene*>(this->scene());
    //scene->clear();
    QPainterPath path;
    path.addRect(this->rect());
    drawBackgroundPixmap(path);
}

bool MinWhiteBoard_View::viewportEvent(QEvent *event)
{
    switch(event->type())
    {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        {
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            if (ViewTool::Pen == m_Tool) {
                this->drawTouchEvent(touchEvent);
            }
            else if (ViewTool::Erase == m_Tool) {
                this->eraseTouchEvent(touchEvent);
            }
            return true;
        }
        case QEvent::TouchEnd: {
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            if (ViewTool::Pen == m_Tool) {
                this->drawTouchEvent(touchEvent);
            }
            else if (ViewTool::Erase == m_Tool) {
                this->eraseTouchEvent(touchEvent);
                m_TouchPressed = false;
                /*手指长按出现橡皮擦不消失的情况*/
                foreach (QGraphicsItem* it, scene()->items()) {
                    if(it->type() ==7)scene()->removeItem(it);
                }
            }
            return true;
        }break;
        case QEvent::MouseButtonPress:
        case QEvent::MouseMove:
        case QEvent::MouseButtonRelease: {
            if (m_TouchPressed)
                return true;

            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (ViewTool::Pen == m_Tool)
                this->drawMouseEvent(mouseEvent);
            else if (ViewTool::Erase == m_Tool)
                this->eraseMouseEvent(mouseEvent);
        }
        default:
            break;
    }

    return QGraphicsView::viewportEvent(event);
}

void MinWhiteBoard_View::resizeEvent(QResizeEvent *event)
{
    this->setSceneRect(this->rect());
    return QGraphicsView::resizeEvent(event);
}

QPixmap MinWhiteBoard_View::getViewPixmap()
{
    QPixmap pixmap(this->width(), this->height());
    pixmap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    this->render(&painter, this->rect(), this->rect(), Qt::IgnoreAspectRatio);
    painter.end();
    return pixmap;
}

void MinWhiteBoard_View::drawBackgroundPixmap(QPainterPath path)
{
    QImage image =m_pixmap.toImage();
    QPainter pain(&image);
    pain.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    pain.setRenderHint(QPainter::Antialiasing,true);
    pain.fillPath(path,QColor(255, 255, 255, 0));
    m_pixmap =QPixmap().fromImage(image);
    this->scene()->setBackgroundBrush(m_pixmap);
}

void MinWhiteBoard_View::drawTouchEvent(QTouchEvent *event)
{
#if  0
     if (QEvent::TouchBegin == event->type()) {
         m_TouchPressed = true;
         m_MousePressed = false;
         m_DrawItemMap.clear();
     }

     foreach (const QTouchEvent::TouchPoint tp, event->touchPoints()) {
         if (tp.state() == Qt::TouchPointPressed) {
             QPainterPath path = QPainterPath();
             this->getDrawPath(&path, tp.lastScenePos(), tp.scenePos());
             MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene*>(this->scene());
             MinWhiteBoar_PathItem *item = scene->addPathItem(path);
             m_DrawItemMap.insert(tp.id(), item);
             break;
         }else if (tp.state() == Qt::TouchPointMoved) {
             MinWhiteBoar_PathItem *item = (MinWhiteBoar_PathItem*)m_DrawItemMap.value(tp.id(), nullptr);
             QPainterPath path = item->path();
             this->getDrawPath(&path, tp.lastScenePos(), tp.scenePos());
             item->setPath(Public_Function::cubToLine(path));
             int pathCount = path.elementCount();
             if (pathCount > 150) { //路径元素点超过150，新建一个子item
                 MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene*>(this->scene());
                 QPainterPath subItemPath = QPainterPath();
                 this->getDrawPath(&subItemPath, tp.lastScenePos(), tp.scenePos());
                 MinWhiteBoar_PathItem *subItem = scene->addPathItem(subItemPath);
                 subItem->setParentItem(item);
                 m_DrawItemMap.insert(tp.id(), subItem);
             }
             break;
         }else if (tp.state() == Qt::TouchPointReleased) {
             MinWhiteBoar_PathItem *item = (MinWhiteBoar_PathItem*)m_DrawItemMap.value(tp.id(), nullptr);
             if (nullptr != item) {
                 QPainterPath path = item->path();
                 this->getDrawPath(&path, tp.lastScenePos(), tp.scenePos());
                 item->setPath(path);
             }
             m_DrawItemMap.remove(tp.id());
             break;
         }
     }

     if (QEvent::TouchEnd == event->type()) {
         m_DrawItemMap.clear();
         m_TouchPressed = false;
     }
#endif

#if  1
     if (QEvent::TouchBegin == event->type()) {
         m_TouchPressed = true;
         m_MousePressed = false;
         m_DrawItemMap.clear();
     }

     foreach (const QTouchEvent::TouchPoint tp, event->touchPoints()) {
         if (tp.state() == Qt::TouchPointPressed) {
             QPainterPath path = QPainterPath();
             this->getDrawPath(&path, tp.lastScenePos(), tp.scenePos());
             MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene*>(this->scene());
             MinWhiteBoar_PathItem *item = scene->addPathItem(path);
             m_DrawItemMap.insert(tp.id(), item);
             break;
         }else if (tp.state() == Qt::TouchPointMoved) {
             MinWhiteBoar_PathItem *item = (MinWhiteBoar_PathItem*)m_DrawItemMap.value(tp.id(), nullptr);
             QPainterPath path = item->path();
             this->getDrawPath(&path, tp.lastScenePos(), tp.scenePos());
             item->setPath(path);
             if(path.elementCount() >100)
             {
                 this->scene()->setBackgroundBrush(this->getViewPixmap());
                 path.clear();
                 path.moveTo((tp.lastScenePos() +tp.scenePos())/2);
                 item->setPath(path);
                 m_DrawItemMap.insert(tp.id(), item);
             }
             break;
         }else if (tp.state() == Qt::TouchPointReleased) {
             MinWhiteBoar_PathItem *item = (MinWhiteBoar_PathItem*)m_DrawItemMap.value(tp.id(), nullptr);
             if (nullptr != item) {
                 QPainterPath path = item->path();
                 this->getDrawPath(&path, tp.lastScenePos(), tp.scenePos());
                 item->setPath(path);
             }
             this->scene()->setBackgroundBrush(this->getViewPixmap());
             this->scene()->removeItem(item);
             m_DrawItemMap.remove(tp.id());
             break;
         }
     }

     if (QEvent::TouchEnd == event->type()) {
         m_DrawItemMap.clear();
         m_TouchPressed = false;
     }
#endif

}

void MinWhiteBoard_View::drawMouseEvent(QMouseEvent *event)
{
#if  0
    switch(event->type())
    {
    case QEvent::MouseButtonPress: {
        m_MousePressed = true;
        m_DrawItemMap.clear();
        m_LastPoint = event->screenPos();

        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene*>(this->scene());
        MinWhiteBoar_PathItem *item;
        QPainterPath path = QPainterPath();
        this->getDrawPath(&path, m_LastPoint, m_LastPoint);
        item = scene->addPathItem(path);
        m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
    }break;
    case QEvent::MouseMove: {
        if (!m_MousePressed)
            return;

        MinWhiteBoar_PathItem *item = static_cast<MinWhiteBoar_PathItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
        QPainterPath path = item->path();
        this->getDrawPath(&path, m_LastPoint, event->screenPos());
        item->setPath(path);
        int pathCount = path.elementCount();
        if (pathCount > 150) { //路径元素点超过150，新建一个子item
            MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene*>(this->scene());
            QPainterPath subItemPath = QPainterPath();
            this->getDrawPath(&subItemPath, m_LastPoint, event->screenPos());
            MinWhiteBoar_PathItem *subItem = scene->addPathItem(subItemPath);
            subItem->setParentItem(item);
            m_DrawItemMap.insert(MOUSE_PRESSED_ID, subItem);
        }
        m_LastPoint = event->screenPos();
    }break;
    case QEvent::MouseButtonRelease: {
        if (!m_MousePressed)
            return;
        MinWhiteBoar_PathItem *item = static_cast<MinWhiteBoar_PathItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
        if (nullptr != item) {
            QPainterPath path = item->path();
            this->getDrawPath(&path, m_LastPoint, event->screenPos());
            item->setPath(path);
        }

        m_DrawItemMap.remove(MOUSE_PRESSED_ID);
    }break;
    default:
        break;
    }
#endif
    switch(event->type())
    {
    case QEvent::MouseButtonPress: {
        m_MousePressed = true;
        m_DrawItemMap.clear();
        m_LastPoint = event->screenPos();

        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene*>(this->scene());
        MinWhiteBoar_PathItem *item;
        QPainterPath path = QPainterPath();
        this->getDrawPath(&path, m_LastPoint, m_LastPoint);
        item = scene->addPathItem(path);
        m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
    }break;
    case QEvent::MouseMove: {
        if (!m_MousePressed)
            return;

        MinWhiteBoar_PathItem *item = static_cast<MinWhiteBoar_PathItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
        QPainterPath path = item->path();
        this->getDrawPath(&path, m_LastPoint, event->screenPos());
        item->setPath(path);
        if(path.elementCount() >100)
        {
            this->scene()->setBackgroundBrush(this->getViewPixmap());
            path.clear();
            path.moveTo((m_LastPoint +event->screenPos())/2);
            item->setPath(path);
            m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
        }

        m_LastPoint = event->screenPos();
    }break;
    case QEvent::MouseButtonRelease: {
        if (!m_MousePressed)
            return;
        MinWhiteBoar_PathItem *item = static_cast<MinWhiteBoar_PathItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
        if (nullptr != item) {
            QPainterPath path = item->path();
            this->getDrawPath(&path, m_LastPoint, event->screenPos());
            item->setPath(path);
        }
        this->scene()->setBackgroundBrush(this->getViewPixmap());
        this->scene()->removeItem(item);
        m_DrawItemMap.remove(MOUSE_PRESSED_ID);
    }break;
    default:
        break;
    }



}

void MinWhiteBoard_View::getDrawPath(QPainterPath *srcPath, const QPointF &lastPos, const QPointF &curPos)
{
    /* 将本次移动两点之间的路径添加进总路径 */
    QPointF midPoint = (lastPos  + curPos)/2;
    if (0 == srcPath->elementCount())
        srcPath->moveTo(lastPos);
    srcPath->quadTo(lastPos, midPoint);
}

void MinWhiteBoard_View::eraseMouseEvent(QMouseEvent *event)
{
#if  0
    if (QEvent::MouseButtonPress == event->type()) {
        m_MousePressed = true;
        m_LastPoint = event->screenPos();

        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());

        m_EraseItem = new QGraphicsPixmapItem;
        QPixmap pixmap = QPixmap(":/images/cachuzhuangtai@2x.png").scaled(e_MinBoardEraseSize);
        pixmap.setDevicePixelRatio(1);
        m_EraseItem->setPixmap(pixmap);
        m_EraseItem->setOffset(QPointF(m_LastPoint.x() - pixmap.width()/2.0,
                                         m_LastPoint.y() - pixmap.height()/2.0));
        scene->addItem(m_EraseItem);
        scene->eraseItems(this->getErasePath(m_LastPoint, m_LastPoint), m_EraseItem);
    }else if (QEvent::MouseMove == event->type()) {
        if (!m_MousePressed)
            return;

        if (nullptr != m_EraseItem) {
            m_EraseItem->setOffset(QPointF(event->screenPos().x() - m_EraseItem->boundingRect().width()/2.0,
                                             event->screenPos().y() - m_EraseItem->boundingRect().height()/2.0));
            MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
            scene->eraseItems(this->getErasePath(m_LastPoint, event->screenPos()), m_EraseItem);
            m_LastPoint = event->screenPos();
        }
    }else if (QEvent::MouseButtonRelease == event->type()) {
        if (!m_MousePressed || nullptr == m_EraseItem)
            return;

        m_MousePressed = false;
        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
        scene->removeItem(m_EraseItem);
        delete m_EraseItem;
        m_EraseItem = nullptr;
        scene->eraseFinished();
    }

#endif

    if (QEvent::MouseButtonPress == event->type()) {
        m_MousePressed = true;
        m_LastPoint = event->screenPos();

        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());

        m_EraseItem = new QGraphicsPixmapItem;
        QPixmap pixmap = QPixmap(":/images/cachuzhuangtai@2x.png").scaled(e_MinBoardEraseSize);
        pixmap.setDevicePixelRatio(1);
        m_EraseItem->setPixmap(pixmap);
        m_EraseItem->setOffset(QPointF(m_LastPoint.x() - pixmap.width()/2.0,
                                         m_LastPoint.y() - pixmap.height()/2.0));
        scene->addItem(m_EraseItem);
        this->drawBackgroundPixmap(this->getErasePath(m_LastPoint, m_LastPoint));
    }else if (QEvent::MouseMove == event->type()) {
        if (!m_MousePressed)
            return;

        if (nullptr != m_EraseItem) {
            m_EraseItem->setOffset(QPointF(event->screenPos().x() - m_EraseItem->boundingRect().width()/2.0,
                                             event->screenPos().y() - m_EraseItem->boundingRect().height()/2.0));
            this->drawBackgroundPixmap(this->getErasePath(m_LastPoint, m_LastPoint));
            m_LastPoint = event->screenPos();
        }
    }else if (QEvent::MouseButtonRelease == event->type()) {
        if (!m_MousePressed || nullptr == m_EraseItem)
            return;

        m_MousePressed = false;
        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
        scene->removeItem(m_EraseItem);
        delete m_EraseItem;
        m_EraseItem = nullptr;
    }
}

void MinWhiteBoard_View::eraseTouchEvent(QTouchEvent *event)
{

#if   0
    if (QEvent::TouchBegin == event->type()) {
       pointid = event->touchPoints().at(0).id();
       m_EraseItem = new QGraphicsPixmapItem;
       QPixmap pixmap = QPixmap(":/images/cachuzhuangtai@2x.png").scaled(e_MinBoardEraseSize);
       pixmap.setDevicePixelRatio(1);
       m_EraseItem->setPixmap(pixmap);
       m_EraseItem->setOffset(QPointF(event->touchPoints().at(0).screenPos().x() - pixmap.width()/2.0,
                                      event->touchPoints().at(0).screenPos().y() - pixmap.height()/2.0));
       MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
       scene->addItem(m_EraseItem);
       m_TouchPressed = true;
       return;
    }

    if (QEvent::TouchEnd == event->type()) {
        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
        scene->removeItem(m_EraseItem);
        delete m_EraseItem;
        m_EraseItem = nullptr;
        m_TouchPressed = false;
        return;
    }

    foreach (const QTouchEvent::TouchPoint tp, event->touchPoints()) {
    if (tp.state() == Qt::TouchPointPressed && tp.id() == pointid) {
        m_LastPoint = tp.screenPos();
        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
        scene->eraseItems(this->getErasePath(m_LastPoint, m_LastPoint), m_EraseItem);
    }else if (tp.state() == Qt::TouchPointMoved && tp.id() == pointid) {
        if (!m_TouchPressed)
            return;
        if (nullptr != m_EraseItem) {
            m_EraseItem->setOffset(QPointF(tp.screenPos().x() - m_EraseItem->boundingRect().width()/2.0,
                                           tp.screenPos().y() - m_EraseItem->boundingRect().height()/2.0));
            MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
            scene->eraseItems(this->getErasePath(m_LastPoint, tp.screenPos()), m_EraseItem);
            m_LastPoint = tp.screenPos();
        }
    }else if (tp.state() == Qt::TouchPointReleased && tp.id() == pointid) {
        if (!m_TouchPressed || nullptr == m_EraseItem)
            return;
        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
        scene->eraseFinished();
        for(int i=0; i<event->touchPoints().count();i++)
        {
            if(event->touchPoints().at(i).id() !=pointid)
            {
                pointid =event->touchPoints().at(i).id();
                break;
            }
        }
    }
    }
#endif
    if (QEvent::TouchBegin == event->type()) {
       pointid = event->touchPoints().at(0).id();
       m_EraseItem = new QGraphicsPixmapItem;
       QPixmap pixmap = QPixmap(":/images/cachuzhuangtai@2x.png").scaled(e_MinBoardEraseSize);
       pixmap.setDevicePixelRatio(1);
       m_EraseItem->setPixmap(pixmap);
       m_EraseItem->setOffset(QPointF(event->touchPoints().at(0).screenPos().x() - pixmap.width()/2.0,
                                      event->touchPoints().at(0).screenPos().y() - pixmap.height()/2.0));
       MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
       scene->addItem(m_EraseItem);
       m_TouchPressed = true;
       //return;
    }

    if (QEvent::TouchEnd == event->type()) {
        MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
        scene->removeItem(m_EraseItem);
        delete m_EraseItem;
        m_EraseItem = nullptr;
        m_TouchPressed = false;
        return;
    }

    foreach (const QTouchEvent::TouchPoint tp, event->touchPoints()) {
        if (tp.state() == Qt::TouchPointPressed && tp.id() == pointid) {
            m_LastPoint = tp.screenPos();
            //MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
            //scene->eraseItems(this->getErasePath(m_LastPoint, m_LastPoint), m_EraseItem);
            drawBackgroundPixmap(this->getErasePath(m_LastPoint,m_LastPoint));
        }
        else if (tp.state() == Qt::TouchPointMoved && tp.id() == pointid)
        {
            if (!m_TouchPressed)
                return;
            if (nullptr != m_EraseItem) {
                m_EraseItem->setOffset(QPointF(tp.screenPos().x() - m_EraseItem->boundingRect().width()/2.0,
                                               tp.screenPos().y() - m_EraseItem->boundingRect().height()/2.0));
                //MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
                //scene->eraseItems(this->getErasePath(m_LastPoint, tp.screenPos()), m_EraseItem);
                drawBackgroundPixmap(this->getErasePath(m_LastPoint, tp.screenPos()));
                m_LastPoint = tp.screenPos();
            }
        }
        else if (tp.state() == Qt::TouchPointReleased && tp.id() == pointid)
        {
            if (!m_TouchPressed || nullptr == m_EraseItem)
                return;
            //MinWhiteBoard_Scene *scene = static_cast<MinWhiteBoard_Scene *>(this->scene());
            //scene->eraseFinished();
            for(int i=0; i<event->touchPoints().count();i++)
            {
                if(event->touchPoints().at(i).id() !=pointid)
                {
                    pointid =event->touchPoints().at(i).id();
                    break;
                }
            }
        }
    }


}

/* 获取橡皮擦移动时的多边形路径 */
QPainterPath MinWhiteBoard_View::getErasePath(const QPointF &lastPos, const QPointF &currentPos)
{

    QPainterPath path;
    int subX = lastPos.x() - currentPos.x();
    int subY = lastPos.y() - currentPos.y();
    QRectF lastEraserRect = m_EraseItem->boundingRect();
    lastEraserRect.moveCenter(lastPos);
    QRectF currentEraserRect = m_EraseItem->boundingRect();
    currentEraserRect.moveCenter(currentPos);
    if (subX < 0 && subY < 0) {
        path.moveTo(lastEraserRect.topLeft());
        path.lineTo(lastEraserRect.topRight());
        path.lineTo(currentEraserRect.topRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.lineTo(currentEraserRect.bottomLeft());
        path.lineTo(lastEraserRect.bottomLeft());
        path.closeSubpath();
    }else if ((subX < 0) && subY > 0) {
        path.moveTo(lastEraserRect.topLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.lineTo(currentEraserRect.topRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.lineTo(lastEraserRect.bottomLeft());
        path.closeSubpath();
    }else if (subX > 0 && subY > 0) {
        path.moveTo(lastEraserRect.topRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.lineTo(lastEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.lineTo(currentEraserRect.topRight());
        path.closeSubpath();
    }else if (subX > 0 && subY < 0) {
        path.moveTo(lastEraserRect.topLeft());
        path.lineTo(lastEraserRect.topRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.lineTo(currentEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.closeSubpath();
    }else if (0 == subX && subY > 0) {
        path.moveTo(lastEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.lineTo(currentEraserRect.topRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.closeSubpath();
    }else if (0 == subX && subY < 0) {
        path.moveTo(currentEraserRect.bottomLeft());
        path.lineTo(lastEraserRect.topLeft());
        path.lineTo(lastEraserRect.topRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.closeSubpath();
    }else if (subX > 0 && subY == 0) {
        path.moveTo(lastEraserRect.topRight());
        path.lineTo(lastEraserRect.bottomRight());
        path.lineTo(currentEraserRect.bottomLeft());
        path.lineTo(currentEraserRect.topLeft());
        path.closeSubpath();
    }else if (subX < 0 && subY == 0) {
        path.moveTo(currentEraserRect.topRight());
        path.lineTo(currentEraserRect.bottomRight());
        path.lineTo(lastEraserRect.bottomLeft());
        path.lineTo(lastEraserRect.topLeft());
        path.closeSubpath();
    }else {
        path.addRect(lastEraserRect);
    }
    return path;
}
