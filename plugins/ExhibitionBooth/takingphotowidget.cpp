#include "takingphotowidget.h"
#include "ui_takingphotowidget.h"
#include <QFileDialog>
#include "Public/function.h"

TakingPhotoWidget::TakingPhotoWidget(const QPixmap &pixmap, QWidget *parent):
    m_pPixmap(pixmap),
    QWidget(parent),
    ui(new Ui::TakingPhotoWidget)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
}


TakingPhotoWidget::~TakingPhotoWidget()
{
    delete ui;
}

void TakingPhotoWidget::show()
{
    QWidget::show();
    this->raise();
}

void TakingPhotoWidget::resize()
{
    QSize size = PublicFunction::getScaleSize(QSize(800, 600));
    ui->frame->setFixedSize(size);
    ui->label_title->setFixedHeight(PublicFunction::getScaleWidth(50));
    size = PublicFunction::getScaleSize(QSize(100, 40));
    ui->pSave->setFixedSize(size);
    ui->pClose->setFixedSize(size);
    ui->frame_bottom->setFixedHeight(PublicFunction::getScaleWidth(80));
    ui->frame_bottom->setContentsMargins(0, PublicFunction::getScaleWidth(20),
                                         PublicFunction::getScaleWidth(20),
                                         PublicFunction::getScaleWidth(20));
    ui->verticalLayout->setSpacing(PublicFunction::getScaleWidth(10));

    ui->frame->setStyleSheet(QString("#%1{border: none;"
                                     "background: white;"
                                     "border-radius: %2px;}").arg(ui->frame->objectName())
                             .arg(PublicFunction::getScaleWidth(5)));
    ui->label_title->setContentsMargins(PublicFunction::getScaleWidth(10), 0, 0, 0);
    ui->label_title->setStyleSheet(QString("%1 QLabel{border-top-left-radius: %2px;"
                                           "border-top-right-radius: %2px;}").arg(ui->label_title->styleSheet())
                                   .arg(PublicFunction::getScaleWidth(5)));
    QColor color = QColor(102, 102, 102);
    ui->label->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                             .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
    ui->pSave->setStyleSheet(QString("%1 QPushButton{border-radius: %2px;}")
                                        .arg(ui->pSave->styleSheet())
                                        .arg(PublicFunction::getScaleWidth(5)));
    ui->pClose->setStyleSheet(QString("%1 QPushButton{border-radius: %2px;}")
                                        .arg(ui->pClose->styleSheet())
                                        .arg(PublicFunction::getScaleWidth(5)));

    QFont font = PublicFunction::getFont(20);
    ui->label_title->setFont(font);
    font = PublicFunction::getFont(14);
    ui->pSave->setFont(font);
    ui->pClose->setFont(font);
}

void TakingPhotoWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::transparent);
}

void TakingPhotoWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    ui->frame->move(QPoint((this->width() - ui->frame->width())/2,
                           (this->height() - ui->frame->height())/2));
}

void TakingPhotoWidget::initWidget()
{
    ui->frame->setLayout(ui->verticalLayout);
    ui->frame_bottom->setLayout(ui->horizontalLayout_2);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(m_pPixmap);

    connect(ui->pSave, &CustomPushButton::clicked, [=](){
//        QFileDialog fileDialog(this,tr("保存为文件"));
//        fileDialog.resize(PublicFunction::getScaleSize(QSize(600, 400)));
//        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
//        fileDialog.setFont(PublicFunction::getFont(14));
//        fileDialog.setDirectory("/安道展台");
//        fileDialog.setNameFilter("PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)");
//        if (0 == fileDialog.exec())
//            return true;
        QString filter;
        QString fileName = QFileDialog::getSaveFileName(this, tr("保存图片"),
                                                          "/安道展台.png",
                                                          tr("PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)"), &filter);

//        QStringList list = fileDialog.selectedFiles();
//        if (list.size() != 0) {
//            this->setCursor(Qt::WaitCursor);
//            QString fileName = list.at(0);
//            QFile file(fileName);
//            if (file.exists())
//                file.remove();
            bool ret;

            if (0 == filter.compare("PNG(*.png)")) {
                if (fileName.mid(fileName.count() - 4).compare(".png") != 0)
                    ret = m_pPixmap.save(fileName.append(".png"));
                else
                    ret = m_pPixmap.save(fileName);
            }else if (0 == filter.compare("JPG(*.jpg)")) {
                if (fileName.mid(fileName.count() - 4).compare(".jpg") != 0)
                    ret = m_pPixmap.save(fileName.append(".jpg"));
                else
                    ret = m_pPixmap.save(fileName);
            }else {
                if (fileName.mid(fileName.count() - 4).compare(".bmp") != 0)
                    ret = m_pPixmap.save(fileName.append(".bmp"));
                else
                    ret = m_pPixmap.save(fileName);
            }
            this->deleteLater();
       // }

    });
    connect(ui->pClose, &CustomPushButton::clicked, [=](){
        this->deleteLater();
    });
}
