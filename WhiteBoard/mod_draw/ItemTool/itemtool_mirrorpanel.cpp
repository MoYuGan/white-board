#include "itemtool_mirrorpanel.h"
#include "ui_itemtool_mirrorpanel.h"
#include <QButtonGroup>
#include "Public/public_function.h"

ItemTool_MirrorPanel::ItemTool_MirrorPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemTool_MirrorPanel)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_AcceptTouchEvents,true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->setMouseTracking(true);
    this->initWidget();
    this->resize();
}

ItemTool_MirrorPanel::~ItemTool_MirrorPanel()
{
    delete ui;
}

void ItemTool_MirrorPanel::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);
    /*镜像面板*/
    ui->horizontalLayoutWidget_4->hide();
    ui->frame_mirror->setLayout(ui->horizontalLayout_4);
    ui->frame_mirror->mSetBackgroudColor(Qt::white);
    ui->horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout_4->setSpacing(0);
    ui->pMirrorTop->mSetIcon(QPixmap(":/images/itemToolIcon/up-1@2x.png"));
    ui->pMirrorTop->mSetText(tr("向上"));
    connect(ui->pMirrorTop, &DB_CustomPushButton_10::clicked, [=](){emit this->mirror(0);});
    ui->pMirrorBottom->mSetIcon(QPixmap(":/images/itemToolIcon/down-1@2x.png"));
    ui->pMirrorBottom->mSetText(tr("向下"));
    connect(ui->pMirrorBottom, &DB_CustomPushButton_10::clicked, [=](){emit this->mirror(1);});
    ui->pMirrorLeft->mSetIcon(QPixmap(":/images/itemToolIcon/left-1@2x.png"));
    ui->pMirrorLeft->mSetText(tr("向左"));
    connect(ui->pMirrorLeft, &DB_CustomPushButton_10::clicked, [=](){emit this->mirror(2);});
    ui->pMirrorRight->mSetIcon(QPixmap(":/images/itemToolIcon/right-1@2x.png"));
    ui->pMirrorRight->mSetText(tr("向右"));
    connect(ui->pMirrorRight, &DB_CustomPushButton_10::clicked, [=](){emit this->mirror(3);});
}

void ItemTool_MirrorPanel::resize()
{
    /*镜像面板*/
    QSize size = Public_Function::getScaleSize(QSize(247, 72));
    ui->frame_mirror->setFixedSize(size);
    int radius = Public_Function::getScaleSize(12);
    ui->frame_mirror->mSetBordRadius(radius, radius, radius, radius);
    ui->frame_mirror->mSetBorder(Public_Function::getScaleSize(2));
    size = Public_Function::getScaleSize(QSize(50, 60));
    ui->pMirrorTop->setFixedSize(size);
    ui->pMirrorBottom->setFixedSize(size);
    ui->pMirrorLeft->setFixedSize(size);
    ui->pMirrorRight->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(40, 40));
    ui->pMirrorTop->mSetIconSize(size);
    ui->pMirrorBottom->mSetIconSize(size);
    ui->pMirrorLeft->mSetIconSize(size);
    ui->pMirrorRight->mSetIconSize(size);
    radius = Public_Function::getScaleSize(10);
    ui->pMirrorTop->mSetRadius(radius);
    ui->pMirrorBottom->mSetRadius(radius);
    ui->pMirrorLeft->mSetRadius(radius);
    ui->pMirrorRight->mSetRadius(radius);

    this->adjustSize();
}

bool ItemTool_MirrorPanel::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        {
            return true;
            break;
        }
        case QEvent::TouchUpdate:
        {
            return true;
            break;
        }
        case QEvent::TouchEnd:
        {
            QTouchEvent* ev =static_cast<QTouchEvent*>(event);
            QPoint dot =ev->touchPoints().at(0).pos().toPoint();
            if (ui->pMirrorTop->geometry().contains(dot))
            {
                emit this->mirror(0);
            }
            else if (ui->pMirrorBottom->geometry().contains(dot))
            {
                emit this->mirror(1);
            }
            else if (ui->pMirrorLeft->geometry().contains(dot))
            {
                emit this->mirror(2);
            }
            else if (ui->pMirrorRight->geometry().contains(dot))
            {
                emit this->mirror(3);
            }
            return true;
            break;
        }
        default:
        {
            break;
        }
    }
    return QWidget::event(event);
}
