#include "init.cpp"
#include "ui_levelwindow.h"
#include <cmath>



MainWindowThree::MainWindowThree(QWidget *parent) : MainWindow(parent,3){}

MainWindowThree::~MainWindowThree(){}


void MainWindowThree::reset(){
    resettask(0,TaskBuff::total_task);
    set_change(1.0,0.0);
}
