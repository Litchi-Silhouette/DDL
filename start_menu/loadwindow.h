#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <QTimer>
#include "Game.hpp"
#include "windowbase.h"

namespace Ui {
class LoadWindow;
}

class LoadWindow : public windowBase
{
    Q_OBJECT

public:
    explicit LoadWindow(QWidget *parent = nullptr);
    ~LoadWindow();
protected:
    void timerEvent(QTimerEvent*) override;
    void showEvent(QShowEvent*) override;
    void paintEvent(QPaintEvent* event) override;

private slots:
    void closeGradully();
private:
    Ui::LoadWindow *ui;
    int updateTimer;
    StartDialog* center;

    int interval = 40;
    int mon = 10;
    int colour = 0;
};

#endif // LOADWINDOW_H
