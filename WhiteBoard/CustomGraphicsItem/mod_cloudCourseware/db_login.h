#ifndef DB_LOGIN_H
#define DB_LOGIN_H

/***********************
*   登录页面
************************/

#include <QWidget>
#include <QThread>
#include "CustomWidget/db_customwidget.h"
#include "mod_http/db_httpthread.h"
#include "ShareStyle/db_font.h"

namespace Ui {
class DB_Login;
}

class DB_Login : public QWidget
{
    Q_OBJECT

public:
    explicit DB_Login(QWidget *parent = 0);
    ~DB_Login();
    void show();
    void resize();
    //强制退出http请求线程
    void stopHttpThread();

private:
    Ui::DB_Login *ui;
    DB_HttpThread *m_pHttpThread;
    DB_CustomWidget1 *m_pMBoxToolTip;
    QString m_pQrCodeUUID;

signals:
    void showRegisterPage();
    void showUserPanel(_UserInfoData);
    void startHttpWorker(HttpFunction, bool, QVariant);

private:
    void initWidget();
    //检查手机号码格式是否正确, 参数： str: 需要检查的字符串  tip: 返回的提示信息
    bool checkTelephone(const QString &str, QString *tip);
    //检查密码格式是否正确
    bool checkPassword(const QString &str, QString *tip);
    //检查验证码格式是否正确
    bool checkVerificationCode(const QString &str, QString *tip);

private slots:
    //账号密码登录
    void on_pushButton_login_clicked();
    //获取验证码
    void onHttpThreadFinished(HttpFunction, QVariant);
    void on_pushButton_cancelLogin_clicked();
};

#endif // DB_LOGIN_H
