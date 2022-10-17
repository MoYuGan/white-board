#ifndef APPLICATIONCONFIG_H
#define APPLICATIONCONFIG_H

#include <QString>
#include <QSettings>
#include <QFile>
#include <QApplication>
#include "QtDebug"
#include <QProcess>

/*
*   程序配置文件读写类
*/

#define CONFIG_KEY_LANGUAGE "Basic/Language"
#define DIRPATH "/opt/apps/com.amdox.board/files/config"

class ApplicationConfig
{
public:
    ApplicationConfig(){}

    static QString readConfig(const QString &key) {
        QString configPath = QString("%1/amdoxboard.ini").arg(DIRPATH);
        QSettings settings(configPath, QSettings::IniFormat);
        QString value = settings.value(key).toString();
        return value;
    }

    static void writeConfig(const QString &key, const QString &value) {
        QString configPath = QString("%1/amdoxboard.ini").arg(DIRPATH);
        QSettings settings(configPath, QSettings::IniFormat);
        settings.setValue(key, value);
        return;
    }

    // 检查配置文件是否存在，不存在则创建
    static void checkConfigFileExist() {
        QString configPath = QString("%1/amdoxboard.ini").arg(DIRPATH);
        QFile file(configPath);
        if (!file.exists()) {
            qDebug()<<"The program configuration file does not exist.";
            if (file.open(QIODevice::ReadWrite)) {
                file.close();
                ApplicationConfig::writeConfig(CONFIG_KEY_LANGUAGE, "1");
                ApplicationConfig::writeConfig("miniboard", "0");
                qDebug()<<"Program configuration file created successfully.";
            }else {
                qDebug()<<"Failed to create program configuration file.";
            }
        }
    }
};

#endif // APPLICATIONCONFIG_H
