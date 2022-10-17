#include "resolutionmenu.h"
#include "ui_resolutionmenu.h"

static int BORDER = 0;    //阴影边距

ResolutionMenu::ResolutionMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResolutionMenu)
{
    ui->setupUi(this);
    this->initWidget();
    this->resizeWidget();
}

ResolutionMenu::~ResolutionMenu()
{
    delete ui;
}

void ResolutionMenu::show()
{
    QWidget::show();
    this->raise();
}

void ResolutionMenu::resizeWidget()
{
    BORDER = PublicFunction::getScaleSize(3);
    int spacing = PublicFunction::getScaleSize(2);
    int marginTopBottom = BORDER + PublicFunction::getScaleSize(4);
    int marginLeftRight = BORDER;
    ui->verticalLayout->setContentsMargins(marginLeftRight, marginTopBottom, marginLeftRight, marginTopBottom);
    ui->verticalLayout->setSpacing(spacing);

    int btnCount = m_ResolutionBtnList.size();
    int btnHeight = PublicFunction::getScaleSize(50);
    this->setFixedSize(PublicFunction::getScaleSize(130) + BORDER * 2,
                       btnHeight * btnCount + spacing * (btnCount - 1) + marginTopBottom * 2);

    foreach(QPushButton *button, m_ResolutionBtnList) {
        btnCount++;
        button->setFixedHeight(btnHeight);
        button->setFixedWidth(this->width() - 2 * BORDER);
        button->setFont(PublicFunction::getFont(16));
    }
}

void ResolutionMenu::mSetAction(const QList<QString> &resolutionList)
{
    foreach(QPushButton *button, m_ResolutionBtnList) {
        ui->verticalLayout->removeWidget(button);
        m_ResolutionGroup->removeButton(button);
        button->deleteLater();
    }
    m_ResolutionBtnList.clear();

    if (0 == resolutionList.size())
        return;

    for(int i = 0; i < resolutionList.size(); i++)
    {
        QPushButton *button = new QPushButton(this);
        button->setCheckable(true);
        button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        button->setStyleSheet(QString("QPushButton{border: none;"
                                 "color: rgb(68, 68, 68);"
                                 "background: transparent;}"
                                 "QPushButton::hover{"
                                 "background: rgb(238, 238, 238);"
                                 "}"
                                 "QPushButton::checked{"
                                 "color: rgb(20,134,250);}"));
        button->setText(resolutionList.at(i));
        ui->verticalLayout->addWidget(button, 0, Qt::AlignCenter);
        m_ResolutionBtnList.push_back(button);
        m_ResolutionGroup->addButton(button);
    }
    this->resizeWidget();
}

void ResolutionMenu::clearAction()
{
    foreach(QPushButton *button, m_ResolutionBtnList) {
        ui->verticalLayout->removeWidget(button);
        m_ResolutionGroup->removeButton(button);
        button->deleteLater();
    }
    m_ResolutionBtnList.clear();
    this->setFixedSize(0, 0);
}

void ResolutionMenu::setChecked(int index, bool checked)
{
    if (index < 0 || index >= m_ResolutionBtnList.size())
        return;
    disconnect(m_ResolutionGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onResolutionGroupToggled(QAbstractButton*,bool)));
    m_ResolutionBtnList.at(index)->setChecked(checked);
    connect(m_ResolutionGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onResolutionGroupToggled(QAbstractButton*,bool)));

}

void ResolutionMenu::paintEvent(QPaintEvent *event)
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
    for(int i = 0; i < BORDER; i++)
    {
        QRect rect = QRect(QPoint(BORDER - i, BORDER - i),
                           QPoint(this->width() - (BORDER - i),
                            this->height() - (BORDER - i)));
        QPainterPath path;
        int radius = PublicFunction::getScaleSize(4);
        path = PublicFunction::getRoundRectPath(rect, radius, radius, radius, radius);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }
        switch(i)
        {
        case 0:
            color.setAlpha(50);
            break;
        case 1:
            color.setAlpha(25);
            break;
        case 2:
            color.setAlpha(10);
            break;
        default:
            break;
        }
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void ResolutionMenu::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);

    m_ResolutionGroup = new QButtonGroup(this);
    m_ResolutionGroup->setExclusive(true);
    connect(m_ResolutionGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onResolutionGroupToggled(QAbstractButton*,bool)));
}

void ResolutionMenu::onResolutionGroupToggled(QAbstractButton *button, bool checked)
{
    if (checked) {
        foreach(QPushButton *btn, m_ResolutionBtnList) {
            if (btn == button) {
                emit this->resolutionChanged(btn->text());
                return;
            }
        }
    }
}
