#ifndef APPLICATIONSTART_H
#define APPLICATIONSTART_H

#include <QWidget>
#include <QtNetwork>
#include <QScreen>
#include <QPainter>
#include "Public/publicfunction.h"

namespace Ui {
class ApplicationStart;
}

class QNetworkReply;
class QNetworkAccessManager;

// http返回消息
typedef struct NewHttpResultData {
    NewHttpResultData () { state = -1; }
    int state;          //状态 ,1代表成功
    QString code;       //提示信息
    QVariant variant;   //扩展(各种消息体)
}_HttpRetData;
Q_DECLARE_METATYPE(_HttpRetData)   //QVariant可识别

// 版本更新消息体
typedef struct CheckUpdateData {
    QString version;        //版本号
    QString downloadUrl;    //下载网址
    QString fileStyle;      //文件格式
    int fileSize;           //文件大小
}_CheUpdaData;
Q_DECLARE_METATYPE(_CheUpdaData)

class ApplicationStart : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationStart(QWidget *parent = nullptr);
    ~ApplicationStart();
    void show();
    bool checkUpdate();
    inline QString getUrl() { return m_Url; }
    inline QString getVersion() { return m_Version; }

protected:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::ApplicationStart *ui;
    QString m_Url;
    QString m_Version;
    QEventLoop *m_Loop;

    _HttpRetData getVersionRequest();
    void resizeWidget();
};


#endif // APPLICATIONSTART_H
