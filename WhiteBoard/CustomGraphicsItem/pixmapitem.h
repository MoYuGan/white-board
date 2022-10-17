#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <math.h>
#include <QPainter>
#include "Public/public_function.h"
#include "Extern/extern.h"
#include <QTouchEvent>
#include <QMovie>
#include <QTimer>

class PixmapItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    //历史修改类型
    enum HistoryType {
        Move,           //缩放或移动了图片，包括大小和显示位置
        ZValue,         //修改了图层级数
        Rotate,
        None
    };

    /*自定义Type*/
    enum { Type = UserType + (int)((int)(ItemType::PixmapItem)) };
    int type() const override { return Type; }

public:
    PixmapItem(QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void m_setGifPixmap(const QString fileName, const QRect &rect, QPointF rotateCenter = QPointF(), qreal rotateAngle = 0);
    void m_setPixmap(const QPixmap &pixmap,const QRect &rect, QPointF rotateCenter = QPointF(), qreal rotateAngle = 0);
    bool IsGifPixmap();

    void m_setZValue(qreal value);
    //缩放Item
    void scaleItem(const qreal &xFactor, const qreal &yFactor, const QPointF &center);
    //旋转item
    void rotateItem(qreal angle, const QPointF &center);
    //移动item
    void moveItem(const QPointF &subPt);

    void undo();
    void redo();
    void pushDataToUndoData(HistoryType type);
    bool isDelete();
    void setDelete(bool );
    void getItemRect();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF );
    void moveEvent(QPointF );
    void releaseEvent();
    int pointid=0;

private:
    QPixmap m_Pixmap;
    QRect m_PixmapRect;
    QRect m_itemrect;
    qreal m_RotateAngle = 0;
    QPointF m_RotateCenter = QPointF();
    QMovie *movie;
    bool isgif =false;
    bool m_pHasMouseMove = false;
    QPointF m_pMouseLastPoint;
    bool m_delete =false;
    QVector<QVariant> m_pUndoData;              //撤销数据集合
    QVector<HistoryType> m_pUndoType;           //撤销数据类型
    QVector<QVariant> m_pRedoData;              //恢复数据集合
    QVector<HistoryType> m_pRedoType;           //恢复数据类型
    bool m_IsPushToHistory = true;

    QPainterPath getTransformPath(const QPainterPath &srcPath, QTransform *transform, const QPointF &center = QPointF()) const;

signals:
     void itemChanged(QGraphicsItem *);
     void itemClicked(QGraphicsItem *);
};
#endif // PIXMAPITEM_H
