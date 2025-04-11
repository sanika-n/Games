#include "game.h"
#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>

const int GRID_SIZE = 20;

Game::Game(QWidget *parent) : QWidget(parent), direction(1)
{

    setFocusPolicy(Qt::StrongFocus); //to detect keyboard clicks

    snake.append(QPoint(5, 5));
    generateFood();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    timer->start(150);
    // every 150 ms, a signal is sent out from timer and received by updateGame

    //reset button is created and kept it hidden till the game runs
    resetButton = new QPushButton("Reset", this);
    resetButton->setStyleSheet("background-color: #228B22; color: white; font-weight: bold; padding: 6px; border-radius: 5px;");
    resetButton->hide();

    // connect reset Button to resetGame function
    connect(resetButton, &QPushButton::clicked, this, &Game::resetGame);

}

void Game::generateFood()
{
    int gridWidth = width() / GRID_SIZE;
    int gridHeight = height() / GRID_SIZE;

    int x = QRandomGenerator::global()->bounded(gridWidth);
    int y = QRandomGenerator::global()->bounded(gridHeight);

    food = QPoint(x, y);
}


void Game::paintEvent(QPaintEvent *event)
{   QPainter painter(this);

    painter.fillRect(rect(), QColor(144, 238, 144)); // Light green

    if (gameOver)
    {
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 24, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
    }

    // Draw snake
    painter.setBrush(QColor(0, 100, 0));  // Dark Green
    painter.setPen(Qt::NoPen);
    for (const QPoint &point : snake)
    {   painter.drawRect(point.x() * GRID_SIZE, point.y() * GRID_SIZE, GRID_SIZE, GRID_SIZE);}

    //Draw Snake's Eyes (only on the head)
    QPoint head = snake.first();
    painter.setBrush(Qt::black);
    painter.drawEllipse(head.x() * GRID_SIZE + 4, head.y() * GRID_SIZE + 4, 5, 5);
    painter.drawEllipse(head.x() * GRID_SIZE + 12, head.y() * GRID_SIZE + 4, 5, 5);

    // Draw Food
    painter.setBrush(QColor(139, 0, 0));
    painter.setPen(QColor(139, 0, 0));
    painter.drawEllipse(food.x() * GRID_SIZE, food.y() * GRID_SIZE, GRID_SIZE, GRID_SIZE);

    //Draw score
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));
    painter.drawText(10, 20, QString("Score: %1").arg(score));
}

void Game::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:  if (direction != 1) direction = 0; break;
    case Qt::Key_Right: if (direction != 0) direction = 1; break;
    case Qt::Key_Up:    if (direction != 3) direction = 2; break;
    case Qt::Key_Down:  if (direction != 2) direction = 3; break;
    }
}

void Game::updateGame()
{
    QPoint head = snake.first();

    //rx and ry are references to x and y coordinates
    switch (direction)
    {
    case 0: head.rx()--; break;
    case 1: head.rx()++; break;
    case 2: head.ry()--; break;
    case 3: head.ry()++; break;
    }

    //wrap-around
    int gridWidth = width() / GRID_SIZE;
    int gridHeight = height() / GRID_SIZE;

    if (head.rx() < 0) head.setX(gridWidth - 1);
    if (head.ry() < 0) head.setY(gridHeight - 1);
    if (head.rx() >= gridWidth) head.setX(0);
    if (head.ry() >= gridHeight) head.setY(0);

    //check for collision
    if (snake.contains(head)) {
        gameOver = true;
        timer->stop();

        resetButton->show();  // The resetButton is visible when the game get over
        int btnWidth = resetButton->sizeHint().width();
        int btnHeight = resetButton->sizeHint().height();
        int centerX = (width() - btnWidth) / 2;
        int centerY = (height() + 50) / 2; // slightly below GAME OVER
        resetButton->move(centerX, centerY);
    }


    snake.prepend(head);

    //if it doesn't eat food, it doesn't grow
    if (head == food)
    {   generateFood();
        score += 10;
        adjustSpeed();
    }

    else
    {   snake.removeLast();}

    update(); //From QWidget
}


// Adjust speed when score increases
void Game::adjustSpeed()
{
    int newSpeed = 150 - (score / 100) * 10;  // Faster by 5ms per 100 points
    newSpeed = qMax(newSpeed, 50); // Minimum speed limit
    timer->setInterval(newSpeed);
}

//resetGame function implementation
void Game::resetGame()
{
    snake.clear();
    snake.append(QPoint(5, 5));
    direction = 1;
    score = 0;
    gameOver = false;
    generateFood();
    timer->start();
    resetButton->hide();
    update();
}

