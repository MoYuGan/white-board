#include "db_httpthread.h"

DB_HttpThread::DB_HttpThread(QObject *parent) : QObject(parent)
{
    //使得HttpFunction可用信号传送
    qRegisterMetaType<HttpFunction>("HttpFunction");

    m_pHttpWorker = nullptr;
    m_pThread = nullptr;
}

DB_HttpThread::~DB_HttpThread()
{
    if (m_pThread)
        delete m_pThread;
    if (m_pHttpWorker)
        delete m_pHttpWorker;
}

/*
 * 功能：http请求
 * 参数：
 *  fun：请求接口
 *  args：请求参数
*/
void DB_HttpThread::start(HttpFunction fun, const QList<QString> &args)
{
    m_pHttpFun = fun;

    //创建线程
    m_pThread = new QThread;
    connect(m_pThread, &QThread::finished, this, &DB_HttpThread::onThreadFinished);
    //创建一个新的工作类
    m_pHttpWorker = new DB_HttpWorker;
    m_pHttpWorker->setHttpFun(m_pHttpFun);
    m_pHttpWorker->setArgs(args);
    if (HttpFunction::DownloadFile == m_pHttpFun)
        connect(m_pHttpWorker, &DB_HttpWorker::downloadProgress, this, &DB_HttpThread::onDownloadProgress);
    //加入线程
    m_pHttpWorker->moveToThread(m_pThread);
    //连接信号和槽
    connect(m_pThread, &QThread::started, m_pHttpWorker, &DB_HttpWorker::startWorker);
    connect(m_pHttpWorker, &DB_HttpWorker::workFinished, m_pThread, &QThread::quit);
    //启动线程
    m_pThread->start();
}

//强制退出
void DB_HttpThread::stop()
{
    if (nullptr != m_pThread) {
        //删除工作类
        delete m_pHttpWorker;
        //断开信号与槽
        disconnect(m_pThread, &QThread::finished, this, &DB_HttpThread::onThreadFinished);
        //强制退出线程
        m_pThread->exit(0);
        //等待线程退出
        m_pThread->wait();
        //删除线程
        delete m_pThread;

        m_pHttpWorker = nullptr;
        m_pThread = nullptr;
    }
}


//线程退出
void DB_HttpThread::onThreadFinished()
{
    QVariant variant = m_pHttpWorker->getRetData();
    this->stop();
    //发送信号
    emit httpThreadFinished(m_pHttpFun, variant);
}

void DB_HttpThread::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    emit this->downloadProgress(bytesReceived, bytesTotal);
}
