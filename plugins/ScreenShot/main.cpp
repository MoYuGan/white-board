#include <QApplication>
#include "screenshot.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenShot w;
    w.show();
    return a.exec();
}
