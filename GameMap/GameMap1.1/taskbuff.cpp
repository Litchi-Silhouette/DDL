#include "figure.h"
#include "ui_figure.h"
#include "gamemap.h"
#include "ui_gamemap.h"
#include "taskbuff.h"
#include "ui_taskbuff.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskbuff.h"
#include "ui_taskbuff.h"
#include "taskbuffprocessor.h"

int TaskBuff::total_buff = 0;
int TaskBuff::total_task = 0;

TaskBuff::TaskBuff(GameMap *parent, int _x_id, int _y_id, qint64 _appear_time, qint64 _disappear_time) :
    QLabel((QWidget *)parent),
    ui(new Ui::TaskBuff)
{
    ui->setupUi(this);
    parent_gamemap = parent;
    type = "Empty";
    x_id = _x_id;
    y_id = _y_id;
    appear_time = _appear_time;
    disappear_time = _disappear_time;
    resize(CELL_SIZE,CELL_SIZE);
    move(x_id * CELL_SIZE, y_id * CELL_SIZE);

    activated = (appear_time <= 0);
    if(not activated){
        hide(); add_processor(appear_time, 1);
    }
    if(disappear_time > 0)add_processor(disappear_time, 2);

}

TaskBuff::~TaskBuff()
{
    delete ui;
}
void TaskBuff::set_explanation(QString _explanation){explanation = _explanation;}
void TaskBuff::set_name(QString _name){name = _name;}

void TaskBuff::embed_image(QString path){
    QPixmap pixmap(path);
    pixmap = pixmap.scaled(size(), Qt::KeepAspectRatio);
    this->setPixmap(pixmap);
}
// called in effect()
void TaskBuff::add_processor(qint64 delay_time, int _type){
    TaskBuffProcessor tb(this, delay_time + QDateTime::currentMSecsSinceEpoch(), _type);
    parent_gamemap->tbprocessors.insert(tb);
}



TaskHomework::TaskHomework(GameMap *parent, int _x_id, int _y_id, QString subject_name, qint64 _appear_time, qint64 _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Task";total_task ++;
    set_name(subject_name + "作业");set_explanation(subject_name + "作业 +1");
}


BuffSleep::BuffSleep(GameMap *parent, int _x_id, int _y_id, qint64 _sleep_time, qint64 _appear_time, qint64 _disappear_time):
    TaskBuff(parent, _x_id, _y_id, _appear_time, _disappear_time)
{
    type = "Buff"; total_buff ++; sleep_time = _sleep_time;
    set_name("昏昏欲睡");set_explanation("原地停留4秒");
}
void BuffSleep::effect(){parent_gamemap->pfigure->fixed = true; add_processor(sleep_time);}
void BuffSleep::end_effect(){parent_gamemap->pfigure->fixed = false;}
