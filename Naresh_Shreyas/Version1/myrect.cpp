#include "myrect.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QPointF>
#include <QtMath>
#include "bullet.h"
#include "enemy.h"
#include "score.h"

MyRect::MyRect(Score* gameScore) : score(gameScore) {}

void MyRect::keyPressEvent(QKeyEvent * event)
{
    setTransformOriginPoint(boundingRect().center());
    if (event->key() == Qt::Key_Left){
        setRotation(rotation() - 10);
    }
    else if (event->key() == Qt::Key_Right){
        setRotation(rotation() + 10);
    }
    else if (event->key() == Qt::Key_Space){

        qreal playerAngle = rotation();
        Bullet *bullet = new Bullet(playerAngle, score);
        QPointF center = mapToScene(boundingRect().center());
        QPointF topCenter(0, -boundingRect().height() / 2);
        QPointF bulletPos = QTransform().rotate(rotation()).map(topCenter) + center;
        bullet->setPos(bulletPos);
        scene()->addItem(bullet);
    }
}

void MyRect::spawn(){
    QPointF playerPos = mapToScene(boundingRect().center());
    Enemy * enemy = new Enemy(playerPos, score);
    scene()->addItem(enemy);
}


