#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Public/public_function.h"
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include "Custom/PushButton/pushbutton_basic.h"

class MsgWidget : public QWidget
{
    Q_OBJECT
public:
    MsgWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        this->initWidget();
        this->resize();
        //this->installEventFilter(this);
    }

    QString getVersion()
    {
        return m_pVersion->text();
    }
    void resize() {
        QSize size = Public_Function::getScaleSize(QSize(1084, 682));
        this->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(42, 42));
        m_pBtnClose->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(263, 43));
        m_pLogo->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(115, 22));
        m_pLabel->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(306, 30));
        m_pCompanyText->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(306, 30));
        m_pCompany->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(453, 30));
        m_pPlaceText->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(453, 30));
        m_pPlace->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(100, 30));
        m_pPhoneNumberText->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(100, 30));
        m_pPhoneNumber->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(165, 30));
        m_pWebText->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(165, 30));
        m_pWeb->setFixedSize(size);
        size = Public_Function::getScaleSize(QSize(300, 17));
        m_pVersion->setFixedSize(size);

        QFont font = Public_Function::getFont(20);
        m_pLabel->setFont(font);
        m_pVersion->setFont(font);
        font = Public_Function::getFont(18);
        m_pCompanyText->setFont(font);
        m_pPlaceText->setFont(font);
        m_pPhoneNumberText->setFont(font);
        m_pWebText->setFont(font);
        font = Public_Function::getFont(14);
        m_pCompany->setFont(font);
        m_pPlace->setFont(font);
        m_pPhoneNumber->setFont(font);
        m_pWeb->setFont(font);

        int spacing = 50;
        int labelHeight = 30;
        int showX, showY;
        m_pBtnClose->move(Public_Function::getScaleSize(979),
                          Public_Function::getScaleSize(63));
        showX = 83;
        m_pLogo->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(83));
        m_pLabel->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(155));
        showY = 219;
        m_pCompanyText->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(showY));
        m_pCompany->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(showY + labelHeight));
        m_pPlaceText->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(showY + labelHeight*2 + spacing));
        m_pPlace->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(showY + labelHeight*3 + spacing));
        m_pPhoneNumberText->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(showY + labelHeight*4 + spacing*2));
        m_pPhoneNumber->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(showY + labelHeight*5 + spacing*2));
        m_pWebText->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(showY + labelHeight*6 + spacing*3));
        m_pWeb->move(Public_Function::getScaleSize(showX),
                          Public_Function::getScaleSize(showY + labelHeight*7 + spacing*3));
        m_pVersion->move(m_pLogo->x() + m_pLogo->width() + Public_Function::getScaleSize(50),
                            m_pLogo->y() + m_pLogo->height() - m_pVersion->height());
    }

    void setBackgroundPixmap(const QString &fileName) {
        m_pBackgroundFilePath = fileName;
        update();
    }

//    bool eventFilter(QObject *watched, QEvent *event) {
//        if (event->type() == QMouseEvent::MouseButtonPress) {
//            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
//            if (mouseEvent->button() == Qt::LeftButton) {
//                m_pMousePressed = true;
//                m_pMousePressedPoint = mouseEvent->pos();
//            }
//        }else if (event->type() == QMouseEvent::MouseMove) {
//            if (m_pMousePressed) {
//                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
//                QPointF pos = mouseEvent->globalPos();
//                int X = pos.x() - m_pMousePressedPoint.x();
//                int Y = pos.y() - m_pMousePressedPoint.y();
//                QWidget *parent = (QWidget *)this->parent();
//                if (parent != nullptr) {
//                    X = X > 0 ? (X + this->width() > parent->width() ? parent->width() - this->width() : X) : 0;
//                    Y = Y > 0 ? (Y + this->height() > parent->height() ? parent->height() - this->height() : Y) : 0;
//                    this->move(X, Y);
//                }
//            }
//        }else if (event->type() == QMouseEvent::MouseButtonRelease) {
//            m_pMousePressed = false;
//        }
//        return QWidget::eventFilter(watched, event);
//    }

protected:
    void paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);
        QPainter painter(this);
        QPixmap pixmap;
        pixmap.load(m_pBackgroundFilePath);
        painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
    }

private:
    QString m_pBackgroundFilePath;
    PushButton_Basic *m_pBtnClose;
    QLabel *m_pLogo;
    QLabel *m_pLabel;
    QLabel *m_pCompanyText;
    QLabel *m_pCompany;
    QLabel *m_pPlaceText;
    QLabel *m_pPlace;
    QLabel *m_pPhoneNumberText;
    QLabel *m_pPhoneNumber;
    QLabel *m_pWebText;
    QLabel *m_pWeb;
    QLabel *m_pVersion;
    bool m_pMousePressed = false;
    QPoint m_pMousePressedPoint;

    void initWidget() {
        m_pBtnClose = new PushButton_Basic(this);
        connect(m_pBtnClose, &PushButton_Basic::clicked,this, [=](){ emit this->closed(); });
        m_pBtnClose->setStyleSheet("border-image: url(':/images/other/guanbi2.png');");
        m_pLogo = new QLabel(this);
        m_pLogo->setScaledContents(true);
        m_pLogo->setPixmap(QPixmap(":/images/main/menu/安道电子白板@2x.png"));
        m_pLogo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pLabel = new QLabel(this);
        m_pLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pLabel->setText(tr("ABOUT US"));
        m_pCompanyText = new QLabel(this);
        m_pCompanyText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pCompanyText->setText(tr("版权所有："));
        m_pCompany = new QLabel(this);
        m_pCompany->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pCompany->setText(tr("安道云股份有限公司 鄂ICP备18014569号-1"));
        m_pPlaceText = new QLabel(this);
        m_pPlaceText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pPlaceText->setText(tr("联系地址："));
        m_pPlace = new QLabel(this);
        m_pPlace->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pPlace->setText(tr("东莞市松山湖高新技术产业开发区国际金融创新园11A栋"));
        m_pPhoneNumberText = new QLabel(this);
        m_pPhoneNumberText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pPhoneNumberText->setText(tr("联系电话："));
        m_pPhoneNumber = new QLabel(this);
        m_pPhoneNumber->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pPhoneNumber->setText(tr("400-632-8880"));
        m_pWebText = new QLabel(this);
        m_pWebText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pWebText->setText(tr("官方网址"));
        m_pWeb = new QLabel(this);
        m_pWeb->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pWeb->setText(tr("www.amdolla.com.cn"));
        m_pVersion = new QLabel(this);
        m_pVersion->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        //m_pVersion->setText(tr("V1.3.9-build.22.06.06.01"));
        m_pVersion->setText(tr("V1.3.9"));

        QColor color = QColor(68, 68, 68);
        m_pCompanyText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pPlaceText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pPhoneNumberText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pWebText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        color = QColor(136, 136, 136);
        m_pLabel->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pCompany->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pPlace->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pPhoneNumber->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pWeb->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pVersion->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
    }

signals:
    void closed();
};

class AboutUs: public QWidget
{
    Q_OBJECT
public:
    AboutUs(QWidget *parent = nullptr) : QWidget(parent)
    {
        this->initWidget();
    }

    void show() {
        QWidget::show();
        this->raise();
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
        m_pMsgWidget->move(QPoint((this->width() - m_pMsgWidget->width())/2,
                                  (this->height() - m_pMsgWidget->height())/2));
    }


private:
    MsgWidget *m_pMsgWidget;

    void initWidget() {
//        QHBoxLayout *layout = new QHBoxLayout(this);
//        layout->setContentsMargins(0, 0, 0, 0);
//        layout->setSpacing(0);

        m_pMsgWidget = new MsgWidget(this);
        m_pMsgWidget->setBackgroundPixmap(":/images/other/beijing.png");
        connect(m_pMsgWidget, &MsgWidget::closed, [=](){
            this->deleteLater();
        });
    }
};

#endif // ABOUTUS_H
