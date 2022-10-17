#include "selectedrectitem.h"
#include <QtDebug>

static int m_ItemMinWidth = 0;

SelectedRectItem::SelectedRectItem(const QList<QGraphicsItem*>& selectedItems, QGraphicsItem *parent):
    QGraphicsItem(parent), m_SelectedItems(selectedItems)
{
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    this->setFlag(QGraphicsItem::ItemIsMovable);

    if (1 == selectedItems.size() &&selectedItems.at(0)->type() == (QGraphicsItem::UserType + (int)(ItemType::LineItem))) {
        m_RectType = RectType::Line;
        LineItem *lineItem = static_cast<LineItem *>(selectedItems.at(0));
        this->setLine(lineItem->line());
    }else {
        m_RectType = RectType::Rect;
        this->getSelectedRect();
    }

    this->createToolWidget();
    m_ItemAction = ItemAction::None;
    m_ItemMinWidth = Public_Function::getScaleSize(20);
}

SelectedRectItem::~SelectedRectItem()
{
    if (nullptr != m_pToolWidget)
        m_pToolWidget->widget()->deleteLater();
    if (nullptr != m_pBorderPanel)
        m_pBorderPanel->widget()->deleteLater();
    if (nullptr != m_pFillColorPanel)
        m_pFillColorPanel->widget()->deleteLater();
    if (nullptr != m_pFlipPanel)
        m_pFlipPanel->widget()->deleteLater();
    if (nullptr != m_pMirrorPanel)
        m_pMirrorPanel->widget()->deleteLater();
}

void SelectedRectItem::updateSelectItem(const QList<QGraphicsItem*>& selectedItems)
{
    m_SelectedItems.clear();
    m_SelectedItems.append(selectedItems);
    if( m_SelectedItems.size() == 0)
    {
        this->hide();
        return;
    }

    if (1 == selectedItems.size() &&selectedItems.at(0)->type() == (QGraphicsItem::UserType + (int)(ItemType::LineItem))) {
        m_RectType = RectType::Line;
        LineItem *lineItem = static_cast<LineItem *>(selectedItems.at(0));
        this->setLine(lineItem->line());
    }else {
        m_RectType = RectType::Rect;
        this->getSelectedRect();
    }

    createToolWidget();

    m_ItemAction = ItemAction::None;
    m_ItemMinWidth = Public_Function::getScaleSize(20);

    if( m_pBorderPanel)
        m_pBorderPanel->hide();
    if(m_pFillColorPanel)
        m_pFillColorPanel->hide();

    if( m_pMirrorPanel)
        m_pMirrorPanel->hide();
    if( m_pFlipPanel)
        m_pFlipPanel->hide();

    this->show();
    update();

}

void SelectedRectItem::updateLanguage()
{
    if( m_pItemTool != nullptr)
        m_pItemTool->updateLanguage();

}

QRectF SelectedRectItem::boundingRect() const
{
    QRectF rect;
    int radius  = Public_Function::getScaleSize(10);   //图标半径
    if (RectType::Rect == m_RectType) {
        rect = QRectF(QPointF(m_SelectedRect.x() - radius, m_pRotatePoint.y() - radius),
                      QPointF(m_SelectedRect.bottomRight().x() + radius, m_SelectedRect.bottomRight().y() + radius));
    }else if (RectType::Line == m_RectType) {
        qreal minX, minY, maxX, maxY;
        QVector<qreal> data;
        data.push_back(m_Line.p1().x());
        data.push_back(m_Line.p2().x());
        data.push_back(m_pRotatePoint.x());
        minX = Public_Function::getMin(data);
        maxX = Public_Function::getMax(data);
        data.clear();
        data.push_back(m_Line.p1().y());
        data.push_back(m_Line.p2().y());
        data.push_back(m_pRotatePoint.y());
        minY = Public_Function::getMin(data);
        maxY = Public_Function::getMax(data);
        rect = QRectF(QPointF(minX - radius, minY - radius),
                      QPointF(maxX + radius, maxY + radius));
    }
    return rect;
}

QPainterPath SelectedRectItem::shape() const
{
    QPainterPath retPath, path;
    if (RectType::Rect == m_RectType) {
        int radius = Public_Function::getScaleSize(12);
        path.addRect(m_SelectedRect);
        retPath += path;
        path = QPainterPath();
        path.addEllipse(m_SelectedRect.topLeft(), radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse(m_SelectedRect.topRight(), radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse(m_SelectedRect.bottomLeft(), radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse(m_SelectedRect.bottomRight(), radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse((m_SelectedRect.topLeft() +m_SelectedRect.topRight())/2, radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse((m_SelectedRect.bottomLeft() +m_SelectedRect.bottomRight())/2, radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse((m_SelectedRect.topLeft() +m_SelectedRect.bottomLeft())/2, radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse((m_SelectedRect.topRight() +m_SelectedRect.bottomRight())/2, radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse(m_pRotatePoint, radius, radius);
        retPath += path;
    }else if (RectType::Line == m_RectType) {
        int radius = Public_Function::getScaleSize(12);
        path.addEllipse(m_Line.p1(), radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse(m_Line.p2(), radius, radius);
        retPath += path;
        path = QPainterPath();
        path.addEllipse(m_pRotatePoint, radius, radius);
        retPath += path;
        retPath += m_LinePathStrokerPath;
    }

    return retPath;
}

//void SelectedRectItem::setToolVisable(bool bo)
//{
//    m_pShowTool = bo;
//    if (m_pToolWidget->isVisible() && !bo)
//        m_pToolWidget->setVisible(bo);
//}

QRectF SelectedRectItem::getRect()
{
    QRectF rect;
    if (RectType::Rect == m_RectType) {
        rect = m_SelectedRect;
    }else if (RectType::Line == m_RectType) {
        QPainterPath path;
        path.moveTo(m_Line.p1());
        path.lineTo(m_Line.p2());
        rect = path.boundingRect();
    }
    return rect;
}

void SelectedRectItem::setLine(const QLineF &line)
{
    m_Line = line;
    /*计算旋转点*/
    qreal angle = this->getRotateAngle(m_Line.p1(), QPointF(m_Line.p2().x(), m_Line.p1().y()), m_Line.p2());
    int height = Public_Function::getScaleSize(30);    //旋转点距离line的垂直高度
    QVariant variant;
    if (line.p1().x() < line.p2().x())
        variant.setValue(QPointF(m_Line.center().x(), m_Line.center().y() - height));
    else
        variant.setValue(QPointF(m_Line.center().x(), m_Line.center().y() + height));
    m_pRotatePoint = this->getRotateMap(variant, angle, m_Line.center()).toPointF();
    /*计算line的pathstroker，用于item移动功能的鼠标检测*/
    QPainterPath path;
    path.moveTo(line.p1());
    path.lineTo(line.p2());
    QPainterPathStroker stroker;
    int width = (static_cast<LineItem *>(m_SelectedItems.at(0)))->pen().width();
    width = width > Public_Function::getScaleSize(10) ? width : Public_Function::getScaleSize(10);
    stroker.setWidth(width);
    m_LinePathStrokerPath = stroker.createStroke(path);;
}

void SelectedRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_MouseMoved)return;

    //if (!m_pIsAdjustMode) {
    if (1) {
        if (RectType::Rect == m_RectType) {
#if  0
            /*绘制各个图标连接线*/
            painter->setBrush(QBrush());
            painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
            painter->drawRect(m_SelectedRect);
            painter->setPen(QPen(QBrush(QColor(0,184,169)), Public_Function::getScaleSize(2)));
            painter->drawLine(m_pRotatePoint, QLineF(m_SelectedRect.topLeft(), m_SelectedRect.topRight()).center());
            painter->setBrush(QBrush(QColor(0,184,169)));
            /*绘制各个图标*/
            int radius  = Public_Function::getScaleSize(9);   //图标半径
            if (ItemAction::Rotate == m_ItemAction)    //如果鼠标正在进行旋转操作，旋转图标绘制白色边框
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_pRotatePoint, radius, radius);
            painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomTopLeft == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_SelectedRect.topLeft(), radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomTopRight == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_SelectedRect.topRight(), radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomBottomLeft == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_SelectedRect.bottomLeft(), radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomBottomRight == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_SelectedRect.bottomRight(), radius, radius);
#endif

#if  1
            /*绘制各个图标连接线*/
            painter->setBrush(QBrush());
            painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
            painter->drawRect(m_SelectedRect);
            painter->setPen(QPen(QBrush(QColor(0,184,169)), Public_Function::getScaleSize(2)));
            painter->drawLine(m_pRotatePoint, QLineF(m_SelectedRect.topLeft(), m_SelectedRect.topRight()).center());
            painter->setBrush(QBrush(QColor(0,184,169)));
            /*绘制各个图标*/
            int radius  = Public_Function::getScaleSize(9);   //图标半径
            if (ItemAction::Rotate == m_ItemAction)    //如果鼠标正在进行旋转操作，旋转图标绘制白色边框
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_pRotatePoint, radius, radius);
            painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomTopLeft == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_SelectedRect.topLeft(), radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomTopRight == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_SelectedRect.topRight(), radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomBottomLeft == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_SelectedRect.bottomLeft(), radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));

            if (ItemAction::ZoomTopCenter == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse((m_SelectedRect.topLeft() +m_SelectedRect.topRight())/2, radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomBottomCenter == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse((m_SelectedRect.bottomLeft() +m_SelectedRect.bottomRight())/2, radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomRightCenter == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse((m_SelectedRect.topRight() +m_SelectedRect.bottomRight())/2, radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomLeftCenter == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse((m_SelectedRect.topLeft() +m_SelectedRect.bottomLeft())/2, radius, radius);
            painter->setBrush(QBrush(QColor(255,168,0)));

            if (ItemAction::ZoomBottomRight == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_SelectedRect.bottomRight(), radius, radius);
#endif
        }else if (RectType::Line == m_RectType){
            /*绘制旋转点到line的垂直线，需要减去笔宽*/
            painter->setPen(QPen(QBrush(QColor(0,184,169)), Public_Function::getScaleSize(2)));
            QLineF line = QLineF(m_pRotatePoint, m_Line.center());
            line.setLength(line.length() - (static_cast<LineItem *>(m_SelectedItems.at(0)))->pen().width());
            painter->drawLine(line);
            painter->setBrush(QBrush(QColor(0,184,169)));
            /*绘制各个图标*/
            int radius  = Public_Function::getScaleSize(8);   //图标半径
            if (ItemAction::Rotate == m_ItemAction)    //如果鼠标正在进行旋转操作，旋转图标绘制白色边框
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_pRotatePoint, radius, radius);
            painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
            painter->setBrush(QBrush(QColor(255,168,0)));
            if (ItemAction::ZoomP1 == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_Line.p1(), radius, radius);
            painter->setPen(QPen(QBrush(QColor(255,168,0)), Public_Function::getScaleSize(2)));
            if (ItemAction::ZoomP2 == m_ItemAction)
                painter->setPen(QPen(QBrush(Qt::white), Public_Function::getScaleSize(2)));
            painter->drawEllipse(m_Line.p2(), radius, radius);
        }
    }

    if (nullptr != m_pToolWidget && !m_pToolWidget->isVisible()) {
        QPointF showPoint = QPointF(this->boundingRect().center().x() - m_pToolWidget->widget()->width()/2.0,
                                    this->boundingRect().bottomLeft().y() + Public_Function::getScaleSize(20));
        //djf to avoid the tool panel go over the frame rect
        if( (showPoint.y() + m_pToolWidget->boundingRect().height()) > g_ScreenHeight)
        {
            showPoint.setY(g_ScreenHeight - m_pToolWidget->boundingRect().height() - Public_Function::getScaleSize(20));
        }
        if( (showPoint.x() < 0) )
            showPoint.setX( Public_Function::getScaleSize(20));
        else if( (showPoint.x() + m_pToolWidget->widget()->width()) > g_ScreenWidth)
            showPoint.setX( g_ScreenWidth - m_pToolWidget->widget()->width());

        m_pToolWidget->setGeometry(QRectF(showPoint.x(), showPoint.y(),
                                          m_pToolWidget->widget()->width(), m_pToolWidget->boundingRect().height()));
        m_pToolWidget->show();
    }
}

void SelectedRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    if (m_pIsAdjustMode)
//        return QGraphicsItem::hoverMoveEvent(event);
    QPointF pos = event->pos();
    qreal minLength = Public_Function::getScaleSize(10);
    QCursor cursor;
    QSize cursorSize = Public_Function::getScaleSize(QSize(18, 18));
    if (RectType::Rect == m_RectType) {
        if (qAbs(QLineF(pos, m_SelectedRect.topLeft()).length()) <= minLength ||
                qAbs(QLineF(pos, m_SelectedRect.bottomRight()).length()) <= minLength)  {
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao3@2x.png").scaled(cursorSize));
        }else if (qAbs(QLineF(pos, m_SelectedRect.topRight()).length()) <= minLength ||
                  qAbs(QLineF(pos, m_SelectedRect.bottomLeft()).length()) <= minLength)  {
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao4@2x.png").scaled(cursorSize));
        }else if (qAbs(QLineF(pos, (m_SelectedRect.topRight() +m_SelectedRect.topLeft())/2).length()) <= minLength ||
                  qAbs(QLineF(pos, (m_SelectedRect.bottomLeft() +m_SelectedRect.bottomRight())/2).length()) <= minLength)  {
            cursorSize = Public_Function::getScaleSize(QSize(25, 25));
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao6@2x.png").scaled(cursorSize));
        }else if (qAbs(QLineF(pos, (m_SelectedRect.topRight() +m_SelectedRect.bottomRight())/2).length()) <= minLength ||
                  qAbs(QLineF(pos, (m_SelectedRect.topLeft() +m_SelectedRect.bottomLeft())/2).length()) <= minLength)  {
            cursorSize = Public_Function::getScaleSize(QSize(25, 25));
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao7@2x.png").scaled(cursorSize));
        }else if (qAbs(QLineF(pos, m_pRotatePoint).length()) <= minLength)  {
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao2@2x.png").scaled(cursorSize));
        }else if (m_SelectedRect.contains(pos)) {
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png").scaled(Public_Function::getScaleSize(QSize(24, 24))));
        }else {
            cursor = Qt::ArrowCursor;
        }
        this->setCursor(cursor);
    }else if (RectType::Line == m_RectType){
        if (qAbs(QLineF(pos, m_Line.p1()).length()) <= minLength ||
                qAbs(QLineF(pos, m_Line.p2()).length()) <= minLength)  {
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao5@2x.png").scaled(Public_Function::getScaleSize(QSize(20, 26))));
        }else if (qAbs(QLineF(pos, m_pRotatePoint).length()) <= minLength)  {
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao2@2x.png").scaled(cursorSize));
        }else if (m_LinePathStrokerPath.contains(pos)) {
            cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png").scaled(Public_Function::getScaleSize(QSize(24, 24))));
        }else {
            cursor = Qt::ArrowCursor;
        }
        this->setCursor(cursor);
    }

    return QGraphicsItem::hoverMoveEvent(event);
}

void SelectedRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//    if (m_pIsAdjustMode)
//        return QGraphicsItem::hoverLeaveEvent(event);

    this->setCursor(Qt::ArrowCursor);
    return QGraphicsItem::hoverLeaveEvent(event);
}

void SelectedRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    if (m_pIsAdjustMode)
//        return QGraphicsItem::mousePressEvent(event);
    m_pMousePressedPoint = event->pos();
    m_pMouseLastPoint = event->pos();
    pressEvent(event->pos());
    return;
}

void SelectedRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    if (m_pIsAdjustMode)
//        return QGraphicsItem::mouseMoveEvent(event);
    moveEvent(event->pos());
}

void SelectedRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    releaseEvent();
}

bool SelectedRectItem::sceneEvent(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            pointid =ev->touchPoints().at(0).id();
            m_pMousePressedPoint = ev->touchPoints().at(0).pos();
            m_pMouseLastPoint = ev->touchPoints().at(0).pos();
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

void SelectedRectItem::pressEvent(QPointF pos)
{
    qreal minLength = Public_Function::getScaleSize(10);
    if (RectType::Rect == m_RectType) {
        if (qAbs(QLineF(pos, m_SelectedRect.topLeft()).length()) <= minLength) {
            m_ItemAction = ItemAction::ZoomTopLeft;
            m_LastScalePoint = m_SelectedRect.topLeft();
        }else if (qAbs(QLineF(pos, m_SelectedRect.topRight()).length()) <= minLength) {
            m_ItemAction = ItemAction::ZoomTopRight;
            m_LastScalePoint = m_SelectedRect.topRight();
        }else if (qAbs(QLineF(pos, m_SelectedRect.bottomLeft()).length()) <= minLength){
            m_ItemAction = ItemAction::ZoomBottomLeft;
            m_LastScalePoint = m_SelectedRect.bottomLeft();
        }else if (qAbs(QLineF(pos, m_SelectedRect.bottomRight()).length()) <= minLength){
            m_ItemAction = ItemAction::ZoomBottomRight;
            m_LastScalePoint = m_SelectedRect.bottomRight();
        }

        else if (qAbs(QLineF(pos, (m_SelectedRect.topLeft() +m_SelectedRect.topRight())/2).length()) <= minLength){
                    m_ItemAction = ItemAction::ZoomTopCenter;
                    m_LastScalePoint = m_SelectedRect.topLeft();
        }else if (qAbs(QLineF(pos, (m_SelectedRect.bottomLeft() +m_SelectedRect.bottomRight())/2).length()) <= minLength){
                    m_ItemAction = ItemAction::ZoomBottomCenter;
                    m_LastScalePoint = m_SelectedRect.bottomLeft();
        }else if (qAbs(QLineF(pos, (m_SelectedRect.topRight() +m_SelectedRect.bottomRight())/2).length()) <= minLength){
                    m_ItemAction = ItemAction::ZoomRightCenter;
                    m_LastScalePoint = m_SelectedRect.bottomRight();
        }else if (qAbs(QLineF(pos, (m_SelectedRect.topLeft() +m_SelectedRect.bottomLeft())/2).length()) <= minLength){
                    m_ItemAction = ItemAction::ZoomLeftCenter;
                    m_LastScalePoint = m_SelectedRect.bottomLeft();
        }

        else if (qAbs(QLineF(pos, m_pRotatePoint).length()) <= minLength){
            m_ItemAction = ItemAction::Rotate;
        }else if (m_SelectedRect.contains(pos)) {
            m_ItemAction = ItemAction::Move;
        }else
            m_ItemAction = ItemAction::None;
    }else if (RectType::Line == m_RectType) {
        if (qAbs(QLineF(pos, m_Line.p1()).length()) <= minLength) {
            m_ItemAction = ItemAction::ZoomP1;
        }else if (qAbs(QLineF(pos, m_Line.p2()).length()) <= minLength) {
            m_ItemAction = ItemAction::ZoomP2;
        }else if (qAbs(QLineF(pos,m_pRotatePoint).length()) <= minLength){
            m_ItemAction = ItemAction::Rotate;
        }else if (m_LinePathStrokerPath.contains(pos)){
            m_ItemAction = ItemAction::Move;
        }else {
            m_ItemAction = ItemAction::None;
            m_ItemAction = ItemAction::Rotate;
        }
    }
    m_OldRect =m_SelectedRect;
    this->getItemRect();
}

void SelectedRectItem::moveEvent(QPointF pos)
{
    if (ItemAction::None == m_ItemAction)
        return;

    if (!m_MouseMoved) {
        m_MouseMoved = true;
        this->scene()->update(this->boundingRect());
    }
    if (nullptr != m_pToolWidget && m_pToolWidget->isVisible()) {
        ItemTool *tool = static_cast<ItemTool*>(m_pToolWidget->widget());
        tool->clearCheck();
        m_pToolWidget->hide();
    }
    QPointF mousePos = pos;
    if (ItemAction::Move == m_ItemAction) {
        qreal subX = mousePos.x() - m_pMouseLastPoint.x();
        qreal subY = mousePos.y() - m_pMouseLastPoint.y();
        if (nullptr != m_pItemTool && m_pItemTool->isClone()) {
            emit this->cloneItems(QPointF(subX, subY));
        }else {
            this->moveItems(QPointF(subX, subY));
        }
        m_pMouseLastPoint = mousePos;
    }

    else if (ItemAction::Rotate == m_ItemAction) {
        QPointF center;
        qreal angle = 0;
        if (RectType::Rect == m_RectType) {
            angle = this->getRotateAngle(m_SelectedRect.center(), m_pRotatePoint, mousePos);
            center = m_SelectedRect.center();
        }else if (RectType::Line == m_RectType) {
            angle = this->getRotateAngle(m_Line.center(), m_pRotatePoint, mousePos);
            center = m_Line.center();
        }
        this->setTransformOriginPoint(center);
        this->setRotation(this->rotation() + angle);
        this->rotateItems(angle, center);
        m_pMouseLastPoint = mousePos;
    }

    else if (ItemAction::ZoomTopLeft == m_ItemAction) {
        qreal subX = m_SelectedRect.bottomRight().x() - mousePos.x();
        qreal subY = m_SelectedRect.bottomRight().y() - mousePos.y();
        subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
        subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
        qreal xFactor = subX/m_OldRect.width();
        qreal yFactor = subY/m_OldRect.height();
        if (m_ScaleToScale) //等比例缩放
            xFactor > yFactor ? xFactor = yFactor : yFactor = xFactor;
        if (1 == xFactor && 1 == yFactor)
            return;
        m_SelectedRect.setTopLeft(QPointF(m_SelectedRect.bottomRight().x() - subX,m_SelectedRect.bottomRight().y() - subY));
        this->scaleItems(xFactor, yFactor, m_SelectedRect.bottomRight());
    }

    else if (ItemAction::ZoomTopCenter == m_ItemAction) {
        qreal subX = m_SelectedRect.bottomRight().x() - mousePos.x();
        qreal subY = m_SelectedRect.bottomRight().y() - mousePos.y();
        subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
        subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
        qreal yFactor = subY/m_OldRect.height();
        m_SelectedRect.setTopLeft(QPointF(m_SelectedRect.bottomRight().x() - subX,m_SelectedRect.bottomRight().y() - subY));
        this->scaleItems(1, yFactor, m_SelectedRect.bottomRight());
    }

    else if (ItemAction::ZoomBottomCenter == m_ItemAction) {
        qreal subX = m_SelectedRect.topRight().x() - mousePos.x();
        qreal subY = mousePos.y() - m_SelectedRect.topRight().y();
        subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
        subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
        qreal yFactor = subY/m_OldRect.height();
        m_SelectedRect.setBottomLeft(QPointF(m_SelectedRect.topRight().x() - subX,m_SelectedRect.topRight().y() + subY));
        this->scaleItems(1, yFactor, m_SelectedRect.topRight());
    }

    else if (ItemAction::ZoomLeftCenter == m_ItemAction) {
        qreal subX = m_SelectedRect.bottomRight().x() - mousePos.x();
        qreal subY = m_SelectedRect.bottomRight().y() - mousePos.y();
        subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
        subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
        qreal xFactor = subX/m_OldRect.width();
        m_SelectedRect.setTopLeft(QPointF(m_SelectedRect.bottomRight().x() - subX,m_SelectedRect.bottomRight().y() - subY));
        this->scaleItems(xFactor, 1, m_SelectedRect.bottomRight());
    }

    else if (ItemAction::ZoomRightCenter == m_ItemAction) {
        qreal subX = mousePos.x() - m_SelectedRect.bottomLeft().x();
        qreal subY = m_SelectedRect.bottomLeft().y() - mousePos.y();
        subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
        subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
        qreal xFactor = subX/m_OldRect.width();
        m_SelectedRect.setTopRight(QPointF(m_SelectedRect.bottomLeft().x() +subX,m_SelectedRect.bottomLeft().y() -subY));
        this->scaleItems(xFactor, 1, m_SelectedRect.bottomLeft());
    }

    else if (ItemAction::ZoomTopRight == m_ItemAction) {
        qreal subX = mousePos.x() - m_SelectedRect.bottomLeft().x();
        qreal subY = m_SelectedRect.bottomLeft().y() - mousePos.y();
        subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
        subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
        qreal xFactor = subX/m_OldRect.width();
        qreal yFactor = subY/m_OldRect.height();
        if (m_ScaleToScale) //等比例缩放
            xFactor > yFactor ? xFactor = yFactor : yFactor = xFactor;
        if (1 == xFactor && 1 == yFactor)
            return;
        m_SelectedRect.setTopRight(QPointF(m_SelectedRect.bottomLeft().x() + subX,
                                 m_SelectedRect.bottomLeft().y() - subY));
        this->scaleItems(xFactor, yFactor, m_SelectedRect.bottomLeft());
    }

    else if (ItemAction::ZoomBottomLeft == m_ItemAction) {
        qreal subX = m_SelectedRect.topRight().x() - mousePos.x();
        qreal subY = mousePos.y() - m_SelectedRect.topRight().y();
        subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
        subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
        qreal xFactor = subX/m_OldRect.width();
        qreal yFactor = subY/m_OldRect.height();
        if (m_ScaleToScale) //等比例缩放
            xFactor > yFactor ? xFactor = yFactor : yFactor = xFactor;
        if (1 == xFactor && 1 == yFactor)
            return;
        m_SelectedRect.setBottomLeft(QPointF(m_SelectedRect.topRight().x() - subX,
                                   m_SelectedRect.topRight().y() + subY));
        this->scaleItems(xFactor, yFactor, m_SelectedRect.topRight());

    }else if (ItemAction::ZoomBottomRight == m_ItemAction) {    //右下角缩放 (移动点右下角，固定点左上角)
        qreal subX = mousePos.x() - m_SelectedRect.topLeft().x();
        qreal subY = mousePos.y() - m_SelectedRect.topLeft().y();
        subX = subX > Public_Function::getScaleSize(20) ? subX : Public_Function::getScaleSize(20);
        subY = subY > Public_Function::getScaleSize(20) ? subY : Public_Function::getScaleSize(20);
        qreal xFactor = subX/m_OldRect.width();
        qreal yFactor = subY/m_OldRect.height();
        if (m_ScaleToScale) //等比例缩放
            xFactor > yFactor ? xFactor = yFactor : yFactor = xFactor;
        if (1 == xFactor && 1 == yFactor)
            return;
        m_SelectedRect.setBottomRight(QPointF(m_SelectedRect.topLeft().x() + subX,
                                   m_SelectedRect.topLeft().y() + subY));
        this->scaleItems(xFactor, yFactor, m_SelectedRect.topLeft());
    }

    else if (ItemAction::ZoomP1 == m_ItemAction) {
        QLineF newLine = QLineF(mousePos, m_Line.p2());
        LineItem *lineItem = static_cast<LineItem *>(m_SelectedItems.at(0));
        if (!m_IsPushToHistory) {
            lineItem->pushDataToUndoData(LineItem::Line);
            m_IsPushToHistory = true;
        }
        lineItem->setLine(newLine);
        this->setLine(newLine);
    }else if (ItemAction::ZoomP2 == m_ItemAction) {
        QLineF newLine = QLineF(m_Line.p1(), mousePos);
        LineItem *lineItem = static_cast<LineItem *>(m_SelectedItems.at(0));
        if (!m_IsPushToHistory) {
            lineItem->pushDataToUndoData(LineItem::Line);
            m_IsPushToHistory = true;
        }
        lineItem->setLine(newLine);
        this->setLine(newLine);
    }
    this->update();
    return;
}

void SelectedRectItem::releaseEvent()
{
    if (!m_MouseMoved)
        return;

    if (ItemAction::Move == m_ItemAction && m_pItemTool->isClone()) {
        emit cloneFinished();
    }else{
        if (RectType::Rect == m_RectType) {
            this->getSelectedRect();
        }else if (RectType::Line == m_RectType) {
            LineItem *lineItem = static_cast<LineItem *>(m_SelectedItems.at(0));
            this->setLine(lineItem->line());
        }

        if (ItemAction::Rotate == m_ItemAction)
            this->setRotation(0);
        emit this->actionFinished();
    }

    m_ItemAction = ItemAction::None;
    m_IsPushToHistory = false;
    m_MouseMoved = false;
    this->update();

    return;
}


void SelectedRectItem::getSelectedRect()
{
    int count = 0;
    QPointF topLeft;
    QPointF bottomRight;
    foreach(QGraphicsItem *item, m_SelectedItems) {
            QRectF rect = item->boundingRect();
            if (0 == count) {
                topLeft = rect.topLeft();
                bottomRight = rect.bottomRight();
                count++;
            }else {
                if (topLeft.x() > rect.topLeft().x())
                    topLeft.setX(rect.topLeft().x());
                if (topLeft.y() > rect.topLeft().y())
                    topLeft.setY(rect.topLeft().y());
                if (bottomRight.x() < rect.bottomRight().x())
                    bottomRight.setX(rect.bottomRight().x());
                if (bottomRight.y() < rect.bottomRight().y())
                    bottomRight.setY(rect.bottomRight().y());
            }
    }

    m_SelectedRect = QRectF(topLeft, bottomRight);
    m_pRotatePoint = QPointF(m_SelectedRect.center().x(), m_SelectedRect.topLeft().y() - Public_Function::getScaleSize(30));    //旋转点
    return;
}


void SelectedRectItem::createToolWidget()
{
    QPen pen = QPen();
    bool penInit = false;
    int penWidth = -1;
    QColor penColor = QColor();
    Qt::PenStyle penStyle = Qt::NoPen;

    QColor fillColor = QColor();
    bool colorInit = false;
    int R = -1;
    int G = -1;
    int B = -1;
    int A = -1;
    ItemTool::ToolFlags flags = ItemTool::RM_None;
    if (RectType::Line == m_RectType) {
        flags |= ItemTool::RM_FillColor | ItemTool::RM_Adjust;  //移除填充和调节按钮
        LineItem *lineItem = static_cast<LineItem*>(m_SelectedItems.at(0));
        penWidth = lineItem->pen().width();
        penStyle = lineItem->pen().style();
        penColor = lineItem->pen().color();
    }else {
        foreach(QGraphicsItem *item, m_SelectedItems)
        {
                int type = item->type();
                switch(type)
                {
                case (QGraphicsItem::UserType + (int)(ItemType::PathItem)): {
                    flags |= ItemTool::RM_FillColor | ItemTool::RM_Border | ItemTool::RM_Adjust ;
                    PathItem *pathItem = static_cast<PathItem *>(item);
                    fillColor = pathItem->brush().color();
                }break;
                case (QGraphicsItem::UserType + (int)(ItemType::GraphicItem)): {
                    flags |= ItemTool::RM_Flip | ItemTool::RM_Mirror | ItemTool::RM_Adjust;
                    GraphicsItem *graphicItem = static_cast<GraphicsItem *>(item);
                    pen = graphicItem->pen();
                    fillColor = graphicItem->brush().color();
                }break;
                case (QGraphicsItem::UserType + (int)(ItemType::LineItem)): {
                    flags |= ItemTool::RM_FillColor | ItemTool::RM_Adjust;
                    LineItem *lineItem = static_cast<LineItem *>(item);
                    pen = lineItem->pen();
                }break;
                case (QGraphicsItem::UserType + (int)(ItemType::PixmapItem)): {
                    flags |= ItemTool::RM_Border | ItemTool::RM_FillColor | ItemTool::RM_Flip | ItemTool::RM_Mirror | ItemTool::RM_Clone | ItemTool::RM_Adjust;
                    m_ScaleToScale = true;
                }break;
                }

                /*判断每个item的笔宽，样式和颜色是否相同*/
                if (0 == (flags & ItemTool::RM_Border) && !penInit) {
                    penInit = true;
                    penWidth = pen.width();
                    penStyle = pen.style();
                    penColor = pen.color();
                }else if (0 == (flags & ItemTool::RM_Border) && -1 != penWidth) {
                    if (penWidth != pen.width() ||penStyle != pen.style() ||penColor != pen.color())
                    {
                        penWidth = -1;
                        penStyle = Qt::NoPen;
                        penColor = QColor();
                    }
                }

                /*判断每个item的填充颜色是否相同*/
                if (0 == (flags & ItemTool::RM_FillColor) && !colorInit) {
                    colorInit = true;
                    R = fillColor.red();
                    G = fillColor.green();
                    B = fillColor.blue();
                    A = fillColor.alpha();
                }else if (0 == (flags & ItemTool::RM_FillColor) && -1 != R) {
                    if (R != fillColor.red() ||
                        G != fillColor.green() ||
                        B != fillColor.blue() ||
                        A != fillColor.alpha())
                    {
                        R = -1;
                        G = -1;
                        B = -1;
                        A = -1;
                    }
                }
        }
    }
    if( m_pToolWidget == nullptr)
    {
        m_pToolWidget = new QGraphicsProxyWidget(this);
        m_pToolWidget->setAcceptTouchEvents(true);
    }
    if( m_pItemTool == nullptr)
    {
        m_pItemTool = new ItemTool(flags);
        m_pToolWidget->setWidget(m_pItemTool);
        connect(m_pItemTool, &ItemTool::toTop, this, [=](){ emit this->stayOnTop(); });
        connect(m_pItemTool, &ItemTool::toBottom, this, [=](){ emit this->stayOnBottom(); });
        connect(m_pItemTool, &ItemTool::toDelete, this, [=]{ emit this->deleteItems(); });
        //djf to fit all
        connect(m_pItemTool, &ItemTool::showBorderPanel, this, &SelectedRectItem::onShowBorderPanel);
        connect(m_pItemTool, &ItemTool::showFillColorPanel, this, &SelectedRectItem::onShowFillColorPanel);
        connect(m_pItemTool, &ItemTool::showFlipPanel, this, &SelectedRectItem::onShowFlipPanel);
        connect(m_pItemTool, &ItemTool::showMirrorPanel, this, &SelectedRectItem::onShowMirrorPanel);
    }
    else
        m_pItemTool->updateFlag(flags);

    m_pToolWidget->hide();


    if (0 == (flags & ItemTool::RM_Border)) {
        if( m_pBorderPanel == nullptr)
        {
            m_pBorderPanel = new QGraphicsProxyWidget(this);
            m_pBorderPanel->setAcceptTouchEvents(true);
//            ItemTool_BorderPanel *panel = new ItemTool_BorderPanel(penWidth, penColor,penStyle);
//            m_pBorderPanel->setAcceptTouchEvents(true);
//            m_pBorderPanel->setWidget(panel);
//            m_pBorderPanel->hide();
//            connect(panel, &ItemTool_BorderPanel::borderSizeChanged, this, [=](int size){ emit this->borderSizeChanged(size);});
//            connect(panel, &ItemTool_BorderPanel::borderLineChanged, this, [=](Qt::PenStyle penstyle){ emit this->borderLineChanged(penstyle);});
//            connect(panel, &ItemTool_BorderPanel::borderColorChanged, this, [=](QColor color){emit this->borderColorChanged(color);});
            //connect(m_pItemTool, &ItemTool::showBorderPanel, this, &SelectedRectItem::onShowBorderPanel);
        }
        if( p_borderPanelContain == nullptr)
        {
            p_borderPanelContain = new ItemTool_BorderPanel(penWidth, penColor,penStyle);
            m_pBorderPanel->setWidget(p_borderPanelContain);
            connect(p_borderPanelContain, &ItemTool_BorderPanel::borderSizeChanged, this, [=](int size){ emit this->borderSizeChanged(size);});
            connect(p_borderPanelContain, &ItemTool_BorderPanel::borderLineChanged, this, [=](Qt::PenStyle penstyle){ emit this->borderLineChanged(penstyle);});
            connect(p_borderPanelContain, &ItemTool_BorderPanel::borderColorChanged, this, [=](QColor color){emit this->borderColorChanged(color);});
        }else
            p_borderPanelContain->updateBorder(penWidth, penColor,penStyle);
        m_pBorderPanel->hide();
        p_borderPanelContain->hide();
    }

    if (0 == (flags & ItemTool::RM_FillColor)) {
        if( m_pFillColorPanel == nullptr)
        {
            m_pFillColorPanel = new QGraphicsProxyWidget(this);
            m_pFillColorPanel->setAcceptTouchEvents(true);
//            ItemTool_FillColorPanel *panel = new ItemTool_FillColorPanel(Qt::gray);
//            m_pFillColorPanel->setWidget(panel);
//            m_pFillColorPanel->hide();
//            connect(panel, &ItemTool_FillColorPanel::fillColorChanged, this, [=](QColor color){ emit this->fillColorChanged(color); });
            //connect(m_pItemTool, &ItemTool::showFillColorPanel, this, &SelectedRectItem::onShowFillColorPanel);
        }
        if( p_FillColorPanelContain == nullptr)
        {
            p_FillColorPanelContain =  new ItemTool_FillColorPanel(Qt::gray);
            m_pFillColorPanel->setWidget(p_FillColorPanelContain);
            connect(p_FillColorPanelContain, &ItemTool_FillColorPanel::fillColorChanged, this, [=](QColor color){ emit this->fillColorChanged(color); });
        }
        else
            p_FillColorPanelContain->updateFillColor(Qt::gray);
        p_FillColorPanelContain->hide();
        m_pFillColorPanel->hide();
    }

    if (0 == (flags & ItemTool::RM_Flip)) {
        if( m_pFlipPanel == nullptr)
        {
            m_pFlipPanel = new QGraphicsProxyWidget(this);
            ItemTool_FlipPanel *panel = new ItemTool_FlipPanel;
            m_pFlipPanel->setAcceptTouchEvents(true);
            m_pFlipPanel->setWidget(panel);
            m_pFlipPanel->hide();
            connect(panel, &ItemTool_FlipPanel::flip, this, [=](int direction){emit this->flipItems(direction, this->getCenter());});
    //        connect(m_pItemTool, &ItemTool::showFlipPanel, this, &SelectedRectItem::onShowFlipPanel);
        }
    }

    if (0 == (flags & ItemTool::RM_Mirror)) {
        if( m_pMirrorPanel == nullptr)
        {
            m_pMirrorPanel = new QGraphicsProxyWidget(this);
            ItemTool_MirrorPanel *panel = new ItemTool_MirrorPanel;
            m_pMirrorPanel->setAcceptTouchEvents(true);
            m_pMirrorPanel->setWidget(panel);
            m_pMirrorPanel->hide();
            connect(panel, &ItemTool_MirrorPanel::mirror, this, &SelectedRectItem::onMirror);
            //connect(m_pItemTool, &ItemTool::showMirrorPanel, this, &SelectedRectItem::onShowMirrorPanel);
        }
    }
}

QPointF SelectedRectItem::getCenter()
{
    QPointF center;
    if (RectType::Rect == m_RectType) {
        center = m_SelectedRect.center();
    }else if (RectType::Line == m_RectType) {
        center = m_Line.center();
    }
    return center;
}

void SelectedRectItem::moveItems(const QPointF &subPt)
{
    foreach(QGraphicsItem * item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                if (!m_IsPushToHistory)
                {
                    pathItem->pushDataToUndoData(PathItem::Path);   //先加入撤销历史记录
                }
                pathItem->moveItem(subPt);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                if (!m_IsPushToHistory)
                {
                    graphicItem->pushDataToUndoData(GraphicsItem::Path);   //先加入撤销历史记录
                }
                graphicItem->moveItem(subPt);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                if (!m_IsPushToHistory)
                    lineItem->pushDataToUndoData(LineItem::Line);   //先加入撤销历史记录
                lineItem->moveItem(subPt);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                if (!m_IsPushToHistory)
                {
                    pixmapItem->pushDataToUndoData(PixmapItem::Move);   //先加入撤销历史记录
                }
                pixmapItem->moveItem(subPt);
            }
    }
    if (!m_IsPushToHistory)
        m_IsPushToHistory = true;
}

void SelectedRectItem::rotateItems(qreal angle, const QPointF &center)
{
    foreach(QGraphicsItem * item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                if (!m_IsPushToHistory)
                    pathItem->pushDataToUndoData(PathItem::Path);   //先加入撤销历史记录
                pathItem->rotateItem(angle, center);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                if (!m_IsPushToHistory)
                    graphicItem->pushDataToUndoData(GraphicsItem::Path);   //先加入撤销历史记录
                graphicItem->rotateItem(angle, center);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                if (!m_IsPushToHistory)
                    lineItem->pushDataToUndoData(LineItem::Line);   //先加入撤销历史记录
                lineItem->rotateItem(angle, center);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                if (!m_IsPushToHistory)
                    pixmapItem->pushDataToUndoData(PixmapItem::Move);   //先加入撤销历史记录
                pixmapItem->rotateItem(angle, center);
            }
    }
    if (!m_IsPushToHistory)
        m_IsPushToHistory = true;
}

void SelectedRectItem::scaleItems(qreal xFactor, qreal yFactor, const QPointF &center)
{
    foreach(QGraphicsItem* item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                if (!m_IsPushToHistory)
                    pathItem->pushDataToUndoData(PathItem::Path);   //先加入撤销历史记录
                pathItem->scaleItem(xFactor, yFactor, center);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                if (!m_IsPushToHistory)
                    graphicItem->pushDataToUndoData(GraphicsItem::Path);   //先加入撤销历史记录
                graphicItem->scaleItem(xFactor, yFactor, center);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                lineItem->scaleItem(xFactor, yFactor, center);
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                pixmapItem->scaleItem(xFactor, yFactor, center);
            }
    }
    if (!m_IsPushToHistory)
        m_IsPushToHistory = true;
}

void SelectedRectItem::getItemRect()
{
    foreach(QGraphicsItem* item, m_SelectedItems) {
            if ((QGraphicsItem::UserType + (int)(ItemType::PathItem)) == item->type()) {
                PathItem *pathItem = static_cast<PathItem*>(item);
                pathItem->getItemPath();
            }else if ((QGraphicsItem::UserType + (int)(ItemType::GraphicItem)) == item->type()) {
                GraphicsItem *graphicItem = static_cast<GraphicsItem*>(item);
                graphicItem->getItemPath();
            }else if ((QGraphicsItem::UserType + (int)(ItemType::LineItem)) == item->type()) {
                LineItem *lineItem = static_cast<LineItem*>(item);
                lineItem->getItemLine();
            }else if ((QGraphicsItem::UserType + (int)(ItemType::PixmapItem)) == item->type()) {
                PixmapItem *pixmapItem = static_cast<PixmapItem*>(item);
                pixmapItem->getItemRect();
            }
    }
}

qreal SelectedRectItem::getRotateAngle(QPointF center, QPointF firstPoint, QPointF secondPoint)
{
    if(secondPoint == firstPoint)
        return 0;
    qreal ma_x = firstPoint.x() - center.x();
    qreal ma_y = firstPoint.y() - center.y();
    qreal mb_x = secondPoint.x() - center.x();
    qreal mb_y = secondPoint.y() - center.y();
    qreal v1 = (ma_x * mb_x) + (ma_y * mb_y);
    qreal ma_val = sqrt(ma_x * ma_x + ma_y * ma_y);
    qreal mb_val = sqrt(mb_x * mb_x + mb_y * mb_y);
    qreal cosm = v1 / (ma_val * mb_val);
    qreal angle = acos(cosm) * 180 / M_PI;
    if ((secondPoint.x() -firstPoint.x()) * (center.y() - firstPoint.y()) -
            (secondPoint.y() -firstPoint.y()) * (center.x() -firstPoint.x()) < 0) {
        angle = -angle;
    }
    if (qIsNaN(angle))  //Nan
        return 0;
    return angle;
}

QVariant SelectedRectItem::getRotateMap(QVariant data, qreal angle, const QPointF &center)
{
    QTransform transform;
    transform.rotate(angle, Qt::ZAxis);
    /* 设置旋转中心 */
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    QVariant retVariant;
    if (QMetaType::QPointF == (QMetaType::Type)data.type()) {
        retVariant.setValue(transform.map(data.toPointF()));
    }else if (QMetaType::QLineF == (QMetaType::Type)data.type()) {
        retVariant.setValue(transform.map(data.toLineF()));
    }
    return retVariant;
}

void SelectedRectItem::onShowBorderPanel(bool checked, const QPointF &displayPt)
{
    if (checked) {
        QPointF showPoint = QPointF(m_pToolWidget->geometry().x(),
                                    m_pToolWidget->geometry().y() + Public_Function::getScaleSize(92));
        m_pBorderPanel->setGeometry(QRectF(showPoint.x(), showPoint.y(),
                                           m_pBorderPanel->boundingRect().width(), m_pBorderPanel->boundingRect().height()));
        bool bo =false;
        emit checkIs3DShape(&bo);
        if(bo)
        {
            ItemTool_BorderPanel* mpanel =static_cast<ItemTool_BorderPanel*>(m_pBorderPanel->widget());
            mpanel->hideOtherPenStyle();
        }
        m_pBorderPanel->show();
    }else {
        m_pBorderPanel->hide();
    }
}

void SelectedRectItem::onShowFillColorPanel(bool checked, const QPointF &displayPt)
{
    if (checked) {
        QPointF showPoint = QPointF(m_pToolWidget->geometry().x() + displayPt.x(),
                                    m_pToolWidget->geometry().y() + Public_Function::getScaleSize(92));
        m_pFillColorPanel->setGeometry(QRectF(showPoint.x(), showPoint.y(),
                                              m_pFillColorPanel->boundingRect().width(), m_pFillColorPanel->boundingRect().height()));
        m_pFillColorPanel->show();
    }else {
        m_pFillColorPanel->hide();
    }
}

void SelectedRectItem::onShowFlipPanel(bool checked, const QPointF &displayPt)
{
    if (checked) {
        QPointF showPoint = QPointF(m_pToolWidget->geometry().x() + displayPt.x(),
                                    m_pToolWidget->geometry().y() + Public_Function::getScaleSize(92));
        m_pFlipPanel->setGeometry(QRectF(showPoint.x(), showPoint.y(),
                                         m_pFlipPanel->boundingRect().width(), m_pFlipPanel->boundingRect().height()));
        m_pFlipPanel->show();
    }else {
        m_pFlipPanel->hide();
    }
}

void SelectedRectItem::onShowMirrorPanel(bool checked, const QPointF &displayPt)
{
    if (checked) {
        QPointF showPoint = QPointF(m_pToolWidget->geometry().x() + displayPt.x(),
                                    m_pToolWidget->geometry().y() + Public_Function::getScaleSize(92));
        m_pMirrorPanel->setGeometry(QRectF(showPoint.x(), showPoint.y(),
                                           m_pMirrorPanel->boundingRect().width(), m_pMirrorPanel->boundingRect().height()));
        m_pMirrorPanel->show();
    }else {
        m_pMirrorPanel->hide();
    }
}

void SelectedRectItem::onMirror(int direction)
{
    int margin = Public_Function::getScaleSize(10);
    qreal p;    //翻转线，左右翻转时是X值，上下翻转时是Y值
    if (0 == direction) {   //向上翻转
        p = this->getRect().topLeft().y() - margin;
    }else if (1 == direction) { //向下翻转
        p = this->getRect().bottomLeft().y() + margin;
    }else if (2 == direction) { //向左翻转
        p = this->getRect().topLeft().x() - margin;
    }else if (3 == direction){  //向右翻转
        p = this->getRect().topRight().x() + margin;
    }

    emit this->mirrorItems(direction, p);
}



