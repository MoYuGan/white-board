#include "graphicspanel.h"
#include "ui_graphicspanel.h"

GraphicsPanel::GraphicsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicsPanel)
{
    ui->setupUi(this);
    this->initWidget();
}

GraphicsPanel::~GraphicsPanel()
{
    delete ui;
}

void GraphicsPanel::show()
{
    QWidget::show();
    this->raise();
}

void GraphicsPanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

void GraphicsPanel::resizeWidget()
{
    QSize size = Public_Function::getScaleSize(QSize(596, 468));
    this->setFixedSize(size);
    ui->verticalLayout->setContentsMargins(0, Public_Function::getScaleSize(20), 0, 0);
    ui->verticalLayout->setSpacing(Public_Function::getScaleSize(10));
    ui->gridLayout->setContentsMargins(Public_Function::getScaleSize(27), 0,
                                       Public_Function::getScaleSize(27), 0);
    ui->gridLayout->setHorizontalSpacing(0);
    ui->gridLayout->setVerticalSpacing(Public_Function::getScaleSize(20));
    ui->gridLayout_2->setContentsMargins(Public_Function::getScaleSize(27), 0,
                                       Public_Function::getScaleSize(27), 0);
    ui->gridLayout_2->setHorizontalSpacing(0);
    ui->gridLayout_2->setVerticalSpacing(Public_Function::getScaleSize(20));
    ui->horizontalLayout->setSpacing(Public_Function::getScaleSize(13));
    ui->horizontalLayout->setContentsMargins(Public_Function::getScaleSize(17), 0, 0, 0);
    size = Public_Function::getScaleSize(QSize(70, 70));
    ui->pGraphic1->setFixedSize(size);
    ui->pGraphic2->setFixedSize(size);
    ui->pGraphic3->setFixedSize(size);
    ui->pGraphic4->setFixedSize(size);
    ui->pGraphic5->setFixedSize(size);
    ui->pGraphic6->setFixedSize(size);
    ui->pGraphic7->setFixedSize(size);
    ui->pGraphic8->setFixedSize(size);
    ui->pGraphic9->setFixedSize(size);
    ui->pGraphic10->setFixedSize(size);
    ui->pGraphic11->setFixedSize(size);
    ui->pGraphic12->setFixedSize(size);
    ui->pGraphic13->setFixedSize(size);
    ui->pGraphic14->setFixedSize(size);
    ui->pGraphic15->setFixedSize(size);
    ui->pGraphic16->setFixedSize(size);
    ui->pGraphic17->setFixedSize(size);
    ui->pGraphic18->setFixedSize(size);
    ui->pGraphic19->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(70, 70));
    ui->pGraphic3d1->setFixedSize(size);
    ui->pGraphic3d2->setFixedSize(size);
    ui->pGraphic3d3->setFixedSize(size);
    ui->pGraphic3d4->setFixedSize(size);
    ui->pGraphic3d5->setFixedSize(size);
    ui->label_null->setFixedSize(size);
    ui->label_null_2->setFixedSize(size);
    ui->label_line_6->hide();
//    ui->label_3d->hide();
//    ui->pGraphic3d1->hide();
//    ui->pGraphic3d2->hide();
//    ui->pGraphic3d3->hide();
//    ui->pGraphic3d4->hide();
//    ui->pGraphic3d5->hide();
    size = Public_Function::getScaleSize(QSize(50, 50));
    ui->pGraphic1->mSetIconSize(size);
    ui->pGraphic2->mSetIconSize(size);
    ui->pGraphic3->mSetIconSize(size);
    ui->pGraphic4->mSetIconSize(size);
    ui->pGraphic5->mSetIconSize(size);
    ui->pGraphic6->mSetIconSize(size);
    ui->pGraphic7->mSetIconSize(size);
    ui->pGraphic8->mSetIconSize(size);
    ui->pGraphic9->mSetIconSize(size);
    ui->pGraphic10->mSetIconSize(size);
    ui->pGraphic11->mSetIconSize(size);
    ui->pGraphic12->mSetIconSize(size);
    ui->pGraphic13->mSetIconSize(size);
    ui->pGraphic14->mSetIconSize(size);
    ui->pGraphic15->mSetIconSize(size);
    ui->pGraphic16->mSetIconSize(size);
    ui->pGraphic17->mSetIconSize(size);
    ui->pGraphic18->mSetIconSize(size);
    ui->pGraphic19->mSetIconSize(size);
    ui->pGraphic3d1->mSetIconSize(size);
    ui->pGraphic3d2->mSetIconSize(size);
    ui->pGraphic3d3->mSetIconSize(size);
    ui->pGraphic3d4->mSetIconSize(size);
    ui->pGraphic3d5->mSetIconSize(size);
    size = Public_Function::getScaleSize(QSize(548, 1));
    ui->label_line_5->setFixedSize(size);
    ui->label_line_6->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(29, 22));
    ui->pGraphicPanelBack->setFixedSize(size);
    ui->label_2d->setContentsMargins(Public_Function::getScaleSize(30), 0, 0, 0);
    ui->label_3d->setContentsMargins(Public_Function::getScaleSize(30), 0, 0, 0);
    ui->label_graphic->setFont(Public_Function::getFont(13));
}

void GraphicsPanel::paintEvent(QPaintEvent *event)
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
    int border = 6;
    int alpha;
    for(int i = 0; i < border; i++)
    {
        QRect rect = QRect(QPoint(border - i, border - i),
                           QPoint(this->width() - (border - i),
                            this->height() - (border - i)));
        QPainterPath path;
        int radius = Public_Function::getScaleSize(12);
        path = Public_Function::getRoundRectPath(rect, radius);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }
        switch(i)
        {
        case 0: alpha = 80; break;
        case 1: alpha = 50; break;
        case 2: alpha = 30; break;
        case 3: alpha = 15; break;
        case 4: alpha = 10; break;
        case 5: alpha = 7; break;
        }
        color.setAlpha(alpha);
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void GraphicsPanel::initWidget()
{
    ui->verticalLayoutWidget_6->hide();
    this->setLayout(ui->verticalLayout);
    ui->verticalLayout->setAlignment(ui->label_line_5, Qt::AlignCenter);
    ui->verticalLayout->setAlignment(ui->label_line_6, Qt::AlignCenter);
    ui->pGraphic1->mSetIcon(QPixmap(":/images/main/graphic/tuxing1@2x.png"));
    ui->pGraphic1->mSetText(tr("直线"));
    ui->pGraphic2->mSetIcon(QPixmap(":/images/main/graphic/tuxing2@2x.png"));
    ui->pGraphic2->mSetText(tr("虚线"));
    ui->pGraphic3->mSetIcon(QPixmap(":/images/main/graphic/tuxing3@2x.png"));
    ui->pGraphic3->mSetText(tr("线段"));
    ui->pGraphic4->mSetIcon(QPixmap(":/images/main/graphic/tuxing4@2x.png"));
    ui->pGraphic4->mSetText(tr("箭头"));
    ui->pGraphic5->mSetIcon(QPixmap(":/images/main/graphic/tuxing5@2x.png"));
    ui->pGraphic5->mSetText(tr("双箭头"));
    //ui->pGraphic6->mSetIcon(QPixmap(":/images/main/graphic/tuxing6@2x.png"));
    //ui->pGraphic6->mSetText(tr("圆形"));
    ui->pGraphic6->mSetIcon(QPixmap(":/images/main/graphic/tuxing7@2x.png"));
    ui->pGraphic6->mSetText(tr("椭圆"));
    ui->pGraphic7->mSetIcon(QPixmap(":/images/main/graphic/tuxing8@2x.png"));
    ui->pGraphic7->mSetText(tr("矩形"));
    ui->pGraphic8->mSetIcon(QPixmap(":/images/main/graphic/tuxing9@2x.png"));
    ui->pGraphic8->mSetText(tr("圆角矩形"));
    ui->pGraphic9->mSetIcon(QPixmap(":/images/main/graphic/tuxing10@2x.png"));
    ui->pGraphic9->mSetText(tr("平行四边形"));
    ui->pGraphic10->mSetIcon(QPixmap(":/images/main/graphic/tuxing11@2x.png"));
    ui->pGraphic10->mSetText(tr("菱形"));
    ui->pGraphic11->mSetIcon(QPixmap(":/images/main/graphic/tuxing12@2x.png"));
    ui->pGraphic11->mSetText(tr("梯形"));
    ui->pGraphic12->mSetIcon(QPixmap(":/images/main/graphic/tuxing13@2x.png"));
    ui->pGraphic12->mSetText(tr("扇形"));
    ui->pGraphic13->mSetIcon(QPixmap(":/images/main/graphic/tuxing14@2x.png"));
    ui->pGraphic13->mSetText(tr("三角形"));
    ui->pGraphic14->mSetIcon(QPixmap(":/images/main/graphic/tuxing15@2x.png"));
    ui->pGraphic14->mSetText(tr("直角三角形"));
    ui->pGraphic15->mSetIcon(QPixmap(":/images/main/graphic/tuxing16@2x.png"));
    ui->pGraphic15->mSetText(tr("五边形"));
    ui->pGraphic16->mSetIcon(QPixmap(":/images/main/graphic/tuxing17@2x.png"));
    ui->pGraphic16->mSetText(tr("六边形"));
    ui->pGraphic17->mSetIcon(QPixmap(":/images/main/graphic/tuxing18@2x.png"));
    ui->pGraphic17->mSetText(tr("多边形"));
    ui->pGraphic17->hide();
    ui->pGraphic18->mSetIcon(QPixmap(":/images/main/graphic/tuxing19@2x.png"));
    ui->pGraphic18->mSetText(tr("五角星"));
    ui->pGraphic19->mSetIcon(QPixmap(":/images/main/graphic/tuxing20@2x.png"));
    ui->pGraphic19->mSetText(tr("田字格"));
    ui->pGraphic3d1->mSetIcon(QPixmap(":/images/main/graphic/tuxing21@2x.png"));
    ui->pGraphic3d1->mSetText(tr("立方体"));
    ui->pGraphic3d2->mSetIcon(QPixmap(":/images/main/graphic/tuxing22@2x.png"));
    ui->pGraphic3d2->mSetText(tr("圆柱体"));
    ui->pGraphic3d3->mSetIcon(QPixmap(":/images/main/graphic/tuxing23@2x.png"));
    ui->pGraphic3d3->mSetText(tr("圆锥体"));
    ui->pGraphic3d4->mSetIcon(QPixmap(":/images/main/graphic/tuxing24@2x.png"));
    ui->pGraphic3d4->mSetText(tr("三棱锥"));
    ui->pGraphic3d5->mSetIcon(QPixmap(":/images/main/graphic/tuxing25@2x.png"));
    ui->pGraphic3d5->mSetText(tr("四棱锥"));
    QButtonGroup *buttongroup3 = new QButtonGroup(this);
    buttongroup3->addButton(ui->pGraphic1);
    buttongroup3->addButton(ui->pGraphic2);
    buttongroup3->addButton(ui->pGraphic3);
    buttongroup3->addButton(ui->pGraphic4);
    buttongroup3->addButton(ui->pGraphic5);
    buttongroup3->addButton(ui->pGraphic6);
    buttongroup3->addButton(ui->pGraphic7);
    buttongroup3->addButton(ui->pGraphic8);
    buttongroup3->addButton(ui->pGraphic9);
    buttongroup3->addButton(ui->pGraphic10);
    buttongroup3->addButton(ui->pGraphic11);
    buttongroup3->addButton(ui->pGraphic12);
    buttongroup3->addButton(ui->pGraphic13);
    buttongroup3->addButton(ui->pGraphic14);
    buttongroup3->addButton(ui->pGraphic15);
    buttongroup3->addButton(ui->pGraphic16);
    buttongroup3->addButton(ui->pGraphic17);
    buttongroup3->addButton(ui->pGraphic18);
    buttongroup3->addButton(ui->pGraphic19);
    buttongroup3->addButton(ui->pGraphic3d1);
    buttongroup3->addButton(ui->pGraphic3d2);
    buttongroup3->addButton(ui->pGraphic3d3);
    buttongroup3->addButton(ui->pGraphic3d4);
    buttongroup3->addButton(ui->pGraphic3d5);
    connect(buttongroup3, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onBtnGroupToggled(QAbstractButton*)));
    connect(ui->pGraphicPanelBack, &PushButton_Basic::clicked, this, [=](){  emit this->goBack(); });
}

void GraphicsPanel::updateLanguage()
{
    ui->label_2d->setText(tr("二维图形"));
    ui->label_3d->setText(tr("三维图形"));
    ui->label_graphic->setText(tr("图形"));

    ui->pGraphic1->mSetText(tr("直线"));
    ui->pGraphic2->mSetText(tr("虚线"));
    ui->pGraphic3->mSetText(tr("线段"));
    ui->pGraphic4->mSetText(tr("箭头"));
    ui->pGraphic5->mSetText(tr("双箭头"));
    ui->pGraphic6->mSetText(tr("椭圆"));
    ui->pGraphic7->mSetText(tr("矩形"));
    ui->pGraphic8->mSetText(tr("圆角矩形"));
    ui->pGraphic9->mSetText(tr("平行四边形"));

    ui->pGraphic10->mSetText(tr("菱形"));
    ui->pGraphic11->mSetText(tr("梯形"));
    ui->pGraphic12->mSetText(tr("扇形"));
    ui->pGraphic13->mSetText(tr("三角形"));
    ui->pGraphic14->mSetText(tr("直角三角形"));
    ui->pGraphic15->mSetText(tr("五边形"));
    ui->pGraphic16->mSetText(tr("六边形"));
    ui->pGraphic17->mSetText(tr("多边形"));
    ui->pGraphic18->mSetText(tr("五角星"));
    ui->pGraphic19->mSetText(tr("田字格"));
    ui->pGraphic3d1->mSetText(tr("立方体"));
    ui->pGraphic3d2->mSetText(tr("圆柱体"));
    ui->pGraphic3d3->mSetText(tr("圆锥体"));
    ui->pGraphic3d4->mSetText(tr("三棱锥"));
    ui->pGraphic3d5->mSetText(tr("四棱锥"));


}

void GraphicsPanel::onBtnGroupToggled(QAbstractButton *button)
{
    g_DrawGraphic = true;
    if (ui->pGraphic1 == button)
        g_GraphicType = GraphicType::ZhiXian;
    else if (ui->pGraphic2 == button)
        g_GraphicType = GraphicType::XvXian;
    else if (ui->pGraphic3 == button)
        g_GraphicType = GraphicType::XianDuan;
    else if (ui->pGraphic4 == button)
        g_GraphicType = GraphicType::JianTou;
    else if (ui->pGraphic5 == button)
        g_GraphicType = GraphicType::ShuangJianTou;
    else if (ui->pGraphic6 == button)
        g_GraphicType = GraphicType::TuoYuan;
    else if (ui->pGraphic7 == button)
        g_GraphicType = GraphicType::JuXing;
    else if (ui->pGraphic8 == button)
        g_GraphicType = GraphicType::YuanJiaoJuXing;
    else if (ui->pGraphic9 == button)
        g_GraphicType = GraphicType::PingXingSiBianXing;
    else if (ui->pGraphic10 == button)
        g_GraphicType = GraphicType::LingXing;
    else if (ui->pGraphic11 == button)
        g_GraphicType = GraphicType::TiXing;
    else if (ui->pGraphic12 == button)
        g_GraphicType = GraphicType::ShanXing;
    else if (ui->pGraphic13 == button)
        g_GraphicType = GraphicType::SanJiaoXing;
    else if (ui->pGraphic14 == button)
        g_GraphicType = GraphicType::ZhiJiaoSanJiaoXing;
    else if (ui->pGraphic15 == button)
        g_GraphicType = GraphicType::WuBianXing;
    else if (ui->pGraphic16 == button)
        g_GraphicType = GraphicType::LiuBianXing;
    else if (ui->pGraphic17 == button)
        g_GraphicType = GraphicType::DuoBianXing;
    else if (ui->pGraphic18 == button)
        g_GraphicType = GraphicType::WuJiaoXing;
    else if (ui->pGraphic19 == button)
        g_GraphicType = GraphicType::TianZiGe;
    else if (ui->pGraphic3d1 == button)
        g_GraphicType = GraphicType::LiFangTi;
    else if (ui->pGraphic3d2 == button)
        g_GraphicType = GraphicType::YuanZhuTi;
    else if (ui->pGraphic3d3 == button)
        g_GraphicType = GraphicType::YuanZhuiTi;
    else if (ui->pGraphic3d4 == button)
        g_GraphicType = GraphicType::SanLengZhui;
    else if (ui->pGraphic3d5 == button)
        g_GraphicType = GraphicType::SiLengZhui;
}

