#include "maintoolbar_left.h"
#include "ui_maintoolbar_left.h"

static int BORDER = 0;    //阴影边距

MainToolBar_Left::MainToolBar_Left(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainToolBar_Left)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
}

MainToolBar_Left::~MainToolBar_Left()
{
    delete ui;
}

void MainToolBar_Left::resize()
{
    BORDER = PublicFunction::getScaleSize(3);
    int spacing = PublicFunction::getScaleSize(10);
    int marginLeftRight = PublicFunction::getScaleSize(6) + BORDER;
    ui->horizontalLayout->setContentsMargins(marginLeftRight, 0, marginLeftRight, 0);
    ui->horizontalLayout->setSpacing(spacing);

    int marginTopBottom = BORDER;
    if (!ui->pMenu->isChecked())
        ui->verticalLayout->setContentsMargins(0, marginTopBottom, 0, marginTopBottom);
    else
        ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout_2->setContentsMargins(0, marginTopBottom, 0, marginTopBottom);

    ui->pMenu->setFixedWidth(PublicFunction::getScaleSize(48));
    ui->pMenu->mSetIconSize(PublicFunction::getScaleSize(30, 30));
    ui->pHide->setFixedWidth(PublicFunction::getScaleSize(48));
    ui->pHide->mSetIconSize(PublicFunction::getScaleSize(30, 30));
    if (e_EmbeddedToWhiteBoard)
        ui->pHide->hide();

    int btnCount;
    if (e_EmbeddedToWhiteBoard)
        btnCount = 1;
    else
        btnCount = 2;
    this->setFixedSize(ui->pMenu->width() * btnCount + spacing * (btnCount - 1) + marginLeftRight * 2,
                       PublicFunction::getScaleSize(48) + BORDER*2);
}

int MainToolBar_Left::getBorder()
{
    return BORDER;
}

void MainToolBar_Left::setShowMenuBtnChecked(bool checked)
{
    ui->pMenu->setChecked(checked);
}

void MainToolBar_Left::setMenuEnabled(bool enable)
{
    ui->pMenu->setEnabled(enable);
}

void MainToolBar_Left::paintEvent(QPaintEvent *event)
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

void MainToolBar_Left::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);
    ui->pMenu->mSetIcon(QPixmap(":/images/caidan_1@2x.png"), QPixmap(":/images/caidan_2@2x.png"));
    ui->pMenu->mSetColor(QColor(238,238,238), QColor(), QColor(20,134,250));
    ui->pHide->mSetIcon(QPixmap("://images/zuixiaohua_1@2x.png"));
    ui->pHide->mSetColor(QColor(238,238,238));

    connect(ui->pMenu, &CustomPushButton_1::toggled, this, &MainToolBar_Left::onMenuBtnToggled);
    connect(ui->pHide, &CustomPushButton_1::clicked, [=](){ emit this->toMinimize(); });
}

void MainToolBar_Left::onMenuBtnToggled(bool checked)
{
    if (!checked)
        ui->verticalLayout->setContentsMargins(0, BORDER, 0, BORDER);
    else
        ui->verticalLayout->setContentsMargins(0, 0, 0, 0);

    emit this->showMenu(checked);
}
