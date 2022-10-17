#ifndef SCREENSHOTINTERFACE_H
#define SCREENSHOTINTERFACE_H

#include <QWidget>
class ScreenShotInterFace : public QWidget
{
    Q_OBJECT
public:
    ScreenShotInterFace(QWidget *parent =0): QWidget(parent){}
    virtual ~ScreenShotInterFace() {}
    virtual ScreenShotInterFace* getWidget() =0;
    virtual void updateLanguage(bool ){}
signals:
    void sendShotPixmap(QPixmap );//获得截图
    void sendCloseMessage();//窗口关闭信号
    void sendDesktopShow(int );//1显示桌面，2隐藏桌面
};
//内部第一个函数为类名，第二个函数为接口标识，可以随意写
Q_DECLARE_INTERFACE(ScreenShotInterFace, "ScreenShotInterFace/01")
#endif // SCREENSHOTINTERFACE_H
