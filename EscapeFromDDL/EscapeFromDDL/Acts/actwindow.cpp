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
    p->setFocus();
    p->setDefault(true);
    p->setFocusPolicy(Qt::StrongFocus);
    p->setShortcut(QKeySequence(Qt::Key_N));
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
        path = "qrc:/videos/videos/finalplus.mp4";
        break;
    default:
        break;
    }
    player = new QMediaPlayer(this);
    video = new QVideoWidget(this);
    audio = new QAudioOutput(this);
    player->setVideoOutput(video);
    player->setAudioOutput(audio);
    player->setSource(QUrl(path));
    video->setAttribute(Qt::WA_OpaquePaintEvent);
    ui->pageLay1->addWidget(video);

    buttom = new QSoundEffect(this);
    buttom->setSource(QUrl("qrc:/effects/sounds/buttom3.wav"));

    ui->stackedWidget->setCurrentIndex(0);
    connect(player, &QMediaPlayer::playingChanged, this, [=](bool is){
        if(!is && pageindex == 4)
            emit changeWindow(2);
        else if(!is && pageindex == 3){
            acc = new AccDialog(statistics, 4, this);
            connect(acc, &AccDialog::end, this, [=](){
                emit changeWindow(2);
            });
            acc->exec();
        }else if(!is){
            curMask->show();
            QTimer::singleShot(100, this, [=](){
                ui->stackedWidget->setCurrentIndex(1);
                QTimer::singleShot(400, curMask, &CoverMask::close);
            });
        }
    });
    connect(p, &QPushButton::clicked, this, [=](){
        buttom->play();
        buttom->setMuted(!statistics.audioMode);
        buttom->setVolume((double)statistics.effect/10);
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
        default:
            qDebug()<<"invalid index acts";
            break;
        }
    });
}

ActWindow::~ActWindow()
{
    delete ui;
    if(acc)
        delete acc;
    delete p;
    delete player;
    delete audio;
    delete video;
    delete buttom;
}

void ActWindow::showEvent(QShowEvent* event){
    windowBase::showEvent(event);
    curMask = new CoverMask;
    curMask->setGeometry(geometry());
    curMask->move(mapToGlobal(QPoint(0, 0)));
    player->play();
    audio->setMuted(!statistics.audioMode);
    audio->setVolume((double)statistics.music/10);
}
