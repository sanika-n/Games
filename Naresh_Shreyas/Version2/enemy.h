#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
//#include "gamemanager.h"

class player;

class enemy : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    enemy(player* target);

private:
    player* playerTarget;
    //GameManager* gameManager;

public slots:
    void move();
};

#endif // ENEMY_H
