#include "contolwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ContolWindow w;
    w.show();
    return a.exec();
}
