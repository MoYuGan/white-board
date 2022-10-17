#include "maintoolbar_midleft.h"
#include "ui_maintoolbar_midleft.h"

static int BORDER = 0;    //阴影边距
static int BORDER_1 = 0;

MainToolBar_MidLeft::MainToolBar_MidLeft(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainToolBar_MidLeft)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
}

MainToolBar_MidLeft::~MainToolBar_MidLeft()
{
    delete ui;
}

void MainToolBar_MidLeft::resize()
{
    BORDER = PublicFunction::getScaleSize(3);
    BORDER_1 = PublicFunction::getScaleSize(3);
    int spacing = PublicFunction::getScaleSize(10);
    int marginLeftRight = BORDER + PublicFunction::getScaleSize(12);
    int marginTopBottom = BORDER + PublicFunction::getScaleSize(5);
    ui->horizontalLayout->setContentsMargins(marginLeftRight, 0, marginLeftRight, marginTopBottom);
    ui->horizontalLayout->setSpacing(spacing);

    if (ui->pMove->isChecked())
        ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    else
        ui->verticalLayout->setContentsMargins(0, marginTopBottom + BORDER_1, 0, 0);

    if (ui->pPen->isChecked())
        ui->verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    else
        ui->verticalLayout_2->setContentsMargins(0, marginTopBottom + BORDER_1, 0, 0);

    if (ui->pEraser->isChecked())
        ui->verticalLayout_3->setContentsMargins(0, 0, 0, 0);
    else
        ui->verticalLayout_3->setContentsMargins(0, marginTopBottom + BORDER_1, 0, 0);

    ui->verticalLayout_4->setContentsMargins(0, marginTopBottom + BORDER_1, 0, 0);
    ui->verticalLayout_5->setContentsMargins(0, marginTopBottom + BORDER_1, 0, 0);

    QSize size = PublicFunction::getScaleSize(50, 50);
    ui->pMove->mSetIconSize(size);
    ui->pPen->mSetIconSize(size);
    ui->pEraser->mSetIconSize(size);
    ui->pUndo->mSetIconSize(size);
    ui->pRedo->mSetIconSize(size);
    size = PublicFunction::getScaleSize(70, 70);
    ui->pMove->setFixedWidth(size.width());
    ui->pPen->setFixedWidth(size.width());
    ui->pEraser->setFixedWidth(size.width());
    ui->pUndo->setFixedWidth(size.width());
    ui->pRedo->setFixedWidth(size.width());
    int radius = PublicFunction::getScaleSize(4);
    ui->pMove->mSetRadius(radius);
    ui->pPen->mSetRadius(radius);
    ui->pEraser->mSetRadius(radius);
    ui->pUndo->mSetRadius(radius);
    ui->pRedo->mSetRadius(radius);
    QFont font = PublicFunction::getFont(14);
    ui->pMove->mSetFont(font);
    ui->pPen->mSetFont(font);
    ui->pEraser->mSetFont(font);
    ui->pUndo->mSetFont(font);
    ui->pRedo->mSetFont(font);

    int btnCount = 5;
    this->setFixedSize(ui->pMove->width() * btnCount + spacing * (btnCount - 1) + marginLeftRight*2,
                       size.height() + marginTopBottom*2 + BORDER_1);
}

int MainToolBar_MidLeft::getBorder()
{
    return BORDER;
}

void MainToolBar_MidLeft::setActionChecked(int index, bool checked)
{
    if (0 == index)
        ui->pMove->setChecked(checked);
}

void MainToolBar_MidLeft::paintEvent(QPaintEvent *event)
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
        QRect rect = QRect(QPoint(BORDER - i, BORDER + BORDER_1 - i),
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

void MainToolBar_MidLeft::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);

    ui->pMove->mSetIcon(QPixmap("://images/yidong@2x.png"), QPixmap("://images/yidong2@2x.png"));
    ui->pMove->mSetColor(QColor(238, 238, 238));
    ui->pMove->mSetText(tr("移动"), QColor(102, 102, 102), QColor(20,134,250));
    ui->pPen->mSetIcon(QPixmap("://images/bichu_1@2x.png"), QPixmap("://images/bichu_2@2x.png"));
    ui->pPen->mSetColor(QColor(238, 238, 238));
    ui->pPen->mSetText(tr("批注"), QColor(102, 102, 102), QColor(20,134,250));
    ui->pEraser->mSetIcon(QPixmap("://images/cachu_1@2x.png"), QPixmap("://images/cachu_2@2x.png"));
    ui->pEraser->mSetColor(QColor(238, 238, 238));
    ui->pEraser->mSetText(tr("橡皮擦"), QColor(102, 102, 102), QColor(20,134,250));
    ui->pUndo->mSetIcon(QPixmap("://images/chexiao_1@2x.png"));
    ui->pUndo->mSetColor(QColor(238, 238, 238));
    ui->pUndo->mSetText(tr("撤销"), QColor(102, 102, 102), QColor(20,134,250));
    ui->pRedo->mSetIcon(QPixmap("://images/huifu_1@2x.png"));
    ui->pRedo->mSetColor(QColor(238, 238, 238));
    ui->pRedo->mSetText(tr("恢复"), QColor(102, 102, 102), QColor(20,134,250));

    m_BtnGroup = new QButtonGroup(this);
    m_BtnGroup->setExclusive(true);
    m_BtnGroup->addButton(ui->pMove);
    m_BtnGroup->addButton(ui->pPen);
    m_BtnGroup->addButton(ui->pEraser);
    connect(m_BtnGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onBtnGroupToggled(QAbstractButton*,bool)));
    connect(ui->pUndo, &CustomPushButton_1::clicked, [=](){ emit this->undoSignal(); });
    connect(ui->pRedo, &CustomPushButton_1::clicked, [=](){ emit this->redoSignal(); });
}

void MainToolBar_MidLeft::onBtnGroupToggled(QAbstractButton *button, bool checked)
{
    int marginTopBottom = BORDER + BORDER_1 + PublicFunction::getScaleSize(5);
    if (button == ui->pMove) {
        if (checked)
            ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
        else
            ui->verticalLayout->setContentsMargins(0, marginTopBottom, 0, 0);
        emit moveBtnToggled(checked);
    }else if (button == ui->pPen) {
        if (checked)
            ui->verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        else
            ui->verticalLayout_2->setContentsMargins(0, marginTopBottom, 0, 0);
        emit penBtnToggled(checked);
    }else if (button == ui->pEraser) {
        if (checked)
            ui->verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        else
            ui->verticalLayout_3->setContentsMargins(0, marginTopBottom, 0, 0);
        emit eraserBtnToggled(checked);
    }
}
