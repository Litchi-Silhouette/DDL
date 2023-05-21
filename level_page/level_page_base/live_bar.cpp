#include "live_bar.h"
#include <QLayout>
#include <QSizePolicy>
#include <QPainter>

live_bar::live_bar(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setMinimumSize(80,50);
    live_show = new QLabel("生命值",this);
    live_show->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    live_show->setStyleSheet("QLabel{font:bold;}");
    live_show->setMinimumSize(50,20);
    live_show->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    bar = new bar_with_stick(this);

    QVBoxLayout* main_lay = new QVBoxLayout(this);
    main_lay->setSpacing(5);
    main_lay->setContentsMargins(0,0,0,0);
    main_lay->addWidget(live_show);
    main_lay->addWidget(bar);
    main_lay->setStretchFactor(live_show,1);
    main_lay->setStretchFactor(bar,1);
    setLayout(main_lay);

    set_live(100);
}

live_bar::~live_bar()
{
    delete bar;
    delete live_show;
}

void live_bar::set_live(const int x){
    bar->setValue(x);
}

void live_bar::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);
    auto temp = live_show->font();
    temp.setPixelSize(live_show->height()/2);
    live_show->setFont(temp);
}

bar_with_stick::bar_with_stick(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);

    bar = new QProgressBar(this);
    bar->setRange(0,100);
    bar->setOrientation(Qt::Horizontal);
    bar->setMinimumSize(50,20);
    bar->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

    bar_stick = new stick(this);
    bar_stick->setMinimumSize(5,10);
    bar_stick->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

    QHBoxLayout* bottom_lay = new QHBoxLayout(this);
    bottom_lay->setSpacing(0);
    bottom_lay->setContentsMargins(0,0,0,0);
    bottom_lay->addWidget(bar);
    bottom_lay->addWidget(bar_stick);
    bottom_lay->setStretchFactor(bar,20);
    bottom_lay->setStretchFactor(bar_stick,1);

    setLayout(bottom_lay);
}

void bar_with_stick::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    auto temp = bar->font();
    temp.setPixelSize(bar->height()/2);
    bar->setFont(temp);
    bar_stick->set_stick_size(bar_stick->width(),bar->height()/2);
    //update();
}

void bar_with_stick::setValue(int live){
    if(live>60)
    {
        bar->setStyleSheet("QProgressBar{border-radius:6px;"
                "border:2px solid black;"
                "background: transparent;"
                "text-align: center;"
                "font:bold;}"
                "QProgressBar::chunk{border-radius:4px; border:1px solid black;"
                "background-color: #00EE76;"
                "width:10px;margin:0.5px;}");
    }else if(live>30){
        bar->setStyleSheet("QProgressBar{border-radius:6px;"
                "border:2px solid black;"
                "background: transparent;"
                "text-align: center;"
                "font:bold;}"
                "QProgressBar::chunk{border-radius:4px; border:1px solid black;"
                "background-color: #FFB90F;"
                "width:10px;margin:0.5px;}");
    }else{
        bar->setStyleSheet("QProgressBar{border-radius:6px;"
                "border:2px solid black;"
                "background: transparent;"
                "text-align: center;"
                "font:bold;}"
                "QProgressBar::chunk{border-radius:4px; border:1px solid black;"
                "background-color: #FF0000;"
                "width:10px;margin:0.5px;}");
    }
    bar->setValue(live);
    update();
}

bar_with_stick::~bar_with_stick(){
    delete bar;
    delete bar_stick;
}

stick::stick(QWidget *parent)
    :QWidget(parent),stick_height(10),stick_width(10){}

void stick::set_stick_size(const int w, const int h)
{
    stick_height = h;
    stick_width = w;
}

QSize stick::get_stick_size()const{
    return QSize(stick_width,stick_height);
}

void stick::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    QBrush brush(Qt::black);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.translate(0,(height()-stick_height)/2);

    painter.drawRoundedRect(-stick_round,0,stick_width+stick_round,stick_height,stick_round,stick_round);
}
