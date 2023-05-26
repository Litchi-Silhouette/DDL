#include "init.cpp"
#include "obstacle.cpp"

QString random_generate_homework_explanation(QString subject_name);

TaskHomework::TaskHomework(GameMap *parent, int _x_id, int _y_id, QString subject_name, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Task";total_task ++;
    set_name(subject_name + "作业 +1");set_explanation(random_generate_homework_explanation(subject_name));
}
void TaskHomework::effect(){
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}
QString random_generate_homework_explanation(QString subject_name){
    int choice = rand() % 6;
    switch (choice) {
    case 0: return subject_name + QString("太难了，还是学不会");break;
    case 1: return QString("也就花了区区3个小时");break;
    case 2: return subject_name + QString("太难了，还好有npy帮我");break;
    case 3: return QString("我爱")+subject_name+QString("作业!");break;
    case 4: return QString("I can do this all day!");break;
    case 5: return QString("也就花了区区10分钟");break;
    default: break;
    }
    return QString("简直是浪费生命！不如写Qt大作业");
}


BuffSleep::BuffSleep(GameMap *parent, int _x_id, int _y_id, int _sleep_time, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++; sleep_time = _sleep_time;
    set_name("昏昏欲睡");set_explanation("原地停留4秒");
}

void BuffSleep::effect(){
    parent_gamemap->pfigure->fixed = true;
    add_processor(sleep_time);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}
void BuffSleep::end_effect(){
    parent_gamemap->pfigure->fixed = false;
    parent_gamemap->parent_window->remove_taskbuff(this);
}

UtilsStarter::UtilsStarter(GameMap * parent, int start_delay_time):TaskBuff(parent){
    type = "Starter";
    add_processor(start_delay_time,0);
    set_name("UtilsStarter");
}
void UtilsStarter::end_effect(){
    qDebug()<<"UtilsStarter end effect called";
    parent_gamemap->start_game();
    parent_gamemap->parent_window->remove_taskbuff(this);
}
