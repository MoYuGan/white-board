#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QSysInfo>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkInterface>

#ifdef Q_OS_LINUX
#include "X11/extensions/shape.h"
#include <QX11Info>
#endif

#include<QJsonDocument>
#include <QJsonValue>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); // | Qt::WindowStaysOnTopHint
    this->setWindowIcon(QIcon(":/images/ICO/application.ico"));
    this->installEventFilter(this);

    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);

    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    this->setGeometry(screenRect);
    g_ScreenWidth = screenRect.width();
    g_ScreenHeight = screenRect.height();

    this->initWidget();
    this->resizeWidget();

    begintime =QDate::currentDate().toString("yyyy-MM-dd") +" "+QTime::currentTime().toString();
    begintime1 = QDateTime::fromString(begintime, "yyyy-MM-dd HH:mm:ss");
}

MainWidget::~MainWidget()
{
    delete ui;
}

bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::WindowActivate)
        this->showFullScreen();
    else if (event->type() == QEvent::MouseButtonPress && watched == this) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos = mouseEvent->pos();
        if ((m_PenPanel->isHidden() || !m_PenPanel->geometry().contains(pos)) &&
                (m_ErasePanel->isHidden() || !m_ErasePanel->geometry().contains(pos)))
            this->hidePanel();
    }else if (event->type() == QEvent::MouseButtonPress && watched == m_MainBtn) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        m_MousePressedPoint = mouseEvent->pos();

        if ((m_PenPanel->isHidden() || !m_PenPanel->geometry().contains(m_MousePressedPoint)) &&
                (m_ErasePanel->isHidden() || !m_ErasePanel->geometry().contains(m_MousePressedPoint)))
            this->hidePanel();
    }else if (event->type() == QEvent::MouseMove && watched == m_MainBtn) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos = mouseEvent->globalPos();
//        if (!m_ToolHasMoved && m_SelectBtn->isChecked()) {
//            this->onSelectBtnToggled(false);
//        }
        m_ToolHasMoved = true;
        m_ToolFrame->move(pos.x() - m_MousePressedPoint.x(), pos.y() - m_MousePressedPoint.y());
    }else if (event->type() == QEvent::MouseButtonRelease && watched == m_MainBtn) {
        if (m_ToolHasMoved && m_SelectBtn->isChecked()) {
            this->onSelectBtnToggled(true);
        }
        m_ToolHasMoved = false;
    }


    return QWidget::eventFilter(watched, event);
}

QString MainWidget::MAC()
{
    QString strMacAddress = "";
       QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
       foreach (QNetworkInterface iface, list)
       {
           if(iface.flags().testFlag(QNetworkInterface::IsUp) && iface.flags().testFlag(QNetworkInterface::IsRunning) && !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
           {
               strMacAddress = iface.hardwareAddress();
               qInfo() << "strMacAddress:" << iface.hardwareAddress() << Qt::endl;
               break;
           }
       }
       return strMacAddress;
}

DrawingBoard* MainWidget::newBoard()
{
    DrawingBoard* board = new DrawingBoard(this);
    QObject::connect(board, &DrawingBoard::boardClosed, this, &MainWidget::onBoardClose);
    QObject::connect(board, &DrawingBoard::showMinimizedSignal, this, &MainWidget::onShowMinimized);
    QObject::connect(board, &DrawingBoard::showMaximizedSignal, this, &MainWidget::onShowMaximized);
    ui->stackedWidget->addWidget(board);
    ui->stackedWidget->setCurrentWidget(board);
    board->resizeWidget();
    board->show();
    return board;
}

void MainWidget::initWidget()
{
    this->setLayout(ui->verticalLayout);
    ui->verticalLayoutWidget->hide();
    m_Board = this->newBoard();

    m_MinWhiteboard = new MinWhiteboard();
    ui->stackedWidget->addWidget(m_MinWhiteboard);

    m_ToolFrame = new QFrame(this);
    m_MainBtn = new PushButton_7(QPixmap(":/images/minimize/logo@2x.png"), QPixmap(), QPixmap(":/images/minimize/logo2@2x.png"), m_ToolFrame);
    m_MainBtn->setCheckable(true);
    m_MainBtn->setChecked(true);
    m_SelectBtn = new PushButton_7(QPixmap(":/images/minimize/xuanze@2x.png"), QPixmap(":/images/minimize/xuanze2@2x.png"), QPixmap(), m_ToolFrame);
    m_SelectBtn->setCheckable(true);
    m_SelectBtn->setHoverStyle(true);
    m_PenBtn = new PushButton_7(QPixmap(":/images/minimize/bichu@2x.png"), QPixmap(":/images/minimize/bichu2@2x.png"), QPixmap(), m_ToolFrame);
    m_PenBtn->setCheckable(true);
    m_PenBtn->setHoverStyle(true);
    m_EraseBtn = new PushButton_7(QPixmap(":/images/minimize/cachu@2x.png"), QPixmap(":/images/minimize/cachu2@2x.png"), QPixmap(), m_ToolFrame);
    m_EraseBtn->setCheckable(true);
    m_EraseBtn->setHoverStyle(true);
    m_ScreenshotsBtn = new PushButton_7(QPixmap(":/images/minimize/jietu@2x.png"), QPixmap(), QPixmap(), m_ToolFrame);
    m_ScreenshotsBtn->setHoverStyle(true);
    m_FullScreenBtn = new PushButton_7(QPixmap(":/images/minimize/quanping@2x.png"), QPixmap(), QPixmap(), m_ToolFrame);
    m_FullScreenBtn->setHoverStyle(true);
    m_ToolFrame->hide();

    m_MainBtn->installEventFilter(this);

    m_CheckableBtnGroup = new QButtonGroup(this);
    m_CheckableBtnGroup->setExclusive(true);
    m_CheckableBtnGroup->addButton(m_SelectBtn);
    m_CheckableBtnGroup->addButton(m_PenBtn);
    m_CheckableBtnGroup->addButton(m_EraseBtn);

    m_Animation = new QPropertyAnimation(m_ToolFrame, "geometry");
    m_Animation->setDuration(20);

    m_PenPanel = new PenPanel(this);
    m_PenPanel->hide();
    m_PenPanel->hideOtherPen();
    m_PenPanel->isMiniBoard(true);
    connect(m_PenPanel, &PenPanel::penColorChanged, this, [=](QColor color) { e_MinBoardPenColor = color; });
    connect(m_PenPanel, &PenPanel::penSizeChanged, this, [=](int size) { e_MinBoardPenSize = size;});
    m_PenPanel->setCheckedColor(3);
    m_PenPanel->setCheckedSize(2);
    m_PenPanel->setLockBtnVisable(false);

    m_ErasePanel = new ErasePanel(this);
    connect(m_ErasePanel, &ErasePanel::eraseSizeChanged, this, [=](QSize size) { e_MinBoardEraseSize = size;});
    connect(m_ErasePanel, &ErasePanel::clearSignal, this, [=](){ m_MinWhiteboard->clearScene(); });
    m_ErasePanel->hide();
    m_ErasePanel->setCheckedSize(1);

    connect(QGuiApplication::primaryScreen(), &QScreen::geometryChanged, this, &MainWidget::onScreenResize);
    connect(m_MainBtn, &PushButton_7::clicked, this, &MainWidget::animationStart);
    connect(m_SelectBtn, &PushButton_7::toggled, this, &MainWidget::onSelectBtnToggled);
    connect(m_PenBtn, &PushButton_7::toggled, this, &MainWidget::onPenBtnToggled);
    connect(m_PenBtn, &PushButton_7::checkedClicked, this, &MainWidget::onPenBtnCheckedClicked);
    connect(m_EraseBtn, &PushButton_7::toggled, this, &MainWidget::onEraseBtnToggled);
    connect(m_EraseBtn, &PushButton_7::checkedClicked, this, &MainWidget::onEraseBtnCheckedClicked);
    connect(m_ScreenshotsBtn, &PushButton_7::clicked, this, &MainWidget::onScreenShots);
    connect(m_FullScreenBtn, &PushButton_7::clicked, this, &MainWidget::onShowFullScreen);
}

void MainWidget::resizeWidget()
{
    m_Board->resizeWidget();
    m_MinWhiteboard->resizeWidget();
    m_PenPanel->resizeWidget();
    m_ErasePanel->resizeWidget();

    QSize size = Public_Function::getScaleSize(70, 70);
    m_MainBtn->setFixedSize(size);
    size = Public_Function::getScaleSize(54, 54);
    m_SelectBtn->setFixedSize(size);
    m_PenBtn->setFixedSize(size);
    m_EraseBtn->setFixedSize(size);
    m_ScreenshotsBtn->setFixedSize(size);
    m_FullScreenBtn->setFixedSize(size);

    int spacing = Public_Function::getScaleSize(13);
    m_MaxWidth = m_MainBtn->width() + size.width() * 5 + spacing * 5;
    if (m_MainBtn->isChecked())
        m_ToolFrame->resize(m_MaxWidth, m_MainBtn->height());
    else
        m_ToolFrame->resize(m_MainBtn->width(), m_MainBtn->height());

    int y = (m_MainBtn->height() - m_SelectBtn->height())/2;
    m_SelectBtn->move(m_MainBtn->width() + spacing, y);
    m_PenBtn->move(m_SelectBtn->x() + m_SelectBtn->width() + spacing, y);
    m_EraseBtn->move(m_PenBtn->x() + m_PenBtn->width() + spacing, y);
    m_ScreenshotsBtn->move(m_EraseBtn->x() + m_EraseBtn->width() + spacing, y);
    m_FullScreenBtn->move(m_ScreenshotsBtn->x() + m_ScreenshotsBtn->width() + spacing, y);
}

void MainWidget::hidePanel()
{
    if (!m_PenPanel->isHidden())
        m_PenPanel->hide();
    if (!m_ErasePanel->isHidden())
        m_ErasePanel->hide();
}

void MainWidget::sendRunMessage()
{
    QUrl url;
    QNetworkReply *reply;
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    endtime =QDate::currentDate().toString("yyyy-MM-dd") +" "+QTime::currentTime().toString();
    endtime1 = QDateTime::fromString(endtime, "yyyy-MM-dd HH:mm:ss");
    qint64 seconds = begintime1.secsTo(endtime1);
    MsgWidget us;
    QEventLoop _loop;
    QTimer _timer;
    connect(&_timer, &QTimer::timeout, &_loop,&QEventLoop::quit);

    QNetworkRequest netReq;
    url.setUrl("https://test-classbrand.amdox.com.cn/cloudApi/apiPropagate/info/record/insert");
    netReq.setUrl(url);
    netReq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");//post请求设置为json，才能发送josn格式文件
    //创建一个Json对象,这个Json对象就是要发送的内容，展开成Json数据如上所示
    QJsonObject jsonObj;
    jsonObj.insert("deviceType", "1");
    jsonObj.insert("wiredMac", MAC());
    jsonObj.insert("osCode",QSysInfo::productVersion().toInt());
    jsonObj.insert("softNum",us.getVersion());
    jsonObj.insert("beginTime",begintime);
    jsonObj.insert("endTime",endtime);
    jsonObj.insert("runTime",QString("%1").arg(seconds/60));

    //创建一个QJsonDocument类对象，jsonDoc可以将Json格式数据转换之后，使用post发送
    QJsonDocument jsonDoc = QJsonDocument(jsonObj);
    QByteArray post_data = jsonDoc.toJson(QJsonDocument::Compact);
    reply  = manager->post(netReq,post_data);
    _timer.start(500);
    // 阻塞
    _loop.exec();
    QByteArray bytes = reply->readAll();
    qDebug() << " reply " << bytes <<Qt::endl;
}

void MainWidget::onBoardClose(int i)
{
    switch(i) {
    case 1: {//新建白板
        m_Board->closeMiniBoardThread();
        DrawingBoard *board = this->newBoard();
        ui->stackedWidget->removeWidget(m_Board);
        m_Board->deleteLater();
        m_Board = board;
    }break;
    case 2: {   //重启程序
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        QApplication::exit(0);
    }break;
    default: {  //直接关闭程序
        m_Board->closeMiniBoardThread();
        sendRunMessage();
        QApplication::exit(0);
    }break;
    }
}

void MainWidget::onShowMinimized()
{
    ui->stackedWidget->setCurrentWidget(m_MinWhiteboard);

    m_ToolFrame->move(Public_Function::getScaleSize(142), this->height() - Public_Function::getScaleSize(80) - m_ToolFrame->height());
    m_ToolFrame->show();
    if (!m_SelectBtn->isChecked())
        m_SelectBtn->setChecked(true);
}

void MainWidget::onShowMaximized()
{
    onShowFullScreen();
}

void MainWidget::onScreenResize()
{
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    g_ScreenWidth = screenRect.width();
    g_ScreenHeight = screenRect.height();
    this->resizeWidget();
}

void MainWidget::animationStart()
{
    this->hidePanel();
    QRect rect = m_ToolFrame->geometry();
    if (m_MainBtn->isChecked()) {
        m_Animation->setStartValue(rect);
        m_Animation->setEndValue(QRect(rect.x(), rect.y(), m_MaxWidth, m_ToolFrame->height()));
    }else {
        m_Animation->setStartValue(rect);
        m_Animation->setEndValue(QRect(rect.x(), rect.y(), m_MainBtn->width(), m_ToolFrame->height()));
    }
    m_Animation->start();
}

void MainWidget::onSelectBtnToggled(bool checked)
{
#ifdef Q_OS_LINUX
    XRectangle* myrect = new XRectangle;
#endif
    if (checked) {
        m_MinWhiteboard->setTool(MinWhiteBoard_View::NoTool);
#ifdef Q_OS_LINUX
        XShapeCombineRectangles(QX11Info::display(), this->winId(), ShapeInput, 0, 0, NULL, 0, ShapeSet, YXBanded);
        myrect->x = m_ToolFrame->x() + m_MainBtn->x();
        myrect->y = m_ToolFrame->y() + m_MainBtn->y();
        myrect->width = m_MainBtn->width();
        myrect->height = m_MainBtn->height();
        XShapeCombineRectangles(QX11Info::display(), this->winId(), ShapeInput, 0, 0, myrect, 1, ShapeSet, YXBanded);
        myrect->x = m_ToolFrame->x() + m_SelectBtn->x();
        myrect->y = m_ToolFrame->y() + m_SelectBtn->y();
        myrect->width = m_SelectBtn->width();
        myrect->height = m_SelectBtn->height();
        XShapeCombineRectangles(QX11Info::display(), this->winId(), ShapeInput, 0, 0, myrect, 1, ShapeUnion, YXBanded);
        myrect->x = m_ToolFrame->x() + m_PenBtn->x();
        myrect->y = m_ToolFrame->y() + m_PenBtn->y();
        myrect->width = m_PenBtn->width();
        myrect->height = m_PenBtn->height();
        XShapeCombineRectangles(QX11Info::display(), this->winId(), ShapeInput, 0, 0, myrect, 1, ShapeUnion, YXBanded);
        myrect->x = m_ToolFrame->x() + m_EraseBtn->x();
        myrect->y = m_ToolFrame->y() + m_EraseBtn->y();
        myrect->width = m_EraseBtn->width();
        myrect->height = m_EraseBtn->height();
        XShapeCombineRectangles(QX11Info::display(), this->winId(), ShapeInput, 0, 0, myrect, 1, ShapeUnion, YXBanded);
        myrect->x = m_ToolFrame->x() + m_ScreenshotsBtn->x();
        myrect->y = m_ToolFrame->y() + m_ScreenshotsBtn->y();
        myrect->width = m_ScreenshotsBtn->width();
        myrect->height = m_ScreenshotsBtn->height();
        XShapeCombineRectangles(QX11Info::display(), this->winId(), ShapeInput, 0, 0, myrect, 1, ShapeUnion, YXBanded);
        myrect->x = m_ToolFrame->x() + m_FullScreenBtn->x();
        myrect->y = m_ToolFrame->y() + m_FullScreenBtn->y();
        myrect->width = m_FullScreenBtn->width();
        myrect->height = m_FullScreenBtn->height();
        XShapeCombineRectangles(QX11Info::display(), this->winId(), ShapeInput, 0, 0, myrect, 1, ShapeUnion, YXBanded);
#endif
    }else {
#ifdef Q_OS_LINUX
        myrect->x = 0;
        myrect->y = 0;
        myrect->width = this->width();
        myrect->height = this->height();
        XShapeCombineRectangles(QX11Info::display(), this->winId(), ShapeInput, 0, 0, myrect, 1, ShapeSet, YXBanded);
#endif
    }
    m_ErasePanel->hide();
    delete myrect;
}

void MainWidget::onPenBtnToggled(bool checked)
{
    if (checked) {
        this->hidePanel();
        m_MinWhiteboard->setTool(MinWhiteBoard_View::Pen);
    }
}

void MainWidget::onEraseBtnToggled(bool checked)
{
    if (checked) {
        this->hidePanel();
        m_MinWhiteboard->setTool(MinWhiteBoard_View::Erase);
    }
}

void MainWidget::onPenBtnCheckedClicked()
{
    if (m_PenPanel->isHidden()) {
        //int x = m_ToolFrame->x() + m_PenBtn->x() + m_PenBtn->width()/2;
        int y = m_ToolFrame->y() - Public_Function::getScaleSize(10) - m_PenPanel->height();
        m_PenPanel->move(QPoint(m_ToolFrame->x(), y));
        m_PenPanel->show();
    }else
        m_PenPanel->hide();
}

void MainWidget::onEraseBtnCheckedClicked()
{
    if (m_ErasePanel->isHidden()) {
        int x = m_ToolFrame->x() + m_EraseBtn->x() + m_EraseBtn->width()/2;
        int y = m_ToolFrame->y() - Public_Function::getScaleSize(10) - m_ErasePanel->height();
        m_ErasePanel->move(QPoint(x - m_ErasePanel->width()/2, y));
        m_ErasePanel->show();
    }else
        m_ErasePanel->hide();
}

void MainWidget::onScreenShots()
{
    this->hidePanel();
    m_Board->screenShots();
}

void MainWidget::onShowFullScreen()
{
    this->hidePanel(); 
    if (m_SelectBtn->isChecked()) {
        m_CheckableBtnGroup->setExclusive(false);
        m_SelectBtn->setChecked(false);
        m_CheckableBtnGroup->setExclusive(true);
    }
    ui->stackedWidget->setCurrentWidget(m_Board);
    m_ToolFrame->hide();

}

