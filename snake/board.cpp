#include "board.h"
#include "window.h"
#include <QPainter>
#include <QFrame>
#include <iostream>
#include <QKeyEvent>
#define appleXinicial 250
#define appleYinicial 150
#define snakeXinicial 25
#define snakeYinicial 25
#define SquareSize 10
#define movimentacionValue 10
#define margin 10
#define randomX (550 + 1)
#define randomY (270 + 1)

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Board::Board(QFrame* parent)
: QFrame(parent)
{
    _myImage.load(":/image/img/apple.jpg");

    reset();
}


void Board::reset()
{
    //resets the position of the snake and the apple
    _apple = QRect(appleXinicial, appleYinicial, SquareSize, SquareSize);
    _head = QRect(snakeXinicial, snakeYinicial, SquareSize, SquareSize);

    //clear the vector containing the snake parts and
    //add new head to create a new snake
    _body.clear();
    _body.push_back(_head);

    //initialize the snake direction
    _direction = Direction::RIGHT;

    //initialize the number of apples eated
    _eated = 0;

}


//change direction to left
void Board::moveLeft()
{
    if (_direction == Direction::RIGHT)
        return;

    _direction = Direction::LEFT;
}


//change direction to right
void Board::moveRight()
{
    if(_direction == Direction::LEFT)
        return;

    _direction  = Direction::RIGHT;
}


//change direction to up
void Board::moveUp()
{
    if(_direction == Direction::DOWN)
        return;

    _direction = Direction::UP;
}


//change direction to down
void Board::moveDown()
{
    if(_direction == Direction::UP)
        return;

    _direction = Direction::DOWN;
}



void Board::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);

    //paint a white background, and paint the apple and head snake
    painter.fillRect(0, 0, width(), height(), Qt::white);
    painter.drawImage(_apple, _myImage);
    painter.fillRect(_body[0], Qt::black);

    //paint the body snake
    for(int i = 1; i < _body.size(); i++)
    {
        painter.fillRect(_body[i], Qt::red);
    }

    move();
}


//move the snake
void Board::move()
{
    //check if there is any collision
    checkCollision();
    checkCollisionWithBody();
    checkCollisionWithWall();

    int prevx = _body[0].x();
    int prevy = _body[0].y();

    switch (_direction)
    {

        //move the head snake to right
        case Direction::RIGHT:
            _body[0].setX(_body[0].x() + movimentacionValue);
            _body[0].setY(_body[0].y());
            _body[0].setWidth(SquareSize);
            _body[0].setHeight(SquareSize);
            break;

        //move the head snake to left
        case Direction::LEFT:
            _body[0].setX(_body[0].x() - movimentacionValue);
            _body[0].setY(_body[0].y());
            _body[0].setWidth(SquareSize);
            _body[0].setHeight(SquareSize);
            break;

        //move the head snake to up
        case Direction::UP:
            _body[0].setX(_body[0].x());
            _body[0].setY(_body[0].y() - movimentacionValue);
            _body[0].setWidth(SquareSize);
            _body[0].setHeight(SquareSize);
            break;

        //move the head snake to down
        case Direction::DOWN:
            _body[0].setX(_body[0].x());
            _body[0].setY(_body[0].y() + movimentacionValue);
            _body[0].setWidth(SquareSize);
            _body[0].setHeight(SquareSize);
            break;

        default:
            return;
    }


    //move the snake body
    for(int i = 1; i < _body.size(); i++)
    {
        int currentx = _body[i].x();
        int currenty = _body[i].y();

        _body[i].setX(prevx);
        _body[i].setY(prevy);
        _body[i].setWidth(SquareSize);
        _body[i].setHeight(SquareSize);

        prevx = currentx;
        prevy = currenty;
    }
}


//add a new body part to the body snake
void Board::addBodyPart()
{
    QRect newPart(_apple.x(), _apple.y(), SquareSize, SquareSize);
    _body.push_back(newPart);
    _eated ++;
}



void Board::checkCollision()
{
    _h = QRect(_body[0].x(), _body[0].y(), SquareSize, SquareSize);

    //check if the the snake head colides with the apple
    if(_h.x() < _apple.x() + margin &&
            _h.x() + margin > _apple.x() &&
            _h.y() < _apple.y() + margin &&
            _h.y() + margin > _apple.y())
    {
        //generates a new position for the apple
        _apple.setX(rand() % randomX);
        _apple.setY(rand() % randomY);
        _apple.setWidth(SquareSize);
        _apple.setHeight(SquareSize);

        addBodyPart();

        //emits a signal to increment the number of eaten apples on the label
        emit incrementScore();
    }
}


//check if the head collides with the body
void Board::checkCollisionWithBody()
{
    if(_body.size() <=4 )
        return;

     for (int i = 1; i < _body.size() ; i++ )
     {
         if(_h.x() < _body[i].x() + margin &&
            _h.x() + margin > _body[i].x() &&
            _h.y() < _body[i].y() + margin &&
            _h.y() + margin > _body[i].y())
          {
                reset();
                //emit a signal to reset the number of eaten apples on the label
                emit resetScores();
          }
      }
}


//check if the head collides with the walls
void Board::checkCollisionWithWall()
{
    if(_h.x() < 0 || _h.x() > width() || _h.y() < 0 || _h.y() > height())
    {
        reset();
        //emit a signal to reset the number of eaten apples on the label
        emit resetScores();
    }
}

