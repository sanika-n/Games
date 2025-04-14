#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "player.h"
#include "enemy.h"

class EnemySpawner : public QObject {
    Q_OBJECT
public:
    EnemySpawner(QGraphicsScene* gameScene, player* playerRect);

public slots:
    void spawnEnemy();

private:
    QTimer* spawnTimer;
    QGraphicsScene* scene;
    player* playerTarget;
    //GameManager* gameManager;
};

#endif // ENEMYSPAWNER_H

