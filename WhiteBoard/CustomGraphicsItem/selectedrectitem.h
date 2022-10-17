#ifndef SELECTEDRECTITEM_H
#define SELECTEDRECTITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsProxyWidget>
#include "Extern/extern.h"
#include "pathitem.h"
#include "graphicsitem.h"
#include "lineitem.h"
#include "pixmapitem.h"
#include "mod_draw/ItemTool/itemtool.h"
#include "mod_draw/ItemTool/itemtool_borderpanel.h"
#include "mod_draw/ItemTool/itemtool_fillcolorpanel.h"
#include "mod_draw/ItemTool/itemtool_flippanel.h"
#include "mod_draw/ItemTool/itemtool_mirrorpanel.h"
#include "Public/public_function.h"
#include <QEvent>

class SelectedRectItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum RectType {     //矩形框类型，根据选中item的类型决定绘制什么样式的矩形框
        Rect,
        Line
    };

    enum ItemAction {
        Move,
        ZoomTopLeft,
        ZoomTopRight,
        ZoomBottomLeft,
        ZoomBottomRight,
        ZoomTopCenter,
        ZoomBottomCenter,
        ZoomRightCenter,
        ZoomLeftCenter,
        Rotate,
        ZoomP1,
        ZoomP2,
        None
    };

    /*自定义Type*/
    enum { Type = UserType + (int)(ItemType::SelectedRectItem) };
    int type() const { return Type; }

public:
    SelectedRectItem(const QList<QGraphicsItem*>& selectedItems, QGraphicsItem *parent = Q_NULLPTR);
    ~SelectedRectItem();

    //djf
    void updateSelectItem(const QList<QGraphicsItem*>& selectedItems);
    void updateLanguage();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    //void setToolVisable(bool bo);
    QRectF getRect();
    void setLine(const QLineF &line);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    bool sceneEvent(QEvent *event);
    void pressEvent(QPointF );
    void moveEvent(QPointF );
    void releaseEvent();
    int pointid =0;


private:
    QList<QGraphicsItem*> m_SelectedItems;
    RectType m_RectType;
    QRectF m_SelectedRect;
    QRectF m_OldRect;
    bool m_CloneMode = false;
    ItemAction m_ItemAction;
    QLineF m_Line;
    QPainterPath m_LinePathStrokerPath;
    QPointF m_pRotatePoint;
    QPointF m_pMousePressedPoint;
    QPointF m_pMouseLastPoint;
    bool m_MouseMoved = false;
    QLineF m_pRotateLine;
    bool m_IsPushToHistory = false;

    bool m_ScaleToScale = true;    //当选中的item中包含图片item时，所有item按照比例缩放
    QPointF m_LastScalePoint;
    qreal m_LastScaleWidth = 0;
    qreal m_LastScaleHeight = 0;
    
    ItemTool *m_pItemTool = nullptr;
    QGraphicsProxyWidget *m_pToolWidget = nullptr;
    QGraphicsProxyWidget *m_pBorderPanel = nullptr;
    QGraphicsProxyWidget *m_pFillColorPanel = nullptr;
    QGraphicsProxyWidget *m_pFlipPanel = nullptr;
    QGraphicsProxyWidget *m_pMirrorPanel = nullptr;
    //djf
    ItemTool_BorderPanel * p_borderPanelContain = nullptr;
    ItemTool_FillColorPanel* p_FillColorPanelContain = nullptr;
//    bool m_pIsAdjustMode = false;
//    bool m_pShowTool = true;

private:
    void getSelectedRect();
    void createToolWidget();
    QPointF getCenter();
    void moveItems(const QPointF &subPt);
    void rotateItems(qreal angle, const QPointF &center);
    void scaleItems(qreal xFactor, qreal yFactor, const QPointF &center);
    void getItemRect();//获得缩放前的原始图形，用来计算后面的缩放
    //获取旋转角度
    qreal getRotateAngle(QPointF center, QPointF firstPoint, QPointF secondPoint);

    QVariant getRotateMap(QVariant data, qreal angle, const QPointF &center);

private slots:
    void onShowBorderPanel(bool checked, const QPointF &displayPt);
    void onShowFillColorPanel(bool checked, const QPointF &displayPt);
    void onShowFlipPanel(bool checked, const QPointF &displayPt);
    void onShowMirrorPanel(bool checked, const QPointF &displayPt);
    void onMirror(int direction);

signals:
    void borderSizeChanged(int);
    void borderLineChanged(Qt::PenStyle );
    void borderColorChanged(QColor);
    void fillColorChanged(QColor);
    void stayOnTop();
    void stayOnBottom();
    void flipItems(int, QPointF);
    void mirrorItems(int, qreal);
    void deleteItems();
    void actionFinished();
    void itemCreated(QList<QGraphicsItem *>);
    void cloneItems(QPointF);
    void cloneFinished();
    void checkIs3DShape(bool* );

};

#endif // SELECTEDRECTITEM_H
