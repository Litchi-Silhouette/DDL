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
    static double GRAVITY;
    static int X_RIGHT_BARRIER;

    double vx_player, vy_player;
    double x_player, y_player;
    double x_boss, y_boss;

    QLabel * pwarningline;

    //QTimer * pmove_timer;


    explicit GameMapThree(MainWindow *parent = nullptr);
    ~GameMapThree();

    virtual void set_taskbuff(TaskBuff *)override;
    virtual void remove_taskbuff(TaskBuff *)override;
    virtual void set_bullet(Bullet *)override; //自动把taskbuff加入vector
    virtual void remove_bullet(Bullet *)override;//自动把taskbuff移除vector
    virtual void start_game()override;

    virtual void create_all_taskbuff()override;
    virtual void create_all_bullets()override;

    virtual void missed_task_drop_live(TaskBuff * ptb,const int & drop_live = 1)override;
    virtual void update_window_warning(const double & distance)override;

    virtual void time_event()override;
    void move_event();
    void time_event_tbprocessor();
    void time_event_player_hit_taskbuff();
    void hit_bullet_drop_life(Bullet *);
    void time_event_bullet_hit_player();
    int time_event_judge_end_game(); // 0 not end 1 win 2 lose
    //double time_event_all_move();
    void time_event_all_adjust_v();
    void time_event_all_taskbuff_twinkle();

    double calculate_acceleration(const int & x_relative,const int & y_relative, const double & len);

};


#endif // GAMEMAPTHREE_H
