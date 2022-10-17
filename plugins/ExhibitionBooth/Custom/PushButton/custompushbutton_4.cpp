#include "custompushbutton_4.h"
#include <math.h>
#include <QtDebug>

#define PROPERTY_USE_CAMERA  "USE_CAMERA"

CustomPushButton_4::CustomPushButton_4(QWidget *parent) :
    QPushButton(parent)
{
    this->initWidget();
    this->installEventFilter(this);
    this->setStyleSheet("QPushButton{border: none;}");
    connect(this, &CustomPushButton_4::toggled, this, &CustomPushButton_4::onToggled);
    //this->setAttribute(Qt::WA_AcceptTouchEvents, true);
}

void CustomPushButton_4::mSetPixmap(const QPixmap &pixmap, int angle)
{
    this->setCheckable(true);
    m_pPixmap = pixmap;
    m_RotateAngle = angle;
    m_pTipPixmap = QPixmap();
    update();
}

void CustomPushButton_4::mSetTipPixmap(const QPixmap &pixmap)
{
    this->setCheckable(false);
    m_pTipPixmap = pixmap;
    m_pPixmap = QPixmap();
    this->update();
}

bool CustomPushButton_4::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QMouseEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        m_pMousePressedPoint = mouseEvent->localPos();
        if (mouseEvent->button() == Qt::LeftButton) {
            this->setChecked(true);
            m_MousePressed = true;
            return true;
        }
    }else if (event->type() == QMouseEvent::MouseMove) {
        if (m_MousePressed) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF currentPoint = mouseEvent->localPos();
            m_pPixmapRect.translate(QPoint(currentPoint.x() - m_pMousePressedPoint.x(),
                                           currentPoint.y() - m_pMousePressedPoint.y()));
            m_pMousePressedPoint = currentPoint;
            update();
        }
    }else if (event->type() == QEvent::MouseButtonRelease ||
              event->type() == QEvent::TouchEnd) {
        m_MousePressed = false;
    }
    return QPushButton::eventFilter(watched, event);
}

void CustomPushButton_4::setRotateAngle(int angle)
{
    m_RotateAngle = angle;
    update();
}

int CustomPushButton_4::getRotateAngle()
{
    return m_RotateAngle;
}

void CustomPushButton_4::zoomIn()
{
    if (m_ZoomNum < e_MaxZoomInNum)
        m_ZoomNum++;
    update();
}

void CustomPushButton_4::zoomOut()
{
    if (m_ZoomNum > e_MaxZoomOutNum)
        m_ZoomNum--;
    update();
}

void CustomPushButton_4::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.fillRect(this->rect(), Qt::black);
    if (!m_pPixmapRect.isValid())
        m_pPixmapRect = this->rect();

    if (!m_pPixmap.isNull()) {
        QPixmap pixmap;
        QTransform transform;
        QRect rect;
        QPointF center = m_pPixmapRect.center();
        /* 缩放 */
        transform.scale(1 + e_ZoomFactor * m_ZoomNum, 1 + e_ZoomFactor * m_ZoomNum);
        rect = transform.mapRect(m_pPixmapRect);
        rect.moveCenter(center.toPoint());
        /* 旋转 */
        transform.rotate(m_RotateAngle, Qt::ZAxis);
        QPointF tCenter = transform.map(center);
        transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                            transform.m21(), transform.m22(), transform.m23(),
                            center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
        rect = transform.mapRect(rect);
        QMatrix matrix;
        matrix.rotate(m_RotateAngle);
        pixmap = m_pPixmap.transformed(matrix, Qt::SmoothTransformation);
        painter.drawPixmap(rect, pixmap);
    }else if (!m_pTipPixmap.isNull()){
        painter.drawPixmap(this->rect(), m_pTipPixmap);
    }

    if (this->property(PROPERTY_USE_CAMERA).toString().compare("true") == 0) {
        QRect rect = QRect(PublicFunction::getScaleSize(20), PublicFunction::getScaleSize(20),
                           PublicFunction::getScaleSize(68), PublicFunction::getScaleSize(82));
        painter.drawPixmap(rect, QPixmap("://images/kongtai@2x.png"));
    }
    if (this->isChecked()) {
        painter.setPen(QPen(QBrush(Qt::red), PublicFunction::getScaleSize(8)));
        painter.drawRect(this->rect());
    }
}

void CustomPushButton_4::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);
   // m_pPixmapRect = this->rect();
    this->resize();
}

void CustomPushButton_4::onToggled(bool checked)
{
    if (checked) {
        m_pBtnScale->show();
        m_pBtnClose->show();
    }else {
        m_pBtnScale->hide();
        m_pBtnClose->hide();
    }
}

void CustomPushButton_4::onScaleBtnClicked()
{
    m_pShowFullScreen = !m_pShowFullScreen;
    emit toScale(m_pShowFullScreen);
}

void CustomPushButton_4::onCloseBtnClicked()
{
    emit toClosed();
}

void CustomPushButton_4::initWidget()
{
    m_pBtnScale = new CustomPushButton(this);
    m_pBtnScale->hide();
    connect(m_pBtnScale, &CustomPushButton::clicked, this, &CustomPushButton_4::onScaleBtnClicked);
    m_pBtnClose = new CustomPushButton(this);
    m_pBtnClose->setStyleSheet("QPushButton{border-image: url(':/images/guanbi.png');}");
    m_pBtnClose->hide();
    connect(m_pBtnClose, &CustomPushButton::clicked, this, &CustomPushButton_4::onCloseBtnClicked);
}

void CustomPushButton_4::resize()
{
    QSize size = PublicFunction::getScaleSize(56, 56);
    m_pBtnScale->setFixedSize(size);
    m_pBtnClose->setFixedSize(size);

    if (m_pShowFullScreen) {
        m_pBtnClose->hide();
        m_pBtnScale->setStyleSheet("QPushButton{ border-image: url(':/images/shouqi.png');}");
        m_pBtnScale->move(QPoint(PublicFunction::getScaleSize(40), this->height() -
                                 m_pBtnScale->height() - PublicFunction::getScaleSize(80)));
    }else {
        m_pBtnScale->setStyleSheet("QPushButton{ border-image: url(':/images/quanping.png');}");
        m_pBtnScale->move(QPoint(PublicFunction::getScaleSize(10), this->height() - m_pBtnScale->height() - PublicFunction::getScaleSize(10)));
        m_pBtnClose->move(QPoint(m_pBtnScale->x() + m_pBtnScale->width(), m_pBtnScale->y()));
    }

}

qreal CustomPushButton_4::getAngle(QPointF center, QPointF firstPoint, QPointF secondPoint)
{
    if(secondPoint == firstPoint)
        return 0;
    qreal ma_x = firstPoint.x() - center.x();
    qreal ma_y = firstPoint.y() - center.y();
    qreal mb_x = secondPoint.x() - center.x();
    qreal mb_y = secondPoint.y() - center.y();
    qreal v1 = (ma_x * mb_x) + (ma_y * mb_y);
    qreal ma_val = sqrt(ma_x * ma_x + ma_y * ma_y);
    qreal mb_val = sqrt(mb_x * mb_x + mb_y * mb_y);
    qreal cosm = v1 / (ma_val * mb_val);
    qreal angle = acos(cosm) * 180 / M_PI;
    if ((secondPoint.x() -firstPoint.x()) * (center.y() - firstPoint.y()) -
            (secondPoint.y() -firstPoint.y()) * (center.x() -firstPoint.x()) < 0) {
        angle = -angle;
    }
    return angle;
}
