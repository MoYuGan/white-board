#include "db_loginpanel.h"
#include "ui_db_loginpanel.h"

#include <QPainter>
#include <QtDebug>
#include <QEvent>
#include <QMouseEvent>

DB_LoginPanel::DB_LoginPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DB_LoginPanel)
{
    ui->setupUi(this);
    initWidget();
    this->resize();

    connect(ui->label_closed, &DB_CustomLabel_1::mouseClicked, this, &DB_LoginPanel::closePanel);
    connect(ui->label_closed2, &DB_CustomLabel_1::mouseClicked, this, &DB_LoginPanel::closePanel);
    connect(ui->label_backIcon, &DB_CustomLabel_1::mouseClicked, [=](){
        ui->stackedWidget_2->setCurrentWidget(ui->widget);
    });
    connect(ui->label_backIconText, &DB_CustomLabel_1::mouseClicked, [=](){
        ui->stackedWidget_2->setCurrentWidget(ui->widget);
    });
}

DB_LoginPanel::~DB_LoginPanel()
{
    delete ui;
}

void DB_LoginPanel::show()
{
    QWidget::show();
    //窗口居中显示
    QWidget *parent = (QWidget *)this->parent();
    if (nullptr != parent) {
        this->move(QPoint((parent->width() - this->width())/2, (parent->height() - this->height())/2));
    }
    //设置焦点
    this->setFocus();
    //置顶
    this->raise();
    //初始化显示
    this->initDisplay();
}

void DB_LoginPanel::resize()
{
    QSize size = Public_Function::getScaleSize(QSize(700, 500));
    this->setFixedSize(size);
    ui->label->setFixedWidth(Public_Function::getScaleSize(300));
    size = Public_Function::getScaleSize(QSize(16, 16));
    ui->label_closed->setFixedSize(size);
    ui->label_closed2->setFixedSize(size);

    QFont font = Public_Function::getFont(12);
    ui->label_backIconText->setFont(font);
    ui->textEdit->setFont(font);
    font = Public_Function::getFont(16);
    ui->label_version->setFont(font);

    ui->label_version->adjustSize();
    ui->label_version->move(Public_Function::getScaleSize(135),
                            Public_Function::getScaleSize(25));
    ui->label_version->raise();
}

void DB_LoginPanel::initDisplay()
{
    ui->stackedWidget_2->setCurrentWidget(ui->widget);
    ui->stackedWidget->setCurrentWidget(m_pLoginPage);
    m_pLoginPage->show();
}


void DB_LoginPanel::paintEvent(QPaintEvent *event)
{
    /*
    *   阴影边框
    */
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
        path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2, 8, 8);
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

void DB_LoginPanel::initWidget()
{
    this->setLayout(ui->horizontalLayout);
    ui->frame->setLayout(ui->horizontalLayout_4);
    ui->widget->setLayout(ui->horizontalLayout_2);
    ui->widget_2->setLayout(ui->verticalLayout_2);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stackedWidget_2->addWidget(ui->widget);
    ui->stackedWidget_2->addWidget(ui->widget_2);
    //只读
    ui->textEdit->setReadOnly(true);

    m_pLoginPage = new DB_Login(this);
    ui->stackedWidget->addWidget(m_pLoginPage);
    m_pRegisterPage = new DB_Register(this);
    ui->stackedWidget->addWidget(m_pRegisterPage);
    ui->stackedWidget->setCurrentWidget(m_pLoginPage);
    m_pLoginPage->show();

    connect(m_pLoginPage, &DB_Login::showRegisterPage, [=](){ ui->stackedWidget->setCurrentWidget(m_pRegisterPage); m_pRegisterPage->show();});
    connect(m_pRegisterPage, &DB_Register::showLoginPage, [=](){ui->stackedWidget->setCurrentWidget(m_pLoginPage); m_pLoginPage->show();});
    connect(m_pLoginPage, &DB_Login::showUserPanel, this, &DB_LoginPanel::showUserPanelSlot);
    connect(m_pRegisterPage, &DB_Register::showDocument, this, &DB_LoginPanel::showDocument);
}

void DB_LoginPanel::showUserPanelSlot(_UserInfoData data)
{
    emit showUserPanel(data);
}

void DB_LoginPanel::showDocument(int i)
{
    ui->stackedWidget_2->setCurrentWidget(ui->widget_2);
    ui->textEdit->clear();
    if (1 == i)
        ui->textEdit->setText(SERVICE_AGREEMENT);
    else
        ui->textEdit->setText(PRIVACY_POLICY);
}

void DB_LoginPanel::closePanel()
{
    if (ui->stackedWidget->currentWidget() == m_pLoginPage) {
        m_pLoginPage->stopHttpThread();
    }else if (ui->stackedWidget->currentWidget() == m_pRegisterPage) {
        m_pRegisterPage->stopHttpThread();
    }
    emit panelClosed();
}
