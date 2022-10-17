#ifndef DB_CAMERA_H
#define DB_CAMERA_H

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <QObject>
#include <QTimer>
#include <QImage>
#include <QtDebug>
#include <QPainter>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QThread>
#include <QPointer>
#include <QEvent>
#include <QBrush>
#include <QCamera>
#include <QEventLoop>

#include "boardview.h"

using namespace  cv;
using namespace  std;

//旋转角度
enum RotationAngle{
    rotateLeft,         //逆时针90度,顺时针270度
    rotateDown,         //逆时针180度,顺时针180度
    rotateRight,        //逆时针270度,顺时针90度
    None
};

class DisplayView : public QWidget
{
public:
    DisplayView(QWidget *parent = Q_NULLPTR) : QWidget(parent) {
        this->setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
        this->setPalette(palette);
        this->installEventFilter(this);
    }

    QPixmap getPixmap() {
        return m_pPixmap;
    }

    void setPixmap(const QPixmap &pixmap) {
        m_pPixmap = pixmap;
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Background, QBrush(pixmap.scaled(this->size())));

        this->setPalette(palette);
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);

        if (!m_pPixmap.isNull()) {
            this->setPixmap(m_pPixmap);
        }
    }

private:
    QPixmap m_pPixmap;
};


class DB_Camera : public QObject
{
    Q_OBJECT
public:
    DB_Camera(QObject *parent = Q_NULLPTR) : QObject(parent) {
    }

    ~DB_Camera() {
        foreach(QWidget *widget, m_pDisplayWidget) {
            if (nullptr != widget)
                widget->deleteLater();
        }
    }

    QPixmap getDisplayPixmap(QWidget *widget) {
        //没有查询到显示器，返回
        if (-1 == m_pDisplayWidget.indexOf(widget))
            return QPixmap();
        DisplayView *view = static_cast<DisplayView *>(widget);
        return view->getPixmap();
    }

    //获取当前帧
    QImage getCurrentFrame() {
        return m_pImage;
    }

    //创建显示器,可创建多个显示器，需要设置显示器名字
    QWidget *createDisplayWidget() {
        QPointer<DisplayView> pw = new DisplayView;
        QWidget *widget = pw.data();
        widget->setMouseTracking(true);
        m_pDisplayWidget.push_back(widget);

        return widget;
    }


    void initDevice(const QString &deviceName, int resolutionWidth = -1, int resolutionHeight = -1) {
        m_pDeviceName = deviceName;
        m_pResolutionWidth = resolutionWidth;
        m_pResolutionHeight = resolutionHeight;
    }

    //关闭摄像头
    void stopCamera() {
        QEventLoop loop;
        connect(this, &DB_Camera::cameraClosed, &loop, &QEventLoop::quit);

        m_pContinue = false;
        loop.exec();
    }

    bool isRunning() {
        return m_pCap.isOpened();
    }

    QString getDeviceName() {
        return m_pDeviceName;
    }

    void getResolution(int *width, int *height) {
        if (m_pCap.isOpened()) {
            *width =  m_pCap.get(cv::CAP_PROP_FRAME_WIDTH);
            *height =  m_pCap.get(cv::CAP_PROP_FRAME_HEIGHT);
        }else {
            *width = -1;
            *height = -1;
        }
    }

    //逆时针旋转
    void setRotationAngleWithAnti() {
        if (RotationAngle::None == m_pRotationAngle) {
            m_pRotationAngle = RotationAngle::rotateLeft;
        }else if (RotationAngle::rotateLeft == m_pRotationAngle) {
            m_pRotationAngle = RotationAngle::rotateDown;
        }else if (RotationAngle::rotateDown == m_pRotationAngle) {
            m_pRotationAngle = RotationAngle::rotateRight;
        }else if (RotationAngle::rotateRight == m_pRotationAngle) {
            m_pRotationAngle = RotationAngle::None;
        }
    }

    //设置静态图片(参数一：显示器名，参数二：静态图片)
    void setStaticPixmap(QWidget *widget, const QPixmap &pixmap) {
        //没有查询到显示器，返回
        if (-1 == m_pDisplayWidget.indexOf(widget))
            return;

        if (-1 == m_pStaticDisplay.indexOf(widget))
            m_pStaticDisplay.push_back(widget);

        if (!pixmap.isNull()) {
            DisplayView *view = static_cast<DisplayView *>(widget);
            view->setPixmap(pixmap);
        }
    }

    //取消静态显示
    void cancelStaticDisplay(QWidget *widget) {
        m_pStaticDisplay.removeOne(widget);
    }

public slots:
    //开始获取摄像头图像
    void startGetFrame() {
        //打开摄像头
        if (!m_pDeviceName.isEmpty() && this->openCamera(m_pDeviceName))
            ;
        else {
            emit cameraClosed(-2);
            return;
        }

        qDebug()<<m_pResolutionWidth<<m_pResolutionHeight;
        if (-1 !=  m_pResolutionWidth && -1 != m_pResolutionHeight) {
            m_pCap.set(cv::CAP_PROP_FRAME_WIDTH, m_pResolutionWidth);
            m_pCap.set(cv::CAP_PROP_FRAME_HEIGHT, m_pResolutionHeight);
        }

        qDebug()<<"w:"<<m_pCap.get(cv::CAP_PROP_FRAME_WIDTH)<<"h:"<<m_pCap.get(cv::CAP_PROP_FRAME_HEIGHT);

        int ret = 0;
        int badFrameCount = 0;
        m_pContinue = true;
        //循环获取帧
        while(m_pContinue) {
            //获取图像为空，设备异常断开
            if (!this->getFrame()) {
                if (badFrameCount > 100) {  //超过3S获取到的帧都是空值
                    ret = -1;
                    break;
                }else {
                    badFrameCount++;
                    QThread::msleep(30);
                    continue;
                }
            }

            badFrameCount = 0;
            foreach(QWidget *widget, m_pDisplayWidget) {
                if (m_pStaticDisplay.indexOf(widget) != -1)
                    continue;

                DisplayView *view = static_cast<DisplayView *>(widget);
                view->setPixmap(QPixmap::fromImage(m_pImage));
            }

            QThread::msleep(50);
        }

        //释放
        m_pCap.release();
        //发送关闭信号
        emit cameraClosed(ret);
    }


private:
    QVector<QWidget *> m_pDisplayWidget;        //显示器
    QVector<QWidget *> m_pStaticDisplay;        //静态显示器
    QImage m_pImage;                            //当前帧
    VideoCapture m_pCap;
    RotationAngle m_pRotationAngle = RotationAngle::None;
    bool m_pContinue = true;
    DB_BoardView *displayView = nullptr;
    QStringList m_pSupportResolutions;
    QString m_pDeviceName = QString();
    int m_pResolutionWidth = -1;
    int m_pResolutionHeight = -1;

signals:
    void cameraClosed(int);

private:
    //打开摄像头
    bool openCamera(const QString &deviceName) {
        bool ret;
        ret =  m_pCap.open(deviceName.toStdString());
        return ret;
    }

    //获取帧
    bool getFrame() {
        if (!m_pCap.isOpened()) {
            return false;
        }

        Mat srcMat;
        m_pCap.read(srcMat);
        if (!srcMat.data)
            return false;

        /* 旋转 */
        int angle = 0;
        if (RotationAngle::rotateLeft == m_pRotationAngle) {
            angle = 90;
        }else if (RotationAngle::rotateDown == m_pRotationAngle) {
            angle = 180;
        }else if (RotationAngle::rotateRight == m_pRotationAngle) {
            angle = -90;
        }
        Mat dstMat, rotMat;
        cv::Point center(srcMat.cols/2, srcMat.rows/2);
        rotMat = getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(srcMat, dstMat, rotMat, srcMat.size());

        m_pImage = MatImageToQt(dstMat);
        if (m_pImage.isNull())
            return false;

        return true;
    }

    //Mat转成QImage
    QImage MatImageToQt(const Mat &src)
    {
        //CV_8UC1 8位无符号的单通道---灰度图片
        if(src.type() == CV_8UC1)
        {
            //使用给定的大小和格式构造图像
            //QImage(int width, int height, Format format)
            QImage qImage(src.cols,src.rows,QImage::Format_Indexed8);
            //扩展颜色表的颜色数目
            qImage.setColorCount(256);

            //在给定的索引设置颜色
            for(int i = 0; i < 256; i ++)
            {
                //得到一个黑白图
                qImage.setColor(i,qRgb(i,i,i));
            }
            //复制输入图像,data数据段的首地址
            uchar *pSrc = src.data;
            //
            for(int row = 0; row < src.rows; row ++)
            {
                //遍历像素指针
                uchar *pDest = qImage.scanLine(row);
                //从源src所指的内存地址的起始位置开始拷贝n个
                //字节到目标dest所指的内存地址的起始位置中
                memcmp(pDest,pSrc,src.cols);
                //图像层像素地址
                pSrc += src.step;
            }
            return qImage;
        }
        //为3通道的彩色图片
        else if(src.type() == CV_8UC3)
        {
//            Size dsize = Size(1920, 1080);
//            Mat outMat = Mat(dsize, CV_32S);
//            cv::resize(src, outMat, dsize);
            //得到图像的的首地址
            const uchar *pSrc = (const uchar*)src.data;
            //以src构造图片
            QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888);
            //在不改变实际图像数据的条件下，交换红蓝通道
            return qImage.rgbSwapped();
        }
        //四通道图片，带Alpha通道的RGB彩色图像
        else if(src.type() == CV_8UC4)
        {
            const uchar *pSrc = (const uchar*)src.data;
            QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
            //返回图像的子区域作为一个新图像
            return qImage.copy();
        }
        else
        {
            return QImage();
        }
    }
};

#endif // DB_CAMERA_H
