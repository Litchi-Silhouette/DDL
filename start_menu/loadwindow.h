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
    void paintEvent(QPaintEvent* event) override;
signals:
    void changeWindow(int index);
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
