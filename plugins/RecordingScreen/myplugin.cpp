#include "myplugin.h"
#include <QLabel>

MyPlugin::MyPlugin(QObject *parent) :
    RecordScreenInterface(parent)
{
}

QWidget *MyPlugin::create(QWidget *parent)
{
    Audio = new AudioChoose(parent);
    return Audio;
}
void MyPlugin::Btn_MoveTo(double x, double y)
{
    qDebug() << "11111111";
    if(Audio)
        Audio->Btn_MoveTo(x,y);
    qDebug() << "22222222";
}


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(myplugin, MyPlugin)
#endif // QT_VERSION < 0x050000
