#include "mainmenu.h"
#include "ui_mainmenu.h"

static int BORDER = 0;    //阴影边距

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
    this->setDeviceBtnEnabled(false);
    this->setResolutionBtnEnabled(false);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::resize()
{
    BORDER = PublicFunction::getScaleSize(3);
    int spacing = PublicFunction::getScaleSize(2);
    int marginLeftRight = BORDER;
    int marginTopBottom = PublicFunction::getScaleSize(4) + BORDER;
    ui->verticalLayout->setContentsMargins(0, marginTopBottom, 0, marginTopBottom);
    ui->verticalLayout->setSpacing(spacing);
    if (!ui->pDevices->isChecked())
        ui->horizontalLayout->setContentsMargins(marginLeftRight, 0, marginLeftRight, 0);
    else
        ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
    if (!ui->pResolution->isChecked())
        ui->horizontalLayout_2->setContentsMargins(marginLeftRight, 0, marginLeftRight, 0);
    else
        ui->horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout_3->setContentsMargins(marginLeftRight, 0, marginLeftRight, 0);
    ui->horizontalLayout_4->setContentsMargins(marginLeftRight, 0, marginLeftRight, 0);

    QFont font = PublicFunction::getFont(16);
    QSize size = PublicFunction::getScaleSize(32, 32);
    int height = PublicFunction::getScaleSize(50);
    ui->pDevices->setFixedHeight(height);
    ui->pDevices->mSetIconSize(size);
    ui->pDevices->mSetFont(font);
    ui->pDevices->mSetTextSize(PublicFunction::getScaleSize(80, 30));
    ui->pResolution->setFixedHeight(height);
    ui->pResolution->mSetIconSize(size);
    ui->pResolution->mSetFont(font);
    ui->pResolution->mSetTextSize(PublicFunction::getScaleSize(80, 30));
    ui->pAbout->setFixedHeight(height);
    ui->pAbout->mSetIconSize(size);
    ui->pAbout->mSetFont(font);
    ui->pAbout->mSetTextSize(PublicFunction::getScaleSize(80, 30));
    ui->pExit->setFixedHeight(height);
    ui->pExit->mSetIconSize(size);
    ui->pExit->mSetFont(font);
    ui->pExit->mSetTextSize(PublicFunction::getScaleSize(80, 30));

    int btnCount = 4;
    this->setFixedSize(PublicFunction::getScaleSize(166) + BORDER * 2,
                       height * btnCount + spacing * (btnCount - 1) + marginTopBottom * 2);
}

void MainMenu::hide()
{
    if (ui->pResolution->isChecked())
        ui->pResolution->setChecked(false);
    else if (ui->pDevices->isChecked())
        ui->pDevices->setChecked(false);
    QWidget::hide();
    emit widgetHide();
}

void MainMenu::setDeviceBtnEnabled(bool enabled)
{
    ui->pDevices->mSetEnabled(enabled, QPixmap("://images/shebei@2x.png"), QColor(136,136,136));
}

void MainMenu::setResolutionBtnEnabled(bool enabled)
{
    ui->pResolution->mSetEnabled(enabled, QPixmap("://images/fenbianlv@2x.png"), QColor(136,136,136));
}

void MainMenu::paintEvent(QPaintEvent *event)
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

void MainMenu::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);

    ui->pDevices->mSetText(tr("设备列表"), QColor(68,68,68), Qt::white);
    ui->pDevices->mSetIcon(QPixmap("://images/shebei@2x.png"), QPixmap("://images/shebei2@2x.png"));
    ui->pDevices->mSetColor(Qt::transparent, QColor(238, 238, 238), QColor(20,134,250));
    ui->pResolution->mSetText(tr("分辨率"), QColor(68,68,68), Qt::white);
    ui->pResolution->mSetIcon(QPixmap("://images/fenbianlv2@2x.png"), QPixmap("://images/fenbianlv@2x.png"));
    ui->pResolution->mSetColor(Qt::transparent, QColor(238, 238, 238), QColor(20,134,250));
    ui->pAbout->mSetText(tr("关于我们"), QColor(68,68,68));
    ui->pAbout->mSetIcon(QPixmap("://images/guanyu@2x.png"));
    ui->pAbout->mSetColor(Qt::transparent, QColor(238, 238, 238));
    if (!e_EmbeddedToWhiteBoard)
        ui->pExit->mSetText(tr("退出展台"), QColor(68,68,68));
    else
        ui->pExit->mSetText(tr("返回白板"), QColor(68,68,68));
    ui->pExit->mSetIcon(QPixmap("://images/tuichu@2x.png"));
    ui->pExit->mSetColor(Qt::transparent, QColor(238, 238, 238));

    connect(ui->pDevices, &CustomPushButton_3::toggled, this, &MainMenu::onDevicesBtnToggled);
    connect(ui->pResolution, &CustomPushButton_3::toggled, this, &MainMenu::onResolutionBtnToggled);
    connect(ui->pAbout, &CustomPushButton_3::clicked,this, [=](){ emit this->showAbout(); });
    connect(ui->pExit, &CustomPushButton_3::clicked,this, [=](){ emit this->exitApplication(); });
}

void MainMenu::onDevicesBtnToggled(bool checked)
{
    if (checked) {
        if (ui->pResolution->isChecked())
            ui->pResolution->setChecked(false);
        ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
    }else {
        ui->horizontalLayout->setContentsMargins(BORDER, 0, BORDER, 0);
    }
    emit showDeviceListMenu(checked);
}

void MainMenu::onResolutionBtnToggled(bool checked)
{
    if (checked) {
        if (ui->pDevices->isChecked())
            ui->pDevices->setChecked(false);
        ui->horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    }else {
        ui->horizontalLayout_2->setContentsMargins(BORDER, 0, BORDER, 0);
    }
    emit showResolutionListMenu(checked);
}
