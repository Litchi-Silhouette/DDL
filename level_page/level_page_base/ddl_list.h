#ifndef DDL_LIST_H
#define DDL_LIST_H

#include <QWidget>
#include <QListWidget>
#include "mylabel.h"
#include <QHash>

class task_info{
    QPixmap icon;
    QString info;
    QString name;
public:
    explicit task_info(const QPixmap& _icon = QPixmap(), const QString& _name = "", const QString& _info = "")
        :icon(_icon), info(_info), name(_name){}
    QPixmap& geticon(){
        return icon;
    }
    QString& getname(){
        return name;
    }
    QString& getinfo(){
        return info;
    }
};

class DDL_List : public QWidget
{
    Q_OBJECT
public:
    explicit DDL_List(QWidget *parent = nullptr);
    ~DDL_List();
    void set_ini_task(int fin = 0, int all = 0);
    void update_finish();
    void add_task(const QPixmap&, const QString&, const QString&);
    void add_buff(const QPixmap&, const QString&, const QString&);
    void remove_task(QListWidgetItem*);
    void remove_buff(QListWidgetItem*);
    void set_info(QListWidgetItem*, bool is_buff = false);
signals:
private slots:
    void task_click(QListWidgetItem *item);
    void buff_click(QListWidgetItem *item);

private:
    QListWidget* tasklist;
    QListWidget* bufflist;
    MyLabel* title;
    MyLabel* finish;
    MyLabel* name;
    QLabel* icon;
    QLabel* info;

    int finished = 0;
    int all_task = 0;
    static QHash<QListWidgetItem*, task_info> taskitems;
    static QHash<QListWidgetItem*, task_info> buffitems;
};

#endif // DDL_LIST_H
