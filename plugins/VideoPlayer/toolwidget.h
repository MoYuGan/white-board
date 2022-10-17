#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QEvent>
#include <QMouseEvent>
#include "customcontrol.h"
#include <QTimer>
#include <QThread>
#include "videoplayerwork.h"
#include "VideoPlayerInterFace.h"

namespace Ui {
class ToolWidget;
}

class ToolWidget : public VideoPlayerInterFace
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "VideoPlayerInterFace/01" FILE "MyVideoPlayer.json")
    Q_INTERFACES(VideoPlayerInterFace)//填写接口类名称
#endif

public:
    explicit ToolWidget(QWidget *parent = nullptr);
    ~ToolWidget();
    VideoPlayerInterFace* createWidget(QWidget *parent) override;
    void openFilePath() override;

protected:
    void initWidget();
    void initConnect();
    void initeventFilter();
    void resizeControl(int number =1);//设置控件大小
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void pressMiniPlayer();//按下小的播放按钮
    void pressMaxPlayer();//按下大的播放按钮
    void pressFullScreen();//点击全屏
    void pressVolume();//打开音量按钮
    void pressFile();//打开文件夹
    void showButton(int );//选着隐藏和显示按钮

signals:
    /**发送播放的文件，音量，播放速度，获得图片，视频长，视频宽**/
    void sendStartPlaySignal(QString filepath,int volumenum,float speednum,QPixmap *pixmap,int *videowidth,int *videoheight);
    void sendVolumeChangeSignal(int );//发送音量改变信号
    void sendSpeedChangeSignal(float );//发送播放速度改变信号
    void sendPlayPosChangeSignal(int );//发送播放位置度改变信号
    void sendPausePlaySignal();//发送播放暂停信号
    void sendContinuePlaySignal();//发送播放继续信号
    void sendCloseSignal();//发送关闭信号
    void sendStopPlaySignal();//发送停止信号

public slots:
    void rotatePixmap();//视频旋转
    void getUpdateTimeSignal(QString time,int counttime,int currenttime);//更新视频时间


private:
    Ui::ToolWidget *ui;
    QPointF pressdot;
    QPointF widgetpos;
    QString filepath =nullptr;
    bool ispress =false;
    bool isfull =false;
    Volumewidget *volume;
    Speedwidget *speed;
    QTimer* hidebutton;
    QPixmap *pixmap;
    QPixmap mpixmap;
    int m_width =1200;
    int m_height =672;
    int videowidth =1200;
    int videoheight =672;
    QString counttime;
    int  videolength=0;
    int rotate =0;
    QThread *thread;
    VideoPlayerWork *playerwork;
    bool isfinish =false;
    bool isscreenshot =false;

};

#endif // TOOLWIDGET_H
