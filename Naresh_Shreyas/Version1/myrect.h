#ifndef MYRECT_H
#define MYRECT_H
#include <QGraphicsRectItem>
#include <QObject>
#include "score.h"

class MyRect : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    MyRect(Score* gameScore);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
private:
    Score* score;
};

#endif // MYRECT_H
