#include "rulerpanel.h"
#include "ui_rulerpanel.h"

RulerPanel::RulerPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RulerPanel)
{
    ui->setupUi(this);
    this->initWidget();
}

RulerPanel::~RulerPanel()
{
    delete ui;
}

void RulerPanel::show()
{
    QWidget::show();
    this->raise();
}

void RulerPanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

void RulerPanel::resizeWidget()
{
    QSize size = Public_Function::getScaleSize(QSize(432, 156));
    this->setFixedSize(size);
    ui->verticalLayout->setContentsMargins(0, Public_Function::getScaleSize(10), 0, 0);
    ui->verticalLayout->setSpacing(Public_Function::getScaleSize(15));
    ui->gridLayout->setContentsMargins(Public_Function::getScaleSize(25), 0,
                                       Public_Function::getScaleSize(25), 0);
    ui->horizontalLayout->setSpacing(Public_Function::getScaleSize(13));
    ui->horizontalLayout->setContentsMargins(Public_Function::getScaleSize(17), 0, 0, 0);
    size = Public_Function::getScaleSize(QSize(70, 70));
    ui->pChigui1->setFixedSize(size);
    ui->pChigui2->setFixedSize(size);
    ui->pChigui3->setFixedSize(size);
    ui->pChigui4->setFixedSize(size);
    ui->pChigui5->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(50, 50));
    ui->pChigui1->mSetIconSize(size);
    ui->pChigui2->mSetIconSize(size);
    ui->pChigui3->mSetIconSize(size);
    ui->pChigui4->mSetIconSize(size);
    ui->pChigui5->mSetIconSize(size);
    size = Public_Function::getScaleSize(QSize(384, 1));
    ui->label_line_9->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(29, 22));
    ui->pChiguiPanelBack->setFixedSize(size);
    ui->label_chigui->setFont(Public_Function::getFont(13));
}

void RulerPanel::updateLanguage()
{
    ui->pChigui1->mSetText(tr("直尺"));
    ui->pChigui2->mSetText(tr("60°三角尺"));
    ui->pChigui3->mSetText(tr("45°三角尺"));
    ui->pChigui4->mSetText(tr("量角器"));
    ui->pChigui5->mSetText(tr("圆规"));

    ui->label_chigui->setText(tr("尺子"));

}

void RulerPanel::paintEvent(QPaintEvent *event)
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

void RulerPanel::initWidget()
{
    ui->verticalLayoutWidget_9->hide();
    this->setLayout(ui->verticalLayout);
    ui->verticalLayout->setAlignment(ui->label_line_9, Qt::AlignCenter);
    ui->pChigui1->mSetIcon(QPixmap(":/images/main/chiguiPanel/chigui1@2x.png"));
    ui->pChigui1->mSetText(tr("直尺"));
    ui->pChigui2->mSetIcon(QPixmap(":/images/main/chiguiPanel/chigui2@2x.png"));
    ui->pChigui2->mSetText(tr("60°三角尺"));
    ui->pChigui3->mSetIcon(QPixmap(":/images/main/chiguiPanel/chigui3@2x.png"));
    ui->pChigui3->mSetText(tr("45°三角尺"));
    ui->pChigui4->mSetIcon(QPixmap(":/images/main/chiguiPanel/chigui4@2x.png"));
    ui->pChigui4->mSetText(tr("量角器"));
    ui->pChigui5->mSetIcon(QPixmap(":/images/main/chiguiPanel/chigui5@2x.png"));
    ui->pChigui5->mSetText(tr("圆规"));
    connect(ui->pChigui1, &PushButton_2::clicked, [=](){ emit this->addRuler(0); });
    connect(ui->pChigui2, &PushButton_2::clicked, [=](){ emit this->addRuler(1); });
    connect(ui->pChigui3, &PushButton_2::clicked, [=](){ emit this->addRuler(2); });
    connect(ui->pChigui4, &PushButton_2::clicked, [=](){ emit this->addRuler(3); });
    connect(ui->pChigui5, &PushButton_2::clicked, [=](){ emit this->addRuler(4); });
    connect(ui->pChiguiPanelBack, &PushButton_Basic::clicked, [=](){ emit this->goBack(); });
}
