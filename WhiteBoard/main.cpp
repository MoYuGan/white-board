#include <QApplication>
#include <QtDebug>
#include <QTranslator>
#include <QProcess>
#include "applicationconfig.h"
#include "mainwidget.h"
#include <QEventLoop>
#include "initapplication.h"
#include <QMessageBox>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <QString>
#include <QtMessageHandler>
#include <stdio.h>
#include <stdlib.h>
#include "Common/toolkit.h"

class My_Application : public QApplication
{
    /*
    *   自定义QApplication类，屏蔽某些按键
    */
public:
    My_Application(int &argc, char **argv) : QApplication(argc, argv){}
    virtual bool notify(QObject *obj, QEvent *event)
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        {
            // 屏蔽Tab按键
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Tab) {
                return true;
            }
        }
        return QApplication::notify(obj, event);
    }

signals:
    void saveStateChanged();
};

//根据qss样式文件设置样式
//void set_qss(QApplication *a)
//{
//    QFile file(QString(":/qss/style.qss"));
//    if(!file.open(QIODevice::ReadOnly))
//        return;

//    QString qss = QLatin1String(file.readAll());
//    a->setStyleSheet(qss);
//    file.close();

//    return;
//}


void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
 {
     // 加锁
     static QMutex mutex;
     mutex.lock();
     QString text;
     switch(type)
     {
     case QtDebugMsg:
         text = QString("Debug:");
         break;
     case QtWarningMsg:
         text = QString("Warning:");
         break;
     case QtCriticalMsg:
         text = QString("Critical:");
         break;
     case QtFatalMsg:
         text = QString("Fatal:");
         break;
    default:break;
     }

     // 设置输出信息格式
     QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
     QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ");
     QString current_date = QString("(%1)").arg(current_date_time);
     QString message = QString("%1 %2 %3").arg(current_date).arg(context_info).arg(msg);
     // 输出信息至文件中（读写、追加形式）
     static int printlogtime =0;
     static QString print_date_time;
     if(printlogtime ==0 )
     {
        printlogtime =1;
        print_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ");
     }
     QString desktopPath =QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
     desktopPath =desktopPath +"/logText";
     QDir *myfile = new QDir;
     bool exist = myfile->exists(desktopPath);
     if(!exist)
     {
         myfile->mkdir(desktopPath);
     }
     QFile file(QString("%1/log%2.txt").arg(desktopPath).arg(print_date_time));
     file.open(QIODevice::WriteOnly | QIODevice::Append);
     QTextStream text_stream(&file);
     text_stream << message << "\r\n";
     file.flush();
     file.close();
     // 解锁
     mutex.unlock();
 }

int main(int argc, char *argv[])
{
    //2022-1008 to solve white ling problem
    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    //end 2022-1008
    //虚拟键盘
//    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    //WebEngine 以插件形式使用，需要设置这个属性
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    //记录日志信息
    //qInstallMessageHandler(outputMessage);

    My_Application a(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    //QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QGuiApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

    //检查程序配置文件是否存在
    ApplicationConfig::checkConfigFileExist();
    //读取配置文件，初始化语言包 djf change
    ToolKit::installTranslator();


//    InitApplication *initWidget = new InitApplication;
//    initWidget->show();
//    //检查更新
//    int ret = initWidget->checkUpdate();
//    if (1 == ret) { //更新完成
//        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
//        QApplication::exit(0);
//        return 0;
//    }

    MainWidget w;
    w.show();
//    delete initWidget;
    a.exec();
}
