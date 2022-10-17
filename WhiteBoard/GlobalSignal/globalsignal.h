#ifndef GLOBALSIGNAL_H
#define GLOBALSIGNAL_H

#include <QObject>

class GlobalSignal : public QObject
{
    Q_OBJECT
public:
    explicit GlobalSignal(QObject *parent = nullptr);
    static GlobalSignal* getInstance();
    void enablSave();
    void changeLanguage();
    void showFullScreen();

signals:
    void appSaveEnabled();
    void appLanguageChanged();

};

#endif // GLOBALSIGNAL_H
