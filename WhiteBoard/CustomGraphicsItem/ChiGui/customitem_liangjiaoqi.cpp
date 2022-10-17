#include "customitem_liangjiaoqi.h"
#include <QDebug>
#include <qmath.h>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include "Public/public_function.h"

CustomItem_LiangJiaoQi::CustomItem_LiangJiaoQi(QObject *parent) : QObject(parent)
{
    mheight =20;
    Iconlength =50;
    deviation =10;
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    m_rect = QRectF(0,0,adapt(600),adapt(300));
    mrect = QRectF(adapt(75),adapt(75),adapt(450),adapt(450));
    drag_rect = QRect(0,0,adapt(Iconlength),adapt(Iconlength));
    close_rect = QRect(0,0,adapt(Iconlength),adapt(Iconlength));
    rotate_rect = QRect(0,0,adapt(Iconlength),adapt(Iconlength));
    this->setTransformOriginPoint(mrect.center());  //设置旋转点
    movedot1 =QPointF(adapt(551.147),adapt(155));
    movedot2 =QPointF(m_rect.topRight().x() -adapt(10),m_rect.bottomRight().y());
}

QPainterPath CustomItem_LiangJiaoQi::outDrawArea()
{
    QPainterPath path;
    path.arcMoveTo(mrect,0);
    path.arcTo(mrect,0,180);
    path.closeSubpath();
    return path;
}

QPainterPath CustomItem_LiangJiaoQi::inDrawArea4()
{
    QPainterPath path;
    QRect re = QRect(mrect.topLeft().x() +adapt(25),mrect.topLeft().y() +adapt(25),
            mrect.width() -adapt(50),mrect.height() -adapt(50));
//    path.addRect(re);
    path.arcMoveTo(re,0);
    path.arcTo(re,0,180);
    path.closeSubpath();
    return path;
}

QPainterPath CustomItem_LiangJiaoQi::inDrawArea3()
{
    QPainterPath path;
    QRect re = QRect(mrect.topLeft().x() +adapt(45),mrect.topLeft().y() +adapt(42),
            mrect.width() -adapt(90),mrect.height() -adapt(90));
//    path.addRect(re);
    path.arcMoveTo(re,0);
    path.arcTo(re,0,180);
    path.closeSubpath();
    return path;
}

QPainterPath CustomItem_LiangJiaoQi::inDrawArea2()
{
    QPainterPath path;
    QRect re = QRect(mrect.topLeft().x() +adapt(65),mrect.topLeft().y() +adapt(65),
            mrect.width() -adapt(130),mrect.height() -adapt(130));
//    path.addRect(re);
    path.arcMoveTo(re,0);
    path.arcTo(re,0,180);
    path.closeSubpath();
    return path;
}

QPainterPath CustomItem_LiangJiaoQi::inDrawArea1()
{
    QPainterPath path;
    QRect re = QRect(mrect.center().x() -adapt(45),mrect.center().y() -adapt(45),adapt(90),adapt(90));
//    path.addRect(re);
    path.arcMoveTo(re,0);
    path.arcTo(re,0,180);
    path.closeSubpath();
    return path;
}

QPainterPath CustomItem_LiangJiaoQi::getIconrect(QString str)
{
    QPainterPath path;
    if(str == "close_rect")
      {
        path.moveTo(close_rect.topLeft().x() +15*adapt(Iconlength)/50,close_rect.topLeft().y() +15*adapt(Iconlength)/50);
        path.lineTo(close_rect.bottomRight().x() -15*adapt(Iconlength)/50,close_rect.bottomRight().y() -15*adapt(Iconlength)/50);
        path.moveTo(close_rect.topRight().x() -15*adapt(Iconlength)/50,close_rect.topRight().y() +15*adapt(Iconlength)/50);
        path.lineTo(close_rect.bottomLeft().x() +15*adapt(Iconlength)/50,close_rect.bottomLeft().y() -15*adapt(Iconlength)/50);
    }
    else if(str == "drag_rect")
    {
        path.moveTo(drag_rect.topLeft().x() +25*adapt(Iconlength)/50,drag_rect.topLeft().y() +10*adapt(Iconlength)/50);
        path.lineTo(drag_rect.topLeft().x() +20*adapt(Iconlength)/50,drag_rect.topLeft().y() +15*adapt(Iconlength)/50);
        path.lineTo(drag_rect.topLeft().x() +30*adapt(Iconlength)/50,drag_rect.topLeft().y() +15*adapt(Iconlength)/50);
        path.closeSubpath();
        path.moveTo(drag_rect.topLeft().x() +25*adapt(Iconlength)/50,drag_rect.topLeft().y() +15*adapt(Iconlength)/50);
        path.lineTo(drag_rect.topLeft().x() +25*adapt(Iconlength)/50,drag_rect.topLeft().y() +35*adapt(Iconlength)/50);
        path.moveTo(drag_rect.topLeft().x() +20*adapt(Iconlength)/50,drag_rect.topLeft().y() +35*adapt(Iconlength)/50);
        path.lineTo(drag_rect.topLeft().x() +25*adapt(Iconlength)/50,drag_rect.topLeft().y() +40*adapt(Iconlength)/50);
        path.lineTo(drag_rect.topLeft().x() +30*adapt(Iconlength)/50,drag_rect.topLeft().y() +35*adapt(Iconlength)/50);
        path.closeSubpath();
    }
    else if(str == "rotate_rect")
    {
        QRect rect = QRect(rotate_rect.topLeft().x() +12*adapt(Iconlength)/50,rotate_rect.topLeft().y() +12*adapt(Iconlength)/50,
                           rotate_rect.width() -24*adapt(Iconlength)/50,rotate_rect.height() -24*adapt(Iconlength)/50);
        path.arcMoveTo(rect,-90);
        path.arcTo(rect,-90,-280);
        path.moveTo(rotate_rect.topLeft().x() +rotate_rect.width() -12*adapt(Iconlength)/50,
                    rotate_rect.topLeft().y() +rotate_rect.height()/2 +3*adapt(Iconlength)/50);
        path.lineTo(rotate_rect.topLeft().x() +rotate_rect.width() -17*adapt(Iconlength)/50,
                    rotate_rect.topLeft().y() +rotate_rect.height()/2 -1*adapt(Iconlength)/50);
        path.lineTo(rotate_rect.topLeft().x() +rotate_rect.width() -7*adapt(Iconlength)/50,
                    rotate_rect.topLeft().y() +rotate_rect.height()/2 -1*adapt(Iconlength)/50);
        path.lineTo(rotate_rect.topLeft().x() +rotate_rect.width() -12*adapt(Iconlength)/50,
                    rotate_rect.topLeft().y() +rotate_rect.height()*57/100);
    }
    return path;
}

void CustomItem_LiangJiaoQi::getRectStyle(QPoint dot)
{
    if(drag_rect.contains(dot,true))
    {
        mousepos4 = MOUSEPOS4::inRectDrag4;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(close_rect.contains(dot,true))
    {
        mousepos4 = MOUSEPOS4::inRectClose4;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(rotate_rect.contains(dot,true))
    {
        mousepos4 = MOUSEPOS4::inRectRotate4;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(move_rect3.contains(dot,true))
    {
        mousepos4 = MOUSEPOS4::move_rect1;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(move_rect4.contains(dot,true))
    {
        mousepos4 = MOUSEPOS4::move_rect2;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(sqrt((dot.x() -mrect.center().x())*(dot.x() -mrect.center().x()) +
            (dot.y() -mrect.center().y())*(dot.y() -mrect.center().y())) <= mrect.width()/2)
    {
        mousepos4 = MOUSEPOS4::inRectMove4;
        this->setCursor(Qt::SizeAllCursor);
    }
    else
    {
        mousepos4 = MOUSEPOS4::inRectNo4;
        this->setCursor(Qt::ArrowCursor);
    }
    update();
}

void CustomItem_LiangJiaoQi::getrotate(QPointF cen, QPointF second, QPointF first)
{
//    qDebug() << " dot " << cen << second << first <<endl;
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
//    qDebug() << " num " << num << endl;
    if(mousestate == true)
    {
        change_angle =rotate_angle + num;
        //emit sendrotate4(rotate_angle + num);
        this->setRotation(rotate_angle + num);
    }
    else if(mousestate == false)
    {
        rotate_angle = rotate_angle +num;
        //emit sendrotate4(rotate_angle);
        this->setRotation(rotate_angle);
    }
}

void CustomItem_LiangJiaoQi::getrotate2(QPointF cen, QPointF second, QPointF first)
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
        move_change1 =move_angle1 + num;
    }
    else if(mousestate == false)
    {
        move_angle1 = move_change1;
    }

    if( move_change1 < -180)move_change1 = move_change1+360;
    if((move_change1 >90)&&(move_change1<180))move_change1 = -180;
    if((move_change1 >0)&&(move_change1<90))move_change1 = -0;
    movedot1.setX(mrect.center().x() +(m_rect.width()/2 -adapt(10)) *cos(move_change1 *M_PI/180));
    movedot1.setY(mrect.center().y() +(m_rect.width()/2 -adapt(10)) *sin(move_change1 *M_PI/180));
    update();
}

void CustomItem_LiangJiaoQi::getrotate3()
{
    movedot1.setX(mrect.center().x() +(m_rect.width()/2 -adapt(10)) *cos(move_change1 *M_PI/180));
    movedot1.setY(mrect.center().y() +(m_rect.width()/2 -adapt(10)) *sin(move_change1 *M_PI/180));
    update();
}

void CustomItem_LiangJiaoQi::getrotate4(QPointF cen, QPointF second, QPointF first)
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
        move_change2 = move_angle2 +num;
    }
    else if(mousestate == false)
    {
        move_angle2 = move_change2;
    }

    if( move_change2 < -180)move_change2 = move_change2+360;
    if((move_change2 >90)&&(move_change2<180))move_change2 = -180;
    if((move_change2 >0)&&(move_change2<90))move_change2 = -0;
        movedot2.setX(mrect.center().x() +(m_rect.width()/2 -adapt(10)) *cos(move_change2 *M_PI/180));
        movedot2.setY(mrect.center().y() +(m_rect.width()/2 -adapt(10)) *sin(move_change2 *M_PI/180));
        update();

}

void CustomItem_LiangJiaoQi::getrotate5()
{

    movedot2.setX(mrect.center().x() +(m_rect.width()/2 -adapt(10)) *cos(move_change2 *M_PI/180));
    movedot2.setY(mrect.center().y() +(m_rect.width()/2 -adapt(10)) *sin(move_change2 *M_PI/180));
    update();
}

int CustomItem_LiangJiaoQi::adapt(int n)
{
    return Public_Function::getScaleSize(n);
}



QRectF CustomItem_LiangJiaoQi::boundingRect() const
{
    QRect re =QRect(m_rect.topLeft().x(),m_rect.topLeft().y(),m_rect.width() +Public_Function::getScaleSize(10),m_rect.height() +Public_Function::getScaleSize(10));
    return re;
}

QPainterPath CustomItem_LiangJiaoQi::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.arcMoveTo(mrect,0);
    path.arcTo(mrect,0,180);
    path.closeSubpath();
    path.addRect(QRect(movedot1.x() -Public_Function::getScaleSize(10),movedot1.y() -Public_Function::getScaleSize(10),Public_Function::getScaleSize(20),Public_Function::getScaleSize(20)));
    path.addRect(QRect(movedot2.x() -Public_Function::getScaleSize(10),movedot2.y() -Public_Function::getScaleSize(10),Public_Function::getScaleSize(20),Public_Function::getScaleSize(20)));
    return path;
}

QPainterPath CustomItem_LiangJiaoQi::test()
{
    QPainterPath path;
    path.arcMoveTo(mrect,0);
    path.arcTo(mrect,0,180);
    path.closeSubpath();
    path.addRect(QRect(movedot1.x() -Public_Function::getScaleSize(10),movedot1.y() -Public_Function::getScaleSize(10),Public_Function::getScaleSize(20),Public_Function::getScaleSize(20)));
    path.addRect(QRect(movedot2.x() -Public_Function::getScaleSize(10),movedot2.y() -Public_Function::getScaleSize(10),Public_Function::getScaleSize(20),Public_Function::getScaleSize(20)));
    return path;
}

void CustomItem_LiangJiaoQi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPainterPath pathIcon;
//    painter->setPen(QPen(QColor(Qt::red),1));
    painter->setRenderHint(QPainter::Antialiasing,true);
    mrect.moveTo(m_rect.center().x() -mrect.width()/2,m_rect.bottomLeft().y() -mrect.height()/2);
//    painter->drawRect(m_rect);
//    painter->drawRect(mrect);
//    painter->drawPath(test());
    painter->setBrush(Qt::white);
    painter->setPen(QPen(Qt::blue));
    painter->drawLine(mrect.center(),movedot1);
    move_rect3 = QRect(movedot1.x() -adapt(10),movedot1.y() -adapt(10),adapt(20),adapt(20));
    painter->drawEllipse(movedot1,adapt(10),adapt(10));
    painter->drawLine(mrect.center(),movedot2);
    move_rect4 = QRect(movedot2.x() -adapt(10),movedot2.y() -adapt(10),adapt(20),adapt(20));
    painter->drawEllipse(movedot2,adapt(10),adapt(10));
//    painter->drawRect(move_rect1);
//    painter->drawRect(move_rect2);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(210,210,210,150));
//    painter->setBrush(Qt::yellow);
    painter->drawPath(outDrawArea());
    painter->setBrush(QColor(249,249,249,150));
//    painter->setBrush(Qt::green);
    painter->drawPath(inDrawArea4());
    painter->setBrush(QColor(210,210,210,150));
//    painter->setBrush(Qt::blue);
    painter->drawPath(inDrawArea3());
    painter->setBrush(QColor(249,249,249,150));
    painter->drawPath(inDrawArea2());
    painter->translate(mrect.center());
    painter->setPen(QPen(QColor(212,212,213)));
    for(int i=0;i<180;i++)
    {
        if((i %10 ==0)&&(i !=0))
        {
//            qDebug() << " i " << i << endl;
            painter->drawLine(adapt(45),0,mrect.width()/2 -adapt(65),0);
        }
        painter->rotate(-1);
    }
    painter->rotate(180);
    painter->translate(-mrect.center());
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(245,245,245,90));
    painter->drawPath(inDrawArea1());
    if(mousepos4 ==MOUSEPOS4::inRectDrag4)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(drag_rect);
    }
    else if(mousepos4 ==MOUSEPOS4::inRectClose4)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(close_rect);
    }
    else if(mousepos4 ==MOUSEPOS4::inRectRotate4)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(rotate_rect);
    }
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QColor(216,230,233)));
    painter->drawArc(mrect,0,180*16);
    close_rect.moveTo(mrect.topLeft().x() +adapt(90),mrect.center().y() -adapt(70));
    painter->drawEllipse(close_rect);
    drag_rect.moveTo(mrect.center().x() -drag_rect.width()/2,mrect.topLeft().y() +adapt(80));
    painter->drawEllipse(drag_rect);
    rotate_rect.moveTo(mrect.topRight().x() -adapt(140),mrect.center().y() -adapt(70));
    painter->drawEllipse(rotate_rect);
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
    painter->setPen(QPen(QColor(160,161,164)));
    painter->translate(mrect.center());
    //QFont font("宋体",9,9);
    painter->setFont(Public_Function::getFont(9));
    for(int i=0;i<=90;i++)
    {
        if(i == 90)
        {
            painter->drawLine(QPoint(0,-(mrect.width()/2 -adapt(24))),QPoint(0,-mrect.width()/2));
            QRect re(QPoint(-adapt(16),-(mrect.width()/2 -adapt(15))),QSize(adapt(40),adapt(40)));
            QString title = QString("%1").arg(90 -i);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
        else if(i %10 ==0)
        {
            painter->drawLine(QPoint(0,-(mrect.width()/2 -adapt(24))),QPoint(0,-mrect.width()/2));
            QRect re(QPoint(-adapt(20),-(mrect.width()/2 -adapt(15))),QSize(adapt(40),adapt(40)));
            QString title = QString("%1").arg(90 -i);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
        else {
            painter->drawLine(QPoint(0,-(mrect.width()/2 -adapt(11))),QPoint(0,-mrect.width()/2));
        }
        painter->rotate(-1);
    }
    painter->rotate(90);
    for(int i=0;i<=90;i++)
    {
        painter->rotate(1);
        if(i == 90)
        {
            painter->drawLine(QPoint(0,-(mrect.width()/2 -adapt(24))),QPoint(0,-mrect.width()/2));
            QRect re(QPoint(-adapt(30),-(mrect.width()/2 -adapt(15))),QSize(adapt(40),adapt(40)));
            QString title = QString("%1").arg(90 +i);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
       else if(i %10 ==0)
        {
            painter->drawLine(QPoint(0,-(mrect.width()/2 -adapt(24))),QPoint(0,-mrect.width()/2));
            QRect re(QPoint(-adapt(20),-(mrect.width()/2 -adapt(15))),QSize(adapt(40),adapt(40)));
            QString title = QString("%1").arg(90 +i);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
        else {
            painter->drawLine(QPoint(0,-(mrect.width()/2 -adapt(11))),QPoint(0,-mrect.width()/2));
        }
    }
    painter->rotate(-90);
    for(int i=0;i<=90;i++)
    {
        if(i == 90)
        {
            QRect re(QPoint(-adapt(11),-(mrect.width()/2 -adapt(35))),QSize(adapt(40),adapt(40)));
            QString title = QString("%1").arg(90 +i);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
        else if(i %10 ==0)
        {
            QRect re(QPoint(-adapt(20),-(mrect.width()/2 -adapt(35))),QSize(adapt(40),adapt(40)));
            QString title = QString("%1").arg(90 +i);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
        painter->rotate(-1);
    }
    painter->rotate(90);
    for(int i=0;i<=90;i++)
    {
        painter->rotate(1);
        if(i == 90)
        {
            QRect re(QPoint(-adapt(25),-(mrect.width()/2 -adapt(35))),QSize(adapt(40),adapt(40)));
            QString title = QString("%1").arg(90 -i);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
        else if(i %10 ==0)
        {
            QRect re(QPoint(-adapt(20),-(mrect.width()/2 -adapt(35))),QSize(adapt(40),adapt(40)));
            QString title = QString("%1").arg(90 -i);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
    }
    painter->rotate(-90);
    painter->translate(-mrect.center());
    if(showtext != 0)
    {
        //QFont font2("宋体",23,23);
        painter->setFont(Public_Function::getFont(23));
        QRect re = QRect(mrect.center().x() -adapt(45),mrect.center().y() -adapt(45),adapt(90),adapt(60));
        if(showtext == 1)
        {
            QString title = QString("%1°").arg(change_angle);
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
        if(showtext == 2)
        {
            painter->setPen(QPen(QColor(38,122,182)));
            QString title = QString("∠%1°").arg(abs(move_change1 -move_change2));
            painter->drawText(re,Qt::AlignHCenter|Qt::AlignVCenter,title);
        }
    }
}

void CustomItem_LiangJiaoQi::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    this->setCursor(Qt::ArrowCursor);
}

void CustomItem_LiangJiaoQi::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
     getRectStyle(QPoint(event->pos().x(),event->pos().y()));
}


void CustomItem_LiangJiaoQi::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressEvent(event->pos(), event->scenePos());
}

void CustomItem_LiangJiaoQi::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    moveEvent(event->pos(), event->scenePos());
}

void CustomItem_LiangJiaoQi::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    releaseEvent(event->pos(), event->scenePos());
}

bool CustomItem_LiangJiaoQi::sceneEvent(QEvent *event)
{
    switch (event->type()) {
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

void CustomItem_LiangJiaoQi::pressEvent(QPointF pos, QPointF scenePos)
{
    getRectStyle(pos.toPoint());
    mousestate = true;
    if(mousepos4 == MOUSEPOS4::inRectDrag4)
    {
        rect = m_rect;
        start =pos;
        xx =m_rect.width();
        yy =m_rect.height();
        showtext =1;
    }
    else if(mousepos4 == MOUSEPOS4::inRectClose4)
    {
        emit deleteitem4(this);
    }
    else if(mousepos4 == MOUSEPOS4::inRectRotate4)
    {
        showtext =1;
        start = scenePos;
    }
    else if(mousepos4 == MOUSEPOS4::move_rect1)
    {
        showtext =2;
        start = scenePos;
    }
    else if(mousepos4 == MOUSEPOS4::move_rect2)
    {
        showtext =2;
        start = scenePos;
    }
    else if(mousepos4 == MOUSEPOS4::inRectMove4)
    {
        showtext =0;
        start = scenePos;
        store = this->pos();
    }
    else
    {
        ;
    }
}

void CustomItem_LiangJiaoQi::moveEvent(QPointF pos, QPointF scenePos)
{
    if(mousepos4 == MOUSEPOS4::inRectDrag4)
    {
        if(yy +start.y() -pos.y() < adapt(300))return;
        m_rect =QRect(rect.topLeft().x() +pos.y() -start.y(),rect.topLeft().y() +pos.y() -start.y(),
                      xx +2*(start.y() -pos.y()),yy +(start.y() -pos.y()));
        mrect =QRect(m_rect.topLeft().x() +m_rect.width()/8,m_rect.topLeft().y() +m_rect.width()/8,
                     m_rect.width() -m_rect.width()/4,m_rect.height() +m_rect.width()/4);
        getrotate3();
        getrotate5();
        emit refresh();
    }
    else if(mousepos4 == MOUSEPOS4::inRectRotate4)
    {
        if((scenePos.x() !=start.x())||((scenePos.y()!=start.y())))
        {
            getrotate(mapToScene(mrect.center()), scenePos, start);
        }
    }
    else if(mousepos4 == MOUSEPOS4::inRectMove4)
    {
        QPointF dot;
        dot.setX(store.x() +scenePos.x() -start.x());
        dot.setY(store.y() +scenePos.y() -start.y());
        this->setPos(dot);
    }
    else if(mousepos4 == MOUSEPOS4::move_rect1)
    {
       getrotate2(mapToScene(mrect.center()), scenePos, start);
    }
    else if(mousepos4 == MOUSEPOS4::move_rect2)
    {
       getrotate4(mapToScene(mrect.center()), scenePos, start);
    }
    update();
}

void CustomItem_LiangJiaoQi::releaseEvent(QPointF pos, QPointF scenePos)
{
    if(mousepos4 == MOUSEPOS4::inRectRotate4)
    {
       mousestate =false;
       getrotate(mapToScene(mrect.center()), scenePos, start);
    }
    else if(mousepos4 == MOUSEPOS4::inRectDrag4)
    {
       this->prepareGeometryChange();
       this->setTransformOriginPoint(mrect.center());
    }
    else if(mousepos4 == MOUSEPOS4::move_rect1)
    {
       mousestate =false;
       getrotate2(mapToScene(mrect.center()), scenePos, start);
    }
    else if(mousepos4 == MOUSEPOS4::move_rect2)
    {
       mousestate =false;
       getrotate4(mapToScene(mrect.center()), scenePos, start);
    }
    mousestate =false;
    mousepos4 =MOUSEPOS4::inRectNo4;
}
