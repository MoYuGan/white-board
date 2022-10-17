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
        VT_Select,      //选择
        VT_Draw,        //画笔
        VT_Eraser       //橡皮擦
    };

    //触摸功能
    enum TouchFunction {
        TF_TYPE1,        // 类型一：绘图，橡皮擦，选择框
        TF_TYPE2,        // 类型二：移动，缩放
        None
    };

public:
    BoardView(QWidget *parent = nullptr);
    //设置工具
    void setViewTool(BoardView::ViewTool tool);
    //添加新的场景(参数一：场景背景  参数二：场景背景编号)
    void createScene();
    //获取场景列表大小
    int getScenesListSize();
    //获取当前场景在场景列表位置
    int getCurrentSceneIndex();
    //撤销
    void undo();
    //恢复
    void redo();
    //清屏
    void clearScene();
    //放大
    void zoomIn();
    //缩小
    void zoomOut();
    //插入图片
    void loadPicture(const QString &fileName);
    //将场景转换成QPixmap返回
    void getScenePixmap(int index, QPixmap *pixmap);
    //选中所有Item
    void selectAllItem();
    //更改场景
    void selectScene(int index);
    //删除场景
    void deleteScene(int index);

protected:
    void resizeEvent(QResizeEvent *event);
    bool viewportEvent(QEvent *event);

private:
    ViewTool m_pViewTool = ViewTool::VT_Select;
    QMap<int, QPointF> m_pTouchPressedPoint;
    QGraphicsPathItem *m_pSelectDragRect;

    BoardScene *m_pCurrentScene = nullptr;  //当前场景
    QVector<BoardScene *> m_pScenesList;    //场景列表
    QColor m_pFillColor;                    //填充颜色
    bool m_pTempEraser = false;             //临时启动橡皮擦
    bool m_MultiTouch = true;

    QVector<QPixmap> map;
    QString str_fileName;

    bool m_pMousePressed = false;       //鼠标按下标志位
    bool m_pTouchPressed = false;       //触摸屏按下标志位，优先级大于鼠标按下标志位
    QPoint m_pLastPoint;                //鼠标拖动时上一次坐标

    /* 多指移动，缩放相关 */
    QMap<int, QList<QPointF>> m_pTouchPoints;               //记录按下触摸点
    TouchFunction m_pTouchFunction = TouchFunction::None;   //是否允许绘图操作
    QTimer *m_pPressTimer;                                  //触摸按下计时
    QList<QTouchEvent::TouchPoint> m_pTouchMovePointList;

    QPointF m_pPressedPoint;
    int m_pPressedId;

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
    //手势移动
    void gestureMove(const QPointF &lastPt, const QPointF &curPt);
    //设置场景Item是否可被选中
    void setScenesSelectable(bool bo);

signals:
    void newSceneCreated(int);
    void mouseClicked();
    void itemChanged();
};

#endif // BOARDVIEW_H
