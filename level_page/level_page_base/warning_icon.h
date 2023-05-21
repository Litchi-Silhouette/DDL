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
    void set_change(double _Icon_max, double _Icon_min, double _dis_max, double _dis_min);
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paint_pic(double theta);

private slots:
    void shake();
private:
    int mode;  //0:不显示 1：显示 2：颤动
    QTimer* timer;
    QSize icon;
    QPixmap map;
    int index;
    int dir;
    double Icon_max = 0;//相对widget大小
    double Icon_min = 0;
    double dis_max;
    double dis_min;
};

#endif // WARNING_ICON_H

//实现setMode,定时change size if possible
