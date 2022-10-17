#include "maininterface.h"
#include "ui_maininterface.h"
#include "Public/public_function.h"
#include <QButtonGroup>
#include <QDebug>

#define HTTPLESSONS   "https://test-yunkec.amdox.com.cn/prepare_a_lesson/textbook_list?telephone="
#define HTTPNET   "https://test-yunkec.amdox.com.cn/netdisc?telephone="
MainInterface::MainInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInterface)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    initresize();
    initconnect();
}

MainInterface::~MainInterface()
{
    delete ui;
}

void MainInterface::initresize()
{
    this->setFixedSize(Public_Function::getScaleSize(1065,612));
    ui->verticalLayout->setSpacing(0);  
    ui->titleLab->setFixedSize(Public_Function::getScaleSize(124,30));
    ui->tabWidget->setFixedSize(Public_Function::getScaleSize(873,592));
    ui->lessonsBtn->setFixedSize(Public_Function::getScaleSize(134,48));
    ui->lessonsBtn->setTextAndPixmap(tr("我的备课"),QPixmap(":/pixmap/caidan1b@2x.png"));
    ui->networkBtn->setFixedSize(Public_Function::getScaleSize(134,48));
    ui->networkBtn->setTextAndPixmap(tr("我的网盘"),QPixmap(":/pixmap/caidan2@2x.png"));
    group = new QButtonGroup(this);
    group->setExclusive(true);
    group->addButton(ui->lessonsBtn);
    group->addButton(ui->networkBtn);
    ui->lessonsBtn->setChecked(true);

    ui->photoLab->setFixedSize(Public_Function::getScaleSize(54,54));
    ui->photoLab->setPixmap_m(QPixmap(":/pixmap/2.jpg"));

    ui->nameLab->setFixedSize(Public_Function::getScaleSize(134,16));
    ui->nameLab->setText("黄彦哲");
    ui->nameLab->setAlignment(Qt::AlignCenter);
    ui->nameLab->setStyleSheet(QString("color:rgb(255,255,255);font-size:%1px;").arg(14));

    ui->logoutLab->setFixedSize(Public_Function::getScaleSize(74,32));
    ui->logoutLab->setStyleSheet(QString("border:%1px solid rgb(0,157,255);background:transparent;color:rgb(255,255,255);font-size:%2;border-radius:%3px")
                                 .arg(Public_Function::getScaleWidth(1)).arg(Public_Function::getScaleWidth(12)).arg(Public_Function::getScaleWidth(5)));
    ui->logoutLab->setAlignment(Qt::AlignCenter);
    ui->logoutLab->setText(tr("注销账号"));
    ui->logoutLab->installEventFilter(this);

    ui->closeBtn->setFixedSize(Public_Function::getScaleSize(74,32));
    ui->closeBtn->setStyleSheet(QString("background-color:rgb(17,111,206);color:white;border-radius:%1px;font-size:%2px").arg(Public_Function::getScaleWidth(4)).arg(Public_Function::getScaleWidth(12)));
    ui->closeBtn->setText(tr("关闭"));

    ui->horizontalLayout_7->setContentsMargins(Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(29),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(39));
    ui->horizontalLayout->setContentsMargins(Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(12));
    ui->horizontalLayout_2->setContentsMargins(Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(93));
    ui->horizontalLayout_3->setContentsMargins(Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(14));
    ui->horizontalLayout_4->setContentsMargins(Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(30));
    ui->horizontalLayout_5->setContentsMargins(Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(0),Public_Function::getScaleWidth(80));

    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setContentsMargins(0,0,0,0);
    m_lessonsWid = new CustomWidget_9(ui->tabWidget);
    m_networkWid = new CustomWidget_10(ui->tabWidget);
    ui->tabWidget->addTab(m_lessonsWid,"les");
    ui->tabWidget->addTab(m_networkWid,"net");
    ui->tabWidget->setCurrentWidget(m_lessonsWid);
}

void MainInterface::initconnect()
{

    connect(ui->lessonsBtn,&Custom_Btn2::clicked,this,[=](){
        ui->networkBtn->setTextAndPixmap(tr("我的网盘"),QPixmap(":/pixmap/caidan2@2x.png"));
        ui->lessonsBtn->setTextAndPixmap(tr("我的备课"),QPixmap(":/pixmap/caidan1b@2x.png"));
        m_lessonsWid->reLoad();
        ui->tabWidget->setCurrentIndex(0);
    });
    connect(ui->networkBtn,&Custom_Btn2::clicked,this,[=](){
        ui->networkBtn->setTextAndPixmap(tr("我的网盘"),QPixmap(":/pixmap/caidan2b@2x.png"));
        ui->lessonsBtn->setTextAndPixmap(tr("我的备课"),QPixmap(":/pixmap/caidan1@2x.png"));
        m_networkWid->reLoad();
        ui->tabWidget->setCurrentIndex(1);
    });

#if 0
    connect(networkWid,&CustomWidget_10::sendMessage,[=](int a){
        if(a == 1)
        {
            this->hide();
            CustomWidget_11* updateWid = new CustomWidget_11(this->parentWidget());
            updateWid->show();
            connect(updateWid,&CustomWidget_11::sendCloseMassage11,[=](){
                this->show();
                updateWid->deleteLater();
            });
        }
        else if(a == 2)
        {
            this->hide();
            CustomWidget_12* updateWid = new CustomWidget_12(this->parentWidget());
            updateWid->show();

            connect(updateWid,&CustomWidget_12::sendCloseMassage12,[=](){
                this->show();
                updateWid->deleteLater();
            });

            connect(updateWid,&CustomWidget_12::sendAddMassage,[=](){
                this->hide();
                CustomWidget_20* addWid = new CustomWidget_20(this->parentWidget());
                addWid->show();
                connect(addWid,&CustomWidget_20::sendCloseMassage20,[=](){
                  updateWid->close();
                  updateWid->deleteLater();
                  addWid->close();
                  addWid->deleteLater();
                  this->show();
                });

                connect(addWid,&CustomWidget_20::sendCheckOut,[=](){
                    addWid->hide();
                    CustomWidget_13* fineshWid = new CustomWidget_13(this->parentWidget());
                    fineshWid->show();
                    connect(fineshWid,&CustomWidget_13::sendCloseMassage13,[=](){
                        fineshWid->close();
                        fineshWid->deleteLater();
                        addWid->deleteLater();
                        updateWid->deleteLater();
                        this->show();
                    });
                });

            });
        }
    });
#endif

    connect(ui->closeBtn,&QPushButton::clicked,this,[=](){
        emit this->widgetClosed();
    });
}

void MainInterface::getUrl(QString str)
{
    m_lessonsWid->loadWeb(HTTPLESSONS + str);
    m_networkWid->loadWeb(HTTPNET +str);
}

void MainInterface::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(this->rect(),QPixmap(":/pixmap/beijing@2x.png"));
}

QPainterPath MainInterface::drawRoundRect(int r)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-90);
    path.lineTo(this->width(),this->height() -r);
    path.arcTo(this->width() -2*r,this->height() -2*r,2*r,2*r,0,-90);
    path.lineTo(this->width() -r,this->height());
    path.arcTo(0,this->height() -2*r,2*r,2*r,-90,-90);
    path.lineTo(0,r);
    path.arcTo(0,0,2*r,2*r,180,-90);
    return path;
}

bool MainInterface::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->logoutLab)
    {

        if(event->type() == QEvent::MouseButtonPress)
        {
            qDebug()<< "注销账号" <<endl;
            emit cancellation();
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void MainInterface::changePicture(QPixmap p)
{
    ui->photoLab->setPixmap_m(p.scaled(ui->photoLab->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

void MainInterface::changeName(QString str)
{
    ui->nameLab->setText(str);
}
