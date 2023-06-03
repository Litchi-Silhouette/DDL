#include "init.cpp"


QPoint MainWindowTwo::last_press_player_pos = QPoint(0,0);

MainWindowTwo::MainWindowTwo(Game & game,QWidget *parent) : MainWindow(game,parent,2){}

MainWindowTwo::~MainWindowTwo(){}


void MainWindowTwo::mousePressEvent(QMouseEvent* event)
{
    //qDebug()<<"mousePressEvent called";
    if(event->button() == Qt::LeftButton)
    {
        last_press_player_pos = event->pos();
    }
    event->accept();
}

void MainWindowTwo::mouseReleaseEvent(QMouseEvent* event)
{
    //qDebug()<<"mouseReleaseEvent called";
    if(event->button() == Qt::LeftButton)
    {
        int x_relative = event->pos().x() - last_press_player_pos.x();
        int y_relative = event->pos().y() - last_press_player_pos.y();

        pgamemap->set_v_player(x_relative, y_relative);
    }
    event->accept();
}


