#ifndef MINWHITEBOARD_VIEW_H
#define MINWHITEBOARD_VIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTouchEvent>
#include <QLabel>
#include <QTimer>
#include <QMap>
#include "minwhiteboard_scene.h"
#include "minwhiteboar_pathitem.h"

class MinWhiteBoard_View : public QGraphicsView
{
    Q_OBJECT

public:
    //工具
    enum ViewTool {
        Pen,        //画笔
        Erase,       //橡皮擦
        NoTool
    };

public:
    MinWhiteBoard_View(QWidget *parent = nullptr);
    void setTool(ViewTool tool);
    void clearScene();

protected:
    bool viewportEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    QPixmap getViewPixmap();
    void drawBackgroundPixmap(QPainterPath );

private:
    ViewTool m_Tool = ViewTool::Pen;

    /* 画笔 */
    bool m_TouchPressed = false;
    QMap<int, QGraphicsPathItem*> m_DrawItemMap;
    bool m_MousePressed = false;
    QPointF m_LastPoint;

    /* 选择 */
    QGraphicsRectItem *m_SelectRectItem = nullptr;

    /* 橡皮擦 */
    QGraphicsPixmapItem *m_EraseItem = nullptr;

private:
    /* 画笔 */
    void drawTouchEvent(QTouchEvent *event);
    void drawMouseEvent(QMouseEvent *event);
    void getDrawPath(QPainterPath *srcPath, const QPointF &lastPos, const QPointF &curPos);
    void getGraphicPath(const QPointF &p1, const QPointF &p2, QPainterPath *path);

    /* 橡皮擦 */
    void eraseMouseEvent(QMouseEvent *event);
    void eraseTouchEvent(QTouchEvent *event);
    QPainterPath getErasePath(const QPointF &lastPos, const QPointF &currentPos);
    int pointid =0;
    QPixmap m_pixmap;

};

#endif // MINWHITEBOARD_VIEW_H
