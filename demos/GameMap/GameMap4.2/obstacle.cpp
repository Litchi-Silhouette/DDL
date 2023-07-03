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


    void embed_image(QString path = ":/images/images/obstacle2.png"){
        QIcon icon(path);
        setPixmap(icon.pixmap(size()));
    }

    void embed_image(const int & x_id){
        QString path;
        if(x_id < X_GRID_NUM * 0.34)
            path = ":/images/images/obstacle2.png";
        else if(x_id < X_GRID_NUM * 0.67)
            path = ":/images/images/obstacle3.png";
        else
            path = ":/images/images/obstacle4.png";

        QIcon icon(path);
        setPixmap(icon.pixmap(size()));
    }

    void set_state(const int & new_state, const int & x_id = 1){
        state = new_state;
        if(state == 1)
            embed_image(x_id);
        else
            hide();
    }
};


