#ifndef PAGETHREAD_H
#define PAGETHREAD_H

#include <QObject>
#include <QThread>
#include "mod_draw/boardscene.h"
#include "Custom/PushButton/pushbutton_6.h"
#include "mod_draw/boardview.h"
class PageThread : public QThread
{
    Q_OBJECT
public:
    explicit PageThread(QVector<BoardScene *>* mlistscene,QVector<PushButton_6 *>* mlistpix,int mnum,DB_BoardView* mview,QThread *parent = nullptr);
    void run();

signals:
    void sendFinishedMessage(QPixmap );
private:
  QVector<BoardScene *> *listscene;
  QVector<PushButton_6 *> *listpix;
  int num=0;
  DB_BoardView* view;

};

#endif // PAGETHREAD_H
