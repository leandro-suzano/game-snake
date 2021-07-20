#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QFrame>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include "board.h"

class Window:public QWidget
{
    Q_OBJECT
public:
    Window();
    ~Window();
    void keyPressEvent(QKeyEvent *e);

// MOC: meta-object compiler
public slots:
    void tick();
    void restart();
    void increaseScore();
    void resetScore();


private:
    QLabel* _label;
    Board* _gameboard;
    QPushButton* _button;
    QVBoxLayout *_layout;
    int _applesCounter;


};
