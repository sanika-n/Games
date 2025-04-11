#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>
#include <QTimer>
#include "column.h"
#include "bird.h"
#include <QBrush>
#include <QColor>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    srand(time(NULL));
    scene->setBackgroundBrush(QBrush(QColor(71,182,213)));

    Bird *bird = new Bird();
    bird->setPos(10, 250);
    scene->addItem(bird);
    bird->setFlag(QGraphicsItem::ItemIsFocusable);
    bird->setFocus();

    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    view->setFixedSize(700, 500);
    scene->setSceneRect(0, 0, 700, 500);

    QTimer *spawnTimer = new QTimer();
    QObject::connect(spawnTimer, SIGNAL(timeout()), scene, SLOT(update()));

    QObject::connect(spawnTimer, &QTimer::timeout, [=]() {
        if (bird->isGameOver()) return;  // If game over, don't spawn new columns.

        int gap = 150;
        int minGapY = 100;
        int maxGapY = 400;
        int gapY = minGapY + rand() % (maxGapY - minGapY);

        Column *top = new Column(gapY, 0);
        Column *bottom = new Column(500 - gapY - gap, gapY + gap);

        scene->addItem(top);
        scene->addItem(bottom);
    });

    spawnTimer->start(2000); // Spawn every 2 seconds.

    return a.exec();
}

