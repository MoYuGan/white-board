#ifndef CUSTOMMBOX_H
#define CUSTOMMBOX_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "ShareStyle/db_scale.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Custom/PushButton/custompushbutton.h"

class CustomMBox : public QWidget
{
    Q_OBJECT
public:
    CustomMBox(const QString &title, const QString &text,
               const QString &leftText, const QString &rightText,
               QWidget *parent = nullptr) : QWidget(parent) ,
      m_pTitle(title), m_pText(text), m_pLeftText(leftText), m_pRightText(rightText)
    {
        this->initWidget();
        this->resize();
    }

    void resize() {
        QSize size = DB_ApplicationScale::getScaleSize(QSize(350, 200));
        m_pFrame->setFixedSize(size);
        m_pLabelTitle->setFixedHeight(DB_ApplicationScale::getScaleWidth(50));
        m_pLabelTitle->setContentsMargins(DB_ApplicationScale::getScaleWidth(10), 0, 0, 0);
        size = DB_ApplicationScale::getScaleSize(QSize(100, 40));
        m_pButtonLeft->setFixedSize(size);
        m_pButtonRight->setFixedSize(size);
        m_pLayoutBottom->setContentsMargins(0, 0,
                                    0, DB_ApplicationScale::getScaleWidth(20));

        QFont font = DB_ApplicationScale::getFont(18);
        m_pLabelTitle->setFont(font);
        m_pLabelText->setFont(font);
        font = DB_ApplicationScale::getFont(14);
        m_pButtonLeft->setFont(font);
        m_pButtonRight->setFont(font);
        m_pButtonLeft->setStyleSheet(QString("QPushButton{border: none;"
                                             "color: white;"
                                             "background-color: rgb(78,  155,  252);"
                                             "border-radius: %1px;}")
                                            .arg(DB_ApplicationScale::getScaleWidth(5)));
        m_pButtonRight->setStyleSheet(QString("QPushButton{border: none;"
                                             "color: white;"
                                             "background-color: rgb(78,  155,  252);"
                                             "border-radius: %1px;}")
                                            .arg(DB_ApplicationScale::getScaleWidth(5)));
        m_pFrame->setStyleSheet(QString("#%1{border: none;"
                                         "background: white;"
                                         "border-radius: %2px;}").arg(m_pFrame->objectName())
                                 .arg(DB_ApplicationScale::getScaleWidth(5)));
        m_pLabelTitle->setStyleSheet(QString("%1 QLabel{border-top-left-radius: %2px;"
                                               "border-top-right-radius: %2px;}").arg(m_pLabelTitle->styleSheet())
                                       .arg(DB_ApplicationScale::getScaleWidth(5)));
        QColor color = DB_ApplicationScale::getFontColor();
        m_pLabelText->setStyleSheet(QString("QLabel{"
                                            "color: rgba(%1, %2, %3, %4);}")
                                    .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
        m_pFrame->move(QPoint((this->width() - m_pFrame->width())/2,
                              (this->height() - m_pFrame->height())/2));
    }

private:
    QString m_pTitle;
    QString m_pText;
    QString m_pLeftText;
    QString m_pRightText;
    QLabel *m_pLabelTitle;
    QLabel *m_pLabelText;
    CustomPushButton *m_pButtonLeft;
    CustomPushButton *m_pButtonRight;
    QHBoxLayout *m_pLayoutBottom;
    QFrame *m_pFrame;

    void initWidget()
    {
        m_pFrame = new QFrame(this);
        m_pFrame->setObjectName("frame");
        QVBoxLayout *vlayout = new QVBoxLayout(m_pFrame);
        vlayout->setContentsMargins(0, 0, 0, 0);
        vlayout->setSpacing(0);

        m_pLabelTitle = new QLabel(this);
        m_pLabelTitle->setText(m_pTitle);
        m_pLabelTitle->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_pLabelTitle->setStyleSheet("QLabel{"
                                     "border: none;"
                                     "color: white;"
                                     "background-color: rgb(78,  155,  252);"
                                     "}");
        vlayout->addWidget(m_pLabelTitle);

        m_pLabelText = new QLabel(this);
        m_pLabelText->setText(m_pText);
        m_pLabelText->setAlignment(Qt::AlignCenter);
        m_pLabelText->setWordWrap(true);
        vlayout->addWidget(m_pLabelText, 1);

        m_pLayoutBottom = new QHBoxLayout;
        m_pLayoutBottom->setSpacing(0);
        m_pButtonLeft = new CustomPushButton(this);
        m_pButtonLeft->setText(m_pLeftText);
        m_pLayoutBottom->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
        m_pLayoutBottom->addWidget(m_pButtonLeft);
        m_pButtonRight = new CustomPushButton(this);
        m_pButtonRight->setText(m_pRightText);
        m_pLayoutBottom->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
        m_pLayoutBottom->addWidget(m_pButtonRight);
        m_pLayoutBottom->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
        vlayout->addLayout(m_pLayoutBottom);

        connect(m_pButtonLeft, &CustomPushButton::clicked, [=](){ emit mboxClosed(1); });
        connect(m_pButtonRight, &CustomPushButton::clicked, [=](){ emit mboxClosed(-1); });
    }

signals:
    void mboxClosed(int);
};

#endif // CUSTOMMBOX_H
