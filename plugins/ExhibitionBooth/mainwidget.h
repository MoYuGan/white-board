#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPainter>
#include <QThread>
#include <QVector>
#include <QEvent>
#include <QMouseEvent>
#include <QFileDialog>
#include "Worker/getresolutionlistworker.h"
#include "Worker/listeningdevicesworker.h"
#include "Worker/getcameraframeworker.h"
#include "Menu/resolutionmenu.h"
#include "Menu/devicesmenu.h"
#include "Custom/PushButton/custompushbutton_4.h"
#include "aboutus.h"
#include "Public/publicfunction.h"
#include "Extern/extern.h"
#include "OCR/ocrwidget.h"
#include "Custom/MessageBox/messagebox_tip.h"

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
    void show();
    bool event(QEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void resizeEvent(QResizeEvent *event);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWidget *ui;
    ListeningDevicesWorker *m_pListeningDevicesWorker = nullptr;
    GetResolutionListWorker *m_pGetResolutionListWorker = nullptr;
    GetCameraFrameWorker *m_pGetCameraFrameWorker = nullptr;
    QThread *m_pListeningDevicesThread = nullptr;
    QThread *m_pGetResolutionListThread = nullptr;
    QThread *m_pGetCameraFrameThread = nullptr;
    QVector<QString> m_pDeviceNameList;
    DevicesMenu *m_DeviceMenu = nullptr;
    ResolutionMenu *m_ResolutionMenu = nullptr;
    QList<CustomPushButton_4 *> m_pDisplayList;
    bool m_MousePressed = false;
    bool m_LastMousePoint;
    QString m_DeviceName;
    QButtonGroup *m_DisplayGroup;
    MessageBox_Tip *m_MBoxTip;

    void initWidget();
    void hideMenu();
    void addDisplayWidget(int id, bool useCamera = false, const QPixmap &pixmap = QPixmap(), int angle = 0);
    void removeDisplayWidget(int id);
    void removeDisplayWidget(CustomPushButton_4 *button);
    void getTextPixmap(QPixmap *srcPixmap, QColor bgColor,
                       const QPixmap &logoPixmap = QPixmap(), QSize logoSize = QSize(),
                       const QString &text = QString(), QSize textSize = QSize(), const QFont &font = PublicFunction::getFont(20));
    void clearContrastDisplay();
    void stopGetFrameWorker();
    void startGetFrameWorker(const QString &deviceName);
    void showDisplayPixmap(const QString &text);

private slots:
    void showMainMenu(bool checked);
    void onDeviceNumChanged();
    void onGetResolutionListFinished();
    void onOpenCameraFinished();
    void onCameraClosed(int ret);
    void onNewFrame(QPixmap pixmap);
    void showDeviceListMenu(bool checked);
    void showResolutionListMenu(bool checked);
    void showAbout();
    void showControlMenu(bool checked);
    void moveDisplayRect(QPoint pt);
    void onDisplayImage(bool bo, int id);
    void onDisplayWidgetClosed();
    void onDisplayWidgetShowFullScreen(bool fullScreen);
    void onEnableContrast(int id);
    void onCancelContrast(QPixmap pixmap, int id, int angle);
    void onStartOCR();
    void onTakingPhoto();
    void onLeftRotate();
    void onRightRotate();
    void onZoomIn();
    void onZoomOut();
    void onResolutionChanged(QString resolution);
    void onReforeBtnClicked();
    void onCameraChecked(bool checked, int index);

signals:
    void hideWidget();
    void stopThread();
};

#endif // MAINWIDGET_H
