#ifndef EXPORTFILE_H
#define EXPORTFILE_H

#include <QWidget>
#include <QPixmap>
#include <QThread>
#include "Draw/boardview.h"

namespace Ui {
class ExportFile;
}

/************  export file worker ****************/

class ExportFileWorker: public QObject
{
    Q_OBJECT
public:
    ExportFileWorker(BoardView* view, const QString path, QObject *parent = Q_NULLPTR):
        m_pBoardView(view),
        m_pExportPath(path),
        QObject(parent)
    {}

public slots:
    void startWorker() {
        QVector<QPixmap> vector;
        for(int i = 0; i < m_pBoardView->getScenesListSize(); i++) {
            QPixmap pixmap;
            m_pBoardView->getScenePixmap(i, &pixmap);
            vector.push_back(pixmap);
        }
        QString fileName;
        for(int i = 0; i < vector.size();) {
            QPixmap pixmap = vector.at(i);
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
    BoardView *m_pBoardView;
    QString m_pExportPath;
};



/*********************************************/

class ExportFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExportFileWidget(BoardView* view, const QString path, QWidget *parent = 0);
    ~ExportFileWidget();
    void show();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::ExportFile *ui;
    BoardView *m_pBoardView;
    QString m_pExportPath;
    QThread *m_pThread;
    ExportFileWorker *m_pWorker;

    void initWidget();
    void resize();
    void deleteThread();

private slots:
    void onValueChanged(int value);
    void onExportFileWorkerFinished();
    void onCancelBtnClicked();
    void onShowFileBtnClicked();

signals:
    void threadFinished();
};

#endif // EXPORTFILE_H
