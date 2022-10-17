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
    m_pCurrentScene = nullptr;

    m_pPressTimer = new QTimer(this);
    connect(m_pPressTimer, &QTimer::timeout, [=](){
        m_pPressTimer->stop();
        //按下超时，触摸类型为一类型
        m_pTouchFunction = TouchFunction::TF_TYPE1;
    });
}

void BoardView::setViewTool(BoardView::ViewTool tool)
{
    //元素是否可被选中
    if (BoardView::VT_Select == tool)
        this->setScenesSelectable(true);
    else if (BoardView::VT_Select == m_pViewTool)
        this->setScenesSelectable(false);


    m_pViewTool = tool;
}

void BoardView::createScene()
{
    /*创建场景*/
    BoardScene *scene = new BoardScene(this);
    scene->setSceneRect(this->rect());
    scene->setBackgroundBrush(QColor(67,67,77));
    /**********change123*************/
//    int index = this->getCurrentSceneIndex();
    int index = m_pScenesList.count() -1;
    //创建的第一个场景
    if (-1 == index) {
        index = 0;
    }else {
        ++index;
    }

    this->m_pScenesList.insert(index, scene);
    this->selectScene(index);
    emit newSceneCreated(index);
}

int BoardView::getScenesListSize()
{
    return m_pScenesList.size();
}

int BoardView::getCurrentSceneIndex()
{
    return m_pScenesList.indexOf((BoardScene *)this->scene());
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

void BoardView::zoomIn()
{
}

void BoardView::zoomOut()
{
}

void BoardView::loadPicture(const QString &fileName)
{
    m_pCurrentScene->loadPicture(fileName);
}

void BoardView::getScenePixmap(int index, QPixmap *pixmap)
{
    if (index < 0 || index >= m_pScenesList.size())
        *pixmap = QPixmap();
    else
        *pixmap = m_pScenesList.at(index)->getSceneToPixmap();
    return;
}

void BoardView::selectAllItem()
{
    m_pCurrentScene->setSelectionAreaRect(m_pCurrentScene->sceneRect());
}

void BoardView::selectScene(int index)
{
    if (index < 0 || index >= m_pScenesList.size())
        return;

    m_pCurrentScene = m_pScenesList.at(index);
    this->setScene(m_pCurrentScene);
}

void BoardView::deleteScene(int index)
{
    if (index < 0 || index >= m_pScenesList.size())
        return;

    BoardScene *scene = m_pScenesList.at(index);
    if (scene == m_pCurrentScene)
        m_pCurrentScene = nullptr;

    m_pScenesList.removeOne(scene);
    scene->deleteLater();
}

void BoardView::resizeEvent(QResizeEvent *event)
{
    foreach (BoardScene *scene, m_pScenesList) {
        scene->setSceneRect(QRectF(0, 0, this->width(), this->height()));
    }

    return QGraphicsView::resizeEvent(event);
}

#if  1
bool BoardView::viewportEvent(QEvent *event)
{
    switch(event->type())
    {
    /* 触摸事件 */
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd: {
        if (m_pViewTool == ViewTool::VT_Select && !m_MultiTouch && QEvent::TouchEnd != event->type()) {
            return false;
        }

        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        if (QEvent::TouchBegin == event->type()) {
            emit mouseClicked();
            m_pTouchPoints.clear();
            m_pPressTimer->start(300);
            m_pTouchFunction = TouchFunction::None;
            m_TouchMoveCount = 0;
            m_pTouchPressed = true;

            QTouchEvent::TouchPoint tp = touchEvent->touchPoints().at(0);
            if (m_pViewTool == ViewTool::VT_Select && m_pCurrentScene->isMouseInSpecialItem(tp.scenePos())) {
                m_MultiTouch = false;
                return false;
            }
        }

        if (TouchFunction::None == m_pTouchFunction)
        {
            if (touchEvent->touchPoints().size() >= 2) {    //接触点大于等于两个
                m_pPressTimer->stop();
                m_pTouchFunction = TouchFunction::TF_TYPE2;     //触摸功能设置为缩放/移动功能
                m_pTouchMovePointList.clear();
                return true;
            }else {
                QTouchEvent::TouchPoint tp = touchEvent->touchPoints().at(0);
                m_pTouchPoints.insert(tp.id(), QList<QPointF>() << tp.scenePos());
                if (tp.state() == Qt::TouchPointMoved)
                    ++m_TouchMoveCount;
                //第一个按下的点移动超过两次，则判定为绘图操作
                if (m_TouchMoveCount > 2) {
                    m_pPressTimer->stop();
                    m_pTouchFunction = TouchFunction::TF_TYPE1; //触摸功能设置为绘图功能
                }
            }
        }else if (TouchFunction::TF_TYPE1 == m_pTouchFunction) {    //绘图功能
            foreach(int id, m_pTouchPoints.keys()) {
                this->touchBegin();
                QList<QPointF> pointList = m_pTouchPoints.value(id);
                int i = 0;
                QPointF lastPoint;
                foreach(QPointF pt, pointList) {
                    if (0 == i) {
                        ++i;
                        this->touchPressed(id, pt);
                        lastPoint = pt;
                        continue;
                    }

                    if (ViewTool::VT_Select == m_pViewTool)
                        this->touchMove(id, lastPoint, pt);
                    else {
                        this->touchMove(id, lastPoint, pt);
                        lastPoint = pt;
                    }
                }
            }
            m_pTouchPoints.clear();
            foreach (const QTouchEvent::TouchPoint tp, touchEvent->touchPoints()) {
                if (Qt::TouchPointPressed == tp.state()) {
                    this->touchPressed(tp.id(), tp.scenePos());
                }else if (Qt::TouchPointMoved == tp.state()) {
                    if (ViewTool::VT_Select == m_pViewTool)
                        this->touchMove(tp.id(), tp.startScenePos(), tp.scenePos());
                    else {
                        this->touchMove(tp.id(), tp.lastScenePos(), tp.scenePos());
                    }
                }else if (Qt::TouchPointReleased == tp.state()) {
                    this->touchRelease(tp.id(), tp.scenePos());
                }
            }
        }else if (TouchFunction::TF_TYPE2 == m_pTouchFunction) {    //缩放移动功能
            QList<QTouchEvent::TouchPoint> touchPointList = touchEvent->touchPoints();
            if (1 == touchPointList.size()) {
                if (touchPointList.at(0).state() == Qt::TouchPointMoved) {
                    this->gestureMove(touchPointList.at(0).lastScenePos(), touchPointList.at(0).scenePos());
                    m_pTouchMovePointList.clear();
                }
            }else {
                //移动状态触摸点
                QTouchEvent::TouchPoint curMovePoint;
                bool hasMovePoint = false;
                //检测是否存在移动状态的点
                foreach(QTouchEvent::TouchPoint tp, touchPointList) {
                    if (tp.state() == Qt::TouchPointMoved) {
                        hasMovePoint = true;
                        curMovePoint = tp;
                        break;
                    }else if (tp.state() == Qt::TouchPointReleased){
                        for(int i = 0; i < m_pTouchMovePointList.size(); i++) {
                            if (m_pTouchMovePointList.at(i).id() == tp.id()) {
                                m_pTouchMovePointList.removeAt(i);
                                break;
                            }
                        }
                        break;
                    }
                }
                //没有移动状态点
                if (!hasMovePoint)
                    return true;

                //是不是一次完整的移动动作
                bool completeAction = false;
                int index = -1;
                /* 如果有多个点在移动，每个点的状态会依次变为Move状态进入Update循环,记录Move状态的点到列表，
                 * 如果当前移动状态的点已经在列表里，说明已经进行过依次完整的移动操作 */
                foreach(QTouchEvent::TouchPoint tp, m_pTouchMovePointList) {
                    ++index;
                    if (tp.id() == curMovePoint.id())
                    {
                        completeAction = true;
                        break;
                    }
                }
                if (!completeAction) {  //不是一次完整的移动操作，退出
                    m_pTouchMovePointList.push_back(curMovePoint);
                    return true;
                }

                qreal addLength = 0;
                qreal subLength = 0;
                int addNum = 0, subNum = 0, moveNum = 0;
                QPointF center;
                if (m_pTouchMovePointList.size() > 1) {
                    for(int i = 0; i < m_pTouchMovePointList.size(); i++) {
                        for(int j = (i+1); j < m_pTouchMovePointList.size(); j++) {
                            QTouchEvent::TouchPoint tp1 = m_pTouchMovePointList.at(i);
                            QTouchEvent::TouchPoint tp2 = m_pTouchMovePointList.at(j);
                            QLineF line1 = QLineF(tp1.lastScenePos(), tp1.scenePos());
                            QLineF line2 = QLineF(tp2.lastScenePos(), tp2.scenePos());
                            qreal angle = qAbs(PublicFunction::getTwoLineAngle(line1, line2));
                            if (angle > 90) {
                                if (QLineF(line1.p1(), line2.p1()).length() < QLineF(line1.p2(), line2.p2()).length()) {    //手势放
                                    int len = line2.length() + line1.length();
                                    if (addLength < len) {
                                        addLength = len;
                                        center = QPointF(QLineF(line1.p2(), line2.p2()).center());
                                    }
                                    addNum++;
                                }else { //手势捏
                                    int len = -(line2.length() + line1.length());
                                    if (subLength > len) {
                                        subLength = len;
                                        center = QPointF(QLineF(line1.p2(), line2.p2()).center());
                                    }
                                    subNum++;
                                }
                            }else {
                                moveNum++;
                            }
                        }
                    }
                    if (moveNum > addNum && moveNum > subNum) {
                        QTouchEvent::TouchPoint movePoint = m_pTouchMovePointList.last();
                        this->gestureMove(movePoint.lastScenePos(), movePoint.scenePos());
                    }else {
                        if (addNum >= subNum)
                            m_pCurrentScene->scaleAllItems(addLength, center);
                        else
                            m_pCurrentScene->scaleAllItems(subLength, center);
                    }
                }else {
                    //其他手指按住，一个手指移动，缩放操作
                    QTouchEvent::TouchPoint movePoint = m_pTouchMovePointList.last();
                    QTouchEvent::TouchPoint pressPoint;
                    foreach(QTouchEvent::TouchPoint tp, touchPointList) {
                        if (tp.state() != Qt::TouchPointMoved) {
                            pressPoint = tp;
                            break;
                        }
                    }
                    QPointF center = QLineF(movePoint.scenePos(), pressPoint.scenePos()).center();
                    if (QLineF(pressPoint.scenePos(), movePoint.lastScenePos()).length() <
                            QLineF(pressPoint.scenePos(), movePoint.scenePos()).length()) {     //手势放
                        m_pCurrentScene->scaleAllItems(QLineF(movePoint.lastScenePos(), movePoint.scenePos()).length(), center);
                    }else { //手势捏
                        m_pCurrentScene->scaleAllItems(-QLineF(movePoint.lastScenePos(), movePoint.scenePos()).length(), center);
                    }
                }

                m_pTouchMovePointList.clear();
                m_pTouchMovePointList.push_back(curMovePoint);
            }
        }

        if (QEvent::TouchEnd == event->type()) {
            if (TouchFunction::None == m_pTouchFunction) {
                m_pPressTimer->stop();
                foreach(int id, m_pTouchPoints.keys()) {
                    this->touchBegin();
                    QList<QPointF> pointList = m_pTouchPoints.value(id);
                    int i = 0;
                    QPointF lastPoint;
                    foreach(QPointF pt, pointList) {
                        if (0 == i) {
                            ++i;
                            this->touchPressed(id, pt);
                            lastPoint = pt;
                            continue;
                        }

                        if (ViewTool::VT_Select == m_pViewTool)
                            this->touchMove(id, lastPoint, pt);
                        else {
                            this->touchMove(id, lastPoint, pt);
                            lastPoint = pt;
                        }
                    }
                    this->touchRelease(id, lastPoint);
                }
            }
            m_MultiTouch = true;
            m_pTouchPressed = false;
            this->touchEnd();
        }
        return true;
    }
    /* 鼠标按下 */
    case QEvent::MouseButtonPress: {
        //正在触摸当中，不响应鼠标事件
        if (m_pTouchPressed || m_pMousePressed)
            break;

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        //非鼠标左键，不响应鼠标绘图
        if (mouseEvent->button() != Qt::LeftButton)
            break;

        // 如果是橡皮擦工具或者画笔工具，鼠标在尺规item上面不进行操作
        if ((ViewTool::VT_Eraser == m_pViewTool || ViewTool::VT_Draw == m_pViewTool) &&
                m_pCurrentScene->isMouseInSpecialItem(mapToScene(mouseEvent->pos()), (QGraphicsItem::UserType + 108)))
            break;
        // 如果是选择工具，鼠标在其他item上面不进行操作
        else if (ViewTool::VT_Select == m_pViewTool &&
                 m_pCurrentScene->isMouseInSpecialItem(mapToScene(mouseEvent->pos())))
            break;

        m_pMousePressed = true;
        this->touchBegin();
        this->touchPressed(MOUSE_PRESSED_ID, mapToScene(mouseEvent->pos()));
        m_pLastPoint = mouseEvent->pos();
    }break;
    /* 鼠标移动 */
    case QEvent::MouseMove: {
        //鼠标没有按下，不进行绘图
        if (!m_pMousePressed)
            break;

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (ViewTool::VT_Select == m_pViewTool)
            this->touchMove(MOUSE_PRESSED_ID, mapToScene(m_pLastPoint), mapToScene(mouseEvent->pos()));
        else {
            this->touchMove(MOUSE_PRESSED_ID, mapToScene(m_pLastPoint), mapToScene(mouseEvent->pos()));
            m_pLastPoint = mouseEvent->pos();
        }
    }break;
    case QEvent::MouseButtonRelease: {
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
#endif


void BoardView::touchBegin()
{
    if (ViewTool::VT_Draw == m_pViewTool && nullptr != m_pCurrentScene) {
        m_pCurrentScene->drawBegin();
    }
}

void BoardView::touchPressed(int id, const QPointF &pt)
{
    if (ViewTool::VT_Draw == m_pViewTool) {
        m_pCurrentScene->drawPressed(id, pt);
    }else {
        //除了绘图工具，不允许使用多指触摸，m_pTouchPressedPoint的大小只记录第一个触摸点
        if (ViewTool::VT_Select == m_pViewTool)
            m_pCurrentScene->dragPressed(pt);
        else if (ViewTool::VT_Eraser == m_pViewTool)
            m_pCurrentScene->eraserPressed(pt);
    }
}

void BoardView::touchMove(int id, const QPointF &p1, const QPointF &p2)
{
    if (ViewTool::VT_Draw == m_pViewTool) {
        m_pCurrentScene->drawMove(id, p1, p2);
    }else if (ViewTool::VT_Select == m_pViewTool) {
        m_pCurrentScene->dragMove(QRectF(p1, p2));
    }else if (ViewTool::VT_Eraser == m_pViewTool) {
        m_pCurrentScene->eraserMove(p1, p2);
    }
}

void BoardView::touchRelease(int id, const QPointF &p1)
{
    if (ViewTool::VT_Draw == m_pViewTool) {
            m_pCurrentScene->drawReleased(id, p1);
    }else if (ViewTool::VT_Select == m_pViewTool) {
        m_pCurrentScene->dragRelease();
    }else if (ViewTool::VT_Eraser == m_pViewTool) {
        m_pCurrentScene->eraserReleased();
    }
}

void BoardView::touchEnd()
{
    if (ViewTool::VT_Draw == m_pViewTool) {
        m_pCurrentScene->drawEnd();
        emit itemChanged();
    }
}

void BoardView::gestureMove(const QPointF &lastPt, const QPointF &curPt)
{
    qreal x1 = curPt.x() - lastPt.x();
    qreal y1 = curPt.y() - lastPt.y();
    m_pCurrentScene->moveAllItems(QPointF(x1, y1));
}

void BoardView::setScenesSelectable(bool bo)
{
    foreach(BoardScene *scene, m_pScenesList) {
        scene->setItemsSelectable(bo);
    }
}



