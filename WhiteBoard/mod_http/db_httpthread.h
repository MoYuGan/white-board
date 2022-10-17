#ifndef DB_HTTPTHREAD_H
#define DB_HTTPTHREAD_H

#include <QObject>
#include <QThread>
#include "mod_http/db_httpworker.h"

class DB_HttpThread : public QObject
{
    Q_OBJECT
public:
    explicit DB_HttpThread(QObject *parent = nullptr);
    ~DB_HttpThread();
    void start(HttpFunction fun, const QList<QString> &args = QList<QString>());
    void stop();

signals:
    void httpThreadFinished(HttpFunction, QVariant);
public slots:
    void onThreadFinished();
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
private:
    QThread *m_pThread;
    DB_HttpWorker *m_pHttpWorker;
    HttpFunction m_pHttpFun;
signals:
    void downloadProgress(qint64, qint64);
};

#endif // DB_HTTPTHREAD_H
