#include "drawingboard.h"
#include "ui_drawingboard.h"
#include "Public/public_function.h"
#include <QButtonGroup>
#include <QFileDialog>
#include <QDateTime>
#include "applicationconfig.h"
#include <QListWidget>
#include <QWidgetAction>
#include <QScroller>
#include <QMenu>
#include <QDir>
#include <QDateTime>
#include "aboutus.h"
#include "CustomWidget/db_custompushbutton.h"
#include "FileOperations/m_pdf.h"
#include "Spotlight/light.h"
#include "Lockscreen/mylock.h"
#include "Veil/myveil.h"
#include <QScreen>
#include "Custom/Widget/widget_2.h"
#include <QTime>
#include <QByteArray>
#include <QPropertyAnimation>
#include "changebackgroundpixmapthread.h"
#include "Common/toolkit.h""

#define MYTEST
#ifdef IS_UNIX
#define UNIX_LIB_DIR "/opt/apps/com.amdox.board/files/lib/AMLib"
#endif

DrawingBoard::DrawingBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawingBoard)
{
    ui->setupUi(this);
    this->loadPlugin();
    this->initWidget();
    this->onBtnAddPageClicked();
    ui->pPen->setChecked(true);

}

DrawingBoard::~DrawingBoard()
{
    delete ui;
}

void DrawingBoard::initWidget()
{
    ui->verticalLayoutWidget_8->hide();
    this->setLayout(ui->verticalLayout);

    /*左工具栏*/
    ui->frame_left->setLayout(ui->horizontalLayout_5);
    ui->pMenu->setIcon(QIcon(":/images/main/mainpixmap/caidan_1@2x.png"));
    ui->pMinimize->setIcon(QIcon(":/images/main/mainpixmap/zuixiaohua_1@2x.png"));
    ui->pCloud->setIcon(QIcon(":/images/main/mainpixmap/yunkejian_1@2x.png"));
//djf    ui->pCloud->hide();
    connect(ui->pMenu, &PushButton_Basic::toggled, this, &DrawingBoard::onBtnMenuToggled);
    connect(ui->pMinimize, &PushButton_Basic::clicked, this, [=](){ this->hidePanel(); emit this->showMinimizedSignal();});
    connect(ui->pCloud, &PushButton_Basic::clicked, this, &DrawingBoard::onBtnCloudClicked);

    /*中工具栏*/
    ui->frame_mid->setLayout(ui->horizontalLayout_6);
    ui->pSelect->mSetIcon(QPixmap(":/images/main/mainpixmap/xuanze_1@2x.png"));
    ui->pSelect->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/xuanze2_1@2x.png"));
    ui->pSelect->mSetText(tr("选择"));
    ui->pPen->mSetIcon(QPixmap(":/images/main/mainpixmap/bichu_1@2x.png"));
    ui->pPen->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/bichu2_1@2x.png"));
    ui->pPen->mSetText(tr("笔"));
    ui->pEarser->mSetIcon(QPixmap(":/images/main/mainpixmap/cachu_1@2x.png"));
    ui->pEarser->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/cachu2_1@2x.png"));
    ui->pEarser->mSetText(tr("擦除"));
    ui->pUndo->mSetIcon(QPixmap(":/images/main/mainpixmap/chexiao_1@2x.png"));
    ui->pUndo->mSetText(tr("撤销"));
    ui->pRedo->mSetIcon(QPixmap(":/images/main/mainpixmap/huifu_1@2x.png"));
    ui->pRedo->mSetText(tr("恢复"));
    ui->pMore->mSetIcon(QPixmap(":/images/main/mainpixmap/gengduo_1@2x.png"));
    ui->pMore->mSetText(tr("更多"));
    connect(ui->pSelect, &PushButton_2::toggled, this, &DrawingBoard::onBtnSelectToggled);
    connect(ui->pSelect, &PushButton_2::checkedClicked, this, &DrawingBoard::onBtnSelectCheckedClicked);
    connect(ui->pPen, &PushButton_2::toggled, this, &DrawingBoard::onBtnPenToggled);
    connect(ui->pPen, &PushButton_2::checkedClicked, this, &DrawingBoard::onBtnPenCheckedClicked);
    connect(ui->pEarser, &PushButton_2::toggled, this, &DrawingBoard::onBtnEraseToggled);
    connect(ui->pEarser, &PushButton_2::checkedClicked, this, &DrawingBoard::onBtnEraseCheckedClicked);
    connect(ui->pUndo, &PushButton_2::clicked, this, &DrawingBoard::onBtnUndoClicked);
    connect(ui->pRedo, &PushButton_2::clicked, this, &DrawingBoard::onBtnRedoClicked);
    connect(ui->pMore, &PushButton_2::clicked, this, &DrawingBoard::onBtnMoreClicked);
    m_pToolButtonGroup = new QButtonGroup(this);
    m_pToolButtonGroup->setExclusive(true);
    m_pToolButtonGroup->addButton(ui->pSelect);
    m_pToolButtonGroup->addButton(ui->pPen);
    m_pToolButtonGroup->addButton(ui->pEarser);

    /*页管理栏*/
    ui->frame_right->setLayout(ui->horizontalLayout_7);
    ui->frame_page->setLayout(ui->horizontalLayout_8);
    connect(ui->pLastPage, &QPushButton::clicked, this, &DrawingBoard::onBtnLastPageClicked);
    connect(ui->pNextPage, &QPushButton::clicked, this, &DrawingBoard::onBtnNextPageClicked);
    connect(ui->pAdd, &QPushButton::clicked, this, &DrawingBoard::onBtnAddPageClicked);
    connect(ui->pShowPage, &QPushButton::toggled, this, &DrawingBoard::onBtnShowPageToggled);

    /*左右切换按钮*/
    ui->pSwitchLeft->mSetIcon(QPixmap(":/images/main/mainpixmap/qiehuan_1@2x.png"));
    ui->pSwitchRight->mSetIcon(QPixmap(":/images/main/mainpixmap/qiehuan2_1@2x.png"));
    connect(ui->pSwitchLeft, &DB_CustomPushButton_9::clicked, this, &DrawingBoard::onBtnSwitchClicked);
    connect(ui->pSwitchRight, &DB_CustomPushButton_9::clicked, this, &DrawingBoard::onBtnSwitchClicked);

    /*其他*/
    connect(ui->graphicsView, &DB_BoardView::mousePressed, this, [=](){ this->hidePanel(); });
    connect(ui->graphicsView, &DB_BoardView::drawGraphicFinished, this, [=](){ui->pSelect->click();});

    m_MenuPanel = new MenuPanel(this);
    m_MenuPanel->hide();
    connect(m_MenuPanel, &MenuPanel::newBoard, this, &DrawingBoard::onNewBoard);
    connect(m_MenuPanel, &MenuPanel::openFile, this, &DrawingBoard::onOpenFile);
    connect(m_MenuPanel, &MenuPanel::exportToFile, this, &DrawingBoard::onExportToFile);
    connect(m_MenuPanel, &MenuPanel::showAboutUs, this, &DrawingBoard::onShowAboutUs);
    connect(m_MenuPanel, &MenuPanel::exitApplication, this, &DrawingBoard::onExitApplication);
    connect(m_MenuPanel, &MenuPanel::toggleLanguage, this, &DrawingBoard::onToggleLanguage);
    connect(m_MenuPanel, &MenuPanel::panelHide, this, [=](){ui->pMenu->setChecked(false);});

    m_SelectPanel = new SelectPanel(this);
    m_SelectPanel->hide();
    connect(m_SelectPanel, &SelectPanel::selectAll, this, &DrawingBoard::onSelectAll);
    connect(m_SelectPanel, &SelectPanel::panelHide, this, [=](){ ui->pSelect->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/xuanze2_1@2x.png")); });

    m_PenPanel = new PenPanel(this);
    m_PenPanel->hide();
    connect(m_PenPanel, &PenPanel::panelHide, this, [=](){ui->pPen->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/bichu2_1@2x.png"));});
    m_PenPanel->setCheckedColor(1);
    m_PenPanel->setCheckedSize(2);

    m_ErasePanel = new ErasePanel(this);
    m_ErasePanel->hide();
    connect(m_ErasePanel, &ErasePanel::clearSignal, this, &DrawingBoard::onClearScene);
    connect(m_ErasePanel, &ErasePanel::panelHide, this, [=](){ ui->pEarser->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/cachu2_1@2x.png")); });
    connect(m_ErasePanel, &ErasePanel::eraseSizeChanged, this, [=](QSize size) { g_EraserSize = size; });
    m_ErasePanel->setCheckedSize(1);

    m_ToolPanel = new ToolPanel(this);
    m_ToolPanel->hide();
    connect(m_ToolPanel, &ToolPanel::showPanel, this, &DrawingBoard::onShowToolPanel);
    connect(m_ToolPanel, &ToolPanel::toolFunction, this, &DrawingBoard::onToolFunction);

    m_GraphicsPanel = new GraphicsPanel(this);
    m_GraphicsPanel->hide();
    connect(m_GraphicsPanel, &GraphicsPanel::goBack, this, [=](){m_GraphicsPanel->hide(); this->onShowToolPanel(0);});

    m_BackgroundStyle = new BackgroundStyle(this);
    m_BackgroundStyle->hide();
    connect(m_BackgroundStyle, &BackgroundStyle::backgroundChanged, this, &DrawingBoard::onBackgroundChanged);
    connect(m_BackgroundStyle, &BackgroundStyle::sendChangeAllBackgroundSianal, this, &DrawingBoard::onAllBackgroundChanged);
    connect(m_BackgroundStyle, &BackgroundStyle::goBack, this, [=](){m_BackgroundStyle->hide(); this->onShowToolPanel(0);});

    m_RulerPanel = new RulerPanel(this);
    m_RulerPanel->hide();
    connect(m_RulerPanel, &RulerPanel::goBack, this, [=](){m_RulerPanel->hide(); this->onShowToolPanel(0);});
    connect(m_RulerPanel, &RulerPanel::addRuler, this, [=](int type){ui->graphicsView->addChiGuiItem(type);});

    m_pPagePanel = new PagePanel(this);
    m_pPagePanel->hide();
    connect(m_pPagePanel, &PagePanel::panelHide, this, [=](){ ui->pShowPage->setChecked(false); });
    connect(m_pPagePanel, &PagePanel::pageIndexChanged, this, &DrawingBoard::onPageIndexChanged);

    m_PlateplateDisplayTimer = new QTimer(this);
    connect(m_PlateplateDisplayTimer, &QTimer::timeout, this, &DrawingBoard::onPlateplateDisplayTimerTimeOut);

    ui->frame_left->raise();
    ui->frame_mid->raise();
    ui->frame_right->raise();
    ui->pSwitchLeft->raise();
    ui->pSwitchRight->raise();

    m_setBoard =new SetBoard(this);
    m_setBoard->hide();

    onAgainOpenMiniBoard();

    checknumber =new CheckMiniBoardNumber();
    checknumber->setNumber(boardnumber);
    connect(checknumber,&CheckMiniBoardNumber::sendNumberChangeSignal,this,&DrawingBoard::onMiniBoardNumberChange);
    if(boardnumber !=0)checknumber->start();

    connect(m_MenuPanel, &MenuPanel::sendSetBoardSignal, this,&DrawingBoard::onSetMiniBoard);
    connect(m_setBoard,&SetBoard::sendOpenBoardSignal,this,&DrawingBoard::onOpenMiniBoard);
    connect(m_setBoard,&SetBoard::sendAgainOpenBoardSignal,this,[=](){m_setBoard->setBoardNumber(boardnumber);});
    connect(m_setBoard,&SetBoard::sendCloseBoardSignal,this,&DrawingBoard::onCloseMiniBoard);
    connect(m_setBoard,&SetBoard::sendSetCloseSignal,this,[=](){m_MenuPanel->hide(),m_MenuPanel->disableSet();});
}

void DrawingBoard::resizeWidget()
{
    this->setFixedSize(g_ScreenWidth, g_ScreenHeight);
    ui->graphicsView->setFixedSize(this->size());

    QSize size;
    int border;
    int radius;
    QFont font;

    /*左工具栏*/
    size = Public_Function::getScaleSize(QSize(48, 52));
    ui->pMenu->setFixedWidth(size.width());
    ui->pMinimize->setFixedWidth(size.width());
    ui->pCloud->setFixedWidth(size.width());
    size = Public_Function::getScaleSize(QSize(24, 24));
    ui->pMenu->setIconSize(size);
    ui->pMinimize->setIconSize(size);
    ui->pCloud->setIconSize(size);
    //size = Public_Function::getScaleSize(QSize(188, 48));
    size = Public_Function::getScaleSize(QSize(120, 48));
    ui->frame_left->setFixedSize(size);
    ui->frame_left->mSetBackgroudColor(Qt::white);
    ui->frame_left->mSetBorder(Public_Function::getScaleSize(2));
    radius = Public_Function::getScaleSize(5);
    ui->frame_left->mSetBordRadius(radius, radius, radius, radius);
    ui->horizontalLayout_5->setContentsMargins(Public_Function::getScaleSize(6), 0,
                                               Public_Function::getScaleSize(6), 0);
    ui->vLayout_menu->setContentsMargins(0, Public_Function::getScaleSize(2),
                                         0, Public_Function::getScaleSize(2));
    ui->vLayout_minimize->setContentsMargins(0, Public_Function::getScaleSize(2),
                                         0, Public_Function::getScaleSize(2));
    ui->vLayout_cloud->setContentsMargins(0, Public_Function::getScaleSize(2),
                                         0, Public_Function::getScaleSize(2));

    /*中工具栏*/
    border = Public_Function::getScaleSize(10);
    size = Public_Function::getScaleSize(QSize(70, 70));
    ui->pSelect->setFixedWidth(size.width());
    ui->pPen->setFixedWidth(size.width());
    ui->pEarser->setFixedWidth(size.width());
    ui->pUndo->setFixedWidth(size.width());
    ui->pRedo->setFixedWidth(size.width());
    ui->pMore->setFixedWidth(size.width());
    size = Public_Function::getScaleSize(QSize(50, 50));
    ui->pSelect->mSetIconSize(size);
    ui->pPen->mSetIconSize(size);
    ui->pEarser->mSetIconSize(size);
    ui->pUndo->mSetIconSize(size);
    ui->pRedo->mSetIconSize(size);
    ui->pMore->mSetIconSize(size);
    if (!ui->pSelect->isChecked())
        ui->vlayout_select->setContentsMargins(0, border, 0, 0);
    if (!ui->pPen->isChecked())
        ui->vlayout_pen->setContentsMargins(0, border, 0, 0);
    if (!ui->pEarser->isChecked())
        ui->vlayout_eraser->setContentsMargins(0, border, 0, 0);
    ui->vlayout_undo->setContentsMargins(0, border, 0, 0);
    ui->vlayout_redo->setContentsMargins(0, border, 0, 0);
    ui->vlayout_more->setContentsMargins(0, border, 0, 0);
    ui->horizontalLayout_6->setContentsMargins(0, Public_Function::getScaleSize(5),
                                               0, Public_Function::getScaleSize(5));
    ui->frame_mid->mSetBackgroudColor(Qt::white);
    ui->frame_mid->mSetBorder(Public_Function::getScaleSize(2));
    radius = Public_Function::getScaleSize(12);
    ui->frame_mid->mSetBordRadius(radius, radius, 0, 0);
    ui->frame_mid->mSetMargin(0, border, 0, 0);
    size = Public_Function::getScaleSize(QSize(524, 80));
    ui->frame_mid->setFixedSize(size.width(), size.height() + border);
    ui->frame_mid->move(QPoint((this->width() - ui->frame_mid->width())/2,
                               (this->height() - ui->frame_mid->height())));

    /*右工具栏*/
    size = Public_Function::getScaleSize(QSize(30, 30));
    ui->pAdd->setFixedSize(size);
    ui->pLastPage->setFixedSize(size);
    ui->pNextPage->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(20, 20));
    ui->pShowPage->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(288, 48));
    ui->frame_right->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(116, 36));
    ui->frame_page->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(24, 48));
    ui->frame_right->mSetBackgroudColor(Qt::white);
    ui->frame_right->mSetBorder(Public_Function::getScaleSize(2));
    radius = Public_Function::getScaleSize(5);
    ui->frame_right->mSetBordRadius(radius, radius, radius, radius);
    font = Public_Function::getFont(11);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 5);
    ui->label_page->setFont(font);
    ui->frame_page->setStyleSheet(QString("#%2{border: %3px solid; border-radius: %4px;}  %1")
                                 .arg(ui->frame_page->styleSheet()).arg(ui->frame_page->objectName())
                                 .arg(1).arg(Public_Function::getScaleSize(5)));
    ui->horizontalLayout_8->setContentsMargins(0, 0, Public_Function::getScaleSize(5), 0);

    /*左右切换按钮*/
    size = Public_Function::getScaleSize(QSize(24, 48));
    ui->pSwitchLeft->setFixedSize(size);
    ui->pSwitchRight->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(12, 18));
    ui->pSwitchLeft->mSetIconSize(size);
    ui->pSwitchRight->mSetIconSize(size);
    radius = Public_Function::getScaleSize(5);
    ui->pSwitchLeft->setBackgroudColor(Qt::white);
    ui->pSwitchLeft->setBorder(Public_Function::getScaleSize(2));
    ui->pSwitchLeft->setBordRadius(radius, radius, radius, radius);
    ui->pSwitchRight->setBackgroudColor(Qt::white);
    ui->pSwitchRight->setBorder(Public_Function::getScaleSize(2));
    ui->pSwitchRight->setBordRadius(radius, radius, radius, radius);

    m_MenuPanel->resizeWidget();
    m_SelectPanel->resizeWidget();
    m_ErasePanel->resizeWidget();
    m_PenPanel->resizeWidget();
    m_ToolPanel->resizeWidget();
    m_GraphicsPanel->resizeWidget();
    m_RulerPanel->resizeWidget();
    m_pPagePanel->resizeWidget();

    ui->frame_left->move(QPoint(Public_Function::getScaleSize(16) + ui->frame_left->mGetBorder(),
                                this->height() - Public_Function::getScaleSize(16) +
                                ui->frame_left->mGetBorder() - ui->frame_left->height()));
    ui->frame_right->move(QPoint(this->width() - ui->frame_right->width() -
                                 Public_Function::getScaleSize(16) - ui->frame_right->mGetBorder(),
                                 this->height() - Public_Function::getScaleSize(16) +
                                 ui->frame_right->mGetBorder() - ui->frame_right->height()));
    ui->pSwitchLeft->move(QPoint(ui->frame_left->x() + ui->frame_left->width(), ui->frame_left->y()));
    ui->pSwitchRight->move(QPoint(ui->frame_right->x() - ui->pSwitchRight->width(), ui->frame_right->y()));
    ui->frame_mid->move(QPoint((this->width() - ui->frame_mid->width())/2,
                               this->height() - ui->frame_mid->height()));

    m_setBoard->move((this->width() -m_setBoard->width())/2,(this->height() -m_setBoard->height())/2);

}

void DrawingBoard::loadPlugin()
{

    QPluginLoader pluginLoader;
#ifdef IS_UNIX
    //加载板中板模块
    pluginLoader.setFileName((QString("%1/libPlateplate.so").arg(UNIX_LIB_DIR)));
    pluginLoader.load();
    QObject *plugin = pluginLoader.instance();
    if(plugin) {
        m_PlateplateInterface = qobject_cast<Plateplate_Interface*>(plugin);
    }
#endif

#ifdef IS_UNIX
    //展台模块
    pluginLoader.setFileName((QString("%1/libAmdoxBooth.so").arg(UNIX_LIB_DIR)));
    pluginLoader.load();
    plugin = pluginLoader.instance();
    if(plugin) {
        m_ExhibitionBoothInterface = qobject_cast<ExhibitionBooth_Interface*>(plugin);
        m_ExhibitionBoothInterface->setParent(this);
    }else
        qDebug()<<pluginLoader.errorString();
#endif

#ifdef IS_UNIX
    //加载云课堂模块
    pluginLoader.setFileName((QString("%1/libNewCloud.so").arg(UNIX_LIB_DIR)));
    pluginLoader.load();
    plugin = pluginLoader.instance();
    if(plugin) {
        m_CCInterface = qobject_cast<CloudCoursewareInterFace*>(plugin);
        m_CCWidget = m_CCInterface->createWidget(this);
        m_CCWidget->hide();
    }
#endif



#ifdef IS_UNIX
    //加载录屏模块
    pluginLoader.setFileName((QString("%1/libRecoS.so").arg(UNIX_LIB_DIR)));
    pluginLoader.load();
    plugin = pluginLoader.instance();
    if(plugin) {
        m_RecordScreenInterface = qobject_cast<RecordScreenInterface*>(plugin);
    }
#endif

#ifdef IS_UNIX
    //加载播放器模块
    pluginLoader.setFileName((QString("%1/libVideoPlayer.so").arg(UNIX_LIB_DIR)));
    pluginLoader.load();
    plugin = pluginLoader.instance();
    if(plugin) {
        m_VideoPlayerInterface = qobject_cast<VideoPlayerInterFace*>(plugin);
    }
#endif

    return;
}

void DrawingBoard::exportToPicture()
{
    QFileDialog *fileDialog = new QFileDialog(this, Qt::Widget);
    fileDialog->setWindowModality(Qt::WindowModal);
    QString filter;
    int index = m_pPagePanel->getPageIndex();
    Keyboard key;
    key.hide();
    QString fileName = fileDialog->getSaveFileName(this, tr("导出当前页为图片"), QString("安道白板-第%1页").arg(++index)
                                                  , "PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)", &filter);
    fileDialog->deleteLater();
    if (fileName.length() == 0)
        return;

    QString dirPath;
    dirPath = fileName.mid(0, fileName.lastIndexOf("/"));
    if (dirPath.isEmpty()) {  //说明是根目录 {
        //dirPath = "/";
        if (fileName.mid(fileName.lastIndexOf("/") + 1).compare("\\") == 0) {
            //文件名非法
            return;
        }
    }else {
        QDir dir;
        dir.setPath(dirPath);
        if (!dir.exists()) {
            //路径不存在
            return;
        }
    }

    fileName = fileName.mid(fileName.lastIndexOf("/") + 1);     //获取文件名
    fileName.replace("\\", "");
    QString name = fileName;
    QString format;
    if (filter.compare("PNG(*.png)") == 0) {
        format = QString(".png");
        if (fileName.size() > 4 && fileName.mid(fileName.size() -4).compare(".png") == 0)
            name = fileName.mid(0, fileName.size() - 4);
    }else if(filter.compare("JPG(*.jpg)") == 0) {
        format = QString(".jpg");
        if (fileName.size() > 4 && fileName.mid(fileName.size() - 4).compare(".jpg") == 0)
            name = fileName.mid(0, fileName.size() - 4);
    }else if(filter.compare("BMP(*.bmp)") == 0) {
        format = QString(".bmp");
        if (fileName.size() > 4 && fileName.mid(fileName.size() - 4).compare(".bmp") == 0)
            name = fileName.mid(0, fileName.size() - 4);
    }
    QFile file(QString("%1/%2%3").arg(dirPath,name,format));
    int i = 1;
    while(file.exists()) {
        file.setFileName(QString("%1/%2 (%3)%4").arg(dirPath).arg(name).arg(i).arg(format));
        i++;
    }
    ExportFileWidget *exportWidget = new ExportFileWidget(this);
    exportWidget->setGeometry(this->rect());
    exportWidget->show();
    exportWidget->saveFile(QList<QPixmap>()<<this->m_pPagePanel->getScenePixmap(m_pPagePanel->getPageIndex()), file.fileName());
}

void DrawingBoard::exportAllToPicture()
{
    QFileDialog fileDialog;
    fileDialog.setWindowModality(Qt::WindowModal);
    Keyboard key;
    //key.move((this->width() -key.width())/2,this->rect().bottom() -key.height() -Public_Function::getScaleSize(70));
    key.hide();
    QString dirName = fileDialog.getExistingDirectory(this, tr("选择文件夹"), "/");
    if (dirName.length() == 0)
        return;

    QDateTime dateTime = QDateTime::currentDateTime();
    dirName = QString("%1/安道白板图片导出-%2").arg(dirName).arg(dateTime.date().toString("yyyyMMdd"));
    QDir dir;
    dir.setPath(dirName);
    int i = 1;
    while(dir.exists()) {
        dir.setPath(QString("%1 (%2)").arg(dirName).arg(i));
        i++;
    }
    if (dir.mkdir(dir.path())) {
        ExportFileWidget *exportWidget = new ExportFileWidget(this);
        exportWidget->setGeometry(this->rect());
        exportWidget->show();
        QList<QPixmap> pixmapList;
        this->m_pPagePanel->getAllScenePixmap(&pixmapList);
        exportWidget->saveFile(pixmapList, dir.path());
    }
    return;
}

ExportFileWidget* DrawingBoard::exportToOthreFormats()
{
    ExportFileWidget* exportWidget = nullptr;

    QFileDialog fileDialog;
    fileDialog.setWindowModality(Qt::WindowModal);
    QString filter;

    QDateTime dateTime = QDateTime::currentDateTime();
    Keyboard key;
    key.hide();
    QString fileName = fileDialog.getSaveFileName(this, tr("另存为"), QString("%1/安道白板导出-%2").arg("")
                                                  .arg(dateTime.date().toString("yyyyMMdd"))
                                                  , "PDF(*.pdf);;", &filter);
    if (fileName.length() == 0)
        return exportWidget;
    QString dirPath;
    dirPath = fileName.mid(0, fileName.lastIndexOf("/"));
    if (dirPath.isEmpty()) {  //说明是根目录 {
        //dirPath = "/";
        if (fileName.mid(fileName.lastIndexOf("/") + 1).compare("\\") == 0) {
            //文件名非法
            return exportWidget;
        }
    }else {
        QDir dir;
        dir.setPath(dirPath);
        if (!dir.exists()) {
            //路径不存在
            return exportWidget;
        }
    }
    fileName = fileName.mid(fileName.lastIndexOf("/") + 1);     //获取文件名
    fileName.replace("\\", "");
    QString name = fileName;
    QString format;
    if (filter.compare("PDF(*.pdf)") == 0) {
        format = QString(".pdf");
        if (fileName.size() > 4 && fileName.mid(fileName.size() - 4).compare(".pdf") == 0)
            name = fileName.mid(0, fileName.size() - 4);
    }

    QFile file(QString("%1/%2%3").arg(dirPath).arg(name).arg(format));
    int i = 1;
    while(file.exists()) {
        file.setFileName(QString("%1/%2 (%3)%4").arg(dirPath).arg(name).arg(i).arg(format));
        i++;
    }
    exportWidget = new ExportFileWidget(this);
    exportWidget->setGeometry(this->rect());
    exportWidget->show();
    QList<QPixmap> pixmapList;
    this->m_pPagePanel->getAllScenePixmap(&pixmapList);
    exportWidget->saveFile(pixmapList, file.fileName());
    return exportWidget;
}


void DrawingBoard::showMsgBox(const QString &title, const QString &text, const QString &leftBtnText,
                                 const QString &midBtnText, const QString &rightBtnText, const QString &slotFunction)
{
    MessageBox_1 *mbox = new MessageBox_1(title, text, leftBtnText, midBtnText, rightBtnText, this);
    mbox->setGeometry(this->rect());

    if (!slotFunction.isEmpty())
        connect(mbox, SIGNAL(mboxClosed(int)), this, slotFunction.toLatin1().data());
    connect(mbox, &MessageBox_1::mboxClosed, [=](){
        mbox->deleteLater();
    });
    mbox->show();
}

void DrawingBoard::screenShots()
{
    if (nullptr == m_ScreenShotInterface)
    {
        QPluginLoader pluginLoader;
    #ifdef IS_UNIX
        //加载截屏模块
        pluginLoader.setFileName((QString("%1/libScreenShot.so").arg(UNIX_LIB_DIR)));
        pluginLoader.load();
        QObject *plugin = pluginLoader.instance();
        if(plugin) {
            m_ScreenShotInterface = qobject_cast<ScreenShotInterFace*>(plugin);
            m_ScreenShotInterface = m_ScreenShotInterface->getWidget();
            m_ScreenShotInterface->updateLanguage(ToolKit::IsChineseLanguage());
            connect(m_ScreenShotInterface, SIGNAL(sendCloseMessage()), this,SLOT(onScreenShotClose()));
            connect(m_ScreenShotInterface, SIGNAL(sendDesktopShow(int )), this,SLOT(onScreenShotMessage(int )));
            connect(m_ScreenShotInterface, SIGNAL(sendShotPixmap(QPixmap )), this,SLOT(onScreenShotPixmap(QPixmap )));
            m_ScreenShotInterface->move((this->width() - m_ScreenShotInterface->width())/2,(this->height() - m_ScreenShotInterface->height())/2);
            m_ScreenShotInterface->show();
        }
    #endif
    }
    return;
}

void DrawingBoard::getMiniBoardNumber()
{
    m_setBoard->setBoardNumber(boardnumber);
}

void DrawingBoard::closeMiniBoardThread()
{
    if(boardworker!=nullptr)boardworker->closeThread();
    if(boardworker2!=nullptr)boardworker2->closeThread();
    if(checknumber!=nullptr)checknumber->closeThread();
    if(leftpenworker!=nullptr)leftpenworker->closeThread();
    if(rightpenworker!=nullptr)rightpenworker->closeThread();
}

void DrawingBoard::changePenColorHint(QString pos, QString color)
{
    if(!isdrawline)return;
    if(color =="none")return;
    QLabel* label = new QLabel(this);
    label->setFixedSize(Public_Function::getScaleSize(434,280));
    label->setScaledContents(true);
    label->show();
    if(color =="red")label->setPixmap(QPixmap(":/images/pen/redpen@2x.png"));
    else if(color =="blue")label->setPixmap(QPixmap(":/images/pen/bluepen@2x.png"));
    else if(color =="black")label->setPixmap(QPixmap(":/images/pen/blackpen@2x.png"));
    label->raise();
    QTimer* timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
       label->deleteLater();
       timer->deleteLater();
    });
    timer->start(2000);
    if(pos =="left")
    {
      label->move(Public_Function::getScaleSize(250),(this->height() -label->height())/2);
    }
    else if(pos =="right")
    {
      label->move(this->width() -Public_Function::getScaleSize(250) -label->width(),(this->height() -label->height())/2);
    }
}

char *DrawingBoard::getPenPath(int id)
{
    QVector<char*>::iterator iter;
    for (iter = penpathlist.begin(); iter != penpathlist.end(); iter++)
    {
        if (hid_init())
        {
            return nullptr;
        }
        hid_device *m_Handle =hid_open_path(*iter);
        if (!m_Handle)
        {
            return nullptr;
        }
        unsigned char buf[64];
        int res = 0;
        memset(buf, 0, sizeof(buf));
        res = hid_read(m_Handle, buf, sizeof(buf));
        if (res < 0) {
            break;
        }else if (res > 0) {
            if(id ==QString::number(buf[5]).toInt())
            {
                hid_close(m_Handle);
                return *iter;
            }
        }
        hid_close(m_Handle);
    }
    return nullptr;
}

void DrawingBoard::openExhibitionBooth()
{
    if (nullptr != m_ExhibitionBoothInterface &&m_ExhibitionBoothWidget ==nullptr) {
        m_ExhibitionBoothWidget = m_ExhibitionBoothInterface->create(this, SLOT(onExhibitionBoothClosed()));
        m_ExhibitionBoothWidget->setGeometry(this->rect());
        m_ExhibitionBoothInterface->showWidget();
        m_ExhibitionBoothWidget->raise();
    }else
    m_ExhibitionBoothWidget->show();
}

void DrawingBoard::openVideoPlayer()
{
    if (nullptr == m_VideoPlayerWidget)
    {
        QPluginLoader pluginLoader;
    #ifdef IS_UNIX
        pluginLoader.setFileName((QString("%1/libVideoPlayer.so").arg(UNIX_LIB_DIR)));
        pluginLoader.load();
        QObject *plugin = pluginLoader.instance();
        if(plugin) {
            m_VideoPlayerInterface = qobject_cast<VideoPlayerInterFace*>(plugin);
            m_VideoPlayerWidget = m_VideoPlayerInterface->createWidget(this);
            if (nullptr == m_VideoPlayerWidget)
                return;
            connect(m_VideoPlayerWidget, SIGNAL(sendScreenshotPixmapSignal(QPixmap )), this,SLOT(onVideoPlayerScreenShotPixmap(QPixmap )));
            connect(m_VideoPlayerWidget, SIGNAL(sendWidgetCloseSignal()), this,SLOT(onVideoPlayerClose()));
            m_VideoPlayerWidget->move((this->width() - m_VideoPlayerWidget->width())/2,(this->height() - m_VideoPlayerWidget->height())/2);
            m_VideoPlayerWidget->show();
            m_VideoPlayerWidget->openFilePath();
            m_VideoPlayerWidget->raise();
        }
    #endif
    }
    return;

}

void DrawingBoard::showPlateplate()
{
    if (nullptr != m_PlateplateInterface) {
        m_PlateplateWidget = m_PlateplateInterface->create(this, SLOT(onPlateplateClosed()));
        m_PlateplateWidget->setFixedSize(this->size());
        m_PlateplateWidget->move(QPoint(0, -this->height()));
        m_PlateplateWidget->show();
        m_PlateplateWidget->raise();
        m_PlateplateDisplayTimer->setProperty("FUNCTION", "show");
        m_PlateplateDisplayTimer->start(20);
    }
}

void DrawingBoard::showCoverRect()
{
    Myveil *coverRect = new Myveil(ui->graphicsView);
    QRect rect = QRect(0, 0, Public_Function::getScaleSize(466), Public_Function::getScaleSize(318));
    rect.moveCenter(ui->graphicsView->rect().center());
    coverRect->setGeometry(rect);
    coverRect->show();
    coverRect->raise();
}

void DrawingBoard::showSpotlight()
{
    Light *light = new Light(this);
    light->show();
    light->raise();
    connect(light,&Light::getShowPixmap,this,[=](QPixmap *pix){
        BoardScene *scene = ui->graphicsView->getItemScene();
        if (nullptr == scene)
            return;
        *pix = scene->getSceneToPixmap();
    },Qt::DirectConnection);
}

void DrawingBoard::openCalculator()
{
    if (nullptr == m_CalculatorInterface)
    {
    #ifdef IS_UNIX
        //加载计算器模块
        QPluginLoader pluginLoader;
        pluginLoader.setFileName((QString("%1/libCalculator.so").arg(UNIX_LIB_DIR)));
        pluginLoader.load();
        QObject *plugin = pluginLoader.instance();
        if(plugin) {
            m_CalculatorInterface = qobject_cast<CalculatorInterFace*>(plugin);
            m_CalculatorInterface = m_CalculatorInterface->getWidget();
            m_CalculatorInterface->updateLanguage(ToolKit::IsChineseLanguage());
            connect(m_CalculatorInterface, SIGNAL(sendCloseMessage()), this, SLOT(onCalculatorClosed()));
            m_CalculatorInterface->setParent(this);
            m_CalculatorInterface->move((this->width() - m_CalculatorInterface->width())/2,(this->height() - m_CalculatorInterface->height())/2);
            m_CalculatorInterface->show();
        }else {
            m_CalculatorInterface = nullptr;
        }
    #endif
    }
    return;
}

void DrawingBoard::openTimer()
{
    if (nullptr != m_TimerPlugin)
        return;

    QPluginLoader pluginLoader;
#ifdef IS_UNIX
    //加载计时器模块
    pluginLoader.setFileName((QString("%1/libTimerProject.so").arg(UNIX_LIB_DIR)));
    pluginLoader.load();
    QObject *plugin_timer = pluginLoader.instance();
    if(plugin_timer) {
        m_TimerPlugin = qobject_cast<TimerPlugin*>(plugin_timer);
        m_TimerPlugin->setParent(this);
        m_TimerPlugin->updateLanguage(ToolKit::IsChineseLanguage() );
        connect(m_TimerPlugin, SIGNAL(widgetClosed()), this, SLOT(onTimerWidgetClosed()));
        m_TimerPlugin->move((this->width() - m_TimerPlugin->width())/2,(this->height() - m_TimerPlugin->height())/2);
        m_TimerPlugin->show();
        m_TimerPlugin->raise();
    }
#endif
}

void DrawingBoard::startRecordScreen()
{
    if (nullptr == m_RecordScreenInterface)
        return;

    m_RecordScreenWidget = m_RecordScreenInterface->create(this);
    m_RecordScreenWidget->move((this->width() - m_RecordScreenWidget->width())/2,(this->height() - m_RecordScreenWidget->height())/2);
    m_RecordScreenWidget->show();
    m_RecordScreenWidget->raise();
    connect(m_RecordScreenWidget, &QWidget::destroyed, this, [=](){ m_RecordScreenWidget = nullptr;});
}

void DrawingBoard::showLockScreen()
{
    MyLock *mylock = new MyLock(this);
    mylock->show();
}

void DrawingBoard::insertPicture()
{
    QFileDialog fileDialog;
    fileDialog.setWindowModality(Qt::WindowModal);
    QString filter;
    Keyboard key;
    key.hide();
    QString fileName = fileDialog.getOpenFileName(this, tr("插入图片"), "", "Images(*.png *.jpg *.bmp *.gif)", &filter);
    if (fileName.length() == 0)
        return;

    BoardScene *scene = ui->graphicsView->getItemScene();
    if(ui->pPen->isChecked())ui->pSelect->setChecked(true);
    if (nullptr == scene)
        return;

    QString suffix = fileName.mid(fileName.length() -4);
    if((suffix.compare(".png") ==0)||(suffix.compare(".jpg") ==0)||(suffix.compare(".bmp") ==0)||(suffix.compare(".gif") ==0)) {
        scene->loadPicture(fileName);
    }
}

void DrawingBoard::onBtnMenuToggled(bool checked)
{
    this->hidePanel(m_MenuPanel);
    if (checked) {
        ui->pMenu->setIcon(QIcon(":/images/main/mainpixmap/caidan2_1@2x.png"));
        ui->vLayout_menu->setContentsMargins(0, 0, 0, 0);
        QPoint pt = mapToGlobal(QPoint(ui->frame_left->x(), ui->frame_left->y()
                                       - m_MenuPanel->height() - Public_Function::getScaleSize(12)));
        m_MenuPanel->move(pt);
        m_MenuPanel->show();
    }else {
        if (!m_MenuPanel->isHidden())
            m_MenuPanel->hide();
        ui->pMenu->setIcon(QIcon(":/images/main/mainpixmap/caidan_1@2x.png"));
        ui->vLayout_menu->setContentsMargins(0, Public_Function::getScaleSize(2),
                                             0, Public_Function::getScaleSize(2));
    }
}

void DrawingBoard::onBtnCloudClicked()
{
    if (nullptr == m_CCWidget)
        return;
    m_CCWidget->move(QPoint((this->width() - m_CCWidget->width())/2, (this->height() - m_CCWidget->height())/2));
    m_CCWidget->show();
    m_CCInterface->setKeyBoardShow();
    m_CCWidget->raise();
}

void DrawingBoard::onBtnSwitchClicked()
{
    this->hidePanel();
    if (ui->frame_left->x() < ui->frame_right->x()) {
        ui->frame_left->move(QPoint(this->width() - ui->frame_left->width() - Public_Function::getScaleSize(16) - ui->frame_left->mGetBorder(),
                                    this->height() - Public_Function::getScaleSize(16) +
                                    ui->frame_left->mGetBorder() - ui->frame_left->height()));
        ui->frame_right->move(QPoint(Public_Function::getScaleSize(16) + ui->frame_right->mGetBorder(),
                                     this->height() - Public_Function::getScaleSize(16) +
                                     ui->frame_right->mGetBorder() - ui->frame_right->height()));
        ui->pSwitchLeft->move(QPoint(ui->frame_right->x() + ui->frame_right->width(), ui->frame_right->y()));
        ui->pSwitchRight->move(QPoint(ui->frame_left->x() - ui->pSwitchRight->width(), ui->frame_left->y()));
    }else {
        ui->frame_left->move(QPoint(Public_Function::getScaleSize(16) + ui->frame_left->mGetBorder(),
                                    this->height() - Public_Function::getScaleSize(16) +
                                    ui->frame_left->mGetBorder() - ui->frame_left->height()));
        ui->frame_right->move(QPoint(this->width() - ui->frame_right->width() -
                                     Public_Function::getScaleSize(16) - ui->frame_right->mGetBorder(),
                                     this->height() - Public_Function::getScaleSize(16) +
                                     ui->frame_right->mGetBorder() - ui->frame_right->height()));
        ui->pSwitchLeft->move(QPoint(ui->frame_left->x() + ui->frame_left->width(), ui->frame_left->y()));
        ui->pSwitchRight->move(QPoint(ui->frame_right->x() - ui->pSwitchRight->width(), ui->frame_right->y()));
    }

}

void DrawingBoard::onBtnSelectToggled(bool checked)
{
    if (checked) {
        ui->graphicsView->changeViewScene(1);
        this->hidePanel();
        ui->vlayout_select->setContentsMargins(0, 0, 0, 0);
        g_ToolType = ToolType::Cursor;     //设置工具类型为光标      
    }else {
        ui->vlayout_select->setContentsMargins(0, Public_Function::getScaleSize(10), 0, 0);
    }
}

void DrawingBoard::onBtnSelectCheckedClicked()
{
    this->hidePanel(m_SelectPanel);
    if (m_SelectPanel->isHidden()) {
        ui->pSelect->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/xuanze3_1@2x.png"));
        m_SelectPanel->move(QPoint(ui->frame_mid->x() + ui->pSelect->x() + (ui->pSelect->width() - m_SelectPanel->width())/2,
                                      ui->frame_mid->y() - m_SelectPanel->height() - Public_Function::getScaleSize(10)));
        m_SelectPanel->show();
    }else {
        m_SelectPanel->hide();
    }
}

void DrawingBoard::onBtnPenToggled(bool checked)
{
    if (checked) {
        ui->vlayout_pen->setContentsMargins(0, 0, 0, 0);
        ui->graphicsView->changeViewScene(2);
        this->hidePanel();
        g_ToolType = ToolType::Pen;     //设置工具类型为画笔
    }else
        ui->vlayout_pen->setContentsMargins(0, Public_Function::getScaleSize(10), 0, 0);
}

void DrawingBoard::onBtnPenCheckedClicked()
{
    this->hidePanel(m_PenPanel);
    if (m_PenPanel->isHidden()) {
        ui->pPen->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/bichu3_1@2x.png"));
        m_PenPanel->move(QPoint(ui->frame_mid->x() + ui->pPen->x() + (ui->pPen->width() - m_PenPanel->width())/2,
                                      ui->frame_mid->y() - m_PenPanel->height() - Public_Function::getScaleSize(10)));
        m_PenPanel->show();
    }else {
        this->hidePanel();
    }
}

void DrawingBoard::onBtnEraseToggled(bool checked)
{
    if (checked) {
        ui->graphicsView->changeViewScene(1);
        this->hidePanel();
        ui->vlayout_eraser->setContentsMargins(0, 0, 0, 0);
        g_ToolType = ToolType::Erase;     //设置工具类型为橡皮擦
    }else
        ui->vlayout_eraser->setContentsMargins(0, Public_Function::getScaleSize(10), 0, 0);
}

void DrawingBoard::onBtnEraseCheckedClicked()
{
    this->hidePanel(m_ErasePanel);
    if (m_ErasePanel->isHidden()) {
        ui->pEarser->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/cachu3_1@2x.png"));
        m_ErasePanel->move(QPoint(ui->frame_mid->x() + ui->pEarser->x() + (ui->pEarser->width() - m_ErasePanel->width())/2,
                                      ui->frame_mid->y() - m_ErasePanel->height() - Public_Function::getScaleSize(10)));
        m_ErasePanel->show();
    }else {
        m_ErasePanel->hide();
    }
}

void DrawingBoard::onBtnUndoClicked()
{
    BoardScene *scene = ui->graphicsView->getItemScene();
    if (nullptr == scene)
        return;
    scene->undo();
    if(g_ToolType == ToolType::Pen)
    {
        ui->graphicsView->clearDrawingSceneItem();
        ui->graphicsView->changeDrawingScenePixmap(scene->getSceneToPixmap());
    }
}

void DrawingBoard::onBtnRedoClicked()
{
    BoardScene *scene = ui->graphicsView->getItemScene();
    if (nullptr == scene)
        return;
    scene->redo();
    if(g_ToolType == ToolType::Pen)
    {
        ui->graphicsView->clearDrawingSceneItem();
        ui->graphicsView->changeDrawingScenePixmap(scene->getSceneToPixmap());
    }
}

void DrawingBoard::onBtnMoreClicked()
{
    this->hidePanel();
    int i = ui->pMore->property("ShowWhichPanel").toInt();
    if (-1 == i)
        i = 0;

    this->onShowToolPanel(i);
}

void DrawingBoard::onBtnAddPageClicked()
{
    if(ui->graphicsView->scene() != nullptr)
    {
        QPixmap pix =ui->graphicsView->getViewTabPixmap();
        BoardScene *mscene = ui->graphicsView->getItemScene();
        mscene->savePixmap(pix);
    }

    int index = m_pPagePanel->getPageIndex() + 1;
    BoardScene *scene =m_pPagePanel->addPage(index, m_BackgroundStyle->getDefaultPixmap(), m_BackgroundStyle->getDefaultId());
    m_pPagePanel->setPageChecked(index);
    ui->graphicsView->resetDrawingScene(scene);
}

void DrawingBoard::onBtnLastPageClicked()
{
    if(ui->graphicsView->scene() != nullptr)
    {
        QPixmap pix =ui->graphicsView->getViewTabPixmap();
        BoardScene *mscene = ui->graphicsView->getItemScene();
        mscene->savePixmap(pix);
    }

    m_pPagePanel->lastPage();
}

void DrawingBoard::onBtnNextPageClicked()
{
    if(ui->graphicsView->scene() != nullptr)
    {
        QPixmap pix =ui->graphicsView->getViewTabPixmap();
        BoardScene *mscene = ui->graphicsView->getItemScene();
        mscene->savePixmap(pix);
    }

    m_pPagePanel->nextPage();
}

void DrawingBoard::onBtnShowPageToggled(bool checked)
{
    this->hidePanel(m_pPagePanel);
    if (checked) {
        if (ui->frame_left->x() < ui->frame_right->x()) {
            m_pPagePanel->move(QPoint(this->width() - m_pPagePanel->width() - Public_Function::getScaleSize(15),
                                        ui->frame_right->y() - m_pPagePanel->height() - Public_Function::getScaleSize(10)));
        }else {
            m_pPagePanel->move(QPoint(Public_Function::getScaleSize(15),
                                        ui->frame_right->y() - m_pPagePanel->height() - Public_Function::getScaleSize(10)));
        }
        if(ToolType::Pen ==g_ToolType)m_pPagePanel->updateSceneList(ui->graphicsView->getItemDrawingScene());
        else m_pPagePanel->updateSceneList(ui->graphicsView->getItemScene());
        m_pPagePanel->show();
    }else {
        if (!m_pPagePanel->isHidden())
            m_pPagePanel->hide();
    }

}

void DrawingBoard::onNewBoard()
{
    m_MenuPanel->hide();//m_MenuPanel->isSaveEnabled()
    int number =0;
    for(int i =0; i<m_pPagePanel->getBoardSceneList().count();i++)
    {
        BoardScene *scene = static_cast<BoardScene*>(m_pPagePanel->getBoardSceneList().at(i));
        number +=scene->items(scene->sceneRect(),Qt::IntersectsItemBoundingRect).count();
    }
    /**********change123***********/
    if (number !=0) {
        this->showMsgBox(tr("提示"), tr("是否保存当前白板？"), tr("取消"), tr("不保存"), tr("保存"), SLOT(onMBoxRet_NewBoard(int)));
    }else {
        emit this->boardClosed(1);
    }
}

void DrawingBoard::onOpenFile()
{
    m_MenuPanel->hide();
    if (m_MenuPanel->isSaveEnabled()) {
        this->showMsgBox(tr("提示"), tr("是否保存当前白板？"), tr("取消"), tr("不保存"), tr("保存"), SLOT(onMBoxRet_OpenFile(int)));
    }else {
        this->importFile();
    }
}

void DrawingBoard::onExportToFile(int i)
{
    m_MenuPanel->hide();
    if (1 == i) {   // 导出当前页为图片
        this->exportToPicture();
    }else if (2 == i) { // 导出所有页为图片
        this->exportAllToPicture();
    }else if (3 == i) { // 导出文件为其他格式（PDF）
        this->exportToOthreFormats();
    }
}

void DrawingBoard::onShowAboutUs()
{
    m_MenuPanel->hide();
    AboutUs *about = new AboutUs(this);
    about->setGeometry(this->rect());
    about->show();
}

void DrawingBoard::onExitApplication()
{
    m_MenuPanel->hide();//m_MenuPanel->isSaveEnabled()
    int number =0;
    for(int i =0; i<m_pPagePanel->getBoardSceneList().count();i++)
    {
        BoardScene *scene = static_cast<BoardScene*>(m_pPagePanel->getBoardSceneList().at(i));
        number +=scene->items(scene->sceneRect(),Qt::IntersectsItemBoundingRect).count();
    }
    /**********change123***********/
    if (number !=0) {
        this->showMsgBox(tr("提示"), tr("是否保存当前白板？"), tr("取消"), tr("不保存"), tr("保存"), SLOT(onMBoxRet_ExitApplication(int)));
    }else {
        emit this->boardClosed(0);
    }
}

void DrawingBoard::onToggleLanguage(bool isChinese)
{
    ToolKit::ToggleLanguage(isChinese);
    updateLanguaue(isChinese);
}

void DrawingBoard::onSelectAll()
{
    BoardScene *scene = static_cast<BoardScene*>(ui->graphicsView->scene());
    scene->setSelectionAreaRect(scene->sceneRect());
}

void DrawingBoard::onClearScene()
{
    ui->pEarser->mSetCheckedIcon(QPixmap(":/images/main/mainpixmap/cachu2_1@2x.png"));
    BoardScene *scene = static_cast<BoardScene*>(ui->graphicsView->scene());
    if (nullptr == scene)
        return;
    scene->deleteAllItems();
    ui->pPen->setChecked(true);
}

void DrawingBoard::onShowToolPanel(int i)
{
    if (0 == i) {   //显示更多面板
        if (m_ToolPanel->isHidden()) {
            m_ToolPanel->move(QPoint(ui->frame_mid->x() + ui->pMore->x() +
                                             (ui->pMore->width() - m_ToolPanel->width())/2,
                                          ui->frame_mid->y() - m_ToolPanel->height() - Public_Function::getScaleSize(10)));
            m_ToolPanel->show();
        }else {
            m_ToolPanel->hide();
        }
    }else if (1 == i) {       //显示图形面板
        if (m_GraphicsPanel->isHidden()) {
            if (!m_ToolPanel->isHidden())
                m_ToolPanel->hide();

            m_GraphicsPanel->move(QPoint(ui->frame_mid->x() + ui->pMore->x() +
                                             (ui->pMore->width() - m_GraphicsPanel->width())/2,
                                          ui->frame_mid->y() - m_GraphicsPanel->height() - Public_Function::getScaleSize(10)));
            m_GraphicsPanel->show();
        }else {
            m_GraphicsPanel->hide();
        }
    }else if (2 == i) {     //显示背景面板
        if (m_BackgroundStyle->isHidden()) {
            if (!m_ToolPanel->isHidden())
                m_ToolPanel->hide();

            m_BackgroundStyle->move(QPoint(ui->frame_mid->x() + ui->pMore->x() +
                                           (ui->pMore->width() - m_BackgroundStyle->width())/2,
                                        ui->frame_mid->y() - m_BackgroundStyle->height() - Public_Function::getScaleSize(10)));
            m_BackgroundStyle->show();
        }else {
            m_BackgroundStyle->hide();
        }

    }else if (3 == i) {     //显示尺规面板
        if (m_RulerPanel->isHidden()) {
            if (!m_ToolPanel->isHidden())
                m_ToolPanel->hide();

            m_RulerPanel->move(QPoint(ui->frame_mid->x() + ui->pMore->x() +
                                             (ui->pMore->width() - m_RulerPanel->width())/2,
                                          ui->frame_mid->y() - m_RulerPanel->height() - Public_Function::getScaleSize(10)));
            m_RulerPanel->show();
        }else {
            m_RulerPanel->hide();
        }
    }
    ui->pMore->setProperty("ShowWhichPanel", i);    //记录显示哪一个面板
}

void DrawingBoard::onToolFunction(int i)
{
    this->m_ToolPanel->hide();
    switch(i)
    {
    case 1: {   //截屏
        this->screenShots();
    }break;
    case 2: {   //打开展台
        this->openExhibitionBooth();
    }break;
    case 3: {   // 打开播放器
        this->openVideoPlayer();
    }break;
    case 4: {

    }break;
    case 5: {   //显示板中板
        this->showPlateplate();
    }break;
    case 6: {
        this->showCoverRect();
    }break;
    case 7: {
        this->showSpotlight();
    }break;
    case 8: {
        this->openCalculator();
    }break;
    case 9: {
        this->openTimer();
    }break;
    case 10: {
        this->startRecordScreen();
    }break;
    case 11: {
        this->showLockScreen();
    }break;
    case 12: {
        this->insertPicture();
    }break;
    default:
        break;
    }
}

void DrawingBoard::onPageIndexChanged(QGraphicsScene *scene)
{
    /*获得切换后的场景，将切换后的场景放入视图中*/
    BoardScene *mscene = static_cast<BoardScene*>(scene);
    ui->graphicsView->resetCurrentScene(mscene);

    QPixmap pix =ui->graphicsView->getViewToPixmap();
    mscene->savePixmap(pix);
    m_pPagePanel->changeTabPixmap(m_pPagePanel->getPageIndex());

    /* 设置当前页数也样式 */
    int size = m_pPagePanel->getPageSize();
    int index = m_pPagePanel->getPageIndex();
    QString str = QString("%1/%2").arg(QString::number(++index)).arg(size);
    ui->label_page->setText(str);
    if (size == index) {
        ui->pNextPage->setStyleSheet("QPushButton{border-image: url(':/images/main/mainpixmap/xiayiye_1@2x.png');}");
    }else {
        ui->pNextPage->setStyleSheet("QPushButton{border-image: url(':/images/main/mainpixmap/xiayiye2_1@2x.png');}");
    }
    if (1 == index) {
        ui->pLastPage->setStyleSheet("QPushButton{border-image: url(':/images/main/mainpixmap/shangyiye_1@2x.png');}");
    }else {
        ui->pLastPage->setStyleSheet("QPushButton{border-image: url(':/images/main/mainpixmap/shangyiye2_1@2x.png');}");
    }

    int bgNum = scene->property("bgNum").toInt();
    m_BackgroundStyle->setCheckedIndex(bgNum);
}

void DrawingBoard::onSetMiniBoard()
{
    if(!m_setBoard->switchBtnState())m_setBoard->setBoardNumber(3);
    else
    {
        getMiniBoardNumber();
    }
    m_setBoard->show();
}

void DrawingBoard::onOpenMiniBoard()
{
    isdrawline =true;
    if(m_setBoard->switchBtnState())getMiniBoardNumber();
    m_setBoard->show();
}

void DrawingBoard::onAddMiniBoard()
{
    hid_device_info *info=hid_enumerate(0,0);
    hidapilist.clear();
    while (info)
    {
        if((info->product_id ==12424)&&(info->vendor_id ==1351))
        {
            hidapilist.append(info->path);
        }
        info = info->next;
    }

    if(boardworker ==nullptr)
    {
        boardworker = new GetPointWorker();
        boardthread = new QThread();
        boardworker->moveToThread(boardthread);
        connect(this, &DrawingBoard::sendHidapiPath1, boardworker, &GetPointWorker::startWorker,Qt::UniqueConnection);
        connect(boardworker, &GetPointWorker::sendPointDate, this, &DrawingBoard::getNewPoint);
        connect(boardworker, &GetPointWorker::sendShortcutKey, this, &DrawingBoard::getMiniBoardShortcutKey);
        connect(boardworker, &GetPointWorker::sendEraserDate, this, &DrawingBoard::getNewEraser,Qt::BlockingQueuedConnection);
        connect(boardthread,&QThread::finished,this,[=](){
            boardworker->deleteLater();
            boardthread->deleteLater();
            boardworker =nullptr;
            boardthread =nullptr;
        });
        boardthread->start();
        if(boardworker2 ==nullptr)
        {
            emit sendHidapiPath1(hidapilist.at(0));
        }
        else if(strcmp(boardworker2->getPath(),hidapilist.at(0)) ==0)
        {
            emit sendHidapiPath1(hidapilist.at(1));
        }
        else
        {
            emit sendHidapiPath1(hidapilist.at(0));
        }
    }
    else if(boardworker2 ==nullptr)
    {
        boardworker2 = new GetPointWorker();
        boardthread2 = new QThread();
        boardworker2->moveToThread(boardthread2);
        connect(this, &DrawingBoard::sendHidapiPath2, boardworker2, &GetPointWorker::startWorker,Qt::UniqueConnection);
        connect(boardworker2, &GetPointWorker::sendPointDate, this, &DrawingBoard::getNewPoint);
        connect(boardworker2, &GetPointWorker::sendShortcutKey, this, &DrawingBoard::getMiniBoardShortcutKey);
        connect(boardworker2, &GetPointWorker::sendEraserDate, this, &DrawingBoard::getNewEraser,Qt::BlockingQueuedConnection);
        connect(boardthread2,&QThread::finished,this,[=](){
            boardworker2->deleteLater();
            boardthread2->deleteLater();
            boardworker2 =nullptr;
            boardthread2 =nullptr;
        });
        boardthread2->start();
        if(boardworker ==nullptr)
        {
            emit sendHidapiPath2(hidapilist.at(0));
        }
        else if(strcmp(boardworker->getPath(),hidapilist.at(0)) ==0)
        {
            emit sendHidapiPath2(hidapilist.at(1));
        }
        else
        {
            emit sendHidapiPath2(hidapilist.at(0));
        }
    }
}

void DrawingBoard::onAgainOpenMiniBoard()
{
    boardnumber =0;
    hid_device_info *info=hid_enumerate(0,0);
    hidapilist.clear();
    while (info)
    {
        if((info->product_id ==12424)&&(info->vendor_id ==1351))
        {
            hidapilist.append(info->path);
            boardnumber++;
        }
        else if((info->product_id ==648)&&(info->vendor_id ==10473))
        {
            penpathlist.append(info->path);
        }
        info = info->next;
    }

    if(boardnumber !=0)
    {
        if(0 == ApplicationConfig::readConfig("miniboard").compare("0"))
        {
            ApplicationConfig::writeConfig("miniboard", "1");
            QString st3 ="pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY /opt/apps/com.amdox.board/files/bin/usbdev.sh";
            QProcess *process =new QProcess();
            process->execute("sh", QStringList() << "-c" << st3);
            process->waitForFinished(1000);
            this->showMsgBox(tr("提示"), tr("第一次使用请重启电脑完成副板配置"), tr("确定"));
        }
    }

    if(hidapilist.count() >=2)
    {
        if(boardworker ==nullptr)
        {
            boardworker = new GetPointWorker();
            boardthread = new QThread();
            boardworker->moveToThread(boardthread);
            connect(this, &DrawingBoard::sendHidapiPath1, boardworker, &GetPointWorker::startWorker,Qt::UniqueConnection);
            connect(boardworker, &GetPointWorker::sendPointDate, this, &DrawingBoard::getNewPoint);
            connect(boardworker, &GetPointWorker::sendShortcutKey, this, &DrawingBoard::getMiniBoardShortcutKey);
            connect(boardworker, &GetPointWorker::sendEraserDate, this, &DrawingBoard::getNewEraser,Qt::BlockingQueuedConnection);
            connect(boardthread,&QThread::finished,this,[=](){
                boardworker->deleteLater();
                boardthread->deleteLater();
                boardworker =nullptr;
                boardthread =nullptr;
            });
            boardthread->start();
            emit sendHidapiPath1(hidapilist.at(1));
        }  
    }

    if(hidapilist.count() >=1)
    {
        if(boardworker2 ==nullptr)
        {
            boardworker2 = new GetPointWorker();
            boardthread2 = new QThread();
            boardworker2->moveToThread(boardthread2);
            connect(this, &DrawingBoard::sendHidapiPath2, boardworker2, &GetPointWorker::startWorker,Qt::UniqueConnection);
            connect(boardworker2, &GetPointWorker::sendPointDate, this, &DrawingBoard::getNewPoint);
            connect(boardworker2, &GetPointWorker::sendShortcutKey, this, &DrawingBoard::getMiniBoardShortcutKey);
            connect(boardworker2, &GetPointWorker::sendEraserDate, this, &DrawingBoard::getNewEraser,Qt::BlockingQueuedConnection);
            connect(boardthread2,&QThread::finished,this,[=](){
                boardworker2->deleteLater();
                boardthread2->deleteLater();
                boardworker2 =nullptr;
                boardthread2 =nullptr;
            });
        }
            boardthread2->start();
            emit sendHidapiPath2(hidapilist.at(0));
    }


    if(leftpenworker ==nullptr)
    {
        leftpenpath =getPenPath(76);
        if(leftpenpath != nullptr)
        {
            leftpenworker = new GetPenWorker();
            penthread = new QThread();
            leftpenworker->moveToThread(penthread);
            connect(this, &DrawingBoard::sendHidapiPenPath1, leftpenworker, &GetPenWorker::startWorker,Qt::UniqueConnection);
            connect(leftpenworker,&GetPenWorker::sendGetPenMessage,this,&DrawingBoard::getNewPenColor);
            connect(penthread,&QThread::finished,this,[=](){
                leftpenworker->deleteLater();
                penthread->deleteLater();
                leftpenworker =nullptr;
                penthread =nullptr;
            });
            penthread->start();
            emit sendHidapiPenPath1(leftpenpath);
        }
    }


    if(rightpenworker ==nullptr)
    {
        rightpenpath =getPenPath(82);
        if(rightpenpath != nullptr)
        {
            rightpenworker = new GetPenWorker();
            penthread2 = new QThread();
            rightpenworker->moveToThread(penthread2);
            connect(this, &DrawingBoard::sendHidapiPenPath2, rightpenworker, &GetPenWorker::startWorker,Qt::UniqueConnection);
            connect(rightpenworker,&GetPenWorker::sendGetPenMessage,this,&DrawingBoard::getNewPenColor);
            connect(penthread2,&QThread::finished,this,[=](){
                rightpenworker->deleteLater();
                penthread2->deleteLater();
                rightpenworker =nullptr;
                penthread2 =nullptr;
            });
            penthread2->start();
            emit sendHidapiPenPath2(rightpenpath);
        }
    }

    m_setBoard->setBoardNumber(boardnumber);
}

void DrawingBoard::onCloseMiniBoard()
{
    isdrawline =false;
}

void DrawingBoard::onMiniBoardNumberChange(int n)
{
    if(boardworker != nullptr)
    {
        if(!boardworker->isOpenSuccess())
        {
            boardthread->exit();
            boardthread->quit();
            boardthread->wait();
        }
    }

    if(boardworker2 != nullptr)
    {
        if(!boardworker2->isOpenSuccess())
        {
            boardthread2->exit();
            boardthread2->quit();
            boardthread2->wait();
        }
    }

    if(boardnumber <n)
    {
       onAddMiniBoard();
    }
    boardnumber =n;
    if(isdrawline)
    {
        m_setBoard->setBoardNumber(boardnumber);
    }
    checknumber->setNumber(n);
}

void DrawingBoard::getNewPoint(_TPPoint point)
{
    if(!isdrawline)return;
    if(boardnumber ==1)//单板（不分左右副板）
    {
        point.X =this->width()/4 +this->width()/2*point.X;
        point.Y =this->height()*point.Y;
        point.id =point.id +36;
        if(!ui->pPen->isChecked())ui->pPen->setChecked(true);
        if(leftpenpath != nullptr)ui->graphicsView->miniLeftDrawTouchEvent(point,miniboardleftcolor);
        if(rightpenpath != nullptr)ui->graphicsView->miniLeftDrawTouchEvent(point,miniboardrightcolor);
    }
    else if(boardnumber ==2)
    {
        QString value = ApplicationConfig::readConfig("exchange");
        if(point.ID ==76)//左副板
        {
            if(iseraserleft ==true ||iseraserright ==true)return;
            point.id =point.id +36;
            if(value.contains("true"))
            {
                point.X =this->width()/2 +this->width()/2*point.X;
            }
            else if(value.contains("false"))
            {
                point.X =0 +this->width()/2*point.X;
            }
            point.Y =this->height()*point.Y;
            if(!ui->pPen->isChecked())ui->pPen->setChecked(true);
            ui->graphicsView->miniLeftDrawTouchEvent(point,miniboardleftcolor);
        }
        else if(point.ID ==82)//右副板
        {
            if(iseraserleft ==true ||iseraserright ==true)return;
            point.id =point.id +82;
            if(value.contains("true"))
            {
                point.X =this->width()/2*point.X;
            }
            else if(value.contains("false"))
            {
                point.X =this->width()/2 +this->width()/2*point.X;
            }
            point.Y =this->height()*point.Y;
            if(!ui->pPen->isChecked())ui->pPen->setChecked(true);
            ui->graphicsView->miniRightDrawTouchEvent(point,miniboardrightcolor);
        }
    }
}

void DrawingBoard::getNewEraser(_TPPoint point)
{
    if(!isdrawline)return;
    if(boardnumber ==1)//单板（不分左右副板）
    {
        point.X =this->width()/4 +this->width()/2*point.X;
        point.Y =this->height()*point.Y;
        ui->pEarser->setChecked(true);
        ui->graphicsView->miniEraseMouseEvent(point);
    }
    else if(boardnumber ==2)
    {
        QString value = ApplicationConfig::readConfig("exchange");
        if(point.ID ==76)//左副板
        {
            point.id =point.id +36;
            if(iseraserright)return;
            if(point.state ==1)iseraserleft =true;
            if(value.contains("true"))
            {
                point.X =this->width()/2 +this->width()/2*point.X;
            }
            else if(value.contains("false"))
            {
                point.X =0 +this->width()/2*point.X;
            }
            point.Y =this->height()*point.Y;
            ui->pEarser->setChecked(true);
            ui->graphicsView->miniEraseMouseEvent(point);
            if(point.state ==3)iseraserleft =false;
        }
        else if(point.ID ==82)//右副板
        {
            point.id =point.id +82;
            if(iseraserleft)return;
            if(point.state ==1)iseraserright =true;
            if(value.contains("true"))
            {
                point.X =this->width()/2*point.X;
            }
            else if(value.contains("false"))
            {
                point.X =this->width()/2 +this->width()/2*point.X;
            }
            point.Y =this->height()*point.Y;
            ui->pEarser->setChecked(true);
            ui->graphicsView->miniEraseMouseEvent(point);
            if(point.state ==3)iseraserright =false;
        }
    }
}

void DrawingBoard::getMiniBoardShortcutKey(int number)
{
    switch (number)
    {
    case 1:
        emit this->showMinimizedSignal();
        break;
    case 2:
         m_pPagePanel->lastPage();
        break;
    case 3:
    {
        if(m_pPagePanel->getPageIndex() +1 ==m_pPagePanel->getPageSize())
        {
          this->onBtnAddPageClicked();
        }
        else
         m_pPagePanel->nextPage();
    }
        break;
    case 4:
         this->onBtnAddPageClicked();
        break;
    case 5:
    {
        QString str ="dbus-send --session --print-reply --dest=org.onboard.Onboard /org/onboard/Onboard/Keyboard org.onboard.Onboard.Keyboard.Show";
        QProcess *process =new QProcess();
        process->execute(str);
        process->waitForFinished(1000);
    }
        break;
    case 6:
        emit this->showMaximizedSignal();
        break;
    default:
        break;
    }
}

void DrawingBoard::getNewPenColor(int id, QString color)
{  
    if(id ==76)
    {
       if(!color.isEmpty())
       {
           if(color =="black"){miniboardleftcolor =Qt::black;}
           else if(color =="red"){miniboardleftcolor =QColor(247,56,89);}
           else if(color =="blue"){miniboardleftcolor =QColor(68,126,252);}
           else if(color =="none"){
               if(rightpenpath != nullptr)
               {
                   if(rightpenworker->getPenNumber() >0)
                   {
                       miniboardleftcolor =miniboardrightcolor;
                   }
                   else
                   {
                           leftpenworker->getCurrentColor();
                           rightpenworker->getCurrentColor();
                   }
               }
               else
                  leftpenworker->getCurrentColor();
           };

           if(rightpenpath != nullptr)
           {
               if((leftpenworker->getPenNumber() >0) &&(rightpenworker->getPenNumber() ==0))
               {
                   miniboardrightcolor =miniboardleftcolor;
               }
           }

           changePenColorHint("left",color);
       }
       else
       {
           miniboardleftcolor =Qt::black;
       }
    }
    else if(id ==82)
    {
        if(!color.isEmpty())
        {
            if(color =="black"){miniboardrightcolor =Qt::black;}
            else if(color =="red"){miniboardrightcolor =QColor(247,56,89);}
            else if(color =="blue"){miniboardrightcolor =QColor(68,126,252);}
            else if(color =="none"){
                    //这边放下笔，对边还有笔没有放下时
                if(leftpenworker != nullptr)
                {
                    if(leftpenworker->getPenNumber() >0)
                    {
                        miniboardrightcolor =miniboardleftcolor;
                    }
                    else
                    {
                        //放下笔后，两边都没有拿笔
                            leftpenworker->getCurrentColor();
                            rightpenworker->getCurrentColor();
                    }
                }else
                rightpenworker->getCurrentColor();
            };

            //在当前笔颜色改变且对边没有拿笔的情况下改变对边书写颜色
             if(leftpenpath != nullptr)
             {
                if((rightpenworker->getPenNumber() >0) &&(leftpenworker->getPenNumber() ==0))
                {
                    miniboardleftcolor =miniboardrightcolor;
                };
             }
            changePenColorHint("right",color);
        }
        else
        {
            miniboardrightcolor =Qt::black;
        }
    }
}

void DrawingBoard::onScreenShotClose()
{
    m_ScreenShotInterface->hide();
    m_ScreenShotInterface->deleteLater();
    m_ScreenShotInterface = nullptr;
    this->onShowToolPanel(0);

}

void DrawingBoard::onScreenShotMessage(int a)
{
    if(a ==1)
    {
        emit this->showMinimizedSignal();
    }
    else if(a ==2)
    {
        emit this->showMaximizedSignal();
    }
}

void DrawingBoard::onScreenShotPixmap(QPixmap pix)
{
    if(!pix.isNull())
    {
       ui->pSelect->setChecked(true);
       BoardScene *scene = ui->graphicsView->getItemScene();
       scene->addPixmapItem(pix,pix.rect());
       emit this->showMaximizedSignal();
    }
}

void DrawingBoard::onVideoPlayerScreenShotPixmap(QPixmap pix)
{
    if(!pix.isNull())
    {
       ui->pSelect->setChecked(true);
       BoardScene *scene = ui->graphicsView->getItemScene();
       scene->addPixmapItem(pix,pix.rect());
    }
}

void DrawingBoard::onVideoPlayerClose()
{
    m_VideoPlayerWidget->deleteLater();
    m_VideoPlayerWidget = nullptr;
}


void DrawingBoard::onMBoxRet_NewBoard(int i)
{
    if (1 == i) {   //先保存再新建
        ExportFileWidget *widget = this->exportToOthreFormats();
        if (nullptr != widget)
        {
            connect(widget, &ExportFileWidget::threadFinished, this, [=](){
                widget->hide();
                widget->deleteLater();
                emit this->boardClosed(1);
            });
        }
    }else if (0 == i){
        emit this->boardClosed(1);
    }
    MessageBox_1 *box = static_cast<MessageBox_1 *>(sender());
    box->deleteLater();
}

void DrawingBoard::onMBoxRet_ExitApplication(int i)
{
    if (1 == i) {   //先保存再退出
        ExportFileWidget *widget = this->exportToOthreFormats();
        if (nullptr != widget)
        {
            connect(widget,&ExportFileWidget::threadFinished, this, [=](){
                widget->hide();
                widget->deleteLater();
                emit this->boardClosed(0);
            });
        }
    }else if(0 == i){
        emit this->boardClosed(0);
    }
    MessageBox_1 *box = static_cast<MessageBox_1 *>(sender());
    box->deleteLater();
}

void DrawingBoard::onMBoxRet_OpenFile(int i)
{
    if (1 == i) {   //先保存再导入
        ExportFileWidget *widget = this->exportToOthreFormats();
        if (nullptr != widget)
        {
            connect(widget, &ExportFileWidget::threadFinished, this, [=](){
                widget->hide();
                widget->deleteLater();
                this->importFile();
            });
        }
    }else{
        this->importFile();
    }
    MessageBox_1 *box = static_cast<MessageBox_1 *>(sender());
    box->deleteLater();
}



void DrawingBoard::hidePanel(QWidget *widget)
{
    if (!m_MenuPanel->isHidden() && m_MenuPanel != widget)
        m_MenuPanel->hide();
    if (!m_SelectPanel->isHidden() && m_SelectPanel != widget)
        m_SelectPanel->hide();
    if (!m_PenPanel->isHidden() && m_PenPanel != widget && !m_PenPanel->isLocked())
        m_PenPanel->hide();
    if (!m_ErasePanel->isHidden() && m_ErasePanel != widget)
        m_ErasePanel->hide();
    if (!m_ToolPanel->isHidden() && m_ToolPanel != widget)
        m_ToolPanel->hide();
    if (!m_BackgroundStyle->isHidden() && m_BackgroundStyle != widget)
        m_BackgroundStyle->hide();
    if (!m_RulerPanel->isHidden() && m_RulerPanel != widget)
        m_RulerPanel->hide();
    if (!m_pPagePanel->isHidden() && m_pPagePanel != widget)
        m_pPagePanel->hide();
    if (!m_GraphicsPanel->isHidden() && m_GraphicsPanel != widget)
        m_GraphicsPanel->hide();
}

void DrawingBoard::importFile()
{
    QFileDialog fileDialog;
    fileDialog.setWindowModality(Qt::WindowModal);  //模态化

    Keyboard key;
    key.hide();

    QString filter;
    QString fileName = fileDialog.getOpenFileName(this, tr("导入文件"), "", "PDF(*.pdf)", &filter);
    if (fileName.length() == 0)
        return;
    if (filter.compare("PDF(*.pdf)") == 0){
        //获取PDF每一页，图片格式
        QVector<QPixmap> pixmapList = MPdf::Openpdf(fileName);
        if (0 == pixmapList.size()) {
            this->showMsgBox(tr("提示"), tr("文件为空"), tr("确定"));
            return;
        }else {
//            m_pPagePanel->clearPage();
            int num =m_pPagePanel->getPageIndex() + 1;
            int w =pixmapList.at(0).size().width();
            int h =pixmapList.at(0).size().height();
            int sw =ui->graphicsView->getItemDrawingScene()->width();
            int sh =ui->graphicsView->getItemDrawingScene()->height();
            qreal magnification = (qreal)sw/w >(qreal)sh/h?(qreal)sh/h:(qreal)sw/w;
            if(magnification -0.1 >1)magnification-=0.1;
            else if(magnification <1)magnification =1;
            for(int i = 0; i < pixmapList.size(); i++) {
                int index = m_pPagePanel->getPageIndex() + 1;
                BoardScene *scene =m_pPagePanel->addPage(index, m_BackgroundStyle->getDefaultPixmap(), m_BackgroundStyle->getDefaultId());
                m_pPagePanel->setPageChecked(index);
                QRect rect = this->scalePixmapWithRect(pixmapList.at(i).size(), scene->sceneRect().toRect());
                rect.setWidth(rect.width()*magnification);
                rect.setHeight(rect.height()*magnification);
                scene->addPixmapItem(pixmapList.at(i),rect);
                ui->graphicsView->resetDrawingScene(scene);
            }
            m_pPagePanel->setPageChecked(num);
        }
    }
}

QRect DrawingBoard::scalePixmapWithRect(const QSize &pixmapSize, const QRect &rect)
{
    QRect pixmapRect = rect;
    int m_width =pixmapSize.width();
    int m_height =pixmapSize.height();
    if (m_width <= rect.width() && m_height <= rect.height()) {
        pixmapRect = QRect(0, 0, m_width, m_height);
    }else {
        qreal x = m_width/rect.width();
        qreal y = m_height/rect.height();
        int width, height;
        if (x > y) {
            width = rect.width();
            height = m_height/x;
        }else {
            width = rect.width()/y;
            height = m_height;
        }
        pixmapRect = QRect(0, 0, width, height);
    }
    pixmapRect.moveCenter(rect.center());
    return pixmapRect;
}

void DrawingBoard::uncheckTools()
{
    m_pToolButtonGroup->setExclusive(false);
    foreach(QAbstractButton *button, m_pToolButtonGroup->buttons()) {
        DB_CustomPushButton_2 *pBtn = static_cast<DB_CustomPushButton_2*>(button);
        if (pBtn->isChecked())
            pBtn->setChecked(false);
    }
    m_pToolButtonGroup->setExclusive(true);
}

void DrawingBoard::onBackgroundChanged()
{
    BoardScene *scene = ui->graphicsView->getItemScene();
    if (nullptr == scene)
        return;
    scene->setBackgroundBrush(QBrush(m_BackgroundStyle->getBackgroundPixmap().scaled(scene->width(), scene->height())));
    scene->setProperty("bgNum", m_BackgroundStyle->getBackgroundId());
    ui->graphicsView->changeDrawingScenePixmap(QBrush(scene->getSceneToPixmap()
                                                      .scaled(ui->graphicsView->width(), ui->graphicsView->height())));
}

void DrawingBoard::onAllBackgroundChanged()
{
    Widget_2 *w =new Widget_2(tr("操作成功"),this);
    w->show();
    QDesktopWidget *desktop =QApplication::desktop();
    w->move((desktop->width() -w->width())/2,(Public_Function::getScaleSize(50) +w->height()));
    ChangeBackgroundPixmapThread *thread =new ChangeBackgroundPixmapThread(m_pPagePanel->getBoardSceneList(),m_BackgroundStyle->getBackgroundPixmap(),m_BackgroundStyle->getBackgroundId());
    connect(thread,&ChangeBackgroundPixmapThread::finished,this,[=](){thread->deleteLater();});
    thread->start();
    onPageIndexChanged(ui->graphicsView->getItemScene());



}


void DrawingBoard::restartApplication(int i)
{
    MessageBox_1 *mbox = static_cast<MessageBox_1*>(sender());
    mbox->deleteLater();
    if (0 == i) {
        emit this->boardClosed(2);
    }
}

void DrawingBoard::onPlateplateClosed()
{
    m_PlateplateDisplayTimer->setProperty("FUNCTION", "hide");
    m_PlateplateDisplayTimer->start(20);
}

void DrawingBoard::onPlateplateDisplayTimerTimeOut()
{
    m_PlateplateDisplayTimer->stop();
    QString str = m_PlateplateDisplayTimer->property("FUNCTION").toString();
    if (nullptr != m_PlateplateWidget) {
        if (str.compare("show") == 0 && m_PlateplateWidget->y() < 0) {
            int y = m_PlateplateWidget->y() + Public_Function::getScaleSize(80);
            y = y > 0 ? 0 : y;
            m_PlateplateWidget->move(0, y);
            if (y < 0)
                m_PlateplateDisplayTimer->start(20);
        }else if (str.compare("hide") == 0 && m_PlateplateWidget->y() > -this->height()) {
            int y = m_PlateplateWidget->y() - Public_Function::getScaleSize(80);
            y = y < -this->height() ? -this->height() : y;
            m_PlateplateWidget->move(0, y);
            if (y > (-this->height()))
                m_PlateplateDisplayTimer->start(20);
            else
                m_PlateplateWidget->hide();
        }
    }
}

void DrawingBoard::onExhibitionBoothClosed()
{
    //m_ExhibitionBoothWidget->deleteLater();
    //m_ExhibitionBoothWidget = nullptr;
    m_ExhibitionBoothWidget->hide();
}

void DrawingBoard::onTimerWidgetClosed()
{
    m_TimerPlugin->deleteLater();
    m_TimerPlugin = nullptr;
}

void DrawingBoard::onCalculatorClosed()
{
    m_CalculatorInterface->hide();
    m_CalculatorInterface->deleteLater();
    m_CalculatorInterface = nullptr;
}

void DrawingBoard::updateLanguaue(bool isChinese)
{
    ui->pSelect->mSetText(tr("选择"));
    ui->pPen->mSetText(tr("笔"));
    ui->pEarser->mSetText(tr("擦除"));
    ui->pUndo->mSetText(tr("撤销"));
    ui->pRedo->mSetText(tr("恢复"));
    ui->pMore->mSetText(tr("更多"));

    //Tool Panel
    if( m_ToolPanel != nullptr)
        m_ToolPanel->updateLanguage();

    if( m_PenPanel != nullptr)
        m_PenPanel->updateLanguage();

    if( m_BackgroundStyle != nullptr)
        m_BackgroundStyle->updateLanguage();

    if( m_RulerPanel != nullptr)
        m_RulerPanel->updateLanguage();
    if( m_GraphicsPanel != nullptr)
        m_GraphicsPanel->updateLanguage();

    if( m_ErasePanel != nullptr)
        m_ErasePanel->updateLanguage();

    if( m_CalculatorInterface != nullptr)
        m_CalculatorInterface->updateLanguage(isChinese);

    ui->graphicsView->updateLanguage();

}
