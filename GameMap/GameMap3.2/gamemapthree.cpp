#include "init.cpp"


double GameMapThree::PLAYER_V_BUFF = 1.0;
double GameMapThree::GRAVITY = 0.22;
int GameMapThree::X_RIGHT_BARRIER = 0.0;


GameMapThree::GameMapThree(MainWindow *parent) :
    GameMap(parent,3)
{

    pfigure->resize(MainWindow::CELL_SIZE*2,MainWindow::CELL_SIZE*2);
    pboss = new Boss(this);
    pboss->show();

    //pmove_timer = new QTimer(this);
    //connect(pmove_timer, &QTimer::timeout, this, &GameMapThree::move_event);
    //pmove_timer->start(MOVE_EVENT_INTERVAL);

    x_player = MainWindow::WIDTH / 2;
    y_player = MainWindow::MAP_HEIGHT / 2;

    x_boss = MainWindow::WIDTH - pboss->width() - 10;
    y_boss = MainWindow::MAP_HEIGHT * 0.5 - pboss->height() * 0.5;
    GameMapThree::X_RIGHT_BARRIER = x_boss;

    vx_player = vy_player = 0.0;

    pboss->move(x_boss,y_boss);
    pfigure->move(x_player,y_player);

    live = 5;
    boss_live = 10;
    UtilsStarter * starter = new UtilsStarter(this, START_DELAY_TIME);
}

GameMapThree::~GameMapThree(){}

void GameMapThree::time_event(){
    static qint64 last_called_time = QDateTime::currentMSecsSinceEpoch();

    qint64 current_time = QDateTime::currentMSecsSinceEpoch();
    int delay_time = current_time - last_called_time;

    if(paused){
        last_called_time = current_time;

        for(auto tbprocessor : tbprocessors)
            tbprocessor.delay_process(delay_time);
        time_event_tbprocessor();     //check TBporcessor
        return;
    }

    move_event();
    time_event_all_adjust_v();

    if(delay_time < TIME_EVENT_INTERVAL)return;
    last_called_time = current_time;

    time_event_tbprocessor();     //check TBporcessor
    time_event_player_hit_taskbuff();    //check if player hit task
    time_event_all_taskbuff_twinkle();
    double distance = time_event_bullet_hit_player();
    update_window_warning(distance);

    switch (time_event_judge_end_game()) {     //check end game
    case 1: //win
        parent_window->ptaskbuff_board->setText("WIN");break;
    case 2:  //lose
        parent_window->ptaskbuff_board->setText("LOSE");break;
    default:
        break;
    }

}

void GameMapThree::move_event(){

    if(paused)return;
    if(not pfigure->fixed){
        x_player += vx_player;
        y_player += vy_player;
    }

    if(x_player < 0){
        vx_player = - vx_player * 0.4;
        vy_player *= 0.5;
        x_player = 0;
        qDebug()<<"left reflect";
    }
    else if(x_player + pfigure->size().width() > GameMapThree::X_RIGHT_BARRIER){
        vx_player = - vx_player * 0.4;
        vy_player *= 0.5;
        x_player = GameMapThree::X_RIGHT_BARRIER - pfigure->size().width();
        qDebug()<<"right reflect";
    }
    if(y_player < 0){
        vy_player = - vy_player * 0.4;
        vx_player *= 0.5;
        y_player = 0;
        qDebug()<<"top reflect";
    }else if(y_player + pfigure->size().height() > MainWindow::MAP_HEIGHT){
        vy_player = - vy_player * 0.4;
        vx_player *= 0.5;
        y_player = MainWindow::MAP_HEIGHT - pfigure->size().height();
        qDebug()<<"bottom reflect";
    }

    //pboss->move(x_boss,y_boss);
    pfigure->move(x_player,y_player);

}

double GameMapThree::calculate_acceleration(const int & x_relative,const int & y_relative, const double & len){
    return GRAVITY / (MainWindow::WIDTH * MainWindow::WIDTH) * (len * len);
}

void GameMapThree::time_event_all_adjust_v(){
   // QPoint relative_pos = QCursor::pos() - mapToGlobal(pfigure->pos());
    int x_relative = QCursor::pos().x() - this->pos().x() - x_player - 0.5 * pfigure->size().width();
    int y_relative = QCursor::pos().y() - this->pos().y() - y_player - 0.5 * pfigure->size().height();

    //qDebug()<<pfigure->size().width()<<" "<<pfigure->size().height();
    double len = calculate_distance(x_relative,y_relative);

    if(len < 50.0){
        vx_player *= 0.98;vy_player *= 0.98;
        if(calculate_distance(vx_player,vy_player) < 1.0)vx_player = vy_player = 0;
        return;
    }
    double a = calculate_acceleration(x_relative,y_relative,len);
    qDebug()<<a;
    vx_player += x_relative / len * PLAYER_MAX_V_3 * a * PLAYER_V_BUFF;
    vy_player += y_relative / len * PLAYER_MAX_V_3 * a * PLAYER_V_BUFF;

    len = calculate_distance(vx_player,vy_player);
    if(len > PLAYER_MAX_V_3){
        vx_player = vx_player * PLAYER_MAX_V_3 / len * PLAYER_V_BUFF;
        vy_player = vy_player * PLAYER_MAX_V_3 / len * PLAYER_V_BUFF;
    }

}

int GameMapThree::time_event_judge_end_game() // 0 not end 1 win 2 lose
{
    if(live <= 0)return 2;
    if(boss_live <= 0)return 1;
    return 0;
}

void GameMapThree::time_event_tbprocessor(){

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
void GameMapThree::time_event_player_hit_taskbuff(){

    for(auto ptb: taskbuffs){
        if(ptb->activated &&
            calculate_distance(ptb,pfigure) < 0.5 * pfigure->size().width())
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

void GameMapThree::time_event_all_taskbuff_twinkle(){
    for(auto ptb: taskbuffs) ptb->twinkle();
}

double GameMapThree::time_event_bullet_hit_player(){
    return 0.0;
}


void GameMapThree::start_game(){
    paused = false;
    started = true;
    create_all_taskbuff();
    parent_window->reset();
    pfigure->raise();
    pboss->raise();
}

void GameMapThree::create_all_taskbuff(){
    qDebug()<<"All taskbuff created";
    TaskBuff * hw1 = new TaskHomework(this,7,7,"概统",-1,30000);
    set_taskbuff(hw1);

    TaskBuff * hw2 = new TaskHomework(this,17,2,"高数",-1,20000);
    set_taskbuff(hw2);

    TaskBuff * sleep = new BuffSleep(this,20,5,1000,-1,10000);
    sleep->set_explanation("原地停留1秒");
    set_taskbuff(sleep);

    TaskBuff * timemanager = new BuffTimeManager(this,18,7.5,-1,-1,8000);
    set_taskbuff(timemanager);

}


void GameMapThree::set_taskbuff(TaskBuff * ptb){taskbuffs.push_back(ptb);}

void GameMapThree::remove_taskbuff(TaskBuff * ptb){
    ptb->hide();
    for(auto iter = taskbuffs.begin(); iter != taskbuffs.end(); iter ++)
        if((*iter) == ptb){
            taskbuffs.erase(iter);
            qDebug()<<ptb->name<<" removed from task vector";
            break;
        }
}


void GameMapThree::update_window_warning(const double & distance){
    double dis = distance / MainWindow::MAP_HEIGHT - 0.1;
    if(dis < 0.0)dis = 0.0;
    else if(dis > 1.0)dis = 1.0;
    parent_window->update_warning(dis);
}



void GameMapThree::missed_task_drop_live(TaskBuff * ptb,const int & drop_live)
{
    ptb->missed_effect();
    live -= drop_live;
    if(live < 0)live = 0;
    parent_window->missed_task_drop_live(ptb,drop_live);
    update_window_ddl_list();
}
