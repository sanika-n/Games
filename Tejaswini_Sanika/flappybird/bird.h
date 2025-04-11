#ifndef BIRD_H
#define BIRD_H

#include <QGraphicsRectItem>
#include <QObject>

class Bird : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    Bird();
    void keyPressEvent(QKeyEvent *event);
    bool isGameOver() const;  // Add this method

public slots:
    void move();

private:
    qreal velocity;
    bool gameOver;  // Track game over state
};

#endif // BIRD_H
