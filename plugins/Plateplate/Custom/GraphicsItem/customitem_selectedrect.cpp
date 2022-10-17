#include "customitem_selectedrect.h"

CustomItem_SelectedRect::CustomItem_SelectedRect(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    this->setAcceptedMouseButtons(Qt::LeftButton);
    //开启鼠标跟踪
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);

    m_pItemAction = ItemAction::None;
}

CustomItem_SelectedRect::~CustomItem_SelectedRect()
{
    if (nullptr != m_pToolWidget)
        m_pToolWidget->widget()->deleteLater();
}


QRectF CustomItem_SelectedRect::boundingRect() const
{
    QRectF rect;
    int radius  = PublicFunction::getScaleSize(10);   //图标半径
    rect = QRectF(QPointF(m_pSelectRect.x() - radius, m_pRotatePoint.y() - radius),
                  QPointF(m_pSelectRect.bottomRight().x() + radius, m_pSelectRect.bottomRight().y() + radius));

    return rect;
}

QPainterPath CustomItem_SelectedRect::shape() const
{
    QPainterPath retPath, path;
    int radius = PublicFunction::getScaleSize(12);
    path.addRect(m_pSelectRect);
    retPath += path;
    path -= path;
    path.addEllipse(m_pSelectRect.topLeft(), radius, radius);
    retPath += path;
    path -= path;
    path.addEllipse(m_pSelectRect.topRight(), radius, radius);
    retPath += path;
    path -= path;
    path.addEllipse(m_pSelectRect.bottomLeft(), radius, radius);
    retPath += path;
    path -= path;
    path.addEllipse(m_pSelectRect.bottomRight(), radius, radius);
    retPath += path;
    path -= path;
    path.addEllipse(m_pRotatePoint, radius, radius);
    retPath += path;

    return retPath;
}

void CustomItem_SelectedRect::setRect(const QRectF rect)
{
    m_pSelectRect = rect;
    m_pRotatePoint = QPointF(rect.center().x(), rect.topLeft().y() - PublicFunction::getScaleSize(30));
}

/* 创建工具条 */
void CustomItem_SelectedRect::createTool(bool isClone)
{
    m_pToolWidget = new QGraphicsProxyWidget(this);
    m_pItemToolBar = new GraphicsItem_ToolBar;
    m_pItemToolBar->setCloneChecked(isClone);
    m_IsCloneMode = isClone;
    m_pToolWidget->setWidget(m_pItemToolBar);
    m_pToolWidget->hide();
    connect(m_pItemToolBar, &GraphicsItem_ToolBar::actionClone, this, [=](bool checked){
        m_IsCloneMode = checked; emit this->cloneModeChanged(checked);
    }, Qt::DirectConnection);
    connect(m_pItemToolBar, &GraphicsItem_ToolBar::actionStayOnTop, this, [=](){
        emit this->stayTop();
    }, Qt::DirectConnection);
    connect(m_pItemToolBar, &GraphicsItem_ToolBar::actionStayOnBottom, this, [=](){
        emit this->stayBottom();
    }, Qt::DirectConnection);
    connect(m_pItemToolBar, &GraphicsItem_ToolBar::actionDelete, this, [=](){
        emit this->toDelete();
    }, Qt::DirectConnection);
}

void CustomItem_SelectedRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_pMouseMoving)
        return;

    /*绘制各个图标连接线*/
    painter->setBrush(QBrush());
    painter->setPen(QPen(QBrush(QColor(255,168,0)), PublicFunction::getScaleSize(2)));
    painter->drawRect(m_pSelectRect);
    painter->setPen(QPen(QBrush(QColor(0,184,169)), PublicFunction::getScaleSize(2)));
    painter->drawLine(m_pRotatePoint, QLineF(m_pSelectRect.topLeft(), m_pSelectRect.topRight()).center());
    painter->setBrush(QBrush(QColor(0,184,169)));
    /*绘制各个图标*/
    int radius  = PublicFunction::getScaleSize(9);   //图标半径
    if (ItemAction::Rotate == m_pItemAction)    //如果鼠标正在进行旋转操作，旋转图标绘制白色边框
        painter->setPen(QPen(QBrush(Qt::white), PublicFunction::getScaleSize(2)));
    painter->drawEllipse(m_pRotatePoint, radius, radius);
    painter->setPen(QPen(QBrush(QColor(255,168,0)), PublicFunction::getScaleSize(2)));
    painter->setBrush(QBrush(QColor(255,168,0)));
    if (ItemAction::ZoomTopLeft == m_pItemAction)
        painter->setPen(QPen(QBrush(Qt::white), PublicFunction::getScaleSize(2)));
    painter->drawEllipse(m_pSelectRect.topLeft(), radius, radius);
    painter->setBrush(QBrush(QColor(255,168,0)));
    if (ItemAction::ZoomTopRight == m_pItemAction)
        painter->setPen(QPen(QBrush(Qt::white), PublicFunction::getScaleSize(2)));
    painter->drawEllipse(m_pSelectRect.topRight(), radius, radius);
    painter->setBrush(QBrush(QColor(255,168,0)));
    if (ItemAction::ZoomBottomLeft == m_pItemAction)
        painter->setPen(QPen(QBrush(Qt::white), PublicFunction::getScaleSize(2)));
    painter->drawEllipse(m_pSelectRect.bottomLeft(), radius, radius);
    painter->setBrush(QBrush(QColor(255,168,0)));
    if (ItemAction::ZoomBottomRight == m_pItemAction)
        painter->setPen(QPen(QBrush(Qt::white), PublicFunction::getScaleSize(2)));
    painter->drawEllipse(m_pSelectRect.bottomRight(), radius, radius);

    if (m_pShowTool && nullptr != m_pToolWidget && !m_pToolWidget->isVisible()) {
        QPointF showPoint = QPointF(this->boundingRect().center().x() - m_pToolWidget->widget()->width()/2.0,
                                    this->boundingRect().bottomLeft().y() + PublicFunction::getScaleSize(20));
        m_pToolWidget->setGeometry(QRectF(showPoint.x(), showPoint.y(),
                                   m_pToolWidget->widget()->width(), m_pToolWidget->boundingRect().height()));
        m_pToolWidget->show();
    }
}

void CustomItem_SelectedRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pos = event->pos();
    qreal minLength = PublicFunction::getScaleSize(10);
    QCursor cursor;
    QSize cursorSize = PublicFunction::getScaleSize(QSize(18, 18));
    if (qAbs(QLineF(pos, m_pSelectRect.topLeft()).length()) <= minLength ||
            qAbs(QLineF(pos, m_pSelectRect.bottomRight()).length()) <= minLength)  {
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao3@2x.png").scaled(cursorSize));
    }else if (qAbs(QLineF(pos, m_pSelectRect.topRight()).length()) <= minLength ||
              qAbs(QLineF(pos, m_pSelectRect.bottomLeft()).length()) <= minLength)  {
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao4@2x.png").scaled(cursorSize));
    }else if (qAbs(QLineF(pos, m_pRotatePoint).length()) <= minLength)  {
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao2@2x.png").scaled(cursorSize));
    }else if (m_pSelectRect.contains(pos)) {
        cursor = QCursor(QPixmap(":/images/mouseCursor/guangbiao1@2x.png")
                         .scaled(PublicFunction::getScaleSize(QSize(24, 24))));
    }else {
        cursor = Qt::ArrowCursor;
    }
    this->setCursor(cursor);

    return QGraphicsItem::hoverMoveEvent(event);
}

void CustomItem_SelectedRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    return QGraphicsItem::hoverLeaveEvent(event);
}

void CustomItem_SelectedRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_pMouseLastPoint = event->pos();

    qreal minLength = PublicFunction::getScaleSize(10);
    QPointF pos = event->pos();
    if (qAbs(QLineF(pos, m_pSelectRect.topLeft()).length()) <= minLength) {
        m_pItemAction = ItemAction::ZoomTopLeft;
    }else if (qAbs(QLineF(pos, m_pSelectRect.topRight()).length()) <= minLength) {
        m_pItemAction = ItemAction::ZoomTopRight;
    }else if (qAbs(QLineF(pos, m_pSelectRect.bottomLeft()).length()) <= minLength){
        m_pItemAction = ItemAction::ZoomBottomLeft;
    }else if (qAbs(QLineF(pos, m_pSelectRect.bottomRight()).length()) <= minLength){
        m_pItemAction = ItemAction::ZoomBottomRight;
    }else if (qAbs(QLineF(pos, m_pRotatePoint).length()) <= minLength){
        m_pItemAction = ItemAction::Rotate;
    }else if (m_pSelectRect.contains(pos)) {
        m_pItemAction = ItemAction::Move;
    }else
        m_pItemAction = ItemAction::None;

    this->update();
    return;
}

void CustomItem_SelectedRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (ItemAction::None == m_pItemAction)
        return;

    m_pMouseMoving = true;
    if (nullptr != m_pToolWidget && m_pToolWidget->isVisible()) {
        m_pToolWidget->hide();
    }
    QPointF mousePos = event->pos();
    if (ItemAction::Move == m_pItemAction) {
        qreal subX = mousePos.x() - m_pMouseLastPoint.x();
        qreal subY = mousePos.y() - m_pMouseLastPoint.y();
        if (nullptr != m_pItemToolBar && m_IsCloneMode) {
            emit this->toClone(subX, subY);
        }else {
            QRectF rect = m_pSelectRect;
            rect.moveCenter(QPointF(m_pSelectRect.center().x() + subX,
                                    m_pSelectRect.center().y() + subY));
            this->setRect(rect);
            emit actionMove(QPointF(subX, subY));
        }
        m_pMouseLastPoint = mousePos;
    }else if (ItemAction::Rotate == m_pItemAction) {
        QPointF center;
        qreal angle;
        angle = PublicFunction::getRotateAngle(m_pSelectRect.center(), m_pRotatePoint, mousePos);
        center = m_pSelectRect.center();
        this->setTransformOriginPoint(center);
        this->setRotation(this->rotation() + angle);
        emit actionRotate(angle, center);

        m_pMouseLastPoint = mousePos;
    }else if (ItemAction::ZoomTopLeft == m_pItemAction) {
        qreal subX = m_pSelectRect.bottomRight().x() - mousePos.x();
        qreal subY = m_pSelectRect.bottomRight().y() - mousePos.y();
        subX = subX > PublicFunction::getScaleSize(20) ? subX : PublicFunction::getScaleSize(20);
        subY = subY > PublicFunction::getScaleSize(20) ? subY : PublicFunction::getScaleSize(20);
        qreal xFactor = subX/m_pSelectRect.width();
        qreal yFactor = subY/m_pSelectRect.height();
        if (1 == xFactor && 1 == yFactor)
            return;

        QRectF rect = m_pSelectRect;
        rect.setTopLeft(QPointF(m_pSelectRect.bottomRight().x() - subX,
                                         m_pSelectRect.bottomRight().y() - subY));
        this->setRect(rect);
        emit actionScale(xFactor, yFactor, m_pSelectRect.bottomRight());
    }else if (ItemAction::ZoomTopRight == m_pItemAction) {
        qreal subX = mousePos.x() - m_pSelectRect.bottomLeft().x();
        qreal subY = m_pSelectRect.bottomLeft().y() - mousePos.y();
        subX = subX > PublicFunction::getScaleSize(20) ? subX : PublicFunction::getScaleSize(20);
        subY = subY > PublicFunction::getScaleSize(20) ? subY : PublicFunction::getScaleSize(20);
        qreal xFactor = subX/m_pSelectRect.width();
        qreal yFactor = subY/m_pSelectRect.height();
        if (1 == xFactor && 1 == yFactor)
            return;

        QRectF rect = m_pSelectRect;
        rect.setTopRight(QPointF(m_pSelectRect.bottomLeft().x() + subX,
                                         m_pSelectRect.bottomLeft().y() - subY));
        this->setRect(rect);
        emit actionScale(xFactor, yFactor, m_pSelectRect.bottomLeft());
    }else if (ItemAction::ZoomBottomLeft == m_pItemAction) {
        qreal subX = m_pSelectRect.topRight().x() - mousePos.x();
        qreal subY = mousePos.y() - m_pSelectRect.topRight().y();
        subX = subX > PublicFunction::getScaleSize(20) ? subX : PublicFunction::getScaleSize(20);
        subY = subY > PublicFunction::getScaleSize(20) ? subY : PublicFunction::getScaleSize(20);
        qreal xFactor = subX/m_pSelectRect.width();
        qreal yFactor = subY/m_pSelectRect.height();
        if (1 == xFactor && 1 == yFactor)
            return;

        QRectF rect = m_pSelectRect;
        rect.setBottomLeft(QPointF(m_pSelectRect.topRight().x() - subX,
                                         m_pSelectRect.topRight().y() + subY));
        this->setRect(rect);
        emit actionScale(xFactor, yFactor, m_pSelectRect.topRight());
    }else if (ItemAction::ZoomBottomRight == m_pItemAction) {
        qreal subX = mousePos.x() - m_pSelectRect.topLeft().x();
        qreal subY = mousePos.y() - m_pSelectRect.topLeft().y();
        subX = subX > PublicFunction::getScaleSize(20) ? subX : PublicFunction::getScaleSize(20);
        subY = subY > PublicFunction::getScaleSize(20) ? subY : PublicFunction::getScaleSize(20);
        qreal xFactor = subX/m_pSelectRect.width();
        qreal yFactor = subY/m_pSelectRect.height();
        if (1 == xFactor && 1 == yFactor)
            return;

        QRectF rect = m_pSelectRect;
        rect.setBottomRight(QPointF(m_pSelectRect.topLeft().x() + subX,
                                         m_pSelectRect.topLeft().y() + subY));
        this->setRect(rect);
        emit actionScale(xFactor, yFactor, m_pSelectRect.topLeft());
    }
    this->update();
    return;
}

void CustomItem_SelectedRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (ItemAction::Rotate == m_pItemAction) {
        emit actionRotateFinished();
        this->setRotation(0);
    }else if (ItemAction::Move == m_pItemAction) {
        if (nullptr != m_pItemToolBar && m_IsCloneMode) {
            emit this->cloneFinished();
        }else {
            emit actionFinished();
        }
    }else if (ItemAction::ZoomTopLeft == m_pItemAction ||
              ItemAction::ZoomTopRight == m_pItemAction ||
              ItemAction::ZoomBottomLeft == m_pItemAction ||
              ItemAction::ZoomBottomRight == m_pItemAction) {
        emit actionScaleFinished();
    }else
        emit actionFinished();

    m_pItemAction = ItemAction::None;
    m_pMouseMoving = false;
    this->update();
    return;
}

