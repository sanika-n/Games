#include "bullet.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPointF>
#include <QtMath>
#include <QList>
#include <QBrush>

Bullet::Bullet(qreal angle, Score* gameScore) : score(gameScore) {
    setRect(0,0,5,5);
    setBrush(QBrush(Qt::red));
    anglerad = qDegreesToRadians(angle);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for (int i = 0, n = colliding_item.size(); i < n; ++i){
        if ((typeid (*(colliding_item[i]))) == typeid(Enemy)){
            scene()->removeItem(colliding_item[i]);
            scene()->removeItem(this);
            if (score) {
                score->increase();
            }
            delete colliding_item[i];
            delete this;
            return;
            }
    }
    qreal speed = 10.0;
    qreal dx = qSin(anglerad) * speed;
    qreal dy = -qCos(anglerad) * speed;

    setPos(x() + dx, y() + dy);
    // setPos(x(),y()-10);
    if (pos().y() + rect().height()< 0) {
        scene()->removeItem(this);
        delete this;
        }
}

