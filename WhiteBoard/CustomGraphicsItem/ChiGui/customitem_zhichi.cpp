#include "customitem_zhichi.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <qmath.h>
#include <QDesktopWidget>
#include <QApplication>
#include "Public/public_function.h"
#include <QScreen>
#include <QGuiApplication>
CustomItem_ZhiChi::CustomItem_ZhiChi(QObject *parent) : QObject(parent)
{
    mheight =Public_Function::getScaleSize(25);
    deviation =Public_Function::getScaleSize(30);
    Iconlength =Public_Function::getScaleSize(50);
    RoundAngle =Public_Function::getScaleSize(5);
    this->setAcceptHoverEvents(true);  //接受鼠标悬停
    this->setAcceptedMouseButtons(Qt::LeftButton);  //只接受鼠标左键
    this->setAcceptTouchEvents(true);
    this->setTransformOriginPoint(0,deviation);  //设置旋转点
    m_rect = QRect(0,0,adapt(565),adapt(120) +deviation);
    drag_rect = QRect(0,0,Iconlength,Iconlength);
    close_rect = QRect(0,0,Iconlength,Iconlength);
    rotate_rect = QRect(0,0,Iconlength,Iconlength);
    line_rect = QRect(0,0,m_rect.width(),2 *deviation);
    move_rect = QRect(0,2 *deviation,m_rect.width(),m_rect.height() -2 *deviation);
    this->setOpacity(0.9);//设置透明度
    mm =adapt(4);
}

void CustomItem_ZhiChi::getRectStyle(QPoint dot)
{
    if(drag_rect.contains(dot,true))
    {
        mousepos = MOUSEPOS::inRectDrag;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(close_rect.contains(dot,true))
    {
        mousepos = MOUSEPOS::inRectClose;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(rotate_rect.contains(dot,true))
    {
        mousepos = MOUSEPOS::inRectRotate;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(line_rect.contains(dot,true))//&&(ToolType::Pen ==g_ToolType)
    {
        mousepos = MOUSEPOS::inRectLine;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(move_rect.contains(dot,true))
    {
        mousepos = MOUSEPOS::inRectMove;
        this->setCursor(Qt::SizeAllCursor);
    }
    else
    {
        mousepos = MOUSEPOS::inRectNo;
        this->setCursor(Qt::ArrowCursor);
    }
    update();
}

QPainterPath CustomItem_ZhiChi::getCalibrationrect()
{
    QPainterPath path;
    path.moveTo(RoundAngle,deviation);
    path.lineTo(m_rect.width() -RoundAngle,deviation);
    path.arcTo(m_rect.width() -2*RoundAngle,deviation,2*RoundAngle,2*RoundAngle,90,-90);
    path.lineTo(m_rect.width(),mheight +deviation +adapt(2));
    path.lineTo(0,mheight +deviation +adapt(2));
    path.lineTo(0,RoundAngle +deviation);
    path.arcTo(0,deviation,2*RoundAngle,2*RoundAngle,-180,-90);
    return path;
}

QPainterPath CustomItem_ZhiChi::getIconrect(QString str)
{
    QPainterPath path;
    if(str == "close_rect")
      {
        path.moveTo(close_rect.topLeft().x() +15*Iconlength/50,close_rect.topLeft().y() +15*Iconlength/50);
        path.lineTo(close_rect.bottomRight().x() -15*Iconlength/50,close_rect.bottomRight().y() -15*Iconlength/50);
        path.moveTo(close_rect.topRight().x() -15*Iconlength/50,close_rect.topRight().y() +15*Iconlength/50);
        path.lineTo(close_rect.bottomLeft().x() +15*Iconlength/50,close_rect.bottomLeft().y() -15*Iconlength/50);
    }
    else if(str == "drag_rect")
    {
        path.moveTo(drag_rect.topLeft().x() +10*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2);
        path.lineTo(drag_rect.topRight().x() -10*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2);
        path.lineTo(drag_rect.topRight().x() -14*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2*8/10);
        path.lineTo(drag_rect.topRight().x() -14*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2*12/10);
        path.lineTo(drag_rect.topRight().x() -10*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2);
        path.moveTo(drag_rect.topLeft().x() +14*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2*8/10);
        path.lineTo(drag_rect.topLeft().x() +10*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2);
        path.lineTo(drag_rect.topLeft().x() +14*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2*12/10);
        path.lineTo(drag_rect.topLeft().x() +14*Iconlength/50,drag_rect.topLeft().y() +Iconlength/2*8/10);
    }
    else if(str == "rotate_rect")
    {
        QRect rect = QRect(rotate_rect.topLeft().x() +12*Iconlength/50,rotate_rect.topLeft().y() +12*Iconlength/50,
                           rotate_rect.width() -24*Iconlength/50,rotate_rect.height() -24*Iconlength/50);
        path.arcMoveTo(rect,-90);
        path.arcTo(rect,-90,-280);
        path.moveTo(rotate_rect.topLeft().x() +rotate_rect.width() -12*Iconlength/50,
                    rotate_rect.topLeft().y() +rotate_rect.height()/2 +3*Iconlength/50);
        path.lineTo(rotate_rect.topLeft().x() +rotate_rect.width() -17*Iconlength/50,
                    rotate_rect.topLeft().y() +rotate_rect.height()/2 -1*Iconlength/50);
        path.lineTo(rotate_rect.topLeft().x() +rotate_rect.width() -7*Iconlength/50,
                    rotate_rect.topLeft().y() +rotate_rect.height()/2 -1*Iconlength/50);
        path.lineTo(rotate_rect.topLeft().x() +rotate_rect.width() -12*Iconlength/50,
                    rotate_rect.topLeft().y() +rotate_rect.height()*57/100);
    }
    return path;
}

//获得旋转的角度
void CustomItem_ZhiChi::getrotate(QPointF cen, QPointF second, QPointF first)
{
    if(second == first)return;
    double ma_x = first.x() - cen.x();
    double ma_y = first.y() - cen.y();
    double mb_x = second.x() - cen.x();
    double mb_y = second.y() - cen.y();
    double v1 = (ma_x * mb_x) + (ma_y * mb_y);
    double ma_val = sqrt(ma_x * ma_x + ma_y * ma_y);
    double mb_val = sqrt(mb_x * mb_x + mb_y * mb_y);
    double cosm = v1 / (ma_val * mb_val);
    double angleAMB = acos(cosm) * 180 / M_PI;
    int num = angleAMB;
    if(angleAMB >= (num + 0.5))
    {
        num++;
    }
    if ((second.x() -first.x()) *(cen.y() -first.y()) -(second.y() -first.y()) *(cen.x() -first.x()) <0)
    {
        num = -num;
    }
    if(mousestate == true)
    {
        change_angle =rotate_angle + num;
        this->setRotation(rotate_angle + num);
    }
    else if(mousestate == false)
    {
        rotate_angle = rotate_angle +num;
        this->setRotation(rotate_angle);
    }
}

//获得画线需要的坐标点
QPointF CustomItem_ZhiChi::getpoint(QPointF p1, QPointF p2, QPointF p3)
{
        QPointF pfoot;
        qreal dx =p1.x() -p2.x();
        qreal dy =p1.y() -p2.y();
        qreal u =(p3.x() -p1.x())*dx +(p3.y() -p1.y())*dy;
        u/=dx*dx +dy*dy;
        pfoot.setX(p1.x() +u*dx);
        pfoot.setY(p1.y() +u*dy);
        return pfoot;
}

int CustomItem_ZhiChi::adapt(int n)
{
    return Public_Function::getScaleSize(n);
}

void CustomItem_ZhiChi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPainterPath pathIn;
    QPainterPath pathIcon;
    //painter->drawRect(line_rect);
    //painter->drawRect(m_rect);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QBrush(QColor(240,240,240)));
    painter->drawRect(0,mheight +deviation,m_rect.width(),m_rect.height() -mheight -deviation);
    drag_rect.moveTo(m_rect.width() -adapt(60), (m_rect.height() -adapt(50))/2 +deviation);
    close_rect.moveTo(adapt(20), (m_rect.height() -adapt(50))/2 +deviation);
    rotate_rect.moveTo(m_rect.width() -adapt(120), (m_rect.height() -adapt(50))/2 +deviation);
    painter->setPen(QPen(QColor(216,216,216)));
    painter->drawEllipse(drag_rect);
    painter->drawEllipse(close_rect);
    painter->drawEllipse(rotate_rect);
    if(mousepos ==MOUSEPOS::inRectDrag)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(drag_rect);
    }
    else if(mousepos ==MOUSEPOS::inRectClose)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(close_rect);
    }
    else if(mousepos ==MOUSEPOS::inRectRotate)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(rotate_rect);
    }
    painter->setPen(QPen(Qt::NoPen));
    /*****************/
    painter->setBrush(QBrush(QColor(216,216,216)));
    pathIn = getCalibrationrect();
    painter->drawPath(pathIn);
    painter->setPen(QPen(QColor(160,161,164),adapt(2)));
    for(int i= 0; i < m_rect.width() /mm -1; i++)
    {
        if(i ==0)
        {
           painter->drawLine(QPoint(i*mm +adapt(2),deviation +adapt(2)),QPoint(i*mm +adapt(2),mheight +deviation -adapt(2)));
        }
        else if(i % 10 == 0)
        {
            painter->drawLine(QPoint(i*mm +adapt(2),deviation +adapt(2)),QPoint(i*mm +adapt(2),mheight +deviation -adapt(2)));
        }
        else if(i % 5 == 0)
        {
            painter->drawLine(QPoint(i*mm +adapt(2),deviation +adapt(2)),QPoint(i*mm +adapt(2),mheight*0.7 +deviation -adapt(2)));
        }
        else {
            painter->drawLine(QPoint(i*mm +adapt(2),deviation +adapt(2)),QPoint(i*mm +adapt(2),mheight*0.5 +deviation -adapt(2)));
        }
    }
    painter->setPen(QPen(QColor(127,138,142),adapt(4),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter->setBrush(Qt::NoBrush);
    pathIcon = getIconrect("close_rect");
    painter->drawPath(pathIcon);
    pathIcon = getIconrect("drag_rect");
    painter->drawPath(pathIcon);
    pathIcon = getIconrect("rotate_rect");
    painter->drawPath(pathIcon);
    painter->setPen(QPen(QColor(127,138,142),adapt(6),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter->drawPoint(rotate_rect.center());
    int a;
    if(change_angle <= 0)
    {
        a = abs(change_angle);
        if(a > 180)
        {
           a -= 360;
        }
    }
    else
    {
      a =-change_angle;
      if(a < -180)
      {
         a += 360;
      }
    }
//    QFont font("宋体",26,50);
    painter->setFont(Public_Function::getFont(26));
    QRectF re = QRectF(0,deviation,m_rect.width(),m_rect.height() -deviation);
    if(change_lenght !=0)
    {
        int m =change_lenght/10;
        int n =change_lenght%10;
        QString title = QString("%1.%2cm").arg(m).arg(n);
        painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
    }
    else if((showrotate ==1)&&(change_lenght ==0))
    {
       QString title = QString("%1°").arg(a);
       painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
    }

}

void CustomItem_ZhiChi::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    this->setCursor(Qt::ArrowCursor);
}

void CustomItem_ZhiChi::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    getRectStyle(QPoint(event->pos().x(),event->pos().y()));
}

void CustomItem_ZhiChi::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressEvent(event->pos(),event->scenePos());
}

void CustomItem_ZhiChi::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    moveEvent(event->pos(),event->scenePos());
}

void CustomItem_ZhiChi::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    releaseEvent(event->pos(),event->scenePos());
}

bool CustomItem_ZhiChi::sceneEvent(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::TouchBegin:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            pointid =ev->touchPoints().at(0).id();
            pressEvent(ev->touchPoints().at(0).pos(),ev->touchPoints().at(0).scenePos());
            return true;
            break;
        }
        case QEvent::TouchUpdate:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            foreach (QTouchEvent::TouchPoint tp, ev->touchPoints()) {
               if(tp.id() ==pointid)moveEvent(ev->touchPoints().at(0).pos(),ev->touchPoints().at(0).scenePos());
            }
            return true;
            break;
        }
        case QEvent::TouchEnd:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            foreach (QTouchEvent::TouchPoint tp, ev->touchPoints()) {
               if(tp.id() ==pointid)releaseEvent(ev->touchPoints().at(0).pos(),ev->touchPoints().at(0).scenePos());
            }
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

void CustomItem_ZhiChi::pressEvent(QPointF pos,QPointF scenePos)
{
    getRectStyle(pos.toPoint());
    mousestate = true;
    if(mousepos == MOUSEPOS::inRectDrag)
    {
       start.setX(m_rect.width() -pos.x());
    }
    else if(mousepos == MOUSEPOS::inRectClose)
    {
        emit deleteitem(this);
    }
    else if(mousepos == MOUSEPOS::inRectRotate)
    {
        start = scenePos;
        showrotate =1;
        change_lenght =0;
    }
    else if(mousepos == MOUSEPOS::inRectLine)
    {
        start =getpoint(QPointF(line_rect.topLeft().x(),line_rect.topLeft().y() +deviation),
                        QPointF(line_rect.topRight().x(),line_rect.topRight().y() +deviation),pos);
        start.setY(start.y() - g_PenSize/2);
        start =mapToScene(start);
        drawlinedot = pos;
        showrotate =1;
    }
    else if(mousepos == MOUSEPOS::inRectMove)
    {
        start = scenePos;
        movedot = this->pos();
        change_lenght =0;
        showrotate =2;
    }
    else {
        ;
    }
}

void CustomItem_ZhiChi::moveEvent(QPointF pos, QPointF scenePos)
{
    if(mousepos == MOUSEPOS::inRectDrag)
    {
        if(pos.x() > adapt(300))
        {
            m_rect.setRight(pos.x() +start.x());
            move_rect.setWidth(m_rect.width());
            line_rect.setWidth(m_rect.width());
            this->prepareGeometryChange();
        }
    }
    else if(mousepos == MOUSEPOS::inRectRotate)
    {
        if((scenePos.x() !=start.x())||((scenePos.y()!=start.y())))
        {
            getrotate(QPointF(this->pos().x(),this->pos().y() +deviation),scenePos,start);
        }
    }
    else if(mousepos == MOUSEPOS::inRectLine)
    {
       float number = abs((pos.x() -drawlinedot.x())/mm +1);
       change_lenght = number >= ((int)number +0.5)?(int)number +1:(int)number;
       end =getpoint(QPointF(line_rect.topLeft().x(),line_rect.topLeft().y() +deviation),
                       QPointF(line_rect.topRight().x(),line_rect.topRight().y() +deviation),pos);
       end.setY(end.y() - g_PenSize/2);
       end =mapToScene(end);
       emit sendline11(start, end);
    }
    else if(mousepos == MOUSEPOS::inRectMove)
    {
        QPointF dot;
        dot = movedot +scenePos -start;
        this->setPos(dot);
    }
    update();
}

void CustomItem_ZhiChi::releaseEvent(QPointF pos, QPointF scenePos)
{
    if(mousepos == MOUSEPOS::inRectRotate)
    {
        if((scenePos.x() !=start.x())||((scenePos.y()!=start.y())))
        {
            mousestate =false;
            getrotate(QPointF(this->pos().x(),this->pos().y() +deviation),scenePos,start);
        }
    }
    else if(mousepos == MOUSEPOS::inRectLine)
    {
        end =getpoint(QPointF(line_rect.topLeft().x(),line_rect.topLeft().y() +deviation),
                        QPointF(line_rect.topRight().x(),line_rect.topRight().y() +deviation),pos);
        end.setY(end.y() - g_PenSize/2);
        end = mapToScene(end);
        emit sendline12(start,end);
    }
    mousestate =false;
    mousepos =MOUSEPOS::inRectNo;
}

QRectF CustomItem_ZhiChi::boundingRect() const
{
    return QRectF(Public_Function::getScaleSize(-1), Public_Function::getScaleSize(-1),m_rect.width() +Public_Function::getScaleSize(1),m_rect.height() +Public_Function::getScaleSize(1));
}

QPainterPath CustomItem_ZhiChi::shape() const
{
    QPainterPath path;
    path.addRect(m_rect);
    return path;
}
