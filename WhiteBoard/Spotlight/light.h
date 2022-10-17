#ifndef LIGHT_H
#define LIGHT_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QFrame>
#include "CustomWidget/db_custompushbutton.h"

class Light : public QWidget
{
    Q_OBJECT

    enum MOUSEPOS{ //鼠标所在位置标记
        UP =1,
        UPLEFT,
        UPRIGHT,
        LEFT,
        RIGHT,
        DOWN,
        DOWNLEFT,
        DOWNRIGHT,
        MOVE,
        NO
    };

    enum RECTANDROUND{ //方形和圆形
        RECT =1,
        ROUND,
    };

    enum FILLANDPICTURE{ //填充和图片
        FILL =1,
        PICTURE,
    };

    enum MAXANDMIN{ //放大和缩小
        MAX =1,
        MIN,
        NOCHANGE
    };

public:
    explicit Light(QWidget *parent = nullptr);
    void initCustom();      //控件初始化
    void initConnect();     //按钮槽链接
    void outRect(QPainter& ); //绘制外部8个小圆点
    MOUSEPOS getMousePos(QPoint ); //获得鼠标所在的位置和鼠标样式

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
     void getShowPixmap(QPixmap* );//获得当前界面图片

public slots:
    void getColor();

private:
    MOUSEPOS mousepos = MOUSEPOS::NO;
    RECTANDROUND rectandround = RECTANDROUND::RECT;
    FILLANDPICTURE fillandpicture = FILLANDPICTURE::FILL;
    MAXANDMIN maxandmin = MAXANDMIN::NOCHANGE;
    QPoint presspoint;           //鼠标按下点
    QPoint releasepoint;         //鼠标松开点
    QRect moverect;              //当前矩形框
    QRect oldrect;               //移动前的矩形
    int drawflag = 0;            //更改值避免重新绘制矩形
    bool mousepress =false;      //判断鼠标状态
    QFrame *mytool;              //放置自定义按键的界面
    DB_CustomPushButton_16 *rectBtn;       //矩形
    DB_CustomPushButton_16 *roundBtn;      //圆形
    DB_CustomPushButton_16 *maxBtn;        //放大
    DB_CustomPushButton_16 *minBtn;        //缩小
    DB_CustomPushButton_16 *pictureBtn;    //图片
    DB_CustomPushButton_16 *fillBtn;       //填充
    DB_CustomPushButton_16 *closeBtn;      //取消
    QColor fillcolor =Qt::black; //填充色初始值
    QPixmap pixmap;              //聚光灯四周填充图片
    QLabel *textLab;             //开始的文字提示
    QPixmap *copypixmap;         //存储当前界面图片
    float index =2.0;            //放大指数初始值

};

#endif // LIGHT_H
