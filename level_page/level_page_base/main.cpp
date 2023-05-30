#include "levelwindow.h"
#include <QApplication>

Game LevelWindow::gamePages;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelWindow w(nullptr,1), p(nullptr, 3);
    w.gamePages.levels[1] = &p;
    p.gamePages.levels[3] = &w;
    w.show();
    return a.exec();
}
