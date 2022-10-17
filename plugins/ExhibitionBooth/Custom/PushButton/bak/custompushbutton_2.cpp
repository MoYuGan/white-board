#include "custompushbutton_2.h"

CustomPushButton_2::CustomPushButton_2(QWidget *parent) :
    CustomPushButton(parent)
{
    this->initWidget();
    this->setStyleSheet("QPushButton{border: none;}");
    connect(this, &CustomPushButton_2::toggled, this, &CustomPushButton_2::onBtnToggled);
}

void CustomPushButton_2::mSetIcon(const QPixmap &pixmap, const QPixmap &checkedPixmap)
{
    m_pIconPixmap = pixmap;
    m_pIconCheckedPixmap = checkedPixmap;
    if (this->isChecked() && !m_pIconCheckedPixmap.isNull())
        m_pLabelIcon->setPixmap(m_pIconCheckedPixmap);
    else
        m_pLabelIcon->setPixmap(m_pIconPixmap);
}

void CustomPushButton_2::mSetText(const QString &text)
{
    m_pLabelText->setText(text);
}

void CustomPushButton_2::mSetColor(const QColor &textColor, const QColor &checkedTextColor)
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


void CustomPushButton_2::mSetBGColor(const QColor &BGColor, const QColor &hoverBGColor, const QColor &checkedBGColor)
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

void CustomPushButton_2::mSetSpacing(int spacing)
{
    m_pLabelNull->setFixedSize(1, spacing);
}

void CustomPushButton_2::mSetIconSize(int width, int height)
{
    m_pLabelIcon->setFixedSize(width, height);
}

void CustomPushButton_2::mSetFont(const QFont &font)
{
    m_pLabelText->setFont(font);
}

void CustomPushButton_2::initWidget()
{
    m_pLayout = new QVBoxLayout(this);
    m_pLayout->setContentsMargins(0, 0, 0, 0);
    m_pLayout->setSpacing(0);

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setScaledContents(true);
    m_pLabelText = new QLabel(this);
    m_pLabelText->setAlignment(Qt::AlignCenter);
    m_pLabelNull = new QLabel(this);
    m_pLabelNull->setFixedHeight(0);

    m_pLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    m_pLayout->setStretch(0, 1);
    m_pLayout->addWidget(m_pLabelIcon, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pLabelNull, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pLabelText, 0, Qt::AlignCenter);
    m_pLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    m_pLayout->setStretch(4, 1);
}

void CustomPushButton_2::onBtnToggled(bool checked)
{
    if (checked && !m_pIconCheckedPixmap.isNull())
        m_pLabelIcon->setPixmap(m_pIconCheckedPixmap);
    else
        m_pLabelIcon->setPixmap(m_pIconPixmap);

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
