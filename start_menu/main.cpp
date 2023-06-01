#include "controlwindow.h"
#include "set_help_acc_start.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlWindow w;
    w.showFullScreen();
    return a.exec();
}
