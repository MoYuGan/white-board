#ifndef VIDEOPLAYERWORK_H
#define VIDEOPLAYERWORK_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QImage>
#include <QPixmap>

extern "C" {
#include "vlc/vlc.h"
}

struct Context {
    QMutex mutex;
    uchar *pixels;
};

class VideoPlayerWork : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayerWork(QObject *parent = nullptr);
    ~VideoPlayerWork();
    static void *lock(void* opaque, void** planes);
    static void unlock(void* opaque, void* picture, void* const* planes);
    static void display(void* opaque, void* picture);
    void updatePixmap(const QImage &image );
    QString calculateTime(libvlc_time_t );

public slots:
    /***开始播放*/
    void getStartPalySignal(QString filepath,int volumenum,float speednum,QPixmap *pixmap,int *videowidth,int *videoheight);
    void getPausePlaySignal();//暂停播放
    void getContinuePlaySignal();//继续播放
    void getStopPlaySignal();//停止
    void getCloseSignal();//关闭
    void getVolumeChangeSignal(int );//改变播放音量
    void getSpeedChangeSignal(float );//改变播放速度
    void getPlayPosChangeSignal(int );//改变播放位置

signals:
    void sendUpdatePixmapSignal();//发生更新图像信号
    void sendUpdateTimeSignal(QString ,int ,int );//发生更新视频时间信号

private:
    libvlc_instance_t * libvlc_instance = nullptr;
    libvlc_media_player_t *libvlc_media_player = nullptr;
    libvlc_media_t *libvlc_media = nullptr;
    static VideoPlayerWork *pThis;
    struct Context ctx;
    QPixmap *pix;
    int  videolength=0;
    QString counttime;
    QTimer* refreshtime;



};

#endif // VIDEOPLAYERWORK_H
