#include "db_httpworker.h"
#include <QThread>

DB_HttpWorker::DB_HttpWorker(QObject *parent) :
    QObject(parent)
{}

//设置接口参数
void DB_HttpWorker::setArgs(QStringList args)
{
    this->m_pArgs = args;
}

//设置接口
void DB_HttpWorker::setHttpFun(HttpFunction fun)
{
    m_pHttpFun = fun;
}

//开始请求
void DB_HttpWorker::startWorker()
{
    do {
        DB_HttpInterface *httpinterface = DB_HttpInterface::getInstace();
//        if (HttpFunction::DownloadFile ==  m_pHttpFun) {
//            httpinterface->downloadFileRequest(this->m_pArgs);
//            connect(httpinterface, &DB_HttpInterface::downloadProgress, this, &DB_HttpWorker::onDownloadProgress);
//            connect(httpinterface, &DB_HttpInterface::downloadFileFinished, [=](){ emit workFinished(); });
//        }else {
            _HttpRetData data = httpinterface->httpRequest(m_pHttpFun, this->m_pArgs, QVariant());
            m_pRetData = QVariant::fromValue(data);
            emit workFinished();
//        }

    }while(0);
}

void DB_HttpWorker::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    emit this->onDownloadProgress(bytesReceived, bytesTotal);
}

