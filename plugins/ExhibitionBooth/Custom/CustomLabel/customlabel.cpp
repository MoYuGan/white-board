#include "customlabel.h"
#include <QtDebug>

CustomLabel::CustomLabel(QWidget *parent) : QLabel(parent)
{
    m_pPixmap = QPixmap();
    this->installEventFilter(this);
}

void CustomLabel::mSetPixmap(const QPixmap &pixmap, int angle)
{
    m_RotateAngle = angle;
    m_pPixmap = pixmap;
    m_pTipPixmap = QPixmap();
    update();
}

void CustomLabel::mSetTipPixmap(const QPixmap &pixmap)
{
    m_RotateAngle = 0;
    m_pTipPixmap = pixmap;
    m_pPixmap = QPixmap();
    update();
}

QPixmap CustomLabel::getPixmap()
{
    return m_pPixmap;
}

void CustomLabel::moveRect(const QPoint &subPt)
{
    m_pDisplayRect.translate(subPt.x(), subPt.y());
    update();
}

void CustomLabel::setRotateAngle(int angle)
{
    m_RotateAngle = angle;
    update();
}

int CustomLabel::getRotateAngle()
{
    return m_RotateAngle;
}

void CustomLabel::zoomIn()
{
    if (m_ZoomNum < e_MaxZoomInNum)
        m_ZoomNum++;
}

void CustomLabel::zoomOut()
{
    if (m_ZoomNum > e_MaxZoomOutNum)
        m_ZoomNum--;
}

bool CustomLabel::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *> (event);
        if (mouseEvent->button() == Qt::LeftButton && !m_pPixmap.isNull()) {
            m_MousePressed = true;
            m_LastMousePoint = mouseEvent->pos();
        }
    }else if (event->type() == QEvent::MouseMove) {
        if (m_MousePressed) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *> (event);
            QPoint pos = mouseEvent->pos();
            m_pDisplayRect.translate(pos.x() - m_LastMousePoint.x(), pos.y() - m_LastMousePoint.y());
            m_LastMousePoint = pos;
        }
    }else if (event->type() == QEvent::MouseButtonRelease ||
              event->type() == QEvent::TouchEnd) {
        m_MousePressed = false;
    }
    return QLabel::eventFilter(watched, event);
}

void CustomLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if (!m_pDisplayRect.isValid())
        m_pDisplayRect = this->rect();
    if (!m_pPixmap.isNull()) {
        QPixmap pixmap;
        QTransform transform;
        transform.rotate(m_RotateAngle, Qt::ZAxis);
        /* 旋转 */
        QPointF center = m_pDisplayRect.center();
        QPointF tCenter = transform.map(center);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
        QRect rect = transform.mapRect(m_pDisplayRect);
        QMatrix matrix;
        matrix.rotate(m_RotateAngle);
        pixmap = m_pPixmap.transformed(matrix, Qt::SmoothTransformation);
        /* 缩放 */
        center = rect.center();
        transform.scale(1 + e_ZoomFactor * m_ZoomNum, 1 + e_ZoomFactor * m_ZoomNum);
        rect = transform.mapRect(rect);
        rect.moveCenter(center.toPoint());
        painter.drawPixmap(rect, pixmap);
    }else if (!m_pTipPixmap.isNull()){
        painter.drawPixmap(this->rect(), m_pTipPixmap);
    }else {
        painter.fillRect(this->rect(), Qt::transparent);
    }
}
