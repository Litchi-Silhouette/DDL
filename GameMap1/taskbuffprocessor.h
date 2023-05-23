
#ifndef TASKBUFFPROCESSOR_H
#define TASKBUFFPROCESSOR_H
#include "taskbuff.h"
#include "ui_taskbuff.h"
#include <QDateTime>


class GameMap;

class TaskBuffProcessor
{
public:
    qint64 process_time;
    int type; // 0 effect 1 appear 2 disappear
    TaskBuff * ptaskbuff;
    TaskBuffProcessor(TaskBuff * _ptaskbuff = nullptr, qint64 _process_time = -1, int _type = 0);
    bool operator < (const TaskBuffProcessor & processor2) const;

};


#endif // TASKBUFFPROCESSOR_H
