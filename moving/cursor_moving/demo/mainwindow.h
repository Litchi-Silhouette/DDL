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
    void timerEvent(QTimerEvent*) override;
    void paintEvent(QPaintEvent*) override;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void move_boll();
    void move_DDL();
    void getdir();
    double len_dir(const QPointF&) const;

private:
    Ui::MainWindow *ui;
    QPointF dir;    //非标准化的dir
    double me_steplen = 10;
    double DDL_steplen = 5;
    int interval = 20; //刷新频率
    int timer_id;// 计时器
};
#endif // MAINWINDOW_H
