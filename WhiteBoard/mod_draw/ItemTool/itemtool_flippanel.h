#ifndef ITEMTOOL_FLIPPANEL_H
#define ITEMTOOL_FLIPPANEL_H

#include <QWidget>

namespace Ui {
class ItemTool_FlipPanel;
}

class ItemTool_FlipPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ItemTool_FlipPanel(QWidget *parent = 0);
    ~ItemTool_FlipPanel();

private:
    Ui::ItemTool_FlipPanel *ui;

    void initWidget();
    void resize();

protected:
    bool event(QEvent *event);

signals:
    void flip(int);
};

#endif // ITEMTOOL_FLIPPANEL_H
