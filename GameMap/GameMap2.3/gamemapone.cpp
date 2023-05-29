#include "init.cpp"
#include "obstacle.cpp"
#include "ddlline.cpp"

GameMapOne::GameMapOne(MainWindow *parent) :
    GameMap(parent,1)
{
    create_all_obstacle();
    pline = new DDL_Line(this);
    pboss->hide();
    pfigure->move(MainWindow::CELL_SIZE * 4,MainWindow::CELL_SIZE * 4);

    slide_window_left_barrier = 0;
    live = 5;
    UtilsStarter * starter = new UtilsStarter(this, START_DELAY_TIME);
}

GameMapOne::~GameMapOne(){}
//set a rectangle range of cells to obstacle.Index start from 1, not 0.


void GameMapOne::time_event(){

    static qint64 last_called_time = QDateTime::currentMSecsSinceEpoch();

    if(paused){

        qint64 current_time = QDateTime::currentMSecsSinceEpoch();
        int delay_time = current_time - last_called_time;
        last_called_time = current_time;

        for(auto tbprocessor : tbprocessors)
            tbprocessor.delay_process(delay_time);
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
        parent_window->ptaskbuff_board->setText("WIN");break;
    case 2:  //lose
        parent_window->ptaskbuff_board->setText("LOSE");break;
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
            tbprocessors.erase(tbprocessors.begin());
            switch(tbprocessor->type)
            {
            case 0:
                tbprocessor->ptaskbuff->end_effect();
                remove_taskbuff(tbprocessor->ptaskbuff);break;
            case 1:
                tbprocessor->ptaskbuff->activated = true; tbprocessor->ptaskbuff->show(); break;
            case 2:
                tbprocessor->ptaskbuff->activated = false;
                remove_taskbuff(tbprocessor->ptaskbuff);break;
            default:
                break;
            }
            operation = true;
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
    pline->left_barrier += TIME_EVENT_INTERVAL * pline->speed_per_ms;
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

void GameMapOne::start_game(){
    paused = false;
    started = true;
    create_all_taskbuff();
    parent_window->reset();
    pfigure->raise();
    pline->raise();
}
void GameMapOne::create_all_taskbuff(){
    qDebug()<<"All taskbuff created";
    TaskBuff * hw1 = new TaskHomework(this,7,7,"概统",-1,-1);
    set_taskbuff(hw1);

    TaskBuff * hw2 = new TaskHomework(this,17,2,"高数",15000,-1);
    set_taskbuff(hw2);

    TaskBuff * sleep = new BuffSleep(this,20,5,4000,5000,-1);
    set_taskbuff(sleep);

}
void GameMapOne::create_all_obstacle(){
    obstacles = new Obstacle ** [X_GRID_NUM];

    for(int i=0;i<X_GRID_NUM;i++){
        obstacles[i] = new Obstacle *[Y_GRID_NUM];
        for(int j=0;j<Y_GRID_NUM;j++){
            obstacles[i][j] = new Obstacle(0,this);
            obstacles[i][j]->move(i*MainWindow::CELL_SIZE,j*MainWindow::CELL_SIZE);
            if(i==0||j==0||i==X_GRID_NUM-1||j==Y_GRID_NUM-1)obstacles[i][j]->set_state(1);
        }
    }
    obstacles[3][5]->set_state(1); obstacles[3][6]->set_state(1); obstacles[3][7]->set_state(1);
    set_obstacle_rect(5,6,1,3);set_obstacle_rect(1,1,4,4);
    set_obstacle_rect(9,16,7,7);
}
void GameMapOne::set_obstacle_rect(int xLow,int xHigh,int yLow,int yHigh)
{
    for(int x=xLow;x<=xHigh;x++)
        for(int y=yLow;y<=yHigh;y++)obstacles[x][y]->set_state(1);
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
        QPoint mappos = pos(); mappos.rx() -= MainWindow::MOVE_UNIT;
        if(mappos.rx() + size().width() < MainWindow::WIDTH)
            mappos.rx() = - size().width() + MainWindow::WIDTH;
        move(mappos);
        slide_window_left_barrier = - mappos.x() ;
    }
    else if(left_or_right == -1 &&
        x_figure <= 3 * MainWindow::CELL_SIZE)
    {
        QPoint mappos = pos(); mappos.rx() += MainWindow::MOVE_UNIT;
        if(mappos.rx() > 0)
            mappos.rx() = 0;
        move(mappos);
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
