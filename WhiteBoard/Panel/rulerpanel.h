#ifndef RULERPANEL_H
#define RULERPANEL_H

#include <QWidget>
#include <QPainter>
#include "Public/public_function.h"

namespace Ui {
class RulerPanel;
}

class RulerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit RulerPanel(QWidget *parent = 0);
    ~RulerPanel();
    void show();
    void hide();
    void resizeWidget();

    void updateLanguage();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::RulerPanel *ui;

    void initWidget();

signals:
    void goBack();
    void panelHide();
    void addRuler(int);
};

#endif // RULERPANEL_H
