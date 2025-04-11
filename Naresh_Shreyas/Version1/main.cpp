#include <QApplication>
#include <QGraphicsScene>
#include "myrect.h"
#include "score.h"
#include <QGraphicsView>
#include <QTimer>
#include <QBrush>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene * scene = new QGraphicsScene();

    Score * score = new Score;
    scene->addItem(score);
    scene->setBackgroundBrush(QBrush(Qt::black));

    MyRect * player = new MyRect(score);
    player->setRect(-50,-400,100,100);
    player->setBrush(QBrush(Qt::white));

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

    QGraphicsView * view = new QGraphicsView(scene);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(800,800);
    view->setSceneRect(0,0,800,800);

    player->setPos(view->width()/2,view->height()-player->rect().height());

    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(1000);
    return a.exec();
}
