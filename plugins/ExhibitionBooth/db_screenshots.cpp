#include "db_screenshots.h"
#include "ui_db_screenshots.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <math.h>
#include <QtDebug>

DB_ScreenShots::DB_ScreenShots(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DB_ScreenShots)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    this->setMouseTracking(true);
    this->initWidget();
    this->resize();

    m_pMousePressed = false;
    m_pDragRectMinSize = QSize(20, 20);
}

DB_ScreenShots::~DB_ScreenShots()
{
    delete ui;
}

void DB_ScreenShots::show()
{
    QWidget::show();
    this->raise();
    this->showToolWidget();
}

void DB_ScreenShots::resize()
{
    QSize size = DB_ApplicationScale::getScaleSize(QSize(38, 38));
    ui->pSave->setFixedSize(size);
    ui->pClose->setFixedSize(size);
    size = DB_ApplicationScale::getScaleSize(QSize(110, 60));
    ui->frame->setFixedSize(size);

    ui->frame->setStyleSheet(QString("#%1{border-radius: %2px;"
                                     "background: white;}").arg(ui->frame->objectName())
                             .arg(DB_ApplicationScale::getScaleWidth(5)));
}

bool DB_ScreenShots::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            m_pMousePressed = true;
            if (this->cursor().shape() == Qt::SizeAllCursor) {
                m_pPressedPoint = QPointF(mouseEvent->localPos().x() - m_pDragRect.x(),
                                          mouseEvent->localPos().y() - m_pDragRect.y());
            }else {
                m_pPressedPoint = mouseEvent->localPos();
            }

            if (!ui->frame->isHidden())
                ui->frame->hide();
        }
    }else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            m_pMousePressed = false;
            if (ui->frame->isHidden())
                this->showToolWidget();

        }
    }else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (m_pMousePressed) {
            QPointF globalPos = mouseEvent->screenPos();
            if (this->cursor().shape() == Qt::SizeAllCursor) {  // 移动
                int x = globalPos.x() - m_pPressedPoint.x();
                int y = globalPos.y() - m_pPressedPoint.y();
                int width = m_pDragRect.width();
                int height = m_pDragRect.height();
                x = x > 0 ? (x + width < this->width()? x : this->width() - width) :
                            0;
                y = y > 0 ? (y + height < this->height()? y : this->height() - height) :
                            0;
                m_pDragRect.moveTo(x, y);
                m_pUpCenterPoint = QPointF(m_pDragRect.center().x(), m_pDragRect.topLeft().y());
                m_pRightCenterPoint = QPointF(m_pDragRect.topRight().x(), m_pDragRect.center().y());
                m_pDownCenterPoint = QPointF(m_pDragRect.center().x(), m_pDragRect.bottomLeft().y());
                m_pLeftCenterPoint = QPointF(m_pDragRect.topLeft().x(), m_pDragRect.center().y());
            }else if (this->cursor().shape() == Qt::SizeFDiagCursor ||
                      this->cursor().shape() == Qt::SizeVerCursor ||
                      this->cursor().shape() == Qt::SizeBDiagCursor ||
                      this->cursor().shape() == Qt::SizeHorCursor){  // 缩放
                this->scaleDragRect(mouseEvent->localPos());
            }else {
                this->resizeDragRect(m_pPressedPoint, mouseEvent->localPos());
            }
            update();
        }else {
            QPointF currentPos = mouseEvent->localPos();
            if (!m_pDragRect.isEmpty()){       //选择框不为空
                //鼠标在选择框的左上角圆标内
                if (sqrt(pow(m_pDragRect.topLeft().y() - currentPos.y(), 2) +
                              pow(m_pDragRect.topLeft().x() - currentPos.x(), 2)) < 8) {
                    this->setCursor(Qt::SizeFDiagCursor);
                    m_pDirection = 0;
                }
                //鼠标在选择框的上拉圆标内
                else if (sqrt(pow(m_pUpCenterPoint.y() - currentPos.y(), 2) +
                              pow(m_pUpCenterPoint.x() - currentPos.x(), 2)) < 8) {
                    this->setCursor(Qt::SizeVerCursor);
                    m_pDirection = 1;
                }
                //鼠标在选择框的右上角圆标内
                else if (sqrt(pow(m_pDragRect.topRight().y() - currentPos.y(), 2) +
                              pow(m_pDragRect.topRight().x() - currentPos.x(), 2)) < 8) {
                    this->setCursor(Qt::SizeBDiagCursor);
                    m_pDirection = 2;
                }
                //鼠标在选择框的右拉圆标内
                else if (sqrt(pow(m_pRightCenterPoint.y() - currentPos.y(), 2) +
                              pow(m_pRightCenterPoint.x() - currentPos.x(), 2)) < 8) {
                    this->setCursor(Qt::SizeHorCursor);
                    m_pDirection = 3;
                }
                //鼠标在选择框的右下角圆标内
                else if (sqrt(pow(m_pDragRect.bottomRight().y() - currentPos.y(), 2) +
                              pow(m_pDragRect.bottomRight().x() - currentPos.x(), 2)) < 8) {
                    this->setCursor(Qt::SizeFDiagCursor);
                    m_pDirection = 4;
                }
                //鼠标在选择框的下拉圆标内
                else if (sqrt(pow(m_pDownCenterPoint.y() - currentPos.y(), 2) +
                              pow(m_pDownCenterPoint.x() - currentPos.x(), 2)) < 8) {
                    this->setCursor(Qt::SizeVerCursor);
                    m_pDirection = 5;
                }
                //鼠标在选择框的左下角圆标内
                else if (sqrt(pow(m_pDragRect.bottomLeft().y() - currentPos.y(), 2) +
                              pow(m_pDragRect.bottomLeft().x() - currentPos.x(), 2)) < 8) {
                    this->setCursor(Qt::SizeBDiagCursor);
                    m_pDirection = 6;
                }
                //鼠标在选择框的左拉圆标内
                else if (sqrt(pow(m_pLeftCenterPoint.y() - currentPos.y(), 2) +
                              pow(m_pLeftCenterPoint.x() - currentPos.x(), 2)) < 8) {
                    this->setCursor(Qt::SizeHorCursor);
                    m_pDirection = 7;
                }
                //鼠标进入选择框中
                else if (m_pDragRect.contains(currentPos)) {
                    this->setCursor(Qt::SizeAllCursor);
                }
                else {
                    this->setCursor(Qt::ArrowCursor);
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void DB_ScreenShots::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRect(this->rect());
    path.addRect(m_pDragRect);
    path.setFillRule(Qt::OddEvenFill);
    painter.fillPath(path, QBrush(QColor(85, 85, 85, 225)));

    if (!m_pDragRect.isEmpty()) {
        painter.setPen(QPen(QBrush(QColor(103,153,252)), 1, Qt::SolidLine));
        painter.setBrush(Qt::transparent);
        painter.drawRect(m_pDragRect);
        path -= path;
        int eWidth = DB_ApplicationScale::getScaleWidth(14);
        path.addEllipse(m_pDragRect.topLeft(), eWidth, eWidth);
        path.addEllipse(m_pDragRect.topRight(), eWidth, eWidth);
        path.addEllipse(m_pDragRect.bottomLeft(), eWidth, eWidth);
        path.addEllipse(m_pDragRect.bottomRight(), eWidth, eWidth);
        path.addEllipse(m_pUpCenterPoint, eWidth, eWidth);
        path.addEllipse(m_pRightCenterPoint, eWidth, eWidth);
        path.addEllipse(m_pDownCenterPoint, eWidth, eWidth);
        path.addEllipse(m_pLeftCenterPoint, eWidth, eWidth);
        painter.setBrush(QBrush(QColor(103,153,252)));
        QTextOption textOption;
        textOption.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        textOption.setTextDirection(Qt::LeftToRight);
        painter.drawPath(path);
        QSize size = DB_ApplicationScale::getScaleSize(QSize(80, 30));
        painter.setPen(QPen(QColor(Qt::white)));
        painter.drawText(QRectF(m_pDragRect.topLeft().x(), m_pDragRect.topLeft().y() - size.height(),
                                size.width(), size.height()), QString("%1x%2").arg(QString::number(m_pDragRect.width()))
                         .arg(QString::number(m_pDragRect.height())));
    }
}

void DB_ScreenShots::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_pDragRect.isEmpty()) {
        int width = DB_ApplicationScale::getScaleWidth(800);
        int height = DB_ApplicationScale::getScaleWidth(600);
        m_pDragRect = QRectF((this->width() - width)/2,
                             (this->height() - height)/2,
                             width, height);
    }

}

void DB_ScreenShots::initWidget()
{
    ui->horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    ui->horizontalLayout_2->setAlignment(Qt::AlignCenter);
    ui->frame->setLayout(ui->horizontalLayout_2);
    ui->frame->hide();

    connect(ui->pClose, &CustomPushButton::clicked, [=](){
        this->deleteLater();
    });

    connect(ui->pSave, &CustomPushButton::clicked, [=](){
        emit screenShots(m_pDragRect);
    });
}

void DB_ScreenShots::scaleDragRect(QPointF mousePos)
{
    qreal x, y, minX, minY;
    if (0 == m_pDirection) {
        x = mousePos.x();
        y = mousePos.y();
        minX = m_pDragRect.bottomRight().x() - m_pDragRectMinSize.width();
        minY = m_pDragRect.bottomRight().y() - m_pDragRectMinSize.height();
        x = (x < minX ? x : minX);
        y = (y < minY ? y : minY);
        m_pDragRect.setTopLeft(QPointF(x, y));
    }else if (1 == m_pDirection) {
        x = m_pDragRect.topLeft().x();
        y = mousePos.y();
        minY = m_pDragRect.bottomRight().y() - m_pDragRectMinSize.height();
        y = (y < minY ? y : minY);
        m_pDragRect.setTopLeft(QPointF(x, y));
    }else if (2 == m_pDirection) {
        x = mousePos.x();
        y = mousePos.y();
        minX = m_pDragRect.bottomLeft().x() + m_pDragRectMinSize.width();
        minY = m_pDragRect.bottomLeft().y() - m_pDragRectMinSize.height();
        x = (x > minX ? x : minX);
        y = (y < minY ? y : minY);
        m_pDragRect.setTopRight(QPointF(x, y));
    }else if (3 == m_pDirection) {
        x = mousePos.x();
        y = m_pDragRect.topRight().y();
        minX = m_pDragRect.bottomLeft().x() + m_pDragRectMinSize.width();
        x = (x > minX ? x : minX);
        m_pDragRect.setTopRight(QPointF(x, y));
    }else if (4 == m_pDirection) {
        x = mousePos.x();
        y = mousePos.y();
        minX = m_pDragRect.topLeft().x() + m_pDragRectMinSize.width();
        minY = m_pDragRect.topLeft().y() + m_pDragRectMinSize.height();
        x = (x > minX ? x : minX);
        y = (y > minY ? y : minY);
        m_pDragRect.setBottomRight(QPointF(x, y));
    }else if (5 == m_pDirection) {
        x = m_pDragRect.bottomRight().x();
        y = mousePos.y();
        minY = m_pDragRect.topLeft().y() + m_pDragRectMinSize.height();
        y = (y > minY ? y : minY);
        m_pDragRect.setBottomRight(QPointF(x, y));
    }else if (6 == m_pDirection) {
        x = mousePos.x();
        y = mousePos.y();
        minX = m_pDragRect.topRight().x() - m_pDragRectMinSize.width();
        minY = m_pDragRect.topRight().y() + m_pDragRectMinSize.height();
        x = (x < minX ? x : minX);
        y = (y > minY ? y : minY);
        m_pDragRect.setBottomLeft(QPointF(x, y));
    }else if (7 == m_pDirection) {
        x = mousePos.x();
        y = m_pDragRect.bottomLeft().y();
        minX = m_pDragRect.topRight().x() - m_pDragRectMinSize.width();
        x = (x < minX ? x : minX);
        m_pDragRect.setBottomLeft(QPointF(x, y));
    }

    m_pUpCenterPoint = QPointF(m_pDragRect.center().x(), m_pDragRect.topLeft().y());
    m_pRightCenterPoint = QPointF(m_pDragRect.topRight().x(), m_pDragRect.center().y());
    m_pDownCenterPoint = QPointF(m_pDragRect.center().x(), m_pDragRect.bottomLeft().y());
    m_pLeftCenterPoint = QPointF(m_pDragRect.topLeft().x(), m_pDragRect.center().y());
}

void DB_ScreenShots::resizeDragRect(QPointF pressedPoint, QPointF currentPoint)
{
    qreal x, y, minX, minY;
    if (pressedPoint.x() <= currentPoint.x() &&
            pressedPoint.y() <= currentPoint.y()) {
        x = currentPoint.x();
        y = currentPoint.y();
        minX = pressedPoint.x() + m_pDragRectMinSize.width();
        minY = pressedPoint.y() + m_pDragRectMinSize.height();
        x = x > minX ? x : minX;
        y = y > minY ? y : minY;
        m_pDragRect.setTopLeft(pressedPoint);
        m_pDragRect.setBottomRight(QPointF(x, y));
    }else if (pressedPoint.x() <= currentPoint.x() &&
              pressedPoint.y() >= currentPoint.y()) {
        x = currentPoint.x();
        y = currentPoint.y();
        minX = pressedPoint.x() + m_pDragRectMinSize.width();
        minY = pressedPoint.y() - m_pDragRectMinSize.height();
        x = x > minX ? x : minX;
        y = y < minY ? y : minY;
        m_pDragRect.setBottomLeft(pressedPoint);
        m_pDragRect.setTopRight(QPointF(x, y));
    }else if (pressedPoint.x() >= currentPoint.x() &&
              pressedPoint.y() <= currentPoint.y()) {
        x = currentPoint.x();
        y = currentPoint.y();
        minX = pressedPoint.x() - m_pDragRectMinSize.width();
        minY = pressedPoint.y() + m_pDragRectMinSize.height();
        x = x < minX ? x : minX;
        y = y > minY ? y : minY;
        m_pDragRect.setTopRight(pressedPoint);
        m_pDragRect.setBottomLeft(QPointF(x, y));
    }else {
        x = currentPoint.x();
        y = currentPoint.y();
        minX = pressedPoint.x() - m_pDragRectMinSize.width();
        minY = pressedPoint.y() - m_pDragRectMinSize.height();
        x = x < minX ? x : minX;
        y = y < minY ? y : minY;
        m_pDragRect.setBottomRight(pressedPoint);
        m_pDragRect.setTopLeft(QPointF(x, y));
    }
    m_pUpCenterPoint = QPointF(m_pDragRect.center().x(), m_pDragRect.topLeft().y());
    m_pRightCenterPoint = QPointF(m_pDragRect.topRight().x(), m_pDragRect.center().y());
    m_pDownCenterPoint = QPointF(m_pDragRect.center().x(), m_pDragRect.bottomLeft().y());
    m_pLeftCenterPoint = QPointF(m_pDragRect.topLeft().x(), m_pDragRect.center().y());
}

void DB_ScreenShots::showToolWidget()
{
    qreal x = m_pDragRect.bottomRight().x() - ui->frame->width();
    qreal y = m_pDragRect.bottomRight().y() + 5;
    qreal maxX = this->width() - ui->frame->width();
    qreal maxY = this->height() - ui->frame->height();
    qreal minX = 0;
    qreal minY = 0;
    x = x < minX ? minX : (x > maxX ? maxX : x);
    y = y < minY ? minY : (y > maxY ? maxY : y);
    ui->frame->move(x, y);
    ui->frame->show();
}
