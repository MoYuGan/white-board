#ifndef MAINTOOLBAR_RIGHT_H
#define MAINTOOLBAR_RIGHT_H

#include <QWidget>
#include <QPainter>
#include "Public/publicfunction.h"
#include "Menu/imagemenu.h"

namespace Ui {
class MainToolBar_right;
}

class MainToolBar_right : public QWidget
{
    Q_OBJECT

public:
    explicit MainToolBar_right(QWidget *parent = 0);
    ~MainToolBar_right();
    void resize();
    int getBorder();
    void setShowListBtnChecked(bool checked);
    void getPixmap(int id, QPixmap *pixmap, int *angle);
    void addItem(const QPixmap &pixmap);
    void rotateItem(int id, int angle);
    void addCameraItem(const QString &text);
    void clearCameraItem();
    void setCameraItemChecked(int index, bool checked);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainToolBar_right *ui;
    ImageMenu *m_ImageMenu;
    int m_CheckedIndex;

    void initWidget();

private slots:
    void onShowImageBtnClicked();
    void onContrastBtnClicked();
    void onContrastCancelBtnClicked();
    void onSaveBtnClicked();
    void onSaveCancelBtnClicked();
    void onItemNumChanged();
    void onItemChecked(bool checked, int id);
    void onCameraItemChecked(bool checked, int index);
signals:
    void displayImage(bool, int);
    void enableContrast(int);
    void cancelContrast(QPixmap, int, int);
    void cameraChecked(bool, int);

};

#endif // MAINTOOLBAR_RIGHT_H
