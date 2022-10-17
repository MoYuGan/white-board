#ifndef MYMUTEX_H
#define MYMUTEX_H

#include <QMutex>

class MyMutex
{
public:
    static MyMutex* getMutex() {
        static MyMutex* mymutex = nullptr;
        if (nullptr == mymutex)
            mymutex = new MyMutex;
        return mymutex;
    }

    QMutex mutex;
};

#endif // MYMUTEX_H
