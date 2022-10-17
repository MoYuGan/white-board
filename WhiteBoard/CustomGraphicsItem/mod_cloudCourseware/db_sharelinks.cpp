#include "db_sharelinks.h"
#include "ui_db_sharelinks.h"
#include <QClipboard>

DB_ShareLinks::DB_ShareLinks(const QString &fileId, const QString &link, const QString &fileName, const QString &createTime, QWidget *parent) :
    QWidget(parent),
    m_pFileId(fileId),
    ui(new Ui::DB_ShareLinks)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
    ui->label_name->setText(fileName);
    ui->label_time->setText(createTime);
    ui->lineEdit_link->setText(link);
    ui->lineEdit_link->setReadOnly(true);
}

DB_ShareLinks::~DB_ShareLinks()
{
    delete ui;
}

void DB_ShareLinks::show()
{
    QWidget::show();
    this->raise();
    //窗口居中显示
    QWidget *parent = (QWidget *)this->parent();
    if (nullptr != parent) {
        this->move(QPoint((parent->width() - this->width())/2, (parent->height() - this->height())/2));
    }
}

void DB_ShareLinks::resize()
{
    QSize size = DB_ApplicationScale::getScaleSize(QSize(490, 260));
    this->setFixedSize(size);
    ui->frame_title->setGeometry(6, 6, this->width() - 12,
                           DB_ApplicationScale::getScaleWidth(51));
    ui->label_title->setGeometry(DB_ApplicationScale::getScaleWidth(20),
                           DB_ApplicationScale::getScaleWidth(10),
                           DB_ApplicationScale::getScaleWidth(391),
                           DB_ApplicationScale::getScaleWidth(34));
    ui->label_close->setGeometry(DB_ApplicationScale::getScaleWidth(450),
                           DB_ApplicationScale::getScaleWidth(20),
                           DB_ApplicationScale::getScaleWidth(16),
                           DB_ApplicationScale::getScaleWidth(16));
    ui->label_3->setGeometry(DB_ApplicationScale::getScaleWidth(30),
                           DB_ApplicationScale::getScaleWidth(90),
                           DB_ApplicationScale::getScaleWidth(16),
                           DB_ApplicationScale::getScaleWidth(18));
    ui->label_name->setGeometry(DB_ApplicationScale::getScaleWidth(50),
                           DB_ApplicationScale::getScaleWidth(90),
                           DB_ApplicationScale::getScaleWidth(231),
                           DB_ApplicationScale::getScaleWidth(21));
    ui->label_time->setGeometry(DB_ApplicationScale::getScaleWidth(320),
                           DB_ApplicationScale::getScaleWidth(90),
                           DB_ApplicationScale::getScaleWidth(151),
                           DB_ApplicationScale::getScaleWidth(21));
    ui->label_line->setGeometry(6, DB_ApplicationScale::getScaleWidth(120),
                           this->width() - 12,
                           DB_ApplicationScale::getScaleWidth(1));
    ui->label_telephone->setGeometry(DB_ApplicationScale::getScaleWidth(30),
                           DB_ApplicationScale::getScaleWidth(153),
                           DB_ApplicationScale::getScaleWidth(18),
                           DB_ApplicationScale::getScaleWidth(18));
    ui->lineEdit_telephone->setGeometry(DB_ApplicationScale::getScaleWidth(60),
                           DB_ApplicationScale::getScaleWidth(145),
                           DB_ApplicationScale::getScaleWidth(245),
                           DB_ApplicationScale::getScaleWidth(30));
    ui->label_telephoneShare->setGeometry(DB_ApplicationScale::getScaleWidth(370),
                           DB_ApplicationScale::getScaleWidth(145),
                           DB_ApplicationScale::getScaleWidth(91),
                           DB_ApplicationScale::getScaleWidth(30));
    ui->label_link->setGeometry(DB_ApplicationScale::getScaleWidth(30),
                                DB_ApplicationScale::getScaleWidth(200),
                                DB_ApplicationScale::getScaleWidth(18),
                                DB_ApplicationScale::getScaleWidth(18));
    ui->lineEdit_link->setGeometry(DB_ApplicationScale::getScaleWidth(60),
                                   DB_ApplicationScale::getScaleWidth(195),
                                   DB_ApplicationScale::getScaleWidth(245),
                                   DB_ApplicationScale::getScaleWidth(30));
    ui->label_copyLink->setGeometry(DB_ApplicationScale::getScaleWidth(370),
                                    DB_ApplicationScale::getScaleWidth(195),
                                    DB_ApplicationScale::getScaleWidth(91),
                                    DB_ApplicationScale::getScaleWidth(30));

    ui->frame_title->setStyleSheet(QString("#%1{   \
                                   border: none;    \
                                   background-color: rgb(78,155,252);   \
                                   border-top-left-radius: %2px; \
                                   border-top-right-radius: %2px;    \
                                   }").arg(ui->frame_title->objectName())
                                    .arg(QString::number(DB_ApplicationScale::getScaleWidth(8))));
    ui->label_telephoneShare->setStyleSheet(QString("QLabel{ \
                              background-color:  rgb(78,155,252);   \
                              border: none; \
                              border-radius: %1px;   \
                              color: white; \
                              }").arg(QString::number(DB_ApplicationScale::getScaleWidth(8))));
    ui->label_copyLink->setStyleSheet(QString("QLabel{ \
                              background-color:  rgb(78,155,252);   \
                              border: none; \
                              border-radius: %1px;   \
                              color: white; \
                              }").arg(QString::number(DB_ApplicationScale::getScaleWidth(8))));
    size = DB_ApplicationScale::getScaleSize(QSize(120, 80));
    ui->messageBox->setFixedSize(size);


    /* 设置字体 */
    QFont font = DB_ApplicationScale::getFont(16);
    ui->label_title->setFont(font);
    font = DB_ApplicationScale::getFont(14);
    ui->label_name->setFont(font);
    ui->label_time->setFont(font);
    ui->lineEdit_link->setFont(font);
    ui->lineEdit_telephone->setFont(font);
    ui->label_telephoneShare->setFont(font);
    ui->label_copyLink->setFont(font);
}

void DB_ShareLinks::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    QColor color(105, 105, 105);
    int border = 6;
    int j;
    for(int i=0; i<border; i++)
    {
        j = border - i;
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2,
                            DB_ApplicationScale::getScaleWidth(8),
                            DB_ApplicationScale::getScaleWidth(8));
        if (i == 0)
            painter.fillPath(path, QBrush(Qt::white));
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

void DB_ShareLinks::initWidget()
{
    ui->frame_loading->hide();
    ui->messageBox->hide();
    //设置手机号码格式,只允许按格式输入
    QRegExp regexp("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    QRegExpValidator *validator = new QRegExpValidator(regexp);
    ui->lineEdit_telephone->setValidator(validator);

    /* 创建http请求线程 */
    m_pHttpThread = new DB_HttpThread;
    connect(m_pHttpThread, &DB_HttpThread::httpThreadFinished, this, &DB_ShareLinks::onHttpThreadFinished);

    /* 连接信号与槽 */
    connect(ui->label_close, &DB_CustomLabel_1::mouseClicked, [=](){
        if (!ui->frame_loading->isHidden()) {
            m_pHttpThread->stop();
            ui->frame_loading->hide();
        }
        emit panelClosed();
    });
    connect(ui->label_copyLink, &DB_CustomLabel_1::mouseClicked, [=](){
        QString text = ui->lineEdit_link->text();
        QClipboard *clipboard = QApplication::clipboard();   //获取系统剪贴板指针
        clipboard->setText(text);                     //设置剪贴板内容
        ui->messageBox->showMBox(this, tr("复制完成"), QPoint(this->rect().center().x(),
                                                          this->rect().center().y() + ui->messageBox->height()/2));
        return true;
    });
    connect(ui->label_telephoneShare, &DB_CustomLabel_1::mouseClicked, this, &DB_ShareLinks::shareLinkToPhone);
}

bool DB_ShareLinks::checkTelephone(const QString &str, QString *tip)
{
    if (str.isEmpty()) {
        *tip = QString(tr("请输入手机号码"));
        return false;
    }

    if (11 != str.length()) {
        *tip = QString(tr("请输入正确的手机号码"));
        return false;
    }
    return true;
}



void DB_ShareLinks::shareLinkToPhone()
{
    QString tip;
    if (!checkTelephone(ui->lineEdit_telephone->text().trimmed(), &tip)) {
        ui->messageBox->showMBox(this, tip, QPoint(this->rect().center().x(),
                                                          this->rect().center().y() + ui->messageBox->height()/2));
        return;
    }

    //检查账号是否已经注册
    m_pHttpThread->start(HttpFunction::MobileSharing, QList<QString>() << m_pFileId << ui->lineEdit_telephone->text());
    //显示加载框
    ui->frame_loading->setGeometry(ui->frame_title->x(), ui->frame_title->y() + ui->frame_title->height(),
                                   ui->frame_title->width(), this->height() - ui->frame_title->height() - 12);
    ui->frame_loading->show();
}

void DB_ShareLinks::onHttpThreadFinished(HttpFunction fun, QVariant variant)
{
    _HttpRetData data = variant.value<_HttpRetData>();
    switch(fun) {
    case HttpFunction::MobileSharing: {
        if (1 == data.state) {
            ui->messageBox->showMBox(this, tr("分享成功"), QPoint(this->rect().center().x(),
                                                              this->rect().center().y() + ui->messageBox->height()/2));
        }else if (2 == data.state) {
            ui->messageBox->showMBox(this, tr("该账号不存在"), QPoint(this->rect().center().x(),
                                                              this->rect().center().y() + ui->messageBox->height()/2));
        }else {
            ui->messageBox->showMBox(this, tr("分享失败"), QPoint(this->rect().center().x(),
                                                              this->rect().center().y() + ui->messageBox->height()/2));
        }
        ui->frame_loading->hide();
    }break;
    default:
        break;
    }
}
