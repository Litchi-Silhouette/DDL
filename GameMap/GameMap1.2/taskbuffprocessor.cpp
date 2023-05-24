#include "utils.cpp"
#include "init.cpp"
#include "obstacle.cpp"


TaskBuffProcessor::TaskBuffProcessor(TaskBuff * _ptaskbuff, qint64 _process_time, int _type)
{
    type = _type;
    ptaskbuff = _ptaskbuff;
    process_time = _process_time;
}


bool TaskBuffProcessor::operator < (const TaskBuffProcessor & processor2) const{
    return process_time < processor2.process_time;
}
