#include "init.cpp"
#include "ui_levelwindow.h"
#include <cmath>



MainWindowThree::MainWindowThree(Game & game, QWidget *parent) : MainWindow(game,parent,3){}

MainWindowThree::~MainWindowThree(){}


void MainWindowThree::finish_task_hurt_boss(const int & drop_live){
    liveBoss -= drop_live;
    if(liveBoss <= 0)liveBoss = 0;
    update_live(false);
}
