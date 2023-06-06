#include "init.cpp"


qint64 GameMapTwo::last_set_v_time = QDateTime::currentMSecsSinceEpoch();
double GameMapTwo::last_set_vx_player = 0.0;
double GameMapTwo::last_set_vy_player = 0.0;
double GameMapTwo::PLAYER_V_BUFF = 1.0;
double GameMapTwo::BOSS_V_BUFF = 1.0;


GameMapTwo::GameMapTwo(MainWindow *parent) :
    GameMap(parent,2)
{
    pboss = new Boss(this);
    pboss->show();

    x_player = (MainWindow::WIDTH - pfigure->width()) * 0.5;
    y_player = (MainWindow::MAP_HEIGHT - pfigure->height()) * 0.5;
    x_boss = y_boss = 10.0;
    vx_player = vy_player = vx_boss = vy_boss = 0.0;

    pboss->move(x_boss,y_boss);
    pfigure->move(x_player,y_player);

    live = 5;
    boss_live = -1;
    //UtilsStarter * starter = new UtilsStarter(this, START_DELAY_TIME);
}

GameMapTwo::~GameMapTwo(){}


void GameMapTwo::time_event(){
    static qint64 last_called_time = QDateTime::currentMSecsSinceEpoch();
    qint64 current_time = QDateTime::currentMSecsSinceEpoch();
    int delay_time = current_time - last_called_time;

    if(state != 1)return;

    if(paused){

        last_called_time = current_time;
        last_set_v_time += delay_time;

        for(auto tbprocessor = tbprocessors.begin();tbprocessor != tbprocessors.end();tbprocessor ++)
            const_cast<TaskBuffProcessor&>(*tbprocessor).delay_process(delay_time);
        time_event_tbprocessor();     //check TBporcessor
        return;
    }

    move_event();
    qDebug()<<current_time;
    if(delay_time < TIME_EVENT_INTERVAL)return;
    last_called_time = current_time;

    time_event_all_adjust_v();
    time_event_tbprocessor();     //check TBporcessor
    time_event_player_hit_taskbuff();    //check if player hit task
    time_event_all_taskbuff_twinkle();
    double distance = time_event_boss_hit_player();
    update_window_warning(distance);

    switch (time_event_judge_end_game()) {     //check end game
    case 1: //win
        end_game(true);break;
    case 2:  //lose
        end_game(false);break;
    default:
        break;
    }

}

void GameMapTwo::move_event(){

    if(paused)return;
    if(not pfigure->fixed){
        x_player += vx_player;
        y_player += vy_player;
    }
    if(not pboss->fixed){
        x_boss += vx_boss;
        y_boss += vy_boss;
    }

    if(x_player < 0){
        vx_player = - vx_player * 0.4;
        vy_player *= 0.5;
        x_player = 0;
        last_set_vx_player = vx_player;
    }
    else if(x_player + pfigure->size().width() > MainWindow::WIDTH){
        vx_player = - vx_player * 0.4;
        vy_player *= 0.5;
        x_player = MainWindow::WIDTH - pfigure->size().width();
        last_set_vx_player = vx_player;
    }
    if(y_player < 0){
        vy_player = - vy_player * 0.4;
        vx_player *= 0.5;
        y_player = 0;
        last_set_vy_player = vy_player;
    }else if(y_player + pfigure->size().height() > MainWindow::MAP_HEIGHT){
        vy_player = - vy_player * 0.4;
        vx_player *= 0.5;
        y_player = MainWindow::MAP_HEIGHT - pfigure->size().height();
        last_set_vy_player = vy_player;
    }
    pboss->move(x_boss,y_boss);
    pfigure->move(x_player,y_player);

}

void GameMapTwo::time_event_all_adjust_v(){
    qint64 current_time = QDateTime::currentMSecsSinceEpoch();

    set_v_boss(x_player - x_boss, y_player - y_boss);

    if(pfigure->fixed){
        vx_player = vy_player = 0;
        last_set_vx_player = last_set_vy_player = 0;
        return;
    }

    double rate = 1.0 - (current_time - last_set_v_time) / V_DACAY_TIME;
    rate = (rate > 0.0) ? rate : 0.0;
    vx_player = last_set_vx_player * rate;
    vy_player = last_set_vy_player * rate;

    double len = std::sqrt(vx_player * vx_player + vy_player * vy_player); 
    if(len < 0.2){vx_player = 0.0; vx_player = 0.0;}

}

int GameMapTwo::time_event_judge_end_game() // 0 not end 1 win 2 lose
{
    if(TaskBuff::finished_task + TaskBuff::missed_task >= TaskBuff::total_task)return 1;
    if(live <= 0)return 2;
    return 0;
}

void GameMapTwo::time_event_tbprocessor(){

    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    while(not tbprocessors.empty()){
        bool operation = false;
        auto tbprocessor = tbprocessors.begin();
        if(tbprocessor->process_time <= currentTime)
        {

            switch(tbprocessor->type)
            {
            case 0:
                tbprocessor->ptaskbuff->end_effect();
                remove_taskbuff(tbprocessor->ptaskbuff);
                break;
            case 1:
                tbprocessor->ptaskbuff->activated = true;
                tbprocessor->ptaskbuff->show();
                break;
            case 2:
                if(tbprocessor->ptaskbuff->activated)
                {
                    tbprocessor->ptaskbuff->activated = false;
                    remove_taskbuff(tbprocessor->ptaskbuff);
                    if(tbprocessor->ptaskbuff->type == "Task" || tbprocessor->ptaskbuff->type == "task")
                    {
                        TaskBuff::missed_task ++;
                        missed_task_drop_live(tbprocessor->ptaskbuff);
                    }
                }
                break;
            case 3:
                tbprocessor->ptaskbuff->twinkling = tbprocessor->ptaskbuff->activated;
                break;
            default:
                break;
            }
            operation = true;
            tbprocessors.erase(tbprocessors.begin());

        }
        if(not operation)break;
    }

}
void GameMapTwo::time_event_player_hit_taskbuff(){

    for(auto ptb: taskbuffs){
        if(ptb->activated &&
            calculate_distance(ptb,pfigure) < 0.7 * pfigure->size().width())
        {
            ptb->effect();
            ptb->activated = false;
            if(ptb->type == "Task" || ptb->type == "task"){
                TaskBuff::finished_task ++;
                update_window_ddl_list();
            }
            remove_taskbuff(ptb);
            break; //一次只会吃一个
        }
    }
}
void GameMapTwo::time_event_all_taskbuff_twinkle(){
    for(auto ptb: taskbuffs)
        ptb->twinkle();
    pfigure->twinkle();
}

double GameMapTwo::time_event_boss_hit_player(){
    static AutoBossStop * bossstop = nullptr;
    static UtilsFigureTwinkle * ufst = nullptr;
    if(pboss->fixed)return 1e10;

    double dis = calculate_distance(pboss,pfigure);
    if(dis > 0.8 * pfigure->size().width())
        return dis;

    if(bossstop != nullptr)delete bossstop;
    bossstop = new AutoBossStop(this, 2000);

    if(ufst != nullptr)delete ufst;
    ufst = new UtilsFigureTwinkle(this);
    return dis;
}



void GameMapTwo::create_all_taskbuff(){
    qDebug()<<"All taskbuff created";

    TaskBuff * hw1 = new TaskHomework(this,17,2,"高数",-1,12000);
    set_taskbuff(hw1);hw1->embed_image(":/images/images/task2.png");

    TaskBuff * hw2 = new TaskHomework(this,0,Y_GRID_NUM - 2.5,"微电子",1000,-1);
    set_taskbuff(hw2);

    TaskBuff * sleep = new BuffSleep(this,20,5,1000,5000,14000);
    sleep->set_explanation("原地停留1秒");
    set_taskbuff(sleep);

    TaskBuff * pre1 = new TaskAny(this,1,1.5,"膝盖pre","台上10分钟，台下人要疯",":/images/images/task1.png",13000);
    set_taskbuff(pre1);

    TaskBuff * hw3 = new TaskHomework(this,MainWindow::WIDTH / MainWindow::CELL_SIZE - 3,7,"概统",14000,24000);
    set_taskbuff(hw3);hw3->embed_image(":/images/images/task5.png");

    TaskBuff * pre2 = new TaskAny(this,MainWindow::WIDTH / MainWindow::CELL_SIZE * 0.5,0,"史纲pre","怎么做pre的又是我呜呜呜，以后不能再当大腿了",":/images/images/task1.png",16000,-1);
    set_taskbuff(pre2);pre2->embed_image(":/images/images/task2.png");

    TaskBuff * report = new TaskAny(this,3,Y_GRID_NUM - 4,"讲座感想","无所谓，我做了个好梦",":/images/images/task4.png",18000,-1);
    set_taskbuff(report);

    TaskBuff * timemanager = new BuffTimeManager(this,18,2.5,8000,20000,37000);
    set_taskbuff(timemanager);

    TaskBuff * hw4 = new TaskHomework(this,MainWindow::WIDTH / MainWindow::CELL_SIZE - 5,Y_GRID_NUM - 1.5,"线代",21000,-1);
    set_taskbuff(hw4);

    TaskBuff * sleep2 = new BuffSleep(this,0,3.5,1700,23000,-1);
    sleep2->set_name("玩原神");
    sleep2->set_explanation("三天没玩了，领个奖励总行吧(原地停留2秒)");
    sleep2->embed_image(":/images/images/special1.png");
    set_taskbuff(sleep2);

    TaskBuff * cure = new BuffCure(this,MainWindow::WIDTH / MainWindow::CELL_SIZE - 3,0,25000,43000);
    set_taskbuff(cure);

    TaskBuff * pe = new TaskAny(this,16,10,"体测","宅男的噩梦来喽",":/images/images/run.png",25000,32000);
    set_taskbuff(pe);

    TaskBuff * hw5 = new TaskHomework(this,0.5,0.5,"AI基础",28000,40000);
    hw5->set_explanation("选课不选AI基础...诶我好像说过一百遍了");
    hw5->embed_image(":/images/images/AIbasic.png");
    set_taskbuff(hw5);

    TaskBuff * hw6 = new TaskHomework(this,12,Y_GRID_NUM - 1.5,"还是线代",31000,46000);
    hw6->set_explanation("张量是什么？我只知道麻辣烫");
    set_taskbuff(hw6);hw6->embed_image(":/images/images/task2.png");

    TaskBuff * hw7 = new TaskHomework(this,MainWindow::WIDTH / MainWindow::CELL_SIZE - 1.2,2,"还是高数",32000,50000);
    hw7->set_explanation("总是学不会，只是觉得爱太美");
    set_taskbuff(hw7);hw7->embed_image(":/images/images/task4.png");

}


void GameMapTwo::set_taskbuff(TaskBuff * ptb){taskbuffs.push_back(ptb);}

void GameMapTwo::remove_taskbuff(TaskBuff * ptb){
    ptb->hide();
    for(auto iter = taskbuffs.begin(); iter != taskbuffs.end(); iter ++)
        if((*iter) == ptb){
            taskbuffs.erase(iter);
            qDebug()<<ptb->name<<" removed from task vector";
            break;
        }
}


void GameMapTwo::update_window_warning(const double & distance){
    double dis = distance / MainWindow::MAP_HEIGHT - 0.1;
    if(dis < 0.0)dis = 0.0;
    else if(dis > 1.0)dis = 1.0;
    parent_window->update_warning(dis);
}

void GameMapTwo::set_v_player(const int & x_relative,const int & y_relative)
{
    static double PLAYER_MAX_V_2_ = PLAYER_MAX_V_2 * MainWindow::CELL_SIZE;
    double len = calculate_distance(x_relative,y_relative);
    if(len < 10.0)return;
    if(QDateTime::currentMSecsSinceEpoch() - last_set_v_time < 500)return;
    vx_player = x_relative / len * PLAYER_MAX_V_2_ * PLAYER_V_BUFF;
    vy_player = y_relative / len * PLAYER_MAX_V_2_ * PLAYER_V_BUFF;
    last_set_v_time = QDateTime::currentMSecsSinceEpoch();
    last_set_vx_player = vx_player;
    last_set_vy_player = vy_player;

}

void GameMapTwo::set_v_boss(const double & x_relative,const double & y_relative)
{
    double len = calculate_distance(x_relative,y_relative);
    double v = (len / MainWindow::WIDTH * BOSS_MAX_V + BOSS_MIN_V) * MainWindow::CELL_SIZE;
    if(vx_boss < 0 && x_relative > 0)pboss->embed_image(pboss->path2);
    else if(vx_boss > 0 && x_relative < 0)pboss->embed_image(pboss->path1);
    vx_boss = x_relative / len * v * BOSS_V_BUFF;
    vy_boss = y_relative / len * v * BOSS_V_BUFF;
   // qDebug()<<vx_boss<<" "<<vy_boss;
}

void GameMapTwo::missed_task_drop_live(TaskBuff * ptb,const int & drop_live)
{
    ptb->missed_effect();
    live -= drop_live;
    if(live < 0)live = 0;
    parent_window->missed_task_drop_live(ptb,drop_live);
    update_window_ddl_list();
}
