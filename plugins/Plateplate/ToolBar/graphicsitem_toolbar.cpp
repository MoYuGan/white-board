#include "graphicsitem_toolbar.h"
#include "ui_graphicsitem_toolbar.h"

GraphicsItem_ToolBar::GraphicsItem_ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicsItem_ToolBar)
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    ui->setupUi(this);
    this->initWidget();
    this->resize();
}

GraphicsItem_ToolBar::~GraphicsItem_ToolBar()
{
    delete ui;
}

void GraphicsItem_ToolBar::resize()
{
    this->setFixedSize(PublicFunction::getScaleSize(272, 90));
    ui->horizontalLayout->setContentsMargins(PublicFunction::getScaleSize(10), PublicFunction::getScaleSize(10),
                                             PublicFunction::getScaleSize(10), PublicFunction::getScaleSize(10));

    int radius = PublicFunction::getScaleSize(10);
    ui->pClone->mSetRadius(radius);
    ui->pStayOnTop->mSetRadius(radius);
    ui->pStayOnBottom->mSetRadius(radius);
    ui->pDelete->mSetRadius(radius);

    QSize size = PublicFunction::getScaleSize(60, 70);
    ui->pClone->setFixedSize(size);
    ui->pStayOnTop->setFixedSize(size);
    ui->pStayOnBottom->setFixedSize(size);
    ui->pDelete->setFixedSize(size);
    size = PublicFunction::getScaleSize(40, 40);
    ui->pClone->mSetIconSize(size);
    ui->pStayOnTop->mSetIconSize(size);
    ui->pStayOnBottom->mSetIconSize(size);
    ui->pDelete->mSetIconSize(size);

    QFont font = PublicFunction::getFont(12);
    ui->pClone->mSetFont(font);
    ui->pStayOnTop->mSetFont(font);
    ui->pStayOnBottom->mSetFont(font);
    ui->pDelete->mSetFont(font);

    ui->pClone->mSetMargin(0, PublicFunction::getScaleSize(3), 0, PublicFunction::getScaleSize(9));
    ui->pStayOnTop->mSetMargin(0, PublicFunction::getScaleSize(3), 0, PublicFunction::getScaleSize(9));
    ui->pStayOnBottom->mSetMargin(0, PublicFunction::getScaleSize(3), 0, PublicFunction::getScaleSize(9));
    ui->pDelete->mSetMargin(0, PublicFunction::getScaleSize(3), 0, PublicFunction::getScaleSize(9));
}

void GraphicsItem_ToolBar::setCloneChecked(bool checked)
{
    ui->pClone->setChecked(checked);
}

void GraphicsItem_ToolBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor color(135, 135, 135);
    int border = 4;
    int radius = PublicFunction::getScaleSize(12);
    for(int i = 0; i < border; i++)
    {
        QRect rect = QRect(QPoint(border - i, border - i),
                           QPoint(this->width() - (border - i), this->height() - (border - i)));

        QPainterPath path;
        path = PublicFunction::getRoundRectPath(rect, radius, radius, radius, radius);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }

        switch(i)
        {
        case 0:
            color.setAlpha(80);
            break;
        case 1:
            color.setAlpha(50);
            break;
        case 2:
            color.setAlpha(20);
            break;
        case 3:
            color.setAlpha(15);
            break;
        case 4:
            color.setAlpha(10);
            break;
        case 5:
            color.setAlpha(7);
            break;
        default:
            break;
        }
        QPen pen;
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void GraphicsItem_ToolBar::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);

    ui->pClone->mEnabledChecked();
    ui->pClone->mSetIcon(QPixmap(":/images/copy@2x.png"), QPixmap(":/images/copy2@2x.png"));
    ui->pStayOnTop->mSetIcon(QPixmap(":/images/top@2x.png"));
    ui->pStayOnBottom->mSetIcon(QPixmap(":/images/down-1@2x.png"));
    ui->pDelete->mSetIcon(QPixmap(":/images/delete@2x.png"));
    ui->pClone->mSetText(tr("克隆 "));
    ui->pStayOnTop->mSetText(tr("置顶"));
    ui->pStayOnBottom->mSetText(tr("置底 "));
    ui->pDelete->mSetText(tr("删除 "));
    ui->pClone->mSetTextColor(QColor(102, 102, 102), Qt::white);
    ui->pStayOnTop->mSetTextColor(QColor(102, 102, 102));
    ui->pStayOnBottom->mSetTextColor(QColor(102, 102, 102));
    ui->pDelete->mSetTextColor(QColor(102, 102, 102));
    ui->pClone->mSetColor(QColor(238,238,238), QColor(), QColor(20,134,250));
    ui->pStayOnTop->mSetColor(QColor(238,238,238), QColor(), QColor(20,134,250));
    ui->pStayOnBottom->mSetColor(QColor(238,238,238), QColor(), QColor(20,134,250));
    ui->pDelete->mSetColor(QColor(238,238,238), QColor(), QColor(20,134,250));

    connect(ui->pClone, &CustomPushButton_1::toggled, [=](bool checked){ emit actionClone(checked); });
    connect(ui->pStayOnTop, &CustomPushButton_1::clicked, [=](){emit actionStayOnTop();});
    connect(ui->pStayOnBottom, &CustomPushButton_1::clicked, [=](){emit actionStayOnBottom();});
    connect(ui->pDelete, &CustomPushButton_1::clicked, [=](){emit actionDelete();});
}
