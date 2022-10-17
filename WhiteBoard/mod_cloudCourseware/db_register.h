#ifndef DB_REGISTER_H
#define DB_REGISTER_H

/***********************
*   注册页面
************************/

#include <QWidget>
#include <QThread>
#include "mod_http/db_httpinterface.h"
#include "CustomWidget/db_customwidget.h"
#include "mod_http/db_httpthread.h"
#include "ShareStyle/db_font.h"

namespace Ui {
class DB_Register;
}

class DB_Register : public QWidget
{
    Q_OBJECT

public:
    explicit DB_Register(QWidget *parent = 0);
    ~DB_Register();
    void show();
    void resize();
    //初始化显示
    void initDisplay();
    //强制退出http请求线程
    void stopHttpThread();

private:
    Ui::DB_Register *ui;
    DB_CustomWidget1 *m_pMBoxToolTip;   //提示框
    DB_HttpThread *m_pHttpThread;       //http请求线程

private:
    void initWidget();
    //检查手机号码格式是否正确, 参数： str: 需要检查的字符串  tip: 返回的提示信息
    bool checkTelephone(const QString &str, QString *tip);
    //检查密码格式是否正确
    bool checkPassword(const QString &str, QString *tip);
    //检查验证码格式是否正确
    bool checkVerificationCode(const QString &str, QString *tip);

signals:
    //显示登录面板信号
    void showLoginPage();
    //显示隐私协议/服务政策信号
    void showDocument(int);

private slots:
    //获取验证码
    void getVerificationCode();
    void on_pushButton_next_clicked();
    void on_pushButton_finished_clicked();
    //处理http请求返回消息
    void onHttpThreadFinished(HttpFunction, QVariant);
};

#endif // DB_REGISTER_H
