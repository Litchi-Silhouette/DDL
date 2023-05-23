#include "levelwindow.h"
#include <QApplication>

QHash<QListWidgetItem*, task_info> DDL_List::taskitems;
QHash<QListWidgetItem*, task_info> DDL_List::buffitems;
QHash<int , QListWidgetItem*> DDL_List::all_items;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelWindow w(nullptr,1),p(nullptr,2);
    w.setMenu(&p);
    p.setMenu(&w);
    w.show();
    return a.exec();
}
