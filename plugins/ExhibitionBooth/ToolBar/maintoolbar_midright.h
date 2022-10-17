#ifndef MAINTOOLBAR_MIDRIGHT_H
#define MAINTOOLBAR_MIDRIGHT_H

#include <QWidget>
#include <QPainter>
#include "Public/publicfunction.h"
#include "Menu/controlmenu.h"

namespace Ui {
class MainToolBar_MidRight;
}

class MainToolBar_MidRight : public QWidget
{
    Q_OBJECT

public:
    explicit MainToolBar_MidRight(QWidget *parent = 0);
    ~MainToolBar_MidRight();
    void resize();
    int getBorder();
    void setEnabled(bool enabled);
    void hideMenu();

protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::MainToolBar_MidRight *ui;
    ControlMenu *m_ControlMenu;

    void initWidget();

private slots:
    void showControlMenu(bool checked);

signals:
    void action_screenshots();
    void action_ocr();
    void action_tackphoto();

signals:
    void leftRotate();
    void rightRotate();
    void zoomIn();
    void zoomOut();

};

#endif // MAINTOOLBAR_MIDRIGHT_H
