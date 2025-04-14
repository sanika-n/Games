#include "bullet.h"
#include "player.h"
#include <QPointF>
#include <QtMath>
#include <QTimer>
#include <QGraphicsScene>

bullet::bullet(player * p) {
    player * player1;
    player1 = p;


    QRectF rect = player1->rect();
    QPointF topCenter(rect.center().x(), rect.top());
    QPointF sceneTopCenter = player1->mapToScene(topCenter);

    setRect(0, 0, 10, 10);
    setBrush(QBrush(Qt::yellow));
    setPos(sceneTopCenter); // place bullet

    setRotation(player1->rotation());

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}


void bullet::move() {
    // Calculate the direction based on the player's rotation when the bullet was created
    qreal angle = rotation(); // Get the rotation angle of the bullet (inherited from player)

    // Convert angle to radians and calculate x and y components
    qreal radians = qDegreesToRadians(angle - 90); // Adjust by 90 degrees since 0 is up

    // Calculate movement based on direction vector
    qreal dx = 10 * qCos(radians); // Speed of 10 pixels per move
    qreal dy = 10 * qSin(radians);

    // Update position
    setPos(x() + dx, y() + dy);

    // Remove bullet when it goes out of bounds
    if (pos().y() < 0 || pos().y() > scene()->height() ||
        pos().x() < 0 || pos().x() > scene()->width()) {
        scene()->removeItem(this);
        delete this;
    }
}

