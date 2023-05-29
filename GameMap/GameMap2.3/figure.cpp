#include "init.cpp"
#include "obstacle.cpp"



class GameMap;

Figure::Figure(GameMap *parent) :
    QLabel((QWidget *)parent)
{
    parent_gamemap = parent;
    fixed = false;
    switch(parent_gamemap->level)
    {
    case 1:
        resize(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);break;
    case 2:
        resize(MainWindow::CELL_SIZE * 1.3,MainWindow::CELL_SIZE * 1.3);break;
    }

    path1 = path2 = ":/images/images/player_lion.jpg";
    embed_image(path1);
}

Figure::~Figure(){}

void Figure::embed_image(QString path){
    QIcon icon(path);
    setPixmap(icon.pixmap(size()));
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
    resize(MainWindow::CELL_SIZE * 2.5,MainWindow::CELL_SIZE * 2.5);
    path1 = QString(":/images/images/boss1.png");
    path2 = QString(":/images/images/boss2.png");
    embed_image(path2);
}
