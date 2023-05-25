#include "levelwindow.h"
#include "ui_levelwindow.h"
#include <QSizePolicy>

LevelWindow::LevelWindow(QWidget *parent, const int cur_level)
    : QMainWindow(parent)
    , ui(new Ui::LevelWindow)
    , level(cur_level)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/page/level_image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));
    setGeometry(0,0,1200,675);

    pause_b = new pause_block(level,this);
    pause_b->setMaximumWidth(150);
    connect(pause_b->btn, &QPushButton::clicked, this, &LevelWindow::pause);

    bar = new KeepRatioLiveBar(this);

    warning = new KeepRatioWarning(this);

    auto it = gamePages.all_buffs.find(level);
    if(it == gamePages.all_buffs.end())
        gamePages.all_buffs[level] = new ItemHash;
    it = gamePages.all_tasks.find(level);
    if(it == gamePages.all_tasks.end())
        gamePages.all_tasks[level] = new ItemHash;
    list = new DDL_List(this, &gamePages.all_items , gamePages.all_tasks[level], gamePages.all_buffs[level]);

    map_border = new QFrame(this);
    map_border->setFrameShadow(QFrame::Sunken);
    map_border->setFrameShape(QFrame::Panel);
    map_border->setLineWidth(5);
    map_border->setMidLineWidth(5);

    pauseDlg  = new PauseDialog(this);
    startDlg = new StartDialog(this);

    auto up = new QHBoxLayout;
    main_lay = new QVBoxLayout;

    up->setContentsMargins(5,5,5,0);
    up->setSpacing(5);
    up->addWidget(list);
    up->addWidget(warning);
    up->addWidget(bar);
    up->addWidget(pause_b);
    up->setStretchFactor(list,4);
    up->setStretchFactor(warning,1);
    up->setStretchFactor(bar,1);
    up->setStretchFactor(pause_b,1);

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
    delete blureffect;
}

void LevelWindow::pause(){
    setBlur(30);
    changeGameProcess(true);

    pauseDlg->exec();
    switch (pauseDlg->getChoice()) {
    case 1:
        hide();
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
    blureffect->setBlurRadius(extent);
    setGraphicsEffect(blureffect);
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

void LevelWindow::endGame(){
    setBlur(10);
    startDlg->open();
    startDlg->setStartText("游戏结束",50);
    QTimer::singleShot(1500, this, &LevelWindow::turnNext);
}

void LevelWindow::turnNext(){
    startDlg->close();
    hide();
}

void LevelWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);
    if(state == 0)
    {
        update_live();
        update_List();
        set_mode(0);
        QTimer::singleShot(1000,this, &LevelWindow::startText1);
    }
    else if(state ==1 || state == 2)
        QTimer::singleShot(100,this, &LevelWindow::pause);
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

void LevelWindow::hideEvent(QHideEvent* event){
    QMainWindow::hideEvent(event);
    gamePages.nextlevel((level+1)%2+1)->show();
}

void LevelWindow::restart(){
    clearList();
    state = 1;
    pause_b->start_time();
}

