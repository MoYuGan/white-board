#include "custom.h"
#include "Public/public_function.h"
#include <QPainter>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include "screenshot.h"
/*************自定义保存取消按钮**************/
mPushButton_1::mPushButton_1(QWidget *parent) : QPushButton(parent)
{
    this->setCheckable(true);
}

void mPushButton_1::setTextAndPixmap(const QString st, const QPixmap pix)
{
    str =st;
    pixmap = pix;
    update();
}

void mPushButton_1::setLocalText(const QString& txt)
{
     str = txt;
     update();
}

void mPushButton_1::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.drawPath(Public_Function::getRoundRectPath(this->rect(),Public_Function::getScaleSize(10)));
    painter.drawPixmap(Public_Function::getScaleSize(10),Public_Function::getScaleSize(3),Public_Function::getScaleSize(40),
                       Public_Function::getScaleSize(40),pixmap);
    painter.setPen(QColor(102,102,102));
    painter.setFont(Public_Function::getFont(12));
    painter.drawText(QRect(QPoint(Public_Function::getScaleSize(0),Public_Function::getScaleSize(50)),
                           QPoint(Public_Function::getScaleSize(60),Public_Function::getScaleSize(65))),Qt::AlignCenter,str);
}

/*************自定义各种图标**************/
Label_1::Label_1(QPixmap pix, QString text, QWidget *parent):QLabel(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(52,68));
    this->installEventFilter(this);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    pixmap_Lab = new QLabel(this);
    pixmap_Lab->setFixedSize(Public_Function::getScaleSize(52,52));
    pixmap_Lab->setScaledContents(true);
    pixmap_Lab->setPixmap(pix);
    text_Lab = new QLabel(text,this);
    text_Lab->setFixedSize(Public_Function::getScaleSize(52,16));
    text_Lab->setFont(Public_Function::getFont(12));
    vlayout->addWidget(pixmap_Lab);
    vlayout->addWidget(text_Lab);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
}

void Label_1::changePixmapAndText(QPixmap pix, QString str)
{
    pixmap_Lab->setPixmap(pix);
    text_Lab->setText(str);
}

void Label_1::setLocalText(const QString& txt)
{
    text_Lab->setText(txt);

}

bool Label_1::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
       return true;
    }
    else if(event->type() == QEvent::TouchBegin)
    {
       return true;
    }
    return QLabel::eventFilter(watched,event);
}

