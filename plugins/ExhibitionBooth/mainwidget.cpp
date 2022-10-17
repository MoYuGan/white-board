#include "mainwidget.h"
#include "ui_mainwidget.h"

#define PROPERTY_USE_CAMERA  "USE_CAMERA"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->installEventFilter(this);
    this->initWidget();
    this->resize();
    ui->toolBarMidLeft->setActionChecked(0, true);
    e_PenSize = PublicFunction::getScaleSize(3);
    e_PenColor = Qt::red;
    e_EraserSize = PublicFunction::getScaleSize(80, 140);

    QPixmap pixmap(this->size());
    this->getTextPixmap(&pixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                        tr("未连接摄像头"), PublicFunction::getScaleSize(200, 30));
    ui->label_display->mSetTipPixmap(pixmap);

    m_MBoxTip = new MessageBox_Tip(this);
    m_MBoxTip->hide();
}

MainWidget::~MainWidget()
{
    if (nullptr != m_pListeningDevicesWorker)
        m_pListeningDevicesWorker->deleteLater();
    if (nullptr != m_pListeningDevicesThread)
        m_pListeningDevicesThread->deleteLater();
    if (nullptr != m_pGetResolutionListWorker)
        m_pGetResolutionListWorker->deleteLater();
    if (nullptr != m_pGetResolutionListThread)
        m_pGetResolutionListThread->deleteLater();
    if (nullptr != m_pGetCameraFrameWorker)
        m_pGetCameraFrameWorker->deleteLater();
    if (nullptr != m_pGetCameraFrameThread)
        m_pGetCameraFrameThread->deleteLater();
    delete ui;
}

void MainWidget::resize()
{
    QDesktopWidget *desktop = QApplication::desktop();
    this->setGeometry(desktop->screenGeometry(desktop->primaryScreen()));
    ui->graphicsView_1->setGeometry(this->rect());
    ui->graphicsView_2->setGeometry(this->rect());
    ui->sWidget1->setFixedSize(this->size());
    ui->sWidget2->setFixedSize(this->size());
    ui->toolbarLeft->move(QPoint(PublicFunction::getScaleSize(16),
                                 this->height() - PublicFunction::getScaleSize(16) + ui->toolBarMidLeft->getBorder() - ui->toolbarLeft->height()));
    ui->toolbarRefore_left->move(QPoint(ui->toolbarLeft->x() + ui->toolbarLeft->width(),
                                        this->height() - PublicFunction::getScaleSize(16) + ui->toolbarRefore_left->getBorder() - ui->toolbarRefore_left->height()));
    int spacing = 0;
    ui->toolBarMidLeft->move(QPoint((this->width() - ui->toolBarMidLeft->width() -
                                     ui->toolBarMidRight->width() - spacing)/2,
                                    this->height() - PublicFunction::getScaleSize(16) + ui->toolBarMidLeft->getBorder() - ui->toolBarMidLeft->height()));
    ui->toolBarMidRight->move(QPoint(ui->toolBarMidLeft->x() + ui->toolBarMidLeft->width() + spacing,
                                     this->height() - PublicFunction::getScaleSize(16) + ui->toolBarMidRight->getBorder() - ui->toolBarMidRight->height()));
    ui->toolbarRight->move(QPoint(this->width() - PublicFunction::getScaleSize(16) - ui->toolbarRight->width(),
                                  this->height() - PublicFunction::getScaleSize(16) + ui->toolbarRight->getBorder() - ui->toolbarRight->height()));
    ui->toolbarRefore_right->move(QPoint(ui->toolbarRight->x() - ui->toolbarRefore_right->width(),
                                        this->height() - PublicFunction::getScaleSize(16) +
                                         ui->toolbarRefore_right->getBorder() - ui->toolbarRefore_right->height()));

    ui->sWidget2->setAutoFillBackground(true);
    QPalette palette1 = ui->sWidget2->palette();
    palette1.setBrush(QPalette::Background, QBrush(QColor(20, 20, 22)));
    ui->sWidget2->setPalette(palette1);
    ui->horizontalLayout_6->setContentsMargins(PublicFunction::getScaleSize(80),
                                               PublicFunction::getScaleSize(20),
                                               PublicFunction::getScaleSize(80),
                                               ui->toolBarMidLeft->height() + PublicFunction::getScaleSize(10));
}

void MainWidget::show()
{
    QWidget::show();

    QPixmap pixmap(this->size());
    this->getTextPixmap(&pixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                        tr("正在查找设备..."), PublicFunction::getScaleSize(200, 30));
    ui->label_display->mSetTipPixmap(pixmap);
    m_pListeningDevicesThread->start();
}

bool MainWidget::event(QEvent *event)
{
    if (event->type() == QEvent::WindowActivate) {
        this->showFullScreen();
    }
    return QWidget::event(event);
}

bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
            this->hideMenu();
    }
    return QWidget::eventFilter(watched, event);
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    //this->resize();
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), QBrush(QColor(20, 20, 22)));
}

void MainWidget::initWidget()
{
    ui->verticalLayoutWidget_9->hide();
    this->setLayout(ui->verticalLayout);
    ui->stackedWidget->setCurrentWidget(ui->sWidget1);
    ui->sWidget1->setLayout(ui->horizontalLayout);
    ui->horizontalLayoutWidget->hide();
    ui->sWidget2->setLayout(ui->horizontalLayout_6);
    ui->horizontalLayoutWidget_4->hide();
    ui->graphicsView_1->raise();
    ui->graphicsView_2->raise();
    ui->graphicsView_2->hide();
    ui->toolbarLeft->raise();
    ui->toolBarMidLeft->raise();
    ui->toolBarMidRight->raise();
    ui->toolbarRefore_left->raise();
    ui->toolbarRefore_right->raise();
    ui->toolbarRight->raise();
    ui->toolbarRefore_left->mSetIcon(QPixmap("://images/qiehuan_1@2x.png"));
    ui->toolbarRefore_right->mSetIcon(QPixmap("://images/qiehuan2_1@2x.png"));
    ui->menuMain->hide();
    ui->menuDeviceList->hide();
    ui->menuResolutionList->hide();
    ui->controlMenu->hide();
    ui->toolbarRight->setProperty("SHOW_WHICH", "right");
    ui->label_display->setProperty(PROPERTY_USE_CAMERA, "true");

    connect(ui->toolbarLeft, &MainToolBar_Left::showMenu, this, &MainWidget::showMainMenu);
    connect(ui->toolbarLeft, &MainToolBar_Left::toMinimize, [=](){ this->showMinimized(); });
    connect(ui->toolBarMidLeft, &MainToolBar_MidLeft::moveBtnToggled, [=](bool checked){
        if (checked) {ui->graphicsView_1->setViewTool(BoardView::VT_None); ui->graphicsView_2->setViewTool(BoardView::VT_None);}});
    connect(ui->toolBarMidLeft, &MainToolBar_MidLeft::penBtnToggled, [=](bool checked){
        if (checked) {ui->graphicsView_1->setViewTool(BoardView::VT_Draw); ui->graphicsView_2->setViewTool(BoardView::VT_Draw);}});
    connect(ui->toolBarMidLeft, &MainToolBar_MidLeft::eraserBtnToggled, [=](bool checked){
        if (checked) {ui->graphicsView_1->setViewTool(BoardView::VT_Eraser); ui->graphicsView_2->setViewTool(BoardView::VT_Eraser);} });
    connect(ui->toolBarMidLeft, &MainToolBar_MidLeft::undoSignal, [=](){
        if (!ui->graphicsView_1->isHidden()) ui->graphicsView_1->undo();
        else ui->graphicsView_2->undo();
    });
    connect(ui->toolBarMidLeft, &MainToolBar_MidLeft::redoSignal, [=](){
        if (!ui->graphicsView_1->isHidden()) ui->graphicsView_1->redo();
        else ui->graphicsView_2->redo();
    });
    connect(ui->toolBarMidRight, &MainToolBar_MidRight::action_ocr, this, &MainWidget::onStartOCR);
    connect(ui->toolBarMidRight, &MainToolBar_MidRight::action_tackphoto, this, &MainWidget::onTakingPhoto);
    connect(ui->toolBarMidRight, &MainToolBar_MidRight::leftRotate, this, &MainWidget::onLeftRotate);
    connect(ui->toolBarMidRight, &MainToolBar_MidRight::rightRotate, this, &MainWidget::onRightRotate);
    connect(ui->toolBarMidRight, &MainToolBar_MidRight::zoomIn, this, &MainWidget::onZoomIn);
    connect(ui->toolBarMidRight, &MainToolBar_MidRight::zoomOut, this, &MainWidget::onZoomOut);
    connect(ui->toolbarRight, &MainToolBar_right::displayImage, this, &MainWidget::onDisplayImage);
    connect(ui->toolbarRight, &MainToolBar_right::enableContrast, this, &MainWidget::onEnableContrast);
    connect(ui->toolbarRight, &MainToolBar_right::cancelContrast, this, &MainWidget::onCancelContrast);
    connect(ui->toolbarRight, &MainToolBar_right::cameraChecked, this, &MainWidget::onCameraChecked);
    connect(ui->menuDeviceList, &DevicesMenu::deviceChanged, this, &MainWidget::onCameraChecked);
    connect(ui->menuMain, &MainMenu::showDeviceListMenu, this, &MainWidget::showDeviceListMenu, Qt::DirectConnection);
    connect(ui->menuMain, &MainMenu::showResolutionListMenu, this, &MainWidget::showResolutionListMenu, Qt::DirectConnection);
    connect(ui->menuMain, &MainMenu::showAbout, this, &MainWidget::showAbout);
    connect(ui->menuMain, &MainMenu::exitApplication, [=](){
        if (!e_EmbeddedToWhiteBoard)
            qApp->exit(0);
        else {
            if (m_pListeningDevicesWorker->isRunning()) {
                m_pListeningDevicesWorker->stopWorker();
                m_pListeningDevicesThread->quit();
                m_pListeningDevicesThread->wait();
            }

            if (m_pGetCameraFrameWorker->isRunning()) {
                m_pGetCameraFrameWorker->stopRunning();
                m_pGetCameraFrameThread->quit();
                m_pGetCameraFrameThread->wait();
            }

             emit hideWidget();
        }
    });
    connect(ui->menuMain, &MainMenu::widgetHide, [=](){ ui->toolbarLeft->setShowMenuBtnChecked(false);});
    connect(ui->menuResolutionList, &ResolutionMenu::resolutionChanged, this, &MainWidget::onResolutionChanged);
    connect(ui->toolbarRefore_left, &MainToolBar_Refore::btnClicked, this, &MainWidget::onReforeBtnClicked);
    connect(ui->toolbarRefore_right, &MainToolBar_Refore::btnClicked, this, &MainWidget::onReforeBtnClicked);

    m_pListeningDevicesWorker = new ListeningDevicesWorker;
    connect(m_pListeningDevicesWorker, &ListeningDevicesWorker::deviceNumChanged, this, &MainWidget::onDeviceNumChanged);
    m_pListeningDevicesThread = new QThread;
    m_pListeningDevicesWorker->moveToThread(m_pListeningDevicesThread);
    connect(m_pListeningDevicesThread, &QThread::started, m_pListeningDevicesWorker, &ListeningDevicesWorker::startWorker);

    m_pGetResolutionListWorker = new GetResolutionListWorker;
    connect(m_pGetResolutionListWorker, &GetResolutionListWorker::getResolutionListFinished,
            this, &MainWidget::onGetResolutionListFinished);
    m_pGetResolutionListThread = new QThread;
    m_pGetResolutionListWorker->moveToThread(m_pGetResolutionListThread);
    connect(m_pGetResolutionListThread, &QThread::started, m_pGetResolutionListWorker, &GetResolutionListWorker::startWorker);

    m_pGetCameraFrameWorker = new GetCameraFrameWorker;
    connect(m_pGetCameraFrameWorker, &GetCameraFrameWorker::openCameraFinished, this, &MainWidget::onOpenCameraFinished, Qt::DirectConnection);
    connect(m_pGetCameraFrameWorker, &GetCameraFrameWorker::cameraClosed, this, &MainWidget::onCameraClosed, Qt::DirectConnection);
    connect(m_pGetCameraFrameWorker, &GetCameraFrameWorker::newFrame, this, &MainWidget::onNewFrame);
    m_pGetCameraFrameThread = new QThread;
    m_pGetCameraFrameWorker->moveToThread(m_pGetCameraFrameThread);
    connect(m_pGetCameraFrameThread, &QThread::started, m_pGetCameraFrameWorker, &GetCameraFrameWorker::startWorker);

    m_DisplayGroup = new QButtonGroup(this);
    m_DisplayGroup->setExclusive(true);
}

void MainWidget::hideMenu()
{
    if (!ui->menuMain->isHidden())
        ui->menuMain->hide();
    ui->toolBarMidRight->hideMenu();
}


void MainWidget::addDisplayWidget(int id, bool useCamera, const QPixmap &pixmap, int angle)
{
    //int currentNum = m_pDisplayList.size();
    CustomPushButton_4 *button = new CustomPushButton_4(ui->sWidget2);
    button->setCheckable(true);
    button->setProperty("ID", id);
    connect(button, &CustomPushButton_4::toClosed, this, &MainWidget::onDisplayWidgetClosed);
    connect(button, &CustomPushButton_4::toScale, this, &MainWidget::onDisplayWidgetShowFullScreen);
    m_pDisplayList.push_back(button);
    m_DisplayGroup->addButton(button);

    QSize buttonSize;
    buttonSize.setHeight((ui->sWidget2->height() - ui->horizontalLayout_6->contentsMargins().top() - ui->horizontalLayout_6->contentsMargins().bottom() -
            ui->gridLayout->verticalSpacing())/2);
    buttonSize.setWidth((ui->sWidget2->width() - ui->horizontalLayout_6->contentsMargins().left() - ui->horizontalLayout_6->contentsMargins().right() -
                         ui->gridLayout->horizontalSpacing())/2);
    button->setFixedSize(buttonSize);

    QPixmap sPixmap(this->size());
    if (useCamera) {
        button->setProperty(PROPERTY_USE_CAMERA, "true");
        if (m_pGetCameraFrameWorker->isRunning())
            this->getTextPixmap(&sPixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                                tr("摄像头连接中..."), PublicFunction::getScaleSize(200, 30));
        else
            this->getTextPixmap(&sPixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                                tr("未连接摄像头"), PublicFunction::getScaleSize(200, 30));
        button->mSetTipPixmap(sPixmap);
    }else {
        button->setProperty(PROPERTY_USE_CAMERA, "false");
        if (pixmap.isNull()) {
            this->getTextPixmap(&sPixmap, QColor(20, 20, 22), QPixmap(), QSize(),
                                tr("等待画面展示..."), button->size(), PublicFunction::getFont(50));
            button->setProperty("IS_NULL", "true");
            button->mSetTipPixmap(sPixmap);
        }else {
            button->setProperty("IS_NULL", "false");
            button->mSetPixmap(pixmap, angle);
        }
    }

    //qDebug()<<currentNum<<m_pDisplayList.size();
    for(int i = 0; i < m_pDisplayList.size(); i++) {
        if (i < 2) {
            //qDebug()<<"add=====";
            ui->gridLayout->addWidget(m_pDisplayList.at(i), 0, i);
        }else
            ui->gridLayout->addWidget(m_pDisplayList.at(i), 1, i - 2);
    }

    if (4 == m_pDisplayList.size())
        e_Checkable = false;
}

void MainWidget::removeDisplayWidget(int id)
{
    CustomPushButton_4 *btn = nullptr;
    foreach(CustomPushButton_4 *button, m_pDisplayList) {
        if (button->property("ID").toInt() == id) {
            btn = button;
            m_pDisplayList.removeOne(button);
            ui->gridLayout->removeWidget(button);
            m_DisplayGroup->removeButton(button);
            break;
        }
    }
    if (nullptr != btn)
        btn->deleteLater();

    if (1 == m_pDisplayList.size()) {
        CustomPushButton_4 *button = m_pDisplayList.at(0);
        if (button->property("IS_NULL").toString().compare("true") == 0)
        {
            m_pDisplayList.removeOne(button);
            ui->gridLayout->removeWidget(button);
            m_DisplayGroup->removeButton(button);
            button->deleteLater();

            ui->sWidget2->showText(tr("等待画面展示..."), PublicFunction::getFont(30), QColor(102, 102, 102));
        }else {
            this->addDisplayWidget(-1, false);
        }
    }else {
        for(int i = 0; i < m_pDisplayList.size(); i++) {
            if (i < 2)
                ui->gridLayout->addWidget(m_pDisplayList.at(i), 0, i);
            else
                ui->gridLayout->addWidget(m_pDisplayList.at(i), 1, i - 2);
        }
    }

    if (m_pDisplayList.size() > 3)
        e_Checkable = false;
    else
        e_Checkable = true;
}

void MainWidget::removeDisplayWidget(CustomPushButton_4 *button)
{
    m_pDisplayList.removeOne(button);
    ui->gridLayout->removeWidget(button);
    m_DisplayGroup->removeButton(button);
    button->deleteLater();

    if (1 == m_pDisplayList.size()) {
        CustomPushButton_4 *button = m_pDisplayList.at(0);
        if (button->property("IS_NULL").toString().compare("true") == 0)
        {
            m_pDisplayList.removeOne(button);
            ui->gridLayout->removeWidget(button);
            m_DisplayGroup->removeButton(button);
            button->deleteLater();

            ui->sWidget2->showText(tr("等待画面展示..."), PublicFunction::getFont(30), QColor(102, 102, 102));
        }else {
            this->addDisplayWidget(-1, false);
            return;
        }
    }else {
        for(int i = 0; i < m_pDisplayList.size(); i++) {
            if (i < 2)
                ui->gridLayout->addWidget(m_pDisplayList.at(i), 0, i);
            else
                ui->gridLayout->addWidget(m_pDisplayList.at(i), 1, i - 2);
        }
    }

    if (m_pDisplayList.size() > 3)
        e_Checkable = false;
    else
        e_Checkable = true;
}

void MainWidget::getTextPixmap(QPixmap *srcPixmap, QColor bgColor, const QPixmap &logoPixmap, QSize logoSize,
                               const QString &text, QSize textSize, const QFont &font)
{
    srcPixmap->fill(bgColor);
    QPainter painter;
    painter.begin(srcPixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(QPen(QColor(102,102,102)));
    painter.setFont(font);
    if (!logoPixmap.isNull() && logoSize.isValid()) {
        QRect logoRect = QRect((srcPixmap->width() - logoSize.width())/2,
                                 (textSize.isValid() && !text.isEmpty())? (srcPixmap->height() - logoSize.height() - textSize.height())/2 :
                                                     (srcPixmap->height() - logoSize.height())/2, logoSize.width(), logoSize.height());
        painter.drawPixmap(logoRect, logoPixmap);
        if (textSize.isValid() && !text.isEmpty())
            painter.drawText(QRect((srcPixmap->width() - textSize.width())/2,
                                   logoRect.y() + logoRect.height(), textSize.width(), textSize.height()), text, QTextOption(Qt::AlignCenter));
    }else if (textSize.isValid() && !text.isEmpty()) {
        painter.drawText(QRect((srcPixmap->width() - textSize.width())/2,
                               (srcPixmap->height() - textSize.height())/2, textSize.width(), textSize.height()), text, QTextOption(Qt::AlignCenter));
    }
    painter.end();
}

void MainWidget::clearContrastDisplay()
{
    foreach(CustomPushButton_4 *button, m_pDisplayList) {
        ui->gridLayout->removeWidget(button);
        button->deleteLater();
    }
    m_pDisplayList.clear();
}

void MainWidget::stopGetFrameWorker()
{
    m_pGetCameraFrameWorker->stopRunning();
    m_pGetCameraFrameThread->quit();
}

void MainWidget::startGetFrameWorker(const QString &deviceName)
{
    this->showDisplayPixmap(tr("摄像头连接中..."));
    m_pGetResolutionListWorker->setDeviceName(deviceName);
    m_pGetResolutionListThread->start();
}

void MainWidget::showDisplayPixmap(const QString &text)
{
    QPixmap pixmap(this->size());
    this->getTextPixmap(&pixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                        text, PublicFunction::getScaleSize(200, 30));
    ui->label_display->mSetTipPixmap(pixmap);
}


void MainWidget::showMainMenu(bool checked)
{
    if (checked) {
        if (ui->toolbarRight->property("SHOW_WHICH").toString().compare("right") == 0) {
            ui->menuMain->move(ui->toolbarLeft->x(), ui->toolbarLeft->y() - ui->menuMain->height()
                                    - PublicFunction::getScaleSize(16) + ui->toolbarLeft->getBorder());
        }else {
            ui->menuMain->move(ui->toolbarLeft->x() + ui->toolbarLeft->width() - ui->menuMain->width(),
                               ui->toolbarLeft->y() - ui->menuMain->height()
                                    - PublicFunction::getScaleSize(16) + ui->toolbarLeft->getBorder());
        }

        ui->menuMain->raise();
        ui->menuMain->show();
    }else {
        ui->menuMain->hide();
    }
}

void MainWidget::onDeviceNumChanged()
{
    m_pDeviceNameList.clear();
    m_pDeviceNameList = m_pListeningDevicesWorker->getDeviceNameList();
    qDebug()<<"----------device num changed:"<<m_pDeviceNameList.size()<<m_pDeviceNameList;

    if (0 == m_pDeviceNameList.size())
    {
        this->showDisplayPixmap(tr("正在查找设备..."));
        ui->menuDeviceList->clearAction();
        ui->menuMain->setDeviceBtnEnabled(false);
        return;
    }

    int index = 0;
    index = m_pDeviceNameList.indexOf(m_pGetCameraFrameWorker->getDeviceName());
    if (-1 == index) {
        if (m_pGetCameraFrameWorker->isRunning()) {
            qDebug()<<"stop old camera";
            this->stopGetFrameWorker();
        }
    }

    if (0 == m_pDeviceNameList.size())
        return;

    QList<QString> deviceList;
    foreach(QString str, m_pListeningDevicesWorker->getDevicesDescription()) {
        QStringList list = str.split(":");
        if (2 == list.size())
            deviceList.push_back(QString(list.at(1)).trimmed());
        else
            deviceList.push_back(str);
    }

    ui->menuDeviceList->clearAction();
    ui->menuDeviceList->mSetAction(deviceList, m_pDeviceNameList.toList());
    ui->toolbarRight->clearCameraItem();
    foreach(QString str, deviceList) {
        ui->toolbarRight->addCameraItem(str);
    }

    if (-1 == index) {
        if (m_pGetCameraFrameThread->isRunning()) {
            qDebug()<<"wait camera stop";
            m_pGetCameraFrameThread->wait();
        }
        index = 0;
        m_DeviceName = m_pDeviceNameList.at(index);

        qDebug()<<"start camera:"<<m_DeviceName;
        this->startGetFrameWorker(m_DeviceName);
    }

    ui->menuDeviceList->setChecked(index, true);
    ui->toolbarRight->setCameraItemChecked(index, true);
    ui->menuMain->setDeviceBtnEnabled(true);
}

void MainWidget::onGetResolutionListFinished()
{
    m_pGetResolutionListThread->quit();
    m_pGetResolutionListThread->wait(); 
    m_pGetCameraFrameWorker->initWorker(m_DeviceName);

    QVector<QString> resolutionList = m_pGetResolutionListWorker->getResolutionList();

    if (resolutionList.size() == 0)
    {
        ui->menuResolutionList->clearAction();
        ui->menuMain->setResolutionBtnEnabled(false);
        m_pGetCameraFrameThread->start();
        return;
    }

    ui->menuResolutionList->mSetAction(resolutionList.toList());
    ui->menuMain->setResolutionBtnEnabled(true);

    /* 设置最佳分辨率 */
    int width = 0, height = 0;
    foreach(QString str, resolutionList) {
        QStringList list = str.split("x");
        if (2 != list.size())
            continue;

        int rWidth = QString(list.at(0)).toInt();
        if (width < rWidth) {
            width = rWidth;
            height = QString(list.at(1)).toInt();
        }
    }

    int index = resolutionList.indexOf(QString("%1x%2").arg(width).arg(height));
    if (-1 != index)
        ui->menuResolutionList->setChecked(index, true);

    m_pGetCameraFrameWorker->setResolution(width, height);
    m_pGetCameraFrameThread->start();
}

void MainWidget::onOpenCameraFinished()
{
    qDebug()<<"---------camera open finished.";
    ui->toolbarLeft->setMenuEnabled(true);
}

void MainWidget::onCameraClosed(int ret)
{
    Q_UNUSED(ret)
    qDebug()<<"---------camera closed.";

    ui->toolBarMidRight->setEnabled(false);
    int index = m_pDeviceNameList.indexOf(m_DeviceName);
    if (-1 != index) {
        ui->toolbarRight->setCameraItemChecked(index, false);
        ui->menuDeviceList->setChecked(index, false);
    }

    if (-2 == ret) {
        int index = m_pDeviceNameList.indexOf(m_pGetCameraFrameWorker->getDeviceName());
        if (index < (m_pDeviceNameList.size() - 1)) {
            ++index;
        }else if (index == (m_pDeviceNameList.size() - 1) && m_pDeviceNameList.size() > 1) {
            index = 0;
        }else {
            QPixmap pixmap(this->size());
            this->getTextPixmap(&pixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                                tr("正在查找设备..."), PublicFunction::getScaleSize(200, 30));
            ui->label_display->mSetTipPixmap(pixmap);
            return;
        }

        m_DeviceName = m_pDeviceNameList.at(index);
        ui->menuDeviceList->setChecked(index, true);
        ui->toolbarRight->setCameraItemChecked(index, true);
        qDebug()<<"start next camera:"<<m_DeviceName;
        this->startGetFrameWorker(m_DeviceName);
    }
}

void MainWidget::onNewFrame(QPixmap pixmap)
{
    ui->toolBarMidRight->setEnabled(true);
    if (e_FreezeFrame)
        return;

    if (ui->stackedWidget->currentWidget() == ui->sWidget2) {
        foreach(CustomPushButton_4 *button, m_pDisplayList) {
            if (button->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0) {
                button->mSetPixmap(pixmap);
                break;
            }
        }
    }else {
        if (ui->label_display->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0)
            ui->label_display->mSetPixmap(pixmap);
    }
}

void MainWidget::showDeviceListMenu(bool checked)
{
    if (checked) {
        if (ui->toolbarRight->property("SHOW_WHICH").toString().compare("right") == 0) {
            int y = ui->menuMain->y() + PublicFunction::getScaleSize(30) - ui->menuDeviceList->height()/2;
            y = (y + ui->menuDeviceList->height()) > this->height() ? (this->height() - ui->menuDeviceList->height()) : y;
            ui->menuDeviceList->move(ui->menuMain->x() + ui->menuMain->width() + PublicFunction::getScaleSize(5),
                                     ui->menuMain->y() + PublicFunction::getScaleSize(30) - ui->menuDeviceList->height()/2);
        }else {
            ui->menuDeviceList->move(ui->menuMain->x() - PublicFunction::getScaleSize(5) - ui->menuDeviceList->width(),
                                     ui->menuMain->y() + PublicFunction::getScaleSize(30) - ui->menuDeviceList->height()/2);
        }
        ui->menuDeviceList->show();
        ui->menuDeviceList->raise();
    }else {
        ui->menuDeviceList->hide();
    }
}

void MainWidget::showResolutionListMenu(bool checked)
{
    if (checked) {
        int y = ui->menuMain->y() + PublicFunction::getScaleSize(70) - ui->menuResolutionList->height()/2;
        y = (y + ui->menuResolutionList->height()) > this->height() ? (this->height() - ui->menuResolutionList->height()) : y;
        if (ui->toolbarRight->property("SHOW_WHICH").toString().compare("right") == 0) {
            ui->menuResolutionList->move(ui->menuMain->x() + ui->menuMain->width() + PublicFunction::getScaleSize(5),
                                     y);
        }else {
            ui->menuResolutionList->move(ui->menuMain->x() - PublicFunction::getScaleSize(5) - ui->menuResolutionList->width(),
                                     y);
        }
        ui->menuResolutionList->show();
        ui->menuResolutionList->raise();
    }else {
        ui->menuResolutionList->hide();
    }
}

void MainWidget::showAbout()
{
    ui->menuMain->hide();
    AboutUs *about = new AboutUs(this);
    about->setGeometry(this->rect());
    about->raise();
    about->show();
}

void MainWidget::showControlMenu(bool checked)
{
}

void MainWidget::moveDisplayRect(QPoint pt)
{
    if (ui->stackedWidget->currentWidget() == ui->sWidget2) {
    }else {
        ui->label_display->moveRect(pt);
    }
}

void MainWidget::onDisplayImage(bool bo, int id)
{
     if (ui->stackedWidget->currentWidget() == ui->sWidget1) {
         if (bo) {
             ui->label_display->setProperty(PROPERTY_USE_CAMERA, "false");
             QPixmap pixmap;
             int angle;
             ui->toolbarRight->getPixmap(id, &pixmap, &angle);
             ui->label_display->mSetPixmap(pixmap, angle);
         }else {
             QPixmap pixmap(this->size());
             if (m_pGetCameraFrameWorker->isRunning())
                 this->getTextPixmap(&pixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                                     tr("摄像头连接中..."), PublicFunction::getScaleSize(200, 30));
             else
                 this->getTextPixmap(&pixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                                     tr("未连接摄像头"), PublicFunction::getScaleSize(200, 30));
             ui->label_display->mSetTipPixmap(pixmap);
             ui->label_display->setProperty(PROPERTY_USE_CAMERA, "true");
         }
     }else {
         if (bo) {
             QPixmap pixmap;
             int angle;
             ui->toolbarRight->getPixmap(id, &pixmap, &angle);
             foreach(CustomPushButton_4 *button, m_pDisplayList) {
                 if (button->property(PROPERTY_USE_CAMERA).toString().compare("false") == 0 &&
                         button->property("IS_NULL").toString().compare("true") == 0) {
                     button->setProperty("ID", id);
                     button->setProperty("IS_NULL", "false");
                     button->mSetPixmap(pixmap, angle);
                     return;
                 }
             }
             ui->sWidget2->clearText();
             this->addDisplayWidget(id, false, pixmap, angle);
             if (1 == m_pDisplayList.size())
                 this->addDisplayWidget(-1, false);
         }else {
             this->removeDisplayWidget(id);
         }

     }
}

void MainWidget::onDisplayWidgetClosed()
{

}

void MainWidget::onDisplayWidgetShowFullScreen(bool fullScreen)
{

}

void MainWidget::onEnableContrast(int id)
{
    if (ui->label_display->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0) {
        this->addDisplayWidget(-1, true);
        this->addDisplayWidget(-1, false);
    }else {
        QPixmap pixmap;
        int angle;
        pixmap = ui->label_display->getPixmap();
        angle = ui->label_display->getRotateAngle();
        this->addDisplayWidget(-1, false, pixmap, angle);
        this->addDisplayWidget(id, false);
    }
    ui->graphicsView_1->hide();
    ui->graphicsView_2->show();
    //m_pDisplayList.at(0)->setCheckable(true);
    //m_pDisplayList.at(0)->setChecked(true);
    ui->stackedWidget->setCurrentWidget(ui->sWidget2);
}

void MainWidget::onCancelContrast(QPixmap pixmap, int id, int angle)
{
    if (pixmap.isNull()) {
        QPixmap sPixmap(this->size());
        if (m_pGetCameraFrameWorker->isRunning())
            this->getTextPixmap(&sPixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                                tr("摄像头连接中..."), PublicFunction::getScaleSize(200, 30));
        else
            this->getTextPixmap(&sPixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                                tr("未连接摄像头"), PublicFunction::getScaleSize(200, 30));
        ui->label_display->mSetTipPixmap(sPixmap);
        ui->label_display->setProperty(PROPERTY_USE_CAMERA, "true");
    }else if (id == m_pDisplayList.at(0)->property("ID").toInt()){
        ui->label_display->setProperty(PROPERTY_USE_CAMERA, "false");
        ui->label_display->mSetPixmap(pixmap, angle);
    }
    ui->graphicsView_2->hide();
    ui->graphicsView_2->resetNewScene();
    ui->graphicsView_1->show();
    ui->stackedWidget->setCurrentWidget(ui->sWidget1);
    this->clearContrastDisplay();
    e_Checkable = true;
}

void MainWidget::onStartOCR()
{
    QPixmap pixmap = ui->label_display->getPixmap();
    OCRWidget *ocrWidget = new OCRWidget(pixmap, this);
    ocrWidget->setGeometry(this->rect());
    ocrWidget->show();
}

void MainWidget::onTakingPhoto()
{
    if (m_pGetCameraFrameWorker->isRunning()) {
        QPixmap pixmap = m_pGetCameraFrameWorker->getCurrentFrame();
        ui->toolbarRight->addItem(pixmap);
    }else {
        qDebug()<<"摄像头未打开...";
    }
}

void MainWidget::onLeftRotate()
{
    if (ui->stackedWidget->currentWidget() == ui->sWidget1) {
        if (ui->label_display->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0) {
            if (m_pGetCameraFrameWorker->isRunning()) {
                int angle = m_pGetCameraFrameWorker->getRotateAngle() + 90;
                angle = angle > 360 ? (angle - 360) : angle;
                m_pGetCameraFrameWorker->setRotateAngle(angle);
            }
        }else {
            int angle = ui->label_display->getRotateAngle() + 90;
            angle = angle > 360 ? (angle - 360) : angle;
            ui->label_display->setRotateAngle(angle);
            ui->toolbarRight->rotateItem(ui->label_display->property("ID").toInt(), angle);
        }
    }else {
        foreach(CustomPushButton_4 *button, m_pDisplayList) {
            if (button->isChecked()) {
                if (button->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0) {
                    if (m_pGetCameraFrameWorker->isRunning()) {
                        int angle = m_pGetCameraFrameWorker->getRotateAngle() + 90;
                        angle = angle > 360 ? (angle - 360) : angle;
                        m_pGetCameraFrameWorker->setRotateAngle(angle);
                    }
                }else {
                    int angle = button->getRotateAngle() + 90;
                    angle = angle > 360 ? (angle - 360) : angle;
                    button->setRotateAngle(angle);
                    ui->toolbarRight->rotateItem(button->property("ID").toInt(), angle);
                }
                break;
            }
        }
    }
}

void MainWidget::onRightRotate()
{
    if (ui->stackedWidget->currentWidget() == ui->sWidget1) {
        if (ui->label_display->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0) {
            if (m_pGetCameraFrameWorker->isRunning()) {
                int angle = m_pGetCameraFrameWorker->getRotateAngle() - 90;
                angle = angle < -360 ? (angle + 360) : angle;
                m_pGetCameraFrameWorker->setRotateAngle(angle);
            }else {
                int angle = ui->label_display->getRotateAngle() - 90;
                angle = angle < -360 ? (angle + 360) : angle;
                m_pGetCameraFrameWorker->setRotateAngle(angle);
            }
        }
    }else {
        foreach(CustomPushButton_4 *button, m_pDisplayList) {
            if (button->isChecked()) {
                if (button->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0) {
                    if (m_pGetCameraFrameWorker->isRunning()) {
                        int angle = m_pGetCameraFrameWorker->getRotateAngle() + 90;
                        angle = angle < -360 ? (angle + 360) : angle;
                        m_pGetCameraFrameWorker->setRotateAngle(angle);
                    }
                }else {
                    int angle = button->getRotateAngle() + 90;
                    angle = angle < -360 ? (angle + 360) : angle;
                    button->setRotateAngle(angle);
                    ui->toolbarRight->rotateItem(button->property("ID").toInt(), angle);
                }
                break;
            }
        }
    }
}

void MainWidget::onZoomIn()
{
    if (ui->stackedWidget->currentWidget() == ui->sWidget1) {
        ui->label_display->zoomIn();
    }else {
        foreach(CustomPushButton_4 *button, m_pDisplayList) {
            if (button->isChecked()) {
                button->zoomIn();
                break;
            }
        }
    }
}

void MainWidget::onZoomOut()
{
    if (ui->stackedWidget->currentWidget() == ui->sWidget1) {
        ui->label_display->zoomOut();
    }else {
        foreach(CustomPushButton_4 *button, m_pDisplayList) {
            if (button->isChecked()) {
                button->zoomOut();
                break;
            }
        }
    }
}

void MainWidget::onResolutionChanged(QString resolution)
{
    qDebug()<<"resolution change----------1";
    this->hideMenu();
    ui->toolbarLeft->setMenuEnabled(false);
    QStringList list = resolution.split("x");
    if (2 != list.size())
        return;

    qDebug()<<"resolution change----------1-1";
    int width = QString(list.at(0)).toInt();
    int height = QString(list.at(1)).toInt();
    if (m_pGetCameraFrameWorker->isRunning()) {
        m_pGetCameraFrameWorker->stopRunning();
        m_pGetCameraFrameThread->quit();
        m_pGetCameraFrameThread->wait();
    }
    qDebug()<<"resolution change----------1-2";
    m_pGetCameraFrameWorker->setResolution(width, height);
    m_pGetCameraFrameThread->start();
    qDebug()<<"resolution change----------1-3";
}

void MainWidget::onReforeBtnClicked()
{
    this->hideMenu();
    if (ui->toolbarRight->property("SHOW_WHICH").toString().compare("right") == 0) {
        ui->toolbarRight->move(QPoint(PublicFunction::getScaleSize(16),
                                     this->height() - PublicFunction::getScaleSize(16) + ui->toolBarMidLeft->getBorder() - ui->toolbarRight->height()));
        ui->toolbarLeft->move(QPoint(this->width() - PublicFunction::getScaleSize(16) - ui->toolbarLeft->width(),
                                      this->height() - PublicFunction::getScaleSize(16) + ui->toolBarMidLeft->getBorder() - ui->toolbarLeft->height()));
        ui->toolbarRefore_left->move(QPoint(ui->toolbarRight->x() + ui->toolbarRight->width(),
                                            this->height() - PublicFunction::getScaleSize(16) + ui->toolbarRefore_left->getBorder() - ui->toolbarRefore_left->height()));
        ui->toolbarRefore_right->move(QPoint(ui->toolbarLeft->x() - ui->toolbarRefore_right->width(),
                                            this->height() - PublicFunction::getScaleSize(16) +
                                             ui->toolbarRefore_right->getBorder() - ui->toolbarRefore_right->height()));
        ui->toolbarRight->setProperty("SHOW_WHICH", "left");
    }else {
        ui->toolbarLeft->move(QPoint(PublicFunction::getScaleSize(16),
                                     this->height() - PublicFunction::getScaleSize(16) + ui->toolBarMidLeft->getBorder() - ui->toolbarLeft->height()));
        ui->toolbarRefore_left->move(QPoint(ui->toolbarLeft->x() + ui->toolbarLeft->width(),
                                            this->height() - PublicFunction::getScaleSize(16) + ui->toolbarRefore_left->getBorder() - ui->toolbarRefore_left->height()));
        ui->toolbarRight->move(QPoint(this->width() - PublicFunction::getScaleSize(16) - ui->toolbarRight->width(),
                                      this->height() - PublicFunction::getScaleSize(16) + ui->toolbarRight->getBorder() - ui->toolbarRight->height()));
        ui->toolbarRefore_right->move(QPoint(ui->toolbarRight->x() - ui->toolbarRefore_right->width(),
                                            this->height() - PublicFunction::getScaleSize(16) +
                                             ui->toolbarRefore_right->getBorder() - ui->toolbarRefore_right->height()));
        ui->toolbarRight->setProperty("SHOW_WHICH", "right");
    }
}

void MainWidget::onCameraChecked(bool checked, int index)
{
    QString name = m_pDeviceNameList.value(index, QString());
    if (name.isEmpty())
        return;

    QPixmap pixmap(ui->label_display->size());
    this->getTextPixmap(&pixmap, QColor(20, 20, 22), QPixmap("://images/kongtai@2x.png"), PublicFunction::getScaleSize(68, 82),
                        tr("摄像头连接中..."), PublicFunction::getScaleSize(200, 30));
    if (checked) {
        if (m_pGetCameraFrameWorker->isRunning()) {
            m_pGetCameraFrameWorker->stopRunning();
            m_pGetCameraFrameThread->quit();
            m_pGetCameraFrameThread->wait();
            if (ui->stackedWidget->currentWidget() == ui->sWidget1)
                ui->label_display->mSetTipPixmap(pixmap);
            else {
                bool addNewWidget = true;
                foreach(CustomPushButton_4 *button, m_pDisplayList) {
                    if (button->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0)
                    {
                        addNewWidget = false;
                        break;
                    }
                }
                if (addNewWidget)
                    this->addDisplayWidget(-1, true);
            }
        }
        ui->menuDeviceList->setChecked(index, true);
        ui->toolbarRight->setCameraItemChecked(index, true);
        m_DeviceName = name;
        m_pGetResolutionListWorker->setDeviceName(m_DeviceName);
        m_pGetResolutionListThread->start();
    }else {
        qDebug()<<"--------------"<<m_pGetCameraFrameWorker->getDeviceName()<<name;
        if (m_pGetCameraFrameWorker->isRunning() && m_pGetCameraFrameWorker->getDeviceName().compare(name) == 0) {
            m_pGetCameraFrameWorker->stopRunning();
            m_pGetCameraFrameThread->quit();
            m_pGetCameraFrameThread->wait();
            ui->menuDeviceList->setChecked(index, false);
            ui->toolbarRight->setCameraItemChecked(index, false);
            if (ui->stackedWidget->currentWidget() == ui->sWidget1)
                ui->label_display->mSetTipPixmap(pixmap);
            else {
                foreach(CustomPushButton_4 *button, m_pDisplayList) {
                    if (button->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0)
                    {
                        button->setProperty(PROPERTY_USE_CAMERA, "false");
                        this->removeDisplayWidget(button);
                        break;
                    }
                }
            }
        }
    }
}





