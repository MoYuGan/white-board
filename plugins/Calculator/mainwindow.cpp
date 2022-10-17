#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
    calculator = new Calculator(this);

    this->centralWidget()->setStyleSheet("#centralwidget{background-color:none;}");

}

MainWindow::~MainWindow()
{
    delete ui;
}

