#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>
#include "player.h"

class bullet : public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:
    bullet(player * p);
public slots:
    void move();
};

#endif // BULLET_H
