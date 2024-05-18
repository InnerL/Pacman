#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    escena = new QGraphicsScene;

    ui->setupUi(this);    
}

MainWindow::~MainWindow()
{
    delete ui;
    delete escena;
}
