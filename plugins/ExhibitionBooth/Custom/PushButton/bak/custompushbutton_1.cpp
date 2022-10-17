#include "custompushbutton_1.h"

CustomPushButton_1::CustomPushButton_1(QWidget *parent) :
    CustomPushButton(parent)
{
    this->initWidget();
    this->setStyleSheet("QPushButton{border: none;}");
    connect(this, &CustomPushButton_1::toggled, this, &CustomPushButton_1::onBtnToggled);
}

void CustomPushButton_1::mSetIcon(const QPixmap &pixmap, const QPixmap &checkedPixmap)
{
    m_pIconPixmap = pixmap;
    m_pIconCheckedPixmap = checkedPixmap;
    if (this->isChecked() && !m_pIconCheckedPixmap.isNull())
        m_pLabelIcon->setPixmap(m_pIconCheckedPixmap);
    else
        m_pLabelIcon->setPixmap(m_pIconPixmap);
}

void CustomPushButton_1::mSetText(const QString &text)
{
    m_pLabelText->setText(text);
}

void CustomPushButton_1::mSetColor(const QColor &textColor, const QColor &checkedTextColor)
{
    m_pTextColor = textColor;
    m_pTextCheckedColor = checkedTextColor;
    if (this->isChecked() && checkedTextColor.isValid())
    {
        m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                    .arg(checkedTextColor.red()).arg(checkedTextColor.green())
                                    .arg(checkedTextColor.blue()).arg(checkedTextColor.alpha()));
    }else {
        m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                    .arg(textColor.red()).arg(textColor.green())
                                    .arg(textColor.blue()).arg(textColor.alpha()));
    }
}

void CustomPushButton_1::mSetArrow(const QPixmap &pixmap, const QPixmap &checkedPixmap)
{
    m_pArrowPixmap = pixmap;
    m_pArrowCheckedPixmap = checkedPixmap;
    if (this->isChecked() && !m_pArrowCheckedPixmap.isNull())
        m_pLabelArrow->setPixmap(m_pArrowCheckedPixmap);
    else
        m_pLabelArrow->setPixmap(m_pArrowPixmap);
}

void CustomPushButton_1::mSetBGColor(const QColor &BGColor, const QColor &hoverBGColor, const QColor &checkedBGColor)
{
    QString style = QString("QPushButton{"
                            "background-color: rgba(%1, %2, %3, %4); border: none;}").arg(BGColor.red()).arg(BGColor.green())
                            .arg(BGColor.blue()).arg(BGColor.alpha());
    if (hoverBGColor.isValid())
        style.append(QString("QPushButton::hover{"
                             "background-color: rgba(%1, %2, %3, %4);}").arg(hoverBGColor.red()).arg(hoverBGColor.green())
                             .arg(hoverBGColor.blue()).arg(hoverBGColor.alpha()));
    if (checkedBGColor.isValid())
        style.append(QString("QPushButton::checked{"
                             "background-color: rgba(%1, %2, %3, %4);}").arg(checkedBGColor.red()).arg(checkedBGColor.green())
                             .arg(checkedBGColor.blue()).arg(checkedBGColor.alpha()));
    this->setStyleSheet(style);
}

void CustomPushButton_1::mSetMarginAndSpacing(int left, int top, int right, int bottom, int spacing)
{
    m_pLayout->setContentsMargins(left, top, right, bottom);
    m_pLabelNull->setFixedSize(spacing, 1);
}

void CustomPushButton_1::mSetIconSize(int width, int height)
{
    m_pLabelIcon->setFixedSize(width, height);
}

void CustomPushButton_1::mSetArrowSize(int width, int height)
{
    m_pLabelArrow->setFixedSize(width, height);
}

void CustomPushButton_1::mSetFont(const QFont &font)
{
    m_pLabelText->setFont(font);
}

void CustomPushButton_1::initWidget()
{
    m_pLayout = new QHBoxLayout(this);
    m_pLayout->setContentsMargins(0, 0, 0, 0);
    m_pLayout->setSpacing(0);

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setScaledContents(true);
    m_pLabelArrow = new QLabel(this);
    m_pLabelArrow->setScaledContents(true);
    m_pLabelArrow->setFixedSize(0, 0);
    m_pLabelText = new QLabel(this);
    m_pLabelText->setAlignment(Qt::AlignCenter);
    m_pLabelNull = new QLabel(this);

    m_pLayout->addWidget(m_pLabelIcon, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pLabelNull, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pLabelText, 0, Qt::AlignCenter);
    m_pLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    m_pLayout->addWidget(m_pLabelArrow);
}

void CustomPushButton_1::onBtnToggled(bool checked)
{
    if (checked && !m_pIconCheckedPixmap.isNull())
        m_pLabelIcon->setPixmap(m_pIconCheckedPixmap);
    else
        m_pLabelIcon->setPixmap(m_pIconPixmap);

    if (this->isChecked() && !m_pArrowCheckedPixmap.isNull())
        m_pLabelArrow->setPixmap(m_pArrowCheckedPixmap);
    else if (!m_pArrowPixmap.isNull())
        m_pLabelArrow->setPixmap(m_pArrowPixmap);

    if (checked && m_pTextCheckedColor.isValid())
    {
        m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                    .arg(m_pTextCheckedColor.red()).arg(m_pTextCheckedColor.green())
                                    .arg(m_pTextCheckedColor.blue()).arg(m_pTextCheckedColor.alpha()));
    }else if (m_pTextColor.isValid()){
        m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                    .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                    .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
    }
}
