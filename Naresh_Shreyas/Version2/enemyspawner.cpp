#include "enemyspawner.h"
//#include "gamemanager.h"

EnemySpawner::EnemySpawner(QGraphicsScene* gameScene, player* playerRect) {
    scene = gameScene;
    playerTarget = playerRect;

    spawnTimer = new QTimer(this);
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    spawnTimer->start(2000);
}

void EnemySpawner::spawnEnemy() {
    enemy* e = new enemy(playerTarget);
    scene->addItem(e);
}
