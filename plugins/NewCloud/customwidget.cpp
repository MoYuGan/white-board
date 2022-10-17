#include "customwidget.h"
#include <QBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QtDebug>
#include <QListWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QScrollBar>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>
#include <QTextEdit>
#include <QButtonGroup>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QStackedLayout>
#include "customwidget.h"
#include <QPointer>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QStandardPaths>
/*****************************CustomWidget_3******************************/

CustomWidget_3::CustomWidget_3(QWidget *parent) : QListWidget(parent)
{
    this->setVerticalScrollMode(QListWidget::ScrollPerPixel);  //设置垂直滑动模式
    this->setSelectionMode(QAbstractItemView::NoSelection);   //设置此属性不会影响自定义item widget选中样式
    this->setStyleSheet(QString("QListWidget{border: none;background: transparent;}"));
    this->verticalScrollBar();
    this->verticalScrollBar()->setStyleSheet(QString("QScrollBar:vertical{width:%1px;background:transparent;margin:0px,0px,0px,0px;padding-top:0px;padding-bottom:0px;}"
                                             "QScrollBar::handle:vertical{width:%1px;background:rgba(0,0,0,25%);border-radius:%2px;}"
                                             "QScrollBar::handle:vertical:hover{width:%1px;background:rgba(0,0,0,50%);border-radius:%2px;}"
                                             "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent;border-radius:%2px;}"
                                             "QScrollBar::add-line:vertical{height:0px;width:0px;subcontrol-position:bottom;}"
                                             "QScrollBar::sub-line:vertical{height:0px;width:0px;subcontrol-position:top;}"
                                             "QScrollBar::add-line:vertical:hover{height:0px;width:0px;subcontrol-position:bottom;}"
                                             "QScrollBar::sub-line:vertical:hover{height:0px;width:0px;subcontrol-position:top;}"
                                             "QScrollBar::add-page:vertical:QScrollBar::sub-page:vertical{background:transparent;border-radius:%2px;}"
                                             ).arg(Public_Function::getScaleWidth(6)).arg(Public_Function::getScaleWidth(2)));

}


/********************************CustomWidget_4***********************************************/

CustomWidget_4::CustomWidget_4(QString st,QWidget *parent) : QWidget(parent),str(st)
{

}

void CustomWidget_4::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setFont(Public_Function::getFont(14));
    painter.drawText(this->rect(),Qt::AlignVCenter,str);
}


/********************************CustomWidget_5***********************************************/

CustomWidget_5::CustomWidget_5(QString st,QWidget *parent) : QWidget(parent),str(st)
{

}

void CustomWidget_5::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setFont(Public_Function::getFont(14));
    painter.drawText(this->rect(),Qt::AlignVCenter,str);
    painter.setPen(QPen(QColor(224,224,224),Public_Function::getScaleWidth(1)));
    painter.drawLine(this->rect().bottomLeft(),this->rect().bottomRight());
}


/********************************CustomWidget_1***********************************************/

CustomWidget_1::CustomWidget_1(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    lab = new QLabel(this);
    lab->setText(tr("手机:"));
    lab->setStyleSheet("color:rgba(68,68,68,1)");
    lab->setFont(Public_Function::getFont(16));
    lab->move(Public_Function::getScaleWidth(19),Public_Function::getScaleWidth(18));

    edit = new QLineEdit(this);
    edit->move(Public_Function::getScaleWidth(59),Public_Function::getScaleWidth(18));
    edit->setFocus();
    edit->setStyleSheet(QString("border-width:0;border-style:outset;color:rgba(0,0,0,1);font-size:%1px;").arg(Public_Function::getScaleWidth(16)));
    edit->setFixedSize(Public_Function::getScaleSize(220,46));
    edit->setPlaceholderText(tr("请输入手机号码"));
    //设置手机号码格式,只允许按格式输入
    QRegExp regexp("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    QRegExpValidator *validator = new QRegExpValidator(regexp);
    edit->setValidator(validator);

    down_lab = new QLabel(this);
    down_lab->setFixedSize(Public_Function::getScaleSize(20,12));
    down_lab->setScaledContents(true);
    down_lab->setPixmap(QPixmap(":/pixmap/zhankai3@2x.png"));
    down_lab->installEventFilter(this);
    down_lab->setObjectName("up");
    down_lab->setAlignment(Qt::AlignCenter);

    QHBoxLayout* hlayout1 = new QHBoxLayout();
    hlayout1->addWidget(lab);
    hlayout1->addWidget(edit);
    hlayout1->addStretch();
    hlayout1->addWidget(down_lab);

    list_lab = new QLabel(this);
    list_lab->setText(tr("历史登录"));
    list_lab->setFont(Public_Function::getFont(12));
    list_lab->setStyleSheet("color:rgba(136,136,136,1)");
    list_lab->hide();

    QHBoxLayout* hlayout2 = new QHBoxLayout();
    hlayout2->addWidget(list_lab);
    hlayout2->addStretch();

    listwidget = new CustomWidget_3(this);
    listwidget->hide();

    QHBoxLayout* hlayout3 = new QHBoxLayout();
    hlayout3->addWidget(listwidget);

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addStretch(0);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(2),Public_Function::getScaleWidth(15),0);

    connect(listwidget,&CustomWidget_3::currentRowChanged,this,&CustomWidget_1::setText);

}

void CustomWidget_1::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::white);
    painter.setPen(QPen(QColor(224,224,224),1));
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(9),Public_Function::getScaleWidth(9));
    painter.drawPath(path);

}

bool CustomWidget_1::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == down_lab)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(down_lab->objectName() == "up")
            {
                down_lab->setPixmap(QPixmap(":/pixmap/zhankai4@2x.png"));
                down_lab->setObjectName("down");
                disconnect(listwidget, &CustomWidget_3::currentRowChanged, this,&CustomWidget_1::setText);
                emit getTelNumber(listwidget);
                connect(listwidget,&CustomWidget_3::currentRowChanged,this,&CustomWidget_1::setText);
                list_lab->show();
                listwidget->show();
                if(1 >= listwidget->count())
                {
                    this->setFixedSize(Public_Function::getScaleSize(300,108));

                }
                 if(2 == listwidget->count())
                {
                    this->setFixedSize(Public_Function::getScaleSize(300,150));
                }
                else if(3 == listwidget->count())
                {
                    this->setFixedSize(Public_Function::getScaleSize(300,200));
                }
                else if(4 <= listwidget->count())
                {
                    this->setFixedSize(Public_Function::getScaleSize(300,234));
                }
            }
            else if(down_lab->objectName() == "down")
            {
                list_lab->hide();
                listwidget->hide();
                down_lab->setPixmap(QPixmap(":/pixmap/zhankai3@2x.png"));
                down_lab->setObjectName("up");
                this->setFixedSize(Public_Function::getScaleSize(300,50));
            }
            update();
            return true;
        }

    }
    return QWidget::eventFilter(watched,event);
}

void CustomWidget_1::setText(int num)
{
   QWidget *w = listwidget->itemWidget(listwidget->item(num));
   edit->setText(w->objectName());
   list_lab->hide();
   listwidget->hide();
   down_lab->setPixmap(QPixmap(":/pixmap/zhankai3@2x.png"));
   down_lab->setObjectName("up");
   this->setFixedSize(Public_Function::getScaleSize(300,50));
}

QString CustomWidget_1::getEditText()
{
    return edit->text();
}

void CustomWidget_1::setEditText(const QString &text)
{
    edit->setText(text);
}

void CustomWidget_1::setEditFocus()
{
    edit->setFocus();
}

/********************************CustomWidget_2***********************************************/
CustomWidget_2::CustomWidget_2(QWidget *parent) : QWidget(parent)
{
    lab = new QLabel(this);
    lab->setText(tr("密码:"));
    lab->setStyleSheet("color:rgba(68,68,68,1)");
    lab->setFont(Public_Function::getFont(16));
    lab->move(Public_Function::getScaleWidth(19),Public_Function::getScaleWidth(18));

    edit = new QLineEdit(this);
    edit->move(Public_Function::getScaleWidth(59),Public_Function::getScaleWidth(18));
    edit->setFont(Public_Function::getFont(16));
    edit->setStyleSheet(QString("border-width:0;border-style:outset;color:rgba(0,0,0,1);font-size:%1px;").arg(Public_Function::getScaleWidth(16)));
    edit->setEchoMode(QLineEdit::Password);
    edit->setFixedSize(Public_Function::getScaleSize(190,44));
    edit->setPlaceholderText(tr("输入登录密码"));
    edit->setMaxLength(16);

    QHBoxLayout* hlayout = new QHBoxLayout(this);
    hlayout->addWidget(lab);
    hlayout->addWidget(edit);
    hlayout->addStretch();
    hlayout->setContentsMargins(Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(2),0,0);

}

void CustomWidget_2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::white);
    painter.setPen(QPen(QColor(224,224,224),1));
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(9),Public_Function::getScaleWidth(9));
    painter.drawPath(path);

}

void CustomWidget_2::changeText(QString st1, QString st2,int num =0)
{
    lab->setText(st1);
    edit->setPlaceholderText(st2);
    if(st1 == "手机:")
    {
        //设置手机号码格式,只允许按格式输入
//        QRegExp regexp("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
//        QRegExpValidator *validator = new QRegExpValidator(regexp);
//        edit->setValidator(validator);
    }
    if(num ==0)
    {
        edit->setEchoMode(QLineEdit::Password);
    }
    else
    {
        edit->setEchoMode(QLineEdit::Normal);
    }
}

QString CustomWidget_2::getEditText()
{
    return edit->text();
}

void CustomWidget_2::clearEditText()
{
    edit->clear();
}

void CustomWidget_2::setEditText(const QString &text)
{
    edit->setText(text);
}


/********************************CustomWidget_6***********************************************/

CustomWidget_6::CustomWidget_6(QWidget *parent) : QWidget(parent)
{
    lab = new QLabel(this);
    lab->setText(tr("验证码:"));
    lab->setStyleSheet("color:rgba(68,68,68,1)");
    lab->setFont(Public_Function::getFont(16));
    lab->move(Public_Function::getScaleWidth(19),Public_Function::getScaleWidth(0));

    edit = new QLineEdit(this);
    edit->move(Public_Function::getScaleWidth(59),Public_Function::getScaleWidth(0));
    edit->setFont(Public_Function::getFont(16));
    edit->setStyleSheet(QString("border:none; border-style:outset; color:rgba(0,0,0,1); font-size:%1px;").arg(Public_Function::getScaleWidth(16)));
    edit->setFixedSize(Public_Function::getScaleSize(190,44));
    edit->setPlaceholderText(tr("输入验证码"));

    sendBtn = new QPushButton(this);
    sendBtn->setText("发送");
    sendBtn->setEnabled(false);
    sendBtn->setStyleSheet(QString("border:none;background:rgb(255,255,255);color:rgb(102,102,102);font-size:%1px").arg(Public_Function::getScaleWidth(16)));

    QHBoxLayout* hlayout = new QHBoxLayout(this);
    hlayout->setAlignment(Qt::AlignVCenter);
    hlayout->addWidget(lab);
    hlayout->addWidget(edit);
    hlayout->addWidget(sendBtn);
    hlayout->addStretch();
    hlayout->setContentsMargins(Public_Function::getScaleWidth(10),0,Public_Function::getScaleWidth(20),0);

    connect(sendBtn,&QPushButton::clicked,this,[=](){
        emit checkPhoneNumber();
    });


}

QString CustomWidget_6::getEditText()
{
    return edit->text();
}

void CustomWidget_6::enableBtn( bool bo)
{
   sendBtn->setEnabled(bo);
   if(bo)
    sendBtn->setStyleSheet(QString("border:none;background:rgb(255,255,255);color:rgb(20,134,250);font-size:%1px").arg(Public_Function::getScaleWidth(16)));
   else
    sendBtn->setStyleSheet(QString("border:none;background:rgb(255,255,255);color:rgb(102,102,102);font-size:%1px").arg(Public_Function::getScaleWidth(16)));
}

void CustomWidget_6::getPhoneNumber(QString st)
{
    str =st;
}

void CustomWidget_6::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::white);
    painter.setPen(QPen(QColor(224,224,224),1));
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(9),Public_Function::getScaleWidth(9));
    painter.drawPath(path);
}

void CustomWidget_6::getCode()
{
    QTimer *timer = new QTimer(this);
    sendBtn->setEnabled(false);
    timer->start(100);
    connect(timer,&QTimer::timeout,this,[=](){
        countTim--;
        timer->stop();
        sendBtn->setStyleSheet(QString("border:none;background:rgb(255,255,255);color:rgb(102,102,102);font-size:%1px").arg(Public_Function::getScaleWidth(16)));
        sendBtn->setText(QString("%1s").arg(countTim));
        timer->start(1000);
        if(countTim ==0)
        {
            timer->stop();
            countTim = 61;
            sendBtn->setStyleSheet(QString("border:none;background:rgb(255,255,255);color:rgb(20,134,250);font-size:%1px").arg(Public_Function::getScaleWidth(16)));
            sendBtn->setEnabled(true);
            sendBtn->setText("发送");
        }
    });
}

void CustomWidget_6::clearEditText()
{
    edit->clear();
}


/********************************CustomWidget_7***********************************************/
CustomWidget_7::CustomWidget_7(int num,QWidget *parent) : QWidget(parent),flage(num)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(Public_Function::getScaleSize(568,354));
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,(desktop->height() -this->height())/2);
    initLayout();
}

void CustomWidget_7::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::white);
    painter.setPen(QPen(QColor(224,224,224),1));
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(18),Public_Function::getScaleWidth(18));
    painter.drawPath(path);

}

bool CustomWidget_7::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == mcloseLab)
        {
            this->hide();
            emit sendCloseMassage7();
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void CustomWidget_7::initLayout()
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setSpacing(0);

    mtextLab = new QLabel(this);
    mtextLab->setStyleSheet(QString("color:rgb(68,68,68);font-size:%1").arg(Public_Function::getScaleWidth(16)));

    mcloseLab = new QLabel(this);
    mcloseLab->installEventFilter(this);
    mcloseLab->setFixedSize(Public_Function::getScaleSize(19,19));
    mcloseLab->setScaledContents(true);
    mcloseLab->setPixmap(QPixmap(":/pixmap/guanbi@2x.png"));
    QHBoxLayout *hlayout1 =new QHBoxLayout;
    hlayout1->addWidget(mtextLab);
    hlayout1->addStretch(0);
    hlayout1->addWidget(mcloseLab);
    hlayout1->setContentsMargins(Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(10));

    edit = new QTextEdit(this);
    edit->setFixedSize(Public_Function::getScaleSize(518,210));
    edit->setReadOnly(true);
    edit->setStyleSheet("border:none");
    edit->verticalScrollBar()->setStyleSheet(QString("QScrollBar:vertical{width:%1px;background:transparent;margin:0px,0px,0px,0px;padding-top:0px;padding-bottom:0px;}"
                                                           "QScrollBar::handle:vertical{width:%1px;background:rgba(0,0,0,25%);border-radius:%2px;}"
                                                           "QScrollBar::handle:vertical:hover{width:%1px;background:rgba(0,0,0,50%);border-radius:%2px;}"
                                                           "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent;border-radius:%2px;}"
                                                           "QScrollBar::add-line:vertical{height:0px;width:0px;subcontrol-position:bottom;}"
                                                           "QScrollBar::sub-line:vertical{height:0px;width:0px;subcontrol-position:top;}"
                                                           "QScrollBar::add-line:vertical:hover{height:0px;width:0px;subcontrol-position:bottom;}"
                                                           "QScrollBar::sub-line:vertical:hover{height:0px;width:0px;subcontrol-position:top;}"
                                                           "QScrollBar::add-page:vertical:QScrollBar::sub-page:vertical{background:transparent;border-radius:%2px;}"
                                                           ).arg(Public_Function::getScaleWidth(6)).arg(Public_Function::getScaleWidth(2)));

    if(flage == 0)
    {
       QFont font("Microsoft YaHei", Public_Function::getScaleWidth(16), 75);
       mtextLab->setFont(font);
       mtextLab->setText(tr("服务协议"));
       QTextCharFormat fmt;
       fmt.setForeground(QColor(68,68,68));
       fmt.setFont(Public_Function::getFont(14));
       edit->setCurrentCharFormat(fmt);
       edit->append(tr(" 一、软件使用协议\r\n    \
     本协议是用户 (自然人、法人或社会团体)与山东安道云教育科技有限公司之间关于安道白板软件产品（以下简称“本软件产品”）的法律协议。一旦安装、复制或以其他方式使用本软件产品，即表示同意接受协议各项条件的约束。如果用户不同意协议的条件，请不要使用本软件产品。\r\n\
二、软件产品保护条款\r\n \
     2.1 本软件产品之著作权及其它知识产权等相关权利或利益（包括但不限于现已取得或未来可取得之著作权、专利权、商标权、营业秘密等）皆为山东安道云教育科技有限公司所有。本软件产品受中华人民共和国版权法及国际版权条约和其他知识产权法及条约的保护。用户仅获得本软件产品的非排他性使用权。\r\n \
     2.2 用户不得：删除本软件及其他副本上一切关于版权的信息；对本软件进行反向工程，如反汇编、反编译等；\r\n \
     2.3 本软件产品以现状方式提供，山东安道云教育科技有限公司不保证本软件产品能够或不能够完全满足用户需求，在用户手册、帮助文件、使用说明书等软件文档中的介绍性内容仅供用户参考，不得理解为对用户所做的任何承诺。山东安道云教育科技有限公司保留对软件版本进行升级，对功能、内容、结构、界面、运行方式等进行修改或自动更新的权利。\r\n \
     2.4 为了更好地服务于用户，或为了向用户提供具有个性的信息内容的需要，本软件产品可能会收集、传播某些信息，但山东安道云教育科技有限公司承诺不向未经授权的第三方提供此类信息，以保护用户隐私。\r\n \
     2.5 使用本软件产品由用户自己承担风险，在适用法律允许的最大范围内，山东安道云教育科技有限公司在任何情况下不就因使用或不能使用本软件产品所发生的特殊的、意外的、非直接或间接的损失承担赔偿责任。即使已事先被告知该损害发生的可能性。\r\n \
     2.6 山东安道云教育科技有限公司定义的信息内容包括：文字、软件、视频、声音；本公司为用户提供的商业信息，所有这些内容受版权、商标权、和其它知识产权和所有权法律的保护。所以，用户只能在本公司授权下才能使用这些内容，而不能擅自复制、修改、编撰这些内容、或创造与内容有关的衍生产品。\r\n \
     2.7 如果您未遵守本协议的任何一项条款，山东安道云教育科技有限公司有权立即终止本协议，并保留通过法律手段追究责任。\r\n \
三、山东安道云教育科技有限公司具有对以上各项条款内容的最终解释权和修改权。如用户对山东安道云教育科技有限公司的解释或修改有异议，应当立即停止使用本软件产品。用户继续使用本软件产品的行为将被视为对山东安道云教育科技有限公司的解释或修改的接受。\r\n \
四、因本协议所发生的纠纷，双方同意按照中华人民共和国法律，由山东安道云教育科技有限公司所在地的有管辖权的法院管辖。\r\n \
                     \r\n\
         山东安道云教育科技有限公司"));
    }
    else if(flage == 1)
    {
        QFont font("Microsoft YaHei", Public_Function::getScaleWidth(16), 75);
        mtextLab->setFont(font);
        mtextLab->setText(tr("隐私政策"));
        QTextCharFormat fmt;
        fmt.setForeground(QColor(68,68,68));
        fmt.setFont(Public_Function::getFont(14));
        edit->setCurrentCharFormat(fmt);
        edit->append(tr(" 安道云股份有限公司非常重视保护您的个人信息。 为方便您登录、使用相关服务，以及为您提供更个性化的用户体验和服务，您在使用我们的服务时，我们可能会收集和使用您的相关信息。我们希望通过本个人信息保护政策向您说明，在使用安道白板服务(统称“安道白板”)时，我们如何收集、使用、储存和披露您的信息，以及我们为您提供的访问、更新、控制和保护这些信息的方式。本个人信息保护政策与您所使用的安道白板服务信息相关，希望您仔细阅读。\r\n \
    您使用我们的服务，即意味着您已经同意我们按照本个人信息保护政策收 集、使用、储存和披露您的相关信息，以及向您提供的控制和保护措施。\r\n \
一、适用范围\r\n \
    1.1 本个人信息保护政策适用于安道白板所有服务，服务包括向您提供页面浏览、网站登录服务，以及通过安道白板向您提供的技术服务。\r\n \
    1.2 本个人信息保护政策中的“信息”特指第二条所收集的信息。\r\n \
二、信息收集范围\r\n \
    2.1 为完成安道白板账户的注册、管理、实名认证等必要活动，您需要提交真实、合法、有效的信息，包括但不限于您的联系电话、微信昵称、头像等。\r\n \
    2.2 您使用本服务时，可能收集已经经过您授权获取或主动填写的如下信息:\r\n \
    2.2.1 日志信息，指您使用我们的服务时，系统可能通过自动采集的技术信息，包括:\r\n \
    . 设备或软件信息，例如您的移动设备、网页浏览器或用于接入我们服务的其 他程序所提供的配置信息、您的 IP 地址和移动设备所用的版本和设备识别码。\r\n \
    . 有关您曾使用的移动应用和其他软件的信息，以及您曾经使用该等移动应用和软件的信息。\r\n \
    . 您通过我们的服务进行通讯的信息，例如曾通讯的帐号。\r\n \
    . 您通过我们的服务分享的内容所包含的信息(元数据)，例如拍摄或上传的共享照片或录像的日期、时间或地点等。\r\n \
三、如何收集信息\r\n \
    3.1 我们通过您主动提交，以及在您使用我们的服务过程中产生相应的记录等\
    方式收集您的信息。\r\n \
    3.2 我们可能会通过 Cookies和其他相关技术收集和使用您的信息。我们使用 Cookies 的具体用途包括:\r\n \
    . 记住您的身份。例如:Cookies有助于我们辨认您作为我们的注册用户的身份。\r\n \
    . 分析您使用我们服务的情况，以便为您提供更加周到的个性化服务，包括定制化页面、推荐等服务。\r\n \
    3.3 您可以通过浏览器设置拒绝或管理 Cookies。但请注意，如果停用 Cookies，您有可能无法享受最佳的服务体验，某些功能的可用性可能会受到影响。\r\n \
    3.4 通过安道白板 Cookies 记录的有关信息，将适用本个人信息保护政策。\r\n \
四、信息使用\r\n \
    为了向您提供更加优质、便捷、安全的服务，在符合相关法律法规的前提下，我们可能将收集的信息用作以下用途:\r\n \
    . 向您提供服务(如实名认证信息、用来接受验证码的手机号，是继续获得服务的前提)。\r\n \
    . 满足您的个性化需求。例如，语言设定、位置设定、个性化的帮助服务和指示，或对您和其他用户作出其他方面的回应。\r\n \
    . 服务优化和开发。例如，我们会根据安道白板系统响应您的需求时产生的信息，优化我们的服务。\r\n \
    . 保护您或其他用户或公众的人身财产安全免遭侵害，更好地预防钓鱼网站、欺诈、网络漏洞、计算机病毒、网络攻击、网络侵入等安全风险，更准确地识 别违反法律法规或安道白板相关协议、规则的情况，我们可能使用您的帐号信 息、并整合设备信息、有关网络日志以及我们关联公司、合作伙伴分享的信 息，来判断您账户风险、进行身份验证、安全事件的检测及防范，并依法采取 必要的记录、审计、分析、处置措施。例如，我们会将您的信息用于身份验证、安全防范、投诉处理、纠纷协调、诈骗监测等用途。您在使用安全功能或 \
    其他类似服务时，我们会对恶意程序或病毒进行检测，或为您识别诈骗信息。\r\n\
    . 向您提供与您更加相关的服务。例如，向您提供您可能感兴趣的类似功能或服务等。\r\n \
    . 邀请您参与有关我们产品和服务的调查。\r\n \
    . 其他可能需要使用收集的信息的相关场景，如果使用场景与初始场景无合理 的关联性，我们会在使用信息前重新征得您的同意。\r\n \
五、信息共享、转让、披露\r\n \
    5.1 共享\r\n \
    我们不会与其他组织和个人共享您的用户信息，但以下情况除外:\r\n \
    5.1.1 在获取明确同意的情况下共享:获得您的明确同意后，我们会与其他方共享您的用户信息;\r\n \
    5.1.2 在法定情形下的共享:我们可能会根据法律法规规定、诉讼、仲裁解决需要，或按行政、司法机关依法提出的要求，对外共享您的用户信息;\r\n \
    5.1.3 为了促成办理服务或协助解决争议，某些情况下只有共享您的用户信息，才能促成办理或处理您与他人的纠纷或争议。\r\n \
    5.1.4 与授权合作伙伴共享:我们可能委托受信赖的合作伙伴来提供服务(如人脸识别服务)，因此我们可能会与合作伙伴共享您的某些用户信息，以提供更好的客户服务和优化用户体验。我们仅会出于合法、正当、必要、特定、明确的目的共享您的用户信息，并且只会共享提供服务所必要的用户信息。我们的合作伙 伴无权将共享的用户信息用于任何其他用途。 目前，我们的授权合作伙伴包括如下类型:供应商、服务提供商和其他合作伙伴。 我们将信息发送给支持我们业务的供应商、服务提供商和其他合作伙伴，这些支持包括提供基础技术服务、提供咨询、分析等专业服务。 \
    对我们与之共享用户信息的公司、组织和个人，我们会与其签署严格的保密协议以及信息保护约定，要求他们按照我们的说明、本个人信息保护政策以及其他任何相关的保密和安全措施来处理用户信息。\r\n \
    5.2 转让我们不会将您的用户信息转让给任何公司、组织和个人，但以下情况除外: 5.2.1 在获取明确同意的情况下转让:获得您的明确同意后，我们会向其他方转 让您的用户信息。\r\n \
    5.3 披露未经您同意，我们不会与任何无关第三方分享您的信息，以下情形除外:\r\n\
    5.3.1. 我们可能将您的信息与我们的关联公司、第三方服务提供商、承包商及代理分享，仅用作下列用途:\r\n \
    . 提供“二、信息收集范围”中的相应功能或服务所必需，以及出于“四、信息使用”中的部分所述目的所必需。\r\n \
    . 履行我们在《广东省统一身份认证平台用户服务协议》或本个人信息保护政策 中的义务和行使我们的权利。 如我们与任何上述第三方分享您的信息，我们将努力确保第三方在使用您的信息 时遵守本声明及我们要求其遵守的其他适当的保密和安全措施。\r\n \
    5.3.2. 随着我们业务的持续发展，我们以及我们的关联公司有可能进行合并、 收购、资产转让或类似的交易，您的信息有可能作为此类交易的一部分而被转移。 我们将遵守相关法律法规的要求，在转移前通知您，确保信息在转移时的机密性， 以及变更后继续履行相应责任和义务。\r\n \
    5.3.3. 我们还可能因以下原因而披露您的信息:\r\n \
    . 遵守适用的法律法规等有关规定。\r\n \
    . 遵守法院判决、裁定或其他法律程序的规定。\r\n \
    . 遵守相关政府机关或其他有权机关的要求。\r\n \
    . 我们有理由确信需遵守法律法规等有关规定。\r\n \
    . 为执行相关服务协议或本个人信息保护政策、维护社会公共利益、处理投诉/ 纠纷，保护我们的客户、我们或我们的关联公司、其他用户或雇员的人身和财产 安全或合法权益所合理必需的用途。\r\n \
    . 经过您合法授权的情形。 如我们因上述原因而披露您的信息，我们将在遵守法律法规相关规定及本声明的 基础上及时告知您。\r\n \
六、信息存储\r\n \
    6.1 安道白板收集的有关您的信息保存在安道白板位于中国大陆的服务器。\r\n \
    6.2 通常，我们仅在为您提供服务期间保留您的信息，保留时间不会超过满足 相关使用目的所必须的时间。 但在下列情况下，且仅出于下列情况相关的目的，我们有可能需要较长时 \
    间保留您的信息或部分信息:\r\n \
    . 遵守适用的法律法规等有关规定。\r\n \
    . 遵守法院判决、裁定或其他法律程序的要求。\r\n \
    . 遵守相关政府机关或其他有权机关的要求。\r\n \
    . 我们有理由确信需遵守法律法规等有关规定。\r\n \
    . 为执行相关服务协议或本个人信息保护政策、维护社会公共利益、处理投诉/ 纠纷，保护我们的客户、我们或我们的关联公司、其他用户或雇员的人身和财 \
    产安全或合法权益所合理必需的用途。\r\n \
七、信息安全\r\n \
    7.1 如果您拥有安道白板其他账号，在特定场景下，您的安道白板账号的个人信息可能会与您在安道白板拥有的其他账户信息相关联。例如，您使用微信支付注册 安道白板账号。\r\n \
    7.2 我们努力保障信息安全，以防信息的丢失、不当使用、未经授权阅览或披露。\r\n \
    . 我们使用各种安全技术以保障信息的安全。例如，我们将通过服务器多备份、密码加密等安全措施，防止信息泄露、毁损、丢失。\r\n \
    . 我们建立严格的管理制度和流程以保障信息的安全。例如，我们严格限制访问信息的人员范围，并进行审计，要求他们遵守保密义务。\r\n \
    . 我们重视信息安全合规工作，并通过众多国际和国内的安全认证，如网络安全等级保护认证等，以业界先进的解决方案充分保障您的信息安全。 \
    但请您理解，由于技术的限制以及可能存在的各种恶意手段，在互联网环境下，即便竭尽所能加强安全措施，也不可能始终保证信息百分之百的安全。 \
    您需要了解，您接入我们的服务所用的系统和通讯网络，有可能因我们可控范围外的因素而出现问题。 \
    若发生个人信息泄露等安全事件，我们会启动应急预案，阻止安全事件扩大，按照《国家网络安全事件应急预案》等有关规定及时上报，并以发送邮 件、推送通知、公告等形式告知您相关情况，并向您给出安全建议。\r\n \
    7.3 为更有效的保障您的信息安全，我们也希望您能够加强自我保护意识。我们仅在安道白板直接导致您个人信息泄露的范围内承担责任，因此，请您妥善保 管您的账号及密码信息，避免您的个人信息泄露。安道白板账户及微信账号均有 安全保护功能，但您也需要妥善保护自己的个人信息，除非您判断认为必要的 情形下，不向任何第三人提供您的账号密码等个人信息。\r\n \
八、访问与控制\r\n \
    8.1 您可以在使用我们服务的过程中，访问、修改和删除您的相关信息。您访问、修改和删除信息的方式将取决于您使用的具体服务。\r\n \
    8.2 如您发现我们违反法律法规的规定或者双方的约定收集、使用您的信息， 您可以要求我们删除。如您发现我们收集、存储的您的信息有错误的，且无法 自行更正的，您也可以要求我们更正。\r\n \
    8.3 在访问、修改和删除相关信息时，我们可能会要求您进行身份验证，以保 障账户安全。请您理解，由于技术所限、基于法律法规要求，您的某些请求可能无法进行响应。\r\n \
    8.4 基于法律法规要求、保障信息安全等正当事由，您的部分信息可能无法访 问、修改和删除。\r\n \
    8.5 您可以自行选择撤回对某些非基本功能或服务对您信息处理的同意，并通 过联系客服的方式选择注销安道白板账号。\r\n \
    8.6 如您对上述权利实现存在疑问，可以根据“十、与我们联系”中的相关联系方式与我们取得联系。\r\n \
九、个人信息保护政策的更新\r\n \
    我们可能适时修订本个人信息保护政策的条款，该等修订构成本《个人信息保护政策》的一部分。如可能造成您在本个人信息保护政策下权利的实质减少或扩大收集、使用信息的范围等重要规则变更时，我们将在修订生效前通过在主页 上显著位置提示或向您发送电子邮件或以其他方式通知您。在该种情况下，若您 继续使用我们的服务，即表示同意受经修订的本个人信息保护政策的约束。\r\n \
十、与我们联系\r\n \
    如您对本政策或其他相关事宜有疑问，您可以通过 400-632-8880 进行咨询或根据 我们提供的指引，填写意见反馈。我们将尽快审核所涉问题，并在验证您的用户身份后予以回复。"));
    }

    QTextCursor cursor = edit->textCursor();
    cursor.movePosition(QTextCursor::Start);
    edit->setTextCursor(cursor);

    QHBoxLayout *hlayout2 =new QHBoxLayout;
    hlayout2->addStretch(0);
    hlayout2->addWidget(edit);
    hlayout2->addStretch(0);
    hlayout2->setContentsMargins(Public_Function::getScaleWidth(10),0,Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(15));

    mBtn = new QPushButton(this);
    mBtn->setFont(Public_Function::getFont(16));
    mBtn->setText(tr("我知道了"));
    mBtn->setFixedSize(Public_Function::getScaleSize(108,42));
    mBtn->setStyleSheet(QString("border:%1px solid rgba(20,134,250);border-radius:%2px;background-color:rgb(255,255,255);color:rgb(20,134,250)").arg(Public_Function::getScaleWidth(1)).arg(Public_Function::getScaleWidth(5)));

    QHBoxLayout *hlayout3 =new QHBoxLayout;
    hlayout3->addStretch(0);
    hlayout3->addWidget(mBtn);
    hlayout3->addStretch(0);

    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addStretch(0);

    connect(mBtn,&QPushButton::clicked,this,[=](){
        this->hide();
        emit sendCloseMassage7();
    });
}


/********************************CustomWidget_8***********************************************/

CustomWidget_8::CustomWidget_8(QWidget *parent):QTabWidget(parent)
{
}

void CustomWidget_8::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(14),Public_Function::getScaleWidth(14));
    painter.drawPath(path);
}

/********************************CustomWidget_9***********************************************/

CustomWidget_9::CustomWidget_9(QWidget *parent): QWidget(parent)
{
    this->setFixedSize(parentWidget()->size());
    initLayout();
}

CustomWidget_9::~CustomWidget_9()
{
}

void CustomWidget_9::initLayout()
{
    QStackedLayout* layout = new QStackedLayout(this);
    mwebView = new QWebEngineView(this);
    layout->addWidget(mwebView);
}

void CustomWidget_9::webDownload(QWebEngineDownloadItem *item)
{
    connect(item,&QWebEngineDownloadItem::finished, this, &CustomWidget_9::mydownloadFinished);
    connect(item,&QWebEngineDownloadItem::downloadProgress, this,&CustomWidget_9::mydownloadProgress);
    //QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/"+ item->downloadDirectory().mid(item->downloadDirectory().lastIndexOf("/") +1);
    QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    item->setDownloadDirectory(path);
    qDebug() << "item -> path(): " << item->downloadDirectory();
    item->accept();
}

void CustomWidget_9::mydownloadFinished()
{
     qDebug()<< " loadFinished " <<Qt::endl;
}

void CustomWidget_9::mydownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
     qDebug()<<"WebDownloadWork::on_downloadProgress bytesReceived:"<<bytesReceived<<"  bytesTotal:"<<bytesTotal;
}

void CustomWidget_9::loadWeb(QString url)
{
    if (url.isEmpty())
        return;

    QWebEnginePage* webEnginePage = mwebView->page();
    webEnginePage->setBackgroundColor(Qt::transparent);
    QWebEngineProfile* webProfile = mwebView->page()->profile();
    connect(webProfile,&QWebEngineProfile::downloadRequested,this,&CustomWidget_9::webDownload);
    //由于大屏和电脑上尺寸不同，需要对网页进行缩放处理，不能使用固定值
    float num = float(this->width()) /873 -0.01;
    if(num >5)num =5;
    else if(num <0.25)num =0.25;
    mwebView->setZoomFactor(num);
    mwebView->load(url);
    mwebView->reload();
}

void CustomWidget_9::reLoad()
{
    mwebView->reload();
}


/********************************CustomWidget_10***********************************************/

CustomWidget_10::CustomWidget_10(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(parentWidget()->size());
    initLayout();
}

CustomWidget_10::~CustomWidget_10()
{
}

void CustomWidget_10::initLayout()
{
    QStackedLayout* layout = new QStackedLayout(this);
    mwebView = new QWebEngineView(this);
    mwebView->setFixedSize(this->size());
    layout->addWidget(mwebView);
}

void CustomWidget_10::webDownload(QWebEngineDownloadItem *item)
{
//    connect(item,&QWebEngineDownloadItem::finished, this, &CustomWidget_10::mydownloadFinished);
//    connect(item,&QWebEngineDownloadItem::downloadProgress, this,&CustomWidget_10::mydownloadProgress);
//    //QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/"+ item->downloadDirectory().mid(item->downloadDirectory().lastIndexOf("/") +1);
//    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
//    item->setDownloadDirectory(path);
//    qDebug() << "item -> path(): " << item->downloadDirectory();
//    item->accept();
}

void CustomWidget_10::mydownloadFinished()
{
    qDebug()<< " loadFinished " <<Qt::endl;
}

void CustomWidget_10::mydownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug()<<"WebDownloadWork::on_downloadProgress bytesReceived:"<<bytesReceived<<"  bytesTotal:"<<bytesTotal;
}

void CustomWidget_10::loadWeb(QString url)
{
    if (url.isEmpty())
        return;

    QWebEnginePage* webEnginePage = mwebView->page();
    webEnginePage->setBackgroundColor(Qt::transparent);
    //由于大屏和电脑上尺寸不同，需要对网页进行缩放处理，不能使用固定值
    float num = float(this->width()) /873 -0.01;
    if(num >5)num =5;
    else if(num <0.25)num =0.25;
    mwebView->setZoomFactor(num);
    if (!url.isEmpty())
    {
        mwebView->load(url);
    }
}

void CustomWidget_10::reLoad()
{
    mwebView->reload();
}

/********************************CustomWidget_11***********************************************/

CustomWidget_11::CustomWidget_11(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(870,552));
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,(desktop->height() -this->height())/2);
    initLayout();
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        number++;
        length = number*Public_Function::getScaleWidth(468)/100;
        mpercentageLab->setText(QString("%1%").arg(number));
        update();
        if(number >= 100)
        {
            timer->stop();
        }
    });
    timer->start(100);
}

void CustomWidget_11::initLayout()
{
    mcloseLab = new QLabel(this);
    mcloseLab->installEventFilter(this);
    mcloseLab->setFixedSize(Public_Function::getScaleSize(19,19));
    mcloseLab->setScaledContents(true);
    mcloseLab->setPixmap(QPixmap(":/pixmap/guanbi@2x.png"));
    QHBoxLayout *hlayout1 =new QHBoxLayout;
    hlayout1->addStretch(0);
    hlayout1->addWidget(mcloseLab);
    hlayout1->setContentsMargins(0,Public_Function::getScaleWidth(18),Public_Function::getScaleWidth(18),Public_Function::getScaleWidth(112));

    mpercentageLab = new QLabel(this);
    mpercentageLab->setFixedSize(Public_Function::getScaleSize(140,47));
    QFont font("Arial Bold",45,75);
    mpercentageLab->setFont(font);
    mpercentageLab->setAlignment(Qt::AlignCenter);
    mpercentageLab->setStyleSheet(QString("color:rgba(20,134,250,1);font-size:%1px;").arg(Public_Function::getScaleWidth(45)));
    QHBoxLayout *hlayout2 =new QHBoxLayout;
    hlayout2->addStretch(0);
    hlayout2->addWidget(mpercentageLab);
    hlayout2->addStretch(0);
    hlayout2->setContentsMargins(0,0,0,Public_Function::getScaleWidth(30));

    mtetxLab = new QLabel(this);
    mtetxLab->setFixedSize(Public_Function::getScaleSize(253,12));
    mtetxLab->setAlignment(Qt::AlignCenter);
    mtetxLab->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px;").arg(Public_Function::getScaleWidth(12)));
    mtetxLab->setText(tr("正在上传“文件名字段.doc”到我的网盘"));

    QHBoxLayout *hlayout3 =new QHBoxLayout;
    hlayout3->addStretch(0);
    hlayout3->addWidget(mtetxLab);
    hlayout3->addStretch(0);
    hlayout3->setContentsMargins(0,0,0,Public_Function::getScaleWidth(105));

    mcancelBtn = new QPushButton(tr("取消"),this);
    mcancelBtn->setFixedSize(Public_Function::getScaleSize(100,42));
    mcancelBtn->setStyleSheet(QString("border:%1px solid rgba(224,224,224,1);color:rgba(102,102,102,1);font-size:%2px;border-radius:%3px;").arg(Public_Function::getScaleWidth(1)).arg(Public_Function::getScaleWidth(16)).arg(Public_Function::getScaleWidth(5)));

    QHBoxLayout *hlayout4 =new QHBoxLayout;
    hlayout4->addStretch(0);
    hlayout4->addWidget(mcancelBtn);
    hlayout4->addStretch(0);

    QVBoxLayout *vlayout =new QVBoxLayout(this);
    vlayout->setSpacing(0);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);
    vlayout->addStretch(0);

    connect(mcancelBtn,&QPushButton::clicked,[=](){
        qDebug()<< " 取消" <<Qt::endl;
    });
}

void CustomWidget_11::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setBrush(QBrush(QPixmap(":/pixmap/beijing2@2x.png").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    painter.setBrushOrigin(this->rect().topLeft());
    painter.setPen(Qt::NoPen);
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(14),Public_Function::getScaleWidth(14));
    painter.drawPath(path);
    painter.setBrush(QBrush(QColor(20,134,250)));
    painter.drawPath(drawProgressbar());

    QLinearGradient linearGradient(201, 265, 206,270);
    linearGradient.setColorAt(0, QColor(0,242,253,0));
    linearGradient.setColorAt(0.5, QColor(0,242,253,255));
    linearGradient.setColorAt(1, QColor(0,242,253,0));
    painter.setPen(Qt::NoPen);
    linearGradient.setSpread(QGradient::RepeatSpread);
    painter.setBrush(linearGradient);

    painter.drawPath(drawProgressbar2(length));

}

QPainterPath CustomWidget_11::drawProgressbar()
{
    QPainterPath path;
    path.moveTo(Public_Function::getScaleWidth(201),Public_Function::getScaleWidth(265));
    path.lineTo(Public_Function::getScaleWidth(649),Public_Function::getScaleWidth(265));
    path.arcTo(Public_Function::getScaleWidth(634),Public_Function::getScaleWidth(265),Public_Function::getScaleWidth(30),Public_Function::getScaleWidth(30),90,-180);
    path.lineTo(Public_Function::getScaleWidth(201),Public_Function::getScaleWidth(295));
    path.arcTo(Public_Function::getScaleWidth(186),Public_Function::getScaleWidth(265),Public_Function::getScaleWidth(30),Public_Function::getScaleWidth(30),-90,-180);
    return path;
}

QPainterPath CustomWidget_11::drawProgressbar2(int length)
{
    QPainterPath path;
    path.moveTo(Public_Function::getScaleWidth(191),Public_Function::getScaleWidth(270));
    path.lineTo(Public_Function::getScaleWidth(171) +length,Public_Function::getScaleWidth(270));
    path.arcTo(Public_Function::getScaleWidth(171) +length,Public_Function::getScaleWidth(270),Public_Function::getScaleWidth(20),Public_Function::getScaleWidth(20),90,-180);
    path.lineTo(Public_Function::getScaleWidth(191),Public_Function::getScaleWidth(290));
    path.arcTo(Public_Function::getScaleWidth(191),Public_Function::getScaleWidth(270),Public_Function::getScaleWidth(20),Public_Function::getScaleWidth(20),-90,-180);
    return path;
}

bool CustomWidget_11::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == mcloseLab)
        {
            emit sendCloseMassage11();
            this->close();
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}


/********************************CustomWidget_12***********************************************/

CustomWidget_12::CustomWidget_12(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(870,552));
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,(desktop->height() -this->height())/2);
    initLayout();
}

void CustomWidget_12::initLayout()
{
    miconLab = new QLabel(this);
    miconLab->setFixedSize(Public_Function::getScaleSize(188,127));
    miconLab->setScaledContents(true);
    miconLab->setPixmap(QPixmap(":/pixmap/tianjia@2x.png"));
    miconLab->setAlignment(Qt::AlignCenter);

    QHBoxLayout *hlayout1 =new QHBoxLayout;
    hlayout1->addStretch(0);
    hlayout1->addWidget(miconLab);
    hlayout1->addStretch(0);
    hlayout1->setContentsMargins(0,Public_Function::getScaleWidth(107),0,Public_Function::getScaleWidth(30));

    mtetxLab = new QLabel(this);
    mtetxLab->setFixedSize(Public_Function::getScaleSize(125,20));
    QFont font("Microsoft YaHei Bold",18,65);
    mtetxLab->setFont(font);
    mtetxLab->setAlignment(Qt::AlignCenter);
    mtetxLab->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px;").arg(Public_Function::getScaleWidth(18)));
    mtetxLab->setText(tr("从分享链接添加"));

    QHBoxLayout *hlayout2 =new QHBoxLayout;
    hlayout2->addStretch(0);
    hlayout2->addWidget(mtetxLab);
    hlayout2->addStretch(0);
    hlayout2->setContentsMargins(0,0,0,Public_Function::getScaleWidth(40));

    edit = new QLineEdit(this);
    edit->setFixedSize(Public_Function::getScaleSize(550,50));
    edit->setStyleSheet(QString("background-color:rgba(240,240,240,1);font-size:%1px;border:%2px solid rgba(224,224,224,1);border-radius:%3px")
                        .arg(Public_Function::getScaleWidth(16)).arg(Public_Function::getScaleWidth(1)).arg(Public_Function::getScaleWidth(9)));
    edit->setPlaceholderText(tr("输入或粘贴文档共享链接"));
    QHBoxLayout *hlayout3 =new QHBoxLayout;
    hlayout3->addStretch(0);
    hlayout3->addWidget(edit);
    hlayout3->addStretch(0);
    hlayout3->setContentsMargins(0,0,0,Public_Function::getScaleWidth(40));

    mbackBtn = new Custom_Btn3(this);
    mbackBtn->setText_m(tr("返回"));
    mbackBtn->setFixedSize(Public_Function::getScaleSize(100,42));

    maddBtn = new Custom_Btn3(this);
    maddBtn->setText_m(tr("添加"));
    maddBtn->setFixedSize(Public_Function::getScaleSize(100,42));

    group = new QButtonGroup(this);
    group->setExclusive(true);
    group->addButton(mbackBtn);
    group->addButton(maddBtn);
    maddBtn->setChecked(true);

    QHBoxLayout *hlayout4 =new QHBoxLayout;
    hlayout4->setSpacing(Public_Function::getScaleWidth(20));
    hlayout4->addStretch(0);
    hlayout4->addWidget(mbackBtn);
    hlayout4->addWidget(maddBtn);
    hlayout4->addStretch(0);

    QVBoxLayout *vlayout =new QVBoxLayout(this);
    vlayout->setSpacing(0);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);
    vlayout->addStretch(0);

    connect(mbackBtn,&QPushButton::clicked,this,[=](){
        emit sendCloseMassage12();
    });

    connect(maddBtn,&QPushButton::clicked,this,[=](){
        emit sendAddMassage();
    });
}


void CustomWidget_12::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setBrush(QBrush(QPixmap(":/pixmap/beijing2@2x.png")));
    painter.setBrushOrigin(this->rect().topLeft());
    painter.setPen(Qt::NoPen);
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(14),Public_Function::getScaleWidth(14));
    painter.drawPath(path);
}



/********************************CustomWidget_13***********************************************/

CustomWidget_13::CustomWidget_13(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(870,552));
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,(desktop->height() -this->height())/2);
    initLayout();
}

void CustomWidget_13::initLayout()
{
    mcloseLab = new QLabel(this);
    mcloseLab->installEventFilter(this);
    mcloseLab->setFixedSize(Public_Function::getScaleSize(19,19));
    mcloseLab->setScaledContents(true);
    mcloseLab->setPixmap(QPixmap(":/pixmap/guanbi@2x.png"));
    QHBoxLayout *hlayout1 =new QHBoxLayout;
    hlayout1->addStretch(0);
    hlayout1->addWidget(mcloseLab);
    hlayout1->setContentsMargins(0,Public_Function::getScaleWidth(18),Public_Function::getScaleWidth(18),Public_Function::getScaleWidth(82));

    miconLab = new QLabel(this);
    miconLab->setFixedSize(Public_Function::getScaleSize(138,161));
    miconLab->setAlignment(Qt::AlignCenter);
    miconLab->setScaledContents(true);
    miconLab->setPixmap(QPixmap(":/pixmap/tianjia2@2x.png"));
    QHBoxLayout *hlayout2 =new QHBoxLayout;
    hlayout2->addStretch(0);
    hlayout2->addWidget(miconLab);
    hlayout2->addStretch(0);
    hlayout2->setContentsMargins(0,0,0,Public_Function::getScaleWidth(30));

    mtetxLab = new QLabel(this);
    mtetxLab->setFixedSize(Public_Function::getScaleSize(108,20));
    QFont font("Microsoft YaHei Bold",18,55);
    mtetxLab->setFont(font);
    mtetxLab->setAlignment(Qt::AlignCenter);
    mtetxLab->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px;").arg(Public_Function::getScaleWidth(18)));
    mtetxLab->setText(tr("添加文件完成"));

    QHBoxLayout *hlayout3 =new QHBoxLayout;
    hlayout3->addStretch(0);
    hlayout3->addWidget(mtetxLab);
    hlayout3->addStretch(0);
    hlayout3->setContentsMargins(0,0,0,Public_Function::getScaleWidth(50));

    mbackBtn = new Custom_Btn3(this);
    mbackBtn->setText_m(tr("返回"));
    mbackBtn->setFixedSize(Public_Function::getScaleSize(100,42));

    QHBoxLayout *hlayout4 =new QHBoxLayout;
    hlayout4->addStretch(0);
    hlayout4->addWidget(mbackBtn);
    hlayout4->addStretch(0);

    QVBoxLayout *vlayout =new QVBoxLayout(this);
    vlayout->setSpacing(0);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);
    vlayout->addStretch(0);

    connect(mbackBtn,&QPushButton::clicked,this,[=](){
        emit sendCloseMassage13();
    });

}


void CustomWidget_13::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setBrush(QBrush(QPixmap(":/pixmap/beijing2@2x.png").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    painter.setBrushOrigin(this->rect().topLeft());
    painter.setPen(Qt::NoPen);
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(14),Public_Function::getScaleWidth(14));
    painter.drawPath(path);
}

bool CustomWidget_13::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == mcloseLab)
        {
           emit sendCloseMassage13();
           this->close();
           return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}



/********************************CustomWidget_14***********************************************/

CustomWidget_14::CustomWidget_14(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(440,350));
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,(desktop->height() -this->height())/2);
    initLayout();
}

void CustomWidget_14::initLayout()
{
    mtitelLab = new QLabel(this);
    mtitelLab->setFixedSize(Public_Function::getScaleSize(80,20));
    QFont font("Microsoft YaHei Bold",16,65);
    mtitelLab->setFont(font);
    mtitelLab->setStyleSheet(QString("color:rgba(255,255,255,1);font-size:%1px").arg(Public_Function::getScaleWidth(16)));
    mtitelLab->setText(tr("文件云分享"));
    mcloseLab = new QLabel(this);
    mcloseLab->installEventFilter(this);
    mcloseLab->setFixedSize(Public_Function::getScaleSize(19,19));
    mcloseLab->setScaledContents(true);
    mcloseLab->setPixmap(QPixmap(":/pixmap/guanbi3@2x.png"));
    QHBoxLayout *hlayout1 =new QHBoxLayout;
    hlayout1->addWidget(mtitelLab);
    hlayout1->addStretch(0);
    hlayout1->addWidget(mcloseLab);
    hlayout1->setContentsMargins(0,Public_Function::getScaleWidth(5),Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(50));

    mLab1 = new QLabel(this);
    mLab1->setFixedSize(Public_Function::getScaleSize(56,16));
    mLab1->setText(tr("分享文件"));
    mLab1->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    miconLab = new QLabel(this);
    miconLab->setFixedSize(Public_Function::getScaleSize(18,17));
    miconLab->setScaledContents(true);
    miconLab->setPixmap(QPixmap(":/pixmap/word@2x.png"));
    mtetxLab = new QLabel(this);
    mtetxLab->setFixedSize(Public_Function::getScaleSize(113,16));
    mtetxLab->setText("文件名称字段.doc");
    mtetxLab->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    QHBoxLayout *hlayout2 =new QHBoxLayout;
    hlayout2->addWidget(mLab1);
    QLabel *lab = new QLabel(this);
    lab->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout2->addWidget(lab);
    hlayout2->addWidget(miconLab);
    QLabel *lab1 = new QLabel(this);
    lab1->setFixedSize(Public_Function::getScaleSize(9,12));
    hlayout2->addWidget(lab1);
    hlayout2->addWidget(mtetxLab);
    hlayout2->addStretch(0);
    hlayout2->setContentsMargins(Public_Function::getScaleWidth(38),0,0,Public_Function::getScaleWidth(35));

    mLab2 = new QLabel(this);
    mLab2->setFixedSize(Public_Function::getScaleSize(56,16));
    mLab2->setText(tr("访问形式"));
    mLab2->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    mvisitBtn = new Custom_Btn5(this);
    mvisitBtn->setFixedSize(Public_Function::getScaleSize(194,42));
    QHBoxLayout *hlayout3 =new QHBoxLayout;
    hlayout3->addWidget(mLab2);
    QLabel *lab3 = new QLabel(this);
    lab3->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout3->addWidget(lab3);
    hlayout3->addWidget(mvisitBtn);
    hlayout3->addStretch(0);
    hlayout3->setContentsMargins(Public_Function::getScaleWidth(38),0,0,Public_Function::getScaleWidth(35));

    mLab3 = new QLabel(this);
    mLab3->setFixedSize(Public_Function::getScaleSize(56,16));
    mLab3->setText(tr("有效时间"));
    mLab3->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    mtimeBtn = new Custom_Btn6(this);
    mtimeBtn->setFixedSize(Public_Function::getScaleSize(288,42));
    QHBoxLayout *hlayout4 =new QHBoxLayout;
    hlayout4->addWidget(mLab3);
    QLabel *lab4 = new QLabel(this);
    lab4->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout4->addWidget(lab4);
    hlayout4->addWidget(mtimeBtn);
    hlayout4->addStretch(0);
    hlayout4->setContentsMargins(Public_Function::getScaleWidth(38),0,0,Public_Function::getScaleWidth(40));

    mbackBtn = new Custom_Btn3(this);
    mbackBtn->setText_m(tr("返回"));
    mbackBtn->setFixedSize(Public_Function::getScaleSize(100,42));
    mlinkBtn = new Custom_Btn3(this);
    mlinkBtn->setText_m(tr("生成链接"));
    mlinkBtn->setFixedSize(Public_Function::getScaleSize(100,42));
    mgroup = new QButtonGroup(this);
    mgroup->addButton(mbackBtn);
    mgroup->addButton(mlinkBtn);
    mlinkBtn->setChecked(true);

    QHBoxLayout *hlayout5 =new QHBoxLayout;
    hlayout5->addStretch(0);
    hlayout5->addWidget(mbackBtn);
    QLabel *lab5 = new QLabel(this);
    lab5->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout5->addWidget(lab5);
    hlayout5->addWidget(mlinkBtn);
    hlayout5->addStretch(0);
    hlayout5->setContentsMargins(0,0,0,0);

    QVBoxLayout *vlayout =new QVBoxLayout(this);
    vlayout->setSpacing(0);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);
    vlayout->addLayout(hlayout5);
    vlayout->addStretch(0);

    connect(mlinkBtn,&Custom_Btn3::clicked,this,[=](){
        qDebug()<< "mvisitBtn " << mvisitBtn->getBtnText() <<Qt::endl;
        qDebug()<< "mtimeBtn " << mtimeBtn->getBtnText() <<Qt::endl;
    });
}

void CustomWidget_14::changeTextIcon(QString str, QPixmap pix)
{
    mtetxLab->setText(str);
    miconLab->setPixmap(pix);
}

QPainterPath CustomWidget_14::drawRoundRect_1(int r, int mheight)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-90);
    path.lineTo(this->width(),mheight);
    path.lineTo(0,mheight);
    path.lineTo(0,mheight -r);
    path.arcTo(0,0,2*r,2*r,180,-90);
    return path;
}

void CustomWidget_14::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,255,255));
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(14),Public_Function::getScaleWidth(14));
    painter.drawPath(path);
    painter.setBrush(QColor(20,134,250));
    painter.drawPath(drawRoundRect_1(Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(44)));

}

bool CustomWidget_14::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == mcloseLab)
        {
           emit sendCloseMassage14();
           this->close();
           return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}



/********************************CustomWidget_16***********************************************/

CustomWidget_16::CustomWidget_16(QWidget *parent):QWidget(parent)
{
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,(desktop->height() -this->height())/2);
    initLayout();
}

void CustomWidget_16::initLayout()
{
    miconLab = new QLabel(this);
    miconLab->setFixedSize(Public_Function::getScaleSize(50,50));
    miconLab->setScaledContents(true);
    miconLab->setMouseTracking(true);
    miconLab->setPixmap(QPixmap(":/pixmap/fasongchenggong@2x.png"));
    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addStretch(0);
    hlayout1->addWidget(miconLab);
    hlayout1->addStretch(0);
    hlayout1->setContentsMargins(0,Public_Function::getScaleWidth(18),0,Public_Function::getScaleWidth(15));

    mtitelLab = new QLabel(this);
    mtitelLab->setFixedSize(Public_Function::getScaleSize(55,16));
    mtitelLab->setMouseTracking(true);
    QFont font("Microsoft YaHei Bold",14,50);
    mtitelLab->setFont(font);
    mtitelLab->setStyleSheet(QString("color:rgba(34,34,34,1);font-size:%1px").arg(Public_Function::getScaleWidth(14)));
    mtitelLab->setText(tr("发送成功"));
    mtitelLab->setAlignment(Qt::AlignCenter);
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addStretch(0);
    hlayout2->addWidget(mtitelLab);
    hlayout2->addStretch(0);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addStretch(0);
}

void CustomWidget_16::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,255,255));
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(14),Public_Function::getScaleWidth(14));
    painter.drawPath(path);

}

void CustomWidget_16::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->close();
        this->deleteLater();
    }
}


/********************************CustomWidget_15***********************************************/

CustomWidget_15::CustomWidget_15(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(440,408));
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,(desktop->height() -this->height())/2);
    initLayout();
}

void CustomWidget_15::initLayout()
{
    mtitelLab = new QLabel(this);
    mtitelLab->setFixedSize(Public_Function::getScaleSize(80,20));
    QFont font("Microsoft YaHei Bold",16,65);
    mtitelLab->setFont(font);
    mtitelLab->setStyleSheet(QString("color:rgba(255,255,255,1);font-size:%1px").arg(Public_Function::getScaleWidth(16)));
    mtitelLab->setText(tr("文件云分享"));
    mcloseLab = new QLabel(this);
    mcloseLab->installEventFilter(this);
    mcloseLab->setFixedSize(Public_Function::getScaleSize(19,19));
    mcloseLab->setScaledContents(true);
    mcloseLab->setPixmap(QPixmap(":/pixmap/guanbi3@2x.png"));
    QHBoxLayout *hlayout1 =new QHBoxLayout;
    hlayout1->addWidget(mtitelLab);
    hlayout1->addStretch(0);
    hlayout1->addWidget(mcloseLab);
    hlayout1->setContentsMargins(0,Public_Function::getScaleWidth(5),Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(50));

    mLab1 = new QLabel(this);
    mLab1->setFixedSize(Public_Function::getScaleSize(56,16));
    mLab1->setText(tr("分享文件"));
    mLab1->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    miconLab = new QLabel(this);
    miconLab->setFixedSize(Public_Function::getScaleSize(18,17));
    miconLab->setScaledContents(true);
    miconLab->setPixmap(QPixmap(":/pixmap/word@2x.png"));
    mtetxLab = new QLabel(this);
    mtetxLab->setFixedSize(Public_Function::getScaleSize(113,16));
    mtetxLab->setText("文件名称字段.doc");
    mtetxLab->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    QHBoxLayout *hlayout2 =new QHBoxLayout;
    hlayout2->addWidget(mLab1);
    QLabel *lab = new QLabel(this);
    lab->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout2->addWidget(lab);
    hlayout2->addWidget(miconLab);
    QLabel *lab1 = new QLabel(this);
    lab1->setFixedSize(Public_Function::getScaleSize(9,12));
    hlayout2->addWidget(lab1);
    hlayout2->addWidget(mtetxLab);
    hlayout2->addStretch(0);
    hlayout2->setContentsMargins(Public_Function::getScaleWidth(38),0,0,Public_Function::getScaleWidth(35));

    mLab2 = new QLabel(this);
    mLab2->setFixedSize(Public_Function::getScaleSize(56,16));
    mLab2->setText(tr("链接分享"));
    mLab2->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    mtextEdit = new QTextEdit(this);
    mtextEdit->setFixedSize(Public_Function::getScaleSize(288,102));
    mtextEdit->setReadOnly(true);
    mtextEdit->setStyleSheet(QString("background-color:rgba(240,240,240,1);font-size:%1px;border:%2px solid rgba(224,224,224,1);border-radius:%3px;color:rgba(68,68,68,1)").arg(
                                 Public_Function::getScaleWidth(14)).arg(Public_Function::getScaleWidth(1)).arg(Public_Function::getScaleWidth(5)));
    mtextEdit->verticalScrollBar()->setStyleSheet(QString("QScrollBar:vertical{width:%1px;background:transparent;margin:0px,0px,0px,0px;padding-top:0px;padding-bottom:0px;}"
                                                           "QScrollBar::handle:vertical{width:%1px;background:rgba(0,0,0,25%);border-radius:%2px;}"
                                                           "QScrollBar::handle:vertical:hover{width:%1px;background:rgba(0,0,0,50%);border-radius:%2px;}"
                                                           "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent;border-radius:%2px;}"
                                                           "QScrollBar::add-line:vertical{height:0px;width:0px;subcontrol-position:bottom;}"
                                                           "QScrollBar::sub-line:vertical{height:0px;width:0px;subcontrol-position:top;}"
                                                           "QScrollBar::add-line:vertical:hover{height:0px;width:0px;subcontrol-position:bottom;}"
                                                           "QScrollBar::sub-line:vertical:hover{height:0px;width:0px;subcontrol-position:top;}"
                                                           "QScrollBar::add-page:vertical:QScrollBar::sub-page:vertical{background:transparent;border-radius:%2px;}"
                                                           ).arg(Public_Function::getScaleWidth(6)).arg(Public_Function::getScaleWidth(2)));

    mtextEdit->setText("分享课件：课件名称字段 \r\n 链接：https://www.amdox.com/s/1M \r\n GF2uL4A6XadAj4GdlZo2A \r\n 提取码：smkd，打开链接即可查看");

    QHBoxLayout *hlayout3 =new QHBoxLayout;
    hlayout3->addWidget(mLab2);
    QLabel *lab3 = new QLabel(this);
    lab3->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout3->addWidget(lab3);
    hlayout3->addWidget(mtextEdit);
    hlayout3->addStretch(0);
    hlayout3->setContentsMargins(Public_Function::getScaleWidth(38),0,0,Public_Function::getScaleWidth(35));

    mLab3 = new QLabel(this);
    mLab3->setFixedSize(Public_Function::getScaleSize(56,16));
    mLab3->setText(tr("短信分享"));
    mLab3->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    mlineEdit = new QLineEdit(this);
    mlineEdit->setFixedSize(Public_Function::getScaleSize(208,42));
    mlineEdit->setPlaceholderText(tr("    输入接收手机号"));
    mlineEdit->setStyleSheet(QString("background-color:rgba(240,240,240,1);font-size:%1px;border:%2px solid rgba(224,224,224,1);border-radius:%3px;color:rgba(170,170,170,1)")
                             .arg(Public_Function::getScaleWidth(14)).arg(Public_Function::getScaleWidth(1)).arg(Public_Function::getScaleWidth(5)));
    msendBtn = new QPushButton(tr("发送"),this);
    msendBtn->setFixedSize(Public_Function::getScaleSize(70,42));
    msendBtn->setStyleSheet(QString("color:rgba(20,134,250,1);background-color:rgba(229,242,255,1);font-size:%1px;border-radius: %2px;")
                            .arg(Public_Function::getScaleWidth(16)).arg(Public_Function::getScaleWidth(4)));
    QHBoxLayout *hlayout4 =new QHBoxLayout;
    hlayout4->addWidget(mLab3);
    QLabel *lab4 = new QLabel(this);
    lab4->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout4->addWidget(lab4);
    hlayout4->addWidget(mlineEdit);
    QLabel *lab5 = new QLabel(this);
    lab5->setFixedSize(Public_Function::getScaleSize(10,12));
    hlayout4->addWidget(lab5);
    hlayout4->addWidget(msendBtn);
    hlayout4->addStretch(0);
    hlayout4->setContentsMargins(Public_Function::getScaleWidth(38),0,0,Public_Function::getScaleWidth(40));

    mcloseBtn = new Custom_Btn3(this);
    mcloseBtn->setText_m(tr("关闭"));
    mcloseBtn->setFixedSize(Public_Function::getScaleSize(100,42));
    mcopyBtn = new Custom_Btn3(this);
    mcopyBtn->setText_m(tr("复制链接"));
    mcopyBtn->setFixedSize(Public_Function::getScaleSize(100,42));
    mgroup = new QButtonGroup(this);
    mgroup->addButton(mcloseBtn);
    mgroup->addButton(mcopyBtn);
    mcopyBtn->setChecked(true);

    QHBoxLayout *hlayout5 =new QHBoxLayout;
    hlayout5->addStretch(0);
    hlayout5->addWidget(mcloseBtn);
    QLabel *lab6 = new QLabel(this);
    lab6->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout5->addWidget(lab6);
    hlayout5->addWidget(mcopyBtn);
    hlayout5->addStretch(0);
    hlayout5->setContentsMargins(0,0,0,0);

    QVBoxLayout *vlayout =new QVBoxLayout(this);
    vlayout->setSpacing(0);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);
    vlayout->addLayout(hlayout5);
    vlayout->addStretch(0);

    connect(msendBtn,&QPushButton::clicked,this,[=](){
        CustomWidget_16 *sendcuccess = new CustomWidget_16(this->parentWidget());
        sendcuccess->setFixedSize(Public_Function::getScaleSize(122,130));
        qDebug()<< " sendcuccess " <<Qt::endl;
        sendcuccess->show();
    });

    connect(mcloseBtn,&QPushButton::clicked,this,[=](){
        emit sendCloseMassage15();
        this->close();
    });
}

void CustomWidget_15::changeTextIcon(QString str, QPixmap pix)
{
    mtetxLab->setText(str);
    miconLab->setPixmap(pix);
}


QPainterPath CustomWidget_15::drawRoundRect_1(int r, int mheight)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-90);
    path.lineTo(this->width(),mheight);
    path.lineTo(0,mheight);
    path.lineTo(0,mheight -r);
    path.arcTo(0,0,2*r,2*r,180,-90);
    return path;
}

void CustomWidget_15::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,255,255));
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(12));
    painter.drawPath(path);
    painter.setBrush(QColor(20,134,250));
    painter.drawPath(drawRoundRect_1(Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(44)));

}

bool CustomWidget_15::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == mcloseLab)
        {
           emit sendCloseMassage15();
           this->close();
           return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}


/********************************CustomWidget_17***********************************************/

CustomWidget_17::CustomWidget_17(int num,QWidget *parent):QWidget(parent),mnum(num)
{
    initLayout();
}

void CustomWidget_17::initLayout()
{
    micon1Lab = new QLabel(this);;
    micon1Lab->setFixedSize(Public_Function::getScaleSize(18,17));
    micon1Lab->setScaledContents(true);
    micon1Lab->setPixmap(QPixmap(":/pixmap/word@2x.png"));

    micon2Lab = new QLabel(this);
    micon2Lab->setFixedSize(Public_Function::getScaleSize(34,18));
    micon2Lab->setScaledContents(true);
    micon2Lab->installEventFilter(this);
    micon2Lab->setPixmap(QPixmap(":/pixmap/gengduo1@2x.png"));

    mtext1Lab = new QLabel(this);
    mtext1Lab->setFixedSize(Public_Function::getScaleSize(232,16));
    mtext1Lab->setText("文件名称字段.doc");

    mtext2Lab = new QLabel(this);
    mtext2Lab->setFixedSize(Public_Function::getScaleSize(259,16));
    mtext2Lab->setText("2020/12/16 16:03");

    mtext3Lab = new QLabel(this);
    mtext3Lab->setFixedSize(Public_Function::getScaleSize(79,16));
    mtext3Lab->setText("10.21 mb");

    mtext4Lab = new QLabel(this);
    mtext4Lab->setFixedSize(Public_Function::getScaleSize(88,16));
    mtext4Lab->setText("下载中 20%");
    mtext4Lab->setStyleSheet("color:rgba(20,134,250,1)");

    QHBoxLayout* hlayout = new QHBoxLayout(this);
    hlayout->setSpacing(0);
    hlayout->addWidget(micon1Lab);
    QLabel* lab1 = new QLabel(this);
    lab1->setFixedSize(Public_Function::getScaleSize(9,12));
    hlayout->addWidget(lab1);
    hlayout->addWidget(mtext1Lab);
    hlayout->addWidget(mtext2Lab);
    hlayout->addWidget(mtext3Lab);
    hlayout->addStretch(0);
    hlayout->addWidget(mtext4Lab);
    QLabel* lab2 = new QLabel(this);
    lab2->setFixedSize(Public_Function::getScaleSize(18,12));
    hlayout->addWidget(lab2);
    hlayout->addWidget(micon2Lab);

    mtext4Lab->hide();
}

void CustomWidget_17::setStyle(int num)
{
    mnum = num;
    update();
}

void CustomWidget_17::changePixAndTitel(QPixmap pix, QString str)
{
    micon1Lab->setPixmap(pix.scaled(micon1Lab->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    mtext1Lab->setText(str);
}

void CustomWidget_17::setLoadNum(int num)
{
    mtext4Lab->setText(QString("下载中 %1%").arg(num));
}

void CustomWidget_17::setTimeNum(QString st)
{
     mtext2Lab->setText(st);
}

void CustomWidget_17::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(QPen(QColor(224,224,224),Public_Function::getScaleWidth(1)));
    if(mnum == 1)
    {
        painter.drawLine(this->rect().topLeft(),this->rect().topRight());
        painter.drawLine(this->rect().bottomLeft(),this->rect().bottomRight());
    }
    else if(mnum == 0)
    {
        painter.drawLine(this->rect().topLeft(),this->rect().topRight());
    }
}

bool CustomWidget_17::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == micon2Lab)
        {
           micon2Lab->setFixedSize(Public_Function::getScaleSize(34,18));
           micon2Lab->setScaledContents(true);
           micon2Lab->setPixmap(QPixmap(":/pixmap/caozuo2@2x.png"));
           CustomWidget_19 *w = new CustomWidget_19(this->parentWidget());
           w->setFixedSize(Public_Function::getScaleSize(92,184));
           w->move(mapToParent(micon2Lab->pos()) +QPoint(-Public_Function::getScaleWidth(50),Public_Function::getScaleWidth(30)));
           connect(w,&CustomWidget_19::sendMessage,this,&CustomWidget_17::getInstruct);
           connect(this,&CustomWidget_17::sendMessage17,this,[=](){w->changeLoadText(tr("查看文件"));});
           w->show();
           return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void CustomWidget_17::getInstruct(QString st)
{
    if(st == "share")
    {
        QFrame *frame = new QFrame;
        frame->setAttribute(Qt::WA_TranslucentBackground,true);
        frame->showFullScreen();
        CustomWidget_14* sharewidget = new CustomWidget_14(frame);
        sharewidget->show();
        connect(sharewidget,&CustomWidget_14::sendCloseMassage14,this,[=](){
           frame->hide();
           frame->deleteLater();
           sharewidget->deleteLater();
        });

        connect(sharewidget->mbackBtn,&Custom_Btn3::clicked,this,[=](){
            frame->hide();
            frame->deleteLater();
            sharewidget->deleteLater();
        });

        connect(sharewidget->mlinkBtn,&Custom_Btn3::clicked,this,[=](){
            frame->show();
            sharewidget->hide();
            CustomWidget_15* linewidget = new CustomWidget_15(frame);
            linewidget->show();
            connect(linewidget,&CustomWidget_15::sendCloseMassage15,this,[=](){
                frame->close();
                linewidget->close();
                linewidget->deleteLater();
                frame->deleteLater();
            });
        });
    }
    else if(st == "load")
    {
        mtext4Lab->show();
        QTimer *timer = new QTimer(this);
        timer->start(100);
        connect(timer,&QTimer::timeout,this,[=](){
            micon2Lab->setFixedSize(Public_Function::getScaleSize(18,18));
            micon2Lab->setScaledContents(true);
            micon2Lab->setPixmap(QPixmap(":/pixmap/qingchu@2x.png"));
            static int a=0;
            a++;
            setLoadNum(a*5);
            if(a == 20)
            {
                emit sendMessage17();
                timer->stop();
                a =0;
            }
        });
    }
}


/********************************CustomWidget_18***********************************************/

CustomWidget_18::CustomWidget_18(QWidget *parent):QWidget(parent)
{
    initLayout();
}

void CustomWidget_18::initLayout()
{

}

void CustomWidget_18::setPageNum(int num)
{
    pagenum =num;
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    for(int i=1; i < pagenum +1; i++)
    {
        CustomWidget_17 *w =new CustomWidget_17(0,this);
        if(i == pagenum) w->setStyle(1);
        w->setFixedSize(Public_Function::getScaleSize(825,54));
        vlayout->addWidget(w);
        listwi.append(w);
    }
    vlayout->addStretch(0);
}

void CustomWidget_18::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(this->rect());
}


/********************************CustomWidget_19***********************************************/

CustomWidget_19::CustomWidget_19(QWidget *parent):QWidget(parent)
{
    initLayout();
    initConnect();
}

void CustomWidget_19::initLayout()
{
    shareBtn = new QPushButton(tr("云分享"),this);
    shareBtn->setFixedSize(Public_Function::getScaleSize(80,36));
    shareBtn->setStyleSheet("background-color:white;color:rgba(68,68,68,1);border:none;");
    loadBtn = new QPushButton(tr("下载"),this);
    loadBtn->setFixedSize(Public_Function::getScaleSize(80,36));
    loadBtn->setStyleSheet("background-color:white;color:rgba(68,68,68,1);border:none;");
    renameBtn = new QPushButton(tr("重命名"),this);
    renameBtn->setFixedSize(Public_Function::getScaleSize(80,36));
    renameBtn->setStyleSheet("background-color:white;color:rgba(68,68,68,1);border:none;");
    deleteBtn = new QPushButton(tr("删除"),this);
    deleteBtn->setFixedSize(Public_Function::getScaleSize(80,36));
    deleteBtn->setStyleSheet("background-color:white;color:rgba(68,68,68,1);border:none;");
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setAlignment(Qt::AlignHCenter);
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    vlayout->addStretch(0);
    vlayout->addWidget(shareBtn);
    vlayout->addStretch(0);
    vlayout->addWidget(loadBtn);
    vlayout->addStretch(0);
    vlayout->addWidget(renameBtn);
    vlayout->addStretch(0);
    vlayout->addWidget(deleteBtn);
    vlayout->addStretch(0);
}

void CustomWidget_19::initConnect()
{
    connect(shareBtn,&QPushButton::clicked,this,[=](){
        emit sendMessage("share");
    });

    connect(loadBtn,&QPushButton::clicked,this,[=](){
        emit sendMessage("load");
    });

    connect(renameBtn,&QPushButton::clicked,this,[=](){
        emit sendMessage("rename");
    });

    connect(deleteBtn,&QPushButton::clicked,this,[=](){
        emit sendMessage("delete");
    });
}

void CustomWidget_19::changeLoadText(QString str)
{
    loadBtn->setText(str);
}



void CustomWidget_19::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    QColor color(105, 105, 105);
    int border = 3;
    int j;
    for(int i=0; i<border; i++)
    {
        j = border -i;
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        j = Public_Function::getScaleWidth(j);
        path.addRoundedRect(j,j,this->width() -j*2,this->height() -j*2,Public_Function::getScaleWidth(9),Public_Function::getScaleWidth(9));
        switch(i)
        {
        case 0:
            color.setAlpha(7);
            break;
        case 1:
            color.setAlpha(10);
            break;
        case 2:
            color.setAlpha(15);
            break;
        case 3:
            color.setAlpha(20);
            break;
        case 4:
            color.setAlpha(50);
            break;
        case 5:
            color.setAlpha(80);
            break;
        default:
            break;
        }
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);
        painter.drawPath(path);
    }
    painter.setBrush(Qt::white);
    painter.setPen(QPen(QColor(238,238,238),Public_Function::getScaleWidth(1)));
    QPainterPath path;
    path.addRoundedRect(Public_Function::getScaleWidth(3),Public_Function::getScaleWidth(3), this->width() - Public_Function::getScaleWidth(6),
                        this->height()- Public_Function::getScaleWidth(6), Public_Function::getScaleWidth(9),Public_Function::getScaleWidth(9));
    painter.drawPath(path);
    painter.setPen(QPen(QColor(238,238,238),Public_Function::getScaleWidth(1)));
    int num = Public_Function::getScaleWidth(10);
    painter.drawLine(QPoint(num,this->height()*1/4),QPoint(this->width() -num,this->height()*1/4));
    painter.drawLine(QPoint(num,this->height()*2/4),QPoint(this->width() -num,this->height()*2/4));
    painter.drawLine(QPoint(num,this->height()*3/4),QPoint(this->width() -num,this->height()*3/4));

}

/********************************CustomWidget_20***********************************************/

CustomWidget_20::CustomWidget_20(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(360,238));
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,(desktop->height() -this->height())/2);
    initLayout();
}

void CustomWidget_20::initLayout()
{
    mtitelLab = new QLabel(this);
    mtitelLab->setFixedSize(Public_Function::getScaleSize(80,20));
    QFont font("Microsoft YaHei Bold",16,65);
    mtitelLab->setFont(font);
    mtitelLab->setStyleSheet(QString("color:rgba(255,255,255,1);font-size:%1px").arg(Public_Function::getScaleWidth(16)));
    mtitelLab->setText(tr("文件云分享"));
    mcloseLab = new QLabel(this);
    mcloseLab->installEventFilter(this);
    mcloseLab->setFixedSize(Public_Function::getScaleSize(19,19));
    mcloseLab->setScaledContents(true);
    mcloseLab->setPixmap(QPixmap(":/pixmap/guanbi3@2x.png"));
    QHBoxLayout *hlayout1 =new QHBoxLayout;
    hlayout1->addWidget(mtitelLab);
    hlayout1->addStretch(0);
    hlayout1->addWidget(mcloseLab);
    hlayout1->setContentsMargins(0,Public_Function::getScaleWidth(5),Public_Function::getScaleWidth(10),Public_Function::getScaleWidth(48));

    mLab1 = new QLabel(this);
    mLab1->setFixedSize(Public_Function::getScaleSize(56,16));
    mLab1->setText(tr("提取码"));
    mLab1->setStyleSheet(QString("color:rgba(68,68,68,1);font-size:%1px").arg(14));
    medit = new QLineEdit(this);
    medit->setFixedSize(Public_Function::getScaleSize(222,42));
    medit->setPlaceholderText(tr("  输入提取码"));
    medit->setStyleSheet("background-color:rgba(240,240,240,1)");
    QHBoxLayout *hlayout2 =new QHBoxLayout;
    hlayout2->addStretch(0);
    hlayout2->addWidget(mLab1);
    QLabel *lab = new QLabel(this);
    lab->setFixedSize(Public_Function::getScaleSize(10,12));
    hlayout2->addWidget(lab);
    hlayout2->addWidget(medit);
    hlayout2->addStretch(0);
    hlayout2->setContentsMargins(0,0,0,Public_Function::getScaleWidth(40));

    mcancelBtn = new Custom_Btn3(this);
    mcancelBtn->setText_m(tr("取消"));
    mcancelBtn->setFixedSize(Public_Function::getScaleSize(100,42));
    mcheckoutBtn = new Custom_Btn3(this);
    mcheckoutBtn->setText_m(tr("验证"));
    mcheckoutBtn->setFixedSize(Public_Function::getScaleSize(100,42));
    mgroup = new QButtonGroup(this);
    mgroup->addButton(mcancelBtn);
    mgroup->addButton(mcheckoutBtn);
    mcheckoutBtn->setChecked(true);

    QHBoxLayout *hlayout3 =new QHBoxLayout;
    hlayout3->addStretch(0);
    hlayout3->addWidget(mcancelBtn);
    QLabel *lab2 = new QLabel(this);
    lab2->setFixedSize(Public_Function::getScaleSize(20,12));
    hlayout3->addWidget(lab2);
    hlayout3->addWidget(mcheckoutBtn);
    hlayout3->addStretch(0);
    hlayout3->setContentsMargins(0,0,0,0);

    QVBoxLayout *vlayout =new QVBoxLayout(this);
    vlayout->setSpacing(0);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addStretch(0);

    connect(mcheckoutBtn,&Custom_Btn3::clicked,this,[=](){
        emit sendCheckOut();
    });

    connect(mcancelBtn,&Custom_Btn3::clicked,this,[=](){
        emit sendCloseMassage20();
    });
}

QPainterPath CustomWidget_20::drawRoundRect_1(int r, int mheight)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-90);
    path.lineTo(this->width(),mheight);
    path.lineTo(0,mheight);
    path.lineTo(0,mheight -r);
    path.arcTo(0,0,2*r,2*r,180,-90);
    return path;
}

void CustomWidget_20::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,255,255));
    QPainterPath path;
    path.addRoundedRect(0.5,0.5,this->width()-2,this->height()-2,Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(12));
    painter.drawPath(path);
    painter.setBrush(QColor(20,134,250));
    painter.drawPath(drawRoundRect_1(Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(44)));

}

bool CustomWidget_20::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == mcloseLab)
        {
           emit sendCloseMassage20();
           this->close();
           return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

/********************************CustomWidget_21***********************************************/
#if  1
CustomWidget_21::CustomWidget_21(QWidget *parent) :
    QWidget(parent)
{
    initWidget();
    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this,[=](){ this->hide();m_pTimer->stop(); });
}

CustomWidget_21* CustomWidget_21::getToolTip(int tooltipStyle) {
    static QPointer<CustomWidget_21> toolTip = nullptr;
    if (nullptr ==  toolTip) {
        toolTip = new CustomWidget_21;
    }
    toolTip->setToolTipStyle(tooltipStyle);
    return toolTip;
}



void CustomWidget_21::setToolTipStyle(int tooltipStyle) {
    this->m_pToolTipStyle = tooltipStyle;
    if (0 == m_pToolTipStyle)
        hLayout->setContentsMargins(6, 6, 6, 15);
    else if (1 == m_pToolTipStyle)
        hLayout->setContentsMargins(6, 6, 6, 6);
}

void CustomWidget_21::showMBox(QPoint pt) {
    this->move(QPoint(pt.x() - this->width()/2, pt.y() - this->height()));
    this->show();
    m_pTimer->start(2000);
}

void CustomWidget_21::showMBox(QWidget *parent, const QString &text, QPoint pt) {
    this->setText(text);

    this->setParent(parent);
    this->move(QPoint(pt.x() - this->width()/2, pt.y() - this->height()));
    this->raise();
    this->show();
    m_pTimer->start(2000);
}

void CustomWidget_21::setText(const QString &text) {
    m_pLabelText->setText(text);
    m_pFrame->adjustSize();
    this->adjustSize();
    update();
}

QString CustomWidget_21::getText()
{
    return m_pLabelText->text();
}

void CustomWidget_21::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    /* 画阴影  */
    QColor color(105, 105, 105);
    int border = 6;
    int tHeight = 9;
    int j;
    int radius = 8;
    for(int i=0; i<border; i++)
    {
        j = border - i;
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        if (0 == m_pToolTipStyle)
        {
            QPoint topLeft_p1 = QPoint(j, j + radius);
            QPoint topLeft_p2 = QPoint(j + radius, j);
            QPoint topRight_p1 = QPoint(this->width() - j - radius, topLeft_p2.y());
            QPoint topRight_p2 = QPoint(this->width() - j, topLeft_p1.y());
            QPoint BottomRight_p1 = QPoint(topRight_p2.x(), this->height() - j - tHeight - radius);
            QPoint BottomRight_p2 = QPoint(topRight_p1.x(),  this->height() - j - tHeight);
            QPoint BottomLeft_p1 = QPoint(topLeft_p2.x(), BottomRight_p2.y());
            QPoint BottomLeft_p2 = QPoint(topLeft_p1.x(),  BottomRight_p1.y());
            path.moveTo(topLeft_p1);
            path.cubicTo(topLeft_p1, QPoint(j, j), topLeft_p2);
            path.lineTo(topRight_p1);
            path.cubicTo(topRight_p1, QPoint(this->width() - j, j), topRight_p2);
            path.lineTo(BottomRight_p1);
            path.cubicTo(BottomRight_p1, QPoint(this->width() - j, this->height() - j - tHeight), BottomRight_p2);
            path.lineTo(this->width()/2 + 6, BottomRight_p2.y());
            path.lineTo(this->width()/2, BottomRight_p2.y() + tHeight);
            path.lineTo(this->width()/2 - 6, BottomRight_p2.y());
            path.lineTo(BottomLeft_p1);
            path.cubicTo(BottomLeft_p1, QPoint(j, this->height() - j - tHeight),  BottomLeft_p2);
            path.lineTo(topLeft_p1);
        }else if (1 == m_pToolTipStyle) {
            path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2, radius, radius);
        }

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
        painter.setPen(pen);
        painter.drawPath(path);
    }

    /* 画背景色 */
    j = border + 1;
    QPainterPath path;
    if (0 == m_pToolTipStyle) {
        QPoint topLeft_p1 = QPoint(j, j + radius);
        QPoint topLeft_p2 = QPoint(j + radius, j);
        QPoint topRight_p1 = QPoint(this->width() - j - radius, topLeft_p2.y());
        QPoint topRight_p2 = QPoint(this->width() - j, topLeft_p1.y());
        QPoint BottomRight_p1 = QPoint(topRight_p2.x(), this->height() - j - tHeight - radius);
        QPoint BottomRight_p2 = QPoint(topRight_p1.x(),  this->height() - j - tHeight);
        QPoint BottomLeft_p1 = QPoint(topLeft_p2.x(), BottomRight_p2.y());
        QPoint BottomLeft_p2 = QPoint(topLeft_p1.x(),  BottomRight_p1.y());
        path.moveTo(topLeft_p1);
        path.cubicTo(topLeft_p1, QPoint(j, j), topLeft_p2);
        path.lineTo(topRight_p1);
        path.cubicTo(topRight_p1, QPoint(this->width() - j, j), topRight_p2);
        path.lineTo(BottomRight_p1);
        path.cubicTo(BottomRight_p1, QPoint(this->width() - j, this->height() - j - tHeight), BottomRight_p2);
        path.lineTo(this->width()/2 + 6, BottomRight_p2.y());
        path.lineTo(this->width()/2, BottomRight_p2.y() + tHeight);
        path.lineTo(this->width()/2 - 6, BottomRight_p2.y());
        path.lineTo(BottomLeft_p1);
        path.cubicTo(BottomLeft_p1, QPoint(j, this->height() - j - tHeight),  BottomLeft_p2);
        path.lineTo(topLeft_p1);
    }else if (1 == m_pToolTipStyle) {
        path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2, radius, radius);
    }

    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::white);
    painter.drawPath(path);
}

void CustomWidget_21::initWidget() {
    hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(6, 6, 6, 15);
    m_pFrame = new QFrame(this);
    m_pFrame->setObjectName("frame");
    m_pFrame->setStyleSheet("#frame{border: none;}");
    hLayout->addWidget(m_pFrame);

    QHBoxLayout *layout2 = new QHBoxLayout(m_pFrame);
    layout2->setContentsMargins(10, 10, 10, 10);
    layout2->setSpacing(0);

    m_pLabelText = new QLabel(m_pFrame);
    m_pLabelText->setAlignment(Qt::AlignCenter);
    m_pLabelText->setStyleSheet("color: gray;");
    QFont font;
    font.setPixelSize(22);
    m_pLabelText->setFont(font);
    layout2->addWidget(m_pLabelText);
    this->adjustSize();
}



/********************************CustomWidget_22***********************************************/

CustomWidget_22::CustomWidget_22(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(Public_Function::getScaleSize(252,252));
    initLayout();
}

void CustomWidget_22::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,255,255,245));
    painter.drawRect(this->rect());
}

void CustomWidget_22::initLayout()
{
    pixLab = new QLabel(this);
    pixLab->setFixedSize(Public_Function::getScaleSize(78,78));
    pixLab->setScaledContents(true);

    text1Lab = new QLabel(this);
    text1Lab->setAlignment(Qt::AlignCenter);
    text1Lab->setStyleSheet(QString("color:rgba(34,34,34,1);font-size:%1px;").arg(Public_Function::getScaleWidth(26)));

    text2Lab = new QLabel(this);
    text2Lab->setAlignment(Qt::AlignCenter);
    text2Lab->setStyleSheet(QString("color:rgba(136,136,136,1);font-size:%1px;").arg(Public_Function::getScaleWidth(16)));

    text3Lab = new QLabel(this);
    text3Lab->installEventFilter(this);
    text3Lab->setAlignment(Qt::AlignCenter);
    text3Lab->setStyleSheet(QString("color:rgba(87,117,193,1);font-size:%1px;").arg(Public_Function::getScaleWidth(16)));

    vlayout = new QVBoxLayout(this);
    vlayout->setAlignment(Qt::AlignHCenter);
    hlayout = new QHBoxLayout();
    hlayout->addStretch();
    hlayout->addWidget(pixLab);
    hlayout->addStretch();
    vlayout->addStretch(0);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(text1Lab);
    vlayout->addWidget(text2Lab);
    vlayout->addWidget(text3Lab);
    vlayout->addStretch(0);
}

bool CustomWidget_22::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == text3Lab)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sendStateMessage(flag);
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}


void CustomWidget_22::changePixAndText(QPixmap pictrue, QString st1, QString st2, QString st3,int mflag)
{
   pixLab->setPixmap(pictrue);
   text1Lab->setText(st1);
   text2Lab->setText(st2);
   text3Lab->setText(st3);
   if(text2Lab->text().isEmpty())text2Lab->hide();
   flag = mflag;
}

CustomWidget_23::CustomWidget_23(QWidget *parent) :
    QWidget(parent)
{
}

void CustomWidget_23::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::transparent);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawPath(drawRoundRect(Public_Function::getScaleWidth(18)));
}

QPainterPath CustomWidget_23::drawRoundRect(int r)
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

#endif
