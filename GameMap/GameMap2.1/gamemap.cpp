#include "init.cpp"
#include "obstacle.cpp"
#include "ddlline.cpp"



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
    paused = true;
    started = false;
    live = 5;

}

GameMap::~GameMap(){
    delete pfigure; delete ptimer;
}

void GameMap::update_window_ddl_list(){
    static bool initialized = false;
    if(not initialized)parent_window->resettask_(0,TaskBuff::total_task);
    else parent_window->update_finish_();
    initialized = true;
}
