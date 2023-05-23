#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QString>
#include <vector>
#include <map>
#include <set>
#include "figure.h"
#include "ui_figure.h"
#include "taskbuff.h"
#include "ui_taskbuff.h"
#include "taskbuffprocessor.h"


namespace Ui {
class GameMap;
class GameMapOne;
}


class MainWindow;
class Obstacle;
class TaskBuff;
class TaskBuffProcessor;


class GameMap : public QWidget
{
    Q_OBJECT

public:
    Figure * pfigure;
    MainWindow * parent_window;
    QTimer * ptimer;
    std::vector<TaskBuff *> taskbuffs;
    std::multiset<TaskBuffProcessor> tbprocessors;

    explicit GameMap(MainWindow *parent = nullptr);
    virtual ~GameMap();

    virtual bool check_no_obstacle(const QPoint & pos);
    virtual void set_taskbuff(TaskBuff * ptb){return;};
    virtual void remove_taskbuff(TaskBuff * ptb){return;};
    virtual void time_event(){return;};
    virtual void end_game(){return;};

private:
    Ui::GameMap *ui;
};


class GameMapOne : public GameMap
{
    Q_OBJECT

public:
    //std::vector<std::vector<Obstacle>> obstacles;
    Obstacle *** obstacles;
    explicit GameMapOne(MainWindow  *parent = nullptr);
    virtual ~GameMapOne();
    virtual bool check_no_obstacle(const QPoint & pos);
    void set_obstacle_rect(int xLow,int xHigh,int yLow,int yHigh);
    virtual void set_taskbuff(TaskBuff * ptb);
    virtual void remove_taskbuff(TaskBuff * ptb);
    virtual void time_event();
};




#endif // GAMEMAP_H
