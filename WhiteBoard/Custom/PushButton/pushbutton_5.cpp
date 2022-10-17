#include "pushbutton_5.h"


PushButton_5::PushButton_5(QWidget *parent) :
    PushButton_Basic(parent)
{
    this->setStyleSheet("QPushButton{border: none;}");
    m_pHoverColor = Qt::transparent;
    m_pBackgroundColor = Qt::white;
    m_pCheckedTextColor = Qt::white;
    m_pTextColor = QColor(68, 68, 68);
    m_pCheckedBGColor = QColor(20, 134, 250);
    m_pMouseEnter = false;
    m_pTopLeftRadius = 0;
    m_pTopRightRadius = 0;
    m_pBottomLeftRadius = 0;
    m_pBottomRightRadius = 0;
    this->initWidget();
    this->installEventFilter(this);

    connect(this, &PushButton_5::toggled, [=](){
        if (this->isChecked()) {
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
    });
}

void PushButton_5::mSetCheckedTextColor(const QColor &color)
{
    m_pCheckedTextColor = color;
    if (this->isChecked())
        m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                    .arg(m_pCheckedTextColor.red()).arg(m_pCheckedTextColor.green())
                                    .arg(m_pCheckedTextColor.blue()).arg(m_pCheckedTextColor.alpha()));
}

void PushButton_5::mSetCheckedIcon(const QPixmap &pixmap)
{
    m_pCheckedIcon = pixmap;
    if (this->isChecked())
        m_pLabelIcon->setPixmap(pixmap);
    update();
}

void PushButton_5::mSetIcon(const QPixmap &pixmap)
{
    m_pIcon = pixmap;
    if (!this->isChecked())
        m_pLabelIcon->setPixmap(pixmap);
}

void PushButton_5::mSetIconSize(const QSize &size)
{
    m_pLabelIcon->setFixedSize(size);
}

void PushButton_5::mSetText(const QString &str)
{
    m_pLabelText->setText(str);
}

void PushButton_5::mSetMargins(int left, int top, int right, int bottom)
{
    m_pLayout->setContentsMargins(left, top, right, bottom);
}

void PushButton_5::mSetSpacing(int spacing)
{
    m_pLabelSpacing->setFixedWidth(spacing);
}

void PushButton_5::mSetFont(const QFont &font)
{
    m_pLabelText->setFont(font);
}

void PushButton_5::mSetHoverColor(const QColor &color)
{
    m_pHoverColor = color;
}

void PushButton_5::mSetBackgroundColor(const QColor &color)
{
    m_pBackgroundColor = color;
}

void PushButton_5::mSetEnabled(bool bo)
{
    if (bo) {
        m_pLabelText->setStyleSheet("QLabel{color: rgb(68, 68, 68);}");
    }else {
        m_pLabelText->setStyleSheet("QLabel{color: rgb(170,170,170);}");
    }
    this->setEnabled(bo);
}

void PushButton_5::mSetRadius(int topleft, int topright, int bottomleft, int bottomright)
{
    m_pTopLeftRadius = topleft;
    m_pTopRightRadius = topright;
    m_pBottomLeftRadius = bottomleft;
    m_pBottomRightRadius = bottomright;
    this->setStyleSheet(QString("QPushButton{border-top-left-radius: %1px;"
                                "border-top-right-radius: %2px;"
                                "border-bottom-left-radius: %3px;"
                                "border-bottom-right-radius: %4px;}").arg(topleft)
                        .arg(topright).arg(bottomleft).arg(bottomright));
}

bool PushButton_5::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        m_pMouseEnter = true;
        update();
    }else if (event->type() == QEvent::Leave) {
        m_pMouseEnter = false;
        update();
    }
    return PushButton_Basic::eventFilter(watched, event);
}

void PushButton_5::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path = Public_Function::getRoundRectPath(this->rect(), m_pTopLeftRadius, m_pTopRightRadius,
                                      m_pBottomLeftRadius, m_pBottomRightRadius);

    if (this->m_pCheckedBGColor.isValid() && this->isChecked()) {
        painter.fillPath(path, QBrush(m_pCheckedBGColor));
    }else if (m_pMouseEnter && m_pLabelText->isEnabled()) {
        painter.fillPath(path, QBrush(m_pHoverColor));
    }else {
        painter.fillPath(path, QBrush(m_pBackgroundColor));
    }
}

void PushButton_5::initWidget()
{
    m_pLayout = new QHBoxLayout(this);
    m_pLayout->setContentsMargins(0, 0, 0, 0);
    m_pLayout->setSpacing(0);

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setScaledContents(true);
    m_pLabelText = new QLabel(this);
    m_pLabelText->setStyleSheet("QLabel{color: rgb(68, 68, 68);}"
                                "QLabel::unabled{ color: rgb(170,170,170);}");
    m_pLabelSpacing = new QLabel(this);

    m_pLayout->addWidget(m_pLabelIcon, 0, Qt::AlignCenter);
    m_pLayout->addWidget(m_pLabelSpacing);
    m_pLayout->addWidget(m_pLabelText, 0, Qt::AlignCenter);
    m_pLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
}
