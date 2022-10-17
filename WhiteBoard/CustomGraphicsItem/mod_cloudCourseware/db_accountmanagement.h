#ifndef DB_ACCOUNTMANAGEMENT_H
#define DB_ACCOUNTMANAGEMENT_H

/***********************
*   账号管理面板
************************/

#include <QWidget>
#include "ShareStyle/db_font.h"
#include "mod_http/db_httpthread.h"

namespace Ui {
class DB_AccountManagement;
}

class DB_AccountManagement : public QWidget
{
    Q_OBJECT

public:
    explicit DB_AccountManagement(QWidget *parent = 0);
    ~DB_AccountManagement();
    void show();
    void resize();
    void setMsg(const QPixmap &userIcon, const QString &userName,
                const QString &telephone, const QString &weixinName);
    void setUserIcon(const QPixmap &userIcon);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DB_AccountManagement *ui;
    DB_HttpThread *m_pHttpThread;
    QString m_pTelephone;

private:
    void initWidget();

private slots:
    void onHttpThreadFinished(HttpFunction, QVariant);

signals:
    void panelClosed();
    void cancellation();    //注销信号
};

#endif // DB_ACCOUNTMANAGEMENT_H
