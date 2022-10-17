#include "minwhiteboard.h"
#include "ui_minwhiteboard.h"
#include <QtDebug>

MinWhiteboard::MinWhiteboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinWhiteboard)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool ); //| Qt::WindowStaysOnTopHint
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
   // this->setWindowOpacity(0);

    this->initWidget();
}

MinWhiteboard::~MinWhiteboard()
{
    delete ui;
}

void MinWhiteboard::resizeWidget()
{
    this->setFixedSize(g_ScreenWidth, g_ScreenHeight);
    m_BoardView->setFixedSize(this->size());
}

void MinWhiteboard::setTool(MinWhiteBoard_View::ViewTool tool)
{
    m_BoardView->setTool(tool);
}

void MinWhiteboard::clearScene()
{
    m_BoardView->clearScene();
}

void MinWhiteboard::initWidget()
{
    ui->verticalLayoutWidget->hide();
    this->setLayout(ui->verticalLayout);

    m_BoardView = new MinWhiteBoard_View(this);
    m_BoardView->setStyleSheet(QString("background: transparent;"));
    ui->verticalLayout->addWidget(m_BoardView);
}
