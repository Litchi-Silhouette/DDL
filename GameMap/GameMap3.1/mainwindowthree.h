#ifndef MAINWINDOWTHREE_H
#define MAINWINDOWTHREE_H

#include <QWidget>
#include "mainwindow.h"


class MainWindowThree : public MainWindow
{
    Q_OBJECT

public:

    explicit MainWindowThree(QWidget *parent = nullptr);
    ~MainWindowThree();
    virtual void reset() override;

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
};


#endif // MAINWINDOWTHREE_H
