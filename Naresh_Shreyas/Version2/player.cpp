#include "player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "bullet.h"

void player::keyPressEvent(QKeyEvent * event) {
    if(event->key() == Qt:: Key_Left){
        setRotation(rotation() - 10);
    }
    else if(event->key() == Qt:: Key_Right){
        setRotation(rotation() + 10);
    }
    else if(event->key() == Qt:: Key_Space){
        bullet * b = new bullet(this);
        scene()->addItem(b);
    }
}
