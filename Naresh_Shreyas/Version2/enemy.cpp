#include "enemy.h"
#include "player.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QPointF>
#include <QtMath>
#include "bullet.h"
#include <QMessageBox>
#include <QApplication>
//#include "gamemanager.h"
#include "Score.h"
#include <QGraphicsPixmapItem>

enemy::enemy(player* target) {

    // Store player reference
    playerTarget = target;
    //gameManager = gm;

    // Set enemy appearance as a red rectangle
    QPixmap enemyPixmap("/home/shreyas-karthikeyan/Documents/game_try1/yash.jpg");
    setPixmap(enemyPixmap.scaled(100, 100));
    setZValue(1);

    // Determine spawn location on one of the edges
    int side = QRandomGenerator::global()->bounded(4); // 0: top, 1: right, 2: bottom, 3: left
    int x, y;

    // Screen boundaries as defined in your main.cpp
    int screenWidth = 2000;
    int screenHeight = 1000;

    if (side == 0) { // Top
        x = QRandomGenerator::global()->bounded(screenWidth);
        y = 0;
    } else if (side == 1) { // Right
        x = screenWidth;
        y = QRandomGenerator::global()->bounded(screenHeight);
    } else if (side == 2) { // Bottom
        x = QRandomGenerator::global()->bounded(screenWidth);
        y = screenHeight;
    } else if (side == 3) { // Left
        x = 0;
        y = QRandomGenerator::global()->bounded(screenHeight);
    }


    setPos(x, y);

    // Create timer to move the enemy
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void enemy::move() {

    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (QGraphicsItem* item : collidingItemsList) {
        if (dynamic_cast<bullet*>(item)) {

            QList<QGraphicsItem *> items = scene()->items();
            for (QGraphicsItem *i : items) {
                Score *score = dynamic_cast<Score *>(i);
                if (score) {
                    score->increase();
                    break;
                }
            }
            scene()->removeItem(item);
            delete item;

            scene()->removeItem(this);
            delete this;
            return;
        }

        if (dynamic_cast<player*>(item)) {
            QMessageBox::information(nullptr, "Game Over", "YOU WERE FIRED BY YASH!");
            QApplication::quit();
            return;
        }

    }

    if (!playerTarget || !scene()) {
        return;
    }

    // Calculate direction vector to player
    QPointF direction = playerTarget->pos() - pos();

    // Normalize the direction vector
    qreal length = qSqrt(direction.x() * direction.x() + direction.y() * direction.y());
    if (length > 0) {
        direction.rx() /= length;
        direction.ry() /= length;
    }

    // Move toward player with constant speed
    qreal speed = 10.0;
    setPos(x() + direction.x() * speed, y() + direction.y() * speed);
}
