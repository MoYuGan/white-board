#ifndef EXPORTFILE_H
#define EXPORTFILE_H

#include <QWidget>
#include <QPixmap>
#include <QThread>
#include "mod_draw/boardview.h"

namespace Ui {
class ExportFile;
}

/************  export file worker ****************/

class ExportFileWorker: public QObject
{
    Q_OBJECT
public:
    ExportFileWorker(QObject *parent = Q_NULLPTR);
    void mSetPixmapList(QList<QPixmap> *pixmapList);
    void mSetSavePath(const QString &path);

public slots:
    void startWorker();

signals:
    void progressChanged(int);
    void workFinished();

private:
    QList<QPixmap> *m_PixmapList = nullptr;
    QString m_SavePath;


private:
    void saveToPDF();
};



/*********************************************/

class ExportFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExportFileWidget(QWidget *parent = 0);
    ~ExportFileWidget();
    void show();
    void saveFile(QList<QPixmap> pixmapList, const QString &savePath);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::ExportFile *ui;
    QString m_pExportPath;
    QThread *m_Thread = nullptr;
    ExportFileWorker *m_Worker = nullptr;
    QString m_SavePath;
    QList<QPixmap> m_PixmapList;

    void initWidget();
    void resizeWidget();
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
