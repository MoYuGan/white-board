#include "timerinterface.h"
#include "Public/public_function.h"
#include <QMouseEvent>
#include <QDebug>

TimerInterface::TimerInterface(QWidget *parent) : TimerPlugin(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    initCustom();
    initConnect();
}

void TimerInterface::initCustom()
{
    this->setGeometry(0,0,Public_Function::getScaleSize(420),Public_Function::getScaleSize(604));
    titelLab = new QLabel(this);
    titelLab->setFixedSize(Public_Function::getScaleSize(50),Public_Function::getScaleSize(16));
    titelLab->setFont(Public_Function::getFont(16));
    titelLab->setStyleSheet("font-family:Microsoft YaHei Bold; text-align: left;color:#444444;");
    titelLab->setText(tr("计时器"));

    closeLab = new QLabel(this);
    closeLab->setFixedSize(Public_Function::getScaleSize(18),Public_Function::getScaleSize(18));
    closeLab->setScaledContents(true);
    closeLab->setPixmap(QPixmap(":/images/TimerPixmap/guanbi@2x.png"));
    closeLab->installEventFilter(this);

    centreLab = new QLabel(this);
    centreLab->setFixedSize(Public_Function::getScaleSize(96),Public_Function::getScaleSize(32));
    centreLab->setFont(Public_Function::getFont(32));
    centreLab->setStyleSheet("font-family: Microsoft YaHei Bold;text-align: center;color: #222222;");
    centreLab->setText("计时器");
    centreLab->hide();


    buttonFra = new QFrame(this);
    buttonFra->setFixedSize(Public_Function::getScaleSize(380),Public_Function::getScaleSize(46));
    buttonFra->setStyleSheet(QString("background: #f0f0f0;border: %1px; solid #e0e0e0;border-radius: %2px;").arg(Public_Function::getScaleSize(1)).arg(Public_Function::getScaleSize(23)));

    timerBtn = new QPushButton(this);
    timerBtn->setFixedSize(Public_Function::getScaleSize(189),Public_Function::getScaleSize(42));
    timerBtn->setStyleSheet(QString("background: #1486fa;border-radius: %1px;font-family: Microsoft YaHei Regular;"
                                         "text-align: center;color:white").arg(Public_Function::getScaleSize(21)));
    timerBtn->setText(tr("计时器"));

    downBtn = new QPushButton(this);
    downBtn->setFixedSize(Public_Function::getScaleSize(189),Public_Function::getScaleSize(42));
    downBtn->setStyleSheet(QString("background: #f0f0f0;border-radius: %1px;"
                                        "border:none;color:#666666").arg(Public_Function::getScaleSize(21)));
    downBtn->setText(tr("倒计时"));

    timerWidget = new TimerWidget(this);
    timerWidget->setFixedSize(Public_Function::getScaleSize(228,372));

    downWidget = new DownWidget(this);
    downWidget->setFixedSize(Public_Function::getScaleSize(228,372));
    downWidget->hide();

    vlayout = new QVBoxLayout(this);
    hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(titelLab);
    hlayout1->addStretch();
    hlayout1->addWidget(closeLab);
    hlayout1->setContentsMargins(Public_Function::getScaleSize(12),Public_Function::getScaleSize(6),
                                 Public_Function::getScaleSize(12),Public_Function::getScaleSize(6));

    hlayout2 = new QHBoxLayout;
    hlayout2->addStretch();
    hlayout2->addWidget(centreLab);
    hlayout2->addStretch();

    hlayout3 = new QHBoxLayout(buttonFra);
    hlayout3->setContentsMargins(0,0,0,0);
    hlayout3->setSpacing(0);
    hlayout3->addWidget(timerBtn);
    hlayout3->addWidget(downBtn);

    hlayout4 = new QHBoxLayout;
    hlayout4->addWidget(timerWidget);
    hlayout4->addWidget(downWidget);

    vlayout->addLayout(hlayout1);
    vlayout->addStretch(0);
    vlayout->addLayout(hlayout2);
    vlayout->addStretch(1);
    vlayout->addWidget(buttonFra);
    vlayout->addStretch(1);
    vlayout->addLayout(hlayout4);
    vlayout->addStretch(2);


}

void TimerInterface::updateLanguage(bool isChinese)
{
    if( isChinese)
    {
        titelLab->setText(tr("计时器"));
        centreLab->setText(tr("计时器"));
        downBtn->setText(tr("倒计时"));
        timerBtn->setText(tr("计时器"));
    }else
    {
        titelLab->setText("Clock");
        centreLab->setText("Clock");
        downBtn->setText("CountDown");
        timerBtn->setText("Clocking");

    }
    if( downWidget != nullptr)
        downWidget->setLanguage(isChinese);
    update();

}

void TimerInterface::initConnect()
{
    connect(timerBtn,&QPushButton::clicked,this,[=](){
        timerBtn->setStyleSheet(QString("background: #1486fa;border-radius: %1px;font-family: Microsoft YaHei Regular;text-align: center;color:white").arg(Public_Function::getScaleSize(21)));
        downBtn->setStyleSheet(QString("background: #f0f0f0;border-radius: %1px;border:none;color:#666666").arg(Public_Function::getScaleSize(21)));
        downWidget->hide();
        timerWidget->show();
    });

    connect(downBtn,&QPushButton::clicked,this,[=](){
        timerBtn->setStyleSheet(QString("background: #f0f0f0;border-radius: %1px;border:none;color:#666666").arg(Public_Function::getScaleSize(21)));
        downBtn->setStyleSheet(QString("background: #1486fa;border-radius: %1px;font-family: Microsoft YaHei Regular;text-align: center;color: white").arg(Public_Function::getScaleSize(21)));
        timerWidget->hide();
        downWidget->show();
    });

    connect(timerWidget,&TimerWidget::sendMessage,this,&TimerInterface::timerSizeChange);

    connect(downWidget,&DownWidget::sendMessage,this,&TimerInterface::downSizeChange);
}

void TimerInterface::timerSizeChange(QString str)
{
    sizestring =str;
    if(str == "max")
    {
        buttonFra->hide();
        closeLab->hide();
        titelLab->hide();
        QDesktopWidget *desktop = QApplication::desktop();
        this->move(0,0);
        this->setFixedSize(desktop->width(),desktop->height());
        timerWidget->setFixedSize(Public_Function::getScaleSize(590),Public_Function::getScaleSize(822));
        centreLab->show();
        centreLab->setFixedSize(Public_Function::getScaleSize(96),Public_Function::getScaleSize(36));
        centreLab->setText("计时器");
        centreLab->setFont(Public_Function::getFont(32));
        centreLab->setStyleSheet(QString("width: %1px;height: %2px;font-family: Microsoft YaHei Bold;").arg(
                                         Public_Function::getScaleSize(96)).arg(Public_Function::getScaleSize(32)));
    }
    else if(str == "min")
    {
        closeLab->show();
        titelLab->show();
        buttonFra->show();
        centreLab->hide();
        QDesktopWidget *desktop = QApplication::desktop();
        timerWidget->setFixedSize(Public_Function::getScaleSize(228),Public_Function::getScaleSize(372));
        this->setFixedSize(Public_Function::getScaleSize(420),Public_Function::getScaleSize(604));
        this->move((desktop->width() -Public_Function::getScaleSize(420))/2,(desktop->height() -Public_Function::getScaleSize(604))/2);

    }
}

void TimerInterface::downSizeChange(QString str)
{
    sizestring =str;
    if(str == "max")
    {
        buttonFra->hide();
        closeLab->hide();
        titelLab->hide();
        QDesktopWidget *desktop = QApplication::desktop();
        this->move(0,0);
        this->setFixedSize(desktop->width(),desktop->height());
        downWidget->setFixedSize(Public_Function::getScaleSize(783),Public_Function::getScaleSize(822));
        centreLab->show();
        centreLab->setFixedSize(Public_Function::getScaleSize(96),Public_Function::getScaleSize(36));
        centreLab->setText("倒计时");
        centreLab->setFont(Public_Function::getFont(32));
        centreLab->setStyleSheet(QString("width: %1px;height: %2px;font-family: Microsoft YaHei Bold;").arg(
                                         Public_Function::getScaleSize(96)).arg(Public_Function::getScaleSize(32)));
    }
    else if(str == "min")
    {
        closeLab->show();
        titelLab->show();
        buttonFra->show();
        centreLab->hide();
        QDesktopWidget *desktop = QApplication::desktop();
        downWidget->setFixedSize(Public_Function::getScaleSize(228),Public_Function::getScaleSize(372));
        this->setFixedSize(Public_Function::getScaleSize(420),Public_Function::getScaleSize(604));
        this->move((desktop->width() -Public_Function::getScaleSize(420))/2,(desktop->height() -Public_Function::getScaleSize(604))/2);
    }

}

void TimerInterface::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawPath(drawRectRounded());
}

bool TimerInterface::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == closeLab)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            timerWidget->killThread();
            downWidget->killThread();
            emit this->widgetClosed();
            this->close();
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

QPainterPath TimerInterface::drawRectRounded()
{
    int r =Public_Function::getScaleSize(12);
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(rect().topRight().x() -r,0);
    path.arcTo(rect().width() -2*r,0,2*r,2*r,90,-90);
    path.lineTo(rect().bottomRight() -QPoint(0,r));
    path.arcTo(rect().bottomRight().x() -2*r,rect().bottomRight().y()-2*r,2*r,2*r,0,-90);
    path.lineTo(rect().bottomLeft() +QPoint(r,0));
    path.arcTo(rect().bottomLeft().x(),rect().bottomLeft().y() -2*r,2*r,2*r,-90,-90);
    path.lineTo(rect().topLeft() +QPoint(0,r));
    path.arcTo(0,0,2*r,2*r,-180,-90);
    return path;
}

void TimerInterface::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
       if(sizestring =="max")return;
       mousepressstate =true;
       mousepresspoint = event->screenPos() -this->pos();
    }
}

void TimerInterface::mouseMoveEvent(QMouseEvent *event)
{
    if(mousepressstate)
    {
        QPointF dot = event->screenPos() -mousepresspoint;
        this->move(dot.toPoint());
    }
}

void TimerInterface::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mousepressstate =false;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(TimerPlugin, TimerInterface)//第一个参数为接口类名，第二个参数为当前类名
#endif // QT_VERSION < 0x050000
