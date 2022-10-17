#include "pagethread.h"

PageThread::PageThread(QVector<BoardScene *> *mlistscene,QVector<PushButton_6 *> *mlistpix,int mnum,DB_BoardView* mview,QThread *parent)
    : QThread{parent}
{
    listscene =mlistscene;
    listpix =mlistpix;
    num =mnum;
    view =mview;
}

void PageThread::run()
{
    for (int var = 0; var < listscene->count(); ++var) {
          if(num ==var)listpix->value(var)->mSetPixmap(listscene->at(var)->getSceneToPixmap());
          else
          {
              view->setScene(listscene->at(var));
              QPixmap pix = view->getViewToPixmap();
              listpix->value(var)->mSetPixmap(pix);
          }
        }
    view->setScene(listscene->at(num));
    this->deleteLater();
}
