#include "init.cpp"


double GameMapThree::PLAYER_V_BUFF = 1.0;
double GameMapThree::GRAVITY = 1.7;
int GameMapThree::X_RIGHT_BARRIER = 0.0;


GameMapThree::GameMapThree(MainWindow *parent) :
    GameMap(parent,3)
{

    pboss = new Boss(this);
    pboss->show();

    x_player = MainWindow::CELL_SIZE;
    y_player = MainWindow::MAP_HEIGHT * 0.5 - pfigure->height() * 0.5;

    x_boss = MainWindow::WIDTH - pboss->width();
    y_boss = MainWindow::MAP_HEIGHT * 0.5 - pboss->height() * 0.5;


    vx_player = vy_player = vy_boss = 0.0;

    pboss->move(x_boss,y_boss);
    pfigure->move(x_player,y_player);

    live = 100;
    boss_live = 100;

    pwarningline = new QLabel(this);
    pwarningline->resize(MainWindow::MAP_HEIGHT * 0.0588,MainWindow::MAP_HEIGHT);
    pwarningline->move(x_boss - MainWindow::CELL_SIZE,0);
    QIcon icon(":/images/images/barrier1.jpg");
    pwarningline->setPixmap(icon.pixmap(pwarningline->size()));
    GameMapThree::X_RIGHT_BARRIER = x_boss - MainWindow::CELL_SIZE;
}

GameMapThree::~GameMapThree(){}

void GameMapThree::time_event(){

    static qint64 last_called_time = QDateTime::currentMSecsSinceEpoch();
    qint64 current_time = QDateTime::currentMSecsSinceEpoch();
    int delay_time = current_time - last_called_time;

    if(state != 1)return;
    if(paused){
        last_called_time = current_time;

        for(auto tbprocessor = tbprocessors.begin();tbprocessor != tbprocessors.end();tbprocessor ++)
            const_cast<TaskBuffProcessor&>(*tbprocessor).delay_process(delay_time);
        time_event_tbprocessor();
        return;
    }

    move_event();

    if(delay_time < TIME_EVENT_INTERVAL)return;
    last_called_time = current_time;

    time_event_all_adjust_v();
    time_event_tbprocessor();
    time_event_player_hit_taskbuff();
    time_event_bullet_hit_player();
    time_event_all_twinkle();
    time_event_boss_float();

    switch (time_event_judge_end_game()) {
    case 1: //win
        end_game(true);break;
    case 2:  //lose
        end_game(false);break;
    default:
        break;
    }

}

void GameMapThree::move_event(){
    if(paused)return;

    for(auto pblt : bullets)
        pblt->bullet_move();

    for(auto ptb : taskbuffs)
        ptb->taskbuff_move();

    y_boss += vy_boss;
    pboss->move(pboss->x(),y_boss);

    if(not pfigure->fixed){
        x_player += vx_player;
        y_player += vy_player;
    }

    if(x_player < 0){
        vx_player = - vx_player * 0.35;
        vy_player *= 0.4;
        x_player = 0;
    }
    else if(x_player + pfigure->width() > GameMapThree::X_RIGHT_BARRIER){
        vx_player = - vx_player * 0.35;
        vy_player *= 0.4;
        x_player = GameMapThree::X_RIGHT_BARRIER - pfigure->width();
    }
    if(y_player < 0){
        vy_player = - vy_player * 0.35;
        vx_player *= 0.4;
        y_player = 0;
    }else if(y_player + pfigure->height() > MainWindow::MAP_HEIGHT){
        vy_player = - vy_player * 0.35;
        vx_player *= 0.4;
        y_player = MainWindow::MAP_HEIGHT - pfigure->height();

    }

    pfigure->move(x_player,y_player);

}

double GameMapThree::calculate_acceleration(const double & len){
    return GRAVITY / (MainWindow::WIDTH * MainWindow::WIDTH) * (len * len + MainWindow::CELL_SIZE);
}

void GameMapThree::time_event_all_adjust_v(){
    static double PLAYER_MAX_V_3_ = PLAYER_MAX_V_3 * MainWindow::CELL_SIZE;
    for(auto pblt : bullets)
        pblt->bullet_adjust_v();

    for(auto ptb : taskbuffs)
        ptb->taskBuff_adjust_v();

    int x_relative = QCursor::pos().x() - this->pos().x() - x_player - 0.5 * pfigure->size().width();
    int y_relative = QCursor::pos().y() - this->pos().y() - y_player - 0.5 * pfigure->size().height();

    double len = calculate_distance(x_relative,y_relative);
    if(len < 50.0){
        vx_player *= 0.98;vy_player *= 0.98;
        if(calculate_distance(vx_player,vy_player) < 1.0)vx_player = vy_player = 0;
        return;
    }
    double a = calculate_acceleration(len);
    //qDebug()<<a;
    vx_player += x_relative / len * PLAYER_MAX_V_3_ * a * PLAYER_V_BUFF;
    vy_player += y_relative / len * PLAYER_MAX_V_3_ * a * PLAYER_V_BUFF;

    len = calculate_distance(vx_player,vy_player);
    if(len > PLAYER_MAX_V_3_){
        vx_player = vx_player * PLAYER_MAX_V_3_ / len * PLAYER_V_BUFF;
        vy_player = vy_player * PLAYER_MAX_V_3_ / len * PLAYER_V_BUFF;
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
                        missed_task_drop_live(tbprocessor->ptaskbuff,20);
                    }
                }
                break;
            case 3:
                tbprocessor->ptaskbuff->twinkling = tbprocessor->ptaskbuff->activated;
                break;
            case 4:
                tbprocessor->ptaskbuff->pblt->activated = true;
                tbprocessor->ptaskbuff->pblt->show();
                break;
            case 5:
                tbprocessor->ptaskbuff->pblt->activated = false;
                tbprocessor->ptaskbuff->pblt->hide();
                remove_bullet(tbprocessor->ptaskbuff->pblt);
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
            calculate_distance(ptb,pfigure) < pfigure->width())
        {
            ptb->effect();
            ptb->activated = false;
            if(ptb->type == "Task" || ptb->type == "task"){
                TaskBuff::finished_task ++;
                boss_live -= 10;
                parent_window->finish_task_hurt_boss(10);
                update_window_ddl_list();
            }
            remove_taskbuff(ptb);
            break; //一次只会吃一个
        }
    }
}

void GameMapThree::time_event_all_twinkle(){
    for(auto ptb: taskbuffs) ptb->twinkle();
    pfigure->twinkle();
}

void GameMapThree::time_event_bullet_hit_player(){

    for(auto pblt: bullets)
    {
        if(pblt->activated &&
            calculate_distance(pblt,pfigure) < pfigure->width())
        {
            hit_bullet_drop_life(pblt);
            pblt->activated = false;
            remove_bullet(pblt);
            break; //一次只会吃一个
        }
    }
}



void GameMapThree::create_all_taskbuff(){

    TaskBuff * hw1 = new TaskHomework(this,7,8,"概统",10000,35000);
    set_taskbuff(hw1);

    TaskBuff * hw2 = new TaskHomework(this,15,2,"高数",-1,23000);
    set_taskbuff(hw2);

    TaskBuff * hw3 = new TaskHomework(this,2,9,"英语",18000,32000);
    set_taskbuff(hw3);

    TaskBuff * hw4 = new TaskHomework(this,1,5.5,"AI基础",25000,39000);
    set_taskbuff(hw4);

    TaskBuff * sleep = new BuffSleep(this,2,0,1000,-1,15000);
    sleep->set_explanation("原地停留1秒");
    set_taskbuff(sleep);

    TaskBuff * timemanager = new BuffTimeManager(this,10,7.5,-1,-1,10000);
    set_taskbuff(timemanager);
    timemanager->set_v(1.0,1.0);

    qDebug()<<"All taskbuff created";
}

void GameMapThree::create_all_bullets(){
    Bullet * pblt1 = new Bullet(this,"Reflect",pboss,-1,22000);
    set_bullet(pblt1);

    Bullet * pblt12 = new Bullet(this,"Reflect",pboss,15000,40000);
    set_bullet(pblt12);

    Bullet * pblt13 = new Bullet(this,"Reflect",pboss,10000,25000);
    set_bullet(pblt13);

    Bullet * pblt2 = new Bullet(this,"Trace",pboss,8000,20000);
    set_bullet(pblt2);

    Bullet * pblt3 = new Bullet(this,"Missle",pboss,-1,10000);
    set_bullet(pblt3);

    Bullet * pblt4 = new Bullet(this,"Missle",pboss,10000,20000);
    set_bullet(pblt4);

    qDebug()<<"All bullets created";
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

void GameMapThree::set_bullet(Bullet * pblt){bullets.push_back(pblt);}
void GameMapThree::remove_bullet(Bullet * pblt){
    pblt->hide();
    for(auto iter = bullets.begin(); iter != bullets.end(); iter ++)
        if((*iter) == pblt){
            bullets.erase(iter);
            qDebug()<<"Bullet "<<pblt->type<<" "<<pblt->id<<" removed from bullet vector";
            break;
        }
}


void GameMapThree::time_event_boss_float(){
    static double top_barrier = MainWindow::CELL_SIZE;
    static double bottom_barrier = MainWindow::MAP_HEIGHT - pboss->height() - MainWindow::CELL_SIZE;

    if(y_boss < top_barrier){
        y_boss = top_barrier; vy_boss = - vy_boss;
    }else if(y_boss > bottom_barrier){
        y_boss = bottom_barrier; vy_boss = - vy_boss;
    }


    int k = rand() % 60;
    if(k == 0){
        vy_boss = - vy_boss * (80 + rand() % 50 )/100.0;
    }else if(k == 1){
        vy_boss = vy_boss * (80 + rand() % 50 )/100.0;
    }else if(k < 4){
        vy_boss = 0.0;
    }else if(vy_boss == 0 && k > 55){
        if(rand()%2 == 1)
            vy_boss = BOSS_FLOAT_V * MainWindow::CELL_SIZE;
        else
            vy_boss = - BOSS_FLOAT_V * MainWindow::CELL_SIZE;
    }

}

void GameMapThree::hit_bullet_drop_life(Bullet * pblt){
    live -= pblt->attack;
    if(live < 0)live = 0;
    UtilsFigureTwinkle * ufst = new UtilsFigureTwinkle(this);
    parent_window->hit_bullet_drop_life(pblt,pblt->attack);
}


void GameMapThree::missed_task_drop_live(TaskBuff * ptb,const int & drop_live)
{
    ptb->missed_effect();
    live -= drop_live;
    if(live < 0)live = 0;
    parent_window->missed_task_drop_live(ptb,drop_live);
    update_window_ddl_list();
}

void GameMapThree::start_game(){

    create_all_taskbuff();
    create_all_bullets();
    parent_window->reset();
    pfigure->raise();
    pboss->raise();
    paused = false;
    state = 1;
}

