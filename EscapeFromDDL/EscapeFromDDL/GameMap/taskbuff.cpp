#include "init.cpp"
#include "obstacle.cpp"


int TaskBuff::total_buff = 0;
int TaskBuff::total_task = 0;
int TaskBuff::finished_task = 0;
int TaskBuff::missed_task = 0;

QString random_missed_explanation();

TaskBuff::TaskBuff(GameMap *parent, double _x_id, double _y_id, int _appear_time, int _disappear_time) :
    QLabel((QWidget *)parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);

    parent_gamemap = parent;
    pblt = nullptr;
    type = "Empty";
    img_path = "";
    id = total_buff + total_task;
    x_id = _x_id;
    y_id = _y_id;
    move(x_id * MainWindow::CELL_SIZE, y_id * MainWindow::CELL_SIZE);
    vx = vy = 0.0;
    movable = false;
    missed = false;
    twinkling = false;
    appear_time = _appear_time;
    disappear_time = _disappear_time;
    attack_to_boss = 5;
    switch(parent_gamemap->level)
    {
    case 1:
        resize(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);break;
    case 2:
        resize(MainWindow::CELL_SIZE * 1.3,MainWindow::CELL_SIZE * 1.3);break;
    case 3:
        resize(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);break;
    }


    activated = (appear_time <= 0);
    if(not activated){
        hide(); add_processor(appear_time, 1);
    }else{
        show();
    }
    if(disappear_time - appear_time > 4000){
        add_processor(disappear_time - 4000, 3);
        add_processor(disappear_time, 2);
    }


}

TaskBuff::~TaskBuff(){}

void TaskBuff::set_explanation(QString _explanation){explanation = _explanation;}
void TaskBuff::set_name(QString _name){name = _name;}

void TaskBuff::embed_image(QString path){
    QIcon icon(path);
    setPixmap(icon.pixmap(size()));
    img_path = path;
}

void TaskBuff::add_processor(int delay_time, int _type){
    TaskBuffProcessor tb(this, QDateTime::currentMSecsSinceEpoch() + delay_time, _type);
    parent_gamemap->tbprocessors.insert(tb);
}



void TaskBuff::missed_effect(){
    if(type != "Task" && type != "task") return;
    name = name + " 未完成";
    explanation = random_missed_explanation();
    missed = true;
    parent_gamemap->parent_window->add_taskbuff(this);
    parent_gamemap->parent_window->show_taskbuff(this);
}

void TaskBuff::twinkle(){
    if(activated and not isVisible()) show();
    else if(twinkling) hide();
}


QString random_missed_explanation(){
    int choice = rand() % 5;
    switch(choice){
    case 0: return QString("警惕！DDL快要将你吞噬！");break;
    case 1: return QString("你离绩点自由不远了！");break;
    case 2: return QString("只能求老师网开一面了...");break;
    case 3: return QString("退课来得及嘛？");break;
    default:break;
    }return QString("我的血量..疼..太疼了");
}

void TaskBuff::set_v(const double & x_dir, const double & y_dir, const double & v_buff){
    movable = true;
    double len = GameMap::calculate_distance(x_dir,y_dir);
    vx = x_dir / len * MainWindow::CELL_SIZE * TASKBUFF_BASE_V * v_buff;
    vy = y_dir / len * MainWindow::CELL_SIZE * TASKBUFF_BASE_V * v_buff;
}


void TaskBuff::taskbuff_move(){
    if(not movable)return;
    x_id += vx / MainWindow::CELL_SIZE;
    y_id += vy / MainWindow::CELL_SIZE;
    move(x_id * MainWindow::CELL_SIZE, y_id * MainWindow::CELL_SIZE);
}

void TaskBuff::taskBuff_adjust_v(){
    if(not movable)return;
    int x = x_id * MainWindow::CELL_SIZE;
    int y = y_id * MainWindow::CELL_SIZE;
    if(x < 0){
        vx = - vx;
        x_id = 0.0;
    }
    else if(x + width() > GameMapThree::X_RIGHT_BARRIER){
        vx = - vx;
        x_id = (GameMapThree::X_RIGHT_BARRIER - width()) / MainWindow::CELL_SIZE;
    }
    else if(y < 0){
        vy = - vy;
        y_id = 0.0;
    }
    else if(y + height() > MainWindow::MAP_HEIGHT){
        vy = - vy;
        y_id = (MainWindow::MAP_HEIGHT - height()) / MainWindow::CELL_SIZE;
    }

}

