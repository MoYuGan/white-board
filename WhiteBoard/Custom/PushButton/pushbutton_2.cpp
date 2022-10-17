#include "pushbutton_2.h"
#include <QDebug>
PushButton_2::PushButton_2(QWidget *parent) :
    PushButton_Basic(parent)
{
    this->setAutoFillBackground(true);
    this->installEventFilter(this);
    m_pMouseEnter = false;
    m_pRadius = Public_Function::getScaleSize(10);
    m_pTextColor = QColor(102, 102, 102);
    m_pCheckedTextColor = QColor(20, 134, 250);
    m_pHoverColor = QColor(238, 238, 238);
    m_pCheckedBorderColor = QColor();
    this->initWidget();

    connect(this, &PushButton_2::toggled, this, &PushButton_2::onToggled);
}

void PushButton_2::mSetIcon(const QPixmap &pixmap)
{
    m_pIcon = pixmap;
    m_pLabelIcon->setPixmap(pixmap);
}

void PushButton_2::mSetIconSize(const QSize &size)
{
    m_pLabelIcon->setFixedSize(size);
}

void PushButton_2::mSetCheckedTextColor(const QColor &color)
{
    m_pCheckedTextColor = color;
    if (this->isChecked())
        m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                    .arg(m_pCheckedTextColor.red()).arg(m_pCheckedTextColor.green())
                                    .arg(m_pCheckedTextColor.blue()).arg(m_pCheckedTextColor.alpha()));
}

void PushButton_2::mSetText(const QString &str)
{
    m_pLabelText->setText(str);
}

void PushButton_2::mSetTextColor(const QColor &color)
{
    m_pTextColor = color;
    m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
}

void PushButton_2::mSetFont(const QFont &font)
{
    m_pLabelText->setFont(font);
}

void PushButton_2::mSetCheckedIcon(const QPixmap &pixmap)
{
    m_pCheckedIcon = pixmap;
    if (this->isChecked())
        m_pLabelIcon->setPixmap(m_pCheckedIcon);
}

void PushButton_2::mSetCheckedBGColor(const QColor &color)
{
    m_pCheckedBGColor = color;
}

void PushButton_2::mSetRadius(int radius)
{
    m_pRadius = radius;
}

void PushButton_2::mSetCheckedBorderColor(const QColor &color)
{
    m_pCheckedBorderColor = color;
}

bool PushButton_2::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        m_pMouseEnter = true;
        update();
    }else if (event->type() == QEvent::Leave) {
        m_pMouseEnter = false;
        update();
    }else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (this->rect().contains(mouseEvent->pos()) &&
                mouseEvent->button() == Qt::LeftButton &&
                this->isChecked())
            emit checkedClicked();
    }
    return PushButton_Basic::eventFilter(watched, event);
}

//bool PushButton_2::event(QEvent *e)
//{

//}

void PushButton_2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::transparent);
    if (this->m_pCheckedBGColor.isValid() && this->isChecked()) {
        QPainterPath path = Public_Function::getRoundRectPath(this->rect(), m_pRadius);
        painter.setPen(QPen(QBrush(m_pCheckedBGColor), Public_Function::getScaleSize(3)));
        painter.setBrush(QBrush(m_pCheckedBGColor));
        painter.drawPath(path);
    }else
        painter.fillRect(this->rect(), QBrush(Qt::transparent));

    QPainterPath path;
    if (m_pCheckedBorderColor.isValid() && this->isChecked()) {
        path = Public_Function::getRoundRectPath(this->rect(), m_pRadius);
        painter.setPen(QPen(QBrush(m_pCheckedBorderColor), Public_Function::getScaleSize(3)));
        painter.setBrush(QBrush());
    }else if (m_pMouseEnter && !this->isChecked()) {
        path = Public_Function::getRoundRectPath(this->rect(), m_pRadius);
        painter.setPen(QPen(m_pHoverColor));
        painter.setBrush(m_pHoverColor);
    }
    painter.drawPath(path);
}

void PushButton_2::initWidget()
{
    m_pLayout = new QVBoxLayout(this);
    m_pLayout->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(4));
    m_pLayout->setSpacing(0);

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setScaledContents(true);
    m_pLayout->addWidget(m_pLabelIcon, 0, Qt::AlignCenter);

    m_pLabelText = new QLabel(this);
    m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
    m_pLabelText->setFont(Public_Function::getFont(14));
    m_pLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    m_pLayout->addWidget(m_pLabelText, 0, Qt::AlignCenter);
}

void PushButton_2::onToggled(bool checked)
{
    if (checked) {
        if (!m_pCheckedIcon.isNull()) {
            m_pLabelIcon->setPixmap(m_pCheckedIcon);
        }
        if (m_pCheckedTextColor.isValid()) {
            m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                        .arg(m_pCheckedTextColor.red()).arg(m_pCheckedTextColor.green())
                                        .arg(m_pCheckedTextColor.blue()).arg(m_pCheckedTextColor.alpha()));
        }
    }else {
        if (!m_pIcon.isNull()) {
            m_pLabelIcon->setPixmap(m_pIcon);
            m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                        .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                        .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
        }

    }
}
