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


class BoardView : public QGraphicsView
{
    Q_OBJECT

public:
    //工具
    enum ViewTool {
        VT_None,
        VT_Draw,        //画笔
        VT_Eraser       //橡皮擦
    };

public:
    BoardView(QWidget *parent = nullptr);
    //设置工具
    void setViewTool(BoardView::ViewTool tool);
    //添加新的场景(参数一：场景背景  参数二：场景背景编号)
    void createScene();
    //撤销
    void undo();
    //恢复
    void redo();
    //清屏
    void clearScene();
    //
    void resetNewScene();



protected:
    void resizeEvent(QResizeEvent *event);
    bool viewportEvent(QEvent *event);

private:
    ViewTool m_pViewTool = ViewTool::VT_None;
    QMap<int, QPointF> m_pTouchPressedPoint;
    QGraphicsPathItem *m_pSelectDragRect;
    BoardScene *m_pCurrentScene = nullptr;  //当前场景
    bool m_pTempEraser = false;             //临时启动橡皮擦
    bool m_pMousePressed = false;       //鼠标按下标志位
    QPoint m_pLastPoint;                //鼠标拖动时上一次坐标

private:
    //触摸开始
    void touchBegin();
    //触摸按下
    void touchPressed(int id, const QPointF &pt);
    //触摸移动
    void touchMove(int id, const QPointF &p1, const QPointF &p2);
    //触摸松开
    void touchRelease(int id, const QPointF &p1);
    //触摸结束
    void touchEnd();
};

#endif // BOARDVIEW_H
