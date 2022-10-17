#ifndef DB_LOGINPANEL_H
#define DB_LOGINPANEL_H

#include <QWidget>
#include "mod_cloudCourseware/db_login.h"
#include "mod_cloudCourseware/db_register.h"
#include "ShareStyle/db_font.h"
#include "mod_cloudCourseware/db_define.h"

namespace Ui {
class DB_LoginPanel;
}

class DB_LoginPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DB_LoginPanel(QWidget *parent = 0);
    ~DB_LoginPanel();
    void show();
    void resize();
    //初始化显示
    void initDisplay();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DB_LoginPanel *ui;
    //登录页面
    DB_Login *m_pLoginPage;
    //注册页面
    DB_Register *m_pRegisterPage;

private:
    void initWidget();

signals:
    //面板关闭信号
    void panelClosed();
    //显示用户面板信号
    void showUserPanel(_UserInfoData);

private:
    //登录成功, 显示用户面板
    void showUserPanelSlot(_UserInfoData);
    //显示文档：1代表许可协议，2代表隐私政策
    void showDocument(int);
    void closePanel();

};

#endif // DB_LOGINPANEL_H
