#include "controlmenu.h"
#include "ui_controlmenu.h"
static int BORDER = 0;    //阴影边距

ControlMenu::ControlMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlMenu)
{
    ui->setupUi(this);
    this->initWidget();
    ui->pDynamic->setChecked(true);
}

ControlMenu::~ControlMenu()
{
    delete ui;
}

void ControlMenu::resize()
{
    BORDER = PublicFunction::getScaleSize(3);
    int spacing = PublicFunction::getScaleSize(10);
    int marginLeftRight = BORDER + PublicFunction::getScaleSize(14);
    int marginTop = BORDER + PublicFunction::getScaleSize(8);
    int marginBottom = BORDER + PublicFunction::getScaleSize(14);
    ui->verticalLayout->setContentsMargins(marginLeftRight, marginTop,
                                             marginLeftRight, marginBottom);
    ui->verticalLayout->setSpacing(spacing);
    int margin = PublicFunction::getScaleSize(4);
    ui->horizontalLayout_3->setContentsMargins(margin, margin, margin, margin);

    QSize size = PublicFunction::getScaleSize(50, 50);
    ui->pRotateLeft->mSetIconSize(size);
    ui->pRotateRight->mSetIconSize(size);
    ui->pZoomIn->mSetIconSize(size);
    ui->pZoomOut->mSetIconSize(size);
    size = PublicFunction::getScaleSize(70, 70);
    ui->pRotateLeft->setFixedSize(size);
    ui->pRotateRight->setFixedSize(size);
    ui->pZoomIn->setFixedSize(size);
    ui->pZoomOut->setFixedSize(size);
    int radius = PublicFunction::getScaleSize(4);
    ui->pRotateLeft->mSetRadius(radius);
    ui->pRotateRight->mSetRadius(radius);
    ui->pZoomIn->mSetRadius(radius);
    ui->pZoomOut->mSetRadius(radius);
    QFont font = PublicFunction::getFont(14);
    ui->pRotateLeft->mSetFont(font);
    ui->pRotateRight->mSetFont(font);
    ui->pZoomIn->mSetFont(font);
    ui->pZoomOut->mSetFont(font);
    ui->pDynamic->setFont(font);
    ui->pStatic->setFont(font);
    ui->frame->setFixedSize(PublicFunction::getScaleSize(160, 42));
    ui->pDynamic->setFixedSize(PublicFunction::getScaleSize(75, 34));
    ui->pStatic->setFixedSize(PublicFunction::getScaleSize(75, 34));
    ui->label_line->setFixedHeight(PublicFunction::getScaleSize(1));

    ui->frame->setStyleSheet(QString("#frame{background: rgb(238, 238, 238);"
                                     "border: none;"
                                     "border-radius:%1px;}").arg(PublicFunction::getScaleSize(4)));
    ui->pDynamic->setStyleSheet(QString("QPushButton{background: transparent;"
                                        "border: none;"
                                        "border-radius: %1px;"
                                        "color: rgb(102, 102, 102);}"
                                        "QPushButton::checked{"
                                        "background: rgb(170, 170, 170);"
                                        "color: white;}").arg(PublicFunction::getScaleSize(2)));
    ui->pStatic->setStyleSheet(QString("QPushButton{background: transparent;"
                                        "border: none;"
                                        "border-radius: %1px;"
                                        "color: rgb(102, 102, 102);}"
                                        "QPushButton::checked{"
                                        "background: rgb(170, 170, 170);"
                                       "color: white;}").arg(PublicFunction::getScaleSize(2)));


    this->setFixedSize(PublicFunction::getScaleSize(192, 247));
}

int ControlMenu::getBorder()
{
    return BORDER;
}

void ControlMenu::paintEvent(QPaintEvent *event)
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
        int radius = PublicFunction::getScaleSize(12);
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

void ControlMenu::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);
    ui->frame->setLayout(ui->horizontalLayout);
    ui->horizontalLayoutWidget->hide();

    ui->pRotateLeft->mSetIcon(QPixmap("://images/xuanzhuan@2x.png"));
    ui->pRotateLeft->mSetColor(QColor(238, 238, 238), QColor(), QColor(238, 238, 238));
    ui->pRotateLeft->mSetText(tr("左旋转"), QColor(102, 102, 102), QColor(20,134,250));

    ui->pRotateRight->mSetIcon(QPixmap("://images/xuanzhuan2@2x.png"));
    ui->pRotateRight->mSetColor(QColor(238, 238, 238), QColor(), QColor(238, 238, 238));
    ui->pRotateRight->mSetText(tr("右旋转"), QColor(102, 102, 102), QColor(20,134,250));

    ui->pZoomIn->mSetIcon(QPixmap("://images/suofang2@2x.png"));
    ui->pZoomIn->mSetColor(QColor(238, 238, 238), QColor(), QColor(238, 238, 238));
    ui->pZoomIn->mSetText(tr("放大"), QColor(102, 102, 102), QColor(20,134,250));

    ui->pZoomOut->mSetIcon(QPixmap("://images/suofang@2x.png"));
    ui->pZoomOut->mSetColor(QColor(238, 238, 238), QColor(), QColor(238, 238, 238));
    ui->pZoomOut->mSetText(tr("缩小"), QColor(102, 102, 102), QColor(20,134,250));

    ui->pDynamic->setText(tr("实时"));
    ui->pStatic->setText(tr("定格"));

    QButtonGroup *group = new QButtonGroup(this);
    group->setExclusive(true);
    group->addButton(ui->pDynamic);
    group->addButton(ui->pStatic);

    connect(ui->pDynamic, &QPushButton::clicked, [=](){ e_FreezeFrame = false; });
    connect(ui->pStatic, &QPushButton::clicked, [=](){ e_FreezeFrame = true; });
    connect(ui->pRotateLeft, &CustomPushButton_1::clicked, [=](){ emit this->leftRotate(); });
    connect(ui->pRotateRight, &CustomPushButton_1::clicked, [=](){ emit this->rightRotate(); });
    connect(ui->pZoomIn, &CustomPushButton_1::clicked, [=](){ emit this->zoomIn(); });
    connect(ui->pZoomOut, &CustomPushButton_1::clicked, [=](){ emit this->zoomOut(); });
}
