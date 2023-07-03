#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <QSoundEffect>
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
    QSoundEffect * psound[6];

    MainWindow(Game & game, QWidget *parent = nullptr, int level = 0);
    ~MainWindow();
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
    void update_all_live();
    virtual void finish_task_hurt_boss(const int & drop_live = 10){return;};
    void play_sound_effect(const int & id);
    // 0 task 1 buff 2 bullet 3 fault 4 lose 5 win



protected:
    void keyPressEvent(QKeyEvent*) override{};//需继承wzl的levelwindow并重载
    //void resizeEvent(QResizeEvent *) override;//
    void showEvent(QShowEvent *event) override;
    virtual void changeGameProcess(bool pause_or_continue); // true pause false continue

};

#endif // MAINWINDOW_H
