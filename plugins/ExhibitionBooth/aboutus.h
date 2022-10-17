#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ShareStyle/db_scale.h"
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include "Custom/PushButton/custompushbutton.h"

class MsgWidget : public QWidget
{
    Q_OBJECT
public:
    MsgWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        this->initWidget();
        this->resize();
    }

    void resize() {
        QSize size = DB_ApplicationScale::getScaleSize(QSize(1645, 963));
        this->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(42, 42));
        m_pBtnClose->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(463, 76));
        m_pLogo->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(145, 22));
        m_pLabel->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(306, 30));
        m_pCompanyText->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(306, 30));
        m_pCompany->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(453, 30));
        m_pPlaceText->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(453, 30));
        m_pPlace->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(100, 30));
        m_pPhoneNumberText->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(100, 30));
        m_pPhoneNumber->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(165, 30));
        m_pWebText->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(165, 30));
        m_pWeb->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(100, 30));
        m_pVersionText->setFixedSize(size);
        size = DB_ApplicationScale::getScaleSize(QSize(200, 30));
        m_pVersion->setFixedSize(size);

        QFont font = DB_ApplicationScale::getFont(24);
        m_pLabel->setFont(font);
        font = DB_ApplicationScale::getFont(18);
        m_pCompanyText->setFont(font);
        m_pPlaceText->setFont(font);
        m_pPhoneNumberText->setFont(font);
        m_pWebText->setFont(font);
        m_pVersionText->setFont(font);
        font = DB_ApplicationScale::getFont(14);
        m_pCompany->setFont(font);
        m_pPlace->setFont(font);
        m_pPhoneNumber->setFont(font);
        m_pWeb->setFont(font);
        m_pVersion->setFont(font);

        int spacing = 50;
        int labelHeight = 30;
        int showX, showY;
        m_pBtnClose->move(DB_ApplicationScale::getScaleSize(1529),
                          DB_ApplicationScale::getScaleSize(73));
        showX = 144;
        m_pLogo->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(131));
        m_pLabel->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(240));
        showY = 362;
        m_pCompanyText->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY));
        m_pCompany->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight));
        m_pPlaceText->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight*2 + spacing));
        m_pPlace->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight*3 + spacing));
        m_pPhoneNumberText->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight*4 + spacing*2));
        m_pPhoneNumber->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight*5 + spacing*2));
        m_pWebText->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight*6 + spacing*3));
        m_pWeb->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight*7 + spacing*3));
        m_pVersionText->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight*8 + spacing*4));
        m_pVersion->move(DB_ApplicationScale::getScaleSize(showX),
                          DB_ApplicationScale::getScaleSize(showY + labelHeight*9 + spacing*4));
    }

    void setBackgroundPixmap(const QString &fileName) {
        m_pBackgroundFilePath = fileName;
        update();
    }

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
    CustomPushButton *m_pBtnClose;
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
    QLabel *m_pVersionText;
    QLabel *m_pVersion;

    void initWidget() {
        m_pBtnClose = new CustomPushButton(this);
        connect(m_pBtnClose, &CustomPushButton::clicked, [=](){ emit this->closed(); });
        m_pBtnClose->setStyleSheet("border-image: url(':/images/guanbi2.png');");
        m_pLogo = new QLabel(this);
        m_pLogo->setScaledContents(true);
        m_pLogo->setPixmap(QPixmap(":/images/amdoxLogo.png"));
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
        m_pPlace->setText(tr("东莞市松山湖高新技术产业开发区研发5路2号宏远新智汇3栋313"));
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
        m_pVersionText = new QLabel(this);
        m_pVersionText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pVersionText->setText(tr("当前版本："));
        m_pVersion = new QLabel(this);
        m_pVersion->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pVersion->setText(tr("1.2.0-build21.09.18.01"));

        QColor color = QColor(68, 68, 68);
        m_pCompanyText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pPlaceText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pPhoneNumberText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pWebText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
                                .arg(color.green()).arg(color.blue()).arg(color.alpha()));
        m_pVersionText->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(color.red())
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
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        m_pMsgWidget = new MsgWidget(this);
        m_pMsgWidget->setBackgroundPixmap(":/images/beijing.png");
        connect(m_pMsgWidget, &MsgWidget::closed, [=](){
            this->deleteLater();
        });
    }
};

#endif // ABOUTUS_H
