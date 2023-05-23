#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include "gamemap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class TaskBuff;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    GameMap * pgamemap;
    QLabel * ptaskbuff_board;
    MainWindow(QString MapType = "1",QWidget *parent = nullptr);
    ~MainWindow();
    void renew_taskbuff_board(TaskBuff * ptb);

protected:
    void keyPressEvent(QKeyEvent*) override;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
