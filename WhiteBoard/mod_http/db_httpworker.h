#ifndef DB_HTTPWORKER_H
#define DB_HTTPWORKER_H

#include <QObject>
#include "mod_http/db_httpinterface.h"

/*
*   执行http请求的线程对象
*/

class DB_HttpWorker : public QObject
{
    Q_OBJECT
public:
    explicit  DB_HttpWorker(QObject *parent = nullptr);
    void setArgs(QStringList args);
    void setHttpFun(HttpFunction fun);
    inline QVariant getRetData() { return m_pRetData; }

public slots:
    void startWorker(); 
    // 下载进度实时返回
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QStringList m_pArgs;        //参数
    HttpFunction m_pHttpFun;    //请求接口
    QVariant m_pRetData;        //返回数据

signals:
    void workFinished();
    void downloadProgress(qint64, qint64);
};

#endif // DB_HTTPWORKER_H
