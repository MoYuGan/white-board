#include "itemtool_fillcolorpanel.h"
#include "ui_itemtool_fillcolorpanel.h"
#include <QButtonGroup>
#include "Public/public_function.h"

ItemTool_FillColorPanel::ItemTool_FillColorPanel(const QColor& color, QWidget *parent) :
    m_pFillColor(color),
    QWidget(parent),
    ui(new Ui::ItemTool_FillColorPanel)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_AcceptTouchEvents,true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->setMouseTracking(true);
    this->initWidget();
    this->resize();
}

ItemTool_FillColorPanel::~ItemTool_FillColorPanel()
{
    delete ui;
}

void ItemTool_FillColorPanel::updateFillColor(const QColor& color)
{
    m_pFillColor = color;

    if (ui->pFillColor1->mGetColor() == m_pFillColor)
        ui->pFillColor1->setChecked(true);
    else if (ui->pFillColor2->mGetColor() == m_pFillColor)
        ui->pFillColor2->setChecked(true);
    else if (ui->pFillColor3->mGetColor() == m_pFillColor)
        ui->pFillColor3->setChecked(true);
    else if (ui->pFillColor4->mGetColor() == m_pFillColor)
        ui->pFillColor4->setChecked(true);
    else if (ui->pFillColor5->mGetColor() == m_pFillColor)
        ui->pFillColor5->setChecked(true);
    else if (ui->pFillColor6->mGetColor() == m_pFillColor)
        ui->pFillColor6->setChecked(true);
    else if (ui->pFillColor7->mGetColor() == m_pFillColor)
        ui->pFillColor7->setChecked(true);
    else if (ui->pFillColor8->mGetColor() == m_pFillColor)
        ui->pFillColor8->setChecked(true);


}

void ItemTool_FillColorPanel::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);
    /*填充面板*/
    ui->gridLayoutWidget_2->hide();
    ui->frame_fillcolor->setLayout(ui->gridLayout_2);
    ui->frame_fillcolor->mSetBackgroudColor(Qt::white);
    ui->pFillColor1->mSetIconColor(Qt::white);
    ui->pFillColor2->mSetIconColor(Qt::black);
    ui->pFillColor3->mSetIconColor(QColor(247,56,89));
    ui->pFillColor4->mSetIconColor(QColor(255,168,0));
    ui->pFillColor5->mSetIconColor(QColor(0,184,169));
    ui->pFillColor6->mSetIconColor(QColor(172,115,255));
    ui->pFillColor7->mSetIconColor(QColor(100,181,246));
    ui->pFillColor8->mSetIconColor(Qt::transparent);
    if (ui->pFillColor1->mGetColor() == m_pFillColor)
        ui->pFillColor1->setChecked(true);
    else if (ui->pFillColor2->mGetColor() == m_pFillColor)
        ui->pFillColor2->setChecked(true);
    else if (ui->pFillColor3->mGetColor() == m_pFillColor)
        ui->pFillColor3->setChecked(true);
    else if (ui->pFillColor4->mGetColor() == m_pFillColor)
        ui->pFillColor4->setChecked(true);
    else if (ui->pFillColor5->mGetColor() == m_pFillColor)
        ui->pFillColor5->setChecked(true);
    else if (ui->pFillColor6->mGetColor() == m_pFillColor)
        ui->pFillColor6->setChecked(true);
    else if (ui->pFillColor7->mGetColor() == m_pFillColor)
        ui->pFillColor7->setChecked(true);
    else if (ui->pFillColor8->mGetColor() == m_pFillColor)
        ui->pFillColor8->setChecked(true);
    fillColorGroup = new QButtonGroup(this);
    fillColorGroup->setExclusive(true);
    fillColorGroup->addButton(ui->pFillColor1);
    fillColorGroup->addButton(ui->pFillColor2);
    fillColorGroup->addButton(ui->pFillColor3);
    fillColorGroup->addButton(ui->pFillColor4);
    fillColorGroup->addButton(ui->pFillColor5);
    fillColorGroup->addButton(ui->pFillColor6);
    fillColorGroup->addButton(ui->pFillColor7);
    fillColorGroup->addButton(ui->pFillColor8);
    //buttonId =fillColorGroup->id(ui->pFillColor8);
    connect(fillColorGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onFillColorGroup(QAbstractButton*,bool)));
}

void ItemTool_FillColorPanel::resize()
{
    /*填充面板*/
    QSize size = Public_Function::getScaleSize(QSize(226, 126));
    ui->frame_fillcolor->setFixedSize(size);
    int radius = Public_Function::getScaleSize(12);
    ui->frame_fillcolor->mSetBordRadius(radius, radius, radius, radius);
    ui->frame_fillcolor->mSetBorder(Public_Function::getScaleSize(2));
    size = Public_Function::getScaleSize(QSize(48, 48));
    ui->pFillColor1->setFixedSize(size);
    ui->pFillColor2->setFixedSize(size);
    ui->pFillColor3->setFixedSize(size);
    ui->pFillColor4->setFixedSize(size);
    ui->pFillColor5->setFixedSize(size);
    ui->pFillColor6->setFixedSize(size);
    ui->pFillColor7->setFixedSize(size);
    ui->pFillColor8->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(36, 36));
    ui->pFillColor1->mSetIconSize(size);
    ui->pFillColor2->mSetIconSize(size);
    ui->pFillColor3->mSetIconSize(size);
    ui->pFillColor4->mSetIconSize(size);
    ui->pFillColor5->mSetIconSize(size);
    ui->pFillColor6->mSetIconSize(size);
    ui->pFillColor7->mSetIconSize(size);
    ui->pFillColor8->mSetIconSize(size);

    this->adjustSize();
}

bool ItemTool_FillColorPanel::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        {
            return true;
            break;
        }
        case QEvent::TouchUpdate:
        {
            return true;
            break;
        }
        case QEvent::TouchEnd:
        {
            QTouchEvent* ev =static_cast<QTouchEvent*>(event);
            QPoint dot =ev->touchPoints().at(0).pos().toPoint();
            if (ui->pFillColor1->geometry().contains(dot))
            {
                if(ui->pFillColor1->isChecked())return true;
                ui->pFillColor1->setChecked(true);
                m_pFillColor = QColor(ui->pFillColor1->mGetColor());
                emit this->fillColorChanged(m_pFillColor);
            }
            else if (ui->pFillColor2->geometry().contains(dot))
            {
                if(ui->pFillColor2->isChecked())return true;
                ui->pFillColor2->setChecked(true);
                m_pFillColor = QColor(ui->pFillColor2->mGetColor());
                emit this->fillColorChanged(m_pFillColor);
            }
            else if (ui->pFillColor3->geometry().contains(dot))
            {
                if(ui->pFillColor3->isChecked())return true;
                ui->pFillColor3->setChecked(true);
                m_pFillColor = QColor(ui->pFillColor3->mGetColor());
                emit this->fillColorChanged(m_pFillColor);
            }
            else if (ui->pFillColor4->geometry().contains(dot))
            {
                if(ui->pFillColor4->isChecked())return true;
                ui->pFillColor4->setChecked(true);
                m_pFillColor = QColor(ui->pFillColor4->mGetColor());
                emit this->fillColorChanged(m_pFillColor);
            }
            else if (ui->pFillColor5->geometry().contains(dot))
            {
                if(ui->pFillColor5->isChecked())return true;
                ui->pFillColor5->setChecked(true);
                m_pFillColor = QColor(ui->pFillColor5->mGetColor());
                emit this->fillColorChanged(m_pFillColor);
            }
            else if (ui->pFillColor6->geometry().contains(dot))
            {
                if(ui->pFillColor6->isChecked())return true;
                ui->pFillColor6->setChecked(true);
                m_pFillColor = QColor(ui->pFillColor6->mGetColor());
                emit this->fillColorChanged(m_pFillColor);
            }
            else if (ui->pFillColor7->geometry().contains(dot))
            {
                if(ui->pFillColor7->isChecked())return true;
                ui->pFillColor7->setChecked(true);
                m_pFillColor = QColor(ui->pFillColor7->mGetColor());
                emit this->fillColorChanged(m_pFillColor);
            }
            else if (ui->pFillColor8->geometry().contains(dot))
            {
                if(ui->pFillColor8->isChecked())return true;
                ui->pFillColor8->setChecked(true);
                m_pFillColor = QColor(ui->pFillColor8->mGetColor());
                emit this->fillColorChanged(m_pFillColor);
            }
             return true;
             break;
        }
        default:
        {
            break;
        }
    }
    return QWidget::event(event);
}

void ItemTool_FillColorPanel::onFillColorGroup(QAbstractButton *button, bool isChecked)
{
    if(buttonId ==fillColorGroup->id(button))return;
    buttonId =fillColorGroup->id(button);
    if (isChecked) {
        if (ui->pFillColor1 == button)
            m_pFillColor = QColor(ui->pFillColor1->mGetColor());
        else if (ui->pFillColor2 == button)
            m_pFillColor = QColor(ui->pFillColor2->mGetColor());
        else if (ui->pFillColor3 == button)
            m_pFillColor = QColor(ui->pFillColor3->mGetColor());
        else if (ui->pFillColor4 == button)
            m_pFillColor = QColor(ui->pFillColor4->mGetColor());
        else if (ui->pFillColor5 == button)
            m_pFillColor = QColor(ui->pFillColor5->mGetColor());
        else if (ui->pFillColor6 == button)
            m_pFillColor = QColor(ui->pFillColor6->mGetColor());
        else if (ui->pFillColor7 == button)
            m_pFillColor = QColor(ui->pFillColor7->mGetColor());
        else if (ui->pFillColor8 == button)
            m_pFillColor = QColor(ui->pFillColor8->mGetColor());
        else
            return;
    }
    emit this->fillColorChanged(m_pFillColor);
}
