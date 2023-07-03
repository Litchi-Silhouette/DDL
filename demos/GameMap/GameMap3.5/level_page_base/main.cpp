#include "levelwindow.h"
#include <QApplication>

Game LevelWindow::statics;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelWindow w(nullptr,3);
    w.show();
    return a.exec();
}
