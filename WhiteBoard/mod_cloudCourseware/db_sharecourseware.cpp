#include "db_sharecourseware.h"
#include "ui_db_sharecourseware.h"
#include <QMouseEvent>
#include <QEvent>
#include <QStandardItemModel>
#include <QtDebug>
#include <QScrollBar>
#include "Public/public_function.h"

DB_ShareCourseware::DB_ShareCourseware(_CoIoData data, QWidget *parent) :
    m_pCoIoData(data),
    QWidget(parent),
    ui(new Ui::DB_ShareCourseware)
{
    ui->setupUi(this);
    this->initWidget();
    this->resize();
}

DB_ShareCourseware::~DB_ShareCourseware()
{
    delete ui;
}

void DB_ShareCourseware::show()
{
    QWidget::show();
    this->raise();
    //窗口居中显示
    QWidget *parent = (QWidget *)this->parent();
    if (nullptr != parent) {
        this->move(QPoint((parent->width() - this->width())/2, (parent->height() - this->height())/2));
    }
}

void DB_ShareCourseware::resize()
{
    QSize size = Public_Function::getScaleSize(QSize(490, 490));
    this->setFixedSize(size);
    ui->frame_title->setGeometry(6, 6, this->width() - 12,
                           Public_Function::getScaleSize(51));
    ui->label_title->setGeometry(Public_Function::getScaleSize(20),
                           Public_Function::getScaleSize(10),
                           Public_Function::getScaleSize(391),
                           Public_Function::getScaleSize(34));
    ui->label_close->setGeometry(Public_Function::getScaleSize(450),
                           Public_Function::getScaleSize(20),
                           Public_Function::getScaleSize(16),
                           Public_Function::getScaleSize(16));
    ui->label_3->setGeometry(Public_Function::getScaleSize(30),
                           Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(16),
                           Public_Function::getScaleSize(18));
    ui->label_name->setGeometry(Public_Function::getScaleSize(50),
                           Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(231),
                           Public_Function::getScaleSize(21));
    ui->label_time->setGeometry(Public_Function::getScaleSize(320),
                           Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(151),
                           Public_Function::getScaleSize(21));
    ui->label_line->setGeometry(6, Public_Function::getScaleSize(120),
                           this->width() - 12,
                           Public_Function::getScaleSize(1));
    ui->frame_2->setGeometry(Public_Function::getScaleSize(60),
                           Public_Function::getScaleSize(120),
                           Public_Function::getScaleSize(367),
                           Public_Function::getScaleSize(171));
    ui->label_linkName->setGeometry(Public_Function::getScaleSize(10),
                           Public_Function::getScaleSize(10),
                           Public_Function::getScaleSize(351),
                           Public_Function::getScaleSize(71));
    ui->label_viewLink->setGeometry(Public_Function::getScaleSize(10),
                           Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(351),
                           Public_Function::getScaleSize(71));
    ui->label->setGeometry(Public_Function::getScaleSize(30),
                           Public_Function::getScaleSize(310),
                           Public_Function::getScaleSize(75),
                           Public_Function::getScaleSize(30));
    ui->label_viewLink->setGeometry(Public_Function::getScaleSize(10),
                           Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(351),
                           Public_Function::getScaleSize(71));
    ui->radioButton_public->setGeometry(Public_Function::getScaleSize(130),
                           Public_Function::getScaleSize(310),
                           Public_Function::getScaleSize(55),
                           Public_Function::getScaleSize(30));
    ui->radioButton_private->setGeometry(Public_Function::getScaleSize(210),
                           Public_Function::getScaleSize(310),
                           Public_Function::getScaleSize(55),
                           Public_Function::getScaleSize(30));
    ui->label_2->setGeometry(Public_Function::getScaleSize(30),
                           Public_Function::getScaleSize(350),
                           Public_Function::getScaleSize(75),
                           Public_Function::getScaleSize(30));
    ui->comboBox->setGeometry(Public_Function::getScaleSize(130),
                           Public_Function::getScaleSize(350),
                           Public_Function::getScaleSize(150),
                           Public_Function::getScaleSize(30));
    ui->label_line1->setGeometry(6, Public_Function::getScaleSize(400),
                           this->width() - 12,
                           Public_Function::getScaleSize(1));
    ui->pShare->setGeometry(Public_Function::getScaleSize(380),
                           Public_Function::getScaleSize(430),
                           Public_Function::getScaleSize(92),
                           Public_Function::getScaleSize(32));

    ui->frame_title->setStyleSheet(QString("#%1{   \
                                   border: none;    \
                                   background-color: rgb(78,155,252);   \
                                   border-top-left-radius: %2px; \
                                   border-top-right-radius: %2px;    \
                                   }").arg(ui->frame_title->objectName())
                                    .arg(QString::number(Public_Function::getScaleSize(8))));
    ui->frame_2->setStyleSheet(QString("#%1{       \
                               border: none;        \
                               background-color: rgba(245,245,245); \
                               border-radius: %2px;  \
                               }").arg(ui->frame_2->objectName())
                                .arg(QString::number(Public_Function::getScaleSize(8))));
    ui->pShare->setStyleSheet(QString("QPushButton{ \
                              background-color:  rgb(78,155,252);   \
                              border: none; \
                              border-radius: %1px;   \
                              color: white; \
                              }").arg(QString::number(Public_Function::getScaleSize(8))));
    ui->radioButton_public->setStyleSheet(QString("QRadioButton::indicator{"
                                                  "width:%1px;"
                                                  "height:%1px;}")
                                          .arg(QString::number(Public_Function::getScaleSize(16))));
    ui->radioButton_private->setStyleSheet(QString("QRadioButton::indicator{"
                                                  "width:%1px;"
                                                  "height:%1px;}")
                                          .arg(QString::number(Public_Function::getScaleSize(16))));


    /* 设置字体 */
    QFont font = Public_Function::getFont(16);
    ui->label_title->setFont(font);
    font = Public_Function::getFont(14);
    ui->label_name->setFont(font);
    ui->label_time->setFont(font);
    ui->label_linkName->setFont(font);
    ui->label_viewLink->setFont(font);
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->radioButton_public->setFont(font);
    ui->radioButton_private->setFont(font);
    ui->comboBox->setFont(font);
    ui->pShare->setFont(font);
}

void DB_ShareCourseware::paintEvent(QPaintEvent *event)
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

void DB_ShareCourseware::initWidget()
{
    /* 初始化显示 */
    ui->label_linkName->setText(QString(tr("课件分享：《%1》")).arg(m_pCoIoData.fileName));
    ui->label_name->setText(m_pCoIoData.fileName);
    ui->label_time->setText(m_pCoIoData.createTime);
    ui->comboBox->addItem(tr("一天"));
    ui->comboBox->addItem(tr("一周"));
    ui->comboBox->addItem(tr("一月"));
    ui->comboBox->setCurrenIndex(0);
    ui->radioButton_public->setChecked(true);

    /* 连接信号与槽 */
    connect(ui->comboBox, &DB_CustomComboBox::currentItemChanged,
            this, &DB_ShareCourseware::onComboBoxItemChanged);
    connect(ui->radioButton_private, &QRadioButton::clicked, this, &DB_ShareCourseware::getSharingLinks);
    connect(ui->radioButton_public, &QRadioButton::clicked, this, &DB_ShareCourseware::getSharingLinks);
    connect(ui->label_close, &DB_CustomLabel_1::mouseClicked, [=](){ emit this->panelClosed(); });
    connect(ui->pShare, &QPushButton::clicked, [=](){
        //if (ui->label_link->text().isEmpty())
         //   return;

        m_pShareLinks = new DB_ShareLinks(QString::number(m_pCoIoData.fileId), ui->label_viewLink->text(), m_pCoIoData.fileName,
                                          m_pCoIoData.createTime,  (QWidget *)this->parent());
        connect(m_pShareLinks, &DB_ShareLinks::panelClosed, [=](){
            m_pShareLinks->deleteLater();
            m_pShareLinks = nullptr;
            emit panelClosed();
        });
        this->hide();
        this->setCursor(Qt::ArrowCursor);
        m_pShareLinks->show();
    });

    /* 创建http请求线程 */
    m_pHttpThread = new DB_HttpThread;
    connect(m_pHttpThread, &DB_HttpThread::httpThreadFinished, this, &DB_ShareCourseware::onHttpThreadFinished);

    //生成分享链接
    this->getSharingLinks();

}


void DB_ShareCourseware::onComboBoxItemChanged(int index)
{
    Q_UNUSED(index)
    ui->comboBox->hideListView();
    this->getSharingLinks();
}


void DB_ShareCourseware::getSharingLinks()
{
    // 是否加密, 2=是, 1=否
    int isEncrypt = ui->radioButton_public->isChecked() ? 1 : 2;
    // 过期时间 1一天,2一周,3一月
    int inDate = ui->comboBox->currentIndex() + 1;
    m_pHttpThread->start(HttpFunction::GenerateLink, QList<QString>() << QString::number(m_pCoIoData.whiteRelateId)
                         << QString::number(isEncrypt) << QString::number(inDate));
}

void DB_ShareCourseware::onHttpThreadFinished(HttpFunction fun, QVariant variant)
{
    _HttpRetData data = variant.value<_HttpRetData>();
    switch(fun) {
    case HttpFunction::GenerateLink: {
        if (1 == data.state) {
            _ShaLinkData sdata = data.variant.value<_ShaLinkData>();
            QString password = sdata.password;
            if (!password.isEmpty())
                password = tr("密码：") + password;

            ui->label_viewLink->setText(QString("%1 %2").arg(sdata.code).arg(password));
        }
    }break;

    default:
        break;
    }
}
