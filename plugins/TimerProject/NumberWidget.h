#ifndef NUMBERWIDGET_H
#define NUMBERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "Public/public_function.h"
#include <QDebug>
class NumWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NumWidget(QWidget *parent = nullptr):QWidget(parent)
    {
    }
    void setRange(int num1,int num2)
    {
        min = num1;
        max = num2;
    }

    void setCurrentVlaue(int num)
    {
        currentvlaue = num;
        update();
    }

    int  getCurrentVlaue()
    {
        return currentvlaue;
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);
        QString str;
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setBrush(QBrush(Qt::white));
        int size = this->height()*2/5 -qAbs((this->height() - qAbs(mousemovepos)) /4);
        //painter.setFont(Public_Function::getFont(size));
        QFont font;
        font.setPixelSize(size);
        painter.setFont(font);
        painter.setPen(QPen(Qt::gray));
        for(int a=0;a <2;a++)
        {
            if(currentvlaue -a >min)
            {
                str = (currentvlaue -a -1)<10?(QString::number(0) +QString::number(currentvlaue -a -1)) :QString::number(currentvlaue -a -1);
                painter.drawText(0,-a*height()/3 +mousemovepos,this->width(),this->height()/3,Qt::AlignCenter,str);
            }
            else
            {
                str = (currentvlaue -a+max)<10?(QString::number(0) +QString::number(currentvlaue -a+max)) :QString::number(currentvlaue -a+max);
                painter.drawText(0,-a*height()/3 +mousemovepos,this->width(),this->height()/3,Qt::AlignCenter,str);
            }

            if(currentvlaue +a <max)
            {
                str = (currentvlaue +a +1)<10?(QString::number(0) +QString::number(currentvlaue +a +1)) :QString::number(currentvlaue +a +1);
                painter.drawText(0,a*height()/3 +height()*2/3 +mousemovepos,this->width(),this->height()/3,Qt::AlignCenter,str);
            }
            else
            {
                str = (currentvlaue +a -max)<10?(QString::number(0) +QString::number(currentvlaue +a -max)) :QString::number(currentvlaue +a -max);
                painter.drawText(0,a*height()/3 +height()*2/3 +mousemovepos,this->width(),this->height()/3,Qt::AlignCenter,str);
            }
        }
        painter.setPen(QPen(Qt::black));
        size = qAbs((this->height() - qAbs(mousemovepos)) /4);
        font.setPixelSize(size);
        painter.setFont(font);
        //painter.setFont(Public_Function::getFont(size));
        str = (currentvlaue)<10?(QString::number(0) +QString::number(currentvlaue)) :QString::number(currentvlaue);
        painter.drawText(0,height()/3 +mousemovepos,this->width(),this->height()/3,Qt::AlignCenter,str);
    }

    void mousePressEvent(QMouseEvent *event)
    {
        mousepresspos = event->globalPos();
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        mousemovepos = event->globalPos().y() -mousepresspos.y();
        if(mousemovepos > height()/3)
        {
            currentvlaue -=1;
            if(currentvlaue ==min)currentvlaue =0;
            else if(currentvlaue <min)currentvlaue +=(max+1);
            mousepresspos = event->globalPos();
        }
        else if(qAbs(mousemovepos) >height()/3)
        {
            currentvlaue +=1;
            if(currentvlaue ==max)currentvlaue =max;
            else if(currentvlaue >max)currentvlaue -=(max +1);
            mousepresspos = event->globalPos();
        }
        update();
    }

    void mouseReleaseEvent(QMouseEvent *)
    {
        if(mousemovepos >=0)
        {
            if(mousemovepos*3%this->height() >= this->height()/3)
                currentvlaue -=1;
            if(currentvlaue ==min)currentvlaue =0;
            else if(currentvlaue <min)currentvlaue +=(max+1);
        }
        else
        {
            if(qAbs(mousemovepos*3%this->height()) >= this->height()/3)
                currentvlaue +=1;
            if(currentvlaue ==max)currentvlaue =max;
            else if(currentvlaue >max)currentvlaue -=(max +1);
        }
        mousemovepos=0;
        update();
    }

signals:

private:
    int min =0;
    int max=59;
    int currentvlaue =(max +min)/2;
    int mousemovepos =0;
    QPoint mousepresspos;
};
#endif // NUMBERWIDGET_H
