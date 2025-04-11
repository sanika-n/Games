#include "enemy.h"
#include "myrect.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QPointF>
#include <cmath>
#include <QList>
#include <QGraphicsItem>
#include <QApplication>

Enemy::Enemy(QPointF playerpos, Score* gameScore) {
    int screen_height = 800;
    int screen_width = 800;
    int side = rand()%4;
    int rand_x, rand_y;
    if (side == 0) {
        rand_x = rand() % screen_width;
        rand_y = 0;
            }
    else if (side == 1) {
        rand_x = rand() % screen_width;
        rand_y = screen_height;
            }
    else if (side == 2) {
        rand_x = screen_width;
        rand_y = rand() % screen_height;
            }
    else {
        rand_x = 0;
        rand_y = rand() % screen_height;
            }
    setPos(rand_x, rand_y);
    setRect(0,0,50,50);
    setBrush(QBrush(Qt::blue));  // Fill the rectangle with red

    direction = playerpos - QPointF(rand_x,rand_y);
    direction /= sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    score = gameScore;

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Enemy::move()
{
    int speed = 4;
    setPos(x() + direction.x() * speed, y() + direction.y() * speed);

    if (pos().x() + rect().height()< 0) {
        scene()->removeItem(this);
        delete this;
    }
    else if (pos().x() + rect().height()> 800) {
        scene()->removeItem(this);
        delete this;
    }
    else if (pos().y() + rect().width()< 0) {
        scene()->removeItem(this);
        delete this;
    }
    else if (pos().y() + rect().width()> 800) {
        scene()->removeItem(this);
        delete this;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(MyRect)) {
            qDebug() << "Player Hit! Game Over.";
            qDebug() << "Final score: " << score->getscore();
            QApplication::quit();
        }
    }
}

