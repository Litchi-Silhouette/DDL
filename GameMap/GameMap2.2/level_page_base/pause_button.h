#ifndef PAUSE_BUTTON_H
#define PAUSE_BUTTON_H

#include <QPushButton>

class pause_button : public QPushButton
{
    Q_OBJECT
public:
    explicit pause_button(const QString& text, QWidget *parent = nullptr);
};

#endif // PAUSE_BUTTON_H

#ifndef PAUSE_BLOCK_H
#define PAUSE_BLOCK_H

#include "mylabel.h"
#include <QTimer>
#include <QResizeEvent>
class pause_block: public QWidget
{
    Q_OBJECT
public:
    explicit pause_block(const int cur_level,QWidget* parent = nullptr, int startTime = 0);
    ~pause_block();
    void start_time();
    void pause_time();
    pause_button* btn;

private slots:
    void update_time();
private:
    int level;
    MyLabel* time_l;
    MyLabel* time_t;
    MyLabel* level_l;
    MyLabel* level_t;
    QTimer* timer;
    int time;
};

#endif // PAUSE_BLOCK_H

#ifndef KEEPRATIOPAUSE_H
#define KEEPRATIOPAUSE_H

#include <QFrame>
#include <QResizeEvent>
class KeepRatioPause : public QFrame
{
    Q_OBJECT
public:
    explicit KeepRatioPause(const int cur_level, QWidget *parent = nullptr)
        : QFrame{parent}, width_ratio(0), height_ratio(0)
    {
        center = new pause_block(cur_level,this);
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground,true);
        setMinimumSize(50,50);
        setMaximumSize(100,100);
        set_ratio(1,1);
        resize(60,70);
    }
    ~KeepRatioPause(){
        delete center;
    }
    void set_ratio(int w, int h){
        width_ratio = w;
        height_ratio = h;
    }
    void start_time(){
        center->start_time();
    }
    void pause_time(){
        center->pause_time();
    }
    pause_button* getbtn(){
        return center->btn;
    }

protected:
    void resizeEvent(QResizeEvent* event){
        QSize old_size = event->oldSize();
        QSize new_size = event->size();
        if(width_ratio && height_ratio)
        {
            if(new_size.width()<width_ratio*new_size.height()/height_ratio){
                new_size.setHeight(height_ratio*new_size.width()/width_ratio);
                center->move(0,(old_size.height()-new_size.height())/2);
            }
            if(new_size.width()>width_ratio*new_size.height()/height_ratio){
                new_size.setWidth(width_ratio*new_size.height()/height_ratio);
                center->move((old_size.width()-new_size.width())/2,0);
            }
        }
        center->resize(new_size);
    }
signals:
private:
    int width_ratio;
    int height_ratio;
    pause_block* center;
};

#endif // KEEPRATIOPAUSE_H
