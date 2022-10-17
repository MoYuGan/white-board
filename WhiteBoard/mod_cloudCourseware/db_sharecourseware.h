#ifndef DB_SHARECOURSEWARE_H
#define DB_SHARECOURSEWARE_H

/***********************
*   分享课件面板
************************/

#include <QWidget>
#include "ShareStyle/db_font.h"
#include "CustomWidget/db_customdelegate.h"
#include "mod_http/db_httpthread.h"
#include "mod_cloudCourseware/db_sharelinks.h"

namespace Ui {
class DB_ShareCourseware;
}

class DB_ShareCourseware : public QWidget
{ 
    Q_OBJECT
public:
    explicit DB_ShareCourseware(_CoIoData data, QWidget *parent = 0);
    ~DB_ShareCourseware();
    void show();
    void resize();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DB_ShareCourseware *ui;
    bool m_pMousePressed = false;
    _CoIoData m_pCoIoData;          //课件信息消息体
    DB_HttpThread *m_pHttpThread;   //http请求线程
    DB_ShareLinks *m_pShareLinks;   //分享链接面板

private:
    void initWidget();
    // 生成分享链接


private slots:
    void onComboBoxItemChanged(int index);
    void getSharingLinks();
    void onHttpThreadFinished(HttpFunction, QVariant);

signals:
    void panelClosed();

};

#endif // DB_SHARECOURSEWARE_H
