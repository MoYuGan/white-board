#include "customslider_1.h"

CustomSlider_1::CustomSlider_1(QWidget *parent) : QWidget(parent)
{
    m_pRadius = 0;
    m_pMousePressed = false;
    this->initWidget();
    this->installEventFilter(this);
}

void CustomSlider_1::mSetText(const QString &text)
{
    m_pText = text;
    update();
}

void CustomSlider_1::mSetFont(const QFont &font)
{
    m_pFont = font;
}

void CustomSlider_1::mSetMargin(int left, int right)
{
    m_pLeftMargin = left;
    m_pRightMargin = right;
    this->mSetHandleSize(m_pHandle->size());
}

void CustomSlider_1::mSetHandleIcon(const QPixmap &pixmap)
{
    m_pHandle->setPixmap(pixmap);
}

void CustomSlider_1::mSetHandleSize(const QSize &size)
{
    m_pHandle->setFixedSize(size);
    m_pHandle->move(QPoint(m_pLeftMargin, (this->height() - m_pHandle->height())/2));
}

void CustomSlider_1::mSetRadius(int radius)
{
    m_pRadius = radius;
}

bool CustomSlider_1::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress &&
            watched == this) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        m_pMousePressedPoint = mouseEvent->pos();
        if (mouseEvent->button() == Qt::LeftButton &&
                m_pHandle->rect().contains(m_pMousePressedPoint)) {
            m_pMousePressed = true;
        }
    }else if (event->type() == QEvent::MouseButtonRelease &&
              watched == this) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            if (m_pMousePressed) {
                m_pMousePressed = false;
                int maxX = this->width() - m_pHandle->width() - m_pRightMargin;
                if (m_pHandle->x() == maxX) {
                    emit clearSignal();
                }
                m_pHandle->move(QPoint(m_pLeftMargin, (this->height() - m_pHandle->height())/2));
                update();
            }
        }
    }else if (event->type() == QEvent::MouseMove &&
              watched == this) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (m_pMousePressed) {
            QPoint curPos = mouseEvent->pos();
            int subX = curPos.x() - m_pMousePressedPoint.x();
            int x = m_pLeftMargin + subX;
            int maxX = this->width() - m_pHandle->width() - m_pRightMargin;
            x = x < m_pLeftMargin ? m_pLeftMargin :
                    (x < maxX ? x : maxX);
            m_pHandle->move(QPoint(x, m_pHandle->y()));
            update();
        }

    }else if (event->type() == QEvent::Enter &&
              watched == m_pHandle) {
        this->setCursor(Qt::PointingHandCursor);
    }else if (event->type() == QEvent::Leave &&
              watched == m_pHandle) {
        this->setCursor(Qt::ArrowCursor);
    }
    return QWidget::eventFilter(watched, event);
}

void CustomSlider_1::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QBrush(QColor(224, 224, 224)), PublicFunction::getScaleSize(1)));
    painter.setBrush(QBrush(QColor(238,238,238)));
    painter.drawRoundedRect(this->rect(), m_pRadius, m_pRadius);
    if (!m_pText.isEmpty()) {
        painter.setFont(m_pFont);
        painter.setPen(QPen(QColor(136, 136, 136)));
        painter.drawText(QRect(m_pLeftMargin, 0, this->width() - m_pLeftMargin - m_pRightMargin - PublicFunction::getScaleSize(16),
                               this->height()), m_pText, QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    }
    painter.fillRect(QRect(m_pLeftMargin, m_pHandle->y(), m_pHandle->x() - m_pLeftMargin + m_pHandle->width(), m_pHandle->height()),
                     QBrush(QColor(201, 201, 201)));
}

void CustomSlider_1::initWidget()
{
    m_pHandle = new QLabel(this);
    m_pHandle->installEventFilter(this);
    m_pHandle->setScaledContents(true);
}
