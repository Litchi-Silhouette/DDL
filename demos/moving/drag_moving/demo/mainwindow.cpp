#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dir(QPointF(0,0)), dir_store(QPointF(0,0))
{
    ui->setupUi(this);
    timer_painter = startTimer(interval_time);
    timer_speed = startTimer(interval_speed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        dir = event->globalPosition()-ui->me->pos()
                -QPoint(ui->me->width(),ui->me->height());
        dir /= len_dir(dir);
        event->accept();
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        me_steplen = 2;
        DDL_steplen =1;
    }
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        dir_store = dir;
        me_steplen = 20;
        DDL_steplen = 10;
    }
    event->accept();
}

void MainWindow::move_boll()
{
    QPointF cur = ui->me->pos();
    QPointF next = cur+dir_store*me_steplen;
    double steptemp = me_steplen;
    std::pair<int, int> sig = change_dir(next);

    switch (sig.first) {
    case 1:
        steptemp = fabs(sig.second - cur.x())/dir_store.x();
        next = cur+dir_store*steptemp;
        dir_store.rx() = -dir_store.x();
        break;
    case 2:
        steptemp = fabs(sig.second - cur.y())/dir_store.y();
        next = cur+dir_store*steptemp;
        dir_store.ry() = -dir_store.y();
        break;
    default:
        break;
    }
    ui->me->move(next.toPoint());
}

void MainWindow::move_DDL()
{
    QPointF temp_dir = ui->me->pos() + QPointF(ui->me->width()/2,ui->me->height()/2)
            - ui->enemy->pos() - QPointF(ui->enemy->width()/2,ui->enemy->height()/2);
    if(dir_store!=QPointF(0,0))
        if(len_dir(temp_dir)>=(ui->me->width()+ui->enemy->width())/2)
    {
        DDL_steplen = 2+15*len_dir(temp_dir)/(this->width()+this->height());
        temp_dir /= len_dir(temp_dir);
        QPointF next = ui->enemy->pos()+temp_dir*DDL_steplen;
        ui->enemy->move(next.toPoint());
    }
}

std::pair<int, int> MainWindow::change_dir(const QPointF& temp)
{
    QSize cur = this->size() - ui->me->size();
    if(temp.x()<0)
        return std::make_pair(1,0);
    if(temp.x()>cur.width())
        return std::make_pair(1,cur.width());
    if(temp.y()<0)
        return std::make_pair(2,0);
    if(temp.y()>cur.height())
        return std::make_pair(2,cur.height());
    return std::make_pair(0,-1);
}

double MainWindow::len_dir(const QPointF& dir_temp) const
{
    return sqrt(dir_temp.x()*dir_temp.x()+dir_temp.y()*dir_temp.y());
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    if(event->timerId() == timer_painter)
    {
        move_boll();
        move_DDL();
    }
    else if(event->timerId() == timer_speed && me_steplen>0)
    {
        me_steplen -=1;
    }
    event->accept();
}

void MainWindow::on_pushButton_clicked()
{
    dir_store = QPointF(0,0);
}

