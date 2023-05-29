#include "init.cpp"
#include "obstacle.cpp"
#include "ddlline.cpp"



GameMap::GameMap(MainWindow  *parent, int _level) :
    QWidget((QWidget *)parent),
    taskbuffs(0),
    tbprocessors()
{
    level = _level;
    parent_window = parent;
    pfigure = new Figure(this);
    pboss = new Boss(this);

    ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &GameMap::time_event);
    ptimer->start(TIME_EVENT_INTERVAL);

    resize(MainWindow::CELL_SIZE * X_GRID_NUM, MainWindow::CELL_SIZE * Y_GRID_NUM);
    move(0,MainWindow::Y_TOOL_HEIGHT);
    paused = true;
    started = false;
    live = 5;
}

GameMap::~GameMap(){delete pfigure; delete ptimer;}

void GameMap::update_window_ddl_list(){parent_window->update_ddl_list();}

double GameMap::calculate_distance(QWidget * pa, QWidget * pb){
    int dx = pa->pos().x() - pb->pos().x() + pa->size().width() * 0.5 - pb->size().width() * 0.5;
    int dy = pa->pos().y() - pb->pos().y() + pa->size().height() * 0.5 - pb->size().height() * 0.5;
    return std::sqrt(dx * dx + dy * dy);
}


double GameMap::calculate_distance(const double & dx, const double & dy){
    return std::sqrt(dx * dx + dy * dy);
}
