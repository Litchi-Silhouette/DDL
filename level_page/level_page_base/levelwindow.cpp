#include "levelwindow.h"
#include "ui_levelwindow.h"
#include <QSizePolicy>
#include <QLayout>
#include <QDialog>
#include <QMessageBox>

LevelWindow::LevelWindow(QWidget *parent, const int cur_level)
    : QMainWindow(parent)
    , ui(new Ui::LevelWindow)
    , level(cur_level), live(100)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/page/level_image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));
    setGeometry(200,150,800,450);

    pause_b = new pause_block(level,this);
    connect(pause_b->btn, &QPushButton::clicked, this, &LevelWindow::pause);
    pause_b->start_time();

    bar = new live_bar(this);
    bar->set_live(live);

    warning = new warning_icon(this);
    warning->set_mode(2);

    list = new DDL_List(this);
    QIcon test(":/page/level_image/icon_w.png");
    list->add_task(test,"sdf","asd");
    list->add_buff(test,"agfqf","sdga");

    map_border = new QFrame(this);
    map_border->setFrameShadow(QFrame::Sunken);
    map_border->setFrameShape(QFrame::Panel);
    map_border->setLineWidth(5);
    map_border->setMidLineWidth(5);

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
}

void LevelWindow::pause(){
    //实现pause
    timer_update->stop();
    pause_b->pause_time();
    QMessageBox temp(this);
    temp.setIcon(QMessageBox::Information);
    temp.setText(QString("Sure to exit?"));

    QPushButton *yesBtn = temp.addButton(QString("exit(&Y)"),
                                        QMessageBox::YesRole );
    QPushButton *canBtn = temp.addButton(QString("cancel"),
                                         QMessageBox::RejectRole);

    temp.exec();
    if(temp.clickedButton() == yesBtn)
        close();
    else if(temp.clickedButton() == canBtn)
        pause_b->start_time();
}
