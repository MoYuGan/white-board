#include "cubeitem.h"
#include <QDebug>
CubeItem::CubeItem(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{

}

void CubeItem::drawItemPath(QPainterPath inpath1, QPainterPath outpath1)
{
    inpath =inpath1;
    outpath =outpath1;
    update();
}

//QPainterPath CubeItem::shape() const
//{
//    QPainterPathStroker stroker;
//    int checkWidth = this->pen().width();
//    //检测范围至少10个像素点（1920分辨率下）
//    checkWidth > Public_Function::getScaleSize(10) ? checkWidth : Public_Function::getScaleSize(10);
//    stroker.setWidth(checkWidth);
//    return stroker.createStroke(outpath);
//}

QRectF CubeItem::boundingRect() const
{
    return QRectF(0,0,1920,1080);
}

void CubeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(this->pen().color(),this->pen().width(),Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPath(inpath);
    painter->setPen(QPen(this->pen().color(),this->pen().width(),Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPath(outpath);

    painter->drawRect(100,100,500,500);
}
