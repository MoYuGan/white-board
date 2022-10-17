#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>

#include "boardview.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    void hide();
    void setDisplayWidget(QWidget *widget);
    inline QWidget* getDisplayWidget() {return m_pDisplayWidget;}
    void showTool(bool);
    void setChecked(bool);
    inline bool isChecked() {return m_pChecked;}
    void setShowFullScreenStyle(bool bo);
    void setDrawTool(DrawTool tool);
    void undo();
    void redo();
    void zoomIn();
    void zoomOut();

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void windowChecked();
    void windowShowFullScreen();
    void showCameraFrame(bool, QWidget *, QPixmap);
public slots:

private:
    DB_BoardView *m_pBoardView;
    QWidget *m_pDisplayWidget = nullptr;
    QFrame *m_pFrame;
    bool m_pChecked = false;

    ImageTool *m_pTool;
    QPushButton *m_pToolBtnShowTool;
    QPushButton *m_pToolBtnUseCamera;
    QPushButton *m_pToolBtnFullScreen;
    QPushButton *m_pToolBtnOpenFile;
private:
    void initWidget();
};

#endif // DISPLAYWIDGET_H
