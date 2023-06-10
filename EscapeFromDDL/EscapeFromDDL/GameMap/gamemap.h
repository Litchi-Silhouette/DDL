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
    int state; //0: haven't start  1：ongonging  2:pause  3:lose  4:win
    Figure * pfigure;  //玩家（后面可以加ddl）
    Boss * pboss;
    MainWindow * parent_window; //上级窗口（关卡），这里只是样例，实际开发继承wzl的levelwindow
    QTimer * ptimer;   //用于每隔一段时间执行time_event()
    std::vector<TaskBuff *> taskbuffs;
    std::vector<Bullet *>bullets;
    std::multiset<TaskBuffProcessor> tbprocessors;
    int live;
    int boss_live;
    int level;
    int slide_window_left_barrier;//仅限第一关
    QLabel * pending;

    explicit GameMap(MainWindow *parent = nullptr, int _level = 0);
    virtual ~GameMap();

    void update_window_ddl_list();

    virtual bool check_no_obstacle(const QPoint &){return false;}; //仅限第一关
    virtual void set_v_player(const int &, const int &){};//仅限第二关
    virtual void set_v_boss(const double &,const double &){};
    virtual void set_taskbuff(TaskBuff *){return;}; //自动把taskbuff加入vector
    virtual void remove_taskbuff(TaskBuff *){return;};//自动把taskbuff移除vector
    virtual void set_bullet(Bullet *){return;}; //自动把taskbuff加入vector
    virtual void remove_bullet(Bullet *){return;};//自动把taskbuff移除vector

    virtual void time_event(){return;};

    virtual void pause_game(){
        paused = true;
        qDebug()<<"paused";
    };
    virtual void continue_game(){
        paused = false;
        qDebug()<<"continue";
    };
    virtual void start_game();
    virtual void end_game(bool);
    virtual void create_all_taskbuff(){return;};
    virtual void create_all_bullets(){return;};
    virtual void create_all_obstacle(){return;};

    virtual void missed_task_drop_live(TaskBuff *,const int & drop_live = 1){return;};
    virtual void slide_window_event(int){return;};//仅限第一关
    virtual void update_window_warning(const double &){return;};


    static double calculate_distance(QWidget * pa, QWidget * pb);
    static double calculate_distance(const double &,const double &);

};


#endif // GAMEMAP_H
