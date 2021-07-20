#pragma once
#include <QObject>

class ButtonController : public QObject
{
    Q_OBJECT
public:
    ButtonController();

// MOC: meta-object compiler
public slots:
    void start();
};
