#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "window.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    const int wnd_Width = 600;
    const int wnd_Height = 400;

    Window mainWindow;
    mainWindow.setFixedSize(wnd_Width, wnd_Height);

    mainWindow.show();
    return app.exec();

}
