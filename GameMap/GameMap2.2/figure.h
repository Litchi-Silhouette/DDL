#ifndef FIGURE_H
#define FIGURE_H


#include "config.h"
#include <QWidget>
#include <QString>
#include <QLabel>


class GameMap;


//figure 是功能比较少的类，具体交互依关卡而变，需继承后自己写

class Figure : public QLabel
{
    Q_OBJECT

public:
    bool fixed;                                  //if true，不能移动，在buff里可能用到
    GameMap * parent_gamemap;
    explicit Figure(GameMap *parent = nullptr);
    ~Figure();

    void embed_image(QString path);             //嵌入图片，path 为资源文件中图片的路径 e.g. sleep->embed_image(":/images/images/buff1.jpg");
    void move_in_grid(const QPoint & pos);      //仅限第一关，其他自己另外写

};

#endif // FIGURE_H
