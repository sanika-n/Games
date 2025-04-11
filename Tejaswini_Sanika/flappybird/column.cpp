#include "column.h"
#include <QTimer>
#include <QGraphicsScene>

Column::Column(int height, int y) {
    setRect(0, 0, 50, height);  // Set the column width and height
    setBrush(Qt::green);
    setPos(700, y);  // Spawn column at the right edge

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(30);  // Column moves every 30 ms
}

void Column::move() {
    setPos(x() - 5, y());  // Move columns leftward

    if (x() + rect().width() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}

// Stop the column's movement when the game is over
void Column::stop() {
    timer->stop();  // Stop the timer to prevent further movement
}
