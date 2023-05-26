#ifndef WARNING_ICON_H
#define WARNING_ICON_H

#include <QWidget>
#include <QTimer>

class warning_icon : public QWidget
{
    Q_OBJECT
public:
    explicit warning_icon(QWidget *parent = nullptr);
    void set_mode(int);
    void set_size(double dis = 0);
    void set_change(double _dis_max, double _dis_min, double _Icon_max, double _Icon_min);
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paint_pic(double theta);

private slots:
    void shake();
private:
    int mode;   //0:不显示 1：显示 2：颤动
    QTimer* timer;
    QSize icon;
    QPixmap map;
    int index;
    int dir;
    double Icon_max = 1;//相对widget大小
    double Icon_min = 0;
    double dis_max;
    double dis_min;
};

#endif // WARNING_ICON_H

//实现setMode,定时change size if possible

#ifndef KEEPRATIOWARNING_H
#define KEEPRATIOWARNING_H

#include <QFrame>
#include <QResizeEvent>
class KeepRatioWarning : public QFrame
{
    Q_OBJECT
public:
    explicit KeepRatioWarning(QWidget *parent = nullptr)
        : QFrame{parent}, width_ratio(0), height_ratio(0)
    {
        center = new warning_icon(this);
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground,true);
        setMinimumSize(20,16);
        setMaximumSize(100,80);
        set_ratio(5,4);
        resize(minimumSize());
    }
    ~KeepRatioWarning(){
        delete center;
    }
    void set_ratio(int w, int h){
        width_ratio = w;
        height_ratio = h;
    }
    void set_mode(int x){
        center->set_mode(x);
    }
    void set_size(double dis = 0){
        center->set_size(dis);
    }
    void set_change(double _dis_max, double _dis_min, double _Icon_max, double _Icon_min){
        center->set_change(_dis_max,_dis_min, _Icon_max,_Icon_min);
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
    warning_icon* center;
};

#endif // KEEPRATIOWARNING_H
