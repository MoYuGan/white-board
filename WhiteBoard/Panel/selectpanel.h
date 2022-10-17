#ifndef SELECTPANEL_H
#define SELECTPANEL_H

#include <QWidget>
#include <QPainter>
#include "Public/public_function.h"

namespace Ui {
class SelectPanel;
}

class SelectPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SelectPanel(QWidget *parent = 0);
    ~SelectPanel();
    void resizeWidget();
    void show();
    void hide();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::SelectPanel *ui;

    void initWidget();

signals:
    void selectAll();
    void panelHide();
};

#endif // SELECTPANEL_H
