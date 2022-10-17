#ifndef DB_CUSTOMPUSHBUTTON_H
#define DB_CUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QtDebug>
#include <QFrame>
#include "Public/public_function.h"

class DB_CustomPushButton : public QPushButton
{
    /*
     *效果:
     * 1、鼠标进入改变光标样式
    */
public:
    DB_CustomPushButton(QWidget *parent = nullptr) : QPushButton(parent) {
        this->installEventFilter(this);
    }

    virtual bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::Enter) {
            m_pOrgCursor = this->cursor();
            this->setCursor(Qt::PointingHandCursor);
        }else if (event->type() == QEvent::Leave) {
            this->setCursor(m_pOrgCursor);
        }
        return QPushButton::eventFilter(watched, event);
    }

private:
    QCursor m_pOrgCursor;
};


//change
class DB_CustomPushButton_2 : public QPushButton
{
    /*
    * 工具专用button
    * 实现:
    *  1、鼠标进入和离开改变光标样式
    *  2、鼠标单击时发送单击事件，双计时发送双击事件（默认不开启），
    *     需要先通过setDblClicked(true)才会开启双击事件，开启后单击事件的响应速度会减慢
    *  3、可设置图标和文本(垂直排列水平居中)
    *  4、可设置图标大小
    */
    Q_OBJECT
public:
    DB_CustomPushButton_2(QWidget *parent = nullptr) :
        QPushButton(parent)
    {
        this->installEventFilter(this);
        this->initWidget();
        m_pHasDblClicked = false;
        m_pClickTimes = 0;

        m_pClickTimer = new QTimer(this);
        connect(m_pClickTimer, &QTimer::timeout, [=](){
            m_pClickTimer->stop();
            if (m_pClickTimes < 2) {
                emit mouseClicked();
            }else {
                emit mouseDblClicked();
            }
            m_pClickTimes = 0;
        });
    }

    //是否拥有双击事件
    void setDblClicked(bool bo) {
        m_pHasDblClicked = bo;
    }

    //设置图标
    void mSetIcon(const QPixmap &pixmap) {
        m_pLabelIcon->setPixmap(pixmap);
    }

    //设置文本
    void mSetText(const QString &text) {
        m_pLabelText->setText(text);
    }

    //设置图标和文本
    void setIconAndText(const QPixmap &pixmap, const QString &text) {
        if (!pixmap.isNull())
            m_pLabelIcon->setPixmap(pixmap);
        m_pLabelText->setText(text);
    }

    //设置图标文本
    void setIconText(const QString &text) {
        m_pLabelIcon->setText(text);
    }

    //设置图标大小
    void mSetIconSize(const QSize &size) {
        if (nullptr != m_pLabelIcon) {
            m_pLabelIcon->setFixedSize(size);
        }
    }

    //设置文本字体
    void mSetFont(const QFont &font) {
        if (nullptr != m_pLabelText) {
            m_pLabelText->setFont(font);
        }
        if (nullptr != m_pLabelIcon) {
            m_pLabelIcon->setFont(font);
        }
    }

    virtual bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent  *mouseEvent = static_cast<QMouseEvent *>(event);
            if (this->rect().contains(mouseEvent->pos()) &&
                    mouseEvent->button() == Qt::LeftButton) {
                if (m_pHasDblClicked) { //拥有双击事件，启动定时器判断双击
                    m_pClickTimes++;
                    if (!m_pClickTimer->isActive()) {
                        m_pClickTimer->start(290);
                    }
                }else {
                    emit this->mouseClicked();
                }
                if (this->isChecked())
                    emit this->checkedClicked();
                else
                    emit this->uncheckedClicked();
            }
        }else if (event->type() == QEvent::Enter) {
            this->setCursor(Qt::PointingHandCursor);
        }else if (event->type() == QEvent::Leave) {
            this->setCursor(Qt::ArrowCursor);
        }

        return QWidget::eventFilter(watched, event);
    }

private:
    void initWidget() {
        //m_pLayout->setSizeConstraint(QLayout::SetMinimumSize);
        QVBoxLayout *vLayout = new QVBoxLayout(this);
        vLayout->setContentsMargins(5, 5, 5, 5);
        vLayout->setSpacing(0);

        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->setContentsMargins(0, 0, 0, 0);
        hLayout->setSpacing(0);
        m_pLabelIcon = new QLabel(this);
        m_pLabelIcon->setStyleSheet("color: rgb(105, 105, 105);");
        m_pLabelIcon->setFixedSize(24, 24);
        m_pLabelIcon->setAlignment(Qt::AlignCenter);
        m_pLabelIcon->setScaledContents(true);
        hLayout->addWidget(m_pLabelIcon, 0, Qt::AlignCenter);
        vLayout->addLayout(hLayout, 1);

        m_pLabelText = new QLabel(this);
        m_pLabelText->setStyleSheet("color: rgb(105, 105, 105);");
        m_pLabelText->setAlignment(Qt::AlignCenter);
        vLayout->addWidget(m_pLabelText, 0, Qt::AlignCenter);
    }

private:
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
    bool m_pHasDblClicked;
    int m_pClickTimes;
    QTimer *m_pClickTimer;

signals:
    void mouseClicked();
    void mouseDblClicked();
    void checkedClicked();
    void uncheckedClicked();
};



class DB_CustomPushButton_5 : public QPushButton
{
    /*
    * QSlider专用减小按钮
    */
    Q_OBJECT
public:
    DB_CustomPushButton_5(QWidget *parent = nullptr) :
        QPushButton(parent)
    {
        m_pIsPressed = false;
        this->installEventFilter(this);
        this->setMouseTracking(true);
    }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (m_pEllipsePath.contains(mouseEvent->pos())) {
                this->setCursor(Qt::PointingHandCursor);
            }else {
                this->setCursor(Qt::ArrowCursor);
                m_pIsPressed = false;
            }
        }else if (event->type() == QEvent::Leave) {
            this->setCursor(Qt::ArrowCursor);
            m_pIsPressed = false;
        }else if (event->type() == QEvent::MouseButtonPress &&
                  this->cursor().shape() == Qt::PointingHandCursor ) {
            m_pIsPressed = true;
            update();
        }else if (event->type() == QEvent::MouseButtonRelease) {
            m_pIsPressed = false;
            update();
        }

        return QPushButton::eventFilter(watched, event);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        QPushButton::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        m_pEllipsePath = QPainterPath();
        m_pEllipsePath.addEllipse(this->rect().center(),
                                  this->width()/2 - Public_Function::getScaleSize(2),
                                  this->height()/2 - Public_Function::getScaleSize(2));

        QPainterPath path = m_pEllipsePath;
        painter.setBrush(QBrush(Qt::white));
        QColor color(105, 105, 105);
        color.setAlpha(30);
        QSize size = Public_Function::getScaleSize(QSize(2, 2));
        painter.setPen(QPen(QBrush(color), size.width()));
        painter.drawPath(path);
        path -= path;
        path.addEllipse(this->rect().center(),
                        this->width()/2 - Public_Function::getScaleSize(3),
                        this->height()/2 - Public_Function::getScaleSize(3));
        color.setAlpha(185);
        painter.drawPath(path);

        if (!m_pIsPressed) {
            painter.setPen(QPen(QBrush(QColor(147,147,147)), Public_Function::getScaleSize(2)));
        }else {
            painter.setPen(QPen(QBrush(QColor(185,185,185)), Public_Function::getScaleSize(2)));
        }

        painter.setBrush(QBrush());
        QRectF rect = path.boundingRect();
        path -= path;
        path.moveTo(rect.x() + Public_Function::getScaleSize(7), rect.y() + rect.height()/2);
        path.lineTo(rect.x() + rect.width() - Public_Function::getScaleSize(7),
                    rect.y() + rect.height()/2);
        painter.drawPath(path);
    }

private:
    QPainterPath m_pEllipsePath;
    bool m_pIsPressed;
};

class DB_CustomPushButton_6 : public QPushButton
{
    /*
    * QSlider专用增加按钮
    */
    Q_OBJECT
public:
    DB_CustomPushButton_6(QWidget *parent = nullptr) :
        QPushButton(parent)
    {
        m_pIsPressed = false;
        this->installEventFilter(this);
        this->setMouseTracking(true);
    }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (m_pEllipsePath.contains(mouseEvent->pos())) {
                this->setCursor(Qt::PointingHandCursor);
            }else {
                this->setCursor(Qt::ArrowCursor);
                m_pIsPressed = false;
            }
        }else if (event->type() == QEvent::Leave) {
            this->setCursor(Qt::ArrowCursor);
            m_pIsPressed = false;
        }else if (event->type() == QEvent::MouseButtonPress &&
                  this->cursor().shape() == Qt::PointingHandCursor ) {
            m_pIsPressed = true;
            update();
        }else if (event->type() == QEvent::MouseButtonRelease) {
            m_pIsPressed = false;
            update();
        }

        return QPushButton::eventFilter(watched, event);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        QPushButton::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        m_pEllipsePath = QPainterPath();
        m_pEllipsePath.addEllipse(this->rect().center(),
                                  this->width()/2 - Public_Function::getScaleSize(2),
                                  this->height()/2 - Public_Function::getScaleSize(2));

        QPainterPath path = m_pEllipsePath;
        painter.setBrush(QBrush(Qt::white));
        QColor color(105, 105, 105);
        color.setAlpha(30);
        QSize size = Public_Function::getScaleSize(QSize(2, 2));
        painter.setPen(QPen(QBrush(color), size.width()));
        painter.drawPath(path);
        path -= path;
        path.addEllipse(this->rect().center(),
                        this->width()/2 - Public_Function::getScaleSize(3),
                        this->height()/2 - Public_Function::getScaleSize(3));
        color.setAlpha(185);
        painter.drawPath(path);


        if (!m_pIsPressed) {
            painter.setPen(QPen(QBrush(QColor(147,147,147)), Public_Function::getScaleSize(2)));
        }else {
            painter.setPen(QPen(QBrush(QColor(185,185,185)), Public_Function::getScaleSize(2)));
        }

        painter.setBrush(QBrush());
        QRectF rect = path.boundingRect();
        path -= path;
        path.moveTo(rect.x() + Public_Function::getScaleSize(7),
                    rect.y() + rect.height()/2);
        path.lineTo(rect.x() + rect.width() - Public_Function::getScaleSize(7),
                    rect.y() + rect.height()/2);
        painter.drawPath(path);
        path -= path;
        path.moveTo(rect.x() + rect.width()/2, rect.y() + Public_Function::getScaleSize(7));
        path.lineTo(rect.x() + rect.width()/2,
                    rect.y() + rect.height() - Public_Function::getScaleSize(7));
        painter.drawPath(path);
    }

private:
    QPainterPath m_pEllipsePath;
    bool m_pIsPressed;
};

class DB_CustomPushButton_9 : public DB_CustomPushButton
{
    Q_OBJECT
public:
   DB_CustomPushButton_9(QWidget *parent = nullptr) : DB_CustomPushButton(parent) {
       m_pBorder = 0;
       m_pLeftMargin = 0;
       m_pTopMargin = 0;
       m_pRightMargin = 0;
       m_pBottomMargin = 0;
       m_pRadiusTopLeft = 0;
       m_pRadiusTopRight = 0;
       m_pRadiusBottomLeft = 0;
       m_pRadiusBottomRight = 0;
       m_pIconSize = QSize(24, 24);
       m_pMouseHover = false;
       m_pHoverColor = QColor(238, 238, 238);

       this->installEventFilter(this);
   }

   void mSetIcon(const QPixmap &pixmap) {
       m_pIcon = pixmap;
       update();
   }

   void mSetIconSize(const QSize &size) {
       this->mSetIconSize(size.width(), size.height());
   }

   inline void mSetIconSize(int width, int height) {
       m_pIconSize.setWidth(width);
       m_pIconSize.setHeight(height);
   }

   void setBorder(int border) {
       m_pBorder = border;
   }

   void setBackgroudColor(const QColor &color) {
       m_pBackgroundColor = color;
   }

   void setCheckedColor(const QColor &color) {
       m_pCheckedColor = color;
   }

   void setBordRadius(int topLeft, int topRight, int bottomLeft, int bottomRight) {
       m_pRadiusTopLeft = topLeft;
       m_pRadiusTopRight = topRight;
       m_pRadiusBottomLeft = bottomLeft;
       m_pRadiusBottomRight = bottomRight;
   }

    void setMargin(int left, int top, int right, int bottom) {
        m_pLeftMargin = left;
        m_pTopMargin = top;
        m_pRightMargin = right;
        m_pBottomMargin = bottom;
    }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::Enter) {
            m_pMouseHover = true;
            update();
        }else if (event->type() == QEvent::Leave) {
            m_pMouseHover = false;
            update();
        }
        return DB_CustomPushButton::eventFilter(watched, event);
    }

protected:
   void paintEvent(QPaintEvent *) {
       QPainter painter(this);
       painter.setRenderHint(QPainter::Antialiasing);
       painter.fillRect(this->rect(), QBrush(Qt::transparent));

       QColor color(105, 105, 105);
       int border = m_pBorder;
       int j;
       if (0 == border) {
           if (this->isChecked() && m_pCheckedColor.isValid()) {
                painter.fillRect(this->rect(), QBrush(m_pCheckedColor));
           }else if (m_pMouseHover && m_pHoverColor.isValid())
                painter.fillRect(this->rect(), QBrush(m_pHoverColor));
           else if (m_pBackgroundColor.isValid()) {
                painter.fillRect(this->rect(), QBrush(m_pBackgroundColor));
           }
       }

       for(int i = 0; i < border; i++)
       {
           j = border - i;
           QPainterPath path;
           path.setFillRule(Qt::WindingFill);

           QPoint topLeft_p1 = QPoint(j + m_pLeftMargin, j + m_pTopMargin + m_pRadiusTopLeft);
           QPoint topLeft_p2 = QPoint(j + m_pLeftMargin + m_pRadiusTopLeft, j + m_pTopMargin);
           QPoint topRight_p1 = QPoint(this->width() - j - m_pRightMargin - m_pRadiusTopRight, topLeft_p2.y());
           QPoint topRight_p2 = QPoint(this->width() - j - m_pRightMargin, topLeft_p1.y());
           QPoint BottomRight_p1 = QPoint(topRight_p2.x(), this->height() - j - m_pBottomMargin - m_pRadiusBottomRight);
           QPoint BottomRight_p2 = QPoint(topRight_p1.x(),  this->height() - j - m_pBottomMargin);
           QPoint BottomLeft_p1 = QPoint(topLeft_p2.x(), BottomRight_p2.y());
           QPoint BottomLeft_p2 = QPoint(topLeft_p1.x(),  BottomRight_p1.y());
           path.moveTo(topLeft_p1);
           path.cubicTo(topLeft_p1, QPoint(j + m_pLeftMargin, j + m_pTopMargin), topLeft_p2);
           path.lineTo(topRight_p1);
           path.cubicTo(topRight_p1, QPoint(this->width() - j - m_pRightMargin, j + m_pTopMargin), topRight_p2);
           path.lineTo(BottomRight_p1);
           path.cubicTo(BottomRight_p1, QPoint(this->width() - j - m_pRightMargin, this->height() - j - m_pBottomMargin), BottomRight_p2);
           path.lineTo(BottomLeft_p1);
           path.cubicTo(BottomLeft_p1, QPoint(j + m_pLeftMargin , this->height() - j - m_pBottomMargin),  BottomLeft_p2);
           path.lineTo(topLeft_p1);

           switch(i)
           {
           case 0:
               color.setAlpha(80);
               break;
           case 1:
               color.setAlpha(0);
               break;
           case 2:
               color.setAlpha(0);
               break;
           case 3:
               color.setAlpha(0);
               break;
           case 4:
               color.setAlpha(0);
               break;
           case 5:
               color.setAlpha(0);
               break;
           default:
               break;
           }
           QPen pen;
           pen.setColor(color);
           pen.setStyle(Qt::SolidLine);
           pen.setCapStyle(Qt::RoundCap);
           pen.setJoinStyle(Qt::RoundJoin);
           painter.setRenderHint(QPainter::Antialiasing);
           painter.setPen(pen);
           if (i == 0) {
               if (this->isChecked() && m_pCheckedColor.isValid()) {
                   painter.fillRect(this->rect(), QBrush(m_pCheckedColor));
               }else if (m_pMouseHover && m_pHoverColor.isValid())
                   painter.setBrush(QBrush(m_pHoverColor));
               else if (m_pBackgroundColor.isValid()) {
                   painter.setBrush(QBrush(m_pBackgroundColor));
               }
           }else {
               painter.setBrush(QBrush());
           }
           painter.drawPath(path);
       }

       if (!m_pIcon.isNull()) {
           painter.drawPixmap((this->width() - m_pIconSize.width())/2,
                              (this->height() - m_pIconSize.height())/2,
                              m_pIconSize.width(), m_pIconSize.height(), m_pIcon);
       }
   }

private:
   int m_pBorder;
   int m_pLeftMargin;
   int m_pTopMargin;
   int m_pRightMargin;
   int m_pBottomMargin;
   int m_pRadiusTopLeft;
   int m_pRadiusTopRight;
   int m_pRadiusBottomLeft;
   int m_pRadiusBottomRight;
   bool m_pMouseHover;
   QColor m_pBackgroundColor;
   QPixmap m_pIcon;
   QSize m_pIconSize;
   QColor m_pHoverColor;
   QColor m_pCheckedColor;
};

class DB_CustomPushButton_10 : public DB_CustomPushButton
{
    /* icon和文本垂直布局 */
    Q_OBJECT
public:
    DB_CustomPushButton_10(QWidget *parent = nullptr) : DB_CustomPushButton(parent) {
        this->setAutoFillBackground(true);
        this->installEventFilter(this);
        m_pMouseEnter = false;
        m_pRadius = Public_Function::getScaleSize(10);
        m_pTextColor = QColor(102, 102, 102);
        m_pCheckedTextColor = QColor(20, 134, 250);
        m_pHoverColor = QColor(238, 238, 238);
        m_pCheckedBorderColor = QColor();
        this->initWidget();

        connect(this, &DB_CustomPushButton_10::toggled, [=](){
            if (this->isChecked()) {
                if (!m_pCheckedIcon.isNull()) {
                    m_pLabelIcon->setPixmap(m_pCheckedIcon);
                }
                if (m_pCheckedTextColor.isValid()) {
                    m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                                .arg(m_pCheckedTextColor.red()).arg(m_pCheckedTextColor.green())
                                                .arg(m_pCheckedTextColor.blue()).arg(m_pCheckedTextColor.alpha()));
                }
            }else {
                if (!m_pIcon.isNull()) {
                    m_pLabelIcon->setPixmap(m_pIcon);
                    m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                                .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                                .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
                }

            }
        });
    }

    void mSetIcon(const QPixmap &pixmap) {
        m_pIcon = pixmap;
        m_pLabelIcon->setPixmap(pixmap);
    }

    void mSetIconSize(const QSize &size) {
        m_pLabelIcon->setFixedSize(size);
    }

    void mSetCheckedTextColor(const QColor &color) {
        m_pCheckedTextColor = color;
        if (this->isChecked())
            m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                        .arg(m_pCheckedTextColor.red()).arg(m_pCheckedTextColor.green())
                                        .arg(m_pCheckedTextColor.blue()).arg(m_pCheckedTextColor.alpha()));
    }

    void mSetText(const QString &str) {
        m_pLabelText->setText(str);
    }

    void mSetTextColor(const QColor &color) {
        m_pTextColor = color;
        m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                    .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                    .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
    }

    void mSetFont(const QFont &font) {
        m_pLabelText->setFont(font);
    }

    void mSetCheckedIcon(const QPixmap &pixmap) {
        m_pCheckedIcon = pixmap;
        if (this->isChecked())
            m_pLabelIcon->setPixmap(m_pCheckedIcon);
    }

    void mSetCheckedBGColor(const QColor &color) {
        m_pCheckedBGColor = color;
    }

    void mSetRadius(int radius) {
        m_pRadius = radius;
    }

    void mSetCheckedBorderColor(const QColor &color) {
        m_pCheckedBorderColor = color;
    }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::Enter) {
            m_pMouseEnter = true;
            update();
        }else if (event->type() == QEvent::Leave) {
            m_pMouseEnter = false;
            update();
        }else if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (this->rect().contains(mouseEvent->pos()) &&
                    mouseEvent->button() == Qt::LeftButton &&
                    this->isChecked())
                emit checkedClicked();
        }
        return DB_CustomPushButton::eventFilter(watched, event);
    }

protected:
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        if (this->m_pCheckedBGColor.isValid() && this->isChecked()) {
            QPainterPath path = Public_Function::getRoundRectPath(this->rect(), m_pRadius);
            painter.setPen(QPen(QBrush(m_pCheckedBGColor), Public_Function::getScaleSize(3)));
            painter.setBrush(QBrush(m_pCheckedBGColor));
            painter.drawPath(path);
        }else
            painter.fillRect(this->rect(), QBrush(Qt::transparent));

        QPainterPath path;
        if (m_pCheckedBorderColor.isValid() && this->isChecked()) {
            path = Public_Function::getRoundRectPath(this->rect(), m_pRadius);
            painter.setPen(QPen(QBrush(m_pCheckedBorderColor), Public_Function::getScaleSize(3)));
            painter.setBrush(QBrush());
        }else if (m_pMouseEnter && !this->isChecked()) {
            path = Public_Function::getRoundRectPath(this->rect(), m_pRadius);
            painter.setPen(QPen(m_pHoverColor));
            painter.setBrush(m_pHoverColor);
        }
        painter.drawPath(path);
    }

private:
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
    QPixmap m_pIcon;
    QPixmap m_pCheckedIcon;
    QColor m_pCheckedTextColor;
    QColor m_pTextColor;
    QColor m_pHoverColor;
    QColor m_pCheckedBGColor;
    QVBoxLayout *m_pLayout;
    QColor m_pCheckedBorderColor;
    int m_pRadius;
    bool m_pMouseEnter;

    void initWidget() {
       m_pLayout = new QVBoxLayout(this);
       m_pLayout->setContentsMargins(0, 0, 0, Public_Function::getScaleSize(4));
       m_pLayout->setSpacing(0);

       m_pLabelIcon = new QLabel(this);
       m_pLabelIcon->setScaledContents(true);
       m_pLayout->addWidget(m_pLabelIcon, 0, Qt::AlignCenter);

       m_pLabelText = new QLabel(this);
       m_pLabelText->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                                   .arg(m_pTextColor.red()).arg(m_pTextColor.green())
                                   .arg(m_pTextColor.blue()).arg(m_pTextColor.alpha()));
       m_pLabelText->setFont(Public_Function::getFont(14));
       m_pLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
       m_pLayout->addWidget(m_pLabelText, 0, Qt::AlignCenter);
    }

signals:
    void checkedClicked();
};

class DB_CustomPushButton_12 : public DB_CustomPushButton
{
    Q_OBJECT
public:
    DB_CustomPushButton_12(QWidget *parent = nullptr) : DB_CustomPushButton(parent)
    {
        m_pMouseEnter = false;
        m_pValue = 0;
    }

    void mSetRoundSize(const QSize &size) {
        m_pRoundSize = size;
    }

    void mSetValue(int value) {
        m_pValue = value;
    }

    inline int mGetValue() { return m_pValue; }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::Enter) {
            m_pMouseEnter = true;
            update();
        }else if (event->type() == QEvent::Leave) {
            m_pMouseEnter = false;
            update();
        }
        return DB_CustomPushButton::eventFilter(watched, event);
    }

protected:
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(this->rect(), QBrush(Qt::transparent));
        if (this->isChecked()) {
            painter.setPen(QPen(QBrush(QColor(20, 134, 250)), Public_Function::getScaleSize(2)));
            painter.setBrush(QBrush());
            painter.drawEllipse(this->rect().center(), this->width()/2 - Public_Function::getScaleSize(2),
                                this->height()/2 - Public_Function::getScaleSize(2));
        }else {
            if (m_pMouseEnter)  {
                painter.setPen(QPen(QBrush(QColor(238, 238, 238)), Public_Function::getScaleSize(2)));
                painter.setBrush(QBrush(QColor(238, 238, 238)));
                painter.drawEllipse(this->rect().center(), this->width()/2 - Public_Function::getScaleSize(2),
                                    this->height()/2 - Public_Function::getScaleSize(2));
            }
        }
        painter.setPen(QPen(QColor(136, 136, 136)));
        painter.setBrush(QBrush(QColor(136, 136, 136)));
        painter.drawEllipse(this->rect().center(), m_pRoundSize.width()/2, m_pRoundSize.height()/2);
    }

private:
    QSize m_pRoundSize;
    bool m_pMouseEnter;
    int m_pValue;
};

class DB_CustomPushButton_13 : public DB_CustomPushButton
{
    Q_OBJECT
public:
    DB_CustomPushButton_13(QWidget *parent = nullptr) : DB_CustomPushButton(parent)
    {
        m_pMouseEnter = false;
    }

    void mSetIconColor(const QColor &color) {
        m_pIconColor = color;
    }

    void mSetIconSize(const QSize &size) {
        m_pIconSize = size;
    }

    inline QColor mGetColor() { return m_pIconColor; }

    bool eventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::Enter) {
            m_pMouseEnter = true;
            update();
        }else if (event->type() == QEvent::Leave) {
            m_pMouseEnter = false;
            update();
        }
        return DB_CustomPushButton::eventFilter(watched, event);
    }

protected:
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(this->rect(), QBrush(Qt::transparent));
        if (this->isChecked()) {
            int radius = Public_Function::getScaleSize(12);
            QPainterPath path = Public_Function::getRoundRectPath(this->rect(), radius);
            painter.setPen(QPen(QBrush(QColor(20, 134, 250)), Public_Function::getScaleSize(2)));
            painter.setBrush(QBrush());
            painter.drawPath(path);
        }else {
            if (m_pMouseEnter) {
                int radius = Public_Function::getScaleSize(12);
                QPainterPath path = Public_Function::getRoundRectPath(this->rect(), radius);
                painter.setPen(QPen(QColor(238, 238, 238)));
                painter.setBrush(QBrush(QColor(238, 238, 238)));
                painter.drawPath(path);
            }
        }

        if (m_pIconColor.isValid()) {
            if (QColor(Qt::white) == m_pIconColor ||
                    QColor(Qt::transparent) == m_pIconColor) {
                painter.setPen(QPen(QColor(224, 224, 224),Public_Function::getScaleSize(2)));
            }else
                painter.setPen(QPen(m_pIconColor));
            if (QColor(Qt::transparent) == m_pIconColor)
                painter.setBrush(QBrush(Qt::white));
            else
                painter.setBrush(QBrush(m_pIconColor));
            QRectF iconRect =  QRectF((this->width() - m_pIconSize.width())/2.0, (this->height() - m_pIconSize.height())/2.0,
                                     m_pIconSize.width(), m_pIconSize.height());
            int radius = Public_Function::getScaleSize(5);
            QPainterPath path = Public_Function::getRoundRectPath(iconRect, radius);
            painter.drawPath(path);

            if (QColor(Qt::transparent) == m_pIconColor) {
                painter.setPen(QPen(QBrush(Qt::red), Public_Function::getScaleSize(2)));
                painter.drawLine(QPointF(path.boundingRect().topRight().x() - Public_Function::getScaleSize(2),
                                         path.boundingRect().topRight().y() + Public_Function::getScaleSize(2)),
                                 QPointF(path.boundingRect().bottomLeft().x() + Public_Function::getScaleSize(2),
                                        path.boundingRect().bottomLeft().y() - Public_Function::getScaleSize(2)));
            }
        }
    }

private:
    QColor m_pIconColor;
    QSize m_pIconSize;
    bool m_pMouseEnter;
};


class DB_CustomPushButton_16 : public QPushButton
{
    Q_OBJECT
public:
    DB_CustomPushButton_16(QString st,QPixmap pix,QWidget *parent =nullptr) :QPushButton(parent),pixmap(pix),str(st){
        this->setFixedSize(Public_Function::getScaleSize(60,70));
        this->setCheckable(true);
    }
    virtual ~DB_CustomPushButton_16() {}

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setPen(Qt::NoPen);
        if(isChecked())
        {
            painter.setBrush(QColor(20,134,250));
        }
        else if(setcolor ==2)
        {
            painter.setBrush(QColor(238,238,238));
        }
        else
        {
            painter.setBrush(Qt::NoBrush);
        }
        painter.drawPath(Public_Function::getRoundRectPath(this->rect(),Public_Function::getScaleSize(10)));
        painter.drawPixmap(Public_Function::getScaleSize(10),Public_Function::getScaleSize(3),Public_Function::getScaleSize(40),Public_Function::getScaleSize(40),pixmap);
        painter.setPen(QColor(102,102,102));
        painter.setFont(Public_Function::getFont(12));
        painter.drawText(QRect(QPoint(Public_Function::getScaleSize(0),Public_Function::getScaleSize(50)),
                               QPoint(Public_Function::getScaleSize(60),Public_Function::getScaleSize(65))),Qt::AlignCenter,str);
    }

    void mousePressEvent(QMouseEvent *e)
    {

        if(e->button() == Qt::LeftButton)
        {
            this->setChecked(true);
        }
        update();
        return QPushButton::mousePressEvent(e);
    }

    void enterEvent(QEvent *)
    {
        setcolor =2;
        update();
    }

    void leaveEvent(QEvent *)
    {
        setcolor =3;
        update();
    }

private:
    QPixmap pixmap = QPixmap();
    QString str;
    int setcolor =0;
};

#endif // DB_CUSTOMPUSHBUTTON_H
