#include "versionupdate.h"
#include "ui_versionupdate.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QProcess>
#include <QProcessEnvironment>
#include <QStandardPaths>
#include <QLineEdit>
#include <QDialog>
#include "Public/public_function.h"
VersionUpdate::VersionUpdate(const QString &url, const QString &fileName, QWidget *parent):
    QWidget(parent),
    ui(new Ui::VersionUpdate),
    m_pUrl(url)
{
    //m_pFileName = fileName;
    m_pFileName = QString("%1/%2").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),fileName);
    ui->setupUi(this);
    initWidget();
    loop =new QEventLoop(this);
}

VersionUpdate::~VersionUpdate()
{
    delete ui;
}

void VersionUpdate::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    QColor color(105, 105, 105);
    int border = 6;
    int j;
    for(int i=0; i<border; i++)
    {
        j = border - i;
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(j, j, this->width()-j*2, this->height()- j*2, 8, 8);
        switch(i)
        {
        case 0:
            color.setAlpha(80);
            break;
        case 1:
            color.setAlpha(50);
            break;
        case 2:
            color.setAlpha(20);
            break;
        case 3:
            color.setAlpha(15);
            break;
        case 4:
            color.setAlpha(10);
            break;
        case 5:
            color.setAlpha(7);
            break;
        default:
            break;
        }
        QPen pen;
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

bool VersionUpdate::eventFilter(QObject *watched, QEvent *event)
{
//    if (event->type() == QEvent::MouseButtonRelease) {
//        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

//    }
    return QWidget::eventFilter(watched, event);
}

void VersionUpdate::initWidget()
{
    this->setLayout(ui->horizontalLayout);
    ui->frame->setLayout(ui->verticalLayout);
    ui->widget->setLayout(ui->verticalLayout_2);
    ui->widget_2->setLayout(ui->verticalLayout_3);
    ui->widget_3->setLayout(ui->verticalLayout_4);
    ui->stackedWidget->addWidget(ui->widget);
    ui->stackedWidget->addWidget(ui->widget_2);
    ui->stackedWidget->addWidget(ui->widget_3);
    ui->stackedWidget->addWidget(ui->widget_4);
    ui->stackedWidget->setCurrentWidget(ui->widget);
    ui->label_title->setContentsMargins(10, 0, 0, 0);
    this->adjustSize();
    ui->pushButton_cancelUpdate->hide();
}

void VersionUpdate::on_pushButton_update_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->widget_2);
    QDir dir;
    if (dir.exists(m_pFileName))
    {
        dir.remove(m_pFileName);
    }
    ui->label_updateMsg->setText(tr("正在下载更新包......"));
    connect(DB_HttpInterface::getInstace(), SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)),Qt::UniqueConnection);
    connect(DB_HttpInterface::getInstace(), &DB_HttpInterface::downloadFileFinished, this, &VersionUpdate::onDownloadUpdatePackageResult,Qt::UniqueConnection);

//    QString dirPath;
#ifdef Q_OS_LINUX
    //dirPath = QString("/tmp");
    //dirPath =QString("%1").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
//    QFileInfo fi;
//    fi.setFile(dirPath);
//    if (fi.exists())
//        m_pFileName = QString("%1/%2").arg(dirPath, m_pFileName);
//    else
//        m_pFileName = QString("%1/%2").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),m_pFileName);
#endif
    DB_HttpInterface::getInstace()->downloadUpdatePackageRequest(m_pUrl, m_pFileName);
}


void VersionUpdate::on_pushButton_cancel_clicked()
{
    emit closePanel(-1);
}

void VersionUpdate::on_pushButton_cancelUpdate_clicked()
{
    //disconnect(DB_HttpInterface::getInstace(), &DB_HttpInterface::downloadUpdatePackageResult, this, &VersionUpdate::onDownloadUpdatePackageResult);
    QFile file(m_pFileName);
    file.remove();
    emit closePanel(-1);
}

void VersionUpdate::on_pushButton_restart_clicked()
{
    qApp->exit(66);
}

void VersionUpdate::onDownloadProgress(qint64 value, qint64 maxValue)
{
    if(maxValue ==0)
    {
        qDebug()<< "maxValue " << maxValue <<Qt::endl;
        ui->pushButton_update->clicked(true);
    }
    else
    {
        ui->progressBar->setMaximum(maxValue);
        ui->progressBar->setValue(value);
    }

}

void VersionUpdate::onDownloadUpdatePackageResult()
{
    ui->pushButton_cancelUpdate->setEnabled(false);
    QFileInfo fileInfo(m_pFileName);
#if  1
    if (fileInfo.suffix().compare("gz") == 0) {
        ui->label_updateMsg->setText(tr("正在解压缩更新包......"));
        QProcess *process =new QProcess;
        int res =process->execute("tar", QStringList() << "-zxvmf" << m_pFileName << "-C" << QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)));
        process->waitForFinished(10000);
        if(!res)
        {
           QProcess *process =new QProcess;
           QString infoPath ="/opt/apps/com.amdox.board";
           QString libPath ="/opt/apps/com.amdox.board/files/lib/AMLib/";
           QString binPath ="/opt/apps/com.amdox.board/files/bin/";
           QString desktopPath =QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
           process->waitForFinished(10000);
           QString st1 ="mv " +desktopPath+"/AmdoxBoard/AmdoxBoard "+binPath;
           process->execute("sh", QStringList() << "-c" << st1);
           process->waitForFinished(10000);
           QString st2 ="mv " +desktopPath+"/AmdoxBoard/info "+infoPath;
           process->execute("sh", QStringList() << "-c" << st2);
           process->waitForFinished(10000);
           QString st3 ="mv " +QString("%1/AmdoxBoard/AMLib/* ").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)) +libPath;
           process->execute("sh", QStringList() << "-c" << st3);
           process->waitForFinished(10000);
           process->execute("rm", QStringList()<< "-r" <<QString("%1/AmdoxBoard/").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)));
           process->execute("rm", QStringList()<<QString("%1/AmdoxBoard.tar.gz").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)));
           emit closePanel(1);
        }
        else
        {
           qDebug()<< res <<"失败" <<Qt::endl;
           return;
        }
    }
#endif
//    if(fileInfo.suffix().compare("deb") == 0)
//    {
//        ui->stackedWidget->setCurrentWidget(ui->widget_4);
//        loop->exec();
//    }
//    emit closePanel(1);
}

void VersionUpdate::on_pushButton_update_2_clicked()
{
    loop->exit();
}


void VersionUpdate::on_pushButton_cancel_2_clicked()
{
    loop->exit();
}

