#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include "gamemap.h"
#include "config.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

//上级窗口（关卡），这里只是样例，实际开发继承wzl的levelwindow

class TaskBuff;

class MainWindow : public LevelWindow
{
    Q_OBJECT
public:
    static int MOVE_UNIT;
    static int CELL_SIZE;
    static int X_BARRIER;
    static int Y_BARRIER;
    static int Y_TOOL_HEIGHT;
    static int HEIGHT;
    static int WIDTH;
    static int MAP_HEIGHT;

    GameMap * pgamemap;
    QLabel * ptaskbuff_board;//for test
    MainWindow(QWidget *parent = nullptr, int level = 0);
    ~MainWindow();
    void renew_taskbuff_board(TaskBuff * ptb);
    void add_taskbuff(TaskBuff * ptb);
    void show_taskbuff(TaskBuff * ptb);
    void remove_taskbuff(TaskBuff * ptb);
    void update_ddl_list(){finished = TaskBuff::finished_task; missed = TaskBuff::missed_task; LevelWindow::update_List();}
    void missed_task_drop_live(TaskBuff * ptb, const int & drop_live);
    void hit_bullet_drop_life(Bullet * ptb,const int & drop_live);
    virtual void reset();
    virtual void startCount() override;
    void endGame();
    void update_warning(const double &);


protected:
    void keyPressEvent(QKeyEvent*) override{};//需继承wzl的levelwindow并重载
    void resizeEvent(QResizeEvent *) override;//
    virtual void changeGameProcess(bool pause_or_continue); // true pause false continue

};

#endif // MAINWINDOW_H
