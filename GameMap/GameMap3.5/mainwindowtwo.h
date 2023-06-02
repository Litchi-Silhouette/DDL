
#ifndef MAINWINDOWTWO_H
#define MAINWINDOWTWO_H


#include <QWidget>
#include "mainwindow.h"

class MainWindowTwo : public MainWindow
{
    Q_OBJECT

public:
    static QPoint last_press_player_pos;

    explicit MainWindowTwo(QWidget *parent = nullptr);
    ~MainWindowTwo();


protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};



#endif // MAINWINDOWTWO_H
