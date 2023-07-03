#include "init.cpp"
#include "obstacle.cpp"
#include "ddlline.cpp"

double GameMapOne::DDL_LINE_V_BUFF = 1.0;

GameMapOne::GameMapOne(MainWindow *parent) :
    GameMap(parent,1)
{
    create_all_obstacle();
    pline = new DDL_Line(this);
    pfigure->move(MainWindow::CELL_SIZE * 3,MainWindow::CELL_SIZE * 3);

    slide_window_left_barrier = 0;
    live = 5;
    boss_live = -1;

}

GameMapOne::~GameMapOne(){
    delete pline;
}
//set a rectangle range of cells to obstacle.Index start from 1, not 0.


void GameMapOne::time_event(){

    static qint64 last_called_time = QDateTime::currentMSecsSinceEpoch();

    if(state != 1)return;
    if(paused){

        qint64 current_time = QDateTime::currentMSecsSinceEpoch();
        int delay_time = current_time - last_called_time;
        last_called_time = current_time;

        for(auto tbprocessor = tbprocessors.begin();tbprocessor != tbprocessors.end();tbprocessor ++)
            const_cast<TaskBuffProcessor&>(*tbprocessor).delay_process(delay_time);
        time_event_tbprocessor();     //check TBporcessor
        return;
    }

    last_called_time = QDateTime::currentMSecsSinceEpoch();

    time_event_tbprocessor();     //check TBporcessor
    time_event_player_hit_taskbuff();    //check if player hit task
    double distance = time_event_move_ddlline();    //move deadline
    update_window_warning(distance);
    time_event_ddlline_eat_taskbuff();

    switch (time_event_judge_end_game()) {     //check end game
    case 1: //win
        end_game(true);break;
    case 2:  //lose
        end_game(false);break;
    default:
        break;
    }
}

int GameMapOne::time_event_judge_end_game() // 0 not end 1 win 2 lose
{
    if(pline->pos().rx() >= pfigure->pos().x())return 2;
    if(TaskBuff::finished_task + TaskBuff::missed_task >= TaskBuff::total_task)return 1;
    if(live <= 0)return 2;
    return 0;
}

void GameMapOne::time_event_tbprocessor(){

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

void GameMapOne::time_event_player_hit_taskbuff(){
    for(auto ptb: taskbuffs){
        if(ptb->activated &&
            pfigure->pos().x()==ptb->x_id * MainWindow::CELL_SIZE &&
            pfigure->pos().y()==ptb->y_id * MainWindow::CELL_SIZE)
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
double GameMapOne::time_event_move_ddlline(){

    QPoint ddlpos = pline->pos();

    pline->left_barrier += TIME_EVENT_INTERVAL * pline->speed_per_ms * DDL_LINE_V_BUFF;
    ddlpos.rx() = pline->left_barrier;
    pline->move(ddlpos);
    double dis = (pfigure->pos().x() - pline->left_barrier) / MainWindow::CELL_SIZE;
    dis = std::min(dis/40.0,1.0);
    return dis;
}
void GameMapOne::time_event_ddlline_eat_taskbuff(){
    static std::vector<TaskBuff *> to_be_removed(0);

    for(auto ptb: taskbuffs){
        if(ptb->pos().x() < pline->left_barrier){
            if(not ptb->activated) {return;}
            ptb->activated = false;
            to_be_removed.push_back(ptb);
        }
    }
    if(to_be_removed.size() == 0)return;
    for(auto ptb: to_be_removed){
        remove_taskbuff(ptb);
        if(ptb->type == "Task" || ptb->type == "task"){
            TaskBuff::missed_task ++;
            missed_task_drop_live(ptb,2);
        }
    }
    to_be_removed.clear();
}


void GameMapOne::create_all_taskbuff(){
    qDebug()<<"All taskbuff created";
    TaskBuff * hw1 = new TaskHomework(this,16,1,"概统",3000,-1);
    set_taskbuff(hw1);

    TaskBuff * hw2 = new TaskHomework(this,6,10,"线代",-1,-1);
    set_taskbuff(hw2);

    TaskBuff * hw3 = new TaskHomework(this,18,9,"高数",15000,-1);
    set_taskbuff(hw3);
    TaskBuff * hw32 = new TaskHomework(this,66,1,"高数",12000,-1);
    set_taskbuff(hw32);
    hw32->set_explanation("又是高数，想不到吧");

    TaskBuff * hw4 = new TaskHomework(this,50,6,"程设",-1,-1);
    set_taskbuff(hw4);
    hw4->set_explanation("郭神出的题怎么可能这么容易AC");

    TaskBuff * hw5 = new TaskHomework(this,48,2,"软科",-1,-1);
    set_taskbuff(hw5);
    hw4->set_explanation("软件是什么...我不会...");

    TaskAny * pre1 = new TaskAny(this,29,10,"英语pre","火星语根本不会怎么办呢",":/images/images/task1.png",26000,-1);
    set_taskbuff(pre1);

    TaskAny * imgrotation = new TaskAny(this,37,4,"图像旋转作业","很简单嘛^_^毫无难度",":/images/images/task1.png",32000,-1);
    set_taskbuff(imgrotation);

    TaskBuff * sleep = new BuffSleep(this,20,6,4000,5000,-1);
    set_taskbuff(sleep);

}

void GameMapOne::set_obstacle_rect(int xLow,int xHigh,int yLow,int yHigh)
{
    for(int x=xLow;x<=xHigh;x++)
        for(int y=yLow;y<=yHigh;y++)obstacles[x][y]->set_state(1,xLow);
}

void GameMapOne::set_obstacle_diag(int xStart, int yStart, int len, int xStride, int yStride){  // dir = -1 topright dir = 1 bottomright
    for(int i=0;i<len;i++) {
        if(xStart <= 0 || yStart <= 0 || xStart >= X_GRID_NUM || yStart >= Y_GRID_NUM)break;
        obstacles[xStart][yStart]->set_state(1,xStart);
        xStart += xStride;
        yStart += yStride;
    }
}

void GameMapOne::set_taskbuff(TaskBuff * ptb){taskbuffs.push_back(ptb);}
void GameMapOne::remove_taskbuff(TaskBuff * ptb){
    ptb->hide();
    for(auto iter = taskbuffs.begin(); iter != taskbuffs.end(); iter ++)
        if((*iter) == ptb){
            taskbuffs.erase(iter);
            qDebug()<<ptb->name<<" removed from task list";
            break;
        }
}


bool GameMapOne::check_no_obstacle(const QPoint & pos)
{
    int x_id = (pos.x() - MainWindow::X_BARRIER) / MainWindow::CELL_SIZE + 1;
    int y_id = (pos.y() - MainWindow::Y_BARRIER) / MainWindow::CELL_SIZE + 1;
    if(obstacles[x_id][y_id]->state != 0)return false;
    return true;
}

void GameMapOne::slide_window_event(int left_or_right){

    int x_figure = pfigure->pos().rx() - slide_window_left_barrier;
    if(left_or_right == 1 &&
        x_figure >= MainWindow::WIDTH - 4 * MainWindow::CELL_SIZE)
    {
        qDebug()<<"Slide window 1 called "<<pos();
        QPoint mappos = pos(); mappos.rx() -= MainWindow::MOVE_UNIT;
        qDebug()<<mappos;
        if(mappos.rx() + width() < MainWindow::WIDTH){
            qDebug()<<width()<<" "<<MainWindow::WIDTH;
            mappos.rx() = - width() + MainWindow::WIDTH;
        }

        move(mappos);
        qDebug()<<"after pos "<<pos()<<" "<<mappos;
        slide_window_left_barrier = - mappos.x() ;
    }
    else if(left_or_right == -1 &&
        x_figure <= 3 * MainWindow::CELL_SIZE)
    {
        qDebug()<<"Slide window -1 called "<<pos();
        QPoint mappos = pos(); mappos.rx() += MainWindow::MOVE_UNIT;
        qDebug()<<mappos;
        if(mappos.rx() > 0)
            mappos.rx() = 0;
        move(mappos);
        qDebug()<<"after pos "<<pos()<<" "<<mappos;
        slide_window_left_barrier = - mappos.x();
    }
}

void GameMapOne::missed_task_drop_live(TaskBuff * ptb,const int & drop_live)
{
    ptb->missed_effect();
    live -= drop_live;
    if(live < 0)live = 0;
    parent_window->missed_task_drop_live(ptb,drop_live);
    update_window_ddl_list();
}

void GameMapOne::update_window_warning(const double & distance){
    parent_window->update_warning(distance);
}

void GameMapOne::start_game(){

    create_all_taskbuff();
    create_all_obstacle();
    parent_window->reset();
    pfigure->raise();
    pline->raise();
    paused = false;
    state = 1;
}

void GameMapOne::create_all_obstacle(){
    obstacles = new Obstacle ** [X_GRID_NUM];

    for(int i=0;i<X_GRID_NUM;i++){
        obstacles[i] = new Obstacle *[Y_GRID_NUM];
        for(int j=0;j<Y_GRID_NUM;j++){
            obstacles[i][j] = new Obstacle(0,this);
            obstacles[i][j]->move(i*MainWindow::CELL_SIZE,j*MainWindow::CELL_SIZE);
            if(i==0||j==0||i==X_GRID_NUM-1||j==Y_GRID_NUM-1)obstacles[i][j]->set_state(1,i);
            //else obstacles[i][j]->setText(QString::number(i) + " " + QString::number(j));
        }
    }
    obstacles[3][5]->set_state(1,3); obstacles[3][6]->set_state(1,3); obstacles[3][7]->set_state(1,3);
    obstacles[6][5]->set_state(1,6);obstacles[21][9]->set_state(1,21);
    obstacles[12][5]->set_state(1,21);
    obstacles[17][4]->set_state(1,21);
    set_obstacle_rect(5,6,1,3);set_obstacle_rect(1,1,4,4);
    set_obstacle_rect(10,16,7,7);
    set_obstacle_rect(9,9,4,5);
    set_obstacle_rect(10,10,9,9);
    set_obstacle_rect(13,13,10,10);
    set_obstacle_rect(16,16,9,9);
    set_obstacle_rect(19,20,7,10);
    set_obstacle_rect(3,4,10,10);set_obstacle_rect(4,5,9,9);set_obstacle_rect(5,6,8,8);set_obstacle_rect(6,7,7,7);
    set_obstacle_diag(18,2,6,1,1);
    set_obstacle_diag(11,1,3,1,1);
    set_obstacle_diag(15,3,3,1,-1);
    set_obstacle_diag(24,3,4,1,1);
    set_obstacle_rect(21,22,10,10);
    set_obstacle_rect(27,28,1,2);
    set_obstacle_rect(32,39,5,6);
    set_obstacle_rect(35,36,2,9);
    set_obstacle_diag(41,2,10,0,2);
    set_obstacle_diag(43,1,10,0,2);
    set_obstacle_diag(32,1,2,1,1);
    set_obstacle_rect(26,30,9,9);
    obstacles[38][3]->set_state(1,38);
    obstacles[40][7]->set_state(1,40);
    obstacles[39][9]->set_state(1,39);
    obstacles[47][2]->set_state(1,47);
    set_obstacle_diag(46,9,7,1,-1);
    set_obstacle_diag(46,6,5,1,-1);
    set_obstacle_diag(49,9,5,1,-1);
    set_obstacle_diag(51,10,2,1,-1);
    obstacles[54][2]->set_state(1,54);
    obstacles[55][4]->set_state(1,55);
    obstacles[54][8]->set_state(1,54);
    obstacles[56][6]->set_state(1,56);
    obstacles[55][1]->set_state(1,55);
    obstacles[56][9]->set_state(1,56);
    obstacles[57][8]->set_state(1,56);
    obstacles[57][3]->set_state(1,55);
    obstacles[58][4]->set_state(1,54);
    obstacles[58][2]->set_state(1,56);
    obstacles[60][8]->set_state(1,55);
    obstacles[58][7]->set_state(1,56);
    obstacles[72][10]->set_state(1,72);
    obstacles[60][3]->set_state(1,72);
    obstacles[59][10]->set_state(1,72);
    obstacles[68][1]->set_state(1,72);
    obstacles[65][9]->set_state(1,72);
    set_obstacle_rect(61,61,1,7);
    set_obstacle_rect(63,63,3,10);
    set_obstacle_rect(65,65,1,7);
    set_obstacle_rect(65,72,5,5);
    set_obstacle_rect(67,67,7,10);
    set_obstacle_rect(68,70,9,9);
    set_obstacle_rect(69,72,7,7);
    set_obstacle_rect(74,74,2,9);
    set_obstacle_diag(67,4,3,2,0);
    set_obstacle_diag(67,2,3,2,0);
    set_obstacle_rect(76,76,1,2);
    set_obstacle_rect(76,76,5,6);
    set_obstacle_rect(76,76,9,10);
    obstacles[77][3]->set_state(1,72);
    obstacles[77][8]->set_state(1,72);
}
