#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointF>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void timerEvent(QTimerEvent *event) override;

private slots:
    void on_pushButton_clicked();

private:
    void move_boll();
    void move_DDL();
    std::pair<int, int> change_dir(const QPointF&); //first: 0不变，1横向，2纵向 second: 边界
    double len_dir(const QPointF&) const;

private:
    Ui::MainWindow *ui;
    QPointF dir;       //实时方向
    QPointF dir_store; //现行方向
    double me_steplen = 20;
    double DDL_steplen = 5;
    int interval_time = 30; //画面刷新频率
    int interval_speed = 100; //速度刷新频率
    int timer_painter; // 画面计时器
    int timer_speed;   // 速度改变计时器
};
#endif // MAINWINDOW_H
