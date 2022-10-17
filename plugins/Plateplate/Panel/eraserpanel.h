#ifndef ERASERPANEL_H
#define ERASERPANEL_H

#include <QWidget>
#include <QAbstractButton>
#include <QPainter>
#include <QButtonGroup>
#include "Public/publicfunction.h"
#include "Extern/extern.h"

namespace Ui {
class EraserPanel;
}

class EraserPanel : public QWidget
{
    Q_OBJECT

public:
    explicit EraserPanel(QWidget *parent = 0);
    ~EraserPanel();
    void show();
    void hide();
    inline int getTransparentBorder() { return m_TransparentBorder; }
    void resize();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::EraserPanel *ui;
    int m_TransparentBorder = 6;

    void initWidget();

private slots:
    void onSizeGroupToggled(QAbstractButton* button, bool checked);

signals:
    void panelHide();
    void panelShow();
    void clearAction();
};

#endif // ERASERPANEL_H
