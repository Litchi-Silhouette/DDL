#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    QPoint cur = ui->me->pos();
    QSize size = ui->me->size();
    event->accept();

    switch(event->key())
    {
    case Qt::Key_A:
        if(cur.x()-5>0)
            cur.rx() -=5;
        break;
    case Qt::Key_W:
        if(cur.y()-5>0)
            cur.ry() -=5;
        break;
    case Qt::Key_D:
        if(cur.x()+size.width()+5<this->width())
            cur.setX(cur.x()+5);
        break;
    case Qt::Key_S:
        if(cur.y()+size.height()+5<this->height())
            cur.setY(cur.y()+5);
        break;
    default:
        ui->me->setText(event->text());
        break;
    }
    ui->me->move(cur);
}
