#include "db_login.h"
#include "ui_db_login.h"

#include <QEvent>
#include <QMouseEvent>
#include <QtConcurrent/QtConcurrent>
#include <QtDebug>
#include <QRegExp>
#include <QRegExpValidator>
#include <QToolTip>
#include <QMovie>

const QString str_WhiteBoardTeacher = "wihteboardteacher";
const QString str_WhiteBoardUser    = "wihteboarduser";

DB_Login::DB_Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DB_Login)
{
    ui->setupUi(this);
    initWidget();
    this->resize();
#if 1
    //http请求线程
    m_pHttpThread = new DB_HttpThread;
    connect(m_pHttpThread, &DB_HttpThread::httpThreadFinished, this, &DB_Login::onHttpThreadFinished);

    connect(ui->label_passwordLogin, &DB_CustomLabel_1::mouseClicked, [=](){
        ui->stackedWidget->setCurrentWidget(ui->widget);
        ui->label_line->setStyleSheet("background: rgb(85, 85, 85);");
        ui->label_line1->setStyleSheet("background: rgba(0, 0, 0, 0);");
        ui->label_passwordLogin->setStyleSheet("color: black;");
        ui->label_qrcodelogin->setStyleSheet("color: gray;");

        if (!ui->pushButton_cancelLogin->isHidden()) {
            ui->label_qrcode->isShowLogo(false);
            ui->pushButton_cancelLogin->hide();
            ui->label_registerNow_2->show();
        }
        m_pHttpThread->stop();
    });

    connect(ui->label_qrcodelogin, &DB_CustomLabel_1::mouseClicked, [=](){
        ui->stackedWidget->setCurrentWidget(ui->widget_2);
        ui->label_line->setStyleSheet("background: rgba(0, 0, 0, 0);");
        ui->label_line1->setStyleSheet("background: rgb(85, 85, 85);");
        ui->label_passwordLogin->setStyleSheet("color: gray;");
        ui->label_qrcodelogin->setStyleSheet("color: black;");

        //获取二维码
        m_pHttpThread->start(HttpFunction::GetQrCode, QList<QString>() << str_WhiteBoardUser);
    });

    connect (ui->label_registerNow, &DB_CustomLabel_1::mouseClicked, [=](){
        emit this->showRegisterPage();
    });

    connect (ui->label_registerNow_2, &DB_CustomLabel_1::mouseClicked, [=](){
        emit this->showRegisterPage();
    });

    //设置手机号码格式,只允许按格式输入
    QRegExp regexp("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    QRegExpValidator *validator = new QRegExpValidator(regexp);
    ui->lineEdit_telephone->setValidator(validator);

    //提示框
    m_pMBoxToolTip = new DB_CustomWidget1;
    m_pMBoxToolTip->setParent((QWidget*)ui->pushButton_login->parent());
    m_pMBoxToolTip->setFixedSize(Public_Function::getScaleSize(300,100));
    m_pMBoxToolTip->hide();

#endif
}

DB_Login::~DB_Login()
{
    if (m_pHttpThread)
        delete m_pHttpThread;
    delete ui;
}

void DB_Login::show()
{
    QWidget::show();

    ui->lineEdit_telephone->clear();
    ui->lineEdit_password->clear();
    ui->stackedWidget->setCurrentWidget(ui->widget);
    ui->label_passwordLogin->setStyleSheet("color: black;");
    ui->label_qrcodelogin->setStyleSheet("color: gray;");
    ui->label_line->setStyleSheet("background: black;");
    ui->label_line1->setStyleSheet("background: rgba(165, 165, 165);");
}

void DB_Login::resize()
{
    QSize size = Public_Function::getScaleSize(QSize(40, 30));
    ui->verticalLayout->setContentsMargins(size.width(), size.height(), size.width(), 0);
    ui->verticalLayout_2->setSpacing(size.height());
    ui->verticalLayout_2->setContentsMargins(0, size.height(), 0, Public_Function::getScaleSize(10));
    ui->verticalLayout_3->setSpacing(size.height());
    ui->verticalLayout_3->setContentsMargins(0, size.height(), 0, Public_Function::getScaleSize(10));
    ui->horizontalLayout_12->setContentsMargins(Public_Function::getScaleSize(10), 0, 0, 0);
    ui->horizontalLayout_13->setContentsMargins(Public_Function::getScaleSize(10), 0, 0, 0);
    size = Public_Function::getScaleSize(QSize(0, 50));
    ui->frame->setFixedHeight(size.height());
    ui->frame_2->setFixedHeight(size.height());
    ui->pushButton_login->setFixedHeight(size.height());
    size = Public_Function::getScaleSize(QSize(18, 18));
    ui->label_userIcon->setFixedSize(size);
    ui->label_passwdIcon->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(180, 180));
    ui->label_qrcode->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(145, 45));
    ui->pushButton_cancelLogin->setFixedSize(size);

    QFont font = Public_Function::getFont(16);
    ui->label_passwordLogin->setFont(font);
    ui->label_qrcodelogin->setFont(font);
    ui->pushButton_login->setFont(font);
    ui->pushButton_cancelLogin->setFont(font);
    font = Public_Function::getFont(14);
    ui->lineEdit_telephone->setFont(font);
    ui->lineEdit_password->setFont(font);
    ui->label_registerNow->setFont(font);
    ui->label_registerNow_2->setFont(font);
    ui->label_text->setFont(font);

    ui->frame->setStyleSheet(QString("#%1{border: 1px solid rgb(105, 105, 105); "
                                     "border-radius: %2px}").arg(ui->frame->objectName())
                                    .arg(Public_Function::getScaleSize(5)));
    ui->frame_2->setStyleSheet(QString("#%1{border: 1px solid rgb(105, 105, 105); "
                                     "border-radius: %2px}").arg(ui->frame_2->objectName())
                                    .arg(Public_Function::getScaleSize(5)));
}

void DB_Login::stopHttpThread()
{
    m_pHttpThread->stop();
    if (!ui->frame_loading->isHidden())
        ui->frame_loading->hide();
}


void DB_Login::initWidget()
{
    this->setLayout(ui->verticalLayout);
    ui->widget->setLayout(ui->verticalLayout_2);
    ui->widget_2->setLayout(ui->verticalLayout_3);
    ui->frame->setLayout(ui->horizontalLayout_12);
    ui->frame_2->setLayout(ui->horizontalLayout_13);
    ui->stackedWidget->addWidget(ui->widget);
    ui->stackedWidget->addWidget(ui->widget_2);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    ui->pushButton_cancelLogin->hide();
    ui->frame_loading->hide();
}

bool DB_Login::checkTelephone(const QString &str, QString *tip)
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

bool DB_Login::checkPassword(const QString &str, QString *tip)
{
    if (str.isEmpty()) {
        *tip = QString(tr("请输入密码"));
        return false;
    }
    return true;
}

//bool DB_Login::checkVerificationCode(const QString &str, QString *tip)
//{
//    if (str.isEmpty()) {
//        *tip = QString(tr("请输入验证码"));
//        return false;
//    }

//    if (6 != str.length()) {
//        *tip = QString(tr("请输入正确的验证码"));
//        return false;
//    }

//    return true;
//}


void DB_Login::on_pushButton_login_clicked()
{
    QString tip;
#if 1
    if (!checkTelephone(ui->lineEdit_telephone->text().trimmed(), &tip)) {
        m_pMBoxToolTip->setText(tip);
        ui->lineEdit_telephone->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_login->x() + ui->pushButton_login->width()/2, ui->pushButton_login->y()));
        return;
    }

    if (!checkPassword(ui->lineEdit_password->text().trimmed(), &tip)) {
        m_pMBoxToolTip->setText(tip);
        ui->lineEdit_password->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_login->x() + ui->pushButton_login->width()/2, ui->pushButton_login->y()));
        return;
    }

    //检查账号是否已经注册
    m_pHttpThread->start(HttpFunction::CheckRegistered, QList<QString>() << ui->lineEdit_telephone->text());
    //显示加载框
    ui->frame_loading->show();
#endif
}

//void DB_Login::getVerificationCode()
//{
//    QString tip;
//    if (!checkTelephone(ui->lineEdit_telephone->text().trimmed(), &tip)) {
//        m_pMBoxToolTip->setText(tip);
//        ui->lineEdit_telephone->setFocus();
//        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_login->x() + ui->pushButton_login->width()/2, ui->pushButton_login->y()));
//        return;
//    }

//    m_pHttpThread->start(HttpFunction::GetVerificationCode, QList<QString>() << ui->lineEdit_telephone->text());
//    //显示加载框
//    ui->frame_loading->show();
//}

void DB_Login::onHttpThreadFinished(HttpFunction fun, QVariant variant)
{
    _HttpRetData data = variant.value<_HttpRetData>();
    switch(fun) {
    //获取二维码返回
    case HttpFunction::GetQrCode: {
        if (1 == data.state) {  //获取成功
            //提取二维码消息体
            QrCodeData codeData = data.variant.value<QrCodeData>();
            //获取二维码登录凭证
            m_pQrCodeUUID = codeData.uuid;
            //显示二维码
            ui->label_qrcode->setString(codeData.url);
            //隐藏加载框
            ui->frame_loading->hide();
            //监听登录状态
            m_pHttpThread->start(HttpFunction::QrCodeLogin, QList<QString>() << m_pQrCodeUUID);
        }else { //获取失败
        }
    }break;
    //监听登录状态返回(登录状态:1登录成功 2登录失败 3未扫描 4已扫描 5已取消 6二维码过期 7未绑定用户)
    case HttpFunction::QrCodeLogin: {
        if (1 == data.state) {    //登录成功
            //提取用户信息消息体
            _UserInfoData userData = data.variant.value<_UserInfoData>();
            //显示用户面板
            emit showUserPanel(userData);
        }else {     //未登录
            if (4 == data.state || 7 == data.state) {    //已扫码
                if (ui->pushButton_cancelLogin->isHidden()) {
                    ui->label_registerNow_2->hide();
                    ui->label_qrcode->isShowLogo(true);
                    ui->pushButton_cancelLogin->show();
                }
            }else if (5 == data.state){
                if (!ui->pushButton_cancelLogin->isHidden()) {
                    ui->label_registerNow_2->show();
                    ui->label_qrcode->isShowLogo(false);
                    ui->pushButton_cancelLogin->hide();
                }
            } //其他情况

            m_pHttpThread->start(HttpFunction::QrCodeLogin, QList<QString>() << m_pQrCodeUUID);
        }
    }break;
    // 取消二维码登录返回
    case HttpFunction::CancelQrCodeLogin: {
        if (1 == data.state) {    //取消成功
            //隐藏logo
            ui->label_qrcode->isShowLogo(false);
            ui->pushButton_cancelLogin->hide();
            ui->label_registerNow_2->show();
            //重新监听登录状态
            m_pHttpThread->start(HttpFunction::QrCodeLogin, QList<QString>() << m_pQrCodeUUID);
        }else { //取消失败
            m_pHttpThread->start(HttpFunction::CancelQrCodeLogin, QList<QString>() << m_pQrCodeUUID);
        }
    }break;
    //注册检查返回
    case HttpFunction::CheckRegistered:{
        if (1 == data.state) {  //未注册
            ui->frame_loading->hide();
            m_pMBoxToolTip->setText(tr("该手机号码未注册"));
            m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_login->x() + ui->pushButton_login->width()/2, ui->pushButton_login->y()));
        }else if (2 == data.state){ //已注册
            m_pHttpThread->start(HttpFunction::LoginAccount,
                             QList<QString>() << ui->lineEdit_telephone->text() << ui->lineEdit_password->text() << "");
        }
    }break;
    //账号密码登录返回
    case HttpFunction::LoginAccount: {
        if (1 == data.state) {  //登录成功
            //提取用户信息消息体
            _UserInfoData userData = data.variant.value<_UserInfoData>();
            //显示用户面板
            emit showUserPanel(userData);
        }else{
            if (2 == data.state)    //密码错误
                m_pMBoxToolTip->setText(tr("密码错误"));
            else    //其他情况
                m_pMBoxToolTip->setText(tr("登录失败"));

            ui->lineEdit_password->clear();
            ui->lineEdit_password->setFocus();
            m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_login->x() + ui->pushButton_login->width()/2, ui->pushButton_login->y()));
        }
        //隐藏加载框
        ui->frame_loading->hide();
    }break;
    case HttpFunction::GetVerificationCode: {
        if (1 == data.state) {
            m_pMBoxToolTip->setText(tr("发送成功"));
        }else {
            m_pMBoxToolTip->setText(tr("发送失败"));
        }
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_login->x() + ui->pushButton_login->width()/2, ui->pushButton_login->y()));
        ui->frame_loading->hide();
    }break;
    default:
        break;
    }
}


void DB_Login::on_pushButton_cancelLogin_clicked()
{
    m_pHttpThread->start(HttpFunction::CancelQrCodeLogin, QList<QString>() << m_pQrCodeUUID);
}
