#include "getupdatezip.h"
#include "ui_getupdatezip.h"

GetUpdateZip::GetUpdateZip(const QString &version, const QString &url, QWidget *parent) :
    QWidget(parent), ui(new Ui::GetUpdateZip), m_Url(url)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->label_version->setText(version);
    this->initWidget();
    this->resizeWidget();
}


GetUpdateZip::~GetUpdateZip()
{
    delete ui;
}

void GetUpdateZip::show()
{
    QRect rect = QGuiApplication::primaryScreen()->geometry();
    this->move((rect.width() - this->width())/2, (rect.height() - this->height())/2);
    QWidget::show();
}

int GetUpdateZip::exec()
{
    m_Ret = 0;
    m_Loop.exec();
    return m_Ret;
}

void GetUpdateZip::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(this->rect(), QPixmap(":/images/bf@2x.png"));
}

void GetUpdateZip::initWidget()
{
    ui->label_slider->hide();
    ui->label_downloadTip->hide();
    ui->label_progress->hide();
    ui->label_finishTip->hide();
    ui->pushButton_restart->hide();

    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &GetUpdateZip::onBtnCancelClicked);
    connect(ui->pushButton_update, &QPushButton::clicked, this, &GetUpdateZip::onBtnUpdateClicked);
    connect(ui->pushButton_restart, &QPushButton::clicked, this, [=]{m_Loop.quit();});
}

void GetUpdateZip::resizeWidget()
{
    this->setFixedSize(PublicFunction::getScaleSize(584, 473));
    ui->verticalLayout->setContentsMargins(0, PublicFunction::getScaleSize(65), 0, PublicFunction::getScaleSize(30));
    ui->verticalLayout->setSpacing(PublicFunction::getScaleSize(10));
    ui->horizontalLayout->setContentsMargins(PublicFunction::getScaleSize(20), PublicFunction::getScaleSize(16), PublicFunction::getScaleSize(16), 0);
    ui->horizontalLayout->setSpacing(PublicFunction::getScaleSize(16));
    ui->horizontalLayout_2->setContentsMargins(PublicFunction::getScaleSize(40), PublicFunction::getScaleSize(37), 0, 0);
    ui->horizontalLayout_3->setSpacing(PublicFunction::getScaleSize(20));
    if (!ui->pushButton_restart->isHidden())
        ui->horizontalLayout_4->setContentsMargins(0, 0, 0, PublicFunction::getScaleSize(12));

    ui->label_logo->setFixedSize(PublicFunction::getScaleSize(32, 32));
    ui->label_slider->setFixedSize(PublicFunction::getScaleSize(424, 14));
    ui->pushButton_update->setFixedSize(PublicFunction::getScaleSize(96, 38));
    ui->pushButton_cancel->setFixedSize(PublicFunction::getScaleSize(96, 38));
    ui->pushButton_restart->setFixedSize(PublicFunction::getScaleSize(96, 38));

    QFont font = PublicFunction::getFont(16);
    ui->label_appName->setFont(font);
    font = PublicFunction::getFont(32);
    font.setWeight(QFont::Bold);
    ui->label_version->setFont(font);
    font = PublicFunction::getFont(14);
    ui->label_downloadTip->setFont(font);
    ui->pushButton_update->setFont(font);
    ui->pushButton_cancel->setFont(font);
    ui->pushButton_restart->setFont(font);
    font = PublicFunction::getFont(22);
    ui->label_progress->setFont(font);
    font = PublicFunction::getFont(18);
    ui->label_finishTip->setFont(font);

    QString style = QString("QPushButton{ background: rgb(20,134,250); color: white; border-radius: %1px;}").arg(PublicFunction::getScaleSize(4));
    ui->pushButton_update->setStyleSheet(style);
    ui->pushButton_cancel->setStyleSheet(style);
    ui->pushButton_restart->setStyleSheet(style);
}

void GetUpdateZip::downloadFile()
{
    QEventLoop *_loop = new QEventLoop;
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    connect(manager, &QNetworkAccessManager::finished, _loop, &QEventLoop::quit);

    QUrl url;
    QNetworkRequest request;

    url.setUrl(m_Url);         //下载网址
    request.setUrl(url);
    m_pNetworkReply = manager->get(request);
    qDebug() << "support openssl:" << QSslSocket::supportsSsl();
    //写入文件
    connect(m_pNetworkReply, &QNetworkReply::readyRead, this, &GetUpdateZip::readReplyData, Qt::DirectConnection);
    //下载进度
    connect(m_pNetworkReply, &QNetworkReply::downloadProgress, this, &GetUpdateZip::onDownloadProgress, Qt::DirectConnection);

    _loop->exec();
    m_pNetworkReply->abort();
    manager->deleteLater();
}

void GetUpdateZip::onBtnUpdateClicked()
{
    ui->pushButton_update->hide();
    ui->pushButton_cancel->hide();
    ui->label_slider->show();
    ui->label_downloadTip->show();
    ui->label_progress->show();

    m_SaveFile = QString("%1/update_%2.tar.gz").arg(QCoreApplication::applicationDirPath(), QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    m_DownLoadSuccess = false;
    this->downloadFile();


    if (m_DownLoadSuccess) { //下载成功
        m_Ret = 1;
        QProcess process;
        QStringList args = QStringList() << "-zxvmf" << m_SaveFile << "-C" << "/";
        int ret = process.execute("tar", args);
        if (-2 == ret || -1 == ret)
            m_Ret = -1;
    }
    if (1 != m_Ret) {
        ui->label_finishTip->setText(tr("升级失败"));
        ui->label_finishTip->setStyleSheet(QString("QLabel{color:red;}"));
        ui->pushButton_restart->setText(tr("确定"));
    }

    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, this, [=](){
        timer->stop();
        timer->deleteLater();
        ui->label_slider->hide();
        ui->label_downloadTip->hide();
        ui->label_progress->hide();
        ui->label_finishTip->show();
        ui->pushButton_restart->show();
        ui->horizontalLayout_4->setContentsMargins(0, 0, 0, PublicFunction::getScaleSize(12));
    });
    timer->start(200);
}

void GetUpdateZip::onBtnCancelClicked()
{
    m_Loop.quit();
}

void GetUpdateZip::readReplyData()
{
    QByteArray bytes = m_pNetworkReply->readAll();
    QFile file(m_SaveFile);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        file.write(bytes);
    }
    file.close();
}

void GetUpdateZip::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesReceived == bytesTotal)
        m_DownLoadSuccess = true;
    ui->label_slider->mSizeChanged(bytesReceived, bytesTotal);
    qreal p = (qreal)bytesReceived / (qreal)bytesTotal * 100;
    ui->label_progress->setText(QString("%1\%").arg(QString::number(p)));
}

