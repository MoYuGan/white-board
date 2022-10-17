#include "audiochoose.h"
#include "ui_audiochoose.h"

AudioChoose::AudioChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioChoose)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    QDesktopWidget* desktop = new QDesktopWidget;
    int width = desktop->width();
    int height = desktop->height();
    w = new Widget;

    //build UI
    QFont font;
    font.setFamily("Microsoft YaHei Bold, Microsoft YaHei Bold-Bold;");
    font.setWeight(Public_Function::getScaleSize(700));
    font.setPixelSize(Public_Function::getScaleSize(20));
    ui->Label_TEXT->setFont(font);
    ui->Label_TEXT->setAlignment(Qt::AlignCenter);
    ui->Label_TEXT->setFixedSize(Public_Function::getScaleSize(119,22));
    ui->Label_TEXT->setText("-  屏幕录制  -");
    ui->Label_TEXT->setStyleSheet("color:rgb(20,134,250)");

    QFont font_s;
    font_s.setFamily("Microsoft YaHei Regular, Microsoft YaHei Regular-Regular;");
    font_s.setWeight(Public_Function::getScaleSize(400));
    font_s.setPixelSize(Public_Function::getScaleSize(18));
    ui->Lable_Choose->setFont(font_s);
    ui->Lable_Choose->setAlignment(Qt::AlignCenter);
    ui->Lable_Choose->setText("请选择麦克风设备开始录屏");
    ui->Lable_Choose->setFixedSize(Public_Function::getScaleSize(216,20));
    ui->Lable_Choose->setStyleSheet("color:rgb(68,68,68)");

    ui->Btn_Close->setFixedSize(Public_Function::getScaleSize(18,19));
    ui->Btn_Close->setIconSize(Public_Function::getScaleSize(18,18));
    ui->Btn_Close->setIcon(QIcon(":/prc/ScreenCap/jisuanqi10@2x.png"));
    ui->Btn_Close->setStyleSheet("border:none;color:rgb(170,170,170)");

    QFont font_start;
    font_start.setFamily("Microsoft YaHei Regular, Microsoft YaHei Regular-Regular;");
    font_start.setWeight(Public_Function::getScaleSize(400));
    font_start.setPixelSize(Public_Function::getScaleSize(16));
    ui->Btn_Start->setFont(font_start);
    ui->Btn_Start->setFixedSize(Public_Function::getScaleSize(100,42));
    ui->Btn_Start->setText("开始");
    ui->Btn_Start->setStyleSheet("border-radius:4px;text-align:center;color:rgb(255,255,255);background:#cccccc;border:none");
    ui->Btn_Start->setEnabled(false);

    ui->Btn_quit->setFont(font_start);
    ui->Btn_quit->setFixedSize(Public_Function::getScaleSize(100,42));
    ui->Btn_quit->setText("取消");
    ui->Btn_quit->setStyleSheet("border-radius:4px;text-align:center;color:rgb(102,102,102);background:#ffffff;border: 1px solid #e0e0e0");

    QFont font_device;
    font_device.setFamily("Microsoft YaHei Regular, Microsoft YaHei Regular-Regular;");
    font_device.setWeight(Public_Function::getScaleSize(400));
    font_device.setPixelSize(Public_Function::getScaleSize(14));

    m_Combobox = new  CP_Combobox(this);
    m_List = new CP_ListVIew;
    m_List->raise();

    QHBoxLayout* layout1 = new QHBoxLayout;
    layout1->addWidget(ui->Btn_Close);
    layout1->setAlignment(Qt::AlignRight);

    QHBoxLayout* layout2 = new QHBoxLayout;
    layout2->addWidget(ui->Label_TEXT);
    layout2->setAlignment(Qt::AlignCenter);

    QHBoxLayout* layout3 = new QHBoxLayout;
    layout3->addWidget(ui->Lable_Choose);
    layout3->setAlignment(Qt::AlignCenter);

    QHBoxLayout* layout4 = new QHBoxLayout;
    layout4->addWidget(m_Combobox);
    //layout4->setAlignment(Qt::AlignCenter);

    QHBoxLayout* layout5 = new QHBoxLayout;
    layout5->addWidget(ui->Btn_Start);
    layout5->addWidget(ui->Btn_quit);
    layout5->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->setSpacing(Public_Function::getScaleSize(20));
    layout->addStretch(1);
    layout->setContentsMargins(10,10,10,5);

    this->move((width - this->width()) /2,(height - this->height()) /2);

    m_Combobox->installEventFilter(this);

    init();
}


AudioChoose::~AudioChoose()
{
    delete ui;
    delete m_Combobox;
    delete m_List;
    delete w;
}

void AudioChoose::Btn_MoveTo(double width, double height)
{
    qDebug() << "the w :" << w;
    w->Moveto(width,height);
}


void AudioChoose::init()
{
    connect(ui->Btn_Close,SIGNAL(clicked()),this,SLOT(slot_Close()));
    connect(ui->Btn_quit,SIGNAL(clicked()),this,SLOT(slot_Close()));
    connect(ui->Btn_Start,SIGNAL(clicked()),this,SLOT(slot_Start()));
    connect(m_List,SIGNAL(signal_clickList()),this,SLOT(slot_ChangeText()));
}

void AudioChoose::slot_Close()
{
    //this->close();
    this->deleteLater();
}

void AudioChoose::slot_Start()
{
    this->hide();
    w->show();
    w->StartTime();


}

void AudioChoose::slot_ChangeText()
{
    m_Combobox->Combo_Setting(m_List->m_Text);
    ui->Btn_Start->setStyleSheet("border-radius:4px;text-align:center;color:rgb(102,102,102);background:#ffffff;border: 1px solid #e0e0e0");
    m_List->hide();
    ui->Btn_Start->setEnabled(true);
}

void AudioChoose::paintEvent(QPaintEvent *event)
{

    QWidget::paintEvent(event);


    QPainter painter(this);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    this->setFixedSize(Public_Function::getScaleSize(396,296));
    QColor color(105, 105, 105);
    int border = 6;
    int j;
    int radius = 12;
    path.addRoundedRect(border, border, this->width() - border*2, this->height() - border*2, radius, radius);
    painter.fillPath(path, QBrush(QColor(255,255,255)));
    for(int i=0; i<border; i++)
    {
        j = border - i;
        path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2, radius, radius);
        switch(i)
        {
        case 0:
            color.setAlpha(80);
            break;
        case 1:
            color.setAlpha(50);
            break;
        case 2:
            color.setAlpha(20);
            break;
        case 3:
            color.setAlpha(15);
            break;
        case 4:
            color.setAlpha(10);
            break;
        case 5:
            color.setAlpha(7);
            break;
        default:
            break;
        }
        QPen pen;
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(pen);
        painter.drawPath(path);
    }

}


bool AudioChoose::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_Combobox)
    {
        if(event->type() == QMouseEvent::MouseButtonPress)
        {
            m_List->move(this->x() + m_Combobox->x() ,this->y() + m_Combobox->y() + m_Combobox->height() - 2 );
            if(!m_Combobox->m_isClick)
            {
                m_List->hide();
                m_isShowList = false;
            }
            else
            {
                m_List->show();
                m_isShowList = true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}
