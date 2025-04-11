#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game(this);  // Initialize Game
    //by passing this: we are telling Game that its parent is MainWindow.
    setCentralWidget(game); // Set Game as main UI

    resize(400,500);
    connect(ui->resetButton, &QPushButton::clicked, game, &Game::resetGame);


}

MainWindow::~MainWindow()
{
    delete ui;
}
