#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QGenericPlugin>
#include "recodescreeninteface.h"
#include "audiochoose.h"
#include "QFileDialog"
class Videoplayer;
class MyPlugin : public RecordScreenInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "TestPlugin.Demo.Plugin" FILE "myplugin.json")
    Q_INTERFACES(RecordScreenInterface)
#endif // QT_VERSION >= 0x050000

public:
    MyPlugin(QObject *parent = 0);
    QWidget *create(QWidget *parent) override;
    void Btn_MoveTo(double x,double y) override;
    AudioChoose* Audio ;
};

#endif // MYPLUGIN_H
