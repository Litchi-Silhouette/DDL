#include "figure.h"
#include "ui_figure.h"
#include "gamemap.h"
#include "ui_gamemap.h"
#include "taskbuff.h"
#include "ui_taskbuff.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "obstacle.cpp"
#include "utils.cpp"
#include <QString>
#include <QObject>



GameMap::GameMap(MainWindow  *parent) :
    QWidget((QWidget *)parent),
    taskbuffs(0),
    tbprocessors(),
    ui(new Ui::GameMap)
{
    ui->setupUi(this);
    parent_window = parent;
    pfigure = new Figure(this);

    ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &GameMap::time_event);
    ptimer->start(50);

    move(0,160);
    resize(1280,560);
}

GameMap::~GameMap()
{
    delete pfigure;
    delete ui;
}
bool GameMap::check_no_obstacle(const QPoint & pos){return false;}

GameMapOne::GameMapOne(MainWindow  *parent) :
    GameMap(parent)
{
    obstacles = new Obstacle ** [30+2];
    for(int i=0;i<30+2;i++){
        obstacles[i] = new Obstacle *[12+2];
        for(int j=0;j<12+2;j++){
            obstacles[i][j] = new Obstacle(0,this);
            obstacles[i][j]->move(i*CELL_SIZE,j*CELL_SIZE);
            if(i==0||j==0||i==31||j==13)obstacles[i][j]->set_state(1);
        }
    }
    //for test
    obstacles[3][5]->set_state(1); obstacles[3][6]->set_state(1); obstacles[3][7]->set_state(1);
    set_obstacle_rect(5,7,1,2);
    set_obstacle_rect(9,16,7,7);

    TaskBuff * hw1 = new TaskHomework(this,8,8,"概统",10000,20000);
    hw1->embed_image(":/images/images/task1.jpg");
    set_taskbuff(hw1);

    TaskBuff * sleep = new BuffSleep(this,20,5,4000,20000,40000);
    sleep->embed_image(":/images/images/buff1.jpg");
    set_taskbuff(sleep);

}

GameMapOne::~GameMapOne(){}

bool GameMapOne::check_no_obstacle(const QPoint & pos)
{
    int x_id = (pos.x() - X_BARRIER) / CELL_SIZE + 1;
    int y_id = (pos.y() - Y_BARRIER) / CELL_SIZE + 1;
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
           pfigure->pos().x()==ptb->x_id * CELL_SIZE &&
           pfigure->pos().y()==ptb->y_id * CELL_SIZE)
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

