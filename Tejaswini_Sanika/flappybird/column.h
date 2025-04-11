#ifndef COLUMN_H
#define COLUMN_H

#include <QGraphicsRectItem>
#include <QObject>

class Column : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    Column(int height, int y);

public slots:
    void move();
    void stop();  // Add this stop method to stop the movement.

private:
    QTimer *timer;
};

#endif // COLUMN_H
