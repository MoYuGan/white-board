#include "listeningdevicesworker.h"

ListeningDevicesWorker::ListeningDevicesWorker(QObject *parent) : QObject(parent)
{

}

QVector<QString> ListeningDevicesWorker::getDevicesDescription()
{
    return m_pDevicesDescription;
}

QString ListeningDevicesWorker::getDeviceName(int index)
{
    if (index < 0 || index >= m_pDevicesName.size())
        return QString();

    return m_pDevicesName.at(index);
}

QVector<QString> ListeningDevicesWorker::getDeviceNameList()
{
    return m_pDevicesName;
}

void ListeningDevicesWorker::stopWorker()
{
    m_Continue = false;
}

bool ListeningDevicesWorker::isRunning()
{
    return m_IsRunning;
}

void ListeningDevicesWorker::startWorker()
{
    m_Continue = true;
    m_IsRunning = true;
    //监听设备，设备列表有改变，发送信号
    while(m_Continue) {
        QList<QCameraInfo> cameraInfoList = QCameraInfo::availableCameras();
        qDebug()<<"get camera info list:"<<cameraInfoList;
        if (cameraInfoList.size() == m_pDevicesDescription.size()) {
            QThread::msleep(300);
            continue;
        }

        m_pDevicesDescription.clear();
        m_pDevicesName.clear();
        foreach (QCameraInfo cameraInfo, cameraInfoList) {
            m_pDevicesDescription.push_back(cameraInfo.description());
            m_pDevicesName.push_back(cameraInfo.deviceName());
        }

        emit deviceNumChanged();
    }
    m_IsRunning = false;
}
