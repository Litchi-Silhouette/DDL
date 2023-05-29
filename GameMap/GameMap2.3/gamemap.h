#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QString>
#include <vector>
#include <map>
#include <set>
#include "config.h"
#include "figure.h"
#include "taskbuff.h"
#include "taskbuffprocessor.h"



//gamemap是每一关下面的部分，也是关卡内部核心实现
//所有虚函数都是用来重写的，不用到的话默认return

class MainWindow;
class Obstacle;
class TaskBuff;
class TaskBuffProcessor;
class DDL_Line;


class GameMap : public QWidget
{
    Q_OBJECT

public:
    bool paused;
    bool started;
    Figure * pfigure;  //玩家（后面可以加ddl）
    Boss * pboss;
    MainWindow * parent_window; //上级窗口（关卡），这里只是样例，实际开发继承wzl的levelwindow
    QTimer * ptimer;   //用于每隔一段时间执行time_event()
    std::vector<TaskBuff *> taskbuffs;
    std::multiset<TaskBuffProcessor> tbprocessors;
    int live;
    int level;

    explicit GameMap(MainWindow *parent = nullptr, int _level = 0);
    virtual ~GameMap();

    void update_window_ddl_list();

    virtual bool check_no_obstacle(const QPoint &){return false;}; //仅限第一关
    virtual void set_v_player(const int &, const int &){};//仅限第二关
    virtual void set_v_boss(const double &,const double &){};
    virtual void set_taskbuff(TaskBuff *){return;}; //自动把taskbuff加入vector
    virtual void remove_taskbuff(TaskBuff *){return;};//自动把taskbuff移除vector
    virtual void time_event(){return;};
    virtual void start_game(){return;};
    virtual void pause_game(){paused = true;}; //for wzl levelwindow
    virtual void continue_game(){paused = false;}; //for wzl levelwindow
    virtual void create_all_taskbuff(){return;} //called in start_game()
    virtual void missed_task_drop_live(TaskBuff *,const int & drop_live = 1){return;};
    virtual void end_game(){return;};//判断游戏结束，需要向上级窗口返回一些信息
    virtual void slide_window_event(int left_or_right){return;};//仅限第一关
    virtual void update_window_warning(const double &){return;};


    double calculate_distance(QWidget * pa, QWidget * pb);
    double calculate_distance(const double &,const double &);

};

/*
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
    int time_event_judge_end_game(); // 0 not end 1 win 2 lose
};


*/

#endif // GAMEMAP_H
