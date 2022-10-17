#include "itemtool_borderpanel.h"
#include "ui_itemtool_borderpanel.h"
#include <QButtonGroup>
#include "Public/public_function.h"

ItemTool_BorderPanel::ItemTool_BorderPanel(int width, QColor color, QWidget *parent) :
    m_pBorderWidth(width),
    m_pBorderColor(color),
    QWidget(parent),
    ui(new Ui::ItemTool_BorderPanel)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->setMouseTracking(true);
    this->initWidget();
    this->resize();
}

ItemTool_BorderPanel::~ItemTool_BorderPanel()
{
    delete ui;
}

void ItemTool_BorderPanel::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);
    /*边框面板*/
    ui->verticalLayoutWidget->hide();
    ui->frame_border->setLayout(ui->verticalLayout);
    ui->frame_border->mSetBackgroudColor(Qt::white);
    ui->pBorderSize1->mSetValue(Public_Function::getScaleWidth(1));
    ui->pBorderSize2->mSetValue(Public_Function::getScaleWidth(3));
    ui->pBorderSize3->mSetValue(Public_Function::getScaleWidth(8));
    ui->pBorderSize4->mSetValue(Public_Function::getScaleWidth(12));
    ui->pBorderColor1->mSetIconColor(Qt::white);
    ui->pBorderColor2->mSetIconColor(Qt::black);
    ui->pBorderColor3->mSetIconColor(QColor(247,56,89));
    ui->pBorderColor4->mSetIconColor(QColor(255,168,0));
    ui->pBorderColor5->mSetIconColor(QColor(0,184,169));
    ui->pBorderColor6->mSetIconColor(QColor(172,115,255));
    ui->pBorderColor7->mSetIconColor(QColor(100,181,246));
    ui->pBorderColor8->mSetIconColor(Qt::transparent);
    if (ui->pBorderSize1->mGetValue() == m_pBorderWidth)
        ui->pBorderSize1->setChecked(true);
    else if (ui->pBorderSize2->mGetValue() == m_pBorderWidth)
        ui->pBorderSize2->setChecked(true);
    else if (ui->pBorderSize3->mGetValue() == m_pBorderWidth)
        ui->pBorderSize3->setChecked(true);
    else if (ui->pBorderSize4->mGetValue() == m_pBorderWidth)
        ui->pBorderSize4->setChecked(true);
    if (ui->pBorderColor1->mGetColor() == m_pBorderColor)
        ui->pBorderColor1->setChecked(true);
    else if (ui->pBorderColor2->mGetColor() == m_pBorderColor)
        ui->pBorderColor2->setChecked(true);
    else if (ui->pBorderColor3->mGetColor() == m_pBorderColor)
        ui->pBorderColor3->setChecked(true);
    else if (ui->pBorderColor4->mGetColor() == m_pBorderColor)
        ui->pBorderColor4->setChecked(true);
    else if (ui->pBorderColor5->mGetColor() == m_pBorderColor)
        ui->pBorderColor5->setChecked(true);
    else if (ui->pBorderColor6->mGetColor() == m_pBorderColor)
        ui->pBorderColor6->setChecked(true);
    else if (ui->pBorderColor7->mGetColor() == m_pBorderColor)
        ui->pBorderColor7->setChecked(true);
    else if (ui->pBorderColor8->mGetColor() == m_pBorderColor)
        ui->pBorderColor8->setChecked(true);
    QButtonGroup *borderSizeGroup = new QButtonGroup(this);
    borderSizeGroup->setExclusive(true);
    borderSizeGroup->addButton(ui->pBorderSize1);
    borderSizeGroup->addButton(ui->pBorderSize2);
    borderSizeGroup->addButton(ui->pBorderSize3);
    borderSizeGroup->addButton(ui->pBorderSize4);
    QButtonGroup *borderColorGroup = new QButtonGroup(this);
    borderColorGroup->setExclusive(true);
    borderColorGroup->addButton(ui->pBorderColor1);
    borderColorGroup->addButton(ui->pBorderColor2);
    borderColorGroup->addButton(ui->pBorderColor3);
    borderColorGroup->addButton(ui->pBorderColor4);
    borderColorGroup->addButton(ui->pBorderColor5);
    borderColorGroup->addButton(ui->pBorderColor6);
    borderColorGroup->addButton(ui->pBorderColor7);
    borderColorGroup->addButton(ui->pBorderColor8);
    connect(borderSizeGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onBorderSizeGroup(QAbstractButton*,bool)));
    connect(borderColorGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onBorderColorGroup(QAbstractButton*,bool)));
}

void ItemTool_BorderPanel::resize()
{
    /*边框面板*/
    QSize size = Public_Function::getScaleSize(QSize(226, 197));
    ui->frame_border->setFixedSize(size);
    int radius = Public_Function::getScaleWidth(12);
    ui->frame_border->mSetBordRadius(radius, radius, radius, radius);
    ui->frame_border->mSetBorder(Public_Function::getScaleWidth(2));
    size = Public_Function::getScaleSize(QSize(48, 48));
    ui->pBorderColor1->setFixedSize(size);
    ui->pBorderColor2->setFixedSize(size);
    ui->pBorderColor3->setFixedSize(size);
    ui->pBorderColor4->setFixedSize(size);
    ui->pBorderColor5->setFixedSize(size);
    ui->pBorderColor6->setFixedSize(size);
    ui->pBorderColor7->setFixedSize(size);
    ui->pBorderColor8->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(36, 36));
    ui->pBorderColor1->mSetIconSize(size);
    ui->pBorderColor2->mSetIconSize(size);
    ui->pBorderColor3->mSetIconSize(size);
    ui->pBorderColor4->mSetIconSize(size);
    ui->pBorderColor5->mSetIconSize(size);
    ui->pBorderColor6->mSetIconSize(size);
    ui->pBorderColor7->mSetIconSize(size);
    ui->pBorderColor8->mSetIconSize(size);
    size = Public_Function::getScaleSize(QSize(6, 6));
    ui->pBorderSize1->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(26, 26));
    ui->pBorderSize1->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(14, 14));
    ui->pBorderSize2->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(34, 34));
    ui->pBorderSize2->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(22, 22));
    ui->pBorderSize3->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(42, 42));
    ui->pBorderSize3->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(30, 30));
    ui->pBorderSize4->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(50, 50));
    ui->pBorderSize4->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(200, 1));
    ui->label_line->setFixedSize(size);

    this->adjustSize();
}

void ItemTool_BorderPanel::onBorderSizeGroup(QAbstractButton *button, bool isChecked)
{
    if (isChecked) {
        if (ui->pBorderSize1 == button)
            m_pBorderWidth = ui->pBorderSize1->mGetValue();
        else if (ui->pBorderSize2 == button)
            m_pBorderWidth = ui->pBorderSize2->mGetValue();
        else if (ui->pBorderSize3 == button)
            m_pBorderWidth = ui->pBorderSize3->mGetValue();
        else if (ui->pBorderSize4 == button)
            m_pBorderWidth = ui->pBorderSize4->mGetValue();
        else
            return;
    }
    emit this->borderSizeChanged(m_pBorderWidth);
}

void ItemTool_BorderPanel::onBorderColorGroup(QAbstractButton *button, bool isChecked)
{
    if (isChecked) {
        if (ui->pBorderColor1 == button)
            m_pBorderColor = QColor(ui->pBorderColor1->mGetColor());
        else if (ui->pBorderColor2 == button)
            m_pBorderColor = QColor(ui->pBorderColor2->mGetColor());
        else if (ui->pBorderColor3 == button)
            m_pBorderColor = QColor(ui->pBorderColor3->mGetColor());
        else if (ui->pBorderColor4 == button)
            m_pBorderColor = QColor(ui->pBorderColor4->mGetColor());
        else if (ui->pBorderColor5 == button)
            m_pBorderColor = QColor(ui->pBorderColor5->mGetColor());
        else if (ui->pBorderColor6 == button)
            m_pBorderColor = QColor(ui->pBorderColor6->mGetColor());
        else if (ui->pBorderColor7 == button)
            m_pBorderColor = QColor(ui->pBorderColor7->mGetColor());
        else if (ui->pBorderColor8 == button)
            m_pBorderColor = QColor(ui->pBorderColor8->mGetColor());
        else
            return;
    }
    emit this->borderColorChanged(m_pBorderColor);
}
