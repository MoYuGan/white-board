#include "menupanel_export.h"
#include "ui_menupanel_export.h"

MenuPanel_Export::MenuPanel_Export(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuPanel_Export)
{
    ui->setupUi(this);
    this->initWidget();
}

MenuPanel_Export::~MenuPanel_Export()
{
    delete ui;
}

void MenuPanel_Export::resizeWidget()
{
    ui->verticalLayout->setContentsMargins(Public_Function::getScaleSize(6), Public_Function::getScaleSize(10),
                                           Public_Function::getScaleSize(6), Public_Function::getScaleSize(10));
    ui->verticalLayout->setSpacing(4);
    QSize size = Public_Function::getScaleSize(QSize(176, 178));
    this->setFixedSize(size);
    QString strStyle = QString("QPushButton{"
                                "border: none;"
                                "background: transparent;"
                                "color: rgb(68, 68, 68);}"
                                "QPushButton::hover{"
                                "background: rgb(238, 238, 238);"
                                "}");
    ui->pExportToPicture->setStyleSheet(strStyle);
    ui->pExportAllToPicture->setStyleSheet(strStyle);
    ui->pExportOther->setStyleSheet(strStyle);

    QFont font = Public_Function::getFont(16);
    ui->pExportToPicture->setFont(font);
    ui->pExportAllToPicture->setFont(font);
    ui->pExportOther->setFont(font);

    m_ShadowEffect->setBlurRadius(Public_Function::getScaleSize(8));
    m_ShadowEffect->setXOffset(-Public_Function::getScaleSize(6));
    m_ShadowEffect->setYOffset(-Public_Function::getScaleSize(6));
}

void MenuPanel_Export::show()
{
    QWidget::show();
    this->raise();
}

void MenuPanel_Export::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

void MenuPanel_Export::paintEvent(QPaintEvent *event)
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
        int radius = Public_Function::getScaleSize(4);
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

void MenuPanel_Export::initWidget()
{
    ui->verticalLayoutWidget_11->hide();
    this->setLayout(ui->verticalLayout);
    connect(ui->pExportToPicture, &PushButton_Basic::clicked, this, [=]() {emit this->exportToFile(1);});
    connect(ui->pExportAllToPicture, &PushButton_Basic::clicked, this, [=]() {emit this->exportToFile(2);});
    connect(ui->pExportOther, &PushButton_Basic::clicked, this, [=]() {emit this->exportToFile(3);});

    m_ShadowEffect = new QGraphicsDropShadowEffect(this);
    m_ShadowEffect->setColor(QColor(135, 135, 135, 50));
    this->setGraphicsEffect(m_ShadowEffect);
}
