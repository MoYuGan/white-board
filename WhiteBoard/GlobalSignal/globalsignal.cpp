#include "globalsignal.h"

GlobalSignal::GlobalSignal(QObject *parent) : QObject(parent)
{
}

GlobalSignal *GlobalSignal::getInstance()
{
    static GlobalSignal* globalSignal = new  GlobalSignal;
    return globalSignal;
}

void GlobalSignal::enablSave()
{
    emit this->appSaveEnabled();
}

void GlobalSignal::changeLanguage()
{
    emit this->appLanguageChanged();
}
