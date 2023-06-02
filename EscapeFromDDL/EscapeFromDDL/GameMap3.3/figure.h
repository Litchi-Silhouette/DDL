#ifndef FIGURE_H
#define FIGURE_H


#include "config.h"
#include <QWidget>
#include <QString>
#include <QLabel>
#include <random>


class GameMap;


//figure 是功能比较少的类，具体交互依关卡而变，需继承后自己写

class Figure : public QLabel
{
    Q_OBJECT

public:
    bool fixed;                                  //if true，不能移动，在buff里可能用到
    GameMap * parent_gamemap;
    QString path1,path2;
    explicit Figure(GameMap *parent = nullptr);
    ~Figure();

    void embed_image(QString path);             //嵌入图片，path 为资源文件中图片的路径 e.g. sleep->embed_image(":/images/images/buff1.jpg");
    void move_in_grid(const QPoint & pos);      //仅限第一关，其他自己另外写
};

class Boss : public Figure
{
    Q_OBJECT
public:

    explicit Boss(GameMap *parent = nullptr);
    ~Boss(){};

};

class Bullet : public Figure
{
    Q_OBJECT
public:
    static double BULLET_V_BUFF;
    static double MISSLE_ACCELERATION;
    static int total_bullet;
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_real_distribution<double> distribution1;
    static std::uniform_real_distribution<double> distribution2;

    int id;
    int attack;
    bool activated;
    bool entered_field;
    QString type;
    Boss * pboss;
    double v_buff;
    double x,y;
    double vx,vy;
    explicit Bullet(GameMap *parent = nullptr, QString _type = "Reflect", Boss * _pboss = nullptr);
    void bullet_move();
    void init_v_pos_img();
    void bullet_adjust_v();
    ~Bullet(){};
};




#endif // FIGURE_H
