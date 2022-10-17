#ifndef GRAPHIC_H
#define GRAPHIC_H

/*
*   图形类
*/

#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <math.h>
#include <QtDebug>


class GraphicsPath
{
    GraphicsPath() {}
public:
    //获取直线
    static QPainterPath getLine(QPointF pointStart, QPointF pointEnd)
    {
        QPainterPath path;
        path.moveTo(pointStart);
        path.lineTo(pointEnd);
        return path;
    }

    //获取箭头
    static QPainterPath getArrow(QPointF pointStart, QPointF pointEnd, qreal arrowSize)
    {
        QPainterPath path;
        path.moveTo(pointStart);
        path.lineTo(pointEnd);

        QLineF line(pointStart, pointEnd);
        qreal angle = std::atan2(-line.dy(), line.dx());
        arrowSize = arrowSize*10;
        QPointF arrowP1 = line.p2() - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

        path.lineTo(arrowP1);
        path.moveTo(pointEnd);
        path.lineTo(arrowP2);
        return path;
    }

    //获取双箭头
    static QPainterPath getDoubleArrow(QPointF pointStart, QPointF pointEnd, qreal arrowSize)
    {
        QPainterPath path;
        path.moveTo(pointStart);
        path.lineTo(pointEnd);

        QLineF line(pointStart, pointEnd);
        qreal angle = std::atan2(-line.dy(), line.dx());
        arrowSize = arrowSize*10;
        QPointF arrowP1 = line.p2() - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);
        QPointF arrowP3 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP4 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

        path.lineTo(arrowP1);
        path.moveTo(pointEnd);
        path.lineTo(arrowP2);
        path.moveTo(pointStart);
        path.lineTo(arrowP3);
        path.moveTo(pointStart);
        path.lineTo(arrowP4);
        return path;
    }

    //获取圆
    static QPainterPath getCircular(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        qreal width = drawRect.width();
        qreal height = drawRect.height();
        qreal minSize = qMin(qAbs(width), qAbs(height));
        qreal XSize = minSize;
        qreal YSize = minSize;
        if (width < 0)
            XSize = -minSize;
        if (height < 0)
            YSize = -minSize;
        path.addEllipse(drawRect.x(), drawRect.y(), XSize, YSize);

        //将曲线转换成用直线表示
        QPolygonF polygonf = QPolygonF(path.toFillPolygon());
        QPainterPath newPath;
        newPath.addPolygon(polygonf);

        return newPath;
    }

    //获取椭圆
    static QPainterPath getEllipse(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        qreal width = drawRect.width();
        qreal height = drawRect.height();
        path.addEllipse(drawRect.x(), drawRect.y(), width, height);
        //将曲线转换成用直线表示
        QPolygonF polygonf = QPolygonF(path.toFillPolygon());
        QPainterPath newPath;
        newPath.addPolygon(polygonf);
        return newPath;
    }

    //获取矩形
    static QPainterPath getRectangle(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        path.addRect(drawRect);
        return path;
    }

    //获取圆角矩形
    static QPainterPath getRoundedRectangle(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        path.addRoundedRect(drawRect, 10, 10);
        return path;
    }

    //获取平行四边形
    static QPainterPath getParallelogram(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        qreal width = drawRect.width();
        qreal height = drawRect.height();
        path.moveTo(drawRect.x() + width *5/11, drawRect.y());
        path.lineTo(drawRect.x() ,drawRect.y() + height);
        path.lineTo(drawRect.x() + width *6/11, drawRect.y() + height);
        path.lineTo(drawRect.x() + width ,drawRect.y());
        path.closeSubpath();
        return path;
    }

    //获取菱形
    static QPainterPath getDiamond(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        path.moveTo(drawRect.topLeft().x(), drawRect.center().y());
        path.lineTo(drawRect.center().x(), drawRect.topLeft().y());
        path.lineTo(drawRect.topRight().x(), drawRect.center().y());
        path.lineTo(drawRect.center().x(), drawRect.bottomLeft().y());
        path.closeSubpath();
        return path;
    }

    //获取梯形
    static QPainterPath getTrapezoid(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        qreal width = drawRect.width();
        qreal height = drawRect.height();
        path.moveTo(drawRect.x() + width/4, drawRect.y() + height/10);
        path.lineTo(drawRect.x() + width/10, drawRect.y() + height*3/4);
        path.lineTo(drawRect.x() + width*9/10, drawRect.y() + height*3/4);
        path.lineTo(drawRect.x() + width*3/4, drawRect.y() + height/10);
        path.closeSubpath();
        return path;
    }

    //获取扇形
    static QPainterPath getFan(QPointF pointStart, QPointF pointEnd)
    {
        QRectF rect = QRectF(pointStart, pointEnd);
//        QPainterPath path;
//        path.moveTo(drawRect.topRight());
//        path.lineTo(drawRect.bottomRight());
//        path.lineTo(drawRect.bottomLeft());
//        QRectF cirRect = QRectF(drawRect.topLeft(), QPointF(drawRect.bottomRight().x() + drawRect.width(),
//                                                            drawRect.bottomRight().y() + drawRect.height()));
//        path.arcMoveTo(cirRect, 180);
//        path.arcTo(cirRect, 180, -90);
        QRectF drawRect = QRectF(rect.topLeft(), QPointF(rect.bottomRight().x() + rect.width(),
                                                         rect.bottomRight().y() + rect.height()));
        QPainterPath path;
        path.moveTo(drawRect.center());
        path.arcTo(drawRect, 90, 90);
        path.closeSubpath();
        return path;
    }

    //获取三角形
    static QPainterPath getTriangle(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;

        qreal width = drawRect.width();
        qreal height = drawRect.height();
        path.moveTo(drawRect.x() + width/2, drawRect.y());
        path.lineTo(drawRect.x() , drawRect.y() + height);
        path.lineTo(drawRect.x() + width, drawRect.y() + height);
        path.closeSubpath();

        return path;
    }

    //获取直角三角形
    static QPainterPath getRightTriangle(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        path.moveTo(drawRect.topLeft());
        path.lineTo(drawRect.bottomLeft());
        path.lineTo(drawRect.bottomRight());
        path.closeSubpath();

        return path;
    }

    //获取五边形
    static QPainterPath getPentagon(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        qreal width = drawRect.width();
        qreal height = drawRect.height();
        path.moveTo(drawRect.x() + width/2, drawRect.y());
        path.lineTo(drawRect.x() , drawRect.y() + height*11/32);
        path.lineTo(drawRect.x() + width*7/40, drawRect.y() + height);
        path.lineTo(drawRect.x() + width*33/40, drawRect.y() + height);
        path.lineTo(drawRect.x() + width, drawRect.y() + height*11/32);
        path.closeSubpath();
        return path;
    }

    //获取六边形
    static QPainterPath getHexagon(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        qreal width = drawRect.width();
        qreal height = drawRect.height();
        path.moveTo(drawRect.x() + width/4, drawRect.y());
        path.lineTo(drawRect.x() , drawRect.y() + height/2);
        path.lineTo(drawRect.x() + width/4, drawRect.y() + height);
        path.lineTo(drawRect.x() + width*3/4, drawRect.y() + height);
        path.lineTo(drawRect.x() + width, drawRect.y() + height/2);
        path.lineTo(drawRect.x() + width*3/4, drawRect.y());
        path.closeSubpath();
        return path;
    }

    //获取五角星
    static QPainterPath getStar(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        qreal width = drawRect.width();
        qreal height = drawRect.height();
        path.moveTo(drawRect.x() + width*50/100, drawRect.y());
        path.lineTo(drawRect.x() + width*38.8/100, drawRect.y() + height*34.5/100);
        path.lineTo(drawRect.x() + width*2.4/100,  drawRect.y() + height*34.5/100);
        path.lineTo(drawRect.x() + width*31.8/100, drawRect.y() + height*55.9/100);
        path.lineTo(drawRect.x() + width*20.6/100, drawRect.y() + height*90.5/100);
        path.lineTo(drawRect.x() + width*50/100, drawRect.y() + height*69.1/100);
        path.lineTo(drawRect.x() + width*79.4/100, drawRect.y() + height*90.5/100);
        path.lineTo(drawRect.x() + width*68.2/100, drawRect.y() + height*55.9/100);
        path.lineTo(drawRect.x() + width*97.6/100, drawRect.y() + height*34.5/100);
        path.lineTo(drawRect.x() + width*61.2/100, drawRect.y() + height*34.5/100);
        path.closeSubpath();
        return path;
    }

    //获取田字格
    static QPainterPath getTian(QPointF pointStart, QPointF pointEnd)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath path;
        qreal width = drawRect.width();
        qreal height = drawRect.height();
        path.moveTo(drawRect.x(),drawRect.y() + height/2);
        path.lineTo(drawRect.x() + width,drawRect.y() + height/2);
        path.moveTo(drawRect.x() + width/2 ,drawRect.y());
        path.lineTo(drawRect.x() + width/2,drawRect.y() + height);
        path.addRect(drawRect.x() ,drawRect.y(),width,height);
        return path;
    }

    //获取立方体
    static QPainterPath getCube(QPointF pointStart, QPointF pointEnd ,QPainterPath *path,QPainterPath *newPath)
    {
        newPath->clear();
        path->clear();
        QRectF drawRect = QRectF(pointStart, pointEnd);
        qreal width = drawRect.width();
        qreal height = drawRect.height();

        path->moveTo(drawRect.x() + width, drawRect.y());
        path->lineTo(drawRect.x() + width*2/7, drawRect.y());
        path->lineTo(drawRect.x(), drawRect.y() + height*2/7);
        path->lineTo(drawRect.x() + width*5/7, drawRect.y() + height*2/7);
        path->lineTo(drawRect.x() + width, drawRect.y());
        path->lineTo(drawRect.x() + width, drawRect.y() + height*5/7);
        path->lineTo(drawRect.x() + width*5/7, drawRect.y() + height);
        path->lineTo(drawRect.x() + width*5/7, drawRect.y() + height*2/7);
        path->moveTo(drawRect.x(), drawRect.y() + height*2/7);
        path->lineTo(drawRect.x(), drawRect.y() + height);
        path->lineTo(drawRect.x() + width*5/7, drawRect.y() + height);
        path->lineTo(drawRect.x() + width*5/7, drawRect.y() + height*2/7);

        newPath->moveTo(drawRect.x() + width*2/7, drawRect.y());
        newPath->lineTo(drawRect.x() + width*2/7, drawRect.y() + height*5/7);
        newPath->lineTo(drawRect.x(), drawRect.y() + height);
        newPath->moveTo(drawRect.x() + width*2/7,drawRect.y() + height*5/7);
        newPath->lineTo(drawRect.x() + width,drawRect.y() + height*5/7);
        return *newPath;
    }

    //获取四凌锥
    static QPainterPath getFourCones(QPointF pointStart, QPointF pointEnd ,QPainterPath *path,QPainterPath *newPath)
    {
        newPath->clear();
        path->clear();
        QRectF drawRect = QRectF(pointStart, pointEnd);
        qreal width = drawRect.width();
        qreal height = drawRect.height();

        path->moveTo(drawRect.x() + width/2,drawRect.y());
        path->lineTo(drawRect.x() + width,drawRect.y() + height*23/32);
        path->lineTo(drawRect.x() + width*29/40,drawRect.y() + height);
        path->lineTo(drawRect.x(),drawRect.y() + height);
        path->lineTo(drawRect.x() + width/2,drawRect.y());
        path->lineTo(drawRect.x() + width*29/40,drawRect.y() + height);

        newPath->moveTo(drawRect.x() + width/2,drawRect.y());
        newPath->lineTo(drawRect.x() + width*11/40,drawRect.y() + height*23/32);
        newPath->lineTo(drawRect.x(),drawRect.y() + height);
        newPath->moveTo(drawRect.x() + width*11/40,drawRect.y() + height*23/32);
        newPath->lineTo(drawRect.x() + width,drawRect.y() + height*23/32);
        return *newPath;
    }

    //获取三凌锥
    static QPainterPath getThreeCones(QPointF pointStart, QPointF pointEnd ,QPainterPath *path,QPainterPath *newPath)
    {
        newPath->clear();
        path->clear();
        QRectF drawRect = QRectF(pointStart, pointEnd);
        qreal width = drawRect.width();
        qreal height = drawRect.height();

        path->moveTo(drawRect.x() + width*7/12,drawRect.y());
        path->lineTo(drawRect.x() + width,drawRect.y() + height*23/32);
        path->lineTo(drawRect.x() + width*25/36,drawRect.y() + height);
        path->lineTo(drawRect.x() + width*5/36,drawRect.y() + height*27/32);
        path->lineTo(drawRect.x() + width*7/12,drawRect.y());
        path->lineTo(drawRect.x() + width*25/36,drawRect.y() + height);

        newPath->moveTo(drawRect.x() + width*5/36,drawRect.y() + height*27/32);
        newPath->lineTo(drawRect.x() + width,drawRect.y() + height*23/32);
        return *newPath;
    }

    //获取圆柱体
    static QPainterPath getCylinder(QPointF pointStart, QPointF pointEnd ,QPainterPath *path,QPainterPath *newPath)
    {
        newPath->clear();
        path->clear();
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath tempPath;
        qreal width = drawRect.width();
        qreal height = drawRect.height();

        QRectF rectUp = QRectF(drawRect.x(), drawRect.y(),width,height*5/16);
        QRectF rectDown = QRectF(drawRect.x(), drawRect.y() + height*22/32,width,height*5/16);
        QPolygonF polygonf;
        //画上圆
        tempPath.arcMoveTo(rectUp, 0);
        tempPath.arcTo(rectUp, 0, 360);
        //将曲线用直线表示
        polygonf = QPolygonF(tempPath.toFillPolygon());
        //转换成路径
        path->addPolygon(polygonf);
        if (path->elementCount() == 0)
            return QPainterPath();
        //右竖线
        path->lineTo(drawRect.x() + width, drawRect.y()+height*27/32);
        //画下圆实线部分
        tempPath -= tempPath;
        tempPath.arcMoveTo(rectDown, 0);
        tempPath.arcTo(rectDown, 0, -180);
        //将曲线用直线表示
        polygonf = QPolygonF(tempPath.toFillPolygon());
        tempPath -= tempPath;
        tempPath.addPolygon(polygonf);
        //使用QPolygonF后路径会自动封闭，需要移除最后一个点,将最后一点X和Y设置成和倒数第二个点一样
        if (tempPath.elementCount() > 2)
            tempPath.setElementPositionAt(tempPath.elementCount() - 1,
                                          tempPath.elementAt(tempPath.elementCount() - 2).x,
                                          tempPath.elementAt(tempPath.elementCount() - 2).y);
        //去除第一个点MoveTo和最后一个重复点，并入总路径
        for(int i = 1; i < (tempPath.elementCount() - 1); i++)
        {
            path->lineTo(tempPath.elementAt(i).x, tempPath.elementAt(i).y);
        }
        //左竖线
        path->lineTo(drawRect.x(), drawRect.y()+height*5/32);
        //重复画上圆下半部分,封闭路径
        tempPath -= tempPath;
        tempPath.arcMoveTo(rectUp, 180);
        tempPath.arcTo(rectUp, 180, 180);
        //将曲线用直线表示
        polygonf = QPolygonF(tempPath.toFillPolygon());
        tempPath -= tempPath;
        tempPath.addPolygon(polygonf);
        //使用QPolygonF后路径会自动封闭，需要移除最后一个点,将最后一点X和Y设置成和倒数第二个点一样
        if (tempPath.elementCount() > 2)
            tempPath.setElementPositionAt(tempPath.elementCount() - 1,
                                          tempPath.elementAt(tempPath.elementCount() - 2).x,
                                          tempPath.elementAt(tempPath.elementCount() - 2).y);
        //去除第一个点MoveTo和最后一个重复点，并入总路径
        for(int i = 1; i < (tempPath.elementCount() - 1); i++)
        {
            path->lineTo(tempPath.elementAt(i).x, tempPath.elementAt(i).y);
        }

        //清空临时路径
        tempPath -= tempPath;
        //画下圆虚线部分
        tempPath.arcMoveTo(rectDown, 0);
        tempPath.arcTo(rectDown, 0, 180);
        //将曲线用直线表示
        polygonf = QPolygonF(tempPath.toFillPolygon());
        tempPath -= tempPath;
        tempPath.addPolygon(polygonf);
        //使用QPolygonF后路径会自动封闭，需要移除最后一个点,将最后一点X和Y设置成和倒数第二个点一样
        if (tempPath.elementCount() < 1)
            return QPainterPath();
        tempPath.setElementPositionAt(tempPath.elementCount() - 1,
                                      tempPath.elementAt(tempPath.elementCount() - 2).x,
                                      tempPath.elementAt(tempPath.elementCount() - 2).y);
        *newPath += tempPath;
        return *newPath;
    }

    //获取圆锥
    static QPainterPath getCone(QPointF pointStart, QPointF pointEnd ,QPainterPath *path,QPainterPath *newPath)
    {
        QRectF drawRect = QRectF(pointStart, pointEnd);
        QPainterPath tempPath;
        qreal width = drawRect.width();
        qreal height = drawRect.height();

        QRectF rect = QRectF(drawRect.x(),drawRect.y()+ height*22/32,width,height*5/16);
        tempPath.moveTo(rect.x(), rect.y());
        tempPath.arcMoveTo(rect,165);
        tempPath.arcTo(rect, 165, 210);
        tempPath.lineTo(drawRect.x() + width/2,drawRect.y());
        tempPath.closeSubpath();
        //将曲线转换成用直线表示
        QPolygonF polygonf = QPolygonF(tempPath.toFillPolygon());
        path->addPolygon(polygonf);

        tempPath.clear();
        //画虚线部分
        tempPath.arcMoveTo(rect, 15);
        tempPath.arcTo(rect, 15, 150);
        //将曲线转换成用直线表示
        polygonf = QPolygonF(tempPath.toFillPolygon());
        tempPath -= tempPath;
        tempPath.addPolygon(polygonf);
        //使用QPolygonF后路径会自动封闭，需要移除最后一个点,将最后一点X和Y设置成和倒数第二个点一样
        if (tempPath.elementCount() < 1)
            return QPainterPath();
        tempPath.setElementPositionAt(tempPath.elementCount() - 1,
                                      tempPath.elementAt(tempPath.elementCount() - 2).x,
                                      tempPath.elementAt(tempPath.elementCount() - 2).y);
        *newPath += tempPath;
        return *newPath;
    }

};

#endif // GRAPHIC_H
