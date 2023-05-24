#ifndef LIVE_BAR_H
#define LIVE_BAR_H

#include <QWidget>
#include<QProgressBar>
#include<QLabel>

class stick:public QWidget
{
    Q_OBJECT
public:
    explicit stick(QWidget *parent = nullptr);
    void set_stick_size(const int,const int);
    QSize get_stick_size()const;
protected:
    void paintEvent(QPaintEvent*);
private:
    int stick_height;
    int stick_width;
    int stick_round = 3;
};

class bar_with_stick:public QWidget
{
    Q_OBJECT
public:
    explicit bar_with_stick(QWidget *parent = nullptr);
    ~bar_with_stick();
    void setValue(int);
protected:
    void resizeEvent(QResizeEvent*);
private:
    QProgressBar* bar;
    stick* bar_stick;
};

class live_bar : public QWidget
{
    Q_OBJECT
public:
    explicit live_bar(QWidget *parent = nullptr);
    void set_live(const int);
    void resizeEvent(QResizeEvent*);
    ~live_bar();
signals:
private:
    bar_with_stick* bar;
    QLabel* live_show;
};

#endif // LIVE_BAR_H

#ifndef KEEPRATIOLIVEBAR_H
#define KEEPRATIOLIVEBAR_H

#include <QFrame>
#include <QResizeEvent>
class KeepRatioLiveBar : public QFrame
{
    Q_OBJECT
public:
    explicit KeepRatioLiveBar(QWidget *parent = nullptr)
        : QFrame{parent}, width_ratio(0), height_ratio(0)
    {
        center = new live_bar(this);
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground,true);
        setMinimumSize(25,20);
        setMaximumSize(80,64);
        set_ratio(5,4);
        resize(minimumSize());
    }
    ~KeepRatioLiveBar(){
        delete center;
    }
    void set_ratio(int w, int h){
        width_ratio = w;
        height_ratio = h;
    }
    void set_live(const int x){
        center->set_live(x);
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
    live_bar* center;
};

#endif // KEEPRATIOWIDGET_H
