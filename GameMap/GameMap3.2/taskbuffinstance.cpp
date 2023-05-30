#include "init.cpp"
#include "obstacle.cpp"

QString random_generate_homework_explanation(QString subject_name);

TaskHomework::TaskHomework(GameMap *parent, double _x_id, double _y_id, QString subject_name, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Task";total_task ++;
    set_name(subject_name + "作业");set_explanation(random_generate_homework_explanation(subject_name));
    embed_image(":/images/images/task1.jpg");
}
void TaskHomework::effect(){
    set_name(name + "+1");
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}
QString random_generate_homework_explanation(QString subject_name){
    int choice = rand() % 6;
    switch (choice) {
    case 0: return subject_name + QString("太难了，还是学不会");break;
    case 1: return QString("也就花了区区3个小时");break;
    case 2: return subject_name + QString("太难了，还好有npy帮我^_^");break;
    case 3: return QString("我爱")+subject_name+QString("!");break;
    case 4: return QString("I can do this all day!");break;
    case 5: return QString("也就花了区区10分钟");break;
    default: break;
    }
    return QString("浪费生命>_< 不如写Qt大作业");
}


BuffSleep::BuffSleep(GameMap *parent, double _x_id, double _y_id, int _sleep_time, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++; sleep_time = _sleep_time;
    set_name("昏昏欲睡");set_explanation("原地停留4秒");
    embed_image(":/images/images/buff1.jpg");
}

void BuffSleep::effect(){
    qDebug()<<"Sleep effect called";
    parent_gamemap->pfigure->fixed = true;
    add_processor(sleep_time,0);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);

}
void BuffSleep::end_effect(){
    qDebug()<<"Sleep end effect called";
    parent_gamemap->pfigure->fixed = false;
    parent_gamemap->parent_window->remove_taskbuff(this);
    qDebug()<<"Sleep end effect ended";
}

BuffTimeManager::BuffTimeManager(GameMap *parent, double _x_id, double _y_id, int _duration, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++; duration = _duration;
    set_name("时间管理大师");set_explanation("获得学长的时间管理秘笈，移动速度增加");
    embed_image(":/images/images/buff1.jpg");
}

void BuffTimeManager::effect(){
    qDebug()<<"TimeManage effect called";
    GameMapTwo::PLAYER_V_BUFF = 1.3;
    if(duration > 0)add_processor(duration,0);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}
void BuffTimeManager::end_effect(){
    qDebug()<<"TimeManage end effect called";
    GameMapTwo::PLAYER_V_BUFF = 1.0;
    parent_gamemap->parent_window->remove_taskbuff(this);
}


UtilsStarter::UtilsStarter(GameMap * parent, int start_delay_time):TaskBuff(parent){
    type = "Starter";
    total_buff ++;
    add_processor(start_delay_time,0);
    set_name("UtilsStarter");
}
void UtilsStarter::end_effect(){
    qDebug()<<"UtilsStarter end effect called";
    parent_gamemap->start_game();
    parent_gamemap->parent_window->remove_taskbuff(this);
}


AutoBossStop::AutoBossStop(GameMap *parent,int stop_time):TaskBuff(parent){
    type = "Auto";
    total_buff ++;
    add_processor(stop_time,0);
    set_name("DDL追上了你");
    set_explanation("趁它得意，快跑！");
    missed = true; //show color red
    embed_image(":/images/images/warning1.jpg");
    qDebug()<<"BossStop effect called";
    parent_gamemap->pboss->fixed = true;
    parent_gamemap->missed_task_drop_live(this,1);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}
void AutoBossStop::end_effect(){
    qDebug()<<"BossStop end effect called";
    parent_gamemap->pboss->fixed = false;
    parent_gamemap->parent_window->remove_taskbuff(this);
    qDebug()<<"BossStop end effect ended";
}

