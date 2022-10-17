#ifndef GRAPHICSITEM_TOOLBAR_H
#define GRAPHICSITEM_TOOLBAR_H

#include <QWidget>
#include <QPixmap>
#include "Public/publicfunction.h"

namespace Ui {
class GraphicsItem_ToolBar;
}

class GraphicsItem_ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsItem_ToolBar(QWidget *parent = 0);
    ~GraphicsItem_ToolBar();
    void resize();
    void setCloneChecked(bool checked);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::GraphicsItem_ToolBar *ui;
    void initWidget();

signals:
    void actionClone(bool checked);
    void actionStayOnTop();
    void actionStayOnBottom();
    void actionDelete();
};

#endif // GRAPHICSITEM_TOOLBAR_H
