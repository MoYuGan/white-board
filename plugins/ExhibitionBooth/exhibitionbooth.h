#ifndef EXHIBITIONBOOTH_H
#define EXHIBITIONBOOTH_H

#include <QGenericPlugin>
#include "exhibitionbooth_interface.h"
#include "mainwidget.h"
#include "Extern/extern.h"

class ExhibitionBooth : public ExhibitionBooth_Interface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "ExhibitionBooth.json")
    Q_INTERFACES(ExhibitionBooth_Interface)
#endif // QT_VERSION >= 0x050000

public:
    ExhibitionBooth(QObject *parent = 0);
    QWidget *create(QWidget *parent, const QString &closeSlotFunction) override;
    void showWidget();

private:
    MainWidget *m_MainWidget = nullptr;
};

#endif // EXHIBITIONBOOTH_H
