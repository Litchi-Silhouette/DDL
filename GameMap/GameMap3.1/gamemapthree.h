#ifndef GAMEMAPTHREE_H
#define GAMEMAPTHREE_H

#include <QWidget>
#include <QString>
#include <vector>
#include <map>
#include <set>
#include "config.h"
#include "figure.h"
#include "taskbuff.h"
#include "gamemap.h"
#include "taskbuffprocessor.h"

class MainWindow;
class Obstacle;
class TaskBuff;
class TaskBuffProcessor;
class DDL_Line;

class GameMapThree : public GameMap
{
    Q_OBJECT

public:


    static double PLAYER_V_BUFF;
    static double MOMENTUM;
    static double ACCELERATION;
    static int X_RIGHT_BARRIER;

    double vx_player, vy_player;
    double x_player, y_player;
    double x_boss, y_boss;

    QTimer * pmove_timer;


    explicit GameMapThree(MainWindow *parent = nullptr);
    ~GameMapThree();

    virtual void set_taskbuff(TaskBuff *) override;
    virtual void remove_taskbuff(TaskBuff *)override;
    virtual void time_event()override;
    virtual void start_game()override;
    virtual void create_all_taskbuff()override;

    virtual void end_game()override{return;};
    virtual void missed_task_drop_live(TaskBuff * ptb,const int & drop_live = 1)override;
    virtual void update_window_warning(const double & distance)override;
    virtual void set_v_player(const int &, const int &)override;//仅限第二关

    void move_event();
    void time_event_tbprocessor();
    void time_event_player_hit_taskbuff();
    double time_event_bullet_hit_player();
    int time_event_judge_end_game(); // 0 not end 1 win 2 lose
    //double time_event_all_move();
    void time_event_all_adjust_v();

};


#endif // GAMEMAPTHREE_H