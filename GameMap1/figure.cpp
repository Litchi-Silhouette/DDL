#include "figure.h"
#include "ui_figure.h"
#include "gamemap.h"
#include "ui_gamemap.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



class GameMap;

Figure::Figure(GameMap *parent) :
    QLabel((QWidget *)parent),
    ui(new Ui::Figure)
{
    ui->setupUi(this);
    parent_gamemap = parent;
    resize(40,40);
    move(40,40);
    fixed = false;
    embed_image(":/images/images/player_lion.jpg");
    //1280*560
    //1280 = 40 + 40*30 + 40
    //560 =  40 + 40*12 + 40
}

Figure::~Figure()
{
    delete ui;
}

void Figure::embed_image(QString path){
    QPixmap pixmap(path);
    pixmap = pixmap.scaled(size(), Qt::KeepAspectRatio);
    this->setPixmap(pixmap);
}

void Figure::move_in_grid(const QPoint & pos){

    if(not fixed &&
       pos.x() >= X_BARRIER &&
       pos.y() >= Y_BARRIER &&
       pos.x() + size().width() + X_BARRIER <= parent_gamemap->width() &&
       pos.y() + size().height() + Y_BARRIER <= parent_gamemap->height());
    else return;

    if(parent_gamemap->check_no_obstacle(pos))
        move(pos);
}
