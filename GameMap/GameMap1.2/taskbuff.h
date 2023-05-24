#ifndef TASKBUFF_H
#define TASKBUFF_H

#include <QWidget>
#include <QTime>
#include <config.h>
#include <QString>
#include <QLabel>



class GameMap;

class TaskBuff : public QLabel{
    Q_OBJECT
public:
    static int total_task,total_buff;
    int id; //start from 0; (when a taskbuff is created)id = total_task + total_buff
    int x_id,y_id;//在第几格，仅限第一关；后续代码一样，x_id表示格子数，x表示坐标
    bool activated;//是否被触发（是否显示，玩家是否吃到）
    QString type;//"task" or "buff"
    QString name;
    QString explanation;
    qint64 appear_time,disappear_time;
    GameMap * parent_gamemap;

    explicit TaskBuff(GameMap *parent, int _x_id, int _y_id, qint64 _appear_time = -1, qint64 _disappear_time = -1);
    ~TaskBuff();

    void embed_image(QString path);
    void set_explanation(QString _explanation);
    void set_name(QString _name);

    virtual void effect(){qDebug()<<name<<" effect called";return;};//触发效果
    virtual void end_effect(){return;};//延时结束效果
    void add_processor(qint64 delay_time, int _type = 0);


};

//以下是两个例子
//不同task/buff有不同效果，必须每个都继承一个类，大概率需要重载effect（），end_effect()，详见样例代码
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
