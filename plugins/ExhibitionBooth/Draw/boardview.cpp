#include "boardview.h"

#include <QTouchEvent>
#include <QOpenGLWidget>
#include <QtDebug>
#include <QDateTime>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QFileInfo>
#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QMenu>

#define MOUSE_PRESSED_ID 101
static int m_TouchMoveCount = 0;
static int m_FirstMovePointId = -1;

BoardView::BoardView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet("border: none;");
    this->setRenderHint(QPainter::Antialiasing,true);
    this->createScene();
    this->setMouseTracking(true);
}

void BoardView::setViewTool(BoardView::ViewTool tool)
{
    m_pViewTool = tool;
    if (BoardView::VT_None == tool) {
        this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    }else {
        this->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    }
}

void BoardView::createScene()
{
    /*创建场景*/
    m_pCurrentScene = new BoardScene(this);
    m_pCurrentScene->setSceneRect(this->rect());
    m_pCurrentScene->setBackgroundBrush(Qt::transparent);
    this->setScene(m_pCurrentScene);
}

void BoardView::undo()
{
    m_pCurrentScene->undo();
}

void BoardView::redo()
{
    m_pCurrentScene->redo();
}

void BoardView::clearScene()
{
    m_pCurrentScene->deleteAllItems();
}

void BoardView::resetNewScene()
{
    m_pCurrentScene->deleteLater();
    this->createScene();
}

void BoardView::resizeEvent(QResizeEvent *event)
{
    m_pCurrentScene->setSceneRect(QRectF(0, 0, this->width(), this->height()));
    return QGraphicsView::resizeEvent(event);
}

bool BoardView::viewportEvent(QEvent *event)
{
    switch(event->type())
    {
    /* 鼠标按下 */
    case QEvent::MouseButtonPress: {
        if (ViewTool::VT_None == m_pViewTool)
            return false;

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        //非鼠标左键，不响应鼠标绘图
        if (mouseEvent->button() != Qt::LeftButton)
            break;

        m_pMousePressed = true;
        this->touchBegin();
        this->touchPressed(MOUSE_PRESSED_ID, mapToScene(mouseEvent->pos()));
        m_pLastPoint = mouseEvent->pos();
    }break;
    /* 鼠标移动 */
    case QEvent::MouseMove: {
        if (ViewTool::VT_None == m_pViewTool)
            return false;

        //鼠标没有按下，不进行绘图
        if (!m_pMousePressed)
            break;

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        this->touchMove(MOUSE_PRESSED_ID, mapToScene(m_pLastPoint), mapToScene(mouseEvent->pos()));
        m_pLastPoint = mouseEvent->pos();
    }break;
    case QEvent::MouseButtonRelease: {
        if (ViewTool::VT_None == m_pViewTool)
            return false;

        //鼠标没有按下，退出
        if (!m_pMousePressed)
            break;

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        //非鼠标左键，不响应
        if (mouseEvent->button() != Qt::LeftButton)
            break;

        this->touchRelease(MOUSE_PRESSED_ID, mapToScene(mouseEvent->pos()));
        this->touchEnd();
        m_pMousePressed = false;
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}

void BoardView::touchBegin()
{
    if (ViewTool::VT_Draw == m_pViewTool) {
        m_pCurrentScene->drawBegin();
    }
}

void BoardView::touchPressed(int id, const QPointF &pt)
{
    if (ViewTool::VT_Draw == m_pViewTool) {
        m_pCurrentScene->drawPressed(id, pt);
    }else if (ViewTool::VT_Eraser == m_pViewTool){
        m_pCurrentScene->eraserPressed(pt);
    }
}

void BoardView::touchMove(int id, const QPointF &p1, const QPointF &p2)
{
    if (ViewTool::VT_Draw == m_pViewTool) {
        m_pCurrentScene->drawMove(id, p1, p2);
    }else if (ViewTool::VT_Eraser == m_pViewTool) {
        m_pCurrentScene->eraserMove(p1, p2);
    }
}

void BoardView::touchRelease(int id, const QPointF &p1)
{
    if (ViewTool::VT_Draw == m_pViewTool) {
            m_pCurrentScene->drawReleased(id, p1);
    }else if (ViewTool::VT_Eraser == m_pViewTool) {
        m_pCurrentScene->eraserReleased();
    }
}

void BoardView::touchEnd()
{
    if (ViewTool::VT_Draw == m_pViewTool) {
        m_pCurrentScene->drawEnd();
    }
}




