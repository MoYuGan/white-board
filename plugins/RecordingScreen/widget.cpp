#include "widget.h"
#include "ui_widget.h"
#include "QDebug"


static QPainterPath getRoundRectPath(const QRectF &rect, qreal topLeftRadius, qreal topRightRadius, qreal bottomLeftRadius,
                                     qreal bottomRightRadius)
{
    //偏离值(给圆角的开始和结束点设置一个偏离值，可以使圆角看起来更圆滑)
    qreal topLeftSubValue = topLeftRadius > 5 ? topLeftRadius*1.5/12.0 : 0;
    qreal topRightSubValue = topRightRadius > 5 ? topRightRadius*1.5/12.0 : 0;
    qreal bottomRightSubValue = bottomRightRadius > 5 ? bottomRightRadius*1.5/12.0 : 0;
    qreal bottomLeftSubValue = bottomLeftRadius > 5 ? bottomLeftRadius*1.5/12.0 : 0;
    qreal subValue = topLeftSubValue;
    //如果四个角偏离值不相等，不做偏离
    if (subValue != topRightSubValue ||
            subValue != bottomRightSubValue ||
            subValue != bottomLeftSubValue)
        subValue =  0;

    QPainterPath path;
    QPointF topLeftP1 = QPointF(rect.x() + subValue, rect.y() + topLeftRadius);
    QPointF topLeftP2 = QPointF(rect.x() + topLeftRadius, rect.y() + subValue);
    QPointF topRightP1 = QPointF(rect.x() + rect.width() - topRightRadius, rect.y() + subValue);
    QPointF topRightP2 = QPointF(rect.x() + rect.width() - subValue, rect.y() + topRightRadius);
    QPointF bottomRightP1 = QPointF(rect.x() + rect.width() - subValue, rect.y() + rect.height() - bottomLeftRadius);
    QPointF bottomRightP2 = QPointF(rect.x() + rect.width() - bottomLeftRadius, rect.y() + rect.height()- subValue);
    QPointF bottomLeftP1 = QPointF(rect.x() + bottomRightRadius, rect.y() + rect.height()- subValue);
    QPointF bottomLeftP2 = QPointF(rect.x() + subValue, rect.y() + rect.height()- bottomRightRadius);
    path.moveTo(topLeftP1);
    path.cubicTo(topLeftP1, rect.topLeft(), topLeftP2);
    path.lineTo(topRightP1);
    path.cubicTo(topRightP1, rect.topRight(), topRightP2);
    path.lineTo(bottomRightP1);
    path.cubicTo(bottomRightP1, rect.bottomRight(), bottomRightP2);
    path.lineTo(bottomLeftP1);
    path.cubicTo(bottomLeftP1, rect.bottomLeft(), bottomLeftP2);
    path.lineTo(topLeftP1);
    return path;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setFixedSize(Public_Function::getScaleSize(80,80));
    ui->start->resize(Public_Function::getScaleSize(54,54));
    ui->start->setIconSize(Public_Function::getScaleSize(54,54));
    ui->start->setIcon(QIcon(":/prc/ScreenCap/gongju11b@2x.png"));
    ui->start->setStyleSheet("QPushButton{border:none;}");

    ui->Label_Time->setFixedSize(52,11);
    ui->Label_Time->setText("00:00:00");
    ui->Label_Time->setAlignment(Qt::AlignCenter);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(ui->start);
    layout->addWidget(ui->Label_Time);
    layout->setSpacing(0);
    layout->setAlignment(this,Qt::AlignCenter);

    po = new QProcess(this);
    connect(ui->start,SIGNAL(clicked()),this,SLOT(SLOT_End()));

}

void Widget::StartTime()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(SLOT_CurrentTime()));
    timer->start(1000);
    Start();
}


void Widget::Moveto(double w, double h)
{
    this->move(w,h);
    qDebug() << "set x,y success!";
    qDebug() << "x = " << w << "y = " << h;
}

void Widget::Start()
{
    QString fileName = QCoreApplication::applicationDirPath();
    QDateTime curtime = QDateTime::currentDateTime();
    fileName += "/" + curtime.toString("yyyy-MM-dd hh:mm:ss") + ".avi";
    QString pixl = QString::number(QApplication::desktop()->width()) + "x" + QString::number(QApplication::desktop()->height());
    qDebug() << pixl ;
    QString threads = "1";
    QString rate = "18";
    QString program = "./ffmpeg";
    QStringList argu;
    argu.append("-y");
    argu.append("-f");
    argu.append("x11grab");
    argu.append("-r");
    argu.append(rate);
    argu.append("-threads");
    argu.append(threads);
    argu.append("-s");
    argu.append(pixl);
    argu.append("-i");
    argu.append(":0.0");

    argu.append("-f");
    argu.append("alsa");
    argu.append("-i");
    argu.append("pulse");
    argu.append("-b:v");
    argu.append("2600k");
    argu.append("-q:v");
    argu.append("5");
    argu.append("-b:a");
    argu.append("200k");
    argu.append("-q:a");
    argu.append("5");
    //无损音质 因Bits太大 不采用
    //    argu.append("-acodec");
    //    argu.append("flac");
    //无损画质 因Bits太大 不采用
    //    argu.append("-vcodec");
    //    argu.append("ffvhuff");

    argu.append(fileName);
    qDebug() << "argu = " << argu.join(" ");
    po->start(program,argu);

}

void Widget::SLOT_CurrentTime()
{
    time ++;
    int hour = time / 3600;
    int min = (time - hour * 3600) / 60;
    int second = (time - hour * 3600 - min * 60);
    QTime cur(hour,min,second);
    ui->Label_Time->setText(" " + cur.toString("hh:mm:ss"));
    update();
}

void Widget::SLOT_End()
{
    if (po)
    {
        po->close();
        delete po;
    }
    timer->stop();
    close();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::transparent);
    painter.setPen(QPen(QColor(185, 185, 185)));
    painter.setBrush(QBrush(Qt::white));
    QRectF rect = QRectF(QPointF(1, 7),
                         QPointF(this->width()  - 1, this->height()  - 1));
    painter.drawPath(getRoundRectPath(rect, 12, 12, 4, 4));

}

Widget::~Widget()
{
    delete ui;
}

