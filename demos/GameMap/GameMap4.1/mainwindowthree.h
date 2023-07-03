#ifndef MAINWINDOWTHREE_H
#define MAINWINDOWTHREE_H

#include <QWidget>
#include "mainwindow.h"


class MainWindowThree : public MainWindow
{
    Q_OBJECT

public:

    explicit MainWindowThree(Game & game,QWidget *parent = nullptr);
    ~MainWindowThree();

    virtual void finish_task_hurt_boss(const int & drop_live = 10)override;

};


#endif // MAINWINDOWTHREE_H
