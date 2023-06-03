#include "actwindow.h"
#include "ui_actwindow.h"
#include <QUrl>

ActWindow::ActWindow(Game& game, int index, QWidget *parent)
    : windowBase(parent)
    , ui(new Ui::ActWindow)
    , pageindex(index)
    , statistics(game)
{
    ui->setupUi(this);
    p = new QPushButton("Click to continue···");
    p->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->pageLay2->addWidget(p);
    switch (index) {
    case 0:
        path = "qrc:/videos/videos/Prologue.mp4";
        break;
    case 1:
        path = "qrc:/videos/videos/act1.mp4";
        break;
    case 2:
        path = "qrc:/videos/videos/act2.mp4";
        break;
    case 3:
        path = "qrc:/videos/videos/ending4.mp4";
        break;
    case 4:
        path = "qrc:/videos/videos/final.mp4";
        break;
    default:
        break;
    }
    player = new QMediaPlayer(this);
    video = new QVideoWidget(this);
    video->setAttribute(Qt::WA_OpaquePaintEvent);
    player->setVideoOutput(video);
    player->setSource(QUrl(path));
    ui->pageLay1->addWidget(video);

    ui->stackedWidget->setCurrentIndex(0);
    connect(player, &QMediaPlayer::playingChanged, this, [=](bool is){
        if(!is&& pageindex != 3)
            ui->stackedWidget->setCurrentIndex(1);
        else if(!is){
            acc = new AccDialog(4, this);
            connect(acc, &AccDialog::end, this, [=](){
                emit changeWindow(2);
            });
            acc->exec();
        }
    });
    connect(p, &QPushButton::clicked, this, [=](){
        switch (pageindex) {
        case 0:
            statistics.getLevels[1] = true;
            emit changeWindow(21);
            break;
        case 1:
            statistics.getLevels[2] = true;
            emit changeWindow(22);
            break;
        case 2:
            statistics.getLevels[3] = true;
            emit changeWindow(23);
            break;
        case 4:
            emit changeWindow(2);
            break;
        default:
            break;
        }
    });
}

ActWindow::~ActWindow()
{
    delete ui;
    if(acc)
        delete acc;
}

void ActWindow::showEvent(QShowEvent* event){
    windowBase::showEvent(event);
    player->play();
}
