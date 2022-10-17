#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QtDebug>
#include <QDesktopWidget>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->initWidget();
    this->resize();
    ui->tool_right->addPage();
    ui->tool_mid->mSetActionChecked(1, true);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::resize()
{
    this->setFixedSize(1920,890);

    int temp = 0;
    ui->tool_mid->setFixedSize(PublicFunction::getScaleSize(440, 86));
    ui->tool_mid->mSetRadius(PublicFunction::getScaleSize(12), PublicFunction::getScaleSize(12),
                             PublicFunction::getScaleSize(4), PublicFunction::getScaleSize(4));
    temp = PublicFunction::getScaleSize(6);
    ui->tool_mid->mSetTransparentBorder(temp, temp, temp, 0);
    temp = PublicFunction::getScaleSize(12);
    ui->tool_mid->mSetMargin(temp, temp);
    temp = PublicFunction::getScaleSize(5);
    ui->tool_mid->mSetActionMargin(PublicFunction::getScaleSize(11), 0, temp, temp);
    ui->tool_mid->mSetActionSize(PublicFunction::getScaleSize(70), PublicFunction::getScaleSize(50, 50), PublicFunction::getScaleSize(4));
    ui->tool_mid->mSetFont(PublicFunction::getFont(14));

    ui->tool_left->setFixedSize(PublicFunction::getScaleSize(188, 52));
    temp = PublicFunction::getScaleSize(4);
    ui->tool_left->mSetRadius(temp, temp, temp, temp);
    temp = PublicFunction::getScaleSize(4);
    ui->tool_left->mSetTransparentBorder(temp, temp, temp, temp);
    temp = PublicFunction::getScaleSize(5);
    ui->tool_left->mSetMargin(temp, temp);
    temp = PublicFunction::getScaleSize(4);
    ui->tool_left->mSetActionMargin(temp, temp, temp, temp);
    ui->tool_left->mSetActionSize(PublicFunction::getScaleSize(48), PublicFunction::getScaleSize(24, 24));

    ui->tool_mid->move(QPoint((this->width() - ui->tool_mid->width())/2,
                              (this->height() - ui->tool_mid->height())));
    ui->tool_left->move(QPoint(PublicFunction::getScaleSize(16),
                               this->height() - ui->tool_left->height() - PublicFunction::getScaleSize(16) + ui->tool_left->mGetTransparentBorderBottom()));
    ui->tool_right->move(QPoint(this->width() - ui->tool_right->width() - PublicFunction::getScaleSize(16),
                                this->height() - ui->tool_right->height() - PublicFunction::getScaleSize(16) + ui->tool_right->mGetTransparentBorder()));
    ui->pSwitchLeft->move(ui->tool_left->x() + ui->tool_left->width() + PublicFunction::getScaleSize(4), PublicFunction::getScaleSize(16));
    ui->pSwitchRight->move(ui->tool_right->x() - ui->pSwitchRight->width() - PublicFunction::getScaleSize(4), PublicFunction::getScaleSize(16));

    ui->penPanel->setFixedSize(PublicFunction::getScaleSize(240) + ui->penPanel->getTransparentBorder(),
                               PublicFunction::getScaleSize(254) + ui->penPanel->getTransparentBorder());
    ui->penPanel->resize();
    ui->penPanel->move(QPoint(ui->tool_mid->mGetActionCenterX(2),
                              ui->tool_mid->y() - PublicFunction::getScaleSize(12) - ui->penPanel->height()));
    ui->eraserPanel->setFixedSize(PublicFunction::getScaleSize(292) + ui->eraserPanel->getTransparentBorder(),
                               PublicFunction::getScaleSize(183) + ui->eraserPanel->getTransparentBorder());
    ui->eraserPanel->resize();
    ui->eraserPanel->move(QPoint(ui->tool_mid->mGetActionCenterX(3),
                                 ui->tool_mid->y() - PublicFunction::getScaleSize(12) - ui->eraserPanel->height()));
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->resize();
}

void MainWidget::initWidget()
{
    ui->horizontalLayoutWidget->hide();
    this->setLayout(ui->horizontalLayout);
    ui->penPanel->hide();
    ui->eraserPanel->hide();

    QColor textColor = QColor(102, 102, 102);
    QColor hoverColor = QColor(238, 238, 238);
    QColor checkedColor = QColor(20, 134, 250);
    ui->tool_mid->mAddAction(1, tr("选择"), QPixmap(":/images/xuanze_1@2x.png"),
                           textColor, hoverColor, true, checkedColor, QPixmap(":/images/xuanze2_1@2x.png"));
    ui->tool_mid->mAddAction(2, tr("笔"), QPixmap(":/images/bichu_1@2x.png"),
                           textColor, hoverColor, true, checkedColor, QPixmap(":/images/bichu2_1@2x.png"));
    ui->tool_mid->mAddAction(3, tr("擦除"), QPixmap(":/images/cachu_1@2x.png"),
                           textColor, hoverColor, true, checkedColor, QPixmap(":/images/cachu2_1@2x.png"));
    ui->tool_mid->mAddAction(4, tr("撤销"), QPixmap(":/images/chexiao_1@2x.png"),
                           textColor, hoverColor, false);
    ui->tool_mid->mAddAction(5, tr("恢复"), QPixmap(":/images/huifu_1@2x.png"),
                           textColor, hoverColor, false);
    ui->tool_mid->mSetExclusive(true);
    ui->tool_mid->raise();

    //hoverColor = QColor(238, 238, 238, 130);
    ui->tool_left->mAddAction(1, QString(), QPixmap(":/images/Putaway@2x.png"), QColor(), hoverColor);
    ui->tool_left->mAddAction(2, QString(), QPixmap(":/images/down@2x.png"), QColor(), hoverColor, false);
    ui->tool_left->mAddAction(3, QString(), QPixmap(":/images/jpg_1@2x.png"), QColor(), hoverColor, false);
    ui->tool_left->raise();

    ui->tool_right->raise();

    connect(ui->tool_mid, &CustomToolBar_1::actionToggled, this, &MainWidget::onToolMidActionToggled);
    connect(ui->tool_mid, &CustomToolBar_1::actionClicked, this, &MainWidget::onToolMidActionClicked);
    connect(ui->tool_mid, &CustomToolBar_1::actionCheckedClicked, this, &MainWidget::onToolMidActionCheckedClicked);
    connect(ui->tool_right, &TabTools_1::addPageClicked, [=](){ ui->graphicsView->createScene(); });
    connect(ui->tool_right, &TabTools_1::currentItemChanged, [=](int index){ ui->graphicsView->selectScene(index); });
    connect(ui->tool_left, &CustomToolBar_1::actionClicked, this, &MainWidget::onToolLeftActionClicked);
    connect(ui->graphicsView, &BoardView::newSceneCreated, this, &MainWidget::onNewSceneCreated);
    connect(ui->graphicsView, &BoardView::mouseClicked, [=](){ this->hidePanel(); });
    connect(ui->graphicsView, &BoardView::itemChanged, this, &MainWidget::onSceneChanged);
    connect(ui->penPanel, &PenPanel::panelHide, this, [=](){
        ui->tool_mid->mSetActionCheckedIcon(2, QPixmap(":/images/bichu2_1@2x.png"));});
    connect(ui->penPanel, &PenPanel::panelShow, this, [=](){
        ui->tool_mid->mSetActionCheckedIcon(2, QPixmap(":/images/bichu3_1@2x.png"));});
    connect(ui->eraserPanel, &EraserPanel::panelHide, this, [=](){
        ui->tool_mid->mSetActionCheckedIcon(3, QPixmap(":/images/xuanze2_1@2x.png"));});
    connect(ui->eraserPanel, &EraserPanel::panelShow, this, [=](){
        ui->tool_mid->mSetActionCheckedIcon(3, QPixmap(":/images/xuanze3_1@2x.png"));});
    connect(ui->eraserPanel, &EraserPanel::clearAction, [=](){ ui->graphicsView->clearScene(); });
    connect(ui->tool_right,&TabTools_1::hasDelete,this,&MainWidget::deleteScene);
}

void MainWidget::exportFile()
{
    QFileDialog fileDialog;
    fileDialog.setWindowModality(Qt::WindowModal);
    QString dirName = fileDialog.getExistingDirectory(this, tr("选择文件夹"), "/");
    if (dirName.length() == 0)
        return;

    QDateTime dateTime = QDateTime::currentDateTime();
    dirName = QString("%1/安道白板图片导出-%2").arg(dirName).arg(dateTime.date().toString("yyyyMMdd"));
    QDir dir;
    dir.setPath(dirName);
    int i = 1;
    while(dir.exists()) {
        dir.setPath(QString("%1 (%2)").arg(dirName).arg(i));
        i++;
    }
    if (dir.mkdir(dir.path())) {
        ExportFileWidget *exportWidget = new ExportFileWidget(ui->graphicsView, dir.path(), this);
        exportWidget->setGeometry(this->rect());
        exportWidget->show();
    }
    return;
}

void MainWidget::insertPicture()
{
    QFileDialog fileDialog;
    fileDialog.setWindowModality(Qt::WindowModal);
    QString filter;
    QString fileName = fileDialog.getOpenFileName(this, tr("插入图片"), "", "PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)", &filter);
    if (fileName.length() == 0)
        return;

    if (filter.compare("PNG(*.png)") == 0) {
        ui->graphicsView->loadPicture(fileName);
    }else if (filter.compare("JPG(*.jpg)") == 0){
        ui->graphicsView->loadPicture(fileName);
    }else if (filter.compare("BMP(*.bmp)") == 0){
        ui->graphicsView->loadPicture(fileName);
    }
}

void MainWidget::onNewSceneCreated()
{
    int index = ui->graphicsView->getCurrentSceneIndex();
    QPixmap pixmap;
    ui->graphicsView->getScenePixmap(index, &pixmap);
    ui->tool_right->insertItem(ui->graphicsView->getCurrentSceneIndex(), pixmap);
    ui->tool_right->setItemChecked(index);
}

void MainWidget::onToolMidActionClicked(int id)
{
    if (4 == id)
        ui->graphicsView->undo();
    else if (5 == id)
        ui->graphicsView->redo();
}

void MainWidget::onToolMidActionCheckedClicked(int id)
{
    if (1 == id) {

    }else if (2 == id) {
        if (ui->penPanel->isHidden()) {
            this->hidePanel(ui->penPanel);
            ui->penPanel->show();
        }else
            ui->penPanel->hide();
    }else if (3 == id) {
        if (ui->eraserPanel->isHidden()) {
            this->hidePanel(ui->eraserPanel);
            ui->eraserPanel->show();
        }else
            ui->eraserPanel->hide();
    }
}

void MainWidget::onToolMidActionToggled(int id, bool checked)
{
    this->hidePanel();
    if (checked) {
        if (1 == id)
            ui->graphicsView->setViewTool(BoardView::VT_Select);
        else if (2 == id)
            ui->graphicsView->setViewTool(BoardView::VT_Draw);
        else if (3 == id)
            ui->graphicsView->setViewTool(BoardView::VT_Eraser);
    }
}

void MainWidget::onToolLeftActionClicked(int id)
{
    if (1 == id) {
        //emit this->hideWidget();
        this->close();
    }else if (2 == id) {
        this->exportFile();
    }else if (3 == id) {
        this->insertPicture();
    }
}

void MainWidget::hidePanel(QWidget *widget)
{
    if (widget != ui->penPanel && !ui->penPanel->isHidden())
        ui->penPanel->hide();
    if (widget != ui->eraserPanel && !ui->eraserPanel->isHidden())
        ui->eraserPanel->hide();
    ui->tool_right->hidePageListWidget();

}

void MainWidget::onSceneChanged()
{
    int index = ui->graphicsView->getCurrentSceneIndex();
    QPixmap pixmap;
    ui->graphicsView->getScenePixmap(index, &pixmap);
    ui->tool_right->changeItemPixmap(index, pixmap);
}
/**************change123****************/
void MainWidget::deleteScene(int index)
{
    if(ui->graphicsView->getScenesListSize() >1)
    {
        if(index == ui->graphicsView->getScenesListSize())
        {
            ui->graphicsView->deleteScene(index - 0);
            ui->graphicsView->selectScene(index -1);
        }
        else
        {
            ui->graphicsView->deleteScene(index - 0);
            ui->graphicsView->selectScene(index - 0);
        }
    }
    else
    {
        return;
    }
}


