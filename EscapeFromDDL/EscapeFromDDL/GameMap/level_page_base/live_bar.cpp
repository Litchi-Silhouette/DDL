#include "live_bar.h"
#include <QLayout>
#include <QSizePolicy>
#include <QPainter>

live_bar::live_bar(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);

    live_show = new MyLabel(this, "生命值");
    live_show->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);

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
    temp.setPixelSize(live_show->height()*2/3);
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
    bar->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    bar->setStyleSheet("QProgressBar{border-radius:6px;"
            "border:2px solid black;"
            "background: transparent;"
            "text-align: center;"
            "font:bold;}"
            "QProgressBar::chunk{border-radius:4px; border:1px solid black;"
            "background-color: #FFB90F;"
            "width:10px;margin:1px;}");

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
    double now_w = (double)(bar->width()*0.97-7.6)/totalLive-3;
    auto cur = bar->styleSheet();
    int p = cur.indexOf("width") + 6;
    int i = p;
    while(cur[i]>='0'&&cur[i]<='9')
        ++i;
    bar->setStyleSheet(cur.mid(0,p)+QString::number(now_w)+cur.mid(i));
}

void bar_with_stick::setValue(int live){
    auto cur = bar->styleSheet();
    int s = cur.indexOf("#");
    int p = cur.indexOf(";width");
    QString tempcolor;
    auto actualLive = live*100/totalLive;
    if(actualLive>60)
        tempcolor = "#FFD700";
    else if(actualLive>30)
        tempcolor = "#FFB90F";
    else
        tempcolor = "#FF0000";

    bar->setStyleSheet(cur.mid(0,s) + tempcolor + cur.mid(p));
    bar->setValue(actualLive);
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

DoubleLive::DoubleLive(QWidget* parent):
    QWidget{parent}, t(new QTimer(this))
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);

    connect(t, &QTimer::timeout, this, &DoubleLive::changeLive);

    bossBar = new QProgressBar(this);
    bossBar->setRange(0,100);
    bossBar->setOrientation(Qt::Horizontal);
    bossBar->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    bossBar->setStyleSheet("QProgressBar{border-radius:6px; border:2px solid black;"
                                        "background: transparent; text-align: center;font:bold;}"
                            "QProgressBar::chunk{border-radius:4px; border:1px solid gray;"
                                        "background-color: #FFB90F;}");
    bossBar->setMaximumHeight(20);
    bossBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    lionBar = new QProgressBar(this);
    lionBar->setRange(0,100);
    lionBar->setOrientation(Qt::Horizontal);
    lionBar->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    lionBar->setStyleSheet("QProgressBar{border-radius:6px; border:2px solid black;"
                                        "background: transparent; text-align: center;font:bold;}"
                            "QProgressBar::chunk{border-radius:4px; border:1px solid gray;"
                                        "background-color: #FFB90F;}");
    lionBar->setMaximumHeight(20);
    lionBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    lionTitle = new QLabel("",this);
    lionTitle->setPixmap(QPixmap(":/page/level_image/lionIcon.png").scaled(80,80,Qt::KeepAspectRatio));
    bossTitle = new QLabel("", this);
    bossTitle->setPixmap(QPixmap(":/page/level_image/bossIcon.png").scaled(80,80,Qt::KeepAspectRatio));

    auto mainLay = new QGridLayout;
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->setSpacing(0);
    mainLay->addWidget(bossTitle,0,0,1,1);
    mainLay->addWidget(bossBar, 0,1,1,1);
    mainLay->addWidget(lionTitle, 1,0,1,1);
    mainLay->addWidget(lionBar, 1,1,1,1);
    setLayout(mainLay);

}

DoubleLive::~DoubleLive()
{
    delete bossBar;
    delete lionBar;
    delete t;
    delete lionTitle;
    delete bossTitle;
}

void DoubleLive::set_live(const int x, bool isLion)
{
    if(isLion)
        lionLiveAim = x;
    else
        bossLiveAim = x;
    if(!t->isActive())
        t->start(interval);
}

void DoubleLive::changeLive()
{
    if(lionLiveAim >= lionLiveCur && bossLiveAim >= bossLiveCur)
        t->stop();
    if(lionLiveAim < lionLiveCur)
    {
        lionLiveCur -= singleStep;
        auto cur = lionBar->styleSheet();
        int s = cur.indexOf("#");
        QString tempcolor;
        if(lionLiveCur>60)
            tempcolor = "#FFD700";
        else if(lionLiveCur>30)
            tempcolor = "#FFB90F";
        else
            tempcolor = "#FF0000";
        lionBar->setStyleSheet(cur.mid(0,s) + tempcolor + ";}");
        lionBar->setValue(lionLiveCur);
    }
    if(bossLiveAim < bossLiveCur)
    {
        bossLiveCur -= singleStep;
        /*
        auto cur = bossBar->styleSheet();
        int s = cur.indexOf("#");
        int p = cur.indexOf(";width");
        QString tempcolor;
        if(bossLiveCur>60)
            tempcolor = "#FFD700";
        else if(bossLiveCur>30)
            tempcolor = "#FFB90F";
        else
            tempcolor = "#FF0000";
        bossBar->setStyleSheet(cur.mid(0,s) + tempcolor + cur.mid(p));
        */
        bossBar->setValue(bossLiveCur);
    }
}

void DoubleLive::setiniLive(const int lion,const int boss)
{
    lionLiveAim = lionLiveCur = lion;
    bossLiveAim = bossLiveCur = boss;
    bossBar->setValue(bossLiveCur);
    lionBar->setValue(lionLiveCur);
}
