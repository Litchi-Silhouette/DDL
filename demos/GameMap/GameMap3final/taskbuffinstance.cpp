#include "init.cpp"
#include "obstacle.cpp"

QString random_generate_homework_explanation(QString subject_name);

TaskHomework::TaskHomework(GameMap *parent, double _x_id, double _y_id, QString subject_name, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Task";total_task ++;
    set_name(subject_name + "作业");set_explanation(random_generate_homework_explanation(subject_name));
    embed_image(":/images/images/task1.png");
}
void TaskHomework::effect(){
    set_name(name + "+1");
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}

TaskAny::TaskAny(GameMap *parent, double _x_id, double _y_id, QString _name, QString _explanation, QString _path, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Task";total_task ++;
    set_name(_name);set_explanation(_explanation);
    embed_image(_path);
}
void TaskAny::effect(){
    set_name(name + "+1");
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}




QString random_generate_homework_explanation(QString subject_name){
    int choice = rand() % 8;
    switch (choice) {
    case 0: return subject_name + QString("太难了www");break;
    case 1: return QString("也就花了区区3个小时");break;
    case 2: return subject_name + QString("太难了，还好有npy帮我");break;
    case 3: return QString("没人比我更懂")+subject_name+QString("!");break;
    case 4: return QString("I can do this all day!");break;
    case 5: return QString("也就花了区区10分钟");break;
    case 6: return QString("做到凌晨3点,早八又要翘了");break;
    case 7: return QString("听不听课没区别，反正不会做");break;
    default: break;
    }
    return QString("浪费生命,不如肝Qt大作业");
}


BuffSleep::BuffSleep(GameMap *parent, double _x_id, double _y_id, int _sleep_time, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++; sleep_time = _sleep_time;
    set_name("昏昏欲睡");set_explanation("原地停留4秒");
    embed_image(":/images/images/buff1.png");
}

void BuffSleep::effect(){
    parent_gamemap->pfigure->fixed = true;
    add_processor(sleep_time,0);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
    qDebug()<<"Sleep effect called";

}
void BuffSleep::end_effect(){
    parent_gamemap->pfigure->fixed = false;
    parent_gamemap->parent_window->remove_taskbuff(this);
    qDebug()<<"Sleep end effect called";
}

BuffTimeManager::BuffTimeManager(GameMap *parent, double _x_id, double _y_id, int _duration, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++; duration = _duration;
    set_name("时间管理大师");set_explanation("获得学长的时间管理秘笈，移动速度增加");
    embed_image(":/images/images/special1.png");
}

void BuffTimeManager::effect(){
    GameMapTwo::PLAYER_V_BUFF = 1.3;
    if(duration > 0)add_processor(duration,0);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
    qDebug()<<"TimeManage effect called";
}
void BuffTimeManager::end_effect(){
    GameMapTwo::PLAYER_V_BUFF = 1.0;
    parent_gamemap->parent_window->remove_taskbuff(this);
    qDebug()<<"TimeManage end effect called";
}

AutoBossStop::AutoBossStop(GameMap *parent,int stop_time):TaskBuff(parent){
    type = "Auto";
    total_buff ++;
    add_processor(stop_time,0);
    set_name("DDL追上了你");
    set_explanation("趁它得意，快跑！");
    missed = true; //show color red
    embed_image(":/images/images/warning1.png");
    qDebug()<<"BossStop effect called";
    parent_gamemap->pboss->fixed = true;
    parent_gamemap->missed_task_drop_live(this,1);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}
void AutoBossStop::end_effect(){
    parent_gamemap->pboss->fixed = false;
    parent_gamemap->parent_window->remove_taskbuff(this);
    qDebug()<<"BossStop end effect called";
}


UtilsBulletActivate::UtilsBulletActivate(GameMap *parent, Bullet * _pblt):
    TaskBuff(parent, -100, -100, -1, -1)
{
    type = "Utils"; hide();
    set_name("UtilsBulletActivate");
    pblt = _pblt;
}

UtilsFigureTwinkle::UtilsFigureTwinkle(GameMap *parent):
    TaskBuff(parent, -100, -100, -1, -1)
{
    type = "Utils"; hide();
    set_name("UtilsFigureStopTwinkle");
    parent_gamemap->pfigure->twinkling = true;
    add_processor(1000,0);
}
void UtilsFigureTwinkle::end_effect()
{
    parent_gamemap->pfigure->twinkling = false;
    parent_gamemap->pfigure->embed_image(parent_gamemap->pfigure->path1);
    parent_gamemap->pfigure->show();
}
