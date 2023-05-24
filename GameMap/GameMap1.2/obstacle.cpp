#include "init.cpp"


class Obstacle :public QLabel{
public:
    GameMap * parent_gamemap;
    int state;
    Obstacle(int _state = 0, GameMap * parent = nullptr):
        QLabel((QWidget *)parent)
    {
        parent_gamemap = parent;
        state = _state;
        resize(MainWindow::CELL_SIZE,MainWindow::CELL_SIZE);
        if(state == 1)embed_image();
    }


    void embed_image(QString path = ":/images/images/obstacle4.jpg"){
        QPixmap pixmap(path);
        pixmap = pixmap.scaled(size(), Qt::KeepAspectRatio);
        this->setPixmap(pixmap);
    }

    void set_state(int new_state = 1){
        state = new_state;
        if(state == 1)embed_image(":/images/images/obstacle4.jpg");
    }
};


