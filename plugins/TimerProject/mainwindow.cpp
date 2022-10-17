#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerinterface.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerinterface = new TimerInterface(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

