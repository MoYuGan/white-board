#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QWidget>
#include <QPluginLoader>
#include "Extern/extern.h"
#include "ExportFile/exportfile.h"
#include "../plugins/Plateplate/plateplate_interface.h"
#include "../plugins/ExhibitionBooth/exhibitionbooth_interface.h"
#include "VirtualKeyBoard/keyboard.h"
#include "mod_draw/boardscene.h"
#include "Panel/menupanel.h"
#include "Panel/selectpanel.h"
#include "Panel/penpanel.h"
#include "Panel/erasepanel.h"
#include "Panel/toolpanel.h"
#include "Panel/graphicspanel.h"
#include "Panel/rulerpanel.h"
#include "Panel/pagepanel.h"
#include "Custom/MessageBox/messagebox_1.h"
#include "../plugins/TimerProject/TimerPlugin.h"
#include "../plugins/NewCloud/cloudcoursewareinterface.h"
#include "../plugins/RecordingScreen/recodescreeninteface.h"
#include "../plugins/Calculator/CalculatorInterFace.h"
#include "../plugins/ScreenShot/ScreenShotInterFace.h"
#include "../plugins/VideoPlayer/VideoPlayerInterFace.h"
#include "Panel/backgroundstyle.h"
#include "Panel/setboard.h"
#include "MiniBoard/getpointworker.h"
#include "MiniBoard/checkminiboardnumber.h"
#include "MiniBoard/getpenworker.h"


namespace Ui {
class DrawingBoard;
}

class DrawingBoard : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingBoard(QWidget *parent = 0);
    ~DrawingBoard();
    void resizeWidget();
    // 截屏
    void screenShots();
    void getMiniBoardNumber();
    void closeMiniBoardThread();

private:
    int boardnumber =0;
    bool iseraserleft =false;
    bool iseraserright =false;
    bool isdrawline =true;

private:
    Ui::DrawingBoard *ui;
    //云课件模块
    QButtonGroup *m_pToolButtonGroup;
    void changePenColorHint(QString ,QString );
    char* getPenPath(int );

    /*板中板模块*/
    Plateplate_Interface *m_PlateplateInterface = nullptr;      //插件类
    QWidget *m_PlateplateWidget = nullptr;                      //板中板窗口
    QTimer *m_PlateplateDisplayTimer;

    /*展台插件类*/
    ExhibitionBooth_Interface *m_ExhibitionBoothInterface = nullptr;
    QWidget *m_ExhibitionBoothWidget = nullptr;                         //展台窗口

    /*计时器插件类*/
    TimerPlugin *m_TimerPlugin = nullptr;

     /*截屏插件类*/
    ScreenShotInterFace *m_ScreenShotInterface = nullptr;   //截屏插件类

    /*云课件插件类*/
    CloudCoursewareInterFace *m_CCInterface = nullptr;
    QWidget *m_CCWidget = nullptr;

    CalculatorInterFace *m_CalculatorInterface = nullptr;   //计算器插件类

    RecordScreenInterface *m_RecordScreenInterface = nullptr;   //录屏插件类
    QWidget *m_RecordScreenWidget = nullptr;                    //录屏窗口

    VideoPlayerInterFace *m_VideoPlayerInterface = nullptr;  //播放器插件类
    VideoPlayerInterFace *m_VideoPlayerWidget = nullptr;                  //播放器窗口

    MenuPanel *m_MenuPanel;
    SelectPanel *m_SelectPanel;
    PenPanel *m_PenPanel;
    ErasePanel *m_ErasePanel;
    ToolPanel *m_ToolPanel;
    GraphicsPanel *m_GraphicsPanel;
    BackgroundStyle *m_BackgroundStyle;
    RulerPanel *m_RulerPanel;
    PagePanel *m_pPagePanel;
    SetBoard *m_setBoard;

    GetPointWorker *boardworker=nullptr;
    QThread *boardthread =nullptr;
    GetPointWorker *boardworker2=nullptr;
    QThread *boardthread2 =nullptr;

    GetPenWorker *leftpenworker=nullptr;
    QThread *penthread =nullptr;
    GetPenWorker *rightpenworker=nullptr;
    QThread *penthread2 =nullptr;
    char* leftpenpath =nullptr;
    char* rightpenpath =nullptr;

    QVector<char* >hidapilist;
    QVector<char* >penpathlist;
    CheckMiniBoardNumber *checknumber;
    QColor miniboardrightcolor =Qt::black;
    QColor miniboardleftcolor =Qt::black;

private:
    void initWidget();
    //加载模块
    void loadPlugin();
    // 导出当前页为图片
    void exportToPicture();
    // 导出所有页为图片
    void exportAllToPicture();
    // 导出文件为其他格式（PDF）
    ExportFileWidget* exportToOthreFormats();
    //不阻塞显示消息提示框
    void showMsgBox(const QString &title = QString(),
                    const QString &text = QString(),
                    const QString &leftBtnText = QString(),
                    const QString &midBtnText = QString(),
                    const QString &rightBtnText = QString(),
                    const QString &slotFunction = QString());
    // 打开展台
    void openExhibitionBooth();
    // 打开播放器
    void openVideoPlayer();
    // 显示板中板
    void showPlateplate();
    // 显示遮慕
    void showCoverRect();
    // 显示聚光灯
    void showSpotlight();
    // 打开计算器
    void openCalculator();
    // 打开计时器
    void openTimer();
    // 打开录屏
    void startRecordScreen();
    // 显示锁屏
    void showLockScreen();
    // 插入图片
    void insertPicture();
    // 隐藏指定面板外的其他面板
    void hidePanel(QWidget *widget = nullptr);
    // 导入文件
    void importFile();
    // 按照限定的宽高缩放图片，保持图片原有比例
    QRect scalePixmapWithRect(const QSize &pixmapSize, const QRect &rect);


private slots:
    void onBtnMenuToggled(bool checked);
    void onBtnCloudClicked();
    void onBtnSwitchClicked();
    void onBtnSelectToggled(bool checked);
    void onBtnSelectCheckedClicked();
    void onBtnPenToggled(bool checked);
    void onBtnPenCheckedClicked();
    void onBtnEraseToggled(bool checked);
    void onBtnEraseCheckedClicked();
    void onBtnUndoClicked();
    void onBtnRedoClicked();
    void onBtnMoreClicked();
    void onBtnAddPageClicked();
    void onBtnLastPageClicked();
    void onBtnNextPageClicked();
    void onBtnShowPageToggled(bool checked);
    void onNewBoard();
    void onOpenFile();
    void onExportToFile(int);
    void onShowAboutUs();
    void onExitApplication();
    void onToggleLanguage(bool isChinese);
    void onSelectAll();
    void onClearScene();
    void onShowToolPanel(int);
    void onToolFunction(int);
    void onPageIndexChanged(QGraphicsScene *scene);
    void onSetMiniBoard();
    void onOpenMiniBoard();//允许副板发送信号到屏幕
    void onAddMiniBoard();//添加副板
    void onAgainOpenMiniBoard();//打开副板接口，开启副板
    void onCloseMiniBoard();//禁止副板发送信号到屏幕
    void onMiniBoardNumberChange(int );
    void getNewPoint(_TPPoint );//获得副板发送的数据
    void getNewEraser(_TPPoint );//获得副板发送的数据
    void getMiniBoardShortcutKey(int );//获得快捷键1桌面 2上一页 3下一页 4新建 5键盘 6窗口
    void getNewPenColor(int ,QString );

    void onScreenShotClose();//截图窗口关闭
    void onScreenShotMessage(int );//截图窗口信息
    void onScreenShotPixmap(QPixmap );//截图窗口传递的图像
    void onVideoPlayerScreenShotPixmap(QPixmap );//截图窗口传递的图像
    void onVideoPlayerClose();

    void onMBoxRet_NewBoard(int);
    void onMBoxRet_ExitApplication(int);
    void onMBoxRet_OpenFile(int);

    void onBackgroundChanged();
    void onAllBackgroundChanged();

    //取消工具按钮的选中状态
    void uncheckTools();
    void restartApplication(int i);
    void onPlateplateClosed();
    void onPlateplateDisplayTimerTimeOut();
    void onExhibitionBoothClosed();

    void onTimerWidgetClosed();
    void onCalculatorClosed();

signals:
    void boardClosed(int);
    void showMinimizedSignal();
    void showMaximizedSignal();
    void sendHidapiPath1(char* );
    void sendHidapiPath2(char* );

    void sendHidapiPenPath1(char* );
    void sendHidapiPenPath2(char* );
private:
    void updateLanguaue(bool isChinese);
};

#endif // DRAWINGBOARD_H
