#include "downwork.h"
#include <QDebug>
#include <QThread>
#include "Public/public_function.h"
#include <QBoxLayout>
#include <QTimer>

DownWork::DownWork(QObject *parent) : QObject(parent)
{
    mtimer = new QTimer(this);
    showtime = new QLabel;
    showtime->setFixedSize(Public_Function::getScaleSize(228,44));
    connect(mtimer,&QTimer::timeout,this,&DownWork::showTimeText,Qt::DirectConnection);
}

void DownWork::updateText()
{
    QString str;
    showtime->show();
    if(hour <10)str +=QString("0%1").arg(hour);
    else(str +=QString("%1").arg(hour));
    if(showtime->width() == Public_Function::getScaleSize(228))
    {
        addBlank(str,2);
        str += ":";
        addBlank(str,2);
    }
    else if(showtime->width() == Public_Function::getScaleSize(783))
    {
        addBlank(str,4);
        str += ":";
        addBlank(str,4);
    }

    if(minute <10)str +=QString("0%1").arg(minute);
    else(str +=QString("%1").arg(minute));
    if(showtime->width() == Public_Function::getScaleSize(228))
    {
        addBlank(str,2);
        str += ":";
        addBlank(str,2);
    }
    else if(showtime->width() ==Public_Function::getScaleSize(783))
    {
        addBlank(str,4);
        str += ":";
        addBlank(str,4);
    }
    if(second <10)str +=QString("0%1").arg(second);
    else str+=QString("%1").arg(second);
    if(showtime->width() ==Public_Function::getScaleSize(228))
    {
        showtime->show();
        showtime->setFixedSize(Public_Function::getScaleSize(228,44));
        showtime->setFont(Public_Function::getFont(40));
    }
    else if(showtime->width() == Public_Function::getScaleSize(783))
    {
        showtime->show();
        showtime->setFont(Public_Function::getFont(100));
        showtime->setFixedSize(Public_Function::getScaleSize(783,112));
    }
    showtime->setAlignment(Qt::AlignCenter);
    showtime->setText(str);
}

void DownWork::addBlank(QString &str, int n)
{
    for(int i=0;i< n;i++)
    {
        str+=" ";
    }
}

void DownWork::getTimeNum(int h, int min, int sec)
{
    hour =h;
    minute =min;
    second =sec;
    updateText();
}

void DownWork::startTimer()
{
    mtimer->start(1000);
    qDebug() << " DownThread::startTimer() " << QThread::currentThread() << endl;
}

void DownWork::stopTimer()
{
    mtimer->stop();
}

void DownWork::getDrawLab(QLabel *showlabel)
{
    showtime = showlabel;
}

void DownWork::showTimeText()
{
    mtimer->stop();
    if((minute ==0)&&(second ==0))
    {
        if(hour !=0)
        {
            hour--;
            minute =60;
        }
        else
        {
          minute =0;
        }
    }
    if(second ==0)
    {
        if(minute !=0)
        {
            minute--;
            second =60;
        }
        else
        {
            second =0;
        }
    }
    if((hour ==0)&&(minute ==0)&&(second ==0))
    {
        mtimer->stop();
    }
    else
    {
       second--;
    }
    updateText();
    mtimer->start(1000);
}
