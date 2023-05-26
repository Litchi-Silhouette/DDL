#include "levelwindow.h"
#include <QApplication>

Game LevelWindow::gamePages;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelWindow w(nullptr,1), p(nullptr, 2);
    w.gamePages.levels[1] = &p;
    p.gamePages.levels[2] = &w;
    w.show();
    return a.exec();
}
