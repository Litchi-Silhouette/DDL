#include "loadwindow.h"
#include "ui_loadwindow.h"
#include <QTimerEvent>
#include <QLayout>
#include <QPainter>

LoadWindow::LoadWindow(QWidget *parent):
    QMainWindow{parent},
    ui(new Ui::LoadWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/pic/image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));

    center = new StartDialog(this);
    center->setAttribute(Qt::WA_DeleteOnClose, true);
    center->resetFont(QFont("STKaiti", 20, QFont::Bold));
    center->setStartText("     3W    出品", 60);
    center->setMinimumSize(550,200);
}

LoadWindow::~LoadWindow(){
    delete ui;
}

void LoadWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);
    updateTimer = startTimer(interval);
    QTimer::singleShot(1,center, &StartDialog::show);
    QTimer::singleShot(1500, this, &LoadWindow::closeGradully);
}

void LoadWindow::timerEvent(QTimerEvent* event){
    if(event->timerId() == updateTimer)
    {
        colour += mon;
        update();
    }
    if(colour >= 245)
        killTimer(updateTimer);
    else if(colour == 0){
        killTimer(updateTimer);
        center->close();
        emit changeWindow(1);
        close();
    }
}

void LoadWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QBrush brush;
    brush.setColor(qRgba(colour,colour,colour,1));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(rect());
}

void LoadWindow::closeGradully(){
    mon = -10;
    updateTimer = startTimer(interval);
}
