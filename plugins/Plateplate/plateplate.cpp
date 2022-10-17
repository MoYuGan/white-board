#include "plateplate.h"
#include "mainwidget.h"

Plateplate::Plateplate(QObject *parent) :
    Plateplate_Interface(parent)
{
}

QWidget *Plateplate::create(QWidget *parent, const QString &closeSlotFunction)
{
    static MainWidget *widget = nullptr;
    if (nullptr == widget) {
        widget = new MainWidget(parent);
        connect(widget, SIGNAL(hideWidget()), parent, closeSlotFunction.toLatin1().data());
    }
    return widget;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(Plateplate, Plateplate)
#endif // QT_VERSION < 0x050000
