#ifndef VIDEOPLAYERINTERFACE_H
#define VIDEOPLAYERINTERFACE_H

#include <QWidget>
#include <QObject>

class VideoPlayerInterFace : public QWidget
{
    Q_OBJECT
public:
    VideoPlayerInterFace(QWidget *parent =0): QWidget(parent) {}
    virtual ~VideoPlayerInterFace() {}
    virtual VideoPlayerInterFace* createWidget(QWidget *parent = nullptr) =0;
    virtual void openFilePath() =0;

signals:
    void sendScreenshotPixmapSignal(QPixmap );
    void sendWidgetCloseSignal();
};

Q_DECLARE_INTERFACE(VideoPlayerInterFace, "VideoPlayerInterFace/01")
#endif // VIDEOPLAYERINTERFACE_H
