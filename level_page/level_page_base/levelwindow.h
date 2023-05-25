#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsEffect>
#include "pause_button.h"
#include "live_bar.h"
#include "warning_icon.h"
#include "ddl_list.h"
#include "set_pausedialog.h"
#include "Game.h"

namespace Ui {
class LevelWindow;
}

class LevelWindow : public QMainWindow
{
    Q_OBJECT

public:
    static Game gamePages;
    LevelWindow(QWidget *parent = nullptr,const int cur_level = 0);
    ~LevelWindow();

    void endGame();
protected:
    //DDL_List 部分操作
    void resettask(int fin = 0, int all = 0){
        finished = fin;
        list->set_ini_task(finished, all);
    }   //设置初始
    void update_finish(){
        list->update_finish(finished);
    }   //完成+1
    // 同一关卡中task,buff统一编号，总数请不超过1000
    void add_task(const QPixmap& icon, const QString& name, const QString& info, const int index){
        list->add_task(icon,name,info,index + (level - 1)*1000);
    }
    void add_buff(const QPixmap& icon, const QString& name, const QString& info, const int index){
        list->add_buff(icon,name,info,index + (level - 1)*1000);
    }
    void remove_task(const int index){
        list->remove_task(index + (level - 1)*100);
    }
    void remove_buff(const int index){
        list->remove_buff(index + (level - 1)*1000);
    }
    void showTask(const int index){
        list->showTask(index + (level - 1)*1000);
    }
    void showBuff(const int index){
        list->showBuff(index + (level - 1)*1000);
    }
    void clearList(){
        list->clear();
    }   //清空表单并重置完成为0

    //Live_bar部分操作
    void update_live(){
        bar->set_live(live);
    }   //设置当前血量
    void setTotalLive(int allLive){
        bar->setTotalLive(allLive);
    }   //开始时设置总血量
    void setIniLive(int inilive){
        live = inilive;
        update_live();
    }   //设置初始血量

    //warning 部分操作
    void set_mode(int mode){
        warning->set_mode(mode);
    }   //设置模式，默认开始时为0  0:不显示 1：显示 2：颤动
    void set_size(double dis = 0){
        warning->set_size(dis);
    }   //输入自变量定比例
    void set_change(double _dis_max, double _dis_min, double _Icon_max = (double)3/4, double _Icon_min = (double)1/2){
        warning->set_change(_dis_max,_dis_min, _Icon_max,_Icon_min);
    }   //设置显示时比例放缩关系

    //map_border部分操作
    void setMapVisible(bool can){
        map_border->setVisible(can);
    }
    void deleteMap(){
        map_border->setLineWidth(0);
        map_border->setMidLineWidth(0);
    }
    QFrame* getWidget(){
        return map_border;
    }

    int live = 5;
    int finished = 0;
    int state = 0;         //0: haven't start  1：ongonging 2:pause  3:lose  4:win
    int interval = 30;
    QTimer* timer_update;
protected slots:
    void pause();
    void turnNext();
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);
    virtual void startCount();
    virtual void restart();
    virtual void pauseGameProcess(bool pause);

private slots:
    void startText1();
    void startText2();
    void startText3();
private:
    void setBlur(int extent);

    pause_block* pause_b;
    KeepRatioLiveBar* bar;
    KeepRatioWarning* warning;
    DDL_List* list;
    QFrame* map_border;
    PauseDialog* pauseDlg;
    StartDialog* startDlg;

    QGraphicsBlurEffect* blureffect = new QGraphicsBlurEffect;
    Ui::LevelWindow *ui;
    int level;
};
#endif // LEVELWINDOW_H

/*
 * 使用注意
 * 1、task出现addtask, task完成removetask, buff吃到addbuff buff消失emovebuff  如果在buff吃到之外强制显示提示调用showbuff/task
 * 2、完成任务finished++， 掉血live--, 之后调用相应update， 开始时先设置总血量，再设置初始血量
 * 3、warning部分请间隔interval后就调用一次setsize， mode!=1时省略参数
 * 4、添加地图请使用getWidegt作为parent  相应的边框操作其实可以自己修改
 * 5、由于qt自身编译的影响，我无法做到接口和基本实现分离（卑微），hideEvent(QHideEvent* event);restart();pauseGameProcess(bool pause);
 * 现阶段可以不用填写实现，要实现先调用基类  注意实时更新游戏状态
 * Game类是串联的类，现阶段不应改，main函数只要改掉相应的构造就行
 * 运行结束只能用任务管理器（嘿嘿嘿）嫌麻烦可以注释掉hideevent
 * 包含代码时注意删除或重写main,要声明gamePage成员变量
 * startCount函数是游戏正式开始的函数，如有需要可继承后重写
*/
