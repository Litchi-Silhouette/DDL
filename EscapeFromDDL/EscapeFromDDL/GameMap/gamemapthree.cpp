#include "init.cpp"


double GameMapThree::PLAYER_V_BUFF = 1.0;
double GameMapThree::GRAVITY = 1.7;
int GameMapThree::X_RIGHT_BARRIER = 0.0;
int GameMapThree::X_ID_WARNING_LINE = 0;


GameMapThree::GameMapThree(MainWindow *parent) :
    GameMap(parent,3)
{
    PLAYER_V_BUFF = 1.0;
    GRAVITY = 1.7;
    X_RIGHT_BARRIER = 0.0;
    X_ID_WARNING_LINE = 0;

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
    X_ID_WARNING_LINE = x_boss / MainWindow::CELL_SIZE - 1;
    pwarningline->move(x_boss - MainWindow::CELL_SIZE,0);
    QIcon icon(":/images/images/barrier1.jpg");
    pwarningline->setPixmap(icon.pixmap(pwarningline->size()));
    GameMapThree::X_RIGHT_BARRIER = x_boss - MainWindow::CELL_SIZE;

    pwhitecover = new QLabel(this);
    pwhitecover->setStyleSheet(QString("background-color:white"));
    pwhitecover->setGeometry(pwarningline->x(),0,MainWindow::HEIGHT,MainWindow::WIDTH);
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
        vx_player = - vx_player * 0.4;
        vy_player *= 0.45;
        x_player = 0;
    }
    else if(x_player + pfigure->width() > GameMapThree::X_RIGHT_BARRIER){
        vx_player = - vx_player * 0.4;
        vy_player *= 0.45;
        x_player = GameMapThree::X_RIGHT_BARRIER - pfigure->width();
    }
    if(y_player < 0){
        vy_player = - vy_player * 0.4;
        vx_player *= 0.45;
        y_player = 0;
    }else if(y_player + pfigure->height() > MainWindow::MAP_HEIGHT){
        vy_player = - vy_player * 0.4;
        vx_player *= 0.45;
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
            calculate_distance(ptb,pfigure) < 0.8 * pfigure->width())
        {
            ptb->effect();

            if(ptb->type == "Task" || ptb->type == "task"){
                parent_window->play_sound_effect(0);
                TaskBuff::finished_task ++;
                boss_live -= ptb->attack_to_boss;
                parent_window->finish_task_hurt_boss(ptb->attack_to_boss);
                update_window_ddl_list();
            }else{
                parent_window->play_sound_effect(1);
            }

            ptb->activated = false;
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
            parent_window->play_sound_effect(2);
            if(not Bullet::omitted)hit_bullet_drop_life(pblt);
            pblt->activated = false;
            remove_bullet(pblt);
            break; //一次只会吃一个
        }
    }
}



void GameMapThree::create_all_taskbuff(){

    TaskBuff * essay1 = new TaskAny(this,15,2,"膝盖论文","小意思，区区5000字",":/images/images/task4.png",-1,23300);
    set_taskbuff(essay1);//10

    TaskBuff * war = new TaskAny(this,7,8,"魔兽世界","这魔兽里面的lion怎么还会逃跑？我攻城狮可不能逃跑",":/images/images/task3.png",7000,-1);
    set_taskbuff(war);war->attack_to_boss = 15;

    TaskBuff * essay2 = new TaskAny(this,2,9,"通选课论文","差点都忘了有这门课了www",":/images/images/task2.png",16500,39000);
    set_taskbuff(essay2);essay2->attack_to_boss = 5;

    TaskBuff * hw1 = new TaskHomework(this,X_ID_WARNING_LINE / 2,Y_GRID_NUM / 2,"最后的高数",27400,53000);
    hw1->set_explanation("积积积，急急急");
    set_taskbuff(hw1);//40

    TaskBuff * sleep1 = new BuffSleep(this,2,0,3000,13000,36600);
    sleep1->set_explanation("都期末寄了还摆烂？（原地停留3秒）");
    set_taskbuff(sleep1);

    TaskBuff * coffee = new BuffTimeManager(this,10,7.5,8000,25100,40000);
    set_taskbuff(coffee);

    TaskBuff * cure1 = new BuffCure(this,X_ID_WARNING_LINE * 0.45,1,31100,47000);
    set_taskbuff(cure1);

    TaskBuff * pre1 = new TaskAny(this,X_ID_WARNING_LINE - 2.1,0.5,"体育pre","体育还有pre,想不到吧？不过在P大倒也正常",":/images/images/task4.png",30000,-1);
    set_taskbuff(pre1);pre1->attack_to_boss = 5;

    TaskBuff * staylate = new BuffStayLate(this,0.5,0.5,37300,56200);
    set_taskbuff(staylate);

    TaskBuff * affair = new TaskAny(this,X_ID_WARNING_LINE * 0.1,Y_GRID_NUM * 0.4,"社务总结","如果你也和我一样，对这学期社团工作感到满意，那么我觉得这件事情，泰裤辣！",":/images/images/task5.png",41000,53000);
    set_taskbuff(affair);affair->attack_to_boss = 5;

    TaskBuff * run = new TaskAny(this,X_ID_WARNING_LINE / 2,Y_GRID_NUM / 2,"85km","骑上我心爱的小摩托~~",":/images/images/85km.png",45000,59500);
    set_taskbuff(run);run->attack_to_boss = 5;

    TaskBuff * gpt = new BuffGPT(this,X_ID_WARNING_LINE * 0.2,Y_GRID_NUM - 6,7000,49000,-1);
    set_taskbuff(gpt);

    TaskBuff * essay3 = new TaskAny(this,0.5,Y_GRID_NUM - 2,"英语论文","加油！胜利在望",":/images/images/task4.png",52500,69000);
    set_taskbuff(essay3);

    TaskBuff * cure2 = new BuffCure(this,X_ID_WARNING_LINE * 0.25,Y_GRID_NUM - 2.7,57100,-1);
    set_taskbuff(cure2);

    TaskBuff * king = new TaskAny(this,4,3.5,"AI基础王者荣耀","鲁班七号，智商二百五！鲁班，鲁班，顶级鲁班！",":/images/images/AIbasic.png",61200,71000);
    set_taskbuff(king);king->attack_to_boss = 15;

    TaskBuff * hw2 = new TaskHomework(this,X_ID_WARNING_LINE - 3,Y_GRID_NUM - 2.2,"永远的线代",66500,74000);
    hw2->set_explanation("要跟线代说拜拜了，有点不舍呢~");
    set_taskbuff(hw2);

    TaskBuff * qt = new TaskAny(this,X_ID_WARNING_LINE * 0.7,Y_GRID_NUM / 2,"Qt大作业","给予DDL致命一击！",":/images/images/qt.png",75000,-1);
    qt->resize(MainWindow::CELL_SIZE * 1.5,MainWindow::CELL_SIZE * 1.5);
    qt->embed_image(":/images/images/qt.png");
    set_taskbuff(qt);qt->attack_to_boss = 100;



    coffee->set_v(1.0,1.0);
    sleep1->set_v(-1.0,2.0,1.6);
    hw1->set_v(4.0,1.0,1.9);
    qt->set_v(-10.0,13.0,5.0);
    run->set_v(1.0,-0.7);
    gpt->set_v(-0.3,1.0,0.6);
    essay3->set_v(0.7,1.8,2.7);
    hw2->set_v(0,1.0,3.0);
    cure2->set_v(3.2,-5.4,1.3);
    king->set_v(-1.0,-0.8);


    qDebug()<<"All taskbuff created";
}

void GameMapThree::create_all_bullets(){
    Bullet * pblt11 = new Bullet(this,"Reflect",pboss,-1,18500);
    set_bullet(pblt11);
    Bullet * pblt12 = new Bullet(this,"Reflect",pboss,16600,37500);
    set_bullet(pblt12);
    Bullet * pblt13 = new Bullet(this,"Reflect",pboss,11100,24700);
    set_bullet(pblt13);
    Bullet * pblt14 = new Bullet(this,"Reflect",pboss,22500,32600);
    set_bullet(pblt14);
    Bullet * pblt15 = new Bullet(this,"Reflect",pboss,27300,43000);
    set_bullet(pblt15);
    Bullet * pblt16 = new Bullet(this,"Reflect",pboss,32000,40300);
    set_bullet(pblt16);
    Bullet * pblt17 = new Bullet(this,"Reflect",pboss,40000,-1);
    set_bullet(pblt17);
    Bullet * pblt18 = new Bullet(this,"Reflect",pboss,43100,50200);
    set_bullet(pblt18);
    Bullet * pblt19 = new Bullet(this,"Reflect",pboss,49000,58200);
    set_bullet(pblt19);
    Bullet * pblt110 = new Bullet(this,"Reflect",pboss,56400,69800);
    set_bullet(pblt110);
    Bullet * pblt111 = new Bullet(this,"Reflect",pboss,62800,-1);
    set_bullet(pblt111);
    Bullet * pblt112 = new Bullet(this,"Reflect",pboss,69200,75200);
    set_bullet(pblt112);
    Bullet * pblt113 = new Bullet(this,"Reflect",pboss,73000,-1);
    set_bullet(pblt113);
    Bullet * pblt114 = new Bullet(this,"Reflect",pboss,53200,67300);
    set_bullet(pblt114);

    Bullet * pblt21 = new Bullet(this,"Trace",pboss,8100,20300);
    set_bullet(pblt21);
    Bullet * pblt22 = new Bullet(this,"Trace",pboss,26600,36400);
    set_bullet(pblt22);
    Bullet * pblt23 = new Bullet(this,"Trace",pboss,374000,48100);
    set_bullet(pblt23);
    Bullet * pblt24 = new Bullet(this,"Trace",pboss,49100,64200);
    set_bullet(pblt24);
    Bullet * pblt25 = new Bullet(this,"Trace",pboss,51700,67700);
    set_bullet(pblt25);
    Bullet * pblt26 = new Bullet(this,"Trace",pboss,58700,70000);
    set_bullet(pblt26);
    Bullet * pblt27 = new Bullet(this,"Trace",pboss,72500,-1);
    set_bullet(pblt27);

    Bullet * pblt31 = new Bullet(this,"Missle",pboss,4000,10000);
    set_bullet(pblt31);
    Bullet * pblt32 = new Bullet(this,"Missle",pboss,11000,20000);
    set_bullet(pblt32);
    Bullet * pblt33 = new Bullet(this,"Missle",pboss,32000,40000);
    set_bullet(pblt33);
    Bullet * pblt34 = new Bullet(this,"Missle",pboss,49000,20000);
    set_bullet(pblt34);
    Bullet * pblt35 = new Bullet(this,"Missle",pboss,615000,70000);
    set_bullet(pblt35);
    Bullet * pblt36 = new Bullet(this,"Missle",pboss,705000,79000);
    set_bullet(pblt36);

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
    static UtilsFigureTwinkle * ufst = nullptr;
    static qint64 last_called_time = -1;

    qint64 current_time = QDateTime::currentMSecsSinceEpoch();
    live -= pblt->attack;
    if(live < 0)live = 0;
    if(current_time - last_called_time > 1200){
        if(ufst != nullptr)delete ufst;
        ufst = new UtilsFigureTwinkle(this);
    }
    parent_window->hit_bullet_drop_life(pblt,pblt->attack);
    last_called_time = current_time;
}


void GameMapThree::missed_task_drop_live(TaskBuff * ptb,const int & drop_live)
{
    parent_window->play_sound_effect(3);
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
    pwhitecover->raise();
    pwarningline->raise();
    pfigure->raise();
    pboss->raise();
    paused = false;
    state = 1;
}

