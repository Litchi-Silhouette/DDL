#include "init.cpp"
#include "obstacle.cpp"



class GameMap;

Figure::Figure(GameMap *parent) :
    QLabel((QWidget *)parent)
{
    parent_gamemap = parent;
    fixed = false;
    resize(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);
    move(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);
    embed_image(":/images/images/player_lion.jpg");
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
