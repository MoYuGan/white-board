#include "itemtool_borderpanel.h"
#include "ui_itemtool_borderpanel.h"
#include <QButtonGroup>
#include "Public/public_function.h"

ItemTool_BorderPanel::ItemTool_BorderPanel(int width, const QColor& color, Qt::PenStyle penStyle,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemTool_BorderPanel),
    m_pBorderWidth(width),
    m_pBorderColor(color)
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

    if (penStyle == Qt::SolidLine) ui->pBorderFullLine->setChecked(true);
    else if (penStyle == Qt::DotLine) ui->pBorderPointLine->setChecked(true);
    else if (penStyle == Qt::DashLine) ui->pBorderDottedLine->setChecked(true);
}

ItemTool_BorderPanel::~ItemTool_BorderPanel()
{
    delete ui;
}

void ItemTool_BorderPanel::hideOtherPenStyle()
{
    ui->pBorderDottedLine->hide();
    ui->pBorderPointLine->hide();
    ui->horizontalSpacer->changeSize(40,20,QSizePolicy::Expanding);
    update();
}

void ItemTool_BorderPanel::updateBorder(int width, const QColor& color, Qt::PenStyle penStyle)
{
    m_pBorderWidth = width;
    m_pBorderColor = color;

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

    if (penStyle == Qt::SolidLine) ui->pBorderFullLine->setChecked(true);
    else if (penStyle == Qt::DotLine) ui->pBorderPointLine->setChecked(true);
    else if (penStyle == Qt::DashLine) ui->pBorderDottedLine->setChecked(true);
}

void ItemTool_BorderPanel::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);
    /*边框面板*/
    ui->verticalLayoutWidget->hide();
    ui->frame_border->setLayout(ui->verticalLayout);
    ui->frame_border->mSetBackgroudColor(Qt::white);
    ui->pBorderSize1->mSetValue(Public_Function::getScaleSize(1));
    ui->pBorderSize2->mSetValue(Public_Function::getScaleSize(3));
    ui->pBorderSize3->mSetValue(Public_Function::getScaleSize(8));
    ui->pBorderSize4->mSetValue(Public_Function::getScaleSize(12));
    ui->horizontalSpacer->changeSize(0,0);
    ui->pBorderFullLine->msetShape(0);
    ui->pBorderPointLine->msetShape(1);
    ui->pBorderDottedLine->msetShape(2);
    borderLineGroup = new QButtonGroup(this);
    borderLineGroup->setExclusive(true);
    borderLineGroup->addButton(ui->pBorderFullLine,1);
    borderLineGroup->addButton(ui->pBorderPointLine,2);
    borderLineGroup->addButton(ui->pBorderDottedLine,3);
    connect(borderLineGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&ItemTool_BorderPanel::onBorderLineGroup);

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
    borderSizeGroup = new QButtonGroup(this);
    borderSizeGroup->setExclusive(true);
    borderSizeGroup->addButton(ui->pBorderSize1,1);
    borderSizeGroup->addButton(ui->pBorderSize2,2);
    borderSizeGroup->addButton(ui->pBorderSize3,3);
    borderSizeGroup->addButton(ui->pBorderSize4,4);
    borderColorGroup = new QButtonGroup(this);
    borderColorGroup->setExclusive(true);
    borderColorGroup->addButton(ui->pBorderColor1,1);
    borderColorGroup->addButton(ui->pBorderColor2,2);
    borderColorGroup->addButton(ui->pBorderColor3,3);
    borderColorGroup->addButton(ui->pBorderColor4,4);
    borderColorGroup->addButton(ui->pBorderColor5,5);
    borderColorGroup->addButton(ui->pBorderColor6,6);
    borderColorGroup->addButton(ui->pBorderColor7,7);
    borderColorGroup->addButton(ui->pBorderColor8,8);
    connect(borderSizeGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&ItemTool_BorderPanel::onBorderSizeGroup);
    connect(borderColorGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&ItemTool_BorderPanel::onBorderColorGroup);

}

void ItemTool_BorderPanel::resize()
{
    /*边框面板*/
    QSize size = Public_Function::getScaleSize(QSize(226, 270));
    ui->frame_border->setFixedSize(size);
    int radius = Public_Function::getScaleSize(12);
    ui->frame_border->mSetBordRadius(radius, radius, radius, radius);
    ui->frame_border->mSetBorder(Public_Function::getScaleSize(2));
    size = Public_Function::getScaleSize(QSize(54, 38));
    ui->pBorderFullLine->setFixedSize(size);
    ui->pBorderPointLine->setFixedSize(size);
    ui->pBorderDottedLine->setFixedSize(size);
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
    ui->label_line_2->setFixedSize(size);

    this->adjustSize();
}

bool ItemTool_BorderPanel::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        {
            QTouchEvent* ev =static_cast<QTouchEvent*>(event);
            QPoint dot =ev->touchPoints().at(0).pos().toPoint();
            if(ui->pBorderFullLine->geometry().contains(dot));
            else if(ui->pBorderPointLine->geometry().contains(dot));
            else if(ui->pBorderDottedLine->geometry().contains(dot));
            else
            {
                return true;
            }
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
            if(ui->pBorderSize1->geometry().contains(dot))
             {
               if(ui->pBorderSize1->isChecked())return true;
               ui->pBorderSize1->setChecked(true);
               m_pBorderWidth = ui->pBorderSize1->mGetValue();
               emit this->borderSizeChanged(m_pBorderWidth);
             }
             else if(ui->pBorderSize2->geometry().contains(dot))
             {
                if(ui->pBorderSize2->isChecked())return true;
                ui->pBorderSize2->setChecked(true);
                m_pBorderWidth = ui->pBorderSize2->mGetValue();
                emit this->borderSizeChanged(m_pBorderWidth);
             }
             else if(ui->pBorderSize3->geometry().contains(dot))
             {
                if(ui->pBorderSize3->isChecked())return true;
                ui->pBorderSize3->setChecked(true);
                m_pBorderWidth = ui->pBorderSize3->mGetValue();
                emit this->borderSizeChanged(m_pBorderWidth);
             }
             else if(ui->pBorderSize4->geometry().contains(dot))
             {
                if(ui->pBorderSize4->isChecked())return true;
                ui->pBorderSize4->setChecked(true);
                m_pBorderWidth = ui->pBorderSize4->mGetValue();
                emit this->borderSizeChanged(m_pBorderWidth);
             }
             else if(ui->pBorderColor1->geometry().contains(dot))
             {
                if(ui->pBorderColor1->isChecked())return true;
                ui->pBorderColor1->setChecked(true);
                m_pBorderColor = ui->pBorderColor1->mGetColor();
                emit this->borderColorChanged(m_pBorderColor);
             }
             else if(ui->pBorderColor2->geometry().contains(dot))
             {
                if(ui->pBorderColor2->isChecked())return true;
                ui->pBorderColor2->setChecked(true);
                m_pBorderColor = ui->pBorderColor2->mGetColor();
                emit this->borderColorChanged(m_pBorderColor);
             }
             else if(ui->pBorderColor3->geometry().contains(dot))
             {
                if(ui->pBorderColor3->isChecked())return true;
                ui->pBorderColor3->setChecked(true);
                m_pBorderColor = ui->pBorderColor3->mGetColor();
                emit this->borderColorChanged(m_pBorderColor);
             }
             else if(ui->pBorderColor4->geometry().contains(dot))
             {
                if(ui->pBorderColor4->isChecked())return true;
                ui->pBorderColor4->setChecked(true);
                m_pBorderColor = ui->pBorderColor4->mGetColor();
                emit this->borderColorChanged(m_pBorderColor);
             }
             else if(ui->pBorderColor5->geometry().contains(dot))
             {
                if(ui->pBorderColor5->isChecked())return true;
                ui->pBorderColor5->setChecked(true);
                m_pBorderColor = ui->pBorderColor5->mGetColor();
                emit this->borderColorChanged(m_pBorderColor);
             }
             else if(ui->pBorderColor6->geometry().contains(dot))
             {
                if(ui->pBorderColor6->isChecked())return true;
                ui->pBorderColor6->setChecked(true);
                m_pBorderColor = ui->pBorderColor6->mGetColor();
                emit this->borderColorChanged(m_pBorderColor);
             }
             else if(ui->pBorderColor7->geometry().contains(dot))
             {
                if(ui->pBorderColor7->isChecked())return true;
                ui->pBorderColor7->setChecked(true);
                m_pBorderColor = ui->pBorderColor7->mGetColor();
                emit this->borderColorChanged(m_pBorderColor);
             }
             else if(ui->pBorderColor8->geometry().contains(dot))
             {
                if(ui->pBorderColor8->isChecked())return true;
                ui->pBorderColor8->setChecked(true);
                m_pBorderColor = ui->pBorderColor8->mGetColor();
                emit this->borderColorChanged(m_pBorderColor);
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

void ItemTool_BorderPanel::onBorderSizeGroup(QAbstractButton *button)
{
   int num =borderSizeGroup->id(button);
    if (num == 1)
        m_pBorderWidth = ui->pBorderSize1->mGetValue();
    else if (num == 2)
        m_pBorderWidth = ui->pBorderSize2->mGetValue();
    else if (num == 3)
        m_pBorderWidth = ui->pBorderSize3->mGetValue();
    else if (num == 4)
        m_pBorderWidth = ui->pBorderSize4->mGetValue();
    else
        return;
    emit this->borderSizeChanged(m_pBorderWidth);
}

void ItemTool_BorderPanel::onBorderLineGroup(QAbstractButton *button)
{
     int num =borderLineGroup->id(button);
     Qt::PenStyle style = Qt::SolidLine;
     if (num == 1)style = Qt::SolidLine;
     else if (num == 2)style = Qt::DotLine;
     else if (num == 3)style = Qt::DashLine;
     else return ;;
     emit borderLineChanged(style);
}


void ItemTool_BorderPanel::onBorderColorGroup(QAbstractButton *button)
{
    int num =borderColorGroup->id(button);
    if (num == 1)
        m_pBorderColor = QColor(ui->pBorderColor1->mGetColor());
    else if (num == 2)
        m_pBorderColor = QColor(ui->pBorderColor2->mGetColor());
    else if (num == 3)
        m_pBorderColor = QColor(ui->pBorderColor3->mGetColor());
    else if (num == 4)
        m_pBorderColor = QColor(ui->pBorderColor4->mGetColor());
    else if (num == 5)
        m_pBorderColor = QColor(ui->pBorderColor5->mGetColor());
    else if (num == 6)
        m_pBorderColor = QColor(ui->pBorderColor6->mGetColor());
    else if (num == 7)
        m_pBorderColor = QColor(ui->pBorderColor7->mGetColor());
    else if (num == 8)
        m_pBorderColor = QColor(ui->pBorderColor8->mGetColor());
    else
        return;
    emit this->borderColorChanged(m_pBorderColor);
}
