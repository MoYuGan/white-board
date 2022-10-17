#include "applicationstart.h"
#include "ui_applicationstart.h"

#include <QtDebug>

#define AMDOX_BOOTH_VERSION 100000
#define URL_HEADER "http://192.168.5.21:8081"
//#define URL_HEADER "https://new-version.amdox.com.cn"
#define UPDATE_URL "version/terminalproduct/getLatestVersion?name=å±å°è½¯ä»¶&perms=windows:showbooth:app&versionCode=100000&ipAddress="

ApplicationStart::ApplicationStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationStart)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->resizeWidget();
}

ApplicationStart::~ApplicationStart()
{
    delete ui;
}

void ApplicationStart::show()
{
    QRect rect = QGuiApplication::primaryScreen()->geometry();
    this->move((rect.width() - this->width())/2, (rect.height() - this->height())/2);
    QWidget::show();
}

//检查版本更新
bool ApplicationStart::checkUpdate()
{
    _HttpRetData data = this->getVersionRequest();
    if (1 == data.state) {
        _CheUpdaData cData = data.variant.value<_CheUpdaData>();
        qDebug()<<"get application version:"<<cData.version.toInt();
        int version = cData.version.toInt();
        if (version > AMDOX_BOOTH_VERSION) {
            m_Version = QString::number(version);
            m_Url = cData.downloadUrl;
            return true;
        }
    }

    return false;
}

void ApplicationStart::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(this->rect(), QPixmap(":/images/bg@2x.png"));
}

/* http请求 */
_HttpRetData ApplicationStart::getVersionRequest()
{
    m_Loop = new QEventLoop;
    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, this, [=](){
        timer->stop();
        m_Loop->quit();
    });
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    connect(manager, &QNetworkAccessManager::finished, this, [=](){
        m_Loop->quit();
    });
    QNetworkReply *networkReply;

    QUrl url;
    QNetworkRequest request;
    _HttpRetData data;

    //发送请求
    url.setUrl(QString("%1/%2").arg(URL_HEADER ,UPDATE_URL));
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader,"RT-Thread ART");
    networkReply = manager->get(request);

    // 阻塞
    timer->start(3000);
    m_Loop->exec();

    if (!timer->isActive()) {   //timeout
        networkReply->abort();
        manager->deleteLater();
        m_Loop->deleteLater();
        timer->deleteLater();
        m_Loop = nullptr;
        return data;
    }

    //处理返回消息
    QByteArray bytes = networkReply->readAll();
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        QJsonObject jsonObject = doucment.object();
        //状态,返回数据为空是，toInt()是-1
        data.state = jsonObject.value("state").toString().toInt();
        //获取消息体
        if (1 == data.state) {
            _CheUpdaData cuData;
            cuData.version = jsonObject.value("data").toObject().value("versionCode").toString();      //版本号
            cuData.downloadUrl = jsonObject.value("data").toObject().value("downloadUrl").toString();  //下载网址
            cuData.fileStyle = jsonObject.value("data").toObject().value("fileStyle").toString();      //文件格式
            cuData.fileSize = jsonObject.value("data").toObject().value("fileSize").toInt();
            data.variant = QVariant::fromValue(cuData);
        }
    }

    //释放资源
    networkReply->abort();
    manager->deleteLater();
    QThread::msleep(1000);
    return data;
}

void ApplicationStart::resizeWidget()
{
    QSize size = PublicFunction::getScaleSize(QSize(584, 408));
    this->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(32, 32));
    ui->label_logo->setFixedSize(size);

    ui->horizontalLayout->setContentsMargins(PublicFunction::getScaleSize(20), 0,
                                           PublicFunction::getScaleSize(20), PublicFunction::getScaleSize(16));
    ui->horizontalLayout->setSpacing(PublicFunction::getScaleSize(16));

    QFont font = PublicFunction::getFont(13);
    ui->label_applicationName->setFont(font);
    ui->label_tip->setFont(font);
}
