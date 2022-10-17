#ifndef ERASERTHREAD_H
#define ERASERTHREAD_H

#include <QObject>
#include <QThread>
#include <QEventLoop>
#include "eraserworker.h"
#include <QtDebug>

class EraserThread : public QObject
{
    Q_OBJECT
public:
    explicit EraserThread(QObject *parent = nullptr) {
        m_pEraserWorker = nullptr;
        m_pThread = nullptr;
    }

    ~EraserThread() {
        if (m_pThread)
            delete m_pThread;
        if (m_pEraserWorker)
            delete m_pEraserWorker;
    }

    bool isRunning() {
        if (nullptr != m_pThread) {
            return m_pThread->isRunning();
        }else
            return false;
    }

    void setNewAction(QVector<QGraphicsItem *> items,
                       const QPainterPath &path,
                       QVector<QLineF> lineVector) {
        qDebug()<<"set new action";
        m_pEraserWorker->setNewAction(items, path, lineVector);
        qDebug()<<"set new action finished";
    }

    QMap<QGraphicsItem *, QPainterPath> getResult() {
        return m_pResult;
    }

    void start() {
        //创建线程
        m_pThread = new QThread;
        //创建一个新的工作类
        m_pEraserWorker = new EraserWorker();
        //加入线程
        m_pEraserWorker->moveToThread(m_pThread);
        //连接信号和槽
        connect(m_pThread, &QThread::started, m_pEraserWorker, &EraserWorker::startWorker);
        connect(m_pEraserWorker, &EraserWorker::workFinished, this, &EraserThread::onWorkFinished);
        //启动线程
        m_pThread->start();
    }

public slots:
    void stop(){
        m_pEraserWorker->stop();
    }

signals:
    void threadFinished();

private:
    QThread *m_pThread;
    EraserWorker *m_pEraserWorker;
    QMap<QGraphicsItem *, QPainterPath> m_pResult;

private slots:
    void onWorkFinished() {
        m_pResult = m_pEraserWorker->getResult();
        delete m_pEraserWorker;
        if (m_pThread->isRunning()) {
            //强制退出线程
            m_pThread->exit(0);
            //等待线程退出
            m_pThread->wait();
        }
        delete m_pThread;
        m_pThread = nullptr;
        emit threadFinished();
    }
};

#endif // ERASERTHREAD_H
