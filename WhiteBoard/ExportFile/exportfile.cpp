#include "exportfile.h"
#include "ui_exportfile.h"
#include "Public/public_function.h"
#include <QPalette>
#include <QtDebug>
#include <QString>
#include <QDesktopServices>
#include <QProcess>

ExportFileWidget::ExportFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExportFile)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);

    this->initWidget();
    this->resizeWidget();
}

ExportFileWidget::~ExportFileWidget()
{
    this->deleteThread();
    delete ui;
}

void ExportFileWidget::show()
{
    QWidget::show();
    ui->pClose->hide();
    ui->pShowFile->hide();
}

void ExportFileWidget::saveFile(QList<QPixmap> pixmapList, const QString &savePath)
{
    m_PixmapList = pixmapList;
    if (nullptr == m_Thread || m_Worker == nullptr || 0 == m_PixmapList.size())
        return;

    m_SavePath = savePath;
    ui->horizontalSlider->setMaximum(m_PixmapList.size());

    m_Worker->mSetPixmapList(&m_PixmapList);
    m_Worker->mSetSavePath(savePath);
    m_Thread->start();
}

void ExportFileWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    ui->frame->move(QPoint((this->width() - ui->frame->width())/2,
                           (this->height() - ui->frame->height())/2));
}

void ExportFileWidget::initWidget()
{
    ui->verticalLayoutWidget_3->hide();
    ui->frame->setLayout(ui->verticalLayout_3);
    ui->frame->mSetBackgroudColor(Qt::white);
    ui->verticalLayout_3->setSpacing(0);
    ui->label_icon->setScaledContents(true);
    ui->label_icon->setPixmap(QPixmap(":/images/ExportFile/daochu@2x.png"));

    int pageSize = 0;
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(pageSize);
    ui->label_title->setText(tr("导出文件"));

    ui->pCancel->setText(tr("取消导出"));
    connect(ui->pCancel, &PushButton_Basic::clicked, this, &ExportFileWidget::onCancelBtnClicked);
    ui->pShowFile->setText(tr("查看本地文件"));
    connect(ui->pShowFile, &PushButton_Basic::clicked, this, &ExportFileWidget::onShowFileBtnClicked);

    connect(ui->pClose, &PushButton_Basic::clicked, this, [=](){this->deleteLater();});
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &ExportFileWidget::onValueChanged, Qt::DirectConnection);

    m_Thread = new QThread;
    m_Worker = new ExportFileWorker;
    connect(m_Thread, &QThread::started, m_Worker, &ExportFileWorker::startWorker);
    connect(m_Worker, &ExportFileWorker::progressChanged, ui->horizontalSlider, &QSlider::setValue);
    connect(m_Worker, &ExportFileWorker::workFinished, this, &ExportFileWidget::onExportFileWorkerFinished);
}

void ExportFileWidget::resizeWidget()
{
    ui->verticalLayout_3->setContentsMargins(Public_Function::getScaleSize(34),
                                             Public_Function::getScaleSize(16),
                                             Public_Function::getScaleSize(16),
                                             Public_Function::getScaleSize(28));
    QSize size = Public_Function::getScaleSize(496, 276);
    ui->frame->setFixedSize(size);
    int radius = Public_Function::getScaleSize(12);
    ui->frame->mSetBordRadius(radius, radius, radius, radius);
    size = Public_Function::getScaleSize(58, 58);
    ui->label_icon->setFixedSize(size);
    ui->label_null->setFixedSize(size);
    ui->label_null_2->setFixedSize(size);
    ui->horizontalSlider->setFixedSize(Public_Function::getScaleSize(324, 14));
    ui->pCancel->setFixedSize(Public_Function::getScaleSize(100, 42));
    ui->pShowFile->setFixedSize(Public_Function::getScaleSize(134, 42));
    ui->pClose->setFixedSize(Public_Function::getScaleSize(18, 18));

    QFont font = Public_Function::getFont(20);
    font.setBold(true);
    font.setWeight(72);
    ui->label_title->setFont(font);
    ui->label_text->setFont(Public_Function::getFont(14));
    font.setPixelSize(Public_Function::getScaleSize(22));
    ui->label_progress->setFont(font);
    ui->pCancel->setFont(Public_Function::getFont(16));
    ui->pShowFile->setFont(Public_Function::getFont(16));
    int spacing = Public_Function::getScaleSize(32);
    ui->horizontalLayout->setSpacing(spacing);
    ui->horizontalLayout_2->setSpacing(spacing);
    ui->horizontalLayout_3->setSpacing(spacing);
    ui->horizontalLayout_4->setSpacing(Public_Function::getScaleSize(20));
    ui->verticalLayout_4->setContentsMargins(0, Public_Function::getScaleSize(20), 0, 0);
    ui->verticalLayout_4->setSpacing(Public_Function::getScaleSize(10));

    ui->pCancel->setStyleSheet(QString("QPushButton{"
                                      "border: %1px solid rgb(224, 224, 224);"
                                      "color: rgb(102, 102, 102);"
                                      "background: white;"
                                      "border-radius: %2px;}").arg(Public_Function::getScaleSize(1))
                              .arg(Public_Function::getScaleSize(4)));
    ui->pShowFile->setStyleSheet(QString("QPushButton{"
                                      "border: none;"
                                      "color: white;"
                                      "background: rgb(20,134,250);"
                                         "border-radius: %1px;}").arg(Public_Function::getScaleSize(4)));
    this->onValueChanged(ui->horizontalSlider->value());
}

void ExportFileWidget::deleteThread()
{
    if (nullptr != m_Worker) {
        disconnect(m_Worker, &ExportFileWorker::progressChanged, ui->horizontalSlider, &QSlider::setValue);
        disconnect(m_Worker, &ExportFileWorker::workFinished, this, &ExportFileWidget::onExportFileWorkerFinished);
        delete m_Worker;
        m_Worker = nullptr;
    }

    if (nullptr != m_Thread) {
        m_Thread->quit();
        m_Thread->wait();
        delete m_Thread;
        m_Thread = nullptr;
    }
}

void ExportFileWidget::onValueChanged(int value)
{
    QColor color;
    int radius = Public_Function::getScaleSize(5);
    if (0 == value)
        color = Qt::transparent;
    else
        color = QColor(20,134,250);

    ui->horizontalSlider->setStyleSheet(QString("QSlider{ border-radius: %1px; background: rgb(199,226,254);  margin: 0 0 0 0; }   \
                                                QSlider::groove:horizontal{ border: 1px solid transparent; height: %2px; }   \
                                                QSlider::add-page:horizontal{background: transparent; margin-left: %3px; margin-right: %3px; }   \
                                                QSlider::sub-page:horizontal{ background-color: rgba(%4,%5,%6,%7); border-radius: %8px; margin-left: %3px; margin-right: %3px; }   \
                                                QSlider::handle:horizontal{ background-color: transparent; width: 0px; \
                                                }").arg(Public_Function::getScaleSize(7))
                                             .arg(Public_Function::getScaleSize(8))
                                             .arg(Public_Function::getScaleSize(3))
                                             .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha())
                                             .arg(radius));

    if (0 == ui->horizontalSlider->maximum())
        return;
    int progress = value * 100/ui->horizontalSlider->maximum();

    if (value < ui->horizontalSlider->maximum())
        ui->label_text->setText(QString("%1%2/%3").arg(tr("正在导出")).arg(++value).arg(ui->horizontalSlider->maximum()));
    else {
        ui->label_text->setText(QString("%1").arg(tr("导出完成")));
    }
    ui->label_progress->setText(QString("%1\%").arg(progress));
}

void ExportFileWidget::onExportFileWorkerFinished()
{
    this->deleteThread();

    ui->pCancel->setText(tr("关闭"));
    ui->pShowFile->show();
    ui->pClose->show();

    emit threadFinished();
}

void ExportFileWidget::onCancelBtnClicked()
{
    this->deleteThread();
    this->deleteLater();
}

void ExportFileWidget::onShowFileBtnClicked()
{
    ui->pShowFile->setEnabled(false);

    QString dirPath = m_SavePath;
    QFileInfo fileInfo(dirPath);
    if (!fileInfo.isDir() && !fileInfo.isFile())
        dirPath = QString("/");
    dirPath = QString("%1").arg(dirPath);
    //QProcess process;
    dirPath =dirPath.mid(0,dirPath.lastIndexOf("/"));
    qDebug()<<dirPath;
    //process.startDetached(QString("%1/am_openfile.sh").arg(QCoreApplication::applicationDirPath()), QStringList() << dirPath);
    //QDesktopServices::openUrl(QUrl(dirPath, QUrl::TolerantMode));
    QDesktopServices::openUrl(QUrl::fromLocalFile(dirPath));
    this->onCancelBtnClicked();
}

ExportFileWorker::ExportFileWorker(QObject *parent) :
    QObject(parent)
{
}

void ExportFileWorker::mSetPixmapList(QList<QPixmap> *pixmapList)
{
    m_PixmapList = pixmapList;
}

void ExportFileWorker::mSetSavePath(const QString &path)
{
    m_SavePath = path;
}

void ExportFileWorker::startWorker()
{
    if (nullptr == m_PixmapList || m_PixmapList->isEmpty() || m_SavePath.isEmpty())
        return;

    int index = m_SavePath.lastIndexOf(".");
    QString str;
    if (-1 == index)
        str = "";
    else {
        str = m_SavePath.mid(index + 1);
        if (str.isNull())
            return;
    }

    if (str.compare("pdf") == 0) {
        this->saveToPDF();
        /*********change123 解决只能保存PNG格式的图片问题*****************/
    }else if ((str.compare("png") == 0)||(str.compare("jpg") == 0)||(str.compare("bmp") == 0)) {
        m_PixmapList->at(0).save(m_SavePath);
        emit progressChanged(1);
    }else {
        QFileInfo fileInfo(m_SavePath);
        if (fileInfo.isDir()) {
            QString fileName;
            for(int i = 0; i < m_PixmapList->size(); i++) {
                fileName = QString("%1/第%2页.png").arg(m_SavePath, QString::number(i + 1));
                m_PixmapList->at(i).save(fileName);
                emit progressChanged(i + 1);
            }
        }
    }

    emit workFinished();
}

void ExportFileWorker::saveToPDF()
{
    if (0 == m_PixmapList->size())
        return;

    QRect pixmapRect;
    pixmapRect = m_PixmapList->at(0).rect();
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPagedPaintDevice::Custom);
    printer.setPageSizeMM(QSizeF(pixmapRect.width()*16.67/47.25, pixmapRect.height()*16.67/47.25));
    printer.setPageMargins(0, 0, 0, 0, QPrinter::DevicePixel);
    printer.setOutputFormat(QPrinter::PdfFormat);  //设置输出格式为pdf
    printer.setOutputFileName(m_SavePath);   //设置输出路径
    QPainter painter;
    painter.begin(&printer);

    float xmultiple = (double(painter.viewport().width()) / pixmapRect.width());
    float yMultiple = (double(painter.viewport().height()) / pixmapRect.height());
    float fMin = (xmultiple < yMultiple) ? xmultiple : yMultiple;
    painter.scale(fMin, fMin); //将图像(所有要画的东西)在pdf上放大multiple-1倍

    for(int i = 0; i < m_PixmapList->size();)
    {
        painter.drawPixmap(0, 0, m_PixmapList->at(i));  //画图
        if(i != m_PixmapList->size() - 1)
            printer.newPage();
        emit progressChanged(++i);
    }
    painter.end();
}
