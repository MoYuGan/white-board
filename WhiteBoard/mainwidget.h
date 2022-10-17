#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QGuiApplication>
#include <QScreen>
#include <QFrame>
#include <QPropertyAnimation>
#include <QEvent>
#include "drawingboard.h"
#include "Extern/extern.h"
#include "MinimizedWhiteboard/minwhiteboard.h"
#include "Custom/PushButton/pushbutton_7.h"
#include "Panel/penpanel.h"
#include "Panel/erasepanel.h"
#include "aboutus.h"
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    bool eventFilter(QObject *watched, QEvent *event);
    QString MAC();
private:
    Ui::MainWidget *ui;
    DrawingBoard *m_Board = nullptr;
    MinWhiteboard *m_MinWhiteboard = nullptr;

    QFrame *m_ToolFrame;
    PushButton_7 *m_MainBtn;
    PushButton_7 *m_SelectBtn;
    PushButton_7 *m_PenBtn;
    PushButton_7 *m_EraseBtn;
    PushButton_7 *m_ScreenshotsBtn;
    PushButton_7 *m_FullScreenBtn;
    QPropertyAnimation *m_Animation;
    int m_MaxWidth;
    QButtonGroup *m_CheckableBtnGroup;

    PenPanel *m_PenPanel = nullptr;
    ErasePanel *m_ErasePanel = nullptr;

    QPoint m_MousePressedPoint;
    bool m_ToolHasMoved = false;

    QString begintime;
    QString endtime;
    QDateTime begintime1;
    QDateTime endtime1;


private:
    DrawingBoard* newBoard();
    void initWidget();
    void resizeWidget();
    void hidePanel();
    void sendRunMessage();

signals:
    void quitLoop();
    void showMaxMessage();

private slots:
    void onBoardClose(int);
    void onShowMinimized();
    void onShowMaximized();
    void onScreenResize();
    void animationStart();
    void onSelectBtnToggled(bool checked);
    void onPenBtnToggled(bool checked);
    void onEraseBtnToggled(bool checked);
    void onPenBtnCheckedClicked();
    void onEraseBtnCheckedClicked();
    void onScreenShots();
    void onShowFullScreen();

};

#endif // MAINWIDGET_H
