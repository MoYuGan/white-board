#ifndef DB_EXHIBITIONBOOTH_H
#define DB_EXHIBITIONBOOTH_H

/*
 *  展台部件
 *
*/

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QCamera>
#include <QMenu>
#include <QWidgetAction>

#include "db_camera.h"
#include "db_mboxtooltip.h"
#include "menuwidget.h"

#include "Worker/getresolutionlistworker.h"
#include "Worker/listeningdevicesworker.h"
#include "Worker/getcameraframeworker.h"
#include "Custom/CustomItemDelegate/customitemdelegate.h"

#if 1
namespace Ui {
class DB_ExhibitionBooth;
}

class DB_ExhibitionBooth : public QWidget
{
    Q_OBJECT
public:
    explicit DB_ExhibitionBooth(QWidget *parent = 0);
    ~DB_ExhibitionBooth();  
    void show();

protected:
    bool event(QEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::DB_ExhibitionBooth *ui;
    ListeningDevicesWorker *m_pListeningDevicesWorker;
    GetResolutionListWorker *m_pGetResolutionListWorker;
    GetCameraFrameWorker *m_pGetCameraFrameWorker;
    QThread *m_pListeningDevicesThread;
    QThread *m_pGetResolutionListThread;
    QThread *m_pGetCameraFrameThread;
    QVector<QString> m_pDeviceNameList;
    CustomItemDelegate *m_pCustomItemDelegate;
    QList<CustomPushButton_3 *> m_pDisplayList;

    QList<CustomPushButton_2*> m_pDeviceBtnList;
    QList<CustomPushButton_2*> m_pResolutionBtnList;
    int m_pLastScreenMode = 2;                              //用来记录上一次的分屏模式,1=单屏，2=双屏，4=四分屏
    QTimer *m_pRestartCameraTimer;
    QVector<QString> m_pDeviceList;                         //设备列表
    QButtonGroup *m_pDeviceGroup;
    QButtonGroup *m_pResolutionGroup;
private:
    //初始化
    void initWidget();
    //添加自定义widget到QMenu
    QWidgetAction * setWidgetToMenu(QWidget *defaultWidget, QMenu *menu);
    void showFrameCover();
    void showDisplayList();
private slots:
    void resize();
    void onDeviceNumChanged();
    void onGetResolutionListFinished();
    void onOpenCameraFinished();
    void onCameraClosed(int ret);
    void onNewFrame(QPixmap pixmap);
    void onReforeBtnClicked();
    void onContrastTeachingClicked();
    void onExitContrastTeachingClicked();
    void onShowResolutionBtnToggled(bool checked);
    void onShowDeviceBtnToggled(bool checked);
    void onShowMenuBtnToggled(bool checked);
    void onResolutionListViewIndexMoved(const QModelIndex &current, const QModelIndex &previous);
    void onFrameCoverClicked();
    void onDisplayClosed();
    void onDisplayScale(bool showFullScreen);
    void onZoomIn();
    void onZoomOut();
    void onRotate();
    void onUndo();
    void onRedo();

    void screenShots(QRectF rect);
    void onTakingPhoto();

signals:
    void exhibitionBoothClosed();
    void displayImage();

};
#endif

#endif // DB_EXHIBITIONBOOTH_H
