#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QKeyEvent> //To get key board inputs
#include <QTimer>   //so that the game screen can be refereshed at set time intervals

//Game is sub-class of QWidget: helps for it to act like a GUI element
//this gives it the ability to draw graphics, handle keyboard input
class Game : public QWidget
{
    Q_OBJECT //a macro that enables Qt's meta-object features like using signals and slots
public:
    Game(QWidget *parent = nullptr); //if no parent given it defaults to null ptr

protected:
    void paintEvent(QPaintEvent *event) override; //to over-ride virtual fns of base class properly
    void keyPressEvent(QKeyEvent *event) override;

private slots:
   void updateGame();
   /*Instead of using a while loop(ew>inefficent),
    * or a run function using QThread::msleep(not scalable and blocks other UI evnts)
    * Signal slots are the most effective way to do this in Qt
    */

private:
    QTimer *timer;
    QVector<QPoint> snake;
    QPoint food;
    int direction; // 0=Left, 1=Right, 2=Up, 3=Down

    int score = 0;
    bool gameOver = false;

    void move();
    void generateFood();
    bool checkCollision();
    void adjustSpeed();
};

#endif // GAME_H
