#ifndef CLOUDCOURSEWAREINTERFACE_H
#define CLOUDCOURSEWAREINTERFACE_H

#include <QWidget>
#include <QObject>

class CloudCoursewareInterFace : public QWidget
{
    Q_OBJECT

public:
    CloudCoursewareInterFace(QWidget *parent =0): QWidget(parent){}
    virtual ~CloudCoursewareInterFace() {}
    virtual QWidget* createWidget(QWidget *parent = nullptr) =0; //创建一个纯虚函数，以提供给主接口调用插件功能使用

public slots:
    virtual void setKeyBoardShow() =0;
};

Q_DECLARE_INTERFACE(CloudCoursewareInterFace,"MyNewCloudeInterFace/01")//内部第一个函数为类名，第二个函数为接口标识，可以随意写

#endif // CLOUDCOURSEWAREINTERFACE_H
