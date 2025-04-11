#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPointF>
class Score;

class Enemy: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Enemy(QPointF playerpos, Score * gameScore );
public slots:
    void move();
private:
    QPointF direction;
    Score * score;
};

#endif // ENEMY_H
