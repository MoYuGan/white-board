#ifndef GRAPHICSPANEL_H
#define GRAPHICSPANEL_H

#include <QWidget>
#include <QAbstractButton>
#include <QPainter>
#include <QButtonGroup>
#include "Public/public_function.h"
#include "Extern/extern.h"

namespace Ui {
class GraphicsPanel;
}

class GraphicsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsPanel(QWidget *parent = 0);
    ~GraphicsPanel();
    void show();
    void hide();
    void resizeWidget();

    void updateLanguage();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::GraphicsPanel *ui;

    void initWidget();

private slots:
    void onBtnGroupToggled(QAbstractButton *button);

signals:
    void goBack();
    void panelHide();
};

#endif // GRAPHICSPANEL_H
