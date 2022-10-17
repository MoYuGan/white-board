#include "custompushbutton_3.h"
#include <math.h>
#include <QtDebug>

CustomPushButton_3::CustomPushButton_3(QWidget *parent) :
    QPushButton(parent)
{
    this->initWidget();
    this->installEventFilter(this);
    this->setStyleSheet("QPushButton{border: none;}");
    connect(this, &CustomPushButton_3::toggled, this, &CustomPushButton_3::onToggled);
    //this->setAttribute(Qt::WA_AcceptTouchEvents, true);
}

void CustomPushButton_3::registGestureType()
{

    this->grabGesture(Qt::PinchGesture);
    this->grabGesture(Qt::TapGesture);
    this->grabGesture(Qt::TapAndHoldGesture);
}

void CustomPushButton_3::mSetPixmap(const QPixmap &pixmap)
{
    if (!this->isCheckable())
        this->setCheckable(true);
    m_pPixmap = pixmap;
    this->update();
}

void CustomPushButton_3::toClearDisplay()
{
    this->setCheckable(false);
    m_pPixmap = QPixmap();
    this->update();
}

bool CustomPushButton_3::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QMouseEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        m_pMousePressedPoint = mouseEvent->localPos();
        if (mouseEvent->button() == Qt::LeftButton) {
            this->setChecked(true);
            update();
            return true;
        }
    }else if (event->type() == QMouseEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF currentPoint = mouseEvent->localPos();
        m_pPixmapRect.translate(QPoint(currentPoint.x() - m_pMousePressedPoint.x(),
                                       currentPoint.y() - m_pMousePressedPoint.y()));
        m_pMousePressedPoint = currentPoint;
    }
//    else if (event->type() == QMouseEvent::MouseButtonRelease) {

//    }else if(event->type() == QTouchEvent::TouchBegin ||
//             event->type() == QTouchEvent::TouchEnd) {
//        return true;
//    }else if (event->type() == QTouchEvent::TouchUpdate) {
//        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
//        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
//        if (touchPoints.count() == 1) {
//            QPointF p1 = touchPoints.at(0).lastPos();
//            QPointF p2 = touchPoints.at(0).pos();
//            m_pPixmapRect.translate(QPoint(p2.x() - p1.x(),
//                                           p2.y() - p1.y()));
//        }else if (touchPoints.count() == 2) {
//            //判断两点也就是双指缩放动作
//            QPointF p1 = touchPoints.at(0).startPos();
//            QPointF p2 = touchPoints.at(0).lastPos();
//            QPointF p3 = touchPoints.at(1).startPos();
//            QPointF p4 = touchPoints.at(1).lastPos();
//            QLineF line1 = QLineF(p1, p2);
//            QLineF line2 = QLineF(p3, p4);
//            QPointF iPoint;
//            line1.intersect(line2, &iPoint);
//            if (!iPoint.isNull()) {
//                qreal angle = this->getAngle(iPoint, p2, p4);
//                qDebug()<<"angle:"<<angle;
//            }

//        }
//        return true;
//    }
    else if (event->type() == QEvent::Gesture) {
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    return QPushButton::eventFilter(watched, event);
}

void CustomPushButton_3::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::black);

    if (!m_pPixmap.isNull())
        painter.drawPixmap(m_pPixmapRect, m_pPixmap.scaled(m_pPixmapRect.size()));
    else {
        painter.setFont(PublicFunction::getFont(38));
        painter.setPen(QPen(QBrush(QColor(102, 102, 102)), PublicFunction::getScaleWidth(2)));
        painter.drawText(this->rect(), Qt::AlignCenter, tr("等待画面展示..."));
    }
    if (this->isChecked()) {
        painter.setPen(QPen(QBrush(Qt::red), PublicFunction::getScaleWidth(8)));
        painter.drawRect(this->rect());
    }
}

void CustomPushButton_3::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);
    m_pPixmapRect = this->rect();
    this->resize();
}

bool CustomPushButton_3::gestureEvent(QGestureEvent *event)
{
    if (QGesture *tap = event->gesture(Qt::TapGesture))
        qDebug()<<"TapGesture---1";
        //tapTriggered(static_cast<QTapGesture *>(tap));

    else if (QGesture *tapAndHold = event->gesture(Qt::TapAndHoldGesture))
        qDebug()<<"TapAndHoldGesture---1";
        //tapAndHoldTriggered(static_cast<QTapAndHoldGesture *>(tapAndHold));

    else if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        qDebug()<<"PinchGesture---1";
        //pinchTriggered(static_cast<QPinchGesture *>(pinch));

    return true;
}

void CustomPushButton_3::onToggled(bool checked)
{
    if (checked) {
        m_pBtnScale->show();
        m_pBtnClose->show();
    }else {
        m_pBtnScale->hide();
        m_pBtnClose->hide();
    }
}

void CustomPushButton_3::onScaleBtnClicked()
{
    m_pShowFullScreen = !m_pShowFullScreen;
    emit toScale(m_pShowFullScreen);
}

void CustomPushButton_3::onCloseBtnClicked()
{
    emit toClosed();
}

void CustomPushButton_3::initWidget()
{
    m_pBtnScale = new CustomPushButton(this);
    m_pBtnScale->hide();
    connect(m_pBtnScale, &CustomPushButton::clicked, this, &CustomPushButton_3::onScaleBtnClicked);
    m_pBtnClose = new CustomPushButton(this);
    m_pBtnClose->setStyleSheet("QPushButton{border-image: url(':/images/guanbi.png');}");
    m_pBtnClose->hide();
    connect(m_pBtnClose, &CustomPushButton::clicked, this, &CustomPushButton_3::onCloseBtnClicked);
}

void CustomPushButton_3::resize()
{
    QSize size = PublicFunction::getScaleSize(56, 56);
    m_pBtnScale->setFixedSize(size);
    m_pBtnClose->setFixedSize(size);

    if (m_pShowFullScreen) {
        m_pBtnClose->hide();
        m_pBtnScale->setStyleSheet("QPushButton{ border-image: url(':/images/shouqi.png');}");
        m_pBtnScale->move(QPoint(PublicFunction::getScaleWidth(40), this->height() -
                                 m_pBtnScale->height() - PublicFunction::getScaleWidth(80)));
    }else {
        m_pBtnScale->setStyleSheet("QPushButton{ border-image: url(':/images/quanping.png');}");
        m_pBtnScale->move(QPoint(PublicFunction::getScaleWidth(10), this->height() - m_pBtnScale->height() - PublicFunction::getScaleWidth(10)));
        m_pBtnClose->move(QPoint(m_pBtnScale->x() + m_pBtnScale->width(), m_pBtnScale->y()));
    }

}

qreal CustomPushButton_3::getAngle(QPointF center, QPointF firstPoint, QPointF secondPoint)
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
