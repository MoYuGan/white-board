#ifndef CUSTOMITEM_PIXMAP_H
#define CUSTOMITEM_PIXMAP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <math.h>
#include <QtDebug>
#include <QPainter>
#include "Public/publicfunction.h"

class  CustomItem_Pixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //历史修改类型
    enum ActionType {
        Scale,      //缩放了图片，包括大小和显示位置
        Move,     //修改了显示位置
        ZValue,     //修改了图层级数
        Rotation,   //修改了旋转角度
        None
    };

    /*自定义Type*/
    enum { Type = UserType + 102 };
public:
    CustomItem_Pixmap(QGraphicsItem *parent = Q_NULLPTR);

    int type() const { return Type; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    QRect getPixmapRect();
    void setPixmap(const QPixmap &pixmap, const QRect &pixmapRect, qreal rotateAngle = 0, QPointF rotateCenter = QPointF());
    void setZValue(qreal value);
    //缩放Item
    void scaleItemWithFactor(const qreal &xFactor, const qreal &yFactor, const QPointF &center);
    void scaleItemWithLength(qreal length, const QPointF &center);
    //旋转item
    void rotateItem(qreal angle, const QPointF &center);
    //移动item
    void moveItem(const QPointF &subPt);
    //翻转，参数一：翻转方向(0=水平，1=垂直), 参数二：翻转中心点
    void flipItem(int direction, QPointF center);
    //--->当前Item进行过缩放，移动，旋转，修改图层等操作后应该调用此函数，将操作加入历史修改记录<----
    void actionFinished();

    //镜像, 参数一：镜像方向(0=向上/向下，1=向左/向右)，参数二：向上向下翻转时是翻转线的Y坐标，向左向右翻转时是翻转线的X坐标
//    void mirror(int direction, qreal p) {
//        QTransform transform;
//        QPointF center;
//        if (0 == direction) {
//            transform.rotate(180, Qt::XAxis);
//            center = QPointF(this->boundingRect().center().x(), p);
//        }else {
//            transform.rotate(180, Qt::YAxis);
//            center = QPointF(p, this->boundingRect().center().x());
//        }
//        /* 设置旋转中心 */
//        QPointF tCenter = transform.map(center);
//        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
//                            transform.m21(), transform.m22(), transform.m23(),
//                            center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
//        QPainterPath path = transform.map(this->path());
//        CustomItem_GraphicPath *pathItem = new CustomItem_GraphicPath;
//        pathItem->setFlags(QGraphicsItem::ItemIsSelectable);
//        pathItem->setPen(this->pen());
//        pathItem->setZValue(this->zValue());
//        pathItem->setPath(path);
//        this->scene()->addItem(pathItem);
//    }

    //设置克隆模式，如果为真，移动item将变成克隆item
    void setClone(bool bo);
    inline bool isClone() { return m_pIsClone; }
    //克隆item，参数一：最近两个鼠标点之间X方向差值，参数二：最近两个鼠标点之间Y方向差值
    void toClone(qreal dx, qreal dy);
    //克隆完成
    void cloneFinished();
    //撤销
    void undo();
    //恢复
    void redo();
    void clearRedoList();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    bool m_pHasMouseMove = false;
    QPointF m_pMouseLastPoint;
    bool m_pIsClone = false;
    CustomItem_Pixmap *m_pCloneItem = nullptr;
    QRect m_pPixmapRect = QRect();
    QRect m_pTempPixmapRect = QRect();          //保存图片矩形框大小，进行缩放操作时记录原来图片矩形框大小
    qreal m_pRotateAngle = 0;
    qreal m_pTempRotateAngle = 0;               //保存角度的变化值，一个完整旋转操作（按下到释放）结束时，将角度变化值加入历史记录
    QPointF m_pRotateCenter = QPointF();
    QPointF m_pScaleCenter = QPointF();
    int m_pTempZValue;                          //图层级数，置顶或者置底的时候保存当前层级，操作完成后加入历史记录
    ActionType m_pActionType = ActionType::None;
    QVector<QVariant> m_pUndoData;              //撤销数据集合
    QVector<ActionType> m_pUndoType;           //撤销数据类型
    QVector<QVariant> m_pRedoData;              //恢复数据集合
    QVector<ActionType> m_pRedoType;           //恢复数据类型
    QPointF m_pMousePressedPoint;
    QPainterPath path;



    void pushDataToUndoData(QVariant variant, ActionType type) {
        m_pUndoData.push_back(variant);
        m_pUndoType.push_back(type);

        m_pRedoData.clear();
        m_pRedoType.clear();
    }

    //根据旋转角度获取图片矩形框
    QRect getPixmapRectWithAngle(qreal newAngle, QPointF center) {
        QTransform transform;
        //新的旋转角度减去就的旋转角度就是当前的旋转角度
        transform.rotate(newAngle - m_pRotateAngle, Qt::ZAxis);
        /* 设置旋转中心 */
        QPointF tCenter = transform.map(center);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
        return transform.mapRect(m_pPixmapRect);
    }

signals:
     void itemHasChanged(QGraphicsItem *);
     void itemSelected();
     void newItemCreated(QGraphicsItem *);
};

#endif // CUSTOMITEM_PIXMAP_H
