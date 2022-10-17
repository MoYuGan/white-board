#include "custompushbutton_1.h"
#include <QtDebug>

CustomPushButton_1::CustomPushButton_1(QWidget *parent) :
    CustomPushButton(parent)
{
    this->initWidget();
    this->installEventFilter(this);
    this->setStyleSheet("QPushButton{border: none;}");
    connect(this, &CustomPushButton_1::toggled, this, &CustomPushButton_1::onBtnToggled);
}

void CustomPushButton_1::mSetText(const QString &text, const QColor &textColor, const QColor &checkedTextColor)
{
    if (nullptr == m_pLabelText && !text.isEmpty()) {
        m_pLabelText = new QLabel(this);
        m_pLabelText->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
        m_pLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
        m_pLayout->addWidget(m_pLabelText, 0, Qt::AlignCenter);

        m_pLabelText->setText(text);
        m_pLabelText->adjustSize();

        m_pTextColor = textColor;
        m_pCheckedTextColor = checkedTextColor;
        if (!this->isChecked() && textColor.isValid())  {
            m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                        .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                        .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
        }else if (this->isChecked() && checkedTextColor.isValid()){
            m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                        .arg(m_pCheckedTextColor.red()).arg(m_pCheckedTextColor.green())
                                        .arg(m_pCheckedTextColor.blue()).arg(m_pCheckedTextColor.alpha()));
        }
    }else if (nullptr != m_pLabelText){
        m_pLabelText->setText(text);
    }
}

void CustomPushButton_1::mSetFont(const QFont &font)
{
    if (nullptr != m_pLabelText)
        m_pLabelText->setFont(font);
}

void CustomPushButton_1::mSetIcon(const QPixmap &icon, const QPixmap &checkedIcon, const QPixmap &hoverIcon)
{
    m_pIcon = icon;
    m_pCheckedIcon = checkedIcon;
    m_pHoverIcon = hoverIcon;
    if (!this->isChecked()) {
        if (!m_pIcon.isNull())
            m_pLabelIcon->setPixmap(m_pIcon);
    }else {
        if (!m_pCheckedIcon.isNull())
            m_pLabelIcon->setPixmap(m_pCheckedIcon);
    }
}

void CustomPushButton_1::mSetColor(const QColor &hoverColor, const QColor &backgroundColor, const QColor &checkedColor)
{
    m_pBGColor = backgroundColor;
    m_pHoverColor = hoverColor;
    m_pCheckedColor = checkedColor;
}

void CustomPushButton_1::mSetIconSize(const QSize &size)
{
    m_pLabelIcon->setFixedSize(size);
}

void CustomPushButton_1::mSetRadius(int radius)
{
    m_pRadius = radius;
}

bool CustomPushButton_1::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter)
        m_pMouseEnter = true;
    else if (event->type() == QEvent::Leave)
        m_pMouseEnter = false;
    else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton &&
                this->rect().contains(mouseEvent->pos()) &&
                this->isChecked()) {
            emit checkedClicked();
        }
    }

    return CustomPushButton::eventFilter(watched, event);
}

void CustomPushButton_1::mSetCheckedIcon(const QPixmap &pixmap)
{
    m_pCheckedIcon = pixmap;
    if (this->isChecked())
        m_pLabelIcon->setPixmap(pixmap);
}

void CustomPushButton_1::mSetMargin(int left, int top, int right, int bottom)
{
    m_pLayout->setContentsMargins(left, top, right, bottom);
}

void CustomPushButton_1::mSetEnabled(bool enabled, const QColor &textColor)
{
    if (!enabled) {
        if (textColor.isValid())
            m_pLabelText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(textColor.red())
                                       .arg(textColor.green()).arg(textColor.blue()).arg(textColor.alpha()));
    }else {
        if (m_pTextColor.isValid())
            m_pLabelText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(m_pTextColor.red())
                                       .arg(m_pTextColor.green()).arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
    }
    this->setEnabled(enabled);
}

void CustomPushButton_1::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path = PublicFunction::getRoundRectPath(this->rect(), m_pRadius);
    QColor color = Qt::transparent;
    if (this->isChecked()) {
        if (m_pCheckedColor.isValid())
            color = m_pCheckedColor;
    }else {
        if (m_pMouseEnter && m_pHoverColor.isValid()){
            color = m_pHoverColor;
        }else if (m_pMouseEnter && !m_pHoverIcon.isNull()) {
            m_pLabelIcon->setPixmap(m_pHoverIcon);
        }else if (!m_pMouseEnter && !m_pHoverIcon.isNull() && !m_pIcon.isNull()){
            m_pLabelIcon->setPixmap(m_pIcon);
        }else if (m_pBGColor.isValid()){
            color = m_pBGColor;
        }
    }
    painter.fillPath(path, QBrush(color));
}


void CustomPushButton_1::initWidget()
{
    m_pLayout = new QVBoxLayout(this);
    m_pLayout->setContentsMargins(0, 0, 0, 0);
    m_pLayout->setSpacing(0);

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setScaledContents(true);
    m_pLayout->addWidget(m_pLabelIcon, 0, Qt::AlignCenter);
}

void CustomPushButton_1::onBtnToggled(bool checked)
{
    if (checked) {
        if (m_pCheckedTextColor.isValid() &&  nullptr != m_pLabelText)
            m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                        .arg(m_pCheckedTextColor.red()).arg(m_pCheckedTextColor.green())
                                        .arg(m_pCheckedTextColor.blue()).arg(m_pCheckedTextColor.alpha()));
        if (!m_pCheckedIcon.isNull()) {
            m_pLabelIcon->setPixmap(m_pCheckedIcon);
        }
    }else {
        if (m_pTextColor.isValid() &&  nullptr != m_pLabelText)
            m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                        .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                        .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
        if (!m_pIcon.isNull())
            m_pLabelIcon->setPixmap(m_pIcon);
    }
}
