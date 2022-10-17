#include "custompushbutton_2.h"

CustomPushButton_2::CustomPushButton_2(const QPixmap &pixmap, int pageIndex, QWidget *parent) :
    m_pPixmap(pixmap),
    m_pPageIndex(pageIndex),
    QPushButton(parent)
{
    this->installEventFilter(this);
    this->setMouseTracking(true);
}

void CustomPushButton_2::mSetPixmap(const QPixmap &pixmap)
{
    m_pPixmap = pixmap;
    update();
}

void CustomPushButton_2::mSetIndex(int index)
{
    m_pPageIndex = index;
    update();
}

void CustomPushButton_2::setContrastModel(bool bo)
{
    m_pContrastModel = bo;
    update();
}

bool CustomPushButton_2::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if ((m_pContrastModel && m_pCheckedRect.contains(mouseEvent->pos()) ||
             (!m_pContrastModel && m_pDelectRect.contains(mouseEvent->pos()))))
            this->setCursor(Qt::PointingHandCursor);
        else
            this->setCursor(Qt::ArrowCursor);
    }if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton &&
                m_pDelectRect.contains(mouseEvent->pos()) && !m_pContrastModel) {
            emit this->deleteSignal();
            return true;
        }
    }
    return QPushButton::eventFilter(watched, event);
}

void CustomPushButton_2::mGetPixmap(QPixmap *pixmap)
{
    *pixmap = m_pPixmap;
}

void CustomPushButton_2::setRotateAngle(int angle)
{
    m_RotateAngle = angle;
    update();
}

int CustomPushButton_2::getRotateAngle()
{
    return m_RotateAngle;
}

QPixmap CustomPushButton_2::mGetPixmap()
{
    return m_pPixmap;
}

void CustomPushButton_2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    int radius = PublicFunction::getScaleSize(5);
    int border = PublicFunction::getScaleSize(3);
    int margin = PublicFunction::getScaleSize(3);
    QRect pixmapRect;

    painter.fillPath(PublicFunction::getRoundRectPath(this->rect(), radius), QBrush(QColor(20, 20, 22)));
    if (this->isChecked()) {
        pixmapRect = QRect(border + margin, border + margin, this->width() - border*2 - margin*2, this->height() - border*2 - margin*2);
    }else {
        pixmapRect = this->rect();
    }

    int height = PublicFunction::getScaleSize(35);
    QRect bottomRect = QRect(0, this->height() - height,
                             this->width(), height);

    QTransform transform;
    transform.rotate(m_RotateAngle, Qt::ZAxis);
    /* 设置旋转中心 */
    QPointF center = pixmapRect.center();
    QPointF tCenter = transform.map(center);
    transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        center.x() - tCenter.x(), center.y() - tCenter.y(), transform.m33());
    QRect rect = transform.mapRect(pixmapRect);
    QMatrix matrix;
    matrix.rotate(m_RotateAngle);
    painter.drawPixmap(rect, m_pPixmap.transformed(matrix, Qt::SmoothTransformation));
    QPainterPath path = PublicFunction::getRoundRectPath(bottomRect, 0, 0, radius, radius);
    painter.fillPath(path, QBrush(QColor(0, 0, 0, 125)));

    QRectF borderRect;
    if (this->isChecked()) {
        borderRect = QRectF(border/2.0, border/2.0, this->width() - border, this->height() - border);
        painter.setPen(QPen(QBrush(QColor(20,134,250)), border));
        painter.setBrush(QBrush());
        painter.drawPath(PublicFunction::getRoundRectPath(borderRect, radius));
    }

    QSize size;
    QRect textRect;
    if (m_pContrastModel) {
        size = PublicFunction::getScaleSize(QSize(20, 20));
        m_pCheckedRect = QRect(bottomRect.x() + PublicFunction::getScaleSize(10),
                               bottomRect.y() + (bottomRect.height() - size.height())/2, size.width(), size.height());
        textRect = QRect(m_pCheckedRect.x() + m_pCheckedRect.width() + PublicFunction::getScaleSize(10),
                         bottomRect.y(), bottomRect.width(), bottomRect.height());
        if (this->isChecked())
            painter.drawPixmap(m_pCheckedRect, QPixmap(":/images/xuanxiang2@2x.png"));
        else
            painter.drawPixmap(m_pCheckedRect, QPixmap(":/images/xuanxiang1@2x.png"));
    }else {
        size = PublicFunction::getScaleSize(QSize(17, 17));
        m_pDelectRect = QRect(bottomRect.x() + bottomRect.width() - PublicFunction::getScaleSize(10) - size.width(),
                                 bottomRect.y() + (bottomRect.height() - size.height())/2, size.width(), size.height());
        textRect = QRect(bottomRect.x() + PublicFunction::getScaleSize(10),
                         bottomRect.y(), bottomRect.width(), bottomRect.height());
        painter.drawPixmap(m_pDelectRect, QPixmap(":/images/shanchu@2x.png"));
    }

    painter.setFont(PublicFunction::getFont(11));
    painter.setPen(QPen(QColor(255, 255, 255)));
    QString text;
    if (this->isChecked() && !m_pContrastModel)
        text = QString("%1（再次点击返回摄像头）").arg(QString::number(m_pPageIndex + 1));
    else
        text = QString("%1").arg(QString::number(m_pPageIndex + 1));

    painter.drawText(textRect, text, QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
}

