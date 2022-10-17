#ifndef INITAPPLICATION_H
#define INITAPPLICATION_H

#include <QWidget>
#include <QEventLoop>
#include <QPainter>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include "Public/public_function.h"
#include "mod_http/db_httpthread.h"
#include "VersionUpdate/versionupdate.h"

namespace Ui {
class InitApplication;
}

class InitApplication : public QWidget
{
    Q_OBJECT

public:
    explicit InitApplication(QWidget *parent = 0);
    ~InitApplication();
    void show();
    int checkUpdate();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::InitApplication *ui;
    DB_HttpThread *m_pHttpThread;
    _HttpRetData m_pData;
    int m_Ret = -1;

    void initWidget();

private slots:
    void onHttpThreadFinished(HttpFunction fun, QVariant variant);

signals:
    void quitLoop();
};

#endif // INITAPPLICATION_H
