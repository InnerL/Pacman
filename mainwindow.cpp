#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crea un widget central para el diseño
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Crea un diseño horizontal
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Crea el tablero de juego
    GameBoard *gameBoard = new GameBoard(this);
    mainLayout->addWidget(gameBoard);

    // Crea un diseño vertical para las palabras
    QVBoxLayout *rightLayout = new QVBoxLayout();
    QLabel *label1 = new QLabel("Score: 0", this);
    QLabel *label2 = new QLabel("Lives: 3", this);
    rightLayout->addWidget(label1);
    rightLayout->addWidget(label2);

    // Añade el diseño vertical al diseño principal
    mainLayout->addLayout(rightLayout);
}

MainWindow::~MainWindow() {
    delete ui;
}
