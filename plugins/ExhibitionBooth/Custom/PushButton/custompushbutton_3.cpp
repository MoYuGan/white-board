#include "custompushbutton_3.h"
#include <QtDebug>
CustomPushButton_3::CustomPushButton_3(QWidget *parent) :
    CustomPushButton(parent)
{
    this->initWidget();
    connect(this, &CustomPushButton_3::toggled, this, &CustomPushButton_3::onBtnToggled);
}

void CustomPushButton_3::mSetText(const QString &text, const QColor &color, const QColor &checkedColor)
{
    m_LabelText->setText(text);
    m_TextColor = color;
    m_CheckedTextColor = checkedColor;
}

void CustomPushButton_3::mSetColor(const QColor &bgColor, const QColor hoverColor, const QColor &checkedColor)
{
    m_BGColor = bgColor;
    m_HoverColor = hoverColor;
    m_CheckedColor = checkedColor;
}

void CustomPushButton_3::mSetIcon(const QPixmap &icon, const QPixmap &checkedIcon)
{
    m_Icon = icon;
    m_CheckedIcon = checkedIcon;
    m_LabelIcon->setPixmap(m_Icon);
}

void CustomPushButton_3::mSetIconSize(QSize size)
{
    m_LabelIcon->setFixedSize(size);
}

void CustomPushButton_3::mSetTextSize(QSize size)
{
    m_LabelText->setFixedSize(size);
}

void CustomPushButton_3::mSetFont(const QFont &font)
{
    m_LabelText->setFont(font);
}

void CustomPushButton_3::mSetRadius(int radius)
{
    m_Radius = radius;
}

bool CustomPushButton_3::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter && this->isEnabled()) {
        m_MouseEnter = true;
    }else if (event->type() == QEvent::Leave && this->isEnabled()) {
        m_MouseEnter = false;
    }
    return CustomPushButton::eventFilter(watched, event);
}

void CustomPushButton_3::mSetEnabled(bool bo, const QPixmap &pixmap, const QColor &textColor)
{
    if (!bo) {
        if (this->isChecked())
            this->setChecked(false);
        if (!pixmap.isNull())
            m_LabelIcon->setPixmap(pixmap);
        if (textColor.isValid())
            m_LabelText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(textColor.red())
                                       .arg(textColor.green()).arg(textColor.blue()).arg(textColor.alpha()));
    }else {
        if (!m_Icon.isNull())
            m_LabelIcon->setPixmap(m_Icon);
        if (m_TextColor.isValid())
            m_LabelText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(m_TextColor.red())
                                       .arg(m_TextColor.green()).arg(m_TextColor.blue()).arg(m_TextColor.alpha()));
    }
    this->setEnabled(bo);
}

void CustomPushButton_3::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path = PublicFunction::getRoundRectPath(this->rect(), m_Radius);
    QColor color = Qt::transparent;
    if (this->isChecked()) {
        if (m_CheckedColor.isValid())
            color = m_CheckedColor;
    }else {
        if (m_MouseEnter && m_HoverColor.isValid())
            color = m_HoverColor;
        else if (m_BGColor.isValid())
            color = m_BGColor;
    }
    painter.fillPath(path, QBrush(color));
}

void CustomPushButton_3::initWidget()
{
    m_Layout = new QHBoxLayout(this);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->setSpacing(0);

    m_LabelIcon = new QLabel(this);
    m_LabelIcon->setScaledContents(true);
    m_LabelText = new QLabel(this);
    m_LabelSpacing = new QLabel(this);

    m_Layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    m_Layout->addWidget(m_LabelIcon);
    m_Layout->addWidget(m_LabelSpacing);
    m_Layout->addWidget(m_LabelText);
    m_Layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
}

void CustomPushButton_3::onBtnToggled(bool checked)
{
    if (checked) {
        if (!m_CheckedIcon.isNull())
            m_LabelIcon->setPixmap(m_CheckedIcon);
        if (m_CheckedTextColor.isValid())
            m_LabelText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(m_CheckedTextColor.red())
                                       .arg(m_CheckedTextColor.green()).arg(m_CheckedTextColor.blue()).arg(m_CheckedTextColor.alpha()));
    }else {
        if (!m_Icon.isNull())
            m_LabelIcon->setPixmap(m_Icon);
        if (m_TextColor.isValid())
            m_LabelText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(m_TextColor.red())
                                       .arg(m_TextColor.green()).arg(m_TextColor.blue()).arg(m_TextColor.alpha()));
    }
}
