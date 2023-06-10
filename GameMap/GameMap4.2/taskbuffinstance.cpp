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
    attack_to_boss = 10;
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
    set_name("睡懒觉");set_explanation("早八就是用来翘的嘛（原地停留4秒）");
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

BuffTired::BuffTired(GameMap *parent, double _x_id, double _y_id, int _tired_time, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++; tired_time = _tired_time;
    set_name("疲惫");set_explanation("好累呀，想摆烂...我走慢一点");
    embed_image(":/images/images/special1.png");
}
void BuffTired::effect(){
    GameMapOne::MIN_KEYEVENT_INTERVAL = 500;
    add_processor(tired_time,0);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
    qDebug()<<"Tired effect called";
}
void BuffTired::end_effect(){
    GameMapOne::MIN_KEYEVENT_INTERVAL = 120;
    parent_gamemap->parent_window->remove_taskbuff(this);
    qDebug()<<"Tired end effect called";
}

BuffSurprise::BuffSurprise(GameMap *parent, double _x_id, double _y_id,int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++;
    set_name("意外之喜");set_explanation("喜报！喜报！DDL延期了！！！（DDL减速）");
    embed_image(":/images/images/special1.png");
};
void BuffSurprise::effect(){
    GameMapOne::DDL_LINE_V_BUFF = 0.6;
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
    qDebug()<<"Surprise effect called";
}

BuffCure::BuffCure(GameMap *parent, double _x_id, double _y_id,int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++;
    if(parent_gamemap->level == 2){
        set_name("爸妈的投喂");set_explanation("送来一大箱水果呢（回复40血量）");
    }else{
        set_name("卷王护体！");set_explanation("伟大的卷王保佑我！！(回复40血量)");
    }

    embed_image(":/images/images/buff2.png");
};
void BuffCure::effect(){
    add_processor(5000,0);
    if(parent_gamemap->level == 2){
        parent_gamemap->live += 2;
        if(parent_gamemap->live > 5)parent_gamemap->live = 5;
    }else{
        parent_gamemap->live += 40;
        if(parent_gamemap->live > 100)parent_gamemap->live = 100;
    }
    parent_gamemap->parent_window->update_all_live();
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
    qDebug()<<"Cure effect called";
}
void BuffCure::end_effect(){
    parent_gamemap->parent_window->remove_taskbuff(this);
}

BuffGPT::BuffGPT(GameMap *parent, double _x_id, double _y_id,int _duration, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++;
    duration = _duration;
    set_name("ChatGPT");set_explanation("GPT祝我一臂之力！是时候展现真正的技术了！（免疫所有子弹）");
    embed_image(":/images/images/gpt.png");
};
void BuffGPT::effect(){
    add_processor(duration,0);
    Bullet::omitted = true;
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
    qDebug()<<"GPT effect called";
}
void BuffGPT::end_effect(){
    Bullet::omitted = false;
    parent_gamemap->parent_window->remove_taskbuff(this);
    qDebug()<<"GPT end_effect called";
}

BuffStayLate::BuffStayLate(GameMap *parent, double _x_id, double _y_id,int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++;
    set_name("熬夜");set_explanation("熬夜伤身体（你和DDL各扣10血量）");
    embed_image(":/images/images/special2.png");
};
void BuffStayLate::effect(){
    add_processor(5000,0);
    parent_gamemap->live -= 10;
    parent_gamemap->boss_live -= 10;
    if(parent_gamemap->live <= 0)parent_gamemap->live = 0;
    if(parent_gamemap->boss_live <= 0)parent_gamemap->boss_live = 0;
    parent_gamemap->parent_window->update_all_live();
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}
void BuffStayLate::end_effect(){
    parent_gamemap->parent_window->remove_taskbuff(this);
}



BuffTimeManager::BuffTimeManager(GameMap *parent, double _x_id, double _y_id, int _duration, int _appear_time, int _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++; duration = _duration;
    if(parent_gamemap->level == 2){
        set_name("时间管理大师");set_explanation("获得学长的时间管理秘笈，移动速度增加");
        embed_image(":/images/images/special1.png");
    }else{
        set_name("咖啡");set_explanation("续命神器，你值得拥有（提升速度和加速度）");
        embed_image(":/images/images/coffee.png");
    }

}

void BuffTimeManager::effect(){
    GameMapTwo::PLAYER_V_BUFF = 1.3;
    GameMapThree::PLAYER_V_BUFF = 1.3;
    GameMapThree::GRAVITY = 2.5;
    if(duration > 0)add_processor(duration,0);
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
    qDebug()<<"TimeManage effect called";
}
void BuffTimeManager::end_effect(){
    GameMapTwo::PLAYER_V_BUFF = 1.0;
    GameMapThree::PLAYER_V_BUFF = 1.0;
    GameMapThree::GRAVITY = 1.3;
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
