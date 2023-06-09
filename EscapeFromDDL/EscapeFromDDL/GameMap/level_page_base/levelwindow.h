#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsEffect>
#include <QLayout>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>
#include "pause_button.h"
#include "live_bar.h"
#include "warning_icon.h"
#include "ddl_list.h"
#include "pause_start_end.h"
#include "../../Game.hpp"
#include "../../windowbase.h"

namespace Ui {
class LevelWindow;
}

class LevelWindow : public windowBase
{
    Q_OBJECT

public:
    LevelWindow(Game& game, QWidget *parent = nullptr,const int cur_level = 0);
    ~LevelWindow();

    void endGame();

protected:
    //DDL_List 部分操作
    void resettask(int fin = 0, int all = 0){
        finished = fin;
        list->set_ini_task(finished, all);
    }   //设置初始
    void update_List(){
        list->update_finish(finished + missed);
    }   //完成+1
    void banBuffList(bool toBan){
        list->banBuff(toBan);
    }
    // 同一关卡中task,buff统一编号，总数请不超过1000
    void add_task(const QString& icon, const QString& name, const QString& info, const int index, const bool isred = false){
        list->add_task(icon,name,info,index + (level - 1)*1000, isred);
    }
    void add_buff(const QString& icon, const QString& name, const QString& info, const int index, const bool isred = false){
        list->add_buff(icon,name,info,index + (level - 1)*1000, isred);
    }
    void remove_task(const int index){
        list->remove_task(index + (level - 1)*100);
    }
    void remove_buff(const int index){
        list->remove_buff(index + (level - 1)*1000);
    }
    void changeTaskColour(const int index, bool red){
        list->changeTaskColour(index, red);
    }
    void changeBuffColour(const int index, bool red){
        list->changeBuffColour(index, red);
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
    void update_live(bool isLion = true){
        if(level!=3)
            bar->set_live(live);
        else if(isLion)
            double_bar->set_live(live, true);
        else
            double_bar->set_live(liveBoss, false);
    }   //设置当前血量
    void setTotalLive(int allLive){
        if(level!=3)
            bar->setTotalLive(allLive);
    }   //开始时设置总血量(level = 3 无效)
    void setIniLive(int lionini, int bossini = 100){
        if(level!=3)
        {
            live = lionini;
            update_live();
        }else
            double_bar->setiniLive(lionini, bossini);
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
        if(!can)
            map_border->setFrameStyle(QFrame::NoFrame);
    }
    void deleteMap(){
        map_border->setLineWidth(0);
        map_border->setMidLineWidth(0);
    }
    QFrame* getWidget(){
        return map_border;
    }
    //half操作
    virtual void halfMovie();

    int level;
    int live = 5;
    int liveBoss = 100;
    int finished = 0;
    int missed = 0;
    int state = 0;         //0: haven't start  1：ongonging 2:pause  3:lose  4:win
    int interval = 30;
    QTimer* timer_update;
    QVBoxLayout* main_lay;
protected slots:
    void pause();
    void showEvent(QShowEvent* event);

    virtual void startCount();
    virtual void restart();
    virtual void changeGameProcess(bool topause);

private slots:
    void startText1();
    void startText2();
    void startText3();
    void end();
private:
    void setBlur(int extent);

    pause_block* pause_b;
    KeepRatioLiveBar* bar;
    DoubleLive* double_bar;
    KeepRatioWarning* warning;
    DDL_List* list;
    QFrame* map_border;
    PauseDialog* pauseDlg;
    StartDialog* startDlg;
    EndDialog* endDlg;

    Ui::LevelWindow *ui;
    QGraphicsBlurEffect* blureffect;
    Game& statistics;
    CoverMask* curMask;
    QMediaPlayer* player;
    QAudioOutput* audio;
    QSoundEffect* start1;
    QSoundEffect* start2;
    QSoundEffect* buttom;
};
#endif // LEVELWINDOW_H

/*
 * 使用注意
 * 1、task出现addtask, task完成removetask, buff吃到addbuff buff消失emovebuff  如果在buff吃到之外强制显示提示调用showbuff/task
 * 2、完成任务finished++，miss任务miss++ 掉血live--, 之后调用相应update， 开始时先设置总血量，再设置初始血量
 * 3、warning部分请间隔interval后就调用一次setsize， mode!=1时省略参数
 * 4、添加地图请使用getWidegt作为parent  相应的边框操作其实可以自己修改
 * 5、由于qt自身编译的影响，我无法做到接口和基本实现分离（卑微），hideEvent(QHideEvent* event);restart();changeGameProcess(bool pause);
 * 现阶段可以不用填写实现，要实现先调用基类  注意实时更新游戏状态
 * Game类是串联的类，现阶段不应改，main函数只要改掉相应的构造就行
 * 运行结束只能用任务管理器（嘿嘿嘿）嫌麻烦可以注释掉hideevent
 * 包含代码时注意删除或重写main,要声明gamePage成员变量
 * startCount函数是游戏正式开始的函数，如有需要可继承后重写
 *
 * 对于level3设置live时总数固定100，设置live时注意最小步长为5
*/
