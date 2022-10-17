#ifndef PLATEPLATE_H
#define PLATEPLATE_H

#include <QGenericPlugin>
#include "plateplate_interface.h"

class Plateplate : public Plateplate_Interface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "Plateplate.json")
    Q_INTERFACES(Plateplate_Interface)
#endif // QT_VERSION >= 0x050000

public:
    Plateplate(QObject *parent = 0);
    QWidget *create(QWidget *parent, const QString &closeSlotFunction) override;
};

#endif // PLATEPLATE_H
