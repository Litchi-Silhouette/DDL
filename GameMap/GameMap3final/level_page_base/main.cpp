#include "levelwindow.h"
#include <QApplication>

Game statics;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelWindow w(statics, nullptr,3);
    w.showFullScreen();
    return a.exec();
}
