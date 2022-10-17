#ifndef GETRESOLUTIONLISTWORKER_H
#define GETRESOLUTIONLISTWORKER_H

#include <QObject>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include <QVector>
#include <sys/ioctl.h>

static struct v4l2_fmtdesc fmtdesc;
static struct v4l2_frmsizeenum frmsizeenum;
static int fd = -1;

class GetResolutionListWorker : public QObject
{
    Q_OBJECT
public:
    explicit GetResolutionListWorker(QObject *parent = nullptr);
    QVector<QString> getResolutionList();
    void setDeviceName(const QString &deviceName);
signals:
    void getResolutionListFinished();
public slots:
    void startWorker();

private:
    QVector<QString> m_pResolutionList;
    QString m_pDeviceName;

    int V4L2_GetResolutionList();
};

#endif // GETRESOLUTIONLISTWORKER_H
