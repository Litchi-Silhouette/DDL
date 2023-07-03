#include "warning_icon.h"
#include "qpainter.h"
#include <QPaintEvent>
#include <QResizeEvent>
warning_icon::warning_icon(QWidget *parent)
    : QWidget{parent},timer(new QTimer(this))
    ,icon(size()*2/3), map(":/page/level_image/warning.png")
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    connect(timer,&QTimer::timeout, this, &warning_icon::shake);
}

void warning_icon::set_mode(int x){
    mode = x;
    switch (x) {
    case 0:
        setVisible(false);
        timer->stop();
        break;
    case 1:
        setVisible(true);
        index = 4;
        dir = 0;
        timer->stop();
        break;
    case 2:
        setVisible(true);
        index = 4;
        dir = 1;
        timer->start(10);
        break;
    default:
        qDebug()<<"warning mode unavailable"<<Qt::endl;
        break;
    }
    update();
}

void warning_icon::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    if(!mode) return;

    QPainter painter(this);
    painter.translate(width()/2,height()/2);
    switch(index)
    {
    case 1:
        painter.rotate(-5);
        break;
    case 2:
        painter.rotate(-3);
        break;
    case 3:
        painter.rotate(-1);
        break;
    case 5:
        painter.rotate(1);
        break;
    case 6:
        painter.rotate(3);
        break;
    case 7:
        painter.rotate(5);
        break;
    default:
        break;
    }
    painter.drawPixmap(-icon.width()/2,-icon.height()/2, map.scaled(icon));
}

void warning_icon::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    set_size();
}

void warning_icon::shake()
{
    if(index + dir<1||index+dir>7)
        dir = -dir;
    index += dir;
    update();
}

void warning_icon::set_size(double dis){
    if(!dis || mode != 1 )
        icon = size()*Icon_max;
    else
        icon = size()*(Icon_min+(Icon_max-Icon_min)*dis/(dis_max-dis_min));
    update();
}

void warning_icon::set_change(double _dis_max, double _dis_min, double _Icon_max, double _Icon_min){
    Icon_max = _Icon_max;
    Icon_min = _Icon_min;
    dis_max = _dis_max;
    dis_min = _dis_min;
}
