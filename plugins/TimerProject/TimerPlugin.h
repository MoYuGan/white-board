#ifndef TIMERPLUGIN_H
#define TIMERPLUGIN_H
#include <QWidget>
#include <QObject>

class TimerPlugin : public QWidget
{
    Q_OBJECT
public:
    TimerPlugin(QWidget *parent =0): QWidget(parent){}
    virtual ~TimerPlugin() {}

    virtual void updateLanguage(bool) {}

signals:
    void widgetClosed();

};
Q_DECLARE_INTERFACE(TimerPlugin, "TimerPlugin/01")
#endif // TIMERPLUGIN_H
