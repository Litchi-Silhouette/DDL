#include "figure.h"
#include "ui_figure.h"
#include "gamemap.h"
#include "ui_gamemap.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskbuff.h"
#include "ui_taskbuff.h"
#include <QKeyEvent>
#include <QString>
#include <utils.cpp>



MainWindow::MainWindow(QString MapType,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (MapType == "1")
        pgamemap = new GameMapOne(this);
    else
        pgamemap = new GameMap(this);
    resize(1280,720);
    ptaskbuff_board = new QLabel(this);
    ptaskbuff_board->move(100,0);
    ptaskbuff_board->resize(1000,100);
    ptaskbuff_board->setText("Empty task list");
    ptaskbuff_board->show();
}

MainWindow::~MainWindow()
{
    delete pgamemap;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    static qint64 lastKeyPressTime = 0;
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    QPoint cur = pgamemap->pfigure->pos();
    QSize size = pgamemap->pfigure->size();
    event->accept();

    switch(event->key())
    {
    case Qt::Key_A:
        cur.rx() -=MOVE_UNIT;break;
    case Qt::Key_W:
        cur.ry() -=MOVE_UNIT;break;
    case Qt::Key_D:
        cur.setX(cur.x()+MOVE_UNIT);break;
    case Qt::Key_S:
        cur.setY(cur.y()+MOVE_UNIT);break;
    default:
        return;
    }

    if(currentTime - lastKeyPressTime < MIN_KEYEVENT_INTERVAL) return;

    pgamemap->pfigure->move_in_grid(cur);
    lastKeyPressTime = currentTime;
}

void MainWindow::renew_taskbuff_board(TaskBuff * ptb){
    ptaskbuff_board->setText("名称 "+ptb->name+"\n文字 "+ptb->explanation);
}
