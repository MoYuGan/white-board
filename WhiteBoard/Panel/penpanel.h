#ifndef PENPANEL_H
#define PENPANEL_H

#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QAbstractButton>
#include <QButtonGroup>
#include "Public/public_function.h"
#include "Extern/extern.h"
#include <QTabWidget>
#include <QTabBar>
#include "Custom/PushButton/pushbutton_8.h"

namespace Ui {
class PenPanel;
}

class PenPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PenPanel(QWidget *parent = 0);
    ~PenPanel();
    void show();
    void hide();
    void resizeWidget();
    bool isLocked();
    void setCheckedColor(int);
    void setCheckedSize(int);
    void setLockBtnVisable(bool visable);
    bool eventFilter(QObject *watched, QEvent *event);
    void hideOtherPen();
    void isMiniBoard(bool );

    void updateLanguage();
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::PenPanel *ui;
    bool m_MousePressed = false;
    QPoint m_LastPoint;
    QButtonGroup *m_PenColorGroup = nullptr;
    QButtonGroup *m_PenSizeGroup = nullptr;
    QButtonGroup *m_PenStyleGroup = nullptr;

    QButtonGroup *softPenColorGroup = nullptr;
    QButtonGroup *softPenSizeGroup = nullptr;

    QButtonGroup *nitePenColorGroup = nullptr;
    QButtonGroup *nitePenSizeGroup = nullptr;

    QButtonGroup *patternPenColorGroup = nullptr;
    QButtonGroup *patternPenSizeGroup = nullptr;

    void initWidget();
    bool miniboard =false;

private slots:
    void onPixmapBtnGroupToggled(QAbstractButton* button);
    void onPixmapSizeBtnGroupToggled(QAbstractButton* button);
    void onColorBtnGroupToggled(QAbstractButton* button);
    void onSizeBtnGroupToggled(QAbstractButton *button);
    void onStyleBtnGroupToggled(QAbstractButton *button);

signals:
    void panelHide();
    void penColorChanged(QColor);
    void penSizeChanged(int);
};

#endif // PENPANEL_H
