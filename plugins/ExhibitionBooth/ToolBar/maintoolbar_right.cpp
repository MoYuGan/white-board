#include "maintoolbar_right.h"
#include "ui_maintoolbar_right.h"

static int BORDER = 0;    //阴影边距

MainToolBar_right::MainToolBar_right(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainToolBar_right)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();

    ui->pContrast->setEnabled(false);
    ui->pSave->setEnabled(false);
}

MainToolBar_right::~MainToolBar_right()
{
    delete ui;
}

void MainToolBar_right::resize()
{
    BORDER = PublicFunction::getScaleSize(3);
    int spacing = 0;
    int marginLeftRight = BORDER + PublicFunction::getScaleSize(6);
    int marginTopBottom = BORDER + PublicFunction::getScaleSize(6);
    ui->horizontalLayout->setContentsMargins(marginLeftRight, marginTopBottom,
                                             marginLeftRight, marginTopBottom);
    ui->horizontalLayout->setSpacing(spacing);

    ui->pShowList->mSetIconSize(PublicFunction::getScaleSize(20, 20));
    ui->pShowList->setFixedSize(PublicFunction::getScaleSize(40, 36));
    ui->pShowList->mSetRadius(PublicFunction::getScaleSize(4));
    ui->pContrast->mSetIconSize(PublicFunction::getScaleSize(30, 30));
    ui->pContrast->setFixedWidth(PublicFunction::getScaleSize(120));
    ui->pContrast->setFont(PublicFunction::getFont(14));
    ui->pContrast->mSetRadius(PublicFunction::getScaleSize(4));
    ui->pSave->mSetIconSize(PublicFunction::getScaleSize(30, 30));
    ui->pSave->setFixedWidth(PublicFunction::getScaleSize(90));
    ui->pSave->setFont(PublicFunction::getFont(14));
    ui->pSave->mSetRadius(PublicFunction::getScaleSize(4));
    ui->label_line->setFixedWidth(PublicFunction::getScaleSize(1));

    QFont font = PublicFunction::getFont(14);
    ui->pCancelContrast->setFont(font);
    ui->pCancelSave->setFont(font);
    ui->label_text_contrast->setFont(font);
    ui->label_text_save->setFont(font);
    ui->pContrast->mSetFont(font);
    ui->pSave->mSetFont(font);

    ui->pCancelContrast->setStyleSheet(QString("QPushButton{"
                                               "border: 1px solid rgb(224, 224, 224);"
                                               "border-radius: %1px;"
                                               "background: transparent;"
                                               "color: rgb(102, 102, 102);}"
                                               "QPushButton::hover{"
                                               "background: rgb(238, 238, 238);}").arg(PublicFunction::getScaleSize(4)));
    ui->pCancelSave->setStyleSheet(QString("QPushButton{"
                                               "border: 1px solid rgb(224, 224, 224);"
                                               "border-radius: %1px;"
                                               "background: transparent;"
                                               "color: rgb(102, 102, 102);}"
                                               "QPushButton::hover{"
                                               "background: rgb(238, 238, 238);}").arg(PublicFunction::getScaleSize(4)));

    this->setFixedSize(PublicFunction::getScaleSize(277) + BORDER * 2,
                       PublicFunction::getScaleSize(48) + BORDER * 2);

    m_ImageMenu->resize();
}

int MainToolBar_right::getBorder()
{
    return BORDER;
}

void MainToolBar_right::setShowListBtnChecked(bool checked)
{
    ui->pShowList->setChecked(checked);
}

void MainToolBar_right::getPixmap(int id, QPixmap *pixmap, int *angle)
{
    m_ImageMenu->getPixmap(id, pixmap, angle);
}

void MainToolBar_right::addItem(const QPixmap &pixmap)
{
    m_ImageMenu->addItem(pixmap);
}

void MainToolBar_right::rotateItem(int id, int angle)
{
    m_ImageMenu->rotateItem(id, angle);
}

void MainToolBar_right::addCameraItem(const QString &text)
{
    m_ImageMenu->addCameraItem(text);
}

void MainToolBar_right::clearCameraItem()
{
    m_ImageMenu->clearCameraItem();
}

void MainToolBar_right::setCameraItemChecked(int index, bool checked)
{
    m_ImageMenu->setCameraItemChecked(index, checked);
}

void MainToolBar_right::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::transparent);
    QColor color(135, 135, 135);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    for(int i = 0; i < BORDER; i++)
    {
        QRect rect = QRect(QPoint(BORDER - i, BORDER - i),
                           QPoint(this->width() - (BORDER - i),
                            this->height() - (BORDER - i)));
        QPainterPath path;
        int radius = PublicFunction::getScaleSize(4);
        path = PublicFunction::getRoundRectPath(rect, radius, radius, radius, radius);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }
        switch(i)
        {
        case 0:
            color.setAlpha(50);
            break;
        case 1:
            color.setAlpha(25);
            break;
        case 2:
            color.setAlpha(10);
            break;
        default:
            continue;
        }
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void MainToolBar_right::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);
    ui->frame->setLayout(ui->horizontalLayout_2);
    ui->horizontalLayoutWidget_2->hide();
    ui->frame_contrast->setLayout(ui->horizontalLayout_3);
    ui->horizontalLayoutWidget_3->hide();
    ui->frame_save->setLayout(ui->horizontalLayout_4);
    ui->horizontalLayoutWidget_4->hide();
    ui->horizontalLayout->addWidget(ui->frame);
    ui->horizontalLayout->addWidget(ui->frame_contrast);
    ui->horizontalLayout->addWidget(ui->frame_save);
    ui->frame_contrast->hide();
    ui->frame_save->hide();

    ui->pShowList->mSetIcon(QPixmap("://images/zhankai_1@2x.png"), QPixmap("://images/zhankai2_1@2x.png"));
    ui->pShowList->mSetColor(QColor(238, 238, 238));
    ui->pContrast->mSetText(tr("对比教学"), QColor(68,68,68));
    ui->pContrast->mSetIcon(QPixmap("://images/duibi@2x.png"));
    ui->pContrast->mSetColor(Qt::transparent, QColor(238, 238, 238));
    ui->pSave->mSetText(tr("保存"), QColor(68,68,68));
    ui->pSave->mSetIcon(QPixmap("://images/baocun@2x.png"));
    ui->pSave->mSetColor(Qt::transparent, QColor(238, 238, 238));
    ui->pCancelContrast->setText(tr("取消对比教学"));
    ui->pCancelSave->setText(tr("取消保存图片"));
    ui->label_text_contrast->setText(QString("0 / 4"));

    m_ImageMenu = new ImageMenu((QWidget *)this->parent());
    m_ImageMenu->hide();

    connect(ui->pContrast, &CustomPushButton_3::clicked, this, &MainToolBar_right::onContrastBtnClicked);
    connect(ui->pCancelContrast, &QPushButton::clicked, this, &MainToolBar_right::onContrastCancelBtnClicked);
    connect(ui->pSave, &CustomPushButton_3::clicked, this, &MainToolBar_right::onSaveBtnClicked);
    connect(ui->pCancelSave, &QPushButton::clicked, this, &MainToolBar_right::onSaveCancelBtnClicked);
    connect(ui->pShowList, &CustomPushButton_1::toggled, this, &MainToolBar_right::onShowImageBtnClicked);
    connect(m_ImageMenu, &ImageMenu::itemNumChanged, this, &MainToolBar_right::onItemNumChanged);
    connect(m_ImageMenu, &ImageMenu::itemChecked, this, &MainToolBar_right::onItemChecked);
    connect(m_ImageMenu, &ImageMenu::cameraChecked, this, &MainToolBar_right::onCameraItemChecked);
    connect(m_ImageMenu, &ImageMenu::itemDelete, [=](int id){ emit this->displayImage(false, id); });
}

void MainToolBar_right::onShowImageBtnClicked()
{
    if (m_ImageMenu->isHidden()) {
        if (this->property("SHOW_WHICH").toString().compare("right") == 0) {
            m_ImageMenu->move(QPoint(this->x() + this->width() - m_ImageMenu->width(),
                                     this->y() - PublicFunction::getScaleSize(16) + m_ImageMenu->getBorder() - m_ImageMenu->height()));
        }else {
            m_ImageMenu->move(QPoint(this->x(),
                                     this->y() - PublicFunction::getScaleSize(16) + m_ImageMenu->getBorder() - m_ImageMenu->height()));
        }
        m_ImageMenu->raise();
        m_ImageMenu->show();
    }else {
        m_ImageMenu->hide();
    }
}

void MainToolBar_right::onContrastBtnClicked()
{
    ui->frame->hide();
    ui->frame_contrast->show();
    m_ImageMenu->setContastModel(true);
    int num = m_ImageMenu->getAllCheckedNum();
    ui->label_text_contrast->setText(QString("%1 / 4").arg(num));

    emit enableContrast(m_ImageMenu->getCheckedIndex());
}

void MainToolBar_right::onContrastCancelBtnClicked()
{
    ui->frame_contrast->hide();
    ui->frame->show();
    m_ImageMenu->setContastModel(false);

    int num = m_ImageMenu->getCheckedNum();
    QPixmap pixmap;
    int id;
    int angle;
    if (1 == num) {
        id = m_ImageMenu->getCheckedIndex();
        m_ImageMenu->getPixmap(id, &pixmap, &angle);
    }else {
        m_ImageMenu->clearChecked();
        pixmap = QPixmap();
    }

    emit cancelContrast(pixmap, id, angle);
}

void MainToolBar_right::onSaveBtnClicked()
{
    ui->frame->hide();
    ui->frame_save->show();
    m_ImageMenu->showImageList();
    m_ImageMenu->showSaveWidget(true);
    m_ImageMenu->setContastModel(true);
    m_CheckedIndex = m_ImageMenu->getCheckedIndex();
    ui->label_text_save->setText(QString("%1%2%3").arg(tr("已选：")).arg(m_ImageMenu->getCheckedNum()).arg(tr("张")));
    m_ImageMenu->setCameraItemEnabled(false);

    if (!ui->pShowList->isChecked())
        ui->pShowList->click();
}

void MainToolBar_right::onSaveCancelBtnClicked()
{
    ui->frame_save->hide();
    ui->frame->show();
    m_ImageMenu->setContastModel(false);
    m_ImageMenu->clearChecked();
    m_ImageMenu->showSaveWidget(false);
    m_ImageMenu->setItemChecked(m_CheckedIndex);
    m_ImageMenu->setCameraItemEnabled(true);
}

void MainToolBar_right::onItemNumChanged()
{
    if (m_ImageMenu->getItemSize() > 0) {
        ui->pContrast->setEnabled(true);
        ui->pSave->setEnabled(true);
    }else{
        ui->pContrast->setEnabled(false);
        ui->pSave->setEnabled(false);
    }
}

void MainToolBar_right::onItemChecked(bool checked, int id)
{
    if (ui->frame_save->isHidden()) {
        int num = m_ImageMenu->getAllCheckedNum();
        ui->label_text_contrast->setText(QString("%1 / 4").arg(num));
        emit this->displayImage(checked, id);
    }else {
        ui->label_text_save->setText(QString("%1%2%3").arg(tr("已选：")).arg(m_ImageMenu->getCheckedNum()).arg(tr("张")));
    }
}

void MainToolBar_right::onCameraItemChecked(bool checked, int index)
{
    qDebug()<<"----on camera item checked";
    if (ui->frame_save->isHidden()) {
        int num = m_ImageMenu->getAllCheckedNum();
        ui->label_text_contrast->setText(QString("%1 / 4").arg(num));
        emit this->cameraChecked(checked, index);
    }else {
        ui->label_text_save->setText(QString("%1%2%3").arg(tr("已选：")).arg(m_ImageMenu->getCheckedNum()).arg(tr("张")));
    }
}

