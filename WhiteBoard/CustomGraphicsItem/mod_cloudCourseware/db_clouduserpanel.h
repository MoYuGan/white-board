#ifndef DB_CLOUDUSERPANEL_H
#define DB_CLOUDUSERPANEL_H

#include <QWidget>
#include <QStandardItemModel>
#include <QThread>

#include "mod_http/db_httpthread.h"
#include "CustomWidget/db_customwidget.h"
#include "mod_cloudCourseware/db_tablemodel.h"
#include "mod_cloudCourseware/db_tabledelegate.h"
#include "ShareStyle/db_font.h"
#include "mod_cloudCourseware/db_accountmanagement.h"
#include "mod_cloudCourseware/db_sharecourseware.h"
#include "db_messagebox.h"

namespace Ui {
class DB_CloudUserPanel;
}


class DB_CloudUserPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DB_CloudUserPanel(_UserInfoData userData, QWidget *parent = 0);
    DB_CloudUserPanel(QWidget *parent = 0);
    ~DB_CloudUserPanel();
    void show();
    void resize();

private:
    Ui::DB_CloudUserPanel *ui;

protected:
    void paintEvent(QPaintEvent *event);

private:
    _UserInfoData m_pUserData;                      //用户信息
    DB_HttpThread *m_pHttpThread;                   //http请求线程
    QString m_desc = QString("1");                  //课件列表排序方式,默认降序
    DB_CustomWidget1 *m_pMBoxToolTip;               //提示框
    DB_AccountManagement *m_pAccountManagement;     //账号管理面板
    DB_TableModel *m_tableModel;                    //课件列表表格模型
    DB_TableDelegate *m_tableDelegate;              //课件列表表格代理
    QPixmap m_pUserIcon;                            //用户头像
    DB_ShareCourseware *m_pShareCourseware;         //分享面板

private:
    void initWidget();
    //获取课件列表
    void getCoursewareInfo();
    //上传课件
    void uploadCourseware();
    void showFrameCover();

private slots:
    void onChangMouseCursor(Qt::CursorShape shape);
    void onTabelViewMouseClick(int, int);
    //处理http请求返回
    void onHttpThreadFinished(HttpFunction fun, QVariant variant);
    //下载进度
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

signals:
    void panelClose();          //关闭信号
    void cancellation();           //注销信号
};

#endif // DB_CLOUDUSERPANEL_H
