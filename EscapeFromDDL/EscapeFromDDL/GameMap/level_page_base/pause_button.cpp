#include "pause_button.h"
#include <QLayout>

pause_block::pause_block(const int cur_level, QWidget* parent, int startTime)
    :QWidget(parent),level(cur_level),time(startTime)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setGeometry(100,100,100,100);
    btn = new QPushButton("",this);
    btn->setStyleSheet("QPushButton{border-width:0px;"
                  "border-image:url(:/page/level_image/stop_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/page/level_image/stop_on_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/page/level_image/stop_on.png);}"
                  "QPushButton:focus{outline: none;}"
                  );
    btn->setFixedSize(50,50);
    btn->setShortcut(QKeySequence(Qt::Key_P));

    time_l = new MyLabel(this, "00:00:00");
    time_t = new MyLabel(this, "游戏时间");
    level_l = new MyLabel(this, QString("%1/3").arg(level));
    level_t = new MyLabel(this, "关卡");

    QVBoxLayout* main_lay = new QVBoxLayout(this);
    QVBoxLayout* up_left = new QVBoxLayout;
    QVBoxLayout* down = new QVBoxLayout;
    QHBoxLayout* up = new QHBoxLayout;
    QGridLayout* up_right = new QGridLayout;

    up_left->addWidget(level_t);
    up_left->addWidget(level_l);
    up_left->setSpacing(0);
    up->setContentsMargins(0,0,0,0);
    up_right->addWidget(btn,0,1);
    up_right->addWidget(new QWidget,1,0);
    up_right->setContentsMargins(0,0,0,0);
    up->addLayout(up_left);
    up->addLayout(up_right);
    up->setSpacing(0);
    up->setContentsMargins(0,0,0,0);
    up->setStretchFactor(up_left,1);
    up->setStretchFactor(btn,1);
    down->addWidget(time_t);
    down->addWidget(time_l);
    down->setSpacing(0);
    down->setContentsMargins(0,0,0,0);
    main_lay->addLayout(up);
    main_lay->addLayout(down);
    main_lay->setSpacing(20);
    main_lay->setStretchFactor(up,1);
    main_lay->setStretchFactor(down,1);
    main_lay->setContentsMargins(0,0,0,0);
    setLayout(main_lay);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&pause_block::update_time);
}

pause_block::~pause_block()
{
    delete btn;
    delete time_l;
    delete time_t;
    delete level_l;
    delete level_t;
    delete timer;
}

void pause_block::start_time(){
    timer->start(1000);
}

void pause_block::update_time()
{
    ++time;
    time_l->setText(QString("%1:%2:%3")
                    .arg(time/3600, 2, 10, QLatin1Char('0'))
                    .arg(time/60%60, 2, 10, QLatin1Char('0'))
                    .arg(time%60, 2, 10, QLatin1Char('0')));
}

void pause_block::pause_time()
{
    timer->stop();
}
