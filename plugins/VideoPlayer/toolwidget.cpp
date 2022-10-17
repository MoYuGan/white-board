#include "toolwidget.h"
#include "ui_toolwidget.h"
#include "Public/public_function.h"
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

ToolWidget::ToolWidget(QWidget *parent) :
    VideoPlayerInterFace(parent),
    ui(new Ui::ToolWidget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint,true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setMouseTracking(true);

    playerwork = new VideoPlayerWork();
    thread = new QThread(this);
    playerwork->moveToThread(thread);
    initeventFilter();
    initWidget();
    initConnect();
}

ToolWidget::~ToolWidget()
{
    delete ui;
    volume->deleteLater();
    speed->deleteLater();
    thread->deleteLater();
}

VideoPlayerInterFace *ToolWidget::createWidget(QWidget *parent)
{
    this->setParent(parent);
    return this;
}

void ToolWidget::openFilePath()
{
        pressFile();
}

void ToolWidget::initWidget()
{
    this->setFixedSize(Public_Function::getScaleSize(1200,674));
    pixmap =new QPixmap(this->size());
    *pixmap =QPixmap(":/Pixmap/background.png");
    mpixmap =*pixmap;
    m_width =this->width();
    m_height =this->height();
    ui->player_Lab->changeSizeAndPixmap(Public_Function::getScaleSize(26,27),QPixmap(":/Pixmap/play-small-1@2x.png"));
    ui->time_Lab->setText("00:00:00 / 00:00:00");
    ui->time_Lab->setStyleSheet("color:white;");
    ui->time_Lab->setFont(Public_Function::getFont(18));
    ui->speed_Lab->setText("1.0x");
    ui->speed_Lab->setStyleSheet("color:white;");
    ui->speed_Lab->setFont(Public_Function::getFont(18));

    ui->volume_Lab->changeSizeAndPixmap(Public_Function::getScaleSize(26,27),QPixmap(":/Pixmap/volume-1@2x.png"));
    ui->file_Lab->changeSizeAndPixmap(Public_Function::getScaleSize(26,27),QPixmap(":/Pixmap/wenjian@2x.png"));
    ui->full_Lab->changeSizeAndPixmap(Public_Function::getScaleSize(26,27),QPixmap(":/Pixmap/quanping@2x.png"));
    ui->close_Lab->changeSizeAndPixmap(Public_Function::getScaleSize(26,27),QPixmap(":/Pixmap/guanbi@2x.png"));
    ui->screenshot_Lab->changeSizeAndPixmap(Public_Function::getScaleSize(26,27),QPixmap(":/Pixmap/jietu-1@2x.png"));
    ui->rotate_Lab->changeSizeAndPixmap(Public_Function::getScaleSize(26,27),QPixmap(":/Pixmap/xuanzhuan-1@2x.png"));

    ui->Player->changeSizeAndPixmap(Public_Function::getScaleSize(98,98),QPixmap(":/Pixmap/play-big-1@2x.png"));
    ui->Player->changePixmapSize(Public_Function::getScaleSize(36,46));
    ui->horizontalLayout->setContentsMargins(Public_Function::getScaleSize(23),Public_Function::getScaleSize(12),Public_Function::getScaleSize(22),Public_Function::getScaleSize(12));
    ui->progressbar->changeSize(this->width(),Public_Function::getScaleSize(20),Public_Function::getScaleSize(6));

    ui->progressbar->hide();
    ui->Player->hide();


    volume =new Volumewidget(this);
    volume->changeSize(44,166,4,14,22,14,119,20,6);
    volume->hide();

    speed =new Speedwidget(this);
    speed->hide();

    hidebutton = new QTimer(this);
}

void ToolWidget::initConnect()
{
    connect(this,&ToolWidget::sendStartPlaySignal,playerwork,&VideoPlayerWork::getStartPalySignal);

    connect(this,&ToolWidget::sendPausePlaySignal,playerwork,&VideoPlayerWork::getPausePlaySignal);

    connect(this,&ToolWidget::sendContinuePlaySignal,playerwork,&VideoPlayerWork::getContinuePlaySignal);

    connect(this,&ToolWidget::sendCloseSignal,playerwork,&VideoPlayerWork::getCloseSignal);

    connect(this,&ToolWidget::sendStopPlaySignal,playerwork,&VideoPlayerWork::getStopPlaySignal);

    connect(playerwork,&VideoPlayerWork::sendUpdatePixmapSignal,this,&ToolWidget::rotatePixmap);

    connect(playerwork,&VideoPlayerWork::sendUpdateTimeSignal,this,&ToolWidget::getUpdateTimeSignal);


    connect(speed,&Speedwidget::speedChange,this,[=](QString speedtext,float number){
        ui->speed_Lab->setText(speedtext);
        if(!filepath.isEmpty()) emit sendSpeedChangeSignal(number);
    });

    connect(this,&ToolWidget::sendSpeedChangeSignal,playerwork,&VideoPlayerWork::getSpeedChangeSignal);

    connect(ui->progressbar,&Progressbar::sendPos,this,[=](int number){hidebutton->start(5000);if((!filepath.isEmpty())&&(!isfinish)) emit sendPlayPosChangeSignal(number);});

    connect(ui->progressbar,&Progressbar::sendPressProgressbarSignal,this,[=](){hidebutton->stop(),showButton(1);});

    connect(this,&ToolWidget::sendPlayPosChangeSignal,playerwork,&VideoPlayerWork::getPlayPosChangeSignal);

    connect(this,&ToolWidget::sendVolumeChangeSignal,playerwork,&VideoPlayerWork::getVolumeChangeSignal);

    connect(volume,&Volumewidget::sendVolumeNumber,this,[=](int number){if(!filepath.isEmpty())emit sendVolumeChangeSignal(number);});


    connect(hidebutton,&QTimer::timeout,this,[=](){
        hidebutton->stop();
        if(ui->Player->isHidden())showButton(0);
    });

}

void ToolWidget::initeventFilter()
{
    ui->Player->installEventFilter(this);
    ui->Player->setObjectName("maxplayer");
    ui->player_Lab->installEventFilter(this);
    ui->player_Lab->setObjectName("minplayer");
    ui->volume_Lab->installEventFilter(this);
    ui->volume_Lab->setObjectName("volume");
    ui->file_Lab->installEventFilter(this);
    ui->file_Lab->setObjectName("file");
    ui->full_Lab->installEventFilter(this);
    ui->full_Lab->setObjectName("full");
    ui->speed_Lab->installEventFilter(this);
    ui->close_Lab->installEventFilter(this);
    ui->screenshot_Lab->installEventFilter(this);
    ui->rotate_Lab->installEventFilter(this);
    this->installEventFilter(this);
}

void ToolWidget::resizeControl(int number)
{
    if(number ==1)
    {
        this->setFixedSize(Public_Function::getScaleSize(1200,674));
        this->move(widgetpos.x(),widgetpos.y());
        ui->player_Lab->changePixmapSize(Public_Function::getScaleSize(26,27));
        ui->volume_Lab->changePixmapSize(Public_Function::getScaleSize(26,27));
        ui->file_Lab->changePixmapSize(Public_Function::getScaleSize(26,27));
        ui->full_Lab->changePixmapSize(Public_Function::getScaleSize(26,27));
        ui->close_Lab->changePixmapSize(Public_Function::getScaleSize(26,27));
        ui->screenshot_Lab->changePixmapSize(Public_Function::getScaleSize(26,27));
        ui->rotate_Lab->changePixmapSize(Public_Function::getScaleSize(26,27));
        ui->Player->changeSize(Public_Function::getScaleSize(98,98));
        ui->Player->changePixmapSize(Public_Function::getScaleSize(36,46));
        ui->horizontalLayout->setContentsMargins(Public_Function::getScaleSize(23),Public_Function::getScaleSize(12),Public_Function::getScaleSize(22),Public_Function::getScaleSize(12));
        ui->progressbar->changeSize(this->width(),Public_Function::getScaleSize(20),Public_Function::getScaleSize(6));
        ui->time_Lab->setFont(Public_Function::getFont(18));
        ui->speed_Lab->setFont(Public_Function::getFont(18));
        volume->changeSize(44,166,4,14,22,14,119,20,6);
        speed->changeSize(72,180,4,14);
    }
    else if(number ==2)
    {
        this->setFixedSize(QApplication::desktop()->size());
        widgetpos =this->pos();
        this->move(0,0);
        ui->player_Lab->changePixmapSize(Public_Function::getScaleSize(42,42));
        ui->volume_Lab->changePixmapSize(Public_Function::getScaleSize(42,42));
        ui->file_Lab->changePixmapSize(Public_Function::getScaleSize(42,42));
        ui->full_Lab->changePixmapSize(Public_Function::getScaleSize(42,42));
        ui->close_Lab->changePixmapSize(Public_Function::getScaleSize(42,42));
        ui->screenshot_Lab->changePixmapSize(Public_Function::getScaleSize(42,42));
        ui->rotate_Lab->changePixmapSize(Public_Function::getScaleSize(42,42));
        ui->Player->changeSize(Public_Function::getScaleSize(156,156));
        ui->Player->changePixmapSize(Public_Function::getScaleSize(58,74));
        ui->horizontalLayout->setContentsMargins(Public_Function::getScaleSize(37),Public_Function::getScaleSize(20),Public_Function::getScaleSize(35),Public_Function::getScaleSize(20));
        ui->progressbar->changeSize(this->width(),Public_Function::getScaleSize(32),Public_Function::getScaleSize(10));
        ui->time_Lab->setFont(Public_Function::getFont(24));
        ui->speed_Lab->setFont(Public_Function::getFont(24));
        volume->changeSize(70,266,6,18,32,18,190,32,10);
        speed->changeSize(90,220,6,18);        
    }

    m_width =this->width();
    m_height =this->height();
}

void ToolWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

    painter.setBrush(Qt::black);
    painter.drawRect(this->rect());
    if(rotate ==0)
    {
        painter.drawPixmap((this->width() - m_width)/2,(this->height() -m_height)/2,m_width,m_height,mpixmap);
    }
    else if(rotate ==1)
    {
        float num = float(videowidth)/videoheight;
        painter.drawPixmap((this->width() - m_height/num)/2,(this->height() -m_height)/2,m_height/num,m_height,mpixmap);
    }
}

bool ToolWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == ui->close_Lab)
        {
            emit sendCloseSignal();
            thread->exit();
            thread->quit();
            thread->wait();
            emit sendWidgetCloseSignal();
            this->close();
        }
        else if(watched == ui->player_Lab)
        {
            pressMiniPlayer();
        }
        else if(watched == ui->Player)
        {
            pressMaxPlayer();
        }
        else if(watched == ui->file_Lab)
        {
            pressFile();
            return true;
        }
        else if(watched == ui->full_Lab)
        {
            pressFullScreen();
            return true;
        }
        else if(watched == ui->speed_Lab)
        {
            QEvent event(QEvent::WindowActivate);
            QApplication::sendEvent(this,&event);
            speed->show();
            speed->raise();
            return true;
        }
        else if(watched == ui->volume_Lab)
        {
            pressVolume();
            return true;
        }
        else if(watched == ui->rotate_Lab)
        {
            if(rotate ==1)rotate =0;
            else rotate =1;
            return true;
        }
        else if(watched == ui->screenshot_Lab)
        {
            isscreenshot =true;
            return true;
        }
        else if(watched ==this)
        {
            QMouseEvent* e =static_cast<QMouseEvent*>(event);
            volume->hide();
            speed->hide();
            ispress =true;
            pressdot =e->pos();
        }
        return true;
    }

    else if(event->type() == QEvent::MouseMove)
    {
        if(ispress)
        {
            if(isfull)return true;
            QMouseEvent* e =static_cast<QMouseEvent*>(event);
            this->move((e->screenPos() -pressdot).toPoint());
            return true;
        }
        else
        {
           if(filepath.isEmpty())return true;
           showButton(1);
           hidebutton->start(5000);
        }

        return true;
    }

    else if(event->type() == QEvent::MouseButtonRelease)
    {
        if(watched ==this)
        {
            ispress =false;
        }
        return true;
    }

    if(event->type() == QEvent::WindowActivate)
    {
            volume->move(ui->volume_Lab->pos().x() +ui->volume_Lab->width()/2 -volume->width()/2,ui->progressbar->y() -volume->height() -Public_Function::getScaleSize(12));
            speed->move(ui->speed_Lab->pos().x() +ui->speed_Lab->width()/2 -speed->width()/2,ui->progressbar->y() -speed->height() -Public_Function::getScaleSize(12));
            return true;
    }
    return QWidget::eventFilter(watched,event);
}

void ToolWidget::pressMiniPlayer()
{
    if(filepath.isEmpty())return;
    if(isfinish){
        emit sendStartPlaySignal(filepath,volume->getVolume(),speed->getCurrentSpeed(),pixmap,&videowidth,&videoheight);
        videowidth =4096;
        videoheight =2160;
        isfinish =false;
        ui->Player->hide();
        ui->player_Lab->setObjectName("minplayer");
        ui->player_Lab->changePixmap(QPixmap(":/Pixmap/pause-1@2x.png"));
        return;
    }

    if(ui->player_Lab->objectName().compare("minplayer") ==0)
    {
        ui->player_Lab->setObjectName("minpause");
        ui->player_Lab->changePixmap(QPixmap(":/Pixmap/bofang@2x.png"));
        emit sendPausePlaySignal();

        ui->Player->setObjectName("maxplayer");
        pressMaxPlayer();
        ui->Player->show();
    }
    else if(ui->player_Lab->objectName().compare("minpause") ==0)
    {
        ui->player_Lab->setObjectName("minplayer");
        ui->player_Lab->changePixmap(QPixmap(":/Pixmap/pause-1@2x.png"));
        if(!ui->Player->isHidden())ui->Player->hide();
        emit sendContinuePlaySignal();
    }
}

void ToolWidget::pressMaxPlayer()
{
    if(filepath.isEmpty())return;
    if(isfinish){
        emit sendStartPlaySignal(filepath,volume->getVolume(),speed->getCurrentSpeed(),pixmap,&videowidth,&videoheight);
        videowidth =4096;
        videoheight =2160;
        isfinish =false;
        ui->Player->hide();
        ui->player_Lab->setObjectName("minplayer");
        ui->player_Lab->changePixmap(QPixmap(":/Pixmap/pause-1@2x.png"));
        return;
    }
    if(ui->Player->objectName().compare("maxplayer") ==0)
    {
        ui->Player->setObjectName("maxpause");
        if(isfull)
        {
            ui->Player->changeSizeAndPixmap(Public_Function::getScaleSize(156,156),QPixmap(":/Pixmap/play-big-1@2x.png"));
            ui->Player->changePixmapSize(Public_Function::getScaleSize(56,74),2);
        }
        else
        {
            ui->Player->changeSizeAndPixmap(Public_Function::getScaleSize(98,98),QPixmap(":/Pixmap/play-big-1@2x.png"));
            ui->Player->changePixmapSize(Public_Function::getScaleSize(36,46),1);
        }
    }
    else if(ui->Player->objectName().compare("maxpause") ==0)
    {
        ui->Player->setObjectName("maxplayer");
        ui->Player->hide();
        emit sendContinuePlaySignal();
        ui->player_Lab->setObjectName("minpause");
        pressMiniPlayer();

        if(isfull)
        {
            ui->Player->changeSizeAndPixmap(Public_Function::getScaleSize(156,156),QPixmap(":/Pixmap/zanting@2x.png"));
            ui->Player->changePixmapSize(Public_Function::getScaleSize(56,74),2);
        }
        else
        {
            ui->Player->changeSizeAndPixmap(Public_Function::getScaleSize(98,98),QPixmap(":/Pixmap/zanting@2x.png"));
            ui->Player->changePixmapSize(Public_Function::getScaleSize(36,46),1);
        }
    }
}

void ToolWidget::pressFullScreen()
{
    if(ui->full_Lab->objectName().compare("full") ==0)
    {
        isfull =true;
        ui->full_Lab->setObjectName("mini");
        this->hide();
        resizeControl(2);
        this->show();
        ui->full_Lab->changePixmap(QPixmap(":/Pixmap/narrow-1@2x.png"));
    }
    else if(ui->full_Lab->objectName().compare("mini") ==0)
    {
        isfull =false;
        ui->full_Lab->setObjectName("full");
        this->hide();
        resizeControl(1);
        this->show();
        ui->full_Lab->changePixmap(QPixmap(":/Pixmap/quanping@2x.png"));
    }
    volume->hide();
    speed->hide();
    QEvent event(QEvent::WindowActivate);
    QApplication::sendEvent(this,&event);
}

void ToolWidget::pressVolume()
{
    QEvent event(QEvent::WindowActivate);
    QApplication::sendEvent(this,&event);
    if(ui->volume_Lab->objectName().compare("volume") ==0)
    {
        if(volume->isHidden())
        {
            volume->show();
            volume->raise();
        }
        else
        {
            ui->volume_Lab->setObjectName("mute");
            ui->volume_Lab->changePixmap(QPixmap(":/Pixmap/yinliang2@2x.png"));
            volume->changeVolume("mute");
            volume->hide();
            emit sendVolumeChangeSignal(0);
        }
    }
    else if(ui->volume_Lab->objectName().compare("mute") ==0)
    {
        ui->volume_Lab->setObjectName("volume");
        ui->volume_Lab->changePixmap(QPixmap(":/Pixmap/volume-1@2x.png"));
        volume->changeVolume("volume");
    }
}

void ToolWidget::pressFile()
{
    filepath = QFileDialog::getOpenFileName(0,"Open Video File","/"," *.MPEG *.AVI *.MOV *.MP4 *.FLV");
    if(filepath.isEmpty())return;
    ui->progressbar->show();
    thread->start();
    ui->Player->hide();
    ui->player_Lab->changePixmap(QPixmap(":/Pixmap/pause-1@2x.png"));
    emit sendStartPlaySignal(filepath,volume->getVolume(),speed->getCurrentSpeed(),pixmap,&videowidth,&videoheight);
    hidebutton->start(5000);
    videowidth =4096;
    videoheight =2160;
}

void ToolWidget::showButton(int num)
{
    if(num ==0)
    {
       ui->progressbar->hide();
       ui->player_Lab->hide();
       ui->time_Lab->hide();
       ui->speed_Lab->hide();
       ui->volume_Lab->hide();
       ui->file_Lab->hide();
       ui->full_Lab->hide();
       ui->screenshot_Lab->hide();
       ui->rotate_Lab->hide();
       ui->close_Lab->hide();
       speed->hide();
       volume->hide();
    }
    else if(num ==1)
    {
        ui->progressbar->show();
        ui->player_Lab->show();
        ui->time_Lab->show();
        ui->speed_Lab->show();
        ui->volume_Lab->show();
        ui->file_Lab->show();
        ui->full_Lab->show();
        ui->screenshot_Lab->show();
        ui->rotate_Lab->show();
        ui->close_Lab->show();
    }

}

void ToolWidget::rotatePixmap()
{
    m_width =this->width();
    m_height=this->height();
    m_width = videowidth<m_width?videowidth:m_width;
    m_height = videoheight<m_height?videoheight:m_height;

    if(rotate ==1)
    {
        QTransform transform;
        transform.rotate(90);
        *pixmap = (*pixmap).transformed(transform,Qt::SmoothTransformation);
    }

    if(isscreenshot)
    {
        isscreenshot =false;
        if(filepath.isEmpty())return;
        int w =0;
        int h =0;
        if(rotate ==0){
            w =m_width;
            h =m_height;
        }
        else
        {
            float num = float(videowidth)/videoheight;
            w= m_height/num;
            h= m_height;
        }
        QPixmap mpix =pixmap->scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        emit sendScreenshotPixmapSignal(mpix);
    }
    mpixmap =*pixmap;
    this->update();
}

void ToolWidget::getUpdateTimeSignal(QString time, int counttime, int currenttime)
{
    ui->time_Lab->setText(time);
    ui->progressbar->setMaximum(counttime);
    ui->progressbar->setProgressbarVlaue(currenttime);
    if(currenttime >= counttime)
    {
        isfinish =true;
        emit sendStopPlaySignal();
        hidebutton->stop();
        showButton(1);
        if(isfull)
        {
            ui->Player->changeSizeAndPixmap(Public_Function::getScaleSize(156,156),QPixmap(":/Pixmap/play-big-1@2x.png"));
            ui->Player->changePixmapSize(Public_Function::getScaleSize(56,74),2);
        }
        else
        {
            ui->Player->changeSizeAndPixmap(Public_Function::getScaleSize(98,98),QPixmap(":/Pixmap/play-big-1@2x.png"));
            ui->Player->changePixmapSize(Public_Function::getScaleSize(36,46),1);
        }
        ui->player_Lab->changePixmap(QPixmap(":/Pixmap/bofang@2x.png"));
        ui->Player->show();
    }
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(VideoPlayerInterFace, ToolWidget)//第一个参数为接口类名，第二个参数为当前类名
#endif // QT_VERSION < 0x050000
