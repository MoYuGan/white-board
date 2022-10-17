#ifndef PAGEPANEL_H
#define PAGEPANEL_H

#include <QWidget>
#include <QPainter>
#include <QScroller>
#include <QButtonGroup>
#include "Public/public_function.h"
#include "Custom/PushButton/pushbutton_6.h"
#include "mod_draw/boardscene.h"
#include "Extern/extern.h"
#include "mod_draw/boardview.h"
namespace Ui {
class PagePanel;
}

class PagePanel : public QWidget
{
    Q_OBJECT

public:
    explicit PagePanel(QWidget *parent = 0);
    ~PagePanel();
    void changeTabPixmap(int );
    void resizeWidget();
    void show();
    void hide();
    BoardScene* addPage(int index, const QPixmap &bgPixmap, int bgNum);
    int getPageSize();
    int getPageIndex();
    void setPageChecked(int index);
    void lastPage();
    void nextPage();
    void clearPage();
    void getAllScenePixmap(QList<QPixmap> *pixmapList);
    QPixmap getScenePixmap(int index);
    QVector<BoardScene *> getBoardSceneList();
    void updateSceneList(BoardScene*);



protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::PagePanel *ui;
    QButtonGroup *m_pPageGroup;
    QVector<PushButton_6 *> m_PageList;
    QVector<BoardScene *> m_SceneList;

    void initWidget();
    void deletePage(PushButton_6 *button);
    int number =0;

signals:
    void panelHide();
    void pageIndexChanged(QGraphicsScene *);

public slots:
    void onPageToggled(bool checked);
    void onPageDelete();
};

#endif // PAGEPANEL_H
