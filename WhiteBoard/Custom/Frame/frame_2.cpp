#include "frame_2.h"
#include "Public/public_function.h"
#include "applicationconfig.h"
#include <QPixmap>
#include <QTime>
Frame_2::Frame_2(QWidget *parent)
    : QFrame{parent}
{
    laber =new QLabel(this);
    laber->setFixedSize(Public_Function::getScaleSize(129,46));
    laber->setStyleSheet(QString("background-color:rgba(255,0,0,0.48);color:rgb(255,255,255);border-radius:%1px;").arg(Public_Function::getScaleSize(23)));
    laber->setText(tr("调换成功"));
    laber->setAlignment(Qt::AlignCenter);
    laber->hide();

    laber2 =new QLabel(this);
    laber2->setFixedSize(Public_Function::getScaleSize(144,16));
    laber2->setStyleSheet(QString("color:rgb(255,255,255);font-size:%1px;").arg(Public_Function::getScaleSize(16)));
    laber2->setText(tr("记忆黑板功能已关闭"));
    laber2->setAlignment(Qt::AlignCenter);
    laber2->hide();

    laber3 =new QLabel(this);
    laber3->setFixedSize(Public_Function::getScaleSize(330,30));
    laber3->setText(QObject::tr("<font color = white>%1</font>").arg("未检测到可使用的记忆黑板,")+
            QObject::tr("<font color = #68B3FF>%1</font>").arg("请重新检测"));
    laber3->setAlignment(Qt::AlignCenter);
    laber3->installEventFilter(this);
    laber3->hide();

    laber4 =new Label_1(this);
    laber4->hide();

    timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        timer->stop();
        laber->hide();
    });

    timer2 =new QTimer(this);
    connect(timer2,&QTimer::timeout,this,[=](){
       timer2->stop();
       laber4->hide();
       emit sendOpenSignal();
    });
}

void Frame_2::setPixmapShow(int num)
{
    if(num ==2)
    {
        this->setFixedSize(Public_Function::getScaleSize(760,300));
        QString value = ApplicationConfig::readConfig("exchange");
        if(value.isEmpty())ApplicationConfig::writeConfig("exchange","false");
        else
        {
            if(value.contains("true"))
            {
                exchange =true;
            }
            else if(value.contains("false"))
            {
                exchange =false;
            }
        }
        if(exchange)pixmap =QPixmap(":/images/main/menu/ban-2@2x.png");
        else pixmap =QPixmap(":/images/main/menu/ban-3@2x.png");
        laber2->hide();
        laber3->hide();
    }
    else if(num ==1)
    {
        this->setFixedSize(Public_Function::getScaleSize(595,300));
        pixmap =QPixmap(":/images/main/menu/ban-1@2x.png");
        laber2->hide();
        laber3->hide();
    }
    else if(num ==0)
    {
        this->setFixedSize(Public_Function::getScaleSize(760,300));
        pixmap =QPixmap(":/images/main/menu/hei-1@2x.png");
        laber3->move((this->width() -laber3->width())/2,(this->height() -laber3->height())/2);
        laber3->show();
        laber2->hide();
    }
    else if(num ==3)
    {
        this->setFixedSize(Public_Function::getScaleSize(760,300));
        pixmap =QPixmap(":/images/main/menu/hei-1@2x.png");
        laber2->move((this->width() -laber2->width())/2,(this->height() -laber2->height())/2);
        laber2->show();
        laber3->hide();
    };
    update();
}

void Frame_2::swithcPixmap()
{
    if(!exchange)
    {
        exchange =true;
        ApplicationConfig::writeConfig("exchange","true");
    }
    else
    {
        exchange =false;
        ApplicationConfig::writeConfig("exchange","false");
    }

    if(exchange)pixmap =QPixmap(":/images/main/menu/ban-2@2x.png");
    else pixmap =QPixmap(":/images/main/menu/ban-3@2x.png");
    timer->start(3000);
    laber->move((this->width() -laber->width())/2,(this->height() -laber->height())/2);
    laber->show();
    update();
}

void Frame_2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(this->rect(),pixmap);
}

bool Frame_2::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched ==laber3)
        {
            laber4->move((this->width() -laber4->width())/2,(this->height() -laber4->height())/2);
            laber4->show();
            timer2->start(4000);
            laber3->hide();
            return true;
        }
    }
   return QFrame::eventFilter(watched,event);
}
