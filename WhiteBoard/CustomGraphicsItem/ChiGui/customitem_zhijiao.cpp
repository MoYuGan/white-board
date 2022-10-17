#include "customitem_zhijiao.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <qmath.h>
#include <QDesktopWidget>
#include <QApplication>
#include "Public/public_function.h"
#include "Extern/extern.h"

CustomItem_ZhiJiao::CustomItem_ZhiJiao(QObject *parent) : QObject(parent)
{
    this->setAcceptHoverEvents(true);//使用鼠标悬停
    this->setAcceptTouchEvents(true);
    m_rect = new QRect(0,0,adapt(300*san),adapt(300));
    drag_rect = QRect(0,0,adapt(Iconlength),adapt(Iconlength));
    close_rect = QRect(0,0,adapt(Iconlength),adapt(Iconlength));
    rotate_rect = QRect(0,0,adapt(Iconlength),adapt(Iconlength));
    mm = adapt(4);
    this->setTransformOriginPoint(m_rect->bottomLeft().x() +adapt(deviation),m_rect->bottomLeft().y() -adapt(deviation));
}

QPainterPath CustomItem_ZhiJiao::outDrawArea()
{
    QPainterPath path;
    path.moveTo(m_rect->topLeft().x() +adapt(deviation),m_rect->topLeft().y() +adapt(deviation/san));
    path.lineTo(m_rect->bottomLeft().x()+adapt(deviation),m_rect->bottomLeft().y() -adapt(deviation));
    path.lineTo(m_rect->bottomRight().x() -adapt(san*deviation),m_rect->bottomRight().y() -adapt(deviation));
    path.closeSubpath();
    return path;
}

QPainterPath CustomItem_ZhiJiao::inDrawArea()
{
    QPainterPath path;
    path.moveTo(m_rect->topLeft().x() +adapt(deviation +mheight),m_rect->topLeft().y() +adapt(deviation/san +san*mheight));
    path.lineTo(m_rect->bottomLeft().x()+adapt(deviation +mheight),m_rect->bottomLeft().y() -adapt(deviation +mheight));
    path.lineTo(m_rect->bottomRight().x() -adapt(san*(mheight +deviation) +2*mheight),m_rect->bottomRight().y() -adapt(deviation +mheight));
    path.closeSubpath();
    return path;
}

QPainterPath CustomItem_ZhiJiao::getIconrect(QString str)
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
          path.moveTo(drag_rect.topLeft().x() +25.7*adapt(Iconlength)/50,drag_rect.topLeft().y() +13.8*adapt(Iconlength)/50);
          path.lineTo(drag_rect.topLeft().x() +32.5*adapt(Iconlength)/50,drag_rect.topLeft().y() +12*adapt(Iconlength)/50);
          path.lineTo(drag_rect.topLeft().x() +34.3*adapt(Iconlength)/50,drag_rect.topLeft().y() +18.4*adapt(Iconlength)/50);
          path.closeSubpath();
          path.moveTo(drag_rect.topLeft().x() +30*adapt(Iconlength)/50,drag_rect.topLeft().y() +16.3*adapt(Iconlength)/50);
          path.lineTo(drag_rect.topLeft().x() +20*adapt(Iconlength)/50,drag_rect.topLeft().y() +33.7*adapt(Iconlength)/50);
          path.moveTo(drag_rect.topLeft().x() +17.5*adapt(Iconlength)/50,drag_rect.topLeft().y() +38*adapt(Iconlength)/50);
          path.lineTo(drag_rect.topLeft().x() +15.7*adapt(Iconlength)/50,drag_rect.topLeft().y() +31.2*adapt(Iconlength)/50);
          path.lineTo(drag_rect.topLeft().x() +24.3*adapt(Iconlength)/50,drag_rect.topLeft().y() +36.2*adapt(Iconlength)/50);
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

QPainterPath CustomItem_ZhiJiao::test()
{
    QPainterPath path;
    path.moveTo(m_rect->topLeft());
    path.lineTo(m_rect->bottomLeft());
    path.lineTo(m_rect->bottomRight());
    path.lineTo(m_rect->bottomRight().x(),m_rect->bottomRight().y() -adapt(deviation));
    path.lineTo(m_rect->topLeft().x() +Public_Function::getScaleSize(deviation +deviation/2),m_rect->topLeft().y());
    path.closeSubpath();
    return path;
}

void CustomItem_ZhiJiao::getRectStyle(QPoint dot)
{
    mousepos =0;
    if(getMousePos(dot)  ==true);
    else if(drag_rect.contains(dot,true))
    {
        mousepos|=0x0010;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(close_rect.contains(dot,true))
    {
        mousepos|=0x0020;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(rotate_rect.contains(dot,true))
    {
        mousepos|=0x0040;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if(move_rect.containsPoint(dot,Qt::WindingFill))
    {
        mousepos|=0x0080;
        this->setCursor(Qt::SizeAllCursor);
    }
    else
    {
        mousepos =0x0000;
        this->setCursor(Qt::ArrowCursor);
    }
    update();
}

QPointF CustomItem_ZhiJiao::getpoint(QPointF p1, QPointF p2, QPointF p3)
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

bool CustomItem_ZhiJiao::getMousePos(QPoint dot)
{
    //if(ToolType::Pen !=g_ToolType)return false;
    if(lineup_rect.containsPoint(dot,Qt::WindingFill))
        {
            mousepos|=0x0001;
            this->setCursor(Qt::PointingHandCursor);
        }
    if(linedown_rect.contains(dot,true))
        {
            mousepos|=0x0002;
            this->setCursor(Qt::PointingHandCursor);
        }
    if(lineleft_rect.contains(dot,true))
        {
            mousepos|=0x0004;
            this->setCursor(Qt::PointingHandCursor);
        }

    if((mousepos&0x000F) !=0)return true;
    else return false;
}


QRectF CustomItem_ZhiJiao::boundingRect() const
{
    return *m_rect;
}

QPainterPath CustomItem_ZhiJiao::shape() const
{
    QPainterPath path;
    path.moveTo(m_rect->topLeft());
    path.lineTo(m_rect->bottomLeft());
    path.lineTo(m_rect->bottomRight());
    path.lineTo(m_rect->bottomRight().x(),m_rect->bottomRight().y() -Public_Function::getScaleSize(deviation));
    path.lineTo(m_rect->topLeft().x() +Public_Function::getScaleSize(deviation +deviation/2),m_rect->topLeft().y());
    path.closeSubpath();
    return path;
}

void CustomItem_ZhiJiao::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //painter->setPen(QPen(QColor(Qt::red),adapt(3)));
    //painter->drawRect(*m_rect);
    //painter->drawPath(test());

    painter->setPen(Qt::NoPen);
    QPainterPath pathIn,pathIcon;
    QPainterPath pathOut;
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor(216,216,216,150)));
    pathOut =outDrawArea();
    painter->drawPath(pathOut);
    painter->setBrush(QBrush(QColor(246,246,246,150)));
    pathIn = inDrawArea();
    painter->drawPath(pathIn);
    painter->setPen(QPen(QColor(216,216,216)));
    lineleft_rect =QRect(m_rect->topLeft().x(),m_rect->topLeft().y() +adapt(san/3*deviation),adapt(deviation +mheight),m_rect->height() -adapt(san/3*deviation));
    linedown_rect=QRect(m_rect->topLeft().x(),m_rect->bottomLeft().y() -adapt(deviation +mheight),m_rect->width() -adapt(san*deviation),adapt(deviation +mheight));
    //painter->drawRect(lineleft_rect);
    //painter->drawRect(linedown_rect);
    close_rect.moveTo(m_rect->topLeft().x() +adapt(deviation +mheight +(sqrt(2) -1)/2*Iconlength),m_rect->topLeft().y() +adapt(deviation +mheight+Iconlength));
    painter->drawEllipse(close_rect);
    rotate_rect.moveTo(m_rect->bottomRight().x() -adapt((1+san)*(deviation +mheight) +3*Iconlength),m_rect->bottomLeft().y() -adapt(deviation +mheight +(sqrt(2) +1)/2*Iconlength));
    painter->drawEllipse(rotate_rect);
    drag_rect.moveTo((close_rect.topLeft()+rotate_rect.topLeft())/2);
    painter->drawEllipse(drag_rect);
    lineup_rect.setPoints(4,m_rect->topLeft().x() +adapt(deviation -mheight/2),m_rect->topLeft().y() +adapt(deviation/san +san/2*mheight),
                            m_rect->topLeft().x() +adapt(deviation +deviation/2),m_rect->topLeft().y() +adapt(deviation/san -san/2*deviation),
                            m_rect->bottomRight().x() -adapt(san*deviation -deviation/2),m_rect->bottomRight().y() -adapt(deviation +san/2*deviation),
                            m_rect->bottomRight().x() -adapt(san*deviation +mheight/2),m_rect->bottomRight().y() -adapt(deviation -san/2*mheight));
    //painter->drawPolygon(lineup_rect);
    move_rect.setPoints(3,m_rect->topLeft().x() +adapt(deviation +mheight),m_rect->topLeft().y() +adapt(deviation/san +san*mheight),
                        m_rect->bottomLeft().x()+adapt(deviation +mheight),m_rect->bottomLeft().y() -adapt(deviation +mheight),
                        m_rect->bottomRight().x() -adapt(san*(mheight +deviation) +2*mheight),m_rect->bottomRight().y() -adapt(deviation +mheight));

    //painter->drawPolygon(move_rect);
    if((mousepos&0x00F0) == 0x0010)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(drag_rect);
    }
    else if((mousepos&0x00F0) == 0x0020)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(close_rect);
    }
    else if((mousepos&0x00F0) == 0x0040)
    {
        painter->setBrush(QColor(216,230,233));
        painter->drawEllipse(rotate_rect);
    }
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QColor(127,138,142),adapt(4),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    pathIcon = getIconrect("close_rect");
    painter->drawPath(pathIcon);
    pathIcon = getIconrect("drag_rect");
    painter->drawPath(pathIcon);
    pathIcon = getIconrect("rotate_rect");
    painter->drawPath(pathIcon);
    painter->setPen(QPen(QColor(127,138,142),adapt(6),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter->drawPoint(rotate_rect.center());
    painter->setPen(QPen(QColor(160,161,164),adapt(2)));
    painter->translate(QPoint(m_rect->bottomLeft().x() +adapt(deviation +2),m_rect->bottomLeft().y() -adapt(deviation +mheight)));
    for(int i =0; i <(m_rect->height() -adapt(deviation +mheight +san*mheight +deviation/san))/mm; i++)
    {
        if(i ==0)
        {
           painter->drawLine(QPoint(0,-i*mm),QPoint(adapt(mheight)*0.7 ,-i*mm));
        }
        else if(i % 10 == 0)
        {
            painter->drawLine(QPoint(0,-i*mm),QPoint(adapt(mheight)*0.7 ,-i*mm));
        }
        else if(i % 5 == 0)
        {
            painter->drawLine(QPoint(0,-i*mm),QPoint(adapt(mheight)*0.5 ,-i*mm));
        }
        else {
            painter->drawLine(QPoint(0,-i*mm),QPoint(adapt(mheight)*0.3 ,-i*mm));
        }
    }
    painter->translate(-QPoint(m_rect->bottomLeft().x() +adapt(deviation +2),m_rect->bottomLeft().y() -adapt(deviation +mheight)));
    painter->translate(QPoint(m_rect->bottomLeft().x() +adapt(deviation +mheight),m_rect->bottomLeft().y() -adapt(deviation +2)));
    for(int i= 0; i < (m_rect->width() -adapt((san +1)*(deviation +mheight) +2*mheight))/mm; i++)
    {
        if(i ==0)
        {
           painter->drawLine(QPoint(i*mm ,0),QPoint(i*mm ,-adapt(mheight)*0.7));
        }
        else if(i % 10 == 0)
        {
            painter->drawLine(QPoint(i*mm ,0),QPoint(i*mm ,-adapt(mheight)*0.7));
        }
        else if(i % 5 == 0)
        {
            painter->drawLine(QPoint(i*mm ,0),QPoint(i*mm ,-adapt(mheight)*0.5));
        }
        else {
            painter->drawLine(QPoint(i*mm ,0),QPoint(i*mm ,-adapt(mheight)*0.3));
        }
    }
    painter->translate(-QPoint(m_rect->bottomLeft().x() +adapt(deviation +mheight),m_rect->bottomLeft().y() -adapt(deviation +2)));
    painter->save();
    painter->translate(QPoint(m_rect->topLeft().x() +adapt(deviation +mheight +san/3*mheight),m_rect->topLeft().y() +adapt(deviation +8)));
    painter->rotate(30);
    painter->setPen(QPen(QColor(160,161,164),adapt(2)));
    int length = sqrt((m_rect->width() -adapt((san+1)*(mheight +deviation) +2*mheight))*(m_rect->width() -adapt((san+1)*(mheight +deviation) +2*mheight))+
                      (m_rect->height() -adapt((1 +san)*mheight +deviation +deviation/san))*(m_rect->height() -adapt((1 +san)*mheight +deviation +deviation/san)));
    for(int i =0; i < length/mm; i++)
    {
        if(i ==0)
        {
           painter->drawLine(QPoint(i*mm,0),QPoint(i*mm,adapt(mheight)*0.7));
        }
        else if(i %10 == 0)
        {
            painter->drawLine(QPoint(i*mm,0),QPoint(i*mm,adapt(mheight)*0.7));
        }
        else if(i %5 == 0)
        {
            painter->drawLine(QPoint(i*mm,0),QPoint(i*mm,adapt(mheight)*0.5));
        }
        else {
            painter->drawLine(QPoint(i*mm,0),QPoint(i*mm,adapt(mheight)*0.3));
        }
    }
    painter->restore();
    painter->setPen(QPen(QColor(127,138,142)));
    int rotatenum;
    if(change_angle <= 0)
    {
        rotatenum = abs(change_angle);
        if(rotatenum > 180)
        {
           rotatenum -= 360;
        }
    }
    else
    {
      rotatenum =-change_angle;
      if(rotatenum < -180)
      {
         rotatenum += 360;
      }
    }
    painter->setFont(Public_Function::getFont(26));
    QRect re =QRect(m_rect->bottomLeft().x() +adapt(deviation +mheight +5),m_rect->bottomRight().y() -adapt(deviation +mheight +painter->font().pixelSize() +5),adapt(m_rect->width()/2),adapt(painter->font().pixelSize() +5));
    if(change_lenght !=0)
    {
        int m =change_lenght/10;
        int n =change_lenght%10;
        QString title = QString("%1.%2cm").arg(m).arg(n);
        painter->drawText(re,Qt::AlignLeft|Qt::AlignVCenter,title);
    }
    else if((showrotate ==1)&&(change_lenght ==0))
    {
       QString title = QString("%1°").arg(rotatenum);
       painter->drawText(re,Qt::AlignLeft|Qt::AlignVCenter,title);
    }
}


void CustomItem_ZhiJiao::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    this->setCursor(Qt::ArrowCursor);
}

void CustomItem_ZhiJiao::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    getRectStyle(QPoint(event->pos().x(),event->pos().y()));
}

void CustomItem_ZhiJiao::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressEvent(event->pos(),event->scenePos());
}

void CustomItem_ZhiJiao::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    moveEvent(event->pos(),event->scenePos());
}

void CustomItem_ZhiJiao::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    releaseEvent(event->pos(),event->scenePos());
}

void CustomItem_ZhiJiao::getrotate(QPointF cen, QPointF second, QPointF first)
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

int CustomItem_ZhiJiao::adapt(int num)
{
    return Public_Function::getScaleSize(num);
}

QSize CustomItem_ZhiJiao::adapt(int m, int n)
{
    return Public_Function::getScaleSize(m,n);
}

bool CustomItem_ZhiJiao::sceneEvent(QEvent *event)
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

void CustomItem_ZhiJiao::pressEvent(QPointF pos, QPointF scenePos)
{
    getRectStyle(pos.toPoint());
    mousestate = true;
    if((mousepos&0x00F0) == 0x0010)//拉伸
    {
        start[0] = pos;
        mrect = *m_rect;
        xx = m_rect->width();
        yy = m_rect->height();
    }
    else if((mousepos&0x00F0) == 0x0020)//删除
    {
        emit deleteitem3(this);
    }
    else if((mousepos&0x00F0) == 0x0040)//旋转
    {
      start[0] = scenePos;
      showrotate =1;
      change_lenght =0;
    }
    else if((mousepos&0x00F0) == 0x0080)//移动
    {
      start[0] = scenePos;
      store = this->pos();
      change_lenght =0;
      showrotate =2;
    }

    if((mousepos&0x0004) == 0x0004)//左检测区
    {
      start[1] =mapToScene(QPointF(adapt(deviation) -g_PenSize/2,pos.y()));
      store = pos;
      showrotate =1;
    }

    if((mousepos&0x0002) == 0x0002)//下检测区
    {
      start[2] =mapToScene(QPointF(pos.x(),m_rect->bottomLeft().y() -adapt(deviation) +g_PenSize/2));
      store = pos;
      showrotate =1;
    }

    if((mousepos&0x0001) == 0x0001)//上检测区
    {
      start[3] = getpoint(QPointF(m_rect->topLeft().x() +adapt(deviation),m_rect->topLeft().y() +adapt(deviation)/san) ,
                       QPointF(m_rect->bottomRight().x() -san*adapt(deviation),m_rect->bottomRight().y() -adapt(deviation)),
                       pos);
      start[3].setX(start[3].x() +g_PenSize/4);
      start[3].setY(start[3].y() -0.866*g_PenSize/2);
      start[3] = mapToScene(start[3]);
      store = pos;
      showrotate =1;
    }
    else
    {
        ;
    }
}

void CustomItem_ZhiJiao::moveEvent(QPointF pos, QPointF scenePos)
{
    if((mousepos&0x00F0) == 0x0010)
    {
        QRect rrect;
        if(yy +start[0].y() -pos.y() < adapt(300))return;
        rrect =QRect(mrect.topLeft().x(), mrect.topLeft().y() +pos.y() -start[0].y(),
                     xx +san*(start[0].y() -pos.y()),yy +start[0].y() -pos.y());
        *m_rect = rrect;
        update();
        emit refresh();
    }
    else if((mousepos&0x00F0) == 0x0040)
    {
        getrotate(mapToScene(m_rect->bottomLeft()), scenePos, start[0]);
    }
    else if((mousepos&0x00F0) == 0x0080)
    {
        QPointF dot;
        dot.setX(store.x() +scenePos.x() -start[0].x());
        dot.setY(store.y() +scenePos.y() -start[0].y());
        this->setPos(dot);
    }
    else if((mousepos&0x000F) == 0x0006)
    {
        num++;
        if(num ==5){
            num =0;
            if(abs((pos -store).x()) >=abs((pos -store).y()))
                 mousepos =0x0002;
            else
                 mousepos =0x0004;
        }
    }
    else if((mousepos&0x000F) == 0x0005)
    {
        num++;
        if(num ==5){
            num =0;
            if(abs((pos -store).x()) >=abs((pos -store).y()))
                 mousepos =0x0001;
            else
                 mousepos =0x0004;
        }
    }
    else if((mousepos&0x000F) == 0x0004)
    {
        float number = abs((pos.y() -store.y())/mm);
        change_lenght = number >= ((int)number +0.5)?(int)number +1:(int)number;
        emit sendline31(start[1],mapToScene(QPointF(adapt(deviation) -g_PenSize/2,pos.y())));
    }
    else if((mousepos&0x000F) == 0x0003)
    {
        num++;
        if(num ==5){
            num =0;
            if(abs((pos -store).x()) >=abs((pos -store).y()))
                 mousepos =0x0002;
            else
                 mousepos =0x0001;
        }
    }
    else if((mousepos&0x000F) == 0x0002)
    {
        float number = abs((pos.x() -store.x())/mm);
        change_lenght = number >= ((int)number +0.5)?(int)number +1:(int)number;
        emit sendline31(start[2],mapToScene(QPointF(pos.x(),m_rect->bottomLeft().y() -adapt(deviation) +g_PenSize/2)));
    }
    else if((mousepos&0x000F) == 0x0001)
    {
        qreal length = sqrt((pos.x() -store.x())*(pos.x() -store.x()) +
                            (pos.y() -store.y())*(pos.y() -store.y()));
        float number = length/mm;
        change_lenght = number >= ((int)number +0.5)?(int)number +1:(int)number;
        end = getpoint(QPointF(m_rect->topLeft().x() +adapt(deviation),m_rect->topLeft().y() +adapt(deviation)/san) ,
                         QPointF(m_rect->bottomRight().x() -san*adapt(deviation),m_rect->bottomRight().y() -adapt(deviation)),
                         pos);
        end.setX(end.x() +g_PenSize/4);
        end.setY(end.y() -0.866*g_PenSize/2);
        end = mapToScene(end);
        emit sendline31(start[3],end);
    }
    update();
}

void CustomItem_ZhiJiao::releaseEvent(QPointF pos, QPointF scenePos)
{
    if((mousepos&0x00F0) == 0x0040)
    {
        if((scenePos.x() !=start[0].x())||((scenePos.y()!=start[0].y())))
        {
            mousestate =false;
            getrotate(mapToScene(m_rect->bottomLeft()), scenePos, start[0]);
        }
    }
    else if((mousepos&0x00F0) == 0x0010)
    {
        this->setTransformOriginPoint(m_rect->bottomLeft().x() +adapt(deviation),m_rect->bottomLeft().y() -adapt(deviation));
        this->prepareGeometryChange();
    }
    else if((mousepos&0x000F) == 0x0004)
    {
        emit sendline32(start[1],mapToScene(QPointF(adapt(deviation) -g_PenSize/2,pos.y())));
    }
    else if((mousepos&0x000F) == 0x0002)
    {
        emit sendline32(start[2],mapToScene(QPointF(pos.x(),m_rect->bottomLeft().y() -adapt(deviation) +g_PenSize/2)));
    }
    else if((mousepos&0x000F) == 0x0001)
    {
        end = getpoint(QPointF(m_rect->topLeft().x() +adapt(deviation),m_rect->topLeft().y() +adapt(deviation)/san) ,
                         QPointF(m_rect->bottomRight().x() -san*adapt(deviation),m_rect->bottomRight().y() -adapt(deviation)),
                         pos);
        end.setX(end.x() +g_PenSize/4);
        end.setY(end.y() -0.866*g_PenSize/2);
        end = mapToScene(end);
        emit sendline32(start[3],end);
    }
    mousestate =false;
    mousepos &=0x0000;
}
