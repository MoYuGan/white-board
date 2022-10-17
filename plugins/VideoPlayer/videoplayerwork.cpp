#include "videoplayerwork.h"
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QTime>

#define VIDEO_WIDTH   4096
#define VIDEO_HEIGHT  2160
VideoPlayerWork* VideoPlayerWork::pThis = nullptr;

VideoPlayerWork::VideoPlayerWork(QObject *parent)
    : QObject{parent}
{
    pThis =this;
    refreshtime = new QTimer(this);

    connect(refreshtime,&QTimer::timeout,this,[=](){
        /**获取当前视频的播放进度**/
       libvlc_time_t currenttime = libvlc_media_player_get_time(libvlc_media_player);
       QString currenttime_str =calculateTime(currenttime);
       emit sendUpdateTimeSignal(currenttime_str + " / " +counttime,videolength,(int)(currenttime/1000));
       refreshtime->start(1000);
    });
}

VideoPlayerWork::~VideoPlayerWork()
{

}

void *VideoPlayerWork::lock(void *opaque, void **planes)
{
    struct Context *ctx = static_cast<Context *>(opaque);
    ctx->mutex.lock();
    *planes = ctx->pixels;
    return nullptr;
}

void VideoPlayerWork::unlock(void *opaque, void *picture, void * const *planes)
{
    Q_UNUSED(picture);
    struct Context *ctx = static_cast<Context *>(opaque);
    unsigned char *data = static_cast<unsigned char *>(*planes);
    QImage image(data, VIDEO_WIDTH, VIDEO_HEIGHT, QImage::Format_RGBA8888);
    VideoPlayerWork::pThis->updatePixmap(image);
    ctx->mutex.unlock();
}

void VideoPlayerWork::display(void *opaque, void *picture)
{
    Q_UNUSED(picture);
    (void)opaque;
}

void VideoPlayerWork::updatePixmap(const QImage &image)
{
    *pix = QPixmap::fromImage(image); 
    emit sendUpdatePixmapSignal();
}

QString VideoPlayerWork::calculateTime(libvlc_time_t timenumber)
{
    timenumber /= 1000;
    int h = timenumber/3600;
    int m = (timenumber-h*3600)/60;
    int s = timenumber-h*3600-m*60;
    QString hour= h<10? QString("0%1").arg(h):QString("%1").arg(h);
    QString minute= m<10? QString("0%1").arg(m):QString("%1").arg(m);
    QString second= s<10? QString("0%1").arg(s):QString("%1").arg(s);
    QString length= hour +":" +minute +":" +second;
    return length;
}

void VideoPlayerWork::getStartPalySignal(QString filepath, int volumenum, float speednum, QPixmap *pixmap,int *videowidth,int *videoheight)
{
    qDebug()<<QThread::currentThreadId();
    if(libvlc_media_player !=nullptr){
        libvlc_media_player_stop(libvlc_media_player);
        libvlc_media_player_release(libvlc_media_player);
    }
    pix= pixmap;
    if(refreshtime->isActive())refreshtime->stop();
    ctx.pixels = new uchar[VIDEO_WIDTH * VIDEO_HEIGHT* 4];
    memset(ctx.pixels, 0, VIDEO_WIDTH * VIDEO_HEIGHT * 4);
    std::string str = filepath.toStdString();
    const char* m_name = str.c_str();

    int vlc_argc = 0;
    const char * const vlc_argv[] = {"--vout=direct2d",};
    vlc_argc = sizeof(vlc_argv) / sizeof(vlc_argv[0]);
    libvlc_instance = libvlc_new (vlc_argc, vlc_argv);

    //libvlc_instance = libvlc_new (0, nullptr);
    libvlc_media = libvlc_media_new_path (libvlc_instance, m_name);
    libvlc_media_player = libvlc_media_player_new_from_media (libvlc_media);
    libvlc_media_release (libvlc_media);

    libvlc_video_set_callbacks(libvlc_media_player,lock,unlock,display,&ctx);
    libvlc_video_set_format(libvlc_media_player, "RGBA", VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH * 4);
    if(libvlc_media_player != nullptr)libvlc_audio_set_volume(libvlc_media_player,volumenum);
    if(libvlc_media_player != nullptr)libvlc_media_player_set_rate( libvlc_media_player, speednum);
    libvlc_media_player_play (libvlc_media_player);

    getPausePlaySignal();
    QThread::msleep(1000);
    getContinuePlaySignal();
    /**获取视频的总时长**/
    libvlc_time_t counttimelength = libvlc_media_player_get_length(libvlc_media_player);
    counttime =calculateTime(counttimelength);
    videolength =(int)(counttimelength/1000);
    *videowidth =libvlc_video_get_width(libvlc_media_player);
    *videoheight =libvlc_video_get_height(libvlc_media_player);
    refreshtime->start(10);
}

void VideoPlayerWork::getPausePlaySignal()
{
    refreshtime->stop();
    libvlc_media_player_set_pause(libvlc_media_player,1);
}

void VideoPlayerWork::getContinuePlaySignal()
{
    refreshtime->start(1);
    libvlc_media_player_set_pause(libvlc_media_player,0);
}

void VideoPlayerWork::getStopPlaySignal()
{
    if(libvlc_media_player !=nullptr)
    {
        libvlc_media_player_stop(libvlc_media_player);
        libvlc_media_player =nullptr;
    }
    refreshtime->stop();
}

void VideoPlayerWork::getCloseSignal()
{
    getStopPlaySignal();
    if(libvlc_media_player !=nullptr){
        libvlc_media_player_stop(libvlc_media_player);
        libvlc_media_player_release(libvlc_media_player);
    }
    if(libvlc_instance !=nullptr)libvlc_release(libvlc_instance);
}

void VideoPlayerWork::getVolumeChangeSignal(int number)
{
    if(libvlc_media_player != nullptr)libvlc_audio_set_volume(libvlc_media_player,number);
}

void VideoPlayerWork::getSpeedChangeSignal(float number)
{
    if(libvlc_media_player != nullptr)libvlc_media_player_set_rate( libvlc_media_player, number);
}

void VideoPlayerWork::getPlayPosChangeSignal(int number)
{
    bool isplay =false;
    if(libvlc_media_player_is_playing(libvlc_media_player) ==1)isplay=true;
    getPausePlaySignal();
    if(libvlc_media_player != nullptr)libvlc_media_player_set_position(libvlc_media_player,(float)number/videolength);
    if(isplay)getContinuePlaySignal();

}



