#include "itemtool_flippanel.h"
#include "ui_itemtool_flippanel.h"
#include <QButtonGroup>
#include "Public/public_function.h"

ItemTool_FlipPanel::ItemTool_FlipPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemTool_FlipPanel)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->setMouseTracking(true);
    this->initWidget();
    this->resize();
}

ItemTool_FlipPanel::~ItemTool_FlipPanel()
{
    delete ui;
}

void ItemTool_FlipPanel::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);
    /*翻转面板*/
    ui->horizontalLayoutWidget_3->hide();
    ui->frame_flip->setLayout(ui->horizontalLayout_3);
    ui->frame_flip->mSetBackgroudColor(Qt::white);
    ui->horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout_3->setSpacing(0);
    ui->pFlipHor->mSetIcon(QPixmap(":/images/itemToolIcon/right@2x.png"));
    ui->pFlipHor->mSetText(tr("水平"));
    connect(ui->pFlipHor, &DB_CustomPushButton_10::clicked, [=](){ emit this->horFlip(); });
    ui->pFlipVer->mSetIcon(QPixmap(":/images/itemToolIcon/under@2x.png"));
    ui->pFlipVer->mSetText(tr("垂直"));
    connect(ui->pFlipVer, &DB_CustomPushButton_10::clicked, [=](){ emit this->verFlip(); });
}

void ItemTool_FlipPanel::resize()
{
    /*翻转面板*/
    QSize size = Public_Function::getScaleSize(QSize(129, 72));
    this->setFixedSize(size);
    ui->frame_flip->setFixedSize(size);
    int radius = Public_Function::getScaleWidth(12);
    ui->frame_flip->mSetBordRadius(radius, radius, radius, radius);
    ui->frame_flip->mSetBorder(Public_Function::getScaleWidth(2));
    size = Public_Function::getScaleSize(QSize(50, 60));
    ui->pFlipHor->setFixedSize(size);
    ui->pFlipVer->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(40, 40));
    ui->pFlipHor->mSetIconSize(size);
    ui->pFlipVer->mSetIconSize(size);
    radius = Public_Function::getScaleWidth(10);
    ui->pFlipHor->mSetRadius(radius);
    ui->pFlipVer->mSetRadius(radius);
}
