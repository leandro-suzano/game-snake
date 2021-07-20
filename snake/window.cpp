#include "window.h"
#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <iostream>
#include <QPainter>
#include <QtDebug>
#include <QKeyEvent>
#include "board.h"
#define tickMillisec 100
#define inicialAplles 0


Window::Window()
{
    const int lbl_Height = 30;
    _applesCounter = inicialAplles;

    //create new gameboard
    _gameboard = new Board();

    //creat restart button
    _button = new QPushButton(this);
    _button->setText("Restart");
    _button->setFocusPolicy(Qt::NoFocus);

    //create vertical box layout
    _layout = new QVBoxLayout(this);

    //create label to show the number of apples eaten
    _label = new QLabel(this);
    _label->setFixedHeight(lbl_Height);
    _label->setNum(inicialAplles);

    //add the button, gameboard and label to vertical box layout
    _layout->addWidget(_button);
    _layout->addWidget(_gameboard);
    _layout->addWidget(_label);

    //call the loop to repaint the gameboard
    tick();

    //connection between the button and his slot
    QObject::connect(_button, SIGNAL(clicked()),
                     this, SLOT(restart()));

    //connection between the signal from gameboard to increase
    //the number of eaten apples on the label
    QObject::connect(_gameboard, SIGNAL(incrementScore()),
                     this, SLOT(increaseScore()));

    //connection between the signal from gameboard to reset
    //the number of eaten apples on the label
    QObject::connect(_gameboard, SIGNAL(resetScores()),
                     this, SLOT(resetScore()));
};


Window::~Window()
{
    if(_gameboard != NULL)
        delete _gameboard;
}


//repaint the gameboard
void Window::tick()
{
    _gameboard->repaint();

    QTimer::singleShot(tickMillisec, this, SLOT(tick()));
}


//check if any arrow is pressed
void Window::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {

        case Qt::Key_Left:
            _gameboard->moveLeft();
            break;

        case Qt::Key_Right:
            _gameboard->moveRight();
            break;

        case Qt::Key_Up:
            _gameboard->moveUp();
            break;

        case Qt::Key_Down:
            _gameboard->moveDown();
            break;

        default:
            return;
    }
}


//restart the gameboard
void Window::restart()
{
    resetScore();
    _gameboard->reset();
}


//reset the number of eaten apples
void Window::resetScore()
{
    _label->setNum(inicialAplles);
    _applesCounter = inicialAplles;
}


//incremets the label when the snake eats the apple
void Window::increaseScore()
{
    _applesCounter++;
    _label->setNum(_applesCounter);
}



