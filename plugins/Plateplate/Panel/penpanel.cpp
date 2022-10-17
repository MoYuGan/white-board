#include "penpanel.h"
#include "ui_penpanel.h"

#include <QtDebug>

PenPanel::PenPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PenPanel)
{
    ui->setupUi(this);
    this->initWidget();
    ui->pSize1->setChecked(true);
    ui->pColor1->setChecked(true);
}

PenPanel::~PenPanel()
{
    delete ui;
}

void PenPanel::show()
{
    QWidget::show();
    this->raise();
    emit this->panelShow();
}

void PenPanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

void PenPanel::resize()
{
    ui->verticalLayout->setContentsMargins(PublicFunction::getScaleSize(20) + m_TransparentBorder, m_TransparentBorder,
                                           PublicFunction::getScaleSize(20) + m_TransparentBorder,
                                           PublicFunction::getScaleSize(20) + m_TransparentBorder);
    ui->gridLayout->setVerticalSpacing(PublicFunction::getScaleSize(2));
    ui->label_line->setFixedHeight(PublicFunction::getScaleSize(1));
    ui->label_null->setFixedHeight(PublicFunction::getScaleSize(14));

    ui->pSize1->mSetRoundSize(PublicFunction::getScaleSize(6, 6));
    ui->pSize1->setFixedSize(PublicFunction::getScaleSize(24, 24));
    ui->pSize2->mSetRoundSize(PublicFunction::getScaleSize(14, 14));
    ui->pSize2->setFixedSize(PublicFunction::getScaleSize(32, 32));
    ui->pSize3->mSetRoundSize(PublicFunction::getScaleSize(22, 22));
    ui->pSize3->setFixedSize(PublicFunction::getScaleSize(40, 40));
    ui->pSize4->mSetRoundSize(PublicFunction::getScaleSize(30, 30));
    ui->pSize4->setFixedSize(PublicFunction::getScaleSize(48, 48));

    QSize size = PublicFunction::getScaleSize(QSize(48, 48));
    ui->pColor1->setFixedSize(size);
    ui->pColor2->setFixedSize(size);
    ui->pColor3->setFixedSize(size);
    ui->pColor4->setFixedSize(size);
    ui->pColor5->setFixedSize(size);
    ui->pColor6->setFixedSize(size);
    ui->pColor7->setFixedSize(size);
    ui->pColor8->setFixedSize(size);
    ui->pColor9->setFixedSize(size);
    ui->pColor10->setFixedSize(size);
    ui->pColor11->setFixedSize(size);
    ui->pColor12->setFixedSize(size);
    size = PublicFunction::getScaleSize(QSize(36, 36));
    ui->pColor1->mSetIconSize(size);
    ui->pColor2->mSetIconSize(size);
    ui->pColor3->mSetIconSize(size);
    ui->pColor4->mSetIconSize(size);
    ui->pColor5->mSetIconSize(size);
    ui->pColor6->mSetIconSize(size);
    ui->pColor7->mSetIconSize(size);
    ui->pColor8->mSetIconSize(size);
    ui->pColor9->mSetIconSize(size);
    ui->pColor10->mSetIconSize(size);
    ui->pColor11->mSetIconSize(size);
    ui->pColor12->mSetIconSize(size);
}

void PenPanel::paintEvent(QPaintEvent *event)
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

void PenPanel::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);
    ui->verticalLayout->setSpacing(0);
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout_2->setSpacing(0);
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);

    ui->pColor1->mSetIconColor(Qt::white);
    ui->pColor2->mSetIconColor(Qt::black);
    ui->pColor3->mSetIconColor(QColor(247,56,89));
    ui->pColor4->mSetIconColor(QColor(255,168,0));
    ui->pColor5->mSetIconColor(QColor(255,222,41));
    ui->pColor6->mSetIconColor(QColor(172,115,255));
    ui->pColor7->mSetIconColor(QColor(0,184,169));
    ui->pColor8->mSetIconColor(QColor(25,118,210));
    ui->pColor9->mSetIconColor(QColor(236,64,122));
    ui->pColor10->mSetIconColor(QColor(100,181,246));
    ui->pColor11->mSetIconColor(QColor(0,172,193));
    ui->pColor12->mSetIconColor(QColor(255,130,171));

    QButtonGroup *sizeGroup = new QButtonGroup(this);
    sizeGroup->setExclusive(true);
    sizeGroup->addButton(ui->pSize1);
    sizeGroup->addButton(ui->pSize2);
    sizeGroup->addButton(ui->pSize3);
    sizeGroup->addButton(ui->pSize4);
    connect(sizeGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onSizeGroupBtnToggled(QAbstractButton*,bool)));


    QButtonGroup *colorGroup = new QButtonGroup(this);
    colorGroup->setExclusive(true);
    colorGroup->addButton(ui->pColor1);
    colorGroup->addButton(ui->pColor2);
    colorGroup->addButton(ui->pColor3);
    colorGroup->addButton(ui->pColor4);
    colorGroup->addButton(ui->pColor5);
    colorGroup->addButton(ui->pColor6);
    colorGroup->addButton(ui->pColor7);
    colorGroup->addButton(ui->pColor8);
    colorGroup->addButton(ui->pColor9);
    colorGroup->addButton(ui->pColor10);
    colorGroup->addButton(ui->pColor11);
    colorGroup->addButton(ui->pColor12);
    connect(colorGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onColorGroupBtnToggled(QAbstractButton*,bool)));
}

void PenPanel::onSizeGroupBtnToggled(QAbstractButton *button, bool checked)
{
    if (checked)
    {
        if (button == ui->pSize1)
            e_PenSize = PublicFunction::getScaleSize(3);
        else if (button == ui->pSize2)
            e_PenSize = PublicFunction::getScaleSize(5);
        else if (button == ui->pSize3)
            e_PenSize = PublicFunction::getScaleSize(7);
        else if (button == ui->pSize4)
            e_PenSize = PublicFunction::getScaleSize(9);
    }
}

void PenPanel::onColorGroupBtnToggled(QAbstractButton *button, bool checked)
{
    if (checked)
    {
        CustomPushButton_4 *cButton = static_cast<CustomPushButton_4*>(button);
        e_PenColor = cButton->mGetColor();
    }
}
