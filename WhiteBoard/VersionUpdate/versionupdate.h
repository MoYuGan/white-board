#ifndef VERSIONUPDATE_H
#define VERSIONUPDATE_H

#include <QWidget>
#include <QPainterPath>
#include "mod_http/db_httpinterface.h"

namespace Ui {
class VersionUpdate;
}

class VersionUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit VersionUpdate(const QString& url, const QString &fileName, QWidget *parent = 0);
    ~VersionUpdate();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pushButton_update_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_cancelUpdate_clicked();
    void on_pushButton_restart_clicked();
    void onDownloadProgress(qint64, qint64);
    void onDownloadUpdatePackageResult();

    void on_pushButton_update_2_clicked();

    void on_pushButton_cancel_2_clicked();

private:
    Ui::VersionUpdate *ui;
    QString m_pUrl;
    QString m_pFileName;
    QString sudostr;
    QEventLoop *loop;

private:
    void initWidget();

signals:
    void closePanel(int);
};

#endif // VERSIONUPDATE_H
