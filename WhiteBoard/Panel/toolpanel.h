#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <QWidget>
#include <QPainter>
#include <QAbstractButton>
#include <QButtonGroup>
#include "Public/public_function.h"

namespace Ui {
class ToolPanel;
}

class ToolPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPanel(QWidget *parent = 0);
    ~ToolPanel();
    void show();
    void hide();
    void resizeWidget();
    void updateLanguage();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ToolPanel *ui;

    void initWidget();


private slots:
    void onToolGroupBtnClicked(QAbstractButton* button);

signals:
    void panelHide();
    void showPanel(int);
    void toolFunction(int);
};

#endif // TOOLPANEL_H
