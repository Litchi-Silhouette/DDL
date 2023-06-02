#include "start_menu/controlwindow.h"

#include <QApplication>
Game LevelWindow::statics;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlWindow w;
    w.showFullScreen();
    return a.exec();
}
