#ifndef TASKBUFFINSTANCE_H
#define TASKBUFFINSTANCE_H

#include "taskbuff.h"

//以下是两个例子
//不同task/buff有不同效果，必须每个都继承一个类，大概率需要重载effect（），end_effect()，详见样例代码
class TaskHomework:public TaskBuff{
public:
    TaskHomework(GameMap *parent, int _x_id, int _y_id, QString subject_name = "高数", int _appear_time = -1, int _disappear_time = -1);
    virtual void effect();
};

class BuffSleep:public TaskBuff{
public:
    qint64 sleep_time;
    BuffSleep(GameMap *parent, int _x_id, int _y_id, int _sleep_time = 4000, int _appear_time = -1, int _disappear_time = -1);
    virtual void effect();
    virtual void end_effect();
};

class UtilsStarter:public TaskBuff{
public:
    UtilsStarter(GameMap *parent,int start_delay_time);
    virtual void end_effect();
};

#endif // TASKBUFFINSTANCE_H
