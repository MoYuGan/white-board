#include "db_accountmanagement.h"
#include "ui_db_accountmanagement.h"
#include "Public/public_function.h"

#include <QPainter>

DB_AccountManagement::DB_AccountManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DB_AccountManagement)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
}

DB_AccountManagement::~DB_AccountManagement()
{
    delete ui;
}

void DB_AccountManagement::show()
{
    QWidget::show();
    //置顶显示
    this->raise();
    //窗口居中显示
    QWidget *parent = (QWidget *)this->parent();
    if (nullptr != parent) {
        this->move(QPoint((parent->width() - this->width())/2, (parent->height() - this->height())/2));
    }
}

void DB_AccountManagement::resize()
{
    QSize size = Public_Function::getScaleSize(QSize(460, 290));
    this->setFixedSize(size);

    ui->label->setGeometry(6, 6, this->width() - 12,
                           Public_Function::getScaleSize(50));
    ui->label_userIcon->setGeometry(Public_Function::getScaleSize(20),
                           Public_Function::getScaleSize(80),
                           Public_Function::getScaleSize(56),
                           Public_Function::getScaleSize(56));
    ui->label_username->setGeometry(Public_Function::getScaleSize(100),
                           Public_Function::getScaleSize(83),
                           Public_Function::getScaleSize(221),
                           Public_Function::getScaleSize(25));
    ui->label_telephone->setGeometry(Public_Function::getScaleSize(100),
                           Public_Function::getScaleSize(110),
                           Public_Function::getScaleSize(221),
                           Public_Function::getScaleSize(25));
    ui->label_cancellation->setGeometry(Public_Function::getScaleSize(350),
                           Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(80),
                           Public_Function::getScaleSize(35));
    ui->label_weixinLogo->setGeometry(Public_Function::getScaleSize(30),
                           Public_Function::getScaleSize(160),
                           Public_Function::getScaleSize(40),
                           Public_Function::getScaleSize(37));
    ui->label_weixinName->setGeometry(Public_Function::getScaleSize(100),
                           Public_Function::getScaleSize(165),
                           Public_Function::getScaleSize(221),
                           Public_Function::getScaleSize(30));
    ui->label_unbundling->setGeometry(Public_Function::getScaleSize(360),
                           Public_Function::getScaleSize(165),
                           Public_Function::getScaleSize(61),
                           Public_Function::getScaleSize(30));
    ui->label_line->setGeometry(6, Public_Function::getScaleSize(210),
                           this->width() - 12,
                           Public_Function::getScaleSize(1));
    ui->label_closed->setGeometry(Public_Function::getScaleSize(170),
                           Public_Function::getScaleSize(230),
                           Public_Function::getScaleSize(120),
                           Public_Function::getScaleSize(40));

    ui->label->setStyleSheet(QString("color: white; \
                             background-color: rgb(78, 155, 252);   \
                             border-top-left-radius: %1px;   \
                             border-top-right-radius: %1px;").arg(QString::number(Public_Function::getScaleSize(8))));
    ui->label_closed->setStyleSheet(QString("color: white;  \
                                    background-color: rgb(78, 155, 252);    \
                                    border-radius: %1px;").arg(QString::number(Public_Function::getScaleSize(5))));

    /* 设置字体 */
    QFont font = Public_Function::getFont(16);
    ui->label->setFont(font);
    font = Public_Function::getFont(14);
    ui->label_username->setFont(font);
    ui->label_telephone->setFont(font);
    ui->label_weixinName->setFont(font);
    ui->label_unbundling->setFont(font);
    ui->label_cancellation->setFont(font);
    ui->label_closed->setFont(font);
    ui->messageBox->setFont(font);

    //设置加载框大小位置
    ui->frame_loading->setGeometry(0, 0, this->width(), this->height() - ui->label_line->y());
}

void DB_AccountManagement::setMsg(const QPixmap &userIcon, const QString &userName, const QString &telephone, const QString &weixinName)
{
    m_pTelephone = telephone;
    ui->label_userIcon->setIcon(userIcon);
    ui->label_username->setText(userName);
    ui->label_telephone->setText(QString("%1****%2").arg(m_pTelephone.mid(0, 3)).arg(m_pTelephone.mid(7, 4)));
    ui->label_weixinName->setText(weixinName);
}

void DB_AccountManagement::setUserIcon(const QPixmap &userIcon)
{
    ui->label_userIcon->setIcon(userIcon);
}

void DB_AccountManagement::paintEvent(QPaintEvent *event)
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
                            Public_Function::getScaleSize(8),
                            Public_Function::getScaleSize(8));
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

void DB_AccountManagement::initWidget()
{ 
    ui->frame_loading->hide();
    ui->messageBox->hide();

    /* 创建http请求线程 */
    m_pHttpThread = new DB_HttpThread;
    connect(m_pHttpThread, &DB_HttpThread::httpThreadFinished, this, &DB_AccountManagement::onHttpThreadFinished);

    /* 连接控件信号与槽 */
    connect(ui->label_cancellation, &DB_CustomLabel_1::mouseClicked, [=](){
        m_pHttpThread->stop();
        m_pHttpThread->start(HttpFunction::Cancellation, QList<QString>());
    });
    connect(ui->label_unbundling, &DB_CustomLabel_1::mouseClicked, [=](){
        m_pHttpThread->stop();
        m_pHttpThread->start(HttpFunction::UnBind, QList<QString>() << m_pTelephone);
    });
    connect(ui->label_closed, &DB_CustomLabel_1::mouseClicked, [=](){
        m_pHttpThread->stop();
        if (!ui->frame_loading->isHidden())
            ui->frame_loading->hide();

        emit this->panelClosed();
    });
}

void DB_AccountManagement::onHttpThreadFinished(HttpFunction fun, QVariant variant)
{
    _HttpRetData data = variant.value<_HttpRetData>();
    switch(fun) {
    case HttpFunction::Cancellation: {
        if (1 == data.state) {}
        emit this->cancellation();
    }break;
    case HttpFunction::UnBind: {
        if (2 == data.state) {
            ui->messageBox->showMBox(this, tr("手机未绑定"), QPoint(this->rect().center().x(), this->rect().center().y() + 50));
        }else if (1 == data.state) {
            ui->messageBox->showMBox(this, tr("解绑成功"), QPoint(this->rect().center().x(), this->rect().center().y() + 50));
            ui->label_unbundling->hide();
        }else {
            ui->messageBox->showMBox(this, tr("解绑失败"), QPoint(this->rect().center().x(), this->rect().center().y() + 50));
        }
    }break;
    default:
        break;
    }
}
