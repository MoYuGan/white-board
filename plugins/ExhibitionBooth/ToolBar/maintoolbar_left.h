#ifndef MAINTOOLBAR_LEFT_H
#define MAINTOOLBAR_LEFT_H

#include <QWidget>
#include <QPainter>
#include "Public/publicfunction.h"
#include "Extern/extern.h"

namespace Ui {
class MainToolBar_Left;
}

class MainToolBar_Left : public QWidget
{
    Q_OBJECT

public:
    explicit MainToolBar_Left(QWidget *parent = 0);
    ~MainToolBar_Left();
    void resize();
    int getBorder();
    void setShowMenuBtnChecked(bool checked);
    void setMenuEnabled(bool enable);

private:
    Ui::MainToolBar_Left *ui;

protected:
    void paintEvent(QPaintEvent *event);

private:
    void initWidget();

private slots:
    void onMenuBtnToggled(bool checked);

signals:
    void showMenu(bool checked);
    void toMinimize();
};

#endif // MAINTOOLBAR_LEFT_H
