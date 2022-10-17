#include "menupanel.h"
#include "ui_menupanel.h"

MenuPanel::MenuPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuPanel)
{
    ui->setupUi(this);
    this->initWidget();
}

MenuPanel::~MenuPanel()
{
    delete ui;
}

void MenuPanel::resizeWidget()
{
    ui->verticalLayout->setContentsMargins(6, 6, 6, 6);
    QSize size = Public_Function::getScaleSize(QSize(166, 270));
    this->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(155, 50));
    ui->pNew->setFixedSize(size);
    ui->pOpen->setFixedSize(size);
    ui->pSave->setFixedSize(size);
    ui->pExport->setFixedSize(size);
    //ui->pShare->setFixedSize(size);
    ui->pLanguage->setFixedSize(size);
    ui->pSet->setFixedSize(size);
    ui->pAboutUs->setFixedSize(size);
    ui->pExit->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(32, 32));
    ui->pNew->mSetIconSize(size);
    ui->pOpen->mSetIconSize(size);
    ui->pSave->mSetIconSize(size);
    ui->pExport->mSetIconSize(size);
    //ui->pShare->mSetIconSize(size);
    ui->pLanguage->mSetIconSize(size);
    ui->pSet->mSetIconSize(size);
    ui->pAboutUs->mSetIconSize(size);
    ui->pExit->mSetIconSize(size);
    ui->pNew->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
    ui->pOpen->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
    ui->pSave->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
    ui->pExport->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
//    ui->pShare->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
    ui->pLanguage->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
    ui->pSet->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
    ui->pAboutUs->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
    ui->pExit->mSetMargins(Public_Function::getScaleSize(21), 0, 0, 0);
    ui->pNew->mSetSpacing(Public_Function::getScaleSize(21));
    ui->pOpen->mSetSpacing(Public_Function::getScaleSize(21));
    ui->pSave->mSetSpacing(Public_Function::getScaleSize(21));
    ui->pExport->mSetSpacing(Public_Function::getScaleSize(21));
    //ui->pShare->mSetSpacing(Public_Function::getScaleSize(21));
    ui->pLanguage->mSetSpacing(Public_Function::getScaleSize(21));
    ui->pSet->mSetSpacing(Public_Function::getScaleSize(21));
    ui->pAboutUs->mSetSpacing(Public_Function::getScaleSize(21));
    ui->pExit->mSetSpacing(Public_Function::getScaleSize(21));
    QFont font = Public_Function::getFont(16);
    ui->pNew->mSetFont(font);
    ui->pOpen->mSetFont(font);
    ui->pSave->mSetFont(font);
    ui->pExport->mSetFont(font);
    //ui->pShare->mSetFont(font);
    ui->pLanguage->mSetFont(font);
    ui->pSet->mSetFont(font);
    ui->pAboutUs->mSetFont(font);
    ui->pExit->mSetFont(font);
    //ui->pNew->mSetRadius(radius, radius, 0, 0);
    //ui->pExit->mSetRadius(0, 0, radius, radius);
//djf    ui->pLanguage->hide();

    m_ExportPanel->resizeWidget();
}

void MenuPanel::show()
{
    QWidget::show();
    this->raise();
}

void MenuPanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
    if (!m_ExportPanel->isHidden())
        m_ExportPanel->hide();
}

bool MenuPanel::isSaveEnabled()
{
    return ui->pSave->isEnabled();
}

void MenuPanel::disableSet()
{
    group->setExclusive(false);
    ui->pSet->setChecked(false);
    group->setExclusive(true);
}

void MenuPanel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::transparent);
    QColor color(135, 135, 135);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    int border = 6;
    int alpha;
    for(int i = 0; i < border; i++)
    {
        QRect rect = QRect(QPoint(border - i, border - i),
                           QPoint(this->width() - (border - i),
                            this->height() - (border - i)));
        QPainterPath path;
        int radius = Public_Function::getScaleSize(4);
        path = Public_Function::getRoundRectPath(rect, radius);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }
        switch(i)
        {
        case 0: alpha = 80; break;
        case 1: alpha = 50; break;
        case 2: alpha = 30; break;
        case 3: alpha = 15; break;
        case 4: alpha = 10; break;
        case 5: alpha = 7; break;
        }
        color.setAlpha(alpha);
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void MenuPanel::initWidget()
{
    ui->verticalLayoutWidget_4->hide();
    this->setLayout(ui->verticalLayout);
    ui->verticalLayout->setSpacing(0);
    group =new QButtonGroup(this);
    group->setExclusive(true);
    QColor color = QColor(238, 238, 238);
    ui->pNew->mSetIcon(QPixmap(":/images/main/menu/xinjian@2x.png"));
    ui->pNew->mSetText(tr("新建白板"));
    ui->pNew->mSetHoverColor(color);
    ui->pOpen->mSetIcon(QPixmap(":/images/main/menu/daoru@2x.png"));
    ui->pOpen->mSetText(tr("打开/导入"));
    ui->pOpen->mSetHoverColor(color);
    ui->pSave->mSetIcon(QPixmap(":/images/main/menu/baocun@2x.png"));
    ui->pSave->mSetText(tr("保存白板"));
    ui->pSave->mSetHoverColor(color);
    ui->pSave->mSetEnabled(false);
    ui->pSave->hide();
    ui->pExport->mSetIcon(QPixmap(":/images/main/menu/daochu@2x.png"));
    ui->pExport->mSetText(tr("另存/导出"));
    ui->pExport->mSetHoverColor(color);
    ui->pExport->mSetCheckedIcon(QPixmap(":/images/main/menu/daochu2@2x.png"));
    ui->pShare->mSetIcon(QPixmap(":/images/main/menu/fenxiang@2x.png"));
    ui->pShare->mSetText(tr("扫码分享"));
    ui->pShare->mSetHoverColor(color);
    ui->pShare->hide();
    if (0 == ApplicationConfig::readConfig(CONFIG_KEY_LANGUAGE).compare("2")) {
        ui->pLanguage->mSetIcon(QPixmap(":/images/main/menu/yuyan2@2x.png"));
        ui->pLanguage->mSetText(tr("切换中文"));
    }else {
        ui->pLanguage->mSetIcon(QPixmap(":/images/main/menu/yuyan@2x.png"));
        ui->pLanguage->mSetText(tr("切换英文"));
    }
    ui->pLanguage->mSetHoverColor(color);

    ui->pSet->setCheckable(true);
    ui->pSet->mSetIcon(QPixmap(":/images/main/menu/baiban@2x.png"));
    ui->pSet->mSetText(tr("白板设置"));
    ui->pSet->mSetHoverColor(color);
    ui->pSet->mSetCheckedIcon(QPixmap(":/images/main/menu/baiban -1@2x.png"));

    ui->pAboutUs->mSetIcon(QPixmap(":/images/main/menu/guanyu@2x.png"));
    ui->pAboutUs->mSetText(tr("关于我们"));
    ui->pAboutUs->mSetHoverColor(color);

    ui->pExit->mSetIcon(QPixmap(":/images/main/menu/tuichu@2x.png"));
    ui->pExit->mSetText(tr("退出软件"));
    ui->pExit->mSetHoverColor(color);

    connect(ui->pNew, &PushButton_5::clicked, this, [=](){ emit this->newBoard(); });
    connect(ui->pOpen, &PushButton_5::clicked, this, [=](){ emit this->openFile(); });
    connect(ui->pExport, &PushButton_5::toggled, this, &MenuPanel::onBtnExportToggled);
    connect(ui->pAboutUs, &PushButton_5::clicked, this, [=](){ emit this->showAboutUs(); });
    connect(ui->pSet, &PushButton_5::clicked, this, [=](){ emit this->sendSetBoardSignal();});
    connect(ui->pExit, &PushButton_5::clicked, this, [=](){ emit this->exitApplication(); });
    connect(GlobalSignal::getInstance(), &GlobalSignal::appSaveEnabled, this, [=](){ ui->pSave->setEnabled(true); });

    m_ExportPanel = new MenuPanel_Export;
    m_ExportPanel->hide();
    connect(m_ExportPanel, &MenuPanel_Export::panelHide, this, [=](){ui->pExport->setChecked(false);});
    connect(m_ExportPanel, &MenuPanel_Export::exportToFile, this, [=](int i) { emit this->exportToFile(i);});

    //djf
    connect(ui->pLanguage, &QPushButton::clicked, this, [=](){
        bool isChinese = true;
        if (0 == ApplicationConfig::readConfig(CONFIG_KEY_LANGUAGE).compare("2")) {
            //chinese 1
        }else {
            isChinese = false;
            //english 2
        }
        toggleLanguage(isChinese);
        updateLanguage();
    });


    //group->addButton(ui->pExport);
    group->addButton(ui->pSet);
}

void MenuPanel::updateLanguage()
{
    ui->pNew->mSetText(tr("新建白板"));
    ui->pOpen->mSetText(tr("打开/导入"));
    ui->pSave->mSetText(tr("保存白板"));
    ui->pExport->mSetText(tr("另存/导出"));
    ui->pShare->mSetText(tr("扫码分享"));
    ui->pSet->mSetText(tr("白板设置"));
    ui->pAboutUs->mSetText(tr("关于我们"));
    ui->pExit->mSetText(tr("退出软件"));
    if (0 == ApplicationConfig::readConfig(CONFIG_KEY_LANGUAGE).compare("2")) {
        ui->pLanguage->mSetIcon(QPixmap(":/images/main/menu/yuyan2@2x.png"));
        ui->pLanguage->mSetText(tr("切换中文"));
    }else {
        ui->pLanguage->mSetIcon(QPixmap(":/images/main/menu/yuyan@2x.png"));
        ui->pLanguage->mSetText(tr("切换英文"));
    }


}

void MenuPanel::onBtnExportToggled(bool checked)
{
    if (checked) {
        QWidget *parent = (QWidget *)this->parent();
        m_ExportPanel->setParent(parent);
        int x, y;
        QRect rect = ui->pExport->geometry();
        x = this->x() + this->width() + Public_Function::getScaleSize(10);
        y = this->y() + rect.y() + rect.height()/2 - m_ExportPanel->height()/2;
        x = (x + m_ExportPanel->width()) > parent->width() ? (this->x() - m_ExportPanel->width() - Public_Function::getScaleSize(10)) :
                                                             x;
        m_ExportPanel->move(x, y);
        m_ExportPanel->show();
    }else {
        m_ExportPanel->hide();
    }
}
