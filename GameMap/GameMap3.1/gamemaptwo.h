#ifndef GAMEMAPTWO_H
#define GAMEMAPTWO_H

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



class GameMapTwo : public GameMap
{
    Q_OBJECT

public:
    static qint64 last_set_v_time;
    static double last_set_vx_player;
    static double last_set_vy_player;
    static double PLAYER_V_BUFF;
    static double BOSS_V_BUFF;

    double vx_player, vy_player;
    double vx_boss, vy_boss;
    double x_player, y_player;
    double x_boss, y_boss;
    QTimer * pmove_timer;


    explicit GameMapTwo(MainWindow  *parent = nullptr);
    virtual ~GameMapTwo();

    virtual void set_taskbuff(TaskBuff *) override;
    virtual void remove_taskbuff(TaskBuff *)override;
    virtual void time_event()override;
    virtual void start_game()override;
    virtual void create_all_taskbuff()override;

    virtual void end_game()override{return;};
    virtual void missed_task_drop_live(TaskBuff * ptb,const int & drop_live = 1)override;
    virtual void update_window_warning(const double & distance)override;
    virtual void set_v_player(const int &, const int &)override;//仅限第二关
    virtual void set_v_boss(const double &,const double &)override;

    void move_event();
    void time_event_tbprocessor();
    void time_event_player_hit_taskbuff();
    double time_event_boss_hit_player();
    int time_event_judge_end_game(); // 0 not end 1 win 2 lose
    //double time_event_all_move();
    void time_event_all_adjust_v();

};

#endif // GAMEMAPTWO_H
