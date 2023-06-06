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

    p = new QTimer(this);
    connect(p, &QTimer::timeout, this, &StartWindow::blink);
    connect(ui->pushButton, &QPushButton::clicked, this, &StartWindow::startBlink);
    connect(ui->tip, &QPushButton::clicked, this, &StartWindow::startBlink);
    connect(ui->back, &QPushButton::clicked, this, &StartWindow::startBlink);

    player = new QMediaPlayer(this);
    audio = new QAudioOutput(this);
    player->setAudioOutput(audio);
    player->setSource(QUrl("qrc:/bkmusic/BKMusic/start.mp3"));

}

StartWindow::~StartWindow()
{
    delete ui;
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
    blink();
    ui->tip->hide();
    p->start(interval);
    QTimer::singleShot(1000, this, &StartWindow::stayRed);
}

void StartWindow::blink(){
    index = (index+1)&1;
    update();
}

void StartWindow::showEvent(QShowEvent* event){
    windowBase::showEvent(event);
    player->play();
    audio->setMuted(!statistics.audioMode);
    audio->setVolume((double)statistics.music/10);
}

void StartWindow::hideEvent(QHideEvent* event){
    QMainWindow::hideEvent(event);
    p->stop();
    player->stop();
    emit changeWindow(2);
}

void StartWindow::stayRed(){
    p->stop();
    index = 1;
    update();
    QTimer::singleShot(1000, this, &StartWindow::close);
}
