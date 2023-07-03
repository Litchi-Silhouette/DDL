#ifndef MAINWINDOWONE_H
#define MAINWINDOWONE_H

#include <QWidget>
#include "mainwindow.h"

class MainWindowOne : public MainWindow
{
    Q_OBJECT

public:
    explicit MainWindowOne(QWidget *parent = nullptr);
    ~MainWindowOne();


protected:
    void keyPressEvent(QKeyEvent*) override;
};

#endif // MAINWINDOWONE_H
