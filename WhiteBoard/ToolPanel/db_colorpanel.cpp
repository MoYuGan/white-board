#include "db_colorpanel.h"
#include "ui_db_colorpanel.h"

DB_ColorPanel::DB_ColorPanel(const QColor &color, QWidget *parent) :
    QWidget(parent),
    m_pCurrentColor(color),
    ui(new Ui::DB_ColorPanel)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();

    ui->redSlider->setValue(color.red());
    ui->greenSlider->setValue(color.green());
    ui->blueSlider->setValue(color.blue());
    ui->alphaSlider->setValue(color.alpha());
}

DB_ColorPanel::~DB_ColorPanel()
{
    delete ui;
}

void DB_ColorPanel::show()
{
    QWidget::show();
    this->raise();
}

void DB_ColorPanel::resize()
{
    QSize size = Public_Function::getScaleSize(QSize(12, 12));
    ui->pClose->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(36, 36));
    ui->pCutRed->setFixedSize(size);
    ui->pAddRed->setFixedSize(size);
    ui->pCutGreen->setFixedSize(size);
    ui->pAddGreen->setFixedSize(size);
    ui->pCutBlue->setFixedSize(size);
    ui->pAddBlue->setFixedSize(size);
    ui->pCutAlpha->setFixedSize(size);
    ui->pAddAlpha->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(50, 30));
    ui->label_red->setFixedWidth(size.width());
    ui->label_green->setFixedWidth(size.width());
    ui->label_blue->setFixedWidth(size.width());
    ui->label_alpha->setFixedWidth(size.width());
    size = Public_Function::getScaleSize(QSize(30, 30));
    ui->redValue->setFixedWidth(size.width());
    ui->greenValue->setFixedWidth(size.width());
    ui->blueValue->setFixedWidth(size.width());
    ui->alphaValue->setFixedWidth(size.width());
    size = Public_Function::getScaleSize(QSize(100, 35));
    ui->pDetermine->setFixedSize(size);
    ui->pCancel->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(330, 120));
    ui->widget->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(30, 80));
    ui->widget_2->setFixedWidth(size.width());
    size = Public_Function::getScaleSize(QSize(200, 30));
    ui->label_color->setFixedHeight(size.height());

    QFont font = Public_Function::getFont(12);
    ui->label_red->setFont(font);
    ui->label_green->setFont(font);
    ui->label_blue->setFont(font);
    ui->redValue->setFont(font);
    ui->greenValue->setFont(font);
    ui->blueValue->setFont(font);
    ui->pDetermine->setFont(font);
    ui->pCancel->setFont(font);
    ui->label_alpha->setFont(font);
    font = Public_Function::getFont(14);
    ui->label_title->setFont(font);
}

QColor DB_ColorPanel::getColor()
{
    m_pCurrentColor = QColor(ui->redSlider->value(),
                             ui->greenSlider->value(),
                             ui->blueSlider->value(),
                             ui->alphaSlider->value());
    return m_pCurrentColor;
}

void DB_ColorPanel::initWidget()
{
    this->setLayout(ui->horizontalLayout);
    ui->widgetMain->setLayout(ui->verticalLayout);

    connect(ui->pDetermine, &PushButton_Basic::clicked, [=](){ emit this->colorPanelClosed(1);});
    connect(ui->pCancel, &PushButton_Basic::clicked, [=](){ emit this->colorPanelClosed(0);});
    connect(ui->pClose, &PushButton_Basic::clicked, [=](){ emit this->colorPanelClosed(0);});
    connect(ui->redSlider, &DB_CustomSlider::valueChanged, [=](){
        ui->redValue->setText(QString::number(ui->redSlider->value()));
        this->setLabelColor();
    });
    connect(ui->greenSlider, &DB_CustomSlider::valueChanged, [=](){
        ui->greenValue->setText(QString::number(ui->greenSlider->value()));
        this->setLabelColor();
    });
    connect(ui->blueSlider, &DB_CustomSlider::valueChanged, [=](){
        ui->blueValue->setText(QString::number(ui->blueSlider->value()));
        this->setLabelColor();
    });
    connect(ui->alphaSlider, &DB_CustomSlider::valueChanged, [=](){
        ui->alphaValue->setText(QString::number(ui->alphaSlider->value()));
        this->setLabelColor();
    });
    connect(ui->pCutRed, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->redSlider->value();
        if (value > 0)
            ui->redSlider->setValue(--value);
    });
    connect(ui->pCutRed, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->redSlider->value();
        if (value > 0)
            ui->redSlider->setValue(--value);
    });
    connect(ui->pCutGreen, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->greenSlider->value();
        if (value > 0)
            ui->greenSlider->setValue(--value);
    });
    connect(ui->pCutBlue, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->blueSlider->value();
        if (value > 0)
            ui->blueSlider->setValue(--value);
    });
    connect(ui->pCutAlpha, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->alphaSlider->value();
        if (value > 0)
            ui->alphaSlider->setValue(--value);
    });
    connect(ui->pAddRed, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->redSlider->value();
        if (value < 255)
            ui->redSlider->setValue(++value);
    });
    connect(ui->pAddGreen, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->greenSlider->value();
        if (value < 255)
            ui->greenSlider->setValue(++value);
    });
    connect(ui->pAddBlue, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->blueSlider->value();
        if (value < 255)
            ui->blueSlider->setValue(++value);
    });
    connect(ui->pAddAlpha, &DB_CustomPushButton_5::clicked, [=](){
        int value = ui->alphaSlider->value();
        if (value < 255)
            ui->alphaSlider->setValue(++value);
    });
    connect(ui->widget_2, &DB_CustomWidget_6::send_color,[=](int r,int g,int b,int a){
        ui->redSlider->setValue(r);
        ui->greenSlider->setValue(g);
        ui->blueSlider->setValue(b);
        ui->alphaSlider->setValue(a);
        ui->widget->Get_color(r,g,b,a);
    });

    connect(ui->widget, &DB_CustomWidget_7::select_color,[=](int r,int g,int b,int a){
        ui->redSlider->setValue(r);
        ui->greenSlider->setValue(g);
        ui->blueSlider->setValue(b);
        ui->alphaSlider->setValue(a);
    });
}

void DB_ColorPanel::setLabelColor()
{
    ui->label_color->setStyleSheet(QString("border: 1px solid gray; background-color:rgb(%1, %2, %3, %4);")
                                   .arg(ui->redSlider->value())
                                   .arg(ui->greenSlider->value())
                                   .arg(ui->blueSlider->value())
                                   .arg(ui->alphaSlider->value()));
}
