#include "startwindow.h"
#include "ui_startwindow.h"
#include <QPainter>
StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/pic/image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));

    p = new QTimer(this);
    connect(p, &QTimer::timeout, this, &StartWindow::blink);
    connect(ui->pushButton, &QPushButton::clicked, this, &StartWindow::startBlink);
    connect(ui->tip, &QPushButton::clicked, this, &StartWindow::startBlink);
    connect(ui->back, &QPushButton::clicked, this, &StartWindow::startBlink);
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
    p->start(interval);
    QTimer::singleShot(1000, this, &StartWindow::stayRed);
}

void StartWindow::blink(){
    index = (index+1)&1;
    update();
}

void StartWindow::hideEvent(QHideEvent* event){
    QMainWindow::hideEvent(event);
    p->stop();
    emit changeWindow(2);
}

void StartWindow::stayRed(){
    p->stop();
    index = 1;
    update();
    QTimer::singleShot(1000, this, &StartWindow::close);
}
