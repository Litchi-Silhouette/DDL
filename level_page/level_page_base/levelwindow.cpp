#include "levelwindow.h"
#include "ui_levelwindow.h"
#include <QSizePolicy>
#include <QPainter>

LevelWindow::LevelWindow(QWidget *parent, const int cur_level)
    : windowBase(parent)
    , level(cur_level)
    , ui(new Ui::LevelWindow)
{
    ui->setupUi(this);

    pause_b = new pause_block(level,this);
    pause_b->setMaximumWidth(150);
    connect(pause_b->getBtn(), &QPushButton::clicked, this, &LevelWindow::pause);

    auto live_warn = new QVBoxLayout;

    live_warn->setContentsMargins(0,0,0,0);
    live_warn->setSpacing(5);
    bar = new KeepRatioLiveBar(this);
    warning = new KeepRatioWarning(this);

    live_warn->addWidget(warning, 1);
    live_warn->addWidget(bar, 1);

    double_bar = new DoubleLive(this);

    auto it = statics.all_buffs.find(level);
    if(it == statics.all_buffs.end())
        statics.all_buffs[level] = new ItemHash;
    it = statics.all_tasks.find(level);
    if(it == statics.all_tasks.end())
        statics.all_tasks[level] = new ItemHash;
    list = new DDL_List((level == 3) ,this, &statics.all_items , statics.all_tasks[level], statics.all_buffs[level]);

    map_border = new QFrame(this);
    map_border->setFrameShadow(QFrame::Sunken);
    map_border->setFrameShape(QFrame::Panel);
    map_border->setLineWidth(5);
    map_border->setMidLineWidth(5);

    pauseDlg  = new PauseDialog(this);
    startDlg = new StartDialog(this);
    endDlg = new EndDialog(this);

    auto up = new QHBoxLayout;
    main_lay = new QVBoxLayout;

    up->setContentsMargins(5,5,5,0);
    up->setSpacing(5);
    if(level!=3)
    {
        double_bar->setVisible(false);
        up->addWidget(list,5);
        up->addStretch(1);
        up->addLayout(live_warn, 1);
    }
    else
    {
        live = 100;
        warning->setVisible(false);
        bar->setVisible(false);
        up->addWidget(double_bar, 3);
        up->addStretch(1);
        up->addWidget(list, 3);
        up->addStretch(2);
    }
    up->addWidget(pause_b, 1);

    main_lay->setContentsMargins(0,0,0,0);
    main_lay->setSpacing(5);
    main_lay->addLayout(up);
    main_lay->addWidget(map_border);
    main_lay->setStretchFactor(up,6);
    main_lay->setStretchFactor(map_border,21);

    ui->centralwidget->setLayout(main_lay);
}

LevelWindow::~LevelWindow()
{
    delete ui;
    delete bar;
    delete list;
    delete warning;
    delete pause_b;
    delete map_border;
    delete pauseDlg;
    delete double_bar;
    delete endDlg;
}

void LevelWindow::pause(){
    setBlur(30);
    changeGameProcess(true);

    pauseDlg->exec();
    switch (pauseDlg->getChoice()) {
    case 1:
        closeGradually();
        break;
    case 2:
        restart();
        break;
    case 3:
        changeGameProcess(false);
        break;
    default:
        break;
    }
    setBlur(0);
}

void LevelWindow::setBlur(int extent){
    if(extent)
    {
        blureffect->setEnabled(true);
        blureffect->setBlurRadius(extent);
        setGraphicsEffect(blureffect);
    }
    else
        blureffect->setEnabled(false);
}

void LevelWindow::startText1(){
    setBlur(10);
    startDlg->open();
    startDlg->setStartText("好",90);
    QTimer::singleShot(1500,this, &LevelWindow::startText2);
}

void LevelWindow::startText2(){
    startDlg->setStartText("准备",60);
    QTimer::singleShot(1500,this, &LevelWindow::startText3);
}

void LevelWindow::startText3(){
    startDlg->setStartText("开始",80);
    QTimer::singleShot(1500,this, &LevelWindow::startCount);
}

void LevelWindow::startCount(){
    startDlg->close();
    setBlur(0);
    pause_b->start_time();
    state = 1;
}

void LevelWindow::timerEvent(QTimerEvent* event){
    if(event->timerId() == updateTimer)
    {
        curBKColor += colourStep;
        update();
    }
    if(curBKColor >= 245)
    {
        killTimer(updateTimer);
        startText1();
    }
    else if(curBKColor <= 0){
        killTimer(updateTimer);
        close();
    }
}

void LevelWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QBrush brush;
    brush.setColor(qRgba(curBKColor,curBKColor,curBKColor,1));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(rect());
}

void LevelWindow::closeGradually(){
    colourStep = -colourStep;
    updateTimer = startTimer(interval);
}

void LevelWindow::endGame(){
    setBlur(10);
    endDlg->open();
    QTimer::singleShot(1500, this, &LevelWindow::closeGradually);
}

void LevelWindow::hideEvent(QHideEvent* event){
    if(endDlg->isActiveWindow())
        endDlg->close();
    if(state)
    {
        if(state == 4)
            emit changeWindow(level+10);
        else if(state == 3)
            emit changeWindow(level+30);
        else
            emit changeWindow(2);
    }
    QMainWindow::hideEvent(event);
}

void LevelWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);
    updateTimer = startTimer(interval);
    if(state == 0)
    {
        setIniLive(live, liveBoss);
        update_List();
        set_mode(0);
    }
    else {
        qDebug()<<"error state";
        exit(0);
    }
    list->fixSize();
}

void LevelWindow::changeGameProcess(bool pause){
    if(pause)
    {
        state = 2;
        pause_b->pause_time();
    }
    else
    {
        pause_b->start_time();
        state = 1;
    }
}

void LevelWindow::restart(){
    clearList();
    state = 1;
    pause_b->start_time();
}

void LevelWindow::halfMovie(){
    switch(level){
    case 1:

        break;
    case 2:
        break;
    case 3:
        break;
    default:
        exit(0);
        break;
    }
}
