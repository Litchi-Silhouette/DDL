#ifndef DDL_LIST_H
#define DDL_LIST_H

#include <QWidget>
#include <QListWidget>
#include "mylabel.h"
#include "Game.h"

class DDL_List : public QWidget
{
    Q_OBJECT
public:
    explicit DDL_List(const bool isThird, QWidget *parent = nullptr, QHash<int , QListWidgetItem*>* _all = nullptr,
                      QHash<QListWidgetItem*, task_info>* _task = nullptr, QHash<QListWidgetItem*, task_info>* _buff = nullptr);
    ~DDL_List();
    void set_ini_task(int fin = 0, int all = 0);
    void update_finish(const int);
    void add_task(const QPixmap&, const QString&, const QString&, const int, const bool = false);
    void add_buff(const QPixmap&, const QString&, const QString&, const int, const bool = false);
    void remove_task(const int index);
    void remove_buff(const int index);
    void showTask(const int index);
    void showBuff(const int index);
    void changeTaskColour(const int index, bool);
    void changeBuffColour(const int index, bool);
    void showIni();
    void banBuff(bool can){
        bufflist->setVisible(can);
    }
    void clear();
signals:
private slots:
    void task_click(QListWidgetItem *item);
    void buff_click(QListWidgetItem *item);

private:
    void set_info(QListWidgetItem*, bool is_buff = false, bool is_nor = true);
    void clearTaskSelected();
    void clearBuffSelected();

    QListWidget* tasklist;
    QListWidget* bufflist;
    MyLabel* titletask;
    MyLabel* titlebuff;
    MyLabel* finish;
    QLabel* name;
    QLabel* icon;
    QLabel* info;

    int finished = 0;
    int all_task = 0;

    QHash<QListWidgetItem*, task_info>* taskitems;
    QHash<QListWidgetItem*, task_info>* buffitems;
    QHash<int , QListWidgetItem*>* allitems;
};

#endif // DDL_LIST_H
