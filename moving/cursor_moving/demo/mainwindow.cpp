#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <cmath>
#include <QCursor>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dir(QPointF(0,0))
    , me_steplen(0),DDL_steplen(0)
{
    ui->setupUi(this);
    timer_id = startTimer(interval);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::move_boll()
{
    if(len_dir(dir)>sqrt(2)*ui->me->width()/2)
    {
        QPointF cur = ui->me->pos();
        QPointF next = cur+dir/len_dir(dir)*me_steplen;
        QSize temp = this->size()-ui->me->size();
        if(next.x()>0 && next.y()>0 &&
                next.x()<temp.width()&&next.y()<temp.height())
            ui->me->move(next.toPoint());
    }
}

void MainWindow::move_DDL()
{
    QPointF temp_dir = ui->me->pos() + QPointF(ui->me->width()/2,ui->me->height()/2)
            - ui->enemy->pos() - QPointF(ui->enemy->width()/2,ui->enemy->height()/2);
    if(len_dir(temp_dir)>=(ui->enemy->width()+ui->me->width())/2)
        {
            temp_dir /= len_dir(temp_dir);
            QPointF next = ui->enemy->pos()+temp_dir*DDL_steplen;
            ui->enemy->move(next.toPoint());
        }
}


double MainWindow::len_dir(const QPointF& dir) const
{
    return sqrt(dir.x()*dir.x()+dir.y()*dir.y());
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    if(event->timerId() == timer_id)
    {
        getdir();
        update();
        move_boll();
        move_DDL();
    }
    event->accept();
}

void MainWindow::getdir()
{
    dir = QCursor::pos() - ui->me->pos()
            - QPointF(ui->me->width()/2, ui->me->height()/2);
}

void MainWindow::paintEvent(QPaintEvent*)
{
    if(len_dir(dir)>ui->me->width()/2)
    {
        QPainter painter(this);
        QPen pen;
        pen.setColor(Qt::black);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setWidth(10);
        painter.setPen(pen);

        QLineF line(QCursor::pos()-QPoint(0,20)
                    ,ui->me->pos()+QPoint(ui->me->width()/2,ui->me->height()/2));
        painter.drawLine(line);
        line.setAngle(line.angle()+45);
        line.setLength(30);
        painter.drawLine(line);
        line.setAngle(line.angle()-90);
        painter.drawLine(line);
    }
}

void MainWindow::on_pushButton_clicked()
{
    me_steplen = DDL_steplen = 0;
}


void MainWindow::on_pushButton_2_clicked()
{
    me_steplen = 10;
    DDL_steplen = 5;
}

