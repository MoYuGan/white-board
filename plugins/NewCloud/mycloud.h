#ifndef MYCLOUD_H
#define MYCLOUD_H

#include <QWidget>
#include <QPainter>
#include "custombtn.h"
#include "customwidget.h"
#include <QMouseEvent>
#include "maininterface.h"
#include "mod_http/db_httpthread.h"
#include "cloudcoursewareinterface.h"
#include "VirtualKeyBoard/keyboard.h"

namespace Ui {
class MyCloud;
}

class MyCloud : public CloudCoursewareInterFace
{
    Q_OBJECT
    #if QT_VERSION >= 0x050000
        Q_PLUGIN_METADATA(IID "MyNewCloudeInterFace/01" FILE "MyCloud.json")//第一个参数为接口类的标识，与接口类处内容一致作呼应，后面为当前类.json文件，内部放入{}即可
        Q_INTERFACES(CloudCoursewareInterFace)//填写接口类名称
    #endif
public:
    explicit MyCloud(QWidget *parent = 0);
    ~MyCloud();
    void show();
    void resizeWidget();
    void initconnect();
    //强制退出http请求线程
    void stopHttpThread();
    QWidget* createWidget(QWidget *parent) override;
    void setKeyBoardShow() override;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void storageNumber(QString );
    int getMaxId();
    void addID(QListWidget* );
    void hideButton();

private slots:
    void onHttpThreadFinished(HttpFunction, QVariant);


private:
    Ui::MyCloud *ui;
    QSqlDatabase* database;
    QSqlQuery *sql_query;
    DB_HttpThread *m_pHttpThread = nullptr;
    CustomWidget_21 *m_pMBoxToolTip;
    CustomWidget_22 *coverWid;
    QString m_pQrCodeUUID;
    Custom_Lab3 *codeLab;
    QEventLoop *loop;
    QPixmap pix;
    int threadstop =1;
    int loginflag =0;
    QString tip;
    int m_AfterCheckedDo = -1;

    void initWidget();
    void signAndLog();
    void signAnLog_Regist();
    bool checkTelephone(const QString &str, QString *tip);
    void clearChangeWidget();
    void clearRegistWidget();
    void createUserPanel(const QString &name, const QString &url);
    Keyboard *keyboard;

};

#endif // MYCLOUD_H
