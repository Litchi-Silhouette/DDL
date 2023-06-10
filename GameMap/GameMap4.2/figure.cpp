#include "init.cpp"
#include "obstacle.cpp"



class GameMap;

Figure::Figure(GameMap *parent) :
    QLabel((QWidget *)parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);
    parent_gamemap = parent;
    fixed = false;
    twinkling = false;
    switch(parent_gamemap->level)
    {
    case 1:
        resize(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);break;
    case 2:
        resize(MainWindow::CELL_SIZE * 1.3,MainWindow::CELL_SIZE * 1.3);break;
    case 3:
        resize(MainWindow::CELL_SIZE * 1.4,MainWindow::CELL_SIZE * 1.4);break;
    }

    path1 = path2 = ":/images/images/player_lion.png";
    embed_image(path1);
}

Figure::~Figure(){}

void Figure::embed_image(QString path){
    QIcon icon(path);
    setPixmap(icon.pixmap(size()));
}

void Figure::twinkle(){
    if(not twinkling)return;
    embed_image(":/images/images/player_lion_red.png");
    if(isVisible())hide();
    else show();
}

void Figure::move_in_grid(const QPoint & next_pos){

    if(not fixed &&
       next_pos.x() >= MainWindow::X_BARRIER &&
       next_pos.y() >= MainWindow::Y_BARRIER &&
       next_pos.x() + size().width() + MainWindow::X_BARRIER <= parent_gamemap->width() &&
       next_pos.y() + size().height() + MainWindow::Y_BARRIER <= parent_gamemap->height());
    else return;

    if(parent_gamemap->check_no_obstacle(next_pos)){

        if(next_pos.x() > pos().x()){
            move(next_pos);
            parent_gamemap->slide_window_event(1);
        }else if(next_pos.x() < pos().x()){
            move(next_pos);
            parent_gamemap->slide_window_event(-1);
        }else{
            move(next_pos);
        }
    }
}

Boss::Boss(GameMap *parent): Figure(parent)
{
    switch(parent_gamemap->level)
    {
    case 2:
        path1 = QString(":/images/images/boss1.png");
        path2 = QString(":/images/images/boss2.png");
        resize(MainWindow::CELL_SIZE * 2.5,MainWindow::CELL_SIZE * 2.5);
        embed_image(path2);break;
    case 3:
        path1 = QString(":/images/images/boss1.png");
        path2 = QString(":/images/images/boss3.png");
        resize(MainWindow::CELL_SIZE * 6,MainWindow::CELL_SIZE * 6);
        embed_image(path2);break;
    }
}

double Bullet::BULLET_V_BUFF = 1.0;
double Bullet::MISSLE_ACCELERATION = 1.5; // bigger than 1
int Bullet::total_bullet = 0;
bool Bullet::omitted = false;

std::random_device Bullet::rd;
std::mt19937 Bullet::gen(rd());
std::uniform_real_distribution<double> Bullet::distribution1(0.5, 1.5);
std::uniform_real_distribution<double> Bullet::distribution2(-1.0, 1.0);

Bullet::Bullet(GameMap *parent, QString _type, Boss * _pboss, int _appear_time, int _disappear_time):
    Figure(parent)
{
    total_bullet ++; id = total_bullet;
    type = _type;
    pboss = _pboss;
    v_buff = 1.0;
    attack = 10;
    entered_field = false;
    appear_time = _appear_time;
    disappear_time = _disappear_time;

    init_v_pos_img();
    move(x,y);

    path2 = "";
    embed_image(path1);

    activated = (appear_time <= 0);
    if(not activated){
        hide(); add_processor(appear_time, 4);
    }else{
        show();
    }
    if(disappear_time - appear_time > 1000){
        add_processor(disappear_time, 5);
    }
    qDebug()<<"Bullet id "<<id<<" created "<<pos();
}

auto sgn = [](double x){if(x>0)return 1.0;return -1.0;};

void Bullet::bullet_adjust_v()
{
    if(not activated)return;
    if(not entered_field){
        if(x + size().width() < GameMapThree::X_RIGHT_BARRIER)entered_field = true;
        return;
    }

    double base_len = BULLET_BASE_V * MainWindow::CELL_SIZE * BULLET_V_BUFF * v_buff;

    if(type == "Reflect"){

        if(x < 0){
            vx = - vx - sgn(vx) * base_len * distribution1(gen);
            vy = vy + sgn(vy) * base_len * distribution1(gen);
            x = 0.0;
        }
        else if(x + size().width() > GameMapThree::X_RIGHT_BARRIER){
            vx = - vx - sgn(vx) * base_len * distribution1(gen);
            vy = vy + sgn(vy) * base_len * distribution1(gen);
            x = GameMapThree::X_RIGHT_BARRIER - size().width();
        }
        else if(y < 0){
            vy = - vy - sgn(vy) * base_len * distribution1(gen);
            vx = vx + sgn(vx) * base_len * distribution1(gen);
            y = 0.0;
        }
        else if(y + size().height() > MainWindow::MAP_HEIGHT){
            vy = - vy - sgn(vy) * base_len * distribution1(gen);
            vx = vx + sgn(vx) * base_len * distribution1(gen);
            y = MainWindow::MAP_HEIGHT - size().height();
        }
        else return;

        double len = GameMap::calculate_distance(vx,vy);
        vx = vx / len * base_len;
        vy = vy / len * base_len;

    }else if(type == "Trace"){
        attack = 15;
        if(x < 0){
            vx = - vx * 0.4;
            vy *= 0.4;
            x = 0.0;
        }
        else if(x + size().width() > GameMapThree::X_RIGHT_BARRIER){
            vx = - vx * 0.4;
            vy *= 0.4;
            x = GameMapThree::X_RIGHT_BARRIER - size().width();
        }
        else if(y < 0){
            vy = - vy * 0.4;
            vx *= 0.4;
            y = 0.0;
        }
        else if(y + size().height() > MainWindow::MAP_HEIGHT){
            vy = - vy * 0.4;
            vx *= 0.4;
            y = MainWindow::MAP_HEIGHT - size().height();
        }

        double dx = parent_gamemap->pfigure->x() - x;
        double dy = parent_gamemap->pfigure->y() - y;

        //double len = GameMap::calculate_distance(dx,dy);

        vx += dx * TRACE_BULLET_ACCELERATION * base_len / MainWindow::CELL_SIZE;
        vy += dy * TRACE_BULLET_ACCELERATION * base_len / MainWindow::CELL_SIZE;

    }else if(type == "Missle"){
        attack = 40;
        vx = vx * MISSLE_ACCELERATION;
    }

}

void Bullet::init_v_pos_img(){
    static double BULLET_BASE_V_ = BULLET_BASE_V * MainWindow::CELL_SIZE;
    x = pboss->x();
    y = pboss->y() + pboss->height() / 2 * distribution1(gen);

    if(type == "Reflect"){

        path1 = QString(":/images/images/bullet1.png");
        resize(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);

        v_buff = pow(2.0,distribution1(gen));
        vx = - distribution1(gen);
        vy = distribution2(gen);
        double len = GameMap::calculate_distance(vx,vy);
        vx = vx / len * BULLET_BASE_V_ * BULLET_V_BUFF * v_buff;
        vy = vy / len * BULLET_BASE_V_ * BULLET_V_BUFF * v_buff;

    }else if(type == "Trace"){

        path1 = QString(":/images/images/bullet3.png");
        resize(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);

        v_buff = 0.5;
        double dx = parent_gamemap->pfigure->x() - x;
        double dy = parent_gamemap->pfigure->y() - y;
        double len = GameMap::calculate_distance(dx,dy);
        vx = dx / len * BULLET_BASE_V_ * BULLET_V_BUFF * v_buff;
        vy = dy / len * BULLET_BASE_V_ * BULLET_V_BUFF * v_buff;

    }else if (type == "Missle"){

        path1 = QString(":/images/images/missle1.png");
        resize(MainWindow::CELL_SIZE * 3,MainWindow::CELL_SIZE * 1.5);

        v_buff = 0.3;
        y = parent_gamemap->pfigure->y();
        vx = - BULLET_BASE_V_ * BULLET_V_BUFF * v_buff;
        vy = 0.0;

    }
}


void Bullet::bullet_move(){
    if(not activated){
        y = parent_gamemap->pfigure->y();
        return;
    }
    x += vx;
    y += vy;
    move(x,y);
}

void Bullet::add_processor(int delay_time, int _type){
    UtilsBulletActivate * uba = new UtilsBulletActivate(parent_gamemap,this);
    TaskBuffProcessor tb(uba, QDateTime::currentMSecsSinceEpoch() + delay_time, _type);
    parent_gamemap->tbprocessors.insert(tb);
}



