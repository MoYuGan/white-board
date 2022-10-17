#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include "custom.h"
#include <QLabel>
#include <QPainterPath>
#include "ScreenShotInterFace.h"
#include <QEventLoop>

class ScreenShot : public ScreenShotInterFace
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    //第一个参数为接口类的标识，与接口类处内容一致作呼应，后面为当前类.json文件，内部放入{}即可
    Q_PLUGIN_METADATA(IID "ScreenShotInterFace/01" FILE "ScreenShotInterFace.json")
    Q_INTERFACES(ScreenShotInterFace)//填写接口类名称
#endif

enum MOUSEPOS{
        UP =1,
        LEFTUP,
        RIGHTUP,
        LEFT,
        RIGHT,
        DOWN,
        LEFTDOWN,
        RIGHTDOWN,
        MOVE,
        NO
};

public:
    explicit ScreenShot(QWidget *parent = nullptr);
    void show();
    void resize();
    void initLayout();
    void changeFreeShot(int a);
    ScreenShotInterFace* getWidget();
    void updateLanguage(bool );

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    MOUSEPOS getMousePos(QPoint );
    QPixmap getShotPixmap(QPixmap );
    void setShow(int );


private:
    QScreen *screen;
    MOUSEPOS mousepos =MOUSEPOS::NO;
    QRect mrect;
    QPoint mousepressdot;
    bool mousestate =false;
    int drawflag =0;
    int r= 8;
    int R= 12;
    int flag =0;
    mPushButton_1 *confirm;
    mPushButton_1 *cancel;
    QWidget *toolwidget;
    int shotshape =4;
    QLabel *textLab;
    QVector<QPoint>listpoint;
    QPainterPath shotpath;
    QPixmap pixmap;
    int x1 =0;
    int x2 =0;
    int y1 =0;
    int y2 =0;
    int toolwidgethide =0;
    QRect recordpos;
    QLabel *back_Lab;
    QLabel *text_Lab;
    Label_1 *rect_Lab;
    Label_1 *free_Lab;
    Label_1 *desktop_Lab;
    QTimer* timer;
    QEventLoop* loop;
    bool mIsChinese;
};

#endif // SCREENSHOT_H
