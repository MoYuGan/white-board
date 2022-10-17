#ifndef EXPORTFILE_H
#define EXPORTFILE_H

#include <QWidget>
#include <QPixmap>
#include <QThread>

#include "Public/publicfunction.h"

namespace Ui {
class ExportFile;
}

/************  export file worker ****************/

class ExportFileWorker: public QObject
{
    Q_OBJECT
public:
    ExportFileWorker(QList<QPixmap> *pixmapList,
                     const QString path, QObject *parent = Q_NULLPTR):
        m_PixmapList(pixmapList),
        m_pExportPath(path),
        QObject(parent)
    {}

public slots:
    void startWorker() {
        QString fileName;
        for(int i = 0; i < m_PixmapList->size();) {
            QPixmap pixmap = m_PixmapList->at(i);
            fileName = QString("%1/第%2页.png").arg(m_pExportPath).arg(++i);
            pixmap.save(fileName);
            emit progressChanged(i);
        }
        emit workFinished();
    }

signals:
    void progressChanged(int);
    void workFinished();

private:
    QString m_pExportPath;
    QList<QPixmap> *m_PixmapList;
};



/*********************************************/

class ExportFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExportFileWidget(QList<QPixmap> *pixmapList, const QString path, QWidget *parent = 0);
    ~ExportFileWidget();
    void show();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::ExportFile *ui;
    QString m_pExportPath;
    ExportFileWorker *m_pWorker;
    QThread *m_pThread;
    QList<QPixmap> *m_PixmapList;

    void initWidget();
    void resize();
    void deleteThread();

private slots:
    void onValueChanged(int value);
    void onExportFileWorkerFinished();
    void onCancelBtnClicked();

signals:
    void threadFinished();
};

#endif // EXPORTFILE_H
