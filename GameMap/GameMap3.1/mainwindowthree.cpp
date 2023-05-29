#include "init.cpp"
#include <cmath>



MainWindowThree::MainWindowThree(QWidget *parent) : MainWindow(parent,3){}

MainWindowThree::~MainWindowThree(){}


void MainWindowThree::mouseMoveEvent(QMouseEvent* event)
{
    pgamemap->set_v_player(event->pos().x() - pgamemap->pfigure->pos().x(),
                           event->pos().y() - pgamemap->pfigure->pos().y());
    event->accept();
}



void MainWindowThree::reset(){
    resettask(0,TaskBuff::total_task);
    set_change(1.0,0.0);
}
