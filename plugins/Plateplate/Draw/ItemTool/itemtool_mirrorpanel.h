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

signals:
    void copyToTop();
    void copyToBottom();
    void copyToLeft();
    void copyToRight();
};

#endif // ITEMTOOL_MIRRORPANEL_H
