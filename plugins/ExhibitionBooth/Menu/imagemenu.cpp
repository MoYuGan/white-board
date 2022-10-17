#include "imagemenu.h"
#include "ui_imagemenu.h"

static int BORDER = 0;    //阴影边距
static int ITEM_HEIGHT = 0;
static int CAMERA_ITEM_HEIGHT = 0;

ImageMenu::ImageMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageMenu)
{
    ui->setupUi(this);
    this->initWidget();
    ui->pShowImgList->setChecked(true);
    ui->pSave->setEnabled(false);
}

ImageMenu::~ImageMenu()
{
    delete ui;
}

void ImageMenu::resize()
{
    ITEM_HEIGHT = PublicFunction::getScaleSize(160);
    CAMERA_ITEM_HEIGHT = PublicFunction::getScaleSize(93);
    BORDER = PublicFunction::getScaleSize(3);
    int spacing = PublicFunction::getScaleSize(12);
    int margin = PublicFunction::getScaleSize(16);
    this->setFixedSize(PublicFunction::getScaleSize(305) + BORDER*2, PublicFunction::getScaleSize(804) + BORDER*2);
    ui->verticalLayout->setContentsMargins(BORDER, BORDER, BORDER, BORDER);
    ui->verticalLayout_2->setContentsMargins(margin, margin, margin, PublicFunction::getScaleSize(12));
    ui->verticalLayout_2->setSpacing(spacing);
    ui->horizontalLayout_2->setSpacing(PublicFunction::getScaleSize(20));

    ui->pAddPicture->setFixedHeight(PublicFunction::getScaleSize(42));
    ui->frame_save->setFixedHeight(PublicFunction::getScaleSize(42));
    ui->frame->setFixedHeight(PublicFunction::getScaleSize(51));
    QFont font = PublicFunction::getFont(16);
    ui->label_title->setFont(font);
    ui->pShowImgList->setFont(font);
    ui->pShowCameraList->setFont(font);
    ui->pSave->setFont(font);
    ui->pAddPicture->setFont(PublicFunction::getFont(14));

    ui->pAddPicture->setStyleSheet(QString("QPushButton{"
                                           "border: 1px solid rgb(224,224,224);"
                                           "background: transparent;"
                                           "color: rgb(102,102,102);"
                                           "border-radius: %1px;}"
                                           "QPushButton::hover{"
                                           "background: rgb(238,238,238);"
                                           "}").arg(PublicFunction::getScaleSize(4)));
    ui->pShowImgList->setStyleSheet(QString("QPushButton{"
                                            "border: none;"
                                            "background: rgb(238,238,238);"
                                            "color: rgb(102,102,102);"
                                            "border-bottom-left-radius: %1px;}"
                                            "QPushButton::checked{"
                                            "color: rgb(20,134,250);"
                                            "background: transparent;}").arg(PublicFunction::getScaleSize(4)));
    ui->pShowCameraList->setStyleSheet(QString("QPushButton{"
                                            "border: none;"
                                            "background: rgb(238,238,238);"
                                            "color: rgb(102,102,102);"
                                            "border-bottom-right-radius: %1px;}"
                                            "QPushButton::checked{"
                                            "color: rgb(20,134,250);"
                                            "background: transparent;}").arg(PublicFunction::getScaleSize(4)));
    ui->pSave->setStyleSheet(QString("QPushButton{"
                                     "border: none;"
                                     "background: rgb(20,134,250);"
                                     "border-radius: %1px;"
                                     "color:white;}"
                                     "QPushButton::!enabled{"
                                     "background: rgb(170,170,170);}").arg(PublicFunction::getScaleSize(4)));

    ui->checkBox->setStyleSheet(QString("QCheckBox::indicator {"
                                        "width: %1px;"
                                        "height: %1px;"
                                        "}"
                                        "QCheckBox::indicator:unchecked {"
                                        "image: url('://images/xuanxiang1@2x.png');"
                                        "}"
                                        "QCheckBox::indicator:checked {"
                                        "image: url('://images/xuanxiang2@2x.png');"
                                        "}").arg(PublicFunction::getScaleSize(20)));

    //通过设置gridsize调整Item之间的间距，间距为gridSize的高度减去item的高度
    ui->listWidget_image->setGridSize(QSize(ui->listWidget_image->width(), ITEM_HEIGHT + PublicFunction::getScaleSize(10)));
    ui->listWidget_camera->setGridSize(QSize(ui->listWidget_camera->width(), CAMERA_ITEM_HEIGHT + PublicFunction::getScaleSize(10)));
}

int ImageMenu::getBorder()
{
    return BORDER;
}

void ImageMenu::showSaveWidget(bool bo)
{
    if (bo) {
        ui->pAddPicture->hide();
        ui->frame->hide();
        ui->frame_save->show();
    }else {
        this->onItemChecked(false);
        ui->frame_save->hide();
        ui->pAddPicture->show();
        ui->frame->show();
    }
}

void ImageMenu::setContastModel(bool bo)
{
    foreach(CustomPushButton_2 *button, m_BtnList) {
        button->setContrastModel(bo);
    }
    m_IsContast = bo;
}

void ImageMenu::addItem(const QPixmap &pixmap)
{
    CustomPushButton_2 *button = new CustomPushButton_2(pixmap, m_BtnList.size(), this);
    button->setCheckable(true);
    if (this->m_IsContast)
        button->setContrastModel(true);
    connect(button, &CustomPushButton_2::deleteSignal, this, &ImageMenu::onItemDelete);
    connect(button, &CustomPushButton_2::toggled, this, &ImageMenu::onItemChecked);
    m_BtnList.push_back(button);

    //创建listWidgetItem
    QSize size = QSize(PublicFunction::getScaleSize(268), ITEM_HEIGHT);
    QListWidgetItem *widgetItem = new QListWidgetItem(ui->listWidget_image);
    widgetItem->setSizeHint(size);
    ui->listWidget_image->setItemWidget(widgetItem, button);
    ui->listWidget_image->addItem(widgetItem);
    ui->listWidget_image->setCurrentItem(widgetItem);

    emit this->itemNumChanged();
}

void ImageMenu::addCameraItem(const QString &deviceName)
{
    CustomPushButton_5 *button = new CustomPushButton_5(deviceName, this);
    button->setIndex(m_CameraBtnList.size());
    button->setCheckable(true);
    connect(button, &CustomPushButton_5::toggled, this, &ImageMenu::onCameraItemChecked);
    m_CameraBtnList.push_back(button);

    //创建listWidgetItem
    QSize size = QSize(PublicFunction::getScaleSize(268), CAMERA_ITEM_HEIGHT);
    QListWidgetItem *widgetItem = new QListWidgetItem(ui->listWidget_camera);
    widgetItem->setSizeHint(size);
    ui->listWidget_camera->setItemWidget(widgetItem, button);
    ui->listWidget_camera->insertItem(m_CameraBtnList.size() - 1, widgetItem);
    //ui->listWidget_camera->setCurrentItem(widgetItem);
}

void ImageMenu::clearCameraItem()
{
    for(int i = 0; i < m_CameraBtnList.size(); i++) {
        ui->listWidget_camera->takeItem(i);
        m_CameraBtnList.at(i)->deleteLater();
    }
    m_CameraBtnList.clear();
    ui->listWidget_camera->clear();
}

int ImageMenu::getItemSize()
{
    return m_BtnList.size();
}

void ImageMenu::getPixmap(int id, QPixmap *pixmap, int *angle)
{
    if (id < 0 || id >= m_BtnList.size()) {
        *pixmap = QPixmap();
        *angle = 0;
    }else {
        CustomPushButton_2 *button = m_BtnList.at(id);
        button->mGetPixmap(pixmap);
        *angle = button->getRotateAngle();
    }
}

int ImageMenu::getCheckedIndex()
{
    int index = -1;
    for(int i = 0; i < m_BtnList.size(); i++) {
        if (m_BtnList.at(i)->isChecked())
            index = i;
    }
    return index;
}

int ImageMenu::getCheckedNum()
{
    int num = 0;
    foreach(CustomPushButton_2 *button, m_BtnList) {
        if (button->isChecked())
            num++;
    }
    return num;
}

int ImageMenu::getAllCheckedNum()
{
    int num = 0;
    foreach(CustomPushButton_2 *button, m_BtnList) {
        if (button->isChecked())
            num++;
    }
    foreach(CustomPushButton_5 *button, m_CameraBtnList) {
        if (button->isChecked())
            num++;
    }
    return num;
}

void ImageMenu::clearChecked()
{
    foreach (CustomPushButton_2 *button, m_BtnList) {
        disconnect(button, &CustomPushButton_2::toggled, this, &ImageMenu::onItemChecked);
        button->setChecked(false);
        connect(button, &CustomPushButton_2::toggled, this, &ImageMenu::onItemChecked);
    }
}

void ImageMenu::rotateItem(int id, int angle)
{
    if (id >= m_BtnList.size() || id < 0)
        return;
    m_BtnList.at(id)->setRotateAngle(angle);
}

void ImageMenu::setItemChecked(int index)
{
    if (index < 0 || index >= m_BtnList.size())
        return;

    CustomPushButton_2 *button = m_BtnList.at(index);
    disconnect(button, &CustomPushButton_2::toggled, this, &ImageMenu::onItemChecked);
    button->setChecked(true);
    connect(button, &CustomPushButton_2::toggled, this, &ImageMenu::onItemChecked);
}

void ImageMenu::setCameraItemChecked(int index, bool checked)
{
    if (index < 0 || index >= m_CameraBtnList.size())
        return;

    CustomPushButton_5 *button = m_CameraBtnList.at(index);
    disconnect(button, &CustomPushButton_5::toggled, this, &ImageMenu::onCameraItemChecked);
    button->setChecked(checked);
    connect(button, &CustomPushButton_5::toggled, this, &ImageMenu::onCameraItemChecked);
    if (checked)
        m_CheckedCameraButton = button;
}

void ImageMenu::setCameraItemEnabled(bool enabled)
{
    foreach (CustomPushButton_5 *button, m_CameraBtnList) {
        button->setEnabled(enabled);
    }
}

void ImageMenu::showImageList()
{
    ui->pShowImgList->click();
}

void ImageMenu::paintEvent(QPaintEvent *event)
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
            break;
        }
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void ImageMenu::initWidget()
{
    this->setLayout(ui->verticalLayout);
    ui->verticalLayoutWidget->hide();
    ui->frame->setLayout(ui->horizontalLayout);
    ui->horizontalLayoutWidget->hide();
    ui->frame_save->setLayout(ui->horizontalLayout_2);
    ui->horizontalLayoutWidget_2->hide();
    ui->verticalLayout->addWidget(ui->frame);
    ui->verticalLayout_2->addWidget(ui->frame_save);
    ui->frame_save->hide();

    ui->label_title->setText(tr("选择对比图片"));
    ui->pAddPicture->setText(tr("添加本地图片"));
    ui->pShowImgList->setText(tr("图片"));
    ui->pShowCameraList->setText(tr("摄像头"));
    this->selectedImageNumChanged(0);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);
    buttonGroup->addButton(ui->pShowImgList);
    buttonGroup->addButton(ui->pShowCameraList);

    ui->listWidget_image->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滑动条
    ui->listWidget_image->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_image->setVerticalScrollMode(QListWidget::ScrollPerPixel);  //设置垂直滑动模式
    ui->listWidget_image->setSelectionMode(QAbstractItemView::NoSelection);   //设置此属性不会影响自定义item widget选中样式
    QScroller::grabGesture(ui->listWidget_image, QScroller::LeftMouseButtonGesture);//设置滑动手势
    ui->listWidget_camera->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滑动条
    ui->listWidget_camera->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_camera->setVerticalScrollMode(QListWidget::ScrollPerPixel);  //设置垂直滑动模式
    ui->listWidget_camera->setSelectionMode(QAbstractItemView::NoSelection);   //设置此属性不会影响自定义item widget选中样式
    QScroller::grabGesture(ui->listWidget_camera, QScroller::LeftMouseButtonGesture);//设置滑动手势
    ui->listWidget_camera->hide();

    connect(ui->pAddPicture, &QPushButton::clicked, this, &ImageMenu::addLocalPicture);
    connect(ui->pShowImgList, &CustomPushButton::clicked, [=](){ ui->listWidget_image->show(); ui->listWidget_camera->hide();});
    connect(ui->pShowCameraList, &CustomPushButton::clicked, [=](){ ui->listWidget_camera->show(); ui->listWidget_image->hide();});
    connect(ui->checkBox, &QCheckBox::clicked, this, &ImageMenu::onCheckBoxClicked);
    connect(ui->pSave, &CustomPushButton::clicked, this, &ImageMenu::onSaveBtnClicked);
}

void ImageMenu::selectedImageNumChanged(int num)
{
    ui->pSave->setText(QString("%1%2%3").arg(tr("保存本地（")).arg(QString::number(num)).arg(tr("）")));
}

void ImageMenu::addLocalPicture()
{
    QFileDialog fileDialog;
    fileDialog.setWindowModality(Qt::WindowModal);
    QString filter;
    QString fileName = fileDialog.getOpenFileName(this, tr("选择图片"), "", "PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)", &filter);
    if (fileName.length() == 0)
        return;

    QPixmap pixmap;
    if (filter.compare("PNG(*.png)") == 0) {
        pixmap.load(fileName);
    }else if (filter.compare("JPG(*.jpg)") == 0){
        pixmap.load(fileName);
    }else if (filter.compare("BMP(*.bmp)") == 0){
        pixmap.load(fileName);
    }
    this->addItem(pixmap);
}

void ImageMenu::onItemDelete()
{
    CustomPushButton_2 *button = static_cast<CustomPushButton_2 *>(sender());
    int index = m_BtnList.indexOf(button);
    m_BtnList.removeOne(button);

    ui->listWidget_image->takeItem(index);
    for(int i = 0; i < m_BtnList.size(); i++) {
        m_BtnList.at(i)->mSetIndex(i);
    }

    if (button->isChecked()) {
        m_CheckedButton = nullptr;
        emit this->itemDelete(index);
    }

    button->deleteLater();
    emit itemNumChanged();
}

void ImageMenu::onItemChecked(bool checked)
{
    CustomPushButton_2 *button = static_cast<CustomPushButton_2 *>(sender());
    if (!ui->frame_save->isHidden()) {
        int num = this->getCheckedNum();
        ui->pSave->setText(QString("%1%2%3").arg(tr("保存本地（")).arg(num).arg(tr("）")));
        if (num > 0)
            ui->pSave->setEnabled(true);
        else
            ui->pSave->setEnabled(false);

        if (num == m_BtnList.size())
            ui->checkBox->setChecked(true);
        else
            ui->checkBox->setChecked(false);


        emit this->itemChecked(checked, m_BtnList.indexOf(button));
        return;
    }

    if (checked && !e_Checkable) {
        disconnect(button, &CustomPushButton_2::toggled, this, &ImageMenu::onItemChecked);
        button->setChecked(false);
        connect(button, &CustomPushButton_2::toggled, this, &ImageMenu::onItemChecked);
        return;
    }   

    if (m_IsContast) {
        if (checked)
            m_CheckedButton = button;
        emit this->itemChecked(checked, m_BtnList.indexOf(button));
    }else {
        if (checked) {
            if (nullptr != m_CheckedButton)
                m_CheckedButton->setChecked(false);
            m_CheckedButton = button;
            emit this->itemChecked(true, m_BtnList.indexOf(m_CheckedButton));
        }else {
            if (button == m_CheckedButton) {
                m_CheckedButton = nullptr;
                emit this->itemChecked(false, m_BtnList.indexOf(button));
            }
        }
    }
}

void ImageMenu::onCameraItemChecked(bool checked)
{
    CustomPushButton_5 *button = static_cast<CustomPushButton_5 *>(sender());
    if (checked && !e_Checkable) {
        disconnect(button, &CustomPushButton_5::toggled, this, &ImageMenu::onCameraItemChecked);
        button->setChecked(false);
        connect(button, &CustomPushButton_5::toggled, this, &ImageMenu::onCameraItemChecked);
        return;
    }

    if (checked) {
        if (nullptr != m_CheckedCameraButton) {
            disconnect(m_CheckedCameraButton, &CustomPushButton_5::toggled, this, &ImageMenu::onCameraItemChecked);
            m_CheckedCameraButton->setChecked(false);
            connect(m_CheckedCameraButton, &CustomPushButton_5::toggled, this, &ImageMenu::onCameraItemChecked);
        }
        m_CheckedCameraButton = button;
        emit this->cameraChecked(true, m_CameraBtnList.indexOf(m_CheckedCameraButton));
    }else {
        if (button == m_CheckedCameraButton) {
            m_CheckedCameraButton = nullptr;
            emit this->cameraChecked(false, m_CameraBtnList.indexOf(button));
        }
    }
}

void ImageMenu::onCheckBoxClicked()
{
    if (ui->checkBox->isChecked()) {
        foreach(CustomPushButton_2 *button, m_BtnList) {
            button->setChecked(true);
        }
    }else {
        foreach(CustomPushButton_2 *button, m_BtnList) {
            button->setChecked(false);
        }
    }
}

void ImageMenu::onSaveBtnClicked()
{
    QFileDialog fileDialog;
    fileDialog.setWindowModality(Qt::WindowModal);
    QString dirName = fileDialog.getExistingDirectory(this, tr("选择文件夹"), "/");
    if (dirName.length() == 0)
        return;

    QDateTime dateTime = QDateTime::currentDateTime();
    dirName = QString("%1/安道展台图片导出-%2").arg(dirName).arg(dateTime.date().toString("yyyyMMdd"));
    QDir dir;
    dir.setPath(dirName);
    int i = 1;
    while(dir.exists()) {
        dir.setPath(QString("%1 (%2)").arg(dirName).arg(i));
        i++;
    }

    m_PixmapList.clear();
    foreach(CustomPushButton_2 *button, m_BtnList) {
        if (button->isChecked())
            m_PixmapList.push_back(button->mGetPixmap());
    }
    if (dir.mkdir(dir.path())) {
        QWidget *parent = (QWidget *)this->parent();
        ExportFileWidget *exportWidget = new ExportFileWidget(&m_PixmapList, dir.path(), parent);
        exportWidget->setGeometry(parent->rect());
        exportWidget->show();
    }
    return;
}
