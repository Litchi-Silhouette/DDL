#include "pause_start_end.h"

PauseDialog::PauseDialog(QWidget* parent)
    :MyDialog(parent)
{
    backBtn = new QPushButton(this);
    backBtn->setStyleSheet("QPushButton{border-width:0px;"
                  "border-image:url(:/page/level_image/back_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/page/level_image/back_on_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/page/level_image/back.png);}"
                  );
    backBtn->setFixedSize(80,80);
    connect(backBtn, &QPushButton::clicked, this, &PauseDialog::back);
    restartBtn = new QPushButton(this);
    restartBtn->setStyleSheet("QPushButton{border-width:0px;"
                  "border-image:url(:/page/level_image/restart_gray.png);}"
                  "QPushButton:hover{border-image:url(:/page/level_image/restart.png);}"
                  );
    restartBtn->setFixedSize(80,80);
    connect(restartBtn,&QPushButton::clicked, this, &PauseDialog::restart);
    continueBtn = new QPushButton(this);
    continueBtn->setStyleSheet("QPushButton{border:0px;"
                  "border-image:url(:/page/level_image/continue_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/page/level_image/continue_on_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/page/level_image/continue.png);}"
                  );
    continueBtn->setFixedSize(80,80);
    connect(continueBtn, &QPushButton::clicked, this, &PauseDialog::conti);

    main_lay = new QHBoxLayout(this);
    main_lay->setSpacing(20);
    main_lay->addWidget(backBtn,1);
    main_lay->addWidget(restartBtn,1);
    main_lay->addWidget(continueBtn,1);

    setLayout(main_lay);
    clearMask();
}

PauseDialog::~PauseDialog(){
    delete restartBtn;
    delete backBtn;
    delete continueBtn;
    delete main_lay;
}

int PauseDialog::getChoice()const{
    return choice;
}

void PauseDialog::restart(){
    choice = 2;
    close();
}

void PauseDialog::back(){
    choice = 1;
    close();
}

void PauseDialog::conti(){
    choice = 3;
    close();
}

StartDialog::StartDialog(QWidget* parent)
    :MyDialog(parent)
{
    literature = new QLabel(this);
    literature->setFont(QFont("STHupo", 20, QFont::Bold));
    literature->setAlignment(Qt::AlignCenter);
    literature->setMinimumSize(400,200);
}

StartDialog::~StartDialog(){
    delete literature;
}

void StartDialog::setStartText(const QString& _text, int fontSize){
    auto temp = literature->font();
    temp.setPointSize(fontSize);
    literature->setFont(temp);
    literature->setText(_text);
}
