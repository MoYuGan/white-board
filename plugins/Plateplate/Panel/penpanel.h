#ifndef PENPANEL_H
#define PENPANEL_H

#include <QWidget>
#include <QPainter>
#include <QAbstractButton>
#include <QButtonGroup>
#include "Public/publicfunction.h"
#include "Extern/extern.h"

namespace Ui {
class PenPanel;
}

class PenPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PenPanel(QWidget *parent = nullptr);
    ~PenPanel();
    void show();
    void hide();
    void resize();
    inline int getTransparentBorder() { return m_TransparentBorder; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::PenPanel *ui;
    int m_TransparentBorder = 6;

    void initWidget();

private slots:
    void onSizeGroupBtnToggled(QAbstractButton *button, bool checked);
    void onColorGroupBtnToggled(QAbstractButton *button, bool checked);

signals:
    void panelHide();
    void panelShow();

};

#endif // PENPANEL_H
