#include "pushbutton_12.h"
#include <QFileDialog>

PushButton_12::PushButton_12(QWidget *parent) :
    QPushButton(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(300,168));
    this->setCheckable(true);
    btn =new QPushButton(this);
    btn->setFixedSize(Public_Function::getScaleSize(98,112));
    QIcon icon(QPixmap(":/images/backgroundpixmap/quesheng1@2x.png"));
    btn->setIcon(icon);
    btn->setIconSize(Public_Function::getScaleSize(98,112));
    btn->setFlat(true);

    connect(this,&QPushButton::clicked,this,[=](){
        if(!filepath.isEmpty())
        {
            emit sendShowButtonSignal(filepath);
            update();
        }
    });

    connect(btn,&QPushButton::clicked,this,[=](){
        if(filepath.isEmpty())
        {
            filepath =QFileDialog::getOpenFileName();
            if(filepath.isEmpty())return;
            btn->hide();
            this->setChecked(true);
            emit sendShowButtonSignal(filepath);

        }
    });
}


void PushButton_12::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QPen(QColor(224,224,224),Public_Function::getScaleSize(1)));
    QRect rect =QRect(Public_Function::getScaleSize(1),Public_Function::getScaleSize(1),Public_Function::getScaleSize(298),Public_Function::getScaleSize(166));
    painter.drawRoundedRect(rect,Public_Function::getScaleSize(4),Public_Function::getScaleSize(4));
    if(filepath.isEmpty())
    {
        btn->move(Public_Function::getScaleSize(101),Public_Function::getScaleSize(15));
        QRect mrect =QRect(0,Public_Function::getScaleSize(128),this->width(),Public_Function::getScaleSize(12));
        painter.setPen(QPen(QColor(102,102,102)));
        painter.drawText(mrect, Qt::AlignCenter, tr("点击选择文件"));
    }
    else
    {
        QRect pixmaprect =QRect(Public_Function::getScaleSize(5),Public_Function::getScaleSize(5),Public_Function::getScaleSize(290),Public_Function::getScaleSize(158));
        painter.drawPixmap(pixmaprect,QPixmap(filepath));
        if(this->isChecked())
        {
            painter.setPen(QPen(QColor(19,133,249),Public_Function::getScaleSize(2)));
            painter.drawRoundedRect(rect,Public_Function::getScaleSize(4),Public_Function::getScaleSize(4));
            QRect mrect =QRect(Public_Function::getScaleSize(276),Public_Function::getScaleSize(144),Public_Function::getScaleSize(24),Public_Function::getScaleSize(24));
            painter.drawPixmap(mrect,QPixmap(":/images/backgroundpixmap/xuanzhong2@2x.png"));
        }
    }
}

void PushButton_12::changePixmap(QString pixmappath)
{
    filepath =pixmappath;
    update();
}

