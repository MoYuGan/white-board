#include "pushbutton_6.h"

PushButton_6::PushButton_6(const QPixmap &pixmap, int pageIndex, QWidget *parent) :
    QPushButton(parent),
    m_pPixmap(pixmap),
    m_pPageIndex(pageIndex)
{
    //this->initWidget();
    this->installEventFilter(this);
    this->setMouseTracking(true);
}

void PushButton_6::mSetPixmap(const QPixmap &pixmap)
{
    m_pPixmap = pixmap;
    update();
}

void PushButton_6::mSetIndex(int index)
{
    m_pPageIndex = index;
    update();
}

bool PushButton_6::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (m_pDelectRect.contains(mouseEvent->pos()))
            this->setCursor(Qt::PointingHandCursor);
        else
            this->setCursor(Qt::ArrowCursor);
    }if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton &&
                m_pDelectRect.contains(mouseEvent->pos())) {
            emit this->deleteItem();
            return true;
        }
    }
    return QPushButton::eventFilter(watched, event);
}

void PushButton_6::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int radius = Public_Function::getScaleSize(5);
    int border = Public_Function::getScaleSize(3);
    int margin = Public_Function::getScaleSize(6);
    QRect pixmapRect;

    if (this->isChecked()) {
        QRectF borderRect = QRectF(border/2.0, border/2.0, this->width() - border - border, this->height() - border);
        painter.setPen(QPen(QBrush(QColor(20,134,250)), border));
        painter.setBrush(QBrush());
        painter.drawRoundedRect(borderRect, radius, radius);
        pixmapRect = QRect(margin, margin, this->width() - margin*2 - border, this->height() - margin*2);
    }else {
        pixmapRect = this->rect();
    }

    int height = Public_Function::getScaleSize(35);
    QRect bottomRect = QRect(pixmapRect.x(), pixmapRect.y() + pixmapRect.height() - height,
                             pixmapRect.width(), height);
    painter.drawPixmap(pixmapRect, m_pPixmap.scaled(pixmapRect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter.fillRect(bottomRect, QBrush(QColor(0, 0, 0, 125)));

    margin = Public_Function::getScaleSize(10);
    QRect textRect = QRect(bottomRect.x() + margin, bottomRect.y(), Public_Function::getScaleSize(50), bottomRect.height());
    painter.setFont(Public_Function::getFont(11));
    painter.setPen(QPen(QColor(255, 255, 255)));
    painter.drawText(textRect, QString::number(m_pPageIndex + 1), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    QSize size = Public_Function::getScaleSize(QSize(17, 17));
    m_pDelectRect = QRect(bottomRect.x() + bottomRect.width() - margin - size.width(),
                             bottomRect.y() + (bottomRect.height() - size.height())/2, size.width(), size.height());
    painter.drawPixmap(m_pDelectRect, QPixmap(":/images/shanchu@2x.png"));
}

void PushButton_6::initWidget()
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);

    m_View = new QGraphicsView(this);
    hLayout->addWidget(m_View);
}
