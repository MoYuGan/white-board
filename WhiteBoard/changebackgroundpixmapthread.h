#ifndef CHANGEBACKGROUNDPIXMAPTHREAD_H
#define CHANGEBACKGROUNDPIXMAPTHREAD_H

#include <QObject>
#include <QThread>
#include "mod_draw/boardscene.h"
class ChangeBackgroundPixmapThread : public QThread
{
    Q_OBJECT
public:
    explicit ChangeBackgroundPixmapThread(QVector<BoardScene *> mscenelist,QPixmap mpix,int mid,QThread *parent = nullptr);

    void run();
signals:

private:
    QVector<BoardScene *> scenelist;
    QPixmap pix;
    int id;

};

#endif // CHANGEBACKGROUNDPIXMAPTHREAD_H
