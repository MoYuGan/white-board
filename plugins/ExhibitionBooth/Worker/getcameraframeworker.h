#ifndef GETCAMERAFRAMEWORKER_H
#define GETCAMERAFRAMEWORKER_H

#include <QObject>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/mat.hpp"
#include <fcntl.h>
#include <QPixmap>
#include <QThread>
#include <QEventLoop>
using namespace  cv;

class GetCameraFrameWorker : public QObject
{
    Q_OBJECT
public:
    explicit GetCameraFrameWorker(QObject *parent = nullptr);
    void initWorker(const QString &deviceName, int resolutionWidth = -1, int resolutionHeight = -1);
    void setResolution(int resolutionWidth, int resolutionHeight);
    void setRotateAngle(int angle);
    int getRotateAngle();
    bool isRunning();
    QString getDeviceName();
    void stopRunning();
    QPixmap getCurrentFrame();
    void getResolution(int *width, int *height);

signals:
    void cameraClosed(int);
    void openCameraFinished();
    void newFrame(QPixmap);

public slots:
    void startWorker();

private:
    QString m_pDeviceName;
    int m_pResolutionWidth;
    int m_pResolutionHeight;
    VideoCapture m_pCap;
    bool m_pContinue;
    QImage m_pImage;
    int m_RotateAngle = 0;

private:
    bool openCamera();
    bool getFrame();
    QImage MatImageToQt(const Mat &src);
};

#endif // GETCAMERAFRAMEWORKER_H
