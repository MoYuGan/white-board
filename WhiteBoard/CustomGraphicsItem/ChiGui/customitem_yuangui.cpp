#include "customitem_yuangui.h"

/*************************************************************************
                                圆规左边腿绘制
*************************************************************************/
YuanGui_leftFoot::YuanGui_leftFoot(QObject *parent) : QObject(parent)
{
    this->setAcceptTouchEvents(true);
    this->setAcceptHoverEvents(true);
    rect = QRectF(0,0,Public_Function::getScaleSize(25),Public_Function::getScaleSize(400));
}

void YuanGui_leftFoot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor(198,199,202)));
    painter->drawPath(downShape());
    painter->setBrush(QBrush(QColor(229,231,237)));
    painter->drawPath(upShape());
    painter->setPen(QPen(Qt::darkGray));
    painter->drawLine(rect.topRight(),QPointF(rect.bottomRight().x(),rect.bottomRight().y() -Public_Function::getScaleSize(400/32)));
}

QRectF YuanGui_leftFoot::boundingRect() const
{
    return rect;
}

bool YuanGui_leftFoot::sceneEvent(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        case QEvent::GraphicsSceneMouseMove:
        case QEvent::GraphicsSceneMousePress:
        case QEvent::GraphicsSceneMouseRelease:
        {
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

QPainterPath YuanGui_leftFoot::downShape()
{
    QPainterPath path;
    path.moveTo(rect.topLeft());
    path.lineTo(rect.topRight());
    path.lineTo(rect.bottomRight());
    path.lineTo(rect.topLeft().x(),rect.bottomLeft().y() -Public_Function::getScaleSize(400/11));
    path.closeSubpath();
    return path;
}

QPainterPath YuanGui_leftFoot::upShape()
{
    QPainterPath path;
    path.moveTo(rect.topLeft());
    path.lineTo(rect.topRight());
    QPointF p1 =QPointF(rect.bottomRight().x(),rect.bottomRight().y() -Public_Function::getScaleSize(400/32));
    path.lineTo(p1);
    QPointF p2 =QPointF(rect.bottomLeft().x(),rect.bottomRight().y() -Public_Function::getScaleSize(400/16));
    path.quadTo(QPoint(p2.x() +Public_Function::getScaleSize(5),p1.y() +Public_Function::getScaleSize(2)),p2);
    path.closeSubpath();
    return path;
}

QPainterPath YuanGui_leftFoot::shape() const
{
    QPainterPath path;
    path.moveTo(rect.topLeft());
    path.lineTo(rect.topRight());
    path.lineTo(rect.bottomRight());
    path.lineTo(rect.topLeft().x(),rect.bottomLeft().y() -Public_Function::getScaleSize(400/11));
    path.closeSubpath();
    return path;
}



/*************************************************************************
                                圆规右边腿绘制
*************************************************************************/
YuanGui_rightFoot::YuanGui_rightFoot(QObject *parent) : QObject(parent)
{
    rect = new QRectF;
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    rect->setWidth(Public_Function::getScaleSize(122));
    rect->setHeight(Public_Function::getScaleSize(400));
}

void YuanGui_rightFoot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor(229,231,237)));
    painter->drawPath(downShape());
    painter->save();
    upShape(painter);
    penPointShape(painter);
    penNibShape(painter);
    penHandShape(painter);
    painter->restore();
}

QRectF YuanGui_rightFoot::boundingRect() const
{
    return *rect;
}

void YuanGui_rightFoot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     mousestate =true;
    if(pointpath.contains(event->pos()))
    {
        num =1;
        emit sendRotatePressMessage();
    }
    else if(handpath.contains(event->pos()))
    {
        num =2;
        emit sendDragPressMessage(event->pos());
    }
}

void YuanGui_rightFoot::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mousestate)
    {
        if(num ==1)
        {
           emit  sendRotateMoveMessage(event->scenePos(),event->lastScenePos());
        }
        else if(num ==2)
        {
            emit sendDragMoveMessage(event->pos(),event->lastPos());
        }
    }
}

void YuanGui_rightFoot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(mousestate)
    {
        if(num ==1)
        {
           emit  sendRotateReleaseMessage();
        }
        else if(num ==2)
        {
            emit  sendDragReleaseMessage(event->pos());
        }
        num =0;
        mousestate =false;
    }
}

void YuanGui_rightFoot::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(pointpath.contains(event->pos())||handpath.contains(event->pos()))
    {
        this->setCursor(Qt::PointingHandCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

bool YuanGui_rightFoot::sceneEvent(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::TouchBegin:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            pointid =ev->touchPoints().at(0).id();
            mousestate =true;
           if(pointpath.contains(ev->touchPoints().at(0).pos()))
           {
               num =1;
               emit sendRotatePressMessage();
           }
           else if(handpath.contains(ev->touchPoints().at(0).pos()))
           {
               num =2;
               emit sendDragPressMessage(ev->touchPoints().at(0).pos());
           }
            return true;
            break;
        }
        case QEvent::TouchUpdate:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            foreach (QTouchEvent::TouchPoint tp, ev->touchPoints()) {
               if(tp.id() ==pointid)
               {
                   if(mousestate)
                   {
                       if(num ==1)
                       {
                          emit  sendRotateMoveMessage(ev->touchPoints().at(0).scenePos(),ev->touchPoints().at(0).lastScenePos());
                       }
                       else if(num ==2)
                       {
                           emit sendDragMoveMessage(ev->touchPoints().at(0).pos(),ev->touchPoints().at(0).lastPos());
                       }
                   }
               }
            }
            return true;
            break;
        }
        case QEvent::TouchEnd:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            foreach (QTouchEvent::TouchPoint tp, ev->touchPoints()) {
               if(tp.id() ==pointid)
               {
                   if(mousestate)
                   {
                       if(num ==1)
                       {
                          emit  sendRotateReleaseMessage();
                       }
                       else if(num ==2)
                       {
                           emit  sendDragReleaseMessage(ev->touchPoints().at(0).pos());
                       }
                       num =0;
                       mousestate =false;
                   }
               }
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

QPainterPath YuanGui_rightFoot::shape() const
{
    QPainterPath countpath;
    countpath += downpath;
    countpath += uppath;
    countpath += handpath;
    return countpath;
}

QPainterPath YuanGui_rightFoot::downShape()
{
    QPainterPath path;
    path.moveTo(rect->topLeft());
    path.lineTo(rect->bottomLeft());
    path.lineTo(Public_Function::getScaleSize(25),rect->bottomRight().y() -Public_Function::getScaleSize(400/11));
    path.lineTo(Public_Function::getScaleSize(25),0);
    path.closeSubpath();
    downpath.clear();
    downpath =path;
    return path;
}

void YuanGui_rightFoot::upShape(QPainter *painter)
{
    painter->translate(0,Public_Function::getScaleSize(400));
    painter->rotate(-60);
    painter->setBrush(QBrush(QColor(229,231,237)));
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.moveTo(0,0);
    path.quadTo(Public_Function::getScaleSize(30),Public_Function::getScaleSize(-16),Public_Function::getScaleSize(47),Public_Function::getScaleSize(-16));
    path.lineTo(Public_Function::getScaleSize(217),Public_Function::getScaleSize(-16));
    path.lineTo(Public_Function::getScaleSize(217),Public_Function::getScaleSize(16));
    path.lineTo(Public_Function::getScaleSize(47),Public_Function::getScaleSize(16));
    path.quadTo(Public_Function::getScaleSize(30),Public_Function::getScaleSize(16),0,0);
    painter->drawPath(path);
    uppath =path;
    QTransform transform;
    transform.translate(0, 400);
    transform.rotate(-60);
    uppath =transform.map(uppath);

}

void YuanGui_rightFoot::penPointShape(QPainter *painter)
{
    painter->setBrush(QBrush(QColor(255,0,0)));
    pointshape.clear();
    pointshape.moveTo(0,0);
    pointshape.quadTo(Public_Function::getScaleSize(30),Public_Function::getScaleSize(-16),Public_Function::getScaleSize(47),Public_Function::getScaleSize(-16));
    pointshape.lineTo(Public_Function::getScaleSize(47),Public_Function::getScaleSize(16));
    pointshape.quadTo(Public_Function::getScaleSize(30),Public_Function::getScaleSize(16),0,0);
    painter->drawPath(pointshape);

    QTransform transform_left;
    transform_left.translate(0, Public_Function::getScaleSize(400));
    transform_left.rotate(-60);
    pointpath =transform_left.map(pointshape);
}

void YuanGui_rightFoot::penNibShape(QPainter *painter)
{
    painter->setBrush(QBrush(QColor(70,71,73)));
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.moveTo(Public_Function::getScaleSize(10),Public_Function::getScaleSize(-6));
    path.quadTo(Public_Function::getScaleSize(30),Public_Function::getScaleSize(-16),Public_Function::getScaleSize(50),Public_Function::getScaleSize(-18));
    path.lineTo(Public_Function::getScaleSize(50),Public_Function::getScaleSize(18));
    path.quadTo(Public_Function::getScaleSize(30),Public_Function::getScaleSize(18),Public_Function::getScaleSize(10),Public_Function::getScaleSize(6));
    painter->drawPath(path);
}

void YuanGui_rightFoot::penHandShape(QPainter *painter)
{
    painter->setBrush(QBrush(QColor(229,231,237)));
    handshape.clear();
    handshape.moveTo(Public_Function::getScaleSize(70),0);
    handshape.lineTo(Public_Function::getScaleSize(70),Public_Function::getScaleSize(48));
    handshape.arcTo(Public_Function::getScaleSize(70),Public_Function::getScaleSize(25),Public_Function::getScaleSize(46),
                    Public_Function::getScaleSize(46),180,180);
    handshape.lineTo(Public_Function::getScaleSize(116),0);
    painter->drawPath(handshape);
    painter->setPen(QPen(QColor(198,199,202)));
    QPainterPath path;
    path.moveTo(Public_Function::getScaleSize(77),Public_Function::getScaleSize(16));
    path.lineTo(Public_Function::getScaleSize(77),Public_Function::getScaleSize(48));
    path.arcTo(Public_Function::getScaleSize(77),Public_Function::getScaleSize(30),
               Public_Function::getScaleSize(32),Public_Function::getScaleSize(32),180,180);
    path.lineTo(Public_Function::getScaleSize(109),Public_Function::getScaleSize(16));
    painter->drawPath(path);
    painter->translate(Public_Function::getScaleSize(93),Public_Function::getScaleSize(37));
    pendDragRect(painter);

    QTransform transform;
    transform.translate(0, Public_Function::getScaleSize(400));
    transform.rotate(-60);
    handpath =transform.map(handshape);
}

void YuanGui_rightFoot::pendDragRect(QPainter *painter)
{
    painter->setPen(QPen(QColor(127,138,142),4,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.moveTo(0,Public_Function::getScaleSize(-14));
    path.lineTo(Public_Function::getScaleSize(-6),Public_Function::getScaleSize(-8));
    path.lineTo(Public_Function::getScaleSize(6),Public_Function::getScaleSize(-8));
    path.lineTo(0,Public_Function::getScaleSize(-14));
    path.lineTo(0,Public_Function::getScaleSize(14));
    path.lineTo(Public_Function::getScaleSize(-6),Public_Function::getScaleSize(8));
    path.lineTo(Public_Function::getScaleSize(6),Public_Function::getScaleSize(8));
    path.lineTo(0,Public_Function::getScaleSize(14));
    painter->drawPath(path);
}


/*************************************************************************
                                圆规绞合处绘制
*************************************************************************/
YuanGui_hinge::YuanGui_hinge(QObject *parent) : QObject(parent)
{
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    rect =QRectF(0,0,Public_Function::getScaleSize(72),Public_Function::getScaleSize(166));
    moverect =QRectF(0,Public_Function::getScaleSize(84),Public_Function::getScaleSize(72),Public_Function::getScaleSize(82));
    closerect =QRectF(Public_Function::getScaleSize(11),0,Public_Function::getScaleSize(50),Public_Function::getScaleSize(50));
}

void YuanGui_hinge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing,true);
    closeShape(painter);
    headShape(painter);
    moveShape(painter);
    painter->save();
    painter->translate(moverect.center());
    arrowsShape(painter);
    painter->rotate(90);
    arrowsShape(painter);
    painter->restore();
}

QRectF YuanGui_hinge::boundingRect() const
{
    return rect;
}

void YuanGui_hinge::moveShape(QPainter *painter)
{
    painter->setBrush(QColor(109,111,119));
    painter->drawRoundedRect(moverect,Public_Function::getScaleSize(20),Public_Function::getScaleSize(20));
    update();
    painter->setPen(QPen(QColor(156,157,161),Public_Function::getScaleSize(2)));
    painter->drawEllipse(moverect.center(),Public_Function::getScaleSize(25),Public_Function::getScaleSize(25));
}

void YuanGui_hinge::closeShape(QPainter *painter)
{
    painter->setPen(QPen(QColor(109,111,119),2));
    painter->drawEllipse(closerect.center(),Public_Function::getScaleSize(25),Public_Function::getScaleSize(25));
    int w =closerect.width();
    int h =closerect.height();
    QPainterPath path;
    path.moveTo(closerect.topLeft().x() +27*w/100,closerect.topLeft().y() +27*h/100);
    path.lineTo(closerect.bottomRight().x() -27*w/100,closerect.bottomRight().y() -27*h/100);
    path.moveTo(closerect.bottomLeft().x() +27*w/100,closerect.bottomLeft().y() -27*h/100);
    path.lineTo(closerect.topRight().x() -27*w/100,closerect.topRight().y() +27*h/100);
    painter->drawPath(path);
}


void YuanGui_hinge::arrowsShape(QPainter *painter)
{
    painter->setPen(QPen(QColor(229,231,237),4,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.moveTo(0,Public_Function::getScaleSize(-20));
    path.lineTo(Public_Function::getScaleSize(-6),Public_Function::getScaleSize(-14));
    path.lineTo(Public_Function::getScaleSize(6),Public_Function::getScaleSize(-14));
    path.lineTo(0,Public_Function::getScaleSize(-20));
    path.lineTo(0,Public_Function::getScaleSize(20));
    path.lineTo(Public_Function::getScaleSize(-6),Public_Function::getScaleSize(14));
    path.lineTo(Public_Function::getScaleSize(6),Public_Function::getScaleSize(14));
    path.lineTo(0,Public_Function::getScaleSize(20));
    painter->drawPath(path);
}

void YuanGui_hinge::headShape(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor(229,231,237)));
    QPainterPath path;
    path.moveTo(Public_Function::getScaleSize(24),Public_Function::getScaleSize(56));
    path.lineTo(Public_Function::getScaleSize(24),Public_Function::getScaleSize(80));
    path.lineTo(Public_Function::getScaleSize(31),Public_Function::getScaleSize(80));
    path.lineTo(Public_Function::getScaleSize(31),Public_Function::getScaleSize(90));
    path.lineTo(Public_Function::getScaleSize(41),Public_Function::getScaleSize(90));
    path.lineTo(Public_Function::getScaleSize(41),Public_Function::getScaleSize(80));
    path.lineTo(Public_Function::getScaleSize(47),Public_Function::getScaleSize(80));
    path.lineTo(Public_Function::getScaleSize(47),Public_Function::getScaleSize(56));
    path.quadTo(Public_Function::getScaleSize(35),Public_Function::getScaleSize(52),Public_Function::getScaleSize(24),Public_Function::getScaleSize(56));
    painter->drawPath(path);
    headpath =path;
}

void YuanGui_hinge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(QLineF(moverect.center(),event->pos()).length() <=Public_Function::getScaleSize(25))
    {
        mousepress =true;
    }
    else if(QLineF(closerect.center(),event->pos()).length() <=Public_Function::getScaleSize(25))
    {
        emit sendCloseMessage();
    }
}

void YuanGui_hinge::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mousepress)
    {
        emit sendMoveMessage(event->screenPos() -event->lastScreenPos());
    }
}

void YuanGui_hinge::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    mousepress =false;
}

void YuanGui_hinge::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(QLineF(moverect.center(),event->pos()).length() <=Public_Function::getScaleSize(25))
    {
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(QLineF(closerect.center(),event->pos()).length() <=Public_Function::getScaleSize(25))
    {
        this->setCursor(Qt::PointingHandCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

bool YuanGui_hinge::sceneEvent(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::TouchBegin:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            pointid =ev->touchPoints().at(0).id();
            if(QLineF(moverect.center(),ev->touchPoints().at(0).pos()).length() <=Public_Function::getScaleSize(25))
            {
                mousepress =true;
            }
            else if(QLineF(closerect.center(),ev->touchPoints().at(0).pos()).length() <=Public_Function::getScaleSize(25))
            {
                emit sendCloseMessage();
            }
            return true;
            break;
        }
        case QEvent::TouchUpdate:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            foreach (QTouchEvent::TouchPoint tp, ev->touchPoints()) {
               if(tp.id() ==pointid)
               {
                   if(mousepress)
                   {
                        emit sendMoveMessage(ev->touchPoints().at(0).screenPos() -ev->touchPoints().at(0).lastScreenPos());
                   }
               }
            }
            return true;
            break;
        }
        case QEvent::TouchEnd:
        {
            QTouchEvent *ev =static_cast<QTouchEvent*>(event);
            foreach (QTouchEvent::TouchPoint tp, ev->touchPoints()) {
               if(tp.id() ==pointid)mousepress =false;;
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

QPainterPath YuanGui_hinge::shape() const
{
    QPainterPath path;
    path =headpath;
    path.addRect(moverect);
    path.addEllipse(closerect.center(),Public_Function::getScaleSize(25),Public_Function::getScaleSize(25));
    return path;
}


/*************************************************************************
                                圆规各部件组装
*************************************************************************/
CustomItem_YuanGui::CustomItem_YuanGui(QObject *parent) : QObject(parent)
  {
      rect =QRectF(0,0,Public_Function::getScaleSize(72),Public_Function::getScaleSize(82));
      left = new YuanGui_leftFoot();
      right = new YuanGui_rightFoot();
      zhuanzhou = new YuanGui_hinge();
      left->setParentItem(this);
      right->setParentItem(this);
      zhuanzhou->setParentItem(this);
      left->setTransformOriginPoint(Public_Function::getScaleSize(25),Public_Function::getScaleSize(400));
      right->setTransformOriginPoint(0,0);
      rect.moveTo(0,Public_Function::getScaleSize(84));
      left->moveBy(rect.center().x() -Public_Function::getScaleSize(25),rect.center().y());
      right->moveBy(rect.center().x(),rect.center().y());
      mouseDraw();
      connectInit();
  }

  void CustomItem_YuanGui::connectInit()
  {
      connect(right,&YuanGui_rightFoot::sendDragMoveMessage,this,&CustomItem_YuanGui::mouseDraw);

      connect(right,&YuanGui_rightFoot::sendRotatePressMessage,this,[=](){rotateangle =this->rotation(); rotatechange =0;});
      connect(right,&YuanGui_rightFoot::sendRotateMoveMessage,this,&CustomItem_YuanGui::mouseRotate);
      connect(right,&YuanGui_rightFoot::sendRotateReleaseMessage,this,[=](){
          qreal r =qAbs(getMoveCenter().x() -36)*2;
          int num =(int)rotate%360;
          emit sendarc52(mapToScene(QPointF(Public_Function::getScaleSize(36),Public_Function::getScaleSize(524))),r,-num,rotatechange);
          rotate =rotatechange +rotate;
          rotatechange =0;
          });

      connect(zhuanzhou,&YuanGui_hinge::sendMoveMessage,this,[=](QPointF dot){this->moveBy(dot.x(),dot.y());});
      connect(zhuanzhou,&YuanGui_hinge::sendCloseMessage,this,[=](){emit deleteitem5(this);});
  }

  void CustomItem_YuanGui::mouseDraw(QPointF dot1, QPointF dot2)
  {
      float num = (dot1.x() -dot2.x())/Public_Function::getScaleSize(4);
      angle +=num;
      if(angle <0)angle =0;
      if(angle >170)angle =170;
      left->setRotation(angle/2);
      rect.moveTo(getMoveCenter().x() -rect.width()/2 ,getMoveCenter().y() -rect.height()/2);
      zhuanzhou->setPos(rect.center().x() -Public_Function::getScaleSize(36),rect.center().y() -Public_Function::getScaleSize(124));
      right->setPos(rect.center().x(),rect.center().y());
      right->setRotation(-angle/2);
      update();
  }

  void CustomItem_YuanGui::mouseRotate(QPointF dot1, QPointF dot2)
  {
      getRotate(mapToScene(QPointF(Public_Function::getScaleSize(36),Public_Function::getScaleSize(524))),dot1,dot2);
      this->setTransformOriginPoint(QPointF(Public_Function::getScaleSize(36),Public_Function::getScaleSize(524)));
      this->setRotation(rotate +rotatechange);
      qreal r =qAbs(getMoveCenter().x() -Public_Function::getScaleSize(36))*2;
      emit sendarc51(mapToScene(QPointF(Public_Function::getScaleSize(36),Public_Function::getScaleSize(524))),r,-rotate,rotatechange);
  }

  void CustomItem_YuanGui::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
  {
      Q_UNUSED(option);
      Q_UNUSED(widget);
  }

  QRectF CustomItem_YuanGui::boundingRect() const
  {
      QRectF rect(0,0,Public_Function::getScaleSize(-100),Public_Function::getScaleSize(100));
      return rect;
  }


  QPointF CustomItem_YuanGui::getMoveCenter()
  {
      int r =Public_Function::getScaleSize(400);
      QPointF dot;
      dot.setX(Public_Function::getScaleSize(36) +r*cos((-90 +angle/2)*M_PI/180));
      dot.setY(Public_Function::getScaleSize(524) +r*sin((-90 +angle/2)*M_PI/180));
      return dot;
  }


  void CustomItem_YuanGui::getRotate(QPointF cen, QPointF second, QPointF first)
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
      if(__isnan(angleAMB) == 1)return;
      angleAMB =angleAMB;
      if ((second.x() -first.x()) *(cen.y() -first.y()) -(second.y() -first.y()) *(cen.x() -first.x()) <0)
      {
          angleAMB = -angleAMB;
      }
      rotatechange +=angleAMB;
  }

