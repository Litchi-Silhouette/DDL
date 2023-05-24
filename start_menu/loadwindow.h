#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "set_pausedialog.h"

namespace Ui {
class LoadWindow;
}

class LoadWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadWindow(QWidget *parent = nullptr);
    ~LoadWindow();
protected:
    void timerEvent(QTimerEvent*) override;
    void showEvent(QShowEvent*) override;
private:
    Ui::LoadWindow *ui;
    int updateTimer;
    StartDialog* center;

    int interval = 50;
    int mon = 5;
    int colour = 0;
};

#endif // LOADWINDOW_H
