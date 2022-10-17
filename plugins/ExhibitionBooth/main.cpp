#include <QApplication>
#include "mainwidget.h"
#include "Extern/extern.h"
#include "applicationstart.h"
#include "getupdatezip.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ApplicationStart s;
    s.show();
    if (s.checkUpdate()) {
        GetUpdateZip g(QString("新版本升级"), s.getUrl());
        s.hide();
        g.show();
        int ret = g.exec();
        if (1 == ret) {
            QProcess::startDetached(qApp->applicationFilePath(), QStringList());
            QApplication::exit(0);
            return 0;
        }
        g.hide();
    }

    MainWidget w;
    w.show();
    s.hide();
    return a.exec();
}
