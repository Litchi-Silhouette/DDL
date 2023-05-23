#include "levelwindow.h"
#include "ui_levelwindow.h"
#include <QSizePolicy>
#include <QLayout>
#include <QDialog>
#include <QGraphicsEffect>
#include <QMessageBox>

LevelWindow::LevelWindow(QWidget *parent, const int cur_level)
    : QMainWindow(parent)
    , ui(new Ui::LevelWindow)
    , level(cur_level), live(100)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/page/level_image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));
    setStyleSheet("QMainWindow{background: rgba(245,245,245,1);}");
    setGeometry(200,150,800,450);

    pause_b = new pause_block(level,this);
    pause_b->setMaximumWidth(150);
    connect(pause_b->btn, &QPushButton::clicked, this, &LevelWindow::pause);
    pause_b->start_time();

    bar = new KeepRatioLiveBar(this);
    bar->set_live(live);

    warning = new KeepRatioWarning(this);
    warning->set_mode(2);

    list = new DDL_List(this);
    QPixmap test(":/page/level_image/icon_w.png");
    list->add_task(test,"sdf","asd",1);
    list->add_task(test,"sdf","asd",3);
    list->add_task(test,"sdf","asd",4);
    list->add_task(test,"ssf","asd",5);
    list->add_buff(test,"agfqf","sdga",2);

    map_border = new QFrame(this);
    map_border->setFrameShadow(QFrame::Sunken);
    map_border->setFrameShape(QFrame::Panel);
    map_border->setLineWidth(5);
    map_border->setMidLineWidth(5);

    pauseDlg  = new PauseDialog(this);

    auto up = new QHBoxLayout;
    auto main_lay = new QVBoxLayout;

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

    this->centralWidget()->setLayout(main_lay);
    timer_update = new QTimer(this);
    timer_update->start(interval);
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
}

void LevelWindow::pause(){
    //实现pause
    timer_update->stop();
    pause_b->pause_time();
    QGraphicsBlurEffect *blureffect = new QGraphicsBlurEffect;
    blureffect->setBlurRadius(30);
    setGraphicsEffect(blureffect);

    pauseDlg->exec();
    switch (pauseDlg->getChoice()) {
    case 1:
        hide();
        menu->show();
        break;
    case 2:
        //restart
        break;
    case 3:
        pause_b->start_time();
        break;
    default:
        break;
    }
    blureffect->setBlurRadius(0);
    setGraphicsEffect(blureffect);
}

void LevelWindow::setMenu(QMainWindow* _menu){
    menu = _menu;
}
