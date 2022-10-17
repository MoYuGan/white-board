#include "boardview.h"
#include <QTouchEvent>
#include <QOpenGLWidget>
#include <QtDebug>
#include <QDateTime>
#include <QPrinter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QFileInfo>
#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QMenu>
#include <QDateTime>
#include "Veil/myveil.h"
#include <QAbstractSocket>
#include "CustomGraphicsItem/cubeitem.h"
extern "C" {
#include "mupdf/pdf.h"
}

#define MOUSE_PRESSED_ID 101

DB_BoardView::DB_BoardView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet("border: none;");
    this->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    this->viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);
    this->viewport()->installEventFilter(this);

    m_scene = new BoardScene();
    m_scene->setSceneRect(0, 0, g_ScreenWidth, g_ScreenHeight);
}

void DB_BoardView::show()
{
    QGraphicsView::show();
}

void DB_BoardView::changeDrawingScenePixmap(QBrush brush)
{
    m_scene->clearSelection();
    m_scene->setBackgroundBrush(brush);
}

void DB_BoardView::showCoverRect()
{
//    ItemCoverRect *coverRect = new ItemCoverRect(this);
//    coverRect->setGeometry(this->rect());
//    coverRect->show();
}

void DB_BoardView::addChiGuiItem(int type)
{
    m_sceneold->addChiGuiItem(type);
    if(g_ToolType == ToolType::Pen)moveItemToDrawScene();
    update();
}

bool DB_BoardView::eventFilter(QObject *watched, QEvent *event)
{
    return QGraphicsView::eventFilter(watched, event);
}

void DB_BoardView::resetDrawingScene(BoardScene *scene)
{
    m_sceneold = static_cast<BoardScene *>(scene);
    m_scene->setBackgroundBrush(m_sceneold->getSceneToPixmap());

    if(g_ToolType == ToolType::Pen)this->setScene(m_scene);
    else if(g_ToolType != ToolType::Pen)this->setScene(m_sceneold);

    connect(m_sceneold,&BoardScene::moveArcItemToScene,this,[=](QPainterPath path,int num,QObject* object){
        if(num ==1)
        {
            if(!m_mapTempItem.contains(object))
            {
                m_mapTempItem.insert(object,m_scene->addGraphicItem(path));
                GraphicsItem* arcitem =static_cast<GraphicsItem*>(m_mapTempItem.value(object));
                arcitem->setPen(QPen(g_PenColor,g_PenSize));
            }
        }
        else if(num ==2)
        {
            GraphicsItem* arcitem =static_cast<GraphicsItem*>(m_mapTempItem.value(object));
            arcitem->setPath(path);
        }
        else if(num ==3)
        {
            GraphicsItem* arcitem =static_cast<GraphicsItem*>(m_mapTempItem.value(object));
            arcitem->setPath(path);
            m_mapTempItem.remove(object);
        }
        m_scene->update();
    });

    connect(m_sceneold,&BoardScene::moveLineItemToScene,this,[=](QLineF line,int num,QObject* object){
        if(num ==1)
        {
            if(!m_mapTempItem.contains(object))
            {
                 m_mapTempItem.insert(object,m_scene->addLineItem(line));
                 LineItem* lineitem =static_cast<LineItem*>(m_mapTempItem.value(object));
                 lineitem->setPen(QPen(g_PenColor,g_PenSize));
            }
        }
        else if(num ==2)
        {
            LineItem* lineitem =static_cast<LineItem*>(m_mapTempItem.value(object));
            lineitem->setLine(line);
        }
        else if(num ==3)
        {
            LineItem* lineitem =static_cast<LineItem*>(m_mapTempItem.value(object));
            lineitem->setLine(line);
            m_mapTempItem.take(object);
        }
        m_scene->update();
    });
}

void DB_BoardView::changeViewScene(int a)
{
    if(a == 1)
    {
        m_scene->clearSelection();
        moveItemToScene();
        this->setScene(m_sceneold);
    }
    else if(a ==2)
    {
        m_sceneold->clearSelection();
        m_scene->setBackgroundBrush(getViewToPixmap());
        this->setScene(m_scene);
    }

}

void DB_BoardView::resetCurrentScene(BoardScene* scene)
{
    if(g_ToolType != ToolType::Pen)
    {
        moveItemToScene();
        m_sceneold =scene;
        this->setScene(m_sceneold);
    }
    else
    {
        moveItemToScene();
        m_sceneold =scene;
        moveItemToDrawScene();
        m_scene->setBackgroundBrush(m_sceneold->getSceneToPixmap());
        this->setScene(m_scene);
    }
}

BoardScene *DB_BoardView::getItemScene()
{
    return m_sceneold;
}

BoardScene *DB_BoardView::getItemDrawingScene()
{
    return m_scene;
}

bool DB_BoardView::viewportEvent(QEvent *event)
{
#if  1
    switch(event->type())
    {
        case QEvent::TouchBegin:
        {
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            if (QEvent::TouchBegin == event->type())
            {
                BoardScene *scene = static_cast<BoardScene *>(this->scene());
                if (scene->isMouseInChiGuiItem(touchEvent->touchPoints().at(0).scenePos()))
                {
                   m_CloseTouch = true;
                   return QGraphicsView::viewportEvent(event);
                }
            }
            //if((m_MiniLeftTouchPressed ==false)&&(m_MiniRightTouchPressed ==false))
            {
                m_AddItems.clear();
                m_DrawItemMap.clear();
            }
            if (ToolType::Pen == g_ToolType) {
                if(m_MiniLeftTouchPressed ==true)return true;
                if(m_MiniRightTouchPressed ==true)return true;
                this->drawTouchEvent(touchEvent);
                return true;
            }
            else if (ToolType::Erase == g_ToolType) {
                this->eraseTouchEvent(touchEvent);
                return true;
            }
            else if (ToolType::Cursor == g_ToolType) {
                if(isItemsIn(touchEvent->touchPoints().at(0).screenPos()))
                {
                   pressIsItem =true;
                }
                else
                {
                    this->cursorTouchEvent(touchEvent);
                    pressIsItem =false;
                }
                if(pressIsItem)
                    return QGraphicsView::viewportEvent(event);
                return true;
            }
        }break;
        case QEvent::TouchUpdate:
        {
            if(m_CloseTouch)return QGraphicsView::viewportEvent(event);
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            if (ToolType::Pen == g_ToolType) {
                this->drawTouchEvent(touchEvent);
                return true;
            }
            else if (ToolType::Erase ==g_ToolType) {
                this->eraseTouchEvent(touchEvent);
                return true;
            }
            else if (ToolType::Cursor == g_ToolType) {
                this->cursorTouchEvent(touchEvent);
                if(pressIsItem)
                    return QGraphicsView::viewportEvent(event);
                return true;
            }
        }break;
    case QEvent::TouchEnd: {
        if (QEvent::TouchEnd == event->type() && m_CloseTouch) {
            m_CloseTouch = false;
            return QGraphicsView::viewportEvent(event);
        }
        if (ToolType::Pen == g_ToolType) {
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            this->drawTouchEvent(touchEvent);
            m_scene->setBackgroundBrush(getViewToPixmap());
        }
        else if (ToolType::Erase == g_ToolType) {
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            this->eraseTouchEvent(touchEvent);
            m_MousePressed = false;
            /*手指长按出现橡皮擦不消失的情况*/
            foreach (QGraphicsItem* it, m_sceneold->items()) {
                if(it->type() ==7)m_sceneold->removeItem(it);
            }
        }
        else if (ToolType::Cursor == g_ToolType) {
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            this->cursorTouchEvent(touchEvent);
            if(pressIsItem)
                return QGraphicsView::viewportEvent(event);
            return true;
        }
       if (QEvent::TouchEnd == event->type()) {
            //加入撤销集合
           foreach (QGraphicsItem *var, m_AddItems) {
               if(var->type() ==65635)
               {
                    PathItem *item = (PathItem*)var;
                    if(item->path().elementCount() <2)
                    {
                        m_sceneold->removeItem(item);
                    }
               }
           }
           m_sceneold->pushToUndoData(m_AddItems, BoardScene::NewItemAdd);
           m_TouchPressed = false;
        }
    }break;
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease: {
        if (QEvent::MouseButtonRelease == event->type() && m_CloseTouch)
        {
            m_CloseTouch = false;
            m_TouchPressed = false;
        }
        if (m_TouchPressed)
            return QGraphicsView::viewportEvent(event);

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (ToolType::Pen == g_ToolType)
        {
            if(m_MiniLeftTouchPressed)return true;
            if(m_MiniRightTouchPressed)return true;
            this->drawMouseEvent(mouseEvent);
        }
        else if (ToolType::Erase == g_ToolType)
        {
            this->eraseMouseEvent(mouseEvent);
        }
        else if (ToolType::Cursor == g_ToolType)
        {
            this->cursorMouseEvent(mouseEvent);
        }
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
#endif

}

void DB_BoardView::drawTouchEvent(QTouchEvent *event)
{
     if(QEvent::TouchBegin == event->type()){
         emit mousePressed();
         m_TouchPressed = true;
         m_MousePressed = false;
         m_MiniLeftTouchPressed =false;
         m_MiniRightTouchPressed =false;
         m_DrawItemMap.clear();
         DrawItemMap.clear();
         m_AddItems.clear();
         m_PixmapPoint.clear();
         pointid =event->touchPoints().at(0).id();
     }

     foreach (const QTouchEvent::TouchPoint tp, event->touchPoints()) {
         if (tp.state() == Qt::TouchPointPressed) {
             if(g_DrawGraphic&& (pointid==tp.id()))
             {
                 QGraphicsItem *item = this->drawGraphicPressed();
                 m_AddItems.clear();
                 m_AddItems.push_back(item);    //加入添加集合
                 m_LastPoint = tp.screenPos();
                 m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
             }
             else if(!g_DrawGraphic)
             {
                 if(m_TouchPressed ==false)return;
                 if(g_PenType == PenType::TuAnBi)
                 {
                    m_PixmapPoint.insert(tp.id(),tp.scenePos());
                    m_scene->addTuAnPixmap(QPixmap(g_TuAnBi.str),QRect(tp.scenePos().x() -g_TuAnBi.PenSize/2,tp.scenePos().y() -g_TuAnBi.PenSize/2,g_TuAnBi.PenSize,g_TuAnBi.PenSize));
                    m_sceneold->addTuAnPixmap(QPixmap(g_TuAnBi.str),QRect(tp.scenePos().x() -g_TuAnBi.PenSize/2,tp.scenePos().y() -g_TuAnBi.PenSize/2,g_TuAnBi.PenSize,g_TuAnBi.PenSize));
                 }
                 else
                 {
                     QPainterPath path = QPainterPath();
                     QPainterPath mpath = QPainterPath();
                     path.moveTo(tp.scenePos());
                     mpath.moveTo(tp.scenePos());
                     QGraphicsItem *item;
                     QGraphicsItem *mitem;
                     if(g_PenType == PenType::GangBi)
                     {
                       g_PenColor =g_GangBi.penColor;
                       g_PenSize =g_GangBi.PenSize;
                       item = m_sceneold->addPathItem(path,0,0);
                       mitem = m_scene->addPathItem(mpath,0,0);
                     }
                     else if(g_PenType == PenType::RuanBi)
                     {
                         g_PenColor =g_RuanBi.penColor;
                         g_PenSize =g_RuanBi.PenSize;
                         item = m_sceneold->addPathItem(path,0,1);
                         mitem = m_scene->addPathItem(mpath,0,1);
                     }
                     else if(g_PenType == PenType::YingGuangBi)
                     {
                         g_PenColor =g_YingGuangBi.penColor;
                         g_PenSize =g_YingGuangBi.PenSize;
                         item = m_sceneold->addPathItem(path,0,0);
                         mitem = m_scene->addPathItem(mpath,0,0);
                     }
                     m_AddItems.push_back(item);    //加入添加集合
                     m_DrawItemMap.insert(tp.id(), item);
                     DrawItemMap.insert(tp.id(), mitem);
                 }
             }
             break;
         }else if (tp.state() == Qt::TouchPointMoved) {
             if(m_TouchPressed ==false)return;
             if(g_DrawGraphic&& (pointid==tp.id()))
             {
                this->drawGraphicMove(m_LastPoint, tp.screenPos());
             }
             else if(!g_DrawGraphic)
             {
                 if(g_PenType == PenType::TuAnBi)
                 {
                     QPointF dot =m_PixmapPoint.value(tp.id());
                     if(QLineF(dot,tp.scenePos()).length() >g_TuAnBi.PenSize)
                     {
                        QPointF mdot =getPixmapDot(dot,tp.scenePos(),g_TuAnBi.PenSize);
                        if(mdot.isNull())return;
                        m_PixmapPoint.insert(tp.id(),mdot);
                        m_scene->addTuAnPixmap(QPixmap(g_TuAnBi.str),QRect(mdot.x() -g_TuAnBi.PenSize/2,mdot.y() -g_TuAnBi.PenSize/2,g_TuAnBi.PenSize,g_TuAnBi.PenSize));
                        m_sceneold->addTuAnPixmap(QPixmap(g_TuAnBi.str),QRect(mdot.x() -g_TuAnBi.PenSize/2,mdot.y() -g_TuAnBi.PenSize/2,g_TuAnBi.PenSize,g_TuAnBi.PenSize));
                     }
                 }
                 else
                 {
                   PathItem *item = (PathItem *)m_DrawItemMap.value(tp.id(), nullptr);
                   QPainterPath path = item->path();
                   path.lineTo(tp.scenePos());
                   item->setPath(path);
                   if(g_PenType == PenType::YingGuangBi)
                   {
                      PathItem *mitem = (PathItem *)DrawItemMap.value(tp.id(), nullptr);
                      mitem->setPath(path);
                   }
                   else if(g_PenType != PenType::YingGuangBi)
                   {
                       PathItem *mitem = (PathItem *)DrawItemMap.value(tp.id(), nullptr);
                       if(!pathCutOff(&path,6).isEmpty())mitem->setPath(pathCutOff(&path,6));
                       if(path.elementCount() >6)
                       {
                           QPainterPath mpath;
                           mpath.moveTo(path.elementAt(path.elementCount() -7));
                           mpath.lineTo(path.elementAt(path.elementCount() -6));
                           mpath.lineTo(path.elementAt(path.elementCount() -5));
                           m_scene->addPathItem(mpath,1,0);
                       }
                   }
                 }
             }
             break;
         }else if (tp.state() == Qt::TouchPointReleased) {
             if(m_TouchPressed ==false)return;
             if(g_DrawGraphic&& (pointid==tp.id()))
             {
                 this->setMinGraphic(m_LastPoint,tp.screenPos());
                 this->drawGraphicRelease();
                 m_DrawItemMap.remove(MOUSE_PRESSED_ID);
                 m_sceneold->pushToUndoData(m_AddItems, BoardScene::NewItemAdd);
             }
             else if(!g_DrawGraphic)
             {
                 if(g_PenType == PenType::TuAnBi)
                 {
                     m_PixmapPoint.remove(tp.id());
                 }
                 else
                 {
                     PathItem *item = (PathItem*)m_DrawItemMap.value(tp.id(), nullptr);
                     if (nullptr != item)
                     {
                        QPainterPath path = item->path();
                        if(path.elementCount() <6)m_sceneold->removeItem(item);
                     }
                     m_DrawItemMap.remove(tp.id());
                 }
             }
             break;
         }
     }
}

void DB_BoardView::drawMouseEvent(QMouseEvent *event)
{
    switch(event->type())
    {
        case QEvent::MouseButtonPress: {
            emit mousePressed();
            BoardScene *scene = static_cast<BoardScene *>(this->scene());
            if (scene->isMouseInChiGuiItem(event->screenPos()))return;

            m_MousePressed = true;
            m_DrawItemMap.clear();
            DrawItemMap.clear();
            m_AddItems.clear();
            m_LastPoint = event->screenPos();

            QGraphicsItem *item;
            QGraphicsItem *mitem;
            if (g_DrawGraphic) {   //绘制图形
                item = this->drawGraphicPressed();
                if(ToolType::Pen !=g_ToolType)
                m_AddItems.push_back(item);    //加入添加集合
            }else {    //绘制路径  
                if(g_PenType == PenType::TuAnBi)
                {
                    m_scene->addTuAnPixmap(QPixmap(g_TuAnBi.str),QRect(m_LastPoint.x() -g_TuAnBi.PenSize/2,m_LastPoint.y() -g_TuAnBi.PenSize/2,g_TuAnBi.PenSize,g_TuAnBi.PenSize));
                    m_sceneold->addTuAnPixmap(QPixmap(g_TuAnBi.str),QRect(m_LastPoint.x() -g_TuAnBi.PenSize/2,m_LastPoint.y() -g_TuAnBi.PenSize/2,g_TuAnBi.PenSize,g_TuAnBi.PenSize));
                }
                else
                {
                    QPainterPath path = QPainterPath();
                    path.moveTo(m_LastPoint);
                    //item =m_sceneold->addPathItem(path,0,1);

                    QPainterPath mpath = QPainterPath();
                    mpath.moveTo(m_LastPoint);
                    //mitem =m_scene->addPathItem(mpath,0,1);

                    if(g_PenType == PenType::GangBi)
                    {
                      g_PenColor =g_GangBi.penColor;
                      g_PenSize =g_GangBi.PenSize;
                      item = m_sceneold->addPathItem(path,0,0);
                      mitem = m_scene->addPathItem(mpath,0,0);
                    }
                    else if(g_PenType == PenType::RuanBi)
                    {
                        g_PenColor =g_RuanBi.penColor;
                        g_PenSize =g_RuanBi.PenSize;
                        item = m_sceneold->addPathItem(path,0,1);
                        mitem = m_scene->addPathItem(mpath,0,1);
                    }
                    else if(g_PenType == PenType::YingGuangBi)
                    {
                        g_PenColor =g_YingGuangBi.penColor;
                        g_PenSize =g_YingGuangBi.PenSize;
                        item = m_sceneold->addPathItem(path,0,0);
                        mitem = m_scene->addPathItem(mpath,0,0);
                    }
                    m_AddItems.push_back(item);    //加入添加集合
                }
            }
            m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
            DrawItemMap.insert(MOUSE_PRESSED_ID, mitem);
        }break;
        case QEvent::MouseMove: {
            if (!m_MousePressed)
                return;
            if (g_DrawGraphic) {   //绘制图形
                this->drawGraphicMove(m_LastPoint, event->screenPos());
            }else {    //绘制路径
                if(g_PenType == PenType::TuAnBi)
                {
                    if(QLineF(m_LastPoint,event->screenPos()).length() >g_TuAnBi.PenSize)
                    {
                       QPointF dot =getPixmapDot(m_LastPoint,event->screenPos(),g_TuAnBi.PenSize);
                       if(dot.isNull())return;
                       m_LastPoint =dot;
                       m_scene->addTuAnPixmap(QPixmap(g_TuAnBi.str),QRect(dot.x() -g_TuAnBi.PenSize/2,dot.y() -g_TuAnBi.PenSize/2,g_TuAnBi.PenSize,g_TuAnBi.PenSize));
                       m_sceneold->addTuAnPixmap(QPixmap(g_TuAnBi.str),QRect(dot.x() -g_TuAnBi.PenSize/2,dot.y() -g_TuAnBi.PenSize/2,g_TuAnBi.PenSize,g_TuAnBi.PenSize));
                    }
                }
                else
                {
                    PathItem *item = static_cast<PathItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
                    QPainterPath path = item->path();
                    path.lineTo(event->screenPos());
                    item->setPath(path);

                    if(g_PenType == PenType::YingGuangBi)
                    {
                       PathItem *mitem = static_cast<PathItem *>(DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
                       mitem->setPath(path);
                    }
                    else if(g_PenType != PenType::YingGuangBi)
                    {
                        PathItem *mitem = static_cast<PathItem *>(DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
                        //djf
                        //if(!pathCutOff(&path,6).isEmpty())mitem->setPath(pathCutOff(&path,6));
                        QPainterPath miniHeadPath = pathCutOff(&path,6);
                        if( !miniHeadPath.isEmpty())
                            mitem->setPath(miniHeadPath);
                        if(path.elementCount() >6)
                        {
                            QPainterPath mpath;
                            mpath.moveTo(path.elementAt(path.elementCount() -7));
                            mpath.lineTo(path.elementAt(path.elementCount() -6));
                            mpath.lineTo(path.elementAt(path.elementCount() -5));
                            m_scene->addPathItem(mpath,1,0);
                            qDebug() << m_scene->items().size();
                        }
                    }
                    m_LastPoint = event->screenPos();
                }
            }
        }break;
        case QEvent::MouseButtonRelease: {
            if (!m_MousePressed)
                return;
            m_MousePressed = false;
            if (g_DrawGraphic) {   //绘制图形
                this->setMinGraphic(m_LastPoint,event->screenPos());
                this->drawGraphicRelease();
                m_DrawItemMap.remove(MOUSE_PRESSED_ID);
                m_sceneold->pushToUndoData(m_AddItems, BoardScene::NewItemAdd);
            }
            else
            {    //绘制路径
                if(g_PenType != PenType::TuAnBi)
                {
                    PathItem *item = static_cast<PathItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
                    m_DrawItemMap.remove(MOUSE_PRESSED_ID);
                    if (nullptr != item)
                    {
                       QPainterPath path = item->path();
                       if(path.elementCount() <6)m_sceneold->removeItem(item);
                       m_sceneold->pushToUndoData(m_AddItems, BoardScene::NewItemAdd);
                    }
                }
                m_scene->setBackgroundBrush(getViewToPixmap());
            }
        }break;
        default:
            break;
    }
}

void DB_BoardView::getDrawPath(QPainterPath *srcPath, const QPointF &lastPos, const QPointF &curPos)
{
    /* 将本次移动两点之间的路径添加进总路径 */
    QPointF midPoint = (lastPos  + curPos)/2;
    if (0 == srcPath->elementCount()) {
        srcPath->moveTo(lastPos);
    }
    srcPath->quadTo(lastPos, midPoint);
    //getBezier2(srcPath, lastPos, midPoint, curPos);
}

void DB_BoardView::getGraphicPath(const QPointF &p1, const QPointF &p2, QPainterPath *path,QPainterPath *path2)
{
    switch(g_GraphicType)
    {
    case GraphicType::TuoYuan: {
        *path = GraphicsPath::getEllipse(p1, p2);
    }break;
    case GraphicType::JuXing:{
        *path = GraphicsPath::getRectangle(p1, p2);
    }break;
    case GraphicType::YuanJiaoJuXing:{
        *path = GraphicsPath::getRoundedRectangle(p1, p2);
    }break;
    case GraphicType::PingXingSiBianXing: {
        *path = GraphicsPath::getParallelogram(p1, p2);
    }break;
    case GraphicType::LingXing: {
        *path = GraphicsPath::getDiamond(p1, p2);
    }break;
    case GraphicType::TiXing: {
        *path = GraphicsPath::getTrapezoid(p1, p2);
    }break;
    case GraphicType::ShanXing: {
        *path = GraphicsPath::getFan(p1, p2);
    }break;
    case GraphicType::SanJiaoXing: {
        *path = GraphicsPath::getTriangle(p1, p2);
    }break;
    case GraphicType::ZhiJiaoSanJiaoXing: {
        *path = GraphicsPath::getRightTriangle(p1, p2);
    }break;
    case GraphicType::WuBianXing: {
        *path = GraphicsPath::getPentagon(p1, p2);
    }break;
    case GraphicType::LiuBianXing: {
        *path = GraphicsPath::getHexagon(p1, p2);
    }break;
    case GraphicType::WuJiaoXing: {
        *path = GraphicsPath::getStar(p1, p2);
    }break;
    case GraphicType::TianZiGe: {
        *path = GraphicsPath::getTian(p1, p2);
    }break;
    case GraphicType::LiFangTi: {
        //*path = GraphicsPath::getCube(p1, p2);
        GraphicsPath::getCube(p1, p2,path,path2);
    }break;
    case GraphicType::YuanZhuTi: {
        //*path = GraphicsPath::getCylinder(p1, p2);
        GraphicsPath::getCylinder(p1, p2,path,path2);
    }break;
    case GraphicType::YuanZhuiTi: {
        GraphicsPath::getCone(p1, p2,path,path2);
    }break;
    case GraphicType::SanLengZhui: {
        GraphicsPath::getThreeCones(p1, p2,path,path2);
    }break;
    case GraphicType::SiLengZhui: {
        GraphicsPath::getFourCones(p1, p2,path,path2);
    }break;
    default:
        break;
    }
}

void DB_BoardView::eraseMouseEvent(QMouseEvent *event)
{
    if (QEvent::MouseButtonPress == event->type()) {
        emit mousePressed();
        BoardScene *scene = static_cast<BoardScene *>(this->scene());
        if (scene->isMouseInChiGuiItem(event->screenPos())) {
            return;
        }
        /*清除选择框，避免后面图形删除后选择框还在，导致异常出现*/
        scene->clearSelection();
        m_MousePressed = true;
        m_LastPoint = event->screenPos();
        if (g_DrawGraphic) {   //绘制图形
            QGraphicsItem *item = this->drawGraphicPressed();
            m_AddItems.clear();
            m_AddItems.push_back(item);    //加入添加集合
            m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
        }else {
            m_EraseItem = new QGraphicsPixmapItem;
            m_EraseItem->setZValue(z_ValueMax +3);
            QPixmap pixmap = QPixmap(":/images/other/cachuzhuangtai@2x.png").scaled(g_EraserSize);
            pixmap.setDevicePixelRatio(1);
            m_EraseItem->setPixmap(pixmap);
            m_EraseItem->setOffset(QPointF(m_LastPoint.x() - pixmap.width()/2.0,
                                             m_LastPoint.y() - pixmap.height()/2.0));
            scene->addItem(m_EraseItem);
            scene->eraseItems(this->getErasePath(m_LastPoint, m_LastPoint), m_EraseItem,1);
        }
    }else if (QEvent::MouseMove == event->type()) {
        if (!m_MousePressed)
            return;
        if (g_DrawGraphic) {   //绘制图形
            this->drawGraphicMove(m_LastPoint, event->screenPos());
        }else {
            if (nullptr != m_EraseItem) {
                m_EraseItem->setOffset(QPointF(event->screenPos().x() - m_EraseItem->boundingRect().width()/2.0,
                                                 event->screenPos().y() - m_EraseItem->boundingRect().height()/2.0));
                BoardScene *scene = static_cast<BoardScene *>(this->scene());
                //qDebug()<<"------erase-------1"<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
                QPainterPath path = this->getErasePath(m_LastPoint, event->screenPos());
                //qDebug()<<"------erase-------2"<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
                scene->eraseItems(path, m_EraseItem,2);
                //qDebug()<<"------erase-------3"<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz")<<Qt::endl;
                m_LastPoint = event->screenPos();
            }
        }
    }else if (QEvent::MouseButtonRelease == event->type()) {
        if (!m_MousePressed)
            return;
        m_MousePressed = false;
        if (g_DrawGraphic) {   //绘制图形
            this->setMinGraphic(m_LastPoint,event->screenPos());
            this->drawGraphicRelease();
            m_DrawItemMap.remove(MOUSE_PRESSED_ID);
            m_sceneold->pushToUndoData(m_AddItems, BoardScene::NewItemAdd);
        }else {
            if (m_EraseItem == nullptr)return;
                m_sceneold->removeItem(m_EraseItem);
                delete m_EraseItem;
                qDebug()<< "TouchEnd11 "<<Qt::endl;
                m_EraseItem = nullptr;
                m_sceneold->eraseFinished();
        }
    }
}

void DB_BoardView::eraseTouchEvent(QTouchEvent *event)
{
    if(m_MiniMousePressed)return;
    if (QEvent::TouchBegin == event->type() && !g_DrawGraphic) {
       pointid = event->touchPoints().at(0).id();
       m_EraseItem = new QGraphicsPixmapItem;
       m_EraseItem->setZValue(z_ValueMax +3);
       //QPixmap pixmap = QPixmap(":/images/cachuzhuangtai@2x.png").scaled(g_EraserSize);
       QPixmap pixmap = QPixmap(":/images/other/cachuzhuangtai@2x.png").scaled(g_EraserSize);

       pixmap.setDevicePixelRatio(1);
       m_EraseItem->setPixmap(pixmap);
       m_EraseItem->setOffset(QPointF(event->touchPoints().at(0).screenPos().x() - pixmap.width()/2.0,
                                      event->touchPoints().at(0).screenPos().y() - pixmap.height()/2.0));
       m_sceneold->addItem(m_EraseItem);
       m_MousePressed = true;
    }
    else if(QEvent::TouchBegin == event->type() &&g_DrawGraphic)
    {
       pointid = event->touchPoints().at(0).id();
       m_MousePressed = true;
    }

    foreach (const QTouchEvent::TouchPoint tp, event->touchPoints()) {
    if (tp.state() == Qt::TouchPointPressed &&pointid ==tp.id()) {
        emit mousePressed();
        BoardScene *scene = static_cast<BoardScene *>(this->scene());
        if (scene->isMouseInChiGuiItem(tp.screenPos())) {
            return;
        }
        /*清除选择框，避免后面图形删除后选择框还在，导致异常出现*/
        scene->clearSelection();
        m_LastPoint = tp.screenPos();
        if (g_DrawGraphic) {   //绘制图形
            QGraphicsItem *item = this->drawGraphicPressed();
            m_AddItems.clear();
            m_AddItems.push_back(item);    //加入添加集合
            m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
        }else {
            scene->eraseItems(this->getErasePath(m_LastPoint, m_LastPoint), m_EraseItem,1);
        }
    }else if (tp.state() == Qt::TouchPointMoved &&pointid ==tp.id()) {
        if (!m_MousePressed)
            return;
        if (g_DrawGraphic) {   //绘制图形
            this->drawGraphicMove(m_LastPoint, tp.screenPos());
        }else {
            if (nullptr != m_EraseItem) {
                m_EraseItem->setOffset(QPointF(tp.screenPos().x() - m_EraseItem->boundingRect().width()/2.0,
                                                 tp.screenPos().y() - m_EraseItem->boundingRect().height()/2.0));
                BoardScene *scene = static_cast<BoardScene *>(this->scene());
                QPainterPath path = this->getErasePath(m_LastPoint, tp.screenPos());
                scene->eraseItems(path, m_EraseItem,2);
                m_LastPoint =tp.screenPos();
            }
        }     
    }else if (tp.state() == Qt::TouchPointReleased &&pointid ==tp.id()) {
        if (!m_MousePressed)return;
        BoardScene *scene = static_cast<BoardScene *>(this->scene());
        if (g_DrawGraphic) {   //绘制图形
            this->setMinGraphic(m_LastPoint,tp.screenPos());
            this->drawGraphicRelease();
            m_DrawItemMap.remove(MOUSE_PRESSED_ID);
            m_MousePressed = false;
            scene->pushToUndoData(m_AddItems, BoardScene::NewItemAdd);
            return;
        }else {
            scene->eraseFinished();
            /*由于红外屏手指离得近的时候会合并点，但是无法预测少的是哪个点*/
            /*所以橡皮擦的点被合并后需要将橡皮擦移动到另外一个点上,避免橡皮擦突然消失*/
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
}

/* 获取橡皮擦移动时的多边形路径 */
QPainterPath DB_BoardView::getErasePath(const QPointF &lastPos, const QPointF &currentPos)
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
    }else if((subX <0) && subY >0) {
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

void DB_BoardView::cursorMouseEvent(QMouseEvent *event)
{
    if (QEvent::MouseButtonPress == event->type()) {
        emit mousePressed();
        if (isItemsIn(event->screenPos()))
            return;
        m_MousePressed = true;
        m_LastPoint = event->screenPos();

        BoardScene *scene = static_cast<BoardScene *>(this->scene());
        if (g_DrawGraphic) {   //绘制图形
            QGraphicsItem *item = this->drawGraphicPressed();
            m_AddItems.clear();
            m_AddItems.push_back(item);    //加入添加集合
            m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
        }else {
            if (scene->selectedItems().size() > 0)
                scene->clearSelection();
            /* 添加选择框Item */
            QRectF rect = QRectF(0, 0, Public_Function::getScaleSize(3), Public_Function::getScaleSize(3));
            rect.moveCenter(m_LastPoint);
            m_SelectRectItem = new QGraphicsRectItem;
            m_SelectRectItem->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2), Qt::DashLine,
                                          Qt::RoundCap, Qt::RoundJoin));
            m_SelectRectItem->setRect(rect);
            scene->addItem(m_SelectRectItem);
        }
    }else if (QEvent::MouseMove == event->type()) {
        if (!m_MousePressed)
            return;
        if (g_DrawGraphic) {   //绘制图形
            this->drawGraphicMove(m_LastPoint, event->screenPos());
        }else {
            QRectF rect(m_LastPoint.x(), m_LastPoint.y(),
                        qAbs(event->screenPos().x() - m_LastPoint.x()),
                        qAbs(event->screenPos().y() - m_LastPoint.y()));
            rect.moveCenter(QPointF((m_LastPoint.x() + event->screenPos().x())/2.0, (m_LastPoint.y() + event->screenPos().y())/2.0));
            m_SelectRectItem->setRect(rect);
        }
    }else if (QEvent::MouseButtonRelease == event->type()) {
        if (!m_MousePressed)
            return;
        m_MousePressed = false;
        BoardScene *scene = static_cast<BoardScene *>(this->scene());
        if (g_DrawGraphic) {   //绘制图形
            this->setMinGraphic(m_LastPoint,event->screenPos());
            this->drawGraphicRelease();
            m_DrawItemMap.remove(MOUSE_PRESSED_ID);
            scene->pushToUndoData(m_AddItems, BoardScene::NewItemAdd);
        }else {
            QRectF rect = m_SelectRectItem->rect();
            scene->removeItem(m_SelectRectItem);
            delete m_SelectRectItem;
            m_SelectRectItem = nullptr;
            scene->setSelectionAreaRect(rect);  //设置选中区域
        }
    }
}

void DB_BoardView::cursorTouchEvent(QTouchEvent *event)
{
    if (QEvent::TouchBegin == event->type()) {
       pointid = event->touchPoints().at(0).id();
    }

    foreach (const QTouchEvent::TouchPoint tp, event->touchPoints()) {
        if (tp.state() == Qt::TouchPointPressed &&(pointid ==tp.id())) {
            emit mousePressed();
            if (isItemsIn(tp.screenPos()))
                return;
            m_MousePressed = true;
            m_LastPoint = tp.screenPos();
            BoardScene *scene = static_cast<BoardScene *>(this->scene());
            if (g_DrawGraphic) {   //绘制图形
                QGraphicsItem *item = this->drawGraphicPressed();
                m_AddItems.clear();
                m_AddItems.push_back(item);    //加入添加集合
                m_DrawItemMap.insert(MOUSE_PRESSED_ID, item);
            }else {
                if (scene->selectedItems().size() > 0)
                    scene->clearSelection();
                /* 添加选择框Item */
                QRectF rect = QRectF(0, 0, Public_Function::getScaleSize(3), Public_Function::getScaleSize(3));
                rect.moveCenter(m_LastPoint);
                m_SelectRectItem = new QGraphicsRectItem;
                m_SelectRectItem->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2), Qt::DashLine,
                                              Qt::RoundCap, Qt::RoundJoin));
                m_SelectRectItem->setRect(rect);
                scene->addItem(m_SelectRectItem);
            }
        }else if (tp.state() == Qt::TouchPointMoved &&(pointid ==tp.id())) {
            if (!m_MousePressed)
                return;
            if (g_DrawGraphic) {   //绘制图形
                this->drawGraphicMove(m_LastPoint, tp.screenPos());
            }else {
                QRectF rect(m_LastPoint.x(), m_LastPoint.y(),
                            qAbs(tp.screenPos().x() - m_LastPoint.x()),
                            qAbs(tp.screenPos().y() - m_LastPoint.y()));
                rect.moveCenter(QPointF((m_LastPoint.x() + tp.screenPos().x())/2.0, (m_LastPoint.y() + tp.screenPos().y())/2.0));
                m_SelectRectItem->setRect(rect);
            }
        }else if (tp.state() == Qt::TouchPointReleased &&(pointid ==tp.id())) {
            if (!m_MousePressed)
                return;
            m_MousePressed = false;
            BoardScene *scene = static_cast<BoardScene *>(this->scene());
            if (g_DrawGraphic) {   //绘制图形
                this->setMinGraphic(m_LastPoint,tp.screenPos());
                this->drawGraphicRelease();
                m_DrawItemMap.remove(MOUSE_PRESSED_ID);
                scene->pushToUndoData(m_AddItems, BoardScene::NewItemAdd);
            }else {
                QRectF rect = m_SelectRectItem->rect();
                scene->removeItem(m_SelectRectItem);
                delete m_SelectRectItem;
                m_SelectRectItem = nullptr;
                scene->setSelectionAreaRect(rect);  //设置选中区域
            }
        }
    }
}

bool DB_BoardView::isItemsIn(const QPointF &pt)
{
    QPainterPath path;
    path.addEllipse(pt, 1, 1);
    BoardScene *scene = static_cast<BoardScene*>(this->scene());
    if (scene->items(path).size() > 0)
        return true;
    else
        return false;
}

QGraphicsItem *DB_BoardView::drawGraphicPressed()
{
    QGraphicsItem *item = nullptr;
    BoardScene *scene = static_cast<BoardScene*>(this->scene());

    switch(g_GraphicType)
    {
        case GraphicType::ZhiXian:
        case GraphicType::JianTou:
        case GraphicType::ShuangJianTou:
        case GraphicType::XianDuan:
        case GraphicType::XvXian: {item = scene->addLineItem(QLine(), g_GraphicType);}break;
        default: { item = scene->addGraphicItem();}break;
    }
    return item;
}

void DB_BoardView::drawGraphicMove(const QPointF &p1, const QPointF &p2)
{
    switch(g_GraphicType)
    {
    case GraphicType::ZhiXian:
    case GraphicType::JianTou:
    case GraphicType::ShuangJianTou:
    case GraphicType::XianDuan:
    case GraphicType::XvXian: {
        LineItem *item = static_cast<LineItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
        if (nullptr == item) return;
        item->setLine(QLineF(p1, p2));
    }break;
    default: {
        GraphicsItem *item = static_cast<GraphicsItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
        if (nullptr == item) return;
        if (qAbs(p1.x() - p2.x()) > 5 || qAbs(p1.y() - p2.y()) > 5)
        {
            QPainterPath path = QPainterPath();
            QPainterPath path2 = QPainterPath();
            this->getGraphicPath(p1, p2, &path,&path2);
            item->setPath(path,path2);
        }
    }break;
    }
}

void DB_BoardView::drawGraphicRelease()
{
    g_DrawGraphic = false;  //关闭绘制图形
    switch(g_GraphicType)
    {
    case GraphicType::ZhiXian:
    case GraphicType::JianTou:
    case GraphicType::ShuangJianTou:
    case GraphicType::XianDuan:
    case GraphicType::XvXian: {
        LineItem *item = static_cast<LineItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
        if(ToolType::Pen ==g_ToolType)
        {
           LineItem *m_item = m_sceneold->addLineItem(QLine(), g_GraphicType);
           m_item->setLine(item->line());
           m_scene->removeItem(item);
           m_item->setSelected(true);
           m_AddItems.push_back(m_item);    //加入添加集合
           emit m_item->itemClicked(m_item);
        }
        else
        {
            item->setSelected(true);
            emit item->itemClicked(item);
        }
    }break;
    default: {
        GraphicsItem *item = static_cast<GraphicsItem *>(m_DrawItemMap.value(MOUSE_PRESSED_ID, nullptr));
        if(ToolType::Pen ==g_ToolType)
        {
           GraphicsItem *m_item = m_sceneold->addGraphicItem();
           if(g_GraphicType ==GraphicType::LiFangTi ||g_GraphicType ==GraphicType::YuanZhuTi ||g_GraphicType ==GraphicType::YuanZhuiTi
                   ||g_GraphicType ==GraphicType::SanLengZhui ||g_GraphicType ==GraphicType::SiLengZhui)
           {
               QPainterPath path1;
               QPainterPath path2;
               item->getDrawPath(&path1,&path2);
               m_item->setPath(path1,path2);
           }
           else
           {
               m_item->setPath(item->path());
           }
           m_scene->removeItem(item);
           m_item->setSelected(true);
           m_AddItems.push_back(m_item);    //加入添加集合
           emit m_item->itemClicked(m_item);
        }
        else
        {
            item->setSelected(true);
            emit item->itemClicked(item);
        }
    }break;
    }
    emit this->drawGraphicFinished();
}

void DB_BoardView::moveItemToScene()
{
    QList<QGraphicsItem*> m_items= m_scene->items();
    for(int i=m_items.count() -1;i >=0;i--)
    {
       if((QGraphicsItem::UserType + (int)(ItemType::ChiGuiItem)) == m_items.at(i)->type())
       {
          if(!m_sceneold->items().contains(m_items.at(i)))
          m_sceneold->addItem(m_items.at(i));
       }
       else if((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == m_items.at(i)->type())
       {
          PixmapItem *item =static_cast<PixmapItem*>(m_items.at(i));
          if(item->IsGifPixmap())
          {
              if(!m_sceneold->items().contains(m_items.at(i)))
              {
                 m_sceneold->addItem(m_items.at(i));
              }
          }
       }
       else
       {
           m_scene->removeItem(m_items.at(i));
       }
    }
}

void DB_BoardView::moveChiGuiToScene()
{
    QList<QGraphicsItem*> m_items;
    if(g_ToolType == ToolType::Pen)m_items= m_scene->items();
    if(g_ToolType != ToolType::Pen)m_items= m_sceneold->items();
    for(int i=m_items.count() -1;i >=0;i--)
    {
       if((QGraphicsItem::UserType + (int)(ItemType::ChiGuiItem)) == m_items.at(i)->type())
       {
          if(g_ToolType == ToolType::Pen)
          {
              if(!m_sceneold->items().contains(m_items.at(i)))m_sceneold->addItem(m_items.at(i));
          }
          else
          {
              if(!m_scene->items().contains(m_items.at(i)))m_scene->addItem(m_items.at(i));
          }
       }
       else if((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == m_items.at(i)->type())
       {
           PixmapItem *item =static_cast<PixmapItem*>(m_items.at(i));
           if(item->IsGifPixmap())
           {
              if(g_ToolType == ToolType::Pen)
              {
                  if(!m_sceneold->items().contains(m_items.at(i)))m_sceneold->addItem(m_items.at(i));
              }
              else
              {
                  if(!m_scene->items().contains(m_items.at(i)))m_scene->addItem(m_items.at(i));
              }
           }
       }
    }
}

void DB_BoardView::moveItemToDrawScene()
{
    QList<QGraphicsItem*> m_items= m_sceneold->items();
    for(int i=m_items.count() -1;i >=0;i--)
    {
       if((QGraphicsItem::UserType + (int)(ItemType::ChiGuiItem)) == m_items.at(i)->type())
       {
          if(!m_scene->items().contains(m_items.at(i)))
          m_scene->addItem(m_items.at(i));
       }
       else if((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == m_items.at(i)->type())
       {
           PixmapItem *item =static_cast<PixmapItem*>(m_items.at(i));
           if(item->IsGifPixmap())
           {
              if(!m_scene->items().contains(m_items.at(i)))
              m_scene->addItem(m_items.at(i));
           }
       }
    }
}

void DB_BoardView::clearDrawingSceneItem()
{
    QList<QGraphicsItem*> m_items= m_scene->items();
    for(int i=m_items.count() -1;i >=0;i--)
    {
       if((QGraphicsItem::UserType + (int)(ItemType::ChiGuiItem)) == m_items.at(i)->type()){}
       else if((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == m_items.at(i)->type()){
           PixmapItem *item =static_cast<PixmapItem*>(m_items.at(i));
           if(item->isDelete())
           {
             m_scene->removeItem(item);
           }
       }
       else m_scene->removeItem(m_items.at(i));
    }
}

QPainterPath DB_BoardView::pathCutOff(QPainterPath *path, int num)
{
    QPainterPath m_path;
    if(path->elementCount() <num)return m_path;
    for(int i=num; i>0;i--)
    {
       if(i ==num)m_path.moveTo(path->elementAt(path->elementCount() -i));
       else m_path.lineTo(path->elementAt(path->elementCount() -i));
    }
    return m_path;
}

QPixmap DB_BoardView::getViewToPixmap()
{
    moveChiGuiToScene();
    QPixmap pixmap(this->width(), this->height());
    QPainter painter;
    painter.begin(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    this->render(&painter, this->rect(), this->rect(), Qt::IgnoreAspectRatio);
    painter.end();
    if(g_ToolType == ToolType::Pen)moveItemToDrawScene();
    clearDrawingSceneItem();
    return pixmap;
}

QPixmap DB_BoardView::getViewTabPixmap()
{
    QPixmap pixmap(this->width(), this->height());
    QPainter painter;
    painter.begin(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    this->render(&painter, this->rect(), this->rect(), Qt::IgnoreAspectRatio);
    painter.end();
    return pixmap;
}

void DB_BoardView::updateLanguage()
{
    if( m_sceneold)
        m_sceneold->updateLanguage();
}

void DB_BoardView::miniRightDrawTouchEvent(_TPPoint point,QColor color)
{
    if(m_TouchPressed ==true)return;

    if(point.state ==2)
    {
        color =rightpencolor;
    }
    else rightpencolor = color;

    if ((point.state == 1)&&(point.id ==83))
    {
        m_MiniRightTouchPressed =true;
        emit mousePressed();
        m_MousePressed = false;
        m_TouchPressed =false;
    }

    if (point.state == 1) {
        QPainterPath path = QPainterPath();
        QPainterPath mpath = QPainterPath();
        path.moveTo(QPoint(point.X,point.Y));
        mpath.moveTo(QPoint(point.X,point.Y));
        QGraphicsItem *item;
        QGraphicsItem *mitem;
        // =g_RuanBi.penColor;
        g_PenSize =g_RuanBi.PenSize;
        item = m_sceneold->addMiniPathItem(path,0,1,color);
        mitem = m_scene->addMiniPathItem(mpath,0,1,color);
        m_RightAddItems.push_back(item);    //加入添加集合
        m_RightDrawItemMap.insert(point.id, item);
        RightDrawItemMap.insert(point.id, mitem);
    }
    else if (point.state == 2)
    {
        if(m_MiniRightTouchPressed ==false)return;
        PathItem *item = (PathItem *)m_RightDrawItemMap.value(point.id, nullptr);
        item->setPen(QPen(QBrush(color), g_PenSize));
        QPainterPath path = item->path();
        path.lineTo(QPoint(point.X,point.Y));
        item->setPath(path);

        PathItem *mitem = (PathItem *)RightDrawItemMap.value(point.id, nullptr);
        if(!pathCutOff(&path,6).isEmpty())mitem->setPath(pathCutOff(&path,6));
        if(path.elementCount() >6)
        {
            QPainterPath mpath;
            mpath.moveTo(path.elementAt(path.elementCount() -7));
            mpath.lineTo(path.elementAt(path.elementCount() -6));
            mpath.lineTo(path.elementAt(path.elementCount() -5));
            m_scene->addMiniPathItem(mpath,1,0,color);
        }
    }
    else if (point.state == 3)
    {
        PathItem *item = (PathItem*)m_RightDrawItemMap.value(point.id, nullptr);
        if (nullptr != item)
        {
            QPainterPath path = item->path();
            if(path.elementCount() <6)m_sceneold->removeItem(item);
        }
        m_RightDrawItemMap.remove(point.id);
        RightDrawItemMap.remove(point.id);

        if(point.Num ==1)
        {
            m_sceneold->pushToUndoData(m_RightAddItems, BoardScene::NewItemAdd);
            m_MiniRightTouchPressed =false;
            m_RightDrawItemMap.clear();
            RightDrawItemMap.clear();
            m_RightAddItems.clear();
        }
    }
}

void DB_BoardView::miniLeftDrawTouchEvent(_TPPoint point,QColor color)
{
    if(m_TouchPressed ==true)return;
    if(point.state ==2)
    {
        color =leftpencolor;
    }
    else leftpencolor = color;

    if ((point.state == 1)&&(point.id ==37))
    {
        m_MiniLeftTouchPressed =true;
        emit mousePressed();
        m_MousePressed = false;
        m_TouchPressed =false;
    }

    if (point.state == 1) {
        QPainterPath path = QPainterPath();
        QPainterPath mpath = QPainterPath();
        path.moveTo(QPoint(point.X,point.Y));
        mpath.moveTo(QPoint(point.X,point.Y));
        QGraphicsItem *item;
        QGraphicsItem *mitem;
        //g_PenColor =g_RuanBi.penColor;
        g_PenSize =g_RuanBi.PenSize;
        item = m_sceneold->addMiniPathItem(path,0,1,color);
        mitem = m_scene->addMiniPathItem(mpath,0,1,color);
        m_LeftAddItems.push_back(item);    //加入添加集合
        m_LeftDrawItemMap.insert(point.id, item);
        LeftDrawItemMap.insert(point.id, mitem);
    }
    else if (point.state == 2)
    {
        if(m_MiniLeftTouchPressed ==false)return;
        PathItem *item = (PathItem *)m_LeftDrawItemMap.value(point.id, nullptr);
        QPainterPath path = item->path();
        path.lineTo(QPoint(point.X,point.Y));
        item->setPath(path);

        PathItem *mitem = (PathItem *)LeftDrawItemMap.value(point.id, nullptr);
        if(!pathCutOff(&path,6).isEmpty())mitem->setPath(pathCutOff(&path,6));
        if(path.elementCount() >6)
        {
            QPainterPath mpath;
            mpath.moveTo(path.elementAt(path.elementCount() -7));
            mpath.lineTo(path.elementAt(path.elementCount() -6));
            mpath.lineTo(path.elementAt(path.elementCount() -5));
            m_scene->addMiniPathItem(mpath,1,0,color);
        }
    }
    else if (point.state == 3)
    {
        PathItem *item = (PathItem*)m_LeftDrawItemMap.value(point.id, nullptr);
        if (nullptr != item)
        {
            QPainterPath path = item->path();
            if(path.elementCount() <6)m_sceneold->removeItem(item);
        }
        m_LeftDrawItemMap.remove(point.id);
        LeftDrawItemMap.remove(point.id);
        if(point.Num ==1)
        {
            m_sceneold->pushToUndoData(m_LeftAddItems, BoardScene::NewItemAdd);
            m_MiniLeftTouchPressed =false;
            m_LeftDrawItemMap.clear();
            LeftDrawItemMap.clear();
            m_LeftAddItems.clear();
        }
    }
}

void DB_BoardView::miniEraseMouseEvent(_TPPoint point)
{
    if (point.state == 1)
    {
        if (nullptr != m_EraseItem) return;

        m_sceneold->clearSelection();
        m_MiniMousePressed = true;
        m_LastPoint = QPoint(point.X,point.Y);
        m_EraseItem = new QGraphicsPixmapItem;
        m_EraseItem->setZValue(z_ValueMax +3);
        QPixmap pixmap = QPixmap(":/images/other/cachuzhuangtai@2x.png").scaled(g_EraserSize);
        pixmap.setDevicePixelRatio(1);
        m_EraseItem->setPixmap(pixmap);
        m_EraseItem->setOffset(QPointF(m_LastPoint.x() - pixmap.width()/2.0,
                                       m_LastPoint.y() - pixmap.height()/2.0));
        m_sceneold->addItem(m_EraseItem);
        m_sceneold->eraseItems(this->getErasePath(m_LastPoint, m_LastPoint), m_EraseItem,1);
    }
    else if (point.state == 2)
    {
        if (m_MiniMousePressed != true)return;

        if (nullptr != m_EraseItem) {
            m_EraseItem->setOffset(QPointF(point.X - m_EraseItem->boundingRect().width()/2.0,
                                           point.Y - m_EraseItem->boundingRect().height()/2.0));
            QPainterPath path = this->getErasePath(m_LastPoint, QPoint(point.X,point.Y));
            m_sceneold->eraseItems(path, m_EraseItem,2);
            m_LastPoint = QPoint(point.X,point.Y);
        }
    }
    else if (point.state == 3)
    {
        m_MiniMousePressed = false;
        if (m_EraseItem == nullptr)return;
        m_sceneold->removeItem(m_EraseItem);
        delete m_EraseItem;
        m_EraseItem = nullptr;
        m_sceneold->eraseFinished();
    }
}

void DB_BoardView::setMinGraphic(QPointF P1, QPointF P2)
{
    if(QLineF(P1,P2).length() <Public_Function::getScaleSize(50))
    {
       this->drawGraphicMove(P1, QPointF(P1.x() +Public_Function::getScaleSize(50),P1.y() +Public_Function::getScaleSize(50)));
    }
}

QPointF DB_BoardView::getPixmapDot(QPointF dot1, QPointF dot2,int mlength)
{
    QPointF point;
    if((dot1.x() == dot2.x())&&(dot1.y() == dot2.y()))return point;
    qreal ratio = (qreal)mlength/QLineF(dot1,dot2).length();
    point.setX(dot1.x() +(dot2.x() -dot1.x())*ratio);
    point.setY(dot1.y() -(dot1.y() -dot2.y())*ratio);
    return point;
}





