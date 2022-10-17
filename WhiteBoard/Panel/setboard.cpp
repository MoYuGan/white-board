#include "setboard.h"
#include "ui_setboard.h"
#include "Public/public_function.h"
#include <QDebug>
#include "applicationconfig.h"

SetBoard::SetBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetBoard)
{
    ui->setupUi(this);
    QIcon icon(QPixmap(":/images/main/menu/qiehuan@2x.png"));
    ui->move_Btn->setIcon(icon);
    ui->move_Btn->setFixedSize(Public_Function::getScaleSize(138,34));
    ui->move_Btn->setIconSize(Public_Function::getScaleSize(138,34));
    ui->move_Btn->setStyleSheet(QString("border-radius:%1px;").arg(Public_Function::getScaleSize(17)));
    connect(ui->move_Btn,&QPushButton::clicked,this,[=](){ui->frame->swithcPixmap();});
    connect(ui->frame,&Frame_2::sendOpenSignal,this,[=](){emit sendAgainOpenBoardSignal();});
    connect(ui->switch_Btn,&PushButton_13::clicked,this,[=](){
        if(!ui->switch_Btn->isOpen())
        {
            ui->title5_Lab->hide();
            ui->frame->setPixmapShow(3);
            ui->move_Btn->hide();
            emit sendCloseBoardSignal();
        }
        else
        {
            emit sendOpenBoardSignal();
        }
       });

}

SetBoard::~SetBoard()
{
    delete ui;
}

void SetBoard::setBoardNumber(int num)
{
    if(num ==0)
    {
        /*********未连接*********/
        initWidget();
        this->setFixedSize(Public_Function::getScaleSize(800,460));
        ui->verticalLayout->removeItem(ui->horizontalLayout_4);
        ui->switch_Btn->hide();
        ui->title4_Lab->show();
        ui->frame->setPixmapShow(0);
        ui->title5_Lab->hide();
        ui->move_Btn->hide();
    }
    else if(num ==1)
    {
        /*********连接一块副板*********/
       initWidget();
       ui->switch_Btn->show();
       ui->title5_Lab->show();
       ui->verticalLayout->removeItem(ui->horizontalLayout_4);
       ui->verticalLayout->insertItem(3,ui->horizontalLayout_4);
       ui->frame->setPixmapShow(1);
       ui->move_Btn->hide();
    }
    else if(num ==2)
    {
        /*********连接两块副板*********/
        initWidget();
        ui->switch_Btn->show();
        ui->title5_Lab->show();
        ui->verticalLayout->removeItem(ui->horizontalLayout_4);
        ui->verticalLayout->insertItem(3,ui->horizontalLayout_4);
        ui->frame->setPixmapShow(2);
        ui->move_Btn->show();
    }
    else if(num ==3)
    {
        /*********关闭副板*********/
        initWidget();
        ui->switch_Btn->show();
        ui->verticalLayout->removeItem(ui->horizontalLayout_4);
        ui->verticalLayout->insertItem(3,ui->horizontalLayout_4);
        ui->title5_Lab->hide();
        ui->frame->setPixmapShow(3);
    }

    update();
}

void SetBoard::initWidget()
{
    this->setFixedSize(Public_Function::getScaleSize(800,530));
    ui->horizontalLayout_2->setContentsMargins(Public_Function::getScaleSize(21),Public_Function::getScaleSize(16),
                                           Public_Function::getScaleSize(21),Public_Function::getScaleSize(19));
    ui->title_Lab->setFixedSize(Public_Function::getScaleSize(67,18));
    ui->title_Lab->setStyleSheet(QString("color:rgb(68,68,68);font-size:%1px;").arg(Public_Function::getScaleSize(16)));
    ui->title_Lab->setText(tr("白板设置"));
    ui->close_Lab->installEventFilter(this);
    ui->close_Lab->setFixedSize(Public_Function::getScaleSize(25,25));
    ui->close_Lab->setPixmap(QPixmap(":/images/main/menu/guanbi@2x.png"));
    ui->close_Lab->setScaledContents(true);

    ui->horizontalLayout->setContentsMargins(Public_Function::getScaleSize(30),Public_Function::getScaleSize(0),
                                           Public_Function::getScaleSize(0),Public_Function::getScaleSize(16));
    ui->title2_Lab->setStyleSheet(QString("color:rgb(102,102,102);font-size:%1px;").arg(Public_Function::getScaleSize(14)));
    ui->title2_Lab->setText(tr("记忆黑板启动设置:"));
    ui->title2_Lab->setFixedSize(Public_Function::getScaleSize(126,14));

    ui->horizontalLayout_3->setContentsMargins(Public_Function::getScaleSize(30),Public_Function::getScaleSize(0),
                                           Public_Function::getScaleSize(0),Public_Function::getScaleSize(12));
    ui->title3_Lab->setStyleSheet(QString("color:rgb(68,68,68);font-size:%1px;").arg(Public_Function::getScaleSize(14)));
    ui->title3_Lab->setText(tr("副板"));
    ui->title4_Lab->setStyleSheet(QString("color:rgb(238,63,63);font-size:%1px;").arg(Public_Function::getScaleSize(14)));
    ui->title4_Lab->setText(tr("(未连接)"));
    ui->title4_Lab->hide();


    ui->horizontalLayout_4->setContentsMargins(Public_Function::getScaleSize(30),Public_Function::getScaleSize(0),
                                           Public_Function::getScaleSize(0),Public_Function::getScaleSize(13));
    ui->title5_Lab->setStyleSheet(QString("color:rgb(68,68,68);font-size:%1px;").arg(Public_Function::getScaleSize(16)));
    ui->title5_Lab->setText(tr("记忆黑板功能已开启，副板书写内容将同步至白板软件"));

    ui->horizontalLayout_5->setContentsMargins(Public_Function::getScaleSize(0),Public_Function::getScaleSize(0),
                                               Public_Function::getScaleSize(0),Public_Function::getScaleSize(13));
}

bool SetBoard::switchBtnState()
{
    if(ui->switch_Btn->isOpen())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SetBoard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(this->rect(),Public_Function::getScaleSize(12),Public_Function::getScaleSize(12));
}

bool SetBoard::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched ==ui->close_Lab)
        {
            this->close();
            emit sendSetCloseSignal();
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void SetBoard::mousePressEvent(QMouseEvent *event)
{
    ispress =true;
    pressdot =event->pos();
}

void SetBoard::mouseMoveEvent(QMouseEvent *event)
{
    if(ispress)
    {
        this->move(event->globalPos() -pressdot);
    }
}

void SetBoard::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    ispress =false;
}
