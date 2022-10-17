#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtPlugin>
#include <QObject>
#include <QWidget>

class RecordScreenInterface : public QObject
{
    Q_OBJECT
public:
    RecordScreenInterface(QObject *parent = nullptr) : QObject(parent){}
    virtual ~RecordScreenInterface(){}
    virtual QWidget* create(QWidget *parent = Q_NULLPTR) = 0;
    virtual void Btn_MoveTo(double x,double y) = 0;
};

Q_DECLARE_INTERFACE(RecordScreenInterface, "TestPlugin.Plugin.RecordScreenInterface")

#endif // INTERFACE_H
