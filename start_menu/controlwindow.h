#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "startwindow.h"
#include "loadwindow.h"
#include "menuwindow.h"

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();
protected slots:
    void showEvent(QShowEvent*);
private slots:
    void toWindow(int index);
private:
    Ui::ControlWindow *ui;
    QStackedWidget* mainWidget;
    LoadWindow* load;
    StartWindow* start;
    MenuWindow* menu;
};

#endif // CONTROLWINDOW_H
