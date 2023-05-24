#include "utils.cpp"
#include "init.cpp"
#include "obstacle.cpp"


GameMap::GameMap(MainWindow  *parent) :
    QWidget((QWidget *)parent),
    taskbuffs(0),
    tbprocessors()
{
    parent_window = parent;
    pfigure = new Figure(this);

    ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &GameMap::time_event);
    ptimer->start(TIME_EVENT_INTERVAL); //

    resize(MainWindow::CELL_SIZE * X_GRID_NUM, MainWindow::CELL_SIZE * Y_GRID_NUM);
    move(0,MainWindow::Y_TOOL_HEIGHT);


}

GameMap::~GameMap(){
    delete pfigure; delete ptimer;
}
bool GameMap::check_no_obstacle(const QPoint &){return false;}

GameMapOne::GameMapOne(MainWindow  *parent) :
    GameMap(parent)
{
    obstacles = new Obstacle ** [X_GRID_NUM];
    for(int i=0;i<X_GRID_NUM;i++){
        obstacles[i] = new Obstacle *[Y_GRID_NUM];
        for(int j=0;j<Y_GRID_NUM;j++){
            obstacles[i][j] = new Obstacle(0,this);
            obstacles[i][j]->move(i*MainWindow::CELL_SIZE,j*MainWindow::CELL_SIZE);
            if(i==0||j==0||i==X_GRID_NUM-1||j==Y_GRID_NUM-1)obstacles[i][j]->set_state(1);
        }
    }
    //for test
    obstacles[3][5]->set_state(1); obstacles[3][6]->set_state(1); obstacles[3][7]->set_state(1);
    set_obstacle_rect(5,7,1,2);
    set_obstacle_rect(9,16,7,7);

    slide_window_left_barrier = 0;

    TaskBuff * hw1 = new TaskHomework(this,8,8,"概统",-1,20000);
    hw1->embed_image(":/images/images/task1.jpg");
    set_taskbuff(hw1);
    qDebug()<<hw1->pos()<<" "<<pos()<<" "<<MainWindow::CELL_SIZE;

    TaskBuff * sleep = new BuffSleep(this,20,5,4000,15000,40000);
    sleep->embed_image(":/images/images/buff1.jpg");
    set_taskbuff(sleep);

}

GameMapOne::~GameMapOne(){}

bool GameMapOne::check_no_obstacle(const QPoint & pos)
{
    int x_id = (pos.x() - MainWindow::X_BARRIER) / MainWindow::CELL_SIZE + 1;
    int y_id = (pos.y() - MainWindow::Y_BARRIER) / MainWindow::CELL_SIZE + 1;
    if(obstacles[x_id][y_id]->state != 0)return false;
    return true;
}

//set a rectangle range of cells to obstacle.Index start from 1, not 0.
void GameMapOne::set_obstacle_rect(int xLow,int xHigh,int yLow,int yHigh)
{
    for(int x=xLow;x<=xHigh;x++)
        for(int y=yLow;y<=yHigh;y++)obstacles[x][y]->set_state(1);
}
void GameMapOne::set_taskbuff(TaskBuff * ptb){taskbuffs.push_back(ptb);}
void GameMapOne::remove_taskbuff(TaskBuff * ptb){
    ptb->clear();
    for(auto iter = taskbuffs.begin(); iter < taskbuffs.end(); iter ++)
        if(*iter == ptb){taskbuffs.erase(iter);return;}
}


void GameMapOne::time_event(){
    //check if player hit task
    for(auto ptb: taskbuffs){
        if(ptb->activated &&
           pfigure->pos().x()==ptb->x_id * MainWindow::CELL_SIZE &&
           pfigure->pos().y()==ptb->y_id * MainWindow::CELL_SIZE)
        {
            ptb->effect();
            parent_window->renew_taskbuff_board(ptb);
            remove_taskbuff(ptb);
        }
    }
    //check TBporcessor
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    for(auto tbprocessor: tbprocessors){
        if(tbprocessor.process_time <= currentTime)
        {
            switch(tbprocessor.type){
                case 0:
                    tbprocessor.ptaskbuff->end_effect();break;
                case 1:
                    tbprocessor.ptaskbuff->activated = true; tbprocessor.ptaskbuff->show(); break;
                case 2:
                    tbprocessor.ptaskbuff->activated = false;
                    tbprocessor.ptaskbuff->parent_gamemap->remove_taskbuff(tbprocessor.ptaskbuff);break;
                default:
                    break;
            }
        }else break;
    }

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

