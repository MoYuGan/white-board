#include "maintoolbar_midright.h"
#include "ui_maintoolbar_midright.h"

static int BORDER = 0;    //阴影边距

MainToolBar_MidRight::MainToolBar_MidRight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainToolBar_MidRight)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
    this->setEnabled(false);
}

MainToolBar_MidRight::~MainToolBar_MidRight()
{
    delete ui;
}

void MainToolBar_MidRight::resize()
{
    BORDER = PublicFunction::getScaleSize(3);
    int spacing = PublicFunction::getScaleSize(10);
    int marginLeftRight = BORDER + PublicFunction::getScaleSize(12);
    int marginTopBottom = BORDER + PublicFunction::getScaleSize(5);
    ui->horizontalLayout->setContentsMargins(marginLeftRight, marginTopBottom,
                                             marginLeftRight, marginTopBottom);
    ui->horizontalLayout->setSpacing(spacing);

    QSize size = PublicFunction::getScaleSize(50, 50);
    //ui->pScreenShots->mSetIconSize(size);
    ui->pOCR->mSetIconSize(size);
    ui->pTackPhoto->mSetIconSize(size);
    ui->pControl->mSetIconSize(size);
    size = PublicFunction::getScaleSize(70, 70);
    //ui->pScreenShots->setFixedWidth(size.width());
    ui->pOCR->setFixedWidth(size.width());
    ui->pTackPhoto->setFixedWidth(size.width());
    ui->pControl->setFixedWidth(size.width());
    int radius = PublicFunction::getScaleSize(4);
    //ui->pScreenShots->mSetRadius(radius);
    ui->pOCR->mSetRadius(radius);
    ui->pTackPhoto->setFixedWidth(size.width());
    ui->pControl->mSetRadius(radius);
    QFont font = PublicFunction::getFont(14);
    //ui->pScreenShots->mSetFont(font);
    ui->pOCR->mSetFont(font);
    ui->pTackPhoto->mSetFont(font);
    ui->pControl->mSetFont(font);
    ui->pScreenShots->setFixedSize(0, 0);
    ui->pScreenShots->hide();

    m_ControlMenu->resize();

    int btnCount = 3;
    this->setFixedSize(ui->pOCR->width() * btnCount + spacing * (btnCount - 1) + marginLeftRight * 2,
                       size.height() + marginTopBottom * 2);
}

int MainToolBar_MidRight::getBorder()
{
    return BORDER;
}

void MainToolBar_MidRight::setEnabled(bool enabled)
{
    ui->pTackPhoto->mSetEnabled(enabled, QColor(136,136,136));
}

void MainToolBar_MidRight::hideMenu()
{
    ui->pControl->setChecked(false);
}

void MainToolBar_MidRight::paintEvent(QPaintEvent *event)
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

void MainToolBar_MidRight::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);

    ui->pScreenShots->mSetIcon(QPixmap("://images/jietu@2x.png"));
    ui->pScreenShots->mSetColor(QColor(238, 238, 238));
    ui->pScreenShots->mSetText(tr("截图"), QColor(102, 102, 102), QColor(20,134,250));

    ui->pOCR->mSetIcon(QPixmap("://images/wenzishibie@2x.png"));
    ui->pOCR->mSetColor(QColor(238, 238, 238));
    ui->pOCR->mSetText(tr("文字识别"), QColor(102, 102, 102), QColor(20,134,250));

    ui->pTackPhoto->mSetIcon(QPixmap("://images/paizhao@2x.png"));
    ui->pTackPhoto->mSetColor(QColor(238, 238, 238));
    ui->pTackPhoto->mSetText(tr("拍照"), QColor(102, 102, 102), QColor(20,134,250));

    ui->pControl->mSetIcon(QPixmap("://images/gengduo_1@2x.png"));
    ui->pControl->mSetColor(QColor(238, 238, 238), QColor(), QColor(238, 238, 238));
    ui->pControl->mSetText(tr("画面控制"), QColor(102, 102, 102), QColor(20,134,250));

    m_ControlMenu = new ControlMenu((QWidget *)this->parent());
    m_ControlMenu->hide();

    connect(ui->pScreenShots, &CustomPushButton_1::clicked, [=](){ emit this->action_screenshots(); });
    connect(ui->pOCR, &CustomPushButton_1::clicked, [=](){ emit this->action_ocr(); });
    connect(ui->pTackPhoto, &CustomPushButton_1::clicked, [=]() { emit this->action_tackphoto();});
    connect(ui->pControl, &CustomPushButton_1::toggled, this, &MainToolBar_MidRight::showControlMenu);
    connect(m_ControlMenu, &ControlMenu::leftRotate, [=](){ emit this->leftRotate(); });
    connect(m_ControlMenu, &ControlMenu::rightRotate, [=](){ emit this->rightRotate(); });
    connect(m_ControlMenu, &ControlMenu::zoomIn, [=](){ emit this->zoomIn(); });
    connect(m_ControlMenu, &ControlMenu::zoomOut, [=](){ emit this->zoomOut(); });
}

void MainToolBar_MidRight::showControlMenu(bool checked)
{
    if (checked) {
        m_ControlMenu->move(QPoint(this->x() + ui->pTackPhoto->x() + ui->pTackPhoto->width()/2 - m_ControlMenu->width()/2,
                                   this->y() - PublicFunction::getScaleSize(16) + m_ControlMenu->getBorder() - m_ControlMenu->height()));
        m_ControlMenu->show();
        m_ControlMenu->raise();
    }else {
        m_ControlMenu->hide();
    }
}

