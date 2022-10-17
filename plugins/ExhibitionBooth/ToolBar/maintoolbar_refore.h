#ifndef MAINTOOLBAR_REFORE_H
#define MAINTOOLBAR_REFORE_H

#include <QWidget>
#include <QPainter>
#include "Public/publicfunction.h"

namespace Ui {
class MainToolBar_Refore;
}

class MainToolBar_Refore : public QWidget
{
    Q_OBJECT

public:
    explicit MainToolBar_Refore(QWidget *parent = 0);
    ~MainToolBar_Refore();
    void resize();
    void mSetIcon(const QPixmap &pixmap);
    int getBorder();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainToolBar_Refore *ui;

    void initWidget();

signals:
    void btnClicked();
};

#endif // MAINTOOLBAR_REFORE_H
