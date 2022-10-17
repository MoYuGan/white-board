#ifndef PLATEPLATE_INTERFACE_H
#define PLATEPLATE_INTERFACE_H

#include <QtPlugin>
#include <QObject>
#include <QWidget>

class Plateplate_Interface : public QObject
{
    Q_OBJECT
public:
    Plateplate_Interface(QObject *parent = nullptr) : QObject(parent){}
    virtual ~Plateplate_Interface(){}
    virtual QWidget* create(QWidget *parent, const QString &closeSlotFunction) = 0;
};

Q_DECLARE_INTERFACE(Plateplate_Interface, "Plateplate.Plugin.Interface")

#endif // PLATEPLATE_INTERFACE_H
