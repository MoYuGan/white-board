#include "timerwork.h"
#include <QThread>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <Public/public_function.h>
#include <QPainter>
#include <QDebug>

TimerWork::TimerWork(QObject *parent) : QObject(parent)
{
    m_pTimer = new QTimer(this);
    interfaceLab = new QLabel();
    timerLab = new QLabel();
    connect(m_pTimer,&QTimer::timeout,this,&TimerWork::getTimeText,Qt::DirectConnection);
}

void TimerWork::getTimeText()
{
    m_pTimer->stop();
    second++;
    if(second ==60)
    {
        second =0;
        minute++;
        if(minute ==30)
        {
         timerstop = true;;
        }
    }
    drawClock();
    QString str = QString("00:");
    if(minute <10)str +=QString("0%1:").arg(minute);
    else(str +=QString("%1:").arg(minute));
    if(second <10)str +=QString("0%1").arg(second);
    else if(second ==60)str +=QString("00");
    else str+=QString("%1").arg(second);
    timerLab->setText(str);
    m_pTimer->start(1000);
}

void TimerWork::startTimer()
{
    m_pTimer->start(1000);
}

void TimerWork::stopTimer()
{
    m_pTimer->stop();
}

void TimerWork::drawClock()
{
    QPixmap pix(interfaceLab->width(),interfaceLab->width());
    pix.fill(Qt::white);
    QPainter painter(&pix);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    QRect rect = QRect(0,0,interfaceLab->width(),interfaceLab->width());
    if(interfaceLab->width() == Public_Function::getScaleSize(590))
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
    painter.rotate(minute*12);
    if(interfaceLab->width() == Public_Function::getScaleSize(590))
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
    painter.rotate(second*6);
    if(interfaceLab->width() == Public_Function::getScaleSize(590))
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

void TimerWork::clearTimer()
{
    m_pTimer->stop();
    second =0;
    minute =0;
    drawClock();
}

void TimerWork::getDrawLab(QLabel *mylabel, QLabel *textlabel)
{
    interfaceLab = mylabel;
    drawClock();
    timerLab = textlabel;
}
