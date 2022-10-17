#include "db_clouduserpanel.h"
#include "ui_db_clouduserpanel.h"

#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QFileDialog>
#include <QVector>
#include <QtConcurrent/QtConcurrent>

DB_CloudUserPanel::DB_CloudUserPanel(_UserInfoData userData, QWidget *parent) :
    m_pUserData(userData),
    QWidget(parent),
    ui(new Ui::DB_CloudUserPanel)
{
    ui->setupUi(this);
    initWidget();
    this->resize();
}

DB_CloudUserPanel::DB_CloudUserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DB_CloudUserPanel)
{
    ui->setupUi(this);
    initWidget();
    this->resize();
}

DB_CloudUserPanel::~DB_CloudUserPanel()
{
    if (m_pHttpThread)
        delete m_pHttpThread;
    delete ui;
}

void DB_CloudUserPanel::show()
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
    ui->frame_courseware->setStyleSheet(QString("#%1{background-color: rgba(255, 255, 255, 50);}").arg(ui->frame_courseware->objectName()));
    ui->stackedWidget->setCurrentWidget(ui->widget);
}

void DB_CloudUserPanel::resize()
{
    QSize size = Public_Function::getScaleSize(QSize(1000, 700));
    this->setFixedSize(size);
    ui->frame->setGeometry(6, 6, Public_Function::getScaleSize(281),
                           this->height() - 12);
    ui->label->setGeometry(Public_Function::getScaleSize(20),
                           Public_Function::getScaleSize(20),
                           Public_Function::getScaleSize(200),
                           Public_Function::getScaleSize(40));
    ui->label_userIcon->setGeometry(Public_Function::getScaleSize(20),
                           Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(64),
                           Public_Function::getScaleSize(64));
    ui->label_username->setGeometry(Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(150),
                           Public_Function::getScaleSize(30));
    ui->label_telephone->setGeometry(Public_Function::getScaleSize(90),
                           Public_Function::getScaleSize(125),
                           Public_Function::getScaleSize(150),
                           Public_Function::getScaleSize(30));
    ui->label_management->setGeometry(Public_Function::getScaleSize(245),
                           Public_Function::getScaleSize(115),
                           Public_Function::getScaleSize(13),
                           Public_Function::getScaleSize(7));
    ui->frame_courseware->setGeometry(Public_Function::getScaleSize(0),
                           Public_Function::getScaleSize(190),
                           Public_Function::getScaleSize(280),
                           Public_Function::getScaleSize(50));
    ui->label_icon->setGeometry(Public_Function::getScaleSize(20),
                           Public_Function::getScaleSize(20),
                           Public_Function::getScaleSize(5),
                           Public_Function::getScaleSize(12));
    ui->label_courseware->setGeometry(Public_Function::getScaleSize(35),
                           Public_Function::getScaleSize(0),
                           Public_Function::getScaleSize(250),
                           Public_Function::getScaleSize(50));
    ui->label_close->setGeometry(Public_Function::getScaleSize(970),
                           Public_Function::getScaleSize(16),
                           Public_Function::getScaleSize(16),
                           Public_Function::getScaleSize(16));
    ui->stackedWidget->setGeometry(Public_Function::getScaleSize(320),
                           Public_Function::getScaleSize(50),
                           Public_Function::getScaleSize(641),
                           Public_Function::getScaleSize(621));
    ui->widget->setGeometry(0, 0,
                           Public_Function::getScaleSize(641),
                           Public_Function::getScaleSize(621));
    ui->label_5->setGeometry(Public_Function::getScaleSize(0),
                           Public_Function::getScaleSize(0),
                           Public_Function::getScaleSize(641),
                           Public_Function::getScaleSize(31));
    ui->label_headerName->setGeometry(Public_Function::getScaleSize(0),
                           Public_Function::getScaleSize(60),
                           Public_Function::getScaleSize(330),
                           Public_Function::getScaleSize(31));
    ui->label_headerTime->setGeometry(Public_Function::getScaleSize(330),
                           Public_Function::getScaleSize(60),
                           Public_Function::getScaleSize(78),
                           Public_Function::getScaleSize(31));
    ui->label_HeaderMore->setGeometry(Public_Function::getScaleSize(420),
                           Public_Function::getScaleSize(60),
                           Public_Function::getScaleSize(101),
                           Public_Function::getScaleSize(31));
    ui->label_HeaderSize->setGeometry(Public_Function::getScaleSize(520),
                           Public_Function::getScaleSize(60),
                           Public_Function::getScaleSize(121),
                           Public_Function::getScaleSize(31));
    ui->label_up->setGeometry(Public_Function::getScaleSize(395),
                           Public_Function::getScaleSize(68),
                           Public_Function::getScaleSize(8),
                           Public_Function::getScaleSize(4));
    ui->label_down->setGeometry(Public_Function::getScaleSize(395),
                           Public_Function::getScaleSize(80),
                           Public_Function::getScaleSize(8),
                           Public_Function::getScaleSize(4));
    ui->tableView->setGeometry(Public_Function::getScaleSize(0),
                           Public_Function::getScaleSize(100),
                           Public_Function::getScaleSize(641),
                           Public_Function::getScaleSize(451));
    ui->lineEdit_upload->setGeometry(Public_Function::getScaleSize(0),
                           Public_Function::getScaleSize(570),
                           Public_Function::getScaleSize(551),
                           Public_Function::getScaleSize(51));
    ui->pUpload->setGeometry(Public_Function::getScaleSize(550),
                           Public_Function::getScaleSize(570),
                           Public_Function::getScaleSize(92),
                           Public_Function::getScaleSize(51));

    m_tableDelegate->setColumnWidth(0, ui->label_headerName->width());
    m_tableDelegate->setColumnWidth(1, ui->tableView->width() - ui->label_headerName->width()
                                    - ui->label_HeaderMore->width() - ui->label_HeaderSize->width());
    m_tableDelegate->setColumnWidth(2, ui->label_HeaderMore->width());
    m_tableDelegate->setColumnWidth(3, ui->label_HeaderSize->width());

    ui->frame->setStyleSheet(QString("#%1{   \
                             background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(65, 167, 254, 255), stop:0.949438 rgba(92, 143, 251, 255));  \
                             border: none;  \
                             border-top-left-radius: %2px;   \
                             border-bottom-left-radius: %2px;    \
                         }").arg(ui->frame->objectName()).arg(QString::number(Public_Function::getScaleSize(8))));
    ui->lineEdit_upload->setStyleSheet(QString("QLineEdit{  \
                                       border: none;    \
                                       background: rgb(200, 200, 200, 200); \
                                       border-top-left-radius: %1px; \
                                       border-bottom-left-radius: %1px;  \
                                       }").arg(QString::number(Public_Function::getScaleSize(5))));
    ui->pUpload->setStyleSheet(QString("QPushButton{    \
                               background-color: rgb(78, 155, 252); \
                               color: white;    \
                               border: none;    \
                               border-left: none;   \
                               border-top-right-radius: %1px;    \
                               border-bottom-right-radius: %1px;     \
                               }").arg(QString::number(Public_Function::getScaleSize(5))));

    //设置模态框大小位置
    ui->frame_cover->setGeometry(0, 0, this->width(), this->height());
    ui->frame_cover->hide();

    //设置加载框大小位置
    ui->frame_loading->setGeometry(this->rect());
    ui->frame_loading->hide();

    /* 设置字体 */
    QFont font = Public_Function::getFont(16);
    ui->label->setFont(font);
    ui->label_5->setFont(font);
    font = Public_Function::getFont(13);
    ui->label_username->setFont(font);
    ui->label_telephone->setFont(font);
    ui->label_courseware->setFont(font);
    ui->label_headerName->setFont(font);
    ui->label_headerTime->setFont(font);
    ui->label_HeaderSize->setFont(font);
    ui->lineEdit_upload->setFont(font);
    ui->pUpload->setFont(font);
    ui->tableView->setFont(font);
}

void DB_CloudUserPanel::paintEvent(QPaintEvent *event)
{
    /* 绘制阴影效果 */
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), QBrush(Qt::white));

    QColor color(105, 105, 105);
    int border = 6;
    int j;
    for(int i=0; i<border; i++)
    {
        j = border - i;
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2,
                            Public_Function::getScaleSize(8), Public_Function::getScaleSize(8));
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

void DB_CloudUserPanel::initWidget()
{
    ui->stackedWidget->addWidget(ui->widget);
    ui->frame_loading->hide();
    ui->frame_cover->hide();
    ui->messageBox->hide();

    // 设置提示框样式
    ui->messageBox->setStyle(1);

    //创建表格模型
    m_tableModel = new DB_TableModel(this);
    ui->tableView->setModel(m_tableModel);
    /* 创建表格代理 */
    m_tableDelegate = new DB_TableDelegate(this);
    connect(m_tableDelegate, &DB_TableDelegate::changeCursor, this, &DB_CloudUserPanel::onChangMouseCursor);
    connect(m_tableDelegate, &DB_TableDelegate::mouseClicked, this, &DB_CloudUserPanel::onTabelViewMouseClick);
    connect(ui->tableView, &DB_CustomTableView::mouseLeave, m_tableDelegate, &DB_TableDelegate::clearHover);
    ui->tableView->setItemDelegate(m_tableDelegate);

    /* 设置表格视图属性 */
    ui->tableView->setMouseTracking(true);  //鼠标移动实时监听
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //使用QItemDelegate的sizeHint()自定义行宽
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);   //使用QItemDelegate的sizeHint()自定义行高
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setShowGrid(false);  //隐藏表格分割线
    ui->tableView->setFrameShape(QFrame::NoFrame);  //去掉tableView外部边框
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //整行选中
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);    //只允许单行选中

    /* 创建http请求线程 */
    m_pHttpThread = new DB_HttpThread;
    connect(m_pHttpThread, &DB_HttpThread::httpThreadFinished, this, &DB_CloudUserPanel::onHttpThreadFinished);

    /* 创建用户管理面板 */
    m_pAccountManagement = new DB_AccountManagement(this);
    connect(m_pAccountManagement, &DB_AccountManagement::panelClosed, [=](){
        m_pAccountManagement->hide();
        ui->frame_cover->hide();
    });
    connect(m_pAccountManagement, &DB_AccountManagement::cancellation, [=](){
        ui->frame_cover->hide();
        emit cancellation();
    });
    m_pAccountManagement->hide();

    /* 连接控件信号与槽 */
    connect(ui->label_close, &DB_CustomLabel_1::mouseClicked, [=](){
        emit panelClose();
        //清除选中行,取消选中样式
        ui->tableView->clearSelection();
    });
    connect(ui->pUpload, &QPushButton::clicked, this, &DB_CloudUserPanel::uploadCourseware);
    connect(ui->label_up, &DB_CustomLabel_1::mouseClicked, [=](){
        if (0 == m_desc.compare("1")) {
            m_desc = QString("0");
            ui->label_up->setStyleSheet("border-image: url(':/images/up-4.png');");
            ui->label_down->setStyleSheet("border-image: url(':/images/down-5.png');");
            m_tableModel->reverseOrder();
        }
    });
    connect(ui->label_down, &DB_CustomLabel_1::mouseClicked, [=](){
        if (0 == m_desc.compare("0")) {
            m_desc = QString("1");
            ui->label_up->setStyleSheet("border-image: url(':/images/up-5.png');");
            ui->label_down->setStyleSheet("border-image: url(':/images/down-4.png');");
            m_tableModel->reverseOrder();
        }
    });
    connect(ui->label_management, &DB_CustomLabel_1::mouseClicked, [=](){
        ui->frame_cover->show();
        m_pAccountManagement->show();

    });

    /* 初始化显示 */
    this->m_pUserIcon = QPixmap(":/images/courseware/userAvatar.png");
    ui->label_userIcon->setIcon(m_pUserIcon);
    QString userName = m_pUserData.userName;
    if (userName.contains("amdox_Fri Sep"))
        userName = QString(tr("默认用户名"));
    ui->label_username->setText(userName);
    ui->label_telephone->setText(QString("%1****%2").arg(m_pUserData.telephone.mid(0, 3)).arg(m_pUserData.telephone.mid(7, 4)));
    m_pAccountManagement->setMsg(m_pUserIcon, userName, m_pUserData.telephone, m_pUserData.loginTypeName);
    // 单独创建一个http线程获取用户头像
    DB_HttpThread *httpThread = new DB_HttpThread(this);
    connect(httpThread, &DB_HttpThread::httpThreadFinished, this, &DB_CloudUserPanel::onHttpThreadFinished);
    httpThread->start(HttpFunction::GetUserIconData, QList<QString>() << m_pUserData.userIconPath);
    // 获取课件列表
    this->getCoursewareInfo();
    ui->frame_courseware->setStyleSheet(QString("#%1{background-color: rgba(255, 255, 255, 50);}")
                                            .arg(ui->frame_courseware->objectName()));
}

void DB_CloudUserPanel::getCoursewareInfo()
{
    m_pHttpThread->start(HttpFunction::GetCoursewareInfo, QList<QString>()
                         << QString::number(m_pUserData.userId)
                         << m_pUserData.roleName << m_desc);
    ui->frame_loading->show();
}


void DB_CloudUserPanel::uploadCourseware()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getOpenFileName(this, tr("打开文件"), "", "DOC(*.doc);;DOCX(*.docx);;PPT(*.ppt);;PPTX(*.pptx);;XLS(*.xls);;XLSX(*.xlsx)"
                                                                        ";;PDF(*.pdf);;RAR(*.rar);;ZIP(*.zip)");
    if (!fileName.isEmpty()) {
        m_pHttpThread->start(HttpFunction::UploadCourseware, QList<QString>()
                             << QString::number(m_pUserData.userId) << m_pUserData.roleName << fileName);
        ui->frame_loading->show();
    }
}

void DB_CloudUserPanel::showFrameCover()
{
    ui->frame_cover->show();
}

void DB_CloudUserPanel::onChangMouseCursor(Qt::CursorShape shape)
{
    // 改变光标样式
    this->setCursor(shape);
}

void DB_CloudUserPanel::onTabelViewMouseClick(int i, int row)
{
    _CoIoData data = m_tableModel->getCoIoData(row);

    if (0 == i) {       //分享课件
        m_pShareCourseware = new DB_ShareCourseware(data, this);
        connect(m_pShareCourseware, &DB_ShareCourseware::panelClosed, [=](){
            m_pShareCourseware->deleteLater();
            m_pShareCourseware = nullptr;
            ui->frame_cover->hide();
        });
        this->setCursor(Qt::ArrowCursor);
        ui->frame_cover->show();
        m_pShareCourseware->show();
    }else if (1 == i) { //下载课件
        QFileDialog fileDialog;
        _CoIoData codata = m_tableModel->getCoIoData(row);
        QString fileType = codata.fileType;
        fileDialog.setOption(QFileDialog::ShowDirsOnly);
        QString fileName = fileDialog.getSaveFileName(this, tr("下载课件"), QString("/%1.%2").arg(codata.fileName).arg(fileType),
                                                      QString("%1").arg(codata.fileType));
        if (fileName.length() > 0)
        {
            //文件后缀不正确，添加后缀
            if (0 != fileName.mid(fileName.length() - fileType.length(), fileType.length()).compare(fileType))
                fileName.append(QString(".%1").arg(fileType));

            QFile file(fileName);
            if (file.exists()) {
                file.remove();
            }

            //m_pHttpThread->start(HttpFunction::DownloadFile, QList<QString>() << codata.fileSavePath << fileName);
            //connect(m_pHttpThread, &DB_HttpThread::downloadProgress, this, &DB_CloudUserPanel::onDownloadProgress);
        }
    }
}

void DB_CloudUserPanel::onHttpThreadFinished(HttpFunction fun, QVariant variant)
{
    _HttpRetData data = variant.value<_HttpRetData>();
    switch(fun) {
    case HttpFunction::GetCoursewareInfo: { 
        //获取成功
        if (1 == data.state) {
            //更新列表
            QVector<_CoIoData> vector = data.variant.value<QVector<_CoIoData>>();
            m_tableModel->updateData(vector);
        }
        ui->frame_loading->hide();
    }break;
    case HttpFunction::UploadCourseware: {
        ui->frame_loading->hide();
        if (1 == data.state) {
            this->getCoursewareInfo();
            ui->messageBox->showMBox(ui->widget, tr("上传成功"), QPoint(ui->lineEdit_upload->x() + (ui->lineEdit_upload->width()
                                                                    + ui->pUpload->width())/2, ui->lineEdit_upload->y()));
        }else
            ui->messageBox->showMBox(ui->widget, tr("上传失败"), QPoint(ui->lineEdit_upload->x() + (ui->lineEdit_upload->width()
                                                                    + ui->pUpload->width())/2, ui->lineEdit_upload->y()));

    }break;
    case HttpFunction::GetUserIconData: {
        if (1 == data.state) {
            _UsrIcoData icoData = data.variant.value<_UsrIcoData>();
            m_pUserIcon.loadFromData(icoData.data);
            ui->label_userIcon->setIcon(m_pUserIcon);
            m_pAccountManagement->setUserIcon(m_pUserIcon);
        }
        //删除单独创建的获取头像的线程
        DB_HttpThread *httpThread = static_cast<DB_HttpThread*>(sender());
        httpThread->deleteLater();
    }break;
    case HttpFunction::DownloadFile: {
        ui->frame_loading->hide();
    }break;
    default:
        break;
    }
}

void DB_CloudUserPanel::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug()<<"recv:"<<bytesReceived;
    qDebug()<<"total:"<<bytesTotal;
}


