#include "selectpanel.h"
#include "ui_selectpanel.h"

SelectPanel::SelectPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectPanel)
{
    ui->setupUi(this);
    this->initWidget();
}

SelectPanel::~SelectPanel()
{
    delete ui;
}

void SelectPanel::show()
{
    QWidget::show();
    this->raise();
}

void SelectPanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

void SelectPanel::resizeWidget()
{
    QSize size = Public_Function::getScaleSize(QSize(86, 92));
    this->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(50, 50));
    ui->pSelectAll->setFixedSize(size);
    ui->label_select->setFont(Public_Function::getFont(11));
    QColor color = Public_Function::getTextColor();
    ui->label_select->setStyleSheet(QString("QLabel{color: %1, %2, %3, %4;}")
                                    .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
}

void SelectPanel::paintEvent(QPaintEvent *event)
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

void SelectPanel::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);
    ui->pSelectAll->setPixmap(QPixmap(":/images/main/selectPanel/quanxuan@2x.png"));
    connect(ui->pSelectAll, &PushButton_1::clicked, this,[=](){ emit this->selectAll(); });
}
