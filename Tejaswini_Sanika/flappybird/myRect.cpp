#include "myRect.h"
#include <QDebug>
#include <QGraphicsScene>
#include "bullet.h"
void myRect::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        setPos(x()-10, y());
    }
    else if(event->key() == Qt::Key_Right){
        setPos(x()+10, y());
    }
    else if(event->key() == Qt::Key_Up){
        setPos(x(), y()-10);
    }
    else if(event->key() == Qt::Key_Down){
        setPos(x()-10, y()+10);
    }
    else if(event->key() == Qt::Key_Space){
        Bullet *bullet = new Bullet();
        bullet->setPos(x(), y());
        scene()->addItem(bullet);
    }
}
