#ifndef ITEMTOOL_MIRRORPANEL_H
#define ITEMTOOL_MIRRORPANEL_H

#include <QWidget>

namespace Ui {
class ItemTool_MirrorPanel;
}

class ItemTool_MirrorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ItemTool_MirrorPanel(QWidget *parent = 0);
    ~ItemTool_MirrorPanel();

private:
    Ui::ItemTool_MirrorPanel *ui;

    void initWidget();
    void resize();

protected:
    bool event(QEvent *event);

signals:
    void mirror(int);
};

#endif // ITEMTOOL_MIRRORPANEL_H
