#include "exportfile.h"
#include "ui_exportfile.h"
#include <QPalette>
#include <QtDebug>
#include <QString>
#include <QDesktopServices>
#include <QProcess>

ExportFileWidget::ExportFileWidget(BoardView *view, const QString path, QWidget *parent) :
    m_pBoardView(view),
    m_pExportPath(path),
    QWidget(parent),
    ui(new Ui::ExportFile)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->initWidget();
    this->resize();

    m_pWorker = new ExportFileWorker(view, path);
    connect(m_pWorker, &ExportFileWorker::progressChanged, ui->horizontalSlider, &QSlider::setValue, Qt::DirectConnection);
    connect(m_pWorker, &ExportFileWorker::workFinished, this, &ExportFileWidget::onExportFileWorkerFinished);

    m_pThread = new QThread(this);
    connect(m_pThread, &QThread::started, m_pWorker, &ExportFileWorker::startWorker);
    m_pWorker->moveToThread(m_pThread);
}

ExportFileWidget::~ExportFileWidget()
{
    delete ui;
}

void ExportFileWidget::show()
{
    QWidget::show();
    ui->pClose->hide();
    ui->pShowFile->hide();
    m_pThread->start();
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
    ui->verticalLayout_3->setSpacing(0);
    ui->label_icon->setScaledContents(true);
    ui->label_icon->setPixmap(QPixmap(":/images/ExportFile/daochu@2x.png"));

    int pageSize = m_pBoardView->getScenesListSize();
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(pageSize);
    ui->label_title->setText(tr("导出为图片（所有页）"));
    ui->pCancel->setText(tr("取消导出"));
    connect(ui->pCancel, &CustomPushButton::clicked, this, &ExportFileWidget::onCancelBtnClicked);
    ui->pShowFile->setText(tr("查看本地文件"));
    connect(ui->pShowFile, &CustomPushButton::clicked, this, &ExportFileWidget::onShowFileBtnClicked);
}

void ExportFileWidget::resize()
{
    ui->verticalLayout_3->setContentsMargins(PublicFunction::getScaleSize(34),
                                             PublicFunction::getScaleSize(16),
                                             PublicFunction::getScaleSize(16),
                                             PublicFunction::getScaleSize(28));
    QSize size = PublicFunction::getScaleSize(496, 276);
    ui->frame->setFixedSize(size);
    int radius = PublicFunction::getScaleSize(12);
    ui->frame->mSetBordRadius(radius, radius, radius, radius);
    size = PublicFunction::getScaleSize(58, 58);
    ui->label_icon->setFixedSize(size);
    ui->label_null->setFixedSize(size);
    ui->label_null_2->setFixedSize(size);
    ui->horizontalSlider->setFixedSize(PublicFunction::getScaleSize(324, 14));
    ui->pCancel->setFixedSize(PublicFunction::getScaleSize(100, 42));
    ui->pShowFile->setFixedSize(PublicFunction::getScaleSize(134, 42));
    ui->pClose->setFixedSize(PublicFunction::getScaleSize(18, 18));
    connect(ui->pClose, &CustomPushButton::clicked, [=](){this->deleteLater();});
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &ExportFileWidget::onValueChanged, Qt::DirectConnection);

    QFont font = PublicFunction::getFont(20);
    font.setBold(true);
    font.setWeight(72);
    ui->label_title->setFont(font);
    ui->label_text->setFont(PublicFunction::getFont(14));
    font.setPixelSize(PublicFunction::getScaleSize(22));
    ui->label_progress->setFont(font);
    ui->pCancel->setFont(PublicFunction::getFont(16));
    ui->pShowFile->setFont(PublicFunction::getFont(16));
    int spacing = PublicFunction::getScaleSize(32);
    ui->horizontalLayout->setSpacing(spacing);
    ui->horizontalLayout_2->setSpacing(spacing);
    ui->horizontalLayout_3->setSpacing(spacing);
    ui->horizontalLayout_4->setSpacing(PublicFunction::getScaleSize(20));
    ui->verticalLayout_4->setContentsMargins(0, PublicFunction::getScaleSize(20), 0, 0);
    ui->verticalLayout_4->setSpacing(PublicFunction::getScaleSize(10));

    ui->pCancel->setStyleSheet(QString("QPushButton{"
                                      "border: %1px solid rgb(224, 224, 224);"
                                      "color: rgb(102, 102, 102);"
                                      "background: white;"
                                      "border-radius: %2px;}").arg(PublicFunction::getScaleSize(1))
                              .arg(PublicFunction::getScaleSize(4)));
    ui->pShowFile->setStyleSheet(QString("QPushButton{"
                                      "border: none;"
                                      "color: white;"
                                      "background: rgb(20,134,250);"
                                         "border-radius: %1px;}").arg(PublicFunction::getScaleSize(4)));
    this->onValueChanged(ui->horizontalSlider->value());
}

void ExportFileWidget::deleteThread()
{
    disconnect(m_pWorker, &ExportFileWorker::progressChanged, ui->horizontalSlider, &QSlider::setValue);
    disconnect(m_pWorker, &ExportFileWorker::workFinished, this, &ExportFileWidget::onExportFileWorkerFinished);
    delete m_pWorker;
    m_pWorker = nullptr;
    m_pThread->quit();
    m_pThread->wait();
    delete m_pThread;
    m_pThread = nullptr;
}

void ExportFileWidget::onValueChanged(int value)
{
    QColor color;
    int radius = PublicFunction::getScaleSize(5);
    if (0 == value)
        color = Qt::transparent;
    else
        color = QColor(20,134,250);

    ui->horizontalSlider->setStyleSheet(QString("QSlider{ border-radius: %1px; background: rgb(199,226,254);  margin: 0 0 0 0; }   \
                                                QSlider::groove:horizontal{ border: 1px solid transparent; height: %2px; }   \
                                                QSlider::add-page:horizontal{background: transparent; margin-left: %3px; margin-right: %3px; }   \
                                                QSlider::sub-page:horizontal{ background-color: rgb(%4,%5,%6,%7); border-radius: %8px; margin-left: %3px; margin-right: %3px; }   \
                                                QSlider::handle:horizontal{ background-color: transparent; width: 0px; \
                                                }").arg(PublicFunction::getScaleSize(7))
                                             .arg(PublicFunction::getScaleSize(8))
                                             .arg(PublicFunction::getScaleSize(3))
                                             .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha())
                                             .arg(radius));

    int progress = value*100/ui->horizontalSlider->maximum();
    if (value < ui->horizontalSlider->maximum()) {
        QString fileName = m_pExportPath.mid(m_pExportPath.lastIndexOf("/") + 1);     //获取文件名
        ui->label_text->setText(QString("%1%2/%3 : %4").arg(tr("正在导出")).arg(++value).arg(ui->horizontalSlider->maximum())
                                .arg(fileName));
    }else
        ui->label_text->setText(QString("%1%2%3").arg(tr("导出完成，共计生成")).arg(ui->horizontalSlider->maximum()).arg(tr("张图片")));
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
    if (nullptr != m_pThread) {
        this->deleteThread();
    }

    this->deleteLater();
}

void ExportFileWidget::onShowFileBtnClicked()
{
    ui->pShowFile->setEnabled(false);

    QString dirPath;
    dirPath = m_pExportPath;

    QProcess process;
    process.startDetached(QString("%1/am_openfile.sh").arg(QCoreApplication::applicationDirPath()), QStringList() << dirPath);
    this->deleteLater();
}
