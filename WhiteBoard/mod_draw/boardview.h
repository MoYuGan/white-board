#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QTouchEvent>
#include <QLabel>
#include <QTimer>
#include <QMap>
#include "boardscene.h"
#include "FileOperations/m_pdf.h"
#include "CustomGraphicsItem/graphicsitem.h"
#include "graphic.h"
#include "MiniBoard/getpointworker.h"

class DB_BoardView : public QGraphicsView
{
    Q_OBJECT

public:
    //工具
    enum ViewTool {
        VT_Select,      //选择
        VT_Draw,        //画笔
        VT_Eraser       //橡皮擦
    };


public:
    DB_BoardView(QWidget *parent = nullptr);
    void show();
    /* 改变画图的场景背景图片 */
    void changeDrawingScenePixmap(QBrush );
    /* 显示遮慕 */
    void showCoverRect();
    /* 添加尺规item */
    void addChiGuiItem(int type);
    bool eventFilter(QObject *watched, QEvent *event) override;
    QBrush currentbrush;
    void resetDrawingScene(BoardScene *);

    /*更换现实的场景*/
    void changeViewScene(int );

    /*页面切换后，重新设置当前场景*/
    void resetCurrentScene(BoardScene* );

    /* 获得实际的绘图场景 */
    BoardScene* getItemScene();
    BoardScene* getItemDrawingScene();
    void moveItemToScene();
    void moveChiGuiToScene();
    void moveItemToDrawScene();
    void clearDrawingSceneItem();
    QPainterPath pathCutOff(QPainterPath* ,int );
    QPixmap getViewToPixmap();
    QPixmap getViewTabPixmap();
//djf
    void updateLanguage();


    void miniRightDrawTouchEvent(_TPPoint point,QColor);
    void miniLeftDrawTouchEvent(_TPPoint point,QColor);
    void miniEraseMouseEvent(_TPPoint point);

protected:
    bool viewportEvent(QEvent *event) override;

private:
    /* 画笔 */
    bool m_CloseTouch = false;
    bool m_TouchPressed = false;
    bool m_MiniLeftTouchPressed = false;
    bool m_MiniRightTouchPressed = false;
    QMap<int, QGraphicsItem*> m_DrawItemMap;
    QMap<int, QGraphicsItem*> DrawItemMap;
    QMap<int, QPointF> m_PixmapPoint;
    bool m_MousePressed = false;
    bool m_MiniMousePressed = false;
    QPointF m_LastPoint;
    QList<QGraphicsItem *> m_AddItems;

    QMap<int, QGraphicsItem*> m_LeftDrawItemMap;
    QMap<int, QGraphicsItem*> LeftDrawItemMap;
    QList<QGraphicsItem *> m_LeftAddItems;

    QMap<int, QGraphicsItem*> m_RightDrawItemMap;
    QMap<int, QGraphicsItem*> RightDrawItemMap;
    QList<QGraphicsItem *> m_RightAddItems;

    /* 选择 */
    QGraphicsRectItem *m_SelectRectItem = nullptr;

    /* 橡皮擦 */
    QGraphicsPixmapItem *m_EraseItem = nullptr;

    BoardScene *m_sceneold = nullptr;
    BoardScene *m_scene = nullptr;

    QPointF m_LastLastPoint;
    QVector<QGraphicsItem *>listPath;

    QColor leftpencolor;
    QColor rightpencolor;


private:
    /* 画笔 */
    void drawTouchEvent(QTouchEvent *event);/* 画线触摸事件 */
    void drawMouseEvent(QMouseEvent *event);/* 画线鼠标事件 */
    void getDrawPath(QPainterPath *srcPath, const QPointF &lastPos, const QPointF &curPos);
    void getGraphicPath(const QPointF &p1, const QPointF &p2, QPainterPath *path,QPainterPath *path2 =nullptr);

    /* 橡皮擦 */
    void eraseMouseEvent(QMouseEvent *event);/* 橡皮擦鼠标事件 */
    void eraseTouchEvent(QTouchEvent *event);/* 橡皮擦触摸事件 */
    QPainterPath getErasePath(const QPointF &lastPos, const QPointF &currentPos);

    /* 选择 */
    void cursorMouseEvent(QMouseEvent *event);/* 选择鼠标事件 */
    void cursorTouchEvent(QTouchEvent *event);/* 选择触摸事件 */
    bool isItemsIn(const QPointF &pt);

    /* */
    QGraphicsItem* drawGraphicPressed();
    void drawGraphicMove(const QPointF &p1, const QPointF &p2);
    void drawGraphicRelease();

    bool pressIsItem =false;

    void setMinGraphic(QPointF ,QPointF );
    QPointF getPixmapDot(QPointF ,QPointF ,int mlength =100);

public:
    int pointid =0;/* 记录当前某个使用的手指的ID */
    QMap<QObject*,QGraphicsItem*>m_mapTempItem;

signals:
    void mousePressed();
    void drawGraphicFinished();
    void newGraphicsview();
};

#endif // BOARDVIEW_H
