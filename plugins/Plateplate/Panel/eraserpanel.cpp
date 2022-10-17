#include "eraserpanel.h"
#include "ui_eraserpanel.h"

EraserPanel::EraserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EraserPanel)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
    ui->pSize1->setChecked(true);
}

EraserPanel::~EraserPanel()
{
    delete ui;
}

void EraserPanel::show()
{
    QWidget::show();
    this->raise();
    emit panelShow();
}

void EraserPanel::hide()
{
    QWidget::hide();
    emit panelHide();
}

void EraserPanel::resize()
{
    QSize size = PublicFunction::getScaleSize(QSize(34, 34));
    ui->pSize1->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(14, 14));
    ui->pSize1->mSetRoundSize(size);
    size = PublicFunction::getScaleSize(QSize(48, 48));
    ui->pSize2->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(28, 28));
    ui->pSize2->mSetRoundSize(size);
    size = PublicFunction::getScaleSize(QSize(66, 66));
    ui->pSize3->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(46, 46));
    ui->pSize3->mSetRoundSize(size);

    ui->slider->setFixedSize(PublicFunction::getScaleSize(226, 48));
    ui->slider->mSetHandleSize(PublicFunction::getScaleSize(88, 38));
    ui->slider->mSetMargin(PublicFunction::getScaleSize(5), PublicFunction::getScaleSize(5));
    ui->slider->mSetFont(PublicFunction::getFont(12));
    ui->slider->mSetRadius(PublicFunction::getScaleSize(8));
    ui->label_line->setFixedSize(PublicFunction::getScaleSize(252, 1));
}

void EraserPanel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::transparent);
    QColor color(135, 135, 135);
    int border = m_TransparentBorder;
    int radius = PublicFunction::getScaleSize(12);
    for(int i = 0; i < border; i++)
    {
        QRect rect = QRect(QPoint(border - i, border - i), QPoint(this->width() - border - i, this->height() - border - i));

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

void EraserPanel::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);
    ui->verticalLayout->setAlignment(ui->label_line, Qt::AlignCenter);
    ui->verticalLayout->setAlignment(ui->slider, Qt::AlignCenter);
    ui->slider->mSetHandleIcon(QPixmap(":/images/huakuai@2x.png"));
    ui->slider->mSetText(tr(">>> 右滑清屏"));
    connect(ui->slider, &CustomSlider_1::clearSignal, [=](){ emit this->clearAction(); });
    QButtonGroup *buttongroup = new QButtonGroup(this);
    buttongroup->setExclusive(true);
    buttongroup->addButton(ui->pSize1);
    buttongroup->addButton(ui->pSize2);
    buttongroup->addButton(ui->pSize3);
    connect(buttongroup, SIGNAL(buttonToggled(QAbstractButton*,bool)),
            this, SLOT(onSizeGroupToggled(QAbstractButton*,bool)));

}

void EraserPanel::onSizeGroupToggled(QAbstractButton *button, bool checked)
{
    if (checked)
    {
        if (button == ui->pSize1)
            e_EraserSize = QSize(50, 70);
        else if (button == ui->pSize2)
            e_EraserSize = QSize(80, 111);
        else if (button == ui->pSize3)
            e_EraserSize = QSize(134, 186);
    }
}
