#ifndef TASKBUFF_H
#define TASKBUFF_H

#include <QWidget>
#include <QTime>
#include <config.h>
#include <QString>
#include <QLabel>
#include "config.h"



class GameMap;
class Bullet;

class TaskBuff : public QLabel{
    Q_OBJECT
public:
    static int total_task,total_buff;
    static int finished_task;
    static int missed_task;
    int id; //start from 0; (when a taskbuff is created)id = total_task + total_buff
    double x_id,y_id;//在第几格，仅限第一关；后续代码一样，x_id表示格子数，x表示坐标
    bool movable;//仅限第三关
    double vx,vy;//仅限第三关
    int attack_to_boss;//仅限第三关
    bool activated;//是否被触发（是否显示，玩家是否吃到）
    bool missed;//是否被错过了（被ddl吃掉，也算作完成，但是显示有所不同并且要扣血）
    bool twinkling;
    QString type;//"Task" or "Buff"
    QString name;
    QString explanation;
    QString img_path;
    int appear_time,disappear_time;
    GameMap * parent_gamemap;
    Bullet * pblt;

    explicit TaskBuff(GameMap *parent = nullptr, double _x_id = -10, double _y_id = -10, int _appear_time = -1, int _disappear_time = -1);
    ~TaskBuff();

    void embed_image(QString path);
    void set_explanation(QString _explanation);
    void set_name(QString _name);

    virtual void effect(){return;};//触发效果
    virtual void end_effect(){return;};//延时结束效果
    virtual void missed_effect();
    void add_processor(int delay_time, int _type = 0);
    void twinkle();
    virtual void taskbuff_move();
    virtual void taskBuff_adjust_v();

    void set_v(const double & x_dir, const double & y_dir, const double & v_buff = 1.0);


};



#endif // TASKBUFF_H
