#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QFrame>
#include <QtDebug>
#include "ShareStyle/db_scale.h"

class MenuWidget: public QWidget
{
    Q_OBJECT
public:
    MenuWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        this->initWidget();
    }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::Enter) {
            this->setCursor(Qt::PointingHandCursor);
            if (!m_pHoverIconPath.isEmpty()) {
                QPixmap pixmap;
                pixmap.load(m_pHoverIconPath);
                m_pLabelIcon->setPixmap(pixmap);
            }

            if (!m_pArrowHoverIconPath.isEmpty()) {
                QPixmap pixmap;
                pixmap.load(m_pArrowHoverIconPath);
                m_PLabelArrow->setPixmap(pixmap);
            }

            QColor color = Qt::white;
            m_pLabelText->setStyleSheet(QString("QLabel{"
                                                "color: rgb(%1, %2, %3);"
                                                "}").arg(color.red()).arg(color.green()).arg(color.blue()));
        }else if (event->type() == QEvent::Leave) {
            this->setCursor(Qt::ArrowCursor);
            this->setLeaveStyle();
        }else if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton &&
                    m_pFrame->rect().contains(mouseEvent->pos())) {
                emit this->mouseClicked();
            }
        }

        return QWidget::eventFilter(watched, event);
    }

    void setIcon(const QString &fileName) {
        m_pIconPath = fileName;

        QPixmap pixmap;
        pixmap.load(fileName);
        m_pLabelIcon->setPixmap(pixmap);
    }

    void setHoverIcon(const QString &fileName) {
        m_pHoverIconPath = fileName;
    }

    void setIconSize(const QSize &size) {
        m_pLabelIcon->setFixedSize(size);
    }

    void setText(const QString &text) {
        m_pLabelText->setText(text);
    }

    void setIconAndText(const QString &fileName, const QString &text) {
        m_pIconPath = fileName;
        QPixmap pixmap;
        pixmap.load(fileName);
        m_pLabelIcon->setPixmap(pixmap);
        m_pLabelText->setText(text);
    }

    void setArrowIcon(const QString &fileName) {
        m_pArrowIconPath = fileName;
        QPixmap pixmap;
        pixmap.load(fileName);
        m_PLabelArrow->setPixmap(pixmap);
    }

    void setArrowHoverIcon(const QString &fileName) {
        m_pArrowHoverIconPath = fileName;
    }

    void setArrowSize(const QSize &size) {
        m_PLabelArrow->setFixedSize(size);
    }

    void setRadius(int topLeft, int topRight, int bottomLeft, int bottomRight) {
        m_pBasicStyle.append(QString("#%1{border-top-left-radius: %2px;"
                                     "border-top-right-radius: %3px;"
                                     "border-bottom-left-radius: %4px;"
                                     "border-bottom-right-radius: %5px;"
                                     "}").arg(m_pFrame->objectName())
                                     .arg(topLeft).arg(topRight).arg(bottomLeft).arg(bottomRight));
        m_pFrame->setStyleSheet(m_pBasicStyle);
    }

public slots:
    void setLeaveStyle() {
        if (!m_pHoverIconPath.isEmpty()) {
            QPixmap pixmap;
            pixmap.load(m_pIconPath);
            m_pLabelIcon->setPixmap(pixmap);
        }

        if (!m_pArrowHoverIconPath.isEmpty()) {
            QPixmap pixmap;
            pixmap.load(m_pArrowIconPath);
            m_PLabelArrow->setPixmap(pixmap);
        }

        QColor color = QColor(102, 102, 102);
        m_pLabelText->setStyleSheet(QString("QLabel{"
                                            "color: rgb(%1, %2, %3);"
                                            "}").arg(color.red()).arg(color.green()).arg(color.blue()));
        m_pFrame->clearFocus();
    }

protected:
    void paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.fillRect(this->rect(), QBrush(Qt::transparent));
    }

private:
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
    QLabel *m_PLabelArrow;
    QFrame *m_pFrame;
    QString m_pBasicStyle;
    QString m_pIconPath;
    QString m_pHoverIconPath;
    QString m_pArrowIconPath;
    QString m_pArrowHoverIconPath;

    void initWidget() {
        QHBoxLayout *hLayout = new QHBoxLayout(this);
        hLayout->setContentsMargins(0, 0, 0, 0);
        hLayout->setSpacing(0);


        QColor color = QColor(78, 155, 252);
        m_pFrame = new QFrame(this);
        m_pFrame->setObjectName("frame");
        m_pBasicStyle = QString("#frame{background: rgba(255, 255, 255, 230);}");
        m_pBasicStyle.append(QString("#frame::hover{background: rgba(%1, %2, %3, %4);}")
                             .arg(color.red()).arg(color.green())
                             .arg(color.blue()).arg(color.alpha()));
        color = QColor(102, 102, 102);
        m_pBasicStyle.append(QString("#frame{color: rgba(%1, %2, %3, %4);}")
                             .arg(color.red())
                             .arg(color.green())
                             .arg(color.blue())
                             .arg(color.alpha()));
        m_pFrame->setStyleSheet(m_pBasicStyle);
        m_pFrame->installEventFilter(this);
        hLayout->addWidget(m_pFrame);
        QHBoxLayout *hLayout1 = new QHBoxLayout(m_pFrame);
        hLayout1->setContentsMargins(DB_ApplicationScale::getScaleWidth(10), 0,
                                    DB_ApplicationScale::getScaleWidth(10), 0);
        hLayout1->setSpacing(DB_ApplicationScale::getScaleWidth(10));

        m_pLabelIcon = new QLabel(this);
        m_pLabelIcon->setFixedSize(24, 24);
        m_pLabelIcon->setScaledContents(true);
        hLayout1->addWidget(m_pLabelIcon);

        color = QColor(102, 102, 102);
        m_pLabelText = new QLabel(this);
        m_pLabelText->setStyleSheet(QString("QLabel{"
                                            "color: rgb(%1, %2, %3);"
                                            "}").arg(color.red()).arg(color.green()).arg(color.blue()));
        m_pLabelText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        hLayout1->addWidget(m_pLabelText, 1);

        m_PLabelArrow = new QLabel(this);
        m_PLabelArrow->setFixedSize(16, 16);
        m_PLabelArrow->setScaledContents(true);
        hLayout1->addWidget(m_PLabelArrow);
    }

signals:
    void mouseClicked();

};

#endif // MENUWIDGET_H
