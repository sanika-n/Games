#include "score.h"

Score::Score (QGraphicsItem *parent): QGraphicsTextItem(parent) {
    score = 0;
    setPlainText(QString("Score: ") + QString:: number(score));
}

void Score::increase() {
    score ++;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getscore() {
    return score;
}
