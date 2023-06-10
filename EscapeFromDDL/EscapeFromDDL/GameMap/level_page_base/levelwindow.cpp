#include "levelwindow.h"
#include "ui_levelwindow.h"
#include <QSizePolicy>
#include <QPainter>

LevelWindow::LevelWindow(Game& game, QWidget *parent, const int cur_level)
    : windowBase(parent)
    , level(cur_level)
    , statistics(game)
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

    auto it = statistics.all_buffs.find(level);
    if(it == statistics.all_buffs.end())
        statistics.all_buffs[level] = new ItemHash;
    it = statistics.all_tasks.find(level);
    if(it == statistics.all_tasks.end())
        statistics.all_tasks[level] = new ItemHash;
    list = new DDL_List((level == 3) ,this, &statistics.all_items , statistics.all_tasks[level], statistics.all_buffs[level]);

    map_border = new QFrame(this);
    map_border->setFrameShadow(QFrame::Sunken);
    map_border->setFrameShape(QFrame::Panel);
    map_border->setLineWidth(5);
    map_border->setMidLineWidth(5);

    pauseDlg  = new PauseDialog(game, this);
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

    blureffect = new QGraphicsBlurEffect(this);
    setGraphicsEffect(blureffect);
    blureffect->setEnabled(false);

    curMask = new CoverMask;
    connect(curMask, &CoverMask::showEnd, this, &LevelWindow::startText1);
    connect(curMask, &CoverMask::closeEnd, this, &LevelWindow::end);

    player = new QMediaPlayer(this);
    audio = new QAudioOutput(this);
    player->setAudioOutput(audio);
    player->setSource(QUrl("qrc:/bkmusic/BKMusic/level.mp3"));
    player->setLoops(QMediaPlayer::Infinite);

    start1 = new QSoundEffect(this);
    start1->setSource(QUrl("qrc:/effects/sounds/start1.wav"));
    start2 = new QSoundEffect(this);
    start2->setSource(QUrl("qrc:/effects/sounds/start2.wav"));
    buttom = new QSoundEffect(this);
    buttom->setSource(QUrl("qrc:/effects/sounds/buttom3.wav"));
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
    delete blureffect;
    delete curMask;
    delete player;
    delete audio;
    delete start1;
    delete start2;
    delete buttom;
}

void LevelWindow::pause(){
    setBlur(30);
    buttom->play();
    buttom->setMuted(!statistics.audioMode);
    buttom->setVolume((double)statistics.effect/10);
    changeGameProcess(true);

    pauseDlg->exec();
    switch (pauseDlg->getChoice()) {
    case 1:
        curMask->startClose();
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
    }
    else
        blureffect->setEnabled(false);
}

void LevelWindow::startText1(){
    setBlur(10);
    start1->play();
    start1->setMuted(!statistics.audioMode);
    start1->setVolume((double)statistics.effect/10);
    startDlg->open();
    startDlg->setStartText("好",90);
    QTimer::singleShot(1000,this, &LevelWindow::startText2);
}

void LevelWindow::startText2(){
    start1->play();
    start1->setMuted(!statistics.audioMode);
    start1->setVolume((double)statistics.effect/10);
    startDlg->setStartText("准备",60);
    QTimer::singleShot(1000,this, &LevelWindow::startText3);
}

void LevelWindow::startText3(){
    start2->play();
    start2->setMuted(!statistics.audioMode);
    start2->setVolume((double)statistics.effect/10);
    startDlg->setStartText("开始",80);
    QTimer::singleShot(2000,this, &LevelWindow::startCount);
}

void LevelWindow::startCount(){
    startDlg->close();
    setBlur(0);
    pause_b->start_time();
    state = 1;
    player->play();
    audio->setMuted(!statistics.audioMode);
    audio->setVolume((double)statistics.music/10);
}

void LevelWindow::endGame(){
    setBlur(10);
    endDlg->open();
    QTimer::singleShot(1500, this, &LevelWindow::end);
}

void LevelWindow::end(){
    if(endDlg->isActiveWindow())
        endDlg->close();
    player->stop();
    if(state)
    {
        if(state == 5)
            emit changeWindow(level+20);
        else if(state == 4){
            switch (level) {
            case 1:
            case 2:
                statistics.getActs[level] = true;
                break;
            case 3:
                statistics.getEndings[4] = true;
            default:
                break;
            }
            if(endDlg->getChoice())
                emit changeWindow(2);
            else
                emit changeWindow(level+10);
        }
        else if(state == 3){
            statistics.getEndings[level] = true;
            if(endDlg->getChoice())
                emit changeWindow(2);
            else
                emit changeWindow(level+30);
        }
        else
            emit changeWindow(2);
    }
    QTimer::singleShot(200, curMask, &CoverMask::close);
}

void LevelWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);
    curMask->setGeometry(geometry());
    curMask->move(mapToGlobal(QPoint(0, 0)));
    curMask->startShow();
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
        player->pause();
    }
    else
    {
        player->play();
        pause_b->start_time();
        state = 1;
    }
}

void LevelWindow::restart(){
    state = 5;
    end();
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
