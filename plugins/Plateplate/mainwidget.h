#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDateTime>
#include "Panel/penpanel.h"
#include "ExportFile/exportfile.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void resize();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWidget *ui;

    void initWidget();
    void exportFile();
    void insertPicture();

private slots:
    void onNewSceneCreated();
    void onToolMidActionClicked(int);
    void onToolMidActionCheckedClicked(int);
    void onToolMidActionToggled(int, bool);
    void onToolLeftActionClicked(int);
    void hidePanel(QWidget *widget = nullptr);
    void onSceneChanged();
    void deleteScene(int );
signals:
    void hideWidget();
};

#endif // MAINWIDGET_H
