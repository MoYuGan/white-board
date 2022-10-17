#include "audiochoose.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AudioChoose A;
    A.show();
    return a.exec();
}
