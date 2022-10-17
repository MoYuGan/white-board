#include "db_exhibitionbooth.h"
#include "ui_db_exhibitionbooth.h"
#include "ShareStyle/db_scale.h"

#include <QDesktopWidget>
#include <QGuiApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QCamera>
#include <QCameraInfo>
#include <QtDebug>
#include <QFrame>
#include <QFileDialog>
#include <QMouseEvent>
#include <QClipboard>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QWidgetAction>
#include "aboutus.h"
#include "ocrwidget.h"
#include "custommbox.h"
#include "takingphotowidget.h"
#include "db_screenshots.h"
#include <QScreen>
#include "mymutex.h"
#include <QListWidgetItem>
#include <QScroller>

#if 1
DB_ExhibitionBooth::DB_ExhibitionBooth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DB_ExhibitionBooth)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    this->setWindowFlags(Qt::FramelessWindowHint );//| Qt::WindowStaysOnTopHint
    this->initWidget();

    //init size
    QDesktopWidget *desktopWidget = QApplication::desktop();
    connect(desktopWidget, &QDesktopWidget::resized, [=](int screen){
        if (desktopWidget->primaryScreen() == screen) {
            QRect rect = desktopWidget->screenGeometry(screen);
            this->setGeometry(rect);
        }
    });
    this->setGeometry(desktopWidget->screenGeometry(desktopWidget->primaryScreen()));

    m_pListeningDevicesWorker = new ListeningDevicesWorker;
    connect(m_pListeningDevicesWorker, &ListeningDevicesWorker::deviceNumChanged, this, &DB_ExhibitionBooth::onDeviceNumChanged);
    m_pListeningDevicesThread = new QThread;
    m_pListeningDevicesWorker->moveToThread(m_pListeningDevicesThread);
    connect(m_pListeningDevicesThread, &QThread::started, m_pListeningDevicesWorker, &ListeningDevicesWorker::startWorker);

    m_pGetResolutionListWorker = new GetResolutionListWorker;
    connect(m_pGetResolutionListWorker, &GetResolutionListWorker::getResolutionListFinished,
            this, &DB_ExhibitionBooth::onGetResolutionListFinished);
    m_pGetResolutionListThread = new QThread;
    m_pGetResolutionListWorker->moveToThread(m_pGetResolutionListThread);
    connect(m_pGetResolutionListThread, &QThread::started, m_pGetResolutionListWorker, &GetResolutionListWorker::startWorker);

    m_pGetCameraFrameWorker = new GetCameraFrameWorker;
    connect(m_pGetCameraFrameWorker, &GetCameraFrameWorker::openCameraFinished, this, &DB_ExhibitionBooth::onOpenCameraFinished, Qt::DirectConnection);
    connect(m_pGetCameraFrameWorker, &GetCameraFrameWorker::cameraClosed, this, &DB_ExhibitionBooth::onCameraClosed);
    connect(m_pGetCameraFrameWorker, &GetCameraFrameWorker::newFrame, this, &DB_ExhibitionBooth::onNewFrame);
    m_pGetCameraFrameThread = new QThread;
    m_pGetCameraFrameWorker->moveToThread(m_pGetCameraFrameThread);
    connect(m_pGetCameraFrameThread, &QThread::started, m_pGetCameraFrameWorker, &GetCameraFrameWorker::startWorker);

    ui->pCursor->click();
}

DB_ExhibitionBooth::~DB_ExhibitionBooth()
{
    m_pListeningDevicesWorker->deleteLater();
    m_pListeningDevicesThread->deleteLater();
    m_pGetResolutionListWorker->deleteLater();
    m_pGetResolutionListThread->deleteLater();
    delete ui;
}



void DB_ExhibitionBooth::show()
{
    QWidget::show();
    m_pListeningDevicesThread->start();
}

bool DB_ExhibitionBooth::event(QEvent *event)
{
    if (event->type() == QEvent::WindowActivate) {
        this->showFullScreen();
    }
    return QWidget::event(event);
}

void DB_ExhibitionBooth::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->resize();
}

void DB_ExhibitionBooth::initWidget()
{
    this->setLayout(ui->verticalLayout);
    ui->verticalLayoutWidget_9->hide();
    ui->sWidget1->setLayout(ui->horizontalLayout);
    ui->sWidget2->setLayout(ui->horizontalLayout_6);
    ui->stackedWidget->setCurrentWidget(ui->sWidget1);
    ui->label_display->setScaledContents(true);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QColor(34, 34, 34)));
    this->setPalette(palette);

    /* 左工具栏 */
    ui->frame_left->setLayout(ui->horizontalLayout_1);
    ui->frame_left->setProperty("SHOW_WHERE", "left");
    ui->frame_left->raise();
    ui->pMenu->mSetIcon(QPixmap(":/images/caidan.png"), QPixmap(":/images/caidan2@2x.png"));
    ui->pMenu->mSetColor(QColor(102, 102, 102), Qt::white);
    ui->pMenu->mSetBGColor(Qt::transparent, QColor(216, 216, 216), QColor(20, 134, 250));
    ui->pMenu->mSetText(tr("菜单"));
    connect(ui->pMenu, &CustomPushButton_2::toggled, this, &DB_ExhibitionBooth::onShowMenuBtnToggled);
    ui->pMinimize->mSetIcon(QPixmap(":/images/zuixiaohua.png"));
    ui->pMinimize->mSetText(tr("最小化"));
    ui->pReforeLeft->mSetIcon(QPixmap(":/images/huhuan.png"));
    ui->pReforeLeft->mSetText(tr("互换"));
    connect(ui->pReforeLeft, &CustomPushButton_2::clicked, this, &DB_ExhibitionBooth::onReforeBtnClicked);

    /* 中工具栏 */
    ui->frame_mid->setLayout(ui->horizontalLayout_2);
    ui->frame_mid->raise();
    ui->pCursor->mSetIcon(QPixmap(":/images/yidong.png"), QPixmap(":/images/yidongchecked.png"));
    ui->pCursor->mSetColor(QColor(102, 102, 102), Qt::white);
    ui->pCursor->mSetBGColor(Qt::transparent, QColor(216, 216, 216), QColor(20, 134, 250));
    ui->pCursor->mSetText(tr("移动"));
    ui->pPen->mSetIcon(QPixmap(":/images/pizhu.png"), QPixmap(":/images/pizhuchecked.png"));
    ui->pPen->mSetColor(QColor(102, 102, 102), Qt::white);
    ui->pPen->mSetBGColor(Qt::transparent, QColor(216, 216, 216), QColor(20, 134, 250));
    ui->pPen->mSetText(tr("批注"));
    ui->pEraser->mSetIcon(QPixmap(":/images/xiangpica.png"), QPixmap(":/images/xiangpicachecked.png"));
    ui->pEraser->mSetColor(QColor(102, 102, 102), Qt::white);
    ui->pEraser->mSetBGColor(Qt::transparent, QColor(216, 216, 216), QColor(20, 134, 250));
    ui->pEraser->mSetText(tr("橡皮擦"));
    ui->pUndo->mSetIcon(QPixmap(":/images/chexiao.png"));
    ui->pUndo->mSetText(tr("撤销"));
    connect(ui->pUndo, &CustomPushButton_2::clicked, this, &DB_ExhibitionBooth::onUndo);
    ui->pRedo->mSetIcon(QPixmap(":/images/huifu.png"));
    ui->pRedo->mSetText(tr("恢复"));
    connect(ui->pRedo, &CustomPushButton_2::clicked, this, &DB_ExhibitionBooth::onRedo);
    ui->pRotate->mSetIcon(QPixmap(":/images/xuanzhuan.png"));
    ui->pRotate->mSetText(tr("旋转"));
    connect(ui->pRotate, &CustomPushButton_2::clicked, this, &DB_ExhibitionBooth::onRotate);
    ui->pOCR->mSetIcon(QPixmap(":/images/ocr.png"));
    ui->pOCR->mSetText(tr("文字识别"));
    ui->pTakingPicture->mSetIcon(QPixmap(":/images/paizhao.png"));
    ui->pTakingPicture->mSetText(tr("拍照"));
    ui->pZoomIn->mSetIcon(QPixmap(":/images/fangda.png"));
    ui->pZoomIn->mSetText(tr("放大"));
    connect(ui->pZoomIn, &QPushButton::clicked, this, &DB_ExhibitionBooth::onZoomIn);
    ui->pZoomOut->mSetIcon(QPixmap(":/images/suoxiao.png"));
    ui->pZoomOut->mSetText(tr("缩小"));
    connect(ui->pZoomOut, &QPushButton::clicked, this, &DB_ExhibitionBooth::onZoomOut);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);
    buttonGroup->addButton(ui->pPen);
    buttonGroup->addButton(ui->pEraser);
    buttonGroup->addButton(ui->pCursor);

    /* 右工具栏 */
    ui->frame_right->setLayout(ui->horizontalLayout_3);
    ui->frame_right->raise();
    ui->pContrastTeaching->mSetIcon(QPixmap(":/images/erfenping.png"));
    ui->pContrastTeaching->mSetText(tr("对比教学"));
    connect(ui->pContrastTeaching, &CustomPushButton_2::clicked, this, &DB_ExhibitionBooth::onContrastTeachingClicked);
    ui->pExitContrastTeaching->setText(tr("退出对比"));
    ui->pExitContrastTeaching->hide();
    connect(ui->pExitContrastTeaching, &CustomPushButton_1::clicked, this, &DB_ExhibitionBooth::onExitContrastTeachingClicked);
    ui->pReforeRight->mSetIcon(QPixmap(":/images/huhuan.png"));
    ui->pReforeRight->mSetText(tr("互换"));
    connect(ui->pReforeRight, &CustomPushButton_2::clicked, this, &DB_ExhibitionBooth::onReforeBtnClicked);
    QButtonGroup *buttonGroup1 = new QButtonGroup(this);
    buttonGroup1->setExclusive(true);
    buttonGroup1->addButton(ui->pContrastTeaching);

    /* 换位工具栏 */
    ui->frame_reforeLeft->setLayout(ui->horizontalLayout_4);
    ui->frame_reforeLeft->raise();
    ui->frame_reforeRight->setLayout(ui->horizontalLayout_5);
    ui->frame_reforeRight->raise();

    /* 菜单列表 */
    ui->frame_menu->setLayout(ui->verticalLayout_2);
    ui->frame_menu->hide();
    ui->pDevice->mSetIcon(QPixmap(":/images/shebei@2x.png"), QPixmap(":/images/shebei2@2x.png"));
    ui->pDevice->mSetArrow(QPixmap(":/images/jiantou.png"), QPixmap(":/images/jiantouchecked.png"));
    ui->pDevice->mSetText(tr("设备列表"));
    ui->pDevice->mSetColor(QColor(102,102,102), Qt::white);
    ui->pDevice->mSetBGColor(Qt::transparent, QColor(216,216,216), QColor(20,134,250));
    ui->pDevice->setEnabled(false);
    connect(ui->pDevice, &CustomPushButton_1::toggled, this, &DB_ExhibitionBooth::onShowDeviceBtnToggled, Qt::DirectConnection);
    ui->pScreenShot->mSetIcon(QPixmap(":/images/jietu.png"), QPixmap(":/images/jietuchecked.png"));
    ui->pScreenShot->mSetColor(QColor(102,102,102), Qt::white);
    ui->pScreenShot->mSetBGColor(Qt::transparent, QColor(216,216,216), QColor(20,134,250));
    ui->pScreenShot->mSetText(tr("截屏"));
    ui->pResolution->mSetIcon(QPixmap(":/images/fenbianlv.png"), QPixmap(":/images/fenbianlvchecked.png"));
    ui->pResolution->mSetArrow(QPixmap(":/images/jiantou.png"), QPixmap(":/images/jiantouchecked.png"));
    ui->pResolution->mSetColor(QColor(102,102,102), Qt::white);
    ui->pResolution->mSetBGColor(Qt::transparent, QColor(216,216,216), QColor(20,134,250));
    ui->pResolution->mSetText(tr("分辨率"));
    ui->pResolution->setEnabled(false);
    connect(ui->pResolution, &CustomPushButton_1::toggled, this, &DB_ExhibitionBooth::onShowResolutionBtnToggled, Qt::DirectConnection);
    ui->pAbountUs->mSetIcon(QPixmap(":/images/guanyu.png"), QPixmap(":/images/guanyuchecked.png"));
    ui->pAbountUs->mSetColor(QColor(102,102,102), Qt::white);
    ui->pAbountUs->mSetBGColor(Qt::transparent, QColor(216,216,216), QColor(20,134,250));
    ui->pAbountUs->mSetText(tr("关于我们"));
    ui->pExit->mSetIcon(QPixmap(":/images/tuichu.png"), QPixmap(":/images/tuichuchecked.png"));
    ui->pExit->mSetColor(QColor(102,102,102), Qt::white);
    ui->pExit->mSetBGColor(Qt::transparent, QColor(216,216,216), QColor(20,134,250));
    ui->pExit->mSetText(tr("退出"));

    /* 分辨率列表 */
    QStringListModel *rModel = new QStringListModel(this);
    ui->resolutionListView->setModel(rModel);
    CustomItemDelegate *rDelegate = new CustomItemDelegate(this);
    ui->resolutionListView->setItemDelegate(rDelegate);
    ui->resolutionListView->hide();
    ui->resolutionListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->resolutionListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->resolutionListView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->resolutionListView->setMouseTracking(true);
    ui->resolutionListView->setDragEnabled(false);
    connect(ui->resolutionListView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &DB_ExhibitionBooth::onResolutionListViewIndexMoved);
    /* 设备菜单列表 */
    QStringListModel *dModel = new QStringListModel(this);
    ui->deviceListView->setModel(dModel);
    CustomItemDelegate *dDelegate = new CustomItemDelegate(this);
    ui->deviceListView->setItemDelegate(dDelegate);
    ui->deviceListView->hide();
    ui->deviceListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->deviceListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->deviceListView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->deviceListView->setMouseTracking(true);
    ui->deviceListView->setDragEnabled(false);

    /* 图片列表 */
    ui->frame_imgList->setLayout(ui->verticalLayout_3);
    ui->frame_imgList->hide();
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滑动条
    ui->listWidget->setVerticalScrollMode(QListWidget::ScrollPerPixel);  //设置垂直滑动模式
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);   //设置此属性不会影响自定义item widget选中样式
    QScroller::grabGesture(ui->listWidget, QScroller::LeftMouseButtonGesture);//设置滑动手势


    ui->frame_cover->hide();
    connect(ui->frame_cover, &CustomFrame::frameClicked, this, &DB_ExhibitionBooth::onFrameCoverClicked);


    connect(ui->pOCR, &CustomPushButton_2::clicked, [=](){
        QPixmap pixmap = m_pGetCameraFrameWorker->getCurrentFrame();
        if (!pixmap.isNull()) {
            OCRWidget *ocrWidget = new OCRWidget(pixmap, this);
            ocrWidget->setGeometry(this->rect());
            ocrWidget->show();
        }else {
            DB_MBoxToolTip *m_pToolTip = new DB_MBoxToolTip(this);
            m_pToolTip->setToolTipStyle(1);
            m_pToolTip->showMBox(this, tr("请选择图片"), QPoint(this->rect().center()));
        }
    });

//    connect(ui->pPen, &CustomPushButton_2::toggled, [=](){
//        if (!ui->pPen->isChecked()) {
//            ui->pPen->mSetIcon(QPixmap(":/images/pizhu.png"));
//            return;
//        }
//        ui->pPen->mSetIcon(QPixmap(":/images/pizhuchecked.png"));
//    });
//    connect(ui->pEraser, &CustomPushButton_2::toggled, [=](){
//        if (!ui->pEraser->isChecked()) {
//            ui->pEraser->mSetIcon(QPixmap(":/images/xiangpica.png"));
//            return;
//        }
//        ui->pEraser->mSetIcon(QPixmap(":/images/xiangpicachecked.png"));
//    });
//    connect(ui->pCursor, &CustomPushButton_2::toggled, [=](){
//        if (!ui->pCursor->isChecked()) {
//            ui->pCursor->mSetIcon(QPixmap(":/images/yidong.png"));
//            return;
//        }
//        ui->pCursor->mSetIcon(QPixmap(":/images/yidongchecked.png"));
//    });

    connect(ui->pTakingPicture, &CustomPushButton_2::clicked, this, &DB_ExhibitionBooth::onTakingPhoto);
    connect(ui->pMinimize, &CustomPushButton_2::clicked, [=](){
        //this->showNormal();
        this->showMinimized();
    });
    connect(ui->pAbountUs, &CustomPushButton_1::clicked, [=](){
        ui->frame_menu->hide();
        AboutUs *about = new AboutUs(this);
        about->setGeometry(this->rect());
        about->show();
    });
    connect(ui->pExit, &CustomPushButton_1::clicked, [=](){
        ui->frame_menu->hide();
        qApp->exit(0);
    });
    connect(ui->pScreenShot, &CustomPushButton_1::clicked, [=](){
        ui->frame_menu->hide();
        DB_ScreenShots *screenShots = new DB_ScreenShots(this);
        connect(screenShots, &DB_ScreenShots::screenShots, this, &DB_ExhibitionBooth::screenShots);
        screenShots->setGeometry(this->rect());
        screenShots->show();
    });
}

QWidgetAction * DB_ExhibitionBooth::setWidgetToMenu(QWidget *defaultWidget, QMenu *menu)
{
    QWidgetAction *action = new QWidgetAction(menu);
    action->setDefaultWidget(defaultWidget);
    menu->addAction(action);
    return action;
}

void DB_ExhibitionBooth::showFrameCover()
{
    ui->frame_cover->setGeometry(this->rect());
    ui->frame_cover->show();
    ui->frame_cover->raise();
    ui->frame_left->raise();
    ui->frame_mid->raise();
    ui->frame_right->raise();
    ui->frame_reforeLeft->raise();
    ui->frame_reforeRight->raise();
}

void DB_ExhibitionBooth::showDisplayList()
{
    foreach(CustomPushButton_3 *button, m_pDisplayList) {
        ui->gridLayout->removeWidget(button);
    }
    QList<CustomPushButton_3 *> list;
    int checkedCount = 0;
    foreach(CustomPushButton_3 *button, m_pDisplayList) {
        if (button->isCheckable()) {
            checkedCount++;
            list.push_back(button);
        }else
            list.insert(list.size(), button);
    }
    if (0 == checkedCount)
    {
        foreach(CustomPushButton_3 *button, m_pDisplayList) {
            button->deleteLater();
        }
        m_pDisplayList.clear();
        ui->sWidget2->showText(tr("等待展示画面..."), PublicFunction::getFont(38), QColor(102, 102, 102));
    }else {
        m_pDisplayList.clear();
        for(int i = 0; i < list.size(); i++) {
            if (i > 1 && !list.at(i)->isCheckable()) {
                list.at(i)->deleteLater();
            }else {
                m_pDisplayList.push_back(list.at(i));
                if (i < 2)
                    ui->gridLayout->addWidget(list.at(i), 0, i);
                else
                    ui->gridLayout->addWidget(list.at(i), 1, i - 2);
            }
        }
    }
}

void DB_ExhibitionBooth::resize()
{
    QSize size;
    int radius;
    QFont font;
    int spacing;

    /* 左工具栏 */
    size = PublicFunction::getScaleSize(QSize(158, 74));
    ui->frame_left->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(34, 33));
    ui->pMenu->mSetIconSize(size);
    ui->pMinimize->mSetIconSize(size);
    size = PublicFunction::getScaleSize(QSize(68, 74));
    ui->pMenu->setFixedSize(size);
    ui->pMinimize->setFixedSize(size);
    font = PublicFunction::getFont(14);
    ui->pMenu->mSetFont(font);
    ui->pMinimize->mSetFont(font);
    spacing = PublicFunction::getScaleWidth(5);
    ui->pMenu->mSetSpacing(spacing);
    ui->pMinimize->mSetSpacing(spacing);
    radius = PublicFunction::getScaleWidth(8);
    ui->frame_left->setStyleSheet(QString("#%1{background: rgba(230,230,230,255); "
                                          "border-top-left-radius: %3px;"
                                          "border-top-right-radius: %3px;}").arg(ui->frame_left->objectName()).arg(radius));
    if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0) {
        ui->frame_left->move(QPoint(PublicFunction::getScaleWidth(46), this->height() - ui->frame_left->height()));
    }else {
        ui->frame_left->move(QPoint(this->width() - PublicFunction::getScaleWidth(46) - ui->frame_left->width(),
                                     this->height() - ui->frame_left->height()));
    }

    /* 中工具栏 */
    size = PublicFunction::getScaleSize(QSize(710, 74));
    ui->frame_mid->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(34, 33));
    ui->pCursor->mSetIconSize(size);
    ui->pPen->mSetIconSize(size);
    ui->pEraser->mSetIconSize(size);
    ui->pUndo->mSetIconSize(size);
    ui->pRedo->mSetIconSize(size);
    ui->pRotate->mSetIconSize(size);
    ui->pOCR->mSetIconSize(size);
    ui->pTakingPicture->mSetIconSize(size);
    ui->pZoomIn->mSetIconSize(size);
    ui->pZoomOut->mSetIconSize(size);
    size = PublicFunction::getScaleSize(QSize(68, 74));
    ui->pCursor->setFixedSize(size);
    ui->pPen->setFixedSize(size);
    ui->pEraser->setFixedSize(size);
    ui->pUndo->setFixedSize(size);
    ui->pRedo->setFixedSize(size);
    ui->pRotate->setFixedSize(size);
    ui->pOCR->setFixedSize(size);
    ui->pTakingPicture->setFixedSize(size);
    ui->pZoomIn->setFixedSize(size);
    ui->pZoomOut->setFixedSize(size);
    font = PublicFunction::getFont(14);
    ui->pCursor->mSetFont(font);
    ui->pPen->mSetFont(font);
    ui->pEraser->mSetFont(font);
    ui->pUndo->mSetFont(font);
    ui->pRedo->mSetFont(font);
    ui->pRotate->mSetFont(font);
    ui->pOCR->mSetFont(font);
    ui->pTakingPicture->mSetFont(font);
    ui->pZoomIn->mSetFont(font);
    ui->pZoomOut->mSetFont(font);
    ui->pCursor->mSetSpacing(spacing);
    ui->pPen->mSetSpacing(spacing);
    ui->pEraser->mSetSpacing(spacing);
    ui->pUndo->mSetSpacing(spacing);
    ui->pRedo->mSetSpacing(spacing);
    ui->pRotate->mSetSpacing(spacing);
    ui->pOCR->mSetSpacing(spacing);
    ui->pTakingPicture->mSetSpacing(spacing);
    ui->pZoomIn->mSetSpacing(spacing);
    ui->pZoomOut->mSetSpacing(spacing);
    radius = PublicFunction::getScaleWidth(8);
    ui->frame_mid->setStyleSheet(QString("#%1{background: rgba(230,230,230,255); "
                                          "border-top-left-radius: %3px;"
                                          "border-top-right-radius: %3px;}").arg(ui->frame_mid->objectName()).arg(radius));
    ui->frame_mid->move(QPoint((this->width() - ui->frame_mid->width())/2, this->height() - ui->frame_mid->height()));

    /* 右工具栏 */
    size = PublicFunction::getScaleSize(QSize(34, 33));
    ui->pContrastTeaching->mSetIconSize(size);
    size = PublicFunction::getScaleSize(QSize(68, 74));
    ui->pContrastTeaching->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(78, 74));
    ui->pExitContrastTeaching->setFixedSize(size);
    font = PublicFunction::getFont(14);
    ui->pContrastTeaching->mSetFont(font);
    ui->pExitContrastTeaching->setFont(font);
    ui->pContrastTeaching->mSetSpacing(spacing);
    radius = PublicFunction::getScaleWidth(8);
    ui->frame_right->setStyleSheet(QString("#%1{background: rgba(230,230,230,255); "
                                          "border-top-left-radius: %3px;"
                                          "border-top-right-radius: %3px;}").arg(ui->frame_right->objectName()).arg(radius));
    if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0) {
        size = PublicFunction::getScaleSize(QSize(82, 74));
        ui->frame_right->setFixedSize(size);
        ui->frame_right->move(QPoint(this->width() - PublicFunction::getScaleWidth(46) - ui->frame_right->width(),
                                     this->height() - ui->frame_right->height()));
    }else {
        size = PublicFunction::getScaleSize(QSize(92, 74));
        ui->frame_right->setFixedSize(size);
        ui->frame_right->move(QPoint(PublicFunction::getScaleWidth(46), this->height() - ui->frame_right->height()));
    }

    /* 换位工具栏 */
    size = PublicFunction::getScaleSize(QSize(82, 74));
    ui->frame_reforeLeft->setFixedSize(size);
    ui->frame_reforeRight->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(34, 33));
    ui->pReforeLeft->mSetIconSize(size);
    ui->pReforeRight->mSetIconSize(size);
    size = PublicFunction::getScaleSize(QSize(68, 74));
    ui->pReforeLeft->setFixedSize(size);
    ui->pReforeRight->setFixedSize(size);
    font = PublicFunction::getFont(14);
    ui->pReforeLeft->mSetFont(font);
    ui->pReforeRight->mSetFont(font);
    ui->pReforeLeft->mSetSpacing(spacing);
    ui->pReforeRight->mSetSpacing(spacing);
    radius = PublicFunction::getScaleWidth(8);
    ui->frame_reforeLeft->setStyleSheet(QString("#%1{background: rgba(230,230,230,255); "
                                          "border-top-left-radius: %3px;"
                                          "border-top-right-radius: %3px;}").arg(ui->frame_reforeLeft->objectName()).arg(radius));
    ui->frame_reforeRight->setStyleSheet(QString("#%1{background: rgba(230,230,230,255); "
                                          "border-top-left-radius: %3px;"
                                          "border-top-right-radius: %3px;}").arg(ui->frame_reforeRight->objectName()).arg(radius));
    if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0) {
        ui->frame_reforeLeft->move(QPoint(ui->frame_left->x() + ui->frame_left->width() + PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeLeft->height()));
        ui->frame_reforeRight->move(QPoint(ui->frame_right->x() - ui->frame_reforeLeft->width() - PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeRight->height()));
    }else {
        ui->frame_reforeLeft->move(QPoint(ui->frame_right->x() + ui->frame_right->width() + PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeLeft->height()));
        ui->frame_reforeRight->move(QPoint(ui->frame_left->x() - ui->frame_reforeLeft->width() - PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeRight->height()));
    }

    /* 菜单列表 */
    ui->frame_menu->setStyleSheet("border: none;");
    ui->verticalLayout_2->setContentsMargins(0, PublicFunction::getScaleWidth(12), 0, PublicFunction::getScaleWidth(12));
    ui->verticalLayout_2->setSpacing(2);
    size = PublicFunction::getScaleSize(QSize(146, 252));
    ui->frame_menu->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(146, 44));
    ui->pDevice->setFixedSize(size);
    ui->pResolution->setFixedSize(size);
    ui->pAbountUs->setFixedSize(size);
    ui->pExit->setFixedSize(size);
    ui->pScreenShot->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(25, 25));
    ui->pDevice->mSetIconSize(size);
    ui->pResolution->mSetIconSize(size);
    ui->pAbountUs->mSetIconSize(size);
    ui->pExit->mSetIconSize(size);
    ui->pScreenShot->mSetIconSize(size);
    size = PublicFunction::getScaleSize(QSize(6, 11));
    ui->pDevice->mSetArrowSize(size);
    ui->pResolution->mSetArrowSize(size);
    int margin = PublicFunction::getScaleWidth(18);
    spacing = PublicFunction::getScaleWidth(14);
    ui->pDevice->mSetMarginAndSpacing(margin, 0, margin, 0, spacing);
    ui->pResolution->mSetMarginAndSpacing(margin, 0, margin, 0, spacing);
    ui->pAbountUs->mSetMarginAndSpacing(margin, 0, margin, 0, spacing);
    ui->pExit->mSetMarginAndSpacing(margin, 0, margin, 0, spacing);
    ui->pScreenShot->mSetMarginAndSpacing(margin, 0, margin, 0, spacing);
    font = PublicFunction::getFont(14);
    ui->pDevice->mSetFont(font);
    ui->pResolution->mSetFont(font);
    ui->pAbountUs->mSetFont(font);
    ui->pExit->mSetFont(font);
    ui->pScreenShot->mSetFont(font);
    ui->frame_menu->setStyleSheet(QString("#%1{background: rgba(230, 230, 230, 255);"
                                          "border-radius: %2px;}").arg(ui->frame_menu->objectName()).arg(PublicFunction::getScaleWidth(8)));

    ui->resolutionListView->setStyleSheet(QString("QListView{"
                                                  "background: rgba(230, 230, 230, 255);"
                                                  "border-radius: %1px;"
                                                  "padding-top: %2px;"
                                                  "padding-bottom: %2px;"
                                                  "}").arg(PublicFunction::getScaleWidth(8)).arg(PublicFunction::getScaleWidth(7)));
    static_cast<CustomItemDelegate*>(ui->resolutionListView->itemDelegate())->setPaddindTopAndBottom(PublicFunction::getScaleWidth(7));
    ui->deviceListView->setStyleSheet(QString("QListView{"
                                                  "background: rgba(230, 230, 230, 255);"
                                                  "border-radius: %1px;"
                                                  "padding-top: %2px;"
                                                  "padding-bottom: %2px;"
                                                  "}").arg(PublicFunction::getScaleWidth(8)).arg(PublicFunction::getScaleWidth(7)));
    static_cast<CustomItemDelegate*>(ui->deviceListView->itemDelegate())->setPaddindTopAndBottom(PublicFunction::getScaleWidth(7));

    ui->sWidget2->setAutoFillBackground(true);
    QPalette palette1 = ui->sWidget2->palette();
    palette1.setBrush(QPalette::Background, QBrush(Qt::yellow));
    ui->sWidget2->setPalette(palette1);
    if (ui->stackedWidget->currentWidget() == ui->sWidget2 &&
            ui->sWidget2->property("FULLSCREEN").toString().compare("true") == 0) {
        ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
    }else {
        ui->horizontalLayout_6->setContentsMargins(PublicFunction::getScaleWidth(80),
                                                   PublicFunction::getScaleWidth(20),
                                                   PublicFunction::getScaleWidth(80),
                                                   ui->frame_left->height() + PublicFunction::getScaleWidth(10));
    }

    ui->gridLayout->setVerticalSpacing(PublicFunction::getScaleWidth(10));
}

void DB_ExhibitionBooth::onDeviceNumChanged()
{
    m_pDeviceNameList = m_pListeningDevicesWorker->getDeviceNameList();
    if (0 == m_pDeviceNameList.size())
    {
        ui->pDevice->setEnabled(false);
        return;
    }
    QStringListModel *model = static_cast<QStringListModel*>(ui->deviceListView->model());
    int index = 0;
    index = m_pDeviceNameList.indexOf(m_pGetCameraFrameWorker->getDeviceName());
    if (m_pGetCameraFrameWorker->isRunning() && -1 == index) {
        m_pGetCameraFrameWorker->stopRunning();
        m_pGetCameraFrameThread->quit();
        m_pGetCameraFrameThread->wait();
    }
    if (!m_pGetCameraFrameWorker->isRunning()) {
        index = 0;
        m_pGetCameraFrameWorker->initWorker(m_pDeviceNameList.at(index));
        m_pGetCameraFrameThread->start();
    }
    QVector<QString> deviceList;
    foreach(QString str, m_pListeningDevicesWorker->getDevicesDescription()) {
        QStringList list = str.split(":");
        if (2 == list.size())
            deviceList.push_back(QString(list.at(1)).trimmed());
        else
            deviceList.push_back(str);
    }
    QSize itemSize = ui->deviceListView->itemDelegate()->sizeHint(QStyleOptionViewItem(), model->index(0));
    ui->deviceListView->setFixedSize(itemSize.width(), itemSize.height() * deviceList.size()
                                         + static_cast<CustomItemDelegate*>(ui->deviceListView->itemDelegate())->getPaddingTopAndBottom());
    model->setStringList(deviceList.toList());
    ui->deviceListView->setCurrentIndex(model->index(index));

    if (!ui->pDevice->isEnabled())
        ui->pDevice->setEnabled(true);
}

void DB_ExhibitionBooth::onGetResolutionListFinished()
{
    m_pGetResolutionListThread->quit();
    m_pGetResolutionListThread->wait();

    QVector<QString> resolutionList = m_pGetResolutionListWorker->getResolutionList();
    if (resolutionList.size() == 0)
    {
        ui->pResolution->setEnabled(false);
        return;
    }

    disconnect(ui->resolutionListView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &DB_ExhibitionBooth::onResolutionListViewIndexMoved);
    QStringListModel *model = static_cast<QStringListModel*>(ui->resolutionListView->model());
    model->setStringList(resolutionList.toList());
    QSize itemSize = ui->resolutionListView->itemDelegate()->sizeHint(QStyleOptionViewItem(), model->index(0));
    ui->resolutionListView->setFixedSize(itemSize.width(), itemSize.height() * resolutionList.size()
                                         + static_cast<CustomItemDelegate*>(ui->resolutionListView->itemDelegate())->getPaddingTopAndBottom() * 2);
    int resolutionWidth, resolutionHeight;
    m_pGetCameraFrameWorker->getResolution(&resolutionWidth, &resolutionHeight);
    int index = resolutionList.indexOf(QString("%1x%2").arg(resolutionWidth).arg(resolutionHeight));
    if (-1 != index)
        ui->resolutionListView->setCurrentIndex(model->index(index));
    connect(ui->resolutionListView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &DB_ExhibitionBooth::onResolutionListViewIndexMoved);


    if (!ui->pResolution->isEnabled())
        ui->pResolution->setEnabled(true);
}

void DB_ExhibitionBooth::onOpenCameraFinished()
{
    m_pGetResolutionListWorker->setDeviceName(m_pGetCameraFrameWorker->getDeviceName());
    m_pGetResolutionListThread->start();
}

void DB_ExhibitionBooth::onCameraClosed(int ret)
{
//    if (-2 == ret) {
//        DB_MBoxToolTip *m_pToolTip = new DB_MBoxToolTip(this);
//        m_pToolTip->setToolTipStyle(1);
//        m_pToolTip->showMBox(this, tr("设备打开失败"), QPoint(this->rect().center()));
//    }else if (-1 == ret) {
//        CustomMBox *mbox = new CustomMBox(tr("提示"), tr("设备已断开，是否重新连接？"), tr("重新连接"), tr("关闭"));
//        connect(mbox, &CustomMBox::mboxClosed, this, &DB_ExhibitionBooth::deviceDisconnect);
//        mbox->show();
//    }
//    m_pCameraThread->quit();
//    m_pCameraThread->wait();
}

void DB_ExhibitionBooth::onNewFrame(QPixmap pixmap)
{
    if (ui->stackedWidget->currentWidget() == ui->sWidget2) {
        if (m_pDisplayList.size() == 0) {
            ui->sWidget2->mSetPixmap(pixmap);
            return;
        }else
            ui->sWidget2->mSetPixmap(QPixmap());

        foreach(CustomPushButton_3 *button, m_pDisplayList) {
            if (button->property("USE_CAMERA").toString().compare("true") == 0) {
                button->mSetPixmap(pixmap);
                break;
            }
        }
    }else {
        ui->label_display->mSetPixmap(pixmap);
    }
}

void DB_ExhibitionBooth::onReforeBtnClicked()
{
    ui->pMenu->setChecked(false);
    if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0) {
        ui->frame_left->move(QPoint(this->width() - PublicFunction::getScaleWidth(46) - ui->frame_left->width(),
                                     this->height() - ui->frame_left->height()));
        ui->horizontalLayout_1->insertWidget(1, ui->pMenu);
        ui->horizontalLayout_1->insertWidget(1, ui->pMinimize);
        ui->frame_right->move(QPoint(PublicFunction::getScaleWidth(46), this->height() - ui->frame_right->height()));
        ui->horizontalLayout_3->insertWidget(1, ui->pContrastTeaching);
        ui->horizontalLayout_3->insertWidget(1, ui->pExitContrastTeaching);
        ui->frame_reforeLeft->move(QPoint(ui->frame_right->x() + ui->frame_right->width() + PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeLeft->height()));
        ui->frame_reforeRight->move(QPoint(ui->frame_left->x() - ui->frame_reforeLeft->width() - PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeRight->height()));
        ui->frame_left->setProperty("SHOW_WHERE", "right");
    }else {
        ui->frame_left->move(QPoint(PublicFunction::getScaleWidth(46), this->height() - ui->frame_left->height()));
        ui->horizontalLayout_1->insertWidget(1, ui->pMinimize);
        ui->horizontalLayout_1->insertWidget(1, ui->pMenu);
        ui->frame_right->move(QPoint(this->width() - PublicFunction::getScaleWidth(46) - ui->frame_right->width(),
                                     this->height() - ui->frame_right->height()));
        ui->horizontalLayout_3->insertWidget(1, ui->pExitContrastTeaching);
        ui->horizontalLayout_3->insertWidget(1, ui->pContrastTeaching);
        ui->frame_reforeLeft->move(QPoint(ui->frame_left->x() + ui->frame_left->width() + PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeLeft->height()));
        ui->frame_reforeRight->move(QPoint(ui->frame_right->x() - ui->frame_reforeLeft->width() - PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeRight->height()));
        ui->frame_left->setProperty("SHOW_WHERE", "left");
    }
}

void DB_ExhibitionBooth::onContrastTeachingClicked()
{
    if (m_pGetCameraFrameWorker->isRunning()) {
        CustomPushButton_3 *button = new CustomPushButton_3(this);
        connect(button, &CustomPushButton_3::toClosed, this, &DB_ExhibitionBooth::onDisplayClosed);
        connect(button, &CustomPushButton_3::toScale, this, &DB_ExhibitionBooth::onDisplayScale);
        button->setFixedHeight((this->height() - ui->horizontalLayout_6->contentsMargins().top()
                                - ui->horizontalLayout_6->contentsMargins().bottom() - ui->gridLayout->verticalSpacing())/2);
        QPixmap pixmap(button->size());
        pixmap.fill(Qt::black);
        button->mSetPixmap(pixmap);
        button->setProperty("USE_CAMERA", "true");
        CustomPushButton_3 *button1 = new CustomPushButton_3(this);
        connect(button1, &CustomPushButton_3::toClosed, this, &DB_ExhibitionBooth::onDisplayClosed);
        connect(button1, &CustomPushButton_3::toScale, this, &DB_ExhibitionBooth::onDisplayScale);
        button1->setProperty("USE_CAMERA", "false");
        button1->setFixedHeight((this->height() - ui->horizontalLayout_6->contentsMargins().top()
                                - ui->horizontalLayout_6->contentsMargins().bottom() - ui->gridLayout->verticalSpacing())/2);
        m_pDisplayList.push_back(button);
        m_pDisplayList.push_back(button1);
    }
    this->showDisplayList();

    ui->stackedWidget->setCurrentWidget(ui->sWidget2);
    ui->pContrastTeaching->hide();
    ui->pExitContrastTeaching->show();
    QSize size = PublicFunction::getScaleSize(QSize(92, 74));
    ui->frame_right->setFixedSize(size);
    if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0) {
        ui->frame_right->move(QPoint(this->width() - PublicFunction::getScaleWidth(46) - ui->frame_right->width(),
                                     this->height() - ui->frame_right->height()));
        ui->frame_reforeRight->move(QPoint(ui->frame_right->x() - ui->frame_reforeLeft->width() - PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeRight->height()));
    }else {
        ui->frame_right->move(QPoint(PublicFunction::getScaleWidth(46), this->height() - ui->frame_right->height()));
        ui->frame_reforeLeft->move(QPoint(ui->frame_right->x() + ui->frame_right->width() + PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeLeft->height()));
    }
}

void DB_ExhibitionBooth::onExitContrastTeachingClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sWidget1);
    m_pDisplayList.clear();
    ui->pContrastTeaching->show();
    ui->pExitContrastTeaching->hide();
    QSize size = PublicFunction::getScaleSize(QSize(82, 74));
    ui->frame_right->setFixedSize(size);
    if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0) {
        ui->frame_right->move(QPoint(this->width() - PublicFunction::getScaleWidth(46) - ui->frame_right->width(),
                                     this->height() - ui->frame_right->height()));
        ui->frame_reforeRight->move(QPoint(ui->frame_right->x() - ui->frame_reforeLeft->width() - PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeRight->height()));
    }else {
        ui->frame_right->move(QPoint(PublicFunction::getScaleWidth(46), this->height() - ui->frame_right->height()));
        ui->frame_reforeLeft->move(QPoint(ui->frame_right->x() + ui->frame_right->width() + PublicFunction::getScaleWidth(10),
                                     this->height() - ui->frame_reforeLeft->height()));
    }
}

void DB_ExhibitionBooth::onShowResolutionBtnToggled(bool checked)
{
    if (checked) {
        if (ui->pDevice->isChecked())
            ui->pDevice->setChecked(false);
        if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0)
            ui->resolutionListView->move(QPoint(ui->frame_menu->x() + ui->frame_menu->width() + PublicFunction::getScaleWidth(10),
                                            ui->frame_menu->y() + ui->pResolution->y() + ui->pResolution->height() - ui->resolutionListView->height()));
        else
            ui->resolutionListView->move(QPoint(ui->frame_menu->x() - ui->resolutionListView->width() - PublicFunction::getScaleWidth(10),
                                            ui->frame_menu->y() + ui->pResolution->y() + ui->pResolution->height() - ui->resolutionListView->height()));
        ui->resolutionListView->show();
        ui->resolutionListView->raise();
    }else {
        ui->resolutionListView->hide();
    }
}

void DB_ExhibitionBooth::onShowDeviceBtnToggled(bool checked)
{
    if (checked) {
        if (ui->pResolution->isChecked())
            ui->pResolution->setChecked(false);
        if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0)
            ui->deviceListView->move(QPoint(ui->frame_menu->x() + ui->frame_menu->width() + PublicFunction::getScaleWidth(10),
                                            ui->frame_menu->y() + ui->pDevice->y() + ui->pDevice->height() - ui->deviceListView->height()));
        else
            ui->deviceListView->move(QPoint(ui->frame_menu->x() - ui->deviceListView->width() - PublicFunction::getScaleWidth(10),
                                            ui->frame_menu->y() + ui->pDevice->y() + ui->pDevice->height() - ui->deviceListView->height()));
        ui->deviceListView->show();
        ui->deviceListView->raise();
    }else {
        ui->deviceListView->hide();
    }
}

void DB_ExhibitionBooth::onShowMenuBtnToggled(bool checked)
{
    if (checked) {
        if (ui->frame_left->property("SHOW_WHERE").toString().compare("left") == 0)
            ui->frame_menu->move(QPoint(ui->frame_left->x(),
                                        ui->frame_left->y() - ui->frame_menu->height() - PublicFunction::getScaleWidth(10)));
        else
            ui->frame_menu->move(QPoint(ui->frame_left->x() + ui->frame_left->width() - ui->frame_menu->width(),
                                        ui->frame_left->y() - ui->frame_menu->height() - PublicFunction::getScaleWidth(10)));
        this->showFrameCover();
        ui->frame_menu->show();
        ui->frame_menu->raise();
    }else {
        ui->frame_menu->hide();
        ui->frame_cover->hide();
        ui->pDevice->setChecked(false);
        ui->pResolution->setChecked(false);
    }
}

void DB_ExhibitionBooth::onResolutionListViewIndexMoved(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    QString resolution = ui->resolutionListView->model()->index(current.row(), current.column()).data().toString();
    QStringList list = resolution.split("x");
    if (2 != list.size())
        return;

    int width = QString(list.at(0)).toInt();
    int height = QString(list.at(1)).toInt();
    m_pGetCameraFrameWorker->stopRunning();
    m_pGetCameraFrameThread->quit();
    m_pGetCameraFrameThread->wait();
    m_pGetCameraFrameWorker->setResolution(width, height);
    m_pGetCameraFrameThread->start();
}

void DB_ExhibitionBooth::onFrameCoverClicked()
{
    ui->pMenu->setChecked(false);
}

void DB_ExhibitionBooth::onDisplayClosed()
{
    CustomPushButton_3 *button = static_cast<CustomPushButton_3 *>(sender());
    button->toClearDisplay();
    this->showDisplayList();
}

void DB_ExhibitionBooth::onDisplayScale(bool showFullScreen)
{
    CustomPushButton_3 *button = static_cast<CustomPushButton_3 *>(sender());
    int index = m_pDisplayList.indexOf(button);
    if (-1 == index)
        return;

    if (showFullScreen) {
        button->setCheckable(false);
        ui->sWidget2->setProperty("FULLSCREEN", "true");
        ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        for(int i = 0; i < m_pDisplayList.size(); i++) {
            if (index != i) {
                m_pDisplayList.at(i)->hide();
            }else {
                m_pDisplayList.at(i)->setFixedHeight(ui->sWidget2->height());
            }
        }
    }else {
        button->setCheckable(true);
        ui->sWidget2->setProperty("FULLSCREEN", "false");
        ui->horizontalLayout_6->setContentsMargins(PublicFunction::getScaleWidth(80),
                                                   PublicFunction::getScaleWidth(20),
                                                   PublicFunction::getScaleWidth(80),
                                                   ui->frame_left->height() + PublicFunction::getScaleWidth(10));
        for(int i = 0; i < m_pDisplayList.size(); i++) {
            if (index != i)
                m_pDisplayList.at(i)->show();
            else
                m_pDisplayList.at(i)->setFixedHeight((this->height() - ui->horizontalLayout_6->contentsMargins().top()
                                                    - ui->horizontalLayout_6->contentsMargins().bottom() - ui->gridLayout->verticalSpacing())/2);
        }
    }

}

void DB_ExhibitionBooth::onZoomIn()
{

}

void DB_ExhibitionBooth::onZoomOut()
{

}

void DB_ExhibitionBooth::onRotate()
{
    if (m_pGetCameraFrameWorker->isRunning())
        m_pGetCameraFrameWorker->setRotationAngleWithAnti();
}

void DB_ExhibitionBooth::onUndo()
{

}

void DB_ExhibitionBooth::onRedo()
{

}


void DB_ExhibitionBooth::screenShots(QRectF rect)
{
    DB_ScreenShots *screenShots = static_cast<DB_ScreenShots*>(sender());
    delete screenShots;

    QFileDialog fileDialog;
    QString filter;
    QString fileName = fileDialog.getSaveFileName(this, tr("另存为"), QString("/Screenshot%1")
                            .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")),
                            "PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)", &filter);
    if (fileName.length() == 0)
        return;

    bool ret;
    QPixmap pixmap = this->grab(rect.toRect());
    if (filter.compare("PNG(*.png)") == 0) {
        ret = pixmap.save(fileName.append(".png"));
    }else if (filter.compare("JPG(*.jpg)") == 0){
        ret = pixmap.save(fileName.append(".jpg"));
    }else if (filter.compare("BMP(*.bmp)") == 0){
        ret = pixmap.save(fileName.append(".bmp"));
    }

    if (!ret) {
        //this->execMsgBox(tr("提示"), tr("保存失败。"), tr("确定"), QString());
    }else {
        //this->execMsgBox(tr("提示"), tr("保存完成。"), tr("确定"), QString());
    }
}


void DB_ExhibitionBooth::onTakingPhoto()
{
//    if (!m_pCameraThread->isRunning()) {
//        DB_MBoxToolTip *m_pToolTip = new DB_MBoxToolTip(this);
//        m_pToolTip->setToolTipStyle(1);
//        m_pToolTip->showMBox(this, tr("摄像头未打开"), QPoint(this->rect().center()));
//        return;
//    }
//    //获取摄像头当前帧
//    QImage img = m_pCamera->getCurrentFrame();
//    if (!img.isNull()) {
//        TakingPhotoWidget *widget = new TakingPhotoWidget(QPixmap::fromImage(img), this);
//        widget->setGeometry(this->rect());
//        widget->show();
//    }else {
//        DB_MBoxToolTip *m_pToolTip = new DB_MBoxToolTip(this);
//        m_pToolTip->setToolTipStyle(1);
//        m_pToolTip->showMBox(this, tr("拍照失败"), QPoint(this->rect().center()));
//    }
}
#endif
