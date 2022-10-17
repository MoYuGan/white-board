#ifndef DB_MBOXTOOLTIP_H
#define DB_MBOXTOOLTIP_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QPointer>
#include <QtDebug>

class DB_MBoxToolTip :  public QWidget
{
public:
    DB_MBoxToolTip(QWidget *parent = nullptr) :
        QWidget(parent)
    {
        initWidget();

        m_pTimer = new QTimer(this);
        connect(m_pTimer, &QTimer::timeout, [=](){ this->deleteLater(); });
    }

    static DB_MBoxToolTip *getToolTip(int tooltipStyle = 0) {
        static QPointer<DB_MBoxToolTip> toolTip = nullptr;
        if (nullptr ==  toolTip) {
            toolTip = new DB_MBoxToolTip;
        }
        toolTip->setToolTipStyle(tooltipStyle);
        return toolTip;
    }

    void setToolTipStyle(int tooltipStyle) {
        this->m_pToolTipStyle = tooltipStyle;
        if (0 == m_pToolTipStyle)
            hLayout->setContentsMargins(6, 6, 6, 15);
        else if (1 == m_pToolTipStyle)
            hLayout->setContentsMargins(6, 6, 6, 6);
    }

    void showMBox(QPoint pt) {
        this->move(QPoint(pt.x() - this->width()/2, pt.y() - this->height()));
        this->show();
        m_pTimer->start(1000);
    }

    void showMBox(QWidget *parent, const QString &text, QPoint pt) {
        this->setText(text);

        this->setParent(parent);
        this->move(QPoint(pt.x() - this->width()/2, pt.y() - this->height()));
        this->raise();
        this->show();
        m_pTimer->start(1000);
    }

    void setText(const QString &text) {
        m_pLabelText->setText(text);
        m_pFrame->adjustSize();
        this->adjustSize();
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        /* 画阴影  */
        QColor color(105, 105, 105);
        int border = 6;
        int tHeight = 9;
        int j;
        int radius = 8;
        for(int i=0; i<border; i++)
        {
            j = border - i;
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            if (0 == m_pToolTipStyle)
            {
                QPoint topLeft_p1 = QPoint(j, j + radius);
                QPoint topLeft_p2 = QPoint(j + radius, j);
                QPoint topRight_p1 = QPoint(this->width() - j - radius, topLeft_p2.y());
                QPoint topRight_p2 = QPoint(this->width() - j, topLeft_p1.y());
                QPoint BottomRight_p1 = QPoint(topRight_p2.x(), this->height() - j - tHeight - radius);
                QPoint BottomRight_p2 = QPoint(topRight_p1.x(),  this->height() - j - tHeight);
                QPoint BottomLeft_p1 = QPoint(topLeft_p2.x(), BottomRight_p2.y());
                QPoint BottomLeft_p2 = QPoint(topLeft_p1.x(),  BottomRight_p1.y());
                path.moveTo(topLeft_p1);
                path.cubicTo(topLeft_p1, QPoint(j, j), topLeft_p2);
                path.lineTo(topRight_p1);
                path.cubicTo(topRight_p1, QPoint(this->width() - j, j), topRight_p2);
                path.lineTo(BottomRight_p1);
                path.cubicTo(BottomRight_p1, QPoint(this->width() - j, this->height() - j - tHeight), BottomRight_p2);
                path.lineTo(this->width()/2 + 6, BottomRight_p2.y());
                path.lineTo(this->width()/2, BottomRight_p2.y() + tHeight);
                path.lineTo(this->width()/2 - 6, BottomRight_p2.y());
                path.lineTo(BottomLeft_p1);
                path.cubicTo(BottomLeft_p1, QPoint(j, this->height() - j - tHeight),  BottomLeft_p2);
                path.lineTo(topLeft_p1);
            }else if (1 == m_pToolTipStyle) {
                path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2, radius, radius);
            }

            switch(i)
            {
            case 0:
                color.setAlpha(80);
                break;
            case 1:
                color.setAlpha(50);
                break;
            case 2:
                color.setAlpha(20);
                break;
            case 3:
                color.setAlpha(15);
                break;
            case 4:
                color.setAlpha(10);
                break;
            case 5:
                color.setAlpha(7);
                break;
            default:
                break;
            }
            QPen pen;
            pen.setColor(color);
            pen.setStyle(Qt::SolidLine);
            pen.setCapStyle(Qt::RoundCap);
            pen.setJoinStyle(Qt::RoundJoin);
            painter.setPen(pen);
            painter.drawPath(path);
        }

        /* 画背景色 */
        j = border + 1;
        QPainterPath path;
        if (0 == m_pToolTipStyle) {
            QPoint topLeft_p1 = QPoint(j, j + radius);
            QPoint topLeft_p2 = QPoint(j + radius, j);
            QPoint topRight_p1 = QPoint(this->width() - j - radius, topLeft_p2.y());
            QPoint topRight_p2 = QPoint(this->width() - j, topLeft_p1.y());
            QPoint BottomRight_p1 = QPoint(topRight_p2.x(), this->height() - j - tHeight - radius);
            QPoint BottomRight_p2 = QPoint(topRight_p1.x(),  this->height() - j - tHeight);
            QPoint BottomLeft_p1 = QPoint(topLeft_p2.x(), BottomRight_p2.y());
            QPoint BottomLeft_p2 = QPoint(topLeft_p1.x(),  BottomRight_p1.y());
            path.moveTo(topLeft_p1);
            path.cubicTo(topLeft_p1, QPoint(j, j), topLeft_p2);
            path.lineTo(topRight_p1);
            path.cubicTo(topRight_p1, QPoint(this->width() - j, j), topRight_p2);
            path.lineTo(BottomRight_p1);
            path.cubicTo(BottomRight_p1, QPoint(this->width() - j, this->height() - j - tHeight), BottomRight_p2);
            path.lineTo(this->width()/2 + 6, BottomRight_p2.y());
            path.lineTo(this->width()/2, BottomRight_p2.y() + tHeight);
            path.lineTo(this->width()/2 - 6, BottomRight_p2.y());
            path.lineTo(BottomLeft_p1);
            path.cubicTo(BottomLeft_p1, QPoint(j, this->height() - j - tHeight),  BottomLeft_p2);
            path.lineTo(topLeft_p1);
        }else if (1 == m_pToolTipStyle) {
            path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2, radius, radius);
        }

        painter.setPen(QPen(Qt::white));
        painter.setBrush(Qt::white);
        painter.drawPath(path);
    }

private:
    QLabel *m_pLabelText;
    QTimer *m_pTimer;
    QHBoxLayout *hLayout;
    QFrame *m_pFrame;
    int m_pToolTipStyle = 0;    //ToolTip的样式

private:
    void initWidget() {
        hLayout = new QHBoxLayout(this);
        hLayout->setContentsMargins(6, 6, 6, 15);
        m_pFrame = new QFrame(this);
        m_pFrame->setObjectName("frame");
        m_pFrame->setStyleSheet("#frame{border: none;}");
        hLayout->addWidget(m_pFrame);

        QHBoxLayout *layout2 = new QHBoxLayout(m_pFrame);
        layout2->setContentsMargins(10, 10, 10, 10);
        layout2->setSpacing(0);

        m_pLabelText = new QLabel(m_pFrame);
        m_pLabelText->setAlignment(Qt::AlignCenter);
        m_pLabelText->setStyleSheet("color: gray;");
        QFont font;
        font.setPixelSize(13);
        m_pLabelText->setFont(font);
        layout2->addWidget(m_pLabelText);

        this->adjustSize();
    }

};

#endif // DB_MBOXTOOLTIP_H
