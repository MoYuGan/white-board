#include "devicesmenu.h"
#include "ui_devicesmenu.h"

static int BORDER = 0;    //阴影边距

DevicesMenu::DevicesMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevicesMenu)
{
    ui->setupUi(this);
    this->initWidget();
    this->resizeWidget();
}

DevicesMenu::~DevicesMenu()
{
    delete ui;
}

void DevicesMenu::show()
{
    QWidget::show();
    this->raise();
}

void DevicesMenu::resizeWidget()
{
    BORDER = PublicFunction::getScaleSize(3);
    int spacing = PublicFunction::getScaleSize(2);
    int marginTopBottom = BORDER + PublicFunction::getScaleSize(4);
    int marginLeftRight = BORDER;
    ui->verticalLayout->setContentsMargins(marginLeftRight, marginTopBottom, marginLeftRight, marginTopBottom);
    ui->verticalLayout->setSpacing(spacing);

    int btnCount = m_DeviceBtnList.size();
    int btnHeight = PublicFunction::getScaleSize(50);
    this->setFixedSize(PublicFunction::getScaleSize(130) + BORDER * 2,
                       btnHeight * btnCount + spacing * (btnCount - 1) + marginTopBottom * 2);


    foreach(QPushButton *button, m_DeviceBtnList) {
        btnCount++;
        button->setFixedHeight(btnHeight);
        button->setFixedWidth(this->width() - 2*BORDER);
        button->setFont(PublicFunction::getFont(16));
    }
}

void DevicesMenu::mSetAction(const QList<QString> &descriptionList, const QList<QString> &deviceNameList)
{
    for(int i = 0; i < descriptionList.size(); i++)
    {
        QPushButton *button = new QPushButton(this);
        button->setCheckable(true);
        button->setStyleSheet(QString("QPushButton{border: none;"
                                 "color: rgb(68, 68, 68);"
                                 "background: transparent;}"
                                 "QPushButton::hover{"
                                 "background: rgb(238, 238, 238);"
                                 "}"
                                 "QPushButton::checked{"
                                 "color: rgb(20,134,250);}"));
        button->setProperty("DEVICE_NAME", deviceNameList.at(i));
        button->setText(descriptionList.at(i));
        ui->verticalLayout->addWidget(button, 0, Qt::AlignCenter);
        m_DeviceBtnList.push_back(button);
        m_DevicesGroup->addButton(button);
    }
    this->resizeWidget();
}

void DevicesMenu::clearAction()
{
    foreach(QPushButton *button, m_DeviceBtnList) {
        ui->verticalLayout->removeWidget(button);
        m_DevicesGroup->removeButton(button);
        button->deleteLater();
    }
    m_DeviceBtnList.clear();
    this->setFixedSize(0, 0);
}

void DevicesMenu::setChecked(int index, bool checked)
{
    if (index < 0 || index >= m_DeviceBtnList.size())
        return;

    disconnect(m_DevicesGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onDevicesGroupToggled(QAbstractButton*,bool)));
    m_DeviceBtnList.at(index)->setChecked(checked);
    connect(m_DevicesGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onDevicesGroupToggled(QAbstractButton*,bool)));
}

void DevicesMenu::paintEvent(QPaintEvent *event)
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

void DevicesMenu::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);

    m_DevicesGroup = new QButtonGroup(this);
    m_DevicesGroup->setExclusive(true);
    connect(m_DevicesGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onDevicesGroupToggled(QAbstractButton*,bool)));
}

void DevicesMenu::onDevicesGroupToggled(QAbstractButton *button, bool checked)
{
    int index = m_DeviceBtnList.indexOf(((QPushButton *)button));
    if (-1 == index)
        return;
//    if (checked) {
//        foreach(QPushButton *btn, m_DeviceBtnList) {
//            if (btn == button) {
//                emit this->deviceChanged(btn->property("DEVICE_NAME").toString());
//                return;
//            }
//        }
//    }
    qDebug()<<"emit ==============="<<index;
    emit this->deviceChanged(checked, index);
}
