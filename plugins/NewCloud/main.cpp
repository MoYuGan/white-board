#include <QApplication>
#include "mycloud.h"
#include "maininterface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyCloud w;
    w.show();
    w.setKeyBoardShow();

    return a.exec();
}
