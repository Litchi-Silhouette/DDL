#ifndef GAMEMAPONE_H
#define GAMEMAPONE_H

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



//gamemap是每一关下面的部分，也是关卡内部核心实现
//所有虚函数都是用来重写的，不用到的话默认return

class MainWindow;
class Obstacle;
class TaskBuff;
class TaskBuffProcessor;
class DDL_Line;



class GameMapOne : public GameMap
{
    Q_OBJECT

public:
    DDL_Line * pline;
    Obstacle *** obstacles;
    int slide_window_left_barrier;
    explicit GameMapOne(MainWindow  *parent = nullptr);
    virtual ~GameMapOne();
    virtual bool check_no_obstacle(const QPoint & pos);
    void set_obstacle_rect(int xLow,int xHigh,int yLow,int yHigh);
    virtual void set_taskbuff(TaskBuff * ptb);
    virtual void remove_taskbuff(TaskBuff * ptb);
    virtual void time_event();
    virtual void start_game();
    virtual void create_all_taskbuff();
    void create_all_obstacle();
    virtual void end_game(){return;};
    virtual void slide_window_event(int left_or_right); // left -1 right 0

    void time_event_tbprocessor();
    void time_event_player_hit_taskbuff();
    void time_event_move_ddlline();
    void time_event_ddlline_eat_taskbuff();
    int time_event_judge_end_game(); // 0 not end 1 win 2 lose
};






#endif // GAMEMAPONE_H
