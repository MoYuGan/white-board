#include "customcontrol.h"
#include <QDebug>
#include <QLabel>
#include "Public/public_function.h"

Icon_Lab::Icon_Lab(QWidget *parent) : QLabel(parent)
{

}

void Icon_Lab::changeSizeAndPixmap(QSize size, QPixmap pix)
{
    this->setFixedSize(size);
    pixmap =pix.scaled(size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    update();
}

void Icon_Lab::changePixmapSize(QSize size)
{
    this->setFixedSize(size);
    update();
}

void Icon_Lab::changePixmap(QPixmap pix)
{
    pixmap =pix;
    update();
}

void Icon_Lab::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawPixmap(this->rect(),pixmap);
}

/******************播放按钮**********************/
Player_Lab::Player_Lab(QWidget *parent) : QLabel(parent)
{

}

void Player_Lab::changeSizeAndPixmap(QSize size, QPixmap pix)
{
    this->setFixedSize(size);
    pixmap =pix;
    update();
}

void Player_Lab::changePixmapSize(QSize size,int number)
{
    pixmap =pixmap.scaled(size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    num =number;
    update();
}

void Player_Lab::changeSize(QSize size)
{
    this->setFixedSize(size);
}

void Player_Lab::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(QColor(0,0,0,100));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(this->rect());
    if(num ==1)
    {
        painter.drawPixmap(this->rect().width()/2 -pixmap.width()/3,this->rect().height()/2 -pixmap.height()/2,pixmap.width(),pixmap.height(),pixmap);
    }
    else if(num ==2)
    {
        painter.drawPixmap(this->rect().width()/2 -pixmap.width()/2,this->rect().height()/2 -pixmap.height()/2,pixmap.width(),pixmap.height(),pixmap);
    }
}


/***********************进度条********************/
Progressbar::Progressbar(QWidget *parent) : QSlider(parent)
{
    this->setPageStep(0);
    connect(this,&Progressbar::sliderPressed,this,[=](){emit sendPressProgressbarSignal();});
    connect(this,&Progressbar::sliderMoved,this,[=](int num){ number =num; ispress =true;});
    connect(this,&Progressbar::sliderReleased,this,[=](){if(ispress)emit sendPos(number);ispress =false;});
}

void Progressbar::changeSize(int w,int h,int w1)
{
    this->setFixedSize(w,h);
    QString style =QString("QSlider::groove:horizontal{ height: %2px;background-color:rgb(255,255,255);}"
                           "QSlider::handle:horizontal{width:%1px;height: %1px;border-image: url(:/Pixmap/dian2x.png);"
                           "margin-top: %3px;margin-bottom: %3px;}"
                           "QSlider::add-page:horizontal{background-color:rgb(255,255,255);}"
                           "QSlider::sub-page:horizontal{background-color:rgb(20,134,250);}").arg(h).arg(w1).arg((w1 -h)/2);
    this->setStyleSheet(style);
}

void Progressbar::setProgressbarVlaue(int num)
{
    if(!ispress)this->setValue(num);
}

/*********************音量窗口**********************/
Volumewidget::Volumewidget(QWidget *parent) : QFrame(parent)
{
    slider_Sli = new QSlider(this);
    this->setObjectName("volume");
    text_Lab.setText("60");
    initWidget();
    changeSize(44,166,4,14,17,14,119,20,6);
    slider_Sli->setRange(0,100);
    slider_Sli->setValue(60);

    connect(slider_Sli,&QSlider::sliderMoved,this,[=](int num){text_Lab.setText(QString::number(num));emit sendVolumeNumber(num);});
    connect(slider_Sli,&QSlider::valueChanged,this,[=](int num){text_Lab.setText(QString::number(num));emit sendVolumeNumber(num);});
}

void Volumewidget::initWidget()
{
    QHBoxLayout *hlayout1 =new QHBoxLayout();
    hlayout1->addStretch();
    hlayout1->addWidget(&text_Lab);
    hlayout1->addStretch();

    QHBoxLayout *hlayout2 =new QHBoxLayout();
    hlayout2->addStretch();
    hlayout2->addWidget(slider_Sli);
    hlayout2->addStretch();

    QVBoxLayout *vlayout =new QVBoxLayout(this);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
}

void Volumewidget::changeSize(int width, int heigth, int borderradius,int tetxSize, int textWidth, int textHigth, int sliderHeight, int sliderWidth, int sliderWidth1)
{
    width =Public_Function::getScaleSize(width);
    heigth =Public_Function::getScaleSize(heigth);
    borderradius =Public_Function::getScaleSize(borderradius);
    tetxSize =Public_Function::getScaleSize(tetxSize);
    textWidth =Public_Function::getScaleSize(textWidth);
    textHigth =Public_Function::getScaleSize(textHigth);
    sliderHeight =Public_Function::getScaleSize(sliderHeight);
    sliderWidth =Public_Function::getScaleSize(sliderWidth);
    sliderWidth1 =Public_Function::getScaleSize(sliderWidth1);

    this->setFixedSize(width,heigth);
    this->setStyleSheet(QString("QFrame#volume{border-radius: %1px;background-color:rgba(0,0,0,0.5);}").arg(borderradius));

    text_Lab.setFixedSize(textWidth,textHigth);
    text_Lab.setAlignment(Qt::AlignCenter);
    text_Lab.setStyleSheet(QString("color:white;font-size:%1px;").arg(tetxSize));

    slider_Sli->setFixedSize(sliderWidth,sliderHeight);
    QString style =QString("QSlider::groove:vertical{ height: %1px;width: %2px;background-color:rgb(255,255,255); border-radius:%3px;}"
                           "QSlider::handle:vertical{width:%4px;height: %4px;border-image: url(:/Pixmap/dian2x.png);"
                           "margin-left: %5px;margin-right: %5px;}"
                           "QSlider::add-page:vertical{background-color:rgb(20,134,250);border-radius:%3px;}"
                           "QSlider::sub-page:vertical{background-color:rgb(255,255,255);border-radius:%3px;}").arg(sliderHeight)
            .arg(sliderWidth1).arg(sliderWidth1/2).arg(sliderWidth).arg((sliderWidth1 -sliderWidth)/2);
    slider_Sli->setStyleSheet(style);
}

void Volumewidget::changeVolume(QString str)
{
    if(str.compare("volume") ==0)
    {
        slider_Sli->setValue(volumenumber);
        text_Lab.setText(QString::number(volumenumber));
    }
    else if(str.compare("mute") ==0)
    {
       volumenumber =slider_Sli->value();
       slider_Sli->setValue(0);
       text_Lab.setText(QString::number(0));
    }
}

int Volumewidget::getVolume()
{
    return slider_Sli->value();
}



/*********************速度窗口**********************/
Speedwidget::Speedwidget(QWidget *parent) : QFrame(parent)
{
    this->setObjectName("speed");
    initWidget();
    this->setStyleSheet("color:white");
    changeSize(72,180,4,14);
    emit group_Btn->buttonClicked(speed2_Btn);

}

Speedwidget::~Speedwidget()
{
    speed_Btn->deleteLater();
    speed1_Btn->deleteLater();
    speed2_Btn->deleteLater();
    speed3_Btn->deleteLater();
    speed4_Btn->deleteLater();
    speed5_Btn->deleteLater();
    group_Btn->deleteLater();
}

void Speedwidget::initWidget()
{
    line1_Lab.setFixedSize(Public_Function::getScaleSize(48,1));
    line2_Lab.setFixedSize(Public_Function::getScaleSize(48,1));
    line3_Lab.setFixedSize(Public_Function::getScaleSize(48,1));
    line4_Lab.setFixedSize(Public_Function::getScaleSize(48,1));
    line1_Lab.show();
    line2_Lab.show();
    line3_Lab.show();
    line4_Lab.show();

    speed1_Btn =new QPushButton(this);
    speed1_Btn->setText("0.75x");

    speed2_Btn =new QPushButton(this);
    speed2_Btn->setText("1.0x");
    speed2_Btn->setCheckable(true);

    speed3_Btn =new QPushButton(this);
    speed3_Btn->setText("1.25x");

    speed4_Btn =new QPushButton(this);
    speed4_Btn->setText("1.5x");

    speed5_Btn =new QPushButton(this);
    speed5_Btn->setText("2.0x");

    group_Btn =new QButtonGroup(this);
    group_Btn->setExclusive(true);
    group_Btn->addButton(speed1_Btn,1);
    group_Btn->addButton(speed2_Btn,2);
    group_Btn->addButton(speed3_Btn,3);
    group_Btn->addButton(speed4_Btn,4);
    group_Btn->addButton(speed5_Btn,5);

    QVBoxLayout *vlayout =new QVBoxLayout(this);
    vlayout->setAlignment(Qt::AlignCenter);
    vlayout->addWidget(speed5_Btn);
    vlayout->addWidget(&line4_Lab);

    vlayout->addWidget(speed4_Btn);
    vlayout->addWidget(&line3_Lab);

    vlayout->addWidget(speed3_Btn);
    vlayout->addWidget(&line2_Lab);

    vlayout->addWidget(speed2_Btn);
    vlayout->addWidget(&line1_Lab);

    vlayout->addWidget(speed1_Btn);

    connect(group_Btn,QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&Speedwidget::buttonPress);

}

void Speedwidget::changeSize(int width, int heigth, int borderradius,int tetxSize)
{
    width =Public_Function::getScaleSize(width);
    heigth =Public_Function::getScaleSize(heigth);
    borderradius =Public_Function::getScaleSize(borderradius);
    textsize =Public_Function::getScaleSize(tetxSize);
    this->setFixedSize(width,heigth);
    this->setStyleSheet(QString("QFrame#speed{border-radius: %1px;background-color:rgba(0,0,0,0.5);}"
                        "QLabel{background-color:rgba(255,255,255,0.2);} QPushButton{color:white;border: none solid;font-size:%2px}").arg(borderradius).arg(textsize));
    if(speed_Btn != nullptr){emit group_Btn->buttonClicked(speed_Btn);}
}

float Speedwidget::getCurrentSpeed()
{
    return currentspeed;
}

void Speedwidget::buttonPress(QAbstractButton *button)
{
    speed1_Btn->setStyleSheet(QString("color:white;border: none solid;font-size:%1px").arg(textsize));
    speed2_Btn->setStyleSheet(QString("color:white;border: none solid;font-size:%1px").arg(textsize));
    speed3_Btn->setStyleSheet(QString("color:white;border: none solid;font-size:%1px").arg(textsize));
    speed4_Btn->setStyleSheet(QString("color:white;border: none solid;font-size:%1px").arg(textsize));
    speed5_Btn->setStyleSheet(QString("color:white;border: none solid;font-size:%1px").arg(textsize));
    speed_Btn = static_cast<QPushButton*>(button);
    speed_Btn->setStyleSheet(QString("color:rgb(20,134,250);border: none solid;font-size:%1px").arg(textsize));
    if(group_Btn->id(speed_Btn) ==1)currentspeed =0.75;
    else if(group_Btn->id(speed_Btn) ==2)currentspeed =1;
    else if(group_Btn->id(speed_Btn) ==3)currentspeed =1.25;
    else if(group_Btn->id(speed_Btn) ==4)currentspeed =1.5;
    else if(group_Btn->id(speed_Btn) ==5)currentspeed =2;
    emit speedChange(speed_Btn->text(),currentspeed);
}



