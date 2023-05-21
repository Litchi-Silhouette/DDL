#ifndef DDL_LIST_H
#define DDL_LIST_H

#include <QWidget>
#include <QListWidget>
#include "mylabel.h"
#include <QHash>

class DDL_List : public QWidget
{
    Q_OBJECT
public:
    explicit DDL_List(QWidget *parent = nullptr);
    ~DDL_List();
    void set_ini_task(int fin = 0, int all = 0);
    void update_finish();
    void add_task(const QIcon, const QString, const QString);
    void add_buff(const QIcon, const QString, const QString);
    void remove_task(QListWidgetItem*);
    void remove_buff(QListWidgetItem*);
    void set_info(QListWidgetItem*, bool is_buff = false);
signals:
protected:
    void resizeEvent(QResizeEvent*);
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

    int icon_height = 0;
    int finished = 0;
    int all_task = 0;
    static QHash<QListWidgetItem*, QString> taskitems;
    static QHash<QListWidgetItem*, std::pair<QString,QString> > buffitems;
};

#endif // DDL_LIST_H
