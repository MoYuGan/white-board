#ifndef DB_CUSTOMLABEL_H
#define DB_CUSTOMLABEL_H

/*
 * 自定义QLabel，实现各种动态效果
 *
*/

#include <QLabel>
#include <QTimer>
#include <QtDebug>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QBitmap>
#include <qrencode.h>
#include <math.h>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include "Public/public_function.h"


class DB_CustomLabel : public QLabel
{
/*
 *效果:逐渐缩小或放大
*/
    Q_OBJECT
public:
    DB_CustomLabel(QWidget *parent = nullptr) : QLabel(parent) {
        m_pTimer = new QTimer(this);
        connect(m_pTimer, &QTimer::timeout, [=](){
            m_pTimer->stop();
            if (m_pBaseWidth < m_pScaleWidth) {
                m_pBaseWidth = (m_pBaseWidth + m_pSubWidth) > m_pScaleWidth ? m_pScaleWidth : (m_pBaseWidth + m_pSubWidth);
            }else if (m_pBaseWidth > m_pScaleWidth){
                m_pBaseWidth = (m_pBaseWidth - m_pSubWidth) < m_pScaleWidth ? m_pScaleWidth : (m_pBaseWidth - m_pSubWidth);
            }

            if (m_pBaseHeight < m_pScaleHeight) {
                m_pBaseHeight = (m_pBaseHeight + m_pSubHeight) > m_pScaleHeight ? m_pScaleHeight : (m_pBaseHeight + m_pSubHeight);
            }else if (m_pBaseHeight > m_pScaleHeight){
                m_pBaseHeight = (m_pBaseHeight - m_pSubHeight) < m_pScaleHeight ? m_pScaleHeight : (m_pBaseHeight - m_pSubHeight);
            }

            this->setFixedSize(m_pBaseWidth, m_pBaseHeight);
            if (m_pBaseWidth != m_pScaleWidth || m_pBaseHeight != m_pScaleHeight) {
                m_pTimer->start(m_pIntervalTime);
            }else
                emit scaleFinished();

            if (m_pBaseWidth == 0 && m_pBaseHeight == 0)
                this->hide();
        });
    }

    void setFrameBaseSize(int width, int height) {
        m_pBaseWidth = width;
        m_pBaseHeight = height;
    }

    void setScaleSize(int width, int height) {
        m_pTimer->stop();
        m_pScaleWidth = width;
        m_pScaleHeight = height;
        m_pSubWidth = qAbs(m_pBaseWidth - m_pScaleWidth)/m_pLoopCount;
        m_pSubHeight = qAbs(m_pBaseHeight - m_pScaleHeight)/m_pLoopCount;
    }

    void startResize() {
        m_pTimer->start(m_pIntervalTime);
        this->show();
    }

private:
    int m_pBaseWidth;               //缩放前宽
    int m_pBaseHeight;              //缩放前高
    int m_pScaleWidth;              //缩放后宽
    int m_pScaleHeight;             //缩放后高
    QTimer *m_pTimer;
    int m_pLoopCount = 10;       //循环次数,用于计算每次缩放的差值,与间隔时间一起决定缩放的总时间
    int m_pIntervalTime = 10;    //间隔时间(ms),与循环次数一起决定缩放的总时间
    int m_pSubWidth;            //每次缩放的宽的差值
    int m_pSubHeight;           //每次缩放的高的差值

signals:
    void scaleFinished();

public slots:
    void scaleWithParent(QSize size) {
        this->setFixedSize(size);
        this->setGeometry(0, 0, size.width(), size.height());
    }
};

class DB_CustomLabel_1 : public QLabel
{
/*
 *效果:
 * 1、鼠标点击发送点击事件
 * 2、鼠标进入改变光标样式
*/
    Q_OBJECT
public:
    DB_CustomLabel_1(QWidget *parent = nullptr) : QLabel(parent) {
        this->installEventFilter(this);
    }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QPoint pos = mouseEvent->pos();
            if (mouseEvent->button() == Qt::LeftButton &&
                    this->rect().contains(pos)) {
                emit mouseClicked();
            }
        }else if (event->type() == QEvent::Enter) {
            this->setCursor(Qt::PointingHandCursor);
        }else if (event->type() == QEvent::Leave) {
            this->setCursor(Qt::ArrowCursor);
        }else if (event->type() == QEvent::MouseButtonPress) {
            return true;
        }

        return QLabel::eventFilter(watched, event);
    }

signals:
    void mouseClicked();
};

class DB_CustomLabel_2 : public QLabel
{
    /*
     *功能:
     * 1、二维码显示
    */
    Q_OBJECT

public:
    explicit DB_CustomLabel_2(QWidget *parent = Q_NULLPTR) : QLabel(parent) {
        qrcode = nullptr;
        m_pShowLogo = false;
    }

    ~DB_CustomLabel_2() {
        if(qrcode != nullptr) {
            QRcode_free(qrcode);
        }
    }

    void setString(const QString str) {
        if(qrcode != nullptr) {
            QRcode_free(qrcode);
        }
        qrcode = QRcode_encodeString(str.toStdString().c_str(), 2, QR_ECLEVEL_H, QR_MODE_8, 1);
        update();
    }

    void isShowLogo(bool bo) {
        m_pShowLogo = bo;
        update();
    }

protected:
    void paintEvent(QPaintEvent *ev) {
        Q_UNUSED(ev);
        int width = this->width() - 20;
        int height = this->height() - 20;
        if (qrcode == NULL)
            return;

        int qrWidth = qrcode->width > 0 ? qrcode->width : 1 ;
        double scaleX = (double)width / (double)qrWidth ;
        double scaleY = (double)height / (double)qrWidth ;
        QPainter painter(this);
        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        painter.drawRect(this->rect());
        painter.setBrush(Qt::black);
        for(int y = 0; y < qrWidth; ++y) {
            for(int x = 0; x < qrWidth; ++x) {
                uchar node = qrcode->data[y*qrWidth + x];
                if(node & 0x01) {
                    QRectF rectf(x*scaleX + 10, y*scaleY + 10, scaleX, scaleY);
                    painter.drawRects(&rectf, 1);
                }
            }
        }

        painter.setRenderHint(QPainter::Antialiasing);
        if(m_pShowLogo) {
            QPixmap pixmap(":/images/courseware/weixin-2@2x.png");
            painter.setPen(QPen(QColor(85, 85, 85, 0)));
            painter.setBrush(QBrush(QColor(85, 85, 85, 85)));
            painter.drawRoundedRect(this->rect(), 8, 8);
            QPoint centerPos = this->rect().center();
            int pixmapWidth = 70;
            pixmap.scaled(QSize(pixmapWidth, pixmapWidth));
            QRect pixmapRect = QRect(centerPos.x() - pixmapWidth/2, centerPos.y() - pixmapWidth/2, pixmapWidth, pixmapWidth);
            painter.drawPixmap(pixmapRect, pixmap);
        }
    }

private:
    QRcode* qrcode;
    QPixmap* image;
    bool m_pShowLogo;
};

class DB_CustomLabel_3 : public QLabel
{
    /*
     *自定义“圆”图标
    */
    Q_OBJECT
public:
    explicit DB_CustomLabel_3(QWidget *parent = Q_NULLPTR) : QLabel(parent) {
        m_pIsHighLight = true;
    }

    //高亮显示
    void isHighlight(bool bo) {
        m_pIsHighLight = bo;
    }

protected:
    void paintEvent(QPaintEvent *) {
        QString text = this->text();
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(QColor(0,0,0,0)));
        if (m_pIsHighLight)
            painter.setBrush(QBrush(QColor(78, 155, 252)));
        else
            painter.setBrush(QBrush(QColor(225, 225, 225)));
        painter.drawEllipse(this->rect());

        if (m_pIsHighLight)
            painter.setPen(QPen(Qt::white));
        else
            painter.setPen(QPen(QColor(185, 185, 185)));
        QRect textRect = QRect(this->rect().x(), this->rect().y(), this->rect().width(), this->rect().height() - 1);
        painter.drawText(textRect, (Qt::AlignCenter | Qt::AlignVCenter),  text);
    }

private:
    bool m_pIsHighLight;
};

class DB_CustomLabel_4 : public QLabel
{
    /*
     *用户头像显示
    */
    Q_OBJECT
public:
    explicit DB_CustomLabel_4(QWidget *parent = Q_NULLPTR) : QLabel(parent) {
    }

    void setIcon(const QPixmap &pixmap) {
        m_pIcon = pixmap;
        this->update();
    }
protected:
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing, true);

        QRect rect = QRect(1, 1, this->rect().width() - 2, this->rect().height() - 2);
        int width = rect.width();
        int height = rect.height();
        int radius = width < height ? width/2 : height/2;
        QPainterPath path;
        path.addEllipse(rect.center(), radius, radius);
        painter.setClipPath(path);

        QRect drawRect = QRect(width/2-radius, height/2-radius, radius*2, radius*2);
        QPixmap pixmap = m_pIcon.scaled(drawRect.width(), drawRect.height());
        painter.drawPixmap(drawRect, pixmap);
    }

private:
    QPixmap m_pIcon;
};

class DB_CustomLabel_5 : public QLabel
{
    /*
    *   遮慕专用缩放按钮
    */
    Q_OBJECT
public:
    DB_CustomLabel_5(int direction, QWidget *parent = 0):
        m_pDirection(direction),
        QLabel(parent){}

    //检查鼠标是否进入图标内
    bool isContainsMousePos(const QPoint &pos) {
        QPoint subPos = QPoint(pos.x() - this->geometry().x(), pos.y() - this->geometry().y());
        if (this->rect().contains(subPos))
            return true;
        else
            return false;
    }

private:
    int m_pDirection;       //按钮方向，0=左，1=上，2=右，3=下

protected:
    void paintEvent(QPaintEvent *)
    {
      QPainter painter(this);
      painter.setRenderHint(QPainter::Antialiasing, true);
      QPainterPath path;
      path.setFillRule(Qt::WindingFill);
      int d = qMin(this->width(),this->height());
      QPen pen;
      pen.setWidth(4);
      pen.setColor(Qt::white);
      painter.setPen(pen);
      painter.drawEllipse(QPointF(d/2.0, d/2.0), d/2.0 - 2, d/2.0 - 2);
      path.moveTo(this->width()*11/40, this->width()*10/40);
      path.lineTo(this->width()*20/40, this->width()*32/40);
      path.lineTo(this->width()*29/40, this->width()*10/40);
      path.lineTo(this->width()*20/40, this->width()*15/40);
      path.closeSubpath();
      pen.setWidth(1);
      painter.setPen(pen);
      painter.setBrush(Qt::white);
      switch (m_pDirection)
      {
      case 0: {
         painter.translate(0,d);
         painter.rotate(-90);
      }break;
      case 1:
         break;
      case 2: {
         painter.translate(d,0);
         painter.rotate(90);
      }break;
      case 3: {
         painter.translate(d,d);
         painter.rotate(180);
      }break;
      default:
           break;
      }
        painter.drawPath(path);
    }
};

class DB_CustomLabel_6 : public QLabel
{
    Q_OBJECT
public:
    DB_CustomLabel_6(QWidget *parent = 0):
        QLabel(parent)
    {
        this->initWidget();
        this->mResize();
    }


protected:
    void resizeEvent(QResizeEvent *event) {
        QLabel::resizeEvent(event);
        this->mResize();
    }
private:
    QFrame *m_pFrameBottom;
    QLabel *m_pLabelIndex;
    QPushButton *m_pBtnDelete;
    QHBoxLayout *m_pLayout;

    void initWidget() {
        this->setScaledContents(true);
        QVBoxLayout *vlayout = new QVBoxLayout(this);
        vlayout->setContentsMargins(0, 0, 0, 0);
        vlayout->setSpacing(0);

        m_pFrameBottom = new QFrame(this);
        m_pFrameBottom->setObjectName("frame");
        m_pFrameBottom->setStyleSheet("#frame{border: none; background-color: rgba(0, 0, 0, 125);}");

        QVBoxLayout *vlayout1 = new QVBoxLayout(m_pFrameBottom);
        vlayout1->setContentsMargins(0, 0, 0, 0);
        vlayout1->setSpacing(0);

        m_pLayout = new QHBoxLayout(this);
        m_pLayout->setSpacing(0);

        m_pLabelIndex = new QLabel(this);
        m_pLayout->addWidget(m_pLabelIndex);
        m_pLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));

        m_pBtnDelete = new QPushButton(this);
        m_pBtnDelete->setStyleSheet("QPushButton{border-image: url(':/images/main/showPage/shanchu@2x.png');}");
        m_pLayout->addWidget(m_pBtnDelete);
    }

    void mResize() {
        int margin = Public_Function::getScaleSize(10);
        m_pLayout->setContentsMargins(margin, margin, margin, margin);

        QSize size = Public_Function::getScaleSize(QSize(17, 17));
        m_pBtnDelete->setFixedSize(size);
    }
};


#endif // DB_CUSTOMLABEL_H
