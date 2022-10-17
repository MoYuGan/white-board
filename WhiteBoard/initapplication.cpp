#include "initapplication.h"
#include "ui_initapplication.h"

#define CURRENTVERSIONS 100006
InitApplication::InitApplication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InitApplication)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->initWidget();

    m_pHttpThread = new DB_HttpThread(this);
    qDebug()<< " CURRENTVERSIONS " << CURRENTVERSIONS <<Qt::endl;
    connect(m_pHttpThread, &DB_HttpThread::httpThreadFinished, this, &InitApplication::onHttpThreadFinished);
}

InitApplication::~InitApplication()
{
    delete ui;
}

void InitApplication::show()
{
    QWidget::show();
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    this->move(QPoint((screenRect.width() - this->width())/2,
                    (screenRect.height() - this->height())/2));
}

int InitApplication::checkUpdate()
{
    QEventLoop loop;
    connect(this, &InitApplication::quitLoop, &loop, &QEventLoop::quit);
    //检查版本更新
    m_pHttpThread->start(HttpFunction::CheckUpdate);
    loop.exec();
    return m_Ret;
}

void InitApplication::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(this->rect(), QPixmap(":/images/start/bg@2x.png"));
}

void InitApplication::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);

    QSize size = Public_Function::getScaleSize(QSize(584, 408));
    this->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(32, 32));
    ui->label_logo->setFixedSize(size);
    ui->label_logo->setScaledContents(true);
    ui->label_logo->setPixmap(QPixmap(":/images/start/icon@2x.png"));

    ui->horizontalLayout->setContentsMargins(Public_Function::getScaleSize(20), 0,
                                           Public_Function::getScaleSize(20), Public_Function::getScaleSize(16));
    ui->horizontalLayout->setSpacing(Public_Function::getScaleSize(16));

    QFont font = Public_Function::getFont(13);
    ui->label_applicationName->setFont(font);
    ui->label_tip->setFont(font);

    //    this->setAutoFillBackground(true);
    //    QPalette palette = this->palette();
    //    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/start/bg@2x.png").scaled(this->size())));
    //    this->setPalette(palette);
}

void InitApplication::onHttpThreadFinished(HttpFunction fun, QVariant variant)
{
    Q_UNUSED(fun)

    m_pData = variant.value<_HttpRetData>();
    qDebug()<< "m_pData " << m_pData.state <<Qt::endl;
    //检查更新返回
    if (1 == m_pData.state) {
        if (m_pData.variant.value<_CheUpdaData>().version.toInt() > CURRENTVERSIONS) {
            //打开更新面板
            VersionUpdate *updatePanel = new VersionUpdate(m_pData.variant.value<_CheUpdaData>().downloadUrl,
                                                                 m_pData.variant.value<_CheUpdaData>().fileName +"."+ m_pData.variant.value<_CheUpdaData>().fileStyle,this);
            connect(updatePanel, &VersionUpdate::closePanel,this, [=](int ret){
                updatePanel->deleteLater();
                m_Ret = ret;
                //m_pFrameCover->hide();
                emit quitLoop();
            });
            //m_pFrameCover->show();
            //m_pFrameCover->raise();
            updatePanel->move(QPoint((this->width() - updatePanel->width())/2, (this->height() - updatePanel->height())/2));
            updatePanel->show();
            updatePanel->raise();
        }else {
            m_Ret = 0;
            emit quitLoop();
        }
    }else {
        m_Ret =-2;
        emit quitLoop();
    }
}
