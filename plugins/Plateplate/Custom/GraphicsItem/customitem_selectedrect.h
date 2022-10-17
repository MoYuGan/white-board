#ifndef CUSTOMITEM_SELECTEDRECT_H
#define CUSTOMITEM_SELECTEDRECT_H

#include <QGraphicsItem>
#include <QObject>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <math.h>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneHoverEvent>
#include "Public/publicfunction.h"
#include "ToolBar/graphicsitem_toolbar.h"

class CustomItem_SelectedRect  : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum ItemAction {
        Move,
        ZoomTopLeft,
        ZoomTopRight,
        ZoomBottomLeft,
        ZoomBottomRight,
        Rotate,
        None
    };

    /*自定义Type*/
    enum { Type = UserType + 110 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

public:
    CustomItem_SelectedRect(QGraphicsItem *parent = Q_NULLPTR);
    ~CustomItem_SelectedRect();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setRect(const QRectF rect);
    void createTool(bool isClone);

//    void setToolVisable(bool bo) {
//        m_pShowTool = bo;
//        if (m_pToolWidget->isVisible() && !bo)
//            m_pToolWidget->setVisible(bo);
//    }

//    QPointF getCenter() {
//        QPointF center;
//        center = m_pSelectRect.center();
//        return center;
//    }



//    inline QRectF getRect() {
//        return m_pSelectRect;
//    }



protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF m_pSelectRect;
    QPointF m_pRotatePoint;
    ItemAction m_pItemAction;
    QPointF m_pMouseLastPoint;
    bool m_pMouseMoving = false;
    GraphicsItem_ToolBar *m_pItemToolBar = nullptr;
    QGraphicsProxyWidget *m_pToolWidget = nullptr;
    bool m_pShowTool = true;
    bool m_IsCloneMode = false;

signals:
    void actionRotate(qreal, QPointF);
    void actionRotateFinished();
    void actionMove(QPointF);
    void actionScale(qreal, qreal, QPointF);
    void actionScaleFinished();
    void actionFinished();
    void cloneModeChanged(bool);
    void toClone(qreal, qreal);
    void cloneFinished();
    void stayTop();
    void stayBottom();
    void toDelete();
};

#endif // CUSTOMITEM_SELECTEDRECT_H
