#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsEllipseItem>
#include <QObject>
#include "score.h"

class Bullet: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Bullet(qreal angle, Score* gameScore = nullptr);
public slots:
    void move();
private:
    qreal anglerad;
    Score* score;
};

#endif // BULLET_H
