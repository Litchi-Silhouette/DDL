#include "actwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ActWindow w(0);
    w.show();
    return a.exec();
}
