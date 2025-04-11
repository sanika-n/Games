#include "bird.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include "column.h"

Bird::Bird() : gameOver(false) {
    setRect(0, 0, 20, 20);
    setBrush(Qt::yellow);

    velocity = 0;
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(30);
}

void Bird::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && !gameOver) {
        velocity = -8;
    }
}

void Bird::move() {
    if (gameOver) return;  // Stop movement if the game is over.

    velocity += 0.5;
    setPos(x(), y() + velocity);

    if (y() > 480) {
        setY(480);
        velocity = 0;

    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Column)) {
            velocity = 0;
            gameOver = true;  // Mark game as over when collision happens.

            QList<QGraphicsItem *> allItems = scene()->items();
            for (QGraphicsItem *item : allItems) {
                Column *col = dynamic_cast<Column *>(item);
                if (col) {
                    col->stop();  // Stop column movement.
                }
            }

            return;
        }
    }
}

bool Bird::isGameOver() const {
    return gameOver;
}
