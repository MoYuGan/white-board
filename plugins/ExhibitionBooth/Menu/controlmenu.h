#ifndef CONTROLMENU_H
#define CONTROLMENU_H

#include <QWidget>
#include <QButtonGroup>
#include "Public/publicfunction.h"
#include "Extern/extern.h"

namespace Ui {
class ControlMenu;
}

class ControlMenu : public QWidget
{
    Q_OBJECT
public:
    explicit ControlMenu(QWidget *parent = 0);
    ~ControlMenu();
    void resize();
    int getBorder();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ControlMenu *ui;

    void initWidget();

signals:
    void leftRotate();
    void rightRotate();
    void zoomIn();
    void zoomOut();
};

#endif // CONTROLMENU_H
