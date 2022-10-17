#ifndef DB_SHARELINKS_H
#define DB_SHARELINKS_H

/***********************
*   分享链接面板
************************/

#include <QWidget>
#include "ShareStyle/db_font.h"
#include "mod_http/db_httpthread.h"
#include "mod_http/db_httpthread.h"

namespace Ui {
class DB_ShareLinks;
}

class DB_ShareLinks : public QWidget
{
    Q_OBJECT

public:
    explicit DB_ShareLinks(const QString &fileId, const QString &link, const QString &fileName,
                           const QString &createTime, QWidget *parent = 0);
    ~DB_ShareLinks();
    void show();
    void resize();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DB_ShareLinks *ui;
    DB_HttpThread *m_pHttpThread;   //http请求线程
    QString m_pFileId;

private:
    void initWidget();
    bool checkTelephone(const QString &str, QString *tip);

private slots:
    void shareLinkToPhone();
    void onHttpThreadFinished(HttpFunction, QVariant);

signals:
    void panelClosed();
};

#endif // DB_SHARELINKS_H
