#include "levelwindow.h"
#include <QApplication>

QHash<QListWidgetItem*, QString> DDL_List::taskitems;
QHash<QListWidgetItem*, std::pair<QString,QString> > DDL_List::buffitems;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelWindow w;
    w.showFullScreen();
    return a.exec();
}
