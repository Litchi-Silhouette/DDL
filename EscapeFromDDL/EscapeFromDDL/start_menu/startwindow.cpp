#include "startwindow.h"
#include "ui_startwindow.h"
#include <QPainter>
#include <QUrl>

StartWindow::StartWindow(Game& game, QWidget *parent)
    : windowBase(parent)
    , ui(new Ui::StartWindow)
    , statistics(game)
{
    ui->setupUi(this);
    curMask = new CoverMask;
    p = new QTimer(this);
    connect(p, &QTimer::timeout, this, &StartWindow::blink);
    connect(ui->pushButton, &QPushButton::clicked, this, &StartWindow::startBlink);
    connect(ui->tip, &QPushButton::clicked, this, &StartWindow::startBlink);
    connect(ui->back, &QPushButton::clicked, this, &StartWindow::startBlink);

    player = new QMediaPlayer(this);
    audio = new QAudioOutput(this);
    player->setAudioOutput(audio);
    player->setSource(QUrl("qrc:/bkmusic/BKMusic/start.mp3"));
    player->setLoops(QMediaPlayer::Infinite);
    enter = new QSoundEffect(this);
    enter->setSource(QUrl("qrc:/effects/sounds/entering.wav"));
}

StartWindow::~StartWindow()
{
    delete ui;
    delete player;
    delete audio;
    delete enter;
    delete curMask;
}

void StartWindow::paintEvent(QPaintEvent*){
    QPixmap back;
    QPainter painter(this);
    if(index)
        back.load(on);
    else
        back.load(nor);

    painter.drawPixmap(rect(),back);
}

void StartWindow::startBlink(){
    player->stop();
    enter->play();
    enter->setMuted(!statistics.audioMode);
    enter->setVolume((double)statistics.effect/10);
    ui->tip->hide();
    p->start(interval);
    QTimer::singleShot(2500, this, &StartWindow::stayRed);
}

void StartWindow::blink(){
    index = (index+1)&1;
    update();
}

void StartWindow::showEvent(QShowEvent* event){
    windowBase::showEvent(event);
    curMask->setGeometry(geometry());
    curMask->move(mapToGlobal(QPoint(0, 0)));
    curMask->show();
    player->play();
    audio->setMuted(!statistics.audioMode);
    audio->setVolume((double)statistics.music/10);
    QTimer::singleShot(1000, curMask, &CoverMask::close);
}

void StartWindow::hideEvent(QHideEvent* event){
    QMainWindow::hideEvent(event);
    emit changeWindow(2);
}

void StartWindow::stayRed(){
    index = 1;
    p->stop();
    update();
    QTimer::singleShot(3000, this, &StartWindow::close);
}
