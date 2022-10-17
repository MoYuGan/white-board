#ifndef EXHIBITIONBOOTH_INTERFACE_H
#define EXHIBITIONBOOTH_INTERFACE_H

#include <QtPlugin>
#include <QObject>
#include <QWidget>

class ExhibitionBooth_Interface : public QObject
{
    Q_OBJECT
public:
    ExhibitionBooth_Interface(QObject *parent = nullptr) : QObject(parent){}
    virtual ~ExhibitionBooth_Interface(){}
    virtual QWidget* create(QWidget *parent, const QString &closeSlotFunction) = 0;
    virtual void showWidget() = 0;
};

Q_DECLARE_INTERFACE(ExhibitionBooth_Interface, "ExhibitionBooth.Plugin.Interface")

#endif // EXHIBITIONBOOTH_INTERFACE_H
