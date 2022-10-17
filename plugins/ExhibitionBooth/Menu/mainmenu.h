#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "Public/publicfunction.h"
#include "Extern/extern.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();
    void resize();
    void hide();
    void setDeviceBtnEnabled(bool enabled);
    void setResolutionBtnEnabled(bool enabled);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainMenu *ui;
    void initWidget();

private slots:
    void onDevicesBtnToggled(bool checked);
    void onResolutionBtnToggled(bool checked);

signals:
    void showDeviceListMenu(bool checked);
    void showResolutionListMenu(bool checked);
    void showAbout();
    void exitApplication();
    void widgetHide();
};

#endif // MAINMENU_H
