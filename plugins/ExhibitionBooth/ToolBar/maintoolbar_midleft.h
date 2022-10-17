#ifndef MAINTOOLBAR_MIDLEFT_H
#define MAINTOOLBAR_MIDLEFT_H

#include <QWidget>
#include <QPainter>
#include <QButtonGroup>
#include "Public/publicfunction.h"

namespace Ui {
class MainToolBar_MidLeft;
}

class MainToolBar_MidLeft : public QWidget
{
    Q_OBJECT

public:
    explicit MainToolBar_MidLeft(QWidget *parent = 0);
    ~MainToolBar_MidLeft();
    void resize();
    int getBorder();
    void setActionChecked(int index, bool checked);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainToolBar_MidLeft *ui;
    QButtonGroup *m_BtnGroup;

    void initWidget();

private slots:
    void onBtnGroupToggled(QAbstractButton *, bool);

signals:
    void moveBtnToggled(bool);
    void penBtnToggled(bool);
    void eraserBtnToggled(bool);
    void undoSignal();
    void redoSignal();
};

#endif // MAINTOOLBAR_MIDLEFT_H
