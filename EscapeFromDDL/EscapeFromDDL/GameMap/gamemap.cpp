#include "init.cpp"
#include "obstacle.cpp"
#include "ddlline.cpp"



GameMap::GameMap(MainWindow  *parent, int _level) :
    QWidget((QWidget *)parent),
    taskbuffs(0),
    tbprocessors()
{
    TaskBuff::total_buff = TaskBuff::total_task = TaskBuff::finished_task = TaskBuff::missed_task = 0;
    level = _level;
    parent_window = parent;
    pfigure = new Figure(this);
    pboss = nullptr;

    ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &GameMap::time_event);
    if(level == 1){
        ptimer->start(TIME_EVENT_INTERVAL);
        resize(X_GRID_NUM *MainWindow::CELL_SIZE, MainWindow::MAP_HEIGHT);
    }
    else{
        ptimer->start(MOVE_EVENT_INTERVAL);
        resize(MainWindow::WIDTH, MainWindow::MAP_HEIGHT);
    }
    move(0,MainWindow::Y_TOOL_HEIGHT);
    paused = true;
    state = 0;
    live = 5;
    slide_window_left_barrier = 0;
    pending = new QLabel(this);
}

GameMap::~GameMap(){
    delete pfigure;
    delete ptimer;
    delete pboss;
    delete pending;
}

void GameMap::update_window_ddl_list(){parent_window->update_ddl_list();}

double GameMap::calculate_distance(QWidget * pa, QWidget * pb){
    int dx = pa->pos().x() - pb->pos().x() + pa->size().width() * 0.5 - pb->size().width() * 0.5;
    int dy = pa->pos().y() - pb->pos().y() + pa->size().height() * 0.5 - pb->size().height() * 0.5;
    return std::sqrt(dx * dx + dy * dy);
}


double GameMap::calculate_distance(const double & dx, const double & dy){
    return std::sqrt(dx * dx + dy * dy);
}

void GameMap::start_game(){

    create_all_taskbuff();
    create_all_bullets();
    create_all_obstacle();
    parent_window->reset();
    pfigure->raise();
    pboss->raise();
    paused = false;
    state = 1;
}

void GameMap::end_game(bool win){
    parent_window->changeGameProcess(true);
    pending->setGeometry(slide_window_left_barrier + MainWindow::WIDTH / 2 - MainWindow::CELL_SIZE * 7, MainWindow::MAP_HEIGHT / 3, MainWindow::CELL_SIZE * 14, MainWindow::CELL_SIZE * 4);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);setPalette(pa);
    QFont ft;
    ft.setPointSize(100.0 / 50.0 * MainWindow::CELL_SIZE);
    pending->setPalette(pa);
    pending->setFont(ft);
    pending->setContentsMargins(30.0 / 50.0 * MainWindow::CELL_SIZE,0,0,0);
    pending->setAlignment(Qt::AlignHCenter);
    pending->setAlignment(Qt::AlignVCenter);

    if(win){
        state = 4;
        parent_window->play_sound_effect(5);
        pending->setText("YOU WIN");
    }else{
        state = 3;
        parent_window->play_sound_effect(4);
        pending->setText("YOU LOSE");
    }
    pending->raise();
    pending->show();
    qDebug()<<"End Game called"<<(win ? "win":"lose");
    QTimer::singleShot(5000, parent_window, &MainWindow::endGame);
}
