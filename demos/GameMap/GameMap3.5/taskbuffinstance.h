#ifndef TASKBUFFINSTANCE_H
#define TASKBUFFINSTANCE_H

#include "taskbuff.h"

//以下是两个例子
//不同task/buff有不同效果，必须每个都继承一个类，大概率需要重载effect（），end_effect()，详见样例代码
class TaskHomework:public TaskBuff{
public:
    TaskHomework(GameMap *parent, double _x_id, double _y_id, QString subject_name = "高数", int _appear_time = -1, int _disappear_time = -1);
    virtual void effect();
};

class BuffSleep:public TaskBuff{
public:
    qint64 sleep_time;
    BuffSleep(GameMap *parent, double _x_id, double _y_id, int _sleep_time = 4000, int _appear_time = -1, int _disappear_time = -1);
    virtual void effect();
    virtual void end_effect();
};

class BuffTimeManager:public TaskBuff{
public:
    qint64 duration;
    BuffTimeManager(GameMap *parent, double _x_id, double _y_id, int _duration = 20000, int _appear_time = 10, int _disappear_time = -1);
    virtual void effect();
    virtual void end_effect();
};

class BuffMidTerm:public TaskBuff{
public:
    qint64 duration;
    BuffMidTerm(GameMap *parent, double _x_id, double _y_id, int _appear_time = 10, int _disappear_time = -1);
    virtual void effect();
    virtual void end_effect();
};

/*class UtilsStarter:public TaskBuff{
public:
    UtilsStarter(GameMap *parent,int start_delay_time);
    virtual void end_effect();
};*/

class AutoBossStop:public TaskBuff{
public:
    AutoBossStop(GameMap *parent,int stop_time = 1500);
    virtual void end_effect();
};

#endif // TASKBUFFINSTANCE_H
