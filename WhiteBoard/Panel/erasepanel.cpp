#include "erasepanel.h"
#include "ui_erasepanel.h"

ErasePanel::ErasePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErasePanel)
{
    ui->setupUi(this);
    this->initWidget();
}

ErasePanel::~ErasePanel()
{
    delete ui;
}

void ErasePanel::show()
{
    QWidget::show();
    this->raise();
}

void ErasePanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

void ErasePanel::resizeWidget()
{
    QSize size = Public_Function::getScaleSize(QSize(292, 183));
    this->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(34, 34));
    ui->pEraserSize1->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(14, 14));
    ui->pEraserSize1->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(48, 48));
    ui->pEraserSize2->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(28, 28));
    ui->pEraserSize2->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(66, 66));
    ui->pEraserSize3->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(46, 46));
    ui->pEraserSize3->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(226, 48));
    ui->eraserSlider->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(88, 38));
    ui->eraserSlider->mSetHandleSize(size);
    int radius = Public_Function::getScaleSize(5);
    ui->eraserSlider->mSetMargin(radius, radius);
    ui->eraserSlider->mSetFont(Public_Function::getFont(12));
    ui->eraserSlider->mSetRadius(Public_Function::getScaleSize(8));
    size = Public_Function::getScaleSize(QSize(252, 1));
    ui->label_line->setFixedSize(size);
}

void ErasePanel::setCheckedSize(int id)
{
    QAbstractButton *button = m_EraseSizeGroup->button(id);
    if (nullptr != button)
        button->setChecked(true);
}

void ErasePanel::paintEvent(QPaintEvent *event)
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

void ErasePanel::initWidget()
{
    ui->verticalLayoutWidget_2->hide();
    this->setLayout(ui->verticalLayout);
    ui->verticalLayout->setAlignment(ui->label_line, Qt::AlignCenter);
    ui->verticalLayout->setAlignment(ui->eraserSlider, Qt::AlignCenter);
    ui->horizontalLayout->setAlignment(ui->pEraserSize1, Qt::AlignCenter);
    ui->horizontalLayout->setAlignment(ui->pEraserSize2, Qt::AlignCenter);
    ui->horizontalLayout->setAlignment(ui->pEraserSize3, Qt::AlignCenter);
    ui->eraserSlider->mSetHandleIcon(QPixmap(":/images/main/eraserPanel/huakuai@2x.png"));
    ui->eraserSlider->mSetText(tr(">>> 右滑清屏"));
    connect(ui->eraserSlider, &Widget_1::clearSignal, this, [=](){ emit this->clearSignal(); });

    m_EraseSizeGroup = new QButtonGroup(this);
    m_EraseSizeGroup->setExclusive(true);
    m_EraseSizeGroup->addButton(ui->pEraserSize1, 1);
    m_EraseSizeGroup->addButton(ui->pEraserSize2, 2);
    m_EraseSizeGroup->addButton(ui->pEraserSize3, 3);
    connect(m_EraseSizeGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onSizeGroupToggled(QAbstractButton*,bool)));
}

void ErasePanel::updateLanguage()
{
    ui->eraserSlider->mSetText(tr(">>> 右滑清屏"));
}

void ErasePanel::onSizeGroupToggled(QAbstractButton *button, bool checked)
{
    QSize size;
    if (ui->pEraserSize1 == button) {
        size = Public_Function::getScaleSize(QSize(50, 70));
    }else if (ui->pEraserSize2 == button) {
        size = Public_Function::getScaleSize(QSize(80, 111));
    }else if (ui->pEraserSize3 == button) {
        size = Public_Function::getScaleSize(QSize(134, 186));
    }
    if (checked)
        emit this->eraseSizeChanged(size);
//        g_EraserSize = size;
}
