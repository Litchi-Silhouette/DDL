#include "startwindow.h"
#include "loadwindow.h"
#include "menuwindow.h"
#include "set_pausedialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EndDialog p;p.exec();
    //MenuWindow w;
    //w.show();
    return a.exec();
}
