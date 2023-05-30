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
    static double DDL_LINE_SPEED_PER_S;

    DDL_Line * pline;
    Obstacle *** obstacles;
    int slide_window_left_barrier;

    explicit GameMapOne(MainWindow  *parent = nullptr);
    virtual ~GameMapOne();
    virtual bool check_no_obstacle(const QPoint &)override;
    void set_obstacle_rect(int xLow,int xHigh,int yLow,int yHigh);
    virtual void set_taskbuff(TaskBuff *) override;
    virtual void remove_taskbuff(TaskBuff *)override;
    virtual void time_event()override;
    virtual void start_game()override;
    virtual void create_all_taskbuff()override;
    void create_all_obstacle();
    virtual void end_game()override{return;};
    virtual void missed_task_drop_live(TaskBuff * ptb,const int & drop_live = 1)override;
    virtual void slide_window_event(int left_or_right)override; // left -1 right 0
    virtual void update_window_warning(const double & distance)override;

    void time_event_tbprocessor();
    void time_event_player_hit_taskbuff();
    double time_event_move_ddlline();  // return distance(player,ddl) / CELL_SIZE
    void time_event_ddlline_eat_taskbuff();
    int time_event_judge_end_game(); // 0 not end 1 win 2 lose
};






#endif // GAMEMAPONE_H
