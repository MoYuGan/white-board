#include "toolpanel.h"
#include "ui_toolpanel.h"

ToolPanel::ToolPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolPanel)
{
    ui->setupUi(this);
    this->initWidget();
}

ToolPanel::~ToolPanel()
{
    delete ui;
}

void ToolPanel::show()
{
    QWidget::show();
    this->raise();
}

void ToolPanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

void ToolPanel::resizeWidget()
{
    QSize size = Public_Function::getScaleSize(QSize(596, 380));    //460
    this->setFixedSize(size);
    ui->verticalLayout->setContentsMargins(0, Public_Function::getScaleSize(20), 0, 0);
    ui->verticalLayout->setSpacing(Public_Function::getScaleSize(15));
    ui->gridLayout->setContentsMargins(Public_Function::getScaleSize(27), 0,
                                       Public_Function::getScaleSize(27), 0);
    ui->gridLayout->setHorizontalSpacing(0);
    ui->gridLayout->setVerticalSpacing(Public_Function::getScaleSize(20));
    ui->gridLayout_2->setContentsMargins(Public_Function::getScaleSize(27), 0,
                                       Public_Function::getScaleSize(27), 0);
    ui->gridLayout_2->setHorizontalSpacing(0);
    ui->gridLayout_2->setVerticalSpacing(Public_Function::getScaleSize(20));
    size = Public_Function::getScaleSize(QSize(70, 70));
    ui->pTool1->setFixedSize(size);
    ui->pTool2->setFixedSize(size);
    ui->pTool3->setFixedSize(size);
    ui->pTool4->setFixedSize(size);
    ui->pTool5->setFixedSize(size);
    ui->pTool6->setFixedSize(size);
    ui->pTool7->setFixedSize(size);
    ui->pTool8->setFixedSize(size);
    ui->pTool9->setFixedSize(size);
    ui->pTool10->setFixedSize(size);
    ui->pTool11->setFixedSize(size);
    ui->pTool12->setFixedSize(size);
    ui->pTool13->setFixedSize(size);
    ui->pDisTool1->setFixedSize(size);
    ui->pDisTool2->setFixedSize(size);
    ui->pDisTool3->setFixedSize(size);
    ui->pDisTool4->setFixedSize(size);
    ui->pDisTool5->setFixedSize(size);
    ui->pDisTool6->setFixedSize(size);
    ui->pDisTool7->setFixedSize(size);
    ui->pDisTool8->setFixedSize(size);
    ui->label_NULL->setFixedSize(size);
    ui->label_NULL_2->setFixedSize(size);
    ui->label_NULL_3->setFixedSize(size);
    ui->label_NULL_4->setFixedSize(size);
    ui->label_NULL_5->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(50, 50));
    ui->pTool1->mSetIconSize(size);
    ui->pTool2->mSetIconSize(size);
    ui->pTool3->mSetIconSize(size);
    ui->pTool4->mSetIconSize(size);
    ui->pTool5->mSetIconSize(size);
    ui->pTool6->mSetIconSize(size);
    ui->pTool7->mSetIconSize(size);
    ui->pTool8->mSetIconSize(size);
    ui->pTool9->mSetIconSize(size);
    ui->pTool10->mSetIconSize(size);
    ui->pTool11->mSetIconSize(size);
    ui->pTool12->mSetIconSize(size);
    ui->pTool13->mSetIconSize(size);
    ui->pDisTool1->mSetIconSize(size);
    ui->pDisTool2->mSetIconSize(size);
    ui->pDisTool3->mSetIconSize(size);
    ui->pDisTool4->mSetIconSize(size);
    ui->pDisTool5->mSetIconSize(size);
    ui->pDisTool6->mSetIconSize(size);
    ui->pDisTool7->mSetIconSize(size);
    ui->pDisTool8->mSetIconSize(size);
    ui->label_utool->setFont(Public_Function::getFont(13));
    ui->label_dtool->setFont(Public_Function::getFont(13));
    size = Public_Function::getScaleSize(QSize(556, 1));
    ui->label_line_4->setFixedSize(size);
    ui->label_utool->setContentsMargins(Public_Function::getScaleSize(30), 0, 0, 0);
    ui->label_dtool->setContentsMargins(Public_Function::getScaleSize(30), 0, 0, 0);
}

void ToolPanel::paintEvent(QPaintEvent *event)
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

void ToolPanel::initWidget()
{
    ui->verticalLayoutWidget_5->hide();
    this->setLayout(ui->verticalLayout);
    ui->verticalLayout->setAlignment(ui->label_line_4, Qt::AlignCenter);
    ui->pTool1->mSetIcon(QPixmap(":/images/main/moreTools/gongju1@2x.png"));
    ui->pTool1->mSetText(tr("图形"));
    ui->pTool2->mSetIcon(QPixmap(":/images/main/moreTools/gongju2@2x.png"));
    ui->pTool2->mSetText(tr("截图 "));
    ui->pTool3->mSetIcon(QPixmap(":/images/main/moreTools/gongju3@2x.png"));
    ui->pTool3->mSetText(tr("展台"));
    ui->pTool4->mSetIcon(QPixmap(":/images/main/moreTools/gongju4@2x.png"));
    ui->pTool4->mSetText(tr("播放器"));
    ui->pTool5->mSetIcon(QPixmap(":/images/main/moreTools/gongju5@2x.png"));
    ui->pTool5->mSetText(tr("双屏"));
    ui->pTool5->hide();
    ui->pTool6->mSetIcon(QPixmap(":/images/main/moreTools/gongju6@2x.png"));
    ui->pTool6->mSetText(tr("板中板"));
//djf    ui->pTool6->hide();
    ui->pTool7->mSetIcon(QPixmap(":/images/main/moreTools/gongju7@2x.png"));
    ui->pTool7->mSetText(tr("遮慕"));
    ui->pTool8->mSetIcon(QPixmap(":/images/main/moreTools/gongju8@2x.png"));
    ui->pTool8->mSetText(tr("聚光灯"));
    ui->pTool9->mSetIcon(QPixmap(":/images/main/moreTools/gongju9@2x.png"));
    ui->pTool9->mSetText(tr("计算器"));
    ui->pTool10->mSetIcon(QPixmap(":/images/main/moreTools/gongju10@2x.png"));
    ui->pTool10->mSetText(tr("计时器"));
    ui->pTool11->mSetIcon(QPixmap(":/images/main/moreTools/gongju11@2x.png"));
    ui->pTool11->mSetText(tr("录屏"));
    ui->pTool11->hide();
    ui->pTool12->mSetIcon(QPixmap(":/images/main/moreTools/gongju12@2x.png"));
    ui->pTool12->mSetText(tr("锁屏"));
    ui->pTool13->mSetIcon(QPixmap(":/images/main/moreTools/tupian@2x.png"));
    ui->pTool13->mSetText(tr("插入图片"));
    ui->pDisTool1->mSetIcon(QPixmap(":/images/main/moreTools/gongju13@2x.png"));
    ui->pDisTool1->mSetText(tr("汉语字典"));
    ui->pDisTool1->hide();
    ui->pDisTool2->mSetIcon(QPixmap(":/images/main/moreTools/gongju14@2x.png"));
    ui->pDisTool2->mSetText(tr("英文词典"));
    ui->pDisTool2->hide();
    ui->pDisTool3->mSetIcon(QPixmap(":/images/main/moreTools/gongju15@2x.png"));
    ui->pDisTool3->mSetText(tr("拼音"));
    ui->pDisTool3->hide();
    ui->pDisTool4->mSetIcon(QPixmap(":/images/main/moreTools/gongju16@2x.png"));
    ui->pDisTool4->mSetText(tr("四线三格"));
    ui->pDisTool4->hide();
    ui->pDisTool5->mSetIcon(QPixmap(":/images/main/moreTools/gongju17@2x.png"));
    ui->pDisTool5->mSetText(tr("函数"));
    ui->pDisTool5->hide();
    ui->pDisTool6->mSetIcon(QPixmap(":/images/main/moreTools/gongju18@2x.png"));
    ui->pDisTool6->mSetText(tr("公式"));
    ui->pDisTool6->hide();
    ui->pDisTool7->mSetIcon(QPixmap(":/images/main/moreTools/gongju19@2x.png"));
    ui->pDisTool7->mSetText(tr("尺规"));
    ui->pDisTool8->mSetIcon(QPixmap(":/images/main/moreTools/gongju20@2x.png"));
    ui->pDisTool8->mSetText(tr("背景"));
    QButtonGroup *toolGroup = new QButtonGroup(this);
    toolGroup->setExclusive(true);
    toolGroup->addButton(ui->pTool1);
    toolGroup->addButton(ui->pTool2);
    toolGroup->addButton(ui->pTool3);
    toolGroup->addButton(ui->pTool4);
    toolGroup->addButton(ui->pTool5);
    toolGroup->addButton(ui->pTool6);
    toolGroup->addButton(ui->pTool7);
    toolGroup->addButton(ui->pTool8);
    toolGroup->addButton(ui->pTool9);
    toolGroup->addButton(ui->pTool10);
    toolGroup->addButton(ui->pTool11);
    toolGroup->addButton(ui->pTool12);
    toolGroup->addButton(ui->pTool13);
    toolGroup->addButton(ui->pDisTool1);
    toolGroup->addButton(ui->pDisTool2);
    toolGroup->addButton(ui->pDisTool3);
    toolGroup->addButton(ui->pDisTool4);
    toolGroup->addButton(ui->pDisTool5);
    toolGroup->addButton(ui->pDisTool6);
    toolGroup->addButton(ui->pDisTool7);
    toolGroup->addButton(ui->pDisTool8);
    connect(toolGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onToolGroupBtnClicked(QAbstractButton*)));
}

void ToolPanel::updateLanguage()
{
    ui->label_utool->setText(tr("通用工具"));
    ui->pTool1->mSetText(tr("图形"));
    ui->pTool2->mSetText(tr("截图 "));
    ui->pTool3->mSetText(tr("展台"));
    ui->pTool4->mSetText(tr("播放器"));
    ui->pTool5->mSetText(tr("双屏"));
    ui->pTool6->mSetText(tr("板中板"));
    ui->pTool7->mSetText(tr("遮慕"));
    ui->pTool8->mSetText(tr("聚光灯"));
    ui->pTool9->mSetText(tr("计算器"));
    ui->pTool10->mSetText(tr("计时器"));
    ui->pTool11->mSetText(tr("录屏"));
    ui->pTool12->mSetText(tr("锁屏"));
    ui->pTool13->mSetText(tr("插入图片"));
    ui->pDisTool1->mSetText(tr("汉语字典"));
    ui->pDisTool2->mSetText(tr("英文词典"));
    ui->pDisTool3->mSetText(tr("拼音"));
    ui->pDisTool4->mSetText(tr("四线三格"));
    ui->pDisTool5->mSetText(tr("函数"));
    ui->pDisTool6->mSetText(tr("公式"));
    ui->pDisTool7->mSetText(tr("尺规"));
    ui->pDisTool8->mSetText(tr("背景"));


    ui->label_dtool->setText(tr("学科工具"));

}

void ToolPanel::onToolGroupBtnClicked(QAbstractButton *button)
{
    if (ui->pTool1 == button) {
        emit this->showPanel(1);
    }else if (ui->pTool2 == button) {
        emit this->toolFunction(1);
    }else if (ui->pTool3 == button) {
        emit this->toolFunction(2);
    }else if (ui->pTool4 == button) {
        emit this->toolFunction(3);
    }else if (ui->pTool5 == button) {
        emit this->toolFunction(4);
    }else if (ui->pTool6 == button) {
        emit this->toolFunction(5);
    }else if (ui->pTool7 == button) {
        emit this->toolFunction(6);
    }else if (ui->pTool8 == button) {
        emit this->toolFunction(7);
    }else if (ui->pTool9 == button) {
        emit this->toolFunction(8);
    }else if (ui->pTool10 == button) {
        emit this->toolFunction(9);
    }else if (ui->pTool11 == button) {
        emit this->toolFunction(10);
    }else if (ui->pTool12 == button) {
        emit this->toolFunction(11);
    }else if (ui->pTool13 == button) {
        emit this->toolFunction(12);
    }else if (ui->pDisTool1 == button) {

    }else if (ui->pDisTool2 == button) {

    }else if (ui->pDisTool3 == button) {

    }else if (ui->pDisTool4 == button) {

    }else if (ui->pDisTool5 == button) {

    }else if (ui->pDisTool6 == button) {

    }else if (ui->pDisTool7 == button) {
        emit this->showPanel(3);
    }else if (ui->pDisTool8 == button) {
        emit this->showPanel(2);
    }
}
