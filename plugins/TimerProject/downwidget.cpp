#include "downwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QDebug>
#include <QThread>

DownWidget::DownWidget(QWidget *parent) : QWidget(parent) , mIsChinese(true)
{
    initCustom();
    initConnect();
}


void DownWidget::initCustom()
{
    thread = new QThread(this);
    downwork = new DownWork;
    downwork->moveToThread(thread);

    hour_widget = new NumWidget(this);
    hour_widget->setFixedSize(Public_Function::getScaleSize(50,180));
    hour_widget->setRange(0,23);
    hour_widget->setCurrentVlaue(0);

    minute_widget = new NumWidget(this);
    minute_widget->setFixedSize(Public_Function::getScaleSize(50,180));
    minute_widget->setRange(0,59);
    minute_widget->setCurrentVlaue(4);

    second_widget = new NumWidget(this);
    second_widget->setFixedSize(Public_Function::getScaleSize(50,180));
    second_widget->setRange(0,59);
    second_widget->setCurrentVlaue(39);


    label1 = new QLabel(this);
    label1->setText(":");
    label1->setFixedSize(Public_Function::getScaleSize(40,170));
    label1->setFont(Public_Function::getFont(40));
    label1->setAlignment(Qt::AlignCenter);

    label2 = new QLabel(this);
    label2->setText(":");
    label2->setFixedSize(Public_Function::getScaleSize(40,170));
    label2->setFont(Public_Function::getFont(40));
    label2->setAlignment(Qt::AlignCenter);

    timertextLab = new QLabel(this);
    timertextLab->setFixedSize(Public_Function::getScaleSize(220,16));
    timertextLab->setFont(Public_Function::getFont(16));
    QString str;
    addText(str,1);
    timertextLab->setText(str);

    fillLab = new QLabel(this);
    fillLab->setFixedSize(Public_Function::getScaleSize(228,100));
    fillLab->hide();

    countLab = new QLabel(this);
    countLab->setFixedSize(Public_Function::getScaleSize(228,44));
    countLab->hide();

//    remainLab = new QLabel(this);
//    remainLab->setFixedSize(Public_Function::getScaleSize(100,32));
//    remainLab->setText(tr("剩余时间"));
//    remainLab->setFont(Public_Function::getFont(22));
//    remainLab->hide();

    maxBtn = new QPushButton(this);
    maxBtn->setFixedSize(Public_Function::getScaleSize(54,54));
    maxBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi1.png"));
    maxBtn->setIconSize(QSize(Public_Function::getScaleSize(54,54)));
    maxBtn->setFlat(true);
    maxBtn->setObjectName("max");
    maxBtn->setStyleSheet("border-style:falt");

    startBtn = new QPushButton(this);
    startBtn->setFixedSize(Public_Function::getScaleSize(54),Public_Function::getScaleSize(54));
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
//    hlayout1 = new QHBoxLayout;
//    hlayout1->addStretch(0);
//    hlayout1->addWidget(remainLab);
//    hlayout1->addStretch(0);

    hlayout2 = new QHBoxLayout;
    hlayout2->setSpacing(0);
    hlayout2->setContentsMargins(0,0,0,0);
    hlayout2->addWidget(hour_widget);
    hlayout2->addWidget(label1);
    hlayout2->addWidget(minute_widget);
    hlayout2->addWidget(label2);
    hlayout2->addWidget(second_widget);

    hlayout3 = new QHBoxLayout;
    hlayout3->addStretch(0);
    hlayout3->addWidget(countLab);
    hlayout3->addStretch(0);

    hlayout4 = new QHBoxLayout;
    hlayout4->addStretch(0);
    hlayout4->addWidget(timertextLab);
    hlayout4->addStretch(0);

    hlayout5 = new QHBoxLayout;
    hlayout5->addStretch(0);
    hlayout5->addWidget(maxBtn);
    hlayout5->addWidget(startBtn);
    hlayout5->addWidget(clearBtn);
    hlayout5->addStretch(0);
    hlayout5->setSpacing(Public_Function::getScaleSize(39));

    vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0,0,0,0);
//    vlayout->addStretch(0);
//    vlayout->addLayout(hlayout1);
    vlayout->addStretch(0);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addStretch(0);
    vlayout->addLayout(hlayout4);
    vlayout->addStretch(0);
    vlayout->addLayout(hlayout5);

}

void DownWidget::initConnect()
{
    connect(maxBtn,&QPushButton::clicked,this,&DownWidget::maxBtnslot);
    connect(startBtn,&QPushButton::clicked,this,&DownWidget::startBtnslot);
    connect(clearBtn,&QPushButton::clicked,this,&DownWidget::clearBtnslot);
    connect(this,&DownWidget::sendLabel,downwork,&DownWork::getDrawLab,Qt::DirectConnection);
    connect(this,&DownWidget::sendTimeNum,downwork,&DownWork::getTimeNum,Qt::DirectConnection);
    connect(this,&DownWidget::updateText,downwork,&DownWork::updateText,Qt::DirectConnection);
    connect(this,&DownWidget::sendTimerStop,downwork,&DownWork::stopTimer);
    connect(this,&DownWidget::sendTimerstart,downwork,&DownWork::startTimer);
    emit sendLabel(countLab);
}

void DownWidget::hideCustom(int i)
{
    if(i == 1)
    {
        hour_widget->hide();
        minute_widget->hide();
        second_widget->hide();
        label1->hide();
        label2->hide();
    }
    else if(i == 2)
    {
        hour_widget->show();
        minute_widget->show();
        second_widget->show();
        label1->show();
        label2->show();
    }
}

void DownWidget::addBlank(QString &str, int n)
{
    for(int i=0;i< n;i++)
    {
        str+=" ";
    }
}

void DownWidget::addText(QString &str, int n)
{
    if(n ==1)
    {
        addBlank(str,4);
        str += mIsChinese ? tr("时") : "H";
        addBlank(str,20);
        str += mIsChinese ? tr("分") : "M";
        addBlank(str,21);
        str += mIsChinese ? tr("秒") : "S";
    }
    else if(n ==2)
    {
        addBlank(str,20);
        str += mIsChinese ? tr("时") : "H";
        addBlank(str,53);
        str += mIsChinese ? tr("分") : "M";
        addBlank(str,53);
        str += mIsChinese ? tr("秒") : "S";
    }
}

void DownWidget::killThread()
{
    thread->exit();
    thread->quit();
    thread->wait();
}

void DownWidget::maxBtnslot()
{
    if(maxBtn->objectName() == "max")
    {
        emit sendMessage("max");
        countLab->setFixedSize(Public_Function::getScaleSize(783,112));
        if(!countLab->isHidden())
        {
         emit updateText();
        }
        maxBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi5.png"));
        maxBtn->setIconSize(Public_Function::getScaleSize(54,54));
        maxBtn->setFlat(true);
        maxBtn->setObjectName("min");
        maxBtn->setFixedSize(Public_Function::getScaleSize(54,54));
        startBtn->setFixedSize(Public_Function::getScaleSize(54,54));
        hour_widget->setFixedSize(Public_Function::getScaleSize(180,490));
        minute_widget->setFixedSize(Public_Function::getScaleSize(180,490));
        second_widget->setFixedSize(Public_Function::getScaleSize(180,490));
        label1->setFont(Public_Function::getFont(80));
        label2->setFont(Public_Function::getFont(80));
        timertextLab->setFixedSize(Public_Function::getScaleSize(783,22));
        timertextLab->setFont(Public_Function::getFont(22));
        QString str;
        addText(str,2);
        timertextLab->setText(str);
        timertextLab->show();
        if(!clearBtn->isHidden())
        {
            clearBtn->setFixedSize(Public_Function::getScaleSize(54,54));
        }

    }
    else if(maxBtn->objectName() == "min")
    {
        emit sendMessage("min");
        countLab->setFixedSize(Public_Function::getScaleSize(228,44));
        if(!countLab->isHidden())
        {
         emit updateText();
        }
        maxBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi1.png"));
        maxBtn->setIconSize(Public_Function::getScaleSize(54,54));
        maxBtn->setFlat(true);
        maxBtn->setObjectName("max");
        hour_widget->setFixedSize(Public_Function::getScaleSize(50,180));
        minute_widget->setFixedSize(Public_Function::getScaleSize(50,180));
        second_widget->setFixedSize(Public_Function::getScaleSize(50,180));
        label1->setFixedSize(Public_Function::getScaleSize(40,170));
        label2->setFixedSize(Public_Function::getScaleSize(40,170));
        label1->setFont(Public_Function::getFont(40));
        label2->setFont(Public_Function::getFont(40));
        timertextLab->setFixedSize(Public_Function::getScaleSize(220,16));
        timertextLab->setFont(Public_Function::getFont(16));
        QString str;
        addText(str,1);
        timertextLab->setText(str);
    }
}

void DownWidget::setLanguage(bool isChinese)
{
    mIsChinese = isChinese;
    QString str;
    addText(str,1);
    if( timertextLab != nullptr)
    {
        timertextLab->setText(str);
        timertextLab->update();
    }

}

void DownWidget::startBtnslot()
{
    if(!thread->isRunning())
    {
         thread->start();
    }
    if(!hour_widget->isHidden())
    {
        emit sendTimeNum(hour_widget->getCurrentVlaue(),minute_widget->getCurrentVlaue(),second_widget->getCurrentVlaue());
    }

    if(maxBtn->objectName() == "max")
        {
            if(startBtn->objectName() == "start")
            {
                //remainLab->show();
                countLab->setFixedSize(Public_Function::getScaleSize(228,44));
                emit sendLabel(countLab);
                hideCustom(1);
                startBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi3.png"));
                startBtn->setIconSize(Public_Function::getScaleSize(54,54));
                startBtn->setFlat(true);
                startBtn->setObjectName("stop");
                clearBtn->show();
                hlayout3->setContentsMargins(0,Public_Function::getScaleSize(50),0,0);
                emit sendTimerstart();
            }
            else if(startBtn->objectName() == "stop")
            {
                //remainLab->show();
                countLab->setFixedSize(Public_Function::getScaleSize(228,44));
                startBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi6.png"));
                startBtn->setIconSize(Public_Function::getScaleSize(54,54));
                startBtn->setFlat(true);
                startBtn->setObjectName("start");
                clearBtn->show();
                emit sendTimerStop();
            }
        }
        else if(maxBtn->objectName() == "min")
        {
            if(startBtn->objectName() == "start")
            {
                //remainLab->show();
                hideCustom(1);
                countLab->setFixedSize(Public_Function::getScaleSize(783,112));
                emit sendLabel(countLab);
                startBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi3.png"));
                startBtn->setIconSize(Public_Function::getScaleSize(52,52));
                startBtn->setFlat(true);
                startBtn->setObjectName("stop");
                clearBtn->show();
                emit sendTimerstart();
            }
            else if(startBtn->objectName() == "stop")
            {
                //remainLab->show();
                startBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi6.png"));
                countLab->setFixedSize(Public_Function::getScaleSize(783,112));
                startBtn->setIconSize(Public_Function::getScaleSize(52,52));
                startBtn->setFlat(true);
                startBtn->setObjectName("start");
                clearBtn->show();
                emit sendTimerStop();
            }
    }
}

void DownWidget::clearBtnslot()
{
    if(startBtn->objectName() == "stop")
    {
        emit sendTimerStop();
        startBtn->setIcon(QIcon(":/images/TimerPixmap/daojishi6.png"));
        startBtn->setIconSize(Public_Function::getScaleSize(54,54));
        startBtn->setFlat(true);
        startBtn->setObjectName("start");
        countLab->hide();
        //remainLab->hide();
        hideCustom(2);
    }
    else if(startBtn->objectName() == "start")
    {
        emit sendTimerStop();
        countLab->hide();
        //remainLab->hide();
        hideCustom(2);
    }
}
