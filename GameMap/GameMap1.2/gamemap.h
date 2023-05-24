#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QString>
#include <vector>
#include <map>
#include <set>
#include "figure.h"
#include "taskbuff.h"
#include "taskbuffprocessor.h"



//gamemap是每一关下面3/4的部分，也是关卡内部核心实现
//所有虚函数都是用来重写的，不用到的话默认return

class MainWindow;
class Obstacle;
class TaskBuff;
class TaskBuffProcessor;


class GameMap : public QWidget
{
    Q_OBJECT

public:
    Figure * pfigure;  //玩家（后面可以加ddl）
    MainWindow * parent_window; //上级窗口（关卡），这里只是样例，实际开发继承wzl的levelwindow
    QTimer * ptimer;   //用于每隔一段时间执行time_event()
    std::vector<TaskBuff *> taskbuffs;
    std::multiset<TaskBuffProcessor> tbprocessors;

    explicit GameMap(MainWindow *parent = nullptr);
    virtual ~GameMap();

    virtual bool check_no_obstacle(const QPoint & pos); //仅限第一关
    virtual void set_taskbuff(TaskBuff * ptb){return;}; //自动把taskbuff加入vector
    virtual void remove_taskbuff(TaskBuff * ptb){return;};//自动把taskbuff移除vector
    virtual void time_event(){return;};
    virtual void end_game(){return;};//判断游戏结束，需要向上级窗口返回一些信息
    virtual void slide_window_event(int left_or_right){return;};//仅限第一关

private:

};


class GameMapOne : public GameMap
{
    Q_OBJECT

public:
    //std::vector<std::vector<Obstacle>> obstacles;
    Obstacle *** obstacles;
    int slide_window_left_barrier;
    explicit GameMapOne(MainWindow  *parent = nullptr);
    virtual ~GameMapOne();
    virtual bool check_no_obstacle(const QPoint & pos);
    void set_obstacle_rect(int xLow,int xHigh,int yLow,int yHigh);
    virtual void set_taskbuff(TaskBuff * ptb);
    virtual void remove_taskbuff(TaskBuff * ptb);
    virtual void time_event();
    virtual void slide_window_event(int left_or_right); // left -1 right 0
};




#endif // GAMEMAP_H
