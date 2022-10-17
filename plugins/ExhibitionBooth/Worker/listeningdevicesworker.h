#ifndef LISTENINGDEVICESWORKER_H
#define LISTENINGDEVICESWORKER_H

#include <QObject>
#include <QVector>
#include <QCameraInfo>
#include <QThread>

class ListeningDevicesWorker : public QObject
{
    Q_OBJECT
public:
    explicit ListeningDevicesWorker(QObject *parent = nullptr);
    QVector<QString> getDevicesDescription();
    QString getDeviceName(int index);
    QVector<QString> getDeviceNameList();
    void stopWorker();
    bool isRunning();
signals:
    void deviceNumChanged();
public slots:
    void startWorker();

private:
    QVector<QString> m_pDevicesDescription;
    QVector<QString> m_pDevicesName;
    bool m_Continue;
    bool m_IsRunning;
};

#endif // LISTENINGDEVICESWORKER_H
