#ifndef PUBLIC_FUNCTION_H
#define PUBLIC_FUNCTION_H

#include <QPainterPath>
#include <QRectF>
#include <QDesktopWidget>
#include <QPointF>
#include <QPolygonF>
#include <QApplication>
#include <QPen>
#include <QScreen>
#include <QGuiApplication>

#ifndef MY_DECLARE_METATYPE
#define MY_DECLARE_METATYPE
Q_DECLARE_METATYPE(QPen)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QColor)
#endif

class Public_Function
{
public:
    //获取圆角矩形框路径，参数一：矩形框，参数二：圆角半径
    static QPainterPath getRoundRectPath(const QRectF &rect, qreal topLeftRadius, qreal topRightRadius, qreal bottomLeftRadius,
                                         qreal bottomRightRadius)
    {
        //偏离值(给圆角的开始和结束点设置一个偏离值，可以使圆角看起来更圆滑)
        qreal topLeftSubValue = topLeftRadius > 5 ? topLeftRadius*1.5/12.0 : 0;
        qreal topRightSubValue = topRightRadius > 5 ? topRightRadius*1.5/12.0 : 0;
        qreal bottomRightSubValue = bottomRightRadius > 5 ? bottomRightRadius*1.5/12.0 : 0;
        qreal bottomLeftSubValue = bottomLeftRadius > 5 ? bottomLeftRadius*1.5/12.0 : 0;
        qreal subValue = topLeftSubValue;
        //如果四个角偏离值不相等，不做偏离
        if (subValue != topRightSubValue ||
                subValue != bottomRightSubValue ||
                subValue != bottomLeftSubValue)
            subValue =  0;

        QPainterPath path;
        QPointF topLeftP1 = QPointF(rect.x() + subValue, rect.y() + topLeftRadius);
        QPointF topLeftP2 = QPointF(rect.x() + topLeftRadius, rect.y() + subValue);
        QPointF topRightP1 = QPointF(rect.x() + rect.width() - topRightRadius, rect.y() + subValue);
        QPointF topRightP2 = QPointF(rect.x() + rect.width() - subValue, rect.y() + topRightRadius);
        QPointF bottomRightP1 = QPointF(rect.x() + rect.width() - subValue, rect.y() + rect.height() - bottomLeftRadius);
        QPointF bottomRightP2 = QPointF(rect.x() + rect.width() - bottomLeftRadius, rect.y() + rect.height()- subValue);
        QPointF bottomLeftP1 = QPointF(rect.x() + bottomRightRadius, rect.y() + rect.height()- subValue);
        QPointF bottomLeftP2 = QPointF(rect.x() + subValue, rect.y() + rect.height()- bottomRightRadius);
        path.moveTo(topLeftP1);
        path.cubicTo(topLeftP1, rect.topLeft(), topLeftP2);
        path.lineTo(topRightP1);
        path.cubicTo(topRightP1, rect.topRight(), topRightP2);
        path.lineTo(bottomRightP1);
        path.cubicTo(bottomRightP1, rect.bottomRight(), bottomRightP2);
        path.lineTo(bottomLeftP1);
        path.cubicTo(bottomLeftP1, rect.bottomLeft(), bottomLeftP2);
        path.lineTo(topLeftP1);
        return path;
    }

    inline static QPainterPath getRoundRectPath(const QRectF &rect, qreal radius) {
        return getRoundRectPath(rect, radius, radius, radius, radius);
    }

    //曲线转直线
    static QPainterPath cubToLine(const QPainterPath &path)
    {
        QPolygonF polygonf = QPolygonF(path.toFillPolygon());
        QPainterPath newPath;
        newPath.addPolygon(polygonf);
        //使用QPolygonF后路径会自动封闭，需要移除最后一个点,将最后一点X和Y设置成和倒数第二个点一样
        if (newPath.elementCount() > 2)
            newPath.setElementPositionAt(newPath.elementCount() - 1,
                                          newPath.elementAt(newPath.elementCount() - 2).x,
                                          newPath.elementAt(newPath.elementCount() - 2).y);
        return newPath;
    }

    //根据缩放比例缩放字体
    static QFont getFont(int fontSize) {
        int newFontSize = fontSize * getScaling();

        QFont font;
        font.setPixelSize(newFontSize);
        return font;
    }

    inline static QSize getScaleSize(int width, int height) {
        return getScaleSize(QSize(width, height));
    }

    //根据缩放比例缩放QSize
    static QSize getScaleSize(const QSize &size) {
        int w = size.width() * getScaling();
        int h = size.height() * getScaling();
        return QSize(w, h);
    }

    static int getScaleSize(int size) {
        int w = size * getScaling();
        return w;
    }

    static QColor getTextColor() {
        return QColor(102, 102, 102);
    }

    //获取列表最小值
    static qreal getMin(QVector<qreal> vector){
        qreal min = 0;
        for(int i = 0; i < vector.size(); i++) {
            if (0 == i)
                min = vector.at(i);
            else
                min = min > vector.at(i) ? vector.at(i) : min;
        }
        return min;
    }

    //获取列表最大值
    static qreal getMax(QVector<qreal> vector){
        qreal max = 0;
        for(int i = 0; i < vector.size(); i++) {
            if (0 == i)
                max = vector.at(i);
            else
                max = max < vector.at(i) ? vector.at(i) : max;
        }
        return max;
    }


private:
    /*
     * 功能:以1920x1080的显示器为标准，获取当前主屏幕的大小，计算缩放比例
    */
    static qreal getScaling() {
        int screenWidth =  QGuiApplication::primaryScreen()->geometry().width();
        if (screenWidth < 1920)
            return 1;
        else
            return screenWidth/1920;
    }

};

#endif // PUBLIC_FUNCTION_H
