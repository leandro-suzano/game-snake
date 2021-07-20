#pragma once

#include <QObject>
#include <QFrame>
#include <QKeyEvent>

class Board: public QFrame
{
    Q_OBJECT

signals:
    void incrementScore();
    void resetScores();

public:
    Board(QFrame* parent = NULL);
    void paintEvent(QPaintEvent* event);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void addBodyPart();
    void move();
    void checkCollision();
    void checkCollisionWithBody();
    void checkCollisionWithWall();
    void reset();

private:
    QList<QRect> _body;
    QRect _apple;
    QRect _head;
    QRect _h;
    QImage _myImage;

    int _eated;

    char _direction;

};

