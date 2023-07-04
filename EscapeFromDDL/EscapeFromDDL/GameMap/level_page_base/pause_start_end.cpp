#include "pause_start_end.h"

PauseDialog::PauseDialog(Game& game, QWidget* parent)
    :MyDialog(parent),statistics(game)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    backBtn = new QPushButton(this);
    backBtn->setStyleSheet("QPushButton{border-width:0px;"
                  "border-image:url(:/page/level_image/back_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/page/level_image/back_on_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/page/level_image/back.png);}"
                  "QPushButton:focus{outline: none;}"
                  );
    backBtn->setFixedSize(80,80);
    connect(backBtn, &QPushButton::clicked, this, &PauseDialog::back);
    backBtn->setShortcut(QKeySequence(Qt::Key_B));
    restartBtn = new QPushButton(this);
    restartBtn->setStyleSheet("QPushButton{border-width:0px;"
                  "border-image:url(:/page/level_image/restart_gray.png);}"
                  "QPushButton:hover{border-image:url(:/page/level_image/restart.png);}"
                  "QPushButton:focus{outline: none;}"
                  );
    restartBtn->setFixedSize(80,80);
    connect(restartBtn,&QPushButton::clicked, this, &PauseDialog::restart);
    restartBtn->setShortcut(QKeySequence(Qt::Key_R));
    continueBtn = new QPushButton(this);
    continueBtn->setStyleSheet("QPushButton{border:0px;"
                  "border-image:url(:/page/level_image/continue_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/page/level_image/continue_on_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/page/level_image/continue.png);}"
                  "QPushButton:focus{outline: none;}"
                  );
    continueBtn->setFixedSize(80,80);
    connect(continueBtn, &QPushButton::clicked, this, &PauseDialog::conti);
    continueBtn->setShortcut(QKeySequence(Qt::Key_C));

    buttom = new QSoundEffect(this);
    buttom->setSource(QUrl("qrc:/effects/sounds/buttom2.wav"));

    main_lay = new QHBoxLayout(this);
    main_lay->setSpacing(20);
    main_lay->addStretch();
    main_lay->addWidget(backBtn,1);
    main_lay->addWidget(restartBtn,1);
    main_lay->addWidget(continueBtn,1);
    main_lay->addStretch();
    setLayout(main_lay);

}

PauseDialog::~PauseDialog(){
    delete restartBtn;
    delete backBtn;
    delete continueBtn;
    delete main_lay;
    delete buttom;
}

int PauseDialog::getChoice()const{
    return choice;
}

void PauseDialog::restart(){
    buttom->play();
    buttom->setMuted(!statistics.audioMode);
    buttom->setVolume((double)statistics.effect/10);
    choice = 2;
    close();
}

void PauseDialog::back(){
    buttom->play();
    buttom->setMuted(!statistics.audioMode);
    buttom->setVolume((double)statistics.effect/10);
    choice = 1;
    close();
}

void PauseDialog::conti(){
    buttom->play();
    buttom->setMuted(!statistics.audioMode);
    buttom->setVolume((double)statistics.effect/10);
    choice = 3;
    close();
}

EndDialog::EndDialog(QWidget* parent):
    MyDialog(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    backBtn = new QPushButton(this);
    backBtn->setStyleSheet("QPushButton{border-width:0px;"
                           "border-image:url(:/page/level_image/back_nor_gray.png);}"
                           "QPushButton:hover{border-image:url(:/page/level_image/back_on_gray.png);}"
                           "QPushButton:pressed{border-image:url(:/page/level_image/back.png);}"
                           );
    backBtn->setFixedSize(80,80);
    connect(backBtn, &QPushButton::clicked, this, &EndDialog::back);

    nextBtn = new QPushButton(this);
    nextBtn->setStyleSheet("QPushButton{border:0px;"
                            "border-image:url(:/page/level_image/continue_nor_gray.png);}"
                            "QPushButton:hover{border-image:url(:/page/level_image/continue_on_gray.png);}"
                            "QPushButton:pressed{border-image:url(:/page/level_image/continue.png);}"
                            );
    nextBtn->setFixedSize(80,80);
    connect(nextBtn, &QPushButton::clicked, this, &EndDialog::next);

    literature = new QLabel(this);
    literature->setText("游戏结束");
    literature->setFont(QFont("华文楷体",50, QFont::Bold));
    literature->adjustSize();
    literature->setFixedSize(literature->size());

    auto mainLay = new QGridLayout(this);
    mainLay->setSpacing(10);
    mainLay->addWidget(literature,0,0,1,2, Qt::AlignHCenter | Qt::AlignBottom);
    mainLay->addWidget(backBtn,1,0,1,1, Qt::AlignTop |Qt::AlignRight);
    mainLay->addWidget(nextBtn,1,1,1,1, Qt::AlignTop |Qt::AlignLeft);
    setLayout(mainLay);
}

EndDialog::~EndDialog()
{
    delete backBtn;
    delete nextBtn;
    delete literature;
}

void EndDialog::next(){
    choice = 0;
    close();
}

void EndDialog::back(){
    choice = 1;
    close();
}
