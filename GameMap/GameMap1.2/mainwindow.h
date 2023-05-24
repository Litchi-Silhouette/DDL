#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include "gamemap.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

//上级窗口（关卡），这里只是样例，实际开发继承wzl的levelwindow

class TaskBuff;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static int MOVE_UNIT;
    static int CELL_SIZE;
    static int X_BARRIER;
    static int Y_BARRIER;
    static int Y_TOOL_HEIGHT;
    static int HEIGHT;
    static int WIDTH;

    GameMap * pgamemap;
    QLabel * ptaskbuff_board;//for test
    MainWindow(QString MapType = "1",QWidget *parent = nullptr);
    ~MainWindow();
    void renew_taskbuff_board(TaskBuff * ptb);

protected:
    void keyPressEvent(QKeyEvent*) override;//需继承wzl的levelwindow并重载
    void resizeEvent(QResizeEvent *) override;//仅限第一关

private:

};

#endif // MAINWINDOW_H
