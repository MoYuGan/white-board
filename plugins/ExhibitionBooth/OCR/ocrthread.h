#ifndef OCRTHREAD_H
#define OCRTHREAD_H

#include <QThread>
#include "ocrworker.h"

class OcrThread : public QObject
{
    Q_OBJECT
public:
    explicit OcrThread(QObject *parent = nullptr) {
        //创建线程
        m_pThread = new QThread;
        //创建一个新的工作类
        m_pOCRWorker = new OCR_Worker();
        //加入线程
        m_pOCRWorker->moveToThread(m_pThread);
        //连接信号和槽
        connect(m_pThread, &QThread::started, m_pOCRWorker, &OCR_Worker::startWorker);
        connect(m_pOCRWorker, &OCR_Worker::workFinished, this, &OcrThread::onWorkFinished);
    }

    ~OcrThread() {
        if (m_pThread)
            delete m_pThread;
        if (m_pOCRWorker)
            delete m_pOCRWorker;
    }

    bool isRunning() {
        if (nullptr != m_pThread)
            return m_pThread->isRunning();
        else
            return false;
    }

    QStringList getWordList() {
        return m_pWordList;
    }

    void start(const QPixmap &pixmap) {
        m_pWordList.clear();
        m_pOCRWorker->setPixmap(pixmap);
        qDebug()<<"start ------------";
        //启动线程
        m_pThread->start();
    }

public slots:
    void releaseThread(){
        if (nullptr != m_pThread) {
            //删除工作类
            disconnect(m_pOCRWorker, &OCR_Worker::workFinished, this, &OcrThread::onWorkFinished);
            //强制退出线程
            m_pThread->exit(0);
            //等待线程退出
            m_pThread->wait();
            //删除线程
            delete m_pThread;
            delete m_pOCRWorker;
            m_pOCRWorker = nullptr;
            m_pThread = nullptr;
        }
    }

signals:
    void workFinished(int);

private:
    QThread *m_pThread;
    OCR_Worker *m_pOCRWorker;
    QStringList m_pWordList;

private slots:
    void onWorkFinished(int i) {
        if (1 == i) {
            m_pWordList = m_pOCRWorker->getWordList();
            if (0 == m_pWordList.size())
                i = -1;
        }
        emit workFinished(i);
    }
};


#endif // OCRTHREAD_H
