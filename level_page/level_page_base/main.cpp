#include "levelwindow.h"
#include <QApplication>

QHash<QListWidgetItem*, task_info> DDL_List::taskitems;
QHash<QListWidgetItem*, task_info> DDL_List::buffitems;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelWindow w;
    w.show();
    return a.exec();
}
