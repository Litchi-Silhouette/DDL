#include "startwindow.h"
#include "loadwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadWindow w;
    w.show();
    return a.exec();
}
