#ifndef GETUPDATEZIP_H
#define GETUPDATEZIP_H

#include <QWidget>
#include <QPainter>
#include <QThread>
#include <QScreen>
#include <QTimer>
#include <QEventLoop>
#include <QtNetwork>
#include <QDateTime>
#include <QProcess>
#include "Public/publicfunction.h"

namespace Ui {
class GetUpdateZip;
}

class QNetworkReply;
class QNetworkAccessManager;

class GetUpdateZip : public QWidget
{
    Q_OBJECT

public:
    explicit GetUpdateZip(const QString &version, const QString &url, QWidget *parent = nullptr);
    ~GetUpdateZip();
    void show();
    int exec();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::GetUpdateZip *ui;
    QString m_Url;
    QEventLoop m_Loop;
    int m_Ret;
    QNetworkReply *m_pNetworkReply;
    QString m_SaveFile;
    bool m_DownLoadSuccess;

    void initWidget();
    void resizeWidget();
    void downloadFile();

private slots:
    void onBtnUpdateClicked();
    void onBtnCancelClicked();
    void readReplyData();
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

signals:
    void updateFinished(int);
};

#endif // GETUPDATEZIP_H
