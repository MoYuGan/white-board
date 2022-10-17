#include "getcameraframeworker.h"
#include <QEventLoop>
#include <QtDebug>
#include <QTimer>
GetCameraFrameWorker::GetCameraFrameWorker(QObject *parent) : QObject(parent)
{

}

void GetCameraFrameWorker::initWorker(const QString &deviceName, int resolutionWidth, int resolutionHeight)
{
    m_pDeviceName = deviceName;
    m_pResolutionWidth = resolutionWidth;
    m_pResolutionHeight = resolutionHeight;
}

void GetCameraFrameWorker::setResolution(int resolutionWidth, int resolutionHeight)
{
    this->initWorker(m_pDeviceName, resolutionWidth, resolutionHeight);
}

void GetCameraFrameWorker::setRotateAngle(int angle)
{
    m_RotateAngle = angle;
}

int GetCameraFrameWorker::getRotateAngle()
{
    return m_RotateAngle;
}

bool GetCameraFrameWorker::isRunning()
{
    return m_pCap.isOpened();
}

QString GetCameraFrameWorker::getDeviceName()
{
    return m_pDeviceName;
}

void GetCameraFrameWorker::stopRunning()
{
    m_pContinue = false;
    m_pCap.release();
}

QPixmap GetCameraFrameWorker::getCurrentFrame()
{
    if (m_pImage.isNull())
        return QPixmap();
    else
        return QPixmap::fromImage(m_pImage);
}

void GetCameraFrameWorker::getResolution(int *width, int *height)
{
    if (m_pCap.isOpened()) {
        *width = m_pCap.get(cv::CAP_PROP_FRAME_WIDTH);
        *height = m_pCap.get(cv::CAP_PROP_FRAME_HEIGHT);
    }else {
        *width = -1;
        *height = -1;
    }
}

void GetCameraFrameWorker::startWorker()
{
    qDebug()<<"---------start get frame";
    //打开摄像头
    if (!this->openCamera()) {
        emit cameraClosed(-2);
        return;
    }

    int ret = 0;
    int badFrameCount = 0;
    m_pContinue = true;
    //循环获取帧
    while(m_pContinue) {
        //获取图像为空，设备异常断开
        if (!this->getFrame()) {
            qDebug()<<"---------get bad frame: "<<badFrameCount;
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
        emit newFrame(QPixmap::fromImage(m_pImage));
        QThread::msleep(50);
    }

    qDebug()<<"---------stop get frame.";
    //释放

    //m_pCap.release();
    //发送关闭信号
    emit cameraClosed(ret);
}

bool GetCameraFrameWorker::openCamera()
{
    if (!m_pDeviceName.isEmpty()) {
        if (m_pCap.open(m_pDeviceName.toStdString())) {
            if (-1 !=  m_pResolutionWidth && -1 != m_pResolutionHeight) {
                if (!m_pCap.set(cv::CAP_PROP_FRAME_WIDTH, m_pResolutionWidth))
                   qDebug()<<"set frame width failed";
                if (!m_pCap.set(cv::CAP_PROP_FRAME_HEIGHT, m_pResolutionHeight))
                   qDebug()<<"set frame height failed";
            }
            emit openCameraFinished();
            return true;
        }
    }
    return false;
}

//获取帧
bool GetCameraFrameWorker::getFrame()
{
    if (!m_pCap.isOpened()) {
        return false;
    }

    Mat srcMat;

    if (!m_pCap.read(srcMat))
        return false;

    if (!srcMat.data)
        return false;

    /* 旋转 */
    Mat dstMat, rotMat;
    cv::Point center(srcMat.cols/2, srcMat.rows/2);
    rotMat = getRotationMatrix2D(center, m_RotateAngle, 1.0);
    cv::warpAffine(srcMat, dstMat, rotMat, srcMat.size());

    m_pImage = MatImageToQt(dstMat);
    if (m_pImage.isNull())
        return false;

    return true;
}

//Mat转成QImage
QImage GetCameraFrameWorker::MatImageToQt(const Mat &src)
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
