#include "mylock.h"
#include <QPainter>
#include <QDesktopWidget>
#include <QApplication>
#include "Public/public_function.h"
#include <QBoxLayout>
#include <QHBoxLayout>
MyLock::MyLock(QWidget *parent) : QWidget(parent)
{
    QDesktopWidget *desktop = QApplication::desktop();
    this->setGeometry(desktop->rect());
    resize();
}

void MyLock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawPixmap(this->rect(),*pixmap_background);
}

void MyLock::resize()
{
    unlock = new QPushButton(tr("解锁"),this);
    unlock->setFont(Public_Function::getFont(16));
    unlock->setFixedSize(Public_Function::getScaleSize(QSize(100,42)));
    unlock->setStyleSheet(QString("background-color: #ffffff;border-radius: %1px;"
                                  "font-family: Microsoft YaHei Bold;color: #1486fa;").arg(Public_Function::getScaleSize(4)));
    connect(unlock,&QPushButton::clicked,[=](){
        this->close();
        this->deleteLater();
    });
    label_text = new QLabel(tr("安道白板锁屏中"),this);
    label_text->setFont(Public_Function::getFont(18));
    label_text->setStyleSheet("font-family: Microsoft YaHei Regular;color: #ffffff;");

    label_icon = new QLabel(this);
    label_icon->setScaledContents(true);
    label_icon->setFixedSize(Public_Function::getScaleSize(129,129));
    label_icon->setPixmap(QPixmap(":/images/LockPixmap/icon@2x.png").scaled(label_icon->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    pixmap_background = new QPixmap(":/images/LockPixmap/bg@2x.png");
    QVBoxLayout *vlayout  = new QVBoxLayout(this);
    QHBoxLayout  *layout1 = new QHBoxLayout;
    QHBoxLayout  *layout2 = new QHBoxLayout;
    QHBoxLayout  *layout3 = new QHBoxLayout;
    layout1->addWidget(label_icon,0,Qt::AlignCenter);
    layout2->addWidget(label_text,0,Qt::AlignCenter);
    layout3->addWidget(unlock,0,Qt::AlignCenter);
    vlayout->addStretch(0);
    vlayout->addLayout(layout1);
    vlayout->addLayout(layout2);
    vlayout->addLayout(layout3);
    vlayout->addStretch(0);
    layout2->setContentsMargins(Public_Function::getScaleSize(0),Public_Function::getScaleSize(0),Public_Function::getScaleSize(0),Public_Function::getScaleSize(100));
//    vlayout->setContentsMargins(Public_Function::getScaleSize(0),Public_Function::getScaleSize(450),Public_Function::getScaleSize(0),Public_Function::getScaleSize(300));
}
