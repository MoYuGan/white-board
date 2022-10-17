#include "maintoolbar_refore.h"
#include "ui_maintoolbar_refore.h"

static int BORDER = 0;    //阴影边距

MainToolBar_Refore::MainToolBar_Refore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainToolBar_Refore)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
}

MainToolBar_Refore::~MainToolBar_Refore()
{
    delete ui;
}

void MainToolBar_Refore::resize()
{
    BORDER = PublicFunction::getScaleSize(3);
    ui->pRefore->mSetIconSize(PublicFunction::getScaleSize(17, 18));
    this->setFixedSize(PublicFunction::getScaleSize(24) + BORDER * 2,
                       PublicFunction::getScaleSize(48) + BORDER * 2);
}

void MainToolBar_Refore::mSetIcon(const QPixmap &pixmap)
{
    ui->pRefore->mSetIcon(pixmap);
}

int MainToolBar_Refore::getBorder()
{
    return BORDER;
}

void MainToolBar_Refore::paintEvent(QPaintEvent *event)
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

void MainToolBar_Refore::initWidget()
{
    this->setLayout(ui->verticalLayout);
    ui->verticalLayoutWidget->hide();
    connect(ui->pRefore, &CustomPushButton_1::clicked, [=](){ emit this->btnClicked(); });
}
