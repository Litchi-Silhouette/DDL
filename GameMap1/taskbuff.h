#ifndef TASKBUFF_H
#define TASKBUFF_H

#include <QWidget>
#include <QTime>
#include <config.h>
#include <QString>
#include <QLabel>

namespace Ui {
class TaskBuff;
}

class GameMap;

class TaskBuff : public QLabel{
    Q_OBJECT
public:
    static int total_task,total_buff;
    int id;
    int x_id,y_id;
    bool activated;
    QString type;
    QString name;
    QString explanation;
    qint64 appear_time,disappear_time;
    GameMap * parent_gamemap;
    explicit TaskBuff(GameMap *parent, int _x_id, int _y_id, qint64 _appear_time = -1, qint64 _disappear_time = -1);
    ~TaskBuff();
    void embed_image(QString path);
    void set_explanation(QString _explanation);
    void set_name(QString _name);
    virtual void effect(){qDebug()<<name<<" effect called";};
    virtual void end_effect(){return;};
    void add_processor(qint64 delay_time, int _type = 0);

private:
    Ui::TaskBuff *ui;
};


class TaskHomework:public TaskBuff{
public:
    TaskHomework(GameMap *parent, int _x_id, int _y_id, QString subject_name = "高数", qint64 _appear_time = -1, qint64 _disappear_time = -1);
};

class BuffSleep:public TaskBuff{
public:
    qint64 sleep_time;
    BuffSleep(GameMap *parent, int _x_id, int _y_id, qint64 _sleep_time = 4000, qint64 _appear_time = -1, qint64 _disappear_time = -1);
    virtual void effect();
    virtual void end_effect();
};



#endif // TASKBUFF_H
