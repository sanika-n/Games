#include <QApplication>
#include <QGraphicsScene>
#include "player.h"
#include <QGraphicsView>
#include "enemy.h"
#include <QTimer>
#include <QObject>
#include "enemyspawner.h"
#include <QGraphicsRectItem>
#include "Score.h"
//#include "gamemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene * scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 2000, 1000);
    scene->setBackgroundBrush(Qt::blue);

    player * rect = new player();
    rect->setRect(-5, -30, 10, 60);
    rect->setPos(1000, 500);
    rect->setBrush(QBrush(Qt::green));
    scene->addItem(rect);

    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();


    //GameManager* gm = new GameManager(scene);
    EnemySpawner* spawner = new EnemySpawner(scene, rect);

    Score* score = new Score();
    score->setPos(scene->width() - 500, 10); // Position it in the top-left corner with a small margin
    score->setZValue(2);
    scene->addItem(score);


    QGraphicsView * view = new QGraphicsView(scene);
    view->show();

    return a.exec();
}

