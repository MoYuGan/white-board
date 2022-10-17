#ifndef MENUPANEL_EXPORT_H
#define MENUPANEL_EXPORT_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include "Public/public_function.h"

namespace Ui {
class MenuPanel_Export;
}

class MenuPanel_Export : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPanel_Export(QWidget *parent = 0);
    ~MenuPanel_Export();
    void resizeWidget();
    void show();
    void hide();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MenuPanel_Export *ui;
    QGraphicsDropShadowEffect *m_ShadowEffect;  //阴影

    void initWidget();

signals:
    void exportToFile(int);
    void panelHide();
};

#endif // MENUPANEL_EXPORT_H
