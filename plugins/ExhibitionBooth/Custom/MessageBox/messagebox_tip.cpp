#include "messagebox_tip.h"

MessageBox_Tip::MessageBox_Tip(QWidget *parent) : QWidget(parent)
{
    this->initWidget();
    this->resizeWidget();

    m_Timer = new QTimer(this);
    connect(m_Timer, &QTimer::timeout, this, &MessageBox_Tip::onTimeOut);
}

void MessageBox_Tip::setText(const QString &text)
{
    m_Label->setText(text);
    m_Label->adjustSize();
    m_Label->setFixedHeight(this->height());
    this->setFixedWidth(m_Label->width() + PublicFunction::getScaleSize(25) * 2);
}

void MessageBox_Tip::resizeWidget()
{
    this->setFixedHeight(PublicFunction::getScaleSize(50));
    m_Label->setFont(PublicFunction::getFont(18));
    this->layout()->setContentsMargins(PublicFunction::getScaleSize(25), 0, PublicFunction::getScaleSize(25), 0);
}

void MessageBox_Tip::show()
{
    QWidget::show();
    m_Timer->start(1000);
}

void MessageBox_Tip::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    QPainterPath path = PublicFunction::getRoundRectPath(this->rect(), this->height()/2);
    painter.fillPath(path, QBrush(QColor(0, 0, 0, 200)));
}

void MessageBox_Tip::initWidget()
{
    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->setSpacing(0);

    m_Label = new QLabel(this);
    m_Label->setAlignment(Qt::AlignCenter);
    m_Label->setStyleSheet("QLabel{color:white;}");

    hlayout->addWidget(m_Label);
}

void MessageBox_Tip::onTimeOut()
{
    m_Timer->stop();
    this->hide();
}

