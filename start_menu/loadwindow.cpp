#include "loadwindow.h"
#include "ui_loadwindow.h"
#include <QTimerEvent>
#include <QLayout>
LoadWindow::LoadWindow(QWidget *parent):
    QMainWindow{parent},
    ui(new Ui::LoadWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/page/level_image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));

    center = new StartDialog(this);
    center->setAttribute(Qt::WA_DeleteOnClose, true);
    center->resetFont(QFont("STKaiti", 20, QFont::Bold));
    center->setStartText("3W——项目组", 60);
    center->setMinimumSize(550,200);
}

LoadWindow::~LoadWindow(){
    delete ui;
}

void LoadWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);
    updateTimer = startTimer(interval);
    QTimer::singleShot(100,center, &StartDialog::show);
    QTimer::singleShot(1500, center, &StartDialog::close);
}

void LoadWindow::timerEvent(QTimerEvent* event){
    if(event->timerId() == updateTimer)
    {
        colour += mon;
        setStyleSheet(QString("QMainWindow{background: rgba(%1,%2,%3,1);}").arg(colour,colour,colour));
        update();
    }
    if(colour == 245)
        killTimer(updateTimer);
}
