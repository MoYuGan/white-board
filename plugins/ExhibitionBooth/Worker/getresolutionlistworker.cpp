#include "getresolutionlistworker.h"
#include <QtDebug>

GetResolutionListWorker::GetResolutionListWorker(QObject *parent) : QObject(parent)
{
}

QVector<QString> GetResolutionListWorker::getResolutionList()
{
    return m_pResolutionList;
}

void GetResolutionListWorker::setDeviceName(const QString &deviceName)
{
    m_pDeviceName = deviceName;
}

void GetResolutionListWorker::startWorker()
{
    if (m_pDeviceName.isEmpty())
        return;

    fd = open(m_pDeviceName.toLatin1().data(), O_RDWR);
    if(fd == -1)
        return;

    if (-1 == this->V4L2_GetResolutionList())
        return;

    close(fd);
    emit getResolutionListFinished();
}

int GetResolutionListWorker::V4L2_GetResolutionList()
{
    m_pResolutionList.clear();

    fmtdesc.index = 0;
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) == -1)
        return -1;

    frmsizeenum.pixel_format = fmtdesc.pixelformat;
    for(int i = 0; ; i++)
    {
        frmsizeenum.index = i;
        if(ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsizeenum) != -1) {
            m_pResolutionList.push_back(QString("%1x%2").arg(frmsizeenum.discrete.width).arg(frmsizeenum.discrete.height));

        }else
            break;
    }
    return 0;
}
