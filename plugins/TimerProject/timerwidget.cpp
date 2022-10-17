#include "timerwidget.h"
#include "Public/public_function.h"
#include <QBoxLayout>
#include <QPainter>
#include <QThread>
#include <QDebug>

TimerWidget::TimerWidget(QWidget *parent) : QWidget(parent)
{
    initCustom();
    initconnect();
    this->setAutoFillBackground(false);
}

void TimerWidget::initCustom()
{
    timerwork = new TimerWork;
    thread = new QThread(this);
    timerwork->moveToThread(thread);

    interfaceLab = new QLabel(this);
    interfaceLab->setFixedSize(Public_Function::getScaleSize(228,228));

    timerLab = new QLabel(this);
    timerLab->setFixedSize(Public_Function::getScaleSize(112),Public_Function::getScaleSize(26));
    timerLab->setFont(Public_Function::getFont(24));
    timerLab->setStyleSheet("font-family: Arial Bold;color: #444444;");
    timerLab->setText("00:00:00");
    timerLab->setAlignment(Qt::AlignCenter);

    maxBtn = new QPushButton(this);
    maxBtn->setFixedSize(Public_Function::getScaleSize(52,52));
    maxBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi1.png"));
    maxBtn->setIconSize(QSize(Public_Function::getScaleSize(54,54)));
    maxBtn->setFlat(true);
    maxBtn->setObjectName("max");
    maxBtn->setStyleSheet("border-style:falt");

    startBtn = new QPushButton(this);
    startBtn->setFixedSize(Public_Function::getScaleSize(54,54));
    startBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi6.png"));
    startBtn->setIconSize(QSize(Public_Function::getScaleSize(54,54)));
    startBtn->setFlat(true);
    startBtn->setObjectName("start");
    startBtn->setStyleSheet("border-style:falt");

    clearBtn = new QPushButton(this);
    clearBtn->hide();
    clearBtn->setFixedSize(Public_Function::getScaleSize(54),Public_Function::getScaleSize(54));
    clearBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi4b.png"));
    clearBtn->setIconSize(QSize(Public_Function::getScaleSize(54,54)));
    clearBtn->setFlat(true);
    clearBtn->setStyleSheet("border-style:falt");

    hlayout1 = new QHBoxLayout;
    hlayout1->addStretch(0);
    hlayout1->addWidget(timerLab);
    hlayout1->addStretch(0);

    hlayout2 = new QHBoxLayout;
    hlayout2->addStretch();
    hlayout2->addWidget(maxBtn);
    hlayout2->addWidget(startBtn);
    hlayout2->addWidget(clearBtn);
    hlayout2->addStretch();
    hlayout2->setSpacing(Public_Function::getScaleSize(39));

    vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0,0,0,0);
    vlayout->addWidget(interfaceLab);
    vlayout->addStretch(1);
    vlayout->addLayout(hlayout1);
    vlayout->addStretch(1);
    vlayout->addLayout(hlayout2);
    timerLab->show();

}

void TimerWidget::initconnect()
{
    connect(maxBtn,&QPushButton::clicked,this,&TimerWidget::maxBtnslot);
    connect(startBtn,&QPushButton::clicked,this,&TimerWidget::startBtnslot);
    connect(clearBtn,&QPushButton::clicked,this,&TimerWidget::clearBtnslot);
    connect(this,&TimerWidget::sendLabel,timerwork,&TimerWork::getDrawLab);
    connect(this,&TimerWidget::sendShowLabel,timerwork,&TimerWork::drawClock);
    connect(this,&TimerWidget::sendTimerStart,timerwork,&TimerWork::startTimer);
    connect(this,&TimerWidget::sendTimerStop,timerwork,&TimerWork::stopTimer);
    connect(this,&TimerWidget::sendTimerClear,timerwork,&TimerWork::clearTimer);
}

void TimerWidget::setShowTime()
{
    if(this->width() ==Public_Function::getScaleSize(590))
    {
        timerLab->setFixedSize(Public_Function::getScaleSize(333,68));
        timerLab->setFont(Public_Function::getFont(66));
        timerLab->setStyleSheet("font-family: Arial Bold;text-align: center;color: #444444;");
    }
    else
    {
        timerLab->setFixedSize(Public_Function::getScaleSize(112,26));
        timerLab->setFont(Public_Function::getFont(24));
        timerLab->setStyleSheet("font-family: Arial Bold;text-align: center;color: #444444;");
    }
}

void TimerWidget::killThread()
{
    thread->exit();
    thread->quit();
    thread->wait();
}

void TimerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(flage ==1)
    {
        QPixmap pix(this->width(),this->width());
        pix.fill(Qt::white);
        QPainter painter(&pix);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
        QRect rect = QRect(0,0,this->width(),this->width());
        if(this->width() == Public_Function::getScaleSize(590))
        {
            painter.drawPixmap(rect,QPixmap(":/images/TimerPixmap/daojishi2@2x.png"));
        }
        else
        {
            painter.drawPixmap(rect,QPixmap(":/images/TimerPixmap/daojishi@2x.png"));
        }
        painter.translate(rect.center());
        painter.save();
        painter.setPen(QPen(Qt::black,3,Qt::SolidLine,Qt::RoundCap));
        painter.rotate(0);
        if(this->width() == Public_Function::getScaleSize(590))
        {
            QRect fenzhen =QRect(-4,-69,8,69);
            painter.drawPixmap(fenzhen,QPixmap(":/images/TimerPixmap/fenzhen@2x.png"));
        }
        else
        {
            painter.drawLine(0,0,0,-rect.height()/9);
        }
        painter.restore();
        painter.save();
        painter.rotate(0);
        if(this->width() == Public_Function::getScaleSize(590))
        {
            painter.setPen(QPen(Qt::red,4));
            painter.drawLine(0,1*rect.width()/23,0,-rect.height()/2 +2);
            painter.setPen(QPen(Qt::red,4));
            painter.setBrush(Qt::white);
            painter.drawEllipse(QRect(-8,-8,16,16));
        }
        else
        {
            painter.setPen(QPen(Qt::red,2));
            painter.drawLine(0,1*rect.width()/23,0,-rect.height()/2 +2);
            painter.setPen(QPen(Qt::red,2));
            painter.setBrush(Qt::white);
            painter.drawEllipse(QRect(-4,-4,8,8));
        }
        painter.restore();
        interfaceLab->setPixmap(pix);
    }
}

void TimerWidget::maxBtnslot()
{
    if(maxBtn->objectName() == "max")
    {
        emit sendMessage("max");
        interfaceLab->setFixedSize(Public_Function::getScaleSize(590,590));
        emit sendLabel(interfaceLab,timerLab);
        setShowTime();
        maxBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi5.png"));
        maxBtn->setIconSize(Public_Function::getScaleSize(54,54));
        maxBtn->setFlat(true);
        maxBtn->setObjectName("min");
    }
    else if(maxBtn->objectName() == "min")
    {
        emit sendMessage("min");
        interfaceLab->setFixedSize(Public_Function::getScaleSize(228,228));
        emit sendLabel(interfaceLab,timerLab);
        setShowTime();
        maxBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi1.png"));
        maxBtn->setIconSize(Public_Function::getScaleSize(54,54));
        maxBtn->setFlat(true);
        maxBtn->setObjectName("max");
   }
}

void TimerWidget::startBtnslot()
{
    thread->start();
    flage =2;
    if(maxBtn->objectName() == "max")
    {
        if(startBtn->objectName() == "start")
        {
            emit sendTimerStart();
            emit sendLabel(interfaceLab,timerLab);
            startBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi3.png"));
            startBtn->setIconSize(Public_Function::getScaleSize(54,54));
            startBtn->setFlat(true);
            startBtn->setObjectName("stop");
            clearBtn->show();
        }
        else if(startBtn->objectName() == "stop")
        {
            emit sendTimerStop();
            QIcon starticon(":/images/TimerPixmap/daojishi6.png");
            startBtn->setIcon(starticon);
            startBtn->setIconSize(Public_Function::getScaleSize(54,54));
            startBtn->setFlat(true);
            startBtn->setObjectName("start");
            clearBtn->show();
        }
    }
    else if(maxBtn->objectName() == "min")
    {
        if(startBtn->objectName() == "start")
        {
            emit sendTimerStart();
            QIcon starticon(":/images/TimerPixmap/daojishi3.png");
            startBtn->setIcon(starticon);
            startBtn->setIconSize(Public_Function::getScaleSize(54,54));
            startBtn->setFlat(true);
            startBtn->setObjectName("stop");
            clearBtn->show();
        }
        else if(startBtn->objectName() == "stop")
        {
            emit sendTimerStop();
            QIcon starticon(":/images/TimerPixmap/daojishi6.png");
            startBtn->setIcon(starticon);
            startBtn->setIconSize(Public_Function::getScaleSize(54,54));
            startBtn->setFlat(true);
            startBtn->setObjectName("start");
            clearBtn->show();
        }
    }
}

void TimerWidget::clearBtnslot()
{
    if(startBtn->objectName() == "stop")
    {
        startBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi6.png"));
        startBtn->setIconSize(Public_Function::getScaleSize(54,54));
        startBtn->setFlat(true);
        startBtn->setObjectName("start");
        emit sendTimerClear();
        timerLab->setText("00:00:00");
    }
    else if(startBtn->objectName() == "start")
    {
        emit sendTimerClear();
        timerLab->setText("00:00:00");
    }
}
